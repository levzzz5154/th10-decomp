#!/usr/bin/env python3
"""Package compiled code and versioned non-code data into the byte-exact TH10 PE.

The packer has no implicit retail input.  The original non-code bytes are
versioned under ``matching2/reference/data`` and the header is reconstructed from
the declarative layout.  ``--verify`` is an explicit post-build oracle check;
it is the only mode that reads an executable outside the package inputs.
"""

from __future__ import annotations

import hashlib
import json
from pathlib import Path
import struct
from typing import Any, Mapping


class PackError(RuntimeError):
    """The layout or an input asset is not safe to package."""


def _integer(value: Any, field: str) -> int:
    if isinstance(value, bool):
        raise PackError(f"{field} must be an integer")
    try:
        result = int(value, 0) if isinstance(value, str) else int(value)
    except (TypeError, ValueError) as exc:
        raise PackError(f"{field} must be an integer") from exc
    if result < 0:
        raise PackError(f"{field} must be non-negative")
    return result


def _sha256(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


def _load_layout(path: Path) -> dict[str, Any]:
    try:
        layout = json.loads(path.read_text(encoding="utf-8"))
    except (OSError, json.JSONDecodeError) as exc:
        raise PackError(f"cannot read layout {path}: {exc}") from exc
    if not isinstance(layout, dict) or layout.get("schema") != "th10-asm-pe-layout/v1":
        raise PackError("unsupported or missing PE layout schema")
    return layout


def _read_asset(layout_path: Path, path_name: str, expected_size: int, expected_hash: str) -> bytes:
    path = (layout_path.parent / path_name).resolve()
    try:
        data = path.read_bytes()
    except OSError as exc:
        raise PackError(f"cannot read versioned asset {path}: {exc}") from exc
    if len(data) != expected_size:
        raise PackError(f"asset {path_name} has {len(data)} bytes; expected {expected_size}")
    actual_hash = _sha256(data)
    if actual_hash != expected_hash:
        raise PackError(f"asset {path_name} hash mismatch: expected {expected_hash}, got {actual_hash}")
    return data


def _pack_coff(coff: Mapping[str, Any]) -> bytes:
    keys = (
        "machine", "number_of_sections", "timestamp", "pointer_to_symbol_table",
        "number_of_symbols", "size_of_optional_header", "characteristics",
    )
    values = [_integer(coff.get(key), f"coff.{key}") for key in keys]
    return struct.pack("<HHIIIHH", *values)


def _pack_optional(optional: Mapping[str, Any], directories: list[Mapping[str, Any]]) -> bytes:
    result = bytearray()
    result += struct.pack("<HBB", _integer(optional.get("magic"), "optional.magic"),
                          _integer(optional.get("major_linker_version"), "optional.major_linker_version"),
                          _integer(optional.get("minor_linker_version"), "optional.minor_linker_version"))
    for key in (
        "size_of_code", "size_of_initialized_data", "size_of_uninitialized_data",
        "address_of_entry_point", "base_of_code", "base_of_data", "image_base",
        "section_alignment", "file_alignment",
    ):
        result += struct.pack("<I", _integer(optional.get(key), f"optional.{key}"))
    for key in (
        "major_operating_system_version", "minor_operating_system_version",
        "major_image_version", "minor_image_version", "major_subsystem_version",
        "minor_subsystem_version",
    ):
        result += struct.pack("<H", _integer(optional.get(key), f"optional.{key}"))
    for key in ("win32_version_value", "size_of_image", "size_of_headers", "checksum"):
        result += struct.pack("<I", _integer(optional.get(key), f"optional.{key}"))
    for key in ("subsystem", "dll_characteristics"):
        result += struct.pack("<H", _integer(optional.get(key), f"optional.{key}"))
    for key in (
        "size_of_stack_reserve", "size_of_stack_commit", "size_of_heap_reserve",
        "size_of_heap_commit", "loader_flags", "number_of_rva_and_sizes",
    ):
        result += struct.pack("<I", _integer(optional.get(key), f"optional.{key}"))
    if len(directories) != _integer(optional.get("number_of_rva_and_sizes"), "optional.number_of_rva_and_sizes"):
        raise PackError("data directory count does not match optional header")
    for index, directory in enumerate(directories):
        result += struct.pack("<II", _integer(directory.get("rva"), f"data_directories[{index}].rva"),
                              _integer(directory.get("size"), f"data_directories[{index}].size"))
    if len(result) != 224:
        raise PackError(f"PE32 optional header encoded as {len(result)} bytes, expected 224")
    return bytes(result)


def _pack_section(section: Mapping[str, Any]) -> bytes:
    name = section.get("name")
    if not isinstance(name, str) or not name or len(name.encode("ascii", errors="ignore")) > 8:
        raise PackError("section name must be a non-empty ASCII string of at most 8 bytes")
    try:
        encoded_name = name.encode("ascii")
    except UnicodeEncodeError as exc:
        raise PackError(f"section name is not ASCII: {name!r}") from exc
    fields = [
        _integer(section.get("virtual_size"), f"section {name}.virtual_size"),
        _integer(section.get("virtual_address"), f"section {name}.virtual_address"),
        _integer(section.get("raw_size"), f"section {name}.raw_size"),
        _integer(section.get("raw_offset"), f"section {name}.raw_offset"),
        _integer(section.get("pointer_to_relocations"), f"section {name}.pointer_to_relocations"),
        _integer(section.get("pointer_to_linenumbers"), f"section {name}.pointer_to_linenumbers"),
        _integer(section.get("number_of_relocations"), f"section {name}.number_of_relocations"),
        _integer(section.get("number_of_linenumbers"), f"section {name}.number_of_linenumbers"),
        _integer(section.get("characteristics"), f"section {name}.characteristics"),
    ]
    return struct.pack("<8sIIIIIIHHI", encoded_name.ljust(8, b"\0"), *fields)


def _rol32(value: int, shift: int) -> int:
    shift &= 31
    return ((value << shift) | (value >> (32 - shift))) & 0xFFFFFFFF


def _pack_dos_header(spec: Mapping[str, Any]) -> bytes:
    words = [0] * 30
    field_offsets = {
        "e_magic": 0, "e_cblp": 1, "e_cp": 2, "e_crlc": 3, "e_cparhdr": 4,
        "e_minalloc": 5, "e_maxalloc": 6, "e_ss": 7, "e_sp": 8, "e_csum": 9,
        "e_ip": 10, "e_cs": 11, "e_lfarlc": 12, "e_ovno": 13,
        "e_oemid": 18, "e_oeminfo": 19,
    }
    for name, idx in field_offsets.items():
        if name in spec:
            words[idx] = _integer(spec[name], f"dos_prefix.header.{name}")
    e_lfanew = _integer(spec.get("e_lfanew"), "dos_prefix.header.e_lfanew")
    return struct.pack("<30HI", *words, e_lfanew)


def _pack_rich_metadata(spec: Mapping[str, Any], dos_header: bytes, dos_stub: bytes) -> bytes:
    records = spec.get("records")
    if not isinstance(records, list) or not records:
        raise PackError("dos_prefix.rich_metadata.records must be a non-empty list")
    prefix = dos_header + dos_stub
    checksum = len(prefix)
    for idx, byte in enumerate(prefix):
        if 0x3C <= idx < 0x40:
            continue
        checksum = (checksum + _rol32(byte, idx)) & 0xFFFFFFFF
    clear = bytearray(b"DanS" + b"\0" * 12)
    for idx, entry in enumerate(records):
        if not isinstance(entry, Mapping):
            raise PackError(f"dos_prefix.rich_metadata.records[{idx}] must be an object")
        prod_id = _integer(entry.get("prod_id"), f"dos_prefix.rich_metadata.records[{idx}].prod_id")
        build = _integer(entry.get("build"), f"dos_prefix.rich_metadata.records[{idx}].build")
        count = _integer(entry.get("count"), f"dos_prefix.rich_metadata.records[{idx}].count")
        comp_id = (prod_id << 16) | build
        checksum = (checksum + _rol32(comp_id, count)) & 0xFFFFFFFF
        clear += struct.pack("<II", comp_id, count)
    encoded = bytearray()
    for off in range(0, len(clear), 4):
        word = struct.unpack_from("<I", clear, off)[0]
        encoded += struct.pack("<I", word ^ checksum)
    trailing_zeros = _integer(spec.get("trailing_zeros", 0), "dos_prefix.rich_metadata.trailing_zeros")
    encoded += b"Rich" + struct.pack("<I", checksum) + b"\0" * trailing_zeros
    return bytes(encoded)


def _build_dos_prefix(layout_path: Path, spec: Mapping[str, Any], dos_stub: bytes) -> bytes:
    header_spec = spec.get("header")
    rich_spec = spec.get("rich_metadata")
    if not isinstance(header_spec, Mapping) or not isinstance(rich_spec, Mapping):
        raise PackError("dos_prefix requires header and rich_metadata specs")
    if "path" in header_spec:
        header = _read_asset(layout_path, str(header_spec["path"]),
                             _integer(header_spec["size"], "dos_prefix.header.size"),
                             str(header_spec["sha256"]))
    else:
        header = _pack_dos_header(header_spec)
        expected_header_size = _integer(header_spec["size"], "dos_prefix.header.size")
        if len(header) != expected_header_size:
            raise PackError(f"DOS header has {len(header)} bytes; expected {expected_header_size}")
        if _sha256(header) != str(header_spec["sha256"]):
            raise PackError(f"DOS header hash mismatch: expected {header_spec['sha256']}, got {_sha256(header)}")
    if spec["code"].get("source") != "linker.dos_stub":
        raise PackError("dos_prefix.code must come from the PE linker")
    expected_code_size = _integer(spec["code"].get("size"), "dos_prefix.code.size")
    if len(dos_stub) != expected_code_size:
        raise PackError(f"DOS stub has {len(dos_stub)} bytes; expected {expected_code_size}")
    expected_code_hash = str(spec["code"].get("sha256"))
    actual_code_hash = _sha256(dos_stub)
    if actual_code_hash != expected_code_hash:
        raise PackError(f"DOS stub hash mismatch: expected {expected_code_hash}, got {actual_code_hash}")
    if "path" in rich_spec:
        rich = _read_asset(layout_path, str(rich_spec["path"]),
                           _integer(rich_spec["size"], "dos_prefix.rich_metadata.size"),
                           str(rich_spec["sha256"]))
    else:
        rich = _pack_rich_metadata(rich_spec, header, dos_stub)
        expected_rich_size = _integer(rich_spec["size"], "dos_prefix.rich_metadata.size")
        if len(rich) != expected_rich_size:
            raise PackError(f"Rich metadata has {len(rich)} bytes; expected {expected_rich_size}")
        if _sha256(rich) != str(rich_spec["sha256"]):
            raise PackError(f"Rich metadata hash mismatch: expected {rich_spec['sha256']}, got {_sha256(rich)}")
    prefix = header + dos_stub + rich
    expected_size = _integer(spec.get("size"), "dos_prefix.size")
    if len(prefix) != expected_size:
        raise PackError(f"DOS prefix has {len(prefix)} bytes; expected {expected_size}")
    expected_hash = str(spec.get("sha256"))
    actual_hash = _sha256(prefix)
    if actual_hash != expected_hash:
        raise PackError(f"DOS prefix hash mismatch: expected {expected_hash}, got {actual_hash}")
    return prefix


def _build_headers(layout: Mapping[str, Any], sections: list[Mapping[str, Any]]) -> bytes:
    image = layout["image"]
    pe_offset = _integer(image.get("pe_offset"), "image.pe_offset")
    headers_size = _integer(image.get("size_of_headers"), "image.size_of_headers")
    dos_spec = layout["dos_prefix"]
    dos_size = _integer(dos_spec.get("size"), "dos_prefix.size")
    if dos_size != pe_offset:
        raise PackError("DOS prefix must end exactly at the PE header offset")
    coff = _pack_coff(layout["coff"])
    optional = _pack_optional(layout["optional"], layout["data_directories"])
    section_table = b"".join(_pack_section(section) for section in sections)
    headers = b"PE\0\0" + coff + optional + section_table
    if pe_offset + len(headers) > headers_size:
        raise PackError("PE headers and section table exceed SizeOfHeaders")
    return headers + b"\0" * (headers_size - pe_offset - len(headers))


def _validate_layout(layout: Mapping[str, Any]) -> list[Mapping[str, Any]]:
    sections = layout.get("sections")
    if not isinstance(sections, list) or not sections:
        raise PackError("layout must contain a non-empty sections list")
    coff_count = _integer(layout["coff"].get("number_of_sections"), "coff.number_of_sections")
    if coff_count != len(sections):
        raise PackError("COFF section count does not match layout")
    names = [section.get("name") for section in sections]
    if any(not isinstance(name, str) for name in names) or len(set(names)) != len(names):
        raise PackError("section names must be unique strings")
    for section in sections:
        name = section.get("name")
        declared_executable = bool(section.get("executable"))
        characteristic_executable = bool(_integer(section.get("characteristics"),
                                                  f"section {name}.characteristics") & 0x20000000)
        if declared_executable != characteristic_executable:
            raise PackError(f"section {name} executable flag disagrees with characteristics")
    executable = [name for section, name in zip(sections, names) if section.get("executable")]
    if executable != [".text"]:
        raise PackError(f"only .text may be executable; layout claims {executable!r}")
    text = [section for section in sections if section.get("name") == ".text"]
    if len(text) != 1 or text[0].get("source") != "input.text":
        raise PackError("layout must have exactly one .text section sourced from input.text")
    expected_size = _integer(layout["reference"].get("text_section_bytes"), "reference.text_section_bytes")
    if _integer(text[0].get("raw_size"), "section .text.raw_size") != expected_size:
        raise PackError(".text raw size does not match the strict reference size")
    file_size = _integer(layout["reference"].get("file_size"), "reference.file_size")
    header_size = _integer(layout["image"].get("size_of_headers"), "image.size_of_headers")
    intervals = []
    for section in sections:
        name = section["name"]
        start = _integer(section.get("raw_offset"), f"section {name}.raw_offset")
        size = _integer(section.get("raw_size"), f"section {name}.raw_size")
        if start < header_size or start + size > file_size:
            raise PackError(f"section {name} raw range is outside the declared file")
        intervals.append((start, start + size, name))
    intervals.sort()
    cursor = header_size
    for start, end, name in intervals:
        if start != cursor:
            raise PackError(f"unaccounted file range between {cursor:#x} and {start:#x}")
        cursor = end
    if cursor != file_size:
        raise PackError(f"unaccounted file tail from {cursor:#x} to {file_size:#x}")
    return sections


def build_image(layout_path: Path, text_path: Path, output_path: Path, *,
                dos_stub: bytes, expected_differing_bytes: int = 0,
                oracle: bytes | None = None) -> dict[str, Any]:
    """Package the checked .text. An explicit oracle verifies the entire file.

    Only the caller's already-verified equivalent bodies may contribute
    differences. Headers and every non-code section must always match.
    """

    layout = _load_layout(layout_path)
    sections = _validate_layout(layout)
    reference = layout["reference"]
    expected_text_size = _integer(reference["text_section_bytes"], "reference.text_section_bytes")
    try:
        text = text_path.read_bytes()
    except OSError as exc:
        raise PackError(f"cannot read compiled .text input {text_path}: {exc}") from exc
    if len(text) != expected_text_size:
        raise PackError(f"compiled .text has {len(text)} bytes; expected {expected_text_size}")
    expected_text_hash = str(reference["text_section_sha256"])
    actual_text_hash = _sha256(text)
    if not 0 <= expected_differing_bytes <= len(text):
        raise PackError("expected difference count exceeds the compiled .text extent")
    if expected_differing_bytes == 0 and actual_text_hash != expected_text_hash:
        raise PackError(f"compiled .text hash mismatch: expected {expected_text_hash}, got {actual_text_hash}")

    dos_spec = layout["dos_prefix"]
    dos = _build_dos_prefix(layout_path, dos_spec, dos_stub)
    header = dos + _build_headers(layout, sections)
    header_size = _integer(layout["image"].get("size_of_headers"), "image.size_of_headers")
    if len(header) != header_size:
        raise PackError(f"encoded headers have {len(header)} bytes; expected {header_size}")
    expected_header_hash = str(reference["header_sha256"])
    actual_header_hash = _sha256(header)
    if actual_header_hash != expected_header_hash:
        raise PackError(f"header hash mismatch: expected {expected_header_hash}, got {actual_header_hash}")

    file_size = _integer(reference["file_size"], "reference.file_size")
    image = bytearray(file_size)
    image[:header_size] = header
    for section in sections:
        name = section["name"]
        start = _integer(section["raw_offset"], f"section {name}.raw_offset")
        size = _integer(section["raw_size"], f"section {name}.raw_size")
        if name == ".text":
            payload = text
        else:
            source = section.get("source")
            if not isinstance(source, str) or source == "input.text":
                raise PackError(f"non-code section {name} has no versioned data source")
            payload = _read_asset(layout_path, source, size, str(section.get("sha256")))
        image[start:start + size] = payload

    actual_image_hash = _sha256(image)
    expected_image_hash = str(reference["executable_sha256"])
    exact = actual_image_hash == expected_image_hash
    if not exact and not expected_differing_bytes:
        raise PackError(f"packed image hash mismatch: expected {expected_image_hash}, got {actual_image_hash}")
    if exact and expected_differing_bytes:
        raise PackError("packed image is exact despite differences in the selected bodies")

    observed = None
    if oracle is not None:
        if len(oracle) != len(image) or _sha256(oracle) != expected_image_hash:
            raise PackError("verification oracle does not match the supported reference")
        observed = 0 if image == oracle else sum(a != b for a, b in zip(image, oracle))
        if observed != expected_differing_bytes:
            raise PackError(f"packed image differs from retail at {observed} byte positions; "
                            f"the selected bodies account for {expected_differing_bytes}")

    output_path.parent.mkdir(parents=True, exist_ok=True)
    output_path.write_bytes(image)

    return {
        "output": str(output_path),
        "sha256": actual_image_hash,
        "size": len(image),
        "text_sha256": actual_text_hash,
        "text_bytes": len(text),
        "sections": [{"name": section["name"], "raw_offset": section["raw_offset"],
                      "raw_size": section["raw_size"]} for section in sections],
        "exact": exact,
        "verified_against_oracle": oracle is not None,
        "oracle_differing_bytes": observed,
    }
