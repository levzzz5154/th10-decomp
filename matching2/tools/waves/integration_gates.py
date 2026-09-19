#!/usr/bin/env python3
"""Shared schema and acceptance gates for wave result integration.

These helpers deliberately do not commit anything.  A promotion is eligible for
an integration commit only after the manifest, touched-cluster probes, and a
fresh whole-image build report all pass.
"""
from __future__ import annotations

import argparse
import hashlib
import json
import re
import subprocess
import sys
from pathlib import Path
from typing import Any, Iterable, Mapping, Sequence

ROOT = Path(__file__).resolve().parents[3]
if str(ROOT) not in sys.path:
    sys.path.insert(0, str(ROOT))

from matching2.tools.matching.build_msvc import validate_project
from matching2.tools.matching.ltcg_cluster import load_clusters

PROBE = ROOT / "matching2/tools/matching/probe.py"
RESIDUAL_CLASSES = {
    "source_shape",
    "allocator",
    "scheduler",
    "abi",
    "placement",
    "structural",
    "toolkit",
}
BLOCKED_FIELDS = (
    "closest_byte_count",
    "first_diff",
    "residual_class",
    "variants_tested",
    "next_lever",
)


class ResultSchemaError(ValueError):
    """A campaign result cannot be admitted to integration."""


def _nonempty_text(value: Any) -> bool:
    return isinstance(value, str) and bool(value.strip())


def validate_blocked_evidence(record: Mapping[str, Any], where: str = "result") -> None:
    """Require measured, actionable evidence on a ``BLOCKED`` result."""
    missing = [field for field in BLOCKED_FIELDS if field not in record]
    if missing:
        raise ResultSchemaError(
            f"{where}: BLOCKED evidence missing required field(s): {', '.join(missing)}"
        )
    byte_count = record["closest_byte_count"]
    if not isinstance(byte_count, int) or isinstance(byte_count, bool) or byte_count < 0:
        raise ResultSchemaError(f"{where}: BLOCKED closest_byte_count must be a non-negative integer")
    first_diff = record["first_diff"]
    if not ((isinstance(first_diff, int) and not isinstance(first_diff, bool) and first_diff >= 0)
            or (isinstance(first_diff, str) and re.fullmatch(r"0[xX][0-9a-fA-F]+", first_diff))):
        raise ResultSchemaError(f"{where}: BLOCKED first_diff must be an address integer or 0x-prefixed address")
    residual = record["residual_class"]
    if residual not in RESIDUAL_CLASSES:
        raise ResultSchemaError(
            f"{where}: BLOCKED residual_class must be one of {', '.join(sorted(RESIDUAL_CLASSES))}"
        )
    variants = record["variants_tested"]
    valid_variants = (
        isinstance(variants, int) and not isinstance(variants, bool) and variants > 0
    ) or (
        isinstance(variants, list) and bool(variants)
        and all(_nonempty_text(item) for item in variants)
    )
    if not valid_variants:
        raise ResultSchemaError(
            f"{where}: BLOCKED variants_tested must be a positive integer or nonempty string array"
        )
    if not _nonempty_text(record["next_lever"]):
        raise ResultSchemaError(f"{where}: BLOCKED next_lever must be a nonempty string")


def validate_result_payload(payload: Any, where: str) -> None:
    """Validate every explicitly status-tagged BLOCKED record in a JSON payload."""
    def visit(value: Any, location: str) -> None:
        if isinstance(value, dict):
            if value.get("status") == "BLOCKED":
                validate_blocked_evidence(value, location)
            for key, child in value.items():
                visit(child, f"{location}.{key}")
        elif isinstance(value, list):
            for index, child in enumerate(value):
                visit(child, f"{location}[{index}]")

    visit(payload, where)


