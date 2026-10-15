#!/usr/bin/env python3
"""Compare PCM refill with retail, with scripted and executing music cursors.

DirectSound and Win32 remain scripted. All copying, cursor arithmetic, padding,
and integrated rewind/read bodies execute as freshly compiled C++ or retail x86.
Known no-progress loops are checked through matching bounded callback traces.
"""
import argparse
from dataclasses import dataclass
from itertools import product
from pathlib import Path
import subprocess
import tempfile

from unicorn import UC_HOOK_CODE
from unicorn.x86_const import UC_X86_REG_EAX, UC_X86_REG_EDX, UC_X86_REG_ESI
from music_cursor_differential import (
    Case as CursorCase, Execution as CursorExecution, compile_candidate as compile_cursor,
    SYMBOLS, BINDINGS, COMMON, ROOT, CANDIDATE, STOP, STATE, DATA, OUTPUT,
    CURSOR, RECORD, ALT_RECORD, SOURCE, DESTINATION, SEEK, READ, difference,
    PEImage, load_manifest, load_oracle)
from coff_module import load_module

STREAM, BUFFER, TABLE, ALT_TABLE, ALT_CURSOR = (STATE + offset for offset in (0x1000, 0x1100, 0x1200, 0x1300, 0xA00))
STATUS, RESTORE, SLEEP, OTHER_SLEEP, LOCK, UNLOCK, OTHER_UNLOCK, CURSOR_READ, CURSOR_REWIND = (
    STOP + 0x100 * i for i in range(3, 12))
FILL_SYMBOL = "_SoundStream_FillBuffer_0044d110@12"


@dataclass(frozen=True)
class Case(CursorCase):
    integrated: bool = False
    stream: int = STREAM
    buffer: int = BUFFER
    buffer_bytes: int = 32
    locked_bytes: int = 31
    lock_writes: bool = True
    bits: int = 16
    repeat: int = 0
    status: int = 0
    status_result: int = 0
    restore_results: tuple = (0, 0)
    lock_result: int = 0
    unlock_result: int = 0x80004005
    cursor_results: tuple = (0,)
    cursor_counts: tuple = (13,)
    rewind_result: int = 0
    file_counts: tuple = ("requested",)
    stop_prefix: bool = False


def compile_candidates(directory):
    cursor = compile_cursor(directory, CANDIDATE + 0x8000)
    obj = directory / "fill.obj"
    subprocess.run([*COMMON, "-c", str(ROOT / "matching2/reference/semantic_candidates/sound_stream_fill.cpp"),
                    "-o", str(obj)], check=True, timeout=60)
    bindings = dict(BINDINGS, _g_stream_sleep=0x4660AC)
    unit = load_module(obj, CANDIDATE, dict(bindings, **{SYMBOLS["read"]: CURSOR_READ, SYMBOLS["rewind"]: CURSOR_REWIND}))
    full = load_module(obj, CANDIDATE + 0x4000, dict(bindings, **cursor.symbols))
    return unit, full, cursor


