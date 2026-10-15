#!/usr/bin/env python3
"""Compare file-stream launch, optionally executing shutdown through PCM refill.

Win32, COM, allocation and the deleting destructor remain scripted. Thread
creation records its entry/argument without simulating asynchronous execution.
"""
import argparse
from dataclasses import dataclass
from itertools import product
from pathlib import Path
import struct
import subprocess
import tempfile

from unicorn import UC_HOOK_CODE, UC_HOOK_INTR
from unicorn.x86_const import UC_X86_REG_EAX, UC_X86_REG_ECX, UC_X86_REG_EDX, UC_X86_REG_ESI
from sound_stream_create_file_differential import (
    Case as FileCase, Execution as FileExecution, compile_candidates as compile_factory,
    FACTORY_SYMBOL, PATH, CLOSE_FILE, COMMON, ROOT, CANDIDATE, STOP, STATE, RECORD,
    ALT_RECORD, OWNER, PEImage, load_manifest, load_oracle, difference)
from sound_stream_initialize_differential import (
    ALLOCATE, FREE, RELEASE, CREATE, QUERY, SET_NOTICES, RELEASE_NOTIFY, POSITION,
    STREAM, TABLE, ALT_TABLE, ALT_OWNER, DEVICE, HEAP)
from coff_module import load_module
from x86_seh import exception_list, INITIAL_EXCEPTION_LIST

MANAGER = 0x2800000
STOP_MUSIC, CREATE_EVENT, CREATE_THREAD, FACTORY, POST, WAIT, DESTROY, AGG_STOP = (
    STOP + offset for offset in (0x2300, 0x2400, 0x2500, 0x2600, 0x2700, 0x2800, 0x2900, 0x2A00))
STREAM_TABLE = STATE + 0x3300
LAUNCH_SYMBOL = "_SoundStream_LaunchFile_0043d690@8"
STOP_SYMBOL = "_Sound_StopMusicWorker_0043dab0@4"
AGG_SYMBOL = "?Aggregate@PlatformInterfaceState_0044D550@@QAEHXZ"


@dataclass(frozen=True)
class Case(FileCase):
    manager: int = MANAGER
    manager_device: int = DEVICE
    name: bytes = b"thbgm.dat\0"
    sample_rate: int = 44100
    alignment: int = 4
    old_stream: int = STREAM
    old_thread: int = 0x87654321
    old_event: int = 0x55556666
    event_result: int = 0xABCD1111
    thread_result: int = 0xABCD2222
    thread_id: object = 0x1234
    worker_argument: int = 0xFEDCBA98
    factory_result: int = 0
    wait_results: tuple = (0,)


def compile_candidates(directory):
    factory = compile_factory(directory)
    obj = directory / "aggregate.obj"
    subprocess.run([*COMMON, "-c", str(ROOT / "matching2/msvc/src/game/platform_aggregate_interfaces_0044d550.cpp"),
                    "-o", str(obj)], check=True, timeout=60)
    aggregate = load_module(obj, CANDIDATE + 0x12000, {})
    obj = directory / "stop-music.obj"
    subprocess.run([*COMMON, "-c", str(ROOT / "matching2/reference/semantic_candidates/sound_midi_stop.cpp"),
                    "-o", str(obj)], check=True, timeout=60)
    stop = load_module(obj, CANDIDATE + 0x10000, {
        "_g_sound_post_thread_message": 0x466210, "_g_sound_wait_for_object": 0x46611C,
        "_g_sound_close_handle": 0x4660CC,
        "@Sound_AggregateInterfaces_0044d550@4": aggregate.symbols[AGG_SYMBOL]})
    obj = directory / "launch-file.obj"
    subprocess.run([*COMMON, "-c", str(ROOT / "matching2/reference/semantic_candidates/sound_stream_launch.cpp"),
                    "-o", str(obj)], check=True, timeout=60)
    bindings = {"_g_music_create_event": 0x466120, "_g_music_create_thread": 0x466118,
                "_g_music_worker_argument": 0x491C70, "_g_music_stream_algorithm": 0x46A67C,
                "_SoundStream_Worker_0043e3a0@4": 0x43E3A0}
    unit = load_module(obj, CANDIDATE + 0xE000,
                       dict(bindings, **{STOP_SYMBOL: STOP_MUSIC, FACTORY_SYMBOL: FACTORY}))
    full = load_module(obj, CANDIDATE + 0xF000, dict(bindings, **{
        STOP_SYMBOL: stop.symbols[STOP_SYMBOL], FACTORY_SYMBOL: factory[2].symbols[FACTORY_SYMBOL]}))
    return factory, unit, full, stop, aggregate


