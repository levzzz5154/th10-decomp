#!/usr/bin/env python3
"""Replace transcribed runtime-library assembly with the toolkit's own objects.

The retail linker copied the static C/C++ runtime into ``th10.exe`` from the
libraries that ship with the project's toolkit.  Every such function is one
whole ``/Gy`` section of a library member, byte-identical to retail except in
the relocation fields the linker filled.  This tool finds those sections,
derives where each relocation target sits in retail, and rewrites the manifest
so the build links the library section itself (a ``library`` region) instead of
an inline-assembly transcription of it.

A candidate is adopted only when:

* the whole section equals retail outside its relocation fields and exactly
  covers consecutive manifest regions, at least one of them assembly or C++
  built by a non-toolkit ``source_compilers`` profile (other runtime functions
  recovered as C++ are kept);
* every relocation target it implies agrees with the manifest's existing symbol
  addresses and with every other adopted section;
* no symbol it defines collides with a definition elsewhere.

Derived addresses are recorded in the manifest's ``symbols`` table, which the
fixed-address link already uses; a static the section references in a section
the build does not link is given a unique alias through ``coff_aliases``.  The
normal build never reads the retail executable.

Usage:
    python3 adopt_crt_library.py [--dry-run] [--toolkit PATH]
"""
from __future__ import annotations

import argparse
import json
import re
import struct
import sys
import tempfile
from collections import defaultdict
from pathlib import Path

ROOT = Path(__file__).resolve().parents[3]
sys.path.insert(0, str(ROOT))

from matching2.tools.common.coff_regions import _read_object
from matching2.tools.common.library import ar_members, library_source, split_library_source
from matching2.tools.common.pe import PEImage
from matching2.tools.common.wine import DEFAULT_TOOLKIT

PROJECT = ROOT / "matching2/msvc"
ORACLE = ROOT / "matching2/build/oracle/th10.exe"
# Retail is a /MT build: prefer the multithreaded runtime when both agree.
LIBRARIES = ("libcmt.lib", "libcpmt.lib", "libc.lib", "libcp.lib")
CRT_START = 0x00452000
DIR32, REL32 = 0x0006, 0x0014
EXTERNAL, WEAK_EXTERNAL = 2, 105


def scan(toolkit, manifest, text):
    """Yield every whole library code section that equals retail at a region start."""
    text_start = int(manifest["text_start"], 0)
    regions = sorted(manifest["regions"], key=lambda region: int(region["address"], 0))
    index_of = {int(region["address"], 0): index for index, region in enumerate(regions)}

    def cover(address, size):
        index, cursor, covered = index_of.get(address), address, []
        if index is None:
            return None
        while cursor < address + size and index < len(regions):
            covered.append(regions[index])
            cursor += regions[index]["size"]
            index += 1
        return covered if cursor == address + size else None

    starts = sorted(address for address in index_of if address >= CRT_START)
    foreign = set(manifest.get("source_compilers", {}))
    with tempfile.TemporaryDirectory() as scratch:
        path = Path(scratch) / "member.obj"
        for rank, library in enumerate(LIBRARIES):
            for member, blob in ar_members(toolkit / "lib" / library):
                if blob[:2] != b"\x4c\x01":
                    continue
                path.write_bytes(blob)
                try:
                    obj = _read_object(path)
                except Exception:
                    continue
                for section in obj["sections"]:
                    raw = section["raw"]
                    if not section["characteristics"] & 0x20 or not raw:
                        continue
                    if any(r["type"] not in (DIR32, REL32) for r in section["relocations"]):
                        continue
                    masked = set()
                    for relocation in section["relocations"]:
                        masked.update(range(relocation["virtual_address"], relocation["virtual_address"] + 4))
                    for address in starts:
                        offset = address - text_start
                        goal = text[offset:offset + len(raw)]
                        if goal != raw and (len(goal) != len(raw) or any(
                                raw[k] != goal[k] for k in range(len(raw)) if k not in masked)):
                            continue
                        covered = cover(address, len(raw))
                        # Hand-recovered C++ of a runtime function is kept unless
                        # the section also retires assembly, or the C++ needs a
                        # non-toolkit compiler profile: the library body is
                        # then that function's own source.
                        if not covered or not any(region["kind"] == "asm" or region["source"] in foreign
                                                  for region in covered):
                            continue
                        yield plan_candidate(obj, section, library, member, rank, address, text, text_start,
                                             covered)


