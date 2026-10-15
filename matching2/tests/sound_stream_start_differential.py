#!/usr/bin/env python3
"""Compare stream start and command publication with retail instruction bodies.

Integrated cases freshly compile the explicitly sequenced selector plus the
maintained restoration, rewind and volume helpers. Refill, DirectSound methods,
Sleep and rand remain scripted.
Incoming ECX is deliberately varied: it is stack-local storage, not an input
context. This does not verify native private ABIs or live DirectSound behavior.
"""

import argparse
from dataclasses import dataclass
from itertools import product
from pathlib import Path
import struct
import subprocess
import tempfile

from unicorn import Uc, UcError, UC_ARCH_X86, UC_MODE_32, UC_HOOK_CODE, UC_HOOK_MEM_INVALID, UC_HOOK_INTR
from unicorn.x86_const import UC_X86_REG_EAX, UC_X86_REG_EBX, UC_X86_REG_ECX, UC_X86_REG_ESI, UC_X86_REG_EDI, UC_X86_REG_ESP, UC_X86_REG_EIP
from lzss_compressor_differential import (
    ROOT, CANDIDATE, STACK, STOP, PRESERVED, PEImage, load_manifest, load_oracle)
from coff_module import load_module

STATE = 0x2500000
MANAGER, STREAM, ARRAY, ALT_ARRAY = STATE + 0x100, STATE + 0x6000, STATE + 0x6100, STATE + 0x6200
BUFFER, ALT_BUFFER, THIRD = STATE + 0x6300, STATE + 0x6400, STATE + 0x6500
TABLE, ALT_TABLE = STATE + 0x6600, STATE + 0x6700
FIND, RUN, FILL, REWIND, VOLUME, START = (STOP + 0x100 * i for i in range(1, 7))
STATUS, RESTORE, SLEEP, PLAY, POSITION, SET_VOLUME, RANDOM, ALT_PLAY = (STOP + 0x100 * i for i in range(7, 15))
OTHER_SLEEP = STOP + 0xF00
START_FULL, COMMAND, COMMAND_FULL = CANDIDATE + 0x1000, CANDIDATE + 0x2000, CANDIDATE + 0x3000
HELPERS = (("run", "platform_run_interface_0044d300", "?Run@PlatformD300Entry@@QAEHPAI@Z", CANDIDATE + 0x4000),
           ("find", "platform_find_available_0044d370", "?FindAvailable@PlatformInterfaceState_0044D370@@QAEPAUPlatformD370Entry@@XZ", CANDIDATE + 0x6000),
           ("rewind", "platform_query_interfaces_0044d600", "?Query@PlatformQueryInterfaces_0044D600@@QAEHXZ", CANDIDATE + 0x8000),
           ("volume", "platform_set_operation_deadline_0044d4e0", "?SetOperationDeadline@PlatformInterfaceState_0044D4E0@@QAEHH@Z", CANDIDATE + 0xA000))
SYMBOLS = {"find": "?FindAvailable@SoundStream@@QAEPAUWaveSecondaryBuffer@@XZ",
           "run": "?RestoreIfLost@WaveSecondaryBuffer@@QAEHPAI@Z",
           "rewind": "?RewindBuffers@SoundStream@@QAEHXZ", "volume": "?SetVolume@SoundStream@@QAEHH@Z"}


@dataclass(frozen=True)
class Case:
    operation: str = "start"
    integrated: bool = False
    stream: int = STREAM
    array: bool = True
    selected: int = BUFFER
    priority: int = 0
    flags: int = 1
    command: int = 0x12345678
    incoming_ecx: int = 0xA1B2C3D4
    restored: int = 0
    run_result: int = 1
    fill_result: int = 0
    play_result: int = 0
    start_result: int = 0
    mutations: tuple = ()
    entries: tuple = (BUFFER, ALT_BUFFER, THIRD)
    states: tuple = (0, 1, 1)
    restore_status: int = 0
    status_result: int = 0
    restore_results: tuple = (0, 0)
    random: int = 1
    volume: int = 0