class LaunchHarness:
    launch_symbol = LAUNCH_SYMBOL
    factory_argument_count = 12

    def __init__(self, image, compiled=None):
        super().__init__(image, compiled[0] if compiled else None)
        self.uc.mem_map(MANAGER, 0x10000)
        self.uc.mem_map(CANDIDATE + 0x10000, 0x10000)
        self.launches = compiled[1:3] if compiled else ()
        if compiled:
            for module in compiled[1:]:
                self.uc.mem_write(module.base, module.data)
        self.stop_entries = {0x43DAB0, STOP_MUSIC}
        self.factory_entries = {self.retail_entry, FACTORY}
        if compiled:
            if STOP_SYMBOL in compiled[3].symbols:
                self.stop_entries.add(compiled[3].symbols[STOP_SYMBOL])
            self.factory_entries.add(compiled[0][2].symbols[self.factory_symbol])
        self.wait_calls = 0

    def initialize(self, case):
        super().initialize(case)
        self.uc.mem_write(MANAGER, b"\xA5" * 0x10000)
        self.words(MANAGER, case.manager_device)
        self.words(MANAGER + 0x610, case.owner, 0x4321, case.old_thread)
        self.words(MANAGER + 0x1F84, case.record)
        self.words(MANAGER + 0x5208, case.old_stream, case.old_event)
        if case.filename:
            self.uc.mem_write(case.filename, case.name)
        for record, rate, alignment in ((RECORD, case.sample_rate, case.alignment), (ALT_RECORD, 48000, 2)):
            self.words(record + 0x24, rate)
            self.uc.mem_write(record + 0x2C, struct.pack("<H", alignment))
        self.words(0x491C70, case.worker_argument)
        self.words(0x46A67C, *case.algorithm)
        self.words(0x466120, CREATE_EVENT)
        self.words(0x466118, CREATE_THREAD)
        self.words(0x466210, POST)
        self.words(0x46611C, WAIT)
        self.words(STREAM, STREAM_TABLE)
        self.words(STREAM_TABLE, DESTROY)
        for table in (TABLE, ALT_TABLE):
            self.words(table + 72, AGG_STOP)

    def cursor_state(self):
        return (super().cursor_state(), self.read_words(MANAGER), self.read_words(MANAGER + 0x610, 3),
                self.read_words(MANAGER + 0x1F84), self.read_words(MANAGER + 0x5208, 2))

    def interrupt(self, machine, number, context):
        self.faults.append(("interrupt", number))
        self.uc.emu_stop()

    def hook(self, machine, address, size, context):
        case = self.case
        if address in self.stop_entries:
            retail = address == 0x43DAB0
            manager = self.uc.reg_read(UC_X86_REG_ESI) if retail else self.args(1)[0]
            self.event("stop-music", manager)
            if not case.integrated:
                self.finish(0xBAD, 0 if retail else 4)
        elif address == CREATE_EVENT:
            values = self.args(4)
            self.event("create-event", *values)
            assert values == (0, 0, 0, 0)
            self.finish(case.event_result, 16)
        elif address == CREATE_THREAD:
            values = self.args(6)
            self.event("create-thread", *values)
            assert values[:3] == (0, 0, 0x43E3A0) and values[4] == 0
            if case.thread_id is not None:
                self.words(values[5], case.thread_id)
            self.finish(case.thread_result, 24)
        elif address in self.factory_entries:
            retail = address == self.retail_entry
            count = self.factory_argument_count
            values = ((self.uc.reg_read(UC_X86_REG_ECX), self.uc.reg_read(UC_X86_REG_EDX), *self.args(count - 2))
                      if retail else self.args(count))
            self.event("factory", *values)
            if not case.integrated:
                self.words(values[0], STREAM)
                self.finish(case.factory_result, (count - 2 if retail else count) * 4)
        elif address == POST:
            values = self.args(4)
            self.event("post", *values)
            assert values[1:] == (0x12, 0, 0)
            self.finish(0, 16)
        elif address == WAIT:
            handle, delay = self.args(2)
            result = self.selected(case.wait_results, self.wait_calls)
            self.wait_calls += 1
            self.event("wait", handle, delay, result)
            assert delay == 0x100 and self.wait_calls <= 8
            self.finish(result, 8)
        elif address == DESTROY:
            receiver, flags = self.uc.reg_read(UC_X86_REG_ECX), self.args(1)[0]
            self.event("destroy", receiver, flags)
            assert flags == 1
            self.finish(receiver, 4)
        elif address == AGG_STOP:
            buffer, = self.args(1)
            self.event("aggregate-stop", buffer)
            self.finish(0x80004005, 4)
        else:
            super().hook(machine, address, size, context)

    def launch_extra_hooks(self):
        return ()

    def candidate_launch_arguments(self, case):
        return case.manager, case.filename

    def retail_launch_arguments(self, case):
        return 0x43D690, (case.filename,), {UC_X86_REG_EAX: case.manager}

    def execute(self, case):
        self.initialize(case)
        self.install_hooks()
        self.uc.hook_add(UC_HOOK_INTR, self.interrupt)
        for address in (ALLOCATE, FREE, RELEASE, CREATE, QUERY, SET_NOTICES, RELEASE_NOTIFY, POSITION,
                        *self.fill_entries, *self.construct_entries, *self.extra_hook_addresses(),
                        *self.stop_entries, *self.factory_entries, CREATE_EVENT, CREATE_THREAD, POST, WAIT, DESTROY, AGG_STOP,
                        *self.launch_extra_hooks()):
            self.uc.hook_add(UC_HOOK_CODE, self.hook, begin=address, end=address)
        if self.launches:
            observed = self.run(self.launches[int(case.integrated)].symbols[self.launch_symbol],
                                self.candidate_launch_arguments(case), budget=500000)
        else:
            observed = self.run(*self.retail_launch_arguments(case), budget=500000)
        if not self.faults:
            assert exception_list(self.uc) == INITIAL_EXCEPTION_LIST
        observed.update(allocated=self.allocated, freed=self.freed,
                        manager=bytes(self.uc.mem_read(MANAGER, 0x10000)))
        return observed


