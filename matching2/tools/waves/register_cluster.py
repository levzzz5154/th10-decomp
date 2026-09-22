#!/usr/bin/env python3
"""Register a native-LTCG cluster in the maintained manifest, atomically.

Several agents run in parallel and all of them have to record a cluster in
``matching2/msvc/regions.json``. A plain read-modify-write race loses one of
them, so every update goes through this tool: it takes an exclusive lock, re-reads
the manifest, applies only the records that concern the layout's declared
sources, and writes it back with ``os.replace``.

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
sys.path.insert(0, str(ROOT))

from matching2.tools.matching.ltcg_cluster import LTCGClusterError, load_cluster

def _layout_sources(layout):
    """Return the primary and additional source names declared by a layout."""
    return [layout["source"], *layout.get("additional_sources", [])]


def _function_source(layout, function):
    """Use a per-function source override, defaulting to the primary source."""
    source = function.get("source", layout["source"])
    if source not in _layout_sources(layout):
        raise ValueError(f"function source is not declared by the cluster: {source}")
    return source

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
            try:
                function_source = _function_source(layout, function)
            except ValueError as error:
                return str(error), manifest, []
            region = by_address.get(address)
            if region is None:
                return f"no manifest region at {address:#x}", manifest, []
            if region["source"] != function_source:
                return (f"region {address:#x} is owned by {region['source']}, "
                        f"not {function_source}"), manifest, []
            if region["size"] != function["size"]:
                return (f"region {address:#x} size {region['size']} != "
                        f"layout size {function['size']}"), manifest, []
            changes.append((region, function))
        if not apply:
            return "", manifest, [(region["name"], function["symbol"]) for region, function in changes]
        for region, function in changes:
            if region["kind"] != "semantic":
                region["previous_record"] = {key: value for key, value in region.items()
                                             if key != "previous_record"}
            region["kind"] = "semantic"
            region["symbol"] = function["symbol"]
            region["name"] = ("semantic_" + function["name"] + "_%08x" % int(function["address"], 0))
            region.pop("requested_symbol", None)
        clusters = manifest["ltcg_clusters"]
        if layout_rel not in clusters:
            clusters.append(layout_rel)
        manifest["translation_units"] = sorted({region["source"] for region in manifest["regions"]})
        # A registration the loader rejects stops every unit in the project from
        # building, not just this one, so the candidate manifest is validated
        # before it is written.
        try:
            load_cluster(manifest_path.parent, layout_rel, manifest["regions"])
        except LTCGClusterError as error:
            return f"layout rejected by the loader: {error}", manifest, []
        temporary = manifest_path.with_suffix(".json.tmp")
        temporary.write_text(json.dumps(manifest, indent=2) + "\n")
        os.replace(temporary, manifest_path)
        return "", manifest, [(region["name"], function["symbol"]) for region, function in changes]


def unregister(manifest_path, layout_rel, apply):
    """Remove a cluster registration and return its region to assembly.

    An agent iterating on a cluster needs this: while a layout is registered but
    not yet exact, the project does not build, and every other agent's probe dies
    with it. Registering only on success, and unregistering on failure, keeps the
    tree usable for everyone else.
    """
    with open(manifest_path.with_suffix(".json.lock"), "w") as lock:
        fcntl.flock(lock, fcntl.LOCK_EX)
        manifest = json.loads(manifest_path.read_text())
        if layout_rel not in manifest["ltcg_clusters"]:
            return f"{layout_rel} is not registered", manifest
        path = manifest_path.parent / layout_rel
        sources = []
        if path.is_file():
            layout = json.loads(path.read_text())
            sources = _layout_sources(layout)
        manifest["ltcg_clusters"] = [item for item in manifest["ltcg_clusters"]
                                     if item != layout_rel]
        restored, unknown = [], []
        for region in manifest["regions"]:
            if region["kind"] != "semantic":
                continue
            if sources and region["source"] not in sources:
                continue
            # The registration rewrote the region's name and symbol, and the
            # original inline-assembly symbol cannot be recovered from them, so
            # the previous record is kept at registration time. Without it the
            # honest move is to refuse: inventing a name would leave a region no
            # unit defines.
            previous = region.pop("previous_record", None)
            if not previous:
                unknown.append(region["source"])
                continue
            region.update(previous)
            region.pop("requested_symbol", None)
            restored.append(region["source"])
        if unknown:
            return ("cannot unregister " + layout_rel + ": no recorded pre-registration "
                    "state for " + ", ".join(sorted(set(unknown)))), manifest
        if not apply:
            return "", manifest
        temporary = manifest_path.with_suffix(".json.tmp")
        temporary.write_text(json.dumps(manifest, indent=2) + "\n")
        os.replace(temporary, manifest_path)
    return "", manifest


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--project", type=Path, default=ROOT / "matching2/msvc")
    parser.add_argument("--layout", required=True)
    parser.add_argument("--apply", action="store_true")
    parser.add_argument("--unregister", action="store_true",
                        help="remove the registration and return its region to assembly")
    args = parser.parse_args()
    manifest_path = args.project.resolve() / "regions.json"
    if args.unregister:
        problem, manifest = unregister(manifest_path, args.layout, args.apply)
        if problem:
            print("refused: " + problem)
            return 1
        print(("unregistered " if args.apply else "would unregister ") + args.layout)
        if args.apply:
            print(f"ltcg_clusters: {len(manifest['ltcg_clusters'])} entries")
        return 0
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
