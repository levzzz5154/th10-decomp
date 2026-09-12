"""Strict MSVC native PE/MAP validation and compiler invocation helpers."""

from __future__ import annotations

from dataclasses import dataclass
import hashlib
from pathlib import Path
import re
import struct
import subprocess
from typing import Any, Mapping, Sequence


COMPILER_VERSION = "13.10.6030"
LINKER_VERSION = "7.10.6030"

class LTCGSemanticError(ValueError):
    """The manifest or a compiler/linker artifact failed a strict check."""


def _sha256(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


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
        self.export_rva, self.export_size = (0, 0)
        if optional_size >= 104 and struct.unpack_from('<I', data, optional + 92)[0]:
            self.export_rva, self.export_size = struct.unpack_from('<II', data, optional + 96)

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
            # LINK can emit empty canonical section markers (for example
            # ``.text CODE`` before non-empty ``.text$...`` contributions, or
            # ``.edata DATA``).  They contribute no bytes; the non-empty
            # contributions below still determine the backing PE section.
            if segment == 0:
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
    contributions = [item for item in link_map.contributions
                     if item.segment == segment and item.length]
    names = {
        _canonical_section_name(item.name)
        for item in contributions
    }
    # LINK 7.10 describes its synthesized export directory as .edata in the
    # MAP even when the PE stores it in .rdata. Prove that mapping from the
    # PE export data directory; do not guess a section from its ordinal.
    if '.edata' in names and not any(section.name == '.edata' for section in pe.sections):
        if not pe.export_rva or not pe.export_size:
            raise LTCGSemanticError('MAP exports have no PE export data directory')
        _, section, _ = pe.read(pe.image_base + pe.export_rva, pe.export_size)
        exports = [item for item in contributions if _canonical_section_name(item.name) == '.edata']
        if (len(exports) != 1 or section.address + exports[0].start != pe.image_base + pe.export_rva
                or exports[0].length != pe.export_size):
            raise LTCGSemanticError('MAP exports disagree with the PE export data directory')
        names = (names - {'.edata'}) | {section.name}
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
