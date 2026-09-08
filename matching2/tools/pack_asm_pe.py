#!/usr/bin/env python3
"""Package an independently assembled ``.text`` buffer into the TH10 PE.

The packer has no implicit retail input.  The original non-code bytes are
versioned under ``matching2/asm/data`` and the header is reconstructed from
the declarative layout.  ``--verify`` is an explicit post-build oracle check;
it is the only mode that reads an executable outside the package inputs.
"""

from __future__ import annotations

import argparse
import hashlib
import json
from pathlib import Path
import shutil
import subprocess
import struct
import sys
import tempfile
from typing import Any, Mapping


ROOT = Path(__file__).resolve().parents[2]
DEFAULT_LAYOUT = ROOT / "matching2" / "asm" / "pe_layout.json"


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


def _assemble_dos_code(layout_path: Path, spec: Mapping[str, Any], assembler: str,
                       objcopy: str) -> bytes:
    source_name = spec.get("source")
    if not isinstance(source_name, str):
        raise PackError("dos_prefix.code.source is required")
    source = (layout_path.parent / source_name).resolve()
    assembler_path = shutil.which(assembler) if "/" not in assembler else assembler
    objcopy_path = shutil.which(objcopy) if "/" not in objcopy else objcopy
    if not assembler_path:
        raise PackError(f"DOS stub assembler not found: {assembler}")
    if not objcopy_path:
        raise PackError(f"DOS stub objcopy not found: {objcopy}")
    with tempfile.TemporaryDirectory(prefix="th10-dos-stub-") as temporary:
        object_path = Path(temporary) / "dos_stub.o"
        binary_path = Path(temporary) / "dos_stub.bin"
        try:
            assembled = subprocess.run(
                [assembler_path, "--32", str(source), "-o", str(object_path)],
                check=False, capture_output=True, text=True,
            )
            if assembled.returncode:
                raise PackError(f"DOS stub assembly failed: {assembled.stderr.strip()}")
            extracted = subprocess.run(
                [objcopy_path, "-O", "binary", "-j", ".text", str(object_path), str(binary_path)],
                check=False, capture_output=True, text=True,
            )
            if extracted.returncode:
                raise PackError(f"DOS stub objcopy failed: {extracted.stderr.strip()}")
            return binary_path.read_bytes()
        except OSError as exc:
            raise PackError(f"cannot assemble DOS stub {source}: {exc}") from exc


def _build_dos_prefix(layout_path: Path, spec: Mapping[str, Any], assembler: str,
                      objcopy: str, dos_code: bytes | None = None) -> bytes:
    header_spec = spec.get("header")
    rich_spec = spec.get("rich_metadata")
    if not isinstance(header_spec, Mapping) or not isinstance(rich_spec, Mapping):
        raise PackError("dos_prefix requires header and rich_metadata assets")
    header = _read_asset(layout_path, str(header_spec["path"]), _integer(header_spec["size"], "dos_prefix.header.size"),
                         str(header_spec["sha256"]))
    if dos_code is None:
        code = _assemble_dos_code(layout_path, spec["code"], assembler, objcopy)
    else:
        if not isinstance(dos_code, bytes):
            raise PackError("dos_code must be bytes")
        code = dos_code
    expected_code_size = _integer(spec["code"].get("size"), "dos_prefix.code.size")
    if len(code) != expected_code_size:
        raise PackError(f"DOS stub has {len(code)} bytes; expected {expected_code_size}")
    expected_code_hash = str(spec["code"].get("sha256"))
    if _sha256(code) != expected_code_hash:
        raise PackError(f"DOS stub hash mismatch: expected {expected_code_hash}, got {_sha256(code)}")
    rich = _read_asset(layout_path, str(rich_spec["path"]), _integer(rich_spec["size"], "dos_prefix.rich_metadata.size"),
                       str(rich_spec["sha256"]))
    prefix = header + code + rich
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


def build_image(layout_path: Path, text_path: Path, output_path: Path,
                verify_path: Path | None = None,
                assembler: str = "i686-w64-mingw32-as",
                objcopy: str = "objcopy", *,
                dos_code: bytes | None = None) -> dict[str, Any]:
    """Build and validate an image, returning a small reproducibility report."""

    layout = _load_layout(layout_path)
    sections = _validate_layout(layout)
    reference = layout["reference"]
    expected_text_size = _integer(reference["text_section_bytes"], "reference.text_section_bytes")
    try:
        text = text_path.read_bytes()
    except OSError as exc:
        raise PackError(f"cannot read assembled .text input {text_path}: {exc}") from exc
    if len(text) != expected_text_size:
        raise PackError(f"assembled .text has {len(text)} bytes; expected {expected_text_size}")
    expected_text_hash = str(reference["text_section_sha256"])
    actual_text_hash = _sha256(text)
    if actual_text_hash != expected_text_hash:
        raise PackError(f"assembled .text hash mismatch: expected {expected_text_hash}, got {actual_text_hash}")

    dos_spec = layout["dos_prefix"]
    dos = _build_dos_prefix(layout_path, dos_spec, assembler, objcopy, dos_code=dos_code)
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
    if actual_image_hash != expected_image_hash:
        raise PackError(f"packed image hash mismatch: expected {expected_image_hash}, got {actual_image_hash}")

    if verify_path is not None:
        try:
            oracle = verify_path.read_bytes()
        except OSError as exc:
            raise PackError(f"cannot read verification oracle {verify_path}: {exc}") from exc
        if _sha256(oracle) != expected_image_hash:
            raise PackError("verification oracle SHA-256 does not match the supported reference")
        if oracle != image:
            raise PackError("packed image differs from the explicit verification oracle")

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
        "verified_against_oracle": verify_path is not None,
    }


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--text", type=Path, required=True,
                        help="raw assembled .text section, exactly 412672 bytes")
    parser.add_argument("--output", type=Path, required=True, help="output PE path")
    parser.add_argument("--layout", type=Path, default=DEFAULT_LAYOUT)
    parser.add_argument("--assembler", default="i686-w64-mingw32-as",
                        help="assembler used for the versioned 16-bit DOS stub")
    parser.add_argument("--objcopy", default="objcopy",
                        help="objcopy used to make the DOS stub flat binary")
    parser.add_argument("--verify", type=Path, default=None,
                        help="optional explicit retail oracle checked only after packaging")
    args = parser.parse_args(argv)
    try:
        report = build_image(args.layout.resolve(), args.text.resolve(), args.output.resolve(),
                             args.verify.resolve() if args.verify else None,
                             args.assembler, args.objcopy)
    except (KeyError, TypeError, PackError) as exc:
        parser.error(str(exc))
    print(json.dumps(report, indent=2))
    return 0


if __name__ == "__main__":
    sys.exit(main())
