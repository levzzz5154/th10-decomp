#!/usr/bin/env python3
"""Compare normalized retail and reconstruction interpreter-entry stage ticks.

Default/--all aligns VMs by first tick, confirms entry pc + async_id, and
requires equal VM counts, equal per-VM tick counts, and bit-exact clocks,
rank, async_id, scratch and resolved script-relative PCs. Nonempty evidence
is required. Agreement covers these captured fields only, not full runtime
parity. VM pointer reuse and script identity are not established by this trace.
Retail PC mapping retains the legacy 2 MiB candidate window, but multiple
candidate bases are now unresolved rather than silently selecting one. Even
unique mappings remain conditional on that window, not known script lengths.

--clock selects only root VM ticks (retail first VM; reconstruction vm=1)
and applies the same strict field requirements. --flat compares only the
ordered rank/async/scratch sequence. --timeline is a legacy diagnostic using
int(retail clock) versus reconstruction stage_frame with an inferred offset;
it requires equal bucket sets and contents but does not establish VM/PC/clock
parity. --self-check compares each stream to itself: it validates nonempty
complete evidence, not independent repeatability or retail/reconstruction parity.

By default the entire selected captures must agree, including tick counts.
--prefix-ticks N explicitly restricts --all/--flat to the first N global ticks
on each side, or --clock to the first N root ticks. Both sides must supply N;
excluded tails are reported and carry no agreement claim. Timelines may rewind:
clock mode compares ordered raw float bits, never buckets or monotonic frames.

Exit status: 0 = agreement within the printed scope (or valid self-check);
1 = disagreement, missing comparison evidence, or empty/short selected stream;
2 = malformed input or invalid arguments. Diagnostics never claim full parity.
"""
from __future__ import annotations

import argparse
import json
import math
import struct
import sys
from collections import defaultdict
from pathlib import Path


def f32(bits: int) -> float:
    return struct.unpack("<f", struct.pack("<I", bits & 0xFFFFFFFF))[0]


def load(path: Path) -> list[dict]:
    events = []
    for number, line in enumerate(path.read_text(encoding="utf-8").splitlines(), 1):
        if not line.strip():
            continue
        try:
            event = json.loads(line)
        except ValueError as exc:
            raise ValueError(f"{path}:{number}: invalid JSON: {exc}") from exc
        if not isinstance(event, dict) or not isinstance(event.get("type"), str):
            raise ValueError(f"{path}:{number}: expected event object with type")
        events.append(event)
    if not events or events[0].get("type") != "header" or events[0].get("format") != "th10-recon-jsonl-v1":
        raise ValueError(f"{path}: missing th10-recon-jsonl-v1 header")
    return events


def integer(event: dict, name: str, optional: bool = False) -> int | None:
    value = event.get(name)
    if optional and value is None:
        return None
    if isinstance(value, bool) or not isinstance(value, int):
        raise ValueError(f"{event.get('type')} event: {name} must be an integer")
    return value


def clock_value(event: dict, name: str) -> int | None:
    bits = integer(event, name, optional=True)
    if bits is not None and not 0 <= bits <= 0xFFFFFFFF:
        raise ValueError(f"{event.get('type')} event: {name} must contain uint32 float bits")
    return bits


def retail_ticks(events: list[dict]) -> tuple[list[dict], list[int]]:
    """Return interpreter-entry ticks after the first stage entry and bases."""
    stage = [integer(e, "seq") for e in events if e["type"] == "stage_enter"]
    if not stage:
        raise ValueError("retail capture has no stage_enter event")
    bases = sorted({integer(e, "arg0") for e in events if e["type"] == "script_register"})
    bases = [b for b in bases if 0x100000 < b < 0x80000000]
    root_vm = None
    out = []
    for event in events:
        if event["type"] != "ecl_vm_tick" or integer(event, "seq") <= stage[0]:
            continue
        vm = integer(event, "vm")
        if root_vm is None:
            root_vm = vm
        bits = clock_value(event, "clock")
        ip = integer(event, "ip", optional=True)
        offsets = [ip - base for base in bases if ip is not None and 0 <= ip - base < 0x200000]
        out.append({
            "vm": vm, "clock": f32(bits) if bits is not None else None,
            "clock_bits": bits, "rank": integer(event, "rank_mask"),
            "async_id": integer(event, "async_id"),
            "scratch": integer(event, "scratch_top"),
            "pc_rel": offsets[0] if len(offsets) == 1 else None,
            "root": vm == root_vm,
        })
    return out, bases


def recon_ticks(events: list[dict]) -> list[dict]:
    out = []
    for event in events:
        if event["type"] != "ecl_vm_tick":
            continue
        bits = clock_value(event, "time_before")
        vm = integer(event, "vm")
        out.append({
            "stage_frame": integer(event, "stage_frame"),
            "order": integer(event, "order"), "vm": vm,
            "rank": integer(event, "rank_mask"),
            "async_id": integer(event, "async_id"),
            "scratch": integer(event, "scratch_before"),
            "pc_rel": integer(event, "pc_before", optional=True),
            "clock": f32(bits) if bits is not None else None,
            "clock_bits": bits, "root": vm == 1,
        })
    return out