def compile_candidates(directory, config):
    helpers, bodies, entries = {}, {}, {}
    bindings = {"__imp__Sleep@4": 0x4660AC, "_asm_rand_0045371b": 0x45371B,
                "_data_00497854": 0x497854, "__ftol2": 0x463B2C}
    common = ["clang++", "--target=i686-pc-windows-msvc", "-std=c++03", "-O2", "-mno-sse", "-mno-sse2",
              "-fno-exceptions", "-fno-rtti", "-fno-stack-protector", "-fno-builtin",
              "-fno-delete-null-pointer-checks"]
    for name, source, symbol, address in HELPERS:
        obj = directory / (name + ".obj")
        source_path = ROOT / "matching2/msvc/src/game" / (source + ".cpp")
        if name == "find":
            source_path = ROOT / "matching2/reference/semantic_candidates/sound_stream_select.cpp"
            symbol = SYMBOLS["find"]
        subprocess.run([*common, "-c", str(source_path),
                        "-o", str(obj)], check=True, timeout=60)
        module = load_module(obj, address, bindings)
        helpers[name] = module
        entries[name] = module.symbols[symbol]
        bodies[address] = module.data
    unit_bindings = {SYMBOLS[name]: address for name, address in
                     (("find", FIND), ("run", RUN), ("rewind", REWIND), ("volume", VOLUME))}
    unit_bindings.update({"_SoundStream_FillBuffer_0044d110@12": FILL, "_SoundStream_Start_0044d440@12": START})
    modules = {}
    for name, source, unit_address, full_address in (
            ("start", "sound_stream_start", CANDIDATE, START_FULL),
            ("command", "unassigned_0043da80", COMMAND, COMMAND_FULL)):
        obj = directory / (source + ".obj")
        subprocess.run([*common, "-c", str(ROOT / "matching2/reference/semantic_candidates" / (source + ".cpp")),
                        "-o", str(obj)], check=True, timeout=60)
        modules[name] = load_module(obj, unit_address, unit_bindings)
        full_bindings = dict(unit_bindings)
        full_bindings.update((SYMBOLS[key], address) for key, address in entries.items())
        full_bindings["_SoundStream_Start_0044d440@12"] = START_FULL
        modules[name + "_full"] = load_module(obj, full_address, full_bindings)
    bodies.update((module.base, module.data) for module in modules.values())
    return modules, bodies, entries, helpers


