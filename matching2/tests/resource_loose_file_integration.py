#!/usr/bin/env python3
"""Run recovered loose-file resource calls through FileHandle and ReadWhole.

Windows imports and allocation are scripted. Open/path resolution and the
maintained ReadWhole source are freshly compiled; resource candidates call
them directly. Real retail Read/Tell/Seek and CRT searches also execute.
"""

import argparse
from dataclasses import dataclass
from itertools import product
from pathlib import Path
import struct
import subprocess
import tempfile

from unicorn import UC_HOOK_CODE
from unicorn.x86_const import UC_X86_REG_ECX
from dat_archive_integration_differential import (
    Execution, Fixture, ROOT, CANDIDATE, OUTPUT, QUERY, FILE, PEImage,
    load_manifest, load_oracle, load_candidate)
from resource_paths_differential import COUNT, compile_candidates as compile_resources
from file_open_resolve_differential import compile_candidates as compile_files

RESOURCE_BASE, FILE_BASE, WHOLE = CANDIDATE, CANDIDATE + 0x20000, CANDIDATE + 0x26000
IMPORTS = {0x4660C4: CANDIDATE + 0xF000, 0x4660C8: CANDIDATE + 0xF100,
           0x4660CC: CANDIDATE + 0xF200, 0x4660D0: CANDIDATE + 0xF300,
           0x4660D8: CANDIDATE + 0xF400, 0x4660DC: CANDIDATE + 0xF500}
CREATE, SEEK, CLOSE, READ, SIZE, MODULE = IMPORTS.values()


@dataclass(frozen=True)
class Case:
    payload: bytes = b"loose-file payload"
    path: bytes = b"loose.bin"
    capacity: int = 0xFFFFFFFF
    initial_position: int = 0
    initial_handle: int = 0x1234
    initial_access: int = 0x80000000
    opened_handle: int = 0x1234
    allocation_failure: bool = False
    read_boolean: int = 1
    read_limit: object = None
    sizes: tuple = ()
    seek_failure: bool = False
    mutate_at: object = None
    changed_handle: object = None
    changed_access: object = None


def compile_candidates(directory, config):
    files = compile_files(directory, config, FILE_BASE)
    file_open = files["file_handle_open.cpp"].symbols["?Open@FileHandle@@UAEEPBD0@Z"]
    resources, bodies = compile_resources(directory, config, RESOURCE_BASE, {
        "?Open@FileHandle@@UAEEPBD0@Z": file_open,
        "?ReadWhole@FileHandle@@QAEPAXI@Z": WHOLE})
    obj = directory / "maintained-file.obj"
    subprocess.run([
        "clang++", "--target=i686-pc-windows-msvc", "-std=c++03", "-O2", "-mno-sse", "-mno-sse2",
        "-fno-exceptions", "-fno-rtti", "-fno-stack-protector", "-ffunction-sections",
        "-I", str(ROOT / "matching2/msvc/include"), "-c",
        str(ROOT / 'matching2/msvc' / json.loads(project_support(ROOT / 'matching2/msvc', 'regions.json').read_text()).get('compilation_units', {}).get('src/pack/file/file_handle.cpp', 'src/pack/file/file_handle.cpp')), "-o", str(obj)],
        check=True, timeout=60)
    bodies[WHOLE] = load_candidate(obj, config, "?ReadWhole@FileHandle@@QAEPAXI@Z", code_address=WHOLE)
    bodies.update((module.base, module.data) for module in files.values())
    return resources, bodies, file_open


