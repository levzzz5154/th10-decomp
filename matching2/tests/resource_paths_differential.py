#!/usr/bin/env python3
"""Test resource dispatch, size lookup and archive registration against retail.

The retail archive selector, first-slash search and CRT comparison execute.
Disk Open/ReadWhole and Windows imports are scripted. Optional unwind cases
manually invoke the action selected by the live C++ frame's metadata, without
running Windows exception dispatch.
"""

import argparse
from dataclasses import dataclass
from itertools import product
from pathlib import Path
import struct
import subprocess
import tempfile

from unicorn import Uc, UC_ARCH_X86, UC_MODE_32, UC_HOOK_CODE
from unicorn.x86_const import (UC_X86_REG_EAX, UC_X86_REG_EBX, UC_X86_REG_ECX,
                              UC_X86_REG_EBP, UC_X86_REG_ESP, UC_X86_REG_EIP)
from lzss_compressor_differential import (
    ROOT, CANDIDATE, INPUT, OUTPUT, STACK, STOP, PRESERVED, PEImage,
    load_manifest, load_oracle, load_candidate, region_directory)
from coff_module import load_module

COUNT, ARCHIVES = 0x477850, 0x4923B0
STATE, RECORDS, THREAD, LOCALE = 0x2500000, 0x2501000, 0x2503000, 0x2504000
REGISTER, FIND_SIZE = CANDIDATE + 0x2000, CANDIDATE + 0x3000
READ_MODEL, OPEN_MODEL = CANDIDATE + 0xF000, CANDIDATE + 0xF100
GET_SIZE, CLOSE_HANDLE = STOP + 0x400, STOP + 0x500
INITIAL_EXCEPTION_LIST = 0xFEE1DEAD


@dataclass(frozen=True)
class Case:
    path: bytes = b"loose.bin"
    archive_names: tuple = (b"pack.dat", b"other.dat")
    count: object = None
    entry_count: int = 2
    entries_present: bool = True
    supplied_output: bool = False
    open_handle: int = 0x1234
    open_result: int = 1
    size: int = 37
    read_result: int = OUTPUT
    change_after_size: object = None
    change_after_read: object = None
    mutate_register_count: object = None
    throw_at: object = None


def compile_candidates(directory, config, code_base=CANDIDATE, extra_bindings=None):
    register_address = code_base + (REGISTER - CANDIDATE)
    find_size_address = code_base + (FIND_SIZE - CANDIDATE)
    bindings = region_directory(config, config["regions"])
    bindings.update({"@Resource_FindArchive_004356f0@4": 0x4356F0,
                     "_FirstByteSearch_00452730": 0x452730,
                     "_DatArchive_Read_00434dd0@12": READ_MODEL,
                     "_DatArchive_FindSize_00434ef0@8": find_size_address,
                     "_DatArchive_Open_00434c30@8": OPEN_MODEL,
                     "_g_dat_archive_read_mode": 0x474908,
                     "_g_resource_archive_count": COUNT, "_g_resource_archives": ARCHIVES,
                     "?Open@FileHandle@@UAEEPBD0@Z": 0x435370,
                     "___CxxFrameHandler3": STOP + 0x200})
    bindings.update(extra_bindings or {})
    compiled = {}
    for source in ("resource_paths.cpp", "unassigned_004357d0.cpp", "dat_archive_find_size_00434ef0.cpp"):
        obj = directory / (source + ".obj")
        subprocess.run([
            "clang++", "--target=i686-pc-windows-msvc", "-std=c++03", "-O2", "-mno-sse", "-mno-sse2",
            "-fexceptions", "-fcxx-exceptions", "-fno-rtti", "-fno-stack-protector", "-ffunction-sections",
            "-I", str(ROOT / "matching2/msvc/include"), "-c",
            str(ROOT / "matching2/reference/semantic_candidates" / source), "-o", str(obj)],
            check=True, timeout=60)
        compiled[source] = obj
    module = load_module(compiled["resource_paths.cpp"], code_base, bindings)
    bodies = {code_base: module.data,
              register_address: load_candidate(compiled["unassigned_004357d0.cpp"], config,
                  "Resource_RegisterArchive_004357d0", bindings, code_address=register_address),
              find_size_address: load_candidate(compiled["dat_archive_find_size_00434ef0.cpp"], config,
                  "DatArchive_FindSize_00434ef0", bindings, code_address=find_size_address)}
    return module, bodies


