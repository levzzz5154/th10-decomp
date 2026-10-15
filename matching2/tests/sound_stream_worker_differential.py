#!/usr/bin/env python3
"""Compare the music notification worker, alone and through segment servicing.

The production worker already has C++ but misleading MIDI/stop names. Test its
fresh Clang build as well as a typed candidate with explicit import caching.
The integration executes segment, restore, refill and cursor implementations.
"""
import argparse
from dataclasses import dataclass
from itertools import product
from pathlib import Path
import subprocess
import tempfile

from unicorn import UC_HOOK_CODE
from sound_stream_service_differential import (
    Case as ServiceCase, Execution as ServiceExecution, compile_candidates as compile_service,
    SERVICE_SYMBOL, RESTART_SYMBOL, STREAM, ALT_CURSOR, ALT_ARRAY, CURSOR, BUFFER, ROOT, CANDIDATE,
    STOP, STATE, COMMON, difference, PEImage, load_manifest, load_oracle)
from coff_module import load_module
from unicorn.x86_const import UC_X86_REG_EDI

ALT_STREAM = STATE + 0x3000
ACTIVE, EVENT = 0x497798, 0x49779C
SERVICE, WAIT, PEEK, OTHER_WAIT, OTHER_PEEK = (STOP + 0x100 * i for i in range(17, 22))
WORKER_SYMBOL = "_SoundStream_Worker_0043e3a0@4"
MAINTAINED_SYMBOL = "_asm_MidiWorker_MessageLoopRetail_0043e3a0@4"


@dataclass(frozen=True)
class Step:
    result: int = 0
    messages: tuple = ()
    active: object = None


@dataclass(frozen=True)
class Case(ServiceCase):
    active: int = STREAM
    playing: int = 1
    steps: tuple = (Step(), Step(1, (0x12,)))
    service_result: int = 0
    peek_result: int = 1
    thread_argument: int = 0xDEADBEEF
    wait_prefix: bool = False
    restart_first: bool = False


def compile_candidates(directory):
    service = compile_service(directory)
    bindings = {"_g_sound_worker_wait": 0x46620C, "_g_sound_worker_peek": 0x46623C,
                "_g_active_music_stream": ACTIVE, "_g_music_notification_event": EVENT,
                "__imp__MsgWaitForMultipleObjects@20": 0x46620C, "__imp__PeekMessageA@20": 0x46623C,
                "_data_00497798": ACTIVE, "_data_0049779c": EVENT}
    modules = {}
    for name, source, base in (("worker", "reference/semantic_candidates/sound_stream_worker.cpp", CANDIDATE + 0x9000),
                               ("maintained", "msvc/src/platform/midi_worker.cpp", CANDIDATE + 0xB000)):
        obj = directory / (name + ".obj")
        subprocess.run([*COMMON, "-I", str(ROOT / "matching2/msvc/include"), "-c", str(ROOT / "matching2" / source),
                        "-o", str(obj)], check=True, timeout=60)
        for full in (False, True):
            target = service[1]["service_full"].symbols[SERVICE_SYMBOL] if full else SERVICE
            bound = dict(bindings, **{SERVICE_SYMBOL: target, "_asm_FUN_0044d850_0044d850": target})
            modules[name + ("_full" if full else "")] = load_module(obj, base + (0x1000 if full else 0), bound)
    return service, modules


class Execution(ServiceExecution):
    def __init__(self, image, compiled=None, maintained=False):
        service, workers = compiled if compiled else (None, {})
        super().__init__(image, service)
        self.workers, self.maintained = workers, maintained
        for module in workers.values():
            self.uc.mem_write(module.base, module.data)
        self.service_entries = {0x44D850, SERVICE}
        if service:
            self.service_entries.add(service[1]["service_full"].symbols[SERVICE_SYMBOL])
        self.wait_calls = 0
        self.pending = []

    def initialize(self, case):
        super().initialize(case)
        self.words(STREAM + 0x30, case.playing)
        self.words(STREAM + 0x74, 0xABCDEF01)
        self.uc.mem_write(ALT_STREAM, bytes(self.uc.mem_read(STREAM, 0x78)))
        self.words(ALT_STREAM + 4, ALT_ARRAY)
        self.words(ALT_STREAM + 0xC, ALT_CURSOR)
        self.words(ACTIVE, case.active, 0x12345678)
        self.words(0x46620C, WAIT)
        self.words(0x46623C, PEEK)

    def cursor_state(self):
        return (super().cursor_state(), self.read_words(ACTIVE), self.read_words(STREAM + 0x74),
                self.read_words(ALT_STREAM + 0x5C, 8))

    def hook(self, machine, address, size, context):
        case = self.case
        if address in (WAIT, OTHER_WAIT):
            if self.wait_calls == len(case.steps):
                assert case.wait_prefix, "worker exceeded the scripted wait sequence"
                self.faults.append(("bounded-wait-prefix", self.wait_calls))
                self.uc.emu_stop()
                return
            step = case.steps[self.wait_calls]
            self.wait_calls += 1
            count, handles, wait_all, timeout, mask = self.args(5)
            self.event("wait" if address == WAIT else "other-wait", count, handles,
                       self.read_words(handles)[0], wait_all, timeout, mask)
            assert (count, handles, wait_all, timeout, mask) == (1, EVENT, 0, 0xFFFFFFFF, 0xBF)
            if step.active is not None:
                self.words(ACTIVE, step.active)
            self.pending = list(step.messages)
            self.finish(step.result, 20)
        elif address in (PEEK, OTHER_PEEK):
            message, window, low, high, remove = self.args(5)
            self.event("peek" if address == PEEK else "other-peek", window, low, high, remove,
                       self.pending[0] if self.pending else None)
            assert (window, low, high, remove) == (0, 0, 0, 1)
            if self.pending:
                self.words(message + 4, self.pending.pop(0))
                self.finish(case.peek_result, 20)
            else:
                self.finish(0, 20)
        elif address in self.service_entries:
            stream, repeat = self.args(2)
            self.event("service", stream, repeat)
            assert repeat == 1
            self.position_calls = 0
            self.stage = "service"
            if not case.integrated:
                self.finish(case.service_result, 8)
        else:
            super().hook(machine, address, size, context)

    def execute(self, case):
        self.initialize(case)
        self.install_operation_hooks()
        for address in (WAIT, PEEK, OTHER_WAIT, OTHER_PEEK, *self.service_entries):
            self.uc.hook_add(UC_HOOK_CODE, self.hook, begin=address, end=address)
        if case.restart_first:
            if self.modules:
                module = self.modules["restart_full" if case.integrated else "restart"]
                restarted = self.run(module.symbols[RESTART_SYMBOL], (case.stream,))
            else:
                restarted = self.run(0x44DAD0, (), {UC_X86_REG_EDI: case.stream})
            if self.faults:
                return restarted
            self.event("restart-result", restarted["result"])
        if self.workers:
            key = ("maintained" if self.maintained else "worker") + ("_full" if case.integrated else "")
            symbol = MAINTAINED_SYMBOL if self.maintained else WORKER_SYMBOL
            entry = self.workers[key].symbols[symbol]
        else:
            entry = 0x43E3A0
        return self.run(entry, (case.thread_argument,), budget=500000)


