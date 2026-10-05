#!/usr/bin/env python3
"""Compare retail and native MSVC atlas drawing at their external-call boundary."""

import argparse
import itertools
from pathlib import Path
import struct
import sys
import tempfile

from unicorn import Uc, UC_ARCH_X86, UC_MODE_32, UC_HOOK_CODE
from unicorn.x86_const import (
    UC_X86_REG_EAX, UC_X86_REG_EBX, UC_X86_REG_ECX, UC_X86_REG_EDX,
    UC_X86_REG_ESI, UC_X86_REG_EDI, UC_X86_REG_EBP, UC_X86_REG_ESP,
    UC_X86_REG_EIP,
)

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT))
from matching2.tools.matching.equivalence import load_recoveries, verify_recovery
from matching2.tools.matching.probe import load_manifest, load_oracle
from matching2.tools.common.wine import DEFAULT_TOOLKIT

ENTRY, EXTENT = 0x437FE0, 509
ATLAS = 0x474CB0
HEAP, STACK, API, STOP = 0x1000000, 0x2000000, 0x6000000, 0x6000F00
RECT, TEXT, TEXTURE, SURFACE = (HEAP + n for n in (0x100, 0x200, 0x400, 0x500))
TEXTURE_METHODS, SURFACE_METHODS = HEAP + 0x600, HEAP + 0x700
PRESERVED = {
    UC_X86_REG_EBX: 0x11223344, UC_X86_REG_EBP: 0x22334455,
    UC_X86_REG_ESI: 0x33445566, UC_X86_REG_EDI: 0x44556677,
}


def words(*values):
    return struct.pack('<' + 'I' * len(values), *(v & 0xFFFFFFFF for v in values))


