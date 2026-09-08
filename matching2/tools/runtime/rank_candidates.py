#!/usr/bin/env python3
"""Rank bounded semantic-recovery candidates from repository evidence."""

import argparse
import csv
import json
import re
from pathlib import Path


ROOT = Path(__file__).resolve().parents[2]
REPOSITORY = ROOT.parent
INDEX = REPOSITORY / "decompiled" / "ghidra_raw" / "index.tsv"
LEDGER = ROOT / "coverage.json"
MATCHING_ASM = REPOSITORY / "matching" / "src" / "nasm"
CALL = re.compile(r"\bFUN_([0-9A-Fa-f]{8})\s*\(")


def load_rows():
    with INDEX.open(newline="") as stream:
        return list(csv.DictReader(stream, delimiter="\t"))


def load_ledger():
    return {int(entry["address"], 16): entry
            for entry in json.loads(LEDGER.read_text())["functions"]}


def source_calls(path):
    if not path.exists():
        return set()
    return {int(address, 16) for address in CALL.findall(
        path.read_text(errors="replace"))}


def size_score(size):
    if size <= 64:
        return 5
    if size <= 256:
        return 4
    if size <= 512:
        return 3
    if size <= 1024:
        return 1
    return 0


def rank(rows, ledger):
    recovered = sorted(address for address, entry in ledger.items()
                       if entry["status"] in ("semantic", "exact-overlay"))
    asm_addresses = {
        int(match.group(1), 16)
        for path in MATCHING_ASM.glob("*.asm")
        if (match := re.search(r"([0-9A-Fa-f]{8})", path.stem))
    }
    test_driver = (ROOT / "test.sh").read_text()
    tested_sources = set(re.findall(
        r'\$ROOT/src/(?:[A-Za-z0-9_]+/)*([A-Za-z0-9_]+)\.cpp',
        test_driver))
    results = []
    for row in rows:
        address = int(row["address"], 16)
        if ledger.get(address, {}).get("status") != "unrecovered":
            continue
        size = int(row["size"])
        calls = source_calls(INDEX.parent / row["file"])
        calls.discard(address)
        unresolved = sum(ledger.get(call, {}).get("status", "unrecovered")
                         not in ("semantic", "exact-overlay") for call in calls)
        nearby = sum(abs(address - other) <= 0x1000 for other in recovered)
        has_asm = address in asm_addresses
        # Existing source and tests near the address are useful layout/harness
        # evidence. The nearest recovered source supplies the subsystem hint.
        nearest = min(recovered, key=lambda other: abs(address - other))
        source = ledger[nearest]["source"]
        subsystem = Path(source).stem
        harness = subsystem in tested_sources
        leaf = not calls
        score = (size_score(size) + min(nearby, 5) + (3 if leaf else 0)
                 + (2 if has_asm else 0) + (2 if harness else 0)
                 - min(unresolved, 6))
        results.append({
            "address": address, "symbol": row["tracking_name"],
            "size": size, "score": score, "unresolved": unresolved,
            "leaf": leaf, "nearby": nearby, "assembly": has_asm,
            "subsystem": subsystem, "harness": harness,
        })
    return sorted(results, key=lambda item: (-item["score"], item["size"],
                                              item["address"]))


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--limit", type=int, default=30)
    parser.add_argument("--subsystem",
                        help="filter by inferred nearest-source subsystem")
    args = parser.parse_args()
    candidates = rank(load_rows(), load_ledger())
    if args.subsystem:
        needle = args.subsystem.lower()
        candidates = [item for item in candidates
                      if needle in item["subsystem"].lower()]
    print("score address    bytes deps leaf asm test nearby subsystem symbol")
    for item in candidates[:args.limit]:
        print("{score:5d} 0x{address:08X} {size:5d} {unresolved:4d} "
              "{leaf!s:4s} {assembly!s:3s} {harness!s:4s} {nearby:6d} "
              "{subsystem} {symbol}".format(**item))


if __name__ == "__main__":
    main()
