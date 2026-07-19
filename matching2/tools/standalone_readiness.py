#!/usr/bin/env python3
"""Measure retail-code independence on the startup-to-title execution slice.

Unlike broad coverage, this report follows direct game-owned calls from a
milestone root set and treats every unrecovered reachable function as a hard
standalone blocker. Indirect scheduler callbacks that cannot be recovered
from raw pseudocode are represented by explicit additional roots.
"""

import argparse
import csv
import json
import re
from collections import Counter, defaultdict, deque
from pathlib import Path

import coverage_report


ROOT = Path(__file__).resolve().parent.parent
REPOSITORY = ROOT.parent
GHIDRA_ROOT = REPOSITORY / "decompiled" / "ghidra_raw"
INDEX = GHIDRA_ROOT / "index.tsv"
REPORT = ROOT / "standalone_readiness.json"

# GameMain owns initialization and the main loop. Title initialization is
# scheduled through a callback pointer, so it is an explicit second root.
MILESTONE = {
    "id": "startup_to_title",
    "description": "Launch the executable and initialize title.anm/title_v.anm",
    "roots": [
        {"address": "0x00438AD0", "role": "game entry (called by the CRT)"},
        {"address": "0x0042CAA0", "role": "title initializer (indirect callback root)"},
    ],
    "scope_note": (
        "Direct game-owned call closure plus the explicit title callback root. "
        "System DLL imports are host dependencies, not retail-code blockers."
    ),
}

INTEGRATION_GATES = {
    "retail_free_link_target": {
        "passed": False,
        "evidence": "build.sh produces a hybrid image from the retail executable",
    },
    "retail_free_executable_produced": {
        "passed": False,
        "evidence": "no independent executable artifact is built",
    },
    "startup_to_title_smoke_test": {
        "passed": False,
        "evidence": "no retail-free runtime exists to smoke-test",
    },
}

CALL = re.compile(r"\b((?:FUN_)?004[0-9A-Fa-f]{5}|[A-Za-z_]\w*)\s*\(")
DYNAMIC_CALL = re.compile(r"\(\*\*\(code \*\*\)")
IMPLEMENTED = {"semantic", "exact-overlay"}

# Address -> number of indirect call sites whose complete target set has been
# manually enumerated into the milestone roots/graph. Keep empty until an
# audit is backed by repository evidence.
AUDITED_DYNAMIC_SITES = {}


def read_inventory():
    inventory = {}
    names = {}
    with INDEX.open(newline="") as stream:
        for row in csv.DictReader(stream, delimiter="\t"):
            address = int(row["address"], 16)
            inventory[address] = row
            names[row["tracking_name"]] = address
            names[row["ghidra_name"]] = address
            names["FUN_{:08x}".format(address)] = address
            names["FUN_{:08X}".format(address)] = address
            names["{:08x}".format(address)] = address
            names["{:08X}".format(address)] = address
    return inventory, names


def read_edges(inventory, names):
    edges = defaultdict(set)
    dynamic_sites = {}
    for address, row in inventory.items():
        path = GHIDRA_ROOT / row["file"]
        if row["status"] != "ok" or not path.is_file():
            continue
        text = path.read_text(errors="replace")
        for token in CALL.findall(text):
            target = names.get(token)
            if target is not None and target != address:
                edges[address].add(target)
        dynamic_sites[address] = len(DYNAMIC_CALL.findall(text))
    return edges, dynamic_sites


def reachable_closure(roots, edges):
    distance = {address: 0 for address in roots}
    queue = deque(roots)
    while queue:
        caller = queue.popleft()
        for callee in edges.get(caller, ()):
            if callee not in distance:
                distance[callee] = distance[caller] + 1
                queue.append(callee)
    return distance


def blocker_impact(reachable, edges):
    reverse = defaultdict(set)
    for caller in reachable:
        for callee in edges.get(caller, ()):
            if callee in reachable:
                reverse[callee].add(caller)
    impact = {}
    for target in reachable:
        seen = set()
        queue = deque(reverse.get(target, ()))
        while queue:
            caller = queue.popleft()
            if caller in seen:
                continue
            seen.add(caller)
            queue.extend(reverse.get(caller, ()))
        impact[target] = len(seen)
    return impact


