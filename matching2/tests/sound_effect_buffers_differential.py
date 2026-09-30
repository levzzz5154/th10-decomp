#!/usr/bin/env python3
"""Compare effect duplication, worker-pair shutdown, and setup-to-playback.

The global shutdown target and the receiver can be distinct. COM/Win32 calls
are scripted; integrated cases execute shutdown, queue producers and dispatch.
"""
import argparse
from dataclasses import dataclass
from itertools import product
from pathlib import Path
import struct
import subprocess
import tempfile

from unicorn import UC_HOOK_CODE
from unicorn.x86_const import UC_X86_REG_EBX, UC_X86_REG_ECX, UC_X86_REG_ESI, UC_X86_REG_EDI, UC_X86_REG_FPCW, UC_X86_REG_FPTAG, UC_X86_REG_FPSW
from sound_effect_queue_differential import (
    Case as QueueCase, Execution as QueueExecution, compile_candidates as compile_queue, float_bits,
    PLAY_SYMBOL, STOP_SYMBOL, ROOT, COMMON, CANDIDATE, STATE, MANAGER, BUFFER, DISPATCH_SYMBOL,
    DATA, OUTPUT, PEImage, load_manifest, load_oracle, difference)
from sound_commands_differential import TABLE, ALT_TABLE, ALT_BUFFER, THIRD, VOLUME, EFFECT_POSITION
from sound_stream_initialize_differential import DEVICE, DEVICE_TABLE, OWNER, ALT_OWNER
from lzss_compressor_differential import STOP
from coff_module import load_module

GLOBAL = 0x492590
SOURCE_BUFFERS, DUPLICATE_BUFFERS = STATE + 0x5000, STATE + 0x6000
PWAIT, PSLEEP, PCLOSE, OTHER_WAIT, OTHER_SLEEP, OTHER_CLOSE, STOP_WORKERS, DUPLICATE = (
    STOP + value for value in (0x7000, 0x7100, 0x7200, 0x7300, 0x7400, 0x7500, 0x7600, 0x7700))
SETUP_SYMBOL = "_Sound_InitializeEffects_0043db60@4"
WORKER_SYMBOL = "_Sound_StopPreloadWorkers_0043cc40@4"
MAINTAINED_SYMBOL = "?Stop@SoundWorkerPair_0043cc40@@QAEHXZ"


@dataclass(frozen=True)
class Case(QueueCase):
    operation: str = "setup"
    sources: tuple = tuple(i % 37 for i in range(47))
    base_volumes: tuple = (-1000,)
    duplicate_results: tuple = (0,)
    duplicate_writes: tuple = (True,)
    duplicate_outputs: tuple = ()
    old_outputs: tuple = (BUFFER,)
    music_setting: int = 70
    effect_setting: int = 100
    first_worker: int = 0x11112222
    second_worker: int = 0x33334444
    stop_requested: int = 0
    preload_wait_results: tuple = (0, 0)
    stop_stub_result: int = 0
    bounded_wait: bool = False


def compile_candidates(directory):
    queue = compile_queue(directory)
    obj = directory / "preload-stop.obj"
    subprocess.run([*COMMON, "-c", str(ROOT / "matching2/reference/semantic_candidates/sound_preload_stop.cpp"),
                    "-o", str(obj)], check=True, timeout=60)
    imports = {"_g_sound_wait_for_object": 0x46611C, "_g_sound_sleep": 0x4660AC, "_g_sound_close_handle": 0x4660CC}
    worker = load_module(obj, CANDIDATE + 0x3C000, imports)
    obj = directory / "maintained-preload-stop.obj"
    subprocess.run([*COMMON, "-c", str(ROOT / "matching2/msvc/src/platform/sound_worker.cpp"),
                    "-o", str(obj)], check=True, timeout=60)
    maintained = load_module(obj, CANDIDATE + 0x3E000, {
        "__imp__WaitForSingleObject@8": 0x46611C, "__imp__Sleep@4": 0x4660AC, "__imp__CloseHandle@4": 0x4660CC})
    obj = directory / "effect-buffers.obj"
    subprocess.run([*COMMON, "-mlong-double-80", "-c",
                    str(ROOT / "matching2/reference/semantic_candidates/sound_effect_buffers.cpp"), "-o", str(obj)],
                   check=True, timeout=60)
    bindings = {"_g_wave_sound_manager": GLOBAL, "_g_sound_effect_settings": 0x4749C8,
                "_g_music_volume_setting": 0x491D68, "_g_effect_volume_setting": 0x491D69,
                "_g_sound_volume_scale": 0x470B00, "_g_sound_volume_one": 0x470AFC,
                "_g_sound_volume_range": 0x470B80, "__ftol2": 0x463B2C}
    unit = load_module(obj, CANDIDATE + 0x3A000, dict(bindings, **{WORKER_SYMBOL: STOP_WORKERS}))
    full = load_module(obj, CANDIDATE + 0x3B000, dict(bindings, **{WORKER_SYMBOL: worker.symbols[WORKER_SYMBOL]}))
    return queue, unit, full, worker, maintained


