#!/usr/bin/env python3
"""Execute music cursor candidates against hash-verified retail x86 bodies.

File APIs are scripted; memory transfers execute as instructions. Checks include
output aliasing, overlapping copies, partial faults, unsigned wrapping, and
callback mutation. Explicit candidate ABIs do not establish native matching.
"""
import argparse
from dataclasses import dataclass
from itertools import product
from pathlib import Path
import struct
import subprocess
import tempfile

from unicorn import Uc, UcError, UC_ARCH_X86, UC_MODE_32, UC_HOOK_CODE, UC_HOOK_MEM_INVALID
from unicorn.x86_const import UC_X86_REG_EAX, UC_X86_REG_EDX, UC_X86_REG_ESI, UC_X86_REG_ESP, UC_X86_REG_EIP
from lzss_compressor_differential import ROOT, CANDIDATE, STACK, STOP, PRESERVED, PEImage, load_manifest, load_oracle
from coff_module import load_module

STATE, DATA, OUTPUT = 0x2500000, 0x2600000, 0x2100000
CURSOR, RECORD, ALT_RECORD, COUNT = STATE + 0x100, STATE + 0x400, STATE + 0x500, STATE + 0x800
SOURCE, DESTINATION = DATA + 0x100, OUTPUT + 0x100
SEEK, READ = STOP + 0x100, STOP + 0x200
SYMBOLS = {"rewind": "_MusicCursor_Rewind_0044dd40@8", "read": "_MusicCursor_Read_0044de10@16"}
BINDINGS = {"_g_music_seek_file": 0x4660C8, "_g_music_read_file": 0x4660D0, "_g_music_file_base": 0x4977A4}
COMMON = ["clang++", "--target=i686-pc-windows-msvc", "-std=c++03", "-O2", "-mno-sse", "-mno-sse2",
          "-fno-exceptions", "-fno-rtti", "-fno-stack-protector", "-fno-builtin"]


def compile_candidate(directory, address=CANDIDATE):
    obj = directory / "music_cursor.obj"
    subprocess.run([*COMMON, "-c", str(ROOT / "matching2/reference/semantic_candidates/music_cursor.cpp"),
                    "-o", str(obj)], check=True, timeout=60)
    return load_module(obj, address, BINDINGS)


@dataclass(frozen=True)
class Case:
    operation: str = "read"
    buffered: int = 1
    begin: int = SOURCE
    position: int = SOURCE
    limit: int = 37
    file: int = 0x12345678
    remaining: int = 37
    record: int = RECORD
    start: int = 7
    end: int = 29
    file_offset: int = 0x800
    file_base: int = 0x20
    flag: int = 0
    requested: int = 13
    destination: int = DESTINATION
    count: int = COUNT
    actual: object = "requested"
    api_result: int = 1
    mutations: tuple = ()


