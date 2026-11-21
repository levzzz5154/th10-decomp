"""Run the installed high-score keyboard against retail without intercepting any calls.

Covers the input delay, editing, grid navigation, and saving to the two score
buffers. Music, animation creation/teardown and disk I/O are outside this fixture.
"""
import argparse
from pathlib import Path
import struct
from typing import NamedTuple

from unicorn import Uc, UC_ARCH_X86, UC_MODE_32
from unicorn.x86_const import UC_X86_REG_EAX, UC_X86_REG_EIP, UC_X86_REG_ESP

from x86_fixture import INPUT, OUTPUT, PRESERVED, ROOT, STACK, STOP, load_fixture
from matching2.tools.common.pe import PEImage
from matching2.tools.matching.retail import default_oracle

TITLE, SCORE = INPUT, OUTPUT
PHASE, TIMER, NAME, LENGTH, CONFIRMED, GRID = 0x20, 0x2B0, 0x58DC, 0x58E8, 0x58EC, 0x58F4
QUEUE = 0x492590
# Character 1, shot type 2, difficulty 4, rank 3. Each score record is 24 bytes.
RECORD_NAME = (1 * 3 + 2) * 0x437C + 8 + 0x10 + (4 * 10 + 3) * 24 + 6
LAST_NAME = 0x1D878


class KeyboardCase(NamedTuple):
    phase: int
    frame: int
    cell: int
    name: bytes
    length: int
    keys: int
    confirmed: int = 0


def execute(image, case, grid_size):
    cpu = Uc(UC_ARCH_X86, UC_MODE_32)
    cpu.mem_map(0x400000, 0x100000)
    for section in image.sections:
        cpu.mem_write(section['address'], image.read(section['address'], section['raw_size']))
    for address, size in ((TITLE, 0x6000), (SCORE, 0x1E000), (STACK, 0x10000), (STOP, 0x1000)):
        cpu.mem_map(address, size)

    def put(address, value):
        cpu.mem_write(address, struct.pack('<I', value))

    put(TITLE + PHASE, case.phase)
    put(TITLE + TIMER + 4, case.frame)  # current frame, not floating-point elapsed time
    put(TITLE + 0x24, 3)
    put(TITLE + GRID, case.cell)
    put(TITLE + GRID + 8, grid_size)
    put(TITLE + GRID + 0xD0, 1)  # cursor wraps
    cpu.mem_write(TITLE + NAME, case.name)
    put(TITLE + LENGTH, case.length)
    put(TITLE + CONFIRMED, case.confirmed)
    put(0x47783C, SCORE)
    put(0x474C68, 1)
    put(0x474C6C, 2)
    put(0x474C74, 4)
    # The two bytes at +4 are pressed/repeat, those at +6 are held.
    cpu.mem_write(0x474E34, struct.pack('<HH', 0, case.keys))
    cpu.mem_write(QUEUE + 0x620, b'\xff' * 48)
    cpu.mem_write(SCORE + RECORD_NAME, b'012345678')
    cpu.mem_write(SCORE + LAST_NAME, b'abcdefghi')
    sp = STACK + 0x8000
    put(sp, STOP)
    put(sp + 4, TITLE)
    for register, value in PRESERVED.items():
        cpu.reg_write(register, value)
    cpu.reg_write(UC_X86_REG_ESP, sp)
    cpu.emu_start(0x432CB0, STOP, count=10000)
    if (cpu.reg_read(UC_X86_REG_EIP) != STOP or cpu.reg_read(UC_X86_REG_ESP) != sp + 8 or
            cpu.reg_read(UC_X86_REG_EAX) != 1 or any(cpu.reg_read(r) != v for r, v in PRESERVED.items())):
        raise AssertionError(f'{case}: return value, stack or preserved-register mismatch')
    data = next(s for s in image.sections if s['name'] == '.data')
    return (cpu.mem_read(TITLE, 0x5AB0), cpu.mem_read(SCORE, 0x1E000),
            cpu.mem_read(data['address'], data['virtual_size']))


def cases(grid_size):
    def typed(length):
        return b'ABCDEFGH'[:length].ljust(8, b' ') + b'\0xyz'

    for cell in range(grid_size):
        for length in (0, 7, 8):
            yield KeyboardCase(2, 0, cell, typed(length), length, 1)
    for cell in (0, 12, 13, grid_size - 1):
        for keys in (0x10, 0x20, 0x40, 0x80, 0x80 | 1, 0x0A, 0x01 | 0x0A):
            yield KeyboardCase(2, 0, cell, typed(3), 3, keys)
    for keys in (0x01, 0x0A):
        yield KeyboardCase(2, 0, 0, typed(0), 0, keys, confirmed=1)
    for phase, elapsed in ((1, 6), (1, 7), (3, 5)):
        yield KeyboardCase(phase, elapsed, 0, typed(0), 0, 0)
    # A short saved string need not clear bytes following the terminator.
    yield KeyboardCase(2, 0, grid_size - 1, b'A\0ZZZZZZ\0xyz', 1, 1)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--oracle', type=Path, default=default_oracle())
    parser.add_argument('--candidate', type=Path, default=ROOT / 'matching2/build/msvc/th10.exe')
    args = parser.parse_args()
    _, retail = load_fixture(args.oracle)
    candidate = PEImage(args.candidate.read_bytes())
    grid_address, = struct.unpack('<I', retail.read(0x4746D8, 4))
    grid_size = retail.read(grid_address, 128).index(0)
    count = 0
    for case in cases(grid_size):
        expected = execute(retail, case, grid_size)
        actual = execute(candidate, case, grid_size)
        for area, left, right in zip(('title', 'score', 'writable globals'), expected, actual):
            if left != right:
                offset = next(i for i, (a, b) in enumerate(zip(left, right)) if a != b)
                raise AssertionError(f'{case}: {area}+{offset:#x}: retail {left[offset]:#x}, built {right[offset]:#x}')
        if case.phase == 1 and struct.unpack_from('<I', actual[0], PHASE)[0] != (2 if case.frame > 6 else 1):
            raise AssertionError('the keyboard must become editable on frame seven')
        if case.name.startswith(b'A\0'):
            score = actual[1]
            if score[RECORD_NAME:RECORD_NAME + 9] != b'A\x002345678' or score[LAST_NAME:LAST_NAME + 9] != b'A\x00cdefghi':
                raise AssertionError('saving a short name must preserve the bytes after its NUL in both buffers')
        count += 1
    print(f'{count}/{count} title keyboard cases matched retail (room, score, globals and return ABI).')


if __name__ == '__main__':
    main()
