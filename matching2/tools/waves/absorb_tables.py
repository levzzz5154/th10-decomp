#!/usr/bin/env python3
"""Absorb compiler-emitted jump tables into the function that owns them.

MSVC places a ``switch``'s jump table *inside the function's own COMDAT*: the
code, the alignment padding, then the table. Retail's .text reflects that, but
the manifest inherited a different split — the table (and often the pad) landed
in a data region owned by another translation unit. A recovered C++ function
therefore compiles to code+pad+table while its region records only the code, and
the probe rejects the extent.

This tool makes the manifest agree with what the compiler emits: a region whose
owner converted the body may declare a larger extent, and if that growth is
exactly the following filler plus one data region that the retail body
references as a table base, those regions are folded into it — the code region
grows, the filler and data regions disappear, and their bytes stop being
provided by the data source because the compiler now emits them.

Every affected unit is re-probed and any that does not come back exact is
reverted, so the project keeps its byte-exact build throughout.

Usage:
    python3 absorb_tables.py --results matching2/build/waves/results5   # plan
    python3 absorb_tables.py --results matching2/build/waves/results5 --apply
"""
from __future__ import annotations

import argparse
import json
import re
import struct
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[3]
sys.path.insert(0, str(ROOT))

from matching2.tools.common.pe import PEImage

ORACLE = ROOT / "matching2/build/oracle/th10.exe"
PROBE = ROOT / "matching2/tools/matching/probe.py"
MAX_TABLE = 8192


def strip_array(text, symbol):
    """Remove a padding/data byte-array definition from its source."""
    pattern = re.compile(
        r'(?://[^\n]*\n)*#pragma data_seg\("[^"]*"\)\n'
        r'extern "C" unsigned char ' + re.escape(symbol) + r'\[\] = \{.*?\n\};\n'
        r'#pragma data_seg\(\)\n', re.S)
    match = pattern.search(text)
    if match is None:
        raise ValueError(f"source does not define the array {symbol}")
    return text[:match.start()] + text[match.end():]


def strip_naked(text, symbol):
    """Remove an ownerless unassigned naked stub from its source."""
    pattern = re.compile(
        r'(?://[^\n]*\n)*extern "C" __declspec\(naked\) void __cdecl '
        + re.escape(symbol) + r'\(\) \{\n    __asm \{.*?\n    \}\n\}\n', re.S)
    match = pattern.search(text)
    if match is None:
        raise ValueError(f"source does not define the stub {symbol}")
    return text[:match.start()] + text[match.end():]


def is_filler(region):
    """A region that only holds bytes a compiler generates for itself."""
    if region["kind"] == "padding":
        return True
    return region["kind"] == "asm" and not region.get("owner")


def mentions(body, address):
    """Whether the body names an absolute address as a 32-bit value."""
    return struct.pack("<I", address) in body


