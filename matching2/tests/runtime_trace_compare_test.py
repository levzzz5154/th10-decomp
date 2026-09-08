#!/usr/bin/env python3

import sys
from pathlib import Path

if __package__ in (None, ""):
    sys.path.insert(0, str(Path(__file__).resolve().parents[2]))
import json
import tempfile

ROOT = Path(__file__).resolve().parents[1]
from matching2.tools.runtime.compare_runtime_trace import compare  # noqa: E402


def write(path: Path, events: list[dict]) -> None:
    path.write_text(
        "".join(json.dumps(event, separators=(",", ":")) + "\n"
                for event in events),
        encoding="utf-8",
    )


def main() -> None:
    header = {
        "seq": 0,
        "type": "header",
        "frame": -1,
        "schema": 1,
        "format": "th10-recon-jsonl-v1",
    }
    event = {"seq": 1, "type": "frame_begin", "frame": 1}
    with tempfile.TemporaryDirectory() as directory:
        left = Path(directory) / "left.jsonl"
        right = Path(directory) / "right.jsonl"
        write(left, [header, event])
        right_event = dict(event)
        right_event["seq"] = 99
        write(right, [dict(header), right_event])
        assert compare(left, right) == 0
        right_event["frame"] = 2
        write(right, [dict(header), right_event])
        assert compare(left, right) == 1

        lifecycle = [
            dict(header),
            {"seq": 1, "type": "vm_create", "frame": 1, "vm": 7, "pc": 0},
            {"seq": 2, "type": "object", "frame": 1, "handle": 3, "vm": 7},
            {"seq": 3, "type": "entity", "frame": 1, "id": 100,
             "kind": 1, "live": 1},
            {"seq": 4, "type": "stage_spawn", "frame": 1,
             "entity": 100, "opcode": 257, "manager_count": 1,
             "spawn_serial": 1, "x": 1.0, "y": 2.0, "z": 0.0},
            {"seq": 5, "type": "vm_destroy", "frame": 2, "vm": 7,
             "reason": "transition"},
            {"seq": 6, "type": "object_destroy", "frame": 2,
             "handle": 3, "reason": "transition"},
            {"seq": 7, "type": "entity", "frame": 2, "id": 100,
             "kind": 1, "live": 0},
        ]
        write(left, lifecycle)
        write(right, [dict(event) for event in lifecycle])
        assert compare(left, right) == 0
        write(right, lifecycle[:-1])
        assert compare(left, right) == 2
        invalid_tick = lifecycle + [
            {"seq": 8, "type": "vm_tick", "frame": 3, "vm": 7,
             "script": 0, "resource": 0, "pc_before": 0,
             "pc_after": 0, "time": 0, "sprite": 0, "flags": 0,
             "ended": 1},
        ]
        write(right, invalid_tick)
        assert compare(left, right) == 2

    # Retail-side bounded-probe reference: a normalized stage-window capture
    # of the untouched th10.exe (frame loop + full-field ECL core ticks +
    # stage/script anchors). It must stay a valid stream under the same
    # comparator the reconstruction uses, and every tick must carry the
    # complete field set, so a field-less artifact cannot pass.
    reference = ROOT / "tests" / "retail_probe_evidence" / "retail_ecl_reference.jsonl"
    if reference.is_file():
        assert compare(reference, reference) == 0
        reference_events = [json.loads(line) for line in
                            reference.read_text(encoding="utf-8").splitlines()
                            if line.strip()]
        ticks = [event for event in reference_events
                 if event.get("type") == "ecl_vm_tick"]
        assert ticks, "reference carries no ecl_vm_tick events"
        required = ("vm", "pc_before", "pc_after", "clock",
                    "async_id", "rank_mask", "scratch_top")
        for event in ticks:
            missing = [key for key in required if key not in event]
            assert not missing, f"reference tick missing {missing}: {event}"
            clock_bits = int(event["clock"])
            import struct
            clock = struct.unpack("<f", struct.pack("<I", clock_bits))[0]
            assert clock == clock, "reference tick clock is not finite: %r" % event
    print("RUNTIME_TRACE_COMPARE_TEST_PASS")


if __name__ == "__main__":
    main()
