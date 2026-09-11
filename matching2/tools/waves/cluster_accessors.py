#!/usr/bin/env python3
"""Recover retail's EAX-convention field accessors as native-LTCG clusters.

Retail compiled the tiny accessors with ``this`` in EAX, a convention MSVC only
chooses during a native ``/GL`` link, so a plain translation unit can never
reproduce them. They are, however, mechanically uniform: the body is one load or
store through EAX at a fixed offset, and the same synthetic array-walking context
caller forces the convention every time.

For each recognisable region this tool writes the body, the context driver and
the cluster layout, registers it, probes, and rolls the whole thing back if the
bytes do not match — so a region that resists leaves the tree exactly as it was.

Usage:
    python3 cluster_accessors.py [--limit N] [--apply]
"""
from __future__ import annotations

import argparse
import json
import re
import shutil
import struct
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[3]
sys.path.insert(0, str(ROOT))

from matching2.tools.common.pe import PEImage
from matching2.tools.matching.probe import DEFAULT_PROJECT

MANIFEST = ROOT / "matching2/msvc/regions.json"
ORACLE = ROOT / "matching2/build/oracle/th10.exe"
WAVE = ROOT / "matching2/build/waves"
PROBE = ROOT / "matching2/tools/matching/probe.py"
REGISTER = ROOT / "matching2/tools/waves/register_cluster.py"

def struct_name(address):
    """A distinct type per region: the manifest needs one unique symbol each."""
    return "ObjectAccessor_%08x" % address


def accessor_symbol(kind, address):
    owner = struct_name(address)
    return f"?LoadValue@{owner}@@QBEHXZ" if kind == "load" else f"?StoreValue@{owner}@@QAEXH@Z"


def context_symbol(kind, address):
    owner = struct_name(address)
    arity = "H" if kind == "load" else "HH"
    return f"?AccessorCompilerContext@@YGHPAPAU{owner}@@{arity}@Z"


def shape(body):
    """The accessor a retail body implements, or None when it is something else."""
    if body == b"\x8b\x00\xc3":
        return ("load", 0)
    if body == b"\x89\x08\xc3":
        return ("store", 0)
    if len(body) == 4 and body[0] == 0x8B and body[1] == 0x40 and body[3] == 0xC3:
        return ("load", body[2])
    if len(body) == 4 and body[0] == 0x89 and body[1] == 0x48 and body[3] == 0xC3:
        return ("store", body[2])
    if len(body) == 7 and body[:2] == b"\x8b\x80" and body[6] == 0xC3:
        return ("load", struct.unpack_from("<I", body, 2)[0])
    if len(body) == 7 and body[:2] == b"\x89\x88" and body[6] == 0xC3:
        return ("store", struct.unpack_from("<I", body, 2)[0])
    return None


def source_text(kind, offset, address):
    """The recovered translation unit: one struct field and the one accessor.

    Only the accessor being recovered is defined — a cluster's object may not
    emit any function its layout does not declare — and the type is named after
    the region so every cluster declares a distinct symbol.
    """
    owner = struct_name(address)
    pad = f"    unsigned char pad_000[0x{offset:x}];\n" if offset else ""
    if kind == "load":
        declaration = "int LoadValue() const"
        definition = (f"int {owner}::LoadValue() const {{\n"
                      f"    return field_{offset:03x};\n}}\n")
    else:
        declaration = "void StoreValue(int value)"
        definition = (f"void {owner}::StoreValue(int value) {{\n"
                      f"    field_{offset:03x} = value;\n}}\n")
    guard = (f"typedef char {owner}_size_must_fit["
             f"sizeof({owner}) == 0x{offset + 4:x} ? 1 : -1];\n")
    return (
        f"// 0x{address:08X}: {kind} the object field at +0x{offset:x}.\n"
        "// The object pointer arrives in EAX, which only a native LTCG link\n"
        "// chooses, so this region is compiled as a cluster.\n\n"
        f"struct {owner} {{\n"
        f"{pad}    int field_{offset:03x};\n"
        f"    __declspec(noinline) {declaration};\n"
        "};\n"
        f"{guard}\n"
        '#pragma code_seg(".text$01accessor")\n'
        f"{definition}"
        "#pragma code_seg()\n"
    )