def execute(image, candidate, operation, case):
    module, bodies = candidate if candidate else (None, {})
    uc = Uc(UC_ARCH_X86, UC_MODE_32)
    uc.mem_map(0x400000, 0x100000)
    for section in image.sections:
        uc.mem_write(section["address"], image.read(section["address"], section["raw_size"]))
    for address in (CANDIDATE, INPUT, OUTPUT, STACK, STOP, STATE):
        uc.mem_map(address, 0x10000)
    uc.mem_map(0, 0x1000)
    for address, code in bodies.items():
        uc.mem_write(address, code)

    def words(address, *values):
        uc.mem_write(address, struct.pack("<" + "I" * len(values), *(v & 0xFFFFFFFF for v in values)))

    def read_words(address, count):
        return struct.unpack("<" + "I" * count, uc.mem_read(address, count * 4))

    def string(address):
        data = bytearray()
        while True:
            value = uc.mem_read(address + len(data), 1)[0]
            if not value:
                return bytes(data)
            data.append(value)
            assert len(data) < 1024

    words(0, INITIAL_EXCEPTION_LIST)
    words(0x4660D8, GET_SIZE)
    words(0x4660CC, CLOSE_HANDLE)
    words(0x47320C, LOCALE)
    words(THREAD + 0x64, LOCALE)
    uc.mem_write(INPUT, case.path + b"\0")
    uc.mem_write(OUTPUT, b"\xA5" * 256)
    count = len(case.archive_names) if case.count is None else case.count
    words(COUNT, count)
    for index, name in enumerate(case.archive_names):
        pointer = STATE + 0x100 + index * 0x100
        uc.mem_write(pointer, name + b"\0")
        words(ARCHIVES + index * 16, RECORDS if case.entries_present else 0, case.entry_count, pointer, 0)
    for index, name in enumerate((b"asset.bin", b"dir/asset.bin")):
        pointer = STATE + 0x800 + index * 0x100
        uc.mem_write(pointer, name + b"\0")
        words(RECORDS + index * 16, pointer, index * 100, 0x12345678 + index, 0)
    arguments = []
    expected_preserved = dict(PRESERVED)
    supplied = OUTPUT if case.supplied_output else 0
    if operation == "register":
        entry = REGISTER if candidate else 0x4357D0
        arguments = [INPUT] if candidate else []
        uc.reg_write(UC_X86_REG_EAX, INPUT)
    elif operation == "find-size":
        entry = FIND_SIZE if candidate else 0x434EF0
        arguments = [ARCHIVES, INPUT] if candidate else []
        uc.reg_write(UC_X86_REG_EAX, ARCHIVES)
        if not candidate:
            expected_preserved[UC_X86_REG_EBX] = INPUT
    else:
        assert operation in ("load", "size")
        symbol = "_Resource_LoadFile_00435800@8" if operation == "load" else "_Resource_GetFileSize_004358e0@4"
        entry = module.symbols[symbol] if candidate else (0x435800 if operation == "load" else 0x4358E0)
        arguments = ([INPUT, supplied] if operation == "load" else [INPUT]) if candidate else (
            [supplied] if operation == "load" else [])
        uc.reg_write(UC_X86_REG_ECX, INPUT)
    sp = STACK + 0x8000
    words(sp, STOP, *arguments)
    uc.reg_write(UC_X86_REG_ESP, sp)
    for register, value in expected_preserved.items():
        uc.reg_write(register, value)
    events = []
    file_pointer = None
    injected = False
    unwinding = False

    def args(count):
        return read_words(uc.reg_read(UC_X86_REG_ESP) + 4, count)

    def finish(value, cleanup=0):
        current = uc.reg_read(UC_X86_REG_ESP)
        uc.reg_write(UC_X86_REG_EIP, read_words(current, 1)[0])
        uc.reg_write(UC_X86_REG_ESP, current + 4 + cleanup)
        uc.reg_write(UC_X86_REG_EAX, value & 0xFFFFFFFF)

    def file_state():
        vtable, handle, access = read_words(file_pointer, 3)
        expected = module.symbols["??_7FileHandle@@6B@"] if candidate else 0x46F230
        assert vtable == expected
        return handle, access

    def maybe_throw(stage):
        nonlocal injected
        if not unwinding and case.throw_at == stage:
            injected = True
            events.append(("unwind", stage))
            uc.emu_stop()
            return True
        return False

    def hook(machine, address, size, context):
        nonlocal file_pointer
        if address == 0x4356F0:
            events.append(("find-archive", string(uc.reg_read(UC_X86_REG_ECX))))
            maybe_throw("find-archive")
        elif address == 0x456357:
            finish(THREAD)
        elif address in (READ_MODEL, 0x434DD0):
            if address == READ_MODEL:
                archive, name, output = args(3)
            else:
                archive, output = args(2)
                name = uc.reg_read(UC_X86_REG_ECX)
            events.append(("archive-read", archive, string(name), output))
            if not maybe_throw("archive-read"):
                finish(case.read_result, 12 if address == READ_MODEL else 8)
        elif address in (FIND_SIZE, 0x434EF0):
            if address == FIND_SIZE:
                archive, name = args(2)
            else:
                archive, name = uc.reg_read(UC_X86_REG_EAX), uc.reg_read(UC_X86_REG_EBX)
            events.append(("archive-size", archive, string(name)))
            # Execute the actual candidate/retail lookup and CRT comparison.
            maybe_throw("archive-size")
        elif address == 0x435370:
            file_pointer = uc.reg_read(UC_X86_REG_ECX)
            path, mode = args(2)
            events.append(("open", string(path), string(mode), file_state()))
            words(file_pointer + 4, case.open_handle, 0x80000000)
            if not maybe_throw("open"):
                finish(case.open_result, 8)
        elif address == GET_SIZE:
            handle, high = args(2)
            events.append(("disk-size", handle, high, file_state()))
            assert high == 0
            if case.change_after_size is not None:
                words(file_pointer + 4, case.change_after_size)
            if not maybe_throw("disk-size"):
                finish(case.size, 8)
        elif address == 0x435580:
            assert uc.reg_read(UC_X86_REG_ECX) == file_pointer
            capacity, = args(1)
            events.append(("read-whole", capacity, file_state()))
            if case.change_after_read is not None:
                words(file_pointer + 4, case.change_after_read)
            if not maybe_throw("read-whole"):
                finish(case.read_result, 4)
        elif address == CLOSE_HANDLE:
            handle, = args(1)
            events.append(("close-handle", handle, file_state()))
            finish(1, 4)
        elif address in (OPEN_MODEL, 0x434C30):
            archive, path = args(2) if address == OPEN_MODEL else (
                uc.reg_read(UC_X86_REG_ECX), uc.reg_read(UC_X86_REG_EAX))
            events.append(("archive-open", archive, path, read_words(COUNT, 1)[0]))
            if case.mutate_register_count is not None:
                words(COUNT, case.mutate_register_count)
            finish(case.open_result, 8 if address == OPEN_MODEL else 0)
        elif address == STOP + 0x200:
            raise AssertionError("Windows exception dispatch is outside this test")
        else:
            raise AssertionError(f"unexpected hook {address:#x}")

    for address in (0x4356F0, 0x456357, READ_MODEL, 0x434DD0, FIND_SIZE, 0x434EF0,
                    0x435370, GET_SIZE, 0x435580, CLOSE_HANDLE, OPEN_MODEL, 0x434C30, STOP + 0x200):
        uc.hook_add(UC_HOOK_CODE, hook, begin=address, end=address)
    uc.emu_start(entry, STOP, count=1000000)
    state = None
    if injected:
        unwinding = True
        frame, = read_words(0, 1)
        previous, handler, raw_state = read_words(frame, 3)
        assert previous == INITIAL_EXCEPTION_LIST
        assert bytes(uc.mem_read(handler, 1)) == b"\xB8"
        info, = read_words(handler + 1, 1)
        magic, states, table, tries = read_words(info, 4)
        assert magic == (0x19930522 if candidate else 0x19930520) and states == 1 and tries == 0
        state = -1 if raw_state == 0xFFFFFFFF else raw_state
        assert state == (-1 if file_pointer is None else 0)
        if state == 0:
            prior, action = read_words(table, 2)
            assert prior == 0xFFFFFFFF
            words(frame + 8, prior)
            action_sp = STACK + 0x3000
            words(action_sp, STOP)
            uc.reg_write(UC_X86_REG_ESP, action_sp)
            uc.reg_write(UC_X86_REG_EBP, frame + 12)
            uc.emu_start(action, STOP, count=1000000)
            assert uc.reg_read(UC_X86_REG_EIP) == STOP
            assert uc.reg_read(UC_X86_REG_ESP) == action_sp + 4
        assert read_words(0, 1)[0] == frame
        words(0, previous)
        result = None
    else:
        assert case.throw_at is None
        assert uc.reg_read(UC_X86_REG_EIP) == STOP
        assert uc.reg_read(UC_X86_REG_ESP) == sp + 4 * (len(arguments) + 1)
        for register, value in expected_preserved.items():
            assert uc.reg_read(register) == value
        result = uc.reg_read(UC_X86_REG_EAX)
        if operation == "register":
            result &= 255
            expected_count = count if case.mutate_register_count is None else case.mutate_register_count
            assert read_words(COUNT, 1)[0] == ((expected_count + bool(case.open_result & 255)) & 0xFFFFFFFF)
            assert result == bool(case.open_result & 255)
            assert events[0][1] == (ARCHIVES + ((count & 0xFFFFFFFF) << 4)) & 0xFFFFFFFF
    assert read_words(0, 1)[0] == INITIAL_EXCEPTION_LIST
    return {"events": events, "result": result, "unwind-state": state,
            "count": read_words(COUNT, 1)[0], "output": bytes(uc.mem_read(OUTPUT, 256))}


