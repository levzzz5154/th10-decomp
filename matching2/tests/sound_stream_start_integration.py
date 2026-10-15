#!/usr/bin/env python3
"""Execute music startup through selection, restoration, PCM refill and Play.

The candidate path runs nine C++ bodies, including maintained restoration,
buffer rewind and volume helpers. Only external Win32/DirectSound/rand calls
are scripted. This is an instruction comparison, not live audio validation.
"""
import argparse
from dataclasses import dataclass
from itertools import product
from pathlib import Path
import subprocess
import tempfile

from unicorn import UC_HOOK_CODE
from unicorn.x86_const import UC_X86_REG_EAX, UC_X86_REG_EBX, UC_X86_REG_ECX, UC_X86_REG_ESI, UC_X86_REG_EDI
from sound_stream_fill_differential import (
    Case as FillCase, Execution as FillExecution, compile_candidates as compile_fill,
    FILL_SYMBOL, STREAM, BUFFER, TABLE, ALT_TABLE, ALT_CURSOR, STATUS,
    ROOT, CANDIDATE, STOP, STATE, OUTPUT, CURSOR, RECORD, ALT_RECORD, SOURCE, DESTINATION,
    COMMON, difference, PEImage, load_manifest, load_oracle)
from coff_module import load_module

MANAGER, ARRAY, ALT_ARRAY, ALT_BUFFER, THIRD = (STATE + offset for offset in (0x2000, 0x1800, 0x1900, 0x1400, 0x1500))
PLAY, POSITION, SET_VOLUME, OTHER_PLAY = (STOP + 0x100 * i for i in range(12, 16))
START_SYMBOL = "_SoundStream_Start_0044d440@12"
COMMAND_SYMBOL = "_Sound_StartMusicCommand_0043da80@8"
HELPERS = (
    ("find", "reference/semantic_candidates/sound_stream_select.cpp", "?FindAvailable@SoundStream@@QAEPAUWaveSecondaryBuffer@@XZ", "?FindAvailable@SoundStream@@QAEPAUWaveSecondaryBuffer@@XZ", CANDIDATE + 0x3000),
    ("restore-helper", "msvc/src/game/platform_run_interface_0044d300.cpp", "?Run@PlatformD300Entry@@QAEHPAI@Z", "?RestoreIfLost@WaveSecondaryBuffer@@QAEHPAI@Z", CANDIDATE + 0x5000),
    ("rewind-buffers", "msvc/src/game/platform_query_interfaces_0044d600.cpp", "?Query@PlatformQueryInterfaces_0044D600@@QAEHXZ", "?RewindBuffers@SoundStream@@QAEHXZ", CANDIDATE + 0x6000),
    ("volume", "msvc/src/game/platform_set_operation_deadline_0044d4e0.cpp", "?SetOperationDeadline@PlatformInterfaceState_0044D4E0@@QAEHH@Z", "?SetVolume@SoundStream@@QAEHH@Z", CANDIDATE + 0x7000))


@dataclass(frozen=True)
class Case(FillCase):
    integrated: bool = True
    operation: str = "start"
    status: int = 2
    fill_status: int = 0
    fill_status_result: int = 0
    array: bool = True
    entries: tuple = (BUFFER, ALT_BUFFER)
    states: tuple = (0, 1, 1)
    priority: int = 0
    flags: int = 1
    command: int = 0x12345678
    play_result: int = 0
    volume: int = 70
    random: int = 1


