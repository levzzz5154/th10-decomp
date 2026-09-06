#!/usr/bin/env python3
"""Verify recorded evidence integrity; this does not rerun or certify the game."""
import gzip
import hashlib
import json
import subprocess
from pathlib import Path

REPO = Path(__file__).resolve().parents[2]
AUDIT = REPO / "matching2/docs/audit"


def sha(data):
    return hashlib.sha256(data).hexdigest()


def require(condition, message):
    if not condition:
        raise ValueError(message)


def check():
    baseline = json.loads((AUDIT / "baseline.json").read_text(encoding="utf-8"))
    for row in baseline["artifacts"]:
        data = (AUDIT / row["path"]).read_bytes()
        require(sha(data) == row["sha256"] and len(data) == row["bytes"], row["path"] + ": artifact mismatch")
        if "uncompressed_sha256" in row:
            raw = gzip.decompress(data)
            require(sha(raw) == row["uncompressed_sha256"] and len(raw) == row["uncompressed_bytes"], row["path"] + ": decompressed mismatch")
    retail = baseline["traces"]["retail"]
    require(sha((REPO / retail["path"]).read_bytes()) == retail["sha256"], "archived retail trace changed")
    comparison = json.loads((AUDIT / "comparison.json").read_text(encoding="utf-8"))
    require(comparison["source_baseline"] == baseline["baseline_commit"], "comparison baseline mismatch")
    require(sha((REPO / "matching2/tools/retail_vs_recon_stage.py").read_bytes()) == comparison["comparator_sha256"],
            "comparator changed; recapture comparison results")
    for row in comparison["runs"]:
        require(sha((AUDIT / row["log"]).read_bytes()) == row["log_sha256"], row["log"] + ": log changed")
    # Baseline artifacts retain their meaning when production is later fixed:
    # authenticate the historical tree, rather than demanding current equality.
    tree = subprocess.check_output(["git", "rev-parse", baseline["baseline_commit"] + "^{tree}"], cwd=REPO, text=True).strip()
    require(tree == baseline["baseline_tree"], "baseline tree mismatch")
    print("AUDIT_EVIDENCE_INTEGRITY_PASS (stored artifacts; no fresh runtime/parity claim)")


if __name__ == "__main__":
    try:
        check()
    except (ValueError, OSError, KeyError, subprocess.CalledProcessError) as exc:
        raise SystemExit(str(exc))
