#!/usr/bin/env python3
"""Compare a retail bounded-probe stage capture against the reconstruction
stage trace on a shared script-time timeline.

Timeline:
  retail  - the root VM's float clock (vm+0x00, captured as raw bits per
            tick; advances by one frame delta per yield, so its integer
            value approximates the game-frame counter while the stage ECL
            is live)
  recon   - the ecl_vm_tick `stage_frame` field (scheduler frame counter)

Modes:
  --flat       ignore the timeline; compare the full ordered tick sequence
               (retail capture order vs recon (stage_frame, order) order)
               on the comparable fields only
  --self-check report the field agreement of a stream compared to itself
               (must be 100% or the comparer is broken)

Comparison fields: (rank_mask, async_id, scratch_top) per tick.  Script-
relative pc is added when the retail capture carries script_register events
(bases resolved by containment of the tick ip).

Usage:
    retail_vs_recon_stage.py RETAIL_NORMALIZED.jsonl RECON_TRACE.jsonl
    retail_vs_recon_stage.py --flat RETAIL_NORMALIZED.jsonl RECON_TRACE.jsonl
"""
from __future__ import annotations

import argparse
import json
import struct
from collections import defaultdict
from pathlib import Path


def f32(bits: int) -> float:
    return struct.unpack("<f", struct.pack("<I", bits))[0]


def load(path: Path) -> list[dict]:
    events = [
        json.loads(line)
        for line in path.read_text(encoding="utf-8").splitlines()
        if line.strip()
    ]
    if not events or events[0].get("type") != "header":
        raise ValueError(f"{path}: missing th10-recon-jsonl-v1 header")
    return events


def retail_ticks(events: list[dict]) -> tuple[list[dict], list[int]]:
    """Return (ticks, script_bases).

    Each tick: {timeline, rank, async_id, scratch, pc_rel}.  The timeline is
    the last-seen root-VM clock; the root is the first ticked VM.
    """
    stage = [e["seq"] for e in events if e["type"] == "stage_enter"]
    if not stage:
        raise ValueError("retail capture has no stage_enter event")
    stage_seq = stage[0]

    # 0x00450220 (EclNameTable_Register): ECX = the EclTable, [esp+4] = the
    # loaded script buffer (stored into table->files[] and validated against
    # the 'SPCT' magic at offset 0).  arg0 is therefore the script base for
    # pc_rel; the remaining captured values are the table/env allocations.
    bases: list[int] = []
    for e in events:
        if e["type"] != "script_register":
            continue
        bases.append(int(e["arg0"]))
    bases = [b for b in bases if 0x100000 < b < 0x80000000]
    root_vm: int | None = None
    root_clock = 0.0
    out: list[dict] = []
    for e in events:
        if e.get("type") != "ecl_vm_tick" or e["seq"] <= stage_seq:
            continue
        vm = int(e["vm"])
        if root_vm is None:
            root_vm = vm
        clock = f32(int(e["clock"]))
        if vm == root_vm:
            root_clock = clock
        ip = int(e["ip"])
        pc_rel: int | None = None
        for base in bases:
            off = ip - base
            if 0 <= off < 0x200000:
                if pc_rel is None or off < pc_rel:
                    pc_rel = off
        out.append(
            {
                "timeline": int(root_clock),
                "rank": int(e["rank_mask"]),
                "async_id": int(e["async_id"]),
                "scratch": int(e["scratch_top"]),
                "pc_rel": pc_rel,
            }
        )
    return out, bases


def recon_ticks(events: list[dict]) -> list[dict]:
    out: list[dict] = []
    for e in events:
        if e["type"] != "ecl_vm_tick":
            continue
        out.append(
            {
                "stage_frame": int(e["stage_frame"]),
                "order": int(e["order"]),
                "rank": int(e["rank_mask"]),
                "async_id": int(e["async_id"]),
                "scratch": int(e["scratch_top"]),
                "pc_rel": int(e["pc_before"]),
            }
        )
    return out