def plan_candidate(obj, section, library, member, rank, address, text, text_start, covered):
    """Describe what linking this section at ``address`` requires and defines."""
    number = section["number"]
    defines, entry = {}, None
    for record in obj["records"]:
        if record["section_number"] != number or not record["name"] or record["name"] == section["name"]:
            continue
        if record["storage_class"] in (EXTERNAL, WEAK_EXTERNAL):
            defines[record["name"]] = address + record["value"]
        if record["value"] == 0 and (entry is None or record["storage_class"] == EXTERNAL):
            entry = record
    references = []
    for relocation in section["relocations"]:
        target = obj["record_by_index"][obj["index_to_primary"][relocation["symbol_index"]]]
        field_offset = relocation["virtual_address"]
        field = struct.unpack_from("<I", text, address - text_start + field_offset)[0]
        addend = struct.unpack_from("<I", section["raw"], field_offset)[0]
        if relocation["type"] == DIR32:
            value = (field - addend) & 0xFFFFFFFF
        else:
            value = (field + address + field_offset + 4 - addend) & 0xFFFFFFFF
        references.append({"name": target["name"], "section_number": target["section_number"],
                           "storage_class": target["storage_class"], "address": value,
                           "self": target["section_number"] == number})
    return {"library": library, "member": member, "rank": rank, "section_number": number,
            "section": section["name"], "address": address, "size": len(section["raw"]),
            "entry": entry and entry["name"], "defines": defines, "references": references,
            "covered": covered}


def alias_name(library, member, name):
    stem = re.sub(r"[^0-9A-Za-z]+", "_", f"{Path(library).stem}_{Path(member).stem}_{name}").strip("_")
    return f"_crt_{stem}"


def plan_names(candidate, assigned):
    """Choose the linked spelling of every symbol a candidate defines or needs.

    A runtime name keeps its spelling unless the manifest already binds it to a
    different address (some names were attributed by signature matching and
    point at a sibling copy, such as the memmove body at 0x00453280 bound as
    ``_memcpy``).  Such a name, and every static the section reaches in an
    unlinked section, is aliased within this library unit to a unique spelling.
    Returns ``{input name: (linked name, address)}`` or None if inconsistent.
    """
    library, member = candidate["library"], candidate["member"]
    wanted = [(name, address) for name, address in candidate["defines"].items()]
    if candidate["entry"] not in candidate["defines"]:
        wanted.append((candidate["entry"], candidate["address"]))
    for reference in candidate["references"]:
        if reference["self"]:
            continue
        if reference["storage_class"] in (EXTERNAL, WEAK_EXTERNAL):
            wanted.append((reference["name"], reference["address"]))
        else:
            wanted.append((("static", reference["name"]), reference["address"]))
    plan = {}
    for name, address in wanted:
        if isinstance(name, tuple):
            linked = alias_name(library, member, name[1])
        elif assigned.get(name, address) == address:
            linked = name
        else:
            linked = alias_name(library, member, name)
        if plan.get(name, (linked, address)) != (linked, address):
            return None
        if assigned.get(linked, address) != address:
            return None
        plan[name] = (linked, address)
    return plan


def choose(candidates, manifest):
    """Pick at most one consistent candidate per address."""
    replaced = {region["symbol"] for candidate in candidates for region in candidate["covered"]}
    assigned = {name: int(address, 0) for name, address in manifest["symbols"].items()}
    for region in manifest["regions"]:
        if region["symbol"] not in replaced:
            assigned.setdefault(region["symbol"], int(region["address"], 0))
    by_address = defaultdict(list)
    for candidate in candidates:
        if candidate["entry"]:
            by_address[candidate["address"]].append(candidate)
    # Identical bodies (memcpy/memmove) match at each other's address; the
    # relocations of the other runtime sections say which name lives where.
    votes = defaultdict(int)
    for candidate in candidates:
        for reference in candidate["references"]:
            if reference["storage_class"] in (EXTERNAL, WEAK_EXTERNAL):
                votes[(reference["name"], reference["address"])] += 1
    chosen, taken, placed = [], set(), set()
    placement, required = {}, {}
    for region in manifest["regions"]:
        if region["kind"] == "library":
            library, member = split_library_source(region["source"])
            key = (library, member, region["library_section_number"])
            placement[key] = int(region["address"], 0)
            placed.add(key)
    for address in sorted(by_address):
        for candidate in sorted(by_address[address], key=lambda item: (
                -item["size"], -votes[(item["entry"], address)], item["rank"])):
            span = range(address, address + candidate["size"])
            key = (candidate["library"], candidate["member"], candidate["section_number"])
            if taken & set(span) or key in placed:
                continue
            plan = plan_names(candidate, assigned)
            if plan is None:
                continue
            # A static reached in another section of the same member must be
            # that section's placement, if it is placed at all.
            member = candidate["library"], candidate["member"]
            needs = {(*member, reference["section_number"]): reference["address"]
                     for reference in candidate["references"]
                     if not reference["self"] and reference["section_number"] > 0}
            if needs.get(key, address) != address or any(
                    placement.get(section, value) != value or required.get(section, value) != value
                    for section, value in needs.items()) or required.get(key, address) != address:
                continue
            placement[key] = address
            required.update(needs)
            candidate["names"] = plan
            assigned.update({linked: value for linked, value in plan.values()})
            taken.update(span)
            placed.add(key)
            chosen.append(candidate)
            break
    return chosen


