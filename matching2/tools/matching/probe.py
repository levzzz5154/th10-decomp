#!/usr/bin/env python3
"""Compile maintained units and compare every owned region with the exact image.

The full build proves the whole executable; this tool gives the same byte gate
for one translation unit in a couple of seconds, so a single function can be
recovered and checked without a complete rebuild. It uses the build's raw
compilation, normalization and region ownership, so a region that reports
EXACT here is byte-identical in the linked executable.

Comparison masks nothing: object bytes must equal the retail bytes, except in
the fields the linker fills. Those four-byte fields are checked separately by
their implied retail target address, which must equal the address the
relocation's symbol is bound to.
"""

import sys
from pathlib import Path

if __package__ in (None, ""):
    sys.path.insert(0, str(Path(__file__).resolve().parents[3]))

import argparse
from collections import defaultdict
import json
import struct

from matching2.tools.common.coff import RELOCATION_TYPES, defined_functions, function_body, read_object
from matching2.tools.common.project_paths import DEFAULT_PROJECT, ROOT, project_support
from matching2.tools.common.wine import DEFAULT_TOOLKIT
from matching2.tools.matching.build_msvc import CompilationPlan, compile_raw, normalize_unit
from matching2.tools.matching.ltcg_cluster import build_cluster
from matching2.tools.matching.gcc_llvm_backend import validate_source_compilers
from matching2.tools.matching.mismatch import instruction_at
from matching2.tools.matching.retail import default_oracle, load_manifest, load_oracle, region_directory


def owned_regions(config, source):
    entries = [region for region in config["regions"] if region["source"] == source]
    if not entries:
        raise ValueError("no maintained region is owned by " + source)
    return sorted(entries, key=lambda region: int(region["address"], 0))


def apply_proposals(regions, proposals, source):
    """Return region records with any probing-only symbol overrides applied."""
    by_address = {int(region["address"], 0): dict(region) for region in regions}
    for proposal in proposals:
        address = int(proposal["address"], 0)
        if address not in by_address:
            raise ValueError(f"proposal at {address:#x} is not owned by {source}")
        current = by_address[address]
        if proposal.get("size", current["size"]) != current["size"]:
            raise ValueError(f"proposal at {address:#x} changes the region extent")
        by_address[address] = {**current, **proposal, "source": source}
    return [by_address[int(region["address"], 0)] for region in regions]


def resolve_regions(regions, obj):
    """Return region records whose symbols name a function the object defines."""
    defined = defined_functions(obj)
    resolved, problems = [], []
    for region in regions:
        if region.get("kind") == "library":
            # Toolkit sections can begin with bytes before their first function.
            # The normalizer validates the selected section and its base symbol.
            resolved.append(region)
            continue
        if region["symbol"] in defined:
            resolved.append(region)
            continue
        # The C++ declaration decides the decoration, so compare the plain name:
        # a cdecl definition adds a leading underscore the decorated forms drop.
        requested = region["symbol"].lstrip("_")
        candidates = [name for name in defined if requested in name.lstrip("_")]
        if len(candidates) == 1:
            resolved.append({**region, "symbol": candidates[0], "requested_symbol": region["symbol"]})
            continue
        problems.append((region, candidates, sorted(defined)))
    if problems:
        lines = []
        for region, candidates, defined_names in problems:
            reason = ("names several compiled functions: " + ", ".join(candidates) if candidates
                      else "matches no compiled function")
            lines.append(f"{region['symbol']} ({region['name']}) {reason}. Compiled functions: "
                         + (", ".join(defined_names) if defined_names else "none"))
        raise ValueError("; ".join(lines))
    return resolved


