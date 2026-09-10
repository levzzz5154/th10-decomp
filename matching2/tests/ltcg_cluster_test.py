"""Fail-closed native LTCG ownership, provenance and byte-container tests."""

import sys
from pathlib import Path

if __package__ in (None, ''):
    sys.path.insert(0, str(Path(__file__).resolve().parents[2]))

import copy
import json
import struct
import tempfile
from types import SimpleNamespace
import unittest
from unittest.mock import patch

from matching2.tools.common.coff_regions import _read_object, _write_name_table
from matching2.tools.common.process import sha
from matching2.tools.matching.ltcg_cluster import (
    BASE_FLAGS, LTCGClusterError, _absolute_object, _prepare_padding_object,
    _snapshot, _verify_includes, _verify_snapshot, build_cluster, export_bodies,
    load_cluster, load_clusters, validate_native_output,
)
from matching2.tools.matching.ltcg_semantic import (
    LTCGSemanticError, PEImage, parse_map, validate_map_pe,
)
from matching2.tests.ltcg_semantic_test import make_pe


LEAF = '?Leaf@@YGXPAX@Z'
CONTEXT = '?CompilerContext@@YGXPAX@Z'
BODY = bytes.fromhex('33 c9 89 48 08 89 48 0c 89 48 10 c3')
TIMESTAMP = 0x6A9EF533


def fixture_map():
    return f''' cluster
 Timestamp is {TIMESTAMP:08x} (fixture)
 Preferred load address is 00400000
 Start         Length     Name                   Class
 0001:00000000 0000000cH .text$10leaf            CODE
 0001:00000010 00000001H .text$20context         CODE
 Address         Publics by Value              Rva+Base     Lib:Object
 0001:00000000       {LEAF} 00401000 f   cluster.obj
 0001:00000010       {CONTEXT} 00401010 f   cluster.obj
 entry point at        0001:00000010
 Static symbols
'''


def fixture_manifest():
    return {
        'schema_version': 1, 'name': 'fixture', 'source': 'src/leaf.cpp',
        'driver': 'layout/context.cpp', 'headers': ['include/leaf.hpp'],
        'image_base': '0x00400000', 'description': 'Declared compiler context fixture.',
        'functions': [{'name': 'Leaf', 'symbol': LEAF, 'section': '.text$10leaf',
                       'address': '0x00401000', 'size': len(BODY), 'actual_abi': 'state in EAX'}],
        'context': {'symbol': CONTEXT, 'section': '.text$20context',
                    'address': '0x00401010', 'size': 1, 'description': 'Synthetic caller.'},
        'gaps': [], 'constants': [], 'absolute_symbols': [],
    }


def fixture_region():
    return {'name': 'Leaf', 'symbol': LEAF, 'source': 'src/leaf.cpp',
            'address': '0x00401000', 'size': len(BODY), 'kind': 'semantic'}


def write_padding_object(path, payload, symbol='_ltcg_gap_0'):
    names, strings = _write_name_table([{'name': symbol}])
    header = struct.pack('<HHIIIHH', 0x14c, 1, 0, 60 + len(payload), 1, 0, 0)
    section = struct.pack('<8sIIIIIIHHI', b'.rdata\0\0', 0, 0, len(payload), 60,
                          0, 0, 0, 0, 0x40400040)
    record = struct.pack('<8sIhHBB', names[0], 0, 1, 0, 2, 0)
    path.write_bytes(header + section + payload + record + strings)


