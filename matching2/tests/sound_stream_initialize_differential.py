#!/usr/bin/env python3
"""Compare stream initializers and notification-buffer recreation with retail.

Allocator and DirectSound creation/query/notification calls are scripted. The
integrated initializer and lifecycle cases execute actual refill, cursor, and
restart/restoration bodies. Ordered ownership events and full memory are checked.
"""
import argparse
from dataclasses import dataclass
from itertools import product
from pathlib import Path
import struct
import subprocess
import tempfile

from unicorn import UC_HOOK_CODE
from unicorn.x86_const import UC_X86_REG_EAX, UC_X86_REG_ESI, UC_X86_REG_EDI
from sound_stream_fill_differential import (
    Case as FillCase, Execution as FillExecution, compile_candidates as compile_fill,
    FILL_SYMBOL, BINDINGS, STREAM, BUFFER, TABLE, ALT_TABLE, ALT_CURSOR,
    ROOT, CANDIDATE, STOP, STATE, OUTPUT, CURSOR, RECORD, ALT_RECORD, SOURCE, DESTINATION,
    COMMON, difference, PEImage, load_manifest, load_oracle)
from coff_module import load_module

ARRAY, ALT_ARRAY, SOURCE_ARRAY, ALT_BUFFER, THIRD = (STATE + offset for offset in (0x1800, 0x1900, 0x1A00, 0x1400, 0x1500))
OWNER, ALT_OWNER, DEVICE, DEVICE_TABLE = (STATE + offset for offset in (0x1B00, 0x1B10, 0x1C00, 0x1D00))
NOTIFY, ALT_NOTIFY, NOTIFY_TABLE = STATE + 0x1E00, STATE + 0x1E20, STATE + 0x1F00
NEW_BUFFERS, HEAP = STATE + 0x2000, STATE + 0x4000
POSITION, FILL, RELEASE, CREATE, QUERY, SET_NOTICES, RELEASE_NOTIFY = (STOP + 0x100 * i for i in range(12, 19))
ALLOCATE, FREE, IID = 0x452493, 0x4524A1, 0x46743C
SYMBOLS = {"array": "_SoundStream_InitializeArray_0044ce80@20", "single": "_SoundStream_InitializeSingle_0044d6a0@20",
           "recreate": "_SoundStream_RecreateBuffers_0044cf20@4", "restart": "_SoundStream_Restart_0044dad0@4"}
RETAIL = {"array": 0x44CE80, "single": 0x44D6A0, "recreate": 0x44CF20, "restart": 0x44DAD0}


@dataclass(frozen=True)
class Case(FillCase):
    operation: str = "array"
    source: int = SOURCE_ARRAY
    entries: tuple = (BUFFER, ALT_BUFFER)
    count: int = 2
    initial_array: int = ARRAY
    reader: int = CURSOR
    segment_bytes: int = 7
    notification_event: int = 0x12345678
    owner: int = OWNER
    device: int = DEVICE
    fail_allocate: int = 0
    allocations: tuple = ()
    fill_result: int = 0
    position_result: int = 0
    create_results: tuple = (0,)
    query_results: tuple = (0,)
    notice_results: tuple = (0,)
    create_writes: bool = True
    query_writes: bool = True
    query_value: int = NOTIFY
    notify_after_set: object = None
    actions: tuple = ()
    restore_results: tuple = (0, 0, 0, 0)


def compile_candidates(directory):
    fill = compile_fill(directory)
    bindings = dict(BINDINGS, **{"_SoundBuffer_Allocate": ALLOCATE, "_SoundBuffer_Free": FREE,
        "_g_sound_base_methods": 0x4705D8, "_g_sound_streaming_methods": 0x4705D4,
        "_g_wave_notification_iid": IID, FILL_SYMBOL: FILL})
    modules = {}
    for name, source, address in (("initializers", "sound_stream_initialize.cpp", CANDIDATE + 0x1000),
                                  ("recreate", "sound_stream_recreate.cpp", CANDIDATE + 0x3000)):
        obj = directory / (name + ".obj")
        subprocess.run([*COMMON, "-c", str(ROOT / "matching2/reference/semantic_candidates" / source),
                        "-o", str(obj)], check=True, timeout=60)
        modules[name] = load_module(obj, address, bindings)
        if name == "initializers":
            modules[name + "_full"] = load_module(obj, CANDIDATE + 0x2000,
                dict(bindings, **{FILL_SYMBOL: fill[1].symbols[FILL_SYMBOL]}))
    obj = directory / "restore.obj"
    subprocess.run([*COMMON, "-fno-delete-null-pointer-checks", "-c",
                    str(ROOT / "matching2/msvc/src/game/platform_run_interface_0044d300.cpp"), "-o", str(obj)], check=True, timeout=60)
    modules["restore"] = load_module(obj, CANDIDATE + 0x5000, {"__imp__Sleep@4": 0x4660AC})
    obj = directory / "restart.obj"
    subprocess.run([*COMMON, "-c", str(ROOT / "matching2/reference/semantic_candidates/sound_stream_restart.cpp"),
                    "-o", str(obj)], check=True, timeout=60)
    bindings.update({FILL_SYMBOL: fill[1].symbols[FILL_SYMBOL],
                     "?RestoreIfLost@WaveSecondaryBuffer@@QAEHPAI@Z": modules["restore"].symbols["?Run@PlatformD300Entry@@QAEHPAI@Z"]})
    modules["restart"] = load_module(obj, CANDIDATE + 0x6000, bindings)
    return fill, modules


