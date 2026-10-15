#!/usr/bin/env python3
"""Validate the semantic decoder against retail x86, including read faults.

Requires Python's unicorn package and native clang++. No Wine is needed:
  python3 matching2/tests/lzss_decoder_differential.py

Clang is used only for behavior testing. These checks cannot promote the
candidate to the MSVC byte-exact build.
"""

import argparse
from pathlib import Path
import random
import struct
import subprocess
import tempfile

from unicorn import (Uc, UcError, UC_ARCH_X86, UC_MODE_32, UC_HOOK_CODE,
                     UC_HOOK_MEM_READ, UC_HOOK_MEM_WRITE, UC_HOOK_MEM_INVALID)
from unicorn.x86_const import UC_X86_REG_EAX, UC_X86_REG_ESP, UC_X86_REG_EIP

from lzss_compressor_differential import (
    ROOT, CANDIDATE, INPUT, OUTPUT, STACK, STOP, RING, PRESERVED, PEImage,
    load_manifest, load_oracle, load_candidate)

ENTRY = 0x435DC0
SEED_RING = bytes((index * 37 + 13) & 255 for index in range(0x2000))
GUARD = b"\xA5" * 64


def compile_candidate(path):
    subprocess.run([
        "clang++", "--target=i686-pc-windows-msvc", "-O2", "-fno-exceptions",
        "-fno-rtti", "-fno-stack-protector", "-c",
        str(ROOT / "matching2/reference/semantic_candidates/lzss.cpp"),
        "-o", str(path)], check=True, timeout=60)


def execute(image, candidate, payload, *, source_length=None, capacity=0x8000,
            allocate=False, fail_allocation=False, guard_page=False, overlap=None):
    uc = Uc(UC_ARCH_X86, UC_MODE_32)
    uc.mem_map(0x400000, 0x100000)
    for section in image.sections:
        uc.mem_write(section["address"], image.read(section["address"], section["raw_size"]))
    for address in (CANDIDATE, INPUT, OUTPUT, STACK, STOP):
        uc.mem_map(address, 0x10000)
    if candidate:
        uc.mem_write(CANDIDATE, candidate)
    source = INPUT + 0x10000 - len(payload) if guard_page else INPUT
    destination = source + overlap if overlap is not None else OUTPUT
    uc.mem_write(OUTPUT, b"\xA5" * 0x10000)
    uc.mem_write(source, payload + (b"" if guard_page else GUARD))
    uc.mem_write(RING, SEED_RING)
    if source_length is None:
        source_length = len(payload)
    sp = STACK + 0x8000
    uc.mem_write(sp, struct.pack("<5I", STOP, source, source_length & 0xFFFFFFFF,
                                 0 if allocate else destination, capacity))
    uc.reg_write(UC_X86_REG_ESP, sp)
    for register, value in PRESERVED.items():
        uc.reg_write(register, value)
    allocations, reads, writes, faults = [], [], [], []

    def malloc(machine, address, size, context):
        stack = machine.reg_read(UC_X86_REG_ESP)
        allocations.append(struct.unpack("<I", machine.mem_read(stack + 4, 4))[0])
        machine.reg_write(UC_X86_REG_EAX, 0 if fail_allocation else destination)
        machine.reg_write(UC_X86_REG_EIP, struct.unpack("<I", machine.mem_read(stack, 4))[0])
        machine.reg_write(UC_X86_REG_ESP, stack + 4)

    def read(machine, access, address, size, value, context):
        reads.append((address - source, size))

    def write(machine, access, address, size, value, context):
        writes.append((address - destination, size, value))

    def fault(machine, access, address, size, value, context):
        faults.append((access, address, size))
        return False

    uc.hook_add(UC_HOOK_CODE, malloc, begin=0x452706, end=0x452706)
    uc.hook_add(UC_HOOK_MEM_READ, read, begin=INPUT, end=INPUT + 0xFFFF)
    uc.hook_add(UC_HOOK_MEM_WRITE, write, begin=destination, end=destination + 0xFFFF)
    uc.hook_add(UC_HOOK_MEM_INVALID, fault)
    try:
        uc.emu_start(CANDIDATE if candidate else ENTRY, STOP, count=20000000)
    except UcError:
        assert faults, "emulator failure without a memory fault"
    if not faults:
        assert uc.reg_read(UC_X86_REG_EIP) == STOP, "instruction budget exhausted"
        assert uc.reg_read(UC_X86_REG_ESP) == sp + 20, "stdcall cleanup differs"
        assert uc.reg_read(UC_X86_REG_EAX) == (0 if allocate and fail_allocation else destination)
        for register, value in PRESERVED.items():
            assert uc.reg_read(register) == value, "callee-saved register clobbered"
    assert allocations == ([capacity] if allocate else [])
    if allocate and fail_allocation:
        assert not writes and not reads and not faults
    for index, (offset, size, value) in enumerate(writes):
        assert offset == index and size == 1, "nonsequential output writes"
    output = bytes(value for offset, size, value in writes)
    if overlap is None and len(output) + len(GUARD) < 0x10000:
        assert bytes(uc.mem_read(OUTPUT + len(output), len(GUARD))) == GUARD
    return {"output": output, "ring": bytes(uc.mem_read(RING, 0x2000)),
            "reads": reads, "faults": faults, "allocations": allocations}


