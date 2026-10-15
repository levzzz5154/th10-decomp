#!/usr/bin/env python3
"""Carve every region that needs a native LTCG cluster into its own unit.

A cluster owns its whole translation unit, so a region that shares a source with
others cannot be recovered with one. This driver walks the cluster-needed set,
highest address first (so earlier carves do not move the addresses of the ones
still to come), and calls ``carve_region.py`` for each. A carve that fails its
own before/after probe is rolled back by that tool, so the project keeps
building while the loop runs.
"""
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[3]
sys.path.insert(0, str(ROOT))

import argparse
import json
import subprocess

import matching2.tools.waves.plan as plan

CARVE = ROOT / "matching2/tools/waves/carve_region.py"


from matching2.tools.common.project_paths import project_support
def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--max-size", type=int, default=1024)
    parser.add_argument("--limit", type=int, default=0)
    args = parser.parse_args()
    signatures = plan.ida_signatures()
    items = plan.candidates(1, args.max_size, 0x452000, signatures)
    targets = [item for item in items if item["cluster_needed"]]
    project = ROOT / "matching2/msvc"
    manifest = json.loads((project_support(project, 'regions.json')).read_text())
    owned = {}
    for region in manifest["regions"]:
        owned.setdefault(region["source"], []).append(region)
    done = failures = skipped = 0
    for item in sorted(targets, key=lambda entry: (entry["source"], -int(entry["address"], 0))):
        source = item["source"]
        siblings = owned.get(source, [])
        if len(siblings) < 2:
            skipped += 1  # already a single-region unit, or carved by an earlier pass
            continue
        result = subprocess.run(
            [sys.executable, str(CARVE), "--source", source, "--address", item["address"], "--apply"],
            cwd=ROOT, capture_output=True, text=True, timeout=900)
        if result.returncode == 0:
            done += 1
            tail = (result.stdout.strip().splitlines() or [""])[-1]
            print(f"carved {item['address']} {source}: {tail}", flush=True)
            manifest = json.loads((project_support(project, 'regions.json')).read_text())
            owned = {}
            for region in manifest["regions"]:
                owned.setdefault(region["source"], []).append(region)
        else:
            failures += 1
            lines = (result.stdout or result.stderr).strip().splitlines()
            print(f"FAILED {item['address']} {source}: {' | '.join(lines[-3:])[:300]}", flush=True)
        if args.limit and done >= args.limit:
            break
    print(f"carved {done}, failed {failures}, already single-region {skipped}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
