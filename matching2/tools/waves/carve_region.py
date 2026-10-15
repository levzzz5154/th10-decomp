#!/usr/bin/env python3
"""Move one region's naked body into its own single-region translation unit.

A native LTCG cluster must own its whole translation unit, so a region that
shares a source with others has to be carved out first. The carved file keeps
the parent's own ``#include`` lines and the region's comment block; the parent
loses the body and the block. Both the parent and the new file are probed
before the change is kept, so a carve that stops compiling is rolled back on
the spot.

Usage:
    python3 carve_region.py --source src/game/player.cpp --address 0x00405620 \
        [--name player_forward_axis] [--apply]
"""
from __future__ import annotations

import argparse
import json
import re
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[3]
sys.path.insert(0, str(ROOT))

PROBE = ROOT / "matching2/tools/matching/probe.py"
BLOCK = re.compile(r'(?://[^\n]*\n)*extern "C" __declspec\(naked\) void __cdecl (\w+)\(\)\s*\{\s*'
                   r'__asm \{.*?\n    \}\n\}\n', re.S)
PREAMBLE = re.compile(r'^((?:[ \t]*#[^\n]*\n|[ \t]*\n|[ \t]*//[^\n]*\n)*)')


def snake(name):
    """A snake_case file stem for a region name such as asm_RecoveryState_X_00412345."""
    stem = name[4:] if name.startswith("asm_") else name
    stem = re.sub(r"(?<=[a-z0-9])(?=[A-Z])", "_", stem)
    stem = re.sub(r"(?<=[A-Z])(?=[A-Z][a-z])", "_", stem)
    return re.sub(r"[^A-Za-z0-9_]", "_", stem).lower()


def carve_source(text, symbol):
    """Return (preamble, block) for one naked definition and the text without it."""
    hits = [match for match in BLOCK.finditer(text) if match.group(1) == symbol]
    if len(hits) != 1:
        raise ValueError(f"expected one naked definition of {symbol}, found {len(hits)}")
    match = hits[0]
    body_start = text.index("__asm {", match.start())
    block = text[match.start():match.end()]
    comment = text[text.rfind("\n", 0, match.start()) + 1:match.start()]
    if comment.strip().startswith("//"):
        block = comment + block
    return match.start(), match.end(), block, text[:match.start()] + text[match.end():]


def probe(project, sources, output):
    output.mkdir(parents=True, exist_ok=True)
    command = [sys.executable, str(PROBE), "--project", str(project),
               *sum((["--source", source] for source in sources), []),
               "--json", "--output", str(output)]
    result = subprocess.run(command, capture_output=True, text=True, timeout=900)
    try:
        return json.loads(result.stdout)
    except json.JSONDecodeError:
        return None


from matching2.tools.common.project_paths import project_support
def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--project", type=Path, default=ROOT / "matching2/msvc")
    parser.add_argument("--source", required=True, help="project-relative source owning the region")
    parser.add_argument("--address", type=lambda value: int(value, 0), required=True)
    parser.add_argument("--name", help="file stem for the carved file, default derived from the region")
    parser.add_argument("--apply", action="store_true")
    args = parser.parse_args()
    project = args.project.resolve()
    manifest_path = project_support(project, 'regions.json')
    manifest = json.loads(manifest_path.read_text())
    region = next((item for item in manifest["regions"]
                   if int(item["address"], 0) == args.address), None)
    if region is None:
        raise SystemExit(f"no manifest region at {args.address:#x}")
    if region["source"] != args.source:
        raise SystemExit(f"region {args.address:#x} is owned by {region['source']}")
    if region["kind"] != "asm" or not region.get("owner"):
        raise SystemExit(f"region {args.address:#x} is not an owned assembly region")
    siblings = [item for item in manifest["regions"] if item["source"] == args.source]
    if len(siblings) < 2:
        raise SystemExit(f"{args.source} already owns a single region")
    parent = project / args.source
    text = parent.read_text()
    symbol = region["symbol"].lstrip("_")
    try:
        start, end, block, reduced = carve_source(text, symbol)
    except ValueError as error:
        raise SystemExit(str(error))
    stem = args.name or snake(region["name"])
    carved_rel = str(Path(args.source).parent / f"{stem}.cpp")
    carved = project / carved_rel
    if carved.exists():
        raise SystemExit(f"{carved_rel} already exists")
    preamble = PREAMBLE.match(text).group(1)
    body = block if "#include" not in block else block.split("#include", 1)[0]
    content = preamble.rstrip("\n") + "\n\n" + block.strip("\n") + "\n"
    print(f"carve {region['name']} ({region['size']}B) from {args.source} -> {carved_rel}")
    if not args.apply:
        print("(dry run; pass --apply to write)")
        return 0
    before = probe(project, [args.source], ROOT / "matching2/build/waves/carve/probe-before")
    if before is None or not before["exact"]:
        raise SystemExit("the parent unit does not probe exact before the carve; refusing")
    parent.write_text(reduced)
    carved.write_text(content)
    region["source"] = carved_rel
    manifest["translation_units"] = sorted({item["source"] for item in manifest["regions"]})
    manifest_path.write_text(json.dumps(manifest, indent=2) + "\n")
    after = probe(project, [args.source, carved_rel], ROOT / "matching2/build/waves/carve/probe-after")
    problems = []
    if after is None:
        problems.append("probe did not report")
    else:
        problems += [f"{failure['source']}: {failure['error'][:160]}" for failure in after["failures"]]
        problems += [f"{item['address']:#010x} {item['symbol']}: "
                     f"{item.get('detail') or item.get('first_difference')}"
                     for item in after["regions"] if not item["exact"]]
    if problems:
        parent.write_text(text)
        carved.unlink()
        region["source"] = args.source
        manifest["translation_units"] = sorted({item["source"] for item in manifest["regions"]})
        manifest_path.write_text(json.dumps(manifest, indent=2) + "\n")
        print("carve rolled back:")
        for problem in problems:
            print("  " + problem)
        return 1
    print(f"carved and verified: {carved_rel} owns {args.address:#x}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
