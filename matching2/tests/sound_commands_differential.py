#!/usr/bin/env python3
"""Compare complete music-command dispatch and batched sound effects with retail.

Unit calls are scripted. Integration executes cached launch/memory creation,
restart, recreation, refill/cursors and maintained name/record/aggregate code.
All dispatcher arithmetic, queue compaction and effect COM sequencing execute.
"""
import argparse
from dataclasses import dataclass
from itertools import product
from pathlib import Path
import struct
import subprocess
import tempfile

from unicorn import UC_HOOK_CODE, UC_HOOK_INTR
from unicorn.x86_const import (
    UC_X86_REG_EAX, UC_X86_REG_ECX, UC_X86_REG_ESI, UC_X86_REG_EDI, UC_X86_REG_FPCW,
    UC_X86_REG_FPTAG, UC_X86_REG_FPSW)
from sound_stream_launch_cached_differential import (
    Case as LaunchCase, Execution as LaunchExecution, compile_candidates as compile_launch,
    ROOT, COMMON, CANDIDATE, STOP, STATE, MANAGER, STREAM, SOURCE, RECORD, ALT_RECORD, OWNER,
    ALT_OWNER, CURSOR, ALT_CURSOR, MUSIC_RECORDS, FIND_SYMBOL, RECORD_SYMBOL,
    PEImage, load_manifest, load_oracle, difference)
from sound_stream_initialize_differential import (
    BUFFER, ALT_BUFFER, THIRD, ARRAY, ALT_ARRAY, TABLE, ALT_TABLE, HEAP, SYMBOLS,
    ALLOCATE, FREE, RELEASE, CREATE, QUERY, SET_NOTICES, RELEASE_NOTIFY, POSITION)
from sound_stream_fill_differential import FILL_SYMBOL
from sound_stream_launch_differential import CREATE_EVENT, CREATE_THREAD, POST, WAIT, DESTROY, AGG_STOP, STOP_SYMBOL, AGG_SYMBOL
from coff_module import load_module
from coff_module import Module
from lzss_compressor_differential import DEFAULT_TOOLKIT, load_candidate
from x86_seh import exception_list, INITIAL_EXCEPTION_LIST

QUEUE, COMMAND_BYTES = MANAGER + 0x1F88, 0x10C
DISPATCH_SYMBOL = "_Sound_ProcessCommands_0043ddf0@4"
COMMAND_BASE = CANDIDATE + 0x20000
EFFECT_STOP, EFFECT_POSITION, PAN, VOLUME, EFFECT_PLAY, OTHER_VOLUME, CLOSE, OTHER_CLOSE = (
    STOP + i for i in (0x4000, 0x4100, 0x4200, 0x4300, 0x4400, 0x4500, 0x4600, 0x4700))
HELPERS = {
    "cache": (0x43D7D0, "_Sound_CacheMusic_0043d7d0@12"),
    "stop-music": (0x43DAB0, STOP_SYMBOL),
    "launch-cached": (0x43D950, "_SoundStream_LaunchCached_0043d950@8"),
    "restart": (0x44DAD0, SYMBOLS["restart"]),
    "recreate": (0x44CF20, SYMBOLS["recreate"]),
    "fill": (0x44D110, FILL_SYMBOL),
    "aggregate": (0x44D550, "?StopAndRewind@SoundStream@@QAEHXZ"),
    "start": (0x44D440, "_SoundStream_Start_0044d440@12"),
    "stop-first": (0x44D5B0, "@SoundStream_StopFirst_0044d5b0@4"),
    "resume": (0x44D5D0, "?ResumeConfigured@SoundStream@@QAEHXZ"),
    "volume-helper": (0x44D4E0, "?SetVolume@SoundStream@@QAEHH@Z"),
    "find": (0x43D2A0, FIND_SYMBOL),
    "record": (0x44DCA0, "?SelectRecord@MusicReadCursor@@QAEHPAUMusicTrackRecord@@@Z")}
STUBS = {name: STOP + 0x5000 + index * 0x100 for index, name in enumerate(HELPERS)}


