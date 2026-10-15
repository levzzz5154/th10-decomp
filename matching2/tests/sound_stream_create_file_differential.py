#!/usr/bin/env python3
"""Compare the complete file-backed stream factory with retail instruction bodies."""
import argparse
from dataclasses import dataclass
from itertools import product
from pathlib import Path
import struct
import subprocess
import tempfile

from unicorn.x86_const import UC_X86_REG_EAX, UC_X86_REG_ECX, UC_X86_REG_EDX, UC_X86_REG_ESI
from sound_stream_create_memory_differential import (
    Case as MemoryCase, Execution as MemoryExecution, compile_initializers, COMMON, SYMBOLS,
    ALLOCATE, FREE, IID, FRAME_HANDLER, CONSTRUCT, PUBLISHED, OWNER, RECORD, ALT_RECORD,
    SOURCE, DESTINATION, ROOT, CANDIDATE, STOP, STATE, OUTPUT, PEImage, load_manifest, load_oracle, difference)
from sound_stream_initialize_differential import HEAP
from music_cursor_open_differential import OPEN_SYMBOL
from coff_module import load_module

PATH = STATE + 0x3200
OPEN, CREATE_FILE, CLOSE_FILE = STOP + 0x2000, STOP + 0x2100, STOP + 0x2200
FACTORY_SYMBOL = "_SoundStream_CreateFile_0044c8f0@48"


@dataclass(frozen=True)
class Case(MemoryCase):
    filename: int = PATH
    handle: int = 0xABCD1234
    open_result: int = 0
    mock_mode: int = 1


def compile_candidates(directory, asynchronous=True):
    initializers = compile_initializers(directory)
    obj = directory / "cursor-open.obj"
    subprocess.run([*COMMON, "-c", str(ROOT / "matching2/reference/semantic_candidates/music_cursor_open.cpp"),
                    "-o", str(obj)], check=True, timeout=60)
    opener = load_module(obj, CANDIDATE + 0x9000,
                         {"_g_music_create_file": 0x4660C4, "_g_music_seek_file": 0x4660C8, "_g_music_file_base": 0x4977A4})
    obj = directory / "create-file.obj"
    common = [item for item in COMMON if item != "-fno-exceptions"]
    subprocess.run([*common, "-fexceptions", "-fcxx-exceptions", *(["-fasync-exceptions"] if asynchronous else []), "-c",
                    str(ROOT / "matching2/reference/semantic_candidates/sound_stream_create_file.cpp"),
                    "-o", str(obj)], check=True, timeout=60)
    bindings = {"_SoundBuffer_Allocate": ALLOCATE, "_SoundBuffer_Free": FREE,
                "_g_wave_notification_iid": IID, "___CxxFrameHandler3": FRAME_HANDLER, "_g_music_close_file": 0x4660CC}
    unit = load_module(obj, CANDIDATE + 0xA000, dict(bindings, **{SYMBOLS["single"]: CONSTRUCT, OPEN_SYMBOL: OPEN}))
    full = load_module(obj, CANDIDATE + 0xC000, dict(bindings, **{
        SYMBOLS["single"]: initializers[1]["initializers_full"].symbols[SYMBOLS["single"]], OPEN_SYMBOL: opener.symbols[OPEN_SYMBOL]}))
    return initializers, unit, full, opener


class Execution(MemoryExecution):
    factory_symbol = FACTORY_SYMBOL
    retail_entry = 0x44C8F0
    retail_handler = 0x46533B

    def __init__(self, image, compiled=None):
        super().__init__(image, compiled)
        self.open_entries = {0x44DBF0, OPEN}
        if compiled:
            self.open_entries.add(compiled[3].symbols[OPEN_SYMBOL])

    def initialize(self, case):
        super().initialize(case)
        self.uc.mem_write(PATH, b"thbgm.dat\0")
        self.words(0x4660C4, CREATE_FILE)
        self.words(0x4660CC, CLOSE_FILE)

    def factory_arguments(self, case):
        return (case.owner, case.filename, *case.algorithm, case.segment_count,
                case.segment_bytes, case.notification_event, case.record)

    def extra_hook_addresses(self):
        return (*self.open_entries, CREATE_FILE, CLOSE_FILE)

    def hook(self, machine, address, size, context):
        case = self.case
        if address in self.open_entries:
            retail = address == 0x44DBF0
            if retail:
                cursor, mode, filename, record = (self.uc.reg_read(register) for register in
                    (UC_X86_REG_ESI, UC_X86_REG_EAX, UC_X86_REG_ECX, UC_X86_REG_EDX))
            else:
                cursor, mode, filename, record = self.args(4)
            self.event("cursor-open", cursor, mode, filename, record)
            assert mode == 1
            if not case.integrated:
                if cursor:
                    self.words(cursor + 0x78, case.mock_mode)
                    self.words(cursor + 0x90, record)
                    self.words(cursor + 0x8C, case.handle)
                    self.words(cursor + 8, case.end)
                    self.words(cursor + 0x2C, case.end)
                self.finish(case.open_result, 0 if retail else 16)
        elif address == CREATE_FILE:
            values = self.args(7)
            self.event("create-file", *values)
            assert values[1:] == (0x80000000, 1, 0, 3, 0x08000080, 0)
            self.finish(case.handle, 28)
        elif address == CLOSE_FILE:
            handle, = self.args(1)
            self.event("close-file", handle)
            self.finish(0, 4)
        else:
            super().hook(machine, address, size, context)


