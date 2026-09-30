#!/usr/bin/env python3
"""Compare the memory-backed stream factory, including executing initialization.

The retail exception frame uses a real FS segment in the fixture, leaving NULL
unmapped. Clang asynchronous exceptions retain the cleanup state across faulting
publication stores; synchronous-state differences have a separate unwind test.
Normal execution does not exercise Windows exception dispatch.
"""
import argparse
from dataclasses import dataclass
from itertools import product
from pathlib import Path
import struct
import subprocess
import tempfile

from unicorn import UC_HOOK_CODE
from unicorn.x86_const import UC_X86_REG_EAX, UC_X86_REG_ECX, UC_X86_REG_EDX, UC_X86_REG_ESI
from sound_stream_initialize_differential import (
    Case as InitializeCase, Execution as InitializeExecution, compile_candidates as compile_initializers,
    SYMBOLS, ALLOCATE, FREE, IID, CREATE, QUERY, SET_NOTICES, OWNER, ALT_OWNER, DEVICE, NOTIFY, ALT_NOTIFY,
    NEW_BUFFERS, STREAM, RECORD, ALT_RECORD, SOURCE, DESTINATION, ROOT, CANDIDATE, STOP, STATE, OUTPUT,
    COMMON, difference, PEImage, load_manifest, load_oracle)
from coff_module import load_module
from x86_seh import install as install_seh, exception_list, INITIAL_EXCEPTION_LIST

PUBLISHED = STATE + 0x3000
CONSTRUCT = STOP + 0x1300
FRAME_HANDLER = STOP + 0x3000
FACTORY_SYMBOL = "_SoundStream_CreateMemory_0044cbf0@52"


@dataclass(frozen=True)
class Case(InitializeCase):
    operation: str = "factory"
    output: int = PUBLISHED
    flags: int = 0
    pcm: int = SOURCE
    pcm_bytes: int = 37
    algorithm: tuple = (0x11223344, 0x55667788, 0x99AABBCC, 0xDDEEFF00)
    segment_count: int = 16
    constructor_value: object = None
    description_writes: tuple = ()
    buffer_after_query: object = None


def compile_candidates(directory, asynchronous=True):
    initializers = compile_initializers(directory)
    obj = directory / "create-memory.obj"
    common = [item for item in COMMON if item != "-fno-exceptions"]
    subprocess.run([*common, "-fexceptions", "-fcxx-exceptions", *(["-fasync-exceptions"] if asynchronous else []), "-c",
                    str(ROOT / "matching2/reference/semantic_candidates/sound_stream_create_memory.cpp"),
                    "-o", str(obj)], check=True, timeout=60)
    bindings = {"_SoundBuffer_Allocate": ALLOCATE, "_SoundBuffer_Free": FREE,
                "_g_wave_notification_iid": IID, "___CxxFrameHandler3": FRAME_HANDLER}
    unit = load_module(obj, CANDIDATE + 0xA000, dict(bindings, **{SYMBOLS["single"]: CONSTRUCT}))
    full = load_module(obj, CANDIDATE + 0xC000, dict(bindings, **{
        SYMBOLS["single"]: initializers[1]["initializers_full"].symbols[SYMBOLS["single"]]}))
    assert any(name.startswith("___ehhandler$") for name in unit.symbols)
    return initializers, unit, full


