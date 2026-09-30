#!/usr/bin/env python3
"""Compare cached-music launch with actual memory creation or file-track selection."""
import argparse
from dataclasses import dataclass
from itertools import product
from pathlib import Path
import struct
import subprocess
import tempfile

from unicorn.x86_const import UC_X86_REG_EAX, UC_X86_REG_ECX, UC_X86_REG_ESI
from sound_stream_create_memory_differential import (
    Execution as MemoryExecution, compile_candidates as compile_factory, FACTORY_SYMBOL,
    ROOT, COMMON, CANDIDATE, STOP, STATE, STREAM, SOURCE, RECORD, ALT_RECORD, OWNER, ALT_OWNER,
    PEImage, load_manifest, load_oracle, difference)
from sound_stream_launch_differential import Case as LaunchCase, LaunchHarness, MANAGER, FACTORY
from sound_stream_initialize_differential import CURSOR, ALT_CURSOR, HEAP
from lzss_compressor_differential import DEFAULT_TOOLKIT
from coff_module import load_module

LAUNCH_SYMBOL = "_SoundStream_LaunchCached_0043d950@8"
ARCHIVE_SYMBOL = "?SelectArchiveEntry@PathName_0043d2a0@@QAEHPAUPlatformD790ArchiveOwner@@@Z"
RECORD_SYMBOL = "?Select@PlatformStreamState_0044DCA0@@QAEHPAUPlatformStreamRecord_0044DCA0@@@Z"
FIND_SYMBOL = "?FindBasenameSlot_0043d2a0@PathName_0043d2a0@@QAEHPAX@Z"
SELECT = STOP + 0x2B00
MUSIC_RECORDS = STATE + 0x3400


@dataclass(frozen=True)
class Case(LaunchCase):
    index: int = 1
    enabled: int = 1
    mode: int = 0x10
    cached_data: int = SOURCE
    table: int = MUSIC_RECORDS
    track_name: bytes = b"folder/track1.wav"
    select_result: int = 0
    lookup: object = None


def slot(offset, index=1):
    return (MANAGER + offset + index * 4) & 0xFFFFFFFF


def compile_candidates(directory):
    factory = compile_factory(directory)
    copy_source = directory / "strcpy-fixture.cpp"
    copy_source.write_text('extern "C" char* __cdecl strcpy(char* to, const char* from) {\n'
                           '    char* result = to;\n'
                           '    while ((*to++ = *from++) != 0) {}\n'
                           '    return result;\n}\n')
    obj = directory / "strcpy.obj"
    subprocess.run([*COMMON, "-c", str(copy_source), "-o", str(obj)], check=True, timeout=60)
    copy = load_module(obj, CANDIDATE + 0x16000, {})
    obj = directory / "basename.obj"
    subprocess.run([*COMMON, "-I", str(ROOT / "matching2/msvc/include"),
                    "-isystem", str(DEFAULT_TOOLKIT / "include"), "-c",
                    str(ROOT / "matching2/msvc/src/platform/path.cpp"), "-o", str(obj)], check=True, timeout=60)
    find = load_module(obj, CANDIDATE + 0x14000, {
        "_strcpy": copy.symbols["_strcpy"], "_strcmp": 0x45BF30, "_asm_strrchr_00452930": 0x452930})
    obj = directory / "select-record.obj"
    subprocess.run([*COMMON, "-c", str(ROOT / "matching2/msvc/src/game/platform_select_stream_record_0044dca0.cpp"),
                    "-o", str(obj)], check=True, timeout=60)
    select_record = load_module(obj, CANDIDATE + 0x10000,
                                {"_data_004977a4": 0x4977A4, "__imp__SetFilePointer@16": 0x4660C8})
    obj = directory / "select-archive.obj"
    subprocess.run([*COMMON, "-c", str(ROOT / "matching2/msvc/src/game/recovery_select_archive_entry_0043d790.cpp"),
                    "-o", str(obj)], check=True, timeout=60)
    select_archive = load_module(obj, CANDIDATE + 0x12000,
                                 {FIND_SYMBOL: find.symbols[FIND_SYMBOL], RECORD_SYMBOL: select_record.symbols[RECORD_SYMBOL]})
    obj = directory / "launch-cached.obj"
    subprocess.run([*COMMON, "-c", str(ROOT / "matching2/reference/semantic_candidates/sound_stream_launch_cached.cpp"),
                    "-o", str(obj)], check=True, timeout=60)
    bindings = {"_g_music_enabled": 0x491D63, "_g_sound_mode_flags": 0x491D78,
                "_g_music_create_event": 0x466120, "_g_music_create_thread": 0x466118,
                "_g_music_worker_argument": 0x491C70, "_g_music_stream_algorithm": 0x46A67C,
                "_SoundStream_Worker_0043e3a0@4": 0x43E3A0}
    unit = load_module(obj, CANDIDATE + 0xE000,
                       dict(bindings, **{FACTORY_SYMBOL: FACTORY, ARCHIVE_SYMBOL: SELECT}))
    full = load_module(obj, CANDIDATE + 0xF000, dict(bindings, **{
        FACTORY_SYMBOL: factory[2].symbols[FACTORY_SYMBOL], ARCHIVE_SYMBOL: select_archive.symbols[ARCHIVE_SYMBOL]}))
    return factory, unit, full, select_record, select_archive, find, copy