def absorbable(manifest, raw, text_start):
    """Map head address -> extension, for a function followed by its own tables.

    MSVC puts each ``switch``'s tables in the function's own section, after the
    code, so retail's layout is a run of ``[filler][table]`` groups that the
    manifest split across several regions. The walk therefore absorbs groups one
    after another: any amount of compiler filler, then a data region whose base
    the body names. It stops at the first region that is neither, because from
    there the layout belongs to a different function.

    A table more than one head names cannot be owned by either, so such a data
    region is left alone.
    """
    regions = sorted(manifest["regions"], key=lambda region: int(region["address"], 0))
    heads = []
    for region in regions:
        if region["kind"] not in ("asm", "semantic"):
            continue
        owner = region.get("owner")
        if not owner or int(owner, 0) != int(region["address"], 0):
            continue
        address = int(region["address"], 0)
        body = raw[address - text_start:address - text_start + region["size"]]
        heads.append((region, address, body))
    shared = {}
    for table in regions:
        if table["kind"] != "data" or not 0 < table["size"] <= MAX_TABLE or table["size"] % 4 != 0:
            continue
        base = int(table["address"], 0)
        naming = [address for _, address, body in heads if mentions(body, base)]
        if len(naming) > 1:
            shared[base] = True

    by_address = {int(region["address"], 0): region for region in regions}

    def is_table(region, head, end):
        """Whether a data region is a switch table for the function at ``head``.

        MSVC emits a ``switch``'s dword table and, for a dense byte dispatch, a
        byte index table, so the region need not be a whole number of dwords. The
        test is that a majority of its leading dwords are addresses inside the
        function the table follows.
        """
        base = int(region["address"], 0)
        if region["kind"] != "data" or not 0 < region["size"] <= MAX_TABLE or shared.get(base):
            return False
        body = raw[base - text_start:base - text_start + region["size"]]
        entries = [struct.unpack_from("<I", body, offset)[0] for offset in range(0, len(body) - 3, 4)]
        if len(entries) < 2:
            return False
        inside = sum(1 for entry in entries if head <= entry < end)
        return inside * 2 >= len(entries)

    def next_group(cursor, head, end):
        """The filler and table at ``cursor``, or None when no table follows.

        Filler is only taken when a table comes after it: the alignment padding
        that follows the last table belongs to the next function.
        """
        filler, step = [], cursor
        while step in by_address and is_filler(by_address[step]):
            filler.append(by_address[step])
            step += by_address[step]["size"]
        table = by_address.get(step)
        if table is None or not is_table(table, head, end):
            return None
        return filler + [table]

    found = {}
    for region, address, _ in heads:
        end = address + region["size"]
        cursor, absorbed = end, []
        while True:
            group = next_group(cursor, address, end)
            if group is None:
                break
            absorbed.extend(group)
            cursor = int(group[-1]["address"], 0) + group[-1]["size"]
        if any(item["kind"] == "data" for item in absorbed):
            found[address] = {"region": region, "absorbed": absorbed, "size": cursor - address}
    return found


BLOCK = re.compile(r'(?://[^\n]*\n)*extern "C" __declspec\(naked\) void __cdecl (\w+)\(\)\s*\{'
                   r'\s*__asm \{(.*?)\n    \}\n\}\n', re.S)


def emit_bytes(data):
    """``_emit`` lines reproducing bytes verbatim.

    MSVC's inline assembler takes one statement per line, so each byte gets its
    own ``_emit`` even though the block is a data table.
    """
    return "\n".join(f"        _emit 0x{byte:02x}" for byte in data)


def extend_naked(text, symbol, data):
    """Append the absorbed bytes to a naked body so it still emits the extent."""
    hits = [match for match in BLOCK.finditer(text) if match.group(1) == symbol]
    if len(hits) != 1:
        raise ValueError(f"expected one naked definition of {symbol}, found {len(hits)}")
    match = hits[0]
    close = match.end(2)
    body = match.group(2)
    tail = "\n" + emit_bytes(data)
    return text[:close] + tail + text[close:]


def absorb_asm(project, manifest, manifest_path, raw, text_start, candidates):
    """Fold each table group into its region, keeping the naked body exact.

    The region grows to cover the padding and table, the data source stops
    providing those bytes, and the region's own inline assembly emits them — so
    the image is unchanged while the region now has the extent a compiled
    ``switch`` produces.
    """
    original_manifest = manifest_path.read_text()
    backups, absorbed = {}, []
    for address, item in sorted(candidates.items()):
        region = item["region"]
        head = address + region["size"]
        data = raw[head - text_start:head - text_start + (item["size"] - region["size"])]
        absorbed.extend(item["absorbed"])
        path = project / region["source"]
        if region["source"] not in backups:
            backups[region["source"]] = (path, path.read_text())
        path.write_text(extend_naked(path.read_text(), region["symbol"].lstrip("_"), data))
        region["size"] = item["size"]
    dropped = {id(region) for region in absorbed}
    manifest["regions"] = [region for region in manifest["regions"] if id(region) not in dropped]
    for region in absorbed:
        manifest["symbols"].setdefault(region["symbol"], region["address"])
    manifest["translation_units"] = sorted({region["source"] for region in manifest["regions"]})
    for name in sorted({region["source"] for region in absorbed}):
        path = project / name
        text = backups.setdefault(name, (path, path.read_text()))[1]
        for region in sorted((item for item in absorbed if item["source"] == name),
                             key=lambda entry: -int(entry["address"], 0)):
            symbol = region["symbol"].lstrip("_")
            text = (strip_naked(text, symbol) if region["kind"] == "asm"
                    else strip_array(text, symbol))
        path.write_text(text)
    kept = set(manifest["translation_units"])
    for name in sorted({region["source"] for region in absorbed}):
        if name not in kept:
            (project / name).unlink(missing_ok=True)
    manifest_path.write_text(json.dumps(manifest, indent=2) + "\n")
    return original_manifest, backups, absorbed


