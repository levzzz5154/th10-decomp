#!/usr/bin/env python3
"""Compare DAT encryption/decryption candidates with retail under Unicorn.

Requires native clang++, the project's MSVC headers, and Python's unicorn:
  python3 matching2/tests/dat_crypt_differential.py

The C++ candidates expose the AL key as an explicit sixth stack argument.
The emulator supplies each entry's actual ABI. This is a semantic test, not
evidence that the candidate ABI or machine bytes match the retail entries.
"""

import argparse
from pathlib import Path
import random
import struct
import subprocess
import tempfile

from unicorn import Uc, UC_ARCH_X86, UC_MODE_32, UC_HOOK_CODE, UC_HOOK_MEM_READ, UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_EAX, UC_X86_REG_ESP, UC_X86_REG_EIP

from lzss_compressor_differential import (
    ROOT, CANDIDATE, INPUT, OUTPUT, STACK, STOP, PRESERVED, DEFAULT_TOOLKIT,
    PEImage, load_manifest, load_oracle, load_candidate)

ENTRIES = {"decrypt": (0x44B0D0, "Dat_Decrypt_0044b0d0"),
           "encrypt": (0x44B220, "Dat_Encrypt_0044b220")}
ARENA_SIZE = 0x10000
HEAP_PATTERN = bytes((index * 17 + 0x39) & 255 for index in range(ARENA_SIZE))


def compile_candidate(path):
    subprocess.run([
        "clang++", "--target=i686-pc-windows-msvc", "-O2", "-fno-exceptions",
        "-fno-rtti", "-fno-stack-protector", "-fno-vectorize", "-fno-slp-vectorize",
        "-ffunction-sections", "-isystem", str(DEFAULT_TOOLKIT / "include"), "-c",
        str(ROOT / "matching2/reference/semantic_candidates/dat_crypt.cpp"),
        "-o", str(path)], check=True, timeout=60)


def execute(image, operation, code, payload, key, step, block_size, limit,
            fail_allocation=False, logical_size=None):
    uc = Uc(UC_ARCH_X86, UC_MODE_32)
    uc.mem_map(0x400000, 0x100000)
    for section in image.sections:
        uc.mem_write(section["address"], image.read(section["address"], section["raw_size"]))
    for address in (CANDIDATE, INPUT, OUTPUT, STACK, STOP):
        uc.mem_map(address, ARENA_SIZE)
    if code:
        uc.mem_write(CANDIDATE, code)
    # The allocation request may be shorter than a started block. A seeded,
    # fully mapped arena makes retail's reads past that request reproducible.
    uc.mem_write(OUTPUT, HEAP_PATTERN)
    uc.mem_write(INPUT, b"\xA5" * ARENA_SIZE)
    uc.mem_write(INPUT, payload)
    size = len(payload) if logical_size is None else logical_size
    arguments = [INPUT, size, step, block_size, limit]
    if code:
        arguments.insert(2, key)
    sp = STACK + 0x8000
    uc.mem_write(sp, struct.pack("<" + "I" * (len(arguments) + 1), STOP,
                                 *(value & 0xFFFFFFFF for value in arguments)))
    uc.reg_write(UC_X86_REG_ESP, sp)
    uc.reg_write(UC_X86_REG_EAX, 0xABCDEF00 | key)
    for register, value in PRESERVED.items():
        uc.reg_write(register, value)
    events, scratch_reads, writes = [], [], []

    def return_cdecl(machine):
        stack = machine.reg_read(UC_X86_REG_ESP)
        machine.reg_write(UC_X86_REG_EIP, struct.unpack("<I", machine.mem_read(stack, 4))[0])
        machine.reg_write(UC_X86_REG_ESP, stack + 4)

    def malloc(machine, address, instruction_size, context):
        stack = machine.reg_read(UC_X86_REG_ESP)
        requested = struct.unpack("<I", machine.mem_read(stack + 4, 4))[0]
        events.append(("malloc", requested))
        machine.reg_write(UC_X86_REG_EAX, 0 if fail_allocation else OUTPUT)
        return_cdecl(machine)

    def free(machine, address, instruction_size, context):
        stack = machine.reg_read(UC_X86_REG_ESP)
        pointer = struct.unpack("<I", machine.mem_read(stack + 4, 4))[0]
        events.append(("free", pointer))
        return_cdecl(machine)

    def scratch_read(machine, access, address, width, value, context):
        scratch_reads.append((address - OUTPUT, width))

    def write(machine, access, address, width, value, context):
        writes.append((address - INPUT, width, value))

    uc.hook_add(UC_HOOK_CODE, malloc, begin=0x452706, end=0x452706)
    uc.hook_add(UC_HOOK_CODE, free, begin=0x452422, end=0x452422)
    uc.hook_add(UC_HOOK_MEM_READ, scratch_read, begin=OUTPUT, end=OUTPUT + ARENA_SIZE - 1)
    uc.hook_add(UC_HOOK_MEM_WRITE, write, begin=INPUT, end=INPUT + ARENA_SIZE - 1)
    uc.emu_start(CANDIDATE if code else ENTRIES[operation][0], STOP, count=20000000)
    assert uc.reg_read(UC_X86_REG_EIP) == STOP, "instruction budget exhausted"
    assert uc.reg_read(UC_X86_REG_ESP) == sp + 4 * (len(arguments) + 1)
    assert uc.reg_read(UC_X86_REG_EAX) == INPUT
    for register, value in PRESERVED.items():
        assert uc.reg_read(register) == value, "callee-saved register clobbered"
    requested = min(size, limit) & 0xFFFFFFFF
    expected_events = [("malloc", requested)]
    if not fail_allocation:
        expected_events.append(("free", OUTPUT))
    assert events == expected_events
    result = bytes(uc.mem_read(INPUT, len(payload)))
    assert bytes(uc.mem_read(INPUT + len(payload), 64)) == b"\xA5" * 64
    if fail_allocation:
        assert result == payload and not writes and not scratch_reads
    else:
        assert bytes(uc.mem_read(OUTPUT, requested)) == payload[:requested]
        assert bytes(uc.mem_read(OUTPUT + requested, ARENA_SIZE - requested)) == HEAP_PATTERN[requested:]
    return {"data": result, "reads": scratch_reads, "writes": writes, "events": events}


