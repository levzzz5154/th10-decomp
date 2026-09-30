#!/usr/bin/env python3
"""Compare the archive-read candidate's control flow and ownership with retail.

Run with native clang++ and Python's unicorn package:
  python3 matching2/tests/dat_archive_read_differential.py

File operations, lookup, allocation and codecs are scripted collaborators.
The test checks their ordered calls and memory effects; it does not claim to
test a complete archive file or recover the private entry/callee ABIs.
"""

import argparse
from dataclasses import dataclass, replace
from itertools import product
from pathlib import Path
import struct
import subprocess
import tempfile

from unicorn import Uc, UC_ARCH_X86, UC_MODE_32, UC_HOOK_CODE
from unicorn.x86_const import (UC_X86_REG_EAX, UC_X86_REG_EBX, UC_X86_REG_ECX,
                              UC_X86_REG_ESP, UC_X86_REG_EIP)
from lzss_compressor_differential import (
    ROOT, CANDIDATE, OUTPUT, STACK, STOP, PRESERVED, PEImage,
    load_manifest, load_oracle, load_candidate)

ENTRY = 0x434DD0
TEMPORARY = 0x2200000
STATE = 0x2500000
DECODED = 0x2600000
ARCHIVE = STATE + 0x100
RECORD = STATE + 0x200
QUERY = STATE + 0x400
STORED_NAME = STATE + 0x500
CHANGED_NAME = STATE + 0x600
FILE = STATE + 0x700
OTHER_FILE = STATE + 0x710
VTABLE = STATE + 0x800
FIND_MODEL = CANDIDATE + 0x2000
DECRYPT_MODEL = CANDIDATE + 0x2100
SEEK = CANDIDATE + 0x2200
READ = CANDIDATE + 0x2300


@dataclass(frozen=True)
class Case:
    stored_size: int = 19
    unpacked_size: int = 37
    supplied_output: bool = False
    file_present: bool = True
    entry_found: bool = True
    malloc_fails: bool = False
    seek_result: int = 1
    read_result: int = 19
    decode_fails: bool = False
    stored_name: bytes = b"Reimu.anm"
    mutate_on_malloc: bool = False
    mutate_on_seek: bool = False
    mutate_on_read: bool = False
    allocation_is_output: bool = False


def compile_candidate(path):
    subprocess.run([
        "clang++", "--target=i686-pc-windows-msvc", "-O2", "-fno-exceptions",
        "-fno-rtti", "-fno-stack-protector", "-ffunction-sections",
        "-I", str(ROOT / "matching2/msvc/include"), "-c",
        str(ROOT / "matching2/reference/semantic_candidates/dat_archive_read.cpp"),
        "-o", str(path)], check=True, timeout=60)


