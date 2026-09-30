#!/usr/bin/env python3
"""Compare the 37-slot WAVE producer and single-slot helper with retail.

Archive_LoadFile, Sleep and logging are scripted boundary collaborators.
Tests include callback mutations, shutdown transitions, unchecked indices
and matching invalid writes. They do not model concurrent Windows threads.
"""

import argparse
from dataclasses import dataclass
from itertools import product
from pathlib import Path
import struct
import subprocess
import tempfile

from unicorn import Uc, UcError, UC_ARCH_X86, UC_MODE_32, UC_HOOK_CODE, UC_HOOK_MEM_INVALID
from unicorn.x86_const import UC_X86_REG_EAX, UC_X86_REG_ECX, UC_X86_REG_ESP, UC_X86_REG_EIP
from lzss_compressor_differential import (
    ROOT, CANDIDATE, STACK, STOP, PRESERVED, PEImage, load_manifest, load_oracle, region_directory)
from coff_module import load_module

STATE, DATA = 0x2500000, 0x2600000
GLOBAL, LOCAL, SHUTDOWN, NAMES = 0x492590, STATE + 0x100, 0x4977B4, 0x474B40
PENDING = GLOBAL + 0x5230
LOADER, LOG, SLEEP, OTHER_SLEEP = (STOP + 0x100 + 0x100 * i for i in range(4))
REPLACEMENT = STATE + 0x8000


def compile_candidates(directory, config, code_base=CANDIDATE, extra_bindings=None):
    bindings = region_directory(config, config["regions"])
    bindings.update({"_Archive_LoadFile@12": LOADER,
                     "?Append@TextLog_0044b810@@QAAPADPADZZ": LOG,
                     "_g_wave_sound_manager": GLOBAL, "_g_sound_preload_names": NAMES,
                     "_g_sound_preload_error": 0x46FDD4, "_g_wave_error_log": 0x474F70,
                     "_g_sound_shutdown_state": SHUTDOWN, "_g_sound_sleep": 0x4660AC})
    bindings.update(extra_bindings or {})
    modules = {}
    for offset, name in ((0, "sound_preload_worker"), (0x4000, "unassigned_0043d640")):
        obj = directory / (name + ".obj")
        subprocess.run([
            "clang++", "--target=i686-pc-windows-msvc", "-std=c++03", "-O2", "-mno-sse", "-mno-sse2",
            "-fno-exceptions", "-fno-rtti", "-fno-stack-protector", "-fno-builtin",
            "-I", str(ROOT / "matching2/msvc/include"), "-c",
            str(ROOT / "matching2/reference/semantic_candidates" / (name + ".cpp")), "-o", str(obj)],
            check=True, timeout=60)
        modules[name] = load_module(obj, code_base + offset, bindings)
    return modules


@dataclass(frozen=True)
class Case:
    operation: str = "worker"
    initial_shutdown: int = 0
    failure: object = None
    change_at: object = None
    changed_shutdown: int = 2
    replace_name: bool = False
    mutate_pending: bool = False
    sleep_count: int = 1
    sleep_shutdown: int = 1
    change_sleep: bool = False
    owner: int = LOCAL
    index: int = 0