def compile_candidates(directory):
    fill = compile_fill(directory)
    modules, entries = {}, {}
    bindings = {"__imp__Sleep@4": 0x4660AC, "_asm_rand_0045371b": 0x45371B,
                "_data_00497854": 0x497854, "__ftol2": 0x463B2C,
                FILL_SYMBOL: fill[1].symbols[FILL_SYMBOL]}
    for name, source, symbol, binding, address in HELPERS:
        obj = directory / (name + ".obj")
        subprocess.run([*COMMON, "-fno-delete-null-pointer-checks", "-c", str(ROOT / "matching2" / source),
                        "-o", str(obj)], check=True, timeout=60)
        module = load_module(obj, address, bindings)
        modules[name] = module
        entries[name] = module.symbols[symbol]
        bindings[binding] = entries[name]
    for name, source, symbol, address in (
            ("start", "sound_stream_start.cpp", START_SYMBOL, CANDIDATE + 0x1000),
            ("command", "unassigned_0043da80.cpp", COMMAND_SYMBOL, CANDIDATE + 0x2000)):
        obj = directory / (name + ".obj")
        subprocess.run([*COMMON, "-c", str(ROOT / "matching2/reference/semantic_candidates" / source),
                        "-o", str(obj)], check=True, timeout=60)
        module = load_module(obj, address, bindings)
        modules[name] = module
        entries[name] = module.symbols[symbol]
        bindings[symbol] = entries[name]
    spans = sorted((module.base, module.base + len(module.data)) for module in (*fill, *modules.values()))
    assert all(end <= following for (_, end), (following, _) in zip(spans, spans[1:]))
    return fill, modules, entries


class Execution(FillExecution):
    def __init__(self, image, compiled=None):
        fill, modules, entries = compiled if compiled else (None, {}, {})
        super().__init__(image, fill, {module.base: module.data for module in modules.values()})
        self.entries = entries
        self.helper_entries = {0x44D370: "find", 0x44D300: "restore-helper", 0x44D600: "rewind-buffers", 0x44D4E0: "volume"}
        self.helper_entries.update((entries[name], name) for name, *_ in HELPERS if name in entries)
        self.fill_entries = {0x44D110}
        if fill:
            self.fill_entries.add(fill[1].symbols[FILL_SYMBOL])
        self.stage = None

    def initialize(self, case):
        super().initialize(case)
        self.words(STREAM + 4, ARRAY if case.array else 0)
        self.words(STREAM + 0x10, len(case.entries))
        self.words(ARRAY, *case.entries)
        self.words(ALT_ARRAY, ALT_BUFFER, BUFFER, THIRD)
        self.words(MANAGER + 0x5208, case.stream)
        self.words(MANAGER + 0x5210, 0xABCDEF01)
        for buffer in (ALT_BUFFER, THIRD):
            self.words(buffer, TABLE)
        for table in (TABLE, ALT_TABLE):
            for offset, address in ((48, PLAY if table == TABLE else OTHER_PLAY), (52, POSITION), (60, SET_VOLUME)):
                self.words(table + offset, address)
        self.words(0x497854, case.volume)

    def hook(self, machine, address, size, context):
        case = self.case
        if address in self.helper_entries:
            kind = self.helper_entries[address]
            self.stage = kind
            retail = address < CANDIDATE
            receiver = self.uc.reg_read(UC_X86_REG_ESI if retail and kind == "restore-helper" else
                                        UC_X86_REG_EAX if retail and kind == "volume" else
                                        UC_X86_REG_EDI if retail else UC_X86_REG_ECX)
            self.event(kind, receiver, *self.args(1) if kind == "volume" else ())
        elif address in self.fill_entries:
            self.stage = "fill"
            if address == 0x44D110:
                stream = self.uc.reg_read(UC_X86_REG_EAX)
                buffer, repeat = self.args(2)
            else:
                stream, buffer, repeat = self.args(3)
            self.event("fill", stream, buffer, repeat)
            assert repeat == 0
        elif address == STATUS:
            buffer, out = self.args(2)
            if self.stage == "find":
                status = case.states[(BUFFER, ALT_BUFFER, THIRD).index(buffer)]
                result = 0x80004005  # selector ignores HRESULT
            else:
                status = case.status if self.stage == "restore-helper" else case.fill_status
                result = case.status_result if self.stage == "restore-helper" else case.fill_status_result
            self.event("status", buffer, status, self.stage)
            self.words(out, status)
            self.finish(result, 8)
        elif address == POSITION:
            buffer, position = self.args(2)
            self.event("position", buffer, position)
            assert position == 0
            self.finish(0x80004005, 8)
        elif address == SET_VOLUME:
            buffer, volume = self.args(2)
            self.event("set-volume", buffer, volume)
            self.finish(0x80004005, 8)
        elif address in (PLAY, OTHER_PLAY):
            values = self.args(4)
            self.event("play" if address == PLAY else "other-play", *values)
            assert values[1] == 0
            self.finish(case.play_result, 16)
        elif address == 0x45371B:
            self.event("rand", case.random)
            self.finish(case.random)
        else:
            super().hook(machine, address, size, context)

    def execute(self, case):
        self.initialize(case)
        self.install_hooks()
        for address in (*self.helper_entries, *self.fill_entries, POSITION, SET_VOLUME, PLAY, OTHER_PLAY, 0x45371B):
            self.uc.hook_add(UC_HOOK_CODE, self.hook, begin=address, end=address)
        if case.operation == "command":
            if self.entries:
                return self.run(self.entries["command"], (MANAGER, case.command))
            return self.run(0x43DA80, (case.command,), {UC_X86_REG_ESI: MANAGER})
        if self.entries:
            return self.run(self.entries["start"], (case.stream, case.priority, case.flags))
        return self.run(0x44D440, (case.priority, case.flags), {UC_X86_REG_EAX: case.stream})


