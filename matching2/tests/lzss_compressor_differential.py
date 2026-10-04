#!/usr/bin/env python3
"""Compare the MSVC-built semantic compressor with retail under x86 emulation.

Requires Unicorn, Wine and the project's MSVC toolkit. From the repository root:
  python3 matching2/tests/lzss_compressor_differential.py

--object can reuse an already compiled candidate COFF object. This test compares
behavior, including the complete tree/ring state; it does not establish byte
identity. The build's normal byte gate is still required for promotion.
"""

import argparse
import json
from pathlib import Path
import random
import struct
import subprocess
import sys
import tempfile

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT))

from unicorn import Uc, UC_ARCH_X86, UC_MODE_32, UC_HOOK_CODE
from unicorn.x86_const import (UC_X86_REG_EAX, UC_X86_REG_EBX, UC_X86_REG_EBP,
                              UC_X86_REG_ESI, UC_X86_REG_EDI, UC_X86_REG_ESP,
                              UC_X86_REG_EIP)
from matching2.tools.common.coff import read_coff_function
from matching2.tools.common.pe import PEImage
from matching2.tools.common.wine import DEFAULT_TOOLKIT, compiler_environment, winpath
from matching2.tools.matching.probe import load_manifest, load_oracle, region_directory, relocation_table

ENTRY = 0x4359B0
CANDIDATE = 0x1000000
INPUT = 0x2000000
OUTPUT = 0x2100000
SIZE = 0x2200000
STACK = 0x2300000
STOP = 0x2400000
TREE = 0x477858
TREE_BYTES = 0x2001 * 12
RING = 0x48F868
GUARD = bytes([0xA5]) * 64
PRESERVED = {UC_X86_REG_EBX: 0x13579BDF, UC_X86_REG_EBP: 0x2468ACE0,
             UC_X86_REG_ESI: 0x12345678, UC_X86_REG_EDI: 0x87654321}


def compile_candidate(output, config):
    source = ROOT / "matching2/reference/semantic_candidates/score_save.cpp"
    command = ["wine", str(DEFAULT_TOOLKIT / "bin/cl.exe"), *config["flags"],
               "/I" + winpath(ROOT / "matching2/msvc/include"),
               "/Fo" + winpath(output), winpath(source)]
    subprocess.run(command, env=compiler_environment(DEFAULT_TOOLKIT),
                   check=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE, timeout=180)


def load_candidate(path, config, requested_symbol="Lzss_Compress_004359B0", extra_bindings=None,
                   code_address=CANDIDATE):
    symbol, raw, _ = read_coff_function(path, requested_symbol)
    bindings = region_directory(config, config["regions"])
    cluster = json.loads((ROOT / "matching2/msvc/layout/ltcg/lzss.json").read_text())
    bindings.update({row["symbol"]: int(row["address"], 0)
                     for row in cluster["absolute_symbols"]})
    # The archived candidates still name the match tree as one object.
    bindings["?g_compression_tree@@3UCompressionTree@@A"] = bindings["?g_LzssTree@@3PAULzssNode@@A"]
    bindings.update(extra_bindings or {})
    code = bytearray(raw)
    for offset, name, kind, local in relocation_table(path, symbol):
        target = code_address + local if local is not None else bindings[name]
        value = struct.unpack_from("<I", code, offset)[0] + target
        if kind == 0x14:
            value -= code_address + offset + 4
        elif kind != 6:
            raise ValueError(f"unsupported relocation kind {kind:#x}")
        struct.pack_into("<I", code, offset, value & 0xFFFFFFFF)
    return bytes(code)


