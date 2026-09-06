#!/usr/bin/env python3
"""Synthetic CLI contract tests; these fixtures do not establish retail parity."""
import copy
import io
import json
import subprocess
import sys
import tempfile
import unittest
from contextlib import redirect_stdout
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
from retail_vs_recon_stage import (  # noqa: E402
    all_compare, clock_compare, flat_compare, key_fields, ordered_vms,
    recon_ticks, retail_ticks, tick_agrees,
)

TOOL = ROOT / "tools" / "retail_vs_recon_stage.py"
BASE = 0x30000000


def fixtures() -> tuple[list[dict], list[dict]]:
    """Two VMs, distinct pointer identities, exact clocks including a rewind."""
    header = {"type": "header", "format": "th10-recon-jsonl-v1"}
    retail = [header.copy(), {"type": "script_register", "seq": 1, "arg0": BASE},
              {"type": "stage_enter", "seq": 2}]
    recon = [header.copy()]
    for i, (vm, pc, bits, async_id, scratch) in enumerate([
        (1, 0x100, 1065353216, -1, 16),  # root at 1.0
        (99, 0x300, 0, 7, 0),          # child at 0.0
        (1, 0x140, 0, -1, 16),         # root rewinds
        (99, 0x340, 1065353216, 7, 16),
    ]):
        retail.append({"type": "ecl_vm_tick", "seq": 3 + i, "vm": vm + 500000,
                       "ip": BASE + pc, "clock": bits, "async_id": async_id,
                       "rank_mask": 2, "scratch_top": scratch})
        recon.append({"type": "ecl_vm_tick", "seq": 1 + i, "vm": vm,
                      "stage_frame": i + 1, "order": i, "time_before": bits,
                      "async_id": async_id, "rank_mask": 2,
                      "pc_before": pc, "scratch_before": scratch})
    return retail, recon


def write(path: Path, events: list[dict]) -> None:
    path.write_text("".join(json.dumps(event) + "\n" for event in events), encoding="utf-8")


