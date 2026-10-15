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
import fcntl
import json
import os
import shutil
import subprocess
import tempfile

from matching2.tools.waves.integration_gates import (
    ResultSchemaError,
    commit_gate,
    full_hash_gate,
    manifest_gate,
    probe_cluster_gate,
    touched_clusters,
    validate_result_payload,
    write_gate_report,
)

WAVE = ROOT / "matching2/build/waves"
from matching2.tools.common.project_paths import project_support
MANIFEST = project_support((ROOT) / 'matching2/msvc', 'regions.json')
PROBE = ROOT / "matching2/tools/matching/probe.py"


def collect_proposals(results, manifest_index):
    """Map source -> proposal records gathered from every agent's scratch dir.

    A record marks a conversion when it says so, or when it renames the region's
    symbol: changing the symbol means the body is no longer the maintained
    inline assembly, whatever label the proposal carries.
    """
    proposals = {}
    for path in sorted(results.rglob("*.json")):
        try:
            payload = json.loads(path.read_text())
        except json.JSONDecodeError:
            continue
        validate_result_payload(payload, str(path))
        if path.name == "summary.json" or "probe" in path.parts:
            continue
        if not isinstance(payload, dict):
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

def candidate_manifest(manifest, regions):
    """Apply admissible resolved regions to a copy of the manifest."""
    candidate = json.loads(json.dumps(manifest))
    index = {int(region["address"], 0): position
             for position, region in enumerate(candidate["regions"])}
    rollback, skipped = [], []
    for region in regions:
        address = int(region["address"], 0)
        position = index.get(address)
        if position is None:
            skipped.append(f"no manifest entry for {address:#010x}")
            continue
        previous = candidate["regions"][position]
        if previous["size"] != region["size"]:
            skipped.append(f"extent change at {address:#010x}")
            continue
        if previous == region:
            continue
        if previous["kind"] == "semantic" and previous["symbol"] == region["symbol"]:
            continue
        rollback.append(previous)
        candidate["regions"][position] = dict(region)
    candidate["translation_units"] = sorted(
        {region["source"] for region in candidate["regions"]}
    )
    return candidate, rollback, skipped