def cases():
    for operation, buffered, bits, end in product(("start", "command"), (0, 1), (8, 16), (0, 1, 7, 29)):
        yield Case(operation=operation, buffered=buffered, bits=bits, end=end)
    for operation, status, play_result in product(("start", "command"), (0, 2), (0, 1, 0x80004005)):
        yield Case(operation=operation, status=status, play_result=play_result, flags=0x80000001, priority=99)
    for kwargs in ({"stream": 0, "operation": "command"}, {"array": False}, {"status_result": 0x80004005},
                   {"fill_status_result": 0x80070057}, {"lock_result": 0x80004005},
                   {"buffered": 0, "file": 0}, {"begin": 0}, {"record": 0},
                   {"entries": (0, ALT_BUFFER)}, {"destination": OUTPUT + 0xFFFE},
                   {"fill_status": 2, "restore_results": (0x88780096, 0, 0x88780096, 1, 0, 0)}):
        yield Case(**kwargs)
    for counts in ((0,), (3,), (100,), (None,)):
        yield Case(buffered=0, file_counts=counts, api_result=0)
    for trigger, writes in (
            ("lock", ((STREAM + 0xC, ALT_CURSOR),)),
            ("seek", ((STREAM + 0xC, ALT_CURSOR), (CURSOR + 0x90, ALT_RECORD))),
            ("read", ((STREAM + 0xC, ALT_CURSOR),)),
            ("unlock", ((STREAM + 4, ALT_ARRAY),)),
            ("unlock", ((BUFFER, ALT_TABLE),)),
            ("set-volume", ((STREAM + 4, ALT_ARRAY),))):
        yield Case(buffered=0, mutations=((trigger, writes),))
    yield Case(states=(1, 1, 1), random=0, mutations=(("rand", ((STREAM + 4, ALT_ARRAY),)),))
    yield Case(status=2, bits=8, locked_bytes=31, end=29)


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
    with tempfile.TemporaryDirectory(prefix="th10-stream-start-integration-") as temporary:
        compiled = compile_candidates(Path(temporary))
        total = faults = reads = plays = 0
        for case in cases():
            expected = Execution(image).execute(case)
            actual = Execution(image, compiled).execute(case)
            assert actual == expected, (case, difference(expected, actual))
            total += 1
            faults += bool(expected["faults"])
            reads += sum(event[0] == "cursor-read" for event in expected["events"])
            plays += sum(event[0] in ("play", "other-play") for event in expected["events"])
        # Independent PCM observation: a 29-byte 8-bit track leaves two bytes
        # of 0x80 silence, with guards untouched and startup publishing playing.
        observed = Execution(image, compiled).execute(Case(bits=8))
        pcm = bytes(((SOURCE - 0x2600000 + i) * 71 + 19) & 255 for i in range(29)) + b"\x80\x80"
        offset = DESTINATION - OUTPUT
        assert observed["memory"][2][offset - 1:offset + 32] == b"\xCC" + pcm + b"\xCC"
        assert observed["result"] == 0
        print(f"PASS: {total} complete music-start comparisons, {reads} executing cursor reads, "
              f"{plays} Play calls, {faults} faults, and independent PCM padding check. "
              "Native MSVC matching remains unverified.")


if __name__ == "__main__":
    main()