def key_fields(tick: dict) -> tuple:
    return (tick["rank"], tick["async_id"], tick["scratch"])


def root_ticks(ticks: list[dict]) -> list[dict]:
    return [tick for tick in ticks if tick.get("root")]


def ordered_vms(ticks: list[dict]) -> list[tuple[int, list[dict]]]:
    groups: dict[int, list[dict]] = {}
    for tick in ticks:
        groups.setdefault(tick["vm"], []).append(tick)
    return list(groups.items())


def complete(tick: dict) -> bool:
    return (tick["clock_bits"] is not None and tick["clock"] is not None
            and math.isfinite(tick["clock"]) and tick["pc_rel"] is not None
            and tick["pc_rel"] >= 0)


def tick_agrees(retail: dict, recon: dict) -> bool:
    return (complete(retail) and complete(recon)
            and retail["clock_bits"] == recon["clock_bits"]
            and key_fields(retail) == key_fields(recon)
            and retail["pc_rel"] == recon["pc_rel"])


def show_tick_pair(retail: dict, recon: dict) -> None:
    for field in ("clock_bits", "rank", "async_id", "scratch", "pc_rel"):
        # repr also handles absent clocks/PCs without hexadecimal format errors.
        print(f"  {field:10s} retail={retail[field]!r} recon={recon[field]!r}")


def all_compare(retail: list[dict], recon: list[dict]) -> bool:
    r_vms, c_vms = ordered_vms(retail), ordered_vms(recon)
    n = min(len(r_vms), len(c_vms))
    identity_ok = total = agree = clock_agree = field_agree = equal_counts = 0
    unpaired_r = sum(len(ticks) for _, ticks in r_vms[n:])
    unpaired_c = sum(len(ticks) for _, ticks in c_vms[n:])
    first_div = None
    for i, ((rvm, rticks), (cvm, cticks)) in enumerate(zip(r_vms, c_vms)):
        entry_ok = (rticks[0]["pc_rel"] is not None
                    and rticks[0]["pc_rel"] == cticks[0]["pc_rel"]
                    and rticks[0]["async_id"] == cticks[0]["async_id"])
        identity_ok += entry_ok
        if not entry_ok:
            print(f"identity mismatch at position {i}: retail vm={rvm} recon vm={cvm}")
        equal_counts += len(rticks) == len(cticks)
        unpaired_r += max(0, len(rticks) - len(cticks))
        unpaired_c += max(0, len(cticks) - len(rticks))
        for j, (r, c) in enumerate(zip(rticks, cticks)):
            total += 1
            clock_agree += r["clock_bits"] is not None and r["clock_bits"] == c["clock_bits"]
            field_agree += key_fields(r) == key_fields(c)
            agrees = tick_agrees(r, c)
            agree += agrees
            if not agrees and first_div is None:
                first_div = (i, j, r, c)
    print(f"all-vm compare: retail={len(r_vms)} VMs recon={len(c_vms)} VMs (aligned {n} by creation order)")
    print(f"identity alignment (entry pc + async_id): {identity_ok}/{n}")
    print(f"per-tick clock agreement: {clock_agree}/{total}")
    print(f"per-tick field agreement: {field_agree}/{total}")
    print(f"per-tick full agreement (clock+fields+pc): {agree}/{total}")
    print(f"equal per-VM tick counts: {equal_counts}/{n}")
    print(f"unpaired VMs: retail={len(r_vms)-n} recon={len(c_vms)-n}")
    print(f"unpaired ticks (including unmatched VM tails): retail={unpaired_r} recon={unpaired_c}")
    print(f"incomplete PC/clock evidence: retail={sum(not complete(t) for t in retail)} recon={sum(not complete(t) for t in recon)}")
    if first_div:
        i, j, r, c = first_div
        print(f"FIRST PER-TICK DIVERGENCE at vm position {i} tick {j}")
        show_tick_pair(r, c)
    return bool(total and len(r_vms) == len(c_vms) and identity_ok == n
                and equal_counts == n and agree == total)


def clock_compare(retail: list[dict], recon: list[dict]) -> bool:
    r_root, c_root = root_ticks(retail), root_ticks(recon)
    print(f"clock compare: retail={len(r_root)} root ticks recon={len(c_root)} root ticks; root only, including PC and fields")
    for i, (r, c) in enumerate(zip(r_root, c_root)):
        if r["clock_bits"] is None or r["clock_bits"] != c["clock_bits"]:
            print(f"FIRST CLOCK DIVERGENCE at root tick {i}")
            show_tick_pair(r, c)
            break
    return all_compare(r_root, c_root)


