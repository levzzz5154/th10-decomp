#!/usr/bin/env python3
"""Select function sections from MSVC COFF objects without resolving code.

MSVC's ``/Gy`` puts functions in COMDAT sections.  A normal link of several
translation units can therefore let the linker discard one of two definitions
before the fixed-address port has had a chance to choose its region.  This
module makes a small ordinary-section COFF object containing only the selected
sections.  It keeps section bytes and relocation offsets/types unchanged and
rewrites only the metadata needed by the new object.

The normalizer deliberately does not apply relocations or turn an address in a
region record into bytes.  The caller remains responsible for binding undefined
symbols to the semantic manifest's retail addresses.
"""

from __future__ import annotations

import hashlib
import struct
from pathlib import Path
from typing import Any, Mapping, Optional, Sequence


IMAGE_SYM_CLASS_EXTERNAL = 2
IMAGE_SYM_CLASS_STATIC = 3
IMAGE_SYM_CLASS_WEAK_EXTERNAL = 105
IMAGE_SCN_LNK_COMDAT = 0x00001000


class CoffRegionError(ValueError):
    """A COFF object cannot be normalized without guessing."""


def _parse_int(value: Any, field: str) -> int:
    if isinstance(value, bool):
        raise CoffRegionError(f"{field} must be an integer, not bool")
    try:
        return int(value, 0) if isinstance(value, str) else int(value)
    except (TypeError, ValueError) as exc:
        raise CoffRegionError(f"{field} must be an integer: {value!r}") from exc


def _decode_name(raw: bytes, string_table: bytes) -> str:
    if raw[:4] == b"\0\0\0\0":
        offset = struct.unpack_from("<I", raw, 4)[0]
        if offset < 4 or offset >= len(string_table):
            raise CoffRegionError(f"invalid COFF string-table offset {offset}")
        end = string_table.find(b"\0", offset)
        if end < 0:
            end = len(string_table)
        return string_table[offset:end].decode("ascii")
    short_name = raw.rstrip(b"\0").decode("ascii")
    # COFF section headers use the slash-plus-decimal form for names longer
    # than eight bytes (symbol names use the zero-plus-offset form above).
    if short_name.startswith("/") and short_name[1:].isdigit():
        offset = int(short_name[1:])
        if offset < 4 or offset >= len(string_table):
            raise CoffRegionError(f"invalid section string-table offset {offset}")
        end = string_table.find(b"\0", offset)
        if end < 0:
            end = len(string_table)
        return string_table[offset:end].decode("ascii")
    return short_name


def _encode_name(name: str, strings: bytearray, offsets: dict[str, int]) -> bytes:
    encoded = name.encode("ascii")
    if len(encoded) <= 8:
        return encoded.ljust(8, b"\0")
    if name not in offsets:
        offsets[name] = len(strings)
        strings.extend(encoded)
        strings.append(0)
    return b"\0\0\0\0" + struct.pack("<I", offsets[name])


def _canonical_binding(name: str, bindings: Optional[Mapping[str, Any]]) -> str:
    """Return an optional caller-supplied external alias.

    A binding may be a string (the normal form), or a small mapping carrying a
    ``symbol``/``name`` key.  Integer address bindings are intentionally not
    consumed: resolving them here would violate the normalizer's byte-preserving
    contract, so the original symbol remains available for the caller's linker
    script.
    """

    if not bindings or name not in bindings:
        return name
    value = bindings[name]
    if isinstance(value, str):
        return value
    if isinstance(value, Mapping):
        alias = value.get("symbol", value.get("name"))
        if isinstance(alias, str):
            return alias
    return name


def _has_symbol_alias(name: str, bindings: Optional[Mapping[str, Any]]) -> bool:
    if not bindings or name not in bindings:
        return False
    value = bindings[name]
    if isinstance(value, str):
        return bool(value)
    return isinstance(value, Mapping) and isinstance(value.get("symbol", value.get("name")), str)


def _read_object(path: Path) -> dict[str, Any]:
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

    sections: list[dict[str, Any]] = []
    for number in range(1, section_count + 1):
        offset = section_table + (number - 1) * 40
        fields = struct.unpack_from("<8sIIIIIIHHI", data, offset)
        name = _decode_name(fields[0], string_table)
        raw_size = fields[3]
        raw_offset = fields[4]
        reloc_offset = fields[5]
        reloc_count = fields[7]
        if raw_size:
            if raw_offset == 0 or raw_offset + raw_size > len(data):
                raise CoffRegionError(f"{path}: section {number} has invalid raw-data range")
            raw = data[raw_offset:raw_offset + raw_size]
        else:
            raw = b""
        if reloc_count:
            if reloc_offset == 0 or reloc_offset + reloc_count * 10 > len(data):
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