class ComparatorTest(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory()
        self.addCleanup(self.temp.cleanup)
        self.retail_path = Path(self.temp.name) / "retail.jsonl"
        self.recon_path = Path(self.temp.name) / "recon.jsonl"
        self.retail, self.recon = fixtures()

    def run_cli(self, *options, code=0, raw=False):
        if not raw:
            write(self.retail_path, self.retail)
            write(self.recon_path, self.recon)
        result = subprocess.run([sys.executable, str(TOOL), *options,
                                 str(self.retail_path), str(self.recon_path)],
                                capture_output=True, text=True)
        output = result.stdout + result.stderr
        self.assertEqual(result.returncode, code, output)
        self.assertNotIn("Traceback", output)
        return output

    def test_matching_fixture_and_library_results(self):
        output = self.run_cli()
        self.assertIn("RESULT: PASS", output)
        self.assertIn("identity alignment (entry pc + async_id): 2/2", output)
        self.assertIn("per-tick full agreement (clock+fields+pc): 4/4", output)
        r, bases = retail_ticks(self.retail)
        c = recon_ticks(self.recon)
        self.assertEqual(bases, [BASE])
        self.assertEqual([vm for vm, _ in ordered_vms(r)], [500001, 500099])
        self.assertEqual([vm for vm, _ in ordered_vms(c)], [1, 99])
        with redirect_stdout(io.StringIO()):
            self.assertTrue(all_compare(r, c))
            self.assertTrue(clock_compare(r, c))
            self.assertTrue(flat_compare(r, c))
        self.assertTrue(tick_agrees(r[0], c[0]))
        with self.assertRaises(KeyError):
            key_fields({"rank": 1, "async_id": 2})
        self.run_cli("--all")

    def test_each_compared_field_diverges(self):
        for field in ("pc_before", "time_before", "rank_mask", "async_id", "scratch_before"):
            with self.subTest(field=field):
                self.retail, self.recon = fixtures()
                self.recon[3][field] += 1
                output = self.run_cli(code=1)
                self.assertIn("FIRST PER-TICK DIVERGENCE at vm position 0 tick 1", output)

    def test_creation_identity_mismatch(self):
        self.recon[2]["pc_before"] += 4
        output = self.run_cli(code=1)
        self.assertIn("identity alignment (entry pc + async_id): 1/2", output)

    def test_extra_and_missing_vms(self):
        for side in ("retail", "recon"):
            with self.subTest(side=side):
                self.retail, self.recon = fixtures()
                events = getattr(self, side)
                extra = copy.deepcopy(events[-1])
                extra["vm"] += 1000
                extra["seq"] += 1
                events.append(extra)
                self.assertIn("unpaired VMs:", self.run_cli(code=1))

    def test_extra_and_missing_ticks(self):
        for side in ("retail", "recon"):
            with self.subTest(side=side):
                self.retail, self.recon = fixtures()
                getattr(self, side).pop()
                output = self.run_cli(code=1)
                self.assertIn("equal per-VM tick counts: 1/2", output)
                self.assertIn("unpaired ticks", output)

    def test_equal_total_counts_do_not_hide_per_vm_tails(self):
        self.recon[-1]["vm"] = 1
        output = self.run_cli(code=1)
        self.assertIn("equal per-VM tick counts: 0/2", output)
        self.assertIn("retail=1 recon=1", output)

    def test_empty_streams_never_pass(self):
        for side in ("retail", "recon", "both"):
            for mode in ("--all", "--clock", "--flat", "--timeline", "--self-check"):
                with self.subTest(side=side, mode=mode):
                    self.retail, self.recon = fixtures()
                    if side in ("retail", "both"):
                        self.retail = self.retail[:3]
                    if side in ("recon", "both"):
                        self.recon = self.recon[:1]
                    self.run_cli(mode, code=1)

    def test_missing_or_null_required_evidence(self):
        for side, field in (("retail", "clock"), ("retail", "ip"),
                            ("recon", "time_before"), ("recon", "pc_before")):
            for null in (False, True):
                with self.subTest(side=side, field=field, null=null):
                    self.retail, self.recon = fixtures()
                    tick = getattr(self, side)[-1]
                    if null:
                        tick[field] = None
                    else:
                        del tick[field]
                    self.assertIn("incomplete PC/clock evidence", self.run_cli(code=1))

    def test_unresolved_zero_outside_and_ambiguous_ip(self):
        for ip in (0, BASE - 1, BASE + 0x200000):
            with self.subTest(ip=ip):
                self.retail, self.recon = fixtures()
                self.retail[-1]["ip"] = ip
                self.run_cli(code=1)
        self.retail, self.recon = fixtures()
        self.retail.insert(2, {"type": "script_register", "seq": 1, "arg0": BASE - 0x100})
        self.run_cli(code=1)
        self.retail[2]["arg0"] = BASE  # duplicate same registration is unambiguous
        self.run_cli()

    def test_no_script_base_is_incomplete(self):
        self.retail.pop(1)
        self.run_cli(code=1)

    def test_nonfinite_clocks_and_negative_pc_are_incomplete(self):
        for bits in (0x7F800000, 0xFF800000, 0x7FC00000):
            with self.subTest(bits=bits):
                self.retail, self.recon = fixtures()
                self.retail[3]["clock"] = self.recon[1]["time_before"] = bits
                self.run_cli(code=1)
        self.retail, self.recon = fixtures()
        self.recon[-1]["pc_before"] = -1
        self.run_cli(code=1)

    def test_explicit_prefix_scope_excludes_only_reported_tails(self):
        self.recon[-1]["rank_mask"] = 999
        self.run_cli(code=1)
        output = self.run_cli("--prefix-ticks", "3")
        self.assertIn("exactly 3 global ticks per side", output)
        self.assertIn("excluded tails (not compared): retail=1 recon=1 ticks", output)
        self.run_cli("--prefix-ticks", "4", code=1)
        self.run_cli("--prefix-ticks", "5", code=1)
        self.recon.pop()
        self.run_cli("--prefix-ticks", "4", code=1)
        self.run_cli("--prefix-ticks", "3")

    def test_clock_mode_root_scope_and_prefix(self):
        self.recon[-1]["rank_mask"] += 1  # child excluded by documented root scope
        self.run_cli("--clock")
        self.recon[3]["time_before"] = None
        output = self.run_cli("--clock", code=1)
        self.assertIn("FIRST CLOCK DIVERGENCE at root tick 1", output)
        self.assertIn("recon=None", output)
        self.assertIn("exactly 1 root ticks", self.run_cli("--clock", "--prefix-ticks", "1"))
        self.run_cli("--clock", "--prefix-ticks", "3", code=1)

    def test_clock_mode_requires_pc_and_equal_root_counts(self):
        self.recon[3]["pc_before"] += 1
        self.run_cli("--clock", code=1)
        self.retail, self.recon = fixtures()
        self.recon.pop(3)
        self.run_cli("--clock", code=1)
        self.retail, self.recon = fixtures()
        for tick in self.recon[1:]:
            tick["vm"] += 1
        self.run_cli("--clock", code=1)

    def test_flat_is_explicitly_field_only_and_checks_lengths(self):
        self.recon[-1]["time_before"] = None
        self.assertIn("no VM/PC/clock parity claim", self.run_cli("--flat"))
        self.recon[-1]["rank_mask"] += 1
        self.run_cli("--flat", code=1)
        self.recon.pop()
        self.run_cli("--flat", code=1)

    def test_timeline_requires_complete_bucket_sets_and_values(self):
        # Establish a synthetic exact integer clock / stage_frame alignment.
        for r, c in zip(self.retail[3:], self.recon[1:]):
            c["stage_frame"] = 1 if r["clock"] == 1065353216 else 0
        self.assertIn("no VM/PC/bit-exact-clock parity claim", self.run_cli("--timeline"))
        self.recon[-1]["stage_frame"] = 100
        self.run_cli("--timeline", code=1)
        self.recon[-1]["stage_frame"] = 1
        self.recon[-1]["rank_mask"] += 1
        self.run_cli("--timeline", code=1)
        self.retail[-1]["clock"] = None
        self.run_cli("--timeline", code=1)

    def test_self_check_does_not_claim_cross_stream_agreement(self):
        self.recon[-1]["rank_mask"] += 1
        self.run_cli(code=1)
        self.assertIn("no independent repeatability or retail parity claim", self.run_cli("--self-check"))
        self.recon[-1]["time_before"] = None
        self.run_cli("--self-check", code=1)

    def test_invalid_field_types_and_missing_fields_are_clean_errors(self):
        for field, value in (("rank_mask", None), ("async_id", "7"),
                             ("vm", True), ("time_before", -1),
                             ("time_before", 0x100000000), ("time_before", 1.5)):
            with self.subTest(field=field, value=value):
                self.retail, self.recon = fixtures()
                self.recon[1][field] = value
                self.assertIn("invalid input:", self.run_cli(code=2))
        self.retail, self.recon = fixtures()
        del self.recon[1]["scratch_before"]
        self.run_cli(code=2)

    def test_bad_files_headers_and_events_are_clean_errors(self):
        write(self.recon_path, self.recon)
        for contents in ("", "[]\n", "{bad json}\n", '{}\n',
                         '{"type":"header"}\n',
                         '{"type":"header","format":"wrong"}\n'):
            with self.subTest(contents=contents):
                self.retail_path.write_text(contents)
                self.run_cli(code=2, raw=True)
        self.retail_path.unlink()
        self.run_cli(code=2, raw=True)
        self.retail_path.write_bytes(b"\xff")
        self.run_cli(code=2, raw=True)
        self.retail = [self.retail[0]]
        self.run_cli(code=2)  # missing stage entry

    def test_invalid_options(self):
        for options in (("--all", "--clock"), ("--prefix-ticks", "0"),
                        ("--prefix-ticks", "-1"), ("--prefix-ticks", "x"),
                        ("--timeline", "--prefix-ticks", "1"),
                        ("--self-check", "--prefix-ticks", "1")):
            with self.subTest(options=options):
                self.run_cli(*options, code=2)


def main() -> None:
    result = unittest.TextTestRunner(verbosity=1).run(unittest.defaultTestLoader.loadTestsFromTestCase(ComparatorTest))
    if not result.wasSuccessful():
        raise SystemExit(1)
    print("RETAIL_VS_RECON_STAGE_TEST_PASS")


if __name__ == "__main__":
    main()
