#!/usr/bin/env python3
"""Compare registered parser cleanup states and execute their unwind actions.

The test stops x86 execution at selected calls, reads the actual SEH/C++ frame
records and tables, then manually unwinds those frames by executing the actions
they name. This verifies cleanup semantics and generated metadata; it does not
run Windows exception dispatch, catch matching or CxxFrameHandler3 itself.
"""

import argparse
from dataclasses import dataclass
from pathlib import Path
import struct
import tempfile

from unicorn import Uc, UC_ARCH_X86, UC_MODE_32, UC_HOOK_CODE
from unicorn.x86_const import (UC_X86_REG_EAX, UC_X86_REG_ECX, UC_X86_REG_EBP,
                              UC_X86_REG_ESP, UC_X86_REG_EIP)
from lzss_compressor_differential import (
    ROOT, CANDIDATE, INPUT, STACK, STOP, PRESERVED, PEImage, load_manifest, load_oracle)
from dat_archive_parser_differential import (
    ENTRY, ARRAY_ARENA, ALLOCATION, NAMES, INITIAL_EXCEPTION_LIST,
    compile_candidate, load_parser_candidate, pack)


@dataclass(frozen=True)
class Case:
    count: int
    phase: str
    index: int = 0
    alignment: int = 0
    null_names: bool = False


def execute(image, module, case):
    uc = Uc(UC_ARCH_X86, UC_MODE_32)
    uc.mem_map(0x400000, 0x100000)
    for section in image.sections:
        uc.mem_write(section["address"], image.read(section["address"], section["raw_size"]))
    for address in (CANDIDATE, INPUT, ARRAY_ARENA, STACK, STOP):
        uc.mem_map(address, 0x10000)
    uc.mem_map(NAMES, 0x40000)
    uc.mem_map(0, 0x1000)
    if module:
        uc.mem_write(module.base, module.data)
    uc.mem_write(ARRAY_ARENA, b"\xA5" * 0x10000)
    uc.mem_write(NAMES, b"\xA5" * 0x40000)
    names = tuple(f"entry-{index}.anm".encode() for index in range(case.count))
    packed = pack(names)
    uc.mem_write(INPUT + case.alignment, packed + b"\xA5" * 64)

    def words(address, *values):
        uc.mem_write(address, struct.pack("<" + "I" * len(values), *(v & 0xFFFFFFFF for v in values)))

    def read_words(address, count):
        return struct.unpack("<" + "I" * count, uc.mem_read(address, count * 4))

    words(0, INITIAL_EXCEPTION_LIST)
    words(STACK + 0x8000, STOP, INPUT + case.alignment, case.count, 0x12345678)
    uc.reg_write(UC_X86_REG_ESP, STACK + 0x8000)
    for register, value in PRESERVED.items():
        uc.reg_write(register, value)
    outer_handler = (module.symbols["___ehhandler$_DatArchive_BuildIndex_004350d0@12"]
                     if module else 0x4653CB)
    events, released, freed, allocations = [], [], [], []
    constructors = name_calls = 0
    injected = unwinding = False

    def args(count):
        return read_words(uc.reg_read(UC_X86_REG_ESP) + 4, count)

    def finish(value):
        sp = uc.reg_read(UC_X86_REG_ESP)
        uc.reg_write(UC_X86_REG_EIP, read_words(sp, 1)[0])
        uc.reg_write(UC_X86_REG_ESP, sp + 4)
        uc.reg_write(UC_X86_REG_EAX, value)

    def stop_at(phase, index=0):
        nonlocal injected
        if not unwinding and case.phase == phase and case.index == index:
            assert not injected
            injected = True
            events.append(("leave-by-exception", phase, index))
            uc.emu_stop()
            return True
        return False

    def hook(machine, address, size, context):
        nonlocal constructors, name_calls
        if address == 0x452493:
            requested, = args(1)
            events.append(("new", requested))
            if not stop_at("new"):
                finish(ALLOCATION)
        elif address == 0x45252D:
            events.append(("construct-array", *args(5)))
            stop_at("vector")
        elif address == 0x4352C0:
            receiver = uc.reg_read(UC_X86_REG_ECX)
            events.append(("construct", receiver))
            stop_at("construct", constructors)
            constructors += 1
        elif address == 0x452706:
            requested, = args(1)
            events.append(("malloc", requested))
            if not stop_at("malloc", name_calls):
                pointer = 0 if case.null_names else NAMES + name_calls * 0x1000
                allocations.append((requested, pointer))
                name_calls += 1
                finish(pointer)
        elif address == 0x435250:
            assert unwinding
            receiver = uc.reg_read(UC_X86_REG_ECX)
            events.append(("release", receiver))
            released.append(receiver)
        elif address in (0x452422, 0x4524A1):
            assert unwinding
            pointer, = args(1)
            events.append(("free", address, pointer))
            freed.append((address, pointer))
            finish(0xBAD00001)
        elif address == STOP + 0x200:
            raise AssertionError("Windows exception dispatch is outside this test's scope")
        else:
            raise AssertionError(f"unexpected hook {address:#x}")

    for address in (0x452493, 0x45252D, 0x4352C0, 0x452706, 0x435250, 0x452422, 0x4524A1, STOP + 0x200):
        uc.hook_add(UC_HOOK_CODE, hook, begin=address, end=address)
    uc.emu_start(CANDIDATE if module else ENTRY, STOP, count=1000000)
    assert injected and uc.reg_read(UC_X86_REG_EIP) != STOP

    # Capture the real frame chain before changing registers for action calls.
    frames = []
    frame = read_words(0, 1)[0]
    while frame != INITIAL_EXCEPTION_LIST:
        assert STACK <= frame < STACK + 0x10000 and len(frames) < 3
        previous, handler = read_words(frame, 2)
        frames.append((frame, previous, handler))
        frame = previous
    assert frames and frames[-1][2] == outer_handler
    assert len(frames) == (2 if case.phase == "construct" else 1)
    unwinding = True

    def invoke(action, frame_pointer):
        # The actual actions execute on a separate stack area so their calls
        # cannot overwrite the suspended parser/helper locals under test.
        sp = STACK + 0x3000
        words(sp, STOP)
        uc.reg_write(UC_X86_REG_ESP, sp)
        uc.reg_write(UC_X86_REG_EBP, frame_pointer)
        uc.emu_start(action, STOP, count=1000000)
        assert uc.reg_read(UC_X86_REG_EIP) == STOP
        assert uc.reg_read(UC_X86_REG_ESP) == sp + 4

    states = []
    for frame, previous, handler in frames:
        assert read_words(0, 1)[0] == frame
        if handler == outer_handler:
            # Both compiler thunks load FuncInfo into EAX and tail-call their
            # own C++ frame handler. Versions differ; only common fields are
            # interpreted, and neither runtime handler is substituted for the other.
            assert bytes(uc.mem_read(handler, 1)) == b"\xB8"
            assert bytes(uc.mem_read(handler + 5, 1)) == b"\xE9"
            info = read_words(handler + 1, 1)[0]
            magic, count, unwind_map, try_count, try_map = read_words(info, 5)
            assert magic == (0x19930522 if module else 0x19930520)
            assert count == 1 and try_count == try_map == 0
            state, = struct.unpack("<i", uc.mem_read(frame + 8, 4))
            assert state == (-1 if case.phase == "new" else 0)
            states.append(("parser", state, count, try_count))
            if state >= 0:
                prior, action = read_words(unwind_map + state * 8, 2)
                assert prior == 0xFFFFFFFF and action
                # C++ local unwind records the predecessor state before
                # invoking its action, preventing the same cleanup twice.
                words(frame + 8, prior)
                invoke(action, frame + 12)
        else:
            # The vector helper uses an SEH finally scope. Read its live scope
            # table rather than hard-coding which cleanup funclet to invoke.
            assert handler == 0x454C10 and case.phase == "construct"
            table, level = read_words(frame + 8, 2)
            assert level == 0
            prior, filter_address, action = read_words(table + level * 12, 3)
            assert prior == 0xFFFFFFFF and filter_address == 0 and action == 0x452577
            states.append(("vector", level))
            words(frame + 12, prior)
            invoke(action, frame + 16)
        assert read_words(0, 1)[0] == frame, "action failed to restore its nested frames"
        # Frame removal belongs to the dispatcher, which this harness models.
        words(0, previous)
    assert read_words(0, 1)[0] == INITIAL_EXCEPTION_LIST

    assert freed == ([] if case.phase == "new" else [(0x4524A1, ALLOCATION)])
    expected_releases = ([ALLOCATION + 4 + index * 16 for index in reversed(range(case.index))]
                         if case.phase == "construct" else [])
    assert released == expected_releases
    if case.phase == "malloc":
        # Retail only frees the array here. Already copied names are neither
        # individually released nor cleared by its outer unwind action.
        for index in range(case.index):
            pointer = read_words(ALLOCATION + 4 + index * 16, 1)[0]
            assert pointer == (0 if case.null_names else NAMES + index * 0x1000)
            if pointer:
                assert bytes(uc.mem_read(pointer, len(names[index]) + 1)) == names[index] + b"\0"
    return {"events": events, "states": states,
            "array": bytes(uc.mem_read(ARRAY_ARENA, 0x10000)),
            "names": tuple((size, pointer, bytes(uc.mem_read(pointer, size + 16)) if pointer else b"")
                           for size, pointer in allocations)}


