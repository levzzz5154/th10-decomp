#!/usr/bin/env python3
"""Report matching-source progress from region entries, independently of a build."""

import argparse
from collections import Counter
import json
from pathlib import Path

ROOT = Path(__file__).resolve().parents[3]
MANIFEST = ROOT / "matching2/msvc/regions.json"
KINDS = ("semantic", "asm", "data", "padding")
LABELS = {
    "semantic": "Ordinary C++",
    "asm": "Inline assembly",
    "data": "Embedded .text data",
    "padding": "Padding",
}


def summarize(regions):
    """Use actual entries, never the generator's historical cached summary."""
    counts = Counter()
    sizes = Counter()
    for region in regions:
        kind = region["kind"]
        size = region["size"]
        if kind not in KINDS or type(size) is not int or size <= 0:
            raise ValueError("invalid region classification or size")
        counts[kind] += 1
        sizes[kind] += size
    return {"regions": {kind: counts[kind] for kind in KINDS},
            "bytes": {kind: sizes[kind] for kind in KINDS}}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--manifest", type=Path, default=MANIFEST)
    parser.add_argument("--json", action="store_true", help="print machine-readable counts")
    args = parser.parse_args()
    manifest = json.loads(args.manifest.read_text())
    summary = summarize(manifest["regions"])
    if sum(summary["bytes"].values()) != manifest["text_bytes"]:
        parser.error("region byte counts disagree with the declared .text size")
    if args.json:
        print(json.dumps(summary, indent=2))
    else:
        for kind in KINDS:
            print(f"{LABELS[kind]}: {summary['regions'][kind]:,} regions / {summary['bytes'][kind]:,} bytes")
        print(f"Total .text: {sum(summary['bytes'].values()):,} bytes")



if __name__ == "__main__":
    main()
