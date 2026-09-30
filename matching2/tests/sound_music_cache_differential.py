#!/usr/bin/env python3
"""Compare music-table publication and per-slot music caching with retail.

File imports/allocation are scripted. Integrated cases freshly compile the
maintained basename lookup, execute retail strrchr/strcmp, and use a compiled
byte-copy strcpy fixture. Names passed to that helper fit its 128-byte local;
native stack-cookie/overflow equivalence is not claimed.
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
from unicorn.x86_const import UC_X86_REG_EAX, UC_X86_REG_ECX, UC_X86_REG_ESI, UC_X86_REG_ESP, UC_X86_REG_EIP
from lzss_compressor_differential import (
    ROOT, CANDIDATE, STACK, STOP, PRESERVED, PEImage, load_manifest, load_oracle, load_candidate, DEFAULT_TOOLKIT)
from coff_module import load_module

STATE, DATA = 0x2500000, 0x2600000
LOCAL, GLOBAL, NAME = STATE + 0x100, 0x492590, STATE + 0x9000
TABLE, ALT_TABLE, OLD, ALLOCATION = (DATA + offset for offset in (0x1000, 0x2000, 0x4000, 0x6000))
MODE = 0x491D78
FIND, TABLE_LOAD, STRCPY = CANDIDATE + 0x6000, CANDIDATE + 0x4000, CANDIDATE + 0x8000
CREATE, SEEK, READ, CLOSE, ARCHIVE = (STOP + 0x100 * i for i in range(1, 6))
FIND_SYMBOL = "?FindBasenameSlot_0043d2a0@PathName_0043d2a0@@QAEHPAX@Z"
FILE_DATA = bytes((i * 19 + 7) & 255 for i in range(0x4000))


@dataclass(frozen=True)
class Case:
    operation: str = "cache"
    integrated: bool = False
    manager: int = LOCAL
    index: int = 1
    name: bytes = b"track1.wav"
    stored_name: bytes = b"previous.wav"
    old: bool = True
    flags: int = 0x10
    owner: bool = True
    opened: int = 0x1234
    allocation: int = ALLOCATION
    lookup: int = 1
    seek_result: int = 0
    read_result: int = 1
    read_limit: object = None
    mutations: tuple = ()
    source_delta: object = None  # alias requested name with global destination
    table_present: bool = True
    empty_table: bool = False
    size: int = 31
    repeat: int = 1


def compile_candidates(directory, config, code_base=CANDIDATE, extra_bindings=None):
    find, table_load, strcpy_address = code_base + 0x6000, code_base + 0x4000, code_base + 0x8000
    bindings = {"_g_wave_sound_manager": GLOBAL, "_g_sound_mode_flags": MODE,
                "_g_music_create_file": 0x4660C4, "_g_music_seek_file": 0x4660C8,
                "_g_music_read_file": 0x4660D0, "_g_music_close_file": 0x4660CC,
                "_asm_malloc_00452706": 0x452706, "_entry_free_00452422": 0x452422,
                FIND_SYMBOL: find, "_Archive_LoadFile@12": ARCHIVE,
                "_strcpy": strcpy_address, "_strcmp": 0x45BF30, "_asm_strrchr_00452930": 0x452930}
    bindings.update(extra_bindings or {})
    modules = {}
    for source, address in (("sound_music_cache", code_base), ("unassigned_0043d670", table_load)):
        obj = directory / (source + ".obj")
        subprocess.run([
            "clang++", "--target=i686-pc-windows-msvc", "-std=c++03", "-O2", "-mno-sse", "-mno-sse2",
            "-fno-exceptions", "-fno-rtti", "-fno-stack-protector", "-fno-builtin",
            "-I", str(ROOT / "matching2/msvc/include"), "-c",
            str(ROOT / "matching2/reference/semantic_candidates" / (source + ".cpp")), "-o", str(obj)],
            check=True, timeout=60)
        modules[source] = load_module(obj, address, bindings)
    obj = directory / "music-basename.obj"
    subprocess.run([
        "clang++", "--target=i686-pc-windows-msvc", "-std=c++03", "-O2", "-mno-sse", "-mno-sse2",
        "-fno-exceptions", "-fno-rtti", "-fno-stack-protector", "-fno-builtin", "-ffunction-sections",
        "-I", str(ROOT / "matching2/msvc/include"), "-isystem", str(DEFAULT_TOOLKIT / "include"),
        "-c", str(ROOT / "matching2/msvc/src/platform/path.cpp"), "-o", str(obj)], check=True, timeout=60)
    find_body = load_candidate(obj, config, FIND_SYMBOL, bindings, code_address=find)
    # The maintained source's strcpy is inlined by retail MSVC, while this
    # Clang build emits a library call. Supply its normal byte-copy contract.
    source = directory / "strcpy-fixture.cpp"
    source.write_text('extern "C" char* __cdecl strcpy(char* to, const char* from) {\n'
                      '    char* result = to;\n'
                      '    while ((*to++ = *from++) != 0) {}\n'
                      '    return result;\n}\n')
    obj = directory / "strcpy-fixture.obj"
    subprocess.run(["clang++", "--target=i686-pc-windows-msvc", "-O2", "-fno-builtin", "-mno-sse",
                    "-mno-sse2", "-c", str(source), "-o", str(obj)], check=True, timeout=60)
    copy = load_module(obj, strcpy_address, {})
    bodies = {module.base: module.data for module in modules.values()}
    bodies.update({find: find_body, strcpy_address: copy.data})
    return modules, bodies


def execute(image, compiled, case):
    modules, bodies = compiled if compiled else ({}, {})
    uc = Uc(UC_ARCH_X86, UC_MODE_32)
    uc.mem_map(0x400000, 0x100000)
    for section in image.sections:
        uc.mem_write(section["address"], image.read(section["address"], section["raw_size"]))
    for address in (CANDIDATE, STACK, STOP, STATE, DATA):
        uc.mem_map(address, 0x10000)
    for address, body in bodies.items():
        uc.mem_write(address, body)

    def words(address, *values):
        uc.mem_write(address, struct.pack("<" + "I" * len(values), *(value & 0xFFFFFFFF for value in values)))

    def read_words(address, count=1):
        return struct.unpack("<" + "I" * count, uc.mem_read(address, count * 4))

    def slot(offset):
        return (case.manager + offset + (case.index & 0xFFFFFFFF) * 4) & 0xFFFFFFFF

    def args(count):
        return read_words(uc.reg_read(UC_X86_REG_ESP) + 4, count)

    def string(address):
        result = bytearray()
        while uc.mem_read(address + len(result), 1)[0]:
            result.extend(uc.mem_read(address + len(result), 1))
            assert len(result) < 1024
        return bytes(result)

    def finish(value, cleanup=0):
        sp = uc.reg_read(UC_X86_REG_ESP)
        uc.reg_write(UC_X86_REG_EIP, read_words(sp)[0])
        uc.reg_write(UC_X86_REG_ESP, sp + 4 + cleanup)
        uc.reg_write(UC_X86_REG_EAX, value & 0xFFFFFFFF)

    uc.mem_write(STATE, b"\xA5" * 0x10000)
    uc.mem_write(DATA, b"\xA5" * 0x10000)
    uc.mem_write(GLOBAL, b"\xA5" * 0x5400)
    manager = case.manager
    name = NAME
    if manager:
        words(manager + 0x610, 0x12345678 if case.owner else 0)
        words(manager + 0x1F84, TABLE if case.table_present else 0)
        uc.mem_write(manager + 0x5108, b"music-container.dat\0")
        for offset in (0x1E80, 0x1EC0, 0x1F00, 0x1F40):
            words(slot(offset), OLD if offset == 0x1EC0 and case.old else 0xDEAD0000 + offset)
        if not case.old:
            words(slot(0x1EC0), 0)
        cached_name = (manager + 0x4108 + (case.index & 0xFFFFFFFF) * 256) & 0xFFFFFFFF
        uc.mem_write(cached_name, case.stored_name + b"\0")
    for table, adjustment in ((TABLE, 0), (ALT_TABLE, 7)):
        for index, label in enumerate((b"first.wav", b"track1.wav", b"Last.WAV", b"")):
            if case.empty_table:
                label = b""
            record = (label + bytes(16 - len(label)) + struct.pack("<4I", 0x90 + index * 64 + adjustment,
                       case.size + index + adjustment, 0, 0) +
                       struct.pack("<HHIIHHH", 1, 2, 44100, 176400, 4, 16, 0) + bytes(2))
            assert len(record) == 52
            uc.mem_write(table + index * 52, record)
    uc.mem_write(MODE, bytes([case.flags]))
    for slot_address, target in ((0x4660C4, CREATE), (0x4660C8, SEEK), (0x4660D0, READ), (0x4660CC, CLOSE)):
        words(slot_address, target)
    if case.source_delta is not None:
        name = (GLOBAL + 0x4108 + (case.index & 0xFFFFFFFF) * 256 + case.source_delta) & 0xFFFFFFFF
    uc.mem_write(name, case.name + b"\0")
    events, faults = [], []
    position = 0

    def state():
        if not manager:
            return ()
        return (read_words(manager + 0x1F84)[0], *(read_words(slot(offset))[0]
                for offset in (0x1E80, 0x1EC0, 0x1F00, 0x1F40)))

    def event(kind, *values):
        events.append((kind, *values, state()))
        for stage, writes in case.mutations:
            if kind == stage:
                for address, value in writes:
                    words(address, value)

    def hook(machine, address, size, context):
        nonlocal position
        if address == 0x452422:
            pointer, = args(1)
            event("free", pointer)
            finish(0xBAD00001)
        elif address == 0x452706:
            count, = args(1)
            assert count < 0x1000
            event("malloc", count)
            finish(case.allocation)
        elif address == CREATE:
            path, access, share, security, disposition, flags, template = args(7)
            event("open", string(path), access, share, security, disposition, flags, template)
            assert (access, share, security, disposition, flags, template) == (0x80000000, 1, 0, 3, 0x8000080, 0)
            position = 0
            finish(case.opened, 28)
        elif address in (FIND, 0x43D2A0):
            owner, = args(1)
            event("find", string(uc.reg_read(UC_X86_REG_ECX)), owner)
            assert owner == manager
            if not case.integrated:
                finish(case.lookup, 4)
        elif address == SEEK:
            handle, distance, high, origin = args(4)
            event("seek", handle, distance, high, origin)
            assert high == origin == 0
            if case.seek_result != 0xFFFFFFFF:
                position = distance
            finish(case.seek_result, 16)
        elif address == READ:
            handle, output, count, actual, overlapped = args(5)
            available = count if case.read_limit is None else min(count, case.read_limit)
            data = FILE_DATA[position:position + available]
            event("read", handle, output, count, position, len(data), overlapped)
            if data:
                uc.mem_write(output, data)
            words(actual, len(data))
            position += len(data)
            finish(case.read_result, 20)
        elif address == CLOSE:
            handle, = args(1)
            event("close", handle)
            finish(0, 4)
        elif address in (ARCHIVE, 0x44B360):
            if address == ARCHIVE:
                file_name, out_size, mode = args(3)
            else:
                file_name = uc.reg_read(UC_X86_REG_EAX)
                out_size, mode = args(2)
            event("archive", string(file_name), out_size, mode)
            assert out_size == mode == 0
            finish(case.allocation, 12 if address == ARCHIVE else 8)
        else:
            raise AssertionError(hex(address))

    def fault(machine, kind, address, size, value, context):
        faults.append((kind, address, size, value))
        return False

    for address in (0x452422, 0x452706, CREATE, FIND, 0x43D2A0, SEEK, READ, CLOSE, ARCHIVE, 0x44B360):
        uc.hook_add(UC_HOOK_CODE, hook, begin=address, end=address)
    uc.hook_add(UC_HOOK_MEM_INVALID, fault)
    sp = STACK + 0x8000
    preserved = dict(PRESERVED)
    if case.operation == "table":
        if modules:
            entry = modules["unassigned_0043d670"].symbols["_Sound_LoadMusicTable_0043d670@8"]
            words(sp, STOP, name, manager)
            expected_sp = sp + 12
        else:
            entry = 0x43D670
            words(sp, STOP, manager)
            uc.reg_write(UC_X86_REG_EAX, name)
            expected_sp = sp + 8
    elif modules:
        entry = modules["sound_music_cache"].symbols["_Sound_CacheMusic_0043d7d0@12"]
        words(sp, STOP, name, manager, case.index)
        expected_sp = sp + 16
    else:
        entry = 0x43D7D0
        words(sp, STOP, case.index)
        preserved[UC_X86_REG_ESI] = manager
        uc.reg_write(UC_X86_REG_EAX, name)
        expected_sp = sp + 8
    for register, value in preserved.items():
        uc.reg_write(register, value)
    uc.reg_write(UC_X86_REG_ESP, sp)
    entry_registers = {register: uc.reg_read(register) for register in
                       (*preserved, UC_X86_REG_EAX, UC_X86_REG_ECX, UC_X86_REG_ESP)}
    entry_stack = bytes(uc.mem_read(sp, 16))
    results = []
    for invocation in range(case.repeat):
        uc.mem_write(sp, entry_stack)
        for register, value in entry_registers.items():
            uc.reg_write(register, value)
        try:
            uc.emu_start(entry, STOP, count=10000000)
        except UcError:
            if not faults:
                raise
        if faults:
            break
        assert uc.reg_read(UC_X86_REG_EIP) == STOP, "instruction budget exhausted"
        assert uc.reg_read(UC_X86_REG_ESP) == expected_sp
        assert all(uc.reg_read(register) == value for register, value in preserved.items())
        results.append(uc.reg_read(UC_X86_REG_EAX))
    return {"result": uc.reg_read(UC_X86_REG_EAX) if not faults else None,
            "events": events, "faults": faults, "position": position, "results": tuple(results),
            "local": bytes(uc.mem_read(STATE, 0x10000)), "global": bytes(uc.mem_read(GLOBAL, 0x500000 - GLOBAL)),
            "data": bytes(uc.mem_read(DATA, 0x10000))}


def cases():
    for manager, old, owner, flags, same in product((LOCAL, GLOBAL), (False, True), (False, True),
                                                 (0, 1, 0x10, 0xFF), (False, True)):
        yield Case(manager=manager, old=old, owner=owner, flags=flags,
                   stored_name=b"track1.wav" if same else b"previous.wav")
    for opened, allocation, seek, read, limit in product((0, 0x1234, 0xFFFFFFFF), (0, ALLOCATION),
            (0, 0xFFFFFFFF), (0, 1), (0, 1, None)):
        yield Case(opened=opened, allocation=allocation, seek_result=seek, read_result=read, read_limit=limit)
    for index, size in product((-1, 0, 15, 16, 0x40000000, -0x40000000), (0, 1, 17, 255)):
        yield Case(index=index, size=size)
    for stage in ("free", "open", "find", "seek", "malloc", "read", "close"):
        yield Case(mutations=((stage, ((LOCAL + 0x1F84, ALT_TABLE),)),))
        yield Case(mutations=((stage, ((TABLE + 52 + 20, 51),)),))
    yield Case(mutations=(("free", ((LOCAL + 0x1EC4, ALLOCATION + 0x1000), (LOCAL + 0x610, 0))),))
    yield Case(mutations=(("close", ((LOCAL + 0x1EC4, ALLOCATION + 0x1000),)),))
    for delta in (0, 1, 3, -1):
        yield Case(source_delta=delta, old=False, flags=0)
    for length in (0, 1, 127, 255, 256, 300):
        yield Case(name=b"X" * length, old=False, flags=0)
    for manager, allocation, old in product((LOCAL, GLOBAL, 0), (0, ALLOCATION), (False, True)):
        yield Case(operation="table", manager=manager, allocation=allocation, old=old)
    yield Case(operation="table", mutations=(("archive", ((LOCAL + 0x1F84, ALT_TABLE),)),))
    for manager, limit in product((LOCAL, GLOBAL), (None, 0)):
        yield Case(manager=manager, repeat=3, old=False, read_limit=limit, read_result=0)
    for name, manager in product((b"first.wav", b"track1.wav", b"Last.WAV", b"last.wav", b"missing.wav",
            b"dir/track1.wav", b"dir\\track1.wav", b"dir/other\\track1.wav", b"dir\\other/track1.wav",
            b"dir/", b"", b"dir//track1.wav"), (LOCAL, GLOBAL)):
        yield Case(name=name, manager=manager, integrated=True)
    yield Case(integrated=True, empty_table=True)
    yield Case(integrated=True, table_present=False)
    for stage in ("open", "seek", "malloc", "read", "close"):
        yield Case(integrated=True, mutations=((stage, ((LOCAL + 0x1F84, ALT_TABLE),)),))
    randomizer = random.Random(0x43D7D0)
    for trial in range(48):
        size = randomizer.randrange(512)
        yield Case(integrated=True, size=size, index=randomizer.randrange(16),
                   name=randomizer.choice((b"first.wav", b"track1.wav", b"Last.WAV", b"missing.wav")),
                   read_limit=randomizer.randrange(size + 1), read_result=trial & 1)


def verify(case, result):
    events = result["events"]
    if result["faults"]:
        return
    if case.operation == "table":
        assert result["result"] == (0 if case.allocation else 0xFFFFFFFF)
        assert [event[0] for event in events] == ["archive"]
        return
    read = next((event for event in events if event[0] == "read"), None)
    if read:
        assert result["result"] == 0
        assert [event[0] for event in events][-1] == "close"
        offset = 0x6000
        assert result["data"][offset:offset + read[5]] == FILE_DATA[read[4]:read[4] + read[5]]
        assert result["data"][offset + read[5]:offset + read[5] + 16] == b"\xA5" * 16
    if not events:
        assert result["result"] == 0
    if case.repeat > 1:
        assert result["results"] == (0,) * case.repeat
        assert sum(event[0] == "open" for event in events) == (1 if case.manager == GLOBAL else case.repeat)
    if case.integrated and not case.mutations:
        seek = next((event for event in events if event[0] == "seek"), None)
        if seek:
            # A forward slash anywhere takes priority over backslashes; only
            # absent '/' causes a backslash search. Missing names choose 0.
            basename = case.name.rsplit(b"/", 1)[-1] if b"/" in case.name else case.name.rsplit(b"\\", 1)[-1]
            names = (b"first.wav", b"track1.wav", b"Last.WAV")
            index = names.index(basename) if basename in names and not case.empty_table else 0
            assert seek[2] == 0x90 + index * 64


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--oracle", type=Path, default=ROOT / "matching2/build/oracle/th10.exe")
    options = parser.parse_args()
    config = load_manifest(ROOT / "matching2/msvc/regions.json")
    load_oracle(options.oracle, config)
    image = PEImage(options.oracle.read_bytes())
    with tempfile.TemporaryDirectory(prefix="th10-music-cache-") as temporary:
        compiled = compile_candidates(Path(temporary), config)
        total = integrated = faults = 0
        for index, case in enumerate(cases()):
            expected, actual = execute(image, None, case), execute(image, compiled, case)
            differences = tuple(key for key in expected if expected[key] != actual[key])
            assert not differences, (index, case, differences, expected["events"], actual["events"],
                                     expected["faults"], actual["faults"])
            verify(case, actual)
            total += 1
            integrated += case.integrated
            faults += bool(actual["faults"])
        print(f"PASS: {total} music-cache/table-loader comparisons, including {integrated} actual basename "
              f"lookups and {faults} matching faults. Candidate modules: "
              f"{', '.join(str(len(module.data)) for module in compiled[0].values())} bytes. "
              "Native MSVC frames/bytes and live file I/O remain unverified.")


if __name__ == "__main__":
    main()