def execute(image, code, case):
    uc = Uc(UC_ARCH_X86, UC_MODE_32)
    uc.mem_map(0x400000, 0x100000)
    for section in image.sections:
        uc.mem_write(section["address"], image.read(section["address"], section["raw_size"]))
    for address in (CANDIDATE, OUTPUT, TEMPORARY, STATE, DECODED, STACK, STOP):
        uc.mem_map(address, 0x10000)
    if code:
        uc.mem_write(CANDIDATE, code)
    for address in (OUTPUT, TEMPORARY, DECODED):
        uc.mem_write(address, b"\xA5" * 0x100)

    def words(address, *values):
        uc.mem_write(address, struct.pack("<" + "I" * len(values), *values))

    words(ARCHIVE, RECORD, 1, 0, FILE if case.file_present else 0)
    words(RECORD, STORED_NAME, 0x120, case.unpacked_size, 0,
          0, 0x120 + case.stored_size, 0, 0)
    uc.mem_write(QUERY, b"reimu.ANM\0")
    uc.mem_write(STORED_NAME, case.stored_name + b"\0")
    uc.mem_write(CHANGED_NAME, b"\xFFchanged.dat\0")
    words(FILE, VTABLE)
    words(OTHER_FILE, VTABLE)
    words(VTABLE, 0, 0, READ, 0, 0, 0, SEEK, 0)
    output = OUTPUT if case.supplied_output else 0
    arguments = [ARCHIVE, QUERY, output] if code else [ARCHIVE, output]
    sp = STACK + 0x8000
    words(sp, STOP, *arguments)
    uc.reg_write(UC_X86_REG_ESP, sp)
    uc.reg_write(UC_X86_REG_ECX, QUERY)
    for register, value in PRESERVED.items():
        uc.reg_write(register, value)
    events = []
    frees = []

    def arguments_on_stack(count):
        current_sp = uc.reg_read(UC_X86_REG_ESP)
        return struct.unpack("<" + "I" * count, uc.mem_read(current_sp + 4, 4 * count))

    def finish(value, argument_bytes):
        current_sp = uc.reg_read(UC_X86_REG_ESP)
        uc.reg_write(UC_X86_REG_EAX, value & 0xFFFFFFFF)
        uc.reg_write(UC_X86_REG_EIP, struct.unpack("<I", uc.mem_read(current_sp, 4))[0])
        uc.reg_write(UC_X86_REG_ESP, current_sp + 4 + argument_bytes)

    def hook(machine, address, size, context):
        if address in (0x434F30, FIND_MODEL):
            if address == FIND_MODEL:
                archive, name = arguments_on_stack(2)
            else:
                archive, name = uc.reg_read(UC_X86_REG_EAX), uc.reg_read(UC_X86_REG_EBX)
            events.append(("find", archive, name))
            finish(RECORD if case.entry_found else 0, 8 if address == FIND_MODEL else 0)
        elif address == 0x452706:
            requested, = arguments_on_stack(1)
            events.append(("malloc", requested))
            if case.mutate_on_malloc:
                words(RECORD + 4, 0x240, 0x71)
            allocation = OUTPUT if case.allocation_is_output else TEMPORARY
            finish(0 if case.malloc_fails else allocation, 0)
        elif address == 0x452422:
            pointer, = arguments_on_stack(1)
            events.append(("free", pointer))
            frees.append(pointer)
            finish(0xBAD00001, 0)
        elif address == SEEK:
            distance, origin = arguments_on_stack(2)
            events.append(("seek", uc.reg_read(UC_X86_REG_ECX), distance, origin))
            if case.mutate_on_seek:
                words(ARCHIVE + 12, OTHER_FILE)
            finish(case.seek_result, 8)
        elif address == READ:
            destination, requested = arguments_on_stack(2)
            events.append(("read", uc.reg_read(UC_X86_REG_ECX), destination, requested))
            copied = min(requested, case.read_result)
            uc.mem_write(destination, bytes((index * 13 + 7) & 255 for index in range(copied)))
            if case.mutate_on_read:
                words(RECORD, CHANGED_NAME)
                words(RECORD + 8, 0x77)
            finish(case.read_result, 8)
        elif address in (0x44B0D0, DECRYPT_MODEL):
            if address == DECRYPT_MODEL:
                data, count, key, step, block, limit = arguments_on_stack(6)
            else:
                data, count, step, block, limit = arguments_on_stack(5)
                key = uc.reg_read(UC_X86_REG_EAX) & 255
            events.append(("decrypt", data, count, key, step, block, limit))
            uc.mem_write(data, bytes(value ^ 0x5A for value in uc.mem_read(data, count)))
            # Both callers must ignore the cipher helper's returned pointer.
            finish(0xBAD00002, 24 if address == DECRYPT_MODEL else 20)
        elif address == 0x435DC0:
            source, count, destination, capacity = arguments_on_stack(4)
            events.append(("decompress", source, count, destination, capacity,
                           bytes(uc.mem_read(source, count))))
            result = 0 if case.decode_fails else destination or DECODED
            if result:
                uc.mem_write(result, bytes((index * 7 + 0xD3) & 255 for index in range(capacity)))
            finish(result, 16)
        else:
            raise AssertionError(f"unhandled collaborator {address:#x}")

    for address in (0x434F30, FIND_MODEL, 0x452706, 0x452422, SEEK, READ,
                    0x44B0D0, DECRYPT_MODEL, 0x435DC0):
        uc.hook_add(UC_HOOK_CODE, hook, begin=address, end=address)
    uc.emu_start(CANDIDATE if code else ENTRY, STOP, count=1000000)
    assert uc.reg_read(UC_X86_REG_EIP) == STOP, "instruction budget exhausted"
    assert uc.reg_read(UC_X86_REG_ESP) == sp + 4 * (len(arguments) + 1)
    for register, value in PRESERVED.items():
        assert uc.reg_read(register) == value, "callee-saved register clobbered"
    for address in (OUTPUT, TEMPORARY, DECODED):
        assert bytes(uc.mem_read(address + 0x80, 0x80)) == b"\xA5" * 0x80
    return {"events": events, "frees": frees, "result": uc.reg_read(UC_X86_REG_EAX),
            "buffers": tuple(bytes(uc.mem_read(address, 0x100))
                             for address in (OUTPUT, TEMPORARY, DECODED)),
            "archive": bytes(uc.mem_read(ARCHIVE, 16)),
            "entries": bytes(uc.mem_read(RECORD, 32))}