def flat_compare(retail: list[dict], recon: list[dict]) -> bool:
    print(f"flat diagnostic: retail={len(retail)} ticks recon={len(recon)} ticks; rank/async/scratch only, no VM/PC/clock parity claim")
    n = min(len(retail), len(recon))
    same = 0
    first = None
    for i, (r, c) in enumerate(zip(retail, recon)):
        if key_fields(r) == key_fields(c):
            same += 1
        elif first is None:
            first = i
            print(f"FIRST DIVERGENCE at flat index {i}")
            print(f"  retail: {key_fields(r)}")
            print(f"  recon:  {key_fields(c)}")
    print(f"flat field agreement: {same}/{n}")
    print(f"unpaired ticks: retail={len(retail)-n} recon={len(recon)-n}")
    return bool(n and len(retail) == len(recon) and same == n)


def timeline_compare(retail: list[dict], recon: list[dict], max_offset: int = 6) -> bool:
    print("timeline diagnostic: integer-clock/frame buckets and fields only; no VM/PC/bit-exact-clock parity claim")
    if not retail or not recon or any(t["clock"] is None or not math.isfinite(t["clock"]) for t in retail):
        print("empty stream or missing/invalid retail clock evidence")
        return False
    retail_buckets, recon_buckets = defaultdict(list), defaultdict(list)
    for tick in retail:
        retail_buckets[int(tick["clock"])].append(key_fields(tick))
    for tick in recon:
        recon_buckets[tick["stage_frame"]].append(key_fields(tick))
    best = None
    for offset in range(-max_offset, max_offset + 1):
        matches = sum(sorted(items) == sorted(recon_buckets.get(t + offset, []))
                      for t, items in retail_buckets.items())
        if best is None or matches > best[1]:
            best = (offset, matches)
    offset, matches = best
    r_frames = {frame + offset for frame in retail_buckets}
    c_frames = set(recon_buckets)
    print(f"timeline compare: best offset retail_t+{offset}=recon_frame; matching frames: {matches}/{len(retail_buckets)}")
    print(f"unpaired buckets: retail={len(r_frames-c_frames)} recon={len(c_frames-r_frames)}")
    return r_frames == c_frames and matches == len(retail_buckets)


def self_check(retail: list[dict], recon: list[dict]) -> bool:
    print("self-check: each input versus itself; no independent repeatability or retail parity claim")
    r_ok = all_compare(retail, retail)
    c_ok = all_compare(recon, recon)
    return r_ok and c_ok


def positive_int(value: str) -> int:
    result = int(value)
    if result <= 0:
        raise argparse.ArgumentTypeError("must be positive")
    return result


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("retail")
    parser.add_argument("recon")
    modes = parser.add_mutually_exclusive_group()
    for mode in ("all", "clock", "flat", "timeline", "self-check"):
        modes.add_argument(f"--{mode}", action="store_true")
    parser.add_argument("--prefix-ticks", type=positive_int,
                        help="compare exactly N leading ticks per side (root ticks in --clock); excludes all later evidence")
    args = parser.parse_args()
    if args.prefix_ticks is not None and (args.timeline or args.self_check):
        parser.error("--prefix-ticks requires --all, --clock or --flat")
    try:
        retail, bases = retail_ticks(load(Path(args.retail)))
        recon = recon_ticks(load(Path(args.recon)))
    except (OSError, UnicodeError, ValueError, KeyError, TypeError) as exc:
        print(f"invalid input: {exc}", file=sys.stderr)
        return 2
    if args.clock:
        retail, recon = root_ticks(retail), root_ticks(recon)
    enough = True
    if args.prefix_ticks is not None:
        count = args.prefix_ticks
        enough = len(retail) >= count and len(recon) >= count
        print(f"scope: explicit prefix of exactly {count} {'root' if args.clock else 'global'} ticks per side")
        print(f"excluded tails (not compared): retail={max(0, len(retail)-count)} recon={max(0, len(recon)-count)} ticks")
        if not enough:
            print(f"insufficient prefix evidence: retail={len(retail)} recon={len(recon)} required={count}")
        retail, recon = retail[:count], recon[:count]
    else:
        print(f"scope: entire selected {'root streams' if args.clock else 'captures'}; no unpaired tails permitted")
    compare = (self_check if args.self_check else clock_compare if args.clock else
               flat_compare if args.flat else timeline_compare if args.timeline else all_compare)
    result = compare(retail, recon) and enough
    print(f"retail ticks with script-relative pc: {sum(t['pc_rel'] is not None for t in retail)}/{len(retail)} (candidate bases: {[hex(b) for b in bases]})")
    print(f"RESULT: {'PASS' if result else 'FAIL'} within stated comparison scope")
    return 0 if result else 1


if __name__ == "__main__":
    raise SystemExit(main())