def cases(image):
    randomizer = random.Random(0x44B0D0)
    for block_size in (1, 2, 3, 4, 7, 8, 16, 64, 128, 512, 1024):
        lengths = {0, 1, 2, max(0, block_size // 4 - 1), block_size // 4,
                   block_size // 4 + 1, block_size - 1, block_size,
                   block_size + 1, 2 * block_size - 1, 2 * block_size, 2 * block_size + 1}
        for size in sorted(lengths):
            payload = randomizer.randbytes(size)
            for limit in sorted({0, 1, block_size - 1, block_size, block_size + 1, size, size + 7}):
                key, step = randomizer.choice(((0, 0), (255, 1), (0x1B, 0x37), (0xC1, 0x51)))
                yield payload, key, step, block_size, limit
    for _ in range(100):
        size = randomizer.randrange(4097)
        block_size = randomizer.randrange(1, 257)
        yield (randomizer.randbytes(size), randomizer.randrange(256),
               randomizer.randrange(256), block_size, randomizer.randrange(size + 2))
    # Actual filename-selected DAT parameter rows, including the prefix limit.
    for index in range(8):
        key, step, block_size, limit = struct.unpack(
            "<BB2xii", image.read(0x474BD8 + 12 * index, 12))
        for size in (limit - 1, limit, limit + 1, limit + block_size + 1):
            yield randomizer.randbytes(size), key, step, block_size, limit
    # Header, index, score and replay layers recovered from their call sites.
    for key, step, block_size in ((0x1B, 0x37, 16), (0x3E, 0x9B, 128),
                                 (0xAC, 0x35, 16), (0x3D, 0x7A, 128), (0xAA, 0xE1, 1024)):
        for size in (1, block_size - 1, block_size, block_size + 1, 2 * block_size + 3):
            yield randomizer.randbytes(size), key, step, block_size, size


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--object", type=Path)
    parser.add_argument("--oracle", type=Path, default=ROOT / "matching2/build/oracle/th10.exe")
    args = parser.parse_args()
    config = load_manifest(ROOT / "matching2/msvc/regions.json")
    load_oracle(args.oracle, config)
    image = PEImage(args.oracle.read_bytes())
    with tempfile.TemporaryDirectory(prefix="th10-dat-crypt-") as temporary:
        obj = args.object or Path(temporary) / "dat_crypt.obj"
        if args.object is None:
            compile_candidate(obj)
        aliases = {"_memcpy": int(config["symbols"]["_asm_memcpy_0045bfc0"], 0)}
        codes = {operation: load_candidate(obj, config, symbol, aliases)
                 for operation, (address, symbol) in ENTRIES.items()}
        comparisons = round_trips = overread_cases = 0
        for index, parameters in enumerate(cases(image)):
            payload, key, step, block_size, limit = parameters
            outcomes = {}
            for operation in ENTRIES:
                retail = execute(image, operation, None, *parameters)
                candidate = execute(image, operation, codes[operation], *parameters)
                assert candidate == retail, (index, operation, len(payload), key, step, block_size, limit)
                outcomes[operation] = candidate
                comparisons += 1
            snapshot_size = min(len(payload), limit)
            overread = any(offset + width > snapshot_size
                           for result in outcomes.values() for offset, width in result["reads"])
            if overread:
                overread_cases += 1
            else:
                restored = execute(image, "decrypt", codes["decrypt"],
                                   outcomes["encrypt"]["data"], key, step, block_size, limit)
                assert restored["data"] == payload, (index, "round trip")
                round_trips += 1
        for logical_size, limit in ((0, 0), (1, 1), (64, 64), (-1, 64), (64, -1)):
            for operation in ENTRIES:
                options = {"logical_size": logical_size, "fail_allocation": True}
                parameters = (bytes(range(64)), 255, 255, 16, limit)
                assert execute(image, operation, None, *parameters, **options) == execute(
                    image, operation, codes[operation], *parameters, **options)
                comparisons += 1
        print(f"PASS: {comparisons} retail comparisons, {round_trips} round trips, "
              f"and {overread_cases} boundary configurations reproducing reads past the "
              "requested snapshot size. Both Clang candidates use a conventional ABI; "
              "retail ABI and MSVC bytes remain unrecovered.")


if __name__ == "__main__":
    main()
