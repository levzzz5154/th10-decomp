#!/usr/bin/env python3
"""Generate the address-to-source registry for raw Ghidra functions."""

import sys
from pathlib import Path

if __package__ in (None, ""):
    sys.path.insert(0, str(Path(__file__).resolve().parents[3]))


import argparse
import csv
import json
from collections import Counter

from matching2.tools.runtime import coverage_report


ROOT = Path(__file__).resolve().parents[2]
REPOSITORY = ROOT.parent
GHIDRA_ROOT = REPOSITORY / "decompiled" / "ghidra_raw"
INDEX = GHIDRA_ROOT / "index.tsv"
REGISTRY = ROOT / "function_registry.json"


def read_ghidra_index():
    with INDEX.open(newline="") as stream:
        rows = list(csv.DictReader(stream, delimiter="\t"))

    entries = []
    seen = set()
    for row in rows:
        address = int(row["address"], 16)
        if address in seen:
            raise ValueError("duplicate Ghidra address 0x{:08X}".format(address))
        seen.add(address)

        raw_path = GHIDRA_ROOT / row["file"]
        if row["status"] == "ok" and not raw_path.is_file():
            raise FileNotFoundError(raw_path)
        entries.append((address, row))
    return entries


def generate():
    coverage = {
        int(entry["address"], 16): entry
        for entry in coverage_report.generate()["functions"]
    }
    functions = []

    for address, row in sorted(read_ghidra_index()):
        recovered = coverage.get(address)
        status = recovered["status"] if recovered else "unrecovered"
        source = recovered["source"] if recovered else "unrecovered"
        entry = {
            "address": "0x{:08X}".format(address),
            "tracking_symbol": row["tracking_name"],
            "ghidra_symbol": row["ghidra_name"],
            "size": int(row["size"]) if row["size"] else None,
            "raw_status": row["status"],
            "raw_source": "decompiled/ghidra_raw/{}".format(row["file"]),
            "recovery_status": status,
            "promoted_source": None if source == "unrecovered" else source,
        }
        if row["detail"]:
            entry["raw_detail"] = row["detail"]
        if recovered and "blocker" in recovered:
            entry["blocker"] = recovered["blocker"]
        if recovered and "overlay_object" in recovered:
            entry["overlay"] = {
                "object": recovered["overlay_object"],
                "symbol": recovered["overlay_symbol"],
            }
        functions.append(entry)

    counts = Counter(entry["recovery_status"] for entry in functions)
    return {
        "schema_version": 1,
        "sources": {
            "ghidra_index": "decompiled/ghidra_raw/index.tsv",
            "recovery_ledger": "matching2/coverage.json (generated in memory)",
        },
        "summary": {
            "function_count": len(functions),
            "by_recovery_status": dict(sorted(counts.items())),
        },
        "functions": functions,
    }


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--write", action="store_true",
                        help="replace function_registry.json")
    parser.add_argument("--check", action="store_true",
                        help="fail when function_registry.json is stale")
    args = parser.parse_args()

    document = generate()
    encoded = json.dumps(document, indent=2) + "\n"
    if args.check and (not REGISTRY.exists() or REGISTRY.read_text() != encoded):
        raise SystemExit(
            "function_registry.json is stale; run function_registry.py --write")
    if args.write:
        REGISTRY.write_text(encoded)

    print("function registry: {} Ghidra exports".format(
        document["summary"]["function_count"]))
    for status, count in document["summary"]["by_recovery_status"].items():
        print("  {}: {}".format(status, count))


if __name__ == "__main__":
    main()
