#!/usr/bin/env python3
"""Compare restart and complete segment service with retail x86 instructions.

Integrated cases execute restoration, full refill, and both cursor bodies.
DirectSound/Win32 remain scripted boundaries. Call traces include the streaming
fields, so callback-sensitive buffer reloads and partial failure state matter.
"""
import argparse
from dataclasses import dataclass
from itertools import product
from pathlib import Path
import subprocess
import tempfile

from unicorn import UC_HOOK_CODE, UC_HOOK_INTR
from unicorn.x86_const import UC_X86_REG_EAX, UC_X86_REG_EBX, UC_X86_REG_ECX, UC_X86_REG_ESI, UC_X86_REG_EDI
from sound_stream_fill_differential import (
    Case as FillCase, Execution as FillExecution, compile_candidates as compile_fill,
    FILL_SYMBOL, SYMBOLS, BINDINGS, STREAM, BUFFER, TABLE, ALT_TABLE, ALT_CURSOR,
    CURSOR_READ, CURSOR_REWIND, LOCK, ROOT, CANDIDATE, STOP, STATE, DATA, OUTPUT,
    CURSOR, RECORD, ALT_RECORD, SOURCE, DESTINATION, COMMON, difference,
    PEImage, load_manifest, load_oracle)
from coff_module import load_module

ARRAY, ALT_ARRAY, ALT_BUFFER = STATE + 0x1800, STATE + 0x1900, STATE + 0x1400
POSITION, GET_POSITION, STOP_BUFFER, RUN, FILL = (STOP + 0x100 * i for i in range(12, 17))
RESTART_SYMBOL, SERVICE_SYMBOL = "_SoundStream_Restart_0044dad0@4", "_SoundStream_Service_0044d850@8"
RESTORE_SYMBOL = "?RestoreIfLost@WaveSecondaryBuffer@@QAEHPAI@Z"


@dataclass(frozen=True)
class Case(FillCase):
    operation: str = "service"
    array: int = ARRAY
    reader: int = CURSOR
    incoming_ecx: int = 0xABCDEF09
    restored: int = 0
    run_result: int = 0
    fill_result: int = 0
    restore_results: tuple = (0, 0, 0, 0)
    last_play: int = 3
    played: int = 2
    write_offset: int = 4
    ended: int = 0
    segment_bytes: int = 8
    total_pcm_bytes: int = 53
    initial_play: int = 1
    write_position: int = 0
    next_play: int = 7
    first_position_result: int = 0
    next_position_result: int = 0
    next_position_writes: bool = True
    set_position_result: int = 0
    second: int = 0
    second_bytes: int = 0
    write_lock_count: bool = True


def compile_candidates(directory):
    fill = compile_fill(directory)
    obj = directory / "restore.obj"
    subprocess.run([*COMMON, "-fno-delete-null-pointer-checks", "-c",
                    str(ROOT / "matching2/msvc/src/game/platform_run_interface_0044d300.cpp"),
                    "-o", str(obj)], check=True, timeout=60)
    restore = load_module(obj, CANDIDATE + 0x5000, {"__imp__Sleep@4": 0x4660AC})
    restore_entry = restore.symbols["?Run@PlatformD300Entry@@QAEHPAI@Z"]
    unit_bindings = dict(BINDINGS, **{RESTORE_SYMBOL: RUN, FILL_SYMBOL: FILL,
                                     SYMBOLS["read"]: CURSOR_READ, SYMBOLS["rewind"]: CURSOR_REWIND})
    full_bindings = dict(BINDINGS, **{RESTORE_SYMBOL: restore_entry,
                                     FILL_SYMBOL: fill[1].symbols[FILL_SYMBOL]}, **fill[2].symbols)
    modules = {"restore": restore}
    for name, source, unit_address, full_address in (
            ("restart", "sound_stream_restart.cpp", CANDIDATE + 0x1000, CANDIDATE + 0x2000),
            ("service", "sound_stream_service.cpp", CANDIDATE + 0x3000, CANDIDATE + 0x6000)):
        obj = directory / (name + ".obj")
        subprocess.run([*COMMON, "-c", str(ROOT / "matching2/reference/semantic_candidates" / source),
                        "-o", str(obj)], check=True, timeout=60)
        modules[name] = load_module(obj, unit_address, unit_bindings)
        modules[name + "_full"] = load_module(obj, full_address, full_bindings)
    spans = sorted((module.base, module.base + len(module.data)) for module in (*fill, *modules.values()))
    assert all(end <= following for (_, end), (following, _) in zip(spans, spans[1:]))
    return fill, modules, restore_entry


