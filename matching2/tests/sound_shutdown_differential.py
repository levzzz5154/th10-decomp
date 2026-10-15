#!/usr/bin/env python3
"""Compare sound cleanup and MIDI worker shutdown, individually and together.

Integrated runs execute the maintained interface aggregator as well. Allocation,
COM methods and Windows imports are scripted; callback mutations expose cached
versus reloaded state/imports. No Windows scheduler or MSVC byte match is claimed.
"""

import argparse
from dataclasses import dataclass
from itertools import product
from pathlib import Path
import random
import struct
import subprocess
import tempfile

from unicorn import Uc, UcError, UC_ARCH_X86, UC_MODE_32, UC_HOOK_CODE, UC_HOOK_MEM_INVALID
from unicorn.x86_const import (UC_X86_REG_EAX, UC_X86_REG_ECX, UC_X86_REG_ESI, UC_X86_REG_EDI,
                              UC_X86_REG_ESP, UC_X86_REG_EIP)
from lzss_compressor_differential import (
    ROOT, CANDIDATE, STACK, STOP, PRESERVED, PEImage, load_manifest, load_oracle, load_candidate)
from coff_module import load_module

STATE, DATA = 0x2500000, 0x2600000
MANAGER = STATE + 0x100
OWNER, ALT_OWNER, DEVICE, ALT_DEVICE, STREAM, ALT_STREAM, MIDI, ALT_MIDI = (
    STATE + 0x7000 + i * 0x100 for i in range(8))
BUFFER_TABLE, MIDI_TABLE, AGG_TABLE, ENTRIES, ALT_ENTRIES = (
    STATE + 0x7800 + i * 0x100 for i in range(5))
KILL, MIDI_STUB, AGG_STUB, RELEASE, STOP_BUFFER, DESTROY, POST, WAIT, CLOSE, OTHER_POST, OTHER_WAIT, OTHER_CLOSE, AGG_STOP, AGG_QUERY = (
    STOP + 0x100 + i * 0x100 for i in range(14))
POST_SLOT, WAIT_SLOT, CLOSE_SLOT, KILL_SLOT = 0x466210, 0x46611C, 0x4660CC, 0x466214
CLEANUP, CLEANUP_FULL, MIDI_STOP, MIDI_FULL, AGGREGATE = (CANDIDATE + i * 0x2000 for i in range(5))
SECONDARY, PENDING, AUXILIARY = MANAGER + 8, MANAGER + 0x5230, MANAGER + 0x1EC0
IMAGE, STREAM_SLOT, OWNER_SLOT = MANAGER + 0x1F84, MANAGER + 0x608, MANAGER + 0x610
THREAD_ID, THREAD, MIDI_SLOT, COMPANION = (MANAGER + offset for offset in (0x614, 0x618, 0x5208, 0x520C))


@dataclass(frozen=True)
class Case:
    operation: str = "cleanup"
    integrated: bool = False
    owner: bool = True
    device: bool = True
    stream: int = STREAM
    midi: bool = True
    thread: bool = True
    companion: int = 0xCC001122
    population: str = "edges"
    loaded: bool = True
    wait_results: tuple = (0,)
    mutations: tuple = ()  # (event kind, zero-based occurrence, ((address, value), ...))
    aggregate_entries: bool = True
    aggregate_count: int = 3


