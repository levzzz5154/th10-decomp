#!/usr/bin/env python3
"""Register-normalised instruction-shape comparison for one region.

``vdiff.py`` reports the exact byte difference and is the right tool while a
source shape is still changing *instructions*. Once the instruction sequence
matches and only the allocator's register choices (and the resulting address
shifts) differ, the byte count stays high even though the reconstruction is
essentially right: every displacement behind the first register change differs.

This tool compiles one unit through the probe's own compile path, disassembles
retail and the compiled region, normalises register names and numeric operands,
and reports how much of the *operation sequence* is shared, with the aligned
difference. Use it to decide whether a residual is worth another source-shape
round or is a pure home-assignment blocker.

Usage:
    python3 shape.py --source src/game/foo.cpp --symbol Foo --address 0x4127A0 --size 593
"""
from __future__ import annotations

import argparse
import difflib
import json
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[3]
sys.path.insert(0, str(ROOT))

from matching2.tools.common.coff import read_coff_function
from matching2.tools.matching.build_msvc import DEFAULT_TOOLKIT, ROOT as BUILD_ROOT
from matching2.tools.matching.probe import load_manifest, load_oracle
from matching2.tools.waves.vdiff import disassemble

REGISTERS = re.compile(
    r"\b(eax|ebx|ecx|edx|esi|edi|ebp|esp|al|bl|cl|dl|ah|bh|ch|dh|ax|bx|cx|dx)\b",
    re.IGNORECASE)


def normalise(text):
    """Drop register names and numeric operands, keep the operation shape."""
    text = re.sub(r"0x[0-9a-f]+", "#", text)
    text = REGISTERS.sub("r", text)
    return re.sub(r"\s+", " ", text).strip()


def listing(data, address):
    return [normalise(text) for _, (_, text) in sorted(disassemble(data, address).items())]


from matching2.tools.common.project_paths import project_support
def main():
    parser = argparse.ArgumentParser(description=__doc__,
                                     formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("--project", type=Path, default=BUILD_ROOT / "matching2/msvc")
    parser.add_argument("--toolkit", type=Path, default=DEFAULT_TOOLKIT)
    parser.add_argument("--output", type=Path, default=ROOT / "matching2/build/shape")
    parser.add_argument("--source", required=True)
    parser.add_argument("--symbol", required=True)
    parser.add_argument("--address", type=lambda value: int(value, 0), required=True)
    parser.add_argument("--size", type=int, required=True)
    parser.add_argument("--json", action="store_true")
    args = parser.parse_args()

    project = args.project.resolve()
    config = load_manifest(project_support(project, 'regions.json'))
    oracle = load_oracle(ROOT / "matching2/build/oracle/th10.exe", config)
    text_start = int(config["text_start"], 0)
    from matching2.tools.matching.build_msvc import compile_raw
    args.output.mkdir(parents=True, exist_ok=True)
    raw = compile_raw(project, args.toolkit.resolve(), args.output, 0, args.source, config)
    name, body, ignored = read_coff_function(raw["object"], args.symbol)
    expected = oracle[args.address - text_start:args.address - text_start + args.size]
    differing = [index for index in range(min(len(body), args.size))
                 if index not in ignored and body[index] != expected[index]]
    retail = listing(expected, args.address)
    compiled = listing(body, args.address)
    matcher = difflib.SequenceMatcher(a=retail, b=compiled, autojunk=False)
    rows = [(tag, retail[i1:i2], compiled[j1:j2])
            for tag, i1, i2, j1, j2 in matcher.get_opcodes() if tag != "equal"]
    report = {
        "symbol": name, "address": args.address, "declared": args.size,
        "compiled_extent": len(body), "differing_bytes": len(differing),
        "retail_instructions": len(retail), "compiled_instructions": len(compiled),
        "shape_similarity": round(matcher.ratio(), 3),
        "differences": [{"kind": tag, "retail": left, "compiled": right}
                        for tag, left, right in rows],
    }
    if args.json:
        print(json.dumps(report, indent=2))
        return 0
    print(f"{name} {args.address:#010x}  retail {args.size} / compiled {len(body)} bytes, "
          f"{len(differing)} differing; {len(retail)} / {len(compiled)} instructions; "
          f"shape similarity {report['shape_similarity']:.3f}")
    for tag, left, right in rows:
        print(f"  {tag.upper()} (retail {len(left)}, compiled {len(right)})")
        for line in left[:6]:
            print(f"    R  {line}")
        for line in right[:6]:
            print(f"    C  {line}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
