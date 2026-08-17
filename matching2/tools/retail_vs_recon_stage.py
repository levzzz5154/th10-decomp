#!/usr/bin/env python3
"""Compare a retail bounded-probe stage capture against the reconstruction
stage trace.

Timelines:
  retail  - the VM's float clock (vm+0x00, captured as raw bits per tick at
            interpreter entry)
  recon   - the VM's pre-tick float clock (time_before, raw bits), emitted
            at interpreter entry to mirror the retail probe

The clock is the trusted shared timeline: both sides run the same recovered
interpreter (0x0044E1A0) with the same frame delta, so the clocks agree
through the wait/jump opcodes that move vm+0x00 backwards.  stage_frame is
monotonic and cannot represent those rewinds, so it is no longer used as the
comparison key.

VM identity: VMs are aligned by creation order (first tick).  The stage
script is deterministic, so the root spawns the same async children and
enemies in the same order on both sides; the entry script-relative pc and
async_id confirm the alignment at each position.

Modes:
  --all         (default) align every VM by creation order and compare its
                per-tick (clock, rank_mask, async_id, scratch_top, pc)
  --clock       compare only the root VM's tick sequence
  --flat        ignore the timeline; compare the full ordered tick sequence
  --timeline    legacy stage_frame-vs-int(clock) bucket comparison
  --self-check  report the field agreement of a stream compared to itself

Usage:
    retail_vs_recon_stage.py RETAIL_NORMALIZED.jsonl RECON_TRACE.jsonl
    retail_vs_recon_stage.py --clock RETAIL_NORMALIZED.jsonl RECON_TRACE.jsonl
"""
from __future__ import annotations

import argparse
import json
import struct
from collections import defaultdict
from pathlib import Path


def f32(bits: int) -> float:
    return struct.unpack("<f", struct.pack("<I", bits & 0xFFFFFFFF))[0]


def load(path: Path) -> list[dict]:
    events = [
        json.loads(line)
        for line in path.read_text(encoding="utf-8").splitlines()
        if line.strip()
    ]
    if not events or events[0].get("type") != "header":
        raise ValueError(path + ": missing th10-recon-jsonl-v1 header")
    return events


def retail_ticks(events: list[dict]) -> tuple[list[dict], list[int]]:
    """Return (ticks, script_bases).

    Each tick: {vm, clock, clock_bits, rank, async_id, scratch, pc_rel, root}.
    The root is the first ticked VM; each other vm id is the retail pointer's
    normalized sequential id, in first-tick order.
    """
    stage = [e["seq"] for e in events if e["type"] == "stage_enter"]
    if not stage:
        raise ValueError("retail capture has no stage_enter event")
    stage_seq = stage[0]

    bases: list[int] = []
    for e in events:
        if e["type"] != "script_register":
            continue
        bases.append(int(e["arg0"]))
    bases = [b for b in bases if 0x100000 < b < 0x80000000]
    root_vm: int | None = None
    out: list[dict] = []
    for e in events:
        if e.get("type") != "ecl_vm_tick" or e["seq"] <= stage_seq:
            continue
        vm = int(e["vm"])
        if root_vm is None:
            root_vm = vm
        clock_bits = int(e["clock"]) & 0xFFFFFFFF
        ip = int(e["ip"])
        pc_rel: int | None = None
        for base in bases:
            off = ip - base
            if 0 <= off < 0x200000:
                if pc_rel is None or off < pc_rel:
                    pc_rel = off
        out.append(
            {
                "vm": vm,
                "clock": f32(clock_bits),
                "clock_bits": clock_bits,
                "rank": int(e["rank_mask"]),
                "async_id": int(e["async_id"]),
                "scratch": int(e["scratch_top"]),
                "pc_rel": pc_rel,
                "root": vm == root_vm,
            }
        )
    return out, bases


def recon_ticks(events: list[dict]) -> list[dict]:
    out: list[dict] = []
    for e in events:
        if e["type"] != "ecl_vm_tick":
            continue
        time_before = e.get("time_before")
        clock_bits = (
            int(time_before) & 0xFFFFFFFF if time_before is not None else None
        )
        out.append(
            {
                "stage_frame": int(e["stage_frame"]),
                "order": int(e["order"]),
                "vm": int(e["vm"]),
                "rank": int(e["rank_mask"]),
                "async_id": int(e["async_id"]),
                "scratch": int(e["scratch_before"]),
                "pc_rel": int(e["pc_before"]),
                "clock": f32(clock_bits) if clock_bits is not None else None,
                "clock_bits": clock_bits,
                "root": int(e["vm"]) == 1,
            }
        )
    return out


def key_fields(tick: dict) -> tuple:
    return (tick["rank"], tick["async_id"], tick["scratch"])


def root_ticks(ticks: list[dict]) -> list[dict]:
    return [t for t in ticks if t.get("root")]