def compile_candidates(directory, config, code_base=CANDIDATE):
    cleanup, cleanup_full, midi_stop, midi_full, aggregate_address = (code_base + i * 0x2000 for i in range(5))
    bindings = {"_g_sound_kill_timer": KILL_SLOT, "_g_sound_post_thread_message": POST_SLOT,
                "_g_sound_wait_for_object": WAIT_SLOT, "_g_sound_close_handle": CLOSE_SLOT,
                "_entry_free_00452422": 0x452422, "_owner_free_004524a1": 0x4524A1,
                "_Sound_StopMusicWorker_0043dab0@4": MIDI_STUB,
                "@Sound_AggregateInterfaces_0044d550@4": AGG_STUB}
    modules = {}
    for name, base, linked in (("sound_cleanup", cleanup, cleanup_full), ("sound_midi_stop", midi_stop, midi_full)):
        obj = directory / (name + ".obj")
        subprocess.run([
            "clang++", "--target=i686-pc-windows-msvc", "-std=c++03", "-O2", "-mno-sse", "-mno-sse2",
            "-fno-exceptions", "-fno-rtti", "-fno-stack-protector", "-fno-builtin", "-c",
            str(ROOT / "matching2/reference/semantic_candidates" / (name + ".cpp")), "-o", str(obj)],
            check=True, timeout=60)
        modules[base] = load_module(obj, base, bindings)
        linked_bindings = dict(bindings)
        linked_bindings.update({"_Sound_StopMusicWorker_0043dab0@4": midi_full,
                                "@Sound_AggregateInterfaces_0044d550@4": aggregate_address})
        modules[linked] = load_module(obj, linked, linked_bindings)
    obj = directory / "aggregate.obj"
    subprocess.run([
        "clang++", "--target=i686-pc-windows-msvc", "-std=c++03", "-O2", "-mno-sse", "-mno-sse2",
        "-fno-exceptions", "-fno-rtti", "-fno-stack-protector", "-fno-builtin", "-ffunction-sections",
        "-c", str(ROOT / "matching2/msvc/src/game/platform_aggregate_interfaces_0044d550.cpp"),
        "-o", str(obj)], check=True, timeout=60)
    aggregate = load_candidate(obj, config, "?Aggregate@PlatformInterfaceState_0044D550@@QAEHXZ",
                               code_address=aggregate_address)
    return modules, aggregate


