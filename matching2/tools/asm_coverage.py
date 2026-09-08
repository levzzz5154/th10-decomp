#!/usr/bin/env python3
"""Audit the available assembly listings against the supported retail image.

This is an evidence inventory for the assembly baseline.  It does not turn an
unclassified byte into padding merely because its value looks like padding.
Every byte in the retail ``.text`` raw section receives a range-map entry;
function-body coverage is reported separately from the byte classification.

The two Ghidra exports are deliberately kept as separate evidence sources.
The augmented export adds boundaries, but it is not silently treated as a
replacement for the saved export.  The retail executable is authenticated by
the hashes in ``decompiled/reference_bytes_validation.json`` before any
listing comparison is accepted.
"""

from __future__ import annotations

import argparse
import collections
import csv
import hashlib
import json
import os
import re
import struct
import sys
from dataclasses import dataclass
from pathlib import Path
from typing import Iterable, Iterator, Mapping, Sequence


ROOT = Path(__file__).resolve().parents[2]
REFERENCE_VALIDATION = ROOT / "decompiled" / "reference_bytes_validation.json"
DEFAULT_GAME_DIR = Path.home() / "Games" / "TH10 - Mountain of Faith"
DEFAULT_RETAIL = DEFAULT_GAME_DIR / "th10.exe"
DEFAULT_FULL = ROOT / "decompiled" / "ghidra_full"
DEFAULT_AUGMENTED = ROOT / "decompiled" / "ghidra_augmented"
DEFAULT_OUTPUT = ROOT / "matching2" / "build" / "asm-baseline"

ADDR_RE = re.compile(r"^([0-9A-Fa-f]{8})\t([^\t]+)(?:\t(.*))?$")
ASM_RE = re.compile(r"^([0-9A-Fa-f]{8})\t([^\t]+)\t(.*)$")
RANGE_RE = re.compile(r"^([0-9A-Fa-f]+)-([0-9A-Fa-f]+)$")
HEX_RE = re.compile(r"^[0-9A-Fa-f]*$")


class AuditError(RuntimeError):
    """An input is missing, unauthenticated, or internally inconsistent."""


@dataclass(frozen=True)
class ListingRow:
    corpus: str
    line: int
    address: int
    encoded: str
    data: bytes
    kind: str
    type_name: str
    truncated: bool
    logical_end: int | None = None


@dataclass(frozen=True)
class InstructionClaim:
    corpus: str
    function: str
    line: int
    address: int
    value: int


@dataclass(frozen=True)
class FunctionRecord:
    corpus: str
    address: str
    name: str
    ranges: tuple[tuple[int, int], ...]
    asm_path: Path