def _defined_by_name(obj: dict[str, Any]) -> dict[str, list[dict[str, Any]]]:
    result: dict[str, list[dict[str, Any]]] = {}
    for record in obj["records"]:
        if record["section_number"] > 0 and record["name"]:
            result.setdefault(record["name"], []).append(record)
    return result


def _region_specs(regions: Sequence[Mapping[str, Any]]) -> list[dict[str, Any]]:
    result = []
    for ordinal, region in enumerate(regions):
        if not isinstance(region, Mapping):
            raise CoffRegionError(f"region {ordinal} must be a mapping")
        symbol = region.get("symbol")
        if not isinstance(symbol, str) or not symbol:
            raise CoffRegionError(f"region {ordinal} requires a non-empty decorated symbol")
        address = _parse_int(region.get("address"), f"region {symbol} address")
        size = _parse_int(region.get("size"), f"region {symbol} size")
        if address < 0 or size <= 0:
            raise CoffRegionError(f"region {symbol}: address must be nonnegative and size positive")
        result.append({"ordinal": ordinal, "name": region.get("name", symbol), "symbol": symbol,
                       "address": address, "size": size})
    return result


def _select_sections(obj: dict[str, Any], regions: list[dict[str, Any]]) -> tuple[dict[int, dict[str, Any]], list[dict[str, Any]]]:
    sections = {section["number"]: section for section in obj["sections"]}
    by_name = _defined_by_name(obj)
    selected: dict[int, dict[str, Any]] = {}
    selected_regions: list[dict[str, Any]] = []
    for region in regions:
        all_matches = by_name.get(region["symbol"], [])
        all_sections = sorted({record["section_number"] for record in all_matches})
        if len(all_sections) > 1:
            details = ", ".join(
                f"{sections[n]['name']}#{n}/size={sections[n]['raw_size']}" for n in all_sections
            )
            raise CoffRegionError(
                f"region {region['symbol']}: ambiguous definitions across sections ({details})"
            )
        candidates = [record for record in all_matches if record["value"] == 0]
        candidate_sections = sorted({record["section_number"] for record in candidates})
        if len(candidate_sections) > 1:
            details = ", ".join(
                f"{sections[n]['name']}#{n}/size={sections[n]['raw_size']}" for n in candidate_sections
            )
            raise CoffRegionError(
                f"region {region['symbol']}: ambiguous definitions at value 0 in {details}"
            )
        if not candidate_sections:
            if all_matches:
                values = ", ".join(f"{r['value']:#x}" for r in all_matches)
                raise CoffRegionError(f"region {region['symbol']}: no definition at value 0 (values: {values})")
            raise CoffRegionError(f"region {region['symbol']}: decorated symbol not defined")
        section_number = candidate_sections[0]
        section = sections[section_number]
        if section["raw_size"] != region["size"]:
            raise CoffRegionError(
                f"region {region['symbol']}: section {section['name']} extent {section['raw_size']} "
                f"differs from requested size {region['size']}"
            )
        selected.setdefault(section_number, section)
        selected_regions.append({**region, "section_number": section_number})
    return selected, selected_regions


def _referenced_primary_indices(obj: dict[str, Any], selected: Mapping[int, dict[str, Any]]) -> set[int]:
    referenced: set[int] = set()
    for section in selected.values():
        for relocation in section["relocations"]:
            index = relocation["symbol_index"]
            if index not in obj["index_to_primary"]:
                raise CoffRegionError(
                    f"section {section['name']} relocation at {relocation['virtual_address']:#x} "
                    f"references invalid symbol index {index}"
                )
            referenced.add(obj["index_to_primary"][index])
    return referenced


