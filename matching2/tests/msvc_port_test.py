"""Complete-project partition, compiler-output, and failure gates."""

import sys
from pathlib import Path

if __package__ in (None, ""):
    sys.path.insert(0, str(Path(__file__).resolve().parents[2]))

import copy
import json
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[2]
from matching2.tools.matching.build_msvc import validate_project, verify_linked


class MSVCPortTest(unittest.TestCase):
    def setUp(self):
        self.config = json.loads((ROOT / 'matching2/msvc/regions.json').read_text())
        self.reference = json.loads((ROOT / 'decompiled/reference_bytes_validation.json').read_text())

    def test_complete_partition_and_restored_semantic_functions(self):
        regions, units = validate_project(self.config, self.reference)
        self.assertEqual(sum(r['size'] for r in regions), 412672)
        # Recovery may grow without changing this test. Preserve at least the
        # current ordinary-C++ baseline; exact instruction bytes are gated by
        # the full build, independently of these manifest classifications.
        semantic = [r for r in regions if r['kind'] == 'semantic']
        self.assertGreaterEqual(len(semantic), 47)
        self.assertGreaterEqual(sum(r['size'] for r in semantic), 1725)
        self.assertTrue(all((ROOT / 'matching2/msvc' / source).exists() for source in units))

    def test_resource_lifetime_symbols_and_relocation_evidence(self):
        regions = {int(r['address'], 0): r for r in self.config['regions']}
        for address, symbol, size, count in (
            (0x436400, '?Open@BufferFile@@UAEEPBD0@Z', 46, 2),
            (0x436680, '??1ResourceFile@@UAE@XZ', 49, 3),
            (0x4366c0, '?Open@ResourceFile@@UAEEPBD0@Z', 168, 7),
        ):
            region = regions[address]
            self.assertEqual(region['kind'], 'semantic')
            self.assertEqual(region['symbol'], symbol)
            self.assertEqual(region['size'], size)
            expected_source = ('src/platform/buffer_file_open.cpp' if address == 0x436400
                               else 'src/platform/resource_lifetime.cpp')
            self.assertEqual(region['source'], expected_source)
            self.assertEqual(len(region['relocations']), count)
            for relocation in region['relocations']:
                operand = int.from_bytes(bytes.fromhex(relocation['original_operand']), 'little')
                if relocation['type'] == 'IMAGE_REL_I386_REL32':
                    operand = (operand + address + relocation['offset'] + 4) & 0xffffffff
                self.assertEqual(operand, int(relocation['original_target'], 0))
                self.assertEqual(operand, int(self.config['symbols'][relocation['symbol']], 0))

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
            result = subprocess.run([sys.executable, str(ROOT / 'matching2/tools/matching/build_msvc.py'),
                                     '--project', str(directory), '--output', str(output)],
                                    capture_output=True, text=True, timeout=30)
            self.assertNotEqual(result.returncode, 0)
            self.assertIn('partition', result.stderr)
            self.assertFalse((output / 'th10.exe').exists())
            self.assertFalse((output / 'port-report.json').exists())

    def test_linked_code_and_relocation_bytes_are_checked(self):
        linked = ROOT / 'matching2/build/msvc/linked.exe'
        if not linked.exists():
            self.skipTest('run make build first')
        verify_linked(linked, self.config)
        from matching2.tools.common.pe import PEImage
        original = linked.read_bytes()
        section = PEImage(original).sections[0]
        with tempfile.TemporaryDirectory() as temporary:
            path = Path(temporary) / 'changed.exe'
            # Instructions, destructor CALL operands, and a resource IAT operand.
            for address in (0x401000, 0x401fff, 0x436695, 0x4366d6):
                data = bytearray(original)
                data[section['raw_offset'] + address - section['address']] ^= 1
                path.write_bytes(data)
                with self.subTest(address=hex(address)), self.assertRaisesRegex(ValueError, 'SHA-256 differs'):
                    verify_linked(path, self.config)


if __name__ == '__main__':
    unittest.main()