def cases():
    for count in (0, 1, 2, 7, 16):
        for alignment in range(4):
            yield Case(count, "new", alignment=alignment)
            yield Case(count, "vector", alignment=alignment)
            for index in range(count + 1):
                yield Case(count, "construct", index, alignment)
            for index in range(count):
                yield Case(count, "malloc", index, alignment)
    for index in range(5):
        for null_names in (False, True):
            yield Case(5, "malloc", index, null_names=null_names)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--oracle", type=Path, default=ROOT / "matching2/build/oracle/th10.exe")
    options = parser.parse_args()
    config = load_manifest(ROOT / "matching2/msvc/regions.json")
    load_oracle(options.oracle, config)
    image = PEImage(options.oracle.read_bytes())
    with tempfile.TemporaryDirectory(prefix="th10-parser-unwind-") as temporary:
        path = Path(temporary) / "parser.obj"
        compile_candidate(path)
        module = load_parser_candidate(path)
        count = 0
        for case in cases():
            retail = execute(image, None, case)
            candidate = execute(image, module, case)
            assert retail == candidate, (case, retail, candidate)
            count += 1
        print(f"PASS: {count} registered-state/unwind-action comparisons, including partial "
              "construction and every selected name-allocation stage. Actual table-selected actions "
              "execute; Windows exception dispatch and native MSVC bytes remain unverified.")


if __name__ == "__main__":
    main()
