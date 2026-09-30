#!/usr/bin/env python3
"""Compare file-cursor opening and optional following reads with retail."""
import argparse
from dataclasses import dataclass
from itertools import product
from pathlib import Path
import subprocess
import tempfile

from unicorn import UC_HOOK_CODE
from unicorn.x86_const import UC_X86_REG_EAX, UC_X86_REG_ECX, UC_X86_REG_EDX, UC_X86_REG_ESI
from music_cursor_differential import (
    Case as CursorCase, Execution as CursorExecution, compile_candidate as compile_cursor,
    COMMON, BINDINGS, SYMBOLS, ROOT, CANDIDATE, STOP, STATE, CURSOR, RECORD, ALT_RECORD,
    SOURCE, SEEK, READ, PEImage, load_manifest, load_oracle, difference)
from coff_module import load_module

PATH, CREATE_FILE = STATE + 0x900, STOP + 0x300
OPEN_SYMBOL = "_MusicCursor_Open_0044dbf0@16"


@dataclass(frozen=True)
class Case(CursorCase):
    cursor: int = CURSOR
    mode: int = 1
    filename: int = PATH
    handle: int = 0xABCD1234
    after_read: bool = False


def compile_candidates(directory, code_base=CANDIDATE):
    cursor = compile_cursor(directory, code_base + 0x2000)
    obj = directory / "cursor-open.obj"
    subprocess.run([*COMMON, "-c", str(ROOT / "matching2/reference/semantic_candidates/music_cursor_open.cpp"),
                    "-o", str(obj)], check=True, timeout=60)
    opener = load_module(obj, code_base, dict(BINDINGS, _g_music_create_file=0x4660C4))
    return opener, cursor


class Execution(CursorExecution):
    def __init__(self, image, compiled=None):
        super().__init__(image, extra_bodies={module.base: module.data for module in compiled} if compiled else None)
        self.compiled = compiled

    def initialize(self, case):
        super().initialize(case)
        self.words(CURSOR + 0x78, 0x11223344)
        self.words(CURSOR + 0x2C, 0xABCDEF00)
        self.uc.mem_write(PATH, b"bgm.dat\0")
        self.words(0x4660C4, CREATE_FILE)

    def cursor_state(self):
        return super().cursor_state(), self.read_words(CURSOR + 0x78), self.read_words(CURSOR + 0x2C)

    def hook(self, machine, address, size, context):
        if address == CREATE_FILE:
            values = self.args(7)
            self.event("create-file", *values)
            assert values[1:] == (0x80000000, 1, 0, 3, 0x08000080, 0)
            self.finish(self.case.handle, 28)
        else:
            self.api(machine, address, size, context)

    def execute(self, case):
        self.initialize(case)
        for address in (CREATE_FILE, SEEK, READ):
            self.uc.hook_add(UC_HOOK_CODE, self.hook, begin=address, end=address)
        if self.compiled:
            observed = self.run(self.compiled[0].symbols[OPEN_SYMBOL], (case.cursor, case.mode, case.filename, case.record))
        else:
            observed = self.run(0x44DBF0, (), {UC_X86_REG_ESI: case.cursor, UC_X86_REG_EAX: case.mode,
                                           UC_X86_REG_ECX: case.filename, UC_X86_REG_EDX: case.record})
        if case.after_read and not self.faults and observed["result"] == 0:
            self.event("opened", observed["result"])
            if self.compiled:
                return self.run(self.compiled[1].symbols[SYMBOLS["read"]], (case.cursor, case.requested, case.destination, case.count))
            return self.run(0x44DE10, (case.destination, case.count),
                            {UC_X86_REG_EAX: case.cursor, UC_X86_REG_EDX: case.requested})
        return observed


def cases():
    for mode, filename, record, handle in product((0, 1, 2, 257, 0xFFFFFFFF), (0, PATH), (0, RECORD), (0, 0xFFFFFFFF, 0xABCD1234)):
        yield Case(mode=mode, filename=filename, record=record, handle=handle)
    for end, offset, base in product((0, 29, 0xFFFFFFFF, 0x80000000), (0x800, 0xFFFFFFFF), (0, 0xFFFFFFFF)):
        yield Case(end=end, file_offset=offset, file_base=base, api_result=0xFFFFFFFF)
    for mode in (0, 1, 0xFFFFFFFF):
        yield Case(cursor=0, mode=mode)
    for trigger, writes in (
            ("create-file", ((CURSOR + 0x7C, 1),)),
            ("create-file", ((CURSOR + 0x7C, 0xFFFFFFFF), (CURSOR + 0x80, SOURCE + 13))),
            ("create-file", ((CURSOR + 8, 13), (CURSOR + 0x90, ALT_RECORD))),
            ("create-file", ((CURSOR + 0x8C, 0),)),
            ("seek", ((CURSOR + 0x90, ALT_RECORD),)),
            ("seek", ((CURSOR + 0x7C, 1), (CURSOR + 0x8C, 0), (CURSOR + 8, 55)))):
        for end in (0, 29, 0x80000000):
            yield Case(end=end, mutations=((trigger, writes),))
    for mode, actual, requested in product((0, 1, 2), (0, 3, "requested", None), (0, 13, 53)):
        yield Case(mode=mode, after_read=True, actual=actual, requested=requested, api_result=0)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--oracle", type=Path, default=ROOT / "matching2/build/oracle/th10.exe")
    options = parser.parse_args()
    config = load_manifest(ROOT / "matching2/msvc/regions.json")
    load_oracle(options.oracle, config)
    image = PEImage(options.oracle.read_bytes())
    with tempfile.TemporaryDirectory(prefix="th10-music-cursor-open-") as temporary:
        compiled = compile_candidates(Path(temporary))
        count = faults = 0
        for case in cases():
            expected, actual = Execution(image).execute(case), Execution(image, compiled).execute(case)
            assert actual == expected, (case, difference(expected, actual))
            count += 1
            faults += bool(expected["faults"])
        print(f"PASS: {count} file-cursor open/read comparisons, including {faults} faults; "
              f"{len(compiled[0].data)} Clang opener bytes. Native MSVC private ABIs/bytes remain unverified.")


if __name__ == "__main__":
    main()