class Execution(FillExecution):
    def __init__(self, image, compiled=None):
        fill, modules = compiled if compiled else (None, {})
        super().__init__(image, fill, {module.base: module.data for module in modules.values()})
        self.modules = modules
        self.allocate_calls = self.create_calls = self.query_calls = self.notice_calls = 0
        self.heap_next = HEAP
        self.allocated, self.freed = [], []
        self.query_output = None
        self.fill_entries = {0x44D110, FILL}
        if fill:
            self.fill_entries.add(fill[1].symbols[FILL_SYMBOL])

    def initialize(self, case):
        super().initialize(case)
        self.words(STREAM + 4, case.initial_array, 0x11223344, ALT_CURSOR, case.count)
        self.words(STREAM + 0x30, 0xABCDEF01)
        self.words(STREAM + 0x34, 36, 0x18188, case.buffer_bytes, 0, RECORD + 0x20, 1, 2, 3, 4)
        self.words(STREAM + 0x58, case.owner, 1, 2, 3, 4, case.segment_bytes, case.notification_event, 0xABCDE123)
        self.words(ARRAY, *case.entries)
        self.words(SOURCE_ARRAY, *case.entries)
        self.words(ALT_ARRAY, THIRD, ALT_BUFFER, BUFFER, THIRD)
        self.words(OWNER, case.device)
        self.words(ALT_OWNER, DEVICE)
        self.words(DEVICE, DEVICE_TABLE)
        self.words(DEVICE_TABLE + 12, CREATE)
        for buffer in (ALT_BUFFER, THIRD, *(NEW_BUFFERS + i * 16 for i in range(16))):
            self.words(buffer, TABLE)
        for table in (TABLE, ALT_TABLE):
            for offset, address in ((0, QUERY), (8, RELEASE), (52, POSITION)):
                self.words(table + offset, address)
        for notify in (NOTIFY, ALT_NOTIFY):
            self.words(notify, NOTIFY_TABLE)
        self.words(NOTIFY_TABLE + 8, RELEASE_NOTIFY, SET_NOTICES)

    def cursor_state(self):
        return super().cursor_state(), self.read_words(STREAM + 0x34, 17)

    def hook(self, machine, address, size, context):
        case = self.case
        if address == ALLOCATE:
            requested, = self.args(1)
            self.allocate_calls += 1
            index = self.allocate_calls
            self.event("allocate", requested, index)
            override = case.allocations[index - 1] if index <= len(case.allocations) else None
            if case.fail_allocate == index or requested > 0x4000:
                result = 0
            elif override is not None:
                result = override
            else:
                result = self.heap_next + 16
                self.heap_next += ((max(requested, 4) + 15) & ~15) + 32
                assert self.heap_next < STATE + 0x10000
            self.allocated.append((result, requested))
            self.finish(result)
        elif address == FREE:
            pointer, = self.args(1)
            self.event("free", pointer)
            self.freed.append(pointer)
            self.finish(0xABCD)
        elif address == RELEASE:
            buffer, = self.args(1)
            self.event("release-buffer", buffer)
            self.finish(17, 4)
        elif address == CREATE:
            device, description, out, outer = self.args(4)
            self.event("create", device, description, out, outer, bytes(self.uc.mem_read(description, 36)))
            assert outer == 0
            index = self.create_calls
            self.create_calls += 1
            if case.create_writes:
                assert out, "a null output must use the scripted error path"
                self.words(out, NEW_BUFFERS + index * 16)
            self.finish(self.selected(case.create_results, index), 16)
        elif address == QUERY:
            buffer, iid, out = self.args(3)
            self.query_output = out
            self.event("query", buffer, iid, self.read_words(out)[0])
            assert iid == IID
            index = self.query_calls
            self.query_calls += 1
            if case.query_writes:
                self.words(out, case.query_value)
            self.finish(self.selected(case.query_results, index), 12)
        elif address == SET_NOTICES:
            notify, count, positions = self.args(3)
            self.event("set-notices", notify, count, positions, bytes(self.uc.mem_read(positions, count * 8)))
            assert count == 16
            index = self.notice_calls
            self.notice_calls += 1
            if case.notify_after_set is not None:
                self.words(self.query_output, case.notify_after_set)
            self.finish(self.selected(case.notice_results, index), 12)
        elif address == RELEASE_NOTIFY:
            notify, = self.args(1)
            self.event("release-notify", notify)
            self.finish(9, 4)
        elif address == POSITION:
            buffer, position = self.args(2)
            self.event("position", buffer, position)
            assert position == 0
            self.finish(case.position_result, 8)
        elif address in self.fill_entries:
            if address == 0x44D110:
                stream = self.uc.reg_read(UC_X86_REG_EAX)
                buffer, repeat = self.args(2)
            else:
                stream, buffer, repeat = self.args(3)
            self.event("fill", stream, buffer, repeat)
            assert repeat == 0
            if not case.integrated:
                self.finish(case.fill_result, 8 if address == 0x44D110 else 12)
        else:
            super().hook(machine, address, size, context)

    def execute(self, case):
        self.initialize(case)
        self.install_hooks()
        for address in (ALLOCATE, FREE, RELEASE, CREATE, QUERY, SET_NOTICES, RELEASE_NOTIFY, POSITION, *self.fill_entries):
            self.uc.hook_add(UC_HOOK_CODE, self.hook, begin=address, end=address)
        for operation in case.actions or (case.operation,):
            if self.modules:
                module = self.modules[operation if operation in ("recreate", "restart") else
                                      "initializers_full" if case.integrated else "initializers"]
                args = ((case.stream, case.source, case.count, case.buffer_bytes, case.reader) if operation == "array" else
                        (case.stream, case.buffer, case.buffer_bytes, case.reader, case.segment_bytes) if operation == "single" else (case.stream,))
                observed = self.run(module.symbols[SYMBOLS[operation]], args)
            elif operation == "array":
                observed = self.run(RETAIL[operation], (case.buffer_bytes, case.reader),
                    {UC_X86_REG_ESI: case.stream, UC_X86_REG_EAX: case.source, UC_X86_REG_EDI: case.count})
            elif operation == "single":
                observed = self.run(RETAIL[operation], (case.buffer, case.buffer_bytes, case.reader, case.segment_bytes),
                    {UC_X86_REG_ESI: case.stream})
            else:
                observed = self.run(RETAIL[operation], (), {UC_X86_REG_EDI if operation == "restart" else UC_X86_REG_ESI: case.stream})
            if self.faults:
                break
            self.event("returned", operation, observed["result"])
        observed.update(allocated=self.allocated, freed=self.freed)
        return observed


