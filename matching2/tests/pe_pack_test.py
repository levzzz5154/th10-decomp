#!/usr/bin/env python3
"""Tests for the no-retail-input PE packaging gate."""

import sys
from pathlib import Path

if __package__ in (None, ""):
    sys.path.insert(0, str(Path(__file__).resolve().parents[2]))


import hashlib
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[2]
from matching2.tools.matching import pack_asm_pe  # noqa: E402


RETAIL = Path.home() / "Games" / "TH10 - Mountain of Faith" / "th10.exe"
LAYOUT = ROOT / "matching2" / "asm" / "pe_layout.json"
DOS_CODE = (bytes.fromhex("0e1fba0e00b409cd21b8014ccd21") +
            b"This program cannot be run in DOS mode.\r\r\n$" + bytes(7))


class PEPackagingTest(unittest.TestCase):
    def test_rejects_missing_text_input(self):
        with tempfile.TemporaryDirectory() as directory:
            with self.assertRaises(pack_asm_pe.PackError):
                pack_asm_pe.build_image(LAYOUT, Path(directory) / "missing.bin",
                                         Path(directory) / "out.exe")

    def test_rejects_short_text_before_packaging(self):
        with tempfile.TemporaryDirectory() as directory:
            text = Path(directory) / "text.bin"
            text.write_bytes(bytes(412671))
            with self.assertRaisesRegex(pack_asm_pe.PackError, "412671 bytes; expected 412672"):
                pack_asm_pe.build_image(LAYOUT, text, Path(directory) / "out.exe")

    def test_rejects_same_size_wrong_text_hash(self):
        with tempfile.TemporaryDirectory() as directory:
            text = Path(directory) / "text.bin"
            text.write_bytes(bytes(412672))
            with self.assertRaisesRegex(pack_asm_pe.PackError, "assembled .text hash mismatch"):
                pack_asm_pe.build_image(LAYOUT, text, Path(directory) / "out.exe")

    def test_rejects_second_executable_section(self):
        layout = pack_asm_pe._load_layout(LAYOUT)
        layout["sections"][1]["executable"] = True
        layout["sections"][1]["characteristics"] |= 0x20000000
        with self.assertRaisesRegex(pack_asm_pe.PackError, "only .text may be executable"):
            pack_asm_pe._validate_layout(layout)

    def test_rejects_unaccounted_raw_gap(self):
        layout = pack_asm_pe._load_layout(LAYOUT)
        layout["sections"][1]["raw_offset"] += 512
        with self.assertRaisesRegex(pack_asm_pe.PackError, "unaccounted file range"):
            pack_asm_pe._validate_layout(layout)

    def test_accepts_explicit_dos_code_without_assembler(self):
        layout = pack_asm_pe._load_layout(LAYOUT)
        prefix = pack_asm_pe._build_dos_prefix(
            LAYOUT, layout["dos_prefix"], "missing-assembler", "missing-objcopy", DOS_CODE)
        self.assertEqual(len(DOS_CODE), 64)
        self.assertEqual(hashlib.sha256(DOS_CODE).hexdigest(),
                         layout["dos_prefix"]["code"]["sha256"])
        self.assertEqual(hashlib.sha256(prefix).hexdigest(), layout["dos_prefix"]["sha256"])

    def test_build_without_oracle_matches_declared_image(self):
        if not RETAIL.is_file():
            self.skipTest("supported local retail executable is unavailable")
        retail = RETAIL.read_bytes()
        text = retail[1024:1024 + 412672]
        self.assertEqual(hashlib.sha256(text).hexdigest(),
                         "c1acff416da826334c29a19fa89cd7a094626eb36c32afe7950f705a55f56998")
        with tempfile.TemporaryDirectory() as directory:
            text_path = Path(directory) / "text.bin"
            output = Path(directory) / "th10.exe"
            text_path.write_bytes(text)
            report = pack_asm_pe.build_image(LAYOUT, text_path, output)
            self.assertFalse(report["verified_against_oracle"])
            self.assertEqual(report["sha256"],
                             "2f14760b6fbbf57549541583283badb9a19a4222b90f0a146d5aa17f01dc9040")


if __name__ == "__main__":
    unittest.main()
