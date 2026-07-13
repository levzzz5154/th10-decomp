#!/usr/bin/env python3
"""Compare one function in an MSVC COFF object with the original executable."""

import argparse
import struct
from pathlib import Path


DEFAULT_EXE = Path("/home/levzzz/Games/TH10 - Mountain of Faith/th10.exe")
IMAGE_BASE = 0x400000
TEXT_RVA = 0x1000
TEXT_RAW = 0x400


def coff_name(raw_name, string_table):
    if raw_name[:4] == b"\0\0\0\0":
        offset = struct.unpack_from("<I", raw_name, 4)[0]
        end = string_table.find(b"\0", offset)
        return string_table[offset:end].decode("ascii")
    return raw_name.rstrip(b"\0").decode("ascii")


def read_coff_function(path, requested_symbol):
    data = Path(path).read_bytes()
    _, section_count, _, symbol_offset, symbol_count, optional_size, _ = \
        struct.unpack_from("<HHIIIHH", data, 0)
    section_table = 20 + optional_size
    sections = []
    for index in range(section_count):
        offset = section_table + index * 40
        fields = struct.unpack_from("<8sIIIIIIHHI", data, offset)
        sections.append({
            "size": fields[3],
            "raw": fields[4],
            "reloc": fields[5],
            "reloc_count": fields[7],
        })

    string_offset = symbol_offset + symbol_count * 18
    string_table = data[string_offset:]
    symbols = []
    index = 0
    while index < symbol_count:
        offset = symbol_offset + index * 18
        raw_name, value, section, symbol_type, storage, aux_count = \
            struct.unpack_from("<8sIhHBB", data, offset)
        symbols.append((coff_name(raw_name, string_table), value, section,
                        symbol_type, storage))
        index += 1 + aux_count

    exact = [symbol for symbol in symbols if symbol[0] == requested_symbol]
    matches = exact or [symbol for symbol in symbols
                        if requested_symbol in symbol[0] and symbol[2] > 0]
    if len(matches) != 1:
        names = ", ".join(symbol[0] for symbol in matches) or "none"
        raise ValueError("symbol must identify exactly one function; matches: " + names)

    name, value, section_number, _, _ = matches[0]
    section = sections[section_number - 1]
    function = data[section["raw"] + value:section["raw"] + section["size"]]

    # Link-time address operands are zero in an object. Ignore those four-byte
    # fields instead of reporting them as source/code-generation mismatches.
    ignored = set()
    for index in range(section["reloc_count"]):
        offset = section["reloc"] + index * 10
        virtual_address, _, relocation_type = struct.unpack_from("<IIH", data, offset)
        if virtual_address >= value and relocation_type in (0x0006, 0x0014):
            start = virtual_address - value
            ignored.update(range(start, start + 4))
    return name, function, ignored


def read_original(path, address, size):
    file_offset = TEXT_RAW + (address - IMAGE_BASE - TEXT_RVA)
    with Path(path).open("rb") as executable:
        executable.seek(file_offset)
        return executable.read(size)


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("object", type=Path)
    parser.add_argument("symbol", help="exact name or a unique name fragment")
    parser.add_argument("address", type=lambda value: int(value, 0))
    parser.add_argument("--exe", type=Path, default=DEFAULT_EXE)
    args = parser.parse_args()

    name, compiled, ignored = read_coff_function(args.object, args.symbol)
    original = read_original(args.exe, args.address, len(compiled))
    compared = [index for index in range(len(compiled)) if index not in ignored]
    mismatches = [index for index in compared if compiled[index] != original[index]]
    matched = len(compared) - len(mismatches)
    percentage = 100.0 if not compared else matched * 100.0 / len(compared)

    print("symbol: {}".format(name))
    print("size: {} bytes".format(len(compiled)))
    print("match: {}/{} bytes ({:.2f}%)".format(matched, len(compared), percentage))
    print("ignored relocations: {} bytes".format(len(ignored)))
    if mismatches:
        preview = ", ".join("+0x{:X}".format(offset) for offset in mismatches[:16])
        if len(mismatches) > 16:
            preview += ", ..."
        print("mismatches: {}".format(preview))
        raise SystemExit(1)


if __name__ == "__main__":
    main()