class Execution(CursorExecution):
    def __init__(self, image, compiled=None, extra_bodies=None):
        super().__init__(image, extra_bodies=extra_bodies)
        self.compiled = compiled
        if compiled:
            for module in compiled:
                self.uc.mem_write(module.base, module.data)
        self.occurrences = {}
        self.restore_calls = self.read_calls = self.file_reads = self.rewind_calls = 0

    def initialize(self, case):
        super().initialize(case)
        self.words(STREAM, 0, STATE + 0x1800, case.buffer_bytes, CURSOR, 1)
        self.words(BUFFER, TABLE)
        for table in (TABLE, ALT_TABLE):
            for offset, address in ((36, STATUS), (44, LOCK), (76, UNLOCK if table == TABLE else OTHER_UNLOCK), (80, RESTORE)):
                self.words(table + offset, address)
        self.words(0x4660AC, SLEEP)
        self.uc.mem_write(RECORD + 0x2E, case.bits.to_bytes(2, "little"))
        self.uc.mem_write(ALT_RECORD + 0x2E, (8).to_bytes(2, "little"))
        self.words(ALT_CURSOR + 8, 23)
        self.words(ALT_CURSOR + 0x7C, 1, SOURCE + 0x100, SOURCE + 0x100, 19, 0, ALT_RECORD)

    def cursor_state(self):
        return (super().cursor_state(), self.read_words(ALT_CURSOR + 8),
                self.read_words(ALT_CURSOR + 0x7C, 6), self.read_words(STREAM, 13))

    def event(self, kind, *values):
        self.events.append((kind, *values, self.cursor_state()))
        self.occurrences[kind] = self.occurrences.get(kind, 0) + 1
        for trigger, writes in self.case.mutations:
            if trigger in (kind, f"{kind}:{self.occurrences[kind]}"):
                for address, value in writes:
                    self.words(address, value)

    @staticmethod
    def selected(sequence, index):
        return sequence[min(index, len(sequence) - 1)]

    def hook(self, machine, address, size, context):
        case = self.case
        if address == STATUS:
            buffer, out = self.args(2)
            self.event("status", buffer)
            self.words(out, case.status)
            self.finish(case.status_result, 8)
        elif address == RESTORE:
            buffer, = self.args(1)
            assert self.restore_calls < len(case.restore_results)
            result = case.restore_results[self.restore_calls]
            self.restore_calls += 1
            self.event("restore", buffer, result)
            self.finish(result, 4)
        elif address in (SLEEP, OTHER_SLEEP):
            delay, = self.args(1)
            self.event("sleep" if address == SLEEP else "other-sleep", delay)
            assert delay == 10
            self.finish(0xABCD, 4)
        elif address == LOCK:
            buffer, offset, requested, out, count, second, second_count, flags = self.args(8)
            self.event("lock", buffer, offset, requested, self.read_words(out)[0], self.read_words(count)[0], second, second_count, flags)
            assert offset == second == second_count == flags == 0
            if case.lock_writes:
                self.words(out, case.destination)
                self.words(count, case.locked_bytes)
            self.finish(case.lock_result, 32)
        elif address in (UNLOCK, OTHER_UNLOCK):
            values = self.args(5)
            self.event("unlock" if address == UNLOCK else "other-unlock", *values)
            assert values[3:] == (0, 0)
            self.finish(case.unlock_result, 20)
        elif address == SEEK:
            super().api(machine, address, size, context)
        elif address == READ:
            file, destination, requested, count, overlapped = self.args(5)
            self.event("read", file, destination, requested, self.read_words(count)[0], overlapped)
            assert overlapped == 0
            actual = self.selected(case.file_counts, self.file_reads)
            self.file_reads += 1
            actual = requested if actual == "requested" else actual
            if actual is not None:
                amount = min(actual, requested, 128)
                self.uc.mem_write(destination, bytes((i * 31 + 7) & 255 for i in range(amount)))
                self.words(count, actual)
            self.finish(case.api_result, 20)
        elif address in self.read_entries:
            retail = address == 0x44DE10
            if retail:
                cursor, requested = self.uc.reg_read(UC_X86_REG_EAX), self.uc.reg_read(UC_X86_REG_EDX)
                destination, count = self.args(2)
            else:
                cursor, requested, destination, count = self.args(4)
            self.event("cursor-read", cursor, requested, destination, self.read_words(count)[0])
            if not case.integrated:
                result = self.selected(case.cursor_results, self.read_calls)
                actual = self.selected(case.cursor_counts, self.read_calls)
                actual = requested if actual == "requested" else actual
                if actual is not None:
                    self.words(count, actual)
                    if result < 0x80000000:
                        amount = min(actual, requested, 128)
                        self.uc.mem_write(destination, bytes((i * 43 + 11) & 255 for i in range(amount)))
                self.finish(result, 8 if retail else 16)
            self.read_calls += 1
        elif address in self.rewind_entries:
            retail = address == 0x44DD40
            if retail:
                cursor, flag = self.uc.reg_read(UC_X86_REG_ESI), self.uc.reg_read(UC_X86_REG_EAX) & 255
            else:
                cursor, flag = self.args(2)
                flag &= 255
            self.event("cursor-rewind", cursor, flag)
            assert flag == 0
            self.rewind_calls += 1
            if case.stop_prefix and self.rewind_calls == 16:
                self.faults.append(("bounded-repeat-prefix", 16))
                self.uc.emu_stop()
            elif not case.integrated:
                self.finish(case.rewind_result, 0 if retail else 8)
        else:
            raise AssertionError(hex(address))

    def install_hooks(self):
        self.read_entries = {0x44DE10, CURSOR_READ}
        self.rewind_entries = {0x44DD40, CURSOR_REWIND}
        if self.compiled:
            cursor = self.compiled[2]
            self.read_entries.add(cursor.symbols[SYMBOLS["read"]])
            self.rewind_entries.add(cursor.symbols[SYMBOLS["rewind"]])
        for address in (STATUS, RESTORE, SLEEP, OTHER_SLEEP, LOCK, UNLOCK, OTHER_UNLOCK, SEEK, READ,
                        *self.read_entries, *self.rewind_entries):
            self.uc.hook_add(UC_HOOK_CODE, self.hook, begin=address, end=address)

    def execute(self, case):
        self.initialize(case)
        self.install_hooks()
        if self.compiled:
            module = self.compiled[1 if case.integrated else 0]
            return self.run(module.symbols[FILL_SYMBOL], (case.stream, case.buffer, case.repeat))
        return self.run(0x44D110, (case.buffer, case.repeat), {UC_X86_REG_EAX: case.stream})


