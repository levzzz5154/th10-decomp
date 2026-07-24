#!/usr/bin/env python3
"""Generate and summarize matching2 coverage from the tracked function set."""

import argparse
import ast
import csv
import json
import re
from collections import Counter, defaultdict
from pathlib import Path


ROOT = Path(__file__).resolve().parent.parent
REPOSITORY = ROOT.parent
INDEX = REPOSITORY / "decompiled" / "ghidra_raw" / "index.tsv"
HYBRID_BUILDER = ROOT / "tools" / "build_hybrid.py"
LEDGER = ROOT / "coverage.json"
ADDRESS = re.compile(r"0x(004[0-9A-Fa-f]{5})")

# These functions have readable work in matching2, but the source itself
# documents that only part of the retail function has been recovered.
PARTIAL = {
    0x00418D00: "Remaining code-generation mismatch",
    0x00445900: "Game-state matrix/global initialization remains incomplete",
    0x0040E770: "All 122 retail opcodes dispatched; complex bodies (D3DX init / FUN_0041c510 state machine) remain as documented stubs",
}

# Address mentions matching these entries describe a known dependency rather
# than a readable implementation in the named translation unit.
RESEARCHED = {}

SIZE_BANDS = (
    ("tiny", 0, 64),
    ("small", 64, 256),
    ("medium", 256, 1024),
    ("large", 1024, None),
)


def coverage_summary(entries):
    implemented_statuses = {"semantic", "exact-overlay"}
    by_status = {}
    for status in ("semantic", "exact-overlay"):
        selected = [entry for entry in entries if entry["status"] == status]
        by_status[status] = {
            "function_count": len(selected),
            "retail_bytes": sum(entry["size"] or 0 for entry in selected),
        }

    bands = []
    for name, minimum, maximum in SIZE_BANDS:
        selected = [entry for entry in entries
                    if entry["size"] is not None
                    and entry["size"] >= minimum
                    and (maximum is None or entry["size"] < maximum)]
        implemented = [entry for entry in selected
                       if entry["status"] in implemented_statuses]
        bands.append({
            "name": name,
            "minimum_size": minimum,
            "maximum_size_exclusive": maximum,
            "tracked_functions": len(selected),
            "implemented_functions": len(implemented),
            "tracked_bytes": sum(entry["size"] for entry in selected),
            "implemented_bytes": sum(entry["size"] for entry in implemented),
        })
    return {"by_status": by_status, "size_bands": bands}


def tracked_functions():
    with INDEX.open(newline="") as stream:
        rows = csv.DictReader(stream, delimiter="\t")
        return {int(row["address"], 16): row for row in rows}


def overlay_entries():
    tree = ast.parse(HYBRID_BUILDER.read_text(), filename=str(HYBRID_BUILDER))
    for node in tree.body:
        if isinstance(node, ast.Assign):
            names = [target.id for target in node.targets
                     if isinstance(target, ast.Name)]
            if "OVERLAYS" in names:
                values = ast.literal_eval(node.value)
                return {address: (object_name, symbol)
                        for object_name, symbol, address in values}
    raise RuntimeError("OVERLAYS tuple not found in build_hybrid.py")


def source_annotations():
    mentions = defaultdict(set)
    semantic = defaultdict(set)
    semantic_phrases = (
        "semantic reconstruction", "clean reconstruction",
        "readable reconstruction",
        "readable frame", "conventional-abi form", "backed form",
        "corresponding to", "retail address", "retail function",
    )

    for path in sorted((ROOT / "src").rglob("*.cpp")):
        relative = str(path.relative_to(ROOT))
        for line in path.read_text(errors="replace").splitlines():
            addresses = [int(match, 16) for match in ADDRESS.findall(line)]
            if not addresses:
                continue
            mentions.update((address, mentions[address] | {relative})
                            for address in addresses)
            stripped = line.strip().lower()
            # An address header is useful provenance, but is not evidence that
            # the entire retail function has been reconstructed.
            is_semantic = any(phrase in stripped
                              for phrase in semantic_phrases)
            if is_semantic:
                for address in addresses:
                    semantic[address].add(relative)
    return mentions, semantic