def driver_text(kind, address):
    """A synthetic caller whose codegen forces the object pointer into EAX."""
    owner = struct_name(address)
    if kind == "load":
        body = (f"int __stdcall AccessorCompilerContext({owner}** items, int count) {{\n"
                "    int total = 0;\n"
                "    while (count--) {\n"
                "        total += (*items++)->LoadValue();\n"
                "    }\n"
                "    return total;\n}\n")
    else:
        body = (f"int __stdcall AccessorCompilerContext({owner}** items, int count, int value) {{\n"
                "    while (count--) {\n"
                "        (*items++)->StoreValue(value);\n"
                "    }\n"
                "    return 0;\n}\n")
    return ("// Compiler context only; never selected as recovered game code.\n"
            '#include "../../%s"\n\n'
            '#pragma code_seg(".text$03context")\n'
            + body +
            "#pragma code_seg()\n")


def layout_text(name, source, address, size, context_address, context_size, kind):
    return json.dumps({
        "schema_version": 1, "name": name, "source": source,
        "driver": f"layout/ltcg/{name}_context.cpp", "headers": [],
        "image_base": "0x00400000",
        "description": "Accessor compiled with native LTCG so the object pointer arrives in EAX.",
        "functions": [{"name": "ObjectAccessor_Accessor",
                       "symbol": accessor_symbol(kind, address),
                       "section": ".text$01accessor", "address": f"0x{address:08X}", "size": size,
                       "actual_abi": "object in EAX; plain RET"}],
        "context": {"symbol": context_symbol(kind, address), "section": ".text$03context",
                    "address": f"0x{context_address:08X}", "size": context_size,
                    "description": "Synthetic array-walking caller that establishes the "
                                   "observed register convention; not recovered game code."},
        "gaps": [{"section": ".text$00layout", "address": "0x00401000",
                  "size": address - 0x401000},
                 {"section": ".text$02layout", "address": f"0x{address + size:08X}",
                  "size": context_address - (address + size)}],
        "constants": [], "absolute_symbols": [],
    }, indent=2) + "\n"


def run(command, timeout=900):
    return subprocess.run(command, capture_output=True, text=True, timeout=timeout)


