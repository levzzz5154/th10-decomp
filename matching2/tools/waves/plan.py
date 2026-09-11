#!/usr/bin/env python3
"""Split recoverable game regions into per-agent conversion assignments.

A region is a candidate when it is an entire function (``owner == address``), it
sits in game/app code, and IDA does not report a non-standard parameter register
(those need a native LTCG cluster instead). Regions of one translation unit stay
with one agent, because two agents editing one file cannot merge safely.
"""
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[3]
sys.path.insert(0, str(ROOT))

import argparse
import json
import re
import shutil
import struct
import subprocess

from matching2.tools.common.pe import PEImage

CONFIG = json.loads((ROOT / "matching2/msvc/regions.json").read_text())
TEXT_START = int(CONFIG["text_start"], 0)
ORACLE = PEImage((ROOT / "matching2/build/oracle/th10.exe").read_bytes()).read(
    TEXT_START, CONFIG["text_bytes"])
WAVE = ROOT / "matching2/build/waves"
BACKUP = WAVE / "backup"

def ida_signatures():
    """Map each documented address to its full prototype.

    IDA wraps a long prototype across several lines, so the banner is followed by
    every line up to the opening brace of the body. Taking only the first line
    hides the parameters of exactly the regions that need a cluster — the ones
    whose arguments live in registers no C++ declaration can name.
    """
    text = (ROOT / "ida/th10.exe.c").read_text(errors="replace")
    signatures = {}
    for match in re.finditer(r"^//----- \(([0-9A-F]{8})\) -+\n((?:.+\n)+?)\{", text, re.M):
        joined = " ".join(line.strip() for line in match.group(2).splitlines())
        signatures[int(match.group(1), 16)] = joined.strip()
    return signatures


EXPRESSIBLE = {"ecx", "edx"}


def awkward_parameters(signature):
    """Parameter registers a C++ declaration cannot express.

    MSVC 13.10 puts a value parameter in ECX or EDX (or on the stack), never in
    EAX, EBX, ESI or EDI, and a 64-bit parameter always goes on the stack even
    though the *return* value comes back in EDX:EAX. So a region whose caller
    leaves a parameter anywhere else has to be built as a native LTCG cluster.
    IDA writes such a parameter ``name@<reg>``; only the part after the first
    ``(`` is a parameter list, and the return annotation before it is ignored
    because a 64-bit return is an ordinary ``__int64``.
    """
    parameters = signature[signature.find("(") + 1:]
    found = []
    for group in re.findall(r"\w+@<([^>]+)>", parameters):
        group = group.strip()
        if group in EXPRESSIBLE:
            continue
        found.extend(name for name in re.split(r"[:\s]+", group) if name)
    return found


def called_targets(address, size):
    """Functions this region reaches: direct calls and tail jumps.

    Read from the exact image so no disassembly is needed. A tail jump matters
    as much as a call: the target's entry convention is what the region's last
    instructions must set up, so a callee needing EAX/EBX/ESI/EDI pins those
    bytes just as a call site does.
    """
    body = ORACLE[address - TEXT_START:address - TEXT_START + size]
    targets = set()
    for offset in range(len(body) - 4):
        opcode = body[offset]
        if opcode == 0xE8:
            targets.add(address + offset + 5 + struct.unpack_from("<i", body, offset + 1)[0])
        elif opcode == 0xE9:
            targets.add(address + offset + 5 + struct.unpack_from("<i", body, offset + 1)[0])
    return targets


def recovered_addresses():
    """Addresses whose region is already a compiled C++ function.

    A caller reaches one of these through its recovered declaration, so the
    call's register convention is the C++ one, not retail's original.
    """
    return {int(region["address"], 0) for region in CONFIG["regions"]
            if region["kind"] == "semantic"}