def execute(image, compiled, case):
    modules, aggregate = compiled if compiled else ({}, b"")
    uc = Uc(UC_ARCH_X86, UC_MODE_32)
    uc.mem_map(0x400000, 0x100000)
    for section in image.sections:
        uc.mem_write(section["address"], image.read(section["address"], section["raw_size"]))
    for address in (CANDIDATE, STACK, STOP, STATE, DATA):
        uc.mem_map(address, 0x10000)
    for module in modules.values():
        uc.mem_write(module.base, module.data)
    if aggregate:
        uc.mem_write(AGGREGATE, aggregate)

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

    def populated(index, count):
        return (case.population == "all" or
                (case.population == "edges" and index in (0, 1, count // 2, count - 1)) or
                (case.population.startswith("seed") and randomizer.randrange(4) == 0))

    randomizer = random.Random(int(case.population[4:]) if case.population.startswith("seed") else 0)
    uc.mem_write(STATE, b"\xA5" * 0x10000)
    uc.mem_write(DATA, bytes(range(256)) * 256)
    words(MANAGER, DEVICE)
    words(MANAGER + 0x60C, 0x10203040)
    words(STREAM_SLOT, case.stream)
    words(OWNER_SLOT, OWNER if case.owner else 0)
    words(OWNER, DEVICE if case.device else 0)
    words(ALT_OWNER, ALT_DEVICE)
    words(THREAD_ID, 0x1234)
    words(THREAD, 0x12345678 if case.thread else 0)
    words(MIDI_SLOT, MIDI if case.midi else 0)
    words(COMPANION, case.companion)
    words(IMAGE, DATA + 0x5000 if case.loaded else 0)
    for index in range(256):
        pointer = DATA + index * 16
        words(pointer, BUFFER_TABLE)
        words(SECONDARY + index * 4, pointer if populated(index, 256) else 0)
    for count, table, base in ((37, PENDING, DATA + 0x6000), (16, AUXILIARY, DATA + 0x8000)):
        for index in range(count):
            words(table + index * 4, base + index * 64 if populated(index, count) else 0)
    for pointer in (DEVICE, ALT_DEVICE, STREAM, ALT_STREAM):
        words(pointer, BUFFER_TABLE)
    words(BUFFER_TABLE + 8, RELEASE)
    words(BUFFER_TABLE + 72, STOP_BUFFER)
    words(MIDI_TABLE, DESTROY)
    words(AGG_TABLE + 72, AGG_STOP)
    words(AGG_TABLE + 52, AGG_QUERY)
    for pointer, table in ((MIDI, ENTRIES), (ALT_MIDI, ALT_ENTRIES)):
        words(pointer, MIDI_TABLE, table if case.aggregate_entries else 0)
        words(pointer + 0x10, case.aggregate_count)
        words(pointer + 0x1C, 0x11223344)
        words(pointer + 0x30, 0x55667788)
        for index in range(5):
            entry = DATA + 0x4000 + index * 16 + (0x100 if pointer == ALT_MIDI else 0)
            words(table + index * 4, entry)
            words(entry, AGG_TABLE)
    for slot, pointer in ((POST_SLOT, POST), (WAIT_SLOT, WAIT), (CLOSE_SLOT, CLOSE), (KILL_SLOT, KILL)):
        words(slot, pointer)
    events, faults, occurrences = [], [], {}
    waits = 0

    def state():
        fields = (MANAGER, IMAGE, STREAM_SLOT, OWNER_SLOT, MIDI_SLOT, THREAD_ID, THREAD, COMPANION,
                  SECONDARY, SECONDARY + 128 * 4, SECONDARY + 255 * 4,
                  PENDING, PENDING + 4, PENDING + 36 * 4, AUXILIARY, AUXILIARY + 15 * 4)
        return tuple(read_words(pointer)[0] for pointer in fields)

    def event(kind, *values):
        events.append((kind, *values, state()))
        occurrence = occurrences.get(kind, 0)
        occurrences[kind] = occurrence + 1
        for stage, index, writes in case.mutations:
            if stage == kind and index == occurrence:
                for address, value in writes:
                    words(address, value)

    def hook(machine, address, size, context):
        nonlocal waits
        if address in (0x452422, 0x4524A1):
            pointer, = args(1)
            event("free" if address == 0x452422 else "owner-free", pointer)
            finish(0xBAD00001)
        elif address == RELEASE:
            pointer, = args(1)
            event("release", pointer)
            finish(0xBAD00002, 4)
        elif address == KILL:
            window, timer = args(2)
            event("kill", window, timer)
            assert timer == 1
            finish(0, 8)
        elif address in (MIDI_STUB, MIDI_FULL, 0x43DAB0):
            manager = args(1)[0] if address != 0x43DAB0 else uc.reg_read(UC_X86_REG_ESI)
            assert manager == MANAGER
            event("midi", manager)
            if not case.integrated and case.operation == "cleanup":
                finish(0xBAD00003, 4 if address == MIDI_STUB else 0)
        elif address in (AGG_STUB, AGGREGATE, 0x44D550):
            pointer = uc.reg_read(UC_X86_REG_EDI if address == 0x44D550 else UC_X86_REG_ECX)
            event("aggregate", pointer)
            if not case.integrated:
                finish(0x80004005)
        elif address in (POST, OTHER_POST):
            tid, message, wparam, lparam = args(4)
            event("post" if address == POST else "other-post", tid, message, wparam, lparam)
            assert (message, wparam, lparam) == (0x12, 0, 0)
            finish(0, 16)
        elif address in (WAIT, OTHER_WAIT):
            handle, milliseconds = args(2)
            assert milliseconds == 0x100 and waits < len(case.wait_results)
            result = case.wait_results[waits]
            event("wait" if address == WAIT else "other-wait", handle, milliseconds, result)
            waits += 1
            finish(result, 8)
        elif address in (CLOSE, OTHER_CLOSE):
            handle, = args(1)
            event("close" if address == CLOSE else "other-close", handle)
            finish(0, 4)
        elif address == STOP_BUFFER:
            pointer, = args(1)
            event("stream-stop", pointer)
            assert read_words(MANAGER)[0] == 0
            finish(0x80004005, 4)
        elif address == DESTROY:
            pointer = uc.reg_read(UC_X86_REG_ECX)
            flags, = args(1)
            event("destroy", pointer, flags)
            assert flags == 1
            finish(0xBAD00004, 4)
        elif address == AGG_STOP:
            pointer, = args(1)
            event("aggregate-stop", pointer)
            finish(0x80001000 | (pointer & 0xFF), 4)
        elif address == AGG_QUERY:
            pointer, zero = args(2)
            event("aggregate-query", pointer, zero)
            assert zero == 0
            finish(0x20 | (pointer & 0xFF), 8)
        else:
            raise AssertionError(hex(address))

    def fault(machine, kind, address, size, value, context):
        faults.append((kind, address, size, value))
        return False

    for address in (0x452422, 0x4524A1, RELEASE, KILL, MIDI_STUB, MIDI_FULL, 0x43DAB0,
                    AGG_STUB, AGGREGATE, 0x44D550, POST, OTHER_POST, WAIT, OTHER_WAIT,
                    CLOSE, OTHER_CLOSE, STOP_BUFFER, DESTROY, AGG_STOP, AGG_QUERY):
        uc.hook_add(UC_HOOK_CODE, hook, begin=address, end=address)
    uc.hook_add(UC_HOOK_MEM_INVALID, fault)
    sp = STACK + 0x8000
    words(sp, STOP, MANAGER)
    uc.reg_write(UC_X86_REG_ESP, sp)
    preserved = dict(PRESERVED)
    if modules:
        if case.operation == "cleanup":
            module = modules[CLEANUP_FULL if case.integrated else CLEANUP]
            entry = module.symbols["_Sound_Cleanup_0043d120@4"]
        else:
            module = modules[MIDI_FULL if case.integrated else MIDI_STOP]
            entry = module.symbols["_Sound_StopMusicWorker_0043dab0@4"]
        expected_sp = sp + 8
    else:
        if case.operation == "cleanup":
            entry = 0x43D120
            uc.reg_write(UC_X86_REG_EAX, MANAGER)
        else:
            entry = 0x43DAB0
            preserved[UC_X86_REG_ESI] = MANAGER
        expected_sp = sp + 4
    for register, value in preserved.items():
        uc.reg_write(register, value)
    # Observe candidate MIDI entry consistently in standalone runs too.
    if case.operation == "midi" and modules and not case.integrated:
        uc.hook_add(UC_HOOK_CODE, lambda m, a, s, c: event("midi", args(1)[0]), begin=entry, end=entry)
    try:
        uc.emu_start(entry, STOP, count=2000000)
    except UcError:
        if not faults:
            raise
    if not faults:
        assert uc.reg_read(UC_X86_REG_EIP) == STOP, "instruction budget exhausted"
        assert uc.reg_read(UC_X86_REG_ESP) == expected_sp
        assert all(uc.reg_read(register) == value for register, value in preserved.items())
    return {"result": uc.reg_read(UC_X86_REG_EAX) if case.operation == "cleanup" and not faults else None,
            "events": events, "faults": faults, "waits": waits,
            "state": bytes(uc.mem_read(STATE, 0x10000)), "data": bytes(uc.mem_read(DATA, 0x10000)),
            "imports": tuple(read_words(slot)[0] for slot in (POST_SLOT, WAIT_SLOT, CLOSE_SLOT, KILL_SLOT))}


def mutation_case(stage, writes, occurrence=0, **kwargs):
    return Case(mutations=((stage, occurrence, tuple(writes)),), **kwargs)


def cases(integrated=False):
    if not integrated:
        for owner, device, stream, midi, thread, population in product((False, True), (False, True),
                (0, STREAM), (False, True), (False, True), ("none", "edges", "all")):
            yield Case(owner=owner, device=device, stream=stream, midi=midi, thread=thread, population=population)
        yield Case(loaded=False, population="none", owner=False)
        for seed in range(24):
            yield Case(population="seed" + str(seed), owner=bool(seed & 1))
        for stage, writes in (
            ("free", ((IMAGE, DATA + 0x5004), (SECONDARY + 128 * 4, ALT_STREAM))),
            ("release", ((SECONDARY + 128 * 4, ALT_STREAM), (SECONDARY, ALT_STREAM))),
            ("release", ((OWNER_SLOT, 0),)),
            ("release", ((SECONDARY + 129 * 4, ALT_STREAM), (PENDING + 4, DATA + 0x9000))),
            ("kill", ((STREAM_SLOT, ALT_STREAM), (OWNER_SLOT, ALT_OWNER))),
            ("kill", ((OWNER_SLOT, 0),)),
            ("midi", ((MIDI_SLOT, 0), (STREAM_SLOT, ALT_STREAM))),
            ("midi", ((MIDI_SLOT, ALT_MIDI), (STREAM_SLOT, 0))),
            ("stream-stop", ((STREAM_SLOT, ALT_STREAM), (MIDI_SLOT, ALT_MIDI))),
            ("stream-stop", ((STREAM_SLOT, 0),)),
            ("destroy", ((MIDI_SLOT, ALT_MIDI), (OWNER_SLOT, ALT_OWNER))),
            ("owner-free", ((OWNER_SLOT, ALT_OWNER), (AUXILIARY, DATA + 0x9000))),
        ):
            yield mutation_case(stage, writes)
        # No other releases before the owner's Release, so its callback can
        # replace the manager's owner cell while the old cell remains cached.
        yield Case(population="none", midi=False, mutations=(
            ("stream-stop", 0, ((STREAM_SLOT, 0),)),
            ("release", 0, ((OWNER_SLOT, ALT_OWNER), (OWNER, ALT_DEVICE)))))
        yield Case(mutations=(("free", 1, ((PENDING, DATA + 0x9000), (PENDING + 4, DATA + 0x9040))),))
        yield Case(mutations=(("free", 5, ((AUXILIARY, DATA + 0x9000), (AUXILIARY + 4, DATA + 0x9040))),))
        yield mutation_case("release", ((STREAM_SLOT, ALT_STREAM), (MIDI_SLOT, ALT_MIDI),
                                        (OWNER_SLOT, ALT_OWNER)), population="none", midi=False)

    for midi, thread, companion, waits in product((False, True), (False, True), (0, 0xCC001122),
            ((0,), (258, 0), (0xFFFFFFFF, 0), (0x80, 0), (1, 258, 0xFFFFFFFF, 0))):
        yield Case(operation="midi", integrated=integrated, midi=midi, thread=thread,
                   companion=companion, wait_results=waits)
    midi_mutations = (
        ("aggregate", ((MIDI_SLOT, 0),)),
        ("aggregate", ((MIDI_SLOT, ALT_MIDI), (THREAD, 0))),
        ("aggregate", ((THREAD_ID, 0x4321), (THREAD, 0x87654321))),
        ("post", ((POST_SLOT, OTHER_POST),)),
        ("post", ((WAIT_SLOT, OTHER_WAIT), (THREAD, 0))),
        ("wait", ((WAIT_SLOT, OTHER_WAIT), (THREAD_ID, 0x4321), (THREAD, 0x87654321))),
        ("wait", ((MIDI_SLOT, ALT_MIDI), (CLOSE_SLOT, OTHER_CLOSE))),
        ("close", ((CLOSE_SLOT, OTHER_CLOSE), (COMPANION, 0x112200CC), (THREAD, 0x87654321))),
        ("close", ((MIDI_SLOT, 0),)),
        ("destroy", ((MIDI_SLOT, ALT_MIDI),)),
    )
    for stage, writes in midi_mutations:
        yield mutation_case(stage, writes, operation="midi", integrated=integrated,
                            wait_results=(258, 0xFFFFFFFF, 0))
    if integrated:
        for output, thread, stream, entries, count in product((False, True), (False, True),
                (0, STREAM), (False, True), (0, 1, 3)):
            yield Case(integrated=True, midi=output, thread=thread, stream=stream,
                       aggregate_entries=entries, aggregate_count=count, wait_results=(258, 0))
        for stage, writes in (
            ("aggregate-stop", ((MIDI + 4, ALT_ENTRIES),)),
            ("aggregate-query", ((MIDI + 0x10, 1),)),
            ("aggregate-query", ((MIDI + 0x10, 5),)),
            ("aggregate-query", ((MIDI_SLOT, ALT_MIDI),)),
            ("close", ((STREAM_SLOT, ALT_STREAM), (OWNER_SLOT, ALT_OWNER))),
            ("destroy", ((MIDI_SLOT, ALT_MIDI),)),
            ("stream-stop", ((MIDI_SLOT, ALT_MIDI),)),
            ("release", ((OWNER_SLOT, 0),)),
        ):
            yield mutation_case(stage, writes, integrated=True, wait_results=(258, 0))


def verify(case, result):
    events = result["events"]
    if not result["faults"] and case.operation == "cleanup":
        assert result["result"] == 0
    waits = [event for event in events if event[0] in ("wait", "other-wait")]
    if waits:
        assert tuple(event[3] for event in waits) == case.wait_results
        closes = [event for event in events if event[0] in ("close", "other-close")]
        assert len(closes) == 2 and closes[0][0] == closes[1][0], "Close import is cached"
        assert len({event[0] for event in waits}) == 1, "Wait import is cached after first Post"
        posts = [event for event in events if event[0] in ("post", "other-post")]
        assert len(posts) == len(waits) and len({event[0] for event in posts}) == 1
    if not case.mutations and case.operation == "cleanup":
        releases = [event[1] for event in events if event[0] == "release" and DATA <= event[1] < DATA + 0x1000]
        order = [index for i in range(128) for index in (i + 128, i)]
        assert releases == sorted(releases, key=lambda pointer: order.index((pointer - DATA) // 16))
        if not case.owner:
            assert not any(event[0] in ("kill", "midi", "stream-stop", "owner-free") for event in events)
    if case.operation == "midi" and not case.midi:
        assert [event[0] for event in events] == ["midi"]


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
    with tempfile.TemporaryDirectory(prefix="th10-sound-shutdown-") as temporary:
        compiled = compile_candidates(Path(temporary), config)
        counts, faults = [], []
        for integrated in (False, True):
            comparisons = fault_count = 0
            for index, case in enumerate(cases(integrated)):
                expected, actual = execute(image, None, case), execute(image, compiled, case)
                differences = tuple(key for key in expected if expected[key] != actual[key])
                assert not differences, (integrated, index, case, differences,
                                         expected["events"], actual["events"], expected["faults"], actual["faults"])
                verify(case, actual)
                comparisons += 1
                fault_count += bool(actual["faults"])
            counts.append(comparisons)
            faults.append(fault_count)
        print(f"PASS: {counts[0]} individual sound-cleanup/MIDI-stop comparisons ({faults[0]} matching faults), "
              f"{counts[1]} integrated comparisons ({faults[1]} matching faults). "
              f"Candidate modules: cleanup {len(compiled[0][CLEANUP].data)}, MIDI stop {len(compiled[0][MIDI_STOP].data)}; "
              f"maintained aggregate {len(compiled[1])} bytes. Native MSVC bytes and Windows dispatch remain unverified.")


if __name__ == "__main__":
    main()
