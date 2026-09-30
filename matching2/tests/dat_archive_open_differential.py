#!/usr/bin/env python3
"""Compare archive openers and filename duplication with retail x86.

Compile the real candidates with native clang++ and execute under Unicorn.
Close, index loading, allocation and the final virtual Open are scripted;
string duplication executes its actual retail or candidate instructions.
"""

import argparse
from dataclasses import dataclass
from itertools import product
from pathlib import Path
import random
import struct
import subprocess
import tempfile

from unicorn import Uc, UC_ARCH_X86, UC_MODE_32, UC_HOOK_CODE
from unicorn.x86_const import (UC_X86_REG_EAX, UC_X86_REG_ECX, UC_X86_REG_ESI,
                              UC_X86_REG_EDI, UC_X86_REG_ESP, UC_X86_REG_EIP)
from lzss_compressor_differential import (
    ROOT, CANDIDATE, STACK, STOP, PRESERVED,
    PEImage, load_manifest, load_oracle, load_candidate)
from dat_archive_cleanup_differential import CLOSE

OPEN, OPEN_RESOURCE, DUPLICATE = CANDIDATE + 0xD000, CANDIDATE + 0xD200, CANDIDATE + 0xD400
LOAD = CANDIDATE
STATE, STORAGE = 0x2500000, 0x2600000
ARCHIVE, FILE, OTHER_FILE = STATE + 0x100, STORAGE + 0x100, STORAGE + 0x200
PATH, COPY, RECORD, OLD_FILENAME = STATE + 0x1000, STORAGE + 0x1000, STATE + 0x400, STATE + 0x500


@dataclass(frozen=True)
class Case:
    allocate_file: bool = True
    load_result: int = 1
    allocate_name: bool = True
    reopen_result: int = 1
    load_clears_file: bool = False
    mutate_after_load: bool = False
    mutate_on_malloc: bool = False
    mutate_on_reopen: bool = False
    path: bytes = b"archive.dat"


def compile_candidates(directory, config):
    bindings = {"_DatArchive_Close_00434d10@4": CLOSE,
                "_DatArchive_LoadIndex_00434f70@8": LOAD,
                "_LegacyString_Duplicate_00435220@4": DUPLICATE,
                "_g_dat_archive_read_mode": 0x474908,
                "??_7FileHandle@@6B@": 0x46F230,
                "??_7ResourceFile@@6B@": 0x46F328}
    modules = {}
    for source, targets in (
            ("dat_archive_open.cpp", ((OPEN, "DatArchive_Open_00434c30"),
                                      (OPEN_RESOURCE, "DatArchive_OpenResource_00434ca0"))),
            ("legacy_string_duplicate.cpp", ((DUPLICATE, "LegacyString_Duplicate_00435220"),))):
        path = directory / (source + ".obj")
        subprocess.run([
            "clang++", "--target=i686-pc-windows-msvc", "-O2", "-mno-sse", "-mno-sse2",
            "-fno-builtin", "-fno-exceptions", "-fno-rtti", "-fno-stack-protector",
            "-ffunction-sections", "-I", str(ROOT / "matching2/msvc/include"), "-c",
            str(ROOT / "matching2/reference/semantic_candidates" / source), "-o", str(path)],
            check=True, timeout=60)
        for address, symbol in targets:
            modules[address] = load_candidate(path, config, symbol, bindings, code_address=address)
    return modules