class Execution(LaunchHarness, MemoryExecution):
    launch_symbol = LAUNCH_SYMBOL
    factory_argument_count = 13

    def __init__(self, image, compiled=None):
        super().__init__(image, compiled)
        self.select_entries = {0x43D790, SELECT}
        self.record_entries = {0x44DCA0}
        self.find_entries = {0x43D2A0}
        if compiled:
            self.select_entries.add(compiled[4].symbols[ARCHIVE_SYMBOL])
            self.record_entries.add(compiled[3].symbols[RECORD_SYMBOL])
            self.find_entries.add(compiled[5].symbols[FIND_SYMBOL])

    def initialize(self, case):
        super().initialize(case)
        self.uc.mem_write(0x491D63, bytes([case.enabled]))
        self.uc.mem_write(0x491D78, bytes([case.mode]))
        self.words(MANAGER + 0x1F80, 0x12345678, case.table)
        for offset, value in ((0x1E80, case.record), (0x1EC0, case.cached_data),
                              (0x1F00, case.pcm), (0x1F40, case.pcm_bytes)):
            address = slot(offset, case.index)
            if MANAGER <= address < MANAGER + 0xFFFC:
                self.words(address, value)
        name_address = (MANAGER + 0x4108 + case.index * 256) & 0xFFFFFFFF
        if MANAGER <= name_address < MANAGER + 0xFF00:
            self.uc.mem_write(name_address, case.track_name + b"\0")
        for index, name in enumerate((b"first.wav", b"track1.wav", b"Last.WAV", b"")):
            record = (name + bytes(16 - len(name)) + struct.pack("<4I", 0x80 + index * 64, 31 + index, 0, 29 + index) +
                      struct.pack("<HHIIHHH", 1, 2, 44100, 176400, 4, 16, 0) + bytes(2))
            self.uc.mem_write(MUSIC_RECORDS + index * 52, record)
        self.words(STREAM + 0xC, case.reader)

    def cursor_state(self):
        return super().cursor_state(), self.read_words(MANAGER + 0x1F80)

    def launch_extra_hooks(self):
        return (*self.select_entries, *self.record_entries, *self.find_entries)

    def candidate_launch_arguments(self, case):
        return case.manager, case.index

    def retail_launch_arguments(self, case):
        return 0x43D950, (), {UC_X86_REG_ESI: case.manager, UC_X86_REG_EAX: case.index}

    def hook(self, machine, address, size, context):
        case = self.case
        if address in self.select_entries:
            retail = address == 0x43D790
            name = self.uc.reg_read(UC_X86_REG_ECX)
            manager = self.uc.reg_read(UC_X86_REG_EAX) if retail else self.args(1)[0]
            self.event("select-name", manager, name)
            if not case.integrated:
                self.finish(case.select_result, 0 if retail else 4)
        elif address in self.find_entries:
            name, manager = self.uc.reg_read(UC_X86_REG_ECX), self.args(1)[0]
            self.event("find", name, manager)
            if case.lookup is not None:
                self.finish(case.lookup, 4)
        elif address in self.record_entries:
            retail = address == 0x44DCA0
            cursor = self.uc.reg_read(UC_X86_REG_ESI if retail else UC_X86_REG_ECX)
            record = self.uc.reg_read(UC_X86_REG_ECX) if retail else self.args(1)[0]
            self.event("select-record", cursor, record)
        else:
            super().hook(machine, address, size, context)


