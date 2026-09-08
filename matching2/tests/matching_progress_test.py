"""Progress must reflect source classifications, not cached or stale counts."""

import sys
from pathlib import Path

if __package__ in (None, ""):
    sys.path.insert(0, str(Path(__file__).resolve().parents[2]))
import json
import subprocess
import tempfile
import unittest

from matching2.tools.matching.progress import summarize

ROOT = Path(__file__).resolve().parents[2]
TOOL = ROOT / "matching2/tools/matching/progress.py"


class MatchingProgressTest(unittest.TestCase):
    def test_categories_are_separate_and_empty_categories_remain_visible(self):
        summary = summarize([{"kind": "semantic", "size": 12},
                             {"kind": "asm", "size": 50},
                             {"kind": "semantic", "size": 8}])
        self.assertEqual(summary["regions"], {"semantic": 2, "asm": 1, "data": 0, "padding": 0})
        self.assertEqual(summary["bytes"], {"semantic": 20, "asm": 50, "data": 0, "padding": 0})

    def test_invalid_classification_and_size_rejected(self):
        for region in ({"kind": "unknown", "size": 1}, {"kind": "semantic", "size": -1},
                       {"kind": "semantic", "size": True}):
            with self.subTest(region=region), self.assertRaises(ValueError):
                summarize([region])

    def test_cli_ignores_cached_counts_and_rejects_stale_document(self):
        with tempfile.TemporaryDirectory() as temporary:
            directory = Path(temporary)
            manifest, document = directory / "regions.json", directory / "PROGRESS.md"
            config = {"text_bytes": 20, "regions": [{"kind": "semantic", "size": 20}],
                      "summary": {"regions_by_kind": {"semantic": 999}}}
            manifest.write_text(json.dumps(config))
            command = [sys.executable, str(TOOL), "--manifest", str(manifest), "--document", str(document)]
            result = subprocess.run(command + ["--write"], cwd=directory, capture_output=True, text=True)
            self.assertEqual(result.returncode, 0, result.stderr)
            self.assertIn("| Ordinary C++ | 1 | 20 |", document.read_text())
            result = subprocess.run(command + ["--check"], cwd=directory, capture_output=True, text=True)
            self.assertEqual(result.returncode, 0, result.stderr)
            config["regions"][0]["kind"] = "asm"
            manifest.write_text(json.dumps(config))
            result = subprocess.run(command + ["--check"], cwd=directory, capture_output=True, text=True)
            self.assertNotEqual(result.returncode, 0)
            self.assertIn("stale", result.stderr)


if __name__ == "__main__":
    unittest.main()
