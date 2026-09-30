#!/usr/bin/env python3
"""Run public resource operations through the recovered DAT lifecycle.

Registration, resource dispatch and size queries execute with the recovered
archive loader, parser, ciphers, decoder, reader and cleanup. Only file I/O,
allocation and CRT thread-data retrieval are scripted. Each open file keeps
its own archive bytes and seek position. This does not test loose-file I/O,
Windows exception dispatch or native MSVC byte matching.
"""

import argparse
from pathlib import Path
import struct
import tempfile

from unicorn.x86_const import UC_X86_REG_EAX, UC_X86_REG_ECX
from dat_archive_integration_differential import (
    Execution, Entry, compile_modules, fixtures, fixture, ROOT, CANDIDATE,
    OUTPUT, PATH, QUERY, READ, OPEN, FILE_OPEN, FILE_READ, FILE_SIZE,
    FILE_SEEK, FILE_DELETE, PEImage, load_manifest, load_oracle)
from resource_paths_differential import COUNT, ARCHIVES, compile_candidates

RESOURCE_BASE = CANDIDATE + 0x20000
REGISTER = RESOURCE_BASE + 0x2000
TABLE_SLOTS = 8


class ResourceExecution(Execution):
    def __init__(self, image, modules, source, resource_module=None, fail_allocation=None):
        self.files = {}
        self.sources = {}
        self.resource_module = resource_module
        super().__init__(image, modules, source, fail_allocation, archive_address=ARCHIVES)
        self.words(COUNT, 0)
        # Model the zero-initialized global records used by registration.
        self.uc.mem_write(ARCHIVES, bytes(TABLE_SLOTS * 16))

    def count(self):
        return struct.unpack("<I", self.uc.mem_read(COUNT, 4))[0]

    def hook(self, uc, address, size, context):
        file = uc.reg_read(UC_X86_REG_ECX)
        if address == FILE_OPEN:
            path, _ = self.args(2)
            name = self.string(path)
            assert name in self.sources, ("unexpected disk path", name)
            self.source = self.sources[name]
            self.position = 0
        elif address in (FILE_READ, FILE_SIZE, FILE_SEEK):
            assert file in self.files, ("unopened file", hex(file), hex(address))
            self.source, self.position = self.files[file]
        if address in (FILE_OPEN, FILE_READ, FILE_SIZE, FILE_SEEK, FILE_DELETE):
            self.events.append(("file", address, file))
        super().hook(uc, address, size, context)
        if address in (FILE_OPEN, FILE_READ, FILE_SIZE, FILE_SEEK):
            self.files[file] = self.source, self.position
        elif address == FILE_DELETE:
            self.files.pop(file, None)

    def register(self, name, source):
        before = self.count()
        assert before < TABLE_SLOTS
        self.archive = ARCHIVES + before * 16
        self.sources[name] = source
        self.uc.mem_write(PATH, name + b"\0")
        result = (self.call(REGISTER, [PATH]) if self.recovered else
                  self.call(0x4357D0, [], {UC_X86_REG_EAX: PATH})) & 255
        assert result in (0, 1)
        assert self.count() == before + result
        return result

    def resource_load(self, path, supplied):
        self.uc.mem_write(QUERY, path + b"\0")
        self.uc.mem_write(OUTPUT, b"\xA5" * 0x10000)
        output = OUTPUT if supplied else 0
        if self.recovered:
            address = self.resource_module.symbols["_Resource_LoadFile_00435800@8"]
            return self.call(address, [QUERY, output])
        return self.call(0x435800, [output], {UC_X86_REG_ECX: QUERY})

    def resource_size(self, path):
        self.uc.mem_write(QUERY, path + b"\0")
        if self.recovered:
            address = self.resource_module.symbols["_Resource_GetFileSize_004358e0@4"]
            return self.call(address, [QUERY])
        return self.call(0x4358E0, [], {UC_X86_REG_ECX: QUERY})

    def snapshot(self):
        result = super().snapshot()
        result.update(count=self.count(),
                      table=bytes(self.uc.mem_read(ARCHIVES, TABLE_SLOTS * 16)),
                      files=tuple((pointer, source.label, position)
                                  for pointer, (source, position) in sorted(self.files.items())))
        return result


def compare(retail, recovered, label):
    expected, actual = retail.snapshot(), recovered.snapshot()
    assert expected == actual, (label, tuple(key for key in expected if expected[key] != actual[key]))


def check_resource(retail, recovered, path, match, label):
    before = retail.snapshot()
    expected_size = len(match.payload) if match else 0
    assert retail.resource_size(path) == recovered.resource_size(path) == expected_size, (label, "size")
    assert retail.snapshot() == before, (label, "size changed state")
    compare(retail, recovered, (label, "size"))
    for supplied in (False, True):
        result = retail.resource_load(path, supplied)
        actual = recovered.resource_load(path, supplied)
        assert actual == result, (label, "return", supplied)
        compare(retail, recovered, (label, "load", supplied))
        if match is None or (not match.payload and not match.compressed):
            assert result == 0, (label, "empty/missing")
        else:
            assert result, label
            for execution in (retail, recovered):
                assert bytes(execution.uc.mem_read(result, len(match.payload))) == match.payload, label
                assert bytes(execution.uc.mem_read(result + len(match.payload), 32)) == b"\xA5" * 32, label
        assert bytes(retail.uc.mem_read(OUTPUT, 0x10000)) == bytes(recovered.uc.mem_read(OUTPUT, 0x10000))