def ordered_vms(ticks: list[dict]) -> list[tuple[int, list[dict]]]:
    """Group ticks by vm id, preserving first-tick order."""
    order: list[int] = []
    groups: dict[int, list[dict]] = {}
    for t in ticks:
        vm = t["vm"]
        if vm not in groups:
            groups[vm] = []
            order.append(vm)
        groups[vm].append(t)
    return [(vm, groups[vm]) for vm in order]


def tick_agrees(r: dict, c: dict) -> bool:
    # clock, rank, async, scratch must match; pc matches when the retail
    # capture resolved a script-relative pc (it is None at teardown ip=0).
    if r["clock_bits"] != c["clock_bits"]:
        return False
    if key_fields(r) != key_fields(c):
        return False
    if r["pc_rel"] is not None and r["pc_rel"] != c["pc_rel"]:
        return False
    return True


def all_compare(retail: list[dict], recon: list[dict]) -> None:
    r_vms = ordered_vms(retail)
    c_vms = ordered_vms(recon)
    n = min(len(r_vms), len(c_vms))

    identity_ok = 0
    total = 0
    agree = 0
    clock_agree = 0
    field_agree = 0
    pc_unresolved = 0
    lifespan_equal = 0
    first_identity = None
    first_div = None

    for i in range(n):
        rvm, rticks = r_vms[i]
        cvm, cticks = c_vms[i]
        entry_ok = (
            rticks[0]["pc_rel"] == cticks[0]["pc_rel"]
            and rticks[0]["async_id"] == cticks[0]["async_id"]
        )
        if entry_ok:
            identity_ok += 1
        elif first_identity is None:
            first_identity = (i, rvm, cvm, rticks[0], cticks[0])
        if len(rticks) == len(cticks):
            lifespan_equal += 1
        m = min(len(rticks), len(cticks))
        for j in range(m):
            r = rticks[j]
            c = cticks[j]
            total += 1
            if r["clock_bits"] == c["clock_bits"]:
                clock_agree += 1
            if key_fields(r) == key_fields(c):
                field_agree += 1
            if r["pc_rel"] is None:
                pc_unresolved += 1
            if tick_agrees(r, c):
                agree += 1
            elif first_div is None:
                first_div = (i, j, rvm, cvm, r, c)

    print("all-vm compare: retail=%d VMs recon=%d VMs (aligned %d by "
          "creation order)" % (len(r_vms), len(c_vms), n))
    print("identity alignment (entry pc + async_id): %d/%d" % (identity_ok, n))
    if first_identity is not None:
        i, rvm, cvm, r, c = first_identity
        print("  first identity mismatch at position %d: retail vm=%d "
              "(pc=%s async=%d) recon vm=%d (pc=%s async=%d)"
              % (i, rvm, r["pc_rel"], r["async_id"], cvm, c["pc_rel"],
                 c["async_id"]))
    print("per-tick clock agreement: %d/%d" % (clock_agree, total))
    print("per-tick field agreement: %d/%d" % (field_agree, total))
    print("per-tick full agreement (clock+fields+pc): %d/%d" % (agree, total))
    if pc_unresolved:
        print("  (%d retail ticks had ip=0/unresolved pc; pc not compared "
              "for those)" % pc_unresolved)
    if first_div is not None:
        i, j, rvm, cvm, r, c = first_div
        print("FIRST PER-TICK DIVERGENCE at vm position %d tick %d "
              "(retail vm=%d recon vm=%d)" % (i, j, rvm, cvm))
        print("  clock     retail=%r (0x%08X) recon=%r (0x%08X)"
              % (r["clock"], r["clock_bits"], c["clock"], c["clock_bits"]))
        print("  rank      retail=%d recon=%d" % (r["rank"], c["rank"]))
        print("  async_id  retail=%d recon=%d" % (r["async_id"], c["async_id"]))
        print("  scratch   retail=%d recon=%d" % (r["scratch"], c["scratch"]))
        print("  pc_rel    retail=%s recon=%s" % (r["pc_rel"], c["pc_rel"]))
    print("lifespan note: %d/%d VMs have equal tick counts; the remainder "
          "differ because retail despawns enemy VMs within the bounded window "
          "while the reconstruction keeps them alive to the trace end"
          % (lifespan_equal, n))


