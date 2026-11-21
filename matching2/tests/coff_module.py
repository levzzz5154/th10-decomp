"""Relocate a small i386 COFF test module, including its unwind metadata.

This is an emulator fixture loader, not a linker or an exact-build path.
Ordinary and code_seg .text$ sections (including long COFF section names),
code/data sections and the DIR32/REL32 relocations used by these fixtures
are supported. Unbound imports fail instead of silently acquiring stubs.
"""

from dataclasses import dataclass
from pathlib import Path
import struct
import sys

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT))

from matching2.tools.common.coff import read_object


@dataclass(frozen=True)
class Module:
    base: int
    data: bytes
    symbols: dict


def load_module(path, base, bindings):
    obj = read_object(path)
    assert obj["machine"] == 0x14C, "expected ordinary i386 COFF"

    addresses, data = {}, bytearray()
    for section in obj["sections"]:
        label = section["name"]
        if not section["raw_size"] or (label not in (".text", ".data", ".rdata", ".bss", ".xdata")
                                       and not label.startswith(".text$")):
            continue
        alignment_code = (section["characteristics"] >> 20) & 15
        alignment = max(16, 1 << (alignment_code - 1) if alignment_code else 1)
        data.extend(bytes(-len(data) % alignment))
        addresses[section["number"]] = base + len(data)
        data.extend(section["raw"] or bytes(section["raw_size"]))

    symbols, weak_aliases = {}, {}
    for record in obj["records"]:
        section = record["section_number"]
        if record["storage_class"] == 105:
            assert len(record["aux_records"]) == 1
            fallback, search = struct.unpack_from("<II", record["aux_records"][0])
            assert search == 3, "only COFF weak aliases are supported"
            weak_aliases[record["index"]] = fallback
        if section in addresses:
            symbols[record["name"]] = addresses[section] + record["value"]
        elif section == -1:
            symbols[record["name"]] = record["value"]

    def resolve(index):
        record = obj["record_by_index"][index]
        label, value, section = record["name"], record["value"], record["section_number"]
        if section in addresses:
            return addresses[section] + value
        if section == -1:
            return value
        assert section == 0 and value == 0, f"unsupported symbol {label}: section {section}, value {value}"
        if label not in bindings and index in weak_aliases:
            assert weak_aliases[index] != index, "self-referencing weak alias"
            return resolve(weak_aliases[index])
        return bindings[label]

    for section in obj["sections"]:
        if section["number"] not in addresses:
            continue
        address = addresses[section["number"]]
        for relocation in section["relocations"]:
            offset, kind = relocation["virtual_address"], relocation["type"]
            assert offset + 4 <= section["raw_size"]
            destination = address - base + offset
            value, = struct.unpack_from("<I", data, destination)
            value += resolve(relocation["symbol_index"])
            if kind == 0x14:
                value -= address + offset + 4
            elif kind != 6:
                raise ValueError(f"unsupported i386 relocation {kind:#x} in {section['name']}")
            struct.pack_into("<I", data, destination, value & 0xFFFFFFFF)
    return Module(base, bytes(data), symbols)
