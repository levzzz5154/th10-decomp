#!/usr/bin/env python3
"""Run recovered DAT candidates together against the complete retail read path.

Requires native clang++, the project's MSVC headers, and Python's unicorn.
File I/O, allocation and CRT thread-data retrieval are scripted. The codecs,
packed-index parser, lookup, constructors and memcpy execute x86 instructions.
The candidate lookup adapter changes only the calling convention. This is
behavioral validation, not an MSVC byte or exception-unwind equivalence test.
"""

import argparse
from dataclasses import dataclass
from pathlib import Path
import random
import struct
import tempfile

from unicorn import Uc, UC_ARCH_X86, UC_MODE_32, UC_HOOK_CODE
from unicorn.x86_const import (UC_X86_REG_EAX, UC_X86_REG_EBX, UC_X86_REG_ECX,
                              UC_X86_REG_ESI, UC_X86_REG_ESP, UC_X86_REG_EIP)
from lzss_compressor_differential import (
    ROOT, CANDIDATE, OUTPUT, STACK, STOP, RING, PRESERVED,
    PEImage, load_manifest, load_oracle, load_candidate)
from dat_archive_load_index_differential import compile_candidate as compile_loader
from dat_archive_read_differential import compile_candidate as compile_reader
from dat_archive_parser_differential import compile_candidate as compile_parser, load_parser_candidate
from dat_crypt_differential import compile_candidate as compile_cipher
from lzss_decoder_differential import compile_candidate as compile_decoder, encode
from dat_archive_cleanup_differential import compile_candidates as compile_cleanup, CLOSE, RESET
from dat_archive_open_differential import compile_candidates as compile_open, OPEN, OPEN_RESOURCE

STATE = 0x2500000
ARCHIVE, FILE, VTABLE = STATE + 0x100, STATE + 0x200, STATE + 0x300
PATH, QUERY, THREAD, LOCALE = STATE + 0x400, STATE + 0x800, STATE + 0x1000, STATE + 0x2000
HEAP, HEAP_SIZE = 0x3000000, 0x800000
LOAD, READ, PARSE, DECRYPT, DECODE = (CANDIDATE + i * 0x2000 for i in range(5))
FIND_ADAPTER, FIND_RETURN = CANDIDATE + 0xB000, CANDIDATE + 0xB100
FILE_OPEN, FILE_READ, FILE_SIZE, FILE_SEEK, FILE_DELETE = (
    CANDIDATE + 0xC000 + i * 0x100 for i in range(5))


@dataclass(frozen=True)
class Entry:
    name: bytes
    payload: bytes
    compressed: bool = False
    tokens: object = None


@dataclass(frozen=True)
class Fixture:
    label: str
    entries: tuple
    data: bytes
    packed_index: bytes
    offsets: tuple
    terminal_offset: int


