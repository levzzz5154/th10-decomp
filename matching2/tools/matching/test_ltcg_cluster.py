"""Focused manifest tests for native-LTCG cluster ownership."""

import json
from pathlib import Path
import struct
import tempfile
import unittest
from matching2.tools.common.coff_regions import _read_object, CoffRegionError

from matching2.tools.matching.ltcg_cluster import (
    LTCGClusterError, _validate_generated_contributions, _verify_duplicates,
    load_cluster, validate_internal_calls, validate_native_output,
    _prepare_ordinary_object, _verify_ordinary_object, _snapshot, _verify_snapshot,
)
from matching2.tools.matching.ltcg_semantic import (
    LTCGSemanticError, LinkMap, MapContribution, PEImage, parse_map, validate_map_pe,
)


import sys as _project_sys
from pathlib import Path as _ProjectPath
_project_sys.path.insert(0, str(_ProjectPath(__file__).resolve().parents[3]))
from matching2.tools.common.project_paths import project_support
class ClusterSourceOwnershipTests(unittest.TestCase):
    def _write_manifest(self, project, *, multi_source):
        (project / "src").mkdir()
        (project_support(project, 'layout') / "ltcg").mkdir(parents=True)
        (project / "src" / "primary.cpp").write_text("// primary\n")
        (project / "src" / "secondary.cpp").write_text("// secondary\n")
        (project_support(project, 'layout') / "ltcg" / "context.cpp").write_text("// context\n")
        functions = [{
            "name": "Primary",
            "symbol": "?Primary@@YAHXZ",
            "section": ".text$01primary",
            "address": "0x00401000",
            "size": 1,
            "actual_abi": "plain RET",
        }]
        regions = [{
            "name": "semantic_primary",
            "source": "src/primary.cpp",
            "symbol": "?Primary@@YAHXZ",
            "address": "0x00401000",
            "size": 1,
            "kind": "semantic",
            "owner": "0x00401000",
        }]
        if multi_source:
            functions.append({
                "name": "Secondary",
                "symbol": "?Secondary@@YAHXZ",
                "section": ".text$05secondary",
                "address": "0x00401010",
                "size": 1,
                "actual_abi": "plain RET",
                "source": "src/secondary.cpp",
            })
            functions[0]["source"] = "src/primary.cpp"
            regions.append({
                "name": "semantic_secondary",
                "source": "src/secondary.cpp",
                "symbol": "?Secondary@@YAHXZ",
                "address": "0x00401010",
                "size": 1,
                "kind": "semantic",
                "owner": "0x00401010",
            })
        manifest = {
            "schema_version": 1,
            "name": "source_ownership_test",
            "source": "src/primary.cpp",
            "driver": "layout/ltcg/context.cpp",
            "headers": [],
            "image_base": "0x00400000",
            "description": "test cluster",
            "functions": functions,
            "context": {
                "symbol": "?Context@@YAHXZ",
                "section": ".text$03context",
                "address": "0x00401020",
                "size": 1,
                "description": "test context",
            },
            "gaps": [
                {"section": ".text$00layout", "address": "0x00400000", "size": 4096},
                {"section": ".text$02layout", "address": "0x00401001", "size": 15},
                {"section": ".text$04layout", "address": "0x00401011", "size": 15},
            ],
            "constants": [],
            "absolute_symbols": [],
        }
        if multi_source:
            manifest["additional_sources"] = ["src/secondary.cpp"]
        (project_support(project, 'layout') / "ltcg" / "source_ownership_test.json").write_text(
            json.dumps(manifest)
        )
        return regions

    def test_multi_source_functions_are_owned_by_declared_sources(self):
        with tempfile.TemporaryDirectory() as directory:
            project = Path(directory)
            regions = self._write_manifest(project, multi_source=True)
            loaded = load_cluster(project, "layout/ltcg/source_ownership_test.json", regions)

        self.assertEqual(
            loaded["source_names"], ["src/primary.cpp", "src/secondary.cpp"]
        )
        self.assertEqual(
            [function["_source"] for function in loaded["functions"]],
            ["src/primary.cpp", "src/secondary.cpp"],
        )
        self.assertEqual(
            {region["source"] for region in loaded["regions"]},
            {"src/primary.cpp", "src/secondary.cpp"},
        )

    def test_legacy_manifest_defaults_function_source_to_primary(self):
        with tempfile.TemporaryDirectory() as directory:
            project = Path(directory)
            regions = self._write_manifest(project, multi_source=False)
            loaded = load_cluster(project, "layout/ltcg/source_ownership_test.json", regions)

        self.assertEqual(loaded["source_names"], ["src/primary.cpp"])
        self.assertEqual(loaded["functions"][0]["_source"], "src/primary.cpp")

    def test_schema_one_roots_are_selected_and_distinct(self):
        with tempfile.TemporaryDirectory() as directory:
            project = Path(directory)
            regions = self._write_manifest(project, multi_source=False)
            path = project_support(project, 'layout') / "ltcg" / "source_ownership_test.json"
            manifest = json.loads(path.read_text())
            manifest["roots"] = [manifest["functions"][0]["symbol"]]
            path.write_text(json.dumps(manifest))
            loaded = load_cluster(project, "layout/ltcg/source_ownership_test.json", regions)
            self.assertEqual(loaded["roots"], ["?Primary@@YAHXZ"])

            with self.assertRaisesRegex(LTCGClusterError, "selected real function"):
                manifest["roots"] = ["_external"]
                path.write_text(json.dumps(manifest))
                load_cluster(project, "layout/ltcg/source_ownership_test.json", regions)

            with self.assertRaisesRegex(LTCGClusterError, "distinct"):
                manifest["roots"] = ["?Primary@@YAHXZ"] * 2
                path.write_text(json.dumps(manifest))
                load_cluster(project, "layout/ltcg/source_ownership_test.json", regions)

    def _alias_manifest(self, project, aliases):
        path = project_support(project, 'layout') / "ltcg" / "source_ownership_test.json"
        manifest = json.loads(path.read_text())
        manifest["constant_aliases"] = aliases
        path.write_text(json.dumps(manifest))
        return path

    def test_constant_alias_value_must_match_its_name(self):
        with tempfile.TemporaryDirectory() as directory:
            project = Path(directory)
            regions = self._write_manifest(project, multi_source=False)
            self._alias_manifest(
                project, [{"symbol": "__real@4f800000", "address": "0x00401030", "value": 1.0}]
            )
            with self.assertRaisesRegex(LTCGClusterError, "match its compiler literal name"):
                load_cluster(project, "layout/ltcg/source_ownership_test.json", regions)

    def test_constant_alias_must_name_a_compiler_literal(self):
        with tempfile.TemporaryDirectory() as directory:
            project = Path(directory)
            regions = self._write_manifest(project, multi_source=False)
            self._alias_manifest(
                project,
                [{"symbol": "_data_00470b98", "address": "0x00401030", "value": 4294967296}],
            )
            with self.assertRaisesRegex(LTCGClusterError, "compiler float literal"):
                load_cluster(project, "layout/ltcg/source_ownership_test.json", regions)

    def test_constant_alias_is_loaded_and_cannot_overlap_selected_code(self):
        with tempfile.TemporaryDirectory() as directory:
            project = Path(directory)
            regions = self._write_manifest(project, multi_source=False)
            self._alias_manifest(
                project,
                [{"symbol": "__real@4f800000", "address": "0x00401030", "value": 4294967296}],
            )
            loaded = load_cluster(project, "layout/ltcg/source_ownership_test.json", regions)
            self.assertEqual(loaded["constant_aliases"][0]["symbol"], "__real@4f800000")
            self.assertEqual(loaded["constant_aliases"][0]["size"], 4)

            self._alias_manifest(
                project,
                [{"symbol": "__real@4f800000", "address": "0x00401000", "value": 4294967296}],
            )
            with self.assertRaisesRegex(LTCGClusterError, "extents overlap"):
                load_cluster(project, "layout/ltcg/source_ownership_test.json", regions)

    def test_constant_aliases_cannot_repeat_a_declared_symbol(self):
        with tempfile.TemporaryDirectory() as directory:
            project = Path(directory)
            regions = self._write_manifest(project, multi_source=False)
            self._alias_manifest(
                project,
                [
                    {"symbol": "__real@4f800000", "address": "0x00401030", "value": 4294967296},
                    {"symbol": "__real@4f800000", "address": "0x00401034", "value": 4294967296},
                ],
            )
            with self.assertRaisesRegex(LTCGClusterError, "duplicate symbol"):
                load_cluster(project, "layout/ltcg/source_ownership_test.json", regions)

    def test_data_alias_validates_hex_and_extent(self):
        with tempfile.TemporaryDirectory() as directory:
            project = Path(directory)
            regions = self._write_manifest(project, multi_source=False)
            path = project_support(project, 'layout') / "ltcg" / "source_ownership_test.json"
            manifest = json.loads(path.read_text())
            manifest["data_aliases"] = [{"symbol": "?literal@@3QBDB", "address": "0x00401030", "bytes": "646562756700"}]
            path.write_text(json.dumps(manifest))
            loaded = load_cluster(project, "layout/ltcg/source_ownership_test.json", regions)
            self.assertEqual(loaded["data_aliases"][0]["bytes_value"], b"debug\0")
            manifest["data_aliases"][0]["bytes"] = "xyz"
            path.write_text(json.dumps(manifest))
            with self.assertRaisesRegex(LTCGClusterError, "hexadecimal octets"):
                load_cluster(project, "layout/ltcg/source_ownership_test.json", regions)

    def _whole_program(self, project, change=None):
        regions = self._write_manifest(project, multi_source=True)
        path = project_support(project, 'layout/ltcg/source_ownership_test.json')
        manifest = json.loads(path.read_text())
        manifest['schema_version'] = 2
        del manifest['driver'], manifest['context']
        manifest['entry'] = manifest['functions'][0]['symbol']
        manifest['functions'][0]['size'] = regions[0]['size'] = 5
        manifest['gaps'][1].update(address='0x00401005', size=11)
        manifest['calls'] = [{
            'caller': manifest['functions'][0]['symbol'],
            'callee': manifest['functions'][1]['symbol'],
            'address': '0x00401000', 'instruction': 'call',
        }]
        if change:
            change(manifest)
        path.write_text(json.dumps(manifest))
        return load_cluster(project, 'layout/ltcg/source_ownership_test.json', regions)

    def test_real_entry_replaces_synthetic_driver(self):
        with tempfile.TemporaryDirectory() as directory:
            loaded = self._whole_program(Path(directory))
        self.assertIsNone(loaded['driver_path'])
        self.assertIsNone(loaded['context'])
        self.assertEqual(loaded['entry_address'], 0x401000)
        self.assertEqual(len(loaded['source_paths']), 2)
        self.assertEqual(len(loaded['regions']), 2)

    def test_private_call_cannot_bind_an_external_callee(self):
        with tempfile.TemporaryDirectory() as directory:
            with self.assertRaisesRegex(LTCGClusterError, 'same link'):
                self._whole_program(Path(directory), lambda m: m['calls'][0].update(callee='_external'))

    def test_whole_program_entry_must_be_selected(self):
        with tempfile.TemporaryDirectory() as directory:
            with self.assertRaisesRegex(LTCGClusterError, 'selected real function'):
                self._whole_program(Path(directory), lambda m: m.update(entry='_synthetic'))

    def test_whole_program_roots_are_selected_and_distinct(self):
        with tempfile.TemporaryDirectory() as directory:
            loaded = self._whole_program(
                Path(directory),
                lambda m: m.update(roots=[m['functions'][1]['symbol']]),
            )
        self.assertEqual(loaded['roots'], ['?Secondary@@YAHXZ'])

        with tempfile.TemporaryDirectory() as directory:
            with self.assertRaisesRegex(LTCGClusterError, 'selected real function'):
                self._whole_program(Path(directory), lambda m: m.update(roots=['_external']))

        with tempfile.TemporaryDirectory() as directory:
            with self.assertRaisesRegex(LTCGClusterError, 'distinct'):
                self._whole_program(
                    Path(directory),
                    lambda m: m.update(roots=[m['functions'][1]['symbol']] * 2),
                )

    def test_callee_cannot_be_omitted_from_recovery(self):
        with tempfile.TemporaryDirectory() as directory:
            with self.assertRaisesRegex(LTCGClusterError, 'maintained source ownership'):
                self._whole_program(Path(directory), lambda m: m['functions'].pop())

    def test_call_site_must_fit_inside_caller(self):
        with tempfile.TemporaryDirectory() as directory:
            with self.assertRaisesRegex(LTCGClusterError, 'outside its caller'):
                self._whole_program(Path(directory), lambda m: m['calls'][0].update(address='0x00401001'))


    def _owned_include_manifest(self, project):
        regions = self._write_manifest(project, multi_source=True)
        path = project_support(project, 'layout/ltcg/source_ownership_test.json')
        manifest = json.loads(path.read_text())
        manifest["additional_sources"] = []
        manifest["included_sources"] = ["src/secondary.cpp"]
        manifest["owned_includes"] = {"src/secondary.cpp": "src/primary.cpp"}
        return regions, path, manifest

    def test_owned_include_retains_source_attribution_without_an_extra_unit(self):
        with tempfile.TemporaryDirectory() as directory:
            project = Path(directory)
            regions, path, manifest = self._owned_include_manifest(project)
            path.write_text(json.dumps(manifest))
            loaded = load_cluster(project, str(path.relative_to(project)), regions)
        self.assertEqual(loaded["source_names"], ["src/primary.cpp"])
        self.assertEqual(loaded["ownership_names"], ["src/primary.cpp", "src/secondary.cpp"])
        self.assertEqual(loaded["functions"][1]["_source"], "src/secondary.cpp")

    def test_owned_include_must_be_a_declared_dependency(self):
        with tempfile.TemporaryDirectory() as directory:
            project = Path(directory)
            regions, path, manifest = self._owned_include_manifest(project)
            manifest["included_sources"] = []
            path.write_text(json.dumps(manifest))
            with self.assertRaisesRegex(LTCGClusterError, "declared include"):
                load_cluster(project, str(path.relative_to(project)), regions)

    def test_owned_include_cannot_claim_an_unknown_compiler_unit(self):
        with tempfile.TemporaryDirectory() as directory:
            project = Path(directory)
            regions, path, manifest = self._owned_include_manifest(project)
            manifest["owned_includes"]["src/secondary.cpp"] = "src/missing.cpp"
            path.write_text(json.dumps(manifest))
            with self.assertRaisesRegex(LTCGClusterError, "compiled source owner"):
                load_cluster(project, str(path.relative_to(project)), regions)

    def test_compiler_wrapper_is_separate_and_included_in_the_snapshot(self):
        with tempfile.TemporaryDirectory() as directory:
            project = Path(directory)
            regions, path, manifest = self._owned_include_manifest(project)
            wrapper = project_support(project, 'layout/ltcg/unit.cpp')
            wrapper.write_text('#include "../../src/primary.cpp"\n')
            manifest["compilation_units"] = {"src/primary.cpp": "layout/ltcg/unit.cpp"}
            path.write_text(json.dumps(manifest))
            loaded = load_cluster(project, str(path.relative_to(project)), regions)
            self.assertEqual(loaded["compilation_paths"], [wrapper.resolve()])
            snapshot = _snapshot(loaded)
            self.assertIn(str(wrapper.resolve()), snapshot)
            wrapper.write_text("// changed compiler wrapper\n")
            with self.assertRaisesRegex(LTCGClusterError, "input changed"):
                _verify_snapshot(snapshot)

    def test_compiler_wrapper_cannot_reassign_an_unknown_source(self):
        with tempfile.TemporaryDirectory() as directory:
            project = Path(directory)
            regions, path, manifest = self._owned_include_manifest(project)
            manifest["compilation_units"] = {"src/missing.cpp": "layout/ltcg/context.cpp"}
            path.write_text(json.dumps(manifest))
            with self.assertRaisesRegex(LTCGClusterError, "map maintained sources"):
                load_cluster(project, str(path.relative_to(project)), regions)


