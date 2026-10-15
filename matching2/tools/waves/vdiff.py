#!/usr/bin/env python3
"""Full side-by-side instruction diff for one region, compiled from the project.

The probe reports the *first* differing byte; recovering a function needs the
whole picture, because a source shape usually changes several instructions at
once. This tool compiles one unit through the probe's own compile path, then
prints retail and compiled disassembly of the region aligned by address, with
the differing instructions marked, plus the total differing-byte count — the
number that says whether a variant moved closer or further away.

Usage:
    python3 vdiff.py --source src/game/foo.cpp --address 0x0040B940
    python3 vdiff.py --source src/game/foo.cpp --address 0x0040B940 --proposal p.json
"""
from __future__ import annotations

import argparse
import json
import re
import shutil
import struct
import subprocess
import sys
import tempfile
from pathlib import Path

ROOT = Path(__file__).resolve().parents[3]
sys.path.insert(0, str(ROOT))

from matching2.tools.common.pe import PEImage
from matching2.tools.matching.build_msvc import DEFAULT_TOOLKIT, ROOT as BUILD_ROOT
from matching2.tools.matching.probe import (
    apply_proposals, load_manifest, load_oracle, owned_regions, probe_unit)
from matching2.tools.matching.ltcg_cluster import load_clusters


def disassemble(data, start):
    """Address -> (bytes, text) for every instruction objdump decodes."""
    objdump = shutil.which("i686-w64-mingw32-objdump") or shutil.which("objdump")
    with tempfile.TemporaryDirectory(prefix="th10-vdiff-") as temporary:
        path = Path(temporary) / "region.bin"
        path.write_bytes(data)
        result = subprocess.run(
            [objdump, "-D", "-z", "-b", "binary", "-m", "i386", "-M", "intel",
             "--insn-width=16", f"--adjust-vma={start:#x}", str(path)],
            capture_output=True, text=True, timeout=30)
    listing = {}
    for line in result.stdout.splitlines():
        match = re.match(r"\s*([0-9a-fA-F]+):\s+((?:[0-9a-fA-F]{2}\s+)+)(.*)", line)
        if match:
            listing[int(match[1], 16)] = (bytes.fromhex(match[2]), match[3].strip())
    return listing


def aligned(expected, actual, start):
    """Yield (address, expected text, actual text, differs) over both listings."""
    addresses = sorted(set(expected) | set(actual))
    rows, cursor = [], start
    for address in addresses:
        if address < cursor:
            continue  # a prefix of an instruction already printed
        left = expected.get(address)
        right = actual.get(address)
        if left is None and right is None:
            continue
        text_left = f"{left[0].hex(' '):<24} {left[1]}" if left else "<retail ends>"
        text_right = f"{right[0].hex(' '):<24} {right[1]}" if right else "<compiled ends>"
        rows.append((address, text_left, text_right, left != right))
        span = max(len(left[0]) if left else 1, len(right[0]) if right else 1)
        cursor = address + span
    return rows


from matching2.tools.common.project_paths import project_support
def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--project", type=Path, default=BUILD_ROOT / "matching2/msvc")
    parser.add_argument("--toolkit", type=Path, default=DEFAULT_TOOLKIT)
    parser.add_argument("--output", type=Path, default=ROOT / "matching2/build/vdiff")
    parser.add_argument("--source", required=True)
    parser.add_argument("--address", type=lambda value: int(value, 0), required=True)
    parser.add_argument("--proposal", action="append", default=[])
    parser.add_argument("--context", type=int, default=0,
                        help="instructions of slack to show beyond the region")
    parser.add_argument("--json", action="store_true")
    args = parser.parse_args()
    project = args.project.resolve()
    config = load_manifest(project_support(project, 'regions.json'))
    oracle = load_oracle(ROOT / "matching2/build/oracle/th10.exe", config)
    text_start = int(config["text_start"], 0)
    proposals = []
    for path in args.proposal:
        proposals += json.loads(Path(path).read_text())["regions"]
    regions = apply_proposals(owned_regions(config, args.source), proposals, args.source)
    clusters = load_clusters(project, config, config["regions"])
    cluster_by_source = {cluster["source"]: cluster for cluster in clusters}
    unit, resolved = probe_unit(project, args.toolkit.resolve(), args.output.resolve(),
                                config, args.source, regions, cluster_by_source, 0)
    target = next((region for region in resolved
                   if int(region["address"], 0) == args.address), None)
    if target is None:
        print(f"{args.source} owns no region at {args.address:#x}", file=sys.stderr)
        return 2
    from matching2.tools.common.coff import read_coff_function
    _, body, ignored = read_coff_function(unit["object"], target["symbol"])
    size = target["size"]
    offset = args.address - text_start
    expected = oracle[offset:offset + size]
    actual = body[:size]
    if len(actual) != size:
        print(f"compiled extent {len(actual)} differs from the region size {size}", file=sys.stderr)
    differing = [index for index in range(min(len(actual), size)) if index not in ignored
                 and actual[index] != expected[index]]
    left = disassemble(expected, args.address)
    right = disassemble(actual, args.address)
    rows = aligned(left, right, args.address)
    if args.json:
        print(json.dumps({"address": args.address, "size": size, "symbol": target["symbol"],
                          "compiled_extent": len(actual), "differing_bytes": len(differing),
                          "first_difference": args.address + differing[0] if differing else None,
                          "instructions": [{"address": address, "retail": a, "compiled": b,
                                            "differs": differs}
                                           for address, a, b, differs in rows]}, indent=2))
        return 0 if not differing and len(actual) == size else 1
    print(f"{target['name']} {args.address:#010x} size {size} compiled {len(actual)} "
          f"symbol {target['symbol']}")
    print(f"differing bytes: {len(differing)}"
          + (f"  first at {args.address + differing[0]:#010x}" if differing else ""))
    for address, retail, compiled, differs in rows:
        marker = "!" if differs else " "
        print(f"{marker} {address:#010x}  {retail:<48} | {compiled}")
    return 0 if not differing and len(actual) == size else 1


if __name__ == "__main__":
    sys.exit(main())