def execute(image, modules, operation, case):
    uc = Uc(UC_ARCH_X86, UC_MODE_32)
    uc.mem_map(0x400000, 0x100000)
    for section in image.sections:
        uc.mem_write(section["address"], image.read(section["address"], section["raw_size"]))
    for address in (CANDIDATE, STACK, STOP, STATE, STORAGE):
        uc.mem_map(address, 0x10000)
    for address, code in modules.items():
        uc.mem_write(address, code)
    uc.mem_write(STORAGE, b"\xA5" * 0x10000)

    def words(address, *values):
        uc.mem_write(address, struct.pack("<" + "I" * len(values),
                                         *(value & 0xFFFFFFFF for value in values)))

    def string(address):
        result = bytearray()
        while True:
            byte = uc.mem_read(address + len(result), 1)[0]
            if not byte:
                return bytes(result)
            result.append(byte)
            assert len(result) < 4096

    words(ARCHIVE, RECORD, 13, OLD_FILENAME, OTHER_FILE)
    words(OTHER_FILE, 0x46F230, 0x77777777, 0x88888888)
    uc.mem_write(PATH, case.path + b"\0")
    sp = STACK + 0x8000
    expected_preserved = dict(PRESERVED)
    if operation == "duplicate":
        entry = DUPLICATE if modules else 0x435220
        arguments = [PATH] if modules else []
        if not modules:
            expected_preserved[UC_X86_REG_EDI] = PATH
    else:
        assert operation in ("disk", "resource")
        entry = (OPEN if operation == "disk" else OPEN_RESOURCE) if modules else (
            0x434C30 if operation == "disk" else 0x434CA0)
        arguments = [ARCHIVE, PATH] if modules else []
        uc.reg_write(UC_X86_REG_ECX, ARCHIVE)
        uc.reg_write(UC_X86_REG_EAX, PATH)
    words(sp, STOP, *arguments)
    uc.reg_write(UC_X86_REG_ESP, sp)
    for register, value in expected_preserved.items():
        uc.reg_write(register, value)
    events = []

    def args(count):
        current = uc.reg_read(UC_X86_REG_ESP)
        return struct.unpack("<" + "I" * count, uc.mem_read(current + 4, count * 4))

    def finish(result, argument_bytes=0):
        current = uc.reg_read(UC_X86_REG_ESP)
        uc.reg_write(UC_X86_REG_EIP, struct.unpack("<I", uc.mem_read(current, 4))[0])
        uc.reg_write(UC_X86_REG_ESP, current + 4 + argument_bytes)
        uc.reg_write(UC_X86_REG_EAX, result & 0xFFFFFFFF)

    def hook(machine, address, size, context):
        state = bytes(uc.mem_read(ARCHIVE, 16))
        if address in (CLOSE, 0x434D10):
            archive = args(1)[0] if address == CLOSE else uc.reg_read(UC_X86_REG_ESI)
            assert archive == ARCHIVE
            events.append(("close", state))
            words(ARCHIVE, 0, 0, 0, 0)
            finish(0xD0C00099, 4 if address == CLOSE else 0)
        elif address == 0x452493:
            requested, = args(1)
            assert requested == (12 if operation == "disk" else 16)
            events.append(("new", requested, state))
            finish(FILE if case.allocate_file else 0)
        elif address in (LOAD, 0x434F70):
            if address == LOAD:
                archive, path = args(2)
            else:
                archive, path = uc.reg_read(UC_X86_REG_ESI), args(1)[0]
            assert (archive, path) == (ARCHIVE, PATH)
            expected_file = ((0x46F230, 0xFFFFFFFF, 0, 0xA5A5A5A5) if operation == "disk"
                             else (0x46F328, 0, 0, 0))
            actual_file = struct.unpack("<4I", uc.mem_read(FILE, 16))
            assert actual_file == expected_file
            events.append(("load", path, actual_file, state))
            words(ARCHIVE, RECORD, 7, OLD_FILENAME if case.mutate_after_load else 0,
                  0 if case.load_clears_file else OTHER_FILE if case.mutate_after_load else FILE)
            if case.mutate_after_load:
                uc.mem_write(PATH, b"changed.dat\0")
            finish(case.load_result, 8 if address == LOAD else 4)
        elif address == 0x452706:
            requested, = args(1)
            events.append(("malloc", requested, state))
            if case.mutate_on_malloc:
                uc.mem_write(PATH, b"x\0")
                words(ARCHIVE + 8, OLD_FILENAME, OTHER_FILE)
            finish(COPY if case.allocate_name else 0)
        elif address == 0x435370:
            path, mode = args(2)
            events.append(("reopen", uc.reg_read(UC_X86_REG_ECX), path, string(path), string(mode), state))
            if case.mutate_on_reopen:
                words(ARCHIVE, 0, 0, 0, 0)
            finish(case.reopen_result, 8)
        else:
            raise AssertionError(f"unexpected hook {address:#x}")

    for address in (CLOSE, 0x434D10, 0x452493, LOAD, 0x434F70, 0x452706, 0x435370):
        uc.hook_add(UC_HOOK_CODE, hook, begin=address, end=address)
    uc.emu_start(entry, STOP, count=1000000)
    assert uc.reg_read(UC_X86_REG_EIP) == STOP
    assert uc.reg_read(UC_X86_REG_ESP) == sp + 4 * (len(arguments) + 1)
    for register, value in expected_preserved.items():
        assert uc.reg_read(register) == value
    result = uc.reg_read(UC_X86_REG_EAX)
    if operation == "duplicate":
        assert result == (COPY if case.allocate_name else 0)
        assert len(events) == 1 and events[0][:2] == ("malloc", len(case.path) + 1)
        if result:
            assert string(result) == (b"x" if case.mutate_on_malloc else case.path)
    else:
        result &= 255
        assert result == int(case.allocate_file and bool(case.load_result & 255) and case.allocate_name)
    return {"events": events, "result": result, "archive": bytes(uc.mem_read(ARCHIVE, 16)),
            "storage": bytes(uc.mem_read(STORAGE, 0x4000)), "path": bytes(uc.mem_read(PATH, 0x1000))}


