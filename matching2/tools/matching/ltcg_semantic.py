#!/usr/bin/env python3
"""Build and inspect small MSVC 7.1 LTCG semantic clusters.

This exploratory tool compiles one or more C++98 translation units with the
retail compiler profile, retains an external root, links with ``link.exe /LTCG``,
and inspects explicitly named functions in the linker's final PE layout.
The maintained fixed-layout build uses ``ltcg_cluster.py`` for reviewed native
clusters, adding complete-contribution ownership checks and unchanged body
export at the final executable's fixed addresses.

Input is a JSON manifest.  Paths are relative to the manifest unless absolute::

    {
      "schema_version": 1,
      "name": "d3d-clear-pending",
      "sources": [
        {"path": "d3d.cpp", "role": "cluster"},
        {"path": "d3d_stubs.cpp", "role": "stub"}
      ],
      "include_dirs": ["../../include"],
      "defines": ["PROBE_BUILD=1"],
      "entry_symbol": "?ProbeRoot@@YGXPAUState@@@Z",
      "retain_symbols": [],
      "functions": [
        {
          "name": "ClearPending",
          "symbol": "?ClearPending@@YGXPAUState@@@Z",
          "visibility": "static",
          "size": 12,
          "expected_hex": "33 c9 89 48 08 89 48 0c 89 48 10 c3"
        }
      ]
    }

``cluster`` sources are compiled with /O2 and /GL.  A ``stub`` source is
ordinary C++ compiled without /GL, so its externally visible definitions form
an optimization boundary while satisfying references from the cluster.  Stub
signatures and calling conventions therefore remain explicit, reviewable C++;
this pipeline never synthesizes machine-code bodies.  All unresolved symbols
remain hard linker errors.

Every requested function needs a known byte extent.  This is intentional: a
Microsoft MAP file records symbol starts, not exact function lengths.  The tool
checks the requested extent against MAP symbols, MAP code contributions, PE
sections, and optional expected bytes/hash rather than guessing by trimming
alignment padding.
"""

from __future__ import annotations

import argparse
from dataclasses import dataclass
import hashlib
import json
import os
from pathlib import Path
import re
import shutil
import struct
import subprocess
import sys
from typing import Any, Iterable, Mapping, Sequence


ROOT = Path(__file__).resolve().parents[3]
DEFAULT_TOOLKIT = Path.home() / ".local/share/th10-toolchains/msvc-13.10.6030"
COMPILER_VERSION = "13.10.6030"
LINKER_VERSION = "7.10.6030"

CLUSTER_FLAGS = (
    "/nologo", "/c", "/O2", "/GL", "/Gz", "/MT", "/Gy", "/G6", "/GF", "/Zl"
)
STUB_FLAGS = tuple(flag for flag in CLUSTER_FLAGS if flag != "/GL")


class LTCGSemanticError(ValueError):
    """The manifest or a compiler/linker artifact failed a strict check."""


def _parse_int(value: Any, field: str, *, minimum: int = 0) -> int:
    if isinstance(value, bool):
        raise LTCGSemanticError(f"{field} must be an integer, not bool")
    try:
        parsed = int(value, 0) if isinstance(value, str) else int(value)
    except (TypeError, ValueError) as exc:
        raise LTCGSemanticError(f"{field} must be an integer: {value!r}") from exc
    if parsed < minimum:
        raise LTCGSemanticError(f"{field} must be at least {minimum}")
    return parsed


