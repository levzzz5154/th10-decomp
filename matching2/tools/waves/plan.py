#!/usr/bin/env python3
"""Split recoverable game regions into per-agent conversion assignments.

The shared candidate classifier accepts self-owned and ownerless assembly in the
game range. Explicitly foreign-owned records stay in the structural lane.
Regions of one translation unit stay with one agent, because two agents editing
one file cannot merge safely.
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
from matching2.tools.waves.candidates import GAME_TEXT_END, classify, is_candidate

from matching2.tools.common.project_paths import project_support
CONFIG = json.loads((project_support((ROOT) / 'matching2/msvc', 'regions.json')).read_text())
TEXT_START = int(CONFIG["text_start"], 0)
ORACLE = PEImage((ROOT / "matching2/build/oracle/th10.exe").read_bytes()).read(
    TEXT_START, CONFIG["text_bytes"])
WAVE = ROOT / "matching2/build/waves"
DEFERRED_BLOCKERS_PATH = ROOT / "matching2/tools/waves/deferred_blockers.json"
DEFERRED_BLOCKERS = {
    int(record["address"], 0): record
    for record in json.loads(DEFERRED_BLOCKERS_PATH.read_text())["records"]
}
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
        if (not is_candidate(region)
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


LANES = ("mechanical", "structural", "dependency", "hard")
LANE_PRIORITY = {"mechanical": 0, "hard": 1, "dependency": 2, "structural": 3}
KNOWN_HARD_ADDRESSES = {
    0x00401110,  # argument-home copy order
    0x00405620,  # argument-home copy order
    0x0040A040,  # mutually exclusive scheduling regions
    0x0040D530,  # argument-home copy order
    0x0042A3E0,  # phi/tail compiler tie-break
    0x004364F0,  # phi/tail pairing
    0x0043CD30,  # immediate argument-copy variant
    0x00443080,  # stack-release scheduling
    0x004445C0,  # induction-variable initialization order
}
KNOWN_STRUCTURAL_ADDRESSES = {
    0x004126D0,  # function plus separately owned jump table
    0x0041C0D0,  # two complete functions in one region
    0x00420547,  # function prologue misclassified as text data
    0x0042453D,  # continuation requiring merge with 0x00424530
    0x00449C00,  # compiler-local switch table split from function COMDAT
    0x00449D40,  # compiler-local switch table split from function COMDAT
    0x004521DC,  # table of independent import thunks
    0x00452332,  # table of independent import thunks
}




def _address(value):
    return f"0x{value:08X}"


def _family_key(region):
    """Return a conservative key for named functions likely to share a recipe."""
    name = re.sub(r"(?i)(?:0x)?[0-9a-f]{6,8}", "", region["name"])
    words = [word.lower() for word in re.split(r"[^A-Za-z0-9]+", name) if word]
    while words and words[0] in {"asm", "semantic"}:
        words.pop(0)
    if not words or words[0] in {"fun", "sub", "free", "unassigned", "recovery"}:
        return None
    return words[0]


def campaign_candidates(signatures, max_address=GAME_TEXT_END, mechanical_max_size=512):
    """Classify every remaining game-code assembly address for a campaign.

    Dependencies use the same direct CALL/tail-JMP analysis as the legacy wave
    planner. Scores measure leverage rather than ease: the region's own bytes,
    all transitively dependent caller bytes, and a small repeat-family bonus,
    less the coordination cost of unfinished direct callees and awkward ABIs.
    """
    selected = []
    by_address = {}
    for region in CONFIG["regions"]:
        address = int(region["address"], 0)
        category = classify(region)
        if category not in {"candidate", "structural"} or address >= max_address:
            continue
        if address in by_address:
            raise ValueError(f"duplicate campaign address {_address(address)}")
        signature = signatures.get(address, "")
        item = {
            "source": region["source"],
            "name": region["name"],
            "symbol": region["symbol"],
            "address": _address(address),
            "size": region["size"],
            "signature": signature or "no IDA reference",
            "cluster_needed": bool(awkward_parameters(signature)),
            "ghidra": (ROOT / f"decompiled/ghidra_augmented/functions/{address:08x}.c").is_file(),
            "ownership": category,
        }
        blocker = DEFERRED_BLOCKERS.get(address)
        item["deferred"] = blocker is not None
        item["deferred_blocker"] = blocker
        selected.append(item)
        by_address[address] = item

    callers = {address: set() for address in by_address}
    families = {}
    for address, item in by_address.items():
        targets = called_targets(address, item["size"])
        dependencies = sorted(target for target in targets if target in by_address)
        awkward = sorted(target for target in targets
                          if awkward_parameters(signatures.get(target, "")))
        item["_dependency_addresses"] = dependencies
        item["blocked_by"] = [_address(target) for target in awkward]
        item["callee_blocked"] = bool(awkward)
        for target in dependencies:
            callers[target].add(address)
        family = _family_key(item)
        if family:
            families.setdefault(family, []).append(address)
        item["_family"] = family

    for address, item in by_address.items():
        downstream = set()
        pending = list(callers[address])
        while pending:
            caller = pending.pop()
            if caller == address or caller in downstream:
                continue
            downstream.add(caller)
            pending.extend(callers[caller])
        downstream_bytes = sum(by_address[caller]["size"] for caller in downstream)
        family_count = len(families.get(item["_family"], ())) if item["_family"] else 1
        family_bonus = min(512, 64 * (family_count - 1))
        blocker_cost = (128 * len(item["_dependency_addresses"])
                        + 256 * len(item["blocked_by"]))
        item["dependencies"] = [_address(target) for target in item["_dependency_addresses"]]
        item["downstream_caller_bytes"] = downstream_bytes
        item["reusable_family_bonus"] = family_bonus
        item["blocker_cost"] = blocker_cost
        item["score"] = item["size"] + downstream_bytes + family_bonus - blocker_cost
        if item["ownership"] == "structural" or address in KNOWN_STRUCTURAL_ADDRESSES:
            item["lane"] = "structural"
        elif address in KNOWN_HARD_ADDRESSES:
            item["lane"] = "hard"
        elif downstream_bytes:
            item["lane"] = "dependency"
        elif (item["cluster_needed"] or item["callee_blocked"]
              or item["size"] > mechanical_max_size):
            item["lane"] = "hard"
        else:
            item["lane"] = "mechanical"

    # One source is one editing boundary. Promote the complete source group to
    # its highest-specialization lane so two agents can never receive one file.
    by_source = {}
    for item in selected:
        by_source.setdefault(item["source"], []).append(item)
    for units in by_source.values():
        lane = max((unit["lane"] for unit in units), key=LANE_PRIORITY.__getitem__)
        for unit in units:
            unit["lane"] = lane
    for item in selected:
        if item["lane"] == "structural":
            item["expected_path"] = "structural"
        elif item["callee_blocked"]:
            item["expected_path"] = "schema2"
        elif item["cluster_needed"]:
            item["expected_path"] = "cluster"
        else:
            item["expected_path"] = "plain"


    for item in selected:
        del item["_dependency_addresses"]
        del item["_family"]
    return sorted(selected, key=lambda item: int(item["address"], 0))

def deal_campaign(items, lane_agents, per_agent, wave):
    """Claim highest-scoring source groups without sharing a source or address."""
    assignments = []
    claimed = set()
    for lane in LANES:
        agents = lane_agents[lane]
        if agents < 1:
            continue
        limit = per_agent[lane] if isinstance(per_agent, dict) else per_agent
        by_source = {}
        for item in items:
            if item["lane"] == lane:
                by_source.setdefault(item["source"], []).append(item)
        groups = sorted(
            by_source.values(),
            key=lambda units: (-max(unit["score"] for unit in units),
                               -sum(unit["score"] for unit in units),
                               int(min(unit["address"] for unit in units), 0),
                               units[0]["source"]))
        buckets = [[] for _ in range(agents)]
        for units in groups:
            choices = [(len(bucket), index) for index, bucket in enumerate(buckets)
                       if not bucket or len(bucket) + len(units) <= limit]
            if not choices:
                continue
            _, index = min(choices)
            buckets[index].extend(units)
        prefix = lane[0].upper()
        for index, units in enumerate(buckets):
            if not units:
                continue
            units.sort(key=lambda item: (-item["score"], int(item["address"], 0)))
            for item in units:
                address = int(item["address"], 0)
                if address in claimed:
                    raise ValueError(f"duplicate campaign claim {item['address']}")
                claimed.add(address)
            assignments.append({
                "agent": f"{prefix}{wave}{index + 1:02d}",
                "lane": lane,
                "units": units,
            })
    return assignments


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
    parser.add_argument("--max-address", type=lambda value: int(value, 0), default=GAME_TEXT_END)
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