def _build_symbol_plan(
    obj: dict[str, Any],
    selected: Mapping[int, dict[str, Any]],
    bindings: Optional[Mapping[str, Any]],
    output_section_names: Mapping[int, str],
    exported_symbols: set[str],
) -> tuple[list[dict[str, Any]], dict[int, int], list[dict[str, Any]]]:
    """Build output symbols and input-primary to output-index mappings.

    The two mappings are separate because a selected section definition keeps a
    section number while a discarded external definition becomes section zero.
    """

    records = obj["records"]
    selected_numbers = set(selected)
    referenced = _referenced_primary_indices(obj, selected)
    specs: list[dict[str, Any]] = []
    input_to_spec: dict[int, int] = {}
    canonical_undefined: dict[str, int] = {}
    selected_definitions: dict[str, set[int]] = {}
    selected_specs_by_name: dict[str, int] = {}
    sections_by_number = {section["number"]: section for section in obj["sections"]}

    def add_spec(spec: dict[str, Any], dedup_key: Any = None) -> int:
        if dedup_key is not None:
            for index, existing in enumerate(specs):
                if existing.get("dedup_key") == dedup_key:
                    return index
        spec = dict(spec)
        spec["dedup_key"] = dedup_key
        specs.append(spec)
        return len(specs) - 1

    # Preserve all primary symbols defined in selected sections.  Aux records
    # are intentionally omitted; their information is not needed for linking
    # and can carry stale section indexes after normalization.
    for record in records:
        section_number = record["section_number"]
        if section_number not in selected_numbers or not record["name"]:
            continue
        # MSVC emits a static section symbol (usually named ``.text``) for
        # every /Gy COMDAT section.  Those symbols are local metadata, not
        # competing global definitions.  Rename each one to its normalized
        # section so several selected COMDATs can coexist in one output COFF.
        is_section_symbol = (
            record["storage_class"] == IMAGE_SYM_CLASS_STATIC
            and record["type"] == 0
            and record["value"] == 0
            and record["name"] == sections_by_number[section_number]["name"]
        )
        source_name = output_section_names[section_number] if is_section_symbol else record["name"]
        name = _canonical_binding(source_name, bindings)
        selected_definitions.setdefault(name, set()).add(section_number)
        spec = {
            "name": name,
            "value": record["value"],
            "section_number": section_number,
            "type": record["type"],
            # Explicitly selected entries, including compiler-generated EH
            # handlers, must be visible to the fixed-address linker script.
            "storage_class": (IMAGE_SYM_CLASS_EXTERNAL if record["name"] in exported_symbols
                              else record["storage_class"]),
            "input_index": record["index"],
        }
        # Duplicate records in one defined section are aliases for one
        # definition.  Keep one canonical primary record and remap both relocs.
        key = (name, section_number, record["value"], record["type"], record["storage_class"])
        spec_index = add_spec(spec, key)
        input_to_spec[record["index"]] = spec_index
        selected_specs_by_name.setdefault(name, spec_index)

    for name, section_numbers in selected_definitions.items():
        if len(section_numbers) > 1:
            numbers = ", ".join(str(number) for number in sorted(section_numbers))
            raise CoffRegionError(f"selected output has ambiguous defined symbol {name!r} in sections {numbers}")

    def add_undefined(record: dict[str, Any], reason: str) -> int:
        name = _canonical_binding(record["name"], bindings)
        if not name:
            raise CoffRegionError(f"cannot preserve unnamed {reason} symbol at index {record['index']}")
        if name in selected_specs_by_name:
            return selected_specs_by_name[name]
        if name in canonical_undefined:
            return canonical_undefined[name]
        storage = record["storage_class"]
        if storage == IMAGE_SYM_CLASS_WEAK_EXTERNAL or reason == "bound discarded local":
            storage = IMAGE_SYM_CLASS_EXTERNAL
        spec = {
            "name": name,
            "value": 0,
            "section_number": 0,
            "type": record["type"],
            "storage_class": storage,
            "input_index": record["index"],
            "reason": reason,
        }
        index = add_spec(spec, ("undefined", name))
        canonical_undefined[name] = index
        return index

    for record in records:
        section_number = record["section_number"]
        if section_number in selected_numbers:
            continue
        if section_number > 0:
            # A static/local discarded definition cannot safely be turned into
            # an external with the same spelling: another TU may have a local
            # with that spelling.  If selected code refers to it, stop rather
            # than silently binding the wrong object.  The caller can provide a
            # canonical alias through bindings to make the decision explicit.
            if record["index"] in referenced and record["storage_class"] not in (
                IMAGE_SYM_CLASS_EXTERNAL, IMAGE_SYM_CLASS_WEAK_EXTERNAL
            ):
                if not _has_symbol_alias(record["name"], bindings):
                    section = sections_by_number.get(section_number)
                    raise CoffRegionError(
                        f"selected section relocation references local symbol {record['name']!r} "
                        f"from discarded section {section['name'] if section else section_number}; "
                        "provide an explicit binding alias or retain its defining section"
                    )
                input_to_spec[record["index"]] = add_undefined(record, "bound discarded local")
            elif record["storage_class"] in (IMAGE_SYM_CLASS_EXTERNAL, IMAGE_SYM_CLASS_WEAK_EXTERNAL):
                # Every discarded external definition becomes an undefined
                # external.  This is what lets the fixed-address root bind a
                # discarded vtable/import/free without COMDAT preemption.
                input_to_spec[record["index"]] = add_undefined(record, "discarded definition")
            continue
        if section_number == 0 and record["storage_class"] in (
            IMAGE_SYM_CLASS_EXTERNAL, IMAGE_SYM_CLASS_WEAK_EXTERNAL
        ):
            add_undefined(record, "input undefined external")

    # Ensure every relocation target is represented.  Selected definitions were
    # planned above; discarded locals produce the diagnostic above.
    for primary_index in sorted(referenced):
        record = obj["record_by_index"][primary_index]
        section_number = record["section_number"]
        if section_number in selected_numbers:
            if primary_index not in input_to_spec:
                raise CoffRegionError(
                    f"selected relocation references unnamed or unretained symbol index {primary_index}"
                )
            continue
        if section_number == 0 and record["storage_class"] in (
            IMAGE_SYM_CLASS_EXTERNAL, IMAGE_SYM_CLASS_WEAK_EXTERNAL
        ):
            input_to_spec[primary_index] = add_undefined(record, "relocation target")
            continue
        if section_number == -1:
            name = _canonical_binding(record["name"], bindings)
            input_to_spec[primary_index] = add_spec({
                "name": name,
                "value": record["value"],
                "section_number": -1,
                "type": record["type"],
                "storage_class": record["storage_class"],
                "input_index": record["index"],
            }, ("absolute", name, record["value"], record["type"]))
            continue
        if primary_index not in input_to_spec:
            raise CoffRegionError(
                f"selected relocation target {record['name']!r} has no safe output symbol"
            )

    # ``input_to_spec`` already contains final output-primary indexes because
    # every emitted symbol has exactly one record and aux records are omitted.
    return specs, input_to_spec, [{
        "index": record["index"], "name": record["name"],
        "section_number": record["section_number"], "value": record["value"],
        "storage_class": record["storage_class"],
    } for record in records if record["index"] in referenced]


