"""Check that historical metadata cannot manufacture current completion."""

import sys
from pathlib import Path

if __package__ in (None, ""):
    sys.path.insert(0, str(Path(__file__).resolve().parents[2]))

from collections import defaultdict
import unittest
from unittest.mock import patch

from matching2.tools.runtime import coverage_report
from matching2.tools.runtime import standalone_readiness


class ProgressEvidenceTest(unittest.TestCase):
    def test_overlay_membership_is_inventory_only(self):
        address = 0x00435320
        with patch.object(coverage_report, "tracked_functions", return_value={}), \
             patch.object(coverage_report, "overlay_entries",
                          return_value={address: ("example.obj", "example")}), \
             patch.object(coverage_report, "source_annotations",
                          return_value=(defaultdict(set), defaultdict(set), defaultdict(set))):
            entry, = coverage_report.generate()["functions"]
        self.assertEqual(entry["status"], "unrecovered")
        self.assertEqual(entry["source"], "unrecovered")

    def test_summary_includes_incomplete_categories(self):
        summary = coverage_report.coverage_summary([
            {"status": "partial", "size": 100},
            {"status": "researched", "size": 200},
            {"status": "unrecovered", "size": None},
        ])
        for status in ("partial", "researched", "unrecovered"):
            self.assertEqual(summary["by_status"][status]["function_count"], 1)
        self.assertEqual(summary["by_status"]["semantic"]["function_count"], 0)

    def test_source_report_does_not_certify_execution(self):
        report = standalone_readiness.generate()
        gates = report["integration_gates"]
        self.assertIsNone(gates["current_executable_produced"]["passed"])
        self.assertIsNone(gates["current_startup_to_title_smoke_test"]["passed"])
        self.assertFalse(gates["retail_data_independent_build"]["passed"])
        self.assertFalse(report["summary"]["standalone_ready"])


if __name__ == "__main__":
    unittest.main()
