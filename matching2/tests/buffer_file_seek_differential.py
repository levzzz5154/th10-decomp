#!/usr/bin/env python3
"""Compare BufferFile seek rules and 32-bit edge arithmetic with retail."""

import argparse
from itertools import product
from pathlib import Path
import random
import struct
import subprocess
import tempfile

from unicorn import Uc, UC_ARCH_X86, UC_MODE_32
from unicorn.x86_const import UC_X86_REG_EAX, UC_X86_REG_ECX, UC_X86_REG_ESP, UC_X86_REG_EIP
from lzss_compressor_differential import (
    ROOT, CANDIDATE, STACK, STOP, PRESERVED, PEImage, load_manifest, load_oracle, load_candidate)

FILE = 0x2500100
ENTRY = 0x4364F0


def compile_candidate(path, config):
    subprocess.run([
        "clang++", "--target=i686-pc-windows-msvc", "-std=c++03", "-O2", "-fno-exceptions",
        "-fno-rtti", "-fno-stack-protector", "-ffunction-sections",
        "-I", str(ROOT / "matching2/msvc/include"), "-c",
        str(ROOT / "matching2/reference/semantic_candidates/buffer_file_seek.cpp"), "-o", str(path)],
        check=True, timeout=60)
    return load_candidate(path, config, "?Seek@BufferFile@@UAEEJI@Z")


class Execution:
    def __init__(self, image, candidate=None):
        self.uc = uc = Uc(UC_ARCH_X86, UC_MODE_32)
        for address in (ENTRY & ~0xFFF, CANDIDATE, STACK, STOP, FILE & ~0xFFF):
            uc.mem_map(address, 0x1000)
        uc.mem_write(ENTRY, image.read(ENTRY, 107))
        if candidate:
            uc.mem_write(CANDIDATE, candidate)
        self.entry = CANDIDATE if candidate else ENTRY

    def execute(self, data, size, position, distance, origin):
        uc = self.uc
        initial = struct.pack("<4I", 0x46F308, size, position, data)
        uc.mem_write(FILE - 16, b"\xA5" * 16 + initial + b"\xA5" * 16)
        sp = STACK + 0x800
        uc.mem_write(sp, struct.pack("<3I", STOP, distance & 0xFFFFFFFF, origin))
        uc.reg_write(UC_X86_REG_ESP, sp)
        uc.reg_write(UC_X86_REG_ECX, FILE)
        for register, value in PRESERVED.items():
            uc.reg_write(register, value)
        uc.emu_start(self.entry, STOP, count=200)
        assert uc.reg_read(UC_X86_REG_EIP) == STOP
        assert uc.reg_read(UC_X86_REG_ESP) == sp + 12
        assert all(uc.reg_read(register) == value for register, value in PRESERVED.items())
        output = bytes(uc.mem_read(FILE - 16, 48))
        assert output[:24] == b"\xA5" * 16 + initial[:8]
        assert output[28:] == initial[12:] + b"\xA5" * 16
        result = uc.reg_read(UC_X86_REG_EAX) & 255
        updated, = struct.unpack_from("<I", output, 24)
        assert result in (0, 1)
        if not result:
            assert updated == position
        return result, updated


def cases():
    for data, size in product((0, 0x1000, 0x7FFFFFFD, 0xFFFFFFFD),
                              (0, 1, 4, 0x7FFFFFFF, 0x80000000, 0x80000001, 0xFFFFFFFF)):
        positions = {(data + delta) & 0xFFFFFFFF for delta in (-1, 0, 1, size - 1, size, size + 1)}
        distances = {0x80000000, 0x80000001, 0xFFFFFFFF, 0, 1, 2, 0x7FFFFFFF,
                     size, (size - 1) & 0xFFFFFFFF, (-size) & 0xFFFFFFFF}
        for position, distance, origin in product(sorted(positions), sorted(distances), (0, 1, 2, 3, 0xFFFFFFFF)):
            yield data, size, position, distance, origin
    randomizer = random.Random(0x4364F0)
    for trial in range(3000):
        yield (randomizer.getrandbits(32), randomizer.getrandbits(32), randomizer.getrandbits(32),
               randomizer.getrandbits(32), randomizer.randrange(4))


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
    with tempfile.TemporaryDirectory(prefix="th10-buffer-seek-") as temporary:
        candidate = compile_candidate(Path(temporary) / "seek.obj", config)
        retail, recovered = Execution(image), Execution(image, candidate)
        comparisons = 0
        for case in cases():
            expected, actual = retail.execute(*case), recovered.execute(*case)
            assert actual == expected, (case, expected, actual)
            comparisons += 1
        # Independent boundary observations: strict start/current end bounds,
        # accepted end-relative zero, and an unguarded seek before the buffer.
        for case, expected in (
            ((0x1000, 4, 0x1000, 4, 0), (0, 0x1000)),
            ((0x1000, 4, 0x1000, 4, 1), (0, 0x1000)),
            ((0x1000, 4, 0x1000, 0, 2), (1, 0x1004)),
            ((0x1000, 4, 0x1000, 0xFFFFFFFF, 1), (1, 0xFFF)),
            ((0, 0x80000001, 0, 0x80000000, 2), (1, 1)),
            ((0, 0x80000000, 0, 0, 1), (0, 0))):
            assert retail.execute(*case) == recovered.execute(*case) == expected
            comparisons += 1
        print(f"PASS: {comparisons} BufferFile seek comparisons, including signed limits, "
              f"address wrapping and unchanged failure state; {len(candidate)} Clang bytes. "
              "Native MSVC region matching remains unverified.")


if __name__ == "__main__":
    main()
