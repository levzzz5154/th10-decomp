#!/usr/bin/env python3
"""Inventory audit scope and evidence; this does not establish retail equivalence.

From any directory: python3 matching2/tools/audit_inventory.py --write (or --check).
Paths and hashes describe the files present at generation time, independently of
the named capture baseline. No Git checkout, IDA installation, or Ghidra server
is required. The default baseline is the frozen pre-audit snapshot.
"""

import argparse
import ast
import csv
import hashlib
import json
import re
from collections import Counter, defaultdict
from pathlib import Path


REPOSITORY = Path(__file__).resolve().parents[2]
BASELINE = "895c4202387d1c6099cf0cec2e8798bdae6a1754"
CAPTURE_DATE = "2026-09-06"
SOURCE_ROOTS = ("matching2/src", "matching2/include", "matching2/standalone")
SUMMARY = "matching2/docs/semantic_audit_summary.json"
MANIFEST = "matching2/docs/semantic_exhaustive_audit_manifest.json"
SPARSE = "matching2/docs/semantic_spot_audit.md"
PRIOR_INPUTS = (
    SUMMARY, MANIFEST, SPARSE,
    "matching2/docs/semantic_audit_summary.md",
    "matching2/docs/semantic_audit_coordinator_results.json",
    "matching2/docs/semantic_audit_coordinator.md",
    "matching2/docs/semantic_audit_ending.json",
    "matching2/docs/semantic_audit_ending.md",
    "matching2/docs/semantic_player_audit.json",
    "matching2/docs/semantic_player_audit.md",
)
TOKEN = re.compile(r"\b0x(004[0-9a-f]{5})\b|\b(?:sub|FUN)_([0-9a-f]{6,8})\b", re.I)
MARKER = re.compile(r"^\s*//\s*(?:functions?\s*:\s*)?0x004[0-9a-f]{5}", re.I)
SEMANTIC_PHRASES = (
    "semantic reconstruction", "clean reconstruction", "readable reconstruction",
    "readable frame", "conventional-abi form", "backed form", "corresponding to",
    "retail address", "retail function",
)
C_HEADER = re.compile(r"^//----- \(([0-9A-Fa-f]{8})\) -+")
ASM_START = re.compile(r"^(\S+) proc (?:near|far)\b")
ASM_END = re.compile(r"^(\S+) endp\b")


def address(value):
    return f"0x{int(value, 16) if isinstance(value, str) else value:08X}"


def read_json(root, relative):
    return json.loads((root / relative).read_text())


def file_record(root, relative):
    path = root / relative
    if not path.is_file():
        return {"path": relative, "available": False}
    data = path.read_bytes()
    return {"path": relative, "available": True, "bytes": len(data),
            "sha256": hashlib.sha256(data).hexdigest(),
            "lines": len(data.splitlines())}


def source_inventory(root):
    files, occurrences = [], defaultdict(list)
    for directory in SOURCE_ROOTS:
        if not (root / directory).is_dir():
            raise ValueError(f"missing source scope directory: {directory}")
        for path in sorted((root / directory).rglob("*")):
            if not path.is_file():
                continue
            relative = path.relative_to(root).as_posix()
            row = file_record(root, relative)
            found, claims = set(), set()
            for number, line in enumerate(path.read_text(errors="replace").splitlines(), 1):
                tokens = {int(m.group(1) or m.group(2), 16) for m in TOKEN.finditer(line)}
                for value in sorted(tokens):
                    if not 0x00400000 <= value < 0x00500000:
                        continue
                    addr = address(value)
                    kind = "address_reference"
                    if MARKER.match(line):
                        kind = "implementation_marker_candidate"
                    elif any(phrase in line.lower() for phrase in SEMANTIC_PHRASES):
                        kind = "semantic_phrase_candidate"
                    occurrences[addr].append({"path": relative, "line": number,
                                              "kind": kind, "text": line.strip()})
                    found.add(addr)
                    if kind != "address_reference":
                        claims.add(addr)
            row.update({"audit_status": "pending_file_review", "addresses": sorted(found),
                        "candidate_claim_addresses": sorted(claims)})
            files.append(row)
    return files, occurrences


