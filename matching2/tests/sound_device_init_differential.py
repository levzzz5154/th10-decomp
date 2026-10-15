#!/usr/bin/env python3
"""Compare full sound initialization with retail, using scripted collaborators.

The original Ordinal_11 import thunk and security-cookie helper execute.
Individual cases script DirectSound, timer, primary-format setup, WAVE loading,
logging and allocation. Integrated cases execute the recovered primary-format
and WAVE routines plus the compiled chunk walker. No native byte match is claimed.
"""

import argparse
from dataclasses import dataclass
from itertools import product
from pathlib import Path
import struct
import subprocess
import tempfile

from unicorn import Uc, UcError, UC_ARCH_X86, UC_MODE_32, UC_HOOK_CODE, UC_HOOK_MEM_READ, UC_HOOK_MEM_INVALID
from unicorn.x86_const import (UC_X86_REG_EAX, UC_X86_REG_EBX, UC_X86_REG_ECX, UC_X86_REG_EDX,
                              UC_X86_REG_EDI, UC_X86_REG_ESP, UC_X86_REG_EIP)
from lzss_compressor_differential import (
    ROOT, CANDIDATE, OUTPUT, STACK, STOP, PRESERVED, PEImage,
    load_manifest, load_oracle, region_directory)
from coff_module import load_module
from sound_primary_format_differential import compile_candidate as compile_primary
from sound_wave_load_differential import compile_candidates as compile_wave, wave

STATE = 0x2500000
LOCAL, GLOBAL = STATE + 0x100, 0x492590
OWNER, OTHER_OWNER, OLD_OWNER = STATE + 0x6000, STATE + 0x6100, STATE + 0x6200
DEVICE, OTHER_DEVICE, OLD_DEVICE = STATE + 0x7000, STATE + 0x7100, STATE + 0x7200
BUFFER, OTHER_BUFFER = STATE + 0x7300, STATE + 0x7400
DEVICE_TABLE, BUFFER_TABLE = STATE + 0x7800, STATE + 0x7900
ALT_NAME = STATE + 0x7A00
PRIMARY_BUFFER = STATE + 0x7500
WAVE_DATA, SECONDARY_DATA, SECONDARY_OBJECTS = 0x2600000, 0x2700000, 0x2800000
SHUTDOWN, NAMES = 0x4977B4, 0x474B40
CREATE_DEVICE, COOPERATIVE, RELEASE, CREATE_BUFFER, LOCK, UNLOCK, PLAY, TIMER, PRIMARY, WAVE, LOG = (
    STOP + 0x100 + index * 0x100 for index in range(11))
SET_FORMAT, SLEEP = STOP + 0xC00, STOP + 0xD00


@dataclass(frozen=True)
class Case:
    global_receiver: bool = True
    allocate: bool = True
    previous_after_construct: bool = False
    device_result: int = 0
    device_output: int = DEVICE
    cooperative_result: int = 0
    primary_result: int = 0
    create_result: int = 0
    create_output: int = BUFFER
    lock_result: int = 0
    first: int = OUTPUT + 0x1000
    first_size: int = 0x8000
    second: int = OUTPUT + 0xA000
    second_size: int = 0
    initial_shutdown: int = 0
    cancel_on_wave: object = None
    fail_wave: object = None
    wave_result: int = -1
    change_name_on_failure: bool = False
    changes: tuple = ()
    primary_create_result: int = 0
    secondary_create_failure: object = None
    secondary_lock_failure: object = None


def compile_candidate(path, config, code_address=CANDIDATE, extra_bindings=None):
    subprocess.run([
        "clang++", "--target=i686-pc-windows-msvc", "-std=c++03", "-O2", "-mno-sse", "-mno-sse2",
        "-fno-exceptions", "-fno-rtti", "-fno-stack-protector", "-fno-builtin", "-ffunction-sections",
        "-I", str(ROOT / "matching2/msvc/include"), "-c",
        str(ROOT / "matching2/reference/semantic_candidates/sound_device_init.cpp"), "-o", str(path)],
        check=True, timeout=60)
    bindings = region_directory(config, config["regions"])
    bindings.update({"_asm_operator_new_00452493": 0x452493, "_asm_free_004524a1": 0x4524A1,
                     "_Ordinal_11_00452170@12": 0x452170,
                     "_Sound_SetPrimaryFormat_0044c7e0@16": PRIMARY,
                     "_g_sound_set_timer": 0x466218, "_g_wave_sound_manager": GLOBAL,
                     "_g_sound_preload_names": NAMES, "_g_sound_shutdown_state": SHUTDOWN,
                     "_g_wave_error_log": 0x474F70, "_g_sound_initialize_error": 0x46FE0C,
                     "_g_sound_initialize_ready": 0x46FDAC, "_g_sound_preload_error": 0x46FDD4,
                     "@SoundWave_LoadPending_0043d390@12": WAVE,
                     "?Append@TextLog_0044b810@@QAAPADPADZZ": LOG})
    bindings.update(extra_bindings or {})
    return load_module(path, code_address, bindings)


