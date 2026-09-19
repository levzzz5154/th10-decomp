#!/usr/bin/env python3
"""Screen the remaining assembly for regions a C++ translation unit can express.

Two independent tests, both derived from the byte text of each region's naked
body rather than from IDA prototypes:

``--entry``
    Read-before-write analysis: which registers the region reads before writing
    them. ``--entry eax`` finds the single-EAX family (cluster path, object in
    EAX); ``--entry ecx`` finds the ``__thiscall`` family (plain path).

``--call-shape``
    For every ``call``, inspects the three preceding instructions and reports
    those whose argument setup touches only ECX, EDX and the stack — the shape
    ``extern "C" __fastcall`` reproduces and the cluster layout can bind with a
    ``relative_code`` absolute symbol. Regions whose calls set up ESI/EDI/EBX
    cannot be expressed and are filtered out.

Usage:
    python3 screen_regions.py --entry ecx [--min 25] [--max 140] [--calls]
    python3 screen_regions.py --entry eax --calls --game-only
"""
from __future__ import annotations

import argparse
import json
import re
from pathlib import Path

ROOT = Path(__file__).resolve().parents[3]
PROJECT = ROOT / "matching2/msvc"
REGISTER = re.compile(r"\b(?:e?[abcd]x|e?[sd]i|e?[sb]p|[abcd][lh])\b")
# The static CRT block starts at the lowest region match_crt.py resolves to a
# toolkit library member, 0x00452493 (strrchr), not at the old guess of
# 0x44D000 - a wave-20 agent found the bound had been excluding real game
# regions from 0x44D000 upward and including CRT ones above it.
GAME_LOW, GAME_HIGH = 0x401000, 0x452493
CALL_SETUP = re.compile(r"^(mov|lea|movzx|movsx)\s+(ecx|edx)\s*,", re.I)


def region_block(region, cache):
    source = PROJECT / region["source"]
    if not source.is_file():
        return None
    if source not in cache:
        cache[source] = source.read_text()
    index = cache[source].find("L_%08x:" % int(region["address"], 16))
    if index < 0:
        return None
    return cache[source][index:cache[source].find("\n    }\n", index)]


def entry_reads(block):
    """Registers the region consumes that it never wrote first.

    A call clobbers the caller-saved registers (EAX, ECX, EDX), so a read of one
    of those after a call is not an entry dependency; EBX, ESI, EDI and EBP are
    callee-saved, so reading one of them anywhere without a write is."""
    written, reads = {"esp"}, set()
    for line in block.splitlines():
        line = line.strip()
        if not line or line.startswith("L_"):
            continue
        mnemonic = re.match(r"^([a-z][a-z0-9]*)", line)
        if not mnemonic:
            continue
        parts = line.split(None, 1)
        operands = [item.strip() for item in parts[1].split(",")] if len(parts) > 1 else []
        if mnemonic.group(1) == "call":
            written |= {"eax", "ecx", "edx"}
            continue
        if mnemonic.group(1) == "push":
            # push reads its operand; treating it as a destination would mark
            # callee-saved registers as written and hide live-in dependencies.
            for operand in operands:
                for register in REGISTER.findall(operand):
                    name = register.lower()
                    if name not in written and name != "esp":
                        reads.add(name)
            continue
        # A destination writes a register only when it *is* a bare register. A
        # memory destination such as [eax+230h] reads its base and index
        # registers, so every register in it is an entry read; treating the
        # whole operand string as a write marked EAX as written and hid those
        # dependencies.
        destination = operands[0].lower() if operands else ""
        bare = re.fullmatch(r"(?:e?[abcd]x|e?[sd]i|e?[sb]p)", destination)
        for operand in (operands[1:] if bare else operands):
            for register in REGISTER.findall(operand):
                name = register.lower()
                if name not in written and name != "esp":
                    reads.add(name)
        if bare:
            written.add(destination)
    return reads


def calls_expressed(block):
    """True when every call's argument setup touches only ECX, EDX and the stack."""
    lines = [line.strip() for line in block.splitlines()
             if line.strip() and not line.strip().startswith("L_")]
    calls = 0
    for index, line in enumerate(lines):
        if not line.startswith("call"):
            continue
        calls += 1
        # Indirect calls (through a register) are virtual dispatches: the class
        # declaration fixes the slot and the entry analysis fixes the registers,
        # so their "setup" is nothing for this test to reject.
        if "[" in line or "ptr" in line:
            continue
        for previous in lines[max(0, index - 3):index]:
            if re.match(r"^(mov|lea|movzx|movsx|xor|and|add|sub|imul)", previous) \
                    and CALL_SETUP.match(previous) is None:
                return False, calls
    return calls > 0, calls


def main():
    parser = argparse.ArgumentParser(description=__doc__,
                                     formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("--entry", choices=["eax", "ecx", "none"], required=True,
                        help="required entry register family")
    parser.add_argument("--calls", action="store_true",
                        help="also require every call's setup to be ECX/EDX/stack only")
    parser.add_argument("--game-only", action="store_true",
                        help="exclude the static CRT range above 0x0044D000")
    parser.add_argument("--min", type=int, default=25)
    parser.add_argument("--max", type=int, default=140)
    parser.add_argument("--virtual", action="store_true",
                        help="require at least one indirect (virtual) call")
    parser.add_argument("--limit", type=int, default=20)
    args = parser.parse_args()

    config = json.loads((PROJECT / "regions.json").read_text())
    cache, rows = {}, []
    for region in config["regions"]:
        # owner == address marks a region that is an entire function. A region
        # whose owner is absent or differs from its address was skipped by every
        # screen for sixteen waves, but spot checks show many are complete
        # padded functions (the manifest simply never recorded an owner), so the
        # filter now only excludes regions explicitly owned by another address.
        owner = region.get("owner")
        if region["kind"] != "asm":
            continue
        if owner and int(owner, 0) != int(region["address"], 0):
            continue
            continue
        address, size = int(region["address"], 16), region["size"]
        if not (args.min <= size <= args.max):
            continue
        if args.game_only and not (GAME_LOW <= address < GAME_HIGH):
            continue
        block = region_block(region, cache)
        if block is None or "fld" in block:
            continue
        reads = entry_reads(block)
        if args.entry == "eax":
            if reads - {"eax"}:
                continue
        elif args.entry == "ecx":
            if reads - {"ecx"}:
                continue
        else:
            if reads:
                continue
        if args.virtual and "call dword ptr [" not in block:
            continue
        call_count = 0
        if args.calls:
            ok, call_count = calls_expressed(block)
            if not ok:
                continue
        rows.append((size, call_count, hex(address), region["name"], region["source"]))
    rows.sort(reverse=True)
    print(f"{len(rows)} region(s) match")
    for row in rows[:args.limit]:
        print(row)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
