#!/usr/bin/env python3
"""One-time/review-time conversion of authenticated disassembly into .text source.

Normal builds use the resulting versioned assembly, not this generator or retail.
"""

import argparse
import hashlib
import json
from pathlib import Path
import re
import shutil
import tempfile

from build_asm_proof import PEImage


ROOT = Path(__file__).resolve().parents[2]
TEXT_START = 0x00401000
TEXT_END = 0x00465C00


def address(value):
    return int(value, 0) if isinstance(value, str) else value


def load_instructions():
    rows = {}
    for corpus in ("ghidra_full", "ghidra_augmented"):
        for path in sorted((ROOT / "decompiled" / corpus / "functions").glob("*.asm")):
            for line in path.read_text().splitlines():
                if not line or line.startswith(";"):
                    continue
                encoded_address, encoded, listing = line.split("\t", 2)
                start = int(encoded_address, 16)
                if not TEXT_START <= start < TEXT_END:
                    continue
                if "..." in encoded:
                    raise ValueError("truncated instruction listing: " + str(path))
                raw = bytes.fromhex(encoded)
                if start in rows and rows[start]["data"] != raw:
                    raise ValueError(f"conflicting instructions at {start:#x}")
                rows[start] = {"address": start, "data": raw, "listing": listing,
                               "reference": str(path.relative_to(ROOT)), "kind": "instruction"}
    return rows


def consume_unresolved(spans, start, end, replacement=None):
    """Resolve exactly an interval of previously unclassified bytes."""
    result, covered = [], 0
    for span in spans:
        left, right = address(span["start"]), address(span["end"]) + 1
        overlap_left, overlap_right = max(left, start), min(right, end)
        if overlap_left >= overlap_right:
            result.append(span)
            continue
        if span["kind"] != "unresolved":
            raise ValueError(f"recovery overlaps an already classified range at {overlap_left:#x}")
        covered += overlap_right - overlap_left
        if left < overlap_left:
            result.append({**span, "end": f"0x{overlap_left - 1:08X}"})
        if overlap_right < right:
            result.append({**span, "start": f"0x{overlap_right:08X}"})
    if covered != end - start:
        raise ValueError(f"recovery range {start:#x}..{end:#x} includes known instructions or overlaps another recovery")
    if replacement is not None:
        result.append(replacement)
    return sorted(result, key=lambda span: address(span["start"]))


