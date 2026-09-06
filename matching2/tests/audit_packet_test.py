"""Protect baseline isolation and exact-address reference extraction."""
import sys
import unittest
from pathlib import Path
from unittest.mock import patch

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "tools"))
import audit_packets as packets
import audit_host_contracts as host


class AuditPacketTest(unittest.TestCase):
    def test_reads_immutable_git_revision(self):
        commit = "a" * 40
        with patch.object(packets, "git", side_effect=[(commit + "\n").encode(), b"a.cpp\n", b"original\n"]) as git:
            snapshot = packets.Snapshot(commit)
            self.assertEqual(snapshot.text("a.cpp"), "original\n")
            self.assertEqual(snapshot.text("a.cpp"), "original\n")
            git.assert_called_with("show", commit + ":a.cpp")
            self.assertEqual(git.call_count, 3)

    def test_exact_procedure_boundaries(self):
        text = "sub_44C350 proc near\n fld st\nsub_44C350 endp\nsub_44C351 proc near\n"
        self.assertEqual(packets.ida_range(text, "0x0044C350", True), (1, 3))
        with self.assertRaises(ValueError):
            packets.ida_range(text, "0x0044C351", True)

    def test_no_neighbor_pseudocode_credit(self):
        text = "//----- (0044C350) ---\nfloat a() {}\n//----- (0044C351) ---\nfloat b() {}\n"
        self.assertEqual(packets.ida_range(text, "0x0044C350", False), (1, 2))
        with self.assertRaises(ValueError):
            packets.ida_range(text, "0x0044C352", False)

    def test_pseudocode_final_line_without_newline(self):
        text = "//----- (0044C350) ---\nfloat a() {}"
        self.assertEqual(packets.ida_range(text, "0x0044C350", False), (1, 2))

    def test_host_discard_and_constant_candidates(self):
        text = "void Ignore(void* p) { (void)p; }\nfloat Fixed(int x) { (void)x; return 0.5f; }\n"
        self.assertEqual([r["kind"] for r in host.candidates(text)], ["no_work", "constant_result"])

    def test_host_real_work_and_comments_are_not_empty(self):
        text = "// void Bogus() {}\nvoid Real(int x) { work(x); }\n"
        self.assertEqual(host.candidates(text), [])

    def test_host_function_inside_raw_string_is_not_code(self):
        text = 'const char* example = R"doc(\nvoid ExampleOnly() {}\n)doc";\n'
        self.assertEqual(host.candidates(text), [])

    def test_host_shared_fallback_and_lines(self):
        text = "/* comment\nmore */\nstatic float* Slot(int id) { (void)id; static float fallback; return &fallback; }\n"
        row, = host.candidates(text)
        self.assertEqual(row["kind"], "shared_fallback_slot")
        self.assertEqual(row["line"], 3)


if __name__ == "__main__":
    unittest.main()