def execute(image, compiled, case):
    modules, bodies, entries, _ = compiled if compiled else ({}, {}, {}, {})
    uc = Uc(UC_ARCH_X86, UC_MODE_32)
    uc.mem_map(0x400000, 0x100000)
    for section in image.sections:
        uc.mem_write(section["address"], image.read(section["address"], section["raw_size"]))
    for address in (CANDIDATE, STACK, STOP, STATE):
        uc.mem_map(address, 0x10000)
    for address, body in bodies.items():
        uc.mem_write(address, body)

    def words(address, *values):
        uc.mem_write(address, struct.pack("<" + "I" * len(values), *(v & 0xFFFFFFFF for v in values)))

    def read_words(address, count=1):
        return struct.unpack("<" + "I" * count, uc.mem_read(address, count * 4))

    def args(count):
        return read_words(uc.reg_read(UC_X86_REG_ESP) + 4, count)

    def finish(value, cleanup=0):
        sp = uc.reg_read(UC_X86_REG_ESP)
        uc.reg_write(UC_X86_REG_EIP, read_words(sp)[0])
        uc.reg_write(UC_X86_REG_ESP, sp + 4 + cleanup)
        uc.reg_write(UC_X86_REG_EAX, value & 0xFFFFFFFF)

    uc.mem_write(STATE, b"\xA5" * 0x10000)
    words(MANAGER + 0x5208, case.stream)
    words(MANAGER + 0x5210, 0x10203040)
    words(STREAM + 4, ARRAY if case.array else 0, 256, 0x12345678, len(case.entries))
    words(ARRAY, *case.entries)
    words(ALT_ARRAY, ALT_BUFFER, BUFFER, THIRD)
    for pointer in (BUFFER, ALT_BUFFER, THIRD):
        words(pointer, TABLE)
    for table in (TABLE, ALT_TABLE):
        for offset, address in ((36, STATUS), (48, PLAY if table == TABLE else ALT_PLAY), (52, POSITION),
                                (60, SET_VOLUME), (80, RESTORE)):
            words(table + offset, address)
    words(0x4660AC, SLEEP)
    words(0x497854, case.volume)
    events, faults = [], []
    stage = None
    restore_calls = 0
    labels = {FIND: "find", RUN: "run", REWIND: "rewind", VOLUME: "volume",
              0x44D370: "find", 0x44D300: "run", 0x44D600: "rewind", 0x44D4E0: "volume"}
    labels.update((address, name) for name, address in entries.items())

    def state():
        return read_words(STREAM, 13), read_words(MANAGER + 0x5208, 3)

    def event(kind, *values):
        events.append((kind, *values, state()))
        for trigger, writes in case.mutations:
            if trigger == kind:
                for address, value in writes:
                    words(address, value)

    def hook(machine, address, size, context):
        nonlocal stage, restore_calls
        if address in labels:
            kind = labels[address]
            stage = kind
            retail = address < CANDIDATE
            receiver = uc.reg_read(UC_X86_REG_ESI if retail and kind == "run" else
                                   UC_X86_REG_EAX if retail and kind == "volume" else
                                   UC_X86_REG_EDI if retail else UC_X86_REG_ECX)
            if kind == "run":
                out = uc.reg_read(UC_X86_REG_EBX) if retail else args(1)[0]
                event(kind, receiver)
                if not case.integrated:
                    words(out, case.restored)
                    finish(case.run_result, 0 if retail else 4)
            elif kind == "volume":
                value, = args(1)
                event(kind, receiver, value)
                if not case.integrated:
                    finish(0x80004005, 4)
            else:
                event(kind, receiver)
                if not case.integrated:
                    finish(case.selected if kind == "find" else 0x80004005)
        elif address in (FILL, 0x44D110):
            if address == FILL:
                stream, buffer, loop = args(3)
            else:
                stream = uc.reg_read(UC_X86_REG_EAX)
                buffer, loop = args(2)
            event("fill", stream, buffer, loop)
            assert loop == 0
            finish(case.fill_result, 12 if address == FILL else 8)
        elif address in (START, 0x44D440) and case.operation == "command" and not case.integrated:
            if address == START:
                stream, priority, flags = args(3)
            else:
                stream = uc.reg_read(UC_X86_REG_EAX)
                priority, flags = args(2)
            event("start", stream, priority, flags)
            assert (priority, flags) == (0, 1)
            finish(case.start_result, 12 if address == START else 8)
        elif address == STATUS:
            pointer, out = args(2)
            status = case.restore_status if stage == "run" else case.states[(BUFFER, ALT_BUFFER, THIRD).index(pointer)]
            event("status", pointer, status, stage)
            words(out, status)
            finish(case.status_result if stage == "run" else 0x80004005, 8)
        elif address == RESTORE:
            pointer, = args(1)
            assert restore_calls < len(case.restore_results)
            result = case.restore_results[restore_calls]
            restore_calls += 1
            event("restore", pointer, result)
            finish(result, 4)
        elif address in (SLEEP, OTHER_SLEEP):
            delay, = args(1)
            assert delay == 10
            event("sleep" if address == SLEEP else "alternate-sleep", delay)
            finish(0xBAD00001, 4)
        elif address == 0x45371B:
            event("rand", case.random)
            finish(case.random)
        elif address in (PLAY, ALT_PLAY):
            pointer, reserved, priority, flags = args(4)
            event("play" if address == PLAY else "alternate-play", pointer, reserved, priority, flags)
            assert reserved == 0
            finish(case.play_result, 16)
        elif address == POSITION:
            pointer, position = args(2)
            assert position == 0
            event("position", pointer, position)
            finish(0x80004005, 8)
        elif address == SET_VOLUME:
            pointer, volume = args(2)
            event("set-volume", pointer, volume)
            finish(0x80004005, 8)
        elif address in (START, 0x44D440):
            pass  # execute the actual entry, including the command's callee
        else:
            raise AssertionError(hex(address))

    def fault(machine, kind, address, size, value, context):
        faults.append((kind, address, size, value))
        return False

    def interrupt(machine, number, context):
        faults.append(("interrupt", number))
        uc.emu_stop()

    for address in (*labels, FILL, 0x44D110, START, 0x44D440, STATUS, RESTORE, SLEEP,
                    0x45371B, PLAY, ALT_PLAY, POSITION, SET_VOLUME, OTHER_SLEEP):
        uc.hook_add(UC_HOOK_CODE, hook, begin=address, end=address)
    uc.hook_add(UC_HOOK_MEM_INVALID, fault)
    uc.hook_add(UC_HOOK_INTR, interrupt)
    sp = STACK + 0x8000
    preserved = dict(PRESERVED)
    uc.reg_write(UC_X86_REG_ECX, case.incoming_ecx)
    if case.operation == "start":
        if modules:
            module = modules["start_full" if case.integrated else "start"]
            entry = module.symbols["_SoundStream_Start_0044d440@12"]
            words(sp, STOP, case.stream, case.priority, case.flags)
            expected_sp = sp + 16
        else:
            entry = 0x44D440
            uc.reg_write(UC_X86_REG_EAX, case.stream)
            words(sp, STOP, case.priority, case.flags)
            expected_sp = sp + 12
    else:
        if modules:
            module = modules["command_full" if case.integrated else "command"]
            entry = module.symbols["_Sound_StartMusicCommand_0043da80@8"]
            words(sp, STOP, MANAGER, case.command)
            expected_sp = sp + 12
        else:
            entry = 0x43DA80
            preserved[UC_X86_REG_ESI] = MANAGER
            words(sp, STOP, case.command)
            expected_sp = sp + 8
    for register, value in preserved.items():
        uc.reg_write(register, value)
    uc.reg_write(UC_X86_REG_ESP, sp)
    try:
        uc.emu_start(entry, STOP, count=2000000)
    except UcError:
        if not faults:
            raise
    if not faults:
        assert uc.reg_read(UC_X86_REG_EIP) == STOP, "instruction budget exhausted"
        assert uc.reg_read(UC_X86_REG_ESP) == expected_sp
        assert all(uc.reg_read(register) == value for register, value in preserved.items())
    return {"result": uc.reg_read(UC_X86_REG_EAX) if not faults else None,
            "events": events, "faults": faults, "state": bytes(uc.mem_read(STATE, 0x10000))}