class LTCGClusterTest(unittest.TestCase):
    def setUp(self):
        self.temporary = tempfile.TemporaryDirectory()
        self.addCleanup(self.temporary.cleanup)
        self.directory = Path(self.temporary.name)
        for name in ('src', 'include', 'layout'):
            (self.directory / name).mkdir()
        (self.directory / 'src/leaf.cpp').write_text('void Leaf(void*) {}\n')
        (self.directory / 'layout/context.cpp').write_text('#include "../src/leaf.cpp"\n')
        (self.directory / 'include/leaf.hpp').write_text('void Leaf(void*);\n')
        self.manifest = fixture_manifest()
        self.manifest_path = self.directory / 'layout/cluster.json'
        self.manifest_path.write_text(json.dumps(self.manifest))
        self.spec = load_cluster(self.directory, 'layout/cluster.json', [fixture_region()])
        self.executable = self.directory / 'cluster.exe'
        self.executable.write_bytes(make_pe(BODY + b'\xCC' * 4 + b'\xC3' + b'\xCC' * 15))
        self.map_path = self.directory / 'cluster.map'
        self.map_path.write_text(fixture_map())

    def test_complete_fresh_compiler_bodies_export_unchanged(self):
        functions, native = validate_native_output(self.spec, self.executable, self.map_path, 'cluster.obj')
        self.assertEqual(functions[0]['body'], BODY)
        self.assertEqual(native['pe_sha256'], sha(self.executable.read_bytes()))
        output = self.directory / 'bodies.obj'
        report = export_bodies(output, functions)
        obj = _read_object(output)
        self.assertEqual(len(obj['sections']), 1)
        self.assertEqual(obj['sections'][0]['raw'], BODY)
        self.assertEqual(obj['sections'][0]['relocations'], [])
        self.assertEqual(report['instruction_bytes_changed'], 0)
        self.assertEqual(report['address_operands_changed'], 0)
        self.assertEqual(report['regions'][0]['address'], 0x401000)
        self.assertEqual([s['name'] for s in obj['records']], [LEAF])

    def test_native_function_missing_duplicate_address_origin_and_prefix_fail(self):
        original = fixture_map()
        variants = {
            'missing symbol': original.replace(f' 0001:00000000       {LEAF} 00401000 f   cluster.obj\n', ''),
            'duplicate symbol': original + f' 0001:00000000       {LEAF} 00401000 f   cluster.obj\n',
            'wrong map address': original.replace(f'{LEAF} 00401000', f'{LEAF} 00401001'),
            'wrong source origin': original.replace(f'{LEAF} 00401000 f   cluster.obj', f'{LEAF} 00401000 f   stale.obj'),
            'larger function contribution': original.replace('0000000cH .text$10leaf', '0000000dH .text$10leaf'),
            'interior symbol': original + ' 0001:00000004       ?Interior@@YGXXZ 00401004 f   cluster.obj\n',
            'unlisted helper': original + ' 0001:00000018       ?ExtraHelper@@YGXXZ 00401018 f   cluster.obj\n',
        }
        for label, text in variants.items():
            self.map_path.write_text(text)
            with self.subTest(label=label), self.assertRaises(LTCGSemanticError):
                validate_native_output(self.spec, self.executable, self.map_path, 'cluster.obj')
        self.map_path.write_text(original)
        shortened = copy.deepcopy(self.spec)
        shortened['functions'][0]['size'] -= 1
        with self.assertRaisesRegex(LTCGClusterError, 'entire declared compiler contribution'):
            validate_native_output(shortened, self.executable, self.map_path, 'cluster.obj')

    def test_native_context_and_layout_are_checked_but_cannot_be_selected(self):
        bad = copy.deepcopy(self.manifest)
        bad['context']['symbol'] = LEAF
        self.manifest_path.write_text(json.dumps(bad))
        with self.assertRaisesRegex(LTCGClusterError, 'context must not be selected'):
            load_cluster(self.directory, 'layout/cluster.json', [fixture_region()])
        bad = copy.deepcopy(self.spec)
        bad['context']['address'] += 1
        with self.assertRaisesRegex(LTCGClusterError, 'entry address differs'):
            validate_native_output(bad, self.executable, self.map_path, 'cluster.obj')
        self.map_path.write_text(fixture_map().replace('00000001H .text$20context', '00000002H .text$20context'))
        with self.assertRaisesRegex(LTCGClusterError, 'entire declared compiler contribution'):
            validate_native_output(self.spec, self.executable, self.map_path, 'cluster.obj')

    def test_missing_or_symlinked_native_outputs_fail(self):
        saved = self.executable.read_bytes()
        self.executable.unlink()
        with self.assertRaisesRegex(LTCGClusterError, 'fresh nonempty output'):
            validate_native_output(self.spec, self.executable, self.map_path, 'cluster.obj')
        stale = self.directory / 'old.exe'
        stale.write_bytes(saved)
        self.executable.symlink_to(stale)
        with self.assertRaisesRegex(LTCGClusterError, 'fresh nonempty output'):
            validate_native_output(self.spec, self.executable, self.map_path, 'cluster.obj')

    def test_body_change_is_rejected_before_export(self):
        functions, _ = validate_native_output(self.spec, self.executable, self.map_path, 'cluster.obj')
        functions[0]['body'] = b'\x90' + BODY[1:]
        output = self.directory / 'bodies.obj'
        with self.assertRaisesRegex(LTCGClusterError, 'changed before export'):
            export_bodies(output, functions)
        self.assertFalse(output.exists())

    def test_manifest_cannot_supply_code_or_change_region_ownership(self):
        for key, value in (('expected_hex', BODY.hex()), ('body', BODY.hex()), ('flags', ['/FAcs'])):
            bad = copy.deepcopy(self.manifest)
            bad[key] = value
            self.manifest_path.write_text(json.dumps(bad))
            with self.subTest(key=key), self.assertRaisesRegex(LTCGClusterError, 'unknown fields'):
                load_cluster(self.directory, 'layout/cluster.json', [fixture_region()])
        self.manifest_path.write_text(json.dumps(self.manifest))
        for field, value in [('size', len(BODY) + 1), ('kind', 'asm'), ('source', 'src/another.cpp'),
                             ('symbol', CONTEXT), ('address', '0x00401001')]:
            region = {**fixture_region(), field: value}
            with self.subTest(field=field), self.assertRaises(LTCGClusterError):
                load_cluster(self.directory, 'layout/cluster.json', [region])
        for field, value in [('driver', 'src/leaf.cpp'), ('source', '/tmp/outside.cpp')]:
            bad = copy.deepcopy(self.manifest)
            bad[field] = value
            self.manifest_path.write_text(json.dumps(bad))
            with self.subTest(field=field), self.assertRaises(LTCGClusterError):
                load_cluster(self.directory, 'layout/cluster.json', [fixture_region()])

    def test_cluster_manifest_routes_have_distinct_ownership(self):
        with self.assertRaisesRegex(LTCGClusterError, 'distinct manifest paths'):
            load_clusters(self.directory, {'ltcg_clusters': ['layout/cluster.json'] * 2}, [fixture_region()])
        self.assertEqual(load_clusters(self.directory, {}, [fixture_region()]), [])

    def test_changed_inputs_and_undeclared_includes_fail(self):
        snapshot = _snapshot(self.spec)
        (self.directory / 'src/leaf.cpp').write_text('void Leaf(void*) { ++*(int*)0; }\n')
        with self.assertRaisesRegex(LTCGClusterError, 'input changed'):
            _verify_snapshot(snapshot)
        toolkit = self.directory / 'toolkit'
        toolkit.mkdir()
        def windows(path):
            return 'Z:' + str(path).replace('/', '\\')
        include_log = '\n'.join('Note: including file: ' + windows(path)
                                for path in [self.spec['source_path'], *self.spec['header_paths']])
        with patch('matching2.tools.matching.ltcg_cluster.winpath', side_effect=windows):
            verified = _verify_includes(include_log, self.spec, toolkit)
            self.assertEqual(len(verified), 2)
            with self.assertRaisesRegex(LTCGClusterError, 'every declared'):
                _verify_includes('', self.spec, toolkit)
            extra = self.directory / 'include/undeclared.hpp'
            extra.write_text('extern int extra;\n')
            with self.assertRaisesRegex(LTCGClusterError, 'undeclared source/header'):
                _verify_includes(include_log + '\nNote: including file: ' + windows(extra), self.spec, toolkit)

    def test_stale_success_artifacts_cannot_replace_missing_compiler_output(self):
        output = self.directory / 'out'
        output.mkdir()
        (output / 'bodies.obj').write_bytes(b'old body object')
        (output / 'report.json').write_text('old success report')
        stale = output / 'native-old'
        stale.mkdir()
        (stale / 'cluster.obj').write_bytes(b'old compiler object')
        fake_tools = (self.directory / 'cl.exe', self.directory / 'link.exe', {})
        with patch('matching2.tools.matching.ltcg_cluster.compiler_environment', return_value={}), \
                patch('matching2.tools.matching.ltcg_cluster._verify_toolchain', return_value=fake_tools), \
                patch('matching2.tools.matching.ltcg_cluster.winpath', side_effect=str), \
                patch('matching2.tools.matching.ltcg_cluster._run_logged', return_value=SimpleNamespace(stdout='', stderr='')):
            with self.assertRaisesRegex(LTCGClusterError, 'fresh nonempty output'):
                build_cluster(self.spec, self.directory, output, BASE_FLAGS)
        self.assertFalse((output / 'bodies.obj').exists())
        self.assertFalse((output / 'report.json').exists())
        self.assertEqual((stale / 'cluster.obj').read_bytes(), b'old compiler object')

    def test_padding_metadata_rewrite_preserves_only_zero_filled_arrays(self):
        source, destination = self.directory / 'padding.obj', self.directory / 'layout.obj'
        gap = {'section': '.rdata', 'symbol': '_ltcg_gap_0', 'size': 16}
        write_padding_object(source, b'\0' * 16)
        result = _prepare_padding_object(source, destination, [gap])
        self.assertEqual(result['payload_bytes_changed'], 0)
        self.assertEqual(_read_object(destination)['sections'][0]['raw'], b'\0' * 16)
        self.assertEqual(result['recovered_code_bytes'], 0)
        for payload, symbol in [(b'\0' * 15 + b'\xC3', '_ltcg_gap_0'), (b'\0' * 16, '_unknown'),
                                (b'\0' * 15, '_ltcg_gap_0')]:
            write_padding_object(source, payload, symbol)
            with self.subTest(payload=payload, symbol=symbol), self.assertRaises(LTCGClusterError):
                _prepare_padding_object(source, destination, [gap])

    def test_absolute_bindings_have_no_implementation_sections(self):
        output = self.directory / 'bindings.obj'
        _absolute_object(output, [{'symbol': '__ftol2', 'coff_value': 0x63b2c, 'kind': 'relative_code'},
                                  {'symbol': '?Lower@@3MA', 'coff_value': 0x470b68, 'kind': 'data'}])
        obj = _read_object(output)
        self.assertEqual(obj['sections'], [])
        self.assertEqual([item['value'] for item in obj['records']], [0x63b2c, 0x470b68])
        self.assertTrue(all(item['section_number'] == -1 for item in obj['records']))

    def test_zero_length_data_marker_is_validated_without_inventing_a_section(self):
        text = fixture_map().replace(' Address         Publics',
                                     ' 0001:00000020 00000000H .edata DATA\n Address         Publics')
        parsed = parse_map(text)
        validate_map_pe(parsed, PEImage(self.executable.read_bytes()))
        self.assertEqual(parsed.contributions[-1].length, 0)
        with self.assertRaisesRegex(LTCGSemanticError, 'invalid MAP contribution'):
            parse_map(text.replace('00000000H .edata DATA', '00000000H .edata CODE'))
        with self.assertRaisesRegex(LTCGSemanticError, 'exceeds PE section'):
            validate_map_pe(parse_map(text.replace('0001:00000020 00000000H', '0001:00000021 00000000H')),
                            PEImage(self.executable.read_bytes()))


if __name__ == '__main__':
    unittest.main()