class ConstantAliasLinkTests(unittest.TestCase):
    """A rebind of a pooled compiler literal must stay the declared one."""

    ALIAS = {"symbol": "__real@4f800000", "address": 0x470B98}
    TOLERATED = ("CIL library( CIL module) : warning LNK4006: __real@4f800000 "
                 "already defined in a previous module; second definition ignored")

    def test_declared_alias_duplicate_is_recorded_as_evidence(self):
        recorded = _verify_duplicates(self.TOLERATED, [self.ALIAS])
        self.assertEqual(recorded[0]["symbol"], "__real@4f800000")
        self.assertEqual(recorded[0]["address"], "0x00470B98")

    def test_undeclared_duplicate_definition_is_rejected(self):
        log = "CIL library( CIL module) : warning LNK4006: _data_00470b98 already defined in a previous module"
        with self.assertRaisesRegex(LTCGClusterError, "undeclared duplicate definition: _data_00470b98"):
            _verify_duplicates(log + "\n" + self.TOLERATED, [self.ALIAS])

    def test_alias_without_a_pooled_definition_is_rejected(self):
        with self.assertRaisesRegex(LTCGClusterError, "no pooled definition to rebind"):
            _verify_duplicates("Generating code\n", [self.ALIAS])

    def test_alias_free_cluster_tolerates_no_duplicate(self):
        with self.assertRaisesRegex(LTCGClusterError, "undeclared duplicate definition"):
            _verify_duplicates(self.TOLERATED, [])