def compare_maintained_selector(directory, compiled, image):
    """Keep the observed Clang evaluation-order gap reproducible as evidence."""
    obj = directory / "find-maintained.obj"
    subprocess.run(["clang++", "--target=i686-pc-windows-msvc", "-std=c++03", "-O2", "-mno-sse", "-mno-sse2",
                    "-fno-exceptions", "-fno-rtti", "-fno-stack-protector", "-fno-builtin", "-c",
                    str(ROOT / "matching2/msvc/src/game/platform_find_available_0044d370.cpp"),
                    "-o", str(obj)], check=True, timeout=60)
    baseline = load_module(obj, CANDIDATE + 0xC000, {"_asm_rand_0045371b": 0x45371B})
    baseline_entry = baseline.symbols[HELPERS[1][2]]
    modules, bodies, entries, helpers = compiled
    entries = dict(entries, find=baseline_entry)
    bindings = {SYMBOLS[name]: value for name, value in entries.items()}
    bindings["_SoundStream_FillBuffer_0044d110@12"] = FILL
    start = load_module(directory / "sound_stream_start.obj", CANDIDATE + 0xE000, bindings)
    modules = dict(modules, start_full=start)
    bodies = dict(bodies)
    bodies.update({baseline.base: baseline.data, start.base: start.data})
    case = Case(integrated=True, states=(1, 1, 1), mutations=(("rand", ((STREAM + 4, ALT_ARRAY),)),))
    expected = execute(image, None, case)
    actual = execute(image, (modules, bodies, entries, helpers), case)
    differences = tuple(key for key in expected if expected[key] != actual[key])
    # Compiler versions may choose retail's order. If this one differs, the
    # characterized gap must be exactly the old-array versus new-array choice.
    if differences:
        assert differences == ("events",), differences
        assert next(event[1] for event in expected["events"] if event[0] == "play") == BUFFER
        assert next(event[1] for event in actual["events"] if event[0] == "play") == ALT_BUFFER
    return bool(differences)