def compare_region(region, obj, oracle, text_start, bindings, aliases, show):
    """Return a per-region report; 'exact' is the gate the build enforces."""
    address, size = int(region["address"], 0), region["size"]
    function = function_body(obj, region["symbol"], require_external=True)
    name, body = function.name, function.data
    if len(body) != size:
        return {"region": region["name"], "address": address, "size": size, "symbol": name,
                "exact": False, "detail": f"compiled extent {len(body)} differs from {size}"}
    expected = oracle[address - text_start:address - text_start + size]
    ignored = function.linker_bytes()
    differing = [index for index in range(size) if index not in ignored and body[index] != expected[index]]
    report = {"region": region["name"], "address": address, "size": size, "symbol": name,
              "different_bytes": len(differing), "exact": not differing}
    if differing:
        first = address + differing[0]
        report["first_difference"] = first
        window = slice(differing[0], differing[0] + show)
        report["expected_bytes"] = expected[window].hex(" ")
        report["actual_bytes"] = body[window].hex(" ")
        report["expected_instruction"] = instruction_at(expected, address, first)
        report["actual_instruction"] = instruction_at(body, address, first)
        return report
    relocations, problems = [], []
    for relocation in sorted(function.relocations, key=lambda r: r.offset):
        if relocation.kind not in RELOCATION_TYPES:
            continue
        offset, kind = relocation.offset, RELOCATION_TYPES[relocation.kind]
        encoded = struct.unpack_from("<i", expected, offset)[0]
        target = address + offset + 4 + encoded if kind == "rel32" else encoded
        # A member access through a symbol (a struct global's second field, a
        # table element) keeps its offset as the relocation addend inside the
        # object, so the link-time value is the bound address plus that addend.
        addend = struct.unpack_from("<i", body, offset)[0]
        symbol, local = relocation.symbol, relocation.local
        canonical = aliases.get(symbol, symbol)
        bound = bindings.get(canonical)
        if local is not None:
            resolved, bound = address + local + addend, address + local
        else:
            resolved = None if bound is None else bound + addend
        relocations.append({"offset": offset, "kind": kind, "symbol": symbol, "target": target,
                            "bound": bound, "addend": addend, "matches": resolved == target})
        if resolved != target:
            problems.append(f"relocation {symbol}{f'{addend:+#x}' if addend else ''} at +{offset:#x} "
                            f"means {target:#010x} in retail but binds "
                            f"{resolved if resolved is None else f'{resolved:#010x}'}")
    report["relocations"] = relocations
    if problems:
        report["exact"] = False
        report["detail"] = "; ".join(problems)
    return report


def conflicting_definitions(obj, regions, config):
    """Name symbols this unit defines that the layout script also binds.

    The layout script gives every manifest binding a fixed address, so a unit
    that defines one of those names as well would place the same symbol twice.
    """
    owned = {region["symbol"] for region in regions}
    return sorted(name for name in defined_functions(obj)
                  if name in config["symbols"] and name not in owned)


def extra_sections(obj, normalization):
    """Code sections the unit emits that no owned region selects.

    They are dropped by normalization, so they never reach the image; naming
    them shows when a body needs another region (a compiler-generated
    ``__ehhandler`` thunk, an EH-tracked array helper) rather than a code change.
    """
    selected = {region["source_section"] for region in normalization["regions"]}
    return [{"section": s["name"], "size": s["raw_size"]} for s in obj["sections"]
            if s["raw_size"] and s["characteristics"] & 0x20 and s["name"] not in selected]


def probe_unit(project, toolkit, output, config, source, regions, cluster_by_source, index,
               compiler_profiles=None):
    """Compile one unit and resolve its region symbols against the emitted object."""
    if source in cluster_by_source:
        if compiler_profiles is None and config.get('source_compilers'):
            validate_source_compilers(project, config, list(cluster_by_source.values()))
        cluster = cluster_by_source[source]
        unit = build_cluster(cluster, toolkit, output / "clusters" / cluster["name"], config["flags"])
        return unit, [dict(region) for region in cluster["regions"]]
    raw = compile_raw(project, toolkit, output, index, source, config,
                      compiler_profiles=compiler_profiles)
    obj = read_object(raw["object"])
    resolved = resolve_regions(regions, obj)
    normalized = output / "objects" / f"unit{index:04d}.normalized.obj"
    unit = {**raw, **normalize_unit(raw["object"], normalized, source, config, resolved)}
    unit["dropped_sections"] = extra_sections(obj, unit["normalization"])
    return unit, resolved


