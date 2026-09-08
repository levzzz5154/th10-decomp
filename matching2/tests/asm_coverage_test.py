#!/usr/bin/env python3
"""Regression checks for the complete assembly coverage partition."""

import sys
from pathlib import Path

if __package__ in (None, ""):
    sys.path.insert(0, str(Path(__file__).resolve().parents[2]))


import json
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[1]
from matching2.tools.reference import asm_coverage  # noqa: E402


class AssemblyCoverageTest(unittest.TestCase):
    def test_padding_pattern_is_only_a_candidate(self):
        self.assertEqual(asm_coverage._candidate_pattern(bytes([0xCC, 0xCC])), "repeated_CC")
        self.assertIsNone(asm_coverage._candidate_pattern(bytes([0xCC])))
        self.assertIsNone(asm_coverage._candidate_pattern(bytes([0xCC, 0x90])))

    def test_truncated_listing_tail_remains_explicit(self):
        with tempfile.TemporaryDirectory() as directory:
            path = Path(directory) / "listing.asm"
            path.write_text(
                "00401000\tAABB...\tIMAGE\n"
                "00401010\t90\tNOP\n",
                encoding="utf-8",
            )
            rows, truncated = asm_coverage.parse_listing(path, "fixture", 0x00401000, 0x0040101F)
        self.assertEqual(len(rows), 2)
        self.assertEqual(rows[0].data, bytes.fromhex("AABB"))
        self.assertEqual(rows[0].logical_end, 0x0040100F)
        self.assertEqual(truncated[0]["known_bytes"], 2)
        self.assertEqual(truncated[0]["logical_end"], "0x0040100F")

    def test_authenticated_partition_covers_every_text_byte(self):
        if not asm_coverage.DEFAULT_RETAIL.is_file():
            self.skipTest("supported local retail executable is unavailable")
        report = asm_coverage.audit()
        summary = report["summary"]
        counts = summary["byte_counts"]
        self.assertEqual(sum(counts.values()), 412672)
        self.assertEqual(summary["text_start"], "0x00401000")
        self.assertEqual(summary["text_end"], "0x00465BFF")
        self.assertEqual(summary["listing_gap_bytes"], 0)
        self.assertEqual(summary["validation_issue_count"], 0)
        self.assertTrue(report["validation"]["authenticated"])
        ranges = report["ranges"]
        self.assertEqual(ranges[0]["start"], summary["text_start"])
        self.assertEqual(ranges[-1]["end"], summary["text_end"])
        self.assertEqual(sum(item["bytes"] for item in ranges), 412672)


if __name__ == "__main__":
    unittest.main()