class Execution:
    def __init__(self, body):
        self.uc = uc = Uc(UC_ARCH_X86, UC_MODE_32)
        for address, size in ((0x400000, 0x100000), (HEAP, 0x1000),
                              (STACK, 0x10000), (API, 0x1000)):
            uc.mem_map(address, size)
        uc.mem_write(ENTRY, body)
        self.calls = {
            0x436CA0: ('fill', 0), 0x437160: ('invert', 1),
            0x436DA0: ('convert', 2), 0x4521A6: ('upload', 10),
            API: ('select', 2), API + 0x10: ('background', 2),
            API + 0x20: ('color', 2), API + 0x30: ('text', 5),
            API + 0x40: ('surface', 3), API + 0x50: ('release', 1),
        }
        for slot, target in ((0x46602C, API), (0x46601C, API + 0x10),
                             (0x466018, API + 0x20), (0x466014, API + 0x30)):
            uc.mem_write(slot, words(target))
        uc.mem_write(TEXTURE, words(TEXTURE_METHODS))
        uc.mem_write(TEXTURE_METHODS + 0x48, words(API + 0x40))
        uc.mem_write(SURFACE, words(SURFACE_METHODS))
        uc.mem_write(SURFACE_METHODS + 8, words(API + 0x50))
        uc.hook_add(UC_HOOK_CODE, self.hook)

    def read_words(self, pointer, count):
        return struct.unpack('<' + 'I' * count, self.uc.mem_read(pointer, count * 4))

    def hook(self, uc, address, size, context):
        if ENTRY <= address < ENTRY + EXTENT or address == STOP:
            return
        assert address in self.calls, f'unexpected call/branch to {address:#x}'
        name, count = self.calls[address]
        sp = uc.reg_read(UC_X86_REG_ESP)
        return_to, *args = self.read_words(sp, count + 1)
        result = 1
        if name == 'fill':
            args = [uc.reg_read(UC_X86_REG_ESI), uc.reg_read(UC_X86_REG_ECX)]
        elif name == 'invert':
            args.insert(0, uc.reg_read(UC_X86_REG_ECX))
        elif name == 'select':
            result = 0xABCDEF01 + self.select_count
            self.select_count += 1
        elif name == 'surface':
            uc.mem_write(args[2], words(0 if self.null_surface else SURFACE))
            # The output-slot address is a private local, whose lifetime/home
            # can differ. Compare its written value and the two actual inputs.
            args = args[:2] + [0 if self.null_surface else SURFACE]
            result = 0x80004005 if self.null_surface else 0
        elif name == 'upload':
            args[2] = self.read_words(args[2], 4)
            args[7] = self.read_words(args[7], 4)
        elif name == 'text':
            args[3] = bytes(uc.mem_read(args[3], args[4]))
        self.trace.append((name, tuple(args)))
        # External calls may destroy every caller-saved integer register.
        uc.reg_write(UC_X86_REG_EAX, result)
        uc.reg_write(UC_X86_REG_ECX, 0xC1C1C1C1)
        uc.reg_write(UC_X86_REG_EDX, 0xD2D2D2D2)
        uc.reg_write(UC_X86_REG_ESP, sp + 4 * (count + 1))
        uc.reg_write(UC_X86_REG_EIP, return_to)

    def execute(self, size, x, width, text, null_surface):
        uc = self.uc
        self.trace, self.select_count, self.null_surface = [], 0, null_surface
        uc.mem_write(STACK, b'\xA5' * 0x10000)
        uc.mem_write(RECT, words(-7, 11, width - 7, 111))
        uc.mem_write(TEXT, text + b'\0')
        uc.mem_write(ATLAS + 0x100, words(0x1234))
        uc.mem_write(ATLAS + 0x110, words(2048, 0x24681357))
        uc.mem_write(ATLAS + 0x120, words(HEAP + 0x800))
        for index in range(15):
            uc.mem_write(0x491868 + index * 4, words(0x70000000 + index))
        sp = STACK + 0x8000
        uc.mem_write(sp, words(STOP, RECT, x, size, 0xDEADBEEF, TEXT, TEXTURE))
        uc.reg_write(UC_X86_REG_ESP, sp)
        for register, value in PRESERVED.items():
            uc.reg_write(register, value)
        uc.emu_start(ENTRY, STOP, count=10000)
        assert uc.reg_read(UC_X86_REG_EIP) == STOP
        assert uc.reg_read(UC_X86_REG_ESP) == sp + 28
        assert all(uc.reg_read(r) == v for r, v in PRESERVED.items())
        assert bytes(uc.mem_read(RECT, 16)) == words(-7, 11, width - 7, 111)
        return self.trace


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--project', type=Path, default=ROOT / 'matching2/msvc')
    parser.add_argument('--oracle', type=Path, default=ROOT / 'matching2/build/oracle/th10.exe')
    args = parser.parse_args()
    project = args.project.resolve()
    config = load_manifest(project / 'regions.json')
    text = load_oracle(args.oracle, config)
    recovery, = [r for r in load_recoveries(project, config, config['regions'])
                 if r['name'] == 'font_atlas_draw_text_00437fe0']
    with tempfile.TemporaryDirectory(prefix='th10-font-differential-') as temporary:
        report, candidate = verify_recovery(recovery, project, DEFAULT_TOOLKIT,
                                            config['flags'], text, Path(temporary))
        assert report['code_bytes'] == EXTENT
    retail = Execution(text[ENTRY - 0x401000:ENTRY - 0x401000 + EXTENT])
    model = Execution(candidate)
    sizes = [-0x80000000, -1, 0, 16, *range(17, 33), 0x7FFFFFFF]
    cases = itertools.product(sizes, (-123, 0, 17, 0x7FFFFFFF),
                              (-32, 0, 1, 500, 501, 502, 2000),
                              (b'', b'A', b'Font test \x82\xa0'), (False, True))
    count = 0
    for case in cases:
        expected, actual = retail.execute(*case), model.execute(*case)
        assert actual == expected, (case, expected, actual)
        # Independent observations: each draw uses exactly one text call,
        # restores the first selected object twice, and conditionally releases.
        assert sum(name == 'text' for name, _ in actual) == 1
        selections = [a for name, a in actual if name == 'select']
        assert len(selections) == 3 and selections[1][1] == selections[2][1] == 0xABCDEF01
        assert sum(name == 'release' for name, _ in actual) == (not case[-1])
        count += 1
    print(f'{count} retail/native MSVC cases passed: font selection, call arguments, '
          'surface output, register preservation and stack cleanup.')


if __name__ == '__main__':
    main()