def replace_instructions(rows, spans, correction):
    """Retire explicitly identified bad decodes without hiding classified bytes."""
    start, end = address(correction["start"]), address(correction["end"]) + 1
    old = [address(value) for value in correction["old_rows"]]
    if not correction.get("evidence") or len(old) != len(set(old)):
        raise ValueError("boundary correction requires evidence and unique old rows")
    revised = list(spans)
    for key in old:
        if key not in rows:
            raise ValueError(f"boundary correction names missing row {key:#x}")
        row_end = key + len(rows[key]["data"])
        if not start <= key < row_end <= end:
            raise ValueError("boundary correction must contain entire retired rows")
        revised.append({"start": key, "end": row_end - 1, "kind": "unresolved"})
    # The union must be exactly the requested correction, including its unknown prefixes.
    revised = consume_unresolved(revised, start, end)
    cursor = start
    for row in correction["additional_instructions"]:
        if address(row["address"]) != cursor or not row["hex"]:
            raise ValueError("replacement instructions must partition the correction")
        cursor += len(bytes.fromhex(row["hex"]))
    if cursor != end:
        raise ValueError("replacement instructions must cover the entire correction")
    for key in old:
        del rows[key]
    return revised


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--exe", type=Path, default=Path.home() / "Games/TH10 - Mountain of Faith/th10.exe")
    parser.add_argument("--classification", type=Path, default=ROOT / "matching2/asm/text_classification.json")
    parser.add_argument("--recovery", type=Path, action="append", default=[],
                        help="reviewed classification/code recovery overlay; may be repeated")
    parser.add_argument("--output", type=Path, default=ROOT / "matching2/asm/text")
    parser.add_argument("--replace", action="store_true", help="replace an existing generated source directory")
    args = parser.parse_args()
    args.output = args.output.resolve()
    if args.output.exists() and not args.replace:
        parser.error("output exists; review changes and use --replace to regenerate")
    if args.output.exists():
        (args.output / ".generation-in-progress").write_text(
            "A source regeneration was started. Builds refuse this tree until regeneration succeeds.\n")
    # Keep decoder dependencies out of the ordinary build path.
    from asm_instruction import instruction_to_asm

    original = args.exe.read_bytes()
    validation = json.loads((ROOT / "decompiled/reference_bytes_validation.json").read_text())
    if hashlib.sha256(original).hexdigest() != validation["executable_sha256"]:
        raise ValueError("retail SHA-256 does not match the supported reference")
    pe = PEImage(original)
    text = pe.read(TEXT_START, TEXT_END - TEXT_START)
    rows = load_instructions()
    classifications = json.loads(args.classification.read_text())
    expected_reference = {
        "executable_sha256": validation["executable_sha256"],
        "text_sha256": validation["text_section_sha256"],
        "text_start": f"0x{TEXT_START:08X}", "text_end": f"0x{TEXT_END - 1:08X}",
        "text_bytes": TEXT_END - TEXT_START,
    }
    if classifications.get("schema_version") != 1 or any(
            classifications.get("reference", {}).get(key) != value for key, value in expected_reference.items()):
        raise ValueError("classification provenance does not match the supported reference")
    for span in classifications["ranges"]:
        if span["bytes"] != address(span["end"]) - address(span["start"]) + 1:
            raise ValueError("classification range byte count is inconsistent")
    def add_instruction(row):
        start = address(row["address"])
        raw = bytes.fromhex(row["hex"])
        if start in rows:
            raise ValueError(f"additional instruction duplicates {start:#x}")
        rows[start] = {"address": start, "data": raw, "listing": row["listing"],
                       "reference": row["reference"], "kind": "instruction"}
        return start, start + len(raw)

    for row in classifications.get("additional_instructions", []):
        add_instruction(row)
    spans = classifications["ranges"]
    for path in args.recovery:
        recovery = json.loads(path.read_text())
        if any(recovery.get("reference", {}).get(key) != value for key, value in expected_reference.items()
               if key != "text_bytes" or key in recovery.get("reference", {})):
            raise ValueError("recovery provenance does not match the supported reference: " + str(path))
        source_digest = recovery.get("source_manifest_sha256")
        if source_digest and source_digest != hashlib.sha256(args.classification.read_bytes()).hexdigest():
            raise ValueError("recovery was made against a different classification manifest")
        for correction in recovery.get("instruction_replacements", []):
            spans = replace_instructions(rows, spans, correction)
            for row in correction["additional_instructions"]:
                add_instruction(row)
        for row in recovery.get("additional_instructions", []):
            start, end = add_instruction(row)
            spans = consume_unresolved(spans, start, end)
        for span in recovery.get("resolved_ranges", []):
            if span["kind"] not in ("data", "padding"):
                raise ValueError("resolved range must identify data or padding")
            spans = consume_unresolved(spans, address(span["start"]), address(span["end"]) + 1, span)
    segments = list(rows.values())
    for span in spans:
        kind = span["kind"]
        if kind not in ("data", "padding"):
            raise ValueError(f"unresolved classification: {span}")
        start, end = address(span["start"]), address(span["end"]) + 1
        if not TEXT_START <= start < end <= TEXT_END:
            raise ValueError("classification lies outside .text")
        segments.append({"address": start, "data": text[start - TEXT_START:end - TEXT_START],
                         "kind": kind, "evidence": span["evidence"]})
    segments.sort(key=lambda row: row["address"])
    cursor = TEXT_START
    for segment in segments:
        start, raw = segment["address"], segment["data"]
        if start != cursor or not raw:
            raise ValueError(f"source partition has a gap or overlap at {cursor:#x}, next {start:#x}")
        if raw != text[start - TEXT_START:start - TEXT_START + len(raw)]:
            raise ValueError(f"instruction bytes disagree with retail at {start:#x}")
        cursor += len(raw)
    if cursor != TEXT_END:
        raise ValueError("source partition does not cover all .text bytes")

    chunks = {}
    targets = set()
    failures = []
    for segment in segments:
        start, raw = segment["address"], segment["data"]
        bucket = (start - TEXT_START) // 0x10000
        lines = chunks.setdefault(bucket, [])
        if segment["kind"] == "instruction":
            try:
                assembly = instruction_to_asm(start, raw)
            except Exception as error:
                failures.append({"address": f"0x{start:08X}", "hex": raw.hex(), "error": str(error)})
                continue
            if not isinstance(assembly, str) or not assembly.strip():
                raise ValueError("encoder must return nonempty assembly text")
            targets.update(int(match, 16) for match in re.findall(r"_th10_([0-9a-fA-F]{8})\b", assembly))
            lines.extend([f".globl _th10_{start:08x}", f"_th10_{start:08x}:",
                          f"    {assembly}  # {raw.hex()}"])
        else:
            evidence = json.dumps(segment["evidence"], ensure_ascii=True)
            lines.append(f"# {segment['kind']} {start:08x}..{start + len(raw) - 1:08x}: {evidence}")
            if segment["kind"] == "padding" and len(set(raw)) == 1:
                lines.append(f".fill {len(raw)}, 1, 0x{raw[0]:02x}")
            else:
                for offset in range(0, len(raw), 16):
                    lines.append(".byte " + ",".join(f"0x{value:02x}" for value in raw[offset:offset + 16]))
    if failures:
        destination = ROOT / "matching2/build/asm-baseline/encoding_failures.json"
        destination.parent.mkdir(parents=True, exist_ok=True)
        destination.write_text(json.dumps(failures, indent=2) + "\n")
        raise ValueError(f"{len(failures)} instructions could not be encoded; see {destination}")

    args.output.parent.mkdir(parents=True, exist_ok=True)
    with tempfile.TemporaryDirectory(prefix=".text-generate-", dir=args.output.parent) as temporary:
        output = Path(temporary)
        (output / "chunks").mkdir()
        main_lines = ["# Generated from authenticated disassembly. See manifest.json.",
                      ".intel_syntax noprefix", ".code32", ".text", ".globl _th10_text_start", "_th10_text_start:"]
        aliases = sorted(target for target in targets if TEXT_START <= target < TEXT_END and target not in rows)
        for target in aliases:
            main_lines.append(f".set _th10_{target:08x}, _th10_text_start + 0x{target - TEXT_START:x}")
        for bucket, lines in sorted(chunks.items()):
            name = f"chunks/{TEXT_START + bucket * 0x10000:08x}.s"
            (output / name).write_text("\n".join(lines) + "\n")
            main_lines.append(f'.include "{name}"')
        main_lines.extend([".globl _th10_text_end", "_th10_text_end:"])
        (output / "main.s").write_text("\n".join(main_lines) + "\n")
        external = sorted(target for target in targets if not TEXT_START <= target < TEXT_END)
        link_lines = ["SECTIONS", "{", "  .text 0x00401000 : { KEEP(*(.text)) }",
                      "  /DISCARD/ : { *(.data) *(.bss) *(.rdata*) *(.idata*) *(.reloc*) }"]
        link_lines.extend(f"  _th10_{target:08x} = 0x{target:08x};" for target in external)
        link_lines.extend([f'  ASSERT(SIZEOF(.text) == {len(text)}, "wrong .text extent")', "}"])
        (output / "layout.ld").write_text("\n".join(link_lines) + "\n")
        manifest = {
            "text_start": f"0x{TEXT_START:08X}", "text_bytes": len(text),
            "text_sha256": hashlib.sha256(text).hexdigest(),
            "retail_sha256": validation["executable_sha256"],
            "instruction_count": len(rows), "instruction_bytes": sum(len(row["data"]) for row in rows.values()),
            "classified_data_bytes": sum(len(row["data"]) for row in segments if row["kind"] == "data"),
            "classified_padding_bytes": sum(len(row["data"]) for row in segments if row["kind"] == "padding"),
            "classification_sha256": hashlib.sha256(args.classification.read_bytes()).hexdigest(),
            "recovery_sha256": {str(p.relative_to(ROOT)) if p.is_relative_to(ROOT) else str(p):
                                hashlib.sha256(p.read_bytes()).hexdigest() for p in args.recovery},
            "interior_or_data_target_aliases": [f"0x{target:08X}" for target in aliases],
            "external_targets": [f"0x{target:08X}" for target in external],
            "source_sha256": {str(p.relative_to(output)): hashlib.sha256(p.read_bytes()).hexdigest()
                              for p in sorted(output.rglob("*")) if p.is_file()},
            "reference_listing_sha256": {
                corpus: hashlib.sha256("".join(
                    str(p.relative_to(ROOT)) + "\0" + hashlib.sha256(p.read_bytes()).hexdigest() + "\n"
                    for p in sorted((ROOT / "decompiled" / corpus / "functions").glob("*.asm"))
                ).encode()).hexdigest() for corpus in ("ghidra_full", "ghidra_augmented")},
            "notes": ["Instruction encodings are assembled, never extracted during normal builds.",
                      "Data and padding classifications retain their evidence in the generated source.",
                      "Physical address chunks do not claim original translation-unit or class boundaries."],
        }
        (output / "manifest.json").write_text(json.dumps(manifest, indent=2) + "\n")
        if args.output.exists():
            shutil.rmtree(args.output)
        shutil.copytree(output, args.output)
    print(f"Generated {len(rows):,} instructions and all {len(text):,} .text bytes: {args.output}")


if __name__ == "__main__":
    main()