def key_fields(tick: dict) -> tuple:
    return (tick["rank"], tick["async_id"], tick["scratch"])


def flat_compare(retail: list[dict], recon: list[dict]) -> None:
    print(f"flat compare: retail={len(retail)} ticks recon={len(recon)} ticks")
    n = min(len(retail), len(recon))
    same = 0
    first = None
    for i in range(n):
        if key_fields(retail[i]) == key_fields(recon[i]):
            same += 1
        elif first is None:
            first = i
            print(f"FIRST DIVERGENCE at flat index {i}")
            print(f"  retail: {key_fields(retail[i])}")
            print(f"  recon:  {key_fields(recon[i])}")
            if retail[i]["pc_rel"] is not None:
                print(f"  pc: retail={retail[i]['pc_rel']} "
                      f"recon={recon[i]['pc_rel']}")
    print(f"flat field agreement: {same}/{n}")


def timeline_compare(retail: list[dict], recon: list[dict],
                     max_offset: int = 6) -> None:
    retail_buckets: dict[int, list] = defaultdict(list)
    for t in retail:
        retail_buckets[t["timeline"]].append(t)
    recon_buckets: dict[int, list] = defaultdict(list)
    for t in recon:
        recon_buckets[t["stage_frame"]].append(t)

    best = None
    for offset in range(-max_offset, max_offset + 1):
        matches = 0
        for t, items in retail_buckets.items():
            frame = t + offset
            if frame in recon_buckets:
                lk = sorted(key_fields(x) for x in items)
                rk = sorted(key_fields(x) for x in recon_buckets[frame])
                if lk == rk:
                    matches += 1
        if best is None or matches > best[1]:
            best = (offset, matches)
    offset, matches = best
    print(f"timeline compare: best offset retail_t+{offset}=recon_frame "
          f"({matches} matching frames of {len(retail_buckets)}; "
          f"low matches mean field-level divergence dominates)")

    first = None
    divergences = 0
    total = 0
    for t in sorted(retail_buckets):
        frame = t + offset
        if frame not in recon_buckets:
            continue
        total += 1
        lk = sorted(key_fields(x) for x in retail_buckets[t])
        rk = sorted(key_fields(x) for x in recon_buckets[frame])
        if lk == rk:
            continue
        divergences += 1
        if first is None:
            first = (t, frame)
            print(f"\nFIRST DIVERGENCE retail_t={t} recon_frame={frame}")
            for name, key in (("rank_mask", "rank"),
                              ("async_id", "async_id"),
                              ("scratch_top", "scratch")):
                lf = sorted({x[key] for x in retail_buckets[t]})
                rf = sorted({x[key] for x in recon_buckets[frame]})
                print(f"  {name:12s} retail={lf[:8]} recon={rf[:8]}")
            print(f"  tick counts      retail={len(retail_buckets[t])} "
                  f"recon={len(recon_buckets[frame])}")
    print(f"\nmatching frames: {total - divergences}/{total}")


def self_check(retail: list[dict], recon: list[dict]) -> None:
    flat_compare(retail, retail)
    flat_compare(recon, recon)
    r = [key_fields(t) for t in retail]
    rc = [key_fields(t) for t in recon]
    print(f"self-check: retail {r == r}, recon {rc == rc}")


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("retail")
    parser.add_argument("recon")
    parser.add_argument("--flat", action="store_true")
    parser.add_argument("--self-check", action="store_true")
    args = parser.parse_args()

    retail, bases = retail_ticks(load(Path(args.retail)))
    recon = recon_ticks(load(Path(args.recon)))

    if args.self_check:
        self_check(retail, recon)
        return 0
    if args.flat:
        flat_compare(retail, recon)
        return 0
    timeline_compare(retail, recon)
    if bases:
        covered = sum(1 for t in retail if t["pc_rel"] is not None)
        print(f"retail ticks with script-relative pc: {covered}/{len(retail)} "
              f"(bases: {[hex(b) for b in bases]})")
    else:
        print("no script_register events in the retail capture; "
              "script-relative pc unavailable")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