class Execution(InitializeExecution):
    factory_symbol = FACTORY_SYMBOL
    retail_entry = 0x44CBF0
    retail_handler = 0x46531B

    def __init__(self, image, compiled=None):
        super().__init__(image, compiled[0] if compiled else None)
        self.factories = compiled[1:] if compiled else ()
        for module in self.factories:
            self.uc.mem_write(module.base, module.data)
        install_seh(self.uc)
        self.construct_entries = {0x44D6A0, CONSTRUCT}
        if compiled:
            self.construct_entries.add(compiled[0][1]["initializers_full"].symbols[SYMBOLS["single"]])
        self.create_output = None

    def initialize(self, case):
        super().initialize(case)
        self.words(PUBLISHED, 0xABCDEF00)

    def cursor_state(self):
        blocks = tuple((pointer, requested, bytes(self.uc.mem_read(pointer, min(requested, 120))))
                       for pointer, requested in self.allocated if pointer and pointer >= STATE and pointer < STATE + 0xF000)
        return super().cursor_state(), self.read_words(PUBLISHED), blocks

    def hook(self, machine, address, size, context):
        case = self.case
        if address == CREATE:
            device, description, out, outer = self.args(4)
            self.create_output = out
            self.event("create", device, self.read_words(out)[0], outer, bytes(self.uc.mem_read(description, 36)))
            assert outer == 0
            index = self.create_calls
            self.create_calls += 1
            for offset, value in case.description_writes:
                self.words(description + offset, value)
            if case.create_writes:
                self.words(out, NEW_BUFFERS + index * 16)
            self.finish(self.selected(case.create_results, index), 16)
        elif address == QUERY:
            super().hook(machine, address, size, context)
            if case.buffer_after_query is not None:
                self.words(self.create_output, case.buffer_after_query)
        elif address == SET_NOTICES:
            notify, count, positions = self.args(3)
            self.event("set-notices", notify, count, positions, bytes(self.uc.mem_read(positions, count * 8)))
            assert count == case.segment_count
            index = self.notice_calls
            self.notice_calls += 1
            if case.notify_after_set is not None:
                self.words(self.query_output, case.notify_after_set)
            self.finish(self.selected(case.notice_results, index), 12)
        elif address in self.construct_entries:
            retail = address == 0x44D6A0
            if retail:
                receiver = self.uc.reg_read(UC_X86_REG_ESI)
                buffer, bytes_, reader, segment = self.args(4)
            else:
                receiver, buffer, bytes_, reader, segment = self.args(5)
            self.event("construct", receiver, buffer, bytes_, reader, segment)
            if not case.integrated:
                result = receiver if case.constructor_value is None else case.constructor_value
                self.finish(result, 16 if retail else 20)
        else:
            super().hook(machine, address, size, context)

    def factory_arguments(self, case):
        return (case.owner, case.pcm, case.pcm_bytes, case.record, *case.algorithm,
                case.segment_count, case.segment_bytes, case.notification_event)

    def extra_hook_addresses(self):
        return ()

    def execute(self, case):
        self.initialize(case)
        self.install_hooks()
        from sound_stream_initialize_differential import RELEASE, RELEASE_NOTIFY, POSITION
        for address in (ALLOCATE, FREE, RELEASE, CREATE, QUERY, SET_NOTICES, RELEASE_NOTIFY, POSITION,
                        *self.fill_entries, *self.construct_entries, *self.extra_hook_addresses()):
            self.uc.hook_add(UC_HOOK_CODE, self.hook, begin=address, end=address)
        stack_args = self.factory_arguments(case)
        if self.factories:
            module = self.factories[int(case.integrated)]
            observed = self.run(module.symbols[self.factory_symbol], (case.output, case.flags, *stack_args), budget=500000)
        else:
            observed = self.run(self.retail_entry, stack_args, {UC_X86_REG_ECX: case.output, UC_X86_REG_EDX: case.flags}, budget=500000)
        if not self.faults:
            assert exception_list(self.uc) == INITIAL_EXCEPTION_LIST
        observed.update(allocated=self.allocated, freed=self.freed)
        return observed