def reference_inventory(root):
    c_path, asm_path = "ida/th10.exe.c", "ida/th10.exe.asm"
    c_sections, asm_sections, names = {}, {}, {}
    if (root / c_path).is_file():
        lines = (root / c_path).read_text(errors="replace").splitlines()
        starts = [(i, address(m.group(1))) for i, line in enumerate(lines)
                  if (m := C_HEADER.match(line))]
        for index, (start, addr) in enumerate(starts):
            end = starts[index + 1][0] if index + 1 < len(starts) else len(lines)
            signature = next((line.strip() for line in lines[start + 1:end]
                              if line.strip() and not line.startswith("//")), "")
            c_sections[addr] = {"available": True, "path": c_path,
                                "line_start": start + 1, "line_end": end,
                                "signature": signature}
            name = re.search(r"([A-Za-z_]\w*)(?:@<[^>]+>)?\s*\(", signature)
            if name:
                names[name.group(1)] = addr
    if (root / asm_path).is_file():
        active = None
        for number, line in enumerate((root / asm_path).read_text(errors="replace").splitlines(), 1):
            if match := ASM_START.match(line):
                active = (match.group(1), number)
            elif (match := ASM_END.match(line)) and active and match.group(1) == active[0]:
                symbol, start = active
                direct = re.fullmatch(r"sub_([0-9A-Fa-f]+)", symbol)
                canonical = re.sub(r"@\d+$", "", symbol).lstrip("_")
                addr = address(direct.group(1)) if direct else names.get(canonical)
                if addr:
                    asm_sections[addr] = {"available": True, "path": asm_path,
                                          "line_start": start, "line_end": number,
                                          "symbol": symbol,
                                          "mapping": "address_label" if direct else "pseudocode_signature"}
                active = None
    return c_sections, asm_sections


def tracked_inputs(root):
    relative = "decompiled/ghidra_raw/index.tsv"
    with (root / relative).open(newline="") as stream:
        indexed = list(csv.DictReader(stream, delimiter="\t"))
    ghidra = defaultdict(list)
    for line, row in enumerate(indexed, 2):
        path = "decompiled/ghidra_raw/" + row["file"] if row["file"] else None
        record = file_record(root, path) if path else {"path": None, "available": False}
        record.update({"index_path": relative, "index_line": line,
                       "export_status": row["status"], "detail": row["detail"],
                       "tracking_name": row["tracking_name"], "ghidra_name": row["ghidra_name"]})
        if record["available"]:
            record.update({"line_start": 1, "line_end": record["lines"]})
        ghidra[address(row["address"])].append(record)
    tree = ast.parse((root / "matching2/tools/build_hybrid.py").read_text())
    overlays = defaultdict(list)
    for node in tree.body:
        if isinstance(node, ast.Assign) and any(isinstance(t, ast.Name) and t.id == "OVERLAYS"
                                                for t in node.targets):
            for object_name, symbol, value in ast.literal_eval(node.value):
                overlays[address(value)].append({"object": object_name, "symbol": symbol})
            break
    else:
        raise ValueError("historical OVERLAYS inventory not found")
    ledger = read_json(root, "matching2/coverage.json")
    entries = {address(row["address"]): row for row in ledger["functions"]}
    expected = set(ghidra) | set(overlays)
    if len(entries) != len(ledger["functions"]) or set(entries) != expected:
        missing, extra = sorted(expected - set(entries)), sorted(set(entries) - expected)
        raise ValueError(f"coverage address inventory mismatch: missing={missing}, extra={extra}; duplicates are invalid")
    return entries, ghidra, overlays