class LooseExecution(Execution):
    def __init__(self, image, modules, resources, file_open, case):
        self.case = case
        self.resources = resources
        self.file_open = file_open
        self.file_pointer = FILE
        self.size_calls = 0
        source = Fixture("loose-file", (), case.payload, b"", (), 0)
        super().__init__(image, modules, source, 0 if case.allocation_failure else None)
        self.position = case.initial_position
        self.words(COUNT, 0)
        # Undo the DAT harness's virtual-I/O substitutes. All these methods
        # now run their real bodies, down to the scripted Windows imports.
        self.uc.mem_write(0x46F230, image.read(0x46F230, 32))
        self.words(FILE, 0x46F230, case.initial_handle, case.initial_access)
        for slot, address in IMPORTS.items():
            self.words(slot, address)
        for address in (*IMPORTS.values(), 0x435370, file_open, 0x435580, WHOLE):
            self.uc.hook_add(UC_HOOK_CODE, self.hook, begin=address, end=address)

    def state(self):
        return struct.unpack("<2I", self.uc.mem_read(self.file_pointer + 4, 8))

    def mutate(self, stage):
        if self.case.mutate_at == stage:
            if self.case.changed_handle is not None:
                self.words(self.file_pointer + 4, self.case.changed_handle)
            if self.case.changed_access is not None:
                self.words(self.file_pointer + 8, self.case.changed_access)

    def hook(self, uc, address, size, context):
        case = self.case
        if address in (0x435370, self.file_open, 0x435580, WHOLE):
            self.file_pointer = uc.reg_read(UC_X86_REG_ECX)
        elif address == MODULE:
            module, output, capacity = self.args(3)
            assert (module, capacity) == (0, 260)
            self.events.append(("module", module, capacity, self.state()))
            path = b"C:\\game\\th10.exe"
            uc.mem_write(output, path + b"\0")
            self.finish(len(path), 12)
        elif address == CREATE:
            path, access, share, security, disposition, flags, template = self.args(7)
            self.events.append(("create", self.string(path), access, share, security,
                                disposition, flags, template, self.state()))
            self.position = 0
            self.finish(case.opened_handle, 28)
        elif address == SIZE:
            handle, high = self.args(2)
            assert high == 0
            reported = case.sizes[min(self.size_calls, len(case.sizes) - 1)] if case.sizes else len(case.payload)
            self.events.append(("size", handle, reported, self.state()))
            self.mutate("size" + str(self.size_calls))
            self.size_calls += 1
            self.finish(reported, 8)
        elif address == SEEK:
            handle, distance, high, origin = self.args(4)
            assert high == 0 and origin in (0, 1)
            self.events.append(("seek", handle, distance, origin, self.position, self.state()))
            if not case.seek_failure:
                if origin == 0:
                    self.position = distance
                else:
                    assert distance == 0
            self.mutate("seek")
            self.finish(0xFFFFFFFF if case.seek_failure else self.position, 16)
        elif address == READ:
            handle, output, requested, count, overlapped = self.args(5)
            assert overlapped == 0
            amount = requested if case.read_limit is None else min(requested, case.read_limit)
            data = case.payload[self.position:self.position + amount]
            self.events.append(("read", handle, output, requested, self.position, len(data), self.state()))
            if data:
                uc.mem_write(output, data)
            self.position += len(data)
            self.words(count, len(data))
            self.mutate("read")
            self.finish(case.read_boolean, 20)
        elif address == CLOSE:
            handle, = self.args(1)
            self.events.append(("close", handle, self.state()))
            self.mutate("close")
            self.finish(0, 4)
        else:
            super().hook(uc, address, size, context)

    def run(self, operation, supplied):
        self.uc.mem_write(QUERY, self.case.path + b"\0")
        self.uc.mem_write(OUTPUT, b"\xA5" * 0x10000)
        if operation == "whole":
            return self.call(WHOLE if self.recovered else 0x435580, [self.case.capacity], {UC_X86_REG_ECX: FILE})
        if self.recovered:
            symbol = "_Resource_LoadFile_00435800@8" if operation == "load" else "_Resource_GetFileSize_004358e0@4"
            args = [QUERY, OUTPUT if supplied else 0] if operation == "load" else [QUERY]
            return self.call(self.resources.symbols[symbol], args)
        args = [OUTPUT if supplied else 0] if operation == "load" else []
        return self.call(0x435800 if operation == "load" else 0x4358E0, args, {UC_X86_REG_ECX: QUERY})

    def snapshot(self):
        result = super().snapshot()
        result.update(file=self.state(), sizes=self.size_calls,
                      output=bytes(self.uc.mem_read(OUTPUT, 0x10000)))
        return result