@dataclass(frozen=True)
class Case(LaunchCase):
    commands: tuple = ((0, 0, 0, b""),)
    calls: int = 1
    effects_enabled: int = 0
    effects: tuple = ()  # (index, signed count, pan samples)
    effect_volume: int = 70
    effect_base: int = -1000
    effect_buffers: tuple = (BUFFER, ALT_BUFFER, THIRD)
    fade_stream: int = STREAM
    servicing: int = 0
    results: tuple = ()
    fpcw: int = 0x37F
    manager_volume: int = 0x12345678
    music_volume: int = 70
    random: int = 1


def command(kind, argument=1, step=0, name=b"track1.wav"):
    return kind, argument, step, name


import sys as _project_sys
from pathlib import Path as _ProjectPath
_project_sys.path.insert(0, str(_ProjectPath(__file__).resolve().parents[2]))
from matching2.tools.common.project_paths import project_support
def compile_candidates(directory):
    launch = compile_launch(directory)
    obj = directory / "command-aggregate.obj"
    subprocess.run([*COMMON, "-c", str(ROOT / "matching2/msvc/src/game/platform_aggregate_interfaces_0044d550.cpp"),
                    "-o", str(obj)], check=True, timeout=60)
    aggregate = load_module(obj, COMMAND_BASE + 0x4000, {})
    support = [aggregate]
    bindings = {"_g_sound_mode_flags": 0x491D78, "_g_music_enabled": 0x491D63,
                "_g_sound_effects_enabled": 0x491D64, "_g_sound_fade_stream": 0x497798,
                "_g_sound_effects_volume": 0x497858, "_g_sound_effect_settings": 0x4749C8,
                "_g_sound_fade_scale": 0x470B1C, "_g_sound_volume_scale": 0x470B00,
                "_g_sound_volume_one": 0x470AFC, "_g_sound_post_thread_message": 0x466210,
                "_g_sound_wait_for_object": 0x46611C, "_g_sound_close_handle": 0x4660CC,
                "__ftol2": 0x463B2C}
    bindings.update((symbol, STUBS[name]) for name, (_, symbol) in HELPERS.items())
    obj = directory / "commands.obj"
    subprocess.run([*COMMON, "-fno-delete-null-pointer-checks", "-mlong-double-80", "-c",
                    str(ROOT / "matching2/reference/semantic_candidates/sound_commands.cpp"), "-o", str(obj)],
                   check=True, timeout=60)
    unit = load_module(obj, COMMAND_BASE, bindings)
    entries = {"launch-cached": launch[2].symbols[HELPERS["launch-cached"][1]],
               "restart": launch[0][0][1]["restart"].symbols[SYMBOLS["restart"]],
               "recreate": launch[0][0][1]["recreate"].symbols[SYMBOLS["recreate"]],
               "fill": launch[0][0][0][1].symbols[FILL_SYMBOL],
               "find": launch[5].symbols[FIND_SYMBOL], "record": launch[3].symbols[RECORD_SYMBOL],
               "aggregate": aggregate.symbols[AGG_SYMBOL]}
    helper_bindings = {FILL_SYMBOL: entries["fill"],
                       "?RestoreIfLost@WaveSecondaryBuffer@@QAEHPAI@Z":
                           launch[0][0][1]["restore"].symbols["?Run@PlatformD300Entry@@QAEHPAI@Z"],
                       "_asm_rand_0045371b": 0x45371B, "_data_00497854": 0x497854, "__ftol2": 0x463B2C,
                       "_g_sound_post_thread_message": 0x466210, "_g_sound_wait_for_object": 0x46611C,
                       "_g_sound_close_handle": 0x4660CC,
                       "@Sound_AggregateInterfaces_0044d550@4": entries["aggregate"]}
    for name, source, exported, imported, offset in (
            ("stop-music", "reference/semantic_candidates/sound_midi_stop.cpp", STOP_SYMBOL, STOP_SYMBOL, 0x5000),
            ("find-buffer", "reference/semantic_candidates/sound_stream_select.cpp",
             "?FindAvailable@SoundStream@@QAEPAUWaveSecondaryBuffer@@XZ", "?FindAvailable@SoundStream@@QAEPAUWaveSecondaryBuffer@@XZ", 0x7000),
            ("rewind-buffers", "msvc/src/game/platform_query_interfaces_0044d600.cpp",
             "?Query@PlatformQueryInterfaces_0044D600@@QAEHXZ", "?RewindBuffers@SoundStream@@QAEHXZ", 0x8000),
            ("volume-helper", "msvc/src/game/platform_set_operation_deadline_0044d4e0.cpp",
             "?SetOperationDeadline@PlatformInterfaceState_0044D4E0@@QAEHH@Z", HELPERS["volume-helper"][1], 0x9000),
            ("resume", "msvc/src/game/platform_invoke_configured_0044d5d0.cpp",
             "?InvokeConfigured@PlatformInterfaceState_0044D5D0@@QAEHXZ", HELPERS["resume"][1], 0xA000),
            ("start", "reference/semantic_candidates/sound_stream_start.cpp",
             HELPERS["start"][1], HELPERS["start"][1], 0x6000)):
        obj = directory / ("command-" + name + ".obj")
        subprocess.run([*COMMON, "-c", str(ROOT / "matching2" / source), "-o", str(obj)], check=True, timeout=60)
        module = load_module(obj, COMMAND_BASE + offset, helper_bindings)
        support.append(module)
        helper_bindings[imported] = module.symbols[exported]
        if name in HELPERS:
            entries[name] = module.symbols[exported]
    obj = directory / "command-stop-first.obj"
    subprocess.run([*COMMON, "-ffunction-sections", "-I", str(ROOT / "matching2/msvc/include"),
                    "-isystem", str(DEFAULT_TOOLKIT / "include"), "-c",
                    str(ROOT / "matching2/msvc/src/platform/process.cpp"), "-o", str(obj)], check=True, timeout=60)
    first_symbol = "?Platform_InvokeInterface@@YIHPAUSoundBuffer@@@Z"
    first_address = COMMAND_BASE + 0xB000
    first_body = load_candidate(obj, load_manifest(project_support((ROOT) / 'matching2/msvc', 'regions.json')), first_symbol, code_address=first_address)
    support.append(Module(first_address, first_body, {first_symbol: first_address}, ()))
    entries["stop-first"] = first_address
    # Restore the dispatcher object: the helper loop reuses the obj variable.
    full = load_module(directory / "commands.obj", COMMAND_BASE + 0x2000,
                       dict(bindings, **{HELPERS[name][1]: address for name, address in entries.items()}))
    return launch, unit, full, support, entries