def cases():
    for bits, repeat, count, locked_bytes in product((0, 8, 16, 24), (0, 1, 0xFFFFFFFF), (0, 1, 7, 13, 31, 35), (0, 31)):
        yield Case(bits=bits, repeat=repeat, cursor_counts=(count, "requested"), locked_bytes=locked_bytes)
    for status, restores in ((0, ()), (1, ()), (2, (0, 0)), (3, (0x88780096, 0)),
                             (2, (0x80004005, 1, 0x88780096, 0)),
                             (2, (0x88780096, 0x80004005, 0x88780096, 0))):
        yield Case(status=status, restore_results=restores)
    yield Case(status=2, restore_results=(0x88780096, 1, 0x88780096, 0),
               mutations=(("sleep", ((0x4660AC, OTHER_SLEEP),)),))
    for kwargs in ({"buffer": 0}, {"stream": 0, "buffer": 0}, {"status_result": 0x80004005},
                   {"lock_result": 0x80070057}, {"cursor_results": (0x80004005,)},
                   {"repeat": 1, "rewind_result": 0x800401F0},
                   {"repeat": 1, "cursor_results": (0, 0x80004005)}, {"lock_writes": False, "cursor_counts": (0,)}):
        yield Case(**kwargs)
    for mutation in (((STREAM + 8, 71),), ((STREAM + 0xC, ALT_CURSOR),), ((BUFFER, ALT_TABLE),)):
        for trigger in ("status", "lock", "cursor-read"):
            yield Case(mutations=((trigger, mutation),))
    yield Case(repeat=1, cursor_counts=(3, 7, "requested"), mutations=(("cursor-rewind", ((STREAM + 0xC, ALT_CURSOR),)),))
    yield Case(repeat=1, cursor_counts=(1, 0), stop_prefix=True)
    for destination, count in product((OUTPUT + 0xFFFF, OUTPUT + 0xFFFA), (0, 1)):
        yield Case(destination=destination, cursor_counts=(count,))
    yield Case(stream=0)
    yield Case(record=0)
    yield Case(mutations=(("lock", ((STREAM + 0xC, 0),)),))
    for buffered, bits, repeat, end, locked in product((0, 1), (8, 16), (0, 1), (0, 1, 7, 29), (0, 31)):
        yield Case(integrated=True, buffered=buffered, bits=bits, repeat=repeat, end=end, locked_bytes=locked)
    for counts, repeat in product(((0,), (1, 3, "requested"), (None,), (100,), ("requested",)), (0, 1)):
        yield Case(integrated=True, buffered=0, file_counts=counts, repeat=repeat, api_result=0)
    yield Case(integrated=True, buffered=0, file_counts=(1, 0), repeat=1, stop_prefix=True)
    for mutation in (((CURSOR + 0x90, ALT_RECORD),), ((STREAM + 0xC, ALT_CURSOR),),
                     ((CURSOR + 0x8C, 0),), ((CURSOR + 0x7C, 1),), ((CURSOR + 8, 0),)):
        for trigger in ("seek", "read"):
            yield Case(integrated=True, buffered=0, mutations=((trigger, mutation),))
    for kwargs in ({"file": 0, "buffered": 0}, {"begin": 0}, {"record": 0},
                   {"destination": OUTPUT + 0xFFFE}, {"destination": SOURCE + 1},
                   {"destination": CURSOR + 0x84, "locked_bytes": 4}, {"end": 0xFFFFFFFF},
                   {"end": 0x80000000}, {"lock_writes": False}):
        yield Case(integrated=True, **kwargs)


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
    with tempfile.TemporaryDirectory(prefix="th10-stream-fill-") as temporary:
        compiled = compile_candidates(Path(temporary))
        totals, faults, prefixes = [0, 0], [0, 0], [0, 0]
        for case in cases():
            expected = Execution(image).execute(case)
            actual = Execution(image, compiled).execute(case)
            assert actual == expected, (case, difference(expected, actual))
            index = int(case.integrated)
            totals[index] += 1
            prefixes[index] += case.stop_prefix
            faults[index] += bool(expected["faults"]) and not case.stop_prefix
        print(f"PASS: {totals[0]} refill unit comparisons ({faults[0]} faults), "
              f"{totals[1]} with executing music cursors ({faults[1]} faults), "
              f"{sum(prefixes)} bounded no-progress traces; {len(compiled[0].data)} Clang refill bytes. "
              "Native MSVC matching remains unverified.")


if __name__ == "__main__":
    main()
