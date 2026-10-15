#!/usr/bin/env python3
"""Find remaining assembly regions that are CRT code from the project toolkit.

The project's toolchain ships the exact libraries the retail binary was built
with. A CRT function compiled into the image is byte-identical to the library's
copy except in its relocation fields, because the linker only rewrote those. So a
region whose bytes match a library ``.text`` section, outside the relocation
offsets, is that CRT function — and its readable source is the CRT's own.

This tool searches every ``.lib`` beside the compiler, section by section, and
reports which manifest regions are matches, together with the member that holds
them. Nothing is modified: it is the evidence needed to decide whether to rebuild
a unit from the matching source or to keep the region as assembly.

Usage:
    python3 match_crt.py [--min-size 8] [--toolkit PATH]
"""
from __future__ import annotations

import argparse
import json
import struct
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[3]
sys.path.insert(0, str(ROOT))

from matching2.tools.common.library import ar_members
from matching2.tools.common.pe import PEImage
from matching2.tools.common.wine import DEFAULT_TOOLKIT

from matching2.tools.common.project_paths import project_support
MANIFEST = project_support((ROOT) / 'matching2/msvc', 'regions.json')
ORACLE = ROOT / "matching2/build/oracle/th10.exe"


def coff_sections(blob):
    """Return (section name, bytes, relocation offsets) for each section."""
    if len(blob) < 20:
        return []
    machine, count, _, _, _, optional, _ = struct.unpack_from("<HHIIIHH", blob, 0)
    if machine != 0x14C:
        return []
    table, sections = 20 + optional, []
    for index in range(count):
        if table + (index + 1) * 40 > len(blob):
            return []
        name, _, _, size, raw, reloc, _, reloc_count, _, characteristics = \
            struct.unpack_from("<8sIIIIIIHHI", blob, table + index * 40)
        if not (characteristics & 0x20) or not size or raw + size > len(blob):
            continue
        masked = set()
        for entry in range(reloc_count):
            position = reloc + entry * 10
            if position + 10 > len(blob):
                break
            address, _, kind = struct.unpack_from("<IIH", blob, position)
            if kind in (0x0006, 0x0014):
                masked.update(range(address, address + 4))
        sections.append({"name": name.rstrip(b"\0").decode("latin1"),
                         "bytes": blob[raw:raw + size], "masked": masked})
    return sections


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--project", type=Path, default=ROOT / "matching2/msvc")
    parser.add_argument("--toolkit", type=Path, default=DEFAULT_TOOLKIT)
    parser.add_argument("--min-size", type=int, default=8)
    parser.add_argument("--limit", type=int, default=0, help="stop after this many matches")
    args = parser.parse_args()
    manifest = json.loads((project_support(args.project.resolve(), 'regions.json')).read_text())
    text_start = int(manifest["text_start"], 0)
    raw = PEImage(ORACLE.read_bytes()).read(text_start, manifest["text_bytes"])
    pending = [region for region in manifest["regions"]
               if region["kind"] == "asm" and region.get("owner")
               and int(region["owner"], 0) == int(region["address"], 0)
               and region["size"] >= args.min_size]
    by_size = {}
    for region in pending:
        by_size.setdefault(region["size"], []).append(region)
    print(f"{len(pending)} owned assembly region(s) at or above {args.min_size} bytes, "
          f"{len(by_size)} distinct extents")
    libs = sorted(args.toolkit.resolve().glob("lib/*.lib"))
    matches, scanned, sections_total = [], 0, 0
    for library in libs:
        for name, blob in ar_members(library):
            sections = coff_sections(blob)
            if not sections:
                continue
            scanned += 1
            for section in sections:
                size = len(section["bytes"])
                if size not in by_size:
                    continue
                sections_total += 1
                for region in by_size[size]:
                    address = int(region["address"], 0)
                    goal = raw[address - text_start:address - text_start + size]
                    masked = section["masked"]
                    if all(index in masked or section["bytes"][index] == goal[index]
                           for index in range(size)):
                        matches.append({"address": region["address"], "size": size,
                                        "source": region["source"], "name": region["name"],
                                        "library": library.name, "member": name,
                                        "section": section["name"]})
    print(f"scanned {scanned} object(s) in {len(libs)} library file(s); "
          f"{sections_total} section(s) had a matching extent")
    print(f"{len(matches)} region(s) match a library section on the non-relocation bytes")
    for match in matches[:args.limit or len(matches)]:
        print(f"  {match['address']} {match['size']:6d}  {match['library']}:{match['member']} "
              f"({match['section']})  {match['source']}")
    report = ROOT / "matching2/build/waves/crt-matches.json"
    report.parent.mkdir(parents=True, exist_ok=True)
    report.write_text(json.dumps({"matches": matches}, indent=2) + "\n")
    covered = sum(match["size"] for match in matches)
    print(f"total {covered} bytes; report at {report}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
