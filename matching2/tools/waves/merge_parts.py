#!/usr/bin/env python3
"""Merge split retail functions into single regions a C++ function can cover.

Many regions end in an unconditional jump into the region that immediately
follows them: retail's compiler split one function into parts (a shared tail, a
cold block) and the manifest inherited that split. No compiled C++ function can
*end* in such a jump, so those regions cannot be recovered while they stay
split. Merging the parts restores one region per retail function, with the same
bytes in the same places.

Both parts always belong to the same translation unit and the continuation is
named ``*_part_*``. The continuation's symbol stops being a region and becomes a
plain binding so existing cross-references still resolve.
"""
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[3]
sys.path.insert(0, str(ROOT))

import argparse
import json
import re
import struct

from matching2.tools.common.pe import PEImage

MANIFEST = ROOT / "matching2/msvc/regions.json"
ORACLE = ROOT / "matching2/build/oracle/th10.exe"
BLOCK = re.compile(r'extern "C" __declspec\(naked\) void __cdecl (\w+)\(\)\s*\{\s*__asm \{(.*?)\n    \}\n\}', re.S)


def jump_target(body, address):
    """Absolute target of a trailing unconditional jump, if the body ends in one."""
    if len(body) >= 2 and body[-2] == 0xEB:
        return address + len(body) + struct.unpack_from("<b", body, len(body) - 1)[0]
    if len(body) >= 5 and body[-5] == 0xE9:
        return address + len(body) + 4 + struct.unpack_from("<i", body, len(body) - 4)[0]
    return None


def terminates(body):
    """Whether a region's last instruction ends the function (ret or tail jump)."""
    if not body:
        return False
    if body[-1] in (0xC3, 0xCB):                      # ret / retf
        return True
    if len(body) >= 3 and body[-3] == 0xC2:           # ret imm16
        return True
    if len(body) >= 2 and body[-2] == 0xF3 and body[-1] == 0xC3:   # rep ret
        return True
    if body[-1] in (0xE9, 0xEB):                      # jmp rel8/rel32
        return True
    if len(body) >= 2 and body[-2] == 0xFF and (body[-1] & 0x38) == 0x20:   # jmp r/m32
        return True
    return False


def is_filler(region):
    """Whether a region only holds bytes a compiler generates for itself.

    Alignment NOPs between the parts of one function belong to no function: the
    manifest keeps them in a padding region or in an ownerless ``unassigned``
    stub. They can be folded into the merged region, whose inline assembly then
    emits them verbatim.
    """
    if region["kind"] == "padding":
        return True
    return region["kind"] == "asm" and not region.get("owner")


def chains(regions, raw):
    """Group each head region with its parts and the filler between them.

    Retail's compiler split one function into parts and parked its own alignment
    filler between them. Only parts that continue the head (a trailing jump into
    the next part, or an immediate fall-through) are merged, and only filler may
    sit in between: an intervening region that owns a function means the code is
    not one contiguous extent, so the chain is left alone.
    """
    text_start = int(manifest_start, 0)
    ordered = sorted(regions, key=lambda item: int(item["address"], 0))
    position = {id(region): index for index, region in enumerate(ordered)}
    parts_by_owner = {}
    for region in ordered:
        owner = region.get("owner")
        if owner and int(owner, 0) != int(region["address"], 0):
            parts_by_owner.setdefault(int(owner, 0), []).append(region)
    result, seen = [], set()
    for head in ordered:
        address = int(head["address"], 0)
        if (head["kind"] != "asm" or not head.get("owner")
                or int(head["owner"], 0) != address or address in seen):
            continue
        parts = sorted(parts_by_owner.get(address, []), key=lambda item: int(item["address"], 0))
        if not parts:
            continue
        sequence, filler, cursor = [head], [], head
        for part in parts:
            start = int(cursor["address"], 0)
            body = raw[start - text_start:start - text_start + cursor["size"]]
            following = int(part["address"], 0)
            between = [item for item in ordered[position[id(cursor)] + 1:position[id(part)]]
                       if int(item["address"], 0) >= start + cursor["size"]]
            continues = (jump_target(body, start) == following
                         or start + cursor["size"] == following)
            if not continues or any(not is_filler(item) for item in between):
                break
            filler.extend(between)
            sequence.append(part)
            cursor = part
        if len(sequence) < 2:
            continue
        for region in sequence + filler:
            seen.add(int(region["address"], 0))
        result.append({"head": head, "sequence": sequence, "filler": filler})
    return result


def emit_lines(raw, region):
    """Inline-assembly ``_emit`` lines reproducing a filler region verbatim."""
    text_start = int(manifest_start, 0)
    start = int(region["address"], 0)
    body = raw[start - text_start:start - text_start + region["size"]]
    return "\n".join(f"        _emit 0x{byte:02x}" for byte in body)