def cases():
    for size, handle, allocate, limit, boolean in product((0, 1, 3, 64, 4096),
            (0xFFFFFFFF, 0, 0x1234), (False, True), (None, 0, 2), (0, 1)):
        yield Case(payload=bytes(i & 255 for i in range(size)), opened_handle=handle,
                   allocation_failure=allocate, read_limit=limit, read_boolean=boolean)
    for stage, handle, access in product(("size0", "size1", "seek", "read", "close"),
                                         (0xFFFFFFFF, 0x5678), (0, 0x80000000)):
        yield Case(mutate_at=stage, changed_handle=handle, changed_access=access)
    for sizes in ((7, 8), (8, 7), (0, 0), (32, 32)):
        yield Case(sizes=sizes)
    for path in (b"sub/loose.bin", b"C:\\loose.bin", b"name:part", b"", b"\\rooted.bin"):
        yield Case(path=path)
    yield Case(seek_failure=True)


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
    with tempfile.TemporaryDirectory(prefix="th10-loose-file-") as temporary:
        resources, modules, file_open = compile_candidates(Path(temporary), config)
        counts = {"load": 0, "size": 0, "whole": 0}
        scenarios = [(operation, case, supplied) for case in cases()
                     for operation in ("load", "size") for supplied in ((False, True) if operation == "load" else (False,))]
        scenarios.extend(("whole", Case(initial_handle=handle, initial_access=access,
                                         initial_position=position, capacity=capacity), False)
                         for handle, access, position, capacity in product(
                             (0xFFFFFFFF, 0, 0x1234), (0, 0x80000000, 0x40000000),
                             (0, 3, 64), (0, 16, 17, 0xFFFFFFFF)))
        observed_partial_read = observed_ignored_read_failure = observed_leak = False
        for index, (operation, case, supplied) in enumerate(scenarios):
            retail = LooseExecution(image, {}, None, file_open, case)
            recovered = LooseExecution(image, modules, resources, file_open, case)
            expected, actual = retail.run(operation, supplied), recovered.run(operation, supplied)
            assert expected == actual, (index, operation, case, "result", expected, actual)
            expected_state, actual_state = retail.snapshot(), recovered.snapshot()
            differences = tuple(key for key in expected_state if expected_state[key] != actual_state[key])
            assert not differences, (index, operation, case, differences, retail.events, recovered.events)
            assert actual_state["output"] == b"\xA5" * 0x10000, "loose-file branch used caller output"
            if operation != "size" and actual:
                read = next(event for event in recovered.events if event[0] == "read")
                requested, start, count = read[3:6]
                assert count > 0
                assert bytes(recovered.uc.mem_read(actual, count)) == case.payload[start:start + count]
                assert bytes(recovered.uc.mem_read(actual + count, requested - count + 32)) == b"\xA5" * (requested - count + 32)
                observed_partial_read |= count < requested
                observed_ignored_read_failure |= not case.read_boolean
            if operation == "load" and case.sizes == (7, 8):
                assert actual == 0 and not recovered.allocations, "file growth must reject the capacity"
            if operation == "whole" and case.initial_handle == 0xFFFFFFFF and case.initial_access == 0x80000000:
                assert actual == 0
                assert len(recovered.allocations) == 1 and recovered.allocations[0][1] == 0
                assert not any(event[0] == "free" for event in recovered.events), "failed Seek leaks retail's buffer"
                observed_leak = True
            counts[operation] += 1
        assert observed_partial_read and observed_ignored_read_failure and observed_leak
        print(f"PASS: {counts['load']} loose-file resource loads, {counts['size']} resource size queries, "
              f"and {counts['whole']} direct ReadWhole calls agree with retail. "
              "Five C++ functions execute together with scripted Windows imports; native MSVC "
              "byte/frame matching and Windows exception dispatch remain unverified.")


if __name__ == "__main__":
    main()
