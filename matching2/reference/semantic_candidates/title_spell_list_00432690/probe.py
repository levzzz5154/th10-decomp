#!/usr/bin/env python3
"""Measure the complete spell-list candidate and its real text callees.

This diagnostic does not register a recovery or modify the production image.
It compares each complete MAP contribution, including alignment within it.
"""
import argparse
import json
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[4]
sys.path.insert(0, str(ROOT))

from matching2.tools.common.pe import PEImage
from matching2.tools.common.wine import DEFAULT_TOOLKIT
from matching2.tools.matching.equivalence import (
    MAP_SYMBOL, build_model, disassemble, find_differences, normalize, relocate,
)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--output", type=Path, default=ROOT / "matching2/build/experiments/title_spell_list_native_2026_10_06/retained_baseline")
    args = parser.parse_args()
    work = args.output.resolve()
    work.mkdir(parents=True, exist_ok=True)
    project = ROOT / "matching2/msvc"
    spec = json.loads(Path(__file__).with_name("layout.json").read_text())
    spec["source_paths"] = [
        Path(__file__).parent.parent / "title_spell_list_00432690.cpp",
        project / "src/game/recovery_centered_text_00447bb0.cpp",
        project / "layout/ltcg/right_aligned_text_context/exact_text_dispatcher_anchor.cpp",
    ]
    config = json.loads((project / "regions.json").read_text())
    native, link_map, moved = build_model(spec, project, DEFAULT_TOOLKIT, config["flags"], work)
    pe, moved_pe = PEImage(native), PEImage(moved)
    symbols = {name: int(value, 16) for name, value, _ in MAP_SYMBOL.findall(link_map)}
    owned = sorted(int(value, 16) for _, value, where in MAP_SYMBOL.findall(link_map) if where != "<absolute>")
    bindings = {symbols[name]: int(address, 0) for name, address in spec["bindings"].items() if name in symbols}
    extents = {section: int(size, 16) for size, section in re.findall(
        r"^\s*\d+:[0-9a-f]+\s+([0-9a-f]+)H\s+(\S+)\s+CODE", link_map, re.M | re.I)}
    oracle = PEImage((ROOT / "matching2/build/oracle/th10.exe").read_bytes())
    functions = [
        (spec["function"], ".text$00432690_fn", 0x432690, 850),
        ("?FormatCentered@RecoveryIndicatorVm_00419120@@QAAXPAXZZ", ".text$00447bb0_fn", 0x447bb0, 194),
        ("?RecoveryDispatchText_004479d0@@YGXPAURecoveryTextResource_004479d0@@PAXHHIPBDH@Z", ".text$004479d0_fn", 0x4479d0, 127),
    ]
    report = {"functions": []}
    for symbol, section, address, required in functions:
        start, extent = symbols[symbol], extents[section]
        native_rows = disassemble(pe.read(start, extent), start, work, section + "_native")
        body = relocate(pe, moved_pe, native_rows, start, extent, 0, address, bindings, owned)
        (work / (section + "_body.bin")).write_bytes(body)
        original = oracle.read(address, required)
        identity = lambda value, spelling: spelling
        retail_rows = normalize(disassemble(original, address, work, section + "_retail"), address, required, required, identity)
        rows = normalize(disassemble(body, address, work, section + "_body"), address, extent, extent, identity)
        swaps, hunks, _ = find_differences(retail_rows, rows, (), {}, True)
        report["functions"].append({
            "symbol": symbol, "extent": extent, "required": required,
            "exact": body == original,
            "different_overlapping_bytes": sum(a != b for a, b in zip(body, original)),
            "base_index_swaps": swaps, "hunks": hunks,
        })
    (work / "comparison.json").write_text(json.dumps(report, indent=2) + "\n")
    print(json.dumps({"functions": [{k: v for k, v in row.items() if k != "hunks"} | {"hunks": len(row["hunks"])} for row in report["functions"]]}, indent=2))


if __name__ == "__main__":
    main()