def execute(image, modules, case):
    uc = Uc(UC_ARCH_X86, UC_MODE_32)
    uc.mem_map(0x400000, 0x100000)
    for section in image.sections:
        uc.mem_write(section["address"], image.read(section["address"], section["raw_size"]))
    for address in (CANDIDATE, STACK, STOP, STATE, DATA):
        uc.mem_map(address, 0x10000)
    for module in modules.values():
        uc.mem_write(module.base, module.data)

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

    def string(address):
        value = bytearray()
        while uc.mem_read(address + len(value), 1)[0]:
            value.extend(uc.mem_read(address + len(value), 1))
            assert len(value) < 512
        return bytes(value)

    def state():
        return read_words(SHUTDOWN)[0], read_words(PENDING, 37)

    uc.mem_write(GLOBAL, b"\xA5" * 0x5400)
    uc.mem_write(STATE, b"\xA5" * 0x10000)
    uc.mem_write(DATA, bytes(range(256)) * 256)
    uc.mem_write(REPLACEMENT, b"replaced-during-load.wav\0")
    words(SHUTDOWN, case.initial_shutdown)
    words(0x4660AC, SLEEP)
    original_names = read_words(NAMES, 37)
    events, faults = [], []
    loads = sleeps = 0

    def hook(machine, address, size, context):
        nonlocal loads, sleeps
        if address in (LOADER, 0x44B360):
            if address == LOADER:
                name, out_size, from_disk = args(3)
            else:
                name = uc.reg_read(UC_X86_REG_EAX)
                out_size, from_disk = args(2)
            events.append(("load", string(name), out_size, from_disk, state()))
            assert out_size == from_disk == 0
            index = loads if case.operation == "worker" else case.index
            if case.replace_name and 0 <= index < 37:
                words(NAMES + 4 * index, REPLACEMENT)
            if loads == case.change_at:
                words(SHUTDOWN, case.changed_shutdown)
            if case.mutate_pending:
                words(PENDING + 4 * (loads % 37), 0xFA110000 + loads)
                words(PENDING + 4 * ((loads + 1) % 37), 0xFA220000 + loads)
            result = 0 if loads == case.failure else DATA + loads * 0x100
            loads += 1
            finish(result, 12 if address == LOADER else 8)
        elif address in (LOG, 0x44B810):
            if address == LOG:
                log, format, name = args(3)
            else:
                log = uc.reg_read(UC_X86_REG_ECX)
                format, name = args(2)
            events.append(("log", log, format, string(name), state()))
            finish(0xBAD00001)
        elif address in (SLEEP, OTHER_SLEEP):
            milliseconds, = args(1)
            events.append(("sleep" if address == SLEEP else "changed-sleep", milliseconds, state()))
            assert milliseconds == 1
            sleeps += 1
            assert sleeps <= case.sleep_count
            if case.change_sleep:
                words(0x4660AC, OTHER_SLEEP)
            if sleeps == case.sleep_count:
                words(SHUTDOWN, case.sleep_shutdown)
            finish(0xBAD00002, 4)
        else:
            raise AssertionError(hex(address))

    def fault(machine, kind, address, size, value, context):
        faults.append((kind, address, size, value))
        return False

    for address in (LOADER, 0x44B360, LOG, 0x44B810, SLEEP, OTHER_SLEEP):
        uc.hook_add(UC_HOOK_CODE, hook, begin=address, end=address)
    uc.hook_add(UC_HOOK_MEM_INVALID, fault)
    sp = STACK + 0x8000
    for register, value in PRESERVED.items():
        uc.reg_write(register, value)
    if case.operation == "worker":
        words(sp, STOP)
        expected_sp = sp + 4
        entry = (modules["sound_preload_worker"].symbols["_Sound_PreloadWorker_0043d080@0"]
                 if modules else 0x43D080)
    else:
        if modules:
            words(sp, STOP, original_names[0], case.owner, case.index)
            expected_sp = sp + 16
            entry = modules["unassigned_0043d640"].symbols["_Sound_LoadPendingSlot_0043d640@12"]
        else:
            words(sp, STOP, case.owner, case.index)
            expected_sp = sp + 12
            uc.reg_write(UC_X86_REG_EAX, original_names[0])
            entry = 0x43D640
    uc.reg_write(UC_X86_REG_ESP, sp)
    try:
        uc.emu_start(entry, STOP, count=2000000)
    except UcError:
        if not faults:
            raise
    if not faults:
        assert uc.reg_read(UC_X86_REG_EIP) == STOP, "instruction budget exhausted"
        assert uc.reg_read(UC_X86_REG_ESP) == expected_sp
        assert all(uc.reg_read(register) == value for register, value in PRESERVED.items())
    return {"result": uc.reg_read(UC_X86_REG_EAX) if case.operation == "slot" and not faults else None,
            "events": events, "faults": faults, "loads": loads, "sleeps": sleeps,
            "state": state(), "global": bytes(uc.mem_read(GLOBAL, 0x5400)),
            "local": bytes(uc.mem_read(STATE, 0x10000)), "names": read_words(NAMES, 37)}


def cases():
    for shutdown, failure in product((0, 1, 2, 3, 0xFFFFFFFF), (None, 0, 1, 18, 36)):
        yield Case(initial_shutdown=shutdown, failure=failure)
    for index, changed, failed, mutate in product((0, 1, 18, 36), (0, 1, 2, 3, 0xFFFFFFFF),
                                                (False, True), (False, True)):
        yield Case(initial_shutdown=1, change_at=index, changed_shutdown=changed,
                   failure=index if failed else None, replace_name=True, mutate_pending=mutate)
    for count, shutdown, changed in product((1, 2, 5), (1, 2, 3, 0xFFFFFFFF), (False, True)):
        yield Case(sleep_count=count, sleep_shutdown=shutdown, change_sleep=changed)
    for owner, index, failure in product((LOCAL, GLOBAL),
            (0, 1, 36, 37, -1, -37, 0x40000000, -0x40000000, 0x40000024), (None, 0)):
        yield Case(operation="slot", owner=owner, index=index, failure=failure,
                   change_at=0, replace_name=True, mutate_pending=True)
    for failure in (None, 0):
        yield Case(operation="slot", owner=0, failure=failure)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--oracle", type=Path, default=ROOT / "matching2/build/oracle/th10.exe")
    options = parser.parse_args()
    config = load_manifest(ROOT / "matching2/msvc/regions.json")
    load_oracle(options.oracle, config)
    image = PEImage(options.oracle.read_bytes())
    with tempfile.TemporaryDirectory(prefix="th10-sound-preload-") as temporary:
        modules = compile_candidates(Path(temporary), config)
        comparisons = faults = 0
        for index, case in enumerate(cases()):
            expected, actual = execute(image, {}, case), execute(image, modules, case)
            differences = tuple(key for key in expected if expected[key] != actual[key])
            assert not differences, (index, case, differences, expected["events"], actual["events"])
            assert not any(event[0] == "changed-sleep" for event in actual["events"])
            logs = [event for event in actual["events"] if event[0] == "log"]
            if case.operation == "worker":
                if case.initial_shutdown == 2:
                    assert actual["loads"] == 0
                if logs and case.replace_name:
                    assert logs[0][3] == b"replaced-during-load.wav"
                assert len(logs) == int(case.failure is not None and actual["loads"] == case.failure + 1)
                if actual["sleeps"]:
                    assert actual["loads"] == 37 and actual["sleeps"] == case.sleep_count
            else:
                assert actual["loads"] == 1 and not logs and not actual["sleeps"]
                if not actual["faults"]:
                    assert actual["result"] == (0xFFFFFFFF if case.failure == 0 else 0)
            comparisons += 1
            faults += bool(actual["faults"])
        print(f"PASS: {comparisons} preload-worker/slot comparisons, including {faults} matching faults; "
              f"candidate modules: {', '.join(str(len(module.data)) for module in modules.values())} bytes. "
              "Native MSVC byte matching and concurrent Windows dispatch remain unverified.")


if __name__ == "__main__":
    main()