def execute(image, module, case, integration=None):
    uc = Uc(UC_ARCH_X86, UC_MODE_32)
    uc.mem_map(0x400000, 0x100000)
    for section in image.sections:
        uc.mem_write(section["address"], image.read(section["address"], section["raw_size"]))
    bodies = {module.base: module.data} if module else {}
    if module and integration:
        bodies[integration["primary"].base] = integration["primary"].data
        bodies.update(integration["wave"][1])
    for address in {CANDIDATE, OUTPUT, STACK, STOP, STATE} | {address & ~0xFFFF for address in bodies}:
        uc.mem_map(address, 0x10000)
    for address, body in bodies.items():
        uc.mem_write(address, body)

    def words(address, *values):
        uc.mem_write(address, struct.pack("<" + "I" * len(values), *(v & 0xFFFFFFFF for v in values)))

    def read_words(address, count):
        return struct.unpack("<" + "I" * count, uc.mem_read(address, count * 4))

    def args(count):
        return read_words(uc.reg_read(UC_X86_REG_ESP) + 4, count)

    def finish(value, cleanup=0):
        sp = uc.reg_read(UC_X86_REG_ESP)
        uc.reg_write(UC_X86_REG_EIP, read_words(sp, 1)[0])
        uc.reg_write(UC_X86_REG_ESP, sp + 4 + cleanup)
        uc.reg_write(UC_X86_REG_EAX, value & 0xFFFFFFFF)

    def string(address):
        result = bytearray()
        while True:
            byte = uc.mem_read(address + len(result), 1)[0]
            if not byte:
                return bytes(result)
            result.append(byte)
            assert len(result) < 512

    receiver = GLOBAL if case.global_receiver else LOCAL
    for manager in (LOCAL, GLOBAL):
        uc.mem_write(manager, b"\xA5" * 0x5400)
        words(manager + 0x610, OLD_OWNER)
    words(OWNER, 0xA5A5A5A5)
    words(OTHER_OWNER, OTHER_DEVICE)
    words(OLD_OWNER, OLD_DEVICE)
    for device in (DEVICE, OTHER_DEVICE, OLD_DEVICE):
        words(device, DEVICE_TABLE)
    for buffer in (BUFFER, OTHER_BUFFER, PRIMARY_BUFFER):
        words(buffer, BUFFER_TABLE)
    for offset, method in ((8, RELEASE), (12, CREATE_BUFFER), (24, COOPERATIVE)):
        words(DEVICE_TABLE + offset, method)
    for offset, method in ((8, RELEASE), (44, LOCK), (48, PLAY), (56, SET_FORMAT), (76, UNLOCK)):
        words(BUFFER_TABLE + offset, method)
    words(0x466008, CREATE_DEVICE)
    words(0x466218, TIMER)
    words(0x4660AC, SLEEP)
    words(SHUTDOWN, case.initial_shutdown)
    uc.mem_write(ALT_NAME, b"changed.wav\0")
    uc.mem_write(OUTPUT, b"\xA5" * 0x10000)
    events, faults = [], []
    owner_read = False
    secondary_indices = {}
    sources = []
    if integration:
        for address in (WAVE_DATA, SECONDARY_DATA, SECONDARY_OBJECTS):
            uc.mem_map(address, 0x10000)
            uc.mem_write(address, b"\xA5" * 0x10000)
        # A caller other than the global manager still preloads the global
        # object. Seed that object's existing device/slots independently.
        words(GLOBAL, DEVICE)
        uc.mem_write(GLOBAL + 8, bytes(256 * 4))
        for index in range(37):
            source = wave(f"startup-{index}", bytes((index + byte) & 255 for byte in range(17 + index)),
                          format_size=16 if index & 1 else 18)
            sources.append(source)
            address = WAVE_DATA + index * 0x200
            uc.mem_write(address, source.data)
            if index == case.fail_wave:
                uc.mem_write(address, b"FAIL")
            words(GLOBAL + 0x5230 + index * 4, address)
            buffer = SECONDARY_OBJECTS + index * 16
            words(buffer, BUFFER_TABLE)
            secondary_indices[buffer] = index

    def state():
        return tuple(read_words(receiver + offset, 1)[0] for offset in
                     (0, 0x608, 0x60C, 0x610, 0x618, 0x52C4, 0x52C8)) + (
                         read_words(OWNER, 1)[0], read_words(OTHER_OWNER, 1)[0], read_words(OLD_OWNER, 1)[0])

    def mutate(stage):
        offsets = {"device": 0, "stream": 0x608, "window": 0x60C, "owner": 0x610,
                   "cursor": 0x618, "volume_a": 0x52C4, "volume_b": 0x52C8}
        for at, field, value in case.changes:
            if at != stage:
                continue
            if field == "shutdown":
                words(SHUTDOWN, value)
            elif field == "owner_content":
                words(OWNER, value)
            else:
                words(receiver + offsets[field], value)

    def hook(machine, address, size, context):
        if address == 0x452493:
            requested, = args(1)
            assert requested == 4
            assert bytes(uc.mem_read(receiver + 0x408, 512)) == b"\xFF" * 512
            assert bytes(uc.mem_read(receiver + 0x620, 48)) == b"\xFF" * 48
            events.append(("new", requested, state()))
            mutate("new")
            finish(OWNER if case.allocate else 0)
        elif address == CREATE_DEVICE:
            device_id, output, outer = args(3)
            events.append(("device", device_id, output, outer, state()))
            assert device_id == outer == 0 and output == OWNER
            words(output, case.device_output)
            mutate("device")
            finish(case.device_result, 12)
        elif address == COOPERATIVE:
            device, window, level = args(3)
            events.append(("cooperative", device, window, level, state()))
            assert window == 0x12345678 and level == 2
            mutate("cooperative")
            finish(case.cooperative_result, 12)
        elif address == RELEASE:
            device, = args(1)
            events.append(("release", device, state()))
            mutate("release")
            finish(99, 4)
        elif address in (PRIMARY, 0x44C7E0):
            if address == PRIMARY:
                bits, channels, rate, owner = args(4)
            else:
                owner, = args(1)
                bits, channels, rate = (uc.reg_read(register) for register in
                                        (UC_X86_REG_ECX, UC_X86_REG_EBX, UC_X86_REG_EDI))
            events.append(("primary", bits, channels, rate, owner, state()))
            assert (bits, channels, rate, owner) == (16, 2, 44100, OWNER)
            mutate("primary")
            finish(case.primary_result, 16 if address == PRIMARY else 4)
        elif address == CREATE_BUFFER:
            device, description, output, outer = args(4)
            fields = read_words(description, 9)
            format = bytes(uc.mem_read(fields[4], 18)) if fields[4] else b""
            if integration and fields[1] == 1:
                events.append(("create-primary", device, fields, outer, read_words(output, 1)[0], state()))
                assert fields == (36, 1, 0, 0, 0, 0, 0, 0, 0) and outer == 0
                assert read_words(output, 1)[0] == 0
                words(output, PRIMARY_BUFFER)
                finish(case.primary_create_result, 16)
                return
            if integration and fields[1] == 0x80C8:
                index = (output - GLOBAL - 8) // 4
                assert 0 <= index < 37
                source = sources[index]
                events.append(("create-secondary", index, device, fields[:4], fields[5:], format, state()))
                assert fields[:4] == (36, 0x80C8, source.pcm_size, 0) and fields[5:] == (0, 0, 0, 0)
                words(output, SECONDARY_OBJECTS + index * 16)
                finish(-1 if index == case.secondary_create_failure else 0, 16)
                return
            events.append(("create", device, fields[:4], fields[5:], format, output, outer, state()))
            assert fields[:4] == (36, 0x8008, 0x8000, 0) and fields[5:] == (0, 0, 0, 0)
            assert format == struct.pack("<HHIIHHH", 1, 2, 44100, 176400, 4, 16, 0)
            assert output == receiver + 0x608 and outer == 0
            words(output, case.create_output)
            mutate("create")
            finish(case.create_result, 16)
        elif address == LOCK:
            buffer, offset, count, first, first_size, second, second_size, flags = args(8)
            if integration and buffer in secondary_indices:
                index = secondary_indices[buffer]
                source = sources[index]
                split = source.pcm_size // 2
                events.append(("lock-secondary", index, buffer, offset, count, flags, state()))
                assert (offset, count, flags) == (0, source.pcm_size, 0)
                words(first, SECONDARY_DATA + index * 0x400)
                words(first_size, split)
                words(second, SECONDARY_DATA + index * 0x400 + 0x200)
                words(second_size, source.pcm_size - split)
                finish(-1 if index == case.secondary_lock_failure else 0, 32)
                return
            events.append(("lock", buffer, offset, count, flags, state()))
            assert (offset, count, flags) == (0, 0x8000, 0)
            words(first, case.first)
            words(first_size, case.first_size)
            words(second, case.second)
            words(second_size, case.second_size)
            mutate("lock")
            finish(case.lock_result, 32)
        elif address == UNLOCK:
            buffer, first, first_size, second, second_size = args(5)
            if integration and buffer in secondary_indices:
                index = secondary_indices[buffer]
                source = sources[index]
                copied = bytes(uc.mem_read(first, first_size)) + bytes(uc.mem_read(second, second_size))
                assert copied == source.data[source.pcm_offset:source.pcm_offset + source.pcm_size]
                events.append(("unlock-secondary", index, first, first_size, second, second_size, copied, state()))
                finish(0x80004005, 20)
                return
            events.append(("unlock", buffer, first, first_size, second, second_size, state()))
            assert (first, first_size, second, second_size) == (case.first, case.first_size, case.second, case.second_size)
            assert bytes(uc.mem_read(first, 0x8000)) == bytes(0x8000)
            mutate("unlock")
            finish(0x80004005, 20)
        elif address == PLAY:
            buffer, reserved1, reserved2, flags = args(4)
            events.append(("play", buffer, reserved1, reserved2, flags, state()))
            assert (reserved1, reserved2, flags) == (0, 0, 1)
            mutate("play")
            finish(0x80004005, 16)
        elif address == SET_FORMAT:
            buffer, format = args(2)
            raw_format = bytes(uc.mem_read(format, 18))
            events.append(("format-primary", buffer, raw_format, state()))
            assert raw_format == struct.pack("<HHIIHHH", 1, 2, 44100, 176400, 4, 16, 0)
            mutate("primary")
            finish(case.primary_result, 8)
        elif address == TIMER:
            window, timer_id, milliseconds, callback = args(4)
            events.append(("timer", window, timer_id, milliseconds, callback, state()))
            assert (window, timer_id, milliseconds, callback) == (0x12345678, 0, 250, 0)
            mutate("timer")
            finish(0, 16)
        elif address in (WAVE, 0x43D390, integration["wave_entry"] if integration else 0):
            index = uc.reg_read(UC_X86_REG_ECX)
            manager = uc.reg_read(UC_X86_REG_EDX)
            name, = args(1)
            events.append(("wave", index, manager, string(name), state()))
            assert manager == GLOBAL
            if index == case.cancel_on_wave:
                words(SHUTDOWN, 2)
            if index == case.fail_wave and case.change_name_on_failure:
                words(NAMES + index * 4, ALT_NAME)
            mutate("wave")
            if not integration:
                finish(case.wave_result if index == case.fail_wave else 0, 4)
        elif address in (LOG, 0x44B810):
            if address == LOG:
                log, format = args(2)
                filename = args(3)[2] if format in (0x46FDD4, 0x46FD88, 0x46FD64) else 0
            else:
                log = uc.reg_read(UC_X86_REG_ECX)
                format, = args(1)
                filename = args(2)[1] if format in (0x46FDD4, 0x46FD88, 0x46FD64) else 0
            events.append(("log", log, format, string(filename) if filename else None, state()))
            mutate("log")
            finish(0xBAD00001)
        elif address == 0x4524A1:
            allocation, = args(1)
            events.append(("free", allocation, state()))
            mutate("free")
            finish(0xBAD00002)
        elif address == 0x452422:
            allocation, = args(1)
            events.append(("wave-free", allocation, state()))
            finish(0xBAD00003)
        elif address == SLEEP:
            raise AssertionError("all integrated fixture waves must already be pending")
        else:
            raise AssertionError(hex(address))

    def read_owner(machine, kind, address, size, value, context):
        nonlocal owner_read
        if not owner_read and case.previous_after_construct:
            words(OWNER, OLD_DEVICE)
        owner_read = True

    def fault(machine, kind, address, size, value, context):
        faults.append((kind, address, size, value))
        return False

    hooks = {0x452493, 0x4524A1, CREATE_DEVICE, COOPERATIVE, RELEASE,
             CREATE_BUFFER, LOCK, UNLOCK, PLAY, TIMER, PRIMARY, 0x44C7E0, WAVE, 0x43D390, LOG, 0x44B810}
    if integration:
        hooks.difference_update((PRIMARY, 0x44C7E0))
        hooks.update((SET_FORMAT, SLEEP, 0x452422, integration["wave_entry"]))
    for address in hooks:
        uc.hook_add(UC_HOOK_CODE, hook, begin=address, end=address)
    uc.hook_add(UC_HOOK_MEM_READ, read_owner, begin=OWNER, end=OWNER + 3)
    uc.hook_add(UC_HOOK_MEM_INVALID, fault)
    sp = STACK + 0x8000
    words(sp, STOP, 0x12345678)
    uc.reg_write(UC_X86_REG_ESP, sp)
    uc.reg_write(UC_X86_REG_ECX, receiver)
    for register, value in PRESERVED.items():
        uc.reg_write(register, value)
    entry = module.symbols["?Initialize@WaveSoundManager@@QAEHPAX@Z"] if module else 0x43CD30
    try:
        uc.emu_start(entry, STOP, count=2000000)
    except UcError:
        if not faults:
            raise
    if not faults:
        assert uc.reg_read(UC_X86_REG_EIP) == STOP
        assert uc.reg_read(UC_X86_REG_ESP) == sp + 8
        assert all(uc.reg_read(register) == value for register, value in PRESERVED.items())
    result = {"result": uc.reg_read(UC_X86_REG_EAX) if not faults else None,
            "events": events, "faults": faults,
            "local": bytes(uc.mem_read(LOCAL, 0x5400)), "global": bytes(uc.mem_read(GLOBAL, 0x5400)),
            "cells": bytes(uc.mem_read(OWNER, 0x300)), "names": bytes(uc.mem_read(NAMES, 37 * 4)),
            "output": bytes(uc.mem_read(OUTPUT, 0x10000))}
    if integration:
        result.update(waves=bytes(uc.mem_read(WAVE_DATA, 0x10000)),
                      secondary_output=bytes(uc.mem_read(SECONDARY_DATA, 0x10000)))
    return result