def cases(integrated=False):
    if not integrated:
        for array, selected, restored, run, fill in product((False, True), (0, BUFFER), (0, 1, 0xFFFFFFFF),
                (0, 1, 0x80004005), (0, 1, 0x80004005)):
            yield Case(array=array, selected=selected, restored=restored, run_result=run, fill_result=fill)
        for ecx, priority, flags, result in product((0, 1, 2, 0xFFFFFFFF), (0, 0x12345678),
                                                   (0, 1, 0xFFFFFFFF), (0, 1, 0x80004005)):
            yield Case(incoming_ecx=ecx, priority=priority, flags=flags, play_result=result, restored=1)
        yield Case(stream=0)
        for stage in ("find", "run", "fill", "rewind", "volume", "play"):
            yield Case(restored=1, mutations=((stage, ((STREAM + 4, ALT_ARRAY), (ARRAY, ALT_BUFFER))),))
        yield Case(restored=1, mutations=(("volume", ((BUFFER, ALT_TABLE), (STREAM + 0x14, 0xABCDEF))),))
        for stream, command, result in product((0, STREAM), (0, 1, 0xFFFFFFFF, 0x12345678),
                                              (0, 1, 0x7FFFFFFF, 0x80004005)):
            yield Case(operation="command", stream=stream, command=command, start_result=result)
        for result in (0, 0x80004005):
            yield Case(operation="command", start_result=result, mutations=(
                ("start", ((MANAGER + 0x5208, 0), (MANAGER + 0x5210, 0xABCDEF))),))
        return
    for operation, states, restored, ecx in product(("start", "command"),
            ((0, 1, 1), (1, 0, 1), (1, 1, 1)), (0, 2), (0, 0xDEADBEEF)):
        yield Case(operation=operation, integrated=True, states=states, restore_status=restored, incoming_ecx=ecx)
    for results in ((0, 0), (0x88780096, 0), (0x88780096, 1, 0x80004005, 0), (0, 1, 0, 0)):
        yield Case(integrated=True, restore_status=2, restore_results=results)
    for status, fill, play in product((0, 1, 0x80004005), (0, 0x80004005), (0, 1, 0x80004005)):
        yield Case(integrated=True, restore_status=2, status_result=status, fill_result=fill, play_result=play)
    for volume in (-2, -1, 0, 1, 25, 50, 75, 99, 100, 101, 200):
        yield Case(integrated=True, volume=volume)
    for random_value in (0, 2, 32767):
        yield Case(integrated=True, states=(1, 1, 1), random=random_value)
    yield Case(integrated=True, states=(1, 1, 1), mutations=(("rand", ((STREAM + 4, ALT_ARRAY),)),))
    yield Case(integrated=True, restore_status=2, restore_results=(0x88780096, 1, 0x88780096, 0),
               mutations=(("sleep", ((0x4660AC, OTHER_SLEEP),)),))
    for entries in ((), (0,), (0, ALT_BUFFER, THIRD), (0, 0, 0)):
        yield Case(integrated=True, entries=entries)
    yield Case(integrated=True, array=False)
    for stage, writes in (
        ("status", ((STREAM + 4, ALT_ARRAY),)),
        ("restore", ((ARRAY, ALT_BUFFER),)),
        ("fill", ((STREAM + 4, ALT_ARRAY),)),
        ("position", ((STREAM + 0x10, 1),)),
        ("set-volume", ((BUFFER, ALT_TABLE), (STREAM + 0x14, 123))),
        ("play", ((STREAM + 0x30, 0),)),
    ):
        yield Case(integrated=True, restore_status=2, mutations=((stage, writes),))


def verify(case, result):
    if result["faults"]:
        return
    events = result["events"]
    plays = [event for event in events if event[0] in ("play", "alternate-play")]
    if plays:
        stream_words = plays[0][-1][0]
        assert stream_words[7] == 0 and stream_words[12] == 1
        priority, flags = (0, 1) if case.operation == "command" else (case.priority, case.flags)
        assert stream_words[8:10] == (priority, flags) and stream_words[11] == 0
        assert plays[0][3:5] == (priority, flags)
    if not case.integrated and case.operation == "start":
        fills = [event for event in events if event[0] == "fill"]
        assert bool(fills) == bool(case.array and case.selected and case.restored and case.run_result < 0x80000000)
    if case.operation == "command":
        command, = struct.unpack_from("<I", result["state"], MANAGER - STATE + 0x5210)
        if result["result"] == 0:
            assert command == case.command
        assert result["result"] in (0, 0xFFFFFFFF)


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
    with tempfile.TemporaryDirectory(prefix="th10-stream-start-") as temporary:
        compiled = compile_candidates(Path(temporary), config)
        baseline_gap = compare_maintained_selector(Path(temporary), compiled, image)
        counts, faults = [], []
        for integrated in (False, True):
            total = fault_count = 0
            for index, case in enumerate(cases(integrated)):
                expected, actual = execute(image, None, case), execute(image, compiled, case)
                differences = tuple(key for key in expected if expected[key] != actual[key])
                assert not differences, (integrated, index, case, differences, expected["events"], actual["events"],
                                         expected["faults"], actual["faults"])
                verify(case, actual)
                total += 1
                fault_count += bool(actual["faults"])
            counts.append(total)
            faults.append(fault_count)
        print(f"PASS: {counts[0]} stream-start/command comparisons ({faults[0]} matching faults), "
              f"{counts[1]} integrated helper comparisons ({faults[1]} matching faults); "
              f"candidate modules {len(compiled[0]['start'].data)} and {len(compiled[0]['command'].data)} bytes. "
              f"Maintained-selector Clang ordering gap observed: {baseline_gap}. "
              "Refill is scripted; native MSVC bytes and live audio remain unverified.")


if __name__ == "__main__":
    main()