def manifest_gate(project: Path) -> tuple[dict[str, Any], list[dict[str, Any]], dict[str, Any]]:
    """Validate the project manifest and load every registered LTCG cluster."""
    manifest_path = project / "regions.json"
    config = json.loads(manifest_path.read_text())
    reference = json.loads((project / "pe_layout.json").read_text())["reference"]
    regions, units = validate_project(config, reference)
    clusters = load_clusters(project, config, regions)
    return ({
        "passed": True,
        "region_count": len(regions),
        "translation_unit_count": len(units),
        "cluster_count": len(clusters),
    }, clusters, config)


def touched_clusters(clusters: Sequence[Mapping[str, Any]], *,
                     sources: Iterable[str] = (), addresses: Iterable[int] = (),
                     layouts: Iterable[str] = ()) -> list[Mapping[str, Any]]:
    """Return clusters affected by any changed source, function, or layout."""
    source_set = set(sources)
    address_set = set(addresses)
    layout_set = set(layouts)
    selected = []
    for cluster in clusters:
        relative_layout = str(Path(cluster["path"]).relative_to(cluster["project"]))
        function_addresses = {int(function["address"]) for function in cluster["functions"]}
        if (source_set.intersection(cluster["source_names"])
                or address_set.intersection(function_addresses)
                or relative_layout in layout_set):
            selected.append(cluster)
    return selected


def probe_cluster_gate(project: Path, clusters: Sequence[Mapping[str, Any]],
                       output: Path) -> dict[str, Any]:
    """Probe every maintained function belonging to each touched LTCG cluster."""
    output.mkdir(parents=True, exist_ok=True)
    results = []
    for cluster in clusters:
        sources = list(cluster["source_names"])
        cluster_output = output / cluster["name"]
        # A cluster probe returns every selected function even when invoked
        # through one owning source; compiling once avoids rebuilding the same
        # native-LTCG image for each additional source.
        command = [sys.executable, str(PROBE), "--project", str(project),
                   "--source", sources[0], "--json", "--output", str(cluster_output)]
        try:
            completed = subprocess.run(command, capture_output=True, text=True, timeout=3600)
        except (OSError, subprocess.TimeoutExpired) as error:
            results.append({
                "cluster": cluster["name"],
                "layout": str(Path(cluster["path"]).relative_to(project)),
                "sources": sources,
                "passed": False,
                "problem": f"probe could not complete: {error}",
            })
            continue
        try:
            report = json.loads(completed.stdout)
        except json.JSONDecodeError:
            results.append({
                "cluster": cluster["name"],
                "layout": str(Path(cluster["path"]).relative_to(project)),
                "sources": sources,
                "passed": False,
                "problem": "probe did not emit JSON: " + completed.stderr.strip()[:400],
            })
            continue
        expected = {int(function["address"]) for function in cluster["functions"]}
        observed = {int(region["address"]) for region in report.get("regions", [])
                    if region.get("source") in sources}
        failed = [region for region in report.get("regions", [])
                  if int(region.get("address", -1)) in expected and not region.get("exact")]
        passed = (completed.returncode == 0 and report.get("exact") is True
                  and observed == expected and not report.get("failures") and not failed)
        result = {
            "cluster": cluster["name"],
            "layout": str(Path(cluster["path"]).relative_to(project)),
            "sources": sources,
            "expected_addresses": [f"0x{address:08X}" for address in sorted(expected)],
            "observed_addresses": [f"0x{address:08X}" for address in sorted(observed)],
            "passed": passed,
        }
        if not passed:
            details = [failure.get("error", "probe failure")
                       for failure in report.get("failures", [])]
            details += [str(region.get("detail") or region.get("first_difference") or "bytes differ")
                        for region in failed]
            if observed != expected:
                details.append("probe did not report exactly the touched cluster's functions")
            result["problem"] = "; ".join(details)[:1200] or completed.stderr.strip()[:1200]
        results.append(result)
    return {
        "passed": all(result["passed"] for result in results),
        "cluster_count": len(results),
        "clusters": results,
    }


