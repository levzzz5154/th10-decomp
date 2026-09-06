#!/usr/bin/env python3
"""Build the exhaustive semantic-audit inventory and file-level partitions.

The coverage ledger is the authority for current status/source ownership.  This
report intentionally treats exact function addresses as the unit of evidence:
reviewing one function in a translation unit does not mark its neighbors done.
"""

from __future__ import annotations

import argparse
import json
from collections import defaultdict
from pathlib import Path


ROOT = Path(__file__).resolve().parent.parent
LEDGER = ROOT / "coverage.json"
MANIFEST = ROOT / "docs" / "semantic_exhaustive_audit_manifest.md"
JSON_REPORT = ROOT / "docs" / "semantic_exhaustive_audit_manifest.json"

# Exact-address evidence already recorded in docs/semantic_spot_audit.md.
# The three now marked partial remain in the checked set: the audit established
# why their former semantic credit was too broad, and this pass must not count
# that work as a review of any neighboring function in the same file.
KNOWN_CHECKED = {
    0x0040BD80: "docs/semantic_spot_audit.md: EndingScript_Update",
    0x004250B0: "docs/semantic_spot_audit.md: player_front::UpdatePlayer",
    0x0044A5F0: "docs/semantic_spot_audit.md: input_final::Poll",
    0x0042B9C0: "docs/semantic_spot_audit.md: ScorePopup_Enqueue",
    0x00412AC0: "docs/semantic_spot_audit.md: Trajectory_Evaluate2D",
}

GROUPS = ("coordinator", "ending", "player")


def read_entries():
    document = json.loads(LEDGER.read_text())
    return document["functions"]


def partition(entries):
    """Assign whole files greedily while balancing count and retail bytes."""
    grouped = defaultdict(list)
    for entry in entries:
        grouped[entry["source"]].append(entry)

    totals = {group: {"functions": 0, "bytes": 0, "files": []}
              for group in GROUPS}
    # Largest files first avoids putting the three large recovery leaves in one
    # bucket.  The score normalizes both dimensions before choosing a bucket.
    files = sorted(grouped.items(),
                   key=lambda item: (-len(item[1]),
                                     -sum(x.get("size") or 0 for x in item[1]),
                                     item[0]))
    all_count = len(entries)
    all_bytes = sum(x.get("size") or 0 for x in entries)
    for source, values in files:
        count = len(values)
        size = sum(x.get("size") or 0 for x in values)
        chosen = min(
            GROUPS,
            key=lambda group: (
                totals[group]["functions"] / all_count
                + totals[group]["bytes"] / all_bytes,
                totals[group]["functions"],
                totals[group]["bytes"],
                group,
            ),
        )
        totals[chosen]["functions"] += count
        totals[chosen]["bytes"] += size
        totals[chosen]["files"].append(source)

    result = {}
    for group in GROUPS:
        result[group] = {
            "summary": {
                "files": len(totals[group]["files"]),
                "functions": totals[group]["functions"],
                "retail_bytes": totals[group]["bytes"],
            },
            "files": {},
        }
        for source in sorted(totals[group]["files"]):
            result[group]["files"][source] = sorted(
                grouped[source], key=lambda x: int(x["address"], 16))
    return result