def _write_name_table(symbol_specs: list[dict[str, Any]]) -> tuple[list[bytes], bytes]:
    strings = bytearray(struct.pack("<I", 4))
    offsets: dict[str, int] = {}
    encoded = []
    for spec in symbol_specs:
        encoded.append(_encode_name(spec["name"], strings, offsets))
    struct.pack_into("<I", strings, 0, len(strings))
    return encoded, bytes(strings)


def normalize_object(
    input_path: str | Path,
    output_path: str | Path,
    regions: Sequence[Mapping[str, Any]],
    bindings: Optional[Mapping[str, Any]] = None,
) -> dict[str, Any]:
    """Write a normalized COFF object containing the requested whole sections.

    ``regions`` records require ``symbol`` (the exact decorated symbol),
    ``address`` (retail address, retained only in the report), and ``size``
    (the complete input section extent).  ``bindings`` optionally aliases a
    symbol to a canonical external name; it never writes an address into code.

    The return value includes one record per requested region.  In particular,
    ``original_relocations`` preserves each selected section's input relocation
    virtual address and type, and ``sha256`` is the hash of the unmodified raw
    section bytes.
    """

    source = Path(input_path)
    destination = Path(output_path)
    obj = _read_object(source)
    specs = _region_specs(regions)
    selected, selected_regions = _select_sections(obj, specs)
    selected_numbers = sorted(selected)
    output_section_names = {
        number: f".r{position:06d}" for position, number in enumerate(selected_numbers, 1)
    }

    symbol_specs, input_to_spec, referenced_records = _build_symbol_plan(
        obj, selected, bindings, output_section_names, {region["symbol"] for region in specs}
    )
    # Every symbol spec currently occupies one primary record; this is useful
    # for relocation remapping and makes the omission of aux records explicit.
    encoded_names, string_table = _write_name_table(symbol_specs)

    # Validate all relocation targets and prepare their exact original report
    # before writing any output bytes.
    original_relocations: dict[int, list[dict[str, Any]]] = {}
    for number in selected_numbers:
        section = selected[number]
        rows = []
        for relocation in section["relocations"]:
            input_primary = obj["index_to_primary"][relocation["symbol_index"]]
            if input_primary not in input_to_spec:
                raise CoffRegionError(
                    f"section {section['name']} relocation at {relocation['virtual_address']:#x} "
                    f"has no normalized symbol for input index {input_primary}"
                )
            target = obj["record_by_index"][input_primary]
            rows.append({
                "virtual_address": relocation["virtual_address"],
                "type": relocation["type"],
                "symbol_index": relocation["symbol_index"],
                "primary_symbol_index": input_primary,
                "symbol": target["name"],
                "raw": relocation["raw"].hex().upper(),
            })
        original_relocations[number] = rows

    # Layout: header, section table, selected raw data, relocation tables,
    # symbol table, string table.  No input instruction/data bytes are touched.
    section_count = len(selected_numbers)
    section_table_offset = 20
    cursor = section_table_offset + section_count * 40
    raw_offsets: dict[int, int] = {}
    for number in selected_numbers:
        section = selected[number]
        raw_offsets[number] = cursor if section["raw"] else 0
        cursor += len(section["raw"])
    reloc_offsets: dict[int, int] = {}
    for number in selected_numbers:
        rows = selected[number]["relocations"]
        reloc_offsets[number] = cursor if rows else 0
        cursor += len(rows) * 10
    symbol_offset = cursor
    symbol_count = len(symbol_specs)
    cursor += symbol_count * 18
    cursor += len(string_table)

    output = bytearray(cursor)
    struct.pack_into(
        "<HHIIIHH", output, 0, obj["machine"], section_count, obj["timestamp"],
        symbol_offset, symbol_count, 0, obj["characteristics"]
    )
    for position, number in enumerate(selected_numbers):
        section = selected[number]
        name = output_section_names[number].encode("ascii")
        characteristics = section["characteristics"] & ~IMAGE_SCN_LNK_COMDAT
        header = struct.pack(
            "<8sIIIIIIHHI", name.ljust(8, b"\0"), section["misc"],
            section["virtual_address"], len(section["raw"]), raw_offsets[number],
            reloc_offsets[number], 0, len(section["relocations"]), 0, characteristics
        )
        section_header_offset = section_table_offset + position * 40
        output[section_header_offset:section_header_offset + 40] = header
        if section["raw"]:
            start = raw_offsets[number]
            output[start:start + len(section["raw"])] = section["raw"]
        for index, relocation in enumerate(section["relocations"]):
            input_primary = obj["index_to_primary"][relocation["symbol_index"]]
            output_symbol = input_to_spec[input_primary]
            roff = reloc_offsets[number] + index * 10
            struct.pack_into("<IIH", output, roff, relocation["virtual_address"], output_symbol, relocation["type"])

    for index, spec in enumerate(symbol_specs):
        section_number = spec["section_number"]
        if section_number > 0:
            section_number = selected_numbers.index(section_number) + 1
        offset = symbol_offset + index * 18
        output[offset:offset + 18] = struct.pack(
            "<8sIhHBB", encoded_names[index], spec["value"], section_number,
            spec["type"], spec["storage_class"], 0
        )
    output[symbol_offset + symbol_count * 18:] = string_table
    destination.parent.mkdir(parents=True, exist_ok=True)
    destination.write_bytes(output)

    region_reports = []
    for region in selected_regions:
        number = region["section_number"]
        section = selected[number]
        raw_hash = hashlib.sha256(section["raw"]).hexdigest()
        report_relocs = original_relocations[number]
        region_reports.append({
            "name": region["name"],
            "symbol": region["symbol"],
            "address": region["address"],
            "size": region["size"],
            "source_section": section["name"],
            "source_section_number": number,
            "section": output_section_names[number],
            "section_name": output_section_names[number],
            "sha256": raw_hash,
            "section_sha256": raw_hash,
            "original_relocations": report_relocs,
            "relocation_count": len(report_relocs),
        })

    return {
        "input": str(source),
        "output": str(destination),
        "regions": region_reports,
        "selected_sections": [
            {
                "source_section": selected[number]["name"],
                "section": output_section_names[number],
                "size": len(selected[number]["raw"]),
                "sha256": hashlib.sha256(selected[number]["raw"]).hexdigest(),
                "relocation_count": len(selected[number]["relocations"]),
            }
            for number in selected_numbers
        ],
        "selected_section_count": section_count,
        "output_symbol_count": symbol_count,
        "referenced_input_symbols": referenced_records,
    }


__all__ = ["CoffRegionError", "normalize_object"]