class Execution:
    def __init__(self, image, module=None, extra_bodies=None):
        self.uc = uc = Uc(UC_ARCH_X86, UC_MODE_32)
        uc.mem_map(0x400000, 0x100000)
        for section in image.sections:
            uc.mem_write(section["address"], image.read(section["address"], section["raw_size"]))
        for address in (CANDIDATE, STACK, STOP, STATE, DATA, OUTPUT):
            uc.mem_map(address, 0x10000)
        self.module = module
        if module:
            uc.mem_write(module.base, module.data)
        for address, body in (extra_bodies or {}).items():
            uc.mem_write(address, body)
        self.events, self.faults = [], []
        uc.hook_add(UC_HOOK_MEM_INVALID, self.fault)

    def words(self, address, *values):
        self.uc.mem_write(address, struct.pack("<" + "I" * len(values), *(v & 0xFFFFFFFF for v in values)))

    def read_words(self, address, count=1):
        return struct.unpack("<" + "I" * count, self.uc.mem_read(address, count * 4))

    def args(self, count):
        return self.read_words(self.uc.reg_read(UC_X86_REG_ESP) + 4, count)

    def finish(self, value, cleanup=0):
        uc = self.uc
        sp = uc.reg_read(UC_X86_REG_ESP)
        uc.reg_write(UC_X86_REG_EIP, self.read_words(sp)[0])
        uc.reg_write(UC_X86_REG_ESP, sp + 4 + cleanup)
        uc.reg_write(UC_X86_REG_EAX, value & 0xFFFFFFFF)

    def fault(self, machine, kind, address, size, value, context):
        self.faults.append((kind, address, size, value))
        return False

    def initialize(self, case):
        self.case = case
        uc = self.uc
        uc.mem_write(STATE, b"\xA5" * 0x10000)
        uc.mem_write(DATA, bytes((i * 71 + 19) & 255 for i in range(0x10000)))
        uc.mem_write(OUTPUT, b"\xCC" * 0x10000)
        self.words(CURSOR + 8, case.remaining)
        self.words(CURSOR + 0x7C, case.buffered, case.begin, case.position, case.limit, case.file, case.record)
        self.words(RECORD + 0x10, case.file_offset, 53, case.start, case.end)
        self.words(ALT_RECORD + 0x10, 0xAB00, 123, 19, 61)
        self.words(COUNT, 0xABCDEF00)
        self.words(0x4977A4, case.file_base)
        self.words(0x4660C8, SEEK)
        self.words(0x4660D0, READ)

    def cursor_state(self):
        return self.read_words(CURSOR + 8), self.read_words(CURSOR + 0x7C, 6)

    def event(self, kind, *values):
        self.events.append((kind, *values, self.cursor_state()))
        for trigger, writes in self.case.mutations:
            if trigger == kind:
                for address, value in writes:
                    self.words(address, value)

    def api(self, machine, address, size, context):
        case = self.case
        if address == SEEK:
            file, offset, high, origin = self.args(4)
            self.event("seek", file, offset, high, origin)
            assert high == origin == 0
            self.finish(case.api_result, 16)
        elif address == READ:
            file, destination, requested, count, overlapped = self.args(5)
            self.event("read", file, destination, requested, self.read_words(count)[0], overlapped)
            assert overlapped == 0
            actual = requested if case.actual == "requested" else case.actual
            if actual is not None:
                # A script may overreport its count without an out-of-range API write.
                amount = min(actual, requested, 128)
                self.uc.mem_write(destination, bytes((i * 31 + 7) & 255 for i in range(amount)))
                self.words(count, actual)
            self.finish(case.api_result, 20)
        else:
            raise AssertionError(hex(address))

    def run(self, entry, arguments, registers=None, budget=200000):
        uc = self.uc
        sp = STACK + 0x8000
        self.words(sp, STOP, *arguments)
        preserved = dict(PRESERVED)
        for register, value in (registers or {}).items():
            if register in preserved:
                preserved[register] = value
            uc.reg_write(register, value)
        for register, value in preserved.items():
            uc.reg_write(register, value)
        uc.reg_write(UC_X86_REG_ESP, sp)
        try:
            uc.emu_start(entry, STOP, count=budget)
        except UcError:
            if not self.faults:
                raise
        if not self.faults:
            assert uc.reg_read(UC_X86_REG_EIP) == STOP, "instruction budget exhausted"
            assert uc.reg_read(UC_X86_REG_ESP) == sp + 4 + 4 * len(arguments)
            assert all(uc.reg_read(register) == value for register, value in preserved.items())
        return {"result": uc.reg_read(UC_X86_REG_EAX) if not self.faults else None,
                "events": self.events, "faults": self.faults,
                "memory": tuple(bytes(uc.mem_read(address, 0x10000)) for address in (STATE, DATA, OUTPUT))}

    def execute(self, case):
        self.initialize(case)
        for address in (SEEK, READ):
            self.uc.hook_add(UC_HOOK_CODE, self.api, begin=address, end=address)
        if self.module:
            entry = self.module.symbols[SYMBOLS[case.operation]]
            arguments = ((CURSOR, case.flag) if case.operation == "rewind" else
                         (CURSOR, case.requested, case.destination, case.count))
            return self.run(entry, arguments)
        if case.operation == "rewind":
            return self.run(0x44DD40, (), {UC_X86_REG_ESI: CURSOR, UC_X86_REG_EAX: case.flag})
        return self.run(0x44DE10, (case.destination, case.count),
                        {UC_X86_REG_EAX: CURSOR, UC_X86_REG_EDX: case.requested})