def cases():
    for count, segment, flags in product((0, 1, 2, 16, 31), (0, 1, 7, 0x80000001), (0, 0xFFFFFFFF)):
        yield Case(segment_count=count, segment_bytes=segment, flags=flags)
    for create, query, notice in product((0, 1, 0x80070057), (0, 1, 0x80004005), (0, 1, 0x80004005)):
        yield Case(create_results=(create,), query_results=(query,), notice_results=(notice,))
    for kwargs in ({"owner": 0}, {"device": 0}, {"output": 0}, {"record": 0}, {"pcm": 0},
                   {"fail_allocate": 1}, {"fail_allocate": 2}, {"fail_allocate": 3},
                   {"create_writes": False}, {"query_writes": False}, {"query_value": 0},
                   {"notify_after_set": 0}, {"notify_after_set": ALT_NOTIFY}, {"constructor_value": 0},
                   {"constructor_value": STREAM}, {"buffer_after_query": 0},
                   {"description_writes": ((4, 0x12345678), (8, 0xFFEEDDCC), (12, 99), (32, 0x55555555))},
                   {"output": STREAM + 0x34, "constructor_value": STREAM},
                   {"segment_count": 0x20000001}):
        yield Case(**kwargs)
    for trigger, writes in (("allocate:1", ((OWNER, 0),)),
                           ("create", ((RECORD + 0x1C, 13),)),
                           ("query", ((OWNER, 0),)),
                           ("release-notify", ((OWNER, 0),)),
                           ("free", ((PUBLISHED, 0x1234),))):
        yield Case(mutations=((trigger, writes),))
    for count, bits, status, end in product((1, 16), (8, 16), (0, 2), (0, 29)):
        yield Case(integrated=True, segment_count=count, bits=bits, status=status, end=end)
    for kwargs in ({"fail_allocate": 1}, {"fail_allocate": 2}, {"fail_allocate": 3}, {"fail_allocate": 4},
                   {"output": 0}, {"record": 0}, {"pcm": 0}, {"pcm_bytes": 0},
                   {"status_result": 0x80004005}, {"lock_result": 0x80070057},
                   {"buffer_after_query": 0}, {"notify_after_set": 0}, {"notify_after_set": ALT_NOTIFY},
                   {"mutations": (("create", ((RECORD + 0x1C, 7),)),)}):
        yield Case(integrated=True, **kwargs)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--oracle", type=Path, default=ROOT / "matching2/build/oracle/th10.exe")
    options = parser.parse_args()
    config = load_manifest(ROOT / "matching2/msvc/regions.json")
    load_oracle(options.oracle, config)
    image = PEImage(options.oracle.read_bytes())
    with tempfile.TemporaryDirectory(prefix="th10-create-memory-stream-") as temporary:
        compiled = compile_candidates(Path(temporary))
        totals, faults = [0, 0], [0, 0]
        for case in cases():
            expected = Execution(image).execute(case)
            actual = Execution(image, compiled).execute(case)
            assert actual == expected, (case, difference(expected, actual))
            index = int(case.integrated)
            totals[index] += 1
            faults[index] += bool(expected["faults"])
        observed = Execution(image, compiled).execute(Case(integrated=True, bits=8))
        published, = struct.unpack_from("<I", observed["memory"][0], PUBLISHED - STATE)
        assert published == observed["allocated"][2][0]
        assert struct.unpack_from("<I", observed["memory"][0], published - STATE)[0] == 0x4705D4
        assert struct.unpack_from("<I", observed["memory"][0], published - STATE + 0x58)[0] == OWNER
        assert observed["memory"][2][DESTINATION - OUTPUT + 29:DESTINATION - OUTPUT + 31] == b"\x80\x80"
        assert observed["freed"] == [observed["allocated"][1][0]]
        print(f"PASS: {totals[0]} memory-stream factory unit comparisons ({faults[0]} faults), "
              f"{totals[1]} with executing initializer/refill/cursors ({faults[1]} faults), "
              f"independent publication/ownership/PCM check, and restored FS exception lists; "
              f"{len(compiled[1].data)} Clang module bytes. Native MSVC bytes and exception dispatch remain unverified.")


if __name__ == "__main__":
    main()