class InternalCallTests(unittest.TestCase):
    def test_unmodified_rel32_reaches_the_selected_callee(self):
        caller = {'symbol': 'caller', 'address': '0x00401000', 'body': b'\xe8\x0b\0\0\0'}
        callee = {'symbol': 'callee', 'address': '0x00401010', 'body': b'\xc3'}
        call = {'caller': 'caller', 'callee': 'callee', 'address': 0x401000, 'instruction': 'call'}
        self.assertTrue(validate_internal_calls([call], [caller, callee])[0]['verified'])
        for bad_body in (b'\xe8\x0c\0\0\0', b'\xe9\x0b\0\0\0', b'\xe8\x0b\0\0'):
            with self.subTest(body=bad_body), self.assertRaises(LTCGClusterError):
                validate_internal_calls([call], [{**caller, 'body': bad_body}, callee])


class NativeExportMapTests(unittest.TestCase):
    # Minimal PE/MAP reproducing LINK 7.10's observed .edata -> .rdata merge.
    def _image(self, export_rva=0x2000, export_size=0x40):
        data = bytearray(0x600)
        data[:2] = b'MZ'
        struct.pack_into('<I', data, 0x3c, 0x80)
        data[0x80:0x84] = b'PE\0\0'
        struct.pack_into('<HHIIIHH', data, 0x84, 0x14c, 2, 0, 0, 0, 0xe0, 0x102)
        optional = 0x98
        struct.pack_into('<HBB', data, optional, 0x10b, 7, 10)
        struct.pack_into('<I', data, optional + 16, 0x1000)
        struct.pack_into('<III', data, optional + 28, 0x400000, 0x1000, 0x200)
        struct.pack_into('<III', data, optional + 92, 16, export_rva, export_size)
        for index, (name, size, rva, raw, flags) in enumerate([
                (b'.text', 0x10, 0x1000, 0x200, 0x60000020),
                (b'.rdata', 0x40, 0x2000, 0x400, 0x40000040)]):
            struct.pack_into('<8sIIIIIIHHI', data, optional + 0xe0 + 40 * index,
                             name, size, rva, 0x200, raw, 0, 0, 0, 0, flags)
        return PEImage(bytes(data))

    def test_exports_are_mapped_from_the_pe_data_directory(self):
        link_map = parse_map(''' cluster
 Timestamp is 00000000
 Preferred load address is 00400000
 Start         Length     Name                   Class
 0001:00000000 00000010H .text$10caller CODE
 0002:00000000 00000040H .edata DATA
 Address         Publics by Value              Rva+Base     Lib:Object
 0001:00000000 _entry 00401000 f caller.obj
 entry point at 0001:00000000
 Static symbols
''')
        validate_map_pe(link_map, self._image())
        for rva, size in ((0, 0), (0x2001, 0x3f), (0x2000, 0x3f)):
            with self.subTest(rva=rva, size=size), self.assertRaises(LTCGSemanticError):
                validate_map_pe(link_map, self._image(rva, size))


class GeneratedUnwindContributionTests(unittest.TestCase):
    def _check(self, offsets=(0, 11), sizes=(11, 10), length=21):
        functions = [{'symbol': name, 'section': '.text$x', 'generated': True}
                     for name in ('_unwind', '_handler')]
        reports = [{'symbol': name, 'map_segment': '0001', 'map_offset': hex(offset), 'size': size}
                   for name, offset, size in zip(('_unwind', '_handler'), offsets, sizes)]
        link_map = LinkMap(0x400000, None, 1, 0,
                           (MapContribution(1, 0, length, '.text$x', 'CODE'),), ())
        _validate_generated_contributions(functions, reports, link_map)

    def test_complete_unwind_and_handler_contribution_is_accepted(self):
        self._check()

    def test_missing_prefix_middle_or_suffix_is_rejected(self):
        for offsets, sizes, length in [((1, 11), (10, 10), 21),
                                       ((0, 12), (11, 9), 21),
                                       ((0, 11), (11, 9), 21),
                                       ((0, 11), (11, 10), 22)]:
            with self.subTest(offsets=offsets, sizes=sizes, length=length):
                with self.assertRaises(LTCGClusterError):
                    self._check(offsets, sizes, length)

    def test_overlapping_functions_are_rejected(self):
        with self.assertRaises(LTCGClusterError):
            self._check((0, 10))