def path_cases():
    paths = (b"pack/asset.bin", b"pack/dir/asset.bin", b"pack//asset.bin", b"pack/",
             b"PACK/asset.bin", b"pack\\asset.bin", b"pack.dat", b"loose.bin", b"/asset.bin", b"")
    for path, supplied in product(paths, (False, True)):
        yield Case(path=path, supplied_output=supplied)
    for handle, opened, size, result, supplied in product(
            (0xFFFFFFFF, 0, 0x1234), (0, 1, 0xABC00000, 0xABC00080),
            (0, 37, 0xFFFFFFFF), (0, OUTPUT), (False, True)):
        yield Case(open_handle=handle, open_result=opened, size=size,
                   read_result=result, supplied_output=supplied)
    for changed_size, changed_read in product((None, 0xFFFFFFFF, 0x99), repeat=2):
        yield Case(change_after_size=changed_size, change_after_read=changed_read)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--oracle", type=Path, default=ROOT / "matching2/build/oracle/th10.exe")
    options = parser.parse_args()
    config = load_manifest(ROOT / "matching2/msvc/regions.json")
    load_oracle(options.oracle, config)
    image = PEImage(options.oracle.read_bytes())
    with tempfile.TemporaryDirectory(prefix="th10-resource-paths-") as temporary:
        candidate = compile_candidates(Path(temporary), config)
        counts = {}

        def compare(operation, case):
            retail = execute(image, None, operation, case)
            recovered = execute(image, candidate, operation, case)
            assert retail == recovered, (operation, case, retail, recovered)
            counts[operation] = counts.get(operation, 0) + 1

        for operation in ("load", "size"):
            for case in path_cases():
                compare(operation, case)
            for handle, phase in product((0xFFFFFFFF, 0x1234), ("open", "read-whole", "disk-size")):
                if operation == "size" and phase == "read-whole":
                    continue
                if handle == 0xFFFFFFFF and phase == "disk-size":
                    continue
                compare(operation, Case(open_handle=handle, throw_at=phase))
            compare(operation, Case(throw_at="find-archive"))
            compare(operation, Case(path=b"pack/asset.bin", throw_at="archive-read" if operation == "load" else "archive-size"))
        # The actual archive opener always returns AL 0 or 1; its upper EAX
        # bits are unspecified. Noncanonical AL values violate its C++ bool
        # contract and are not outputs of either verified opener body.
        for count, returned, mutation in product((0, 1, 2, 16, -1, 0x10000000),
                (0, 1, 0xFFFF0000, 0xFFFF0001), (None, 0, 31, 0xFFFFFFFF, 0x7FFFFFFF)):
            compare("register", Case(count=count, open_result=returned, mutate_register_count=mutation))
        for name, present, count in product((b"asset.bin", b"ASSET.BIN", b"dir/asset.bin", b"missing", b""),
                                          (False, True), (-1, 0, 1, 2)):
            compare("find-size", Case(path=name, entries_present=present, entry_count=count))
        nested = execute(image, candidate, "load", Case(path=b"pack/dir/asset.bin"))
        assert ("archive-read", ARCHIVES, b"dir/asset.bin", 0) in nested["events"]
        nested_size = execute(image, candidate, "size", Case(path=b"pack/dir/asset.bin"))
        assert nested_size["result"] == 0x12345679
        print("PASS: " + ", ".join(f"{count} {operation}" for operation, count in counts.items()) +
              " retail comparisons, including table-selected stack-file cleanup actions. "
              "Private ABIs, Windows dispatch and MSVC byte matching remain unverified.")


if __name__ == "__main__":
    main()