def cases():
    for result, mode, handle in product((0, 1, 0x80070057, 0xFFFFFFFF), (0, 1, 2), (0, 0xFFFFFFFF, 0xABCD1234)):
        yield Case(open_result=result, mock_mode=mode, handle=handle)
    for count, segment, flags in product((0, 1, 16, 31), (0, 7, 0x80000001), (0, 0xFFFFFFFF)):
        yield Case(segment_count=count, segment_bytes=segment, flags=flags)
    for create, query, notice in product((0, 1, 0x80070057), (0, 1, 0x80004005), (0, 1, 0x80004005)):
        yield Case(create_results=(create,), query_results=(query,), notice_results=(notice,))
    for kwargs in ({"owner": 0}, {"device": 0}, {"output": 0}, {"record": 0},
                   {"fail_allocate": 1}, {"fail_allocate": 1, "open_result": 1}, {"fail_allocate": 2}, {"fail_allocate": 3},
                   {"create_writes": False}, {"query_writes": False}, {"query_value": 0},
                   {"notify_after_set": 0}, {"constructor_value": 0}, {"buffer_after_query": 0},
                   {"description_writes": ((4, 0x12345678), (8, 0xFFEEDDCC), (32, 0x55555555))}):
        yield Case(**kwargs)
    yield Case(open_result=1, mutations=(("close-file", ((HEAP + 16 + 0x8C, 0),)),))
    for handle, filename, bits, status in product((0, 0xFFFFFFFF, 0xABCD1234), (0, PATH), (8, 16), (0, 2)):
        yield Case(integrated=True, handle=handle, filename=filename, bits=bits, status=status)
    for counts in ((0,), (3,), (100,), (None,), ("requested",)):
        yield Case(integrated=True, file_counts=counts, api_result=0)
    for kwargs in ({"owner": 0}, {"device": 0}, {"output": 0}, {"record": 0},
                   {"fail_allocate": 1}, {"fail_allocate": 2}, {"fail_allocate": 3}, {"fail_allocate": 4},
                   {"status_result": 0x80004005}, {"lock_result": 0x80070057},
                   {"create_results": (0x80004005,)}, {"query_results": (0x80004005,)},
                   {"notice_results": (0x80004005,)}):
        yield Case(integrated=True, **kwargs)
    for trigger, writes in (
            ("create-file", ((HEAP + 16 + 0x7C, 1), (HEAP + 16 + 0x80, SOURCE))),
            ("seek", ((HEAP + 16 + 0x90, ALT_RECORD),)),
            ("create-file", ((OWNER, 0),)),
            ("create", ((HEAP + 16 + 0x90, ALT_RECORD),)),
            ("read", ((HEAP + 16 + 8, 123),))):
        yield Case(integrated=True, mutations=((trigger, writes),))


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
    with tempfile.TemporaryDirectory(prefix="th10-create-file-stream-") as temporary:
        compiled = compile_candidates(Path(temporary))
        totals, faults = [0, 0], [0, 0]
        for case in cases():
            expected, actual = Execution(image).execute(case), Execution(image, compiled).execute(case)
            assert actual == expected, (case, difference(expected, actual))
            index = int(case.integrated)
            totals[index] += 1
            faults[index] += bool(expected["faults"])
        observed = Execution(image, compiled).execute(Case(integrated=True, filename=0))
        close, = (event for event in observed["events"] if event[0] == "close-file")
        assert close[1] == 0xA5A5A5A5 and observed["freed"] == [HEAP + 16]
        assert struct.unpack_from("<I", observed["memory"][0], PUBLISHED - STATE)[0] == 0xABCDEF00
        print(f"PASS: {totals[0]} file-stream factory unit comparisons ({faults[0]} faults), "
              f"{totals[1]} with executing open/initializer/refill/cursors ({faults[1]} faults), "
              f"independent failed-open ownership check; {len(compiled[1].data)} Clang module bytes. "
              "Native MSVC frames/bytes and Windows exception dispatch remain unverified.")


if __name__ == "__main__":
    main()