def collect(results):
    """Read every proposal that declares a larger extent for an owned region."""
    wanted = {}
    for directory in results:
        for path in sorted(directory.rglob("*.json")):
            if path.name == "summary.json" or "probe" in path.parts:
                continue
            try:
                payload = json.loads(path.read_text())
            except json.JSONDecodeError:
                continue
            for region in payload.get("regions", []):
                if not isinstance(region, dict) or "address" not in region or "size" not in region:
                    continue
                if region.get("kind") != "semantic":
                    continue
                wanted.setdefault(int(region["address"], 0), region)
    return wanted


def probe(project, sources, output):
    output.mkdir(parents=True, exist_ok=True)
    command = [sys.executable, str(PROBE), "--project", str(project),
               *sum((["--source", source] for source in sources), []),
               "--json", "--output", str(output)]
    result = subprocess.run(command, capture_output=True, text=True, timeout=1800)
    try:
        return json.loads(result.stdout)
    except json.JSONDecodeError:
        return None


def unit_status(report, sources):
    """Map each source to whether every region it owns came back exact."""
    if report is None:
        return {source: False for source in sources}
    failed = {failure["source"] for failure in report["failures"]}
    status = {source: source not in failed for source in sources}
    for region in report["regions"]:
        if not region["exact"]:
            status[region["source"]] = False
    return status


