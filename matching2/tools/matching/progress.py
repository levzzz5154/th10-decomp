#!/usr/bin/env python3
"""Report matching-source progress from region entries, independently of a build."""

import argparse
from collections import Counter
import json
from pathlib import Path

ROOT = Path(__file__).resolve().parents[3]
MANIFEST = ROOT / "matching2/msvc/regions.json"
DOCUMENT = ROOT / "matching2/msvc/PROGRESS.md"
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


def render(summary):
    rows = ["# Matching source progress", "",
            "Generated from [regions.json](regions.json) with `make progress-update`.", "",
            "| Source classification | Regions | Bytes |",
            "| --- | ---: | ---: |"]
    rows += [f"| {LABELS[kind]} | {summary['regions'][kind]:,} | {summary['bytes'][kind]:,} |"
             for kind in KINDS]
    rows += [f"| Total .text | {sum(summary['regions'].values()):,} | {sum(summary['bytes'].values()):,} |",
             "", "These are source-manifest classifications, not a fresh build result.",
             "Regions can be function fragments; their count is not an original function count.",
             "Assembly, data, and padding do not count as ordinary C++ recovery.",
             "Readability requires source review. Run `make verify` to check exact executable output.", ""]
    return "\n".join(rows)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--manifest", type=Path, default=MANIFEST)
    parser.add_argument("--document", type=Path, default=DOCUMENT)
    mode = parser.add_mutually_exclusive_group()
    mode.add_argument("--write", action="store_true", help="update the generated progress document")
    mode.add_argument("--check", action="store_true", help="reject a stale progress document")
    mode.add_argument("--json", action="store_true", help="print machine-readable counts")
    args = parser.parse_args()
    manifest = json.loads(args.manifest.read_text())
    summary = summarize(manifest["regions"])
    if sum(summary["bytes"].values()) != manifest["text_bytes"]:
        parser.error("region byte counts disagree with the declared .text size")
    document = render(summary)
    if args.write:
        args.document.write_text(document)
        print(args.document)
    elif args.check:
        if not args.document.is_file() or args.document.read_text() != document:
            parser.exit(1, "Progress document is stale; run make progress-update.\n")
    elif args.json:
        print(json.dumps(summary, indent=2))
    else:
        print(document, end="")


if __name__ == "__main__":
    main()