def opening_cases():
    for allocated, loaded, copied, reopened in product((False, True),
            (0, 1, 0xABCD0000, 0xABCD0080), (False, True), (0, 1, 0xABCD0000, 0xABCD0001)):
        yield Case(allocate_file=allocated, load_result=loaded, allocate_name=copied, reopen_result=reopened)
    for loaded, copied, after_load, on_malloc, on_reopen in product(
            (0, 1), (False, True), (False, True), (False, True), (False, True)):
        yield Case(load_result=loaded, allocate_name=copied, mutate_after_load=after_load,
                   mutate_on_malloc=on_malloc, mutate_on_reopen=on_reopen)
    yield Case(load_result=0, load_clears_file=True)


def duplication_cases():
    randomizer = random.Random(0x435220)
    samples = [b"", b"a", b"\x80\xFFpath", b"a" * 1023]
    samples.extend(bytes(randomizer.randrange(1, 256) for _ in range(size)) for size in range(65))
    for path in samples:
        for allocate, mutate in product((False, True), repeat=2):
            yield Case(path=path, allocate_name=allocate, mutate_on_malloc=mutate)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--oracle", type=Path, default=ROOT / "matching2/build/oracle/th10.exe")
    options = parser.parse_args()
    config = load_manifest(ROOT / "matching2/msvc/regions.json")
    load_oracle(options.oracle, config)
    image = PEImage(options.oracle.read_bytes())
    with tempfile.TemporaryDirectory(prefix="th10-archive-open-") as temporary:
        modules = compile_candidates(Path(temporary), config)
        counts = {}
        for operation, cases in (("disk", opening_cases()), ("resource", opening_cases()),
                                 ("duplicate", duplication_cases())):
            counts[operation] = 0
            for case in cases:
                retail = execute(image, {}, operation, case)
                recovered = execute(image, modules, operation, case)
                assert retail == recovered, (operation, case, retail, recovered)
                counts[operation] += 1
        print(f"PASS: {counts['disk']} disk-open, {counts['resource']} resource-open and "
              f"{counts['duplicate']} string-copy cases agree with retail. Clang bytes: " +
              ", ".join(str(len(modules[a])) for a in (OPEN, OPEN_RESOURCE, DUPLICATE)) +
              "; retail: 108, 100, 47. Private ABIs and MSVC matching remain unverified.")


if __name__ == "__main__":
    main()