def rewrite(manifest, chosen, project, dry_run):
    by_member = defaultdict(list)
    for candidate in chosen:
        by_member[(candidate["library"], candidate["member"])].append(candidate)
    removed = {region["address"] for candidate in chosen for region in candidate["covered"]}
    old_sources = {region["source"] for candidate in chosen for region in candidate["covered"]}
    regions = [region for region in manifest["regions"] if region["address"] not in removed]
    symbols = manifest["symbols"]
    aliases = manifest.setdefault("coff_aliases", {})
    for candidate in chosen:
        for region in candidate["covered"]:
            symbols.setdefault(region["symbol"], region["address"])
    for (library, member), members in by_member.items():
        source = library_source(library, member)
        linked_sections = {candidate["section_number"] for candidate in members}
        unit_aliases = {}
        for candidate in members:
            names = candidate["names"]
            entry = names[candidate["entry"]][0]
            regions.append({
                "name": f"library_{candidate['entry'].lstrip('_?@$')}_{candidate['address']:08x}",
                "source": source, "symbol": entry,
                "address": f"0x{candidate['address']:08X}", "size": candidate["size"],
                "kind": "library", "owner": f"0x{candidate['address']:08X}",
                "library_section": candidate["section"],
                "library_section_number": candidate["section_number"],
                "library_entry": candidate["entry"],
            })
            for name, (linked, address) in names.items():
                static = isinstance(name, tuple)
                spelling = name[1] if static else name
                if static and any(reference["name"] == spelling and reference["section_number"] in linked_sections
                                  for reference in candidate["references"]):
                    continue
                if linked != spelling:
                    unit_aliases[spelling] = linked
                if name not in candidate["defines"] and name != candidate["entry"]:
                    symbols.setdefault(linked, f"0x{address:08X}")
        if unit_aliases:
            aliases.setdefault(source, {}).update(unit_aliases)
    # A later adoption can alias a name an earlier one used as an entry (a
    # static first reached while its section was unlinked, or a name the
    # manifest had bound elsewhere); the unit then defines the alias.
    for region in regions:
        if region["kind"] == "library":
            region["symbol"] = aliases.get(region["source"], {}).get(region["library_entry"],
                                                                     region["library_entry"])
            bound = symbols.get(region["symbol"])
            if bound is not None and int(bound, 0) != int(region["address"], 0):
                raise ValueError(f"{region['name']}: {region['symbol']} is bound to {bound}")
    regions.sort(key=lambda region: int(region["address"], 0))
    manifest["regions"] = regions
    owning = {region["source"] for region in regions} | {region["source"] for region in manifest["dos_regions"]}
    orphaned = sorted(source for source in old_sources if source not in owning)
    units = set(manifest["translation_units"]) - set(orphaned)
    units |= {region["source"] for region in regions}
    manifest["translation_units"] = sorted(units)
    for key in ("coff_aliases", "source_flags", "source_compilers"):
        for source in orphaned:
            manifest.get(key, {}).pop(source, None)
    if not dry_run:
        for source in orphaned:
            (project / source).unlink()
    return orphaned


from matching2.tools.common.project_paths import project_support
def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--project", type=Path, default=PROJECT)
    parser.add_argument("--toolkit", type=Path, default=DEFAULT_TOOLKIT)
    parser.add_argument("--oracle", type=Path, default=ORACLE)
    parser.add_argument("--dry-run", action="store_true")
    args = parser.parse_args()
    project = args.project.resolve()
    manifest_path = project_support(project, 'regions.json')
    manifest = json.loads(manifest_path.read_text())
    text = PEImage(args.oracle.read_bytes()).read(int(manifest["text_start"], 0), manifest["text_bytes"])
    clustered = set()
    for cluster_path in manifest.get("ltcg_clusters", []):
        cluster = json.loads((project / cluster_path).read_text())
        clustered.add(cluster.get("source"))
        clustered.update(cluster.get("additional_sources", []))
    total = 0
    while True:
        candidates = [candidate for candidate in scan(args.toolkit.resolve(), manifest, text)
                      if not any(region["source"] in clustered or region["kind"] == "library"
                                 for region in candidate["covered"])]
        chosen = choose(candidates, manifest)
        if not chosen:
            break
        asm = sum(region["size"] for candidate in chosen for region in candidate["covered"]
                  if region["kind"] == "asm")
        print(f"{len(candidates)} matching section placements; adopting {len(chosen)} sections "
              f"({sum(c['size'] for c in chosen):,} bytes, {asm:,} of them assembly)")
        orphaned = rewrite(manifest, chosen, project, args.dry_run)
        print(f"{len(orphaned)} assembly sources no longer own a region")
        total += len(chosen)
    print(f"adopted {total} library sections")
    if not args.dry_run:
        manifest_path.write_text(json.dumps(manifest, indent=2) + "\n")
    return 0


if __name__ == "__main__":
    sys.exit(main())
