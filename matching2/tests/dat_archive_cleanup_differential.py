#!/usr/bin/env python3
"""Compare archive cleanup and entry deletion with retail x86.

Requires native clang++ and Python's unicorn. The actual retail vector
destructor helper and entry-release callbacks execute in both runs; only
free and the virtual file deleting destructor are scripted. Throwing
destructors are not injected. No private ABI or MSVC byte match is claimed.
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
                              UC_X86_REG_ESP, UC_X86_REG_EIP)
from lzss_compressor_differential import (
    ROOT, CANDIDATE, STACK, STOP, PRESERVED,
    PEImage, load_manifest, load_oracle, load_candidate)

CLOSE, RESET, DELETE = CANDIDATE + 0xA000, CANDIDATE + 0xA800, CANDIDATE + 0xAA00
STATE, ARRAYS, NAMES = 0x2500000, 0x2600000, 0x2700000
ARCHIVE, FILE, OTHER_FILE, VTABLE = STATE + 0x100, STATE + 0x200, STATE + 0x210, STATE + 0x300
ENTRIES, OTHER_ENTRIES = ARRAYS + 0x100, ARRAYS + 0x500
FILENAME, CHANGED_FILENAME = NAMES + 0x100, NAMES + 0x200
FILE_DELETE = CANDIDATE + 0xE000


@dataclass(frozen=True)
class Case:
    array_count: int = 4
    archive_count: int = 3
    name_bits: int = 15
    filename: bool = True
    entries: bool = True
    file: bool = True
    flags: int = 3
    swap_on_filename: bool = False
    swap_on_name: bool = False
    swap_on_array: bool = False
    mutate_on_delete: bool = False
    mutate_cookie: bool = False


def compile_candidates(directory, config):
    specifications = (
        (CLOSE, "dat_archive_close_00434d10.cpp", "DatArchive_Close_00434d10"),
        (RESET, "dat_archive_reset_00434c20.cpp", "DatArchive_Reset_00434c20"),
        (DELETE, "dat_archive_entry_delete.cpp", "DatArchiveEntry_Delete_00434d70"))
    bindings = {"_DatArchive_Close_00434d10@4": CLOSE,
                "@ArchiveEntry_Release_00435250@4": 0x435250,
                "_asm_eh_vector_destructor_iterator_004525ff@16": 0x4525FF}
    result = {}
    for address, source, symbol in specifications:
        obj = directory / (source + ".obj")
        subprocess.run([
            "clang++", "--target=i686-pc-windows-msvc", "-O2", "-fno-exceptions",
            "-fno-rtti", "-fno-stack-protector", "-ffunction-sections",
            "-I", str(ROOT / "matching2/msvc/include"), "-c",
            str(ROOT / "matching2/reference/semantic_candidates" / source), "-o", str(obj)],
            check=True, timeout=60)
        result[address] = load_candidate(obj, config, symbol, bindings, code_address=address)
    return result


def execute(image, modules, operation, case):
    uc = Uc(UC_ARCH_X86, UC_MODE_32)
    uc.mem_map(0x400000, 0x100000)
    for section in image.sections:
        uc.mem_write(section["address"], image.read(section["address"], section["raw_size"]))
    for address in (CANDIDATE, STACK, STOP, STATE, ARRAYS, NAMES):
        uc.mem_map(address, 0x10000)
    uc.mem_map(0, 0x1000)
    for address, code in modules.items():
        uc.mem_write(address, code)
    uc.mem_write(ARRAYS, b"\xA5" * 0x10000)

    def words(address, *values):
        uc.mem_write(address, struct.pack("<" + "I" * len(values),
                                         *(value & 0xFFFFFFFF for value in values)))

    words(0, 0xFEE1DEAD)
    words(ARCHIVE, ENTRIES if case.entries else 0, case.archive_count,
          FILENAME if case.filename else 0, FILE if case.file else 0)
    for entries, count, bits in ((ENTRIES, case.array_count, case.name_bits),
                                 (OTHER_ENTRIES, 2, 3)):
        words(entries - 4, count)
        for index in range(max(1, count)):
            name = NAMES + 0x1000 + (entries - ENTRIES) + index * 32 if bits & (1 << index) else 0
            words(entries + index * 16, name, 0x100 + index, 0x200 + index, 0x300 + index)
    words(FILE, VTABLE)
    words(OTHER_FILE, VTABLE)
    words(VTABLE + 28, FILE_DELETE)
    arguments = []
    expected_preserved = dict(PRESERVED)
    if operation == "delete":
        arguments = [ENTRIES, case.flags] if modules else [case.flags]
        if not modules:
            expected_preserved[UC_X86_REG_ESI] = ENTRIES
        entry = DELETE if modules else 0x434D70
    elif operation == "close":
        arguments = [ARCHIVE] if modules else []
        if not modules:
            expected_preserved[UC_X86_REG_ESI] = ARCHIVE
        entry = CLOSE if modules else 0x434D10
    else:
        assert operation == "reset"
        uc.reg_write(UC_X86_REG_ECX, ARCHIVE)
        entry = RESET if modules else 0x434C20
    sp = STACK + 0x8000
    words(sp, STOP, *arguments)
    uc.reg_write(UC_X86_REG_ESP, sp)
    for register, value in expected_preserved.items():
        uc.reg_write(register, value)
    events, releases = [], []
    mutated_name = False

    def args(count):
        current = uc.reg_read(UC_X86_REG_ESP)
        return struct.unpack("<" + "I" * count, uc.mem_read(current + 4, count * 4))

    def finish(argument_bytes=0):
        current = uc.reg_read(UC_X86_REG_ESP)
        uc.reg_write(UC_X86_REG_EIP, struct.unpack("<I", uc.mem_read(current, 4))[0])
        uc.reg_write(UC_X86_REG_ESP, current + 4 + argument_bytes)
        uc.reg_write(UC_X86_REG_EAX, 0xBAD00001)

    def hook(machine, address, size, context):
        nonlocal mutated_name
        state = bytes(uc.mem_read(ARCHIVE, 16))
        if address in (0x452422, 0x4524A1):
            pointer, = args(1)
            events.append(("free", address, pointer, state))
            if address == 0x452422 and pointer == FILENAME and case.swap_on_filename:
                words(ARCHIVE, OTHER_ENTRIES, 19, CHANGED_FILENAME, OTHER_FILE)
            elif address == 0x452422 and NAMES + 0x1000 <= pointer < NAMES + 0x8000:
                if case.swap_on_name and not mutated_name:
                    words(ARCHIVE, OTHER_ENTRIES, 29, CHANGED_FILENAME, OTHER_FILE)
                    mutated_name = True
                if case.mutate_cookie:
                    # The vector helper snapshots the count, not the cookie.
                    words(ENTRIES - 4, 0)
                    words(OTHER_ENTRIES - 4, 0)
            elif address == 0x4524A1 and case.swap_on_array:
                words(ARCHIVE, OTHER_ENTRIES, 39, CHANGED_FILENAME, OTHER_FILE)
            finish()
        elif address == 0x4525FF:
            events.append(("destroy-array", *args(4), state))
            # Execute the actual helper, including its normal SEH path.
        elif address == 0x435250:
            receiver = uc.reg_read(UC_X86_REG_ECX)
            releases.append(receiver)
            events.append(("release-entry", receiver, bytes(uc.mem_read(receiver, 16)), state))
        elif address == FILE_DELETE:
            flags, = args(1)
            events.append(("delete-file", uc.reg_read(UC_X86_REG_ECX), flags, state))
            if case.mutate_on_delete:
                words(ARCHIVE, OTHER_ENTRIES, 49, CHANGED_FILENAME, OTHER_FILE)
            finish(4)
        else:
            raise AssertionError(f"unexpected hook {address:#x}")

    for address in (0x452422, 0x4524A1, 0x4525FF, 0x435250, FILE_DELETE):
        uc.hook_add(UC_HOOK_CODE, hook, begin=address, end=address)
    uc.emu_start(entry, STOP, count=1000000)
    assert uc.reg_read(UC_X86_REG_EIP) == STOP, "instruction budget exhausted"
    assert uc.reg_read(UC_X86_REG_ESP) == sp + 4 * (len(arguments) + 1)
    for register, value in expected_preserved.items():
        assert uc.reg_read(register) == value, "callee-saved register clobbered"
    assert struct.unpack("<I", uc.mem_read(0, 4))[0] == 0xFEE1DEAD
    result = uc.reg_read(UC_X86_REG_EAX) if operation == "delete" else None
    if operation == "delete":
        assert result == (ENTRIES - 4 if case.flags & 2 else ENTRIES)
        expected_releases = ([ENTRIES + index * 16 for index in reversed(range(max(0, case.array_count)))]
                             if case.flags & 2 else [])
        assert releases == expected_releases
    return {"events": events, "result": result, "archive": bytes(uc.mem_read(ARCHIVE, 16)),
            "arrays": bytes(uc.mem_read(ARRAYS, 0x1000))}


def cleanup_cases():
    for filename, entries, file, count in product((False, True), (False, True), (False, True), (0, 1, 4, 17, -1, -2)):
        for bits in (0, 0x55555, 0xFFFFF):
            yield Case(filename=filename, entries=entries, file=file, array_count=count, name_bits=bits)
    for values in product((False, True), repeat=5):
        yield Case(swap_on_filename=values[0], swap_on_name=values[1],
                   swap_on_array=values[2], mutate_on_delete=values[3], mutate_cookie=values[4])
    randomizer = random.Random(0x434D10)
    for _ in range(80):
        yield Case(array_count=randomizer.randrange(20), archive_count=randomizer.getrandbits(32),
                   name_bits=randomizer.getrandbits(20))


def deletion_cases():
    for flags in range(256):
        for names in (0, 15):
            yield Case(flags=flags | 0xCAFE0000, name_bits=names)
    for count, flags, mutate in product((0, 1, 7, -1, -2, -0x7FFFFFFF), (0, 1, 2, 3), (False, True)):
        yield Case(array_count=count, flags=flags, mutate_cookie=mutate)


import sys as _project_sys
from pathlib import Path as _ProjectPath
_project_sys.path.insert(0, str(_ProjectPath(__file__).resolve().parents[2]))
from matching2.tools.common.project_paths import project_support
def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--oracle", type=Path, default=ROOT / "matching2/build/oracle/th10.exe")
    options = parser.parse_args()
    config = load_manifest(project_support((ROOT) / 'matching2/msvc', 'regions.json'))
    load_oracle(options.oracle, config)
    image = PEImage(options.oracle.read_bytes())
    with tempfile.TemporaryDirectory(prefix="th10-archive-cleanup-") as temporary:
        modules = compile_candidates(Path(temporary), config)
        counts = {}
        for operation, cases in (("close", cleanup_cases()), ("reset", cleanup_cases()),
                                 ("delete", deletion_cases())):
            counts[operation] = 0
            for case in cases:
                retail = execute(image, {}, operation, case)
                recovered = execute(image, modules, operation, case)
                assert retail == recovered, (operation, case, retail, recovered)
                counts[operation] += 1
        print(f"PASS: {counts['close']} close, {counts['reset']} reset, and {counts['delete']} "
              "entry-deletion cases agree with retail, including real reverse-order destruction "
              "and callback mutations. Clang bytes: " + ", ".join(str(len(modules[a])) for a in (CLOSE, RESET, DELETE)) +
              "; retail bytes: 86, 10, 93. Throwing destructors and MSVC matching remain unverified.")


if __name__ == "__main__":
    main()