class NativeExceptionMapTests(unittest.TestCase):
    def _map(self, table_class='DATA', include_rdata=True):
        data_prefix = ' 0002:00000000 00000020H .rdata$00config DATA\n' if include_rdata else ''
        return parse_map(''' cluster
 Timestamp is 00000000
 Preferred load address is 00400000
 Start         Length     Name                   Class
 0001:00000000 00000010H .text$10caller CODE
''' + data_prefix + f''' 0002:00000020 00000020H .xdata$x {table_class}
 Address         Publics by Value              Rva+Base     Lib:Object
 0001:00000000 _entry 00401000 f caller.obj
 entry point at 0001:00000000
 Static symbols
''')

    def test_exception_tables_share_the_readonly_rdata_segment(self):
        validate_map_pe(self._map(), NativeExportMapTests()._image(0, 0))

    def test_exception_tables_cannot_be_code_or_guess_a_segment(self):
        for table_class, include_rdata in [('CODE', True), ('DATA', False)]:
            with self.subTest(table_class=table_class, include_rdata=include_rdata):
                with self.assertRaises(LTCGSemanticError):
                    validate_map_pe(self._map(table_class, include_rdata),
                                    NativeExportMapTests()._image(0, 0))

    def test_exception_tables_cannot_use_writable_data(self):
        image = bytearray(NativeExportMapTests()._image(0, 0).data)
        struct.pack_into('<I', image, 0x98 + 0xe0 + 40 + 36, 0xc0000040)
        with self.assertRaises(LTCGSemanticError):
            validate_map_pe(self._map(), PEImage(bytes(image)))


class DataAliasReferenceScopeManifestTests(unittest.TestCase):
    _write_manifest = ClusterSourceOwnershipTests._write_manifest
    _alias_manifest = ClusterSourceOwnershipTests._alias_manifest

    def _load_alias(self, project, alias):
        regions = self._write_manifest(project, multi_source=False)
        path = project_support(project, 'layout/ltcg/source_ownership_test.json')
        manifest = json.loads(path.read_text())
        manifest['data_aliases'] = [alias]
        path.write_text(json.dumps(manifest))
        return load_cluster(project, 'layout/ltcg/source_ownership_test.json', regions)

    def test_data_alias_reference_scope_defaults_to_selected(self):
        with tempfile.TemporaryDirectory() as directory:
            loaded = self._load_alias(Path(directory), {
                'symbol': '?vtable@@', 'address': '0x00401030', 'bytes': '00'})
            self.assertEqual(loaded['data_aliases'][0]['reference_scope'], 'selected')

    def test_data_alias_accepts_only_explicit_supported_scope_names(self):
        for scope in ('selected', 'compiled_graph', None, True, 0, [], {}, '', 'anchors', 'all'):
            with self.subTest(scope=scope), tempfile.TemporaryDirectory() as directory:
                alias = {'symbol': '?vtable@@', 'address': '0x00401030', 'bytes': '00',
                         'reference_scope': scope}
                if scope in ('selected', 'compiled_graph'):
                    loaded = self._load_alias(Path(directory), alias)
                    self.assertEqual(loaded['data_aliases'][0]['reference_scope'], scope)
                else:
                    with self.assertRaisesRegex(LTCGClusterError, 'reference_scope'):
                        self._load_alias(Path(directory), alias)

    def test_data_literal_alias_cannot_bypass_selected_scope(self):
        for symbol in ('__real@3f800000', '__real@3ff0000000000000'):
            with self.subTest(symbol=symbol), tempfile.TemporaryDirectory() as directory:
                with self.assertRaisesRegex(LTCGClusterError, 'literal.*selected'):
                    self._load_alias(Path(directory), {
                        'symbol': symbol, 'address': '0x00401030', 'bytes': '0000803f',
                        'reference_scope': 'compiled_graph'})

    def test_constant_alias_does_not_accept_reference_scope(self):
        with tempfile.TemporaryDirectory() as directory:
            project = Path(directory)
            regions = self._write_manifest(project, multi_source=False)
            self._alias_manifest(project, [{'symbol': '__real@3f800000',
                'address': '0x00401030', 'value': 1.0, 'reference_scope': 'compiled_graph'}])
            with self.assertRaisesRegex(LTCGClusterError, 'unknown fields'):
                load_cluster(project, 'layout/ltcg/source_ownership_test.json', regions)

    def test_graph_scope_preserves_extent_and_symbol_constraints(self):
        for mutation in ('overlap', 'overflow', 'duplicate'):
            with self.subTest(mutation=mutation), tempfile.TemporaryDirectory() as directory:
                project = Path(directory)
                regions = self._write_manifest(project, multi_source=False)
                path = project_support(project, 'layout/ltcg/source_ownership_test.json')
                manifest = json.loads(path.read_text())
                alias = {'symbol': '?vtable@@', 'address': '0x00401030', 'bytes': '01020304',
                         'reference_scope': 'compiled_graph'}
                manifest['data_aliases'] = [alias]
                if mutation == 'overlap':
                    alias['address'] = '0x00401000'
                elif mutation == 'overflow':
                    alias['address'] = '0xfffffffe'
                elif mutation == 'duplicate':
                    manifest['data_aliases'].append(dict(alias))
                path.write_text(json.dumps(manifest))
                with self.assertRaises(LTCGClusterError):
                    load_cluster(project, 'layout/ltcg/source_ownership_test.json', regions)