class Execution(FillExecution):
    def __init__(self, image, compiled=None):
        fill, modules, restore_entry = compiled if compiled else (None, {}, None)
        super().__init__(image, fill, {module.base: module.data for module in modules.values()})
        self.modules = modules
        self.run_entries = {0x44D300, RUN}
        self.fill_entries = {0x44D110, FILL}
        if compiled:
            self.run_entries.add(restore_entry)
            self.fill_entries.add(fill[1].symbols[FILL_SYMBOL])
        self.stage = None
        self.position_calls = 0
        self.uc.hook_add(UC_HOOK_INTR, self.interrupt)

    def interrupt(self, machine, number, context):
        self.faults.append(("interrupt", number))
        self.uc.emu_stop()

    def initialize(self, case):
        super().initialize(case)
        self.stage = case.operation
        self.words(STREAM + 4, case.array, case.buffer_bytes, case.reader)
        self.words(STREAM + 0x5C, case.last_play, case.played, case.write_offset, case.ended, case.segment_bytes)
        self.words(CURSOR + 0x2C, case.total_pcm_bytes)
        self.words(ALT_CURSOR + 0x2C, 19)
        self.words(ARRAY, case.buffer)
        self.words(ALT_ARRAY, ALT_BUFFER)
        self.words(ALT_BUFFER, ALT_TABLE)
        for table in (TABLE, ALT_TABLE):
            for offset, address in ((16, GET_POSITION), (52, POSITION), (72, STOP_BUFFER)):
                self.words(table + offset, address)

    def cursor_state(self):
        return super().cursor_state(), self.read_words(STREAM + 0x5C, 5), self.read_words(CURSOR + 0x2C)

    def hook(self, machine, address, size, context):
        case = self.case
        if address in self.run_entries:
            retail = address == 0x44D300
            receiver = self.uc.reg_read(UC_X86_REG_ESI if retail else UC_X86_REG_ECX)
            out = self.uc.reg_read(UC_X86_REG_EBX) if retail else self.args(1)[0]
            self.event("run", receiver)
            if not case.integrated:
                self.words(out, case.restored)
                self.finish(case.run_result, 0 if retail else 4)
        elif address in self.fill_entries:
            if address == 0x44D110:
                stream = self.uc.reg_read(UC_X86_REG_EAX)
                buffer, repeat = self.args(2)
            else:
                stream, buffer, repeat = self.args(3)
            self.event("fill", stream, buffer, repeat)
            assert repeat == 0
            if case.integrated:
                self.stage = "fill"
            else:
                self.finish(case.fill_result, 8 if address == 0x44D110 else 12)
        elif address == GET_POSITION:
            buffer, play, write = self.args(3)
            self.position_calls += 1
            self.event("get-position", buffer, bool(play), bool(write))
            assert bool(write) == (self.position_calls == 1)
            if self.position_calls == 1:
                self.words(play, case.initial_play)
                self.words(write, case.write_position)
                result = case.first_position_result
            else:
                if case.next_position_writes:
                    self.words(play, case.next_play)
                result = case.next_position_result
            self.finish(result, 12)
        elif address == POSITION:
            buffer, position = self.args(2)
            self.event("set-position", buffer, position)
            assert position == 0
            self.finish(case.set_position_result, 8)
        elif address == STOP_BUFFER:
            buffer, = self.args(1)
            self.event("stop", buffer)
            self.finish(0x80004005, 4)
        elif address == LOCK and self.stage == "service":
            buffer, offset, requested, out, count, second, second_count, flags = self.args(8)
            self.event("lock-segment", buffer, offset, requested, self.read_words(out)[0],
                       self.read_words(count)[0], self.read_words(second)[0], bool(second_count), flags)
            assert second and second_count and flags == 0
            if case.lock_writes:
                self.words(out, case.destination)
                self.words(second, case.second)
                self.words(second_count, case.second_bytes)
                if case.write_lock_count:
                    self.words(count, case.locked_bytes)
            self.finish(case.lock_result, 32)
        elif address in self.rewind_entries:
            retail = address == 0x44DD40
            if retail:
                cursor = self.uc.reg_read(UC_X86_REG_ESI)
                flag = self.uc.reg_read(UC_X86_REG_EAX) & 255
            else:
                cursor, flag = self.args(2)
                flag &= 255
            self.event("cursor-rewind", cursor, flag)
            assert flag == (1 if self.stage == "service" else 0)
            self.rewind_calls += 1
            if case.stop_prefix and self.rewind_calls == 16:
                self.faults.append(("bounded-repeat-prefix", 16))
                self.uc.emu_stop()
            elif not case.integrated:
                self.finish(case.rewind_result, 0 if retail else 8)
        else:
            super().hook(machine, address, size, context)

    def install_operation_hooks(self):
        self.install_hooks()
        for address in (*self.run_entries, *self.fill_entries, GET_POSITION, POSITION, STOP_BUFFER):
            self.uc.hook_add(UC_HOOK_CODE, self.hook, begin=address, end=address)

    def execute(self, case):
        self.initialize(case)
        self.install_operation_hooks()
        self.uc.reg_write(UC_X86_REG_ECX, case.incoming_ecx)
        if self.modules:
            module = self.modules[case.operation + ("_full" if case.integrated else "")]
            symbol = RESTART_SYMBOL if case.operation == "restart" else SERVICE_SYMBOL
            arguments = (case.stream,) if case.operation == "restart" else (case.stream, case.repeat)
            return self.run(module.symbols[symbol], arguments)
        if case.operation == "restart":
            return self.run(0x44DAD0, (), {UC_X86_REG_EDI: case.stream})
        return self.run(0x44D850, (case.stream, case.repeat))


