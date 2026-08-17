#!/usr/bin/env python3
"""Contract tests for tools/retail_vs_recon_stage.py.

Synthetic fixtures assert the comparer's core properties: a stream compared
to itself agrees 100%, and a known field divergence is reported at the
expected position.
"""
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
from retail_vs_recon_stage import (  # noqa: E402
    all_compare,
    clock_compare,
    flat_compare,
    key_fields,
    ordered_vms,
    retail_ticks,
    recon_ticks,
)


def write(path: Path, events: list[dict]) -> None:
    path.write_text(
        "".join(
            str(event).replace("'", '"') + "\n"
            if False
            else __import__("json").dumps(event) + "\n"
            for event in events
        ),
        encoding="utf-8",
    )


def retail_fixture() -> list[dict]:
    header = {"type": "header", "format": "th10-recon-jsonl-v1"}
    stage = {"type": "stage_enter", "seq": 10}
    frame = {"type": "frame_begin", "seq": 11}
    ticks = [
        {"type": "ecl_vm_tick", "seq": 12, "vm": 500000, "ip": 0x30001000,
         "pc_before": 16, "pc_after": 16, "clock": 1065353216,  # 1.0f
         "delta": 0, "async_id": -1, "rank_mask": 2, "scratch_top": 16,
         "result": 0, "live": 1},
        {"type": "ecl_vm_tick", "seq": 13, "vm": 500000, "ip": 0x30001040,
         "pc_before": 64, "pc_after": 64, "clock": 1073741824,  # 2.0f
         "delta": 0, "async_id": -1, "rank_mask": 2, "scratch_top": 16,
         "result": 0, "live": 1},
        {"type": "ecl_vm_tick", "seq": 14, "vm": 600000, "ip": 0x30202000,
         "pc_before": 0, "pc_after": 0, "clock": 1073741824,
         "delta": 0, "async_id": 0, "rank_mask": 2, "scratch_top": 0,
         "result": 0, "live": 1},
    ]
    reg = {"type": "script_register", "seq": 9, "ecx": 0x30000000,
           "edx": 0x400000, "arg0": 0x30001000, "arg1": 0, "arg2": 0}
    return [header, reg, stage, frame] + ticks


def recon_fixture() -> list[dict]:
    header = {"type": "header", "format": "th10-recon-jsonl-v1"}
    ticks = [
        {"type": "ecl_vm_tick", "seq": 1, "frame": 1, "vm": 1,
         "stage_frame": 1, "order": 0, "async_id": 0, "rank_mask": 255,
         "pc_before": 40080, "pc_after": 40120, "scratch_before": 16,
         "scratch_top": 16, "result": 0, "live": 1},
    ]
    return [header] + ticks