def cases():
    for buffered, flag, start, end in product((0, 1, 0xFFFFFFFF), (0, 1, 255, 256, 257),
                                            (0, 7, 0xFFFFFFFF, 0x80000000), (0, 29, 0xFFFFFFFF, 0x80000000)):
        yield Case(operation="rewind", buffered=buffered, flag=flag, start=start, end=end)
    for flag, file, record in product((0, 1), (0, 0x12345678), (0, RECORD)):
        yield Case(operation="rewind", buffered=0, flag=flag, file=file, record=record)
    for flag, start, offset, base in product((0, 1), (7, 0x7FFFFFFF), (0xFFFFFFFF, 0x80000000), (1, 0xFFFFFFFE)):
        yield Case(operation="rewind", buffered=0, flag=flag, start=start, file_offset=offset, file_base=base,
                   api_result=0xFFFFFFFF, mutations=(("seek", ((CURSOR + 0x90, ALT_RECORD), (CURSOR + 0x8C, 0))),))
    for position, limit, requested in product((SOURCE, SOURCE + 1, SOURCE + 7, SOURCE + 37),
                                               (0, 37), (0, 1, 3, 4, 7, 37, 53)):
        yield Case(position=position, limit=limit, requested=requested)
    for delta, requested in product((-7, -4, -3, -1, 0, 1, 3, 4, 7), (0, 1, 3, 4, 5, 13, 37)):
        yield Case(destination=SOURCE + delta, requested=requested)
    for count in (0, DESTINATION, CURSOR + 8, CURSOR + 0x7C, CURSOR + 0x80, CURSOR + 0x84, CURSOR + 0x88):
        yield Case(count=count)
        yield Case(count=count, destination=SOURCE + 1)
    for destination in (0, CURSOR + 0x80, CURSOR + 0x84, OUTPUT + 0xFFFF, OUTPUT + 0xFFFA):
        yield Case(destination=destination)
    yield Case(position=0)
    yield Case(position=0, count=0)
    yield Case(destination=0, requested=0)
    for position, requested in ((DATA + 0xFFFD, 8), (SOURCE, 0xFFFFFFFF), (0xFFFFFFFC, 8)):
        yield Case(position=position, requested=requested, limit=0xFFFFFFFF)
    for requested, actual, api_result in product((0, 1, 13, 53, 0xFFFFFFFF), (None, 0, 3, 99, "requested"), (0, 1)):
        yield Case(buffered=0, requested=requested, actual=actual, api_result=api_result)
    for file, destination, count in product((0, 0x12345678), (0, DESTINATION), (0, COUNT, CURSOR + 8)):
        yield Case(buffered=0, file=file, destination=destination, count=count)
    for count in (COUNT, CURSOR + 8, DESTINATION):
        yield Case(buffered=0, count=count, actual=3, mutations=(("read", ((CURSOR + 8, 99),)),))


def difference(expected, actual):
    return {key: (expected[key], actual[key]) if key != "memory" else "memory differs"
            for key in expected if expected[key] != actual[key]}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--oracle", type=Path, default=ROOT / "matching2/build/oracle/th10.exe")
    options = parser.parse_args()
    config = load_manifest(ROOT / "matching2/msvc/regions.json")
    load_oracle(options.oracle, config)
    image = PEImage(options.oracle.read_bytes())
    with tempfile.TemporaryDirectory(prefix="th10-music-cursor-") as temporary:
        module = compile_candidate(Path(temporary))
        total = faults = 0
        for case in cases():
            expected = Execution(image).execute(case)
            actual = Execution(image, module).execute(case)
            assert actual == expected, (case, difference(expected, actual))
            total += 1
            faults += bool(expected["faults"])
        print(f"PASS: {total} music cursor comparisons, including {faults} faults; "
              f"{len(module.data)} Clang module bytes. Native MSVC matching remains unverified.")


if __name__ == "__main__":
    main()
