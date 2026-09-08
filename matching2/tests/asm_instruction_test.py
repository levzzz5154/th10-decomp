#!/usr/bin/env python3
"""Regression checks for the instruction-to-GNU-as encoder."""

from __future__ import annotations

import sys
from pathlib import Path

if __package__ in (None, ""):
    sys.path.insert(0, str(Path(__file__).resolve().parents[2]))


import json
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[1]

try:
    from matching2.tools.matching import asm_instruction  # noqa: E402
except ImportError as exc:  # pragma: no cover - dependency is environment-specific
    asm_instruction = None
    _IMPORT_ERROR = exc
else:
    _IMPORT_ERROR = None


def _assemble(source: str) -> bytes:
    """Assemble one or more instructions and return the COFF .text bytes."""

    with tempfile.TemporaryDirectory() as directory:
        directory = Path(directory)
        assembly = directory / "instruction.s"
        object_file = directory / "instruction.o"
        binary = directory / "instruction.bin"
        assembly.write_text(
            ".intel_syntax noprefix\n.code32\n.text\n" + source + "\n",
            encoding="utf-8",
        )
        assembled = subprocess.run(
            ["i686-w64-mingw32-as", "--32", str(assembly), "-o", str(object_file)],
            capture_output=True,
            text=True,
        )
        if assembled.returncode:
            raise AssertionError(assembled.stderr)
        extracted = subprocess.run(
            ["objcopy", "-O", "binary", "-j", ".text", str(object_file), str(binary)],
            capture_output=True,
            text=True,
        )
        if extracted.returncode:
            raise AssertionError(extracted.stderr)
        return binary.read_bytes()


@unittest.skipIf(asm_instruction is None, f"iced-x86 unavailable: {_IMPORT_ERROR}")
class AssemblyInstructionTest(unittest.TestCase):
    def test_symbolic_references_are_stable(self):
        self.assertEqual(
            asm_instruction.instruction_to_asm(0x00401000, bytes.fromhex("E800000000")),
            "{disp32} call _th10_00401005",
        )
        self.assertEqual(
            asm_instruction.instruction_to_asm(0x00401000, bytes.fromhex("FF15E0764700")),
            "call dword ptr [_th10_004776e0]",
        )

    def test_semantic_sources_reassemble_byte_exactly(self):
        fixtures = {
            "C70614CB4600": 0x00401000,
            "8B8680000000": 0x00401006,
            "F3AB": 0x00401054,
            "D944240C": 0x00401000,
            "D95D54": 0x00401000,
            "DCC0": 0x00401000,
            "F6C444": 0x00401000,
            "C7C0FFFFFFFF": 0x00401000,
            "81C0FFFFFFFF": 0x00401000,
            "EBFE": 0x00401000,
            "9BDD3C24": 0x00401000,
        }
        for encoded, address in fixtures.items():
            with self.subTest(encoded=encoded):
                source = asm_instruction.instruction_to_asm(address, bytes.fromhex(encoded))
                self.assertNotIn(".byte", source.lower())
                expected = bytes.fromhex(encoded)
                # GNU COFF gives a standalone .text section two bytes of
                # alignment padding.  The instruction itself must occupy the
                # complete expected prefix; the parent full-text TU controls
                # padding at region boundaries.
                assembly_source = source
                if encoded == "EBFE":
                    # The branch's symbolic target is the instruction start;
                    # provide that local label just before the fixture.
                    assembly_source = "_th10_00401000:\n" + source
                self.assertEqual(_assemble(assembly_source)[: len(expected)], expected)

    def test_every_inventory_instruction_has_an_explicit_conversion(self):
        inventory = ROOT / "build" / "asm-baseline" / "instruction_rows.json"
        if not inventory.is_file():
            self.skipTest("assembly instruction inventory is unavailable")
        rows = json.loads(inventory.read_text(encoding="utf-8"))
        converted, unsupported = asm_instruction.convert_rows(rows)
        self.assertEqual(len(converted), len(rows))
        self.assertEqual(unsupported, [])
        self.assertTrue(all(".byte" not in row["source"].lower() for row in converted))

    def test_live_ghidra_recovery_rows_have_an_explicit_conversion(self):
        recovery = ROOT / "asm" / "text_code_recovery.json"
        if not recovery.is_file():
            self.skipTest("live Ghidra recovery manifest is unavailable")
        rows = json.loads(recovery.read_text(encoding="utf-8"))["additional_instructions"]
        converted, unsupported = asm_instruction.convert_rows(rows)
        self.assertEqual(len(converted), len(rows))
        self.assertEqual(unsupported, [])
        self.assertTrue(all(".byte" not in row["source"].lower() for row in converted))


if __name__ == "__main__":
    unittest.main()