def cases():
    for restored, run_result, fill_result, set_result, ecx in product((0, 1, 0xFFFFFFFF), (0, 1, 0x80004005),
            (0, 1, 0x80070057), (0, 0x80004005), (0, 0xABCDEF09)):
        yield Case(operation="restart", restored=restored, run_result=run_result,
                   fill_result=fill_result, set_position_result=set_result, incoming_ecx=ecx)
    for buffered, end, file in product((0, 1), (0, 29, 0xFFFFFFFF, 0x80000000), (0, 0x12345678)):
        yield Case(operation="restart", buffered=buffered, end=end, file=file, api_result=0xFFFFFFFF)
    for operation, kwargs in product(("restart", "service"),
            ({"stream": 0}, {"array": 0}, {"buffer": 0}, {"reader": 0}, {"record": 0})):
        yield Case(operation=operation, **kwargs)
    for write, offset, segment in product((0, 4, 8, 16, 0xFFFFFFFF), (0, 1, 7, 8, 15, 16, 0xFFFFFFFE),
                                         (0, 1, 8, 0x80000000, 0xFFFFFFFF)):
        yield Case(write_position=write, write_offset=offset, segment_bytes=segment)
    for count, repeat, ended, bits in product((0, 1, 13, 31, 35), (0, 1, 0xFFFFFFFF), (0, 1), (8, 16)):
        yield Case(cursor_counts=(count, "requested"), repeat=repeat, ended=ended, bits=bits)
    for last, play, played in product((0, 7, 31, 0xFFFFFFFF), (0, 7, 31), (0, 0xFFFFFFFE)):
        yield Case(last_play=last, next_play=play, played=played, ended=1, total_pcm_bytes=15)
    for restored, run_result, fill_result in product((0, 1), (0, 1, 0x80004005), (0, 1, 0x80070057)):
        yield Case(restored=restored, run_result=run_result, fill_result=fill_result)
    for kwargs in ({"lock_result": 0x80004005}, {"second": DESTINATION + 100},
                   {"second": DESTINATION + 100, "second_bytes": 17}, {"second_bytes": 17},
                   {"cursor_results": (0x80070057,)}, {"repeat": 1, "rewind_result": 0x800401F0},
                   {"repeat": 1, "cursor_results": (0, 0x80004005)}, {"next_position_result": 0x80004005},
                   {"first_position_result": 0x80004005},
                   {"buffer_bytes": 0}, {"write_lock_count": False, "cursor_counts": ("requested",)},
                   {"destination": OUTPUT + 0xFFFA, "cursor_counts": (0,)},
                   {"repeat": 1, "cursor_counts": (0,), "stop_prefix": True}):
        yield Case(**kwargs)
    for operation, trigger, writes in (
            ("restart", "run", ((STREAM + 4, ALT_ARRAY),)),
            ("restart", "fill", ((STREAM + 0xC, ALT_CURSOR), (STREAM + 4, ALT_ARRAY))),
            ("restart", "seek", ((STREAM + 4, ALT_ARRAY), (CURSOR + 0x90, ALT_RECORD))),
            ("service", "get-position:1", ((STREAM + 4, ALT_ARRAY), (STREAM + 0x64, 7))),
            ("service", "run", ((STREAM + 4, ALT_ARRAY),)),
            ("service", "lock-segment", ((STREAM + 4, ALT_ARRAY),)),
            ("service", "cursor-read", ((STREAM + 0xC, ALT_CURSOR),)),
            ("service", "cursor-rewind", ((STREAM + 0xC, ALT_CURSOR),)),
            ("service", "unlock", ((STREAM + 4, ALT_ARRAY),)),
            ("service", "get-position:2", ((STREAM + 0x5C, 19), (STREAM + 0x60, 99))),
            ("service", "stop", ((STREAM + 8, 13), (STREAM + 0x64, 11)))):
        yield Case(operation=operation, buffered=0, restored=int(operation == "restart"), repeat=1,
                   ended=int(trigger == "stop"), total_pcm_bytes=0, mutations=((trigger, writes),))
    for operation, buffered, status, bits in product(("restart", "service"), (0, 1), (0, 2), (8, 16)):
        yield Case(operation=operation, integrated=True, buffered=buffered, status=status, bits=bits)
    for repeat, position, end, start in product((0, 1), (SOURCE, SOURCE + 37), (7, 29), (0, 3)):
        yield Case(integrated=True, position=position, limit=37, end=end, start=start, repeat=repeat)
    for operation, kwargs in product(("restart", "service"),
            ({"file": 0, "buffered": 0}, {"begin": 0}, {"record": 0},
             {"destination": OUTPUT + 0xFFFE}, {"status_result": 0x80004005},
             {"status": 2, "lock_result": 0x80070057})):
        yield Case(operation=operation, integrated=True, **kwargs)
    for counts in ((0, "requested"), (3, 7, "requested"), (100,), (None,)):
        yield Case(integrated=True, buffered=0, repeat=1, file_counts=counts, api_result=0)
    yield Case(integrated=True, buffered=0, repeat=1, file_counts=(0,), stop_prefix=True)
    yield Case(integrated=True, repeat=1, position=SOURCE + 37, start=29, end=29, stop_prefix=True)
    for operation, trigger, writes in (
            ("restart", "seek", ((STREAM + 0xC, ALT_CURSOR), (CURSOR + 0x90, ALT_RECORD))),
            ("restart", "unlock", ((STREAM + 4, ALT_ARRAY), (STREAM + 0xC, ALT_CURSOR))),
            ("service", "lock-segment", ((STREAM + 0xC, ALT_CURSOR),)),
            ("service", "read", ((STREAM + 4, ALT_ARRAY),)),
            ("service", "seek", ((CURSOR + 0x90, ALT_RECORD), (STREAM + 0xC, ALT_CURSOR)))):
        yield Case(operation=operation, integrated=True, buffered=0, repeat=1, file_counts=(3, "requested"),
                   status=2 if operation == "restart" else 0, mutations=((trigger, writes),))


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--oracle", type=Path, default=ROOT / "matching2/build/oracle/th10.exe")
    options = parser.parse_args()
    config = load_manifest(ROOT / "matching2/msvc/regions.json")
    load_oracle(options.oracle, config)
    image = PEImage(options.oracle.read_bytes())
    with tempfile.TemporaryDirectory(prefix="th10-stream-service-") as temporary:
        compiled = compile_candidates(Path(temporary))
        totals, faults, prefixes = [0, 0], [0, 0], [0, 0]
        for case in cases():
            expected = Execution(image).execute(case)
            actual = Execution(image, compiled).execute(case)
            assert actual == expected, (case, difference(expected, actual))
            index = int(case.integrated)
            totals[index] += 1
            faults[index] += bool(expected["faults"]) and not case.stop_prefix
            prefixes[index] += case.stop_prefix
        # Looping resumes at byte 3, rather than replaying the seven-byte intro.
        observed = Execution(image, compiled).execute(Case(integrated=True, repeat=1, limit=7, end=7, start=3, locked_bytes=15))
        sample = bytes(((SOURCE - DATA + i) * 71 + 19) & 255 for i in range(7))
        expected_pcm = sample + sample[3:] * 2
        offset = DESTINATION - OUTPUT
        assert observed["memory"][2][offset - 1:offset + 16] == b"\xCC" + expected_pcm + b"\xCC"
        # Do not turn an unwritten, uninitialized API output into a claimed
        # semantic pass. Record whether this compiler's frame happens to agree.
        unwritten = Case(next_position_writes=False)
        unwritten_equal = Execution(image).execute(unwritten) == Execution(image, compiled).execute(unwritten)
        print(f"PASS: {totals[0]} restart/service unit comparisons ({faults[0]} faults), "
              f"{totals[1]} with executing restore/refill/cursors ({faults[1]} faults), "
              f"{sum(prefixes)} bounded no-progress traces, and independent loop-start PCM check. "
              f"Clang restart/service: {len(compiled[1]['restart'].data)}/{len(compiled[1]['service'].data)} bytes. "
              f"Uninitialized-position diagnostic equal: {unwritten_equal} (outside pass count). "
              "Native MSVC matching remains unverified.")


if __name__ == "__main__":
    main()