def prior_inventory(root, tracked):
    summary, manifest = read_json(root, SUMMARY), read_json(root, MANIFEST)
    partition_rows = [address(row["address"]) for group in manifest["groups"].values()
                      for rows in group["files"].values() for row in rows]
    partition = set(partition_rows)
    sparse = {address(row["address"]): row["evidence"] for row in manifest["known_checked"]}
    rows = {address(row["address"]): row for row in summary["rows"]}
    counts = Counter(row["verdict"] for row in rows.values())
    status, scope = summary["status"], summary["scope"]
    if (len(rows) != len(summary["rows"]) or len(partition_rows) != len(partition)
            or not set(rows) <= partition
            or not partition <= set(tracked) or not set(sparse) <= set(tracked)
            or partition & set(sparse)
            or len(partition) != scope["partition_addresses"]
            or len(partition) != manifest["remaining_total"]
            or len(rows) != status["reviewed"]
            or counts["grounded"] != status["grounded"]
            or counts["partial"] != status["partial"]
            or sum(counts.values()) != counts["grounded"] + counts["partial"]
            or status["remaining"] != len(partition) - len(rows)
            or status["remaining"] != status["pending"] + status["reference_unresolved"]
            or len(sparse) != scope["previously_checked_addresses"]
            or len(sparse) != manifest["known_checked_total"]
            or scope["manifest_semantic_addresses"] != manifest["semantic_total"]
            or scope["previously_checked_semantic_addresses"] != manifest["known_checked_semantic_total"]
            or manifest["remaining_total"] + manifest["known_checked_semantic_total"] != manifest["semantic_total"]):
        raise ValueError("prior bounded audit scope/counts are inconsistent; do not promote these results")
    # Preserve the report's explicit reference-unresolved rows, separately from ordinary pending work.
    unresolved = set()
    player = read_json(root, "matching2/docs/semantic_player_audit.json")
    for row in player["rows"]:
        if row["verdict"] in ("unresolved", "reference_unresolved"):
            unresolved.add(address(row["address"]))
    if len(unresolved) != status["reference_unresolved"] or not unresolved <= partition - set(rows):
        raise ValueError("prior reference-unresolved address count/scope is inconsistent")
    per_address = {}
    for addr in sorted(tracked):
        if addr in rows:
            row = rows[addr]
            per_address[addr] = {"status": "reported_" + row["verdict"],
                                 "report": SUMMARY, "finding": row["finding"],
                                 "evidence": row.get("evidence", {}),
                                 "reports": row.get("reports", [])}
        elif addr in sparse:
            per_address[addr] = {"status": "separate_sparse_review", "report": SPARSE,
                                 "evidence": sparse[addr]}
        elif addr in unresolved:
            per_address[addr] = {"status": "reference_unresolved", "report": SUMMARY}
        elif addr in partition:
            per_address[addr] = {"status": "pending_bounded_review", "report": SUMMARY}
        else:
            per_address[addr] = {"status": "outside_prior_bounded_and_sparse_scopes"}
    sources = [file_record(root, relative) for relative in PRIOR_INPUTS]
    for source in sources:
        if not source["available"]:
            raise ValueError(f"missing prior audit evidence: {source['path']}")
        dates = sorted(set(re.findall(r"\b20\d{2}-\d{2}-\d{2}\b", (root / source["path"]).read_text())))
        source["dates_written_in_report"] = dates
    return {"capture_date": CAPTURE_DATE, "capture_baseline_commit": BASELINE,
            "historical_evidence_path_base": "matching2 (paths inside copied historical findings/scope remain verbatim)",
            "original_bounded_review_baseline_commit": None,
            "original_bounded_review_baseline_note": "Not stated in the consolidated report; capture baseline is not proof of the originally reviewed revision.",
            "sparse_review_baseline_description": "Working tree based on 554cfff, as stated in semantic_spot_audit.md; original uncommitted contents are not reconstructed here.",
            "scope": scope, "reported_counts": status, "sources": sources,
            "limit": "Historical verdicts describe stated reviewed boundaries only, may be wrong, and are not revalidated by this inventory."}, per_address


