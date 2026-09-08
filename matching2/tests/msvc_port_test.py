"""Complete-project partition, compiler-output, and failure gates."""
import copy
import json
from pathlib import Path
import subprocess
import sys
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / 'matching2/tools'))
from build_msvc import validate_project, verify_linked


class MSVCPortTest(unittest.TestCase):
    def setUp(self):
        self.config = json.loads((ROOT / 'matching2/msvc/regions.json').read_text())
        self.reference = json.loads((ROOT / 'decompiled/reference_bytes_validation.json').read_text())

    def test_complete_partition_and_restored_semantic_functions(self):
        regions, units = validate_project(self.config, self.reference)
        self.assertEqual(sum(r['size'] for r in regions), 412672)
        self.assertEqual(sum(r['kind'] == 'semantic' for r in regions), 34)
        self.assertTrue(all((ROOT / 'matching2/msvc' / source).exists() for source in units))

    def test_bad_extent_missing_region_and_reference_rejected(self):
        for change in ('extent', 'missing', 'hash'):
            config = copy.deepcopy(self.config)
            if change == 'extent': config['regions'][0]['size'] += 1
            elif change == 'missing': config['regions'].pop(0)
            else: config['text_sha256'] = '0' * 64
            with self.subTest(change=change), self.assertRaises(ValueError):
                validate_project(config, self.reference)

    def test_invalid_project_removes_stale_success_outputs(self):
        with tempfile.TemporaryDirectory() as temporary:
            directory = Path(temporary)
            self.config['regions'][0]['size'] += 1
            (directory / 'regions.json').write_text(json.dumps(self.config))
            output = directory / 'out'; output.mkdir()
            for name in ('th10.exe', 'port-report.json'):
                (output / name).write_text('stale')
            result = subprocess.run([sys.executable, str(ROOT / 'matching2/tools/build_msvc.py'),
                                     '--project', str(directory), '--output', str(output)],
                                    capture_output=True, text=True, timeout=30)
            self.assertNotEqual(result.returncode, 0)
            self.assertIn('partition', result.stderr)
            self.assertFalse((output / 'th10.exe').exists())
            self.assertFalse((output / 'port-report.json').exists())

    def test_linked_code_and_relocation_bytes_are_checked(self):
        linked = ROOT / 'matching2/build/msvc-final/linked.exe'
        if not linked.exists():
            self.skipTest('run build_msvc.sh --output matching2/build/msvc-final first')
        verify_linked(linked, self.config)
        from build_asm_proof import PEImage
        original = linked.read_bytes()
        section = PEImage(original).sections[0]
        with tempfile.TemporaryDirectory() as temporary:
            path = Path(temporary) / 'changed.exe'
            # A normal instruction and the semantic destructor CALL operand.
            for address in (0x401000, 0x401fff):
                data = bytearray(original)
                data[section['raw_offset'] + address - section['address']] ^= 1
                path.write_bytes(data)
                with self.subTest(address=hex(address)), self.assertRaisesRegex(ValueError, 'SHA-256 differs'):
                    verify_linked(path, self.config)


if __name__ == '__main__':
    unittest.main()