def main() -> None:
    import io
    from contextlib import redirect_stdout

    retail_events = retail_fixture()
    recon_events = recon_fixture()

    retail, bases = retail_ticks(retail_events)
    recon = recon_ticks(recon_events)

    # script base resolution: arg0 contains both retail ticks' ips
    assert bases == [0x30001000], bases
    assert retail[0]["pc_rel"] == 0
    assert retail[1]["pc_rel"] == 0x40
    assert retail[2]["pc_rel"] is None  # ip outside the registered base

    # flat_compare of a stream against itself must report full agreement
    # and print no divergence
    buf = io.StringIO()
    with redirect_stdout(buf):
        flat_compare(retail, retail)
    assert "field agreement: 3/3" in buf.getvalue(), buf.getvalue()
    assert "FIRST DIVERGENCE" not in buf.getvalue()

    # flat_compare detects the known divergence at index 0
    buf = io.StringIO()
    with redirect_stdout(buf):
        flat_compare(retail, recon)
    out = buf.getvalue()
    assert "FIRST DIVERGENCE at flat index 0" in out, out
    assert "retail: (2, -1, 16)" in out, out
    assert "recon:  (255, 0, 16)" in out, out

    # key_fields on a schema-violating tick raises instead of comparing
    malformed = {"rank": 1, "async_id": 2}
    try:
        key_fields(malformed)
        raised = False
    except KeyError:
        raised = True
    assert raised, "key_fields accepted a tick missing scratch"

    # clock_compare keys root-VM ticks on the pre-tick float clock, which
    # both sides now emit (retail `clock` / recon `time_before`).  The
    # clocks must be raw bits so the comparison is exact through wait/jump
    # rewinds.
    clock_retail = [
        {"type": "header", "format": "th10-recon-jsonl-v1"},
        {"type": "stage_enter", "seq": 1},
        {"type": "ecl_vm_tick", "seq": 2, "vm": 1, "ip": 0x100,
         "clock": 1065353216, "async_id": -1, "rank_mask": 2,
         "scratch_top": 16, "result": 0, "live": 1},
        {"type": "ecl_vm_tick", "seq": 3, "vm": 1, "ip": 0x200,
         "clock": 1073741824, "async_id": -1, "rank_mask": 2,
         "scratch_top": 16, "result": 0, "live": 1},
    ]
    clock_recon = [
        {"type": "header", "format": "th10-recon-jsonl-v1"},
        {"type": "ecl_vm_tick", "seq": 1, "vm": 1, "stage_frame": 1,
         "order": 0, "time_before": 1065353216, "async_id": -1,
         "rank_mask": 2, "pc_before": 0, "pc_after": 0,
         "scratch_before": 16, "scratch_top": 16, "result": 0, "live": 1},
        {"type": "ecl_vm_tick", "seq": 2, "vm": 1, "stage_frame": 2,
         "order": 0, "time_before": 1073741824, "async_id": -1,
         "rank_mask": 2, "pc_before": 0, "pc_after": 0,
         "scratch_before": 16, "scratch_top": 16, "result": 0, "live": 1},
    ]
    cr, _ = retail_ticks(clock_retail)
    cc = recon_ticks(clock_recon)
    assert [t["root"] for t in cr] == [True, True]
    assert [t["root"] for t in cc] == [True, True]
    assert cc[0]["clock_bits"] == 1065353216
    buf = io.StringIO()
    with redirect_stdout(buf):
        clock_compare(cr, cc)
    out = buf.getvalue()
    assert "clock agreement: 2/2" in out, out
    assert "field agreement: 2/2" in out, out
    assert "FIRST CLOCK DIVERGENCE" not in out

    # a clock divergence is reported at the right tick
    cc[1]["clock_bits"] = 1073741825
    cc[1]["clock"] = 2.0000002
    buf = io.StringIO()
    with redirect_stdout(buf):
        clock_compare(cr, cc)
    out = buf.getvalue()
    assert "FIRST CLOCK DIVERGENCE at root tick 1" in out, out

    # all_compare aligns VMs by creation order (entry pc + async_id) and
    # compares per-tick state across every VM, not just the root.
    base = 0x30000000
    all_retail = [
        {"type": "header", "format": "th10-recon-jsonl-v1"},
        {"type": "script_register", "seq": 1, "arg0": base},
        {"type": "stage_enter", "seq": 2},
        {"type": "ecl_vm_tick", "seq": 3, "vm": 1, "ip": base + 0x100,
         "clock": 1065353216, "async_id": -1, "rank_mask": 2,
         "scratch_top": 16, "result": 0, "live": 1},
        {"type": "ecl_vm_tick", "seq": 4, "vm": 1, "ip": base + 0x200,
         "clock": 1073741824, "async_id": -1, "rank_mask": 2,
         "scratch_top": 16, "result": 0, "live": 1},
        {"type": "ecl_vm_tick", "seq": 5, "vm": 2, "ip": base + 0x300,
         "clock": 1065353216, "async_id": -1, "rank_mask": 2,
         "scratch_top": 0, "result": 0, "live": 1},
        {"type": "ecl_vm_tick", "seq": 6, "vm": 2, "ip": base + 0x400,
         "clock": 1073741824, "async_id": -1, "rank_mask": 2,
         "scratch_top": 16, "result": 0, "live": 1},
    ]
    all_recon = [
        {"type": "header", "format": "th10-recon-jsonl-v1"},
        {"type": "ecl_vm_tick", "seq": 1, "vm": 1, "stage_frame": 1,
         "order": 0, "time_before": 1065353216, "async_id": -1,
         "rank_mask": 2, "pc_before": 0x100, "pc_after": 0,
         "scratch_before": 16, "scratch_top": 16, "result": 0, "live": 1},
        {"type": "ecl_vm_tick", "seq": 2, "vm": 1, "stage_frame": 2,
         "order": 0, "time_before": 1073741824, "async_id": -1,
         "rank_mask": 2, "pc_before": 0x200, "pc_after": 0,
         "scratch_before": 16, "scratch_top": 16, "result": 0, "live": 1},
        {"type": "ecl_vm_tick", "seq": 3, "vm": 99, "stage_frame": 3,
         "order": 1, "time_before": 1065353216, "async_id": -1,
         "rank_mask": 2, "pc_before": 0x300, "pc_after": 0,
         "scratch_before": 0, "scratch_top": 0, "result": 0, "live": 1},
        {"type": "ecl_vm_tick", "seq": 4, "vm": 99, "stage_frame": 4,
         "order": 1, "time_before": 1073741824, "async_id": -1,
         "rank_mask": 2, "pc_before": 0x400, "pc_after": 0,
         "scratch_before": 16, "scratch_top": 16, "result": 0, "live": 1},
    ]
    ar, _ = retail_ticks(all_retail)
    ac = recon_ticks(all_recon)
    assert [vm for vm, _ in ordered_vms(ar)] == [1, 2]
    assert [vm for vm, _ in ordered_vms(ac)] == [1, 99]
    buf = io.StringIO()
    with redirect_stdout(buf):
        all_compare(ar, ac)
    out = buf.getvalue()
    assert "identity alignment (entry pc + async_id): 2/2" in out, out
    assert "per-tick full agreement (clock+fields+pc): 4/4" in out, out

    # an entry-pc mismatch in a later VM is reported as an identity gap
    ac[2]["pc_rel"] = 0x777
    buf = io.StringIO()
    with redirect_stdout(buf):
        all_compare(ar, ac)
    out = buf.getvalue()
    assert "identity alignment (entry pc + async_id): 1/2" in out, out

    print("RETAIL_VS_RECON_STAGE_TEST_PASS")


if __name__ == "__main__":
    main()