def sha256(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


def hex_address(value: int) -> str:
    return f"0x{value:08X}"


def read_tsv(path: Path) -> list[dict[str, str]]:
    try:
        with path.open(encoding="utf-8") as handle:
            return list(csv.DictReader(handle, delimiter="\t"))
    except OSError as exc:
        raise AuditError(f"cannot read {path}: {exc}") from exc


def parse_memory_hex(path: Path) -> dict[int, int]:
    """Read Ghidra's sparse memory export and reject address collisions."""

    memory: dict[int, int] = {}
    try:
        lines = path.read_text(encoding="utf-8").splitlines()
    except OSError as exc:
        raise AuditError(f"cannot read {path}: {exc}") from exc
    for line_number, line in enumerate(lines, 1):
        if not line.strip():
            continue
        fields = line.split()
        if len(fields) != 2 or not re.fullmatch(r"[0-9A-Fa-f]+", fields[0]):
            raise AuditError(f"malformed memory.hex line {path}:{line_number}")
        try:
            payload = bytes.fromhex(fields[1])
        except ValueError as exc:
            raise AuditError(f"invalid memory.hex bytes {path}:{line_number}") from exc
        start = int(fields[0], 16)
        for offset, value in enumerate(payload):
            address = start + offset
            if address in memory:
                raise AuditError(f"overlapping memory export at {hex_address(address)} ({path})")
            memory[address] = value
    return memory


def parse_pe_text(executable: Path, expected: Mapping[str, object]) -> dict[str, object]:
    """Authenticate the executable and return its raw ``.text`` bytes."""

    try:
        image = executable.read_bytes()
    except OSError as exc:
        raise AuditError(f"cannot read retail executable {executable}: {exc}") from exc
    actual_exe_hash = sha256(image)
    expected_exe_hash = str(expected["executable_sha256"])
    if actual_exe_hash != expected_exe_hash:
        raise AuditError(
            f"retail executable SHA-256 mismatch: expected {expected_exe_hash}, got {actual_exe_hash}"
        )
    if len(image) < 0x40:
        raise AuditError("retail executable is too small to be a PE image")
    nt_offset = struct.unpack_from("<I", image, 0x3C)[0]
    if nt_offset + 24 > len(image) or image[nt_offset : nt_offset + 4] != b"PE\0\0":
        raise AuditError("retail executable has no valid PE signature")
    number_of_sections = struct.unpack_from("<H", image, nt_offset + 6)[0]
    optional_size = struct.unpack_from("<H", image, nt_offset + 20)[0]
    optional = nt_offset + 24
    if optional + optional_size > len(image) or optional_size < 32:
        raise AuditError("retail executable has a truncated PE optional header")
    magic = struct.unpack_from("<H", image, optional)[0]
    if magic != 0x10B:
        raise AuditError(f"retail executable is not PE32 (optional-header magic {magic:#x})")
    image_base = struct.unpack_from("<I", image, optional + 28)[0]
    section_table = optional + optional_size
    text: tuple[int, int, int, int] | None = None
    sections: list[dict[str, int | str]] = []
    for index in range(number_of_sections):
        offset = section_table + index * 40
        if offset + 40 > len(image):
            raise AuditError("retail executable has a truncated section table")
        name = image[offset : offset + 8].rstrip(b"\0").decode("ascii", errors="replace")
        virtual_size, virtual_address, raw_size, raw_offset = struct.unpack_from("<IIII", image, offset + 8)
        sections.append(
            {
                "name": name,
                "virtual_size": virtual_size,
                "virtual_address": virtual_address,
                "raw_size": raw_size,
                "raw_offset": raw_offset,
            }
        )
        if name == ".text":
            text = (virtual_address, virtual_size, raw_size, raw_offset)
    if text is None:
        raise AuditError("retail executable has no .text section")
    virtual_address, virtual_size, raw_size, raw_offset = text
    if raw_offset + raw_size > len(image):
        raise AuditError("retail executable .text raw bytes are truncated")
    raw = image[raw_offset : raw_offset + raw_size]
    expected_size = int(expected["text_section_bytes"])
    expected_text_hash = str(expected["text_section_sha256"])
    if len(raw) != expected_size or sha256(raw) != expected_text_hash:
        raise AuditError(
            "retail .text hash mismatch: expected "
            f"{expected_text_hash}/{expected_size}, got {sha256(raw)}/{len(raw)}"
        )
    return {
        "bytes": raw,
        "executable_sha256": actual_exe_hash,
        "text_sha256": sha256(raw),
        "text_start": image_base + virtual_address,
        "text_virtual_size": virtual_size,
        "text_raw_size": raw_size,
        "text_file_offset": raw_offset,
        "sections": sections,
    }


def parse_memory_block(base: Path) -> tuple[int, int]:
    rows = read_tsv(base / "memory_blocks.tsv")
    for row in rows:
        if row.get("name") == ".text":
            try:
                start = int(row["start"], 16)
                end = int(row["end"], 16)
                size = int(row["size"])
            except (KeyError, ValueError) as exc:
                raise AuditError(f"malformed .text row in {base / 'memory_blocks.tsv'}") from exc
            if end - start + 1 != size:
                raise AuditError(f".text block size mismatch in {base / 'memory_blocks.tsv'}")
            return start, end
    raise AuditError(f"no .text row in {base / 'memory_blocks.tsv'}")


def _listing_kind(type_name: str) -> str:
    token = type_name.strip().split(maxsplit=1)[0] if type_name.strip() else ""
    if token == "??":
        return "undefined"
    # Ghidra emits data types in lower case (addr/db/ds/float/...), while
    # instruction mnemonics are upper case (including forms such as JZ and
    # STOSD.REP).  Keep unknown forms explicit rather than guessing from bytes.
    if token and token[0].islower():
        return "defined_data"
    if token:
        return "instruction"
    return "listing_unknown"


def parse_listing(path: Path, corpus: str, text_start: int, text_end: int) -> tuple[list[ListingRow], list[dict[str, object]]]:
    """Parse listing.asm, retaining truncated rows as explicit ambiguity."""

    rows: list[ListingRow] = []
    try:
        lines = path.read_text(encoding="utf-8").splitlines()
    except OSError as exc:
        raise AuditError(f"cannot read {path}: {exc}") from exc
    raw_rows: list[tuple[int, int, str, str, bytes, bool, str]] = []
    for line_number, line in enumerate(lines, 1):
        if not line or line.startswith(";"):
            continue
        match = ADDR_RE.match(line)
        if not match:
            continue
        address = int(match.group(1), 16)
        encoded = match.group(2).strip()
        truncated = encoded.endswith("...")
        prefix = encoded[:-3] if truncated else encoded
        if not HEX_RE.fullmatch(prefix) or len(prefix) % 2:
            raise AuditError(f"malformed listing bytes {path}:{line_number}")
        data = bytes.fromhex(prefix)
        type_name = (match.group(3) or "").strip()
        raw_rows.append((line_number, address, encoded, type_name, data, truncated, _listing_kind(type_name)))
    # The export is address ordered. Sorting here also makes next-row bounds
    # deterministic if a tool version writes a small block out of order.
    raw_rows.sort(key=lambda item: (item[1], item[0]))
    truncated_rows: list[dict[str, object]] = []
    for index, (line_number, address, encoded, type_name, data, truncated, kind) in enumerate(raw_rows):
        next_address = raw_rows[index + 1][1] if index + 1 < len(raw_rows) else None
        logical_end: int | None = None
        if truncated:
            if next_address is not None and next_address > address:
                logical_end = next_address - 1
            elif text_start <= address <= text_end:
                logical_end = text_end
            truncated_rows.append(
                {
                    "line": line_number,
                    "address": hex_address(address),
                    "known_bytes": len(data),
                    "logical_end": hex_address(logical_end) if logical_end is not None else None,
                    "type": type_name,
                }
            )
        rows.append(
            ListingRow(
                corpus=corpus,
                line=line_number,
                address=address,
                encoded=encoded,
                data=data,
                kind=kind,
                type_name=type_name,
                truncated=truncated,
                logical_end=logical_end,
            )
        )
    return rows, truncated_rows


def parse_ranges(raw: str) -> tuple[tuple[int, int], ...]:
    if not raw:
        return ()
    result: list[tuple[int, int]] = []
    for value in raw.split(","):
        match = RANGE_RE.fullmatch(value.strip())
        if not match:
            raise AuditError(f"malformed function range {raw!r}")
        start, end = int(match.group(1), 16), int(match.group(2), 16)
        if end < start:
            raise AuditError(f"reversed function range {value!r}")
        result.append((start, end))
    return tuple(result)


def _iter_asm_rows(path: Path) -> Iterator[tuple[int, str, bytes, int, str]]:
    try:
        lines = path.read_text(encoding="utf-8").splitlines()
    except OSError as exc:
        raise AuditError(f"cannot read {path}: {exc}") from exc
    for line_number, line in enumerate(lines, 1):
        if not line or line.startswith(";"):
            continue
        match = ASM_RE.match(line)
        if not match:
            continue
        encoded = match.group(2).strip()
        truncated = encoded.endswith("...")
        prefix = encoded[:-3] if truncated else encoded
        if not HEX_RE.fullmatch(prefix) or len(prefix) % 2:
            raise AuditError(f"malformed assembly bytes {path}:{line_number}")
        yield int(match.group(1), 16), encoded, bytes.fromhex(prefix), line_number, match.group(3)


def parse_functions(
    base: Path,
    corpus: str,
    text_start: int,
    text_end: int,
    retail: bytes,
    retail_start: int,
) -> tuple[list[FunctionRecord], dict[int, list[InstructionClaim]], list[dict[str, object]]]:
    rows = read_tsv(base / "index.tsv")
    claims: dict[int, list[InstructionClaim]] = collections.defaultdict(list)
    records: list[FunctionRecord] = []
    issues: list[dict[str, object]] = []
    for row in rows:
        try:
            address = row["address"].upper()
            ranges = parse_ranges(row["body_ranges"])
            expected_body_bytes = int(row["body_bytes"])
            if sum(end - start + 1 for start, end in ranges) != expected_body_bytes:
                raise AuditError(f"{base}/index.tsv:{address}: body_bytes mismatch")
            asm_file = row["asm_file"]
            asm_path = base / asm_file
            name = row.get("name", "")
        except (KeyError, ValueError) as exc:
            raise AuditError(f"malformed function row in {base / 'index.tsv'}") from exc
        if not asm_path.is_file():
            raise AuditError(f"missing assembly listing {asm_path}")
        record = FunctionRecord(corpus, address, name, ranges, asm_path)
        records.append(record)
        for start, end in ranges:
            if start < text_start or end > text_end:
                issues.append(
                    {
                        "type": "function_body_outside_text",
                        "corpus": corpus,
                        "function": address,
                        "start": hex_address(start),
                        "end": hex_address(end),
                    }
                )
        range_set = ranges
        for instruction_address, encoded, data, line_number, _ in _iter_asm_rows(asm_path):
            if not any(start <= instruction_address <= end for start, end in range_set):
                issues.append(
                    {
                        "type": "instruction_outside_body",
                        "corpus": corpus,
                        "function": address,
                        "line": line_number,
                        "address": hex_address(instruction_address),
                    }
                )
            if encoded.endswith("..."):
                issues.append(
                    {
                        "type": "truncated_instruction_listing",
                        "corpus": corpus,
                        "function": address,
                        "line": line_number,
                        "address": hex_address(instruction_address),
                        "known_bytes": len(data),
                    }
                )
            for offset, value in enumerate(data):
                current = instruction_address + offset
                claim = InstructionClaim(corpus, address, line_number, current, value)
                claims[current].append(claim)
                if text_start <= current <= text_end:
                    retail_value = retail[current - retail_start]
                    if value != retail_value:
                        issues.append(
                            {
                                "type": "instruction_bytes_mismatch",
                                "corpus": corpus,
                                "function": address,
                                "line": line_number,
                                "address": hex_address(current),
                                "listing": f"{value:02X}",
                                "retail": f"{retail_value:02X}",
                            }
                        )
                else:
                    issues.append(
                        {
                            "type": "instruction_outside_text",
                            "corpus": corpus,
                            "function": address,
                            "line": line_number,
                            "address": hex_address(current),
                        }
                    )
    return records, claims, issues


def _candidate_pattern(data: Sequence[int]) -> str | None:
    """Return a cautious candidate label, never a padding assertion."""

    if len(data) < 2 or not data or len(set(data)) != 1:
        return None
    value = data[0]
    return {0x00: "repeated_00", 0x90: "repeated_90", 0xCC: "repeated_CC", 0xF4: "repeated_F4"}.get(value)


def _mask_ranges(mask: bytearray, start: int) -> list[dict[str, object]]:
    ranges: list[dict[str, object]] = []
    index = 0
    while index < len(mask):
        if not mask[index]:
            index += 1
            continue
        end = index + 1
        while end < len(mask) and mask[end]:
            end += 1
        ranges.append({"start": hex_address(start + index), "end": hex_address(start + end - 1), "bytes": end - index})
        index = end
    return ranges


def _text_bytes(memory: Mapping[int, int], start: int, end: int) -> bytes | None:
    if any(address not in memory for address in range(start, end + 1)):
        return None
    return bytes(memory[address] for address in range(start, end + 1))


def audit(
    retail_executable: Path = DEFAULT_RETAIL,
    full_base: Path = DEFAULT_FULL,
    augmented_base: Path = DEFAULT_AUGMENTED,
) -> dict[str, object]:
    """Return an authenticated, complete range map without writing files."""

    try:
        expected = json.loads(REFERENCE_VALIDATION.read_text(encoding="utf-8"))
    except (OSError, json.JSONDecodeError) as exc:
        raise AuditError(f"cannot read {REFERENCE_VALIDATION}: {exc}") from exc
    retail_info = parse_pe_text(retail_executable, expected)
    retail = retail_info["bytes"]
    retail_start = int(retail_info["text_start"])
    retail_end = retail_start + len(retail) - 1
    if retail_start != 0x00401000:
        raise AuditError(f"unexpected retail .text start {hex_address(retail_start)}")

    corpus_bases = {"full": full_base, "augmented": augmented_base}
    corpus_info: dict[str, dict[str, object]] = {}
    all_function_claims: dict[int, list[InstructionClaim]] = collections.defaultdict(list)
    function_records: dict[str, list[FunctionRecord]] = {}
    validation_issues: list[dict[str, object]] = []
    listing_claims: dict[int, list[ListingRow]] = collections.defaultdict(list)
    listing_issues: list[dict[str, object]] = []

    for corpus, base in corpus_bases.items():
        block_start, block_end = parse_memory_block(base)
        if block_start != retail_start or block_end != retail_end:
            raise AuditError(
                f"{corpus} .text block {hex_address(block_start)}-{hex_address(block_end)} "
                f"does not match authenticated retail {hex_address(retail_start)}-{hex_address(retail_end)}"
            )
        memory = parse_memory_hex(base / "memory.hex")
        exported_text = _text_bytes(memory, retail_start, retail_end)
        if exported_text is None:
            raise AuditError(f"{corpus} memory.hex does not cover the complete .text range")
        if exported_text != retail:
            mismatches = [
                hex_address(retail_start + index)
                for index, (actual, expected_byte) in enumerate(zip(exported_text, retail))
                if actual != expected_byte
            ]
            raise AuditError(f"{corpus} memory.hex differs from retail at {len(mismatches)} bytes (first {mismatches[:3]})")
        listing_rows, truncated_rows = parse_listing(base / "listing.asm", corpus, retail_start, retail_end)
        for row in listing_rows:
            if row.address > retail_end or row.address + len(row.data) - 1 < retail_start:
                continue
            for offset, value in enumerate(row.data):
                current = row.address + offset
                if not retail_start <= current <= retail_end:
                    continue
                if value != retail[current - retail_start]:
                    listing_issues.append(
                        {
                            "type": "listing_bytes_mismatch",
                            "corpus": corpus,
                            "line": row.line,
                            "address": hex_address(current),
                            "listing": f"{value:02X}",
                            "retail": f"{retail[current - retail_start]:02X}",
                        }
                    )
            # Keep the row as evidence for known bytes.  A truncated row's
            # unknown tail is represented separately below and is never
            # populated from the retail image as if it had been listed.
            for offset in range(len(row.data)):
                current = row.address + offset
                if retail_start <= current <= retail_end:
                    listing_claims[current].append(row)
            if row.truncated and row.logical_end is not None:
                unknown_start = max(row.address + len(row.data), retail_start)
                unknown_end = min(row.logical_end, retail_end)
                for current in range(unknown_start, unknown_end + 1):
                    listing_claims[current].append(row)
        function_records[corpus], claims, issues = parse_functions(
            base, corpus, retail_start, retail_end, retail, retail_start
        )
        for address, values in claims.items():
            all_function_claims[address].extend(values)
        validation_issues.extend(issues)
        corpus_info[corpus] = {
            "path": str(base.relative_to(ROOT)),
            "memory_sha256": sha256((base / "memory.hex").read_bytes()),
            "listing_sha256": sha256((base / "listing.asm").read_bytes()),
            "function_count": len(function_records[corpus]),
            "truncated_listing_rows": truncated_rows,
        }

    # A compact per-byte state is used only during auditing.  The output is a
    # coalesced range map, so consumers do not need to process 412,672 rows.
    size = len(retail)
    full_mask = bytearray(size)
    augmented_mask = bytearray(size)
    body_counts = bytearray(size)
    body_counts_by_corpus = {corpus: bytearray(size) for corpus in function_records}
    body_masks: dict[str, bytearray] = {}
    instruction_masks: dict[str, bytearray] = {}
    for corpus, records in function_records.items():
        body_mask = bytearray(size)
        instruction_mask = bytearray(size)
        for record in records:
            for start, end in record.ranges:
                lo, hi = max(start, retail_start), min(end, retail_end)
                for address in range(lo, hi + 1):
                    offset = address - retail_start
                    body_mask[offset] = 1
                    if body_counts[offset] < 255:
                        body_counts[offset] += 1
                    if body_counts_by_corpus[corpus][offset] < 255:
                        body_counts_by_corpus[corpus][offset] += 1
        body_masks[corpus] = body_mask
        instruction_masks[corpus] = instruction_mask
        if corpus == "full":
            full_mask = body_mask
        else:
            augmented_mask = body_mask
    for address, claims in all_function_claims.items():
        if retail_start <= address <= retail_end:
            # An instruction claim can have multiple bytes; mark each byte
            # from the aggregate claim map below.
            for claim in claims:
                instruction_masks[claim.corpus][address - retail_start] = 1

    # Broad listing kinds and source corpus sets are retained as flags.  This
    # makes listing disagreements visible without making one corpus disappear.
    attrs: list[dict[str, object]] = []
    for offset in range(size):
        address = retail_start + offset
        rows = listing_claims.get(address, [])
        function_claim = all_function_claims.get(address, [])
        listing_sources = sorted({row.corpus for row in rows})
        listing_kinds = sorted({row.kind for row in rows})
        truncated = any(row.truncated and row.address + len(row.data) <= address <= (row.logical_end or address) for row in rows)
        function_keys = sorted({claim.function for claim in function_claim})
        function_values = sorted({claim.value for claim in function_claim})
        flags: list[str] = []
        if len(listing_kinds) > 1:
            flags.append("listing_kind_disagreement")
        if len(function_values) > 1:
            flags.append("instruction_byte_disagreement")
        if len(function_keys) > 1:
            flags.append("function_overlap")
        # Two corpora routinely describe the same byte.  That is not an
        # overlap by itself; only two distinct rows within one corpus are a
        # listing overlap.
        if len({(row.corpus, row.line) for row in rows}) > len({row.corpus for row in rows}):
            flags.append("listing_overlap")
        if not rows:
            flags.append("listing_gap")
        if truncated:
            flags.append("truncated_listing")
        if any(issue.get("address") == hex_address(address) for issue in listing_issues):
            flags.append("retail_byte_mismatch")
        if any(issue.get("address") == hex_address(address) for issue in validation_issues):
            flags.append("retail_byte_mismatch")
        if flags:
            category = "disagreement" if any(
                flag in flags
                for flag in ("listing_kind_disagreement", "instruction_byte_disagreement", "retail_byte_mismatch")
            ) else "overlap" if any(flag in flags for flag in ("function_overlap", "listing_overlap")) else None
        else:
            category = None
        if category is None:
            if not rows:
                category = "listing_gap"
            elif truncated:
                category = "listing_ambiguous_truncated"
            elif "instruction" in listing_kinds:
                category = "instruction"
            elif "defined_data" in listing_kinds:
                category = "defined_data"
            elif "undefined" in listing_kinds:
                category = "undefined_or_padding_candidate"
            else:
                category = "listing_unknown"
        candidate = None
        if category == "undefined_or_padding_candidate":
            # Defer the pattern check to a contiguous run below.  The final
            # attrs still state that this is only a candidate.
            candidate = "pending"
        attrs.append(
            {
                "category": category,
                "flags": tuple(sorted(set(flags))),
                "listing_sources": tuple(listing_sources),
                "listing_kinds": tuple(listing_kinds),
                "candidate": candidate,
            }
        )

    # Mark cautious candidate patterns only within undefined listing runs.
    index = 0
    while index < size:
        if attrs[index]["category"] != "undefined_or_padding_candidate":
            index += 1
            continue
        end = index + 1
        while end < size and attrs[end]["category"] == "undefined_or_padding_candidate":
            end += 1
        pattern = _candidate_pattern(retail[index:end])
        if pattern:
            for current in range(index, end):
                attrs[current]["candidate"] = pattern
        else:
            for current in range(index, end):
                attrs[current]["candidate"] = None
        index = end

    # Coalesce bytes with the same externally meaningful evidence. Individual
    # instruction mnemonics, function names, and function counts are kept out
    # of the key; they belong in the function-body report and would make the
    # range map needlessly enormous. Broad listing kinds and source corpora
    # still preserve the evidence distinction needed by the baseline.
    ranges: list[dict[str, object]] = []
    index = 0
    while index < size:
        key = tuple(sorted(attrs[index].items()))
        end = index + 1
        while end < size and tuple(sorted(attrs[end].items())) == key:
            end += 1
        item = attrs[index]
        ranges.append(
            {
                "start": hex_address(retail_start + index),
                "end": hex_address(retail_start + end - 1),
                "bytes": end - index,
                "category": item["category"],
                "flags": list(item["flags"]),
                "listing_sources": list(item["listing_sources"]),
                "listing_kinds": list(item["listing_kinds"]),
                "candidate_pattern": item["candidate"],
            }
        )
        index = end

    function_coverage: dict[str, object] = {}
    for corpus, records in function_records.items():
        body_mask = body_masks[corpus]
        instruction_mask = instruction_masks[corpus]
        body_bytes = sum(body_mask)
        instruction_bytes = sum(instruction_mask)
        inside = sum(1 for i in range(size) if body_mask[i] and instruction_mask[i])
        function_coverage[corpus] = {
            "function_count": len(records),
            "declared_body_bytes": sum(end - start + 1 for record in records for start, end in record.ranges),
            "union_body_bytes": body_bytes,
            "instruction_bytes": instruction_bytes,
            "instruction_bytes_inside_body": inside,
            "body_bytes_without_instruction_listing": body_bytes - inside,
            "instruction_bytes_outside_body": instruction_bytes - inside,
            "body_only_ranges": _mask_ranges(bytearray(1 if body_mask[i] and not instruction_mask[i] else 0 for i in range(size)), retail_start),
        }
    summary = {
        "text_start": hex_address(retail_start),
        "text_end": hex_address(retail_end),
        "text_bytes": size,
        "range_count": len(ranges),
        "byte_counts": dict(sorted(collections.Counter(str(item["category"]) for item in attrs).items())),
        "range_counts": dict(sorted(collections.Counter(str(item["category"]) for item in ranges).items())),
        "listing_gap_bytes": sum(1 for item in attrs if "listing_gap" in item["flags"]),
        "truncated_listing_bytes": sum(1 for item in attrs if "truncated_listing" in item["flags"]),
        "overlap_bytes": sum(1 for item in attrs if item["category"] == "overlap"),
        "disagreement_bytes": sum(1 for item in attrs if item["category"] == "disagreement"),
        "defined_data_bytes": sum(1 for item in attrs if item["category"] == "defined_data"),
        "instruction_bytes": sum(1 for item in attrs if item["category"] == "instruction"),
        "undefined_or_candidate_bytes": sum(1 for item in attrs if item["category"] == "undefined_or_padding_candidate"),
        "function_body_coverage": function_coverage,
        "body_multi_owner_bytes": sum(1 for count in body_counts if count > 1),
        "body_overlap_bytes_cross_corpus": sum(
            1 for index in range(size) if body_masks["full"][index] and body_masks["augmented"][index]
        ),
        "body_multi_owner_bytes_by_corpus": {
            corpus: sum(1 for count in body_counts_by_corpus[corpus] if count > 1)
            for corpus in body_counts_by_corpus
        },
        "body_bytes_without_any_function": sum(1 for count in body_counts if count == 0),
        "validation_issue_count": len(validation_issues) + len(listing_issues),
    }
    validation = {
        "authenticated": True,
        "listing_byte_mismatches": listing_issues,
        "assembly_issues": validation_issues,
        "truncated_listing_rows": {
            corpus: corpus_info[corpus]["truncated_listing_rows"] for corpus in corpus_info
        },
        "assumptions": [
            "The retail executable and its raw .text section were authenticated using reference_bytes_validation.json.",
            "Rows marked ?? are undefined in the Ghidra listing; repeated bytes are reported only as padding candidates.",
            "Truncated listing rows retain an ambiguous tail range and are never filled from retail as listing evidence.",
            "Function body coverage is an independent boundary report and does not classify every body byte as an instruction.",
        ],
    }
    if listing_issues or validation_issues:
        # Keep the map available to callers for diagnosis while making the CLI
        # fail closed below.  A byte-exact baseline cannot trust mismatching
        # listing evidence.
        validation["authenticated"] = False
    result = {
        "schema_version": 1,
        "tool": "matching2/tools/asm_coverage.py",
        "reference": {
            "executable": str(retail_executable),
            "executable_sha256": retail_info["executable_sha256"],
            "text_sha256": retail_info["text_sha256"],
            "text_file_offset": retail_info["text_file_offset"],
            "text_start": hex_address(retail_start),
            "text_end": hex_address(retail_end),
            "text_bytes": size,
        },
        "inputs": corpus_info,
        "summary": summary,
        "validation": validation,
        "ranges": ranges,
    }
    return result


def write_outputs(result: Mapping[str, object], output_dir: Path) -> None:
    output_dir.mkdir(parents=True, exist_ok=True)
    (output_dir / "text_range_map.json").write_text(json.dumps(result, indent=2) + "\n", encoding="utf-8")
    (output_dir / "summary.json").write_text(json.dumps(result["summary"], indent=2) + "\n", encoding="utf-8")
    ranges = result["ranges"]
    with (output_dir / "text_ranges.tsv").open("w", encoding="utf-8", newline="") as handle:
        handle.write("start\tend\tbytes\tcategory\tflags\tlisting_sources\tcandidate_pattern\n")
        for item in ranges:
            handle.write(
                "\t".join(
                    [
                        str(item["start"]),
                        str(item["end"]),
                        str(item["bytes"]),
                        str(item["category"]),
                        ",".join(item["flags"]),
                        ",".join(item["listing_sources"]),
                        str(item["candidate_pattern"] or ""),
                    ]
                )
                + "\n"
            )


def main(argv: Sequence[str] | None = None) -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--retail-exe", type=Path, default=Path(os.environ.get("TH10_RETAIL_EXE", DEFAULT_RETAIL)))
    parser.add_argument("--full-dir", type=Path, default=DEFAULT_FULL)
    parser.add_argument("--augmented-dir", type=Path, default=DEFAULT_AUGMENTED)
    parser.add_argument("--output-dir", type=Path, default=DEFAULT_OUTPUT)
    parser.add_argument("--no-write", action="store_true", help="audit and print summary without writing generated files")
    args = parser.parse_args(argv)
    try:
        result = audit(args.retail_exe, args.full_dir, args.augmented_dir)
        if not args.no_write:
            write_outputs(result, args.output_dir)
        print(json.dumps(result["summary"], sort_keys=True))
        if not result["validation"]["authenticated"]:
            print("assembly/listing validation failed; see validation in text_range_map.json", file=sys.stderr)
            return 1
        return 0
    except AuditError as exc:
        print(f"asm_coverage: {exc}", file=sys.stderr)
        return 2


if __name__ == "__main__":
    raise SystemExit(main())