class Execution(LaunchExecution):
    def __init__(self, image, compiled=None):
        super().__init__(image, compiled[0] if compiled else None)
        self.uc.mem_map(COMMAND_BASE, 0x10000)
        self.dispatchers = compiled[1:3] if compiled else ()
        self.executing_helpers = set(HELPERS) - {"cache"}
        self.helpers = {address: name for name, (address, _) in HELPERS.items()}
        self.helpers.update((address, name) for name, address in STUBS.items())
        if compiled:
            for module in (*compiled[1:3], *compiled[3]):
                self.uc.mem_write(module.base, module.data)
            self.helpers.update((address, name) for name, address in compiled[4].items())

    def initialize(self, case):
        super().initialize(case)
        self.uc.reg_write(UC_X86_REG_FPCW, case.fpcw)
        self.uc.reg_write(UC_X86_REG_FPTAG, 0xFFFF)
        self.uc.mem_write(QUEUE, bytes(COMMAND_BYTES * 32))
        assert len(case.commands) <= 32
        for index, (kind, argument, step, name) in enumerate(case.commands):
            address = QUEUE + index * COMMAND_BYTES
            self.words(address, kind, argument, step)
            assert len(name) <= 255
            self.uc.mem_write(address + 12, name + b"\0")
        self.words(STREAM + 0x74, case.servicing)
        self.words(MANAGER + 0x52C4, case.manager_volume)
        self.words(0x497798, case.fade_stream)
        self.words(0x497858, case.effect_volume)
        self.words(0x497854, case.music_volume)
        self.words(0x4705D4, DESTROY)
        self.uc.mem_write(0x491D64, bytes([case.effects_enabled]))
        self.words(MANAGER + 0x620, *([0xFFFFFFFF] * 12))
        self.words(MANAGER + 0x650, *([0] * 12))
        self.uc.mem_write(MANAGER + 0x680, bytes(12 * 128 * 4))
        for pending, (index, count, pans) in enumerate(case.effects):
            assert pending < 12
            self.words(MANAGER + 0x620 + pending * 4, index)
            self.words(MANAGER + 0x650 + pending * 4, count)
            self.words(MANAGER + 0x680 + pending * 512, *pans)
        for index in range(47):
            self.words(MANAGER + 0x208 + index * 4, case.effect_buffers[index % len(case.effect_buffers)])
            self.uc.mem_write(0x4749CC + index * 8, struct.pack("<h", case.effect_base))
        for table in (TABLE, ALT_TABLE):
            for offset, address in ((72, EFFECT_STOP), (52, EFFECT_POSITION), (64, PAN),
                                     (60, VOLUME if table == TABLE else OTHER_VOLUME), (48, EFFECT_PLAY)):
                self.words(table + offset, address)
        self.words(0x4660CC, CLOSE)

    def cursor_state(self):
        return (super().cursor_state(), self.read_words(QUEUE, 3), self.read_words(MANAGER + 0x620, 24))

    def hook(self, machine, address, size, context):
        case = self.case
        if address in self.helpers:
            kind = self.helpers[address]
            retail = address == HELPERS[kind][0]
            if kind == "cache":
                values = ((self.uc.reg_read(UC_X86_REG_EAX), self.uc.reg_read(UC_X86_REG_ESI), *self.args(1))
                          if retail else self.args(3))
                cleanup = 4 if retail else 12
            elif kind == "launch-cached":
                values = ((self.uc.reg_read(UC_X86_REG_ESI), self.uc.reg_read(UC_X86_REG_EAX)) if retail else self.args(2))
                cleanup = 0 if retail else 8
            elif kind in ("stop-music", "recreate", "restart"):
                values = ((self.uc.reg_read(UC_X86_REG_EDI if kind == "restart" else UC_X86_REG_ESI),) if retail else self.args(1))
                cleanup = 0 if retail else 4
            elif kind in ("fill", "start"):
                values = ((self.uc.reg_read(UC_X86_REG_EAX), *self.args(2)) if retail else self.args(3))
                cleanup = 8 if retail else 12
            elif kind in ("aggregate", "resume", "stop-first", "volume-helper"):
                register = (UC_X86_REG_EDI if kind == "aggregate" else UC_X86_REG_ECX if kind == "stop-first" else UC_X86_REG_EAX) if retail else UC_X86_REG_ECX
                values = (self.uc.reg_read(register), *(self.args(1) if kind == "volume-helper" else ()))
                cleanup = 4 if kind == "volume-helper" else 0
            elif kind == "find":
                values = (self.uc.reg_read(UC_X86_REG_ECX), *self.args(1))
                cleanup = 4
            else:
                values = ((self.uc.reg_read(UC_X86_REG_ESI), self.uc.reg_read(UC_X86_REG_ECX)) if retail else
                          (self.uc.reg_read(UC_X86_REG_ECX), *self.args(1)))
                cleanup = 0 if retail else 4
            self.event(kind, *values)
            if not case.integrated or kind not in self.executing_helpers:
                result = dict(case.results).get(kind, 1 if kind == "find" else 0)
                self.finish(result, cleanup)
        elif address in (EFFECT_STOP, EFFECT_POSITION, PAN, VOLUME, OTHER_VOLUME, EFFECT_PLAY):
            kind, count = {EFFECT_STOP: ("effect-stop", 1), EFFECT_POSITION: ("effect-position", 2),
                           PAN: ("pan", 2), VOLUME: ("effect-volume", 2), OTHER_VOLUME: ("other-volume", 2),
                           EFFECT_PLAY: ("effect-play", 4)}[address]
            self.event(kind, *self.args(count))
            self.finish(case.position_result if address == EFFECT_POSITION else 0x80004005, count * 4)
        elif address == 0x45371B:
            self.event("random")
            self.finish(case.random)
        elif address in (CLOSE, OTHER_CLOSE):
            self.event("close" if address == CLOSE else "other-close", *self.args(1))
            self.finish(0, 4)
        else:
            super().hook(machine, address, size, context)

    def prepare(self, case):
        self.initialize(case)
        self.install_hooks()
        self.uc.hook_add(UC_HOOK_INTR, self.interrupt)
        for address in {ALLOCATE, FREE, RELEASE, CREATE, QUERY, SET_NOTICES, RELEASE_NOTIFY, POSITION,
                        *self.construct_entries, *self.factory_entries, *self.helpers,
                        CREATE_EVENT, CREATE_THREAD, POST, WAIT, DESTROY,
                        EFFECT_STOP, EFFECT_POSITION, PAN, VOLUME, OTHER_VOLUME, EFFECT_PLAY, CLOSE, OTHER_CLOSE, 0x45371B}:
            self.uc.hook_add(UC_HOOK_CODE, self.hook, begin=address, end=address)

    def execute(self, case):
        self.prepare(case)
        returns = []
        for frame in range(case.calls):
            entry = self.dispatchers[int(case.integrated)].symbols[DISPATCH_SYMBOL] if self.dispatchers else 0x43DDF0
            observed = self.run(entry, (case.manager,), budget=1000000)
            returns.append(observed["result"])
            if self.faults:
                break
            assert exception_list(self.uc) == INITIAL_EXCEPTION_LIST
            self.event("frame", frame, observed["result"])
        observed.update(allocated=self.allocated, freed=self.freed, returns=returns,
                        manager=bytes(self.uc.mem_read(MANAGER, 0x10000)),
                        fpcw=self.uc.reg_read(UC_X86_REG_FPCW),
                        fpu_stack=(self.uc.reg_read(UC_X86_REG_FPTAG), (self.uc.reg_read(UC_X86_REG_FPSW) >> 11) & 7))
        return observed