def build_document():
    all_entries = read_entries()
    semantic = [entry for entry in all_entries if entry["status"] == "semantic"]
    remaining = [entry for entry in semantic
                 if int(entry["address"], 16) not in KNOWN_CHECKED]
    checked = [entry for entry in semantic
               if int(entry["address"], 16) in KNOWN_CHECKED]
    return {
        "schema_version": 1,
        "ledger": "coverage.json",
        "semantic_total": len(semantic),
        "known_checked_total": len(KNOWN_CHECKED),
        "known_checked_semantic_total": len(checked),
        "remaining_total": len(remaining),
        "known_checked": [
            {"address": "0x{:08X}".format(address), "evidence": evidence}
            for address, evidence in sorted(KNOWN_CHECKED.items())
        ],
        "evidence_criteria": [
            "Inspect the exact address in local IDA pseudocode and disassembly.",
            "Inspect the matching raw Ghidra export; record corruption or missing data.",
            "Inspect the promoted source body and its host contract/callbacks.",
            "Compare control flow, field offsets, constants, ownership, and error paths.",
            "Run an existing focused test when it exercises the exact address; do not treat a self-authored test as retail proof.",
            "Classify only the reviewed address; neighboring functions in the same file remain unchecked.",
        ],
        "partition_policy": (
            "Whole source files are assigned exactly once. Greedy assignment balances "
            "semantic-function count and tracked retail bytes; each agent records "
            "address-level verdicts in a distinct report."
        ),
        "groups": partition(remaining),
        "excluded_statuses": {
            "partial": "Not part of the currently semantic audit inventory; retain explicit blockers.",
            "researched": "Not semantic credit; retain research provenance and limitations.",
            "unrecovered": "No promoted implementation to audit; retain as unresolved.",
        },
    }


def markdown(document):
    lines = [
        "# Exhaustive semantic implementation audit manifest",
        "",
        "Generated from `coverage.json` on 2026-09-05. The ledger currently has "
        f"**{document['semantic_total']} semantic addresses**; "
        f"**{document['remaining_total']} remain in this pass** after "
        f"{document['known_checked_total']} exact-address reviews "
        f"({document['known_checked_semantic_total']} were still semantic in the "
        "current ledger). The unit of "
        "completion is an address, not a translation unit: a checked function "
        "does not clear its neighbors. See the [consolidated audit status]"
        "(semantic_audit_summary.md) and [deduplicated address ledger]"
        "(semantic_audit_summary.json) for the current bounded-pass results.",
        "",
        "## Evidence criteria",
        "",
    ]
    lines.extend(f"- {criterion}" for criterion in document["evidence_criteria"])
    lines.extend([
        "",
        "## Previously checked exact addresses",
        "",
        "| Address | Evidence |",
        "| --- | --- |",
    ])
    lines.extend(
        f"| `{item['address']}` | {item['evidence']} |"
        for item in document["known_checked"])
    lines.extend([
        "",
        "## Nonsemantic statuses excluded from this pass",
        "",
        "Partial, researched, and unrecovered entries remain visible in the "
        "ledger but are excluded from the semantic implementation inventory. "
        "Their blockers are not silently converted into green audit results.",
        "",
        "## Nonoverlapping agent partitions",
        "",
        "Whole source files belong to one group only. Reports must preserve the "
        "address list below and add one verdict/evidence row per address.",
        "",
    ])
    for group, payload in document["groups"].items():
        summary = payload["summary"]
        lines.extend([
            f"### {group}",
            "",
            f"{summary['files']} files, {summary['functions']} addresses, "
            f"{summary['retail_bytes']} tracked retail bytes.",
            "",
        ])
        for source, entries in payload["files"].items():
            addresses = ", ".join(f"`{entry['address']}`" for entry in entries)
            lines.append(f"- `{source}` ({len(entries)}): {addresses}")
        lines.append("")
    return "\n".join(lines)


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--write", action="store_true")
    parser.add_argument("--check", action="store_true")
    args = parser.parse_args()
    document = build_document()
    encoded = json.dumps(document, indent=2) + "\n"
    rendered = markdown(document)
    if args.check:
        if not JSON_REPORT.exists() or JSON_REPORT.read_text() != encoded:
            raise SystemExit("semantic audit JSON manifest is stale; run --write")
        if not MANIFEST.exists() or MANIFEST.read_text() != rendered:
            raise SystemExit("semantic audit markdown manifest is stale; run --write")
    if args.write:
        JSON_REPORT.write_text(encoded)
        MANIFEST.write_text(rendered)
    print("semantic audit inventory: {} semantic, {} checked, {} remaining".format(
        document["semantic_total"], document["known_checked_total"],
        document["remaining_total"]))
    for group, payload in document["groups"].items():
        summary = payload["summary"]
        print("  {}: {} files, {} addresses, {} bytes".format(
            group, summary["files"], summary["functions"],
            summary["retail_bytes"]))


if __name__ == "__main__":
    main()
