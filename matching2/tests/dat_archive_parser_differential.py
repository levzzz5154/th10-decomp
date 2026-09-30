#!/usr/bin/env python3
"""Test packed DAT index parsing against retail x86.

Run with native clang++ and Python's unicorn package:
  python3 matching2/tests/dat_archive_parser_differential.py

The actual retail vector-constructor helper and entry constructors execute in
both runs. Allocation is scripted. Clang emits real C++ exception metadata;
this test exercises normal paths, while dat_archive_parser_unwind.py separately
checks registered states and executes their cleanup actions.
"""

import argparse
from dataclasses import dataclass
from pathlib import Path
import random
import struct
import subprocess
import tempfile

from unicorn import Uc, UC_ARCH_X86, UC_MODE_32, UC_HOOK_CODE
from unicorn.x86_const import UC_X86_REG_EAX, UC_X86_REG_ECX, UC_X86_REG_ESP, UC_X86_REG_EIP
from lzss_compressor_differential import (
    ROOT, CANDIDATE, INPUT, STACK, STOP, PRESERVED, PEImage,
    load_manifest, load_oracle)
from coff_module import load_module

ENTRY = 0x4350D0
ARRAY_ARENA = 0x2200000
ALLOCATION = ARRAY_ARENA + 0x100
NAMES = 0x2600000
INITIAL_EXCEPTION_LIST = 0xFEE1DEAD


@dataclass(frozen=True)
class Case:
    names: tuple = (b"test.anm",)
    name_failures: frozenset = frozenset()
    allocation_fails: bool = False
    source_alignment: int = 0
    mutate_first_name: bool = False
    logical_count: object = None
    terminal_offset: int = 0x12345678


def compile_candidate(path):
    subprocess.run([
        "clang++", "--target=i686-pc-windows-msvc", "-O2", "-mno-sse", "-mno-sse2",
        "-std=c++03", "-fno-builtin", "-fexceptions", "-fcxx-exceptions", "-fno-rtti", "-fno-stack-protector",
        "-ffunction-sections", "-I", str(ROOT / "matching2/msvc/include"), "-c",
        str(ROOT / "matching2/reference/semantic_candidates/dat.cpp"),
        "-o", str(path)], check=True, timeout=60)


def load_parser_candidate(path, code_address=CANDIDATE):
    bindings = {"_asm_operator_new_00452493": 0x452493,
                "_asm_malloc_00452706": 0x452706,
                "_asm_free_004524a1": 0x4524A1,
                "@ArchiveEntry_Construct_004352c0@4": 0x4352C0,
                "@ArchiveEntry_Release_00435250@4": 0x435250,
                "_asm_eh_vector_constructor_iterator_0045252d@20": 0x45252D,
                # Never executed by the normal-path test or the manual unwind
                # action test. Retail contains the older FrameHandler, whose
                # FuncInfo version must not be treated as interchangeable.
                "___CxxFrameHandler3": STOP + 0x200}
    module = load_module(path, code_address, bindings)
    assert module.symbols["_DatArchive_BuildIndex_004350d0@12"] == code_address
    assert "___ehhandler$_DatArchive_BuildIndex_004350d0@12" in module.symbols
    return module


def pack(names):
    result = bytearray()
    for index, name in enumerate(names):
        assert b"\0" not in name
        result.extend(name + b"\0")
        result.extend(b"\xCC" * (-len(result) % 4))
        result.extend(struct.pack("<3I", 0x1000 + index * 97, 0x2000 + index,
                                  0xC0DE0000 | index))
    return bytes(result)


