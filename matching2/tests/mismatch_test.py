"""Mismatch diagnostics must locate operand changes and preserve the byte gate."""
import hashlib
from pathlib import Path
import shutil
import struct
import sys
import tempfile
import unittest
from unittest.mock import patch

if __package__ in (None, ""):
    sys.path.insert(0, str(Path(__file__).resolve().parents[2]))

from matching2.tools.matching.build_msvc import verify_linked
from matching2.tools.matching.mismatch import describe_mismatch, instruction_at

START = 0x401000
EXPECTED = bytes.fromhex("55 e8 10 00 00 00 5d c3")
ACTUAL = bytes.fromhex("55 e8 20 00 00 00 5d c3")


def pe_fixture(text):
    header = bytearray(512)
    header[:2] = b"MZ"
    struct.pack_into("<I", header, 0x3C, 0x80)
    header[0x80:0x84] = b"PE\0\0"
    struct.pack_into("<HHIIIHH", header, 0x84, 0x14C, 1, 0, 0, 0, 224, 0x102)
    struct.pack_into("<H", header, 0x98, 0x10B)
    struct.pack_into("<I", header, 0x98 + 28, 0x400000)
    struct.pack_into("<8sIIIIIIHHI", header, 0x98 + 224,
                     b".text\0\0\0", len(text), 0x1000, len(text), 512, 0, 0, 0, 0, 0x60000020)
    return header + text


class MismatchTest(unittest.TestCase):
    def setUp(self):
        self.config = {"text_start": hex(START), "text_bytes": len(EXPECTED),
                       "text_sha256": hashlib.sha256(EXPECTED).hexdigest(),
                       "regions": [{"address": hex(START), "size": len(EXPECTED), "kind": "semantic",
                                    "name": "Release", "source": "src/game/entity.cpp", "symbol": "_Release"}]}

    def test_operand_change_reports_region_source_and_expected_bytes(self):
        with patch("matching2.tools.matching.mismatch.instruction_at", return_value="decoded call"):
            report = describe_mismatch(ACTUAL, EXPECTED, self.config)
        self.assertIn("first at 0x00401002", report)
        self.assertIn("Region: Release + 0x2 (semantic)", report)
        self.assertIn("Source: src/game/entity.cpp", report)
        self.assertIn("Symbol: _Release", report)
        self.assertIn("Expected bytes at 0x00401002: 10 00 00 00 5d c3", report)
        self.assertIn("Actual bytes at   0x00401002: 20 00 00 00 5d c3", report)

    def test_decoder_starts_at_instruction_boundary_before_changed_operand(self):
        if not (shutil.which("i686-w64-mingw32-objdump") or shutil.which("objdump")):
            self.skipTest("GNU objdump is unavailable")
        expected = instruction_at(EXPECTED, START, START + 2)
        actual = instruction_at(ACTUAL, START, START + 2)
        self.assertIn("0x00401001: e8 10 00 00 00", expected)
        self.assertIn("call", expected)
        self.assertIn("401016", expected)
        self.assertIn("401026", actual)

    def test_data_is_not_disassembled(self):
        self.config["regions"][0]["kind"] = "data"
        with patch("matching2.tools.matching.mismatch.instruction_at") as decoder:
            report = describe_mismatch(ACTUAL, EXPECTED, self.config)
        decoder.assert_not_called()
        self.assertIn("Expected bytes", report)

    def test_authenticated_reference_explains_failure_but_never_repairs_output(self):
        with tempfile.TemporaryDirectory() as temporary:
            directory = Path(temporary)
            linked, reference = directory / "linked.exe", directory / "text.bin"
            linked.write_bytes(pe_fixture(ACTUAL))
            reference.write_bytes(EXPECTED)
            before = linked.read_bytes()
            with self.assertRaisesRegex(ValueError, "Source: src/game/entity.cpp"):
                verify_linked(linked, self.config, reference_text_path=reference)
            self.assertEqual(linked.read_bytes(), before)
            # A matching-looking reference with the wrong hash is not evidence.
            reference.write_bytes(ACTUAL)
            with self.assertRaisesRegex(ValueError, "Diagnostic reference does not match"):
                verify_linked(linked, self.config, reference_text_path=reference)
            reference.unlink()
            with self.assertRaisesRegex(ValueError, "Run make reference"):
                verify_linked(linked, self.config, reference_text_path=reference)
            # Success never needs to open any diagnostic reference.
            linked.write_bytes(pe_fixture(EXPECTED))
            self.assertEqual(verify_linked(linked, self.config, reference_text_path=reference), EXPECTED)

    def test_explicit_oracle_also_explains_the_mismatch(self):
        with tempfile.TemporaryDirectory() as temporary:
            linked = Path(temporary) / "linked.exe"
            linked.write_bytes(pe_fixture(ACTUAL))
            with self.assertRaisesRegex(ValueError, "Region: Release"):
                verify_linked(linked, self.config, oracle=pe_fixture(EXPECTED))


if __name__ == "__main__":
    unittest.main()