def _sha256(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


def _require_string(value: Any, field: str) -> str:
    if not isinstance(value, str) or not value:
        raise LTCGSemanticError(f"{field} must be a non-empty string")
    if "\0" in value or "\r" in value or "\n" in value:
        raise LTCGSemanticError(f"{field} contains a control character")
    return value


@dataclass(frozen=True)
class PESection:
    name: str
    address: int
    virtual_size: int
    raw_size: int
    raw_offset: int
    characteristics: int

    @property
    def end_address(self) -> int:
        return self.address + self.virtual_size


class PEImage:
    """Strict reader for the small x86 PE32 images emitted by link.exe."""

    def __init__(self, data: bytes):
        self.data = data
        if len(data) < 0x40 or data[:2] != b"MZ":
            raise LTCGSemanticError("linked output is not a DOS/PE image")
        self.pe_offset = struct.unpack_from("<I", data, 0x3C)[0]
        if self.pe_offset < 0x40 or self.pe_offset + 24 > len(data):
            raise LTCGSemanticError("PE header offset is outside the linked image")
        if data[self.pe_offset:self.pe_offset + 4] != b"PE\0\0":
            raise LTCGSemanticError("linked output has no PE signature")

        (machine, section_count, self.timestamp, _symbol_table, _symbol_count,
         optional_size, _characteristics) = struct.unpack_from(
            "<HHIIIHH", data, self.pe_offset + 4
        )
        if machine != 0x14C:
            raise LTCGSemanticError(f"linked output machine is {machine:#x}, expected x86")
        optional = self.pe_offset + 24
        if optional_size < 96 or optional + optional_size > len(data):
            raise LTCGSemanticError("linked output has a truncated PE32 optional header")
        if struct.unpack_from("<H", data, optional)[0] != 0x10B:
            raise LTCGSemanticError("linked output is not PE32")

        self.linker_version = (data[optional + 2], data[optional + 3])
        self.entry_rva = struct.unpack_from("<I", data, optional + 16)[0]
        self.image_base = struct.unpack_from("<I", data, optional + 28)[0]
        self.section_alignment = struct.unpack_from("<I", data, optional + 32)[0]
        self.file_alignment = struct.unpack_from("<I", data, optional + 36)[0]
        self.entry = self.image_base + self.entry_rva

        table = optional + optional_size
        if table + section_count * 40 > len(data):
            raise LTCGSemanticError("linked output has a truncated PE section table")
        sections: list[PESection] = []
        raw_ranges: list[tuple[int, int, str]] = []
        virtual_ranges: list[tuple[int, int, str]] = []
        for index in range(section_count):
            fields = struct.unpack_from("<8sIIIIIIHHI", data, table + index * 40)
            try:
                name = fields[0].rstrip(b"\0").decode("ascii")
            except UnicodeDecodeError as exc:
                raise LTCGSemanticError("PE section name is not ASCII") from exc
            virtual_size, rva, raw_size, raw_offset = fields[1:5]
            if not name:
                raise LTCGSemanticError("linked output has an unnamed PE section")
            if raw_size and (not raw_offset or raw_offset + raw_size > len(data)):
                raise LTCGSemanticError(f"PE section {name} has an invalid raw-data range")
            if virtual_size and rva == 0:
                raise LTCGSemanticError(f"PE section {name} has an invalid virtual address")
            section = PESection(
                name=name,
                address=self.image_base + rva,
                virtual_size=virtual_size,
                raw_size=raw_size,
                raw_offset=raw_offset,
                characteristics=fields[9],
            )
            sections.append(section)
            if raw_size:
                raw_ranges.append((raw_offset, raw_offset + raw_size, name))
            if virtual_size:
                virtual_ranges.append((section.address, section.end_address, name))
        self._check_nonoverlap(raw_ranges, "raw")
        self._check_nonoverlap(virtual_ranges, "virtual")
        self.sections = tuple(sections)

    @staticmethod
    def _check_nonoverlap(ranges: Sequence[tuple[int, int, str]], label: str) -> None:
        ordered = sorted(ranges)
        for left, right in zip(ordered, ordered[1:]):
            if left[1] > right[0]:
                raise LTCGSemanticError(
                    f"PE sections {left[2]} and {right[2]} have overlapping {label} ranges"
                )

    @classmethod
    def from_path(cls, path: Path) -> "PEImage":
        try:
            return cls(path.read_bytes())
        except OSError as exc:
            raise LTCGSemanticError(f"cannot read linked image {path}: {exc}") from exc

    def section_named(self, name: str) -> PESection:
        matches = [section for section in self.sections if section.name == name]
        if len(matches) != 1:
            raise LTCGSemanticError(
                f"expected one PE section named {name}, found {len(matches)}"
            )
        return matches[0]

    def read(self, address: int, size: int) -> tuple[bytes, PESection, int]:
        if size <= 0:
            raise LTCGSemanticError("PE read size must be positive")
        for section in self.sections:
            relative = address - section.address
            if relative < 0 or relative + size > section.virtual_size:
                continue
            if relative + size > section.raw_size:
                raise LTCGSemanticError(
                    f"range {address:#x}+{size:#x} in {section.name} is not file-backed"
                )
            offset = section.raw_offset + relative
            return self.data[offset:offset + size], section, offset
        raise LTCGSemanticError(f"range {address:#x}+{size:#x} is outside PE sections")


@dataclass(frozen=True)
class MapContribution:
    segment: int
    start: int
    length: int
    name: str
    section_class: str

    @property
    def end(self) -> int:
        return self.start + self.length


@dataclass(frozen=True)
class MapSymbol:
    segment: int
    offset: int
    name: str
    address: int
    visibility: str
    flags: tuple[str, ...]
    origin: str | None
    line_number: int


@dataclass(frozen=True)
class LinkMap:
    image_base: int
    timestamp: int | None
    entry_segment: int
    entry_offset: int
    contributions: tuple[MapContribution, ...]
    symbols: tuple[MapSymbol, ...]


_CONTRIBUTION_RE = re.compile(
    r"^\s*([0-9A-Fa-f]{4}):([0-9A-Fa-f]{8})\s+"
    r"([0-9A-Fa-f]+)H\s+(\S+)\s+(\S+)\s*$"
)
_SYMBOL_RE = re.compile(
    r"^\s*([0-9A-Fa-f]{4}):([0-9A-Fa-f]{8})\s+"
    r"(\S+)\s+([0-9A-Fa-f]{8})(?:\s+(.*?))?\s*$"
)


def parse_map(text: str) -> LinkMap:
    """Parse the section, public/static symbol, base, and entry MAP records."""

    preferred = re.findall(
        r"^\s*Preferred load address is\s+([0-9A-Fa-f]{8})\s*$", text, re.MULTILINE
    )
    if len(preferred) != 1:
        raise LTCGSemanticError("MAP must contain exactly one preferred load address")
    entry = re.findall(
        r"^\s*entry point at\s+([0-9A-Fa-f]{4}):([0-9A-Fa-f]{8})\s*$",
        text,
        re.MULTILINE,
    )
    if len(entry) != 1:
        raise LTCGSemanticError("MAP must contain exactly one entry point")
    timestamps = re.findall(
        r"^\s*Timestamp is\s+([0-9A-Fa-f]{8})\b", text, re.MULTILINE
    )
    if len(timestamps) > 1:
        raise LTCGSemanticError("MAP contains multiple timestamps")

    contributions: list[MapContribution] = []
    symbols: list[MapSymbol] = []
    visibility: str | None = None
    saw_public_header = False
    saw_static_header = False
    for line_number, line in enumerate(text.splitlines(), 1):
        if "Publics by Value" in line:
            if saw_public_header:
                raise LTCGSemanticError("MAP contains multiple public-symbol tables")
            saw_public_header = True
            visibility = "public"
            continue
        if line.strip() == "Static symbols":
            if saw_static_header:
                raise LTCGSemanticError("MAP contains multiple static-symbol tables")
            saw_static_header = True
            visibility = "static"
            continue
        contribution = _CONTRIBUTION_RE.match(line)
        if contribution and visibility is None:
            segment, start, length = (int(contribution.group(index), 16) for index in (1, 2, 3))
            # LINK can emit an empty .edata marker in the .rdata segment.
            # It contributes no bytes and must not invent another PE section.
            if segment == 0 or (length == 0 and contribution.group(5) != "DATA"):
                raise LTCGSemanticError(f"invalid MAP contribution on line {line_number}")
            contributions.append(
                MapContribution(segment, start, length, contribution.group(4), contribution.group(5))
            )
            continue
        if visibility is None:
            continue
        match = _SYMBOL_RE.match(line)
        if not match:
            continue
        segment, offset, address = (int(match.group(index), 16) for index in (1, 2, 4))
        tail = tuple(match.group(5).split()) if match.group(5) else ()
        known_flags = tuple(token for token in tail if token.lower() in {"f", "i"})
        origin_tokens = tuple(token for token in tail if token.lower() not in {"f", "i"})
        symbols.append(
            MapSymbol(
                segment=segment,
                offset=offset,
                name=match.group(3),
                address=address,
                visibility=visibility,
                flags=known_flags,
                origin=" ".join(origin_tokens) or None,
                line_number=line_number,
            )
        )

    if not saw_public_header:
        raise LTCGSemanticError("MAP has no public-symbol table")
    if not contributions:
        raise LTCGSemanticError("MAP has no section contributions")
    if not symbols:
        raise LTCGSemanticError("MAP has no symbols")
    contribution_keys = [(item.segment, item.start, item.end) for item in contributions]
    if len(contribution_keys) != len(set(contribution_keys)):
        raise LTCGSemanticError("MAP contains duplicate section contributions")
    for segment in {item.segment for item in contributions}:
        ranges = sorted(
            (item.start, item.end, item.name)
            for item in contributions
            if item.segment == segment and item.length
        )
        for left, right in zip(ranges, ranges[1:]):
            if left[1] > right[0]:
                raise LTCGSemanticError(
                    f"MAP contributions {left[2]} and {right[2]} overlap in segment {segment:04x}"
                )
    return LinkMap(
        image_base=int(preferred[0], 16),
        timestamp=int(timestamps[0], 16) if timestamps else None,
        entry_segment=int(entry[0][0], 16),
        entry_offset=int(entry[0][1], 16),
        contributions=tuple(contributions),
        symbols=tuple(symbols),
    )


def _canonical_section_name(name: str) -> str:
    return name.split("$", 1)[0][:8]


def _segment_section(link_map: LinkMap, pe: PEImage, segment: int) -> PESection:
    names = {
        _canonical_section_name(item.name)
        for item in link_map.contributions
        if item.segment == segment and item.length
    }
    if not names:
        raise LTCGSemanticError(f"MAP segment {segment:04x} has no section contribution")
    if len(names) != 1:
        raise LTCGSemanticError(
            f"MAP segment {segment:04x} maps to multiple PE section names: {sorted(names)}"
        )
    return pe.section_named(next(iter(names)))


def validate_map_pe(link_map: LinkMap, pe: PEImage) -> None:
    """Cross-check independently parsed MAP coordinates against the PE."""

    if link_map.image_base != pe.image_base:
        raise LTCGSemanticError(
            f"MAP image base {link_map.image_base:#x} differs from PE {pe.image_base:#x}"
        )
    if link_map.timestamp is not None and link_map.timestamp != pe.timestamp:
        raise LTCGSemanticError("MAP timestamp differs from PE timestamp")
    if pe.linker_version != (7, 10):
        raise LTCGSemanticError(
            f"PE linker version is {pe.linker_version[0]}.{pe.linker_version[1]}, expected 7.10"
        )
    for contribution in link_map.contributions:
        section = _segment_section(link_map, pe, contribution.segment)
        if contribution.end > section.virtual_size:
            raise LTCGSemanticError(
                f"MAP contribution {contribution.name} exceeds PE section {section.name}"
            )
    entry_section = _segment_section(link_map, pe, link_map.entry_segment)
    map_entry = entry_section.address + link_map.entry_offset
    if map_entry != pe.entry:
        raise LTCGSemanticError(
            f"MAP entry {map_entry:#x} differs from PE entry {pe.entry:#x}"
        )
    for symbol in link_map.symbols:
        if symbol.segment == 0:
            continue
        section = _segment_section(link_map, pe, symbol.segment)
        expected = section.address + symbol.offset
        if expected != symbol.address:
            raise LTCGSemanticError(
                f"MAP symbol {symbol.name} lists {symbol.address:#x}, expected {expected:#x}"
            )


def _resolve_relative(base: Path, raw: Any, field: str, *, suffix: str | None = None) -> Path:
    value = _require_string(raw, field)
    path = Path(value).expanduser()
    path = (base / path).resolve() if not path.is_absolute() else path.resolve()
    if suffix is not None and path.suffix.lower() != suffix:
        raise LTCGSemanticError(f"{field} must name a {suffix} file")
    if not path.is_file():
        raise LTCGSemanticError(f"{field} does not exist or is not a file: {path}")
    return path


def _normalize_manifest(path: Path) -> dict[str, Any]:
    try:
        raw_bytes = path.read_bytes()
        raw = json.loads(raw_bytes)
    except (OSError, json.JSONDecodeError) as exc:
        raise LTCGSemanticError(f"cannot read manifest {path}: {exc}") from exc
    if not isinstance(raw, Mapping):
        raise LTCGSemanticError("manifest root must be a JSON object")
    if raw.get("schema_version") != 1:
        raise LTCGSemanticError("manifest schema_version must be 1")
    allowed = {
        "schema_version", "name", "sources", "include_dirs", "defines",
        "entry_symbol", "retain_symbols", "functions",
    }
    unknown = sorted(set(raw) - allowed)
    if unknown:
        raise LTCGSemanticError("unknown manifest fields: " + ", ".join(unknown))

    base = path.parent.resolve()
    name = _require_string(raw.get("name"), "name")
    sources_raw = raw.get("sources")
    if not isinstance(sources_raw, list) or not sources_raw:
        raise LTCGSemanticError("sources must be a non-empty array")
    sources = []
    for index, item in enumerate(sources_raw):
        if not isinstance(item, Mapping):
            raise LTCGSemanticError(f"sources[{index}] must be an object")
        if set(item) - {"path", "role"}:
            raise LTCGSemanticError(f"sources[{index}] contains unknown fields")
        role = item.get("role", "cluster")
        if role not in ("cluster", "stub"):
            raise LTCGSemanticError(f"sources[{index}].role must be cluster or stub")
        source_path = _resolve_relative(base, item.get("path"), f"sources[{index}].path", suffix=".cpp")
        sources.append({"path": source_path, "role": role})
    if not any(item["role"] == "cluster" for item in sources):
        raise LTCGSemanticError("at least one source must have role cluster")
    if len({item["path"] for item in sources}) != len(sources):
        raise LTCGSemanticError("sources contains a duplicate path")

    include_dirs_raw = raw.get("include_dirs", [])
    if not isinstance(include_dirs_raw, list):
        raise LTCGSemanticError("include_dirs must be an array")
    include_dirs = []
    for index, item in enumerate(include_dirs_raw):
        value = _require_string(item, f"include_dirs[{index}]")
        include = Path(value).expanduser()
        include = (base / include).resolve() if not include.is_absolute() else include.resolve()
        if not include.is_dir():
            raise LTCGSemanticError(f"include_dirs[{index}] is not a directory: {include}")
        include_dirs.append(include)
    if len(set(include_dirs)) != len(include_dirs):
        raise LTCGSemanticError("include_dirs contains a duplicate path")

    defines_raw = raw.get("defines", [])
    if not isinstance(defines_raw, list):
        raise LTCGSemanticError("defines must be an array")
    defines = []
    for index, item in enumerate(defines_raw):
        define = _require_string(item, f"defines[{index}]")
        if define.startswith(("/", "-")) or any(character.isspace() for character in define):
            raise LTCGSemanticError(f"defines[{index}] must be NAME or NAME=VALUE")
        if not re.fullmatch(r"[A-Za-z_]\w*(?:=.*)?", define):
            raise LTCGSemanticError(f"defines[{index}] has an invalid macro name")
        defines.append(define)
    if len(set(defines)) != len(defines):
        raise LTCGSemanticError("defines contains a duplicate")

    entry_symbol = _require_string(raw.get("entry_symbol"), "entry_symbol")
    retain_raw = raw.get("retain_symbols", [])
    if not isinstance(retain_raw, list):
        raise LTCGSemanticError("retain_symbols must be an array")
    retain_symbols = [_require_string(value, f"retain_symbols[{index}]")
                      for index, value in enumerate(retain_raw)]
    retain_symbols = list(dict.fromkeys([entry_symbol, *retain_symbols]))

    functions_raw = raw.get("functions")
    if not isinstance(functions_raw, list) or not functions_raw:
        raise LTCGSemanticError("functions must be a non-empty array")
    functions = []
    for index, item in enumerate(functions_raw):
        field = f"functions[{index}]"
        if not isinstance(item, Mapping):
            raise LTCGSemanticError(f"{field} must be an object")
        allowed_function = {
            "name", "symbol", "visibility", "size", "expected_hex",
            "expected_sha256", "expected_offset",
        }
        unknown_function = sorted(set(item) - allowed_function)
        if unknown_function:
            raise LTCGSemanticError(
                f"{field} has unknown fields: " + ", ".join(unknown_function)
            )
        semantic_name = _require_string(item.get("name"), f"{field}.name")
        symbol = _require_string(item.get("symbol"), f"{field}.symbol")
        visibility = item.get("visibility", "either")
        if visibility not in ("public", "static", "either"):
            raise LTCGSemanticError(f"{field}.visibility must be public, static, or either")
        size = _parse_int(item.get("size"), f"{field}.size", minimum=1)
        expected_hex = item.get("expected_hex")
        expected_bytes = None
        if expected_hex is not None:
            expected_hex = _require_string(expected_hex, f"{field}.expected_hex")
            try:
                expected_bytes = bytes.fromhex(expected_hex)
            except ValueError as exc:
                raise LTCGSemanticError(f"{field}.expected_hex is not hexadecimal") from exc
            if len(expected_bytes) != size:
                raise LTCGSemanticError(
                    f"{field}.expected_hex has {len(expected_bytes)} bytes, expected {size}"
                )
        expected_hash = item.get("expected_sha256")
        if expected_hash is not None:
            expected_hash = _require_string(expected_hash, f"{field}.expected_sha256").lower()
            if not re.fullmatch(r"[0-9a-f]{64}", expected_hash):
                raise LTCGSemanticError(f"{field}.expected_sha256 must be 64 hexadecimal digits")
            if expected_bytes is not None and _sha256(expected_bytes) != expected_hash:
                raise LTCGSemanticError(f"{field} expected_hex and expected_sha256 disagree")
        expected_offset = item.get("expected_offset")
        if expected_offset is not None:
            expected_offset = _parse_int(expected_offset, f"{field}.expected_offset")
        functions.append({
            "name": semantic_name,
            "symbol": symbol,
            "visibility": visibility,
            "size": size,
            "expected_bytes": expected_bytes,
            "expected_sha256": expected_hash,
            "expected_offset": expected_offset,
        })
    symbols = [item["symbol"] for item in functions]
    if len(set(symbols)) != len(symbols):
        raise LTCGSemanticError("functions contains a duplicate decorated symbol")

    return {
        "path": path,
        "raw_bytes": raw_bytes,
        "name": name,
        "sources": sources,
        "include_dirs": include_dirs,
        "defines": defines,
        "entry_symbol": entry_symbol,
        "retain_symbols": retain_symbols,
        "functions": functions,
    }


def extract_functions(
    specs: Sequence[Mapping[str, Any]], link_map: LinkMap, pe: PEImage
) -> list[dict[str, Any]]:
    """Resolve requested MAP symbols and return strictly bounded PE bytes."""

    results = []
    for spec in specs:
        matches = [symbol for symbol in link_map.symbols if symbol.name == spec["symbol"]]
        if spec["visibility"] != "either":
            matches = [symbol for symbol in matches if symbol.visibility == spec["visibility"]]
        if len(matches) != 1:
            locations = ", ".join(
                f"{item.visibility}@{item.segment:04x}:{item.offset:08x}"
                for item in matches
            ) or "none"
            raise LTCGSemanticError(
                f"function {spec['name']} must resolve to one exact MAP symbol; found {locations}"
            )
        symbol = matches[0]
        if symbol.segment == 0 or "f" not in {flag.lower() for flag in symbol.flags}:
            raise LTCGSemanticError(f"MAP symbol {symbol.name} is not marked as a function")
        size = int(spec["size"])
        end = symbol.offset + size
        code_ranges = [
            item for item in link_map.contributions
            if item.segment == symbol.segment
            and item.section_class.upper() == "CODE"
            and item.start <= symbol.offset
            and end <= item.end
        ]
        if not code_ranges:
            raise LTCGSemanticError(
                f"function {spec['name']} extent is outside a MAP CODE contribution"
            )
        interior = sorted(
            [
                item
                for item in link_map.symbols
                if item.segment == symbol.segment and symbol.offset < item.offset < end
            ],
            key=lambda item: item.offset,
        )
        if interior:
            raise LTCGSemanticError(
                f"function {spec['name']} extent crosses MAP symbol {interior[0].name} "
                f"at +{interior[0].offset - symbol.offset:#x}"
            )
        section = _segment_section(link_map, pe, symbol.segment)
        if not (section.characteristics & 0x20 and section.characteristics & 0x20000000):
            raise LTCGSemanticError(f"function {spec['name']} is not in executable PE code")
        data, actual_section, file_offset = pe.read(symbol.address, size)
        if actual_section != section:
            raise LTCGSemanticError(f"function {spec['name']} MAP/PE section selection differs")
        if spec.get("expected_offset") is not None and symbol.offset != spec["expected_offset"]:
            raise LTCGSemanticError(
                f"function {spec['name']} linked at offset {symbol.offset:#x}, "
                f"expected {spec['expected_offset']:#x}"
            )
        expected_bytes = spec.get("expected_bytes")
        if expected_bytes is not None and data != expected_bytes:
            differences = [index for index, pair in enumerate(zip(data, expected_bytes)) if pair[0] != pair[1]]
            preview = ", ".join(f"+{offset:#x}" for offset in differences[:16])
            raise LTCGSemanticError(
                f"function {spec['name']} differs from expected bytes at {preview}"
            )
        digest = _sha256(data)
        expected_hash = spec.get("expected_sha256")
        if expected_hash is not None and digest != expected_hash:
            raise LTCGSemanticError(
                f"function {spec['name']} SHA-256 {digest} differs from {expected_hash}"
            )
        results.append({
            "name": spec["name"],
            "symbol": symbol.name,
            "visibility": symbol.visibility,
            "map_segment": f"{symbol.segment:04X}",
            "map_offset": f"0x{symbol.offset:08X}",
            "address": f"0x{symbol.address:08X}",
            "rva": f"0x{symbol.address - pe.image_base:08X}",
            "section": section.name,
            "file_offset": f"0x{file_offset:X}",
            "size": size,
            "bytes_hex": data.hex(" "),
            "sha256": digest,
            "map_origin": symbol.origin,
            "expected_bytes_checked": expected_bytes is not None,
            "expected_sha256_checked": expected_hash is not None,
        })
    return results


def _which(command: str) -> str:
    found = shutil.which(command)
    if found is None:
        raise LTCGSemanticError(f"required host command is not available: {command}")
    return found


def _run_logged(
    command: Sequence[str],
    env: Mapping[str, str],
    cwd: Path,
    log: Path,
    timeout: int,
    *,
    check: bool = True,
) -> subprocess.CompletedProcess[str]:
    try:
        result = subprocess.run(
            list(command), cwd=cwd, env=dict(env), capture_output=True, text=True, timeout=timeout
        )
    except (OSError, subprocess.TimeoutExpired) as exc:
        log.write_text(str(exc) + "\n")
        raise LTCGSemanticError(f"command could not complete; see {log}: {exc}") from exc
    log.write_text(result.stdout + result.stderr)
    if check and result.returncode:
        raise LTCGSemanticError(
            f"command failed with exit code {result.returncode}; see {log}"
        )
    return result


def _windows_path(path: Path, winepath: str, env: Mapping[str, str], cwd: Path) -> str:
    try:
        result = subprocess.run(
            [winepath, "-w", str(path)], cwd=cwd, env=dict(env), capture_output=True,
            text=True, timeout=30
        )
    except (OSError, subprocess.TimeoutExpired) as exc:
        raise LTCGSemanticError(f"winepath failed for {path}: {exc}") from exc
    if result.returncode or not result.stdout.strip():
        raise LTCGSemanticError(f"winepath failed for {path}: {result.stderr.strip()}")
    return result.stdout.strip()


def _verify_toolchain(
    toolkit: Path, wine: str, env: Mapping[str, str], output: Path
) -> tuple[Path, Path, dict[str, str]]:
    compiler = toolkit / "bin/cl.exe"
    linker = toolkit / "bin/link.exe"
    for path in (compiler, linker, toolkit / "bin/c1xx.dll", toolkit / "bin/c2.dll"):
        if not path.is_file():
            raise LTCGSemanticError(f"MSVC toolkit file is missing: {path}")
    compiler_probe = _run_logged(
        [wine, str(compiler)], env, output, output / "compiler-version.log", 60, check=False
    )
    compiler_banner = compiler_probe.stdout + compiler_probe.stderr
    if f"Version {COMPILER_VERSION}" not in compiler_banner:
        raise LTCGSemanticError(
            f"cl.exe version is not the required {COMPILER_VERSION}; see compiler-version.log"
        )
    linker_probe = _run_logged(
        [wine, str(linker), "/?"], env, output, output / "linker-version.log", 60,
        check=False,
    )
    linker_banner = linker_probe.stdout + linker_probe.stderr
    if f"Version {LINKER_VERSION}" not in linker_banner:
        raise LTCGSemanticError(
            f"link.exe version is not the required {LINKER_VERSION}; see linker-version.log"
        )
    hashes = {
        str(path.relative_to(toolkit)): _sha256(path.read_bytes())
        for path in (compiler, linker, toolkit / "bin/c1.dll", toolkit / "bin/c1xx.dll", toolkit / "bin/c2.dll")
        if path.is_file()
    }
    return compiler, linker, hashes


def run_pipeline(
    manifest_path: Path,
    output: Path,
    toolkit: Path = DEFAULT_TOOLKIT,
    *,
    wine_command: str = "wine",
    winepath_command: str = "winepath",
) -> dict[str, Any]:
    """Compile, LTCG-link, validate, extract, and write ``report.json``."""

    manifest_path = manifest_path.resolve()
    output = output.resolve()
    toolkit = toolkit.expanduser().resolve()
    manifest = _normalize_manifest(manifest_path)
    wine = _which(wine_command)
    winepath = _which(winepath_command)
    output.mkdir(parents=True, exist_ok=True)
    stale = [
        "report.json", "cluster.exe", "cluster.map", "compile-commands.json",
        "link.log", "compiler-version.log", "linker-version.log",
    ]
    for name in stale:
        (output / name).unlink(missing_ok=True)

    env = {**os.environ, "WINEDEBUG": "-all"}
    include = _windows_path(toolkit / "include", winepath, env, output)
    library = _windows_path(toolkit / "lib", winepath, env, output)
    env["INCLUDE"] = include
    env["LIB"] = library
    compiler, linker, tool_hashes = _verify_toolchain(toolkit, wine, env, output)

    include_flags = [
        "/I" + _windows_path(path, winepath, env, output)
        for path in manifest["include_dirs"]
    ]
    define_flags = ["/D" + value for value in manifest["defines"]]
    objects: list[Path] = []
    compile_records = []
    for index, source in enumerate(manifest["sources"]):
        role = source["role"]
        obj = output / f"{role}-{index:04d}.obj"
        log = output / f"compile-{index:04d}.log"
        obj.unlink(missing_ok=True)
        flags = CLUSTER_FLAGS if role == "cluster" else STUB_FLAGS
        command = [
            wine,
            str(compiler),
            *flags,
            *include_flags,
            *define_flags,
            "/Fo" + _windows_path(obj, winepath, env, output),
            _windows_path(source["path"], winepath, env, output),
        ]
        _run_logged(command, env, output, log, 180)
        if not obj.is_file() or not obj.stat().st_size:
            raise LTCGSemanticError(f"compiler reported success without creating {obj}")
        objects.append(obj)
        compile_records.append({
            "source": str(source["path"]),
            "source_sha256": _sha256(source["path"].read_bytes()),
            "role": role,
            "object": obj.name,
            "object_sha256": _sha256(obj.read_bytes()),
            "flags": list(flags),
            "command": command,
        })
    (output / "compile-commands.json").write_text(json.dumps(compile_records, indent=2) + "\n")

    executable = output / "cluster.exe"
    map_path = output / "cluster.map"
    command = [
        wine,
        str(linker),
        "/nologo",
        "/LTCG",
        "/MACHINE:X86",
        "/BASE:0x400000",
        "/FILEALIGN:512",
        "/SUBSYSTEM:WINDOWS",
        "/ENTRY:" + manifest["entry_symbol"],
        "/FIXED",
        "/INCREMENTAL:NO",
        "/OPT:REF",
        "/OPT:NOICF",
        "/NODEFAULTLIB",
        "/OUT:" + _windows_path(executable, winepath, env, output),
        "/MAP:" + _windows_path(map_path, winepath, env, output),
        *["/INCLUDE:" + symbol for symbol in manifest["retain_symbols"]],
        *[_windows_path(obj, winepath, env, output) for obj in objects],
    ]
    _run_logged(command, env, output, output / "link.log", 300)
    if not executable.is_file() or not map_path.is_file():
        raise LTCGSemanticError("linker reported success without producing the PE and MAP")

    try:
        map_text = map_path.read_text(encoding="utf-8")
    except (OSError, UnicodeError) as exc:
        raise LTCGSemanticError(f"cannot read linker MAP {map_path}: {exc}") from exc
    link_map = parse_map(map_text)
    pe = PEImage.from_path(executable)
    validate_map_pe(link_map, pe)
    entry_matches = [
        symbol for symbol in link_map.symbols
        if symbol.name == manifest["entry_symbol"] and symbol.address == pe.entry
    ]
    if len(entry_matches) != 1:
        raise LTCGSemanticError("entry_symbol does not uniquely identify the linked PE entry")
    functions = extract_functions(manifest["functions"], link_map, pe)

    report = {
        "schema_version": 1,
        "purpose": "MSVC 13.10.6030 /O2 /GL plus link.exe 7.10.6030 /LTCG semantic cluster",
        "name": manifest["name"],
        "manifest": str(manifest_path),
        "manifest_sha256": _sha256(manifest["raw_bytes"]),
        "toolkit": str(toolkit),
        "tool_sha256": tool_hashes,
        "compile_profile": {
            "cluster": list(CLUSTER_FLAGS),
            "stub": list(STUB_FLAGS),
            "stub_contract": "Reviewable external C++ definitions compiled without /GL",
        },
        "compiled_sources": compile_records,
        "link_command": command,
        "entry_symbol": manifest["entry_symbol"],
        "entry_address": f"0x{pe.entry:08X}",
        "image_base": f"0x{pe.image_base:08X}",
        "pe_sha256": _sha256(pe.data),
        "map_sha256": _sha256(map_path.read_bytes()),
        "sections": [
            {
                "name": section.name,
                "address": f"0x{section.address:08X}",
                "virtual_size": section.virtual_size,
                "raw_size": section.raw_size,
                "raw_offset": f"0x{section.raw_offset:X}",
                "characteristics": f"0x{section.characteristics:08X}",
            }
            for section in pe.sections
        ],
        "functions": functions,
        "validation": {
            "map_pe_coordinates": True,
            "entry_symbol": True,
            "explicit_function_extents": True,
            "unresolved_externals": "linker hard error",
            "raw_code_emission": False,
        },
    }
    temporary = output / "report.json.tmp"
    temporary.write_text(json.dumps(report, indent=2) + "\n")
    temporary.replace(output / "report.json")
    return report


def main(argv: Sequence[str] | None = None) -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("manifest", type=Path, help="schema-1 semantic cluster manifest")
    parser.add_argument("--output", type=Path, required=True, help="isolated build directory")
    parser.add_argument("--toolkit", type=Path, default=DEFAULT_TOOLKIT)
    args = parser.parse_args(argv)
    try:
        report = run_pipeline(args.manifest, args.output, args.toolkit)
    except LTCGSemanticError as exc:
        parser.error(str(exc))
    print(
        f"Extracted {len(report['functions'])} LTCG function(s) from "
        f"{report['name']}: {args.output.resolve() / 'report.json'}"
    )
    return 0


if __name__ == "__main__":
    sys.exit(main())
