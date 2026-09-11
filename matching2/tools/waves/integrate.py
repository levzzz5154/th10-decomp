#!/usr/bin/env python3
"""Merge probe-verified conversions into the maintained region manifest.

Only regions whose unit the probe reports EXACT enter the manifest, and every
entry is re-verified here rather than trusted from an agent report. The previous
entries are written to a rollback file so a failed whole-image build can be
undone region by region.
"""
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[3]
sys.path.insert(0, str(ROOT))

import argparse
import json
import subprocess

WAVE = ROOT / "matching2/build/waves"
MANIFEST = ROOT / "matching2/msvc/regions.json"
PROBE = ROOT / "matching2/tools/matching/probe.py"


def collect_proposals(results, manifest_index):
    """Map source -> proposal records gathered from every agent's scratch dir.

    A record marks a conversion when it says so, or when it renames the region's
    symbol: changing the symbol means the body is no longer the maintained
    inline assembly, whatever label the proposal carries.
    """
    proposals = {}
    for path in sorted(results.rglob("*.json")):
        if path.name == "summary.json" or "probe" in path.parts:
            continue
        try:
            payload = json.loads(path.read_text())
        except json.JSONDecodeError:
            continue
        for region in payload.get("regions", []):
            if not isinstance(region, dict) or not {"name", "source", "symbol", "address",
                                                    "size", "kind"} <= set(region):
                continue  # probe reports and notes also live under results/
            current = manifest_index.get(int(region["address"], 0))
            if region["kind"] != "semantic" and (current is None or current["symbol"] == region["symbol"]):
                continue
            name = region["name"]
            if name.startswith("asm_"):
                name = "semantic_" + name[len("asm_"):]
            proposals.setdefault(region["source"], {})[region["address"]] = {
                **region, "name": name, "kind": "semantic"}
    return {source: list(by_address.values()) for source, by_address in proposals.items()}


def verify(source, proposals, output, project):
    """Return the probe's resolved region records when the unit is exact."""
    output.mkdir(parents=True, exist_ok=True)
    proposal_path = output / "merged-proposal.json"
    resolved_path = output / "resolved-proposal.json"
    proposal_path.write_text(json.dumps({"regions": proposals}, indent=2) + "\n")
    command = [sys.executable, str(PROBE), "--source", source, "--proposal", str(proposal_path),
               "--write-proposal", str(resolved_path), "--json", "--project", str(project),
               "--output", str(output / "probe")]
    result = subprocess.run(command, capture_output=True, text=True, timeout=900)
    try:
        report = json.loads(result.stdout)
    except json.JSONDecodeError:
        return None, f"probe did not report: {result.stderr.strip()[:400]}"
    if not report["exact"]:
        detail = "; ".join(
            [failure["error"][:160] for failure in report["failures"]] +
            [f"{region['symbol']}: {region.get('detail', 'bytes differ')[:120]}"
             for region in report["regions"] if not region["exact"]])
        return None, detail or "not exact"
    return json.loads(resolved_path.read_text())["regions"], ""


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--project", type=Path, default=ROOT / "matching2/msvc")
    parser.add_argument("--results", type=Path, default=WAVE / "results")
    parser.add_argument("--apply", action="store_true", help="write the manifest")
    args = parser.parse_args()
    manifest_path = args.project.resolve() / "regions.json"
    manifest = json.loads(manifest_path.read_text())
    index = {int(region["address"], 0): position
             for position, region in enumerate(manifest["regions"])}
    manifest_index = {int(region["address"], 0): region for region in manifest["regions"]}
    proposals = collect_proposals(args.results, manifest_index)
    accepted, rejected = [], []
    scratch = WAVE / "integrate"
    for source, regions in sorted(proposals.items()):
        resolved, problem = verify(source, regions, scratch, args.project)
        if resolved is None:
            rejected.append({"source": source, "addresses": [r["address"] for r in regions],
                             "problem": problem})
            continue
        for region in resolved:
            accepted.append(region)
    print(f"verified {len(accepted)} region(s) across "
          f"{len({region['source'] for region in accepted})} unit(s); "
          f"{len(rejected)} unit(s) rejected")
    for item in rejected:
        print(f"  rejected {item['source']}: {item['problem'][:160]}")
    if not args.apply:
        return 0
    rollback = []
    for region in accepted:
        address = int(region["address"], 0)
        position = index.get(address)
        if position is None:
            print(f"  no manifest entry for {address:#010x}; skipping")
            continue
        previous = manifest["regions"][position]
        if previous["size"] != region["size"]:
            print(f"  extent change at {address:#010x}; skipping")
            continue
        if previous == region:
            continue
        if previous["kind"] == "semantic" and previous["symbol"] == region["symbol"]:
            continue
        rollback.append(previous)
        manifest["regions"][position] = dict(region)
    (WAVE / "rollback.json").write_text(json.dumps({"regions": rollback}, indent=2) + "\n")
    manifest_path.write_text(json.dumps(manifest, indent=2) + "\n")
    print(f"applied {len(rollback)} region(s); rollback recorded at {WAVE / 'rollback.json'}")
    subprocess.run([sys.executable, str(ROOT / "matching2/tools/matching/progress.py")], cwd=ROOT)
    return 0


if __name__ == "__main__":
    sys.exit(main())