def clock_compare(retail: list[dict], recon: list[dict]) -> None:
    r_root = root_ticks(retail)
    c_root = root_ticks(recon)
    print("clock compare: retail=%d root ticks recon=%d root ticks"
          % (len(r_root), len(c_root)))
    n = min(len(r_root), len(c_root))

    clock_agree = 0
    field_agree = 0
    all_agree = 0
    first_clock = None
    first_field = None
    for i in range(n):
        r = r_root[i]
        c = c_root[i]
        clock_ok = r["clock_bits"] == c["clock_bits"]
        field_ok = key_fields(r) == key_fields(c)
        if clock_ok:
            clock_agree += 1
        if field_ok:
            field_agree += 1
        if clock_ok and field_ok:
            all_agree += 1
        if not clock_ok and first_clock is None:
            first_clock = i
            print("FIRST CLOCK DIVERGENCE at root tick %d" % i)
            print("  clock     retail=%r (0x%08X) recon=%r (0x%08X)"
                  % (r["clock"], r["clock_bits"], c["clock"], c["clock_bits"]))
            print("  rank      retail=%d recon=%d" % (r["rank"], c["rank"]))
            print("  async_id  retail=%d recon=%d"
                  % (r["async_id"], c["async_id"]))
            print("  scratch   retail=%d recon=%d" % (r["scratch"], c["scratch"]))
            print("  pc_rel    retail=%s recon=%s"
                  % (r["pc_rel"], c["pc_rel"]))
        if not field_ok and first_field is None:
            first_field = i
            print("FIRST FIELD DIVERGENCE at root tick %d" % i)
            print("  rank      retail=%d recon=%d" % (r["rank"], c["rank"]))
            print("  async_id  retail=%d recon=%d"
                  % (r["async_id"], c["async_id"]))
            print("  scratch   retail=%d recon=%d" % (r["scratch"], c["scratch"]))
            print("  pc_rel    retail=%s recon=%s"
                  % (r["pc_rel"], c["pc_rel"]))
            print("  clock     retail=%r recon=%r" % (r["clock"], c["clock"]))
    print("clock agreement: %d/%d" % (clock_agree, n))
    print("field agreement: %d/%d" % (field_agree, n))
    print("clock+field agreement: %d/%d" % (all_agree, n))


def flat_compare(retail: list[dict], recon: list[dict]) -> None:
    print("flat compare: retail=%d ticks recon=%d ticks"
          % (len(retail), len(recon)))
    n = min(len(retail), len(recon))
    same = 0
    first = None
    for i in range(n):
        if key_fields(retail[i]) == key_fields(recon[i]):
            same += 1
        elif first is None:
            first = i
            print("FIRST DIVERGENCE at flat index %d" % i)
            print("  retail: %s" % (key_fields(retail[i]),))
            print("  recon:  %s" % (key_fields(recon[i]),))
            if retail[i]["pc_rel"] is not None:
                print("  pc: retail=%s recon=%s"
                      % (retail[i]["pc_rel"], recon[i]["pc_rel"]))
    print("flat field agreement: %d/%d" % (same, n))


def timeline_compare(retail: list[dict], recon: list[dict],
                     max_offset: int = 6) -> None:
    retail_buckets: dict[int, list] = defaultdict(list)
    for t in retail:
        retail_buckets[int(t["clock"])].append(t)
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
    print("timeline compare: best offset retail_t+%d=recon_frame "
          "(%d matching frames of %d; low matches mean field-level "
          "divergence dominates)" % (offset, matches, len(retail_buckets)))

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
            print("")
            print("FIRST DIVERGENCE retail_t=%d recon_frame=%d" % (t, frame))
            for name, key in (("rank_mask", "rank"),
                              ("async_id", "async_id"),
                              ("scratch_top", "scratch")):
                lf = sorted({x[key] for x in retail_buckets[t]})
                rf = sorted({x[key] for x in recon_buckets[frame]})
                print("  %-12s retail=%s recon=%s" % (name, lf[:8], rf[:8]))
            print("  tick counts      retail=%d recon=%d"
                  % (len(retail_buckets[t]), len(recon_buckets[frame])))
    print("")
    print("matching frames: %d/%d" % (total - divergences, total))


def self_check(retail: list[dict], recon: list[dict]) -> None:
    flat_compare(retail, retail)
    flat_compare(recon, recon)
    r = [key_fields(t) for t in retail]
    rc = [key_fields(t) for t in recon]
    print("self-check: retail %s, recon %s" % (r == r, rc == rc))


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("retail")
    parser.add_argument("recon")
    parser.add_argument("--clock", action="store_true")
    parser.add_argument("--flat", action="store_true")
    parser.add_argument("--timeline", action="store_true")
    parser.add_argument("--self-check", action="store_true")
    args = parser.parse_args()

    retail, bases = retail_ticks(load(Path(args.retail)))
    recon = recon_ticks(load(Path(args.recon)))

    if args.self_check:
        self_check(retail, recon)
        return 0
    if args.clock:
        clock_compare(retail, recon)
    elif args.flat:
        flat_compare(retail, recon)
    elif args.timeline:
        timeline_compare(retail, recon)
    else:
        all_compare(retail, recon)
    if bases:
        covered = sum(1 for t in retail if t["pc_rel"] is not None)
        print("retail ticks with script-relative pc: %d/%d "
              "(bases: %s)" % (covered, len(retail),
                               [hex(b) for b in bases]))
    else:
        print("no script_register events in the retail capture; "
              "script-relative pc unavailable")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
