#!/usr/bin/env python3
"""Repair units an agent left half-converted, either completing them or reverting.

A conversion is two halves: the C++ body in the source, and the manifest region
naming the symbol the compiler emits. When an agent is interrupted between the
two, the manifest still expects the inline-assembly symbol, the unit stops
compiling, and the whole-image gate fails.

This tool closes that gap. For every unit that does not build, it compiles the
source, matches the functions the compiler emitted against the regions the unit
owns, and probes. A unit that comes back exact is written into the manifest; one
that does not is restored from its pristine copy. Nothing is trusted from an
agent report.

Usage:
    python3 repair_units.py                 # report only
    python3 repair_units.py --apply
"""
from __future__ import annotations

import argparse
import json
import shutil
import subprocess
import sys
from collections import defaultdict
from pathlib import Path

ROOT = Path(__file__).resolve().parents[3]
sys.path.insert(0, str(ROOT))

from matching2.tools.matching.probe import DEFAULT_PROJECT, defined_functions, probe_unit
from matching2.tools.matching.build_msvc import DEFAULT_TOOLKIT, compile_raw
from matching2.tools.matching.ltcg_cluster import load_clusters

WAVE = ROOT / "matching2/build/waves"


def pristine(source):
    """The newest backup of a source, if one exists."""
    for wave in (6, 5, 4, 3, 2, 1):
        candidate = WAVE / f"backup{wave}" / source
        if candidate.is_file():
            return candidate
    return None


def match_symbols(regions, defined):
    """Map each region that needs a new symbol to a function the object defines.

    A region whose current symbol the object still defines is untouched and needs
    no entry. A region whose symbol has gone (its body was converted) is matched
    by the address agents keep in the emitted name, or by the plain name; the
    leftovers of a unit that defines one function per region are matched in
    address order.
    """
    mapping, remaining = {}, set(defined)
    pending = []
    for region in sorted(regions, key=lambda item: int(item["address"], 0)):
        symbol = region["symbol"]
        if symbol in remaining:
            remaining.discard(symbol)
            continue
        pending.append(region)
    for region in pending:
        plain = region["symbol"].lstrip("_")
        address = "%08x" % int(region["address"], 0)
        hits = [name for name in remaining
                if name.lstrip("_") == plain or address in name.lower()]
        if len(hits) == 1:
            mapping[int(region["address"], 0)] = hits[0]
            remaining.discard(hits[0])
    unmatched = [region for region in pending
                 if int(region["address"], 0) not in mapping]
    if len(remaining) == len(unmatched) and unmatched:
        for region, name in zip(sorted(unmatched, key=lambda item: int(item["address"], 0)),
                                sorted(remaining)):
            mapping[int(region["address"], 0)] = name
    return mapping