from matching2.tools.common.project_paths import project_support
def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--project", type=Path, default=ROOT / "matching2/msvc")
    parser.add_argument("--results", type=Path, action="append",
                        default=None, help="proposal directory (repeatable)")
    parser.add_argument("--asm", action="store_true",
                        help="keep each absorbed region's body in inline assembly, emitting the "
                             "table bytes verbatim, so the extent grows without a C++ body")
    parser.add_argument("--apply", action="store_true")
    args = parser.parse_args()
    results = args.results or [ROOT / "matching2/build/waves/results5"]
    project = args.project.resolve()
    manifest_path = project_support(project, 'regions.json')
    manifest = json.loads(manifest_path.read_text())
    text_start = int(manifest["text_start"], 0)
    raw = PEImage(ORACLE.read_bytes()).read(text_start, manifest["text_bytes"])
    candidates = absorbable(manifest, raw, text_start)
    if args.asm:
        print(f"{len(candidates)} region(s) are followed by their own jump table")
        for address, item in sorted(candidates.items()):
            groups = " ".join("{}:{}".format(region["kind"], region["size"])
                              for region in item["absorbed"])
            print(f"  extend {item['size']:6d}B  {item['region']['source']:44s} {address:#010x} "
                  f"<- {groups}")
        if not args.apply:
            return 0
        # Absorb one unit at a time and probe it immediately: a unit that was
        # already failing (an agent mid-edit elsewhere) must not block the rest,
        # and a unit that regresses is undone on the spot.
        extended, folded, skipped = 0, 0, []
        for address, item in sorted(candidates.items()):
            source = item["region"]["source"]
            manifest = json.loads(manifest_path.read_text())
            candidates_now = absorbable(manifest, raw, int(manifest["text_start"], 0))
            if address not in candidates_now:
                continue
            original_manifest, backups, absorbed = absorb_asm(
                project, manifest, manifest_path, raw, int(manifest["text_start"], 0),
                {address: candidates_now[address]})
            report = probe(project, [source], ROOT / "matching2/build/waves/absorb/probe-asm")
            status = unit_status(report, [source])
            if status[source]:
                extended += 1
                folded += len(absorbed)
            else:
                manifest_path.write_text(original_manifest)
                for name, (path, text) in backups.items():
                    path.write_text(text)
                skipped.append(source)
                print(f"  skipped {source} ({address:#010x}): unit not exact "
                      f"before or after the extension")
        print(f"extended {extended} region(s), folded {folded} padding/data region(s); "
              f"{len(skipped)} unit(s) skipped")
        subprocess.run([sys.executable, str(ROOT / "matching2/tools/matching/progress.py"),
                        "--manifest", str(manifest_path)], cwd=ROOT)
        return 0
    wanted = collect(results)
    ready, waiting = [], []
    for address, item in sorted(candidates.items()):
        proposal = wanted.get(address)
        if proposal is not None and proposal["size"] == item["size"]:
            ready.append((item, proposal))
        else:
            waiting.append(item)
    print(f"{len(candidates)} region(s) are followed by their own jump table; "
          f"{len(ready)} arrive with a matching proposal")
    for item, proposal in ready:
        print(f"  absorb {item['size']:6d}B  {item['region']['source']:44s} "
              f"{hex(int(item['region']['address'],0))} <- pad {sum(r['size'] for r in item['filler'])}B "
              f"+ table {item['table']['size']}B ({item['table']['source']})")
    for item in waiting[:8]:
        print(f"  waiting on a body for {hex(int(item['region']['address'],0))} "
              f"{item['region']['source']} (extension {item['size']}B)")
    if not args.apply or not ready:
        return 0
    original_manifest = manifest_path.read_text()
    backups = {}
    absorbed = []
    for item, proposal in ready:
        region = item["region"]
        absorbed.extend(item["filler"])
        absorbed.append(item["table"])
        region["size"] = item["size"]
        region["symbol"] = proposal["symbol"]
        region["kind"] = "semantic"
        region["name"] = proposal.get("name", region["name"])
        region.pop("requested_symbol", None)
    dropped = {id(region) for region in absorbed}
    manifest["regions"] = [region for region in manifest["regions"] if id(region) not in dropped]
    for region in absorbed:
        manifest["symbols"].setdefault(region["symbol"], region["address"])
    manifest["translation_units"] = sorted({region["source"] for region in manifest["regions"]})
    for name in sorted({region["source"] for region in absorbed}):
        path = project / name
        text = backups.setdefault(name, (path, path.read_text()))[1]
        for region in sorted((item for item in absorbed if item["source"] == name),
                             key=lambda entry: -int(entry["address"], 0)):
            symbol = region["symbol"].lstrip("_")
            text = (strip_naked(text, symbol) if region["kind"] == "asm"
                    else strip_array(text, symbol))
        path.write_text(text)
    kept = set(manifest["translation_units"])
    for name in sorted({region["source"] for region in absorbed}):
        if name not in kept:
            (project / name).unlink(missing_ok=True)
            print(f"  removed now-empty source {name}")
    manifest_path.write_text(json.dumps(manifest, indent=2) + "\n")
    sources = sorted({item["region"]["source"] for item, _ in ready}
                     | {region["source"] for region in absorbed
                        if (project / region["source"]).is_file()})
    report = probe(project, sources, ROOT / "matching2/build/waves/absorb/probe")
    problems = []
    if report is None:
        problems.append("probe did not report")
    else:
        problems += [f"{failure['source']}: {failure['error'][:200]}" for failure in report["failures"]]
        problems += [f"{region['address']:#010x} {region['symbol']}: "
                     f"{region.get('detail') or region.get('first_difference')}"
                     for region in report["regions"] if not region["exact"]]
    if problems:
        manifest_path.write_text(original_manifest)
        for name, (path, text) in backups.items():
            path.write_text(text)
        print("absorbed changes rolled back:")
        for problem in problems:
            print("  " + problem)
        return 1
    print(f"absorbed {len(ready)} jump table(s) and {len(absorbed) - len(ready)} filler region(s); "
          f"{len(manifest['regions'])} regions remain")
    subprocess.run([sys.executable, str(ROOT / "matching2/tools/matching/progress.py"),
                    "--manifest", str(manifest_path)], cwd=ROOT)
    return 0


if __name__ == "__main__":
    sys.exit(main())