def candidates(min_size, max_size, max_address, signatures):
    usable = []
    for region in CONFIG["regions"]:
        address = int(region["address"], 0)
        if (region["kind"] != "asm" or not region["owner"]
                or int(region["owner"], 0) != address
                or not min_size <= region["size"] <= max_size
                or address >= max_address):
            continue
        signature = signatures.get(address, "")
        # A callee whose retail ABI takes an argument in EAX/EBX/ESI/EDI pins the
        # *call site* bytes in this unit, and no declaration can describe that.
        # Recovering the callee does not lift the block: its readable prototype
        # would make this unit emit an ordinary call, which retail did not.
        blocked = [hex(target) for target in called_targets(address, region["size"])
                   if awkward_parameters(signatures.get(target, ""))]
        usable.append({"source": region["source"], "name": region["name"], "symbol": region["symbol"],
                       "address": region["address"], "size": region["size"],
                       "signature": signature or "no IDA reference",
                       "cluster_needed": bool(awkward_parameters(signature)),
                       "blocked_by": blocked[:4],
                       "callee_blocked": bool(blocked),
                       "ghidra": (ROOT / f"decompiled/ghidra_augmented/functions/{address:08x}.c").is_file()})
    usable.sort(key=lambda item: (item["source"], int(item["address"], 0)))
    return usable


def locally_modified():
    """Files the working tree already modifies hold work that is not ours."""
    changed = subprocess.run(["git", "status", "--porcelain", "--", "matching2/msvc/src"],
                             cwd=ROOT, capture_output=True, text=True).stdout.splitlines()
    return {line[3:].strip() for line in changed if line.strip()}


def pack(files, per_agent, agents):
    """Deal files round-robin from largest to smallest so each agent gets a mix."""
    buckets = [{"units": [], "bytes": 0} for _ in range(max(1, agents))]
    for index, units in enumerate(sorted(files, key=lambda group: -sum(item["size"] for item in group))):
        bucket = buckets[index % len(buckets)]
        if len(bucket["units"]) >= per_agent:
            bucket = min(buckets, key=lambda item: len(item["units"]))
            if len(bucket["units"]) >= per_agent:
                break
        bucket["units"].extend(units)
        bucket["bytes"] += sum(item["size"] for item in units)
    return [bucket["units"] for bucket in buckets if bucket["units"]]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--min-size", type=int, default=1)
    parser.add_argument("--size", type=int, default=512)
    parser.add_argument("--max-address", type=lambda value: int(value, 0), default=0x452000)
    parser.add_argument("--per-agent", type=int, default=8)
    parser.add_argument("--max-agents", type=int, default=16)
    parser.add_argument("--agents", type=int, default=8, help="number of parallel agents to deal to")
    parser.add_argument("--prefix", default="W")
    parser.add_argument("--include-cluster", action="store_true",
                        help="also schedule regions that need a native LTCG cluster")
    parser.add_argument("--write", action="store_true", help="record assignments and backups")
    args = parser.parse_args()
    signatures = ida_signatures()
    usable = [item for item in candidates(args.min_size, args.size, args.max_address, signatures)
              if args.include_cluster or not item["cluster_needed"]]
    dirty = locally_modified()
    usable = [item for item in usable if f"matching2/msvc/{item['source']}" not in dirty]
    by_file = {}
    for item in usable:
        by_file.setdefault(item["source"], []).append(item)
    files = sorted(by_file.values(), key=lambda units: sum(unit["size"] for unit in units))
    groups = pack(files, args.per_agent, args.agents)[:args.max_agents]
    assignments = [{"agent": f"{args.prefix}{index + 1:02d}", "units": units}
                   for index, units in enumerate(groups)]
    total = sum(len(group["units"]) for group in assignments)
    files_touched = {unit["source"] for group in assignments for unit in group["units"]}
    print(f"{total} regions in {len(assignments)} assignments across {len(files_touched)} files; "
          f"{len(dirty)} files skipped for local changes")
    for group in assignments:
        size = sum(unit["size"] for unit in group["units"])
        print(f"  {group['agent']}: {len(group['units'])} regions, {size} bytes, "
              f"{len({unit['source'] for unit in group['units']})} files")
    if not args.write:
        return 0
    (WAVE / "results").mkdir(exist_ok=True)
    for group in assignments:
        for unit in group["units"]:
            source = ROOT / "matching2/msvc" / unit["source"]
            target = BACKUP / unit["source"]
            if not target.is_file():
                target.parent.mkdir(parents=True, exist_ok=True)
                shutil.copy2(source, target)
    (WAVE / "assignments.json").write_text(json.dumps(
        {"excluded_local_changes": sorted(dirty), "assignments": assignments}, indent=2) + "\n")
    print(f"wrote {WAVE / 'assignments.json'}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