def execute(image, code, case):
    uc = Uc(UC_ARCH_X86, UC_MODE_32)
    uc.mem_map(0x400000, 0x100000)
    for section in image.sections:
        uc.mem_write(section["address"], image.read(section["address"], section["raw_size"]))
    for address in (CANDIDATE, INPUT, ARRAY_ARENA, STACK, STOP):
        uc.mem_map(address, 0x10000)
    uc.mem_map(NAMES, 0x40000)
    # FS's default emulated base is zero. Retail and its vector helper link
    # their normal-path SEH records through FS:[0], then restore this value.
    uc.mem_map(0, 0x1000)
    uc.mem_write(0, struct.pack("<I", INITIAL_EXCEPTION_LIST))
    if code:
        uc.mem_write(CANDIDATE, code)
    uc.mem_write(ARRAY_ARENA, b"\xA5" * 0x10000)
    uc.mem_write(NAMES, b"\xA5" * 0x40000)
    packed = pack(case.names)
    source = INPUT + case.source_alignment
    uc.mem_write(source, packed + b"\xA5" * 64)
    count = len(case.names) if case.logical_count is None else case.logical_count
    sp = STACK + 0x8000
    uc.mem_write(sp, struct.pack("<4I", STOP, source, count & 0xFFFFFFFF, case.terminal_offset))
    uc.reg_write(UC_X86_REG_ESP, sp)
    for register, value in PRESERVED.items():
        uc.reg_write(register, value)
    events = []
    name_calls = []

    def args(count):
        current = uc.reg_read(UC_X86_REG_ESP)
        return struct.unpack("<" + "I" * count, uc.mem_read(current + 4, 4 * count))

    def finish(result):
        current = uc.reg_read(UC_X86_REG_ESP)
        uc.reg_write(UC_X86_REG_EAX, result)
        uc.reg_write(UC_X86_REG_EIP, struct.unpack("<I", uc.mem_read(current, 4))[0])
        uc.reg_write(UC_X86_REG_ESP, current + 4)

    def hook(machine, address, size, context):
        if address == 0x452493:
            requested, = args(1)
            events.append(("new", requested))
            finish(0 if case.allocation_fails else ALLOCATION)
        elif address == 0x452706:
            requested, = args(1)
            index = len(name_calls)
            result = 0 if index in case.name_failures else NAMES + index * 0x1000
            events.append(("malloc", requested, result))
            name_calls.append((requested, result))
            if case.mutate_first_name and index == 0:
                # Change a long packed name to "ab" and move metadata to its
                # new aligned position. The rescan must use the new length.
                uc.mem_write(source, b"ab\0\xCC" + struct.pack("<3I", 0x71, 0x72, 0x73))
            finish(result)
        elif address == 0x45252D:
            events.append(("construct-array", *args(5)))
            # Execute the actual retail helper; do not simulate its loop.
        elif address == 0x4352C0:
            events.append(("construct-entry", uc.reg_read(UC_X86_REG_ECX)))
            # Execute the actual constructor that clears only the name word.
        elif address == 0x435250:
            raise AssertionError("entry release was unexpected on a nonthrowing parse")
        else:
            raise AssertionError(f"unexpected hook {address:#x}")

    for address in (0x452493, 0x452706, 0x45252D, 0x4352C0, 0x435250):
        uc.hook_add(UC_HOOK_CODE, hook, begin=address, end=address)
    uc.emu_start(CANDIDATE if code else ENTRY, STOP, count=5000000)
    assert uc.reg_read(UC_X86_REG_EIP) == STOP, "instruction budget exhausted"
    assert uc.reg_read(UC_X86_REG_ESP) == sp + 16
    assert struct.unpack("<I", uc.mem_read(0, 4))[0] == INITIAL_EXCEPTION_LIST
    for register, value in PRESERVED.items():
        assert uc.reg_read(register) == value, "callee-saved register clobbered"
    expected_allocation = (((count + 1) & 0xFFFFFFFF) * 16 + 4) & 0xFFFFFFFF
    assert events[0] == ("new", expected_allocation)
    result = uc.reg_read(UC_X86_REG_EAX)
    if case.allocation_fails:
        assert result == 0 and len(events) == 1
    else:
        assert result == ALLOCATION + 4
        if count >= 0:
            sentinel = struct.unpack("<4I", uc.mem_read(result + count * 16, 16))
            assert sentinel == (0, case.terminal_offset, 0, 0xA5A5A5A5)
            assert bytes(uc.mem_read(ALLOCATION - 64, 64)) == b"\xA5" * 64
            assert bytes(uc.mem_read(ALLOCATION + expected_allocation, 64)) == b"\xA5" * 64
    return {"events": events, "result": result,
            "array": bytes(uc.mem_read(ARRAY_ARENA, 0x10000)),
            "names": tuple(bytes(uc.mem_read(NAMES + index * 0x1000, requested + 16))
                           for index, (requested, pointer) in enumerate(name_calls)),
            "source": bytes(uc.mem_read(source, len(packed) + 64))}


def cases():
    samples = [(), (b"",), (b"a", b"bb", b"ccc", b"dddd"),
               (b"\x80\xFFname",), tuple(b"a" * size for size in (1, 2, 3, 4, 7, 8, 15, 16, 31, 255, 1023))]
    for names in samples:
        for alignment in range(4):
            yield Case(names=names, source_alignment=alignment)
            yield Case(names=names, source_alignment=alignment,
                       name_failures=frozenset(range(len(names))))
            yield Case(names=names, source_alignment=alignment, allocation_fails=True)
    randomizer = random.Random(0x4350D0)
    for _ in range(100):
        names = tuple(bytes(randomizer.randrange(1, 256) for _ in range(randomizer.randrange(80)))
                      for _ in range(randomizer.randrange(25)))
        failures = frozenset(index for index in range(len(names)) if randomizer.randrange(4) == 0)
        yield Case(names=names, name_failures=failures, source_alignment=randomizer.randrange(4),
                   terminal_offset=randomizer.getrandbits(32))
    for alignment in range(4):
        for failures in (frozenset(), frozenset({0})):
            yield Case(names=(b"original-long-name",), name_failures=failures,
                       source_alignment=alignment, mutate_first_name=True)
    # Explicit modulo-2^32 allocation requests, without attempting huge arrays.
    for count in (-2, -1, 0x0FFFFFFF, 0x10000000, 0x7FFFFFFF):
        yield Case(names=(), logical_count=count, allocation_fails=True)
    # Retail count -1 constructs an empty array then writes its sentinel before
    # the returned entries pointer. Preserve, but do not call this a valid index.
    yield Case(names=(), logical_count=-1)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--object", type=Path)
    parser.add_argument("--oracle", type=Path, default=ROOT / "matching2/build/oracle/th10.exe")
    args = parser.parse_args()
    config = load_manifest(ROOT / "matching2/msvc/regions.json")
    load_oracle(args.oracle, config)
    image = PEImage(args.oracle.read_bytes())
    with tempfile.TemporaryDirectory(prefix="th10-archive-parser-") as temporary:
        obj = args.object or Path(temporary) / "parser.obj"
        if args.object is None:
            compile_candidate(obj)
        code = load_parser_candidate(obj).data
        count = 0
        for case in cases():
            retail = execute(image, None, case)
            candidate = execute(image, code, case)
            assert candidate == retail, case
            count += 1
        print(f"PASS: {count} parser cases agree with retail on allocations, constructors, "
              f"names, metadata, sentinel and normal-path SEH restoration. Clang module: {len(code)} "
              "bytes including unwind code/metadata; native MSVC byte matching remains outstanding.")


if __name__ == "__main__":
    main()