def merge_source(text, chain, raw):
    """Replace the head's and parts' naked bodies with one body.

    Filler between the parts is reproduced with ``_emit`` so the merged region
    keeps the retail extent, header comment and all.
    """
    blocks = {}
    for match in BLOCK.finditer(text):
        blocks[match.group(1)] = match
    names = [region["symbol"].lstrip("_") for region in chain["sequence"]]
    missing = [name for name in names if name not in blocks]
    if missing:
        raise SystemExit("source does not define " + ", ".join(missing))
    pieces, previous_end = [], None
    for index, part in enumerate(chain["sequence"]):
        start = int(part["address"], 0)
        if index:
            between = [item for item in chain["filler"]
                       if previous_end <= int(item["address"], 0) < start]
            pieces.extend(emit_lines(raw, region) for region in between)
        pieces.append(blocks[part["symbol"].lstrip("_")].group(2))
        previous_end = start + part["size"]
    joined = "\n".join(piece for piece in pieces if piece)
    merged = (f'extern "C" __declspec(naked) void __cdecl {names[0]}() {{\n'
              f'    __asm {{{joined}\n    }}\n}}')
    first, last = blocks[names[0]], blocks[names[-1]]
    return "".join([text[:first.start()], merged, text[last.end():]]), len(chain["sequence"])


def strip_padding(text, symbol):
    """Remove a padding byte-array definition from a data source."""
    pattern = re.compile(
        r'(?://[^\n]*\n)*#pragma data_seg\("[^"]*"\)\n'
        r'extern "C" unsigned char ' + re.escape(symbol) + r'\[\] = \{.*?\n\};\n'
        r'#pragma data_seg\(\)\n', re.S)
    match = pattern.search(text)
    if match is None:
        raise SystemExit(f"data source does not define {symbol}")
    return text[:match.start()] + text[match.end():]


def strip_naked(text, symbol):
    """Remove an ownerless unassigned naked stub from a source."""
    pattern = re.compile(
        r'(?://[^\n]*\n)*extern "C" __declspec\(naked\) void __cdecl '
        + re.escape(symbol) + r'\(\) \{\n    __asm \{.*?\n    \}\n\}\n', re.S)
    match = pattern.search(text)
    if match is None:
        raise SystemExit(f"source does not define {symbol}")
    return text[:match.start()] + text[match.end():]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--project", type=Path, default=ROOT / "matching2/msvc")
    parser.add_argument("--apply", action="store_true")
    args = parser.parse_args()
    global manifest_start
    project = args.project.resolve()
    manifest_path = project / "regions.json"
    manifest = json.loads(manifest_path.read_text())
    manifest_start = manifest["text_start"]
    raw = PEImage(ORACLE.read_bytes()).read(int(manifest["text_start"], 0), manifest["text_bytes"])
    chains_found = chains(manifest["regions"], raw)
    total_regions = sum(len(chain["sequence"]) - 1 for chain in chains_found)
    total_bytes = sum(int(chain["sequence"][-1]["address"], 0)
                      + chain["sequence"][-1]["size"] - int(chain["head"]["address"], 0)
                      for chain in chains_found)
    by_source = {}
    for chain in chains_found:
        by_source.setdefault(chain["head"]["source"], []).append(chain)
    filler_count = sum(len(chain["filler"]) for chain in chains_found)
    print(f"{len(chains_found)} chains across {len(by_source)} files: "
          f"{total_regions} continuation regions and {filler_count} filler regions absorbed, "
          f"{total_bytes} bytes covered")
    for source in sorted(by_source)[:5]:
        print(f"  {source}: {len(by_source[source])} chains")
    if not args.apply:
        return 0
    removed = []
    for source, source_chains in by_source.items():
        path = project / source
        text = path.read_text()
        for chain in source_chains:
            text, _ = merge_source(text, chain, raw)
            head = chain["head"]
            end = max(int(part["address"], 0) + part["size"] for part in chain["sequence"])
            head["size"] = end - int(head["address"], 0)
            removed.extend(chain["sequence"][1:])
        path.write_text(text)
    for chain in chains_found:
        removed.extend(chain["filler"])
    dropped = {id(region) for region in removed}
    manifest["regions"] = [region for region in manifest["regions"] if id(region) not in dropped]
    for region in removed:
        manifest["symbols"].setdefault(region["symbol"], region["address"])
    # Merging already consumed the continuation bodies; only the filler stubs
    # still have to leave the data and unassigned sources that held them.
    filler = [region for chain in chains_found for region in chain["filler"]]
    for name in sorted({region["source"] for region in filler}):
        path = project / name
        text = path.read_text()
        for region in sorted((item for item in filler if item["source"] == name),
                             key=lambda item: -int(item["address"], 0)):
            symbol = region["symbol"].lstrip("_")
            text = (strip_naked(text, symbol) if region["kind"] == "asm"
                    else strip_padding(text, symbol))
        path.write_text(text)
    live = sorted({region["source"] for region in manifest["regions"]})
    manifest["translation_units"] = live
    kept = set(live)
    for name in sorted({region["source"] for region in removed}):
        if name not in kept:
            (project / name).unlink(missing_ok=True)
            print(f"  removed now-empty source {name}")
    manifest_path.write_text(json.dumps(manifest, indent=2) + "\n")
    print(f"merged {len(by_source)} files; {len(removed)} regions folded into their head; "
          f"now {len(manifest['regions'])} regions")
    return 0


if __name__ == "__main__":
    sys.exit(main())