def encrypt(data, key, step, block_size, limit):
    """Independent format encoder for the archive fixtures' positive sizes."""
    result = bytearray(data)
    remainder = len(data) % block_size
    remaining = len(data) - (len(data) & 1) - (remainder if remainder < block_size // 4 else 0)
    offset = 0
    while remaining > 0 and limit > 0:
        count = min(remaining, block_size)
        order = list(range(count - 1, -1, -2)) + list(range(count - 2, -1, -2))
        for index, position in enumerate(order):
            result[offset + index] = data[offset + position] ^ key
            key = (key + step) & 255
        offset += count
        remaining -= count
        limit -= count
    return bytes(result)


def fixture(label, entries, parameters):
    contents = bytearray(16)
    packed = bytearray()
    offsets = []
    for index, entry in enumerate(entries):
        offsets.append(len(contents))
        stored = entry.payload
        if entry.compressed:
            stored, decoded = encode(entry.tokens if entry.tokens is not None else list(entry.payload))
            if entry.tokens is None or isinstance(entry.tokens[0], int):
                assert decoded == entry.payload
            assert len(stored) != len(entry.payload), "fixture must trigger the size-based codec choice"
        params = parameters[sum(entry.name) & 7]
        contents.extend(encrypt(stored, *params))
        packed.extend(entry.name + b"\0")
        packed.extend(b"\xCC" * (-len(packed) % 4))
        packed.extend(struct.pack("<3I", offsets[-1], len(entry.payload), 0xC0DE0000 | index))
    terminal = len(contents)
    compressed_index, decoded = encode(list(packed))
    assert decoded == packed
    contents.extend(encrypt(compressed_index, 0x3E, 0x9B, 128, len(compressed_index)))
    header = struct.pack("<4I", 0x31414854, len(packed) + 123456789,
                         len(compressed_index) + 987654321, len(entries) + 135792468)
    contents[:16] = encrypt(header, 0x1B, 0x37, 16, 16)
    return Fixture(label, tuple(entries), bytes(contents), bytes(packed), tuple(offsets), terminal)


def compile_modules(directory, config):
    specifications = [
        (LOAD, "load", compile_loader, "DatArchive_LoadIndex_00434f70"),
        (READ, "read", compile_reader, "DatArchive_Read_00434dd0"),
        (PARSE, "parse", compile_parser, "DatArchive_BuildIndex_004350d0"),
        (DECRYPT, "crypt", compile_cipher, "Dat_Decrypt_0044b0d0"),
        (DECODE, "decode", compile_decoder, "DecompressDatLzss_00435dc0")]
    bindings = {
        "_g_dat_archive_read_mode": 0x474908,
        "_g_dat_read_crypt_parameters": 0x474BD8,
        "_Dat_Decrypt_0044b0d0@24": DECRYPT,
        "_DecompressDatLzss_00435dc0@16": DECODE,
        "_DatArchive_BuildIndex_004350d0@12": PARSE,
        "_Archive_FindEntry_00434f30@8": FIND_ADAPTER,
        "@ArchiveEntry_Construct_004352c0@4": 0x4352C0,
        "@ArchiveEntry_Release_00435250@4": 0x435250,
        "_asm_eh_vector_constructor_iterator_0045252d@20": 0x45252D,
        "_memcpy": 0x45BFC0}
    modules = {}
    for address, name, compile_source, symbol in specifications:
        path = directory / (name + ".obj")
        compile_source(path)
        modules[address] = (load_parser_candidate(path, address).data if address == PARSE else
                            load_candidate(path, config, symbol, bindings, code_address=address))
    modules.update(compile_cleanup(directory, config))
    modules.update(compile_open(directory, config))
    return modules


class Execution:
    def __init__(self, image, modules, source, fail_allocation=None, archive_address=ARCHIVE):
        self.uc = uc = Uc(UC_ARCH_X86, UC_MODE_32)
        uc.mem_map(0x400000, 0x100000)
        for section in image.sections:
            uc.mem_write(section["address"], image.read(section["address"], section["raw_size"]))
        code_arenas = {address & ~0xFFFF for address in modules}
        for address in code_arenas | {CANDIDATE, OUTPUT, STACK, STOP, STATE}:
            uc.mem_map(address, 0x10000)
        uc.mem_map(HEAP, HEAP_SIZE)
        uc.mem_map(0, 0x1000)
        self.words(0, 0xFEE1DEAD)
        for address, code in modules.items():
            assert len(code) <= 0x10000 - (address & 0xFFFF)
            uc.mem_write(address, code)
        self.recovered = bool(modules)
        self.source = source
        self.position = 0
        self.events = []
        self.allocations = []
        self.heap_cursor = HEAP + 64
        self.fail_allocation = fail_allocation
        self.lookup_frames = []
        self.archive = archive_address
        self.words(self.archive, 0, 0, 0, FILE)
        self.words(FILE, VTABLE)
        # Both typed constructors retain their actual retail vtable addresses.
        # Replace only the virtual I/O slots with the in-memory collaborator,
        # just as for the preinstalled file used by direct loader scenarios.
        for table in (VTABLE, 0x46F230, 0x46F328):
            self.words(table, FILE_OPEN, 0, FILE_READ, 0, 0, FILE_SIZE, FILE_SEEK, FILE_DELETE)
        uc.mem_write(PATH, b"fixture.dat\0")
        # Supply a minimal C-locale thread record; execute retail stricmp and
        # its ASCII fast path, without invoking Windows TLS initialization.
        self.words(THREAD + 0x64, LOCALE)
        self.words(0x47320C, LOCALE)
        uc.mem_write(RING, bytes((i * 37 + 13) & 255 for i in range(0x2000)))
        for address in (0x452706, 0x452493, 0x452422, 0x4524A1, 0x456357,
                        FIND_ADAPTER, FIND_RETURN, FILE_OPEN, FILE_READ,
                        FILE_SIZE, FILE_SEEK, FILE_DELETE):
            uc.hook_add(UC_HOOK_CODE, self.hook, begin=address, end=address)

    def words(self, address, *values):
        self.uc.mem_write(address, struct.pack("<" + "I" * len(values),
                                             *(value & 0xFFFFFFFF for value in values)))

    def args(self, count):
        sp = self.uc.reg_read(UC_X86_REG_ESP)
        return struct.unpack("<" + "I" * count, self.uc.mem_read(sp + 4, count * 4))

    def string(self, address):
        result = bytearray()
        while True:
            byte = self.uc.mem_read(address + len(result), 1)[0]
            if not byte:
                return bytes(result)
            result.append(byte)
            assert len(result) < 2048

    def finish(self, result, argument_bytes=0):
        uc = self.uc
        sp = uc.reg_read(UC_X86_REG_ESP)
        uc.reg_write(UC_X86_REG_EIP, struct.unpack("<I", uc.mem_read(sp, 4))[0])
        uc.reg_write(UC_X86_REG_ESP, sp + 4 + argument_bytes)
        uc.reg_write(UC_X86_REG_EAX, result & 0xFFFFFFFF)

    def hook(self, uc, address, size, context):
        if address in (0x452706, 0x452493):
            requested, = self.args(1)
            assert requested < 0x100000, f"invalid allocation {requested:#x}"
            pointer = 0 if len(self.allocations) == self.fail_allocation else self.heap_cursor
            self.allocations.append((pointer, requested))
            self.events.append(("new" if address == 0x452493 else "malloc", requested, pointer))
            if pointer:
                uc.mem_write(pointer - 32, b"\xA5" * (requested + 64))
                self.heap_cursor += ((requested + 15) & ~15) + 64
                assert self.heap_cursor < HEAP + HEAP_SIZE
            self.finish(pointer)
        elif address in (0x452422, 0x4524A1):
            pointer, = self.args(1)
            self.events.append(("free", pointer))
            # Retain freed bytes to characterize retail's returned freed
            # uncompressed buffer. This does not make that pointer live.
            self.finish(0xBAD00001)
        elif address == 0x456357:
            self.finish(THREAD)
        elif address == FILE_OPEN:
            path, mode = self.args(2)
            self.events.append(("open", self.string(path), self.string(mode)))
            self.position = 0
            self.finish(1, 8)
        elif address == FILE_SIZE:
            self.events.append(("size", len(self.source.data)))
            self.finish(len(self.source.data))
        elif address == FILE_SEEK:
            distance, origin = self.args(2)
            assert origin == 0
            self.position = distance
            self.events.append(("seek", distance))
            self.finish(1, 8)
        elif address == FILE_READ:
            destination, requested = self.args(2)
            data = self.source.data[self.position:self.position + requested]
            self.events.append(("read", self.position, requested, len(data)))
            if data:
                uc.mem_write(destination, data)
            self.position += len(data)
            self.finish(len(data), 8)
        elif address == FILE_DELETE:
            flags, = self.args(1)
            self.events.append(("delete", flags))
            self.finish(uc.reg_read(UC_X86_REG_ECX), 4)
        elif address == FIND_ADAPTER:
            archive, name = self.args(2)
            sp = uc.reg_read(UC_X86_REG_ESP)
            ret, = struct.unpack("<I", uc.mem_read(sp, 4))
            self.lookup_frames.append((sp, ret, uc.reg_read(UC_X86_REG_EBX)))
            self.words(sp, FIND_RETURN)
            uc.reg_write(UC_X86_REG_EAX, archive)
            uc.reg_write(UC_X86_REG_EBX, name)
            uc.reg_write(UC_X86_REG_EIP, 0x434F30)
        elif address == FIND_RETURN:
            sp, ret, ebx = self.lookup_frames.pop()
            assert uc.reg_read(UC_X86_REG_ESP) == sp + 4
            uc.reg_write(UC_X86_REG_EBX, ebx)
            uc.reg_write(UC_X86_REG_ESP, sp + 12)
            uc.reg_write(UC_X86_REG_EIP, ret)
        else:
            raise AssertionError(f"unexpected hook {address:#x}")

    def call(self, address, arguments, registers=None):
        uc = self.uc
        sp = STACK + 0x8000
        self.words(sp, STOP, *arguments)
        uc.reg_write(UC_X86_REG_ESP, sp)
        expected = dict(PRESERVED)
        expected.update(registers or {})
        for register, value in expected.items():
            uc.reg_write(register, value)
        uc.emu_start(address, STOP, count=20000000)
        assert uc.reg_read(UC_X86_REG_EIP) == STOP, "instruction budget exhausted"
        assert uc.reg_read(UC_X86_REG_ESP) == sp + 4 * (1 + len(arguments))
        assert struct.unpack("<I", uc.mem_read(0, 4))[0] == 0xFEE1DEAD
        for register in PRESERVED:
            assert uc.reg_read(register) == expected[register], "callee-saved register changed"
        assert not self.lookup_frames
        return uc.reg_read(UC_X86_REG_EAX)

    def load(self):
        if self.recovered:
            return self.call(LOAD, [self.archive, PATH]) & 255
        return self.call(0x434F70, [PATH], {UC_X86_REG_ESI: self.archive}) & 255

    def open(self, operation):
        if operation == "load":
            return self.load()
        assert operation in ("disk", "resource")
        if self.recovered:
            return self.call(OPEN if operation == "disk" else OPEN_RESOURCE, [self.archive, PATH]) & 255
        return self.call(0x434C30 if operation == "disk" else 0x434CA0, [],
                         {UC_X86_REG_ECX: self.archive, UC_X86_REG_EAX: PATH}) & 255

    def read(self, name, supplied):
        self.uc.mem_write(QUERY, name + b"\0")
        self.uc.mem_write(OUTPUT, b"\xA5" * 0x10000)
        output = OUTPUT if supplied else 0
        if self.recovered:
            return self.call(READ, [self.archive, QUERY, output])
        return self.call(0x434DD0, [self.archive, output], {UC_X86_REG_ECX: QUERY})

    def close(self, reset=False):
        if reset:
            self.call(RESET if self.recovered else 0x434C20, [], {UC_X86_REG_ECX: self.archive})
        elif self.recovered:
            self.call(CLOSE, [self.archive])
        else:
            self.call(0x434D10, [], {UC_X86_REG_ESI: self.archive})
        assert bytes(self.uc.mem_read(self.archive, 16)) == bytes(16)

    def snapshot(self):
        return {"events": tuple(self.events),
                "archive": bytes(self.uc.mem_read(self.archive, 16)),
                "heap": tuple((pointer, requested,
                               bytes(self.uc.mem_read(pointer - 32, requested + 64)) if pointer else b"")
                              for pointer, requested in self.allocations),
                "ring": bytes(self.uc.mem_read(RING, 0x2000)),
                "position": self.position}

    def verify_index(self, operation):
        entries, count, filename, file = struct.unpack("<4I", self.uc.mem_read(self.archive, 16))
        assert count == len(self.source.entries)
        if operation == "load":
            assert (filename, file) == (0, FILE)
        else:
            assert filename and self.string(filename) == self.string(PATH)
            assert HEAP <= file < HEAP + HEAP_SIZE
        assert struct.unpack("<I", self.uc.mem_read(entries - 4, 4))[0] == count + 1
        for index, item in enumerate(self.source.entries):
            name, offset, unpacked, metadata = struct.unpack("<4I", self.uc.mem_read(entries + index * 16, 16))
            assert self.string(name) == item.name
            assert (offset, unpacked, metadata) == (self.source.offsets[index], len(item.payload), 0xC0DE0000 | index)
        assert struct.unpack("<4I", self.uc.mem_read(entries + count * 16, 16)) == (
            0, self.source.terminal_offset, 0, 0xA5A5A5A5)


def fixtures(parameters):
    yield fixture("empty", (), parameters)
    randomizer = random.Random(0x434F70)
    # Exercise every cipher bucket with sizes around its block and byte limit.
    for bucket, (_, _, block, limit) in enumerate(parameters):
        name = b"entry.dat" + bytes([65 + ((bucket - sum(b"entry.dat") - 65) & 7)])
        for size in (1, block - 1, block, block + 1, limit + 33):
            yield fixture(f"cipher-{bucket}-{size}", (
                Entry(name, randomizer.randbytes(size)),
                Entry(b"compressed.bin", b"A" * 37, True, [65, (1, 18), (1, 18)])), parameters)
    yield fixture("dictionary-carry", (Entry(b"abc.bin", b"abc", True, [(1, 3)]),), parameters)
    yield fixture("wrap-and-empty", (
        Entry(b"ring.bin", bytes(range(256)) * 65, True),
        Entry(b"empty.raw", b""), Entry(b"empty.lz", b"", True)), parameters)
    yield fixture("duplicates", (Entry(b"First.bin", b"first match"),
                                Entry(b"FIRST.BIN", b"second match")), parameters)
    for trial in range(12):
        entries = tuple(Entry(f"file-{index:02}.bin".encode(),
                              randomizer.randbytes(randomizer.randrange(1, 512)), bool(index & 1))
                        for index in range(randomizer.randrange(1, 12)))
        yield fixture(f"random-{trial}", entries, parameters)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--oracle", type=Path, default=ROOT / "matching2/build/oracle/th10.exe")
    options = parser.parse_args()
    config = load_manifest(ROOT / "matching2/msvc/regions.json")
    load_oracle(options.oracle, config)
    image = PEImage(options.oracle.read_bytes())
    parameters = [struct.unpack("<BB2xii", image.read(0x474BD8 + index * 12, 12)) for index in range(8)]
    with tempfile.TemporaryDirectory(prefix="th10-archive-integration-") as temporary:
        modules = compile_modules(Path(temporary), config)
        archives = reads = failures = cleanups = 0
        for source in fixtures(parameters):
            for operation in ("load", "disk", "resource"):
                retail, recovered = (Execution(image, code, source) for code in ({}, modules))
                assert retail.open(operation) == recovered.open(operation) == 1, (source.label, operation)
                retail.verify_index(operation)
                recovered.verify_index(operation)
                assert retail.snapshot() == recovered.snapshot(), (source.label, operation)
                for item in (*source.entries, Entry(b"missing.file", b"")):
                    match = next((entry for entry in source.entries if entry.name.lower() == item.name.lower()), None)
                    for supplied in (False, True):
                        result = retail.read(item.name.swapcase(), supplied)
                        actual = recovered.read(item.name.swapcase(), supplied)
                        assert actual == result, (source.label, operation, item.name, "return")
                        assert retail.snapshot() == recovered.snapshot(), (source.label, operation, item.name, "state")
                        if match is None or (not match.payload and not match.compressed):
                            assert result == 0
                        else:
                            assert result
                            expected = match.payload
                            assert bytes(retail.uc.mem_read(result, len(expected))) == expected, (source.label, item.name)
                            assert bytes(recovered.uc.mem_read(actual, len(expected))) == expected
                            assert bytes(recovered.uc.mem_read(actual + len(expected), 32)) == b"\xA5" * 32
                        reads += 1
                # Alternate the entry used for a live archive, then call the
                # other on the closed object to check both wrappers.
                for reset in (bool(archives & 1), not bool(archives & 1)):
                    retail.close(reset)
                    recovered.close(reset)
                    assert retail.snapshot() == recovered.snapshot(), (source.label, operation, "close", reset)
                    cleanups += 1
                archives += 1
        # Safe failure stages: header scratch, stored index, decoded index,
        # array allocation, and a name allocation. The last can still succeed.
        source = fixture("load-failures", (Entry(b"sample.bin", b"payload"),), parameters)
        for operation in ("load", "disk", "resource"):
            allocations = (0, 1, 3, 4, 5) if operation == "load" else (0, 1, 2, 4, 5, 6, 7)
            for allocation in allocations:
                retail, recovered = (Execution(image, code, source, allocation) for code in ({}, modules))
                assert retail.open(operation) == recovered.open(operation)
                assert retail.snapshot() == recovered.snapshot(), (operation, "allocation", allocation)
                retail.close()
                recovered.close()
                assert retail.snapshot() == recovered.snapshot(), (operation, "failure-close", allocation)
                cleanups += 1
                failures += 1
        print(f"PASS: {archives} complete DAT scenarios, {reads} entry reads, and {failures} "
              f"allocation-failure paths with {cleanups} cleanup calls agree with retail; "
              "ten candidates execute together. "
              "MSVC byte matching and Windows exception dispatch remain unverified.")


if __name__ == "__main__":
    main()
