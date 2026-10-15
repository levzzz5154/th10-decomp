#!/usr/bin/env python3
"""Compare the THA1 index loader's state/call ordering with retail x86.

Requires native clang++ and Python's unicorn. File, codec, allocator and index
parser collaborators are scripted; their implementations are outside this test.
Run: python3 matching2/tests/dat_archive_load_index_differential.py
"""

import argparse
from dataclasses import dataclass, replace
from itertools import product
from pathlib import Path
import struct
import subprocess
import tempfile

from unicorn import Uc, UC_ARCH_X86, UC_MODE_32, UC_HOOK_CODE
from unicorn.x86_const import (UC_X86_REG_EAX, UC_X86_REG_ECX, UC_X86_REG_ESI,
                              UC_X86_REG_ESP, UC_X86_REG_EIP)
from dat_archive_read_differential import (
    ROOT, CANDIDATE, TEMPORARY, STATE, DECODED, STACK, STOP, ARCHIVE, RECORD,
    QUERY, FILE, OTHER_FILE, VTABLE, DECRYPT_MODEL, SEEK, READ, PRESERVED,
    PEImage, load_manifest, load_oracle, load_candidate)

ENTRY = 0x434F70
OPEN = CANDIDATE + 0x2000
GET_SIZE = CANDIDATE + 0x2400
DELETE_FILE = CANDIDATE + 0x2500
OLD_ENTRIES = STATE + 0x900


@dataclass(frozen=True)
class Case:
    file_present: bool = True
    open_result: int = 1
    header_read_result: int = 16
    valid_magic: bool = True
    stored_size: int = 31
    unpacked_size: int = 64
    entry_count: int = 3
    file_size: int = 4096
    seek_result: int = 1
    malloc_fails: bool = False
    data_read_result: int = 31
    decode_fails: bool = False
    build_fails: bool = False
    mutate_header: bool = False
    switch_file: bool = False
    mutate_count: bool = False
    mutate_on_free: bool = False


def compile_candidate(path):
    subprocess.run([
        "clang++", "--target=i686-pc-windows-msvc", "-O2", "-mno-sse", "-mno-sse2",
        "-fno-exceptions", "-fno-rtti", "-fno-stack-protector", "-ffunction-sections",
        "-I", str(ROOT / "matching2/msvc/include"), "-c",
        str(ROOT / "matching2/reference/semantic_candidates/dat_archive_load_index.cpp"),
        "-o", str(path)], check=True, timeout=60)


