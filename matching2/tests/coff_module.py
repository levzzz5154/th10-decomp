"""Relocate a small i386 COFF test module, including its unwind metadata.

This is an emulator fixture loader, not a linker or an exact-build path.
Ordinary and code_seg .text$ sections (including long COFF section names),
code/data sections and the DIR32/REL32 relocations used by these fixtures
are supported. Unbound imports fail instead of silently acquiring stubs.
"""

from dataclasses import dataclass
from pathlib import Path
import struct


@dataclass(frozen=True)
class Module:
    base: int
    data: bytes
    symbols: dict
    sections: tuple


def load_module(path, base, bindings):
    raw = Path(path).read_bytes()
    machine, count, _, symbol_offset, symbol_count, optional_size, _ = struct.unpack_from("<HHIIIHH", raw)
    assert machine == 0x14C and optional_size == 0, "expected ordinary i386 COFF"
    strings = raw[symbol_offset + symbol_count * 18:]

    def name(value):
        if value[:4] == bytes(4):
            offset, = struct.unpack_from("<I", value, 4)
            return strings[offset:strings.index(0, offset)].decode("ascii")
        return value.rstrip(b"\0").decode("ascii")

    sections, data = {}, bytearray()
    for index in range(count):
        fields = struct.unpack_from("<8sIIIIIIHHI", raw, 20 + index * 40)
        label, size, source, relocations, reloc_count, flags = (
            name(fields[0]), fields[3], fields[4], fields[5], fields[7], fields[9])
        if label.startswith("/") and label[1:].isdigit():
            offset = int(label[1:])
            label = strings[offset:strings.index(0, offset)].decode("ascii")
        if (label not in (".text", ".data", ".rdata", ".bss", ".xdata") and
                not label.startswith(".text$")) or not size:
            continue
        alignment_code = (flags >> 20) & 15
        alignment = max(16, 1 << (alignment_code - 1) if alignment_code else 1)
        data.extend(bytes(-len(data) % alignment))
        address = base + len(data)
        data.extend(raw[source:source + size] if source else bytes(size))
        sections[index + 1] = (label, address, size, relocations, reloc_count)

    symbols, indexed, weak_aliases = {}, {}, {}
    index = 0
    while index < symbol_count:
        label, value, section, _, storage, auxiliary = struct.unpack_from("<8sIhHBB", raw, symbol_offset + index * 18)
        label = name(label)
        indexed[index] = (label, value, section)
        if storage == 105:
            assert auxiliary == 1
            fallback, search = struct.unpack_from("<II", raw, symbol_offset + (index + 1) * 18)
            assert search == 3, "only COFF weak aliases are supported"
            weak_aliases[index] = fallback
        if section in sections:
            symbols[label] = sections[section][1] + value
        elif section == -1:
            symbols[label] = value
        index += auxiliary + 1

    def resolve(index):
        label, value, section = indexed[index]
        if section in sections:
            return sections[section][1] + value
        if section == -1:
            return value
        assert section == 0 and value == 0, f"unsupported symbol {label}: section {section}, value {value}"
        if label not in bindings and index in weak_aliases:
            assert weak_aliases[index] != index, "self-referencing weak alias"
            return resolve(weak_aliases[index])
        return bindings[label]

    for label, address, size, relocations, reloc_count in sections.values():
        for index in range(reloc_count):
            offset, symbol, kind = struct.unpack_from("<IIH", raw, relocations + index * 10)
            assert offset + 4 <= size
            destination = address - base + offset
            value, = struct.unpack_from("<I", data, destination)
            value += resolve(symbol)
            if kind == 0x14:
                value -= address + offset + 4
            elif kind != 6:
                raise ValueError(f"unsupported i386 relocation {kind:#x} in {label}")
            struct.pack_into("<I", data, destination, value & 0xFFFFFFFF)
    return Module(base, bytes(data), symbols, tuple(sections.values()))