def cases():
    for rate, alignment, result in product((0, 1, 44100, 48000, 0x7FFFFFFF, 0x80000000, 0xFFFFFFFF),
                                           (0, 1, 2, 4, 0xFFFF), (0, 1, 0x7FFFFFFF, 0x80000000, 0xFFFFFFFF)):
        yield Case(sample_rate=rate, alignment=alignment, factory_result=result)
    for enabled, mode, index in product((0, 1, 0x80), (0, 0x0F, 0x10, 0xFF), (0, 1, 15, 16, 0x40000000, 0xFFFFFFFF)):
        yield Case(enabled=enabled, mode=mode, index=index)
    for event, thread, tid in product((0, 0xABCD1111), (0, 0xABCD2222), (None, 0x1234)):
        yield Case(event_result=event, thread_result=thread, thread_id=tid)
    for result in (0, 1, 0x12345678, 0x80004005, 0xFFFFFFFF):
        yield Case(mode=0, select_result=result)
    for kwargs in ({"owner": 0}, {"manager_device": 0}, {"device": 0}, {"record": 0}, {"manager": 0},
                   {"cached_data": 0}, {"pcm": 0}, {"old_stream": 0}, {"old_thread": 0},
                   {"index": 0x8000000}, {"mode": 0, "index": 0x8000000}):
        yield Case(**kwargs)
    for trigger, writes in (
            ("create-event", ((slot(0x1E80), ALT_RECORD), (RECORD + 0x24, 1), (RECORD + 0x2C, 0))),
            ("create-thread", ((slot(0x1F00), SOURCE + 7), (slot(0x1F40), 13), (slot(0x1EC0), 0))),
            ("create-thread", ((MANAGER + 0x520C, 0), (MANAGER + 0x610, ALT_OWNER))),
            ("create-thread", ((0x46A67C, 1), (0x46A680, 2), (0x46A684, 3), (0x46A688, 4))),
            ("factory", ((MANAGER + 0x1F80, 99),))):
        for result in (0, 0x80004005):
            yield Case(factory_result=result, mutations=((trigger, writes),))
    yield Case(alignment=0, mutations=(("create-thread", ((RECORD + 0x2C, 4),)),))
    for bits, stream, count in product((8, 16), (0, STREAM), (0, 29, 37)):
        yield Case(integrated=True, bits=bits, old_stream=stream, pcm_bytes=count)
    for kwargs in ({"owner": 0}, {"manager_device": 0}, {"device": 0}, {"record": 0}, {"pcm": 0},
                   {"alignment": 0}, {"event_result": 0, "thread_result": 0}, {"cached_data": 0},
                   {"status_result": 0x80004005}, {"lock_result": 0x80070057},
                   {"create_results": (0x80004005,)}, {"query_results": (0x80004005,)},
                   {"notice_results": (0x80004005,)}, {"fail_allocate": 1}, {"fail_allocate": 2},
                   {"fail_allocate": 3}, {"fail_allocate": 4}):
        yield Case(integrated=True, **kwargs)
    for trigger, writes in (
            ("create-thread", ((slot(0x1E80), ALT_RECORD),)),
            ("create-thread", ((slot(0x1F00), SOURCE + 7), (slot(0x1F40), 13))),
            ("create-thread", ((MANAGER + 0x610, ALT_OWNER),)),
            ("create-thread", ((MANAGER + 0x610, 0),)),
            ("create", ((MANAGER + 0x1F80, 99),))):
        yield Case(integrated=True, mutations=((trigger, writes),))
    for buffered, handle, name in product((0, 1, 0xFFFFFFFF), (0, 0xFFFFFFFF, 0x12345678),
            (b"first.wav", b"x/track1.wav", b"x\\Last.WAV", b"missing.wav", b"")):
        yield Case(integrated=True, mode=0, buffered=buffered, file=handle, track_name=name)
    for kwargs in ({"old_stream": 0}, {"reader": 0}, {"table": 0}, {"lookup": 0xFFFFFFFF},
                   {"lookup": 0x40000000}, {"enabled": 0}, {"owner": 0}):
        yield Case(integrated=True, mode=0, buffered=0, **kwargs)
    for trigger, writes in (
            ("find", ((MANAGER + 0x1F84, MUSIC_RECORDS + 52),)),
            ("find", ((STREAM + 0xC, ALT_CURSOR),)),
            ("find", ((MANAGER + 0x5208, 0),)),
            ("seek", ((CURSOR + 0x90, ALT_RECORD), (CURSOR + 8, 123))),
            ("seek", ((CURSOR + 0x8C, 0), (CURSOR + 0x7C, 1)))):
        yield Case(integrated=True, mode=0, buffered=0, mutations=((trigger, writes),))


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--oracle", type=Path, default=ROOT / "matching2/build/oracle/th10.exe")
    options = parser.parse_args()
    config = load_manifest(ROOT / "matching2/msvc/regions.json")
    load_oracle(options.oracle, config)
    image = PEImage(options.oracle.read_bytes())
    with tempfile.TemporaryDirectory(prefix="th10-launch-cached-stream-") as temporary:
        compiled = compile_candidates(Path(temporary))
        totals, faults = [0, 0], [0, 0]
        for case in cases():
            expected, actual = Execution(image).execute(case), Execution(image, compiled).execute(case)
            assert actual == expected, (case, difference(expected, actual))
            index = int(case.integrated)
            totals[index] += 1
            faults[index] += bool(expected["faults"])
        observed = Execution(image, compiled).execute(Case(integrated=True))
        factory, = (event for event in observed["events"] if event[0] == "factory")
        assert factory[1:7] == (MANAGER + 0x5208, 0x10100, OWNER, SOURCE, 37, RECORD)
        assert factory[11:14] == (16, 44100, 0xABCD1111)
        assert struct.unpack_from("<I", observed["manager"], 0x1F80)[0] == 1
        assert not any(event[0] in ("stop-music", "destroy", "post", "close-file") for event in observed["events"])
        failed = Execution(image, compiled).execute(Case(integrated=True, create_results=(0x80004005,)))
        assert failed["result"] == 0xFFFFFFFF
        assert struct.unpack_from("<I", failed["manager"], 0x1F80)[0] == 0x12345678
        assert struct.unpack_from("<II", failed["manager"], 0x5208) == (STREAM, 0xABCD1111)
        selected = Execution(image, compiled).execute(Case(integrated=True, mode=0, buffered=0))
        assert selected["result"] == 0 and not selected["allocated"]
        assert struct.unpack_from("<I", selected["memory"][0], CURSOR + 0x90 - STATE)[0] == MUSIC_RECORDS + 52
        assert struct.unpack_from("<I", selected["manager"], 0x1F80)[0] == 0x12345678
        print(f"PASS: {totals[0]} cached-launch unit comparisons ({faults[0]} faults), "
              f"{totals[1]} with executing memory factory/initializer/refill/cursors or maintained name/record selection "
              f"({faults[1]} faults); independent argument/selection/ownership checks; "
              f"{len(compiled[1].data)} Clang launch bytes. Native MSVC bytes and live threads remain unverified.")


if __name__ == "__main__":
    main()