def probe(source, output):
    result = run([sys.executable, str(PROBE), "--source", source,
                  "--project", str(DEFAULT_PROJECT), "--json", "--output", str(output)])
    try:
        return json.loads(result.stdout)
    except json.JSONDecodeError:
        return None


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--project", type=Path, default=DEFAULT_PROJECT)
    parser.add_argument("--limit", type=int, default=0)
    parser.add_argument("--apply", action="store_true")
    args = parser.parse_args()
    project = args.project.resolve()
    manifest_path = project / "regions.json"
    manifest = json.loads(manifest_path.read_text())
    text_start = int(manifest["text_start"], 0)
    raw = PEImage(ORACLE.read_bytes()).read(text_start, manifest["text_bytes"])
    jobs = []
    for region in manifest["regions"]:
        if (region["kind"] != "asm" or not region.get("owner")
                or int(region["owner"], 0) != int(region["address"], 0)):
            continue
        address = int(region["address"], 0)
        body = raw[address - text_start:address - text_start + region["size"]]
        found = shape(body)
        if found:
            jobs.append((region, address, found[0], found[1]))
    print(f"{len(jobs)} accessor region(s) recognised")
    if not args.apply:
        for region, address, kind, offset in jobs[:args.limit or len(jobs)]:
            print(f"  {address:#010x} {kind:5s} +0x{offset:<4x} {region['source']}")
        return 0

    landed, failed = [], []
    for index, (region, address, kind, offset) in enumerate(jobs[:args.limit or len(jobs)], 1):
        name = "accessor_%08x" % address
        source_rel = region["source"]
        source_path = project / source_rel
        layout_rel = f"layout/ltcg/{name}.json"
        layout_path = project / layout_rel
        driver_path = project / f"layout/ltcg/{name}_context.cpp"
        pristine = source_path.read_text()
        original = dict(region)
        size = region["size"]
        context_address = (address + size + 15) & ~15
        source_path.write_text(source_text(kind, offset, address))
        driver_path.write_text(driver_text(kind, address) % source_rel)
        layout_path.write_text(layout_text(name, source_rel, address, size,
                                           context_address, 37, kind))
        result = run([sys.executable, str(REGISTER), "--layout", layout_rel, "--apply"])
        if result.returncode != 0:
            failed.append((address, "layout rejected: " + result.stdout.strip()[:90]))
            source_path.write_text(pristine)
            layout_path.unlink(missing_ok=True)
            driver_path.unlink(missing_ok=True)
            continue
        manifest = json.loads(manifest_path.read_text())
        symbol = accessor_symbol(kind, address)
        report = probe(source_rel, WAVE / f"probe-accessor/{name}")
        retried = False
        if report is None or not report["exact"]:
            # A context whose emitted extent differs only needs its declared size
            # fixed; the map lists the size column before the section name.
            maps = sorted((WAVE / f"probe-accessor/{name}").glob("**/cluster.map"))
            for map_path in reversed(maps):
                details = re.search(r"([0-9A-F]{8})H\s+\.text\$03context\b",
                                    map_path.read_text())
                if not details:
                    continue
                emitted = int(details.group(1), 16)
                layout = json.loads(layout_path.read_text())
                if layout["context"]["size"] != emitted:
                    layout["context"]["size"] = emitted
                    layout_path.write_text(json.dumps(layout, indent=2) + "\n")
                    retried = True
                    report = probe(source_rel, WAVE / f"probe-accessor/{name}")
                break
        if report is not None and report["exact"]:
            landed.append((address, kind, offset, symbol))
            print(f"  EXACT {address:#010x} {kind:5s} +0x{offset:<4x} {source_rel}"
                  + (" (size fixed)" if retried else ""), flush=True)
        else:
            detail = ""
            if report:
                bad = [r for r in report["regions"] if not r["exact"]]
                detail = (bad[0].get("detail") or bad[0].get("first_difference")
                          if bad else (report["failures"][0]["error"][:90] if report["failures"] else ""))
            else:
                detail = "probe did not report"
            failed.append((address, str(detail)[:100]))
            rollback(project, manifest_path, original, source_path, pristine, layout_rel,
                     layout_path, driver_path)
            print(f"  failed {address:#010x} {kind:5s} +0x{offset:<4x}: {detail}", flush=True)
    print(f"\nlanded {len(landed)}, failed {len(failed)}")
    for address, detail in failed:
        print(f"  {address:#010x} {detail}")
    return 0


def rollback(project, manifest_path, original, source_path, pristine, layout_rel,
             layout_path, driver_path):
    """Undo one accessor: restore the source and the region's original record."""
    source_path.write_text(pristine)
    layout_path.unlink(missing_ok=True)
    driver_path.unlink(missing_ok=True)
    with open(manifest_path.with_suffix(".json.lock"), "w") as lock:
        import fcntl
        fcntl.flock(lock, fcntl.LOCK_EX)
        manifest = json.loads(manifest_path.read_text())
        for item in manifest["regions"]:
            if int(item["address"], 0) == int(original["address"], 0):
                item.update(original)
        manifest["ltcg_clusters"] = [c for c in manifest["ltcg_clusters"] if c != layout_rel]
        manifest["translation_units"] = sorted({r["source"] for r in manifest["regions"]})
        temporary = manifest_path.with_suffix(".json.tmp")
        temporary.write_text(json.dumps(manifest, indent=2) + "\n")
        temporary.replace(manifest_path)


if __name__ == "__main__":
    sys.exit(main())
