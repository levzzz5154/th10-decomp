"""Failure gates for full-text source recovery and build publication."""

import sys
from pathlib import Path

if __package__ in (None, ""):
    sys.path.insert(0, str(Path(__file__).resolve().parents[2]))


import json
import shutil
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[1]
from matching2.tools.maintenance.generate_asm_text import consume_unresolved, replace_instructions


class RecoveryPartitionTest(unittest.TestCase):
    def test_boundary_correction_consumes_prefix_and_explicit_bad_row(self):
        rows = {0x1001: {"data": bytes.fromhex("c8f74600")}}
        spans = [{"start": 0x1000, "end": 0x1000, "kind": "unresolved"}]
        correction = {"start": 0x1000, "end": 0x1004, "old_rows": [0x1001],
                      "evidence": ["PUSH immediate entered from preceding instruction"],
                      "additional_instructions": [{"address": 0x1000, "hex": "68c8f74600"}]}
        self.assertEqual(replace_instructions(rows, spans, correction), [])
        self.assertEqual(rows, {})

    def test_boundary_correction_cannot_discard_unmentioned_row(self):
        rows = {0x1001: {"data": bytes.fromhex("c8f74600")}}
        spans = [{"start": 0x1000, "end": 0x1000, "kind": "unresolved"}]
        with self.assertRaisesRegex(ValueError, "known instructions"):
            replace_instructions(rows, spans, {
                "start": 0x1000, "end": 0x1004, "old_rows": [], "evidence": ["fixture"],
                "additional_instructions": [{"address": 0x1000, "hex": "68c8f74600"}]})

    def test_recovery_splits_unknown_interval_without_losing_bytes(self):
        spans = [{"start": "0x1000", "end": "0x100F", "kind": "unresolved"}]
        resolved = {"start": "0x1004", "end": "0x1007", "kind": "data", "evidence": ["fixture"]}
        result = consume_unresolved(spans, 0x1004, 0x1008, resolved)
        self.assertEqual([(int(s["start"], 16), int(s["end"], 16), s["kind"]) for s in result],
                         [(0x1000, 0x1003, "unresolved"), (0x1004, 0x1007, "data"),
                          (0x1008, 0x100F, "unresolved")])

    def test_recovery_cannot_hide_a_known_instruction_between_ranges(self):
        spans = [{"start": "0x1000", "end": "0x1003", "kind": "unresolved"},
                 {"start": "0x1008", "end": "0x100F", "kind": "unresolved"}]
        with self.assertRaisesRegex(ValueError, "known instructions"):
            consume_unresolved(spans, 0x1000, 0x1010)

    def test_recovery_cannot_overwrite_reviewed_data(self):
        with self.assertRaisesRegex(ValueError, "already classified"):
            consume_unresolved([{"start": "0x1000", "end": "0x100F", "kind": "data"}], 0x1000, 0x1004)


class BuildPublicationTest(unittest.TestCase):
    def test_bad_manifest_invalidates_old_success_outputs(self):
        if not shutil.which("i686-w64-mingw32-as") or not shutil.which("i686-w64-mingw32-ld"):
            self.skipTest("x86 PE binutils unavailable")
        with tempfile.TemporaryDirectory() as temporary:
            directory = Path(temporary)
            source, output = directory / "source", directory / "output"
            source.mkdir()
            output.mkdir()
            (source / "manifest.json").write_text(json.dumps({"text_sha256": "wrong"}))
            (output / "text.bin").write_bytes(b"stale")
            (output / "report.json").write_text("{}")
            result = subprocess.run([sys.executable, str(ROOT / "tools/matching/build_asm_text.py"),
                                     "--source-dir", str(source), "--output", str(output)],
                                    capture_output=True, text=True)
            self.assertNotEqual(result.returncode, 0)
            self.assertIn("source manifest", result.stderr)
            self.assertFalse((output / "text.bin").exists())
            self.assertFalse((output / "report.json").exists())


if __name__ == "__main__":
    unittest.main()