def generate(root=REPOSITORY):
    root = Path(root)
    tracked, ghidra, overlays = tracked_inputs(root)
    files, occurrences = source_inventory(root)
    c_sections, asm_sections = reference_inventory(root)
    prior, statuses = prior_inventory(root, tracked)

    def references(addr):
        return {"ida_c": c_sections.get(addr, {"available": False, "path": "ida/th10.exe.c"}),
                "ida_asm": asm_sections.get(addr, {"available": False, "path": "ida/th10.exe.asm"}),
                "ghidra": ghidra.get(addr, [])}

    functions = []
    for addr, entry in sorted(tracked.items()):
        candidates = occurrences.get(addr, [])
        claim_files = sorted({row["path"] for row in candidates if row["kind"] != "address_reference"})
        functions.append({"address": addr, "symbol": entry["symbol"], "retail_size": entry["size"],
                          "annotation": {"status": entry["status"],
                                         "legacy_selected_source": ("matching2/" + entry["source"]
                                                                    if entry["source"].startswith(("src/", "include/", "standalone/"))
                                                                    else entry["source"]),
                                         "blocker": entry.get("blocker")},
                          "historical_overlays": overlays.get(addr, []),
                          "candidate_claim_files": claim_files,
                          "multiple_candidate_claim_files": len(claim_files) > 1,
                          "source_occurrences": candidates, "references": references(addr),
                          "prior_review": statuses[addr], "current_audit_status": "pending_revalidation"})
    boundary = [{"address": addr, "status": "boundary_review_candidate",
                 "references": references(addr), "source_occurrences": occurrences.get(addr, [])}
                for addr in sorted((set(c_sections) | set(asm_sections)) - set(tracked))]
    untracked = [{"address": addr, "source_occurrences": occurrences[addr]}
                 for addr in sorted(set(occurrences) - set(tracked))]
    inputs = [file_record(root, path) for path in (
        "matching2/coverage.json", "decompiled/ghidra_raw/index.tsv",
        "matching2/tools/build_hybrid.py", "matching2/tools/coverage_report.py",
        "ida/th10.exe.c", "ida/th10.exe.asm", "ida/th10.exe.h")]
    return {"schema_version": 1,
            "baseline": {"commit": BASELINE, "capture_date": CAPTURE_DATE,
                         "hash_policy": "SHA-256 hashes describe current files at generation, which may differ from the capture baseline; no equivalence or unchanged-tree claim."},
            "scope_policy": {"addresses": "Exact union of Ghidra index and historical OVERLAYS; checked against coverage.json.",
                             "files": "Every file recursively under matching2/src, matching2/include, and matching2/standalone, including uncredited helpers and extensionless/resource files; build inclusion is not inferred.",
                             "claims": "All 0x004xxxxx and sub_/FUN_ address tokens in scope are heuristic candidates/references, not parsed function boundaries. Multiple claim files need adjudication, not automatic duplicate-body classification.",
                             "references": "Availability is syntactic, not quality or correctness. IDA C section endpoints include trailing annotations. ASM mapping uses address labels or matching named C signatures. Indirect calls and aliases are not resolved.",
                             "boundary_candidates": "IDA C/ASM entries outside coverage are boundary-review candidates, not newly proven game functions; may include runtime/library functions or split/merged boundaries.",
                             "completion": "No function or file is marked complete by inventory generation; historical results remain separate from source annotations."},
            "summary": {"coverage_addresses": len(functions), "ghidra_index_addresses": len(ghidra),
                        "historical_overlay_addresses": len(overlays), "file_scope": len(files),
                        "files_without_candidate_claims": sum(not row["candidate_claim_addresses"] for row in files),
                        "multiple_candidate_claim_addresses": sum(row["multiple_candidate_claim_files"] for row in functions),
                        "ida_boundary_review_candidates": len(boundary),
                        "annotation_counts": dict(sorted(Counter(row["annotation"]["status"] for row in functions).items())),
                        "prior_review_counts": dict(sorted(Counter(row["prior_review"]["status"] for row in functions).items()))},
            "inputs": inputs, "prior_audit": prior, "functions": functions,
            "file_audit_scope": files, "ida_boundary_review_candidates": boundary,
            "untracked_source_addresses": untracked}


def link(path, line=None):
    label = path + (f":{line}" if line else "")
    return f"[{label}](../../../{path}" + (f"#L{line}" if line else "") + ")"