def full_hash_gate(project: Path, report_path: Path | None) -> dict[str, Any]:
    """Inspect, but never run, the whole-image build/hash gate."""
    command = "python3 matching2/tools/matching/build_msvc.py"
    if report_path is None:
        return {"passed": False, "status": "not_run", "report": None, "command": command}
    try:
        report = json.loads(report_path.read_text())
        config = json.loads((project / "regions.json").read_text())
        package = report["package"]
        reference = json.loads((project / "pe_layout.json").read_text())["reference"]
        expected_image = config["retail_sha256"]
        expected_text = config["text_sha256"]
        manifest_hash = hashlib.sha256((project / "regions.json").read_bytes()).hexdigest()
        reported_manifest_hash = report.get("source_sha256", {}).get("regions.json")
        passed = (package.get("sha256") == expected_image
                  and package.get("text_sha256") == expected_text
                  and package.get("size") == reference["file_size"]
                  and report.get("masked_bytes") == 0
                  and report.get("retail_executable_used_for_build") is False
                  and reported_manifest_hash == manifest_hash)
        return {
            "passed": passed,
            "status": "passed" if passed else "stale_or_mismatched",
            "report": str(report_path),
            "expected_executable_sha256": expected_image,
            "actual_executable_sha256": package.get("sha256"),
            "expected_text_sha256": expected_text,
            "actual_text_sha256": package.get("text_sha256"),
            "manifest_input_current": reported_manifest_hash == manifest_hash,
            "expected_size": reference["file_size"],
            "actual_size": package.get("size"),
            "masked_bytes": report.get("masked_bytes"),
            "retail_executable_used_for_build": report.get("retail_executable_used_for_build"),
            "command": command,
        }
    except (OSError, KeyError, TypeError, json.JSONDecodeError) as error:
        return {"passed": False, "status": "invalid_report", "report": str(report_path),
                "problem": str(error), "command": command}


def commit_gate(commit_ref: str | None, full_hash: Mapping[str, Any]) -> dict[str, Any]:
    """Record the manual commit boundary without invoking git."""
    if commit_ref is not None and not re.fullmatch(r"[0-9a-fA-F]{7,64}", commit_ref):
        raise ValueError("integration commit must be a 7-64 digit hexadecimal object id")
    passed = bool(commit_ref) and bool(full_hash.get("passed"))
    return {
        "passed": passed,
        "status": "recorded" if passed else ("full_hash_required" if commit_ref else "manual_required"),
        "automatic": False,
        "commit": commit_ref,
        "command": "git commit <promoted files>  # run manually only after the full_hash gate passes",
    }


def write_gate_report(path: Path, report: Mapping[str, Any]) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(json.dumps(report, indent=2) + "\n")

def main() -> int:
    parser = argparse.ArgumentParser(
        description="Finalize an existing promotion gate report from a whole-image report; never commit."
    )
    parser.add_argument("--project", type=Path, default=ROOT / "matching2/msvc")
    parser.add_argument("--gate-report", type=Path, required=True)
    parser.add_argument("--full-report", type=Path, required=True)
    parser.add_argument("--integration-commit",
                        help="manual commit object id to record after the full hash gate")
    args = parser.parse_args()
    report = json.loads(args.gate_report.read_text())
    full_hash = full_hash_gate(args.project.resolve(), args.full_report)
    report.setdefault("gates", {})["full_hash"] = full_hash
    report["integration_commit"] = commit_gate(args.integration_commit, full_hash)
    preintegration = bool(
        report.get("batch", {}).get("preintegration_passed")
        or (report.get("gates", {}).get("manifest", {}).get("passed")
            and report.get("gates", {}).get("touched_cluster_probes", {}).get("passed"))
    )
    report["release_ready"] = bool(
        report.get("batch", {}).get("applied")
        and preintegration
        and report["integration_commit"]["passed"]
    )
    write_gate_report(args.gate_report, report)
    print(json.dumps({
        "gate_report": str(args.gate_report),
        "full_hash_passed": full_hash["passed"],
        "integration_commit_recorded": report["integration_commit"]["passed"],
        "release_ready": report["release_ready"],
    }))
    return 0 if full_hash["passed"] else 1


if __name__ == "__main__":
    sys.exit(main())