def cases():
    for kind, mode, step in product(range(10), (0, 0x10), (0, 1, 2, 3, 4, 5, 6, 7, 10, 19, 20, 0xFFFFFFFF, 0x80000000)):
        yield Case(commands=(command(kind, step=step),))
    for kind, stream, servicing, enabled in product((2, 3, 4, 6, 7, 8), (0, STREAM), (0, 1), (0, 1, 2)):
        yield Case(commands=(command(kind, step=1),), old_stream=stream, servicing=servicing, enabled=enabled)
    for mode, step, argument in product((0, 0x10), (0, 1, 2, 3, 5, 7), (-1, 0x80000000, 0x7FFFFFFF)):
        yield Case(commands=(command(2, argument=argument, step=step),))
    for name in ("cache", "stop-music", "launch-cached", "restart", "fill", "recreate", "aggregate", "start", "stop-first", "resume", "volume-helper", "record"):
        kind, mode, step = {"cache": (1, 0x10, 0), "stop-music": (1, 0x10, 0), "launch-cached": (2, 0x10, 0),
                           "restart": (2, 0x10, 2), "fill": (2, 0x10, 5), "recreate": (2, 0, 1),
                           "aggregate": (3, 0, 0), "start": (2, 0x10, 7), "stop-first": (6, 0, 0),
                           "resume": (7, 0, 0), "volume-helper": (8, 0, 0), "record": (2, 0, 2)}[name]
        for result in (1, 0x7FFFFFFF, 0x80004005, 0xFFFFFFFF):
            yield Case(commands=(command(kind, step=step),), mode=mode, results=((name, result),))
    for command_count in (1, 2, 3, 30, 31, 32):
        for kind in (1, 3, 5, 8):
            yield Case(commands=tuple(command(kind if i == 0 else 8, argument=i, step=1) for i in range(command_count)), mode=0)
    yield Case(commands=(command(5), command(0), command(8)), calls=2)
    for duration, pointer in product((0, 1, -1, 0x7FFFFFFF, 0x80000000, 71582789), (0, STREAM)):
        yield Case(commands=(command(5, argument=duration),), fade_stream=pointer)
    for kwargs in ({"owner": 0}, {"manager": 0}, {"old_thread": 0}, {"old_event": 0},
                   {"initial_array": 0}, {"count": 0}, {"reader": 0}, {"record": 0}, {"end": 0}):
        yield Case(commands=(command(2, step=5),), **kwargs)
    for value in (0, 258, 0xFFFFFFFF):
        yield Case(commands=(command(4, step=2),), wait_results=(value,), calls=2)
    for trigger, writes, cmd, mode in (
            ("cache", ((QUEUE, 0),), command(1), 0),
            ("restart", ((STREAM + 4, ALT_ARRAY), (STREAM + 0xC, ALT_CURSOR)), command(2, step=3), 0),
            ("fill", ((QUEUE + 8, 99),), command(2, step=5), 0x10),
            ("find", ((MANAGER + 0x1F84, MUSIC_RECORDS + 52),), command(2, step=2), 0),
            ("wait", ((MANAGER + 0x618, 0x11223344),), command(4, step=2), 0),
            ("post", ((QUEUE + 8, 100),), command(4, step=2), 0),
            ("close", ((0x4660CC, OTHER_CLOSE), (MANAGER + 0x520C, 0)), command(4, step=3), 0),
            ("destroy", ((MANAGER + 0x5208, 0x12345678),), command(4, step=3), 0)):
        yield Case(commands=(cmd,), mode=mode, mutations=((trigger, writes),), wait_results=(258,))
    for volume, base, control in product((0, 1, 30, 70, 99, 100, 101, -1, -100, 200, 0x7FFFFFFF, 0x80000000),
                                        (-32768, -10000, -5000, -1000, 0, 32767), (0x37F, 0x27F, 0x7F)):
        yield Case(effects_enabled=1, effects=((0, 3, (-10000, 10000, -7)),), effect_volume=volume, effect_base=base, fpcw=control)
    for count, pans, buffers in product((-1, -128, 0, 1, 2, 3), ((7, 9, 13), (0x7FFFFFFF, 0x7FFFFFFF, 0x80000000)),
                                      ((0,), (BUFFER,))):
        yield Case(effects_enabled=1, effects=((0, count, pans),), effect_buffers=buffers)
    yield Case(effects_enabled=1, effects=tuple((i, 2, (i * 100, -33)) for i in range(12)))
    yield Case(effects_enabled=1, effects=((0, -1, ()), (-1, 1, (4,)), (2, 1, (9,))))
    for index in (46, 47, 127, 128, 255, 0x40000000, 0x7FFFFFFF, 0x80000000):
        yield Case(effects_enabled=1, effects=((index, 1, (12,)),))
    for count in (128, 129, 0x7FFFFFFF):
        yield Case(effects_enabled=1, effects=((0, count, tuple(range(129))),))
    for volume, control in product((-100, 1, 30, 70, 100, 200, 0x7FFFFFFF), (0x77F, 0xB7F, 0xF7F)):
        yield Case(effects_enabled=1, effects=((0, 1, (37,)),), effect_volume=volume, fpcw=control)
    for trigger, writes in (
            ("effect-stop", ((MANAGER + 0x208, ALT_BUFFER),)),
            ("effect-position", ((MANAGER + 0x208, THIRD),)),
            ("pan", ((MANAGER + 0x208, ALT_BUFFER), (ALT_BUFFER, ALT_TABLE), (0x497858, 0))),
            ("effect-volume", ((MANAGER + 0x208, THIRD),)),
            ("effect-stop", ((MANAGER + 0x650, 99),))):
        for count in (-1, 2):
            yield Case(effects_enabled=1, effects=((0, count, (4, 5)),), mutations=((trigger, writes),))
    for mode, step in product((0, 0x10), range(8)):
        yield Case(integrated=True, commands=(command(2, step=step),))
    yield Case(integrated=True, commands=(command(2), command(3), command(8)), calls=25)
    yield Case(integrated=True, commands=(command(2), command(4)), calls=30)
    yield Case(integrated=True, mode=0, buffered=0, commands=(command(2, argument=-1), command(3)), calls=10)
    yield Case(integrated=True, mode=0x10, buffered=0, commands=(command(2, argument=-1), command(4)), calls=26)
    for kwargs in ({"fail_allocate": 1}, {"fail_allocate": 2}, {"fail_allocate": 3}, {"fail_allocate": 4},
                   {"create_results": (0x80004005,)}, {"query_results": (0x80004005,)},
                   {"notice_results": (0x80004005,)}, {"end": 0}, {"status_result": 0x80004005},
                   {"locked_bytes": 0}, {"lock_result": 0x80070057}):
        yield Case(integrated=True, commands=(command(2),), calls=8, **kwargs)
    for kind, mode, step in product((1, 3, 4, 6, 7, 8), (0, 0x10), (0, 1, 2, 3)):
        yield Case(integrated=True, commands=(command(kind, step=step),), mode=mode)
    for trigger, writes in (("effect-stop", ((STREAM + 4, ALT_ARRAY),)),
                           ("effect-position", ((STREAM + 0x10, 1),)),
                           ("close", ((MANAGER + 0x520C, 0),)),
                           ("destroy", ((MANAGER + 0x5208, 0),))):
        yield Case(integrated=True, commands=(command(1), command(2)), mutations=((trigger, writes),), calls=4)