class NativeDataAliasReferenceTests(unittest.TestCase):
    ALIAS_ADDRESS = 0x46f230

    def _fixture(self, project, reference='anchor', scope='compiled_graph',
                 anchor_origin='cluster.obj', alias_symbol='?vtable@@'):
        data = bytearray(NativeExportMapTests()._image(0, 0).data)
        struct.pack_into('<I', data, 0x98 + 16, 0x1008)
        struct.pack_into('<I', data, 0x98 + 0xe0 + 8, 0x30)
        for name, offset in [('function', 0), ('context', 8), ('anchor', 16)]:
            value = self.ALIAS_ADDRESS if name == reference else 0x12345678
            data[0x200 + offset:0x206 + offset] = b'\xb8' + struct.pack('<I', value) + b'\xc3'
        executable = project / 'cluster.exe'
        executable.write_bytes(data)
        map_path = project / 'cluster.map'
        map_path.write_text(''' cluster
 Timestamp is 00000000
 Preferred load address is 00400000
 Start         Length     Name                   Class
 0001:00000000 00000006H .text$01selected CODE
 0001:00000008 00000006H .text$02context CODE
 0001:00000010 00000006H .text$03anchor CODE
 0002:00000000 00000040H .rdata DATA
 Address         Publics by Value              Rva+Base     Lib:Object
 0001:00000000 _selected 00401000 f cluster.obj
 0001:00000008 _context 00401008 f cluster.obj
 0001:00000010 _anchor 00401010 f ''' + anchor_origin + '''
 0000:0046f230 ''' + alias_symbol + ''' 0046f230 bindings.obj
 entry point at 0001:00000008
 Static symbols
''')
        spec = {
            'image_base': 0x400000, 'entry_address': 0x401008,
            'functions': [{'name': 'Selected', 'symbol': '_selected', 'section': '.text$01selected',
                           'address': 0x401000, 'size': 6, '_source': 'src/primary.cpp',
                           'actual_abi': 'cdecl'}],
            'context': {'symbol': '_context', 'section': '.text$02context',
                        'address': 0x401008, 'size': 6},
            'anchors': [{'name': 'Anchor', 'symbol': '_anchor', 'section': '.text$03anchor',
                         'address': 0x401010, 'size': 6}],
            'gaps': [], 'constants': [], 'absolute_symbols': [], 'constant_aliases': [],
            'anchor_roots': [],
            'data_aliases': [{'symbol': alias_symbol, 'address': self.ALIAS_ADDRESS,
                             'size': 32, 'reference_scope': scope}], 'calls': [],
        }
        return spec, executable, map_path

    def _validate(self, fixture):
        return validate_native_output(*fixture, ['cluster.obj'])

    def test_default_and_explicit_selected_scope_remain_selected_only(self):
        for reference in ('context', 'anchor'):
            for omitted in (False, True):
                with self.subTest(reference=reference, omitted=omitted), tempfile.TemporaryDirectory() as directory:
                    fixture = self._fixture(Path(directory), reference, 'selected')
                    if omitted:
                        fixture[0]['data_aliases'][0].pop('reference_scope')
                    with self.assertRaisesRegex(LTCGClusterError, 'selected body'):
                        self._validate(fixture)

    def test_compiled_graph_accepts_only_valid_complete_bodies(self):
        for reference in ('function', 'context', 'anchor'):
            with self.subTest(reference=reference), tempfile.TemporaryDirectory() as directory:
                reports, provenance = self._validate(self._fixture(Path(directory), reference))
                self.assertEqual([r['symbol'] for r in reports], ['_selected'])
                references = provenance['data_alias_references'][0]['references']
                self.assertEqual(len(references), 1)
                self.assertEqual(references[0]['kind'], reference)
                self.assertEqual(references[0]['selected'], reference == 'function')

    def test_reference_in_no_compiled_body_is_rejected(self):
        for scope in ('selected', 'compiled_graph'):
            with self.subTest(scope=scope), tempfile.TemporaryDirectory() as directory:
                with self.assertRaisesRegex(LTCGClusterError, 'not referenced'):
                    self._validate(self._fixture(Path(directory), 'none', scope))

    def test_default_selected_body_remains_accepted(self):
        with tempfile.TemporaryDirectory() as directory:
            reports, provenance = self._validate(self._fixture(Path(directory), 'function', 'selected'))
            self.assertEqual(len(reports), 1)
            self.assertTrue(provenance['data_alias_references'][0]['references'][0]['selected'])

    def test_anchor_foreign_or_layout_origin_is_rejected(self):
        for origin in ('layout.obj', 'bindings.obj', 'foreign.obj', 'foreign.lib: member.obj'):
            with self.subTest(origin=origin), tempfile.TemporaryDirectory() as directory:
                with self.assertRaisesRegex(LTCGClusterError, 'anchor address/origin'):
                    self._validate(self._fixture(Path(directory), anchor_origin=origin))

    def test_default_scope_preserves_legacy_anchor_origin_behavior(self):
        for origin in ('CIL library: CIL module', 'foreign.obj'):
            with self.subTest(origin=origin), tempfile.TemporaryDirectory() as directory:
                reports, provenance = self._validate(self._fixture(
                    Path(directory), 'function', 'selected', anchor_origin=origin))
                self.assertEqual(len(reports), 1)
                self.assertEqual(provenance['data_alias_references'][0]['reference_scope'], 'selected')

    def test_anchor_symbol_and_extent_checks_are_preserved(self):
        for mutation in ('missing_symbol', 'duplicate_symbol', 'nonfunction', 'segment_zero',
                         'declared_address', 'declared_partial', 'contribution_partial',
                         'contribution_start', 'contribution_segment'):
            with self.subTest(mutation=mutation), tempfile.TemporaryDirectory() as directory:
                fixture = self._fixture(Path(directory))
                spec, executable, map_path = fixture
                text = map_path.read_text()
                if mutation == 'missing_symbol':
                    text = text.replace(' 0001:00000010 _anchor 00401010 f cluster.obj\n', '')
                elif mutation == 'duplicate_symbol':
                    text = text.replace(' entry point', ' 0001:00000010 _anchor 00401010 f cluster.obj\n entry point')
                elif mutation == 'nonfunction':
                    text = text.replace('_anchor 00401010 f cluster.obj', '_anchor 00401010 cluster.obj')
                elif mutation == 'segment_zero':
                    text = text.replace('0001:00000010 _anchor', '0000:00401010 _anchor')
                elif mutation == 'declared_address':
                    spec['anchors'][0]['address'] += 1
                elif mutation == 'declared_partial':
                    spec['anchors'][0]['size'] -= 1
                elif mutation == 'contribution_partial':
                    text = text.replace('00000006H .text$03anchor', '00000007H .text$03anchor')
                elif mutation == 'contribution_start':
                    text = text.replace('0001:00000010 00000006H .text$03anchor', '0001:0000000f 00000006H .text$03anchor')
                elif mutation == 'contribution_segment':
                    text = text.replace('0001:00000010 00000006H .text$03anchor', '0002:00000010 00000006H .text$03anchor')
                map_path.write_text(text)
                with self.assertRaises(LTCGSemanticError):
                    self._validate(fixture)

    def test_context_origin_and_complete_contribution_are_required(self):
        for mutation in ('origin', 'partial', 'address', 'class'):
            with self.subTest(mutation=mutation), tempfile.TemporaryDirectory() as directory:
                fixture = self._fixture(Path(directory), 'context')
                spec, executable, map_path = fixture
                text = map_path.read_text()
                if mutation == 'origin':
                    text = text.replace('_context 00401008 f cluster.obj', '_context 00401008 f layout.obj')
                elif mutation == 'partial':
                    spec['context']['size'] -= 1
                elif mutation == 'address':
                    spec['context']['address'] += 1
                elif mutation == 'class':
                    text = text.replace('.text$02context CODE', '.text$02context DATA')
                map_path.write_text(text)
                with self.assertRaises(LTCGSemanticError):
                    self._validate(fixture)

    def test_constant_alias_remains_selected_only(self):
        with tempfile.TemporaryDirectory() as directory:
            fixture = self._fixture(Path(directory), 'anchor', alias_symbol='__real@3f800000')
            spec = fixture[0]
            spec['constant_aliases'] = spec.pop('data_aliases')
            spec['data_aliases'] = []
            with self.assertRaisesRegex(LTCGClusterError, 'constant alias.*selected body'):
                self._validate(fixture)

    def test_alias_binding_and_undeclared_function_checks_remain_required(self):
        for mutation in ('binding_address', 'binding_segment', 'undeclared_function', 'interior_symbol'):
            with self.subTest(mutation=mutation), tempfile.TemporaryDirectory() as directory:
                fixture = self._fixture(Path(directory))
                map_path = fixture[2]
                text = map_path.read_text()
                if mutation == 'binding_address':
                    text = text.replace('?vtable@@ 0046f230', '?vtable@@ 0046f234')
                elif mutation == 'binding_segment':
                    text = text.replace('0000:0046f230 ?vtable@@ 0046f230 bindings.obj',
                                        '0001:00000018 ?vtable@@ 00401018 bindings.obj')
                elif mutation == 'undeclared_function':
                    text = text.replace(' entry point', ' 0001:00000018 _foreign 00401018 f cluster.obj\n entry point')
                elif mutation == 'interior_symbol':
                    text = text.replace(' entry point', ' 0001:00000011 _interior 00401011 cluster.obj\n entry point')
                map_path.write_text(text)
                with self.assertRaises(LTCGSemanticError):
                    self._validate(fixture)