def generate():
    tracked = tracked_functions()
    overlays = overlay_entries()
    mentions, semantic = source_annotations()
    entries = []

    for address in sorted(set(tracked) | set(overlays)):
        row = tracked.get(address)
        entry = {
            "address": "0x{:08X}".format(address),
            "symbol": (row["tracking_name"] if row else overlays[address][1]),
            "size": (int(row["size"]) if row else None),
            "status": "unrecovered",
            "source": "unrecovered",
        }
        if address in mentions:
            entry["status"] = "researched"
            entry["source"] = sorted(mentions[address])[0]
        if address in semantic:
            entry["status"] = "semantic"
            entry["source"] = sorted(semantic[address])[0]
        if address in RESEARCHED:
            entry["status"] = "researched"
            entry["blocker"] = RESEARCHED[address]
        if address in PARTIAL:
            entry["status"] = "partial"
            entry["blocker"] = PARTIAL[address]
        if address in overlays:
            entry["status"] = "exact-overlay"
            object_name, symbol = overlays[address]
            if entry["source"] == "unrecovered":
                candidates = list((ROOT / "src").rglob(
                    Path(object_name).stem + ".cpp"))
                if len(candidates) == 1:
                    entry["source"] = str(candidates[0].relative_to(ROOT))
            entry["overlay_object"] = object_name
            entry["overlay_symbol"] = symbol
        entries.append(entry)

    return {
        "schema_version": 3,
        "target": {
            "executable_sha256":
                "2f14760b6fbbf57549541583283badb9a19a4222b90f0a146d5aa17f01dc9040",
            "compiler": "MSVC 7.1",
            "tracked_function_source": "decompiled/ghidra_raw/index.tsv",
            "inventory_policy": "union of Ghidra index and verified overlays",
        },
        "coverage_summary": coverage_summary(entries),
        "verified_overlay_summary": {
            "function_count": len(overlays),
            # Byte totals belong to build output and are intentionally not
            # inferred from optional, untracked object files here.
            "compared_bytes": None,
            "source": "tools/build_hybrid.py",
        },
        "functions": entries,
    }


def print_summary(document):
    entries = document["functions"]
    counts = Counter(entry["status"] for entry in entries)
    implemented = counts["semantic"] + counts["exact-overlay"]
    remaining = len(entries) - implemented
    print("coverage ledger ({} tracked functions):".format(len(entries)))
    for status in ("exact-overlay", "semantic", "partial", "researched",
                   "unrecovered"):
        print("  {}: {}".format(status, counts[status]))
    print("  readable implementations: {} ({:.1f}%)".format(
        implemented, implemented * 100.0 / len(entries)))
    print("  not fully implemented: {}".format(remaining))
    coverage = document["coverage_summary"]
    semantic = coverage["by_status"]["semantic"]
    exact = coverage["by_status"]["exact-overlay"]
    print("  semantic bytes: {} across {} functions".format(
        semantic["retail_bytes"], semantic["function_count"]))
    print("  exact-overlay bytes: {} across {} functions".format(
        exact["retail_bytes"], exact["function_count"]))
    print("  size-band progress:")
    for band in coverage["size_bands"]:
        print("    {}: {}/{} functions, {}/{} bytes".format(
            band["name"], band["implemented_functions"],
            band["tracked_functions"], band["implemented_bytes"],
            band["tracked_bytes"]))
    summary = document["verified_overlay_summary"]
    if summary["compared_bytes"] is None:
        print("  verified overlays: {} functions (byte total is build-only)".format(
            summary["function_count"]))
    else:
        print("  verified overlays: {} functions, {} bytes".format(
            summary["function_count"], summary["compared_bytes"]))


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--write", action="store_true",
                        help="replace coverage.json with the generated ledger")
    parser.add_argument("--check", action="store_true",
                        help="fail when coverage.json is not freshly generated")
    args = parser.parse_args()

    document = generate()
    encoded = json.dumps(document, indent=2) + "\n"
    if args.check:
        if not LEDGER.exists() or LEDGER.read_text() != encoded:
            raise SystemExit("coverage.json is stale; run coverage_report.py --write")
    if args.write:
        LEDGER.write_text(encoded)
    print_summary(document)


if __name__ == "__main__":
    main()