def execute(image, code, case):
    uc = Uc(UC_ARCH_X86, UC_MODE_32)
    uc.mem_map(0x400000, 0x100000)
    for section in image.sections:
        uc.mem_write(section["address"], image.read(section["address"], section["raw_size"]))
    for address in (CANDIDATE, TEMPORARY, STATE, DECODED, STACK, STOP):
        uc.mem_map(address, 0x10000)
    if code:
        uc.mem_write(CANDIDATE, code)
    for address in (TEMPORARY, DECODED):
        uc.mem_write(address, b"\xA5" * 256)

    def words(address, *values):
        uc.mem_write(address, struct.pack("<" + "I" * len(values),
                                         *(value & 0xFFFFFFFF for value in values)))

    words(ARCHIVE, OLD_ENTRIES, 9, STATE + 0xA00, FILE if case.file_present else 0)
    words(FILE, VTABLE)
    words(OTHER_FILE, VTABLE)
    words(VTABLE, OPEN, 0, READ, 0, 0, GET_SIZE, SEEK, DELETE_FILE)
    uc.mem_write(QUERY, b"test.dat\0")
    arguments = [ARCHIVE, QUERY] if code else [QUERY]
    sp = STACK + 0x8000
    words(sp, STOP, *arguments)
    uc.reg_write(UC_X86_REG_ESP, sp)
    uc.reg_write(UC_X86_REG_EAX, 0xABCDEF34)
    expected_preserved = dict(PRESERVED)
    if not code:
        expected_preserved[UC_X86_REG_ESI] = ARCHIVE
    for register, value in expected_preserved.items():
        uc.reg_write(register, value)
    events = []
    header_pointer = None
    header_after_decode = None

    def args(count):
        current = uc.reg_read(UC_X86_REG_ESP)
        return struct.unpack("<" + "I" * count, uc.mem_read(current + 4, count * 4))

    def finish(result, argument_bytes):
        current = uc.reg_read(UC_X86_REG_ESP)
        uc.reg_write(UC_X86_REG_EAX, result & 0xFFFFFFFF)
        uc.reg_write(UC_X86_REG_EIP, struct.unpack("<I", uc.mem_read(current, 4))[0])
        uc.reg_write(UC_X86_REG_ESP, current + 4 + argument_bytes)

    def hook(machine, address, size, context):
        nonlocal header_pointer, header_after_decode
        receiver = uc.reg_read(UC_X86_REG_ECX)
        if address == OPEN:
            path, mode = args(2)
            events.append(("open", receiver, path, mode))
            finish(case.open_result, 8)
        elif address == READ:
            destination, count = args(2)
            is_header = STACK <= destination < STACK + 0x10000
            events.append(("read", receiver, "header" if is_header else destination, count))
            if is_header:
                header_pointer = destination
                # The collaborator fills the header even when it reports a
                # nonzero short result, isolating the caller's success test.
                uc.mem_write(destination, b"\xCC" * 16)
                finish(case.header_read_result, 8)
            else:
                uc.mem_write(destination, bytes(index & 255 for index in range(count)))
                finish(case.data_read_result, 8)
        elif address in (0x44B0D0, DECRYPT_MODEL):
            if address == DECRYPT_MODEL:
                data, count, key, step, block, limit = args(6)
            else:
                data, count, step, block, limit = args(5)
                key = uc.reg_read(UC_X86_REG_EAX) & 255
            is_header = data == header_pointer
            events.append(("decrypt", "header" if is_header else data, count, key, step, block, limit))
            if is_header:
                words(data, 0x31414854 if case.valid_magic else 0,
                      case.unpacked_size + 123456789, case.stored_size + 987654321,
                      case.entry_count + 135792468)
                header_after_decode = bytes(uc.mem_read(data, 16))
            finish(0xBAD00001, 24 if address == DECRYPT_MODEL else 20)
        elif address == GET_SIZE:
            # Capture the caller's in-place bias subtraction before further I/O.
            events.append(("size", receiver, bytes(uc.mem_read(header_pointer, 16)),
                           bytes(uc.mem_read(ARCHIVE, 16))))
            if case.mutate_header:
                words(header_pointer + 8, 5)
            finish(case.file_size, 0)
        elif address == SEEK:
            distance, origin = args(2)
            events.append(("seek", receiver, distance, origin))
            if case.mutate_header:
                words(header_pointer + 4, 77, 9)
            if case.switch_file:
                words(ARCHIVE + 12, OTHER_FILE)
            finish(case.seek_result, 8)
        elif address == 0x452706:
            requested, = args(1)
            events.append(("malloc", requested))
            finish(0 if case.malloc_fails else TEMPORARY, 0)
        elif address == 0x435DC0:
            data, count, output, capacity = args(4)
            events.append(("decompress", data, count, output, capacity))
            if case.mutate_count:
                words(ARCHIVE + 4, 0x25)
            if not case.decode_fails:
                uc.mem_write(DECODED, b"\xD3" * min(capacity, 128))
            finish(0 if case.decode_fails else DECODED, 16)
        elif address == 0x4350D0:
            data, count, terminal_offset = args(3)
            events.append(("build", data, count, terminal_offset))
            finish(0 if case.build_fails else RECORD, 12)
        elif address == 0x452422:
            pointer, = args(1)
            events.append(("free", pointer))
            if case.mutate_on_free:
                words(ARCHIVE, OLD_ENTRIES)
                words(ARCHIVE + 12, OTHER_FILE)
            finish(0xBAD00002, 0)
        elif address == DELETE_FILE:
            flags, = args(1)
            events.append(("delete", receiver, flags))
            finish(0xBAD00003, 4)
        else:
            raise AssertionError(f"unexpected call {address:#x}")

    for address in (OPEN, READ, GET_SIZE, SEEK, DELETE_FILE, 0x44B0D0, DECRYPT_MODEL,
                    0x452706, 0x435DC0, 0x4350D0, 0x452422):
        uc.hook_add(UC_HOOK_CODE, hook, begin=address, end=address)
    uc.emu_start(CANDIDATE if code else ENTRY, STOP, count=1000000)
    assert uc.reg_read(UC_X86_REG_EIP) == STOP, "instruction budget exhausted"
    assert uc.reg_read(UC_X86_REG_ESP) == sp + 4 * (len(arguments) + 1)
    for register, value in expected_preserved.items():
        assert uc.reg_read(register) == value, "callee-saved register clobbered"
    return {"events": events, "result": uc.reg_read(UC_X86_REG_EAX) & 255,
            "archive": bytes(uc.mem_read(ARCHIVE, 16)),
            "buffers": tuple(bytes(uc.mem_read(address, 256)) for address in (TEMPORARY, DECODED)),
            "header_after_decode": header_after_decode}


