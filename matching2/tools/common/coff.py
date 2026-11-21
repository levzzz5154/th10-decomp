"""Read COFF sections, symbols and relocations without applying them."""
from __future__ import annotations

from dataclasses import dataclass
from pathlib import Path
import struct
from typing import Any


IMAGE_SYM_CLASS_EXTERNAL = 2
IMAGE_SYM_CLASS_STATIC = 3
IMAGE_SCN_CNT_UNINITIALIZED_DATA = 0x80
RELOCATION_TYPES = {0x0006: "dir32", 0x0014: "rel32"}


class CoffRegionError(ValueError):
    """A COFF object cannot be interpreted or normalized without guessing."""


def _decode_name(raw: bytes, string_table: bytes) -> str:
    if raw[:4] == b"\0\0\0\0":
        offset = struct.unpack_from("<I", raw, 4)[0]
        kind = "COFF"
    else:
        # Long section names use /decimal; long symbol names use zero + offset.
        name = raw.rstrip(b"\0").decode("ascii")
        if not (name.startswith("/") and name[1:].isdigit()):
            return name
        offset = int(name[1:])
        kind = "section"
    if not 4 <= offset < len(string_table):
        raise CoffRegionError(f"invalid {kind} string-table offset {offset}")
    end = string_table.find(b"\0", offset)
    if end < 0:
        raise CoffRegionError(f"unterminated {kind} name at string-table offset {offset}")
    return string_table[offset:end].decode("ascii")


def read_object(path: str | Path) -> dict[str, Any]:
    """Read one ordinary COFF object, retaining raw bytes for preservation checks."""
    path = Path(path)
    data = path.read_bytes()
    if len(data) < 20:
        raise CoffRegionError(f"{path}: truncated COFF header")
    machine, section_count, timestamp, symbol_offset, symbol_count, optional_size, characteristics = struct.unpack_from(
        "<HHIIIHH", data, 0
    )
    if optional_size:
        raise CoffRegionError(f"{path}: optional PE header is not supported in a COFF object")
    section_table = 20
    section_end = section_table + section_count * 40
    if section_end > len(data):
        raise CoffRegionError(f"{path}: truncated section table")
    if symbol_count and (symbol_offset < section_end or symbol_offset + symbol_count * 18 + 4 > len(data)):
        raise CoffRegionError(f"{path}: truncated symbol table")
    if not symbol_count:
        string_table = struct.pack("<I", 4)
    else:
        string_offset = symbol_offset + symbol_count * 18
        if string_offset + 4 > len(data):
            raise CoffRegionError(f"{path}: truncated string-table size")
        string_size = struct.unpack_from("<I", data, string_offset)[0]
        if string_size < 4 or string_offset + string_size > len(data):
            raise CoffRegionError(f"{path}: invalid COFF string-table size {string_size}")
        string_table = data[string_offset:string_offset + string_size]

    sections = _read_sections(path, data, section_table, section_count, string_table)
    records, index_to_primary = _read_symbols(path, data, symbol_offset, symbol_count, string_table)
    return {
        "path": path,
        "data": data,
        "machine": machine,
        "timestamp": timestamp,
        "characteristics": characteristics,
        "sections": sections,
        "records": records,
        "record_by_index": {record["index"]: record for record in records},
        "index_to_primary": index_to_primary,
    }


def _read_sections(path, data, section_table, section_count, string_table):
    sections: list[dict[str, Any]] = []
    for number in range(1, section_count + 1):
        offset = section_table + (number - 1) * 40
        fields = struct.unpack_from("<8sIIIIIIHHI", data, offset)
        name = _decode_name(fields[0], string_table)
        raw_size = fields[3]
        raw_offset = fields[4]
        reloc_offset = fields[5]
        reloc_count = fields[7]
        if raw_size and raw_offset == 0 and fields[9] & IMAGE_SCN_CNT_UNINITIALIZED_DATA:
            raw = b""  # .bss: an extent with no file data
        elif raw_size:
            if raw_offset == 0 or raw_offset + raw_size > len(data):
                raise CoffRegionError(f"{path}: section {number} has invalid raw-data range")
            raw = data[raw_offset:raw_offset + raw_size]
        else:
            raw = b""
        if reloc_count and (reloc_offset == 0 or reloc_offset + reloc_count * 10 > len(data)):
            raise CoffRegionError(f"{path}: section {number} has invalid relocation range")
        relocations = []
        for index in range(reloc_count):
            roff = reloc_offset + index * 10
            virtual_address, symbol_index, relocation_type = struct.unpack_from("<IIH", data, roff)
            relocations.append({
                "virtual_address": virtual_address,
                "symbol_index": symbol_index,
                "type": relocation_type,
                "raw": data[roff:roff + 10],
            })
        sections.append({
            "number": number,
            "name": name,
            "misc": fields[1],
            "virtual_address": fields[2],
            "raw_size": raw_size,
            "raw": raw,
            "relocations": relocations,
            "characteristics": fields[9],
            "line_number_pointer": fields[6],
            "line_number_count": fields[8],
        })
    return sections