class Execution(QueueExecution):
    def __init__(self, image, compiled=None, maintained=False):
        super().__init__(image, compiled[0] if compiled else None)
        self.uc.mem_map(CANDIDATE + 0x30000, 0x10000)
        self.setup = compiled[1:3] if compiled else ()
        self.worker = compiled[4 if maintained else 3] if compiled else None
        self.maintained = maintained
        self.worker_entries = {0x43CC40, STOP_WORKERS}
        self.maintained_entry = None
        if compiled:
            for module in compiled[1:]:
                self.uc.mem_write(module.base, module.data)
            self.worker_entries.add(compiled[3].symbols[WORKER_SYMBOL])
            self.maintained_entry = compiled[4].symbols[MAINTAINED_SYMBOL]
            self.worker_entries.add(self.maintained_entry)
        self.duplicate_calls = self.preload_wait_calls = 0

    def initialize(self, case):
        super().initialize(case)
        self.active_manager = case.manager or MANAGER
        # The mapped retail global manager is distinct from the local test
        # receiver; copy the initial layout, then give their workers different IDs.
        self.uc.mem_write(GLOBAL, bytes(self.uc.mem_read(MANAGER, 0x52D0)))
        self.words(MANAGER + 0x5218, 0xAAAA1111, 0xBBBB2222, 0, 0xCC)
        self.words(GLOBAL + 0x5218, case.first_worker, case.second_worker, 0, case.stop_requested)
        if case.operation == "worker" and case.manager:
            self.words(case.manager + 0x5218, case.first_worker, case.second_worker, 0, case.stop_requested)
        self.uc.mem_write(0x491D68, bytes([case.music_setting & 255, case.effect_setting & 255]))
        self.words(0x46611C, PWAIT)
        self.words(0x4660AC, PSLEEP)
        self.words(0x4660CC, PCLOSE)
        self.words(DEVICE_TABLE + 20, DUPLICATE)
        for index in range(128):
            pointer = SOURCE_BUFFERS + index * 16
            self.words(pointer, TABLE)
            for manager in (MANAGER, GLOBAL):
                self.words(manager + 8 + index * 4, pointer)
        for index in range(47):
            self.words(DUPLICATE_BUFFERS + index * 16, TABLE)
            self.words(0x4749C8 + index * 8, self.selected(case.sources, index))
            self.uc.mem_write(0x4749CC + index * 8, struct.pack("<h", self.selected(case.base_volumes, index)))
            for manager in (MANAGER, GLOBAL):
                self.words(manager + 0x208 + index * 4, self.selected(case.old_outputs, index))

    def cursor_state(self):
        return (super().cursor_state(), self.read_words(GLOBAL + 0x5218, 4),
                self.read_words(self.active_manager + 0x52C4, 3))

    def hook(self, machine, address, size, context):
        case = self.case
        if address in self.worker_entries:
            retail = address == 0x43CC40
            manager = (self.uc.reg_read(UC_X86_REG_ESI) if retail else self.uc.reg_read(UC_X86_REG_ECX)
                       if address == self.maintained_entry else self.args(1)[0])
            self.event("stop-preload", manager)
            if case.operation == "setup" and not case.integrated:
                self.finish(case.stop_stub_result, 0 if retail else 4)
        elif address == DUPLICATE:
            device, source, out = self.args(3)
            self.event("duplicate", device, source, out, self.read_words(out)[0])
            index = self.duplicate_calls
            self.duplicate_calls += 1
            if self.selected(case.duplicate_writes, index):
                pointer = case.duplicate_outputs[index] if index < len(case.duplicate_outputs) else DUPLICATE_BUFFERS + index * 16
                self.words(out, pointer)
            self.finish(self.selected(case.duplicate_results, index), 12)
        elif address in (PWAIT, OTHER_WAIT):
            handle, delay = self.args(2)
            result = self.selected(case.preload_wait_results, self.preload_wait_calls)
            self.preload_wait_calls += 1
            self.event("preload-wait" if address == PWAIT else "other-wait", handle, delay, result)
            assert delay == 100
            if case.bounded_wait and self.preload_wait_calls == 8:
                self.faults.append(("bounded-wait-prefix", 8))
                self.uc.emu_stop()
            else:
                assert self.preload_wait_calls < 20
                self.finish(result, 8)
        elif address in (PSLEEP, OTHER_SLEEP):
            delay, = self.args(1)
            self.event("preload-sleep" if address == PSLEEP else "other-sleep", delay)
            assert delay == 1
            self.finish(0, 4)
        elif address in (PCLOSE, OTHER_CLOSE):
            handle, = self.args(1)
            self.event("preload-close" if address == PCLOSE else "other-close", handle)
            self.finish(0, 4)
        else:
            super().hook(machine, address, size, context)

    def execute(self, case):
        self.prepare(case)
        for address in (*self.worker_entries, DUPLICATE, PWAIT, OTHER_WAIT, PSLEEP, OTHER_SLEEP, PCLOSE, OTHER_CLOSE):
            self.uc.hook_add(UC_HOOK_CODE, self.hook, begin=address, end=address)
        if case.operation == "worker":
            if self.worker:
                observed = (self.run(self.worker.symbols[MAINTAINED_SYMBOL], (), {UC_X86_REG_ECX: case.manager})
                            if self.maintained else self.run(self.worker.symbols[WORKER_SYMBOL], (case.manager,)))
            else:
                observed = self.run(0x43CC40, (), {UC_X86_REG_ESI: case.manager})
        elif self.setup:
            observed = self.run(self.setup[int(case.integrated)].symbols[SETUP_SYMBOL], (case.manager,))
        else:
            observed = self.run(0x43DB60, (), {UC_X86_REG_EBX: case.manager})
        returns = [observed["result"]]
        if case.consume and not self.faults:
            for operation, index, bits in case.requests:
                if self.producer:
                    args = (case.manager, index, bits) if operation == "play" else (case.manager, index)
                    observed = self.run(self.producer.symbols[PLAY_SYMBOL if operation == "play" else STOP_SYMBOL], args)
                else:
                    observed = self.run(0x43DD10 if operation == "play" else 0x43DDB0,
                        (bits,) if operation == "play" else (),
                        {UC_X86_REG_ESI: case.manager, UC_X86_REG_EBX if operation == "play" else UC_X86_REG_EDI: index})
                if self.faults:
                    break
            if not self.faults:
                entry = self.dispatchers[1].symbols[DISPATCH_SYMBOL] if self.dispatchers else 0x43DDF0
                observed = self.run(entry, (case.manager,), budget=1000000)
                returns.append(observed["result"])
        return {"returns": returns, "events": self.events, "faults": self.faults,
                "memory": tuple(bytes(self.uc.mem_read(address, 0x10000)) for address in (STATE, DATA, OUTPUT)),
                "manager": bytes(self.uc.mem_read(MANAGER, 0x10000)), "global": bytes(self.uc.mem_read(GLOBAL, 0x5400)),
                "settings": bytes(self.uc.mem_read(0x4749C8, 0x178)),
                "fpcw": self.uc.reg_read(UC_X86_REG_FPCW),
                "fpu_stack": None if self.faults else
                    (self.uc.reg_read(UC_X86_REG_FPTAG), (self.uc.reg_read(UC_X86_REG_FPSW) >> 11) & 7)}