def cases():
    for index, values in enumerate(product((0, 1, 0xABCD0000, 0xABCD0001),
                                          (0, 1, 16), (False, True), (False, True),
                                          (0, 1, 31), (False, True), (False, True))):
        opened, read, valid, malloc_fails, data_read, decode_fails, build_fails = values
        yield Case(open_result=opened, header_read_result=read, valid_magic=valid,
                   malloc_fails=malloc_fails, data_read_result=data_read,
                   decode_fails=decode_fails, build_fails=build_fails,
                   seek_result=index % 2)
    yield Case(file_present=False)
    for size in (0, 1, 30, 31, 32, 0xFFFFFFFF):
        yield Case(file_size=size, seek_result=0)
    for count in (0, 1, 0x7FFFFFFF, 0x80000000, 0xFFFFFFFF):
        yield Case(entry_count=count)
    yield Case(stored_size=0, unpacked_size=0, data_read_result=1)
    yield Case(stored_size=0xFFFFFFF0, malloc_fails=True)
    yield Case(unpacked_size=0xFFFFFFF0, decode_fails=True)
    for mutate_header, switch_file, mutate_count, mutate_on_free, build_fails in product((False, True), repeat=5):
        yield Case(mutate_header=mutate_header, switch_file=switch_file,
                   mutate_count=mutate_count, mutate_on_free=mutate_on_free, build_fails=build_fails)


import sys as _project_sys
from pathlib import Path as _ProjectPath
_project_sys.path.insert(0, str(_ProjectPath(__file__).resolve().parents[2]))
from matching2.tools.common.project_paths import project_support
def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--object", type=Path)
    parser.add_argument("--oracle", type=Path, default=ROOT / "matching2/build/oracle/th10.exe")
    options = parser.parse_args()
    config = load_manifest(project_support((ROOT) / 'matching2/msvc', 'regions.json'))
    load_oracle(options.oracle, config)
    image = PEImage(options.oracle.read_bytes())
    with tempfile.TemporaryDirectory(prefix="th10-archive-index-") as temporary:
        obj = options.object or Path(temporary) / "load_index.obj"
        if options.object is None:
            compile_candidate(obj)
        bindings = {"_g_dat_archive_read_mode": 0x474908,
                    "_Dat_Decrypt_0044b0d0@24": DECRYPT_MODEL,
                    "_DecompressDatLzss_00435dc0@16": 0x435DC0,
                    "_DatArchive_BuildIndex_004350d0@12": 0x4350D0}
        code = load_candidate(obj, config, "DatArchive_LoadIndex_00434f70", bindings)
        count = 0
        for case in cases():
            retail = execute(image, None, case)
            candidate = execute(image, code, case)
            assert retail == candidate, (case, retail, candidate)
            count += 1
        failed = execute(image, code, Case(malloc_fails=True))
        entries, entry_count, filename, file = struct.unpack("<4I", failed["archive"])
        assert failed["result"] == 0 and entries == OLD_ENTRIES and entry_count == 3 and file == 0
        wrapped = execute(image, code, Case(file_size=1, seek_result=0))
        assert wrapped["result"] == 1 and ("seek", FILE, (1 - 31) & 0xFFFFFFFF, 0) in wrapped["events"]
        print(f"PASS: {count} index-loader cases agree with retail on header decoding, "
              f"archive state, collaborator calls and cleanup. Clang body: {len(code)} bytes; "
              "private ABI and MSVC bytes remain unverified.")


if __name__ == "__main__":
    main()