def preintegration_gates(project, manifest, changed, output):
    """Validate a staged manifest and re-probe every touched LTCG cluster."""
    with tempfile.TemporaryDirectory(prefix="th10-integrate-") as directory:
        staged = Path(directory) / "msvc"
        shutil.copytree(project, staged)
        (project_support(staged, 'regions.json')).write_text(json.dumps(manifest, indent=2) + "\n")
        try:
            manifest_result, clusters, _ = manifest_gate(staged)
        except Exception as error:
            return ({"passed": False, "problem": str(error)},
                    {"passed": False, "cluster_count": 0, "clusters": [],
                     "problem": "manifest gate failed"})
        touched = touched_clusters(
            clusters,
            sources={region["source"] for region in changed},
            addresses={int(region["address"], 0) for region in changed},
        )
        probes = probe_cluster_gate(staged, touched, output)
        return manifest_result, probes


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--project", type=Path, default=ROOT / "matching2/msvc")
    parser.add_argument("--results", type=Path, default=WAVE / "results")
    parser.add_argument("--apply", action="store_true", help="write the manifest")
    parser.add_argument("--gate-report", type=Path, default=WAVE / "integration-gates.json",
                        help="machine-readable integration gate record")
    parser.add_argument("--full-report", type=Path,
                        help="existing whole-image port-report.json to inspect; never runs a build")
    parser.add_argument("--integration-commit",
                        help="manual commit object id to record after the full hash gate")
    args = parser.parse_args()
    project = args.project.resolve()
    manifest_path = project_support(project, 'regions.json')
    manifest = json.loads(manifest_path.read_text())
    manifest_index = {int(region["address"], 0): region for region in manifest["regions"]}
    try:
        proposals = collect_proposals(args.results, manifest_index)
    except ResultSchemaError as error:
        report = {
            "schema": "th10-integration-gates/v1",
            "batch": {"applied": False, "problem": str(error)},
            "gates": {
                "result_schema": {"passed": False, "problem": str(error)},
                "manifest": {"passed": False, "status": "not_run"},
                "touched_cluster_probes": {"passed": False, "status": "not_run"},
                "full_hash": full_hash_gate(project, args.full_report),
            },
        }
        report["integration_commit"] = commit_gate(args.integration_commit,
                                                       report["gates"]["full_hash"])
        report["release_ready"] = False
        write_gate_report(args.gate_report, report)
        print(f"rejected result schema: {error}")
        print(f"gate report: {args.gate_report}")
        return 2

    accepted, rejected = [], []
    scratch = WAVE / "integrate"
    for source, regions in sorted(proposals.items()):
        resolved, problem = verify(source, regions, scratch, project)
        if resolved is None:
            rejected.append({"source": source, "addresses": [r["address"] for r in regions],
                             "problem": problem})
            continue
        accepted.extend(resolved)
    print(f"verified {len(accepted)} region(s) across "
          f"{len({region['source'] for region in accepted})} unit(s); "
          f"{len(rejected)} unit(s) rejected")
    for item in rejected:
        print(f"  rejected {item['source']}: {item['problem'][:160]}")

    def prepare(current):
        candidate, rollback, skipped = candidate_manifest(current, accepted)
        for problem in skipped:
            print(f"  {problem}; skipping")
        manifest_result, probes = preintegration_gates(
            project, candidate, rollback, scratch / "cluster-gates"
        )
        return candidate, rollback, skipped, manifest_result, probes

    lock = None
    if args.apply:
        lock = open(manifest_path.with_suffix(".json.lock"), "w")
        fcntl.flock(lock, fcntl.LOCK_EX)
        manifest = json.loads(manifest_path.read_text())
    try:
        candidate, rollback, skipped, manifest_result, probes = prepare(manifest)
        preintegration_passed = manifest_result["passed"] and probes["passed"]
        applied = False
        if args.apply and preintegration_passed:
            temporary = manifest_path.with_suffix(".json.tmp")
            temporary.write_text(json.dumps(candidate, indent=2) + "\n")
            os.replace(temporary, manifest_path)
            (WAVE / "rollback.json").write_text(
                json.dumps({"regions": rollback}, indent=2) + "\n"
            )
            applied = True
    finally:
        if lock is not None:
            lock.close()

    full_hash = full_hash_gate(project, args.full_report)
    report = {
        "schema": "th10-integration-gates/v1",
        "batch": {
            "apply_requested": args.apply,
            "applied": applied,
            "accepted_regions": [region["address"] for region in accepted],
            "changed_regions": [region["address"] for region in rollback],
            "rejected_units": rejected,
            "skipped": skipped,
            "preintegration_passed": preintegration_passed,
        },
        "gates": {
            "result_schema": {"passed": True},
            "manifest": manifest_result,
            "touched_cluster_probes": probes,
            "full_hash": full_hash,
        },
    }
    report["integration_commit"] = commit_gate(args.integration_commit, full_hash)
    report["release_ready"] = bool(
        report["integration_commit"]["passed"] and preintegration_passed
    )
    write_gate_report(args.gate_report, report)
    print(f"manifest gate: {'passed' if manifest_result['passed'] else 'FAILED'}")
    print(f"touched-cluster probes: {'passed' if probes['passed'] else 'FAILED'} "
          f"({probes.get('cluster_count', 0)} cluster(s))")
    print(f"full hash gate: {full_hash['status']}")
    print(f"gate report: {args.gate_report}")
    if not preintegration_passed:
        return 1
    if not args.apply:
        return 0
    print(f"applied {len(rollback)} region(s); rollback recorded at {WAVE / 'rollback.json'}")
    subprocess.run([sys.executable, str(ROOT / "matching2/tools/matching/progress.py")], cwd=ROOT)
    return 0


if __name__ == "__main__":
    sys.exit(main())