def cases():
    for music, effect, control in product((0, 1, 30, 70, 99, 100, 127, 128, 255), (0, 1, 100, 128, 255), (0x37F, 0x27F, 0x7F)):
        yield Case(music_setting=music, effect_setting=effect, fpcw=control)
    for result, writes, old in product((0, 1, 0x80004005), (True, False), ((BUFFER,), (0,))):
        yield Case(duplicate_results=(result,), duplicate_writes=(writes,), old_outputs=old)
    for kwargs in ({"manager": 0}, {"owner": 0}, {"manager_device": 0}, {"device": 0}, {"duplicate_outputs": (0,)},
                   {"sources": (0x40000000,)}, {"sources": (0x7FFFFFFF,)}, {"sources": (0x80000000,)},
                   {"sources": (0x1000000,)}, {"sources": (128,)}, {"base_volumes": (-32768, 32767)},
                   {"effects": ((0, 7, (1, 2)), (1, -1, (3,)))}, {"stop_stub_result": 0x80004005}):
        yield Case(**kwargs)
    for trigger, writes in (
            ("stop-preload", ((MANAGER + 0x610, 0),)),
            ("stop-preload", ((MANAGER, 0),)),
            ("effect-position:1", ((MANAGER + 0x208, ALT_BUFFER), (0x4749CC, 0x00008000))),
            ("effect-volume:1", ((MANAGER + 8, 0), (0x4749D0, 0))),
            ("effect-volume:1", ((MANAGER, 0),)),
            ("duplicate:47", ((0x491D68, 0x00000180),)),
            ("effect-volume:47", ((0x491D68, 0x00000064),))):
        yield Case(mutations=((trigger, writes),))
    for first, second, requested, waits in product((0, 0x11112222), (0, 0x33334444), (0, 1, 2, 0xFFFFFFFF),
                                                  ((0, 0), (258, 0, 258, 0), (0xFFFFFFFF, 0x80))):
        yield Case(operation="worker", first_worker=first, second_worker=second, stop_requested=requested, preload_wait_results=waits)
    yield Case(operation="worker", manager=0)
    for trigger, writes in (
            ("preload-wait:1", ((0x46611C, OTHER_WAIT),)),
            ("preload-wait:1", ((0x4660AC, OTHER_SLEEP),)),
            ("preload-sleep:1", ((0x4660AC, OTHER_SLEEP), (0x46611C, OTHER_WAIT))),
            ("preload-wait:1", ((MANAGER + 0x5218, 0),)),
            ("preload-wait:2", ((MANAGER + 0x521C, 0),)),
            ("preload-close:1", ((0x4660CC, OTHER_CLOSE), (MANAGER + 0x521C, 0))),
            ("preload-close:2", ((MANAGER + 0x5218, 123), (MANAGER + 0x521C, 456)))):
        yield Case(operation="worker", preload_wait_results=(258, 0, 258, 0), mutations=((trigger, writes),))
    yield Case(operation="worker", preload_wait_results=(258,), bounded_wait=True)
    yield Case(operation="worker", preload_wait_results=(0, 258), bounded_wait=True)
    yield Case(operation="worker", preload_wait_results=(258, 0, 0),
               mutations=(("preload-wait:1", ((MANAGER + 0x5224, 0),)),))
    for manager, first, waits in product((MANAGER, GLOBAL), (0, 0x11112222), ((0, 0), (258, 0, 258, 0))):
        yield Case(integrated=True, manager=manager, first_worker=first, preload_wait_results=waits)
    for kwargs in ({"owner": 0}, {"manager_device": 0}, {"duplicate_outputs": (0,)},
                   {"duplicate_writes": (False,), "old_outputs": (0,)}, {"effect_setting": 0},
                   {"stop_requested": 2}, {"preload_wait_results": (0xFFFFFFFF, 0x80)}):
        yield Case(integrated=True, **kwargs)
    for manager, enabled, music, effect in product((MANAGER, GLOBAL), (0, 1), (0, 70), (0, 100, 255)):
        yield Case(integrated=True, consume=True, manager=manager, effects_enabled=enabled,
                   music_setting=music, effect_setting=effect, requests=(
                       ("play", 0, float_bits(192)), ("play", 0, float_bits(96)),
                       ("play", 1, float_bits(-192)), ("stop", 2, 0)))


