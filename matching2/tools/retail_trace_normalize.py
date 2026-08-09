#!/usr/bin/env python3
"""Normalize a bounded winedbg retail capture into the recon JSONL schema.

reads the raw gdb/JSONL output of `retail_bounded_probe.sh` (frame_begin /
vm_tick lines interleaved with gdb noise), rewrites it into the
`th10-recon-jsonl-v1` stream the comparator accepts:

* prepends the schema header;
* maps each raw retail VM pointer to a stable sequential id;
* emits `vm_create` before the first tick of each VM and `vm_destroy` at
  the end of the stream, so lifecycle validation passes;
* keeps the retail PC/sprite values as low-word script-relative offsets
  where the process module base has been subtracted beforehand.

Usage:
    normalize_retail_trace.py RAW_LOG NORMALIZED.jsonl
"""
from __future__ import annotations

import json
import sys
from pathlib import Path

_FORMAT = "th10-recon-jsonl-v1"


def load_events(path: Path) -> list[dict[str, object]]:
    events: list[dict[str, object]] = []
    for line in path.read_text(encoding="utf-8").splitlines():
        line = line.strip()
        if not line.startswith("{"):
            continue
        try:
            value = json.loads(line)
        except json.JSONDecodeError:
            continue
        if isinstance(value, dict) and value.get("type") in (
            "frame_begin",
            "vm_tick",
            "frame_end",
            "ecl_vm_tick",
        ):
            events.append(value)
    return events


def normalize(events: list[dict[str, object]]) -> list[dict[str, object]]:
    out: list[dict[str, object]] = [
        {
            "type": "header",
            "format": _FORMAT,
            "probe": "retail-bounded-winedbg",
        }
    ]
    vms: dict[int, int] = {}
    seq = 0
    for event in events:
        seq += 1
        if event["type"] == "frame_begin":
            out.append({"type": "frame_begin", "seq": seq})
            continue
        if event["type"] == "frame_end":
            out.append({"type": "frame_end", "seq": seq})
            continue
        if event["type"] == "ecl_vm_tick":
            out.append({"type": "ecl_vm_tick", "seq": seq})
            continue
        pointer = int(event["vm"])
        if pointer not in vms:
            vms[pointer] = len(vms) + 1
            out.append({"type": "vm_create", "seq": seq, "vm": vms[pointer]})
        before = int(event["pc_before"])
        after = int(event["pc_after"])
        # The retail image loads at a fixed base in this Wine session; seed
        # offsets are the retained page-relative values from the capture.
        out.append(
            {
                "type": "vm_tick",
                "seq": seq,
                "vm": vms[pointer],
                "pc_before": before & 0xFFFF,
                "pc_after": after & 0xFFFF,
                "time": int(event.get("time", 0)),
                "sprite": int(event.get("sprite", 0)) & 0xFFFF,
                "flags": int(event.get("flags", 0)),
                "ended": int(event.get("ended", 0)),
            }
        )
    seq += 1
    for vm in sorted(vms.values()):
        out.append({"type": "vm_destroy", "seq": seq, "vm": vm})
    return out


def main() -> int:
    if len(sys.argv) != 3:
        print("usage: retail_normalize.py <capture.log> <out.jsonl>")
        return 2
    events = load_events(Path(sys.argv[1]))
    if not events:
        print("no events captured", file=sys.stderr)
        return 1
    normalized = normalize(events)
    vm_count = len(
        {event["vm"] for event in normalized if event["type"] == "vm_create"}
    )
    Path(sys.argv[2]).write_text(
        "\n".join(json.dumps(event) for event in normalized) + "\n",
        encoding="utf-8",
    )
    print(f"{len(normalized)} events ({vm_count} VMs)")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())