"""Focused manifest tests for native-LTCG cluster ownership."""

import json
from pathlib import Path
import struct
import tempfile
import unittest

from matching2.tools.matching.ltcg_cluster import LTCGClusterError, load_cluster, validate_internal_calls
from matching2.tools.matching.ltcg_semantic import LTCGSemanticError, PEImage, parse_map, validate_map_pe


class ClusterSourceOwnershipTests(unittest.TestCase):
    def _write_manifest(self, project, *, multi_source):
        (project / "src").mkdir()
        (project / "layout" / "ltcg").mkdir(parents=True)
        (project / "src" / "primary.cpp").write_text("// primary\n")
        (project / "src" / "secondary.cpp").write_text("// secondary\n")
        (project / "layout" / "ltcg" / "context.cpp").write_text("// context\n")
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
        (project / "layout" / "ltcg" / "source_ownership_test.json").write_text(
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

    def test_roots_are_schema_two_only(self):
        with tempfile.TemporaryDirectory() as directory:
            project = Path(directory)
            self._write_manifest(project, multi_source=False)
            path = project / "layout" / "ltcg" / "source_ownership_test.json"
            manifest = json.loads(path.read_text())
            manifest["roots"] = [manifest["functions"][0]["symbol"]]
            path.write_text(json.dumps(manifest))
            with self.assertRaisesRegex(LTCGClusterError, "unknown fields"):
                load_cluster(project, "layout/ltcg/source_ownership_test.json", [])

    def _whole_program(self, project, change=None):
        regions = self._write_manifest(project, multi_source=True)
        path = project / 'layout/ltcg/source_ownership_test.json'
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


if __name__ == "__main__":
    unittest.main()