class OrdinarySourceManifestTests(unittest.TestCase):
    def _manifest(self, project):
        regions = ClusterSourceOwnershipTests._write_manifest(self, project, multi_source=False)
        (project_support(project, 'layout/ltcg/ordinary.cpp')).write_text('// complete ordinary input\n')
        path = project_support(project, 'layout/ltcg/source_ownership_test.json')
        manifest = json.loads(path.read_text())
        manifest['exceptions'] = True
        source = 'layout/ltcg/ordinary.cpp'
        manifest['ordinary_sources'] = [{'source': source, 'section_renames': [
            {'from': '.text$x', 'to': '.text$m'}, {'from': '.xdata$x', 'to': '.rdata$m'}]}]
        manifest['anchors'] = [
            {'name': 'OrdinaryOwner', 'symbol': '_ordinary', 'section': '.text$05ordinary',
             'address': '0x00401030', 'size': 1, 'source': source},
            {'name': 'OrdinaryUnwind', 'symbol': '_stable_unwind', 'section': '.text$m',
             'address': '0x00401040', 'size': 3, 'source': source, 'generated': True,
             'native_symbol_pattern': r'\$L[0-9]+'},
            {'name': 'OrdinaryHandler', 'symbol': '_handler', 'section': '.text$m',
             'address': '0x00401043', 'size': 3, 'source': source, 'generated': True}]
        manifest['native_data'] = [{'section': '.rdata$m', 'address': '0x00402000',
                                   'bytes': '00000000', 'source': source, 'description': 'complete metadata'}]
        manifest['anchor_roots'] = ['_ordinary']
        return manifest, regions, path

    def _load(self, project, mutation=None):
        manifest, regions, path = self._manifest(project)
        if mutation:
            mutation(manifest)
        path.write_text(json.dumps(manifest))
        return load_cluster(project, str(path.relative_to(project)), regions)

    def test_mixed_sources_and_generated_anchor_group_are_opt_in(self):
        with tempfile.TemporaryDirectory() as directory:
            project = Path(directory)
            loaded = self._load(project)
            self.assertEqual(loaded['ordinary_source_paths'], [(project_support(project, 'layout/ltcg/ordinary.cpp')).resolve()])
            self.assertEqual(loaded['anchor_roots'], ['_ordinary'])
            self.assertEqual(len(loaded['functions']), 1)
            self.assertEqual(len(loaded['regions']), 1)

    def test_ordinary_source_declarations_reject_invalid_inputs(self):
        mutations = [
            lambda m: m.update(ordinary_sources='ordinary.cpp'),
            lambda m: m['ordinary_sources'].append(dict(m['ordinary_sources'][0])),
            lambda m: m['ordinary_sources'].append(dict(m['ordinary_sources'][0], source='src/secondary.cpp')),
            lambda m: m['ordinary_sources'].append(dict(m['ordinary_sources'][0], source='layout/ltcg/./ordinary.cpp')),
            lambda m: m['ordinary_sources'][0].update(source='/tmp/ordinary.cpp'),
            lambda m: m['ordinary_sources'][0].update(source='src/primary.cpp'),
            lambda m: m['ordinary_sources'][0].update(source='layout/ltcg/context.cpp'),
            lambda m: m['ordinary_sources'][0].update(source='layout/ltcg/missing.cpp'),
            lambda m: m['ordinary_sources'][0].update(flags=['/GL']),
            lambda m: m.update(exceptions=False),
            lambda m: m['included_sources'].append('layout/ltcg/ordinary.cpp'),
        ]
        for index, mutation in enumerate(mutations):
            with self.subTest(index=index), tempfile.TemporaryDirectory() as directory:
                def wrapped(manifest):
                    manifest.setdefault('included_sources', [])
                    mutation(manifest)
                with self.assertRaises(LTCGClusterError):
                    self._load(Path(directory), wrapped)

    def test_only_paired_dedicated_eh_section_headers_can_be_renamed(self):
        mutations = [
            lambda m: m['ordinary_sources'][0].update(section_renames=[]),
            lambda m: m['ordinary_sources'][0]['section_renames'].pop(),
            lambda m: m['ordinary_sources'][0]['section_renames'][0].update(**{'from': '.text$other'}),
            lambda m: m['ordinary_sources'][0]['section_renames'][0].update(to='.rdata$m'),
            lambda m: m['ordinary_sources'][0]['section_renames'][1].update(to='.text$m'),
            lambda m: m['ordinary_sources'][0]['section_renames'][0].update(to='.text$long'),
            lambda m: m['ordinary_sources'][0]['section_renames'][1].update(to='.rdata$long'),
            lambda m: m['ordinary_sources'][0]['section_renames'][0].update(to='.text$x'),
            lambda m: m['ordinary_sources'][0]['section_renames'][1].update(**{'from': '.text$x'}),
            lambda m: m['ordinary_sources'][0]['section_renames'][0].update(offset=100),
        ]
        for index, mutation in enumerate(mutations):
            with self.subTest(index=index), tempfile.TemporaryDirectory() as directory:
                with self.assertRaises(LTCGClusterError):
                    self._load(Path(directory), mutation)

    def test_roots_and_generated_anchors_cannot_borrow_other_sources(self):
        mutations = [
            lambda m: m.update(anchor_roots=['_external']),
            lambda m: m.update(anchor_roots=['_stable_unwind']),
            lambda m: m.update(anchor_roots=['_ordinary', '_ordinary']),
            lambda m: m.update(roots=['_ordinary']),
            lambda m: m['anchors'][0].update(source='src/primary.cpp'),
            lambda m: m['anchors'][1].pop('source'),
            lambda m: m['anchors'][1].update(section='.text$x'),
            lambda m: m['anchors'][1].update(native_symbol_pattern='.*'),
            lambda m: m['anchors'][1].update(generated=1),
            lambda m: m['native_data'][0].pop('source'),
            lambda m: m['native_data'][0].update(source='src/primary.cpp'),
            lambda m: m.update(native_data=[]),
            lambda m: m['anchors'].__setitem__(slice(1, None), []),
        ]
        for index, mutation in enumerate(mutations):
            with self.subTest(index=index), tempfile.TemporaryDirectory() as directory:
                with self.assertRaises(LTCGClusterError):
                    self._load(Path(directory), mutation)

    def test_default_manifest_still_rejects_new_anchor_and_data_fields(self):
        for kind in ('anchor', 'data'):
            with self.subTest(kind=kind), tempfile.TemporaryDirectory() as directory:
                project = Path(directory)
                manifest, regions, path = self._manifest(project)
                manifest.pop('ordinary_sources')
                manifest.pop('anchor_roots')
                if kind == 'anchor':
                    manifest['native_data'] = []
                else:
                    manifest['anchors'] = []
                path.write_text(json.dumps(manifest))
                with self.assertRaisesRegex(LTCGClusterError, 'unknown fields'):
                    load_cluster(project, str(path.relative_to(project)), regions)

    def test_ordinary_source_is_pinned_by_snapshot(self):
        with tempfile.TemporaryDirectory() as directory:
            loaded = self._load(Path(directory))
            snapshot = _snapshot(loaded)
            ordinary = loaded['ordinary_source_paths'][0]
            self.assertIn(str(ordinary), snapshot)
            ordinary.write_text('// changed ordinary TU\n')
            with self.assertRaisesRegex(LTCGClusterError, 'changed during compilation'):
                _verify_snapshot(snapshot)

    def test_unit_cache_key_covers_complete_ordinary_include_closure(self):
        from matching2.tools.matching.build_msvc import UnitCache
        with tempfile.TemporaryDirectory() as directory:
            project = Path(directory)
            loaded = self._load(project)
            ordinary = loaded['ordinary_source_paths'][0]
            header = ordinary.with_name('ordinary.hpp')
            header.write_text('// first header\n')
            ordinary.write_text('#include "ordinary.hpp"\n')
            toolkit = project/'toolkit'
            (toolkit/'bin').mkdir(parents=True)
            config = {'flags': ['/O2'], 'compiler_version': '13.10.6030'}
            def key():
                cache = UnitCache(project, toolkit, project/'cache', config)
                return cache.key(loaded['source'], config, loaded['regions'], loaded, 'native-ltcg')
            first = key()
            header.write_text('// changed header\n')
            second = key()
            ordinary.write_text('#include "ordinary.hpp"\n// changed TU\n')
            third = key()
            self.assertNotEqual(first, second)
            self.assertNotEqual(second, third)


