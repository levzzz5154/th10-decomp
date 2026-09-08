#!/usr/bin/env python3
"""Generate and summarize matching2 coverage from the tracked function set."""

import argparse
import csv
import json
import re
from collections import Counter, defaultdict
from pathlib import Path


ROOT = Path(__file__).resolve().parent.parent
REPOSITORY = ROOT.parent
INDEX = REPOSITORY / "decompiled" / "ghidra_raw" / "index.tsv"
HISTORICAL_OVERLAYS = ROOT / "data" / "historical_overlays.json"
LEDGER = ROOT / "coverage.json"
ADDRESS = re.compile(r"0x(004[0-9A-Fa-f]{5})")

# These functions have readable work in matching2, but the source itself
# documents that only part of the retail function has been recovered.
PARTIAL = {
    0x0040E770: "Extended ECL dispatch has unsupported movement, sound, cleanup, and state-mixer opcodes; other paths still require retail comparison.",
    0x0040BD80: "Ending-script waits, float timekeeping, and opcode-12 stream ownership are modeled through a host adapter; retail text/ANM/timer globals and full stream integration remain unrecovered.",
    0x004250B0: "Player update exposes a typed movement/control slice, but the retail API has separate cardinal/diagonal speeds, gated slow-age updates, and omitted orbit/trail/sprite transitions.",
    0x0044A5F0: "Input state tail and fixed keyboard/DirectInput acquisition masks are covered, but retail global gates, joystick adapter dispatch, and per-player state ownership remain outside the host contract.",
}

# Address mentions matching these entries describe a known dependency rather
# than a readable implementation in the named translation unit.
RESEARCHED = {}

# Resolve ambiguous address mentions to the actual implementation owner.
SOURCE_OVERRIDES = {0x0040E770: "src/script/ecl_vm.cpp"}

SIZE_BANDS = (
    ("tiny", 0, 64),
    ("small", 64, 256),
    ("medium", 256, 1024),
    ("large", 1024, None),
)


def coverage_summary(entries):
    implemented_statuses = {"semantic"}
    by_status = {}
    for status in ("semantic", "partial", "researched", "unrecovered"):
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
    document = json.loads(HISTORICAL_OVERLAYS.read_text())
    return {int(row["address"], 16): (row["object"], row["symbol"])
            for row in document["entries"]}


def source_annotations():
    mentions = defaultdict(set)
    semantic = defaultdict(set)
    headers = defaultdict(set)  # impl markers: '// 0x004XXXXX' at line start
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
            # Address headers in matching2 were emitted by reconstruction
            # agents as implementation markers, not as incidental references.
            is_function_header = bool(re.match(
                r"//\s*(?:functions?\s*:\s*)?0x004[0-9a-f]{5}", stripped))
            if is_function_header:
                for address in addresses:
                    headers[address].add(relative)
            is_semantic = is_function_header or any(
                phrase in stripped for phrase in semantic_phrases)
            if is_semantic:
                for address in addresses:
                    semantic[address].add(relative)
    return mentions, semantic, headers


def generate():
    tracked = tracked_functions()
    overlays = overlay_entries()
    mentions, semantic, headers = source_annotations()
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
            # Impl-file precedence: a '// 0x004XXXXX' function-header claim
            # (the implementation marker) wins over mention-style claims
            # from other files that merely cite the address in prose.
            claimants = (headers[address] if address in headers
                         else semantic[address])
            entry["source"] = sorted(claimants)[0]
        if address in RESEARCHED:
            entry["status"] = "researched"
            entry["blocker"] = RESEARCHED[address]
        if address in PARTIAL:
            entry["status"] = "partial"
            entry["blocker"] = PARTIAL[address]
        if address in SOURCE_OVERRIDES:
            entry["source"] = SOURCE_OVERRIDES[address]
        entries.append(entry)

    return {
        "schema_version": 3,
        "target": {
            "executable_sha256":
                "2f14760b6fbbf57549541583283badb9a19a4222b90f0a146d5aa17f01dc9040",
            "compiler": "PE32 C++17 (MinGW); retail reference: MSVC 7.1",
            "tracked_function_source": "decompiled/ghidra_raw/index.tsv",
            "inventory_policy": "union of Ghidra index and historical overlay addresses (inventory only)",
        },
        "coverage_summary": coverage_summary(entries),
        "evidence_limit": "Semantic status is inferred from source annotations, not proof of behavioral parity. Historical overlay membership never promotes recovery status.",
        "verified_overlay_summary": {
            "function_count": 0,
            "pure_cpp_function_count": 0,
            "compared_bytes": None,
            "source": "legacy overlay inventory; no current exact-match claim",
        },
        "functions": entries,
    }


def print_summary(document):
    entries = document["functions"]
    counts = Counter(entry["status"] for entry in entries)
    implemented = counts["semantic"]
    remaining = len(entries) - implemented
    print("coverage ledger ({} tracked functions):".format(len(entries)))
    for status in ("semantic", "partial", "researched", "unrecovered"):
        print("  {}: {}".format(status, counts[status]))
    print("  readable implementations: {} ({:.1f}%)".format(
        implemented, implemented * 100.0 / len(entries)))
    print("  not fully implemented: {}".format(remaining))
    coverage = document["coverage_summary"]
    semantic = coverage["by_status"]["semantic"]
    print("  semantic bytes: {} across {} functions".format(
        semantic["retail_bytes"], semantic["function_count"]))
    print("  size-band progress:")
    for band in coverage["size_bands"]:
        print("    {}: {}/{} functions, {}/{} bytes".format(
            band["name"], band["implemented_functions"],
            band["tracked_functions"], band["implemented_bytes"],
            band["tracked_bytes"]))
    summary = document["verified_overlay_summary"]
    if summary["compared_bytes"] is None:
        print("  verified overlays: {} functions (no current exact-match evidence)".format(
            summary["function_count"]))
        print("  pure-C++ overlays: {} functions".format(
            summary.get("pure_cpp_function_count", 0)))
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