class Execution(LaunchHarness, FileExecution):
    pass


def cases():
    for rate, alignment, result in product((0, 1, 44100, 48000, 0x7FFFFFFF, 0x80000000, 0xFFFFFFFF),
                                           (0, 1, 2, 4, 0xFFFF), (0, 1, 0x7FFFFFFF, 0x80000000, 0xFFFFFFFF)):
        yield Case(sample_rate=rate, alignment=alignment, factory_result=result)
    for event, thread, tid in product((0, 0xABCD1111), (0, 0xABCD2222), (None, 0x1234)):
        yield Case(event_result=event, thread_result=thread, thread_id=tid)
    for kwargs in ({"owner": 0}, {"manager_device": 0}, {"device": 0}, {"record": 0}, {"manager": 0},
                   {"filename": 0}, {"filename": 0, "owner": 0}, {"name": b"\0"},
                   {"name": b"x" * 300 + b"\0", "owner": 0},
                   {"filename": MANAGER + 0x5108}, {"filename": MANAGER + 0x5109},
                   {"filename": MANAGER + 0x5107}):
        yield Case(**kwargs)
    for trigger, writes in (
            ("stop-music", ((MANAGER + 0x1F84, ALT_RECORD),)),
            ("create-event", ((MANAGER + 0x1F84, ALT_RECORD), (RECORD + 0x24, 1), (RECORD + 0x2C, 0))),
            ("create-event", ((0x491C70, 0x12345678),)),
            ("create-thread", ((MANAGER + 0x520C, 0x99887766), (MANAGER + 0x610, ALT_OWNER))),
            ("create-thread", ((0x46A67C, 0), (0x46A680, 0xFFFFFFFF), (0x46A684, 1), (0x46A688, 2))),
            ("create-thread", ((PATH, 0x006D6762),)),
            ("create-thread", ((MANAGER + 0x618, 0),))):
        yield Case(mutations=((trigger, writes),))
    yield Case(alignment=0, mutations=(("create-thread", ((RECORD + 0x2C, 4),)),))
    for stream, thread, bits, handle in product((0, STREAM), (0, 0x87654321), (8, 16), (0, 0xFFFFFFFF, 0xABCD1234)):
        yield Case(integrated=True, old_stream=stream, old_thread=thread, bits=bits, handle=handle)
    for kwargs in ({"owner": 0}, {"manager_device": 0}, {"device": 0}, {"record": 0}, {"filename": 0},
                   {"alignment": 0}, {"event_result": 0, "thread_result": 0},
                   {"wait_results": (258, 0xFFFFFFFF, 0)}, {"initial_array": 0}, {"count": 0},
                   {"status_result": 0x80004005}, {"lock_result": 0x80070057},
                   {"create_results": (0x80004005,)}, {"query_results": (0x80004005,)},
                   {"notice_results": (0x80004005,)}, {"fail_allocate": 1}, {"fail_allocate": 2},
                   {"fail_allocate": 3}, {"fail_allocate": 4}, {"file_counts": (0,)}, {"file_counts": (3,)}):
        yield Case(integrated=True, **kwargs)
    for trigger, writes in (
            ("destroy", ((MANAGER + 0x1F84, ALT_RECORD),)),
            ("aggregate-stop:1", ((MANAGER + 0x618, 0),)),
            ("create-event", ((RECORD + 0x24, 1), (RECORD + 0x2C, 0))),
            ("create-thread", ((MANAGER + 0x520C, 0),)),
            ("create-thread", ((MANAGER + 0x610, ALT_OWNER),)),
            ("create-thread", ((MANAGER + 0x610, 0),)),
            ("create-file", ((HEAP + 16 + 0x90, ALT_RECORD),)),
            ("read", ((MANAGER + 0x5208, STREAM),))):
        yield Case(integrated=True, mutations=((trigger, writes),))


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
    with tempfile.TemporaryDirectory(prefix="th10-launch-file-stream-") as temporary:
        compiled = compile_candidates(Path(temporary))
        totals, faults = [0, 0], [0, 0]
        for case in cases():
            expected, actual = Execution(image).execute(case), Execution(image, compiled).execute(case)
            assert actual == expected, (case, difference(expected, actual))
            index = int(case.integrated)
            totals[index] += 1
            faults[index] += bool(expected["faults"])
        observed = Execution(image, compiled).execute(Case(integrated=True))
        factory, = (event for event in observed["events"] if event[0] == "factory")
        assert factory[1:5] == (MANAGER + 0x5208, 0x10100, OWNER, PATH)
        assert factory[9:13] == (16, 44100, 0xABCD1111, RECORD)
        assert struct.unpack_from("<I", observed["manager"], 0x5208)[0] == observed["allocated"][2][0]
        failed = Execution(image, compiled).execute(Case(integrated=True, handle=0xFFFFFFFF))
        assert failed["result"] == 0xFFFFFFFF
        assert struct.unpack_from("<I", failed["manager"], 0x618)[0] == 0xABCD2222
        assert struct.unpack_from("<II", failed["manager"], 0x5208) == (0, 0xABCD1111)
        print(f"PASS: {totals[0]} launch unit comparisons ({faults[0]} faults), "
              f"{totals[1]} with executing shutdown/aggregate/factory/open/initializer/refill/cursors "
              f"({faults[1]} faults), independent parameter/publication/failed-open checks; "
              f"{len(compiled[1].data)} Clang launch bytes. Live threads and native MSVC matching remain unverified.")


if __name__ == "__main__":
    main()
