#!/usr/bin/env python3
"""Compile maintained units and compare every owned region with the exact image.

The full build proves the whole executable; this tool gives the same byte gate
for one translation unit in a couple of seconds, so a single function can be
recovered and checked without a complete rebuild. It consumes the same compile
path (``compile_unit``) and the same region ownership as the build, so a region
that reports EXACT here is byte-identical in the linked executable.

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
import os
import struct

from matching2.tools.common.coff import read_coff_function
from matching2.tools.common.coff_regions import CoffRegionError
from matching2.tools.common.pe import PEImage
from matching2.tools.common.process import sha
from matching2.tools.common.wine import DEFAULT_TOOLKIT
from matching2.tools.matching.build_msvc import ROOT, compile_raw, normalize_unit
from matching2.tools.matching.ltcg_cluster import build_cluster, load_clusters
from matching2.tools.matching.mismatch import instruction_at

DEFAULT_PROJECT = ROOT / "matching2/msvc"
ORACLE_CANDIDATES = (Path(os.environ.get("TH10_ORACLE", "/nonexistent")),
                     ROOT / "matching2/build/oracle/th10.exe",
                     ROOT / "matching2/build/msvc/th10.exe")
RELOCATION_TYPES = {0x0006: "dir32", 0x0014: "rel32"}


def default_oracle():
    """Prefer a stable copy: a running build deletes the build output mid-flight."""
    for candidate in ORACLE_CANDIDATES:
        if candidate.is_file():
            return candidate
    return ORACLE_CANDIDATES[-1]


def load_manifest(path):
    config = json.loads(path.read_text())
    reference = json.loads((path.parent / "pe_layout.json").read_text())["reference"]
    if config["text_sha256"] != reference["text_section_sha256"]:
        raise ValueError("project manifest does not match the supported retail image")
    return config


def load_oracle(path, config):
    image = PEImage(Path(path).read_bytes())
    raw = image.read(int(config["text_start"], 0), config["text_bytes"])
    if sha(raw) != config["text_sha256"]:
        raise ValueError(f"{path} does not contain the supported .text bytes")
    return raw


def region_directory(config, regions):
    """Map every defined name to its address for relocation target checks."""
    bindings = {name: int(address, 0) for name, address in config["symbols"].items()}
    for region in regions:
        bindings.setdefault(region["symbol"], int(region["address"], 0))
    return bindings


def owned_regions(config, source):
    entries = [region for region in [*config["regions"], *config["dos_regions"]]
               if region["source"] == source]
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


def defined_functions(object_path):
    """Map each defined function symbol to its section number.

    A recovered function's C++ declaration decides its decorated name, so a
    region only names the intended function. Resolution accepts an exact name
    or a unique substring of the emitted one, which is how a member function or
    an overloaded name is addressed without spelling MSVC's decoration.
    """
    data = Path(object_path).read_bytes()
    _, section_count, _, symbol_offset, symbol_count, optional_size, _ = \
        struct.unpack_from("<HHIIIHH", data, 0)
    strings = data[symbol_offset + symbol_count * 18:]
    symbols, index = {}, 0
    while index < symbol_count:
        offset = symbol_offset + index * 18
        raw_name, _, section, symbol_type, storage, aux = struct.unpack_from("<8sIhHBB", data, offset)
        if raw_name[:4] == b"\0\0\0\0":
            start = struct.unpack_from("<I", raw_name, 4)[0]
            text = strings[start:strings.find(b"\0", start)].decode("ascii")
        else:
            text = raw_name.rstrip(b"\0").decode("ascii")
        if section > 0 and storage in (2, 3) and symbol_type & 0x20:
            symbols[text] = section
        index += 1 + aux
    return symbols


def resolve_regions(regions, object_path):
    """Return region records whose symbols name a function the object defines."""
    defined = defined_functions(object_path)
    resolved, problems = [], []
    for region in regions:
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


def compare_region(region, object_path, oracle, text_start, bindings, aliases, show):
    """Return a per-region report; 'exact' is the gate the build enforces."""
    address, size = int(region["address"], 0), region["size"]
    name, body, ignored = read_coff_function(object_path, region["symbol"])
    if len(body) != size:
        return {"region": region["name"], "address": address, "size": size, "symbol": name,
                "exact": False, "detail": f"compiled extent {len(body)} differs from {size}"}
    expected = oracle[address - text_start:address - text_start + size]
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
    targets = relocation_targets(object_path, name)
    for offset, kind in sorted(relocation_offsets(object_path, name).items()):
        encoded = struct.unpack_from("<i", expected, offset)[0]
        target = address + offset + 4 + encoded if kind == "rel32" else encoded
        # A member access through a symbol (a struct global's second field, a
        # table element) keeps its offset as the relocation addend inside the
        # object, so the link-time value is the bound address plus that addend.
        addend = struct.unpack_from("<i", body, offset)[0]
        symbol, local = targets[offset]
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


def relocation_table(object_path, symbol):
    """Read the relocation rows of the section that defines symbol."""
    data = Path(object_path).read_bytes()
    _, section_count, _, symbol_offset, symbol_count, optional_size, _ = \
        struct.unpack_from("<HHIIIHH", data, 0)
    table = 20 + optional_size
    sections = [struct.unpack_from("<8sIIIIIIHHI", data, table + index * 40)
                for index in range(section_count)]
    strings = data[symbol_offset + symbol_count * 18:]
    names, value_section = {}, {}
    index = 0
    while index < symbol_count:
        offset = symbol_offset + index * 18
        raw_name, value, section, _, storage, aux = struct.unpack_from("<8sIhHBB", data, offset)
        if raw_name[:4] == b"\0\0\0\0":
            start = struct.unpack_from("<I", raw_name, 4)[0]
            text = strings[start:strings.find(b"\0", start)].decode("ascii")
        else:
            text = raw_name.rstrip(b"\0").decode("ascii")
        names[index], value_section[index] = text, (value, section, storage)
        index += 1 + aux
    owners = [number for number, (_, section, storage) in value_section.items()
              if names[number] == symbol and section > 0 and storage == 2]
    if len(owners) != 1:
        raise ValueError(f"expected one definition of {symbol}, found {len(owners)}")
    section_index = value_section[owners[0]][1] - 1
    rows = []
    for index in range(sections[section_index][7]):
        offset = sections[section_index][5] + index * 10
        virtual_address, symbol_index, kind = struct.unpack_from("<IIH", data, offset)
        # A relocation may name a label the same object defines, such as the
        # compiler's own basic-block symbols; the object already fixes where it
        # lands, so no binding is needed for it.
        value, section, _ = value_section.get(symbol_index, (0, 0, 0))
        local = value if section == section_index + 1 else None
        rows.append((virtual_address, names.get(symbol_index, "?"), kind, local))
    return rows


def relocation_offsets(object_path, symbol):
    return {offset: RELOCATION_TYPES[kind]
            for offset, _, kind, _ in relocation_table(object_path, symbol)
            if kind in RELOCATION_TYPES}


def relocation_targets(object_path, symbol):
    """Map each relocation offset to its symbol name and same-section target."""
    return {offset: (name, local) for offset, name, kind, local in relocation_table(object_path, symbol)
            if kind in RELOCATION_TYPES}


def conflicting_definitions(object_path, regions, config):
    """Name symbols this unit defines that the layout script also binds.

    The layout script gives every manifest binding a fixed address, so a unit
    that defines one of those names as well would place the same symbol twice.
    """
    owned = {region["symbol"] for region in regions}
    return sorted(name for name in defined_functions(object_path)
                  if name in config["symbols"] and name not in owned)


def extra_sections(object_path, normalization):
    """Code sections the unit emits that no owned region selects.

    They are dropped by normalization, so they never reach the image; naming
    them shows when a body needs another region (a compiler-generated
    ``__ehhandler`` thunk, an EH-tracked array helper) rather than a code change.
    """
    data = Path(object_path).read_bytes()
    _, section_count, _, _, _, optional_size, _ = struct.unpack_from("<HHIIIHH", data, 0)
    table = 20 + optional_size
    selected = {region["source_section"] for region in normalization["regions"]}
    extra = []
    for index in range(section_count):
        name, _, _, size, _, _, _, _, _, characteristics = \
            struct.unpack_from("<8sIIIIIIHHI", data, table + index * 40)
        text = name.rstrip(b"\0").decode("ascii", "replace")
        if size and characteristics & 0x20 and text not in selected:
            extra.append({"section": text, "size": size})
    return extra


def probe_unit(project, toolkit, output, config, source, regions, cluster_by_source, index):
    """Compile one unit and resolve its region symbols against the emitted object."""
    if source in cluster_by_source:
        cluster = cluster_by_source[source]
        unit = build_cluster(cluster, toolkit, output / "clusters" / cluster["name"], config["flags"])
        return unit, [dict(region) for region in cluster["regions"]]
    raw = compile_raw(project, toolkit, output, index, source, config)
    resolved = resolve_regions(regions, raw["object"])
    normalized = output / "objects" / f"unit{index:04d}.normalized.obj"
    unit = {**raw, **normalize_unit(raw["object"], normalized, source, config, resolved)}
    unit["dropped_sections"] = extra_sections(raw["object"], unit["normalization"])
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
    config = load_manifest(project / "regions.json")
    oracle = load_oracle(args.oracle or default_oracle(), config)
    text_start = int(config["text_start"], 0)
    bindings = region_directory(config, [*config["regions"], *config["dos_regions"]])
    regions_by_source = defaultdict(list)
    for region in [*config["regions"], *config["dos_regions"]]:
        regions_by_source[region["source"]].append(region)
    proposals = defaultdict(list)
    for path in args.proposal:
        for region in json.loads(Path(path).read_text())["regions"]:
            proposals[region["source"]].append(region)
    for source in args.source:
        regions_by_source.setdefault(source, owned_regions(config, source))
    clusters = load_clusters(project, config, config["regions"])
    cluster_by_source = {
        source: cluster for cluster in clusters for source in cluster["source_names"]
    }
    cluster_additional_sources = {
        source for cluster in clusters for source in cluster["additional_sources"]
    }
    units = sorted((set(config["translation_units"]) - cluster_additional_sources)
                   | set(args.source))
    report = {"units": {}, "failures": [], "regions": [], "resolved": []}
    for index, source in enumerate(units):
        if source not in args.source:
            continue
        regions = apply_proposals(owned_regions(config, source), proposals[source], source)
        try:
            unit, resolved = probe_unit(project, args.toolkit.resolve(), args.output.resolve(),
                                        config, source, regions, cluster_by_source, index)
        except Exception as error:  # compiler and region-extent failures are data, not crashes
            log = args.output / "logs" / f"unit{index:04d}.log"
            detail = log.read_text().strip() if log.is_file() else ""
            report["failures"].append({"source": source, "error": str(error), "compiler_log": detail})
            continue
        report["units"][source] = unit
        conflicts = conflicting_definitions(unit["object"], resolved, config)
        if conflicts:
            report["failures"].append({
                "source": source, "compiler_log": "",
                "error": "unit defines symbols the manifest already binds to fixed addresses: "
                         + ", ".join(conflicts)})
            continue
        aliases = config.get("coff_aliases", {}).get(source, {})
        for region in resolved:
            try:
                outcome = compare_region(region, unit["object"], oracle, text_start,
                                         bindings, aliases, args.show)
            except (CoffRegionError, ValueError) as error:
                outcome = {"region": region["name"], "address": int(region["address"], 0),
                           "size": region["size"], "symbol": region["symbol"],
                           "exact": False, "detail": str(error)}
            outcome["source"] = source
            report["regions"].append(outcome)
        if all(region["exact"] for region in report["regions"] if region["source"] == source):
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