def independent_checks(image, compiled):
    observed = Execution(image, compiled).execute(Case(commands=(command(1), command(8)), mode=0))
    assert observed["result"] == 8
    assert [event[0] for event in observed["events"]] == ["cache", "frame"]
    assert struct.unpack_from("<I", observed["manager"], 0x1F88)[0] == 8
    assert struct.unpack_from("<I", observed["manager"], 0x1F88 + COMMAND_BYTES)[0] == 0
    full = Execution(image, compiled).execute(Case(commands=(command(1),) + (command(8),) * 31, mode=0))
    assert [event[0] for event in full["events"]] == ["cache", "volume-helper", "frame"]
    shutdown = Execution(image, compiled).execute(Case(commands=(command(4, step=1),), calls=4))
    assert shutdown["returns"] == [4, 4, 4, 0]
    assert [event[1] for event in shutdown["events"] if event[0] == "close"] == [0, 0x55556666]
    effect = Execution(image, compiled).execute(Case(effects_enabled=1, effects=((0, 3, (-10000, 10000, -7)),)))
    assert [event[2] for event in effect["events"] if event[0] == "pan"] == [0xFFFFFFFE]
    assert [event[2] for event in effect["events"] if event[0] == "effect-volume"] == [(-1109) & 0xFFFFFFFF]
    assert effect["fpu_stack"] == (0xFFFF, 0)
    fade = Execution(image, compiled).execute(Case(commands=(command(5, argument=71582789),)))
    assert struct.unpack_from("<III", fade["memory"][0], STREAM + 0x14 - STATE) == (44, 44, 1)
    busy = Execution(image, compiled).execute(Case(commands=(command(6), command(8)), servicing=1))
    assert busy["result"] == 6 and struct.unpack_from("<I", busy["manager"], 0x1F90)[0] == 0
    empty = Execution(image, compiled).execute(Case(effects_enabled=1, effects=((0, 0, ()),), effect_buffers=(0,)))
    assert empty["faults"] == [("interrupt", 0)]
    lifecycle = Execution(image, compiled).execute(Case(integrated=True, commands=(command(2), command(4)), calls=30))
    kinds = [event[0] for event in lifecycle["events"]]
    assert all(kind in kinds for kind in ("launch-cached", "factory", "construct", "fill", "restart", "start", "effect-play", "destroy"))
    assert struct.unpack_from("<I", lifecycle["manager"], 0x5208)[0] == 0


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--oracle", type=Path, default=ROOT / "matching2/build/oracle/th10.exe")
    options = parser.parse_args()
    config = load_manifest(project_support((ROOT) / 'matching2/msvc', 'regions.json'))
    load_oracle(options.oracle, config)
    image = PEImage(options.oracle.read_bytes())
    with tempfile.TemporaryDirectory(prefix="th10-sound-commands-") as temporary:
        compiled = compile_candidates(Path(temporary))
        totals, faults = [0, 0], [0, 0]
        for number, case in enumerate(cases()):
            expected, actual = Execution(image).execute(case), Execution(image, compiled).execute(case)
            assert actual == expected, (number, case, difference(expected, actual))
            index = int(case.integrated)
            totals[index] += 1
            faults[index] += bool(expected["faults"])
        independent_checks(image, compiled)
        print(f"PASS: {totals[0]} command/effect unit comparisons ({faults[0]} faults), "
              f"{totals[1]} integrated comparisons ({faults[1]} faults), independent queue/pan/volume/fade/shutdown/lifecycle checks; "
              f"{len(compiled[1].data)} Clang module bytes. Native MSVC bytes and live audio remain unverified.")


if __name__ == "__main__":
    main()