def independent_checks(image, compiled):
    case = Case(integrated=True, effects=((0, 7, (1, 2)), (1, -1, (3,))))
    observed = Execution(image, compiled).execute(case)
    assert observed["returns"] == [0]
    assert struct.unpack_from("<12I", observed["manager"], 0x620) == (0xFFFFFFFF,) * 12
    assert struct.unpack_from("<ii", observed["manager"], 0x650) == (7, -1)
    assert struct.unpack_from("<ii", observed["manager"], 0x680) == (1, 2)
    assert struct.unpack_from("<IIII", observed["manager"], 0x5218) == (0xAAAA1111, 0xBBBB2222, 0, 0xCC)
    assert struct.unpack_from("<IIII", observed["global"], 0x5218) == (0, 0, 0, 1)
    assert struct.unpack_from("<iii", observed["manager"], 0x52C4) == (70, 100, -41)
    duplicates = [event for event in observed["events"] if event[0] == "duplicate"]
    assert len(duplicates) == 47
    assert duplicates[0][1:4] == (DEVICE, SOURCE_BUFFERS, MANAGER + 0x208)
    assert duplicates[-1][2:4] == (SOURCE_BUFFERS + (46 % 37) * 16, MANAGER + 0x208 + 46 * 4)
    assert struct.unpack_from("<47I", observed["manager"], 0x208) == tuple(DUPLICATE_BUFFERS + i * 16 for i in range(47))
    for music, effect, result in ((0, 1, -5000), (70, 0, -10000), (100, 1, 0), (99, 1, -1)):
        value = Execution(image, compiled).execute(Case(music_setting=music, effect_setting=effect))
        assert struct.unpack_from("<i", value["manager"], 0x52CC)[0] == result
    absent = Execution(image, compiled).execute(Case(operation="worker", first_worker=0))
    assert [event[0] for event in absent["events"]] == ["stop-preload"]
    assert struct.unpack_from("<IIII", absent["manager"], 0x5218) == (0, 0x33334444, 0, 0)
    chained = Execution(image, compiled).execute(Case(sources=(128,)))
    duplicates = [event for event in chained["events"] if event[0] == "duplicate"]
    assert duplicates[0][2] == BUFFER and all(event[2] == DUPLICATE_BUFFERS for event in duplicates[1:])
    pipeline = Execution(image, compiled).execute(Case(integrated=True, consume=True, effects_enabled=1, requests=(
        ("play", 0, float_bits(192)), ("play", 0, float_bits(96)), ("play", 1, float_bits(-192)))))
    pans = [event[1:3] for event in pipeline["events"] if event[0] == "pan"]
    assert pans == [(DUPLICATE_BUFFERS, 750), (DUPLICATE_BUFFERS + 16, (-1000) & 0xFFFFFFFF)]
    assert pipeline["fpu_stack"] == (0xFFFF, 0)