def verify_observations(case, result):
    events = result["events"]
    if any(event[0] == "unlock" for event in events):
        expected_output = bytearray(b"\xA5" * 0x10000)
        start = case.first - OUTPUT
        expected_output[start:start + 0x8000] = bytes(0x8000)
        assert result["output"] == expected_output, "only the fixed first span must be cleared"
    waves = [event for event in events if event[0] == "wave"]
    assert [event[1] for event in waves] == list(range(len(waves)))
    assert all(event[2] == GLOBAL for event in waves)
    ready = [event for event in events if event[0] == "log" and event[2] == 0x46FDAC]
    if result["result"] == 0:
        assert len(waves) == 37 and len(ready) == 1
    if ready:
        assert result["result"] == 0
    if case.fail_wave is not None and waves and waves[-1][1] == case.fail_wave:
        errors = [event for event in events if event[0] == "log" and event[2] == 0x46FDD4]
        assert len(errors) == 1 and result["result"] == 0xFFFFFFFF
        if case.change_name_on_failure:
            assert errors[0][3] == b"changed.wav", "failure logging must reload the filename table"
    if any(event[0] == "create" for event in events) and (case.create_result < 0 or case.lock_result < 0):
        assert not any(event[0] == "free" for event in events), "late failure must retain the device owner"


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
    with tempfile.TemporaryDirectory(prefix="th10-sound-init-") as temporary:
        module = compile_candidate(Path(temporary) / "init.obj", config)
        trials = [Case(), Case(global_receiver=False), Case(allocate=False), Case(previous_after_construct=True)]
        trials.extend(Case(device_result=device, cooperative_result=cooperative,
                           create_result=create, lock_result=lock)
                      for device, cooperative, create, lock in product((0, 1, -1, -0x80000000), repeat=4))
        trials.extend(Case(primary_result=value) for value in (-1, -0x80000000, 1, 0x7FFFFFFF))
        trials.extend((Case(device_output=0), Case(create_output=0)))
        trials.extend(Case(first_size=first, second_size=second, first=OUTPUT + 0x1000 + alignment)
                      for first, second, alignment in product((0, 1, 0x4000, 0x8000, 0xFFFFFFFF),
                                                              (0, 1, 0x4000), (0, 1, 3)))
        trials.extend((Case(first=0), Case(first=OUTPUT + 0xE000)))
        trials.extend(Case(initial_shutdown=value) for value in (1, 2, 3, 0xFFFFFFFF))
        trials.extend(Case(fail_wave=index, wave_result=result, change_name_on_failure=change)
                      for index, result, change in product((0, 1, 18, 36), (1, -1), (False, True)))
        trials.extend(Case(cancel_on_wave=index) for index in (0, 1, 18, 35, 36))
        trials.extend(Case(changes=((stage, "stream", OTHER_BUFFER),)) for stage in ("create", "lock", "unlock"))
        trials.extend(Case(changes=((stage, "owner", owner),))
                      for stage, owner in product(("device", "cooperative", "primary"), (0, OTHER_OWNER)))
        trials.extend(Case(device_result=-1, changes=(("log", "owner", owner),)) for owner in (0, OTHER_OWNER))
        trials.extend((Case(device_result=-1, changes=(("release", "owner", OTHER_OWNER),)),
                       Case(device_result=-1, changes=(("free", "owner", OTHER_OWNER),)),
                       Case(changes=(("timer", "window", 0), ("timer", "volume_a", 42))),
                       Case(changes=(("timer", "shutdown", 2),)),
                       Case(changes=(("wave", "owner", OTHER_OWNER),))))
        faults = 0
        for index, case in enumerate(trials):
            expected, actual = execute(image, None, case), execute(image, module, case)
            differences = tuple(key for key in expected if expected[key] != actual[key])
            assert not differences, (index, case, differences, expected["events"], actual["events"],
                                     expected["faults"], actual["faults"])
            verify_observations(case, actual)
            faults += bool(expected["faults"])
        directory = Path(temporary)
        primary = compile_primary(directory / "primary.obj", CANDIDATE + 0x10000)
        waves = compile_wave(directory, config, {"?Append@TextLog_0044b810@@QAAPADPADZZ": LOG})
        wave_entry = waves[0].symbols["@SoundWave_LoadPending_0043d390@12"]
        integrated = compile_candidate(directory / "integrated.obj", config, CANDIDATE + 0x20000, {
            "_Sound_SetPrimaryFormat_0044c7e0@16": primary.symbols["_Sound_SetPrimaryFormat_0044c7e0@16"],
            "@SoundWave_LoadPending_0043d390@12": wave_entry})
        integration = {"primary": primary, "wave": waves, "wave_entry": wave_entry}
        combined = [Case(), Case(global_receiver=False), Case(allocate=False), Case(previous_after_construct=True),
                    Case(primary_create_result=-1), Case(primary_create_result=1),
                    Case(primary_result=-1), Case(primary_result=1), Case(create_result=-1),
                    Case(lock_result=-1), Case(initial_shutdown=2)]
        combined.extend(Case(fail_wave=index, change_name_on_failure=change)
                        for index, change in product((0, 18, 36), (False, True)))
        combined.extend(Case(secondary_create_failure=index) for index in (0, 18, 36))
        combined.extend(Case(secondary_lock_failure=index) for index in (0, 18, 36))
        combined.extend(Case(cancel_on_wave=index) for index in (0, 35, 36))
        combined.extend(Case(changes=((stage, "stream", OTHER_BUFFER),)) for stage in ("create", "lock", "unlock"))
        combined.append(Case(changes=(("timer", "window", 0), ("timer", "volume_a", 42))))
        preloads = integrated_faults = 0
        for index, case in enumerate(combined):
            expected = execute(image, None, case, integration)
            actual = execute(image, integrated, case, integration)
            differences = tuple(key for key in expected if expected[key] != actual[key])
            assert not differences, ("integrated", index, case, differences, expected["events"], actual["events"],
                                     expected["faults"], actual["faults"])
            verify_observations(case, actual)
            preloads += sum(event[0] == "wave" for event in actual["events"])
            integrated_faults += bool(actual["faults"])
        print(f"PASS: {len(trials)} sound-initializer comparisons with {faults} matching faults; "
              f"{len(combined)} integrated startup scenarios and {preloads} actual WAVE preloads "
              f"with {integrated_faults} matching fault(s). Four C++ routines execute together; "
              f"initializer module {len(module.data)} bytes. Native MSVC frame/bytes and live DirectSound remain unverified.")


if __name__ == "__main__":
    main()