from matching2.tools.common.project_paths import project_support
def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--project", type=Path, default=DEFAULT_PROJECT)
    parser.add_argument("--toolkit", type=Path, default=DEFAULT_TOOLKIT)
    parser.add_argument("--output", type=Path, default=WAVE / "repair")
    parser.add_argument("--apply", action="store_true")
    args = parser.parse_args()
    project = args.project.resolve()
    manifest_path = project_support(project, 'regions.json')
    manifest = json.loads(manifest_path.read_text())
    by_source = defaultdict(list)
    for region in manifest["regions"]:
        by_source[region["source"]].append(region)
    report_path = ROOT / "matching2/build/msvc/compile-failures.json"
    failures = json.loads(report_path.read_text()) if report_path.is_file() else []
    if not failures:
        print("no compile failures recorded; nothing to repair")
        return 0
    print(f"{len(failures)} failing unit(s)")
    clusters = load_clusters(project, manifest, manifest["regions"])
    cluster_by_source = {cluster["source"]: cluster for cluster in clusters}
    completed, restored, unresolved, cluster_reverts = [], [], [], []
    for index, failure in enumerate(failures):
        source = failure["source"]
        regions = [region for region in by_source[source]
                   if region["kind"] in ("asm", "semantic")]
        if not regions:
            unresolved.append((source, "owns no code region"))
            continue
        if source in cluster_by_source:
            cluster = cluster_by_source[source]
            unresolved.append((source, f"cluster layout {cluster['path'].name} is not buildable"))
            cluster_reverts.append(cluster)
            continue
        try:
            raw = compile_raw(project, args.toolkit.resolve(), args.output.resolve(),
                              index, source, manifest)
            defined = defined_functions(raw["object"])
        except Exception as error:
            defined = {}
            note = str(error)[:160]
        mapping = match_symbols(regions, defined)
        pending = [region for region in regions
                   if region["symbol"] not in defined]
        resolved = mapping if len(mapping) == len(pending) else {}
        if pending and resolved or not pending:
            proposal = {"regions": [{**region,
                                     "name": region["name"].replace("asm_", "semantic_", 1),
                                     "symbol": resolved.get(int(region["address"], 0),
                                                            region["symbol"]),
                                     "kind": "semantic" if int(region["address"], 0) in resolved
                                             else region["kind"]}
                                    for region in regions]}
            path = args.output / f"{Path(source).stem}.json"
            path.parent.mkdir(parents=True, exist_ok=True)
            path.write_text(json.dumps(proposal, indent=2) + "\n")
            print(f"  {source}: {len(resolved)} of {len(pending)} pending region(s) matched, probing")
            completed.append((source, path, regions, resolved))
        else:
            note = (f"matched {len(mapping)} of {len(pending)} converted region(s); "
                    f"defines {len(defined)} function(s)")
            unresolved.append((source, note))
    if not args.apply:
        for source, note in unresolved:
            print(f"  unresolved {source}: {note}")
        print(f"{len(completed)} unit(s) look convertible, {len(unresolved)} unresolved")
        return 0
    for cluster in cluster_reverts:
        relative = "layout/ltcg/" + cluster["path"].name
        backup = pristine(cluster["source"])
        if backup is not None:
            shutil.copy2(backup, project / cluster["source"])
            restored.append(cluster["source"])
        for path in (cluster["path"], cluster["driver_path"]):
            path.unlink(missing_ok=True)
        if relative in manifest["ltcg_clusters"]:
            manifest["ltcg_clusters"].remove(relative)
        for region in by_source[cluster["source"]]:
            if region["kind"] == "semantic":
                region["kind"] = "asm"
                region["symbol"] = "_" + region["symbol"].lstrip("_")
        print(f"  reverted cluster {relative}")
    # Units that cannot be matched are reverted to their pristine copy.
    for source, note in unresolved:
        if source in restored:
            continue
        backup = pristine(source)
        if backup is None:
            print(f"  no pristine copy for {source}; leaving as is ({note})")
            continue
        shutil.copy2(backup, project / source)
        restored.append(source)
        print(f"  restored {source} ({note})")
    # The matched units are verified against the manifest with their proposal.
    applied = []
    for source, path, regions, mapping in completed:
        command = [sys.executable, str(ROOT / "matching2/tools/matching/probe.py"),
                   "--source", source, "--proposal", str(path), "--json",
                   "--project", str(project), "--output", str(args.output / "probe")]
        result = subprocess.run(command, capture_output=True, text=True, timeout=1800)
        try:
            report = json.loads(result.stdout)
        except json.JSONDecodeError:
            report = None
        if report is None or not report["exact"]:
            backup = pristine(source)
            if backup is None:
                print(f"  {source}: not exact and no pristine copy; leaving as is")
                continue
            shutil.copy2(backup, project / source)
            restored.append(source)
            print(f"  {source}: not exact, restored")
            continue
        for region in regions:
            address = int(region["address"], 0)
            if address not in mapping:
                continue
            region["symbol"] = mapping[address]
            region["kind"] = "semantic"
            region["name"] = region["name"].replace("asm_", "semantic_", 1)
            region.pop("requested_symbol", None)
        applied.append(source)
        print(f"  {source}: exact, {len(mapping)} region(s) become semantic")
    manifest["translation_units"] = sorted({region["source"] for region in manifest["regions"]})
    manifest_path.write_text(json.dumps(manifest, indent=2) + "\n")
    print(f"completed {len(applied)} unit(s), restored {len(restored)} unit(s)")
    return 0


if __name__ == "__main__":
    sys.exit(main())