def execute(image, candidate, payload, fail_allocation=False):
    machine = Uc(UC_ARCH_X86, UC_MODE_32)
    machine.mem_map(0x400000, 0x100000)
    for section in image.sections:
        machine.mem_write(section["address"], image.read(section["address"], section["raw_size"]))
    for address in (CANDIDATE, INPUT, OUTPUT, SIZE, STACK, STOP):
        machine.mem_map(address, 0x10000)
    if candidate:
        machine.mem_write(CANDIDATE, candidate)
    machine.mem_write(INPUT, payload + GUARD)
    machine.mem_write(OUTPUT, b"\xA5" * 0x10000)
    machine.mem_write(SIZE, struct.pack("<I", 0xDEADBEEF))
    # A nonzero initial tree/ring proves initialization covers node zero and
    # that allocation failure leaves dictionary state untouched.
    machine.mem_write(TREE, b"\xA5" * TREE_BYTES)
    machine.mem_write(RING, b"\xA5" * 0x2000)
    stack_top = STACK + 0x8000
    machine.mem_write(stack_top, struct.pack("<4I", STOP, INPUT, len(payload), SIZE))
    machine.reg_write(UC_X86_REG_ESP, stack_top)
    for register, value in PRESERVED.items():
        machine.reg_write(register, value)
    allocations = []

    def allocate(uc, address, size, user_data):
        sp = uc.reg_read(UC_X86_REG_ESP)
        allocations.append(struct.unpack("<I", uc.mem_read(sp + 4, 4))[0])
        uc.reg_write(UC_X86_REG_EAX, 0 if fail_allocation else OUTPUT)
        uc.reg_write(UC_X86_REG_EIP, struct.unpack("<I", uc.mem_read(sp, 4))[0])
        uc.reg_write(UC_X86_REG_ESP, sp + 4)

    machine.hook_add(UC_HOOK_CODE, allocate, begin=0x452706, end=0x452706)
    machine.emu_start(CANDIDATE if candidate else ENTRY, STOP, count=500000000)
    assert machine.reg_read(UC_X86_REG_EIP) == STOP, (
        f"instruction budget exhausted at {machine.reg_read(UC_X86_REG_EIP):#x}")
    assert machine.reg_read(UC_X86_REG_ESP) == stack_top + 16, "stdcall cleanup differs"
    for register, value in PRESERVED.items():
        assert machine.reg_read(register) == value, "callee-saved register clobbered"
    assert allocations == [len(payload) * 2]
    assert bytes(machine.mem_read(INPUT, len(payload) + len(GUARD))) == payload + GUARD
    result = machine.reg_read(UC_X86_REG_EAX)
    count = struct.unpack("<I", machine.mem_read(SIZE, 4))[0]
    if fail_allocation:
        assert result == 0 and count == 0xDEADBEEF
        assert bytes(machine.mem_read(TREE, TREE_BYTES)) == b"\xA5" * TREE_BYTES
        assert bytes(machine.mem_read(RING, 0x2000)) == b"\xA5" * 0x2000
        count = 0
    else:
        assert result == OUTPUT and count < 0x10000 - len(GUARD)
    assert bytes(machine.mem_read(OUTPUT + count, len(GUARD))) == GUARD
    return (count, bytes(machine.mem_read(OUTPUT, count)),
            bytes(machine.mem_read(TREE, TREE_BYTES)), bytes(machine.mem_read(RING, 0x2000)))


def decode(payload):
    # Independent format-level check: missing final zero bits are implicit.
    bit = 0
    ring = bytearray(0x2000)
    cursor = 1
    result = bytearray()

    def read_bits(count):
        nonlocal bit
        value = 0
        for _ in range(count):
            byte = payload[bit // 8] if bit // 8 < len(payload) else 0
            value = (value << 1) | ((byte >> (7 - bit % 8)) & 1)
            bit += 1
        return value

    while True:
        if read_bits(1):
            value = read_bits(8)
            ring[cursor] = value
            result.append(value)
            cursor = (cursor + 1) & 0x1FFF
        else:
            position = read_bits(13)
            if not position:
                return bytes(result)
            for index in range(read_bits(4) + 3):
                value = ring[(position + index) & 0x1FFF]
                ring[cursor] = value
                result.append(value)
                cursor = (cursor + 1) & 0x1FFF
        assert len(result) < 0x10000, "invalid stream did not terminate"


def cases():
    randomizer = random.Random(0x4359B0)
    for size in (0, 1, 2, 3, 7, 8, 9, 17, 18, 19, 31, 32, 33, 255, 256,
                 257, 8190, 8191, 8192, 8193, 8210, 16421):
        yield f"zero-{size}", bytes(size)
        yield f"ff-{size}", b"\xFF" * size
        yield f"ramp-{size}", bytes(i & 255 for i in range(size))
        yield f"random-{size}", randomizer.randbytes(size)
        yield f"small-alphabet-{size}", bytes(randomizer.randrange(4) for _ in range(size))
    for trial in range(50):
        size = randomizer.randrange(1, 2048)
        yield f"fuzz-{trial}", randomizer.randbytes(size)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--object", type=Path)
    parser.add_argument("--oracle", type=Path, default=ROOT / "matching2/build/oracle/th10.exe")
    args = parser.parse_args()
    config = load_manifest(ROOT / "matching2/msvc/regions.json")
    load_oracle(args.oracle, config)  # Refuse an unverified retail text section.
    image = PEImage(args.oracle.read_bytes())
    with tempfile.TemporaryDirectory(prefix="th10-lzss-") as temporary:
        obj = args.object or Path(temporary) / "compress.obj"
        if args.object is None:
            compile_candidate(obj, config)
        code = load_candidate(obj, config)
        count = 0
        for label, payload in cases():
            try:
                retail = execute(image, None, payload)
                recovered = execute(image, code, payload)
            except AssertionError as error:
                raise AssertionError(f"{label}: {error}") from error
            assert recovered == retail, f"retail/candidate state differs: {label}"
            assert decode(recovered[1]) == payload, f"round trip differs: {label}"
            count += 1
        for payload in (b"", b"\xFF", bytes(range(256))):
            assert execute(image, None, payload, True) == execute(image, code, payload, True)
        print(f"PASS: {count} streams, full tree/ring state, round trips, and 3 allocation failures; "
              f"candidate {len(code)} bytes, retail 1029 bytes (behavioral check only).")


if __name__ == "__main__":
    main()