def main():
    parser = argparse.ArgumentParser(description=__doc__,
                                     formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("--source", action="append", required=True,
                        help="project-relative translation unit to compile and compare")
    parser.add_argument("--project", type=Path, default=DEFAULT_PROJECT)
    parser.add_argument("--toolkit", type=Path, default=DEFAULT_TOOLKIT)
    parser.add_argument("--output", type=Path, default=ROOT / "matching2/build/probe")
    parser.add_argument("--oracle", type=Path, default=None,
                        help="executable holding the required .text bytes")
    parser.add_argument("--proposal", action="append", default=[],
                        help="JSON file of probing-only region overrides ({'regions': [...]})")
    parser.add_argument("--show", type=int, default=16, help="bytes shown for the first difference")
    parser.add_argument("--json", action="store_true", help="print the report as JSON")
    parser.add_argument("--write-proposal", type=Path,
                        help="write the resolved regions of exact units for manifest integration")
    args = parser.parse_args()
    project = args.project.resolve()
    config = load_manifest(project_support(project, 'regions.json'))
    oracle = load_oracle(args.oracle or default_oracle(), config)
    text_start = int(config["text_start"], 0)
    bindings = region_directory(config, config["regions"])
    proposals = defaultdict(list)
    for path in args.proposal:
        for region in json.loads(Path(path).read_text())["regions"]:
            proposals[region["source"]].append(region)
    plan = CompilationPlan.from_manifest(project, config, config["regions"], config["translation_units"])
    requested = set()
    for source in args.source:
        if source not in plan.regions_by_source:
            raise ValueError("no maintained region is owned by " + source)
        cluster = plan.clusters_by_source.get(source)
        requested.add(cluster["source"] if cluster else source)
    report = {"units": {}, "failures": [], "regions": [], "resolved": []}
    for index, source in enumerate(plan.sources):
        if source not in requested:
            continue
        regions = apply_proposals(plan.regions_by_source[source], proposals[source], source)
        try:
            unit, resolved = probe_unit(project, args.toolkit.resolve(), args.output.resolve(),
                                        config, source, regions, plan.clusters_by_source, index,
                                        plan.compiler_profiles)
        except Exception as error:  # compiler and region-extent failures are data, not crashes
            log = args.output / "logs" / f"unit{index:04d}.log"
            detail = log.read_text().strip() if log.is_file() else ""
            report["failures"].append({"source": source, "error": str(error), "compiler_log": detail})
            continue
        report["units"][source] = unit
        obj = read_object(unit["object"])
        conflicts = conflicting_definitions(obj, resolved, config)
        if conflicts:
            report["failures"].append({
                "source": source, "compiler_log": "",
                "error": "unit defines symbols the manifest already binds to fixed addresses: "
                         + ", ".join(conflicts)})
            continue
        aliases = config.get("coff_aliases", {}).get(source, {})
        outcomes = []
        for region in resolved:
            try:
                outcome = compare_region(region, obj, oracle, text_start,
                                         bindings, aliases, args.show)
            except ValueError as error:
                outcome = {"region": region["name"], "address": int(region["address"], 0),
                           "size": region["size"], "symbol": region["symbol"],
                           "exact": False, "detail": str(error)}
            outcome["source"] = region["source"]
            outcomes.append(outcome)
        report["regions"].extend(outcomes)
        if all(outcome["exact"] for outcome in outcomes):
            report["resolved"] += [{key: region.get(key) for key in
                                    ("name", "source", "symbol", "address", "size", "kind", "owner")}
                                   for region in resolved]
    report["exact"] = (not report["failures"]
                       and bool(report["regions"])
                       and all(region["exact"] for region in report["regions"]))
    if args.write_proposal:
        args.write_proposal.write_text(json.dumps(
            {"regions": report["resolved"] if report["exact"] else []}, indent=2) + "\n")
    if args.json:
        print(json.dumps(report, indent=2))
    else:
        for failure in report["failures"]:
            print(f"{failure['source']}: FAILED TO COMPILE\n{failure['error']}")
            if failure["compiler_log"]:
                print(failure["compiler_log"])
        for region in report["regions"]:
            status = "EXACT" if region["exact"] else "DIFFERENT"
            print(f"{region['address']:#010x} {region['size']:>7} bytes  {region['symbol']}  {status}")
            if region["exact"]:
                continue
            if "expected_bytes" in region:
                print(f"  first difference at {region['first_difference']:#010x}")
                print(f"  expected: {region['expected_bytes']}   {region['expected_instruction']}")
                print(f"  actual:   {region['actual_bytes']}   {region['actual_instruction']}")
            if "detail" in region:
                print("  " + region["detail"])
        for source, unit in sorted(report["units"].items()):
            for section in unit.get("dropped_sections", []):
                print(f"{source}: emits {section['section']} ({section['size']} bytes) that no region "
                      f"selects; normalization drops it")
    print("EXACT" if report["exact"] else "NOT EXACT", file=sys.stderr)
    return 0 if report["exact"] else 1


if __name__ == "__main__":
    sys.exit(main())
