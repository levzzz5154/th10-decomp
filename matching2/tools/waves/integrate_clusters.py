#!/usr/bin/env python3
"""Merge probe-verified cluster recoveries from sandbox agents into the project.

Each agent works in its own copy of the project, so what comes back is a source
file, a cluster driver, a cluster manifest and a region record. This copies the
first three, points the region at them, and — for a region carved out of a
multi-region file — deletes the old naked body from that file. Every region is
re-probed here rather than trusted from the agent's report.
"""
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[3]
sys.path.insert(0, str(ROOT))

import argparse
import json
import re
import shutil
import subprocess

PROJECT = ROOT / "matching2/msvc"
WAVE = ROOT / "matching2/build/waves"
BLOCK = re.compile(r'extern "C" __declspec\(naked\) void __cdecl (\w+)\(\)\s*\{\s*__asm \{.*?\n    \}\n\}', re.S)


def collected(results):
    """Every converted entry an agent recorded, with its sandbox path."""
    entries = []
    for summary in sorted(results.glob("*/summary.json")):
        agent = summary.parent.name
        sandbox = WAVE / "lab" / agent / "msvc"
        payload = json.loads(summary.read_text())
        for item in payload.get("converted", []):
            if isinstance(item, str):
                continue
            entries.append({**item, "agent": agent, "sandbox": sandbox})
    return entries


def carve(original, symbol):
    """Delete one naked body from the file it used to live in."""
    text = original.read_text()
    match = None
    for candidate in BLOCK.finditer(text):
        if candidate.group(1) == symbol:
            match = candidate
            break
    if match is None:
        raise SystemExit(f"{original} does not define {symbol}")
    original.write_text(text[:match.start()] + text[match.end():])


from matching2.tools.common.project_paths import project_support
def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--results", type=Path, default=WAVE / "results3")
    parser.add_argument("--apply", action="store_true")
    args = parser.parse_args()
    manifest_path = project_support(PROJECT, 'regions.json')
    manifest = json.loads(manifest_path.read_text())
    index = {int(region["address"], 0): position for position, region in enumerate(manifest["regions"])}
    entries = collected(args.results)
    print(f"{len(entries)} cluster recovery record(s) across "
          f"{len({entry['agent'] for entry in entries})} sandbox(es)")
    prepared, problems = [], []
    for entry in entries:
        address = int(entry["address"], 0)
        sandbox, source = entry["sandbox"], entry["new_source"] if entry.get("new_source") else entry["source"]
        for key in ("source", "driver", "manifest"):
            if not (sandbox / entry[key]).is_file():
                problems.append(f"{address:#010x}: missing sandbox file {entry[key]}")
        if address not in index:
            problems.append(f"{address:#010x}: no manifest region")
        if not entry.get("symbol"):
            problems.append(f"{address:#010x}: no emitted symbol recorded")
        prepared.append({**entry, "address_int": address, "project_source": source})
    for problem in problems:
        print("  rejected:", problem)
    if not args.apply:
        return 0
    for entry in prepared:
        if any(problem.startswith(f"{entry['address_int']:#010x}") for problem in problems):
            continue
        target = PROJECT / entry["project_source"]
        target.parent.mkdir(parents=True, exist_ok=True)
        shutil.copy2(entry["sandbox"] / entry["project_source"], target)
        for key in ("driver", "manifest"):
            shutil.copy2(entry["sandbox"] / entry[key], PROJECT / entry[key])
        if entry.get("carved_from"):
            carve(PROJECT / entry["carved_from"], entry["carve_symbol"])
        if entry["manifest"] not in manifest["ltcg_clusters"]:
            manifest["ltcg_clusters"].append(entry["manifest"])
        position = index[entry["address_int"]]
        previous = manifest["regions"][position]
        manifest["regions"][position] = {**previous, "source": entry["project_source"],
                                         "symbol": entry["symbol"], "kind": "semantic",
                                         "name": entry.get("name", previous["name"].replace("asm_", "semantic_", 1))}
        print(f"  merged {entry['address_int']:#010x} -> {entry['project_source']} "
              f"({entry['manifest']})")
    manifest["translation_units"] = sorted({region["source"] for region in manifest["regions"]})
    manifest_path.write_text(json.dumps(manifest, indent=2) + "\n")
    print(f"manifest written: {len(manifest['regions'])} regions, "
          f"{len(manifest['translation_units'])} units")
    sources = sorted({entry["project_source"] for entry in prepared})
    command = [sys.executable, str(ROOT / "matching2/tools/matching/probe.py"),
               *sum((["--source", item] for item in sources), []),
               "--output", str(WAVE / "cluster-integration")]
    result = subprocess.run(command, cwd=ROOT, capture_output=True, text=True, timeout=3600)
    print(result.stdout[-4000:])
    print(result.stderr.strip()[-400:])
    return 0 if result.returncode == 0 else 1


if __name__ == "__main__":
    sys.exit(main())