def cases():
    for active, playing, result in product((0, STREAM, ALT_STREAM), (0, 1, 0xFFFFFFFF), (0, 1, 0x80004005)):
        yield Case(active=active, playing=playing, service_result=result)
    for messages, peek_result in product(((), (0x12,), (0x11, 0x12, 0x13), (0x12, 0x12), (0x112,)), (1, 0xFFFFFFFF)):
        yield Case(steps=(Step(1, messages), Step(1, (0x12,))), peek_result=peek_result)
    for result in (2, 0x80, 0x102, 0xFFFFFFFF):
        yield Case(steps=(Step(result), Step(1, (0x12,))))
        yield Case(steps=(Step(result, active=0),))
    yield Case(steps=(Step(1, (0x12, 0x11), active=0),))
    yield Case(active=0, steps=(Step(0, active=STREAM), Step(1, (0x12,))))
    yield Case(steps=(Step(0), Step(0), Step(0, active=0)))
    yield Case(steps=(Step(1, (0x11,)), Step(0), Step(1, (0x12,))),
               mutations=(("wait:1", ((0x46620C, OTHER_WAIT), (0x46623C, OTHER_PEEK))),))
    yield Case(mutations=(("service", ((ACTIVE, ALT_STREAM),)),))
    yield Case(mutations=(("service", ((ACTIVE, 0),)),))
    yield Case(active=0, steps=(Step(1, (0x11,)),), mutations=(("peek:1", ((ACTIVE, STREAM),)),))
    yield Case(steps=(Step(0xFFFFFFFF),) * 16, wait_prefix=True)
    for buffered, status, bits in product((0, 1), (0, 2), (8, 16)):
        yield Case(integrated=True, buffered=buffered, status=status, bits=bits)
    for buffered, status in product((0, 1), (0, 2)):
        yield Case(integrated=True, buffered=buffered, status=status, restart_first=True, restore_results=(0,) * 12)
    for kwargs in ({"active": ALT_STREAM}, {"playing": 0}, {"write_position": 8},
                   {"lock_result": 0x80004005}, {"status_result": 0x80070057},
                   {"buffered": 0, "file": 0}, {"record": 0}, {"buffer_bytes": 0},
                   {"buffered": 0, "file_counts": (0, "requested")},
                   {"steps": (Step(), Step(), Step(), Step(1, (0x12,)))},
                   {"mutations": (("unlock", ((ACTIVE, ALT_STREAM),)),)},
                   {"mutations": (("unlock", ((ACTIVE, 0),)),)}):
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
    with tempfile.TemporaryDirectory(prefix="th10-music-worker-") as temporary:
        compiled = compile_candidates(Path(temporary))
        totals, faults, services, maintained_gaps = [0, 0], [0, 0], 0, 0
        for case in cases():
            expected = Execution(image).execute(case)
            actual = Execution(image, compiled).execute(case)
            assert actual == expected, (case, difference(expected, actual))
            maintained = Execution(image, compiled, maintained=True).execute(case)
            if maintained != expected:
                assert any(address in (0x46620C, 0x46623C) for _, writes in case.mutations for address, _ in writes), (case, difference(expected, maintained))
                maintained_gaps += 1
            index = int(case.integrated)
            totals[index] += 1
            faults[index] += bool(expected["faults"]) and not case.wait_prefix
            services += sum(event[0] == "service" for event in expected["events"])
        print(f"PASS: {totals[0]} worker unit comparisons ({faults[0]} faults), "
              f"{totals[1]} with executing segment/refill/cursors ({faults[1]} faults), "
              f"{services} service calls, 1 bounded wait trace. "
              f"Maintained Clang import-caching gaps: {maintained_gaps}; "
              f"typed/maintained worker modules: {len(compiled[1]['worker'].data)}/{len(compiled[1]['maintained'].data)} bytes. "
              "Native MSVC matching remains unverified.")


if __name__ == "__main__":
    main()