def render_markdown(doc):
    s = doc["summary"]
    lines = ["# Recovered-code audit inventory", "",
             f"Capture baseline: `{BASELINE}`, dated {CAPTURE_DATE}. File hashes describe the current generated inputs, not an assertion that they still match the baseline.", "",
             f"Scope: **{s['coverage_addresses']} coverage addresses**, **{s['file_scope']} production/header/standalone files**, and **{s['ida_boundary_review_candidates']} IDA boundary-review candidates** outside coverage. All require review or revalidation. Full occurrence text, reference ranges, hashes, and historical findings are in [inventory.json](inventory.json).", "",
             "Source annotations and prior review verdicts are separate. Candidate markers are heuristic: several files may be wrappers, references, alternate implementations, or actual competing bodies. The inventory does not choose one owner. File scope includes uncredited helpers and does not infer which files a build uses.", "",
             f"Earlier bounded review: **{doc['prior_audit']['reported_counts']['reviewed']} reviewed** within a **{doc['prior_audit']['scope']['partition_addresses']}-address** partition scope, with five separate sparse checks. Historical `grounded` means a reported result at that report's stated boundary; it is neither revalidated nor whole-program proof. The bounded report does not specify its original source commit. Report hashes, written dates, scope, and count validation are preserved in JSON.", "",
             "Generate: `python3 matching2/tools/audit_inventory.py --write`. Verify: `python3 matching2/tools/audit_inventory.py --check`. Test: `python3 matching2/tests/audit_inventory_test.py`. Commands run from the repository root; the script itself also works from other directories. `--check` fails on missing/stale outputs or inconsistent address/report inventories.", "",
             "## Counts", "", "| Measure | Count |", "| --- | ---: |"]
    for key, value in s.items():
        if isinstance(value, int):
            lines.append(f"| {key} | {value} |")
    for group in ("annotation_counts", "prior_review_counts"):
        for key, value in s[group].items():
            lines.append(f"| {group}: {key} | {value} |")
    lines += ["", "## Every coverage address", "",
              "Reference availability does not imply usable or correct decompilation. Source locations below are candidate claims; JSON also retains every incidental address reference. All current audit statuses are pending revalidation.", "",
              "| Address | Annotation | Prior review | IDA C / ASM / Ghidra | Candidate claim locations |",
              "| --- | --- | --- | --- | --- |"]
    for row in doc["functions"]:
        refs = row["references"]
        availability = " / ".join("yes" if yes else "missing" for yes in (
            refs["ida_c"]["available"], refs["ida_asm"]["available"],
            any(item["available"] for item in refs["ghidra"])))
        claims = "; ".join(link(item["path"], item["line"]) for item in row["source_occurrences"]
                           if item["kind"] != "address_reference") or "none; inspect references"
        lines.append(f"| `{row['address']}` | {row['annotation']['status']} | {row['prior_review']['status']} | {availability} | {claims} |")
    lines += ["", "## Separate file audit scope", "",
              "Every file below remains pending file review, including files whose addresses have historical reviews. SHA-256 hashes are in JSON. Zero marker candidates does not remove a file from scope.", "",
              "| File | Lines | Candidate addresses |", "| --- | ---: | ---: |"]
    for row in doc["file_audit_scope"]:
        lines.append(f"| {link(row['path'])} | {row['lines']} | {len(row['candidate_claim_addresses'])} |")
    lines += ["", "## IDA-only boundary review", "",
              "These are outside the coverage union. They may be runtime/library functions or reflect different function boundaries; listing them makes no new recovery or equivalence claim.", "",
              "| Address | IDA C | IDA ASM |", "| --- | --- | --- |"]
    for row in doc["ida_boundary_review_candidates"]:
        refs = row["references"]
        locations = [link(refs[key]["path"], refs[key]["line_start"]) if refs[key]["available"] else "missing"
                     for key in ("ida_c", "ida_asm")]
        lines.append(f"| `{row['address']}` | {' | '.join(locations)} |")
    return "\n".join(lines) + "\n"


def output_files(document):
    return {"inventory.json": json.dumps(document, indent=2, ensure_ascii=False) + "\n",
            "inventory.md": render_markdown(document)}


def check_outputs(directory, outputs):
    return [name for name, content in outputs.items()
            if not (directory / name).is_file() or (directory / name).read_text() != content]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    mode = parser.add_mutually_exclusive_group(required=True)
    mode.add_argument("--write", action="store_true", help="write deterministic JSON and Markdown")
    mode.add_argument("--check", action="store_true", help="fail on stale output or invalid scope")
    args = parser.parse_args()
    try:
        document = generate()
        outputs = output_files(document)
        directory = REPOSITORY / "matching2/docs/audit"
        if args.write:
            directory.mkdir(parents=True, exist_ok=True)
            for name, content in outputs.items():
                (directory / name).write_text(content)
        else:
            stale = check_outputs(directory, outputs)
            if stale:
                raise ValueError(f"stale audit inventory: {', '.join(stale)}; run audit_inventory.py --write")
    except (ValueError, OSError, KeyError) as error:
        parser.exit(1, f"audit inventory: {error}\n")
    print(json.dumps(document["summary"], sort_keys=True))


if __name__ == "__main__":
    main()