def _read_symbols(path, data, symbol_offset, symbol_count, string_table):
    records: list[dict[str, Any]] = []
    index_to_primary: dict[int, int] = {}
    index = 0
    while index < symbol_count:
        offset = symbol_offset + index * 18
        raw_name, value, section_number, symbol_type, storage_class, aux_count = struct.unpack_from(
            "<8sIhHBB", data, offset
        )
        if index + 1 + aux_count > symbol_count:
            raise CoffRegionError(f"{path}: symbol {index} has truncated auxiliary records")
        primary = {
            "index": index,
            "name": _decode_name(raw_name, string_table),
            "value": value,
            "section_number": section_number,
            "type": symbol_type,
            "storage_class": storage_class,
            "aux_count": aux_count,
            "aux_records": [data[symbol_offset + (index + n) * 18:symbol_offset + (index + n + 1) * 18]
                            for n in range(1, aux_count + 1)],
        }
        records.append(primary)
        index_to_primary[index] = index
        for n in range(1, aux_count + 1):
            index_to_primary[index + n] = index
        index += 1 + aux_count
    return records, index_to_primary


def defined_functions(obj):
    """Map defined function names to their one-based COFF section numbers."""
    return {r["name"]: r["section_number"] for r in obj["records"]
            if r["section_number"] > 0 and r["type"] & 0x20
            and r["storage_class"] in (IMAGE_SYM_CLASS_EXTERNAL, IMAGE_SYM_CLASS_STATIC)}


@dataclass(frozen=True)
class Relocation:
    offset: int
    symbol: str
    kind: int
    local: int | None  # Same-section target relative to the function, before the addend.


@dataclass
class CoffFunction:
    name: str
    data: bytes
    relocations: list[Relocation]

    def linker_bytes(self):
        """Byte offsets occupied by 32-bit fields that the linker fills."""
        return {i for reloc in self.relocations if reloc.kind in RELOCATION_TYPES
                for i in range(reloc.offset, reloc.offset + 4)}


def function_body(obj, requested_symbol, *, require_external=False):
    """Select by exact or unambiguous partial name; return function-relative offsets."""
    records = obj["records"]
    matches = [r for r in records if r["name"] == requested_symbol]
    if not matches:
        matches = [r for r in records if r["section_number"] > 0 and requested_symbol in r["name"]]
    if len(matches) != 1:
        names = ", ".join(r["name"] for r in matches) or "none"
        raise CoffRegionError("symbol must identify exactly one function; matches: " + names)
    owner = matches[0]
    if require_external and owner["storage_class"] != IMAGE_SYM_CLASS_EXTERNAL:
        raise CoffRegionError("expected an external definition of " + owner["name"])

    number, start = owner["section_number"], owner["value"]
    if not 1 <= number <= len(obj["sections"]):
        raise CoffRegionError("symbol is not defined in an object section: " + owner["name"])
    section = obj["sections"][number - 1]
    relocations = []
    for entry in section["relocations"]:
        offset = entry["virtual_address"] - start
        if offset < 0:
            continue
        index = entry["symbol_index"]
        target = obj["record_by_index"].get(index)
        if target is None:
            raise CoffRegionError(f"relocation at +{offset:#x} references invalid symbol index {index}")
        local = target["value"] - start if target["section_number"] == number else None
        relocations.append(Relocation(offset, target["name"], entry["type"], local))
    return CoffFunction(owner["name"], section["raw"][start:], relocations)