def maintained_import_diagnostic(image, compiled):
    case = Case(operation="worker", preload_wait_results=(258, 0, 258, 0),
                mutations=(("preload-wait:1", ((0x46611C, OTHER_WAIT),)),))
    expected = Execution(image).execute(case)
    observed = Execution(image, compiled, maintained=True).execute(case)
    assert expected != observed
    assert [event[0] for event in expected["events"]].count("other-wait") == 0
    assert [event[0] for event in observed["events"]].count("other-wait") == 3
    normalized = dict(observed)
    normalized["events"] = [("preload-wait", *event[1:]) if event[0] == "other-wait" else event for event in observed["events"]]
    assert normalized == expected


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--oracle", type=Path, default=ROOT / "matching2/build/oracle/th10.exe")
    options = parser.parse_args()
    config = load_manifest(ROOT / "matching2/msvc/regions.json")
    load_oracle(options.oracle, config)
    image = PEImage(options.oracle.read_bytes())
    with tempfile.TemporaryDirectory(prefix="th10-effect-buffers-") as temporary:
        compiled = compile_candidates(Path(temporary))
        totals, faults, bounded = {}, {}, 0
        for number, case in enumerate(cases()):
            expected, actual = Execution(image).execute(case), Execution(image, compiled).execute(case)
            assert actual == expected, (number, case, difference(expected, actual))
            name = "worker" if case.operation == "worker" else "pipeline" if case.consume else "integrated" if case.integrated else "unit"
            totals[name] = totals.get(name, 0) + 1
            faults[name] = faults.get(name, 0) + any(fault[0] != "bounded-wait-prefix" for fault in expected["faults"])
            bounded += any(fault[0] == "bounded-wait-prefix" for fault in expected["faults"])
        independent_checks(image, compiled)
        maintained_import_diagnostic(image, compiled)
        print(f"PASS: effect setup/shutdown comparisons {totals}, faults {faults}; "
              f"{bounded} bounded timeout prefixes; independent global-target/duplication/curve/pipeline checks. "
              f"{len(compiled[1].data)} setup and {len(compiled[3].data)} worker Clang bytes. "
              "Maintained Clang Wait import-reload gap reproduced separately. "
              "Native MSVC bytes and live DirectSound remain unverified.")


if __name__ == "__main__":
    main()