def close_slot(retail, recovered, index, reset=False):
    for execution in (retail, recovered):
        execution.archive = ARCHIVES + index * 16
        execution.close(reset)
    compare(retail, recovered, ("close", index, reset))


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--oracle", type=Path, default=ROOT / "matching2/build/oracle/th10.exe")
    options = parser.parse_args()
    config = load_manifest(ROOT / "matching2/msvc/regions.json")
    load_oracle(options.oracle, config)
    image = PEImage(options.oracle.read_bytes())
    parameters = [struct.unpack("<BB2xii", image.read(0x474BD8 + index * 12, 12)) for index in range(8)]
    with tempfile.TemporaryDirectory(prefix="th10-resource-integration-") as temporary:
        directory = Path(temporary)
        modules = compile_modules(directory, config)
        resource_module, resource_bodies = compile_candidates(directory, config, RESOURCE_BASE, {
            "_DatArchive_Read_00434dd0@12": READ,
            "_DatArchive_Open_00434c30@8": OPEN})
        modules.update(resource_bodies)

        def executions(source, failure=None):
            return (ResourceExecution(image, {}, source, fail_allocation=failure),
                    ResourceExecution(image, modules, source, resource_module, failure))

        singles = registrations = reads = sizes = failures = cleanups = 0
        sources = [*fixtures(parameters), fixture("nested-paths", (
            Entry(b"dir/nested.bin", b"nested payload", True),
            Entry(b"dir//raw.bin", b"repeated slash"),
            Entry(b"trailing/", b"trailing slash")), parameters)]
        for source in sources:
            retail, recovered = executions(source)
            assert retail.register(b"fixture.dat", source) == recovered.register(b"fixture.dat", source) == 1
            for execution in (retail, recovered):
                execution.verify_index("disk")
            compare(retail, recovered, (source.label, "register"))
            registrations += 1
            for item in (*source.entries, Entry(b"missing.file", b"")):
                match = next((entry for entry in source.entries if entry.name.lower() == item.name.lower()), None)
                check_resource(retail, recovered, b"fixture/" + item.name.swapcase(), match,
                               (source.label, item.name))
                reads += 2
                sizes += 1
            for reset in (bool(singles & 1), not bool(singles & 1)):
                close_slot(retail, recovered, 0, reset)
                assert retail.count() == recovered.count() == 1
                cleanups += 1
            assert not retail.files and not recovered.files
            singles += 1

        # Distinct files retain independent positions. A duplicate registered
        # archive name must still resolve to the first table entry.
        first = fixture("multi-first", (Entry(b"dir/shared.bin", b"first payload", True),
                                        Entry(b"raw.bin", b"first raw")), parameters)
        second = fixture("multi-second", (Entry(b"dir/shared.bin", b"different second payload"),
                                          Entry(b"compressed.bin", b"second compressed", True)), parameters)
        duplicate = fixture("multi-duplicate", (Entry(b"dir/shared.bin", b"shadowed third archive"),), parameters)
        retail, recovered = executions(first)
        for name, source in ((b"first.dat", first), (b"second.dat", second), (b"first.dat", duplicate)):
            assert retail.register(name, source) == recovered.register(name, source) == 1
            for execution in (retail, recovered):
                execution.verify_index("disk")
            compare(retail, recovered, (source.label, "register"))
            registrations += 1
        for turn in range(3):
            for prefix, source in ((b"first/", first), (b"second/", second)):
                for item in source.entries:
                    check_resource(retail, recovered, prefix + item.name.swapcase(), item,
                                   ("multiple", turn, prefix, item.name))
                    reads += 2
                    sizes += 1
        # Closing the middle record does not close either neighboring file.
        for index in (1, 2, 0):
            close_slot(retail, recovered, index, bool(index & 1))
            cleanups += 1
        assert retail.count() == recovered.count() == 3
        assert not retail.files and not recovered.files

        # Avoid the cipher scratch failure that makes subsequent retail decode
        # consume invalid data. A failed name allocation can register successfully;
        # inspect and close that record without attempting a lookup through NULL.
        source = fixture("registration-failures", (Entry(b"sample.bin", b"payload"),), parameters)
        for allocation in (0, 1, 2, 4, 5, 6, 7):
            retail, recovered = executions(source, allocation)
            result = retail.register(b"failure.dat", source)
            assert recovered.register(b"failure.dat", source) == result
            compare(retail, recovered, ("registration-failure", allocation))
            registrations += 1
            failures += 1
            close_slot(retail, recovered, 0)
            cleanups += 1
            if not result:
                # A failed registration leaves the count at zero, so the next
                # successful attempt must reuse this record.
                assert retail.register(b"retry.dat", source) == recovered.register(b"retry.dat", source) == 1
                for execution in (retail, recovered):
                    execution.verify_index("disk")
                compare(retail, recovered, ("registration-retry", allocation))
                check_resource(retail, recovered, b"retry/SAMPLE.BIN", source.entries[0], ("retry", allocation))
                registrations += 1
                reads += 2
                sizes += 1
                close_slot(retail, recovered, 0, True)
                cleanups += 1
            assert not retail.files and not recovered.files

        print(f"PASS: {singles} single-archive scenarios and one three-archive scenario; "
              f"{registrations} registration attempts, {reads} resource loads, {sizes} size queries, "
              f"{failures} allocation-failure paths and {cleanups} cleanup calls agree with retail. "
              "Fourteen candidates execute together; loose-file I/O, native MSVC byte matching "
              "and Windows exception dispatch remain unverified.")


if __name__ == "__main__":
    main()