class OrdinaryObjectRenameTests(unittest.TestCase):
    def _object(self, path):
        # Minimal genuine COFF format, including relocation and auxiliary records.
        code, metadata = b'\xe8\0\0\0\0\xc3', b'\0\0\0\0'
        section_table_end = 100
        reloc_offset = section_table_end + len(code) + len(metadata)
        symbol_offset = reloc_offset + 10
        records = b''.join([
            struct.pack('<8sIhHBB', b'_callee', 0, 0, 0x20, 2, 0),
            struct.pack('<8sIhHBB', b'.text$x', 0, 1, 0, 3, 1),
            struct.pack('<IHHIhB3x', len(code), 1, 0, 0, 0, 0),
            struct.pack('<8sIhHBB', b'.xdata$x', 0, 2, 0, 3, 1),
            struct.pack('<IHHIhB3x', len(metadata), 0, 0, 0, 0, 0),
        ])
        data = struct.pack('<HHIIIHH', 0x14c, 2, 0, symbol_offset, 5, 0, 0)
        data += struct.pack('<8sIIIIIIHHI', b'.text$x', 0, 0, len(code), 100, reloc_offset, 0, 1, 0, 0x60500020)
        data += struct.pack('<8sIIIIIIHHI', b'.xdata$x', 0, 0, len(metadata), 106, 0, 0, 0, 0, 0x40500040)
        data += code + metadata + struct.pack('<IIH', 1, 0, 0x14) + records + struct.pack('<I', 4)
        path.write_bytes(data)

    def _prepare(self, project):
        original, placed = project/'original.obj', project/'placed.obj'
        self._object(original)
        report = _prepare_ordinary_object(original, placed, [
            {'from': '.text$x', 'to': '.text$m'}, {'from': '.xdata$x', 'to': '.rdata$m'}])
        return original, placed, report

    def test_section_names_change_while_all_other_bytes_remain_identical(self):
        with tempfile.TemporaryDirectory() as directory:
            original, placed, report = self._prepare(Path(directory))
            before, after = _read_object(original), _read_object(placed)
            self.assertEqual(before['records'], after['records'])
            self.assertEqual([s['raw'] for s in before['sections']], [s['raw'] for s in after['sections']])
            self.assertEqual([s['relocations'] for s in before['sections']], [s['relocations'] for s in after['sections']])
            self.assertEqual([s['name'] for s in after['sections']], ['.text$m', '.rdata$m'])
            self.assertEqual(report['instruction_bytes_changed'], 0)
            self.assertEqual(report['relocation_bytes_changed'], 0)
            self.assertEqual(report['symbol_bytes_changed'], 0)

    def test_any_payload_relocation_symbol_flag_or_header_edit_is_rejected(self):
        for offset in (100, 106, 110, 120, 20+36, 0):
            with self.subTest(offset=offset), tempfile.TemporaryDirectory() as directory:
                original, placed, report = self._prepare(Path(directory))
                data = bytearray(placed.read_bytes())
                data[offset] ^= 1
                placed.write_bytes(data)
                with self.assertRaises((LTCGClusterError, CoffRegionError)):
                    _verify_ordinary_object(original, placed, report['section_renames'])

    def test_missing_or_duplicate_source_section_is_rejected(self):
        for duplicate in (False, True):
            with self.subTest(duplicate=duplicate), tempfile.TemporaryDirectory() as directory:
                original = Path(directory)/'original.obj'
                self._object(original)
                data = bytearray(original.read_bytes())
                data[60:68] = b'.text$x\0' if duplicate else b'.rdata\0\0'
                original.write_bytes(data)
                with self.assertRaisesRegex(LTCGClusterError, 'one complete'):
                    _prepare_ordinary_object(original, Path(directory)/'placed.obj', [
                        {'from': '.text$x', 'to': '.text$m'}, {'from': '.xdata$x', 'to': '.rdata$m'}])