def encode(tokens):
    """Build explicit LZSS tokens and their expected output from a seeded ring."""
    bits = []
    ring = bytearray(SEED_RING)
    cursor = 1
    output = bytearray()

    def put(value, count):
        bits.extend((value >> shift) & 1 for shift in range(count - 1, -1, -1))

    def emit(value):
        nonlocal cursor
        output.append(value)
        ring[cursor] = value
        cursor = (cursor + 1) & 0x1FFF

    for token in tokens:
        if isinstance(token, int):
            put(1, 1)
            put(token, 8)
            emit(token)
        else:
            position, length = token
            assert 0 < position < 0x2000 and 3 <= length <= 18
            put(0, 1)
            put(position, 13)
            put(length - 3, 4)
            for index in range(length):
                emit(ring[(position + index) & 0x1FFF])
    put(0, 14)
    bits.extend([0] * (-len(bits) % 8))
    packed = bytes(sum(bits[start + bit] << (7 - bit) for bit in range(8))
                   for start in range(0, len(bits), 8))
    return packed, bytes(output)


import sys as _project_sys
from pathlib import Path as _ProjectPath
_project_sys.path.insert(0, str(_ProjectPath(__file__).resolve().parents[2]))
from matching2.tools.common.project_paths import project_support
def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--object", type=Path)
    parser.add_argument("--oracle", type=Path, default=ROOT / "matching2/build/oracle/th10.exe")
    args = parser.parse_args()
    config = load_manifest(project_support((ROOT) / 'matching2/msvc', 'regions.json'))
    load_oracle(args.oracle, config)
    image = PEImage(args.oracle.read_bytes())
    with tempfile.TemporaryDirectory(prefix="th10-lzss-decode-") as temporary:
        obj = args.object or Path(temporary) / "decoder.obj"
        if args.object is None:
            compile_candidate(obj)
        code = load_candidate(obj, config, "DecompressDatLzss_00435dc0")
        count = 0

        def compare(label, payload, expected=None, **options):
            nonlocal count
            try:
                retail = execute(image, None, payload, **options)
                recovered = execute(image, code, payload, **options)
                assert retail == recovered, "output, dictionary, input reads or fault behavior differs"
                if expected is not None:
                    assert retail["output"] == expected, "decoded token values differ"
            except AssertionError as error:
                raise AssertionError(f"{label}: {error}") from error
            count += 1

        token_cases = [[], [0], [255], list(range(256)), [65, (1, 18)],
                       list(range(256)) * 65, [65] + [(1, 18)] * 920]
        token_cases += [[(position, length)] for position in (1, 0x1FFE, 0x1FFF)
                        for length in range(3, 19)]
        for index, tokens in enumerate(token_cases):
            payload, expected = encode(tokens)
            compare(f"tokens-{index}", payload, expected)
            # Capacity is only a malloc argument, even when smaller than output.
            compare(f"allocated-{index}", payload, expected, allocate=True, capacity=1)
        randomizer = random.Random(0x435DC0)
        for size in range(65):
            compare(f"random-{size}", randomizer.randbytes(size))
        payload, _ = encode([255, 0, 17, (1, 18), (0x1FFF, 5), 255])
        for size in range(-1, len(payload) + 1):
            compare(f"truncated-{size}", payload, source_length=size)
        for size in (0, 1, 2, 3, 7):
            compare(f"read-fault-{size}", b"\xFF" * size, guard_page=True)
            compare(f"allocation-failure-{size}", b"\xFF" * size,
                    guard_page=True, allocate=True, fail_allocation=True)
        compare("zero-length-readable", b"\xFF", source_length=0)
        compare("negative-length-readable", b"\xFF", source_length=-1)
        # Ordinary pointers may alias. Preserve the original read/write order.
        for offset in (0, 1, 3):
            payload, _ = encode([0, 0, 0, 0, 0])
            compare(f"overlapping-output-{offset}", payload, overlap=offset)
        print(f"PASS: {count} decoder cases; output, shared ring, read traces, allocation "
              f"contracts and guard-page faults agree with retail. Clang body: {len(code)} bytes; "
              "MSVC byte identity remains unverified.")


if __name__ == "__main__":
    main()
