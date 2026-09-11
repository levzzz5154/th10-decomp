#!/usr/bin/env python3
"""Register a native-LTCG cluster in the maintained manifest, atomically.

Several agents run in parallel and all of them have to record a cluster in
``matching2/msvc/regions.json``. A plain read-modify-write race loses one of
them, so every update goes through this tool: it takes an exclusive lock, re-reads
the manifest, applies only the records that concern one source, and writes it
back with ``os.replace``.

Usage:
    python3 register_cluster.py --layout layout/ltcg/<name>.json --apply
    python3 register_cluster.py --layout layout/ltcg/<name>.json --unregister --apply
"""
from __future__ import annotations

import argparse
import fcntl
import json
import os
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[3]


def update(manifest_path, layout_rel, apply):
    """Apply the layout's functions to the manifest under an exclusive lock."""
    lock_path = manifest_path.with_suffix(".json.lock")
    layout = json.loads((manifest_path.parent / layout_rel).read_text())
    with open(lock_path, "w") as lock:
        fcntl.flock(lock, fcntl.LOCK_EX)
        manifest = json.loads(manifest_path.read_text())
        by_address = {int(region["address"], 0): region for region in manifest["regions"]}
        changes = []
        for function in layout["functions"]:
            address = int(function["address"], 0)
            region = by_address.get(address)
            if region is None:
                return f"no manifest region at {address:#x}", manifest, []
            if region["source"] != layout["source"]:
                return (f"region {address:#x} is owned by {region['source']}, "
                        f"not {layout['source']}"), manifest, []
            if region["size"] != function["size"]:
                return (f"region {address:#x} size {region['size']} != "
                        f"layout size {function['size']}"), manifest, []
            changes.append((region, function))
        if not apply:
            return "", manifest, [(region["name"], function["symbol"]) for region, function in changes]
        for region, function in changes:
            region["kind"] = "semantic"
            region["symbol"] = function["symbol"]
            region["name"] = ("semantic_" + function["name"] + "_%08x" % int(function["address"], 0))
            region.pop("requested_symbol", None)
        clusters = manifest["ltcg_clusters"]
        if layout_rel not in clusters:
            clusters.append(layout_rel)
        manifest["translation_units"] = sorted({region["source"] for region in manifest["regions"]})
        temporary = manifest_path.with_suffix(".json.tmp")
        temporary.write_text(json.dumps(manifest, indent=2) + "\n")
        os.replace(temporary, manifest_path)
        return "", manifest, [(region["name"], function["symbol"]) for region, function in changes]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--project", type=Path, default=ROOT / "matching2/msvc")
    parser.add_argument("--layout", required=True)
    parser.add_argument("--apply", action="store_true")
    args = parser.parse_args()
    manifest_path = args.project.resolve() / "regions.json"
    problem, manifest, records = update(manifest_path, args.layout, args.apply)
    if problem:
        print("refused: " + problem)
        return 1
    verb = "registered" if args.apply else "would register"
    for name, symbol in records:
        print(f"{verb} {name} as {symbol}")
    if args.apply:
        print(f"ltcg_clusters: {len(manifest['ltcg_clusters'])} entries")
    return 0


if __name__ == "__main__":
    sys.exit(main())