class OrdinaryNativeContributionTests(unittest.TestCase):
    SOURCE = 'layout/ltcg/ordinary.cpp'

    def _fixture(self, project):
        image = bytearray(NativeExportMapTests()._image(0, 0).data)
        struct.pack_into('<I', image, 0x98 + 16, 0x1008)
        struct.pack_into('<I', image, 0x98 + 0xe0 + 8, 0x30)
        image[0x200:0x206] = b'\x90' * 5 + b'\xc3'
        image[0x208:0x20e] = b'\x90' * 5 + b'\xc3'
        image[0x210:0x216] = b'\x33\xc0\xc3' * 2
        executable, map_path = project/'cluster.exe', project/'cluster.map'
        executable.write_bytes(image)
        map_path.write_text(''' cluster
 Timestamp is 00000000
 Preferred load address is 00400000
 Start         Length     Name                   Class
 0001:00000000 00000006H .text$01selected CODE
 0001:00000008 00000006H .text$02context CODE
 0001:00000010 00000006H .text$m CODE
 0002:00000000 00000004H .rdata$m DATA
 Address         Publics by Value              Rva+Base     Lib:Object
 0001:00000000 _selected 00401000 f cluster.obj
 0001:00000008 _context 00401008 f cluster.obj
 entry point at 0001:00000008
 Static symbols
 0001:00000010 $L100 00401010 f ordinary.obj
 0001:00000013 __ehhandler$_ordinary 00401013 f ordinary.obj
''')
        original, obj, _report = OrdinaryObjectRenameTests()._prepare(project)
        ordinary_object = project/'ordinary.obj'
        obj.rename(ordinary_object)
        spec = {
            'image_base': 0x400000, 'entry_address': 0x401008,
            'functions': [{'name': 'Selected', 'symbol': '_selected', 'section': '.text$01selected',
                           'address': 0x401000, 'size': 6, '_source': 'src/primary.cpp', 'actual_abi': 'cdecl'}],
            'context': {'symbol': '_context', 'section': '.text$02context', 'address': 0x401008, 'size': 6},
            'ordinary_sources': [{'source': self.SOURCE, 'section_renames': [
                {'from': '.text$x', 'to': '.text$m'}, {'from': '.xdata$x', 'to': '.rdata$m'}]}],
            'anchors': [
                {'name': 'OrdinaryUnwind', 'symbol': '_stable_unwind', 'native_symbol_pattern': r'\$L[0-9]+',
                 'section': '.text$m', 'address': 0x401010, 'size': 3, '_source': self.SOURCE, 'generated': True},
                {'name': 'OrdinaryHandler', 'symbol': '__ehhandler$_ordinary', 'section': '.text$m',
                 'address': 0x401013, 'size': 3, '_source': self.SOURCE, 'generated': True}],
            'native_data': [{'section': '.rdata$m', 'address': 0x402000, 'size': 4,
                             'bytes_value': bytes(4), 'source': self.SOURCE}],
            'gaps': [], 'constants': [], 'absolute_symbols': [], 'constant_aliases': [],
            'data_aliases': [], 'calls': [],
        }
        return spec, executable, map_path, {self.SOURCE: ordinary_object}

    def _validate(self, fixture):
        spec, executable, map_path, objects = fixture
        return validate_native_output(spec, executable, map_path, ['cluster.obj'], ordinary_objects=objects)

    def test_complete_origin_bound_groups_and_metadata_are_validation_only(self):
        with tempfile.TemporaryDirectory() as directory:
            selected, evidence = self._validate(self._fixture(Path(directory)))
            self.assertEqual([r['symbol'] for r in selected], ['_selected'])
            self.assertEqual(len(evidence['unselected_functions']), 2)
            self.assertEqual(len(evidence['ordinary_contributions']), 2)
            for row in evidence['unselected_functions'] + evidence['ordinary_contributions']:
                self.assertFalse(row['selected'])
                self.assertEqual(row['recovered_code_bytes'], 0)

    def test_unaccounted_foreign_or_partial_groups_and_tables_are_rejected(self):
        mutations = ('foreign_origin', 'public_generated', 'duplicate_generated', 'missing_generated',
                     'missing_prefix', 'missing_suffix', 'overlap', 'wrong_code_extent',
                     'wrong_code_start', 'metadata_partial', 'metadata_bytes', 'metadata_source',
                     'metadata_address', 'missing_metadata', 'missing_object',
                     'undeclared_function', 'undeclared_table', 'unrenamed_object')
        for mutation in mutations:
            with self.subTest(mutation=mutation), tempfile.TemporaryDirectory() as directory:
                fixture = self._fixture(Path(directory))
                spec, executable, map_path, objects = fixture
                text = map_path.read_text()
                if mutation == 'foreign_origin':
                    text = text.replace('$L100 00401010 f ordinary.obj', '$L100 00401010 f foreign.obj')
                elif mutation == 'public_generated':
                    text = text.replace(' Static symbols\n 0001:00000010', ' 0001:00000010')
                elif mutation == 'duplicate_generated':
                    text += ' 0001:00000010 $L100 00401010 f ordinary.obj\n'
                elif mutation == 'missing_generated':
                    spec['anchors'].pop()
                elif mutation == 'missing_prefix':
                    spec['anchors'][0]['address'] += 1
                    spec['anchors'][0]['size'] -= 1
                elif mutation == 'missing_suffix':
                    spec['anchors'][1]['size'] -= 1
                elif mutation == 'overlap':
                    spec['anchors'][0]['size'] += 1
                elif mutation == 'wrong_code_extent':
                    text = text.replace('00000006H .text$m', '00000007H .text$m')
                elif mutation == 'wrong_code_start':
                    text = text.replace('0001:00000010 00000006H .text$m', '0001:00000011 00000006H .text$m')
                elif mutation == 'metadata_partial':
                    spec['native_data'][0]['size'] -= 1
                elif mutation == 'metadata_bytes':
                    spec['native_data'][0]['bytes_value'] = b'\x01\0\0\0'
                elif mutation == 'metadata_source':
                    spec['native_data'][0]['source'] = 'foreign.cpp'
                elif mutation == 'metadata_address':
                    spec['native_data'][0]['address'] += 1
                elif mutation == 'missing_metadata':
                    spec['native_data'] = []
                elif mutation == 'missing_object':
                    objects.clear()
                elif mutation == 'undeclared_function':
                    text += ' 0001:00000018 _undeclared 00401018 f ordinary.obj\n'
                elif mutation == 'undeclared_table':
                    text = text.replace(' Address         Publics', ' 0002:00000004 00000004H .xdata$extra DATA\n Address         Publics')
                elif mutation == 'unrenamed_object':
                    objects[self.SOURCE] = Path(directory)/'original.obj'
                map_path.write_text(text)
                with self.assertRaises(LTCGSemanticError):
                    self._validate(fixture)


class MixedGeneratedNameTests(unittest.TestCase):
    SOURCE = OrdinaryNativeContributionTests.SOURCE
    _fixture = OrdinaryNativeContributionTests._fixture
    _validate = OrdinaryNativeContributionTests._validate
    def _cil_fixture(self, project, duplicate=False):
        fixture = self._fixture(project)
        spec, executable, map_path, objects = fixture
        image = bytearray(executable.read_bytes())
        image[0x220:0x226] = b'\x33\xc0\xc3' * 2
        executable.write_bytes(image)
        text = map_path.read_text()
        text = text.replace(' 0002:00000000 00000004H .rdata$m DATA',
                            ' 0001:00000020 00000006H .text$x CODE\n 0002:00000000 00000004H .rdata$m DATA\n 0002:00000010 00000004H .xdata$x DATA')
        text += ' 0001:00000020 $L100 00401020 f CIL library: CIL module\n'
        text += ' 0001:00000023 __ehhandler$_selected 00401023 f CIL library: CIL module\n'
        if duplicate:
            text += ' 0001:00000020 $L100 00401020 f CIL library: CIL module\n'
        map_path.write_text(text)
        spec['functions'] += [
            {'name': 'SelectedUnwind', 'symbol': '_selected_unwind', 'section': '.text$x',
             'address': 0x401020, 'size': 3, '_source': 'src/primary.cpp', 'actual_abi': 'unwind',
             'generated': True, 'native_symbol_pattern': r'\$L[0-9]+'},
            {'name': 'SelectedHandler', 'symbol': '__ehhandler$_selected', 'section': '.text$x',
             'address': 0x401023, 'size': 3, '_source': 'src/primary.cpp', 'actual_abi': 'handler',
             'generated': True}]
        spec['native_data'].append({'section': '.xdata$x', 'address': 0x402010,
                                   'size': 4, 'bytes_value': bytes(4)})
        return fixture

    def test_static_names_may_repeat_between_cil_and_ordinary_sources(self):
        with tempfile.TemporaryDirectory() as directory:
            selected, evidence = self._validate(self._cil_fixture(Path(directory)))
            self.assertEqual([r['symbol'] for r in selected],
                             ['_selected', '_selected_unwind', '__ehhandler$_selected'])
            self.assertEqual(selected[1]['native_symbol'], '$L100')
            self.assertEqual(selected[1]['map_origin'], 'CIL library: CIL module')
            ordinary_unwind = evidence['unselected_functions'][0]
            self.assertEqual(ordinary_unwind['native_symbol'], '$L100')
            self.assertEqual(ordinary_unwind['map_origin'], 'ordinary.obj')

    def test_same_origin_and_address_duplicate_is_rejected(self):
        with tempfile.TemporaryDirectory() as directory:
            with self.assertRaises(LTCGSemanticError):
                self._validate(self._cil_fixture(Path(directory), duplicate=True))


if __name__ == "__main__":
    unittest.main()