def generate():
    inventory, names = read_inventory()
    edges, dynamic_sites = read_edges(inventory, names)
    coverage = {
        int(entry["address"], 16): entry
        for entry in coverage_report.generate()["functions"]
    }
    roots = [int(root["address"], 16) for root in MILESTONE["roots"]]
    distance = reachable_closure(roots, edges)
    impact = blocker_impact(distance, edges)

    functions = []
    for address in sorted(distance):
        row = inventory[address]
        recovery = coverage.get(address, {})
        status = recovery.get("status", "unrecovered")
        size = int(row["size"]) if row["size"] else 0
        functions.append({
            "address": "0x{:08X}".format(address),
            "symbol": row["tracking_name"],
            "size": size,
            "distance_from_root": distance[address],
            "direct_internal_callees": len([
                callee for callee in edges.get(address, ()) if callee in distance
            ]),
            "dynamic_call_sites": dynamic_sites.get(address, 0),
            "recovery_status": status,
            "source_ready": status in IMPLEMENTED,
            "source": recovery.get("source", "unrecovered"),
        })

    ready = [entry for entry in functions if entry["source_ready"]]
    blockers = [entry for entry in functions if not entry["source_ready"]]
    total_bytes = sum(entry["size"] for entry in functions)
    ready_bytes = sum(entry["size"] for entry in ready)
    blocker_rows = []
    for entry in blockers:
        address = int(entry["address"], 16)
        blocker_rows.append({
            **entry,
            "reachable_callers": impact[address],
            "impact_score": impact[address] * 100000 + entry["size"],
        })
    blocker_rows.sort(key=lambda entry: (-entry["impact_score"],
                                         entry["address"]))

    function_percent = len(ready) * 100.0 / len(functions) if functions else 0
    byte_percent = ready_bytes * 100.0 / total_bytes if total_bytes else 0
    dynamic_total = sum(entry["dynamic_call_sites"] for entry in functions)
    dynamic_audited = sum(min(dynamic_sites.get(address, 0), count)
                          for address, count in AUDITED_DYNAMIC_SITES.items()
                          if address in distance)
    dynamic_unaudited = dynamic_total - dynamic_audited
    return {
        "schema_version": 1,
        "metric": {
            "name": "standalone startup-to-title readiness",
            "definition": (
                "A reachable function is source-ready only when its recovery status "
                "is semantic or exact-overlay; the score is reported by both "
                "function count and retail byte weight. Standalone completion "
                "requires zero reachable retail blockers, zero unaudited "
                "indirect call sites, and every integration gate to pass."
            ),
            "milestone": MILESTONE,
        },
        "summary": {
            "reachable_functions": len(functions),
            "source_ready_functions": len(ready),
            "blocking_functions": len(blockers),
            "source_function_readiness_percent": round(function_percent, 2),
            "reachable_retail_bytes": total_bytes,
            "source_ready_retail_bytes": ready_bytes,
            "source_byte_readiness_percent": round(byte_percent, 2),
            "dynamic_call_sites": dynamic_total,
            "audited_dynamic_call_sites": dynamic_audited,
            "unaudited_dynamic_call_sites": dynamic_unaudited,
            "standalone_ready": (not blockers and dynamic_unaudited == 0 and
                                 all(gate["passed"]
                                     for gate in INTEGRATION_GATES.values())),
            "by_recovery_status": dict(sorted(Counter(
                entry["recovery_status"] for entry in functions).items())),
        },
        "integration_gates": INTEGRATION_GATES,
        "top_blockers": blocker_rows[:25],
        "functions": functions,
    }


def print_summary(document):
    summary = document["summary"]
    print("standalone startup-to-title readiness:")
    print("  source function readiness: {}/{} ({:.2f}%)".format(
        summary["source_ready_functions"], summary["reachable_functions"],
        summary["source_function_readiness_percent"]))
    print("  source byte readiness: {}/{} ({:.2f}%)".format(
        summary["source_ready_retail_bytes"], summary["reachable_retail_bytes"],
        summary["source_byte_readiness_percent"]))
    print("  retail blockers: {}".format(summary["blocking_functions"]))
    print("  indirect call sites: {} total, {} audited, {} requiring audit".format(
        summary["dynamic_call_sites"], summary["audited_dynamic_call_sites"],
        summary["unaudited_dynamic_call_sites"]))
    print("  milestone runnable without retail code: {}".format(
        "yes" if summary["standalone_ready"] else "no"))
    print("  integration gates:")
    for name, gate in document["integration_gates"].items():
        print("    {}: {}".format(name, "pass" if gate["passed"] else "fail"))
    if document["top_blockers"]:
        print("  highest-impact blockers:")
        for entry in document["top_blockers"][:10]:
            print("    {} {:<28} {} bytes, {} reachable callers".format(
                entry["address"], entry["symbol"][:28], entry["size"],
                entry["reachable_callers"]))


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--write", action="store_true")
    parser.add_argument("--check", action="store_true")
    args = parser.parse_args()
    document = generate()
    encoded = json.dumps(document, indent=2) + "\n"
    if args.check and (not REPORT.exists() or REPORT.read_text() != encoded):
        raise SystemExit(
            "standalone_readiness.json is stale; run standalone_readiness.py --write")
    if args.write:
        REPORT.write_text(encoded)
    print_summary(document)


if __name__ == "__main__":
    main()