def cases():
    for (stored, unpacked), supplied, allocation_failure, seek, read, decode_failure in product(
            ((0, 0), (0, 19), (19, 19), (19, 37), (37, 19)), (False, True),
            (False, True), (0, 1, 0xABCD0000, 0xABCD0001), (0, 1, 19, 0x80000000),
            (False, True)):
        yield Case(stored_size=stored, unpacked_size=unpacked, supplied_output=supplied,
                   malloc_fails=allocation_failure, seek_result=seek, read_result=read,
                   decode_fails=decode_failure)
    yield Case(file_present=False)
    yield Case(entry_found=False)
    for name in (b"", b"\xFF", b"\x80high.dat", *(bytes([97 + index]) for index in range(8))):
        yield Case(stored_name=name)
    for supplied in (False, True):
        for on_malloc, on_seek, on_read in product((False, True), repeat=3):
            yield Case(supplied_output=supplied, mutate_on_malloc=on_malloc,
                       mutate_on_seek=on_seek, mutate_on_read=on_read)
        yield Case(supplied_output=supplied, allocation_is_output=True)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--object", type=Path)
    parser.add_argument("--oracle", type=Path, default=ROOT / "matching2/build/oracle/th10.exe")
    args = parser.parse_args()
    config = load_manifest(ROOT / "matching2/msvc/regions.json")
    load_oracle(args.oracle, config)
    image = PEImage(args.oracle.read_bytes())
    with tempfile.TemporaryDirectory(prefix="th10-archive-read-") as temporary:
        obj = args.object or Path(temporary) / "archive_read.obj"
        if args.object is None:
            compile_candidate(obj)
        bindings = {"_Archive_FindEntry_00434f30@8": FIND_MODEL,
                    "_Dat_Decrypt_0044b0d0@24": DECRYPT_MODEL,
                    "_g_dat_read_crypt_parameters": 0x474BD8,
                    "_DecompressDatLzss_00435dc0@16": 0x435DC0}
        code = load_candidate(obj, config, "DatArchive_Read_00434dd0", bindings)
        count = 0
        for case in cases():
            retail = execute(image, None, case)
            candidate = execute(image, code, case)
            assert candidate == retail, case
            count += 1
        raw = Case(stored_size=19, unpacked_size=19)
        dangling = execute(image, code, raw)
        assert dangling["result"] == TEMPORARY and dangling["frees"] == [TEMPORARY]
        failed = execute(image, code, replace(raw, supplied_output=True, seek_result=0))
        assert failed["result"] == 0 and failed["frees"] == [OUTPUT]
        print(f"PASS: {count} archive-read cases agree with retail on collaborator calls, "
              f"buffer contents, return values and cleanup. Clang body: {len(code)} bytes; "
              "private entry and helper ABIs remain unverified.")


if __name__ == "__main__":
    main()