def cases():
    for operation, count, fill_result, position_result in product(("array", "single"), (0, 1, 2, 3), (0, 1, 0x80004005), (0, 0x80070057)):
        yield Case(operation=operation, count=count, entries=(BUFFER, ALT_BUFFER, THIRD), fill_result=fill_result, position_result=position_result)
    for operation, kwargs in product(("array", "single"),
            ({"fail_allocate": 1}, {"stream": 0}, {"buffer": 0, "entries": (0, ALT_BUFFER)},
             {"source": 0}, {"reader": 0}, {"allocations": (STREAM + 4,)},
             {"allocations": (SOURCE_ARRAY + 4,), "count": 3, "entries": (BUFFER, ALT_BUFFER, THIRD)})):
        yield Case(operation=operation, **kwargs)
    yield Case(count=0, fail_allocate=1)
    yield Case(source=STREAM + 4, count=1)
    yield Case(count=0x40000001, source=0)
    for operation, trigger, writes in product(("array", "single"), ("allocate", "fill", "position:1"),
            (((STREAM + 4, ALT_ARRAY),), ((STREAM + 0x10, 0), (STREAM + 0x30, 99)), ((STREAM + 0xC, ALT_CURSOR),))):
        yield Case(operation=operation, mutations=((trigger, writes),))
    for count, entries, segment in product((0, 1, 2), ((BUFFER, ALT_BUFFER), (0, ALT_BUFFER), (0, 0)), (0, 1, 7, 0x80000001, 0xFFFFFFFF)):
        yield Case(operation="recreate", count=count, entries=entries, segment_bytes=segment)
    for count, index in product((1, 2, 3), (1, 2, 3, 4)):
        yield Case(operation="recreate", count=count, entries=(BUFFER, ALT_BUFFER, THIRD), fail_allocate=index,
                   create_writes=index != 1, create_results=(0x8007000E,) if index == 1 else (0,))
    for create, query, notice, notify in product((0, 1, 0x80004005), (0, 1, 0x80070057), (0, 1, 0x80004005), (0, NOTIFY)):
        yield Case(operation="recreate", count=1, create_results=(create,), query_results=(query,), notice_results=(notice,), query_value=notify)
    for kwargs in ({"initial_array": 0, "count": 0}, {"initial_array": 0}, {"owner": 0}, {"device": 0},
                   {"create_writes": False}, {"query_writes": False}, {"notify_after_set": 0},
                   {"notify_after_set": ALT_NOTIFY}, {"notice_results": (0, 0x80004005)},
                   {"query_results": (0, 0x80004005)}, {"create_results": (0, 0x80004005)},
                   {"allocations": (None, STREAM + 0x60)}):
        yield Case(operation="recreate", **kwargs)
    for trigger, writes in (
            ("release-buffer:1", ((STREAM + 4, ALT_ARRAY),)),
            ("release-buffer:1", ((STREAM + 0x10, 1),)),
            ("free:1", ((STREAM + 4, ALT_ARRAY), (STREAM + 0x10, 1))),
            ("allocate:1", ((STREAM + 0x10, 1),)),
            ("create:1", ((STREAM + 4, ALT_ARRAY),)),
            ("query:1", ((STREAM + 0x6C, 13), (STREAM + 0x70, 0xAABBCCDD))),
            ("set-notices:1", ((STREAM + 0x10, 1),)),
            ("free:2", ((STREAM + 0x58, ALT_OWNER),)),
            ("release-notify:1", ((STREAM + 0x10, 0),))):
        yield Case(operation="recreate", mutations=((trigger, writes),))
    for operation, buffered, bits, status in product(("array", "single"), (0, 1), (8, 16), (0, 2)):
        yield Case(operation=operation, integrated=True, buffered=buffered, bits=bits, status=status)
    for operation, kwargs in product(("array", "single"),
            ({"reader": 0}, {"buffered": 0, "file": 0}, {"status_result": 0x80004005},
             {"lock_result": 0x80070057}, {"count": 0}, {"destination": OUTPUT + 0xFFFE})):
        yield Case(operation=operation, integrated=True, **kwargs)
    for buffered, bits, status in product((0, 1), (8, 16), (0, 2)):
        yield Case(integrated=True, actions=("single", "recreate", "restart"), buffered=buffered, bits=bits,
                   status=status, restore_results=(0,) * 8)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--oracle", type=Path, default=ROOT / "matching2/build/oracle/th10.exe")
    options = parser.parse_args()
    config = load_manifest(ROOT / "matching2/msvc/regions.json")
    load_oracle(options.oracle, config)
    image = PEImage(options.oracle.read_bytes())
    with tempfile.TemporaryDirectory(prefix="th10-stream-initialize-") as temporary:
        compiled = compile_candidates(Path(temporary))
        totals, faults, notices = [0, 0], [0, 0], 0
        for case in cases():
            expected = Execution(image).execute(case)
            actual = Execution(image, compiled).execute(case)
            assert actual == expected, (case, difference(expected, actual))
            index = int(case.integrated)
            totals[index] += 1
            faults[index] += bool(expected["faults"])
            notices += sum(event[0] == "set-notices" for event in expected["events"])
        observed = Execution(image, compiled).execute(Case(operation="recreate", count=1, segment_bytes=7))
        event, = (event for event in observed["events"] if event[0] == "set-notices")
        assert struct.unpack("<32I", event[4]) == tuple(value for i in range(16) for value in (7 * (i + 1) - 1, 0x12345678))
        print(f"PASS: {totals[0]} initializer/recreation unit comparisons ({faults[0]} faults), "
              f"{totals[1]} with executing refill/cursors/restart ({faults[1]} faults), "
              f"{notices} notification installations and independent notification-table check. "
              f"Clang initializer module/recreation: {len(compiled[1]['initializers'].data)}/{len(compiled[1]['recreate'].data)} bytes. "
              "Native MSVC matching remains unverified.")


if __name__ == "__main__":
    main()
