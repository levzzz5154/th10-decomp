#!/usr/bin/env python3
"""Audit inventory regressions: omitted scope and stale evidence must fail."""

import json
import shutil
import sys
import tempfile
import unittest
from pathlib import Path

REPOSITORY = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(REPOSITORY / "matching2/tools"))
import audit_inventory as inventory


class AuditInventoryTest(unittest.TestCase):
    def setUp(self):
        self.temporary = tempfile.TemporaryDirectory()
        self.addCleanup(self.temporary.cleanup)
        self.root = Path(self.temporary.name)
        # Use the real frozen address/report sets, but small independent source
        # and reference fixtures so the tests do not edit the working tree.
        for relative in (*inventory.PRIOR_INPUTS, "matching2/coverage.json",
                         "decompiled/ghidra_raw/index.tsv", "matching2/tools/build_hybrid.py"):
            target = self.root / relative
            target.parent.mkdir(parents=True, exist_ok=True)
            shutil.copyfile(REPOSITORY / relative, target)
        self.write("matching2/src/a.cpp", "// 0x0044C350 - retail table\nfloat first() { return 0; }\n")
        self.write("matching2/src/z.cpp", "// 0x0044C350 - retail table\nfloat second() { return 1; }\n")
        self.write("matching2/include/contract.hpp", "// calls sub_44C350 from the host adapter\nvoid callback();\n")
        self.write("matching2/include/cstdint", "typedef unsigned int uint32_t;\n")
        self.write("matching2/standalone/helper.cpp", "int helper() { return 3; }\n")
        self.write("matching2/standalone/app.rc", "1 VERSIONINFO\n")
        self.write("ida/th10.exe.c", "//----- (0044C350) -----\nfloat sub_44C350()\n{ return 0; }\n"
                   "//----- (00401100) -----\nint sub_401100()\n{ return 0; }\n"
                   "//----- (00438AD0) -----\nint __stdcall WinMain(int argument)\n{ return 0; }\n")
        self.write("ida/th10.exe.asm", "sub_44C350 proc near\nret\nsub_44C350 endp\n"
                   "sub_401100 proc near\nret\nsub_401100 endp\n"
                   "_WinMain@16 proc near\nret\n_WinMain@16 endp\n")
        self.write("ida/th10.exe.h", "struct Example { int value; };\n")

    def write(self, relative, text):
        target = self.root / relative
        target.parent.mkdir(parents=True, exist_ok=True)
        target.write_text(text)

    def mutate_json(self, relative, operation):
        path = self.root / relative
        doc = json.loads(path.read_text())
        operation(doc)
        path.write_text(json.dumps(doc))

    def test_all_722_addresses_and_historical_scopes_are_separate(self):
        doc = inventory.generate(self.root)
        self.assertEqual(doc["summary"]["coverage_addresses"], 722)
        self.assertEqual(len({row["address"] for row in doc["functions"]}), 722)
        self.assertEqual(doc["prior_audit"]["scope"]["partition_addresses"], 708)
        self.assertEqual(doc["prior_audit"]["reported_counts"]["reviewed"], 57)
        self.assertEqual(doc["summary"]["prior_review_counts"], {
            "outside_prior_bounded_and_sparse_scopes": 9,
            "pending_bounded_review": 634, "reference_unresolved": 17,
            "reported_grounded": 28, "reported_partial": 29, "separate_sparse_review": 5})
        self.assertTrue(all(row["current_audit_status"] == "pending_revalidation" for row in doc["functions"]))
        self.assertIsNone(doc["prior_audit"]["original_bounded_review_baseline_commit"])

    def test_missing_coverage_address_is_rejected(self):
        self.mutate_json("matching2/coverage.json", lambda doc: doc["functions"].pop())
        with self.assertRaisesRegex(ValueError, "coverage address inventory mismatch"):
            inventory.generate(self.root)

    def test_duplicate_coverage_row_is_rejected(self):
        self.mutate_json("matching2/coverage.json", lambda doc: doc["functions"].append(doc["functions"][0]))
        with self.assertRaisesRegex(ValueError, "coverage address inventory mismatch"):
            inventory.generate(self.root)

    def test_multiple_claimants_and_incidental_reference_are_preserved(self):
        doc = inventory.generate(self.root)
        row = next(row for row in doc["functions"] if row["address"] == "0x0044C350")
        self.assertEqual(row["candidate_claim_files"], ["matching2/src/a.cpp", "matching2/src/z.cpp"])
        self.assertTrue(row["multiple_candidate_claim_files"])
        self.assertEqual(len(row["source_occurrences"]), 3)
        self.assertEqual(row["source_occurrences"][-1]["kind"], "address_reference")
        self.assertTrue(all(item["line"] == 1 for item in row["source_occurrences"]))
        self.assertEqual(row["references"]["ida_c"]["line_start"], 1)
        self.assertEqual(row["references"]["ida_asm"]["line_end"], 3)

    def test_named_assembly_and_ida_only_boundary_are_exposed(self):
        doc = inventory.generate(self.root)
        rows = doc["functions"] + doc["ida_boundary_review_candidates"]
        winmain = next(row for row in rows if row["address"] == "0x00438AD0")
        self.assertEqual(winmain["references"]["ida_asm"]["symbol"], "_WinMain@16")
        self.assertEqual(winmain["references"]["ida_asm"]["mapping"], "pseudocode_signature")
        boundary = next(row for row in doc["ida_boundary_review_candidates"] if row["address"] == "0x00401100")
        self.assertEqual(boundary["status"], "boundary_review_candidate")

    def test_uncredited_and_extensionless_files_stay_in_scope(self):
        doc = inventory.generate(self.root)
        files = {row["path"]: row for row in doc["file_audit_scope"]}
        for path in ("matching2/standalone/helper.cpp", "matching2/include/cstdint", "matching2/standalone/app.rc"):
            self.assertEqual(files[path]["candidate_claim_addresses"], [])
            self.assertEqual(files[path]["audit_status"], "pending_file_review")
            self.assertEqual(len(files[path]["sha256"]), 64)

    def test_prior_review_count_mismatch_fails(self):
        self.mutate_json(inventory.SUMMARY, lambda doc: doc["status"].update(reviewed=58))
        with self.assertRaisesRegex(ValueError, "prior bounded audit scope/counts"):
            inventory.generate(self.root)

    def test_prior_partition_omission_fails(self):
        def remove(doc):
            files = next(iter(doc["groups"].values()))["files"]
            next(iter(files.values())).pop()
        self.mutate_json(inventory.MANIFEST, remove)
        with self.assertRaisesRegex(ValueError, "prior bounded audit scope/counts"):
            inventory.generate(self.root)

    def test_content_change_and_missing_output_are_detected(self):
        first = inventory.output_files(inventory.generate(self.root))
        output = self.root / "outputs"
        output.mkdir()
        self.assertEqual(set(inventory.check_outputs(output, first)), {"inventory.json", "inventory.md"})
        for name, content in first.items():
            (output / name).write_text(content)
        self.assertEqual(inventory.check_outputs(output, first), [])
        self.assertEqual(first, inventory.output_files(inventory.generate(self.root)))
        # No annotation or line count changes: the helper's content hash alone
        # must invalidate the evidence snapshot.
        self.write("matching2/standalone/helper.cpp", "int helper() { return 4; }\n")
        current = inventory.output_files(inventory.generate(self.root))
        self.assertIn("inventory.json", inventory.check_outputs(output, current))
        self.assertNotEqual(first["inventory.json"], current["inventory.json"])

    def test_reference_and_historical_finding_changes_are_detected(self):
        first = inventory.output_files(inventory.generate(self.root))
        self.write("ida/th10.exe.h", "struct Example { float value; };\n")
        second = inventory.output_files(inventory.generate(self.root))
        self.assertNotEqual(first["inventory.json"], second["inventory.json"])
        self.mutate_json(inventory.SUMMARY, lambda doc: doc["rows"][0].update(finding="changed historical claim"))
        third = inventory.output_files(inventory.generate(self.root))
        self.assertNotEqual(second["inventory.json"], third["inventory.json"])


if __name__ == "__main__":
    unittest.main()
