"""Strict parser tests and an optional live MSVC 7.1 LTCG integration test."""

import sys
from pathlib import Path

if __package__ in (None, ""):
    sys.path.insert(0, str(Path(__file__).resolve().parents[2]))


import json
import shutil
import struct
import tempfile
import unittest


ROOT = Path(__file__).resolve().parents[2]

from matching2.tools.matching.ltcg_semantic import (  # noqa: E402
    DEFAULT_TOOLKIT,
    LTCGSemanticError,
    PEImage,
    _normalize_manifest,
    extract_functions,
    parse_map,
    run_pipeline,
    validate_map_pe,
)


TIMESTAMP = 0x6A9EF533
HELPER = "?ClearPending@@YGXPAUD3DResourceList@@@Z"
ROOT_SYMBOL = "?ProbeRoot@@YGXPAUD3DResourceList@@@Z"
CLEAR_BYTES = bytes.fromhex("33 c9 89 48 08 89 48 0c 89 48 10 c3")


def make_pe(code: bytes, *, entry_offset: int = 0x10, symbol_byte: int | None = None) -> bytes:
    """Create the smallest structurally useful PE32 fixture for parser tests."""

    data = bytearray(0x400)
    data[:2] = b"MZ"
    struct.pack_into("<I", data, 0x3C, 0x80)
    data[0x80:0x84] = b"PE\0\0"
    struct.pack_into("<HHIIIHH", data, 0x84, 0x14C, 1, TIMESTAMP, 0, 0, 0xE0, 0x010F)
    optional = 0x98
    struct.pack_into("<HBB", data, optional, 0x10B, 7, 10)
    struct.pack_into("<I", data, optional + 16, 0x1000 + entry_offset)
    struct.pack_into("<I", data, optional + 20, 0x1000)
    struct.pack_into("<I", data, optional + 24, 0x2000)
    struct.pack_into("<I", data, optional + 28, 0x400000)
    struct.pack_into("<II", data, optional + 32, 0x1000, 0x200)
    struct.pack_into("<II", data, optional + 56, 0x2000, 0x200)
    section_table = optional + 0xE0
    struct.pack_into(
        "<8sIIIIIIHHI",
        data,
        section_table,
        b".text\0\0\0",
        len(code),
        0x1000,
        0x200,
        0x200,
        0,
        0,
        0,
        0,
        0x60000020,
    )
    data[0x200:0x200 + len(code)] = code
    if symbol_byte is not None:
        data[0x200] = symbol_byte
    return bytes(data)


def make_map(*, helper_address: int = 0x401000, helper_offset: int = 0) -> str:
    return f""" probe

 Timestamp is {TIMESTAMP:08x} (fixture)

 Preferred load address is 00400000

 Start         Length     Name                   Class
 0001:00000000 00000020H .text                   CODE

  Address         Publics by Value              Rva+Base     Lib:Object

 0001:00000010       {ROOT_SYMBOL} 00401010 f   probe.obj

 entry point at        0001:00000010

 Static symbols

 0001:{helper_offset:08x}       {HELPER} {helper_address:08x} f   probe.obj
"""


class LTCGParserTest(unittest.TestCase):
    def test_static_and_public_symbols_extract_from_cross_checked_map_and_pe(self):
        code = CLEAR_BYTES + b"\xCC" * 4 + b"\xC3" + b"\xCC" * 15
        pe = PEImage(make_pe(code))
        link_map = parse_map(make_map())
        validate_map_pe(link_map, pe)
        functions = extract_functions(
            [{
                "name": "ClearPending",
                "symbol": HELPER,
                "visibility": "static",
                "size": 12,
                "expected_bytes": CLEAR_BYTES,
                "expected_sha256": None,
                "expected_offset": 0,
            }],
            link_map,
            pe,
        )
        self.assertEqual(functions[0]["address"], "0x00401000")
        self.assertEqual(functions[0]["file_offset"], "0x200")
        self.assertEqual(functions[0]["bytes_hex"], CLEAR_BYTES.hex(" "))
        self.assertEqual(functions[0]["visibility"], "static")

    def test_map_pe_coordinate_and_explicit_extent_fail_closed(self):
        code = CLEAR_BYTES + b"\xCC" * 4 + b"\xC3" + b"\xCC" * 15
        pe = PEImage(make_pe(code))
        with self.assertRaisesRegex(LTCGSemanticError, "lists 0x401001"):
            validate_map_pe(parse_map(make_map(helper_address=0x401001)), pe)

        link_map = parse_map(make_map())
        with self.assertRaisesRegex(LTCGSemanticError, "crosses MAP symbol"):
            extract_functions(
                [{
                    "name": "ClearPending",
                    "symbol": HELPER,
                    "visibility": "static",
                    "size": 17,
                    "expected_bytes": None,
                    "expected_sha256": None,
                    "expected_offset": None,
                }],
                link_map,
                pe,
            )
        changed = bytearray(CLEAR_BYTES)
        changed[5] ^= 1
        with self.assertRaisesRegex(LTCGSemanticError, r"expected bytes at \+0x5"):
            extract_functions(
                [{
                    "name": "ClearPending",
                    "symbol": HELPER,
                    "visibility": "static",
                    "size": 12,
                    "expected_bytes": bytes(changed),
                    "expected_sha256": None,
                    "expected_offset": None,
                }],
                link_map,
                pe,
            )

    def test_manifest_requires_reviewable_cpp_stub_and_exact_extent(self):
        with tempfile.TemporaryDirectory() as temporary:
            directory = Path(temporary)
            (directory / "cluster.cpp").write_text("void Root() {}\n")
            (directory / "stubs.cpp").write_text("extern \"C\" void Stub() {}\n")
            manifest = {
                "schema_version": 1,
                "name": "fixture",
                "sources": [
                    {"path": "cluster.cpp", "role": "cluster"},
                    {"path": "stubs.cpp", "role": "stub"},
                ],
                "entry_symbol": "?Root@@YGXXZ",
                "functions": [{
                    "name": "Root",
                    "symbol": "?Root@@YGXXZ",
                    "visibility": "public",
                    "size": 1,
                    "expected_hex": "c3",
                }],
            }
            path = directory / "manifest.json"
            path.write_text(json.dumps(manifest))
            normalized = _normalize_manifest(path)
            self.assertEqual([item["role"] for item in normalized["sources"]], ["cluster", "stub"])
            self.assertEqual(normalized["functions"][0]["expected_bytes"], b"\xC3")

            manifest["functions"][0].pop("size")
            path.write_text(json.dumps(manifest))
            with self.assertRaisesRegex(LTCGSemanticError, "size must be an integer"):
                _normalize_manifest(path)
            manifest["functions"][0]["size"] = 1
            manifest["sources"][1]["path"] = "stubs.obj"
            (directory / "stubs.obj").write_bytes(b"raw")
            path.write_text(json.dumps(manifest))
            with self.assertRaisesRegex(LTCGSemanticError, "must name a .cpp file"):
                _normalize_manifest(path)


class LTCGLiveToolchainTest(unittest.TestCase):
    @unittest.skipUnless(
        DEFAULT_TOOLKIT.joinpath("bin/cl.exe").is_file()
        and DEFAULT_TOOLKIT.joinpath("bin/link.exe").is_file()
        and shutil.which("wine") is not None
        and shutil.which("winepath") is not None,
        "MSVC 13.10.6030 toolkit under Wine is not installed",
    )
    def test_d3d_static_helper_uses_ltcg_eax_abi_and_cpp_stub_resolves(self):
        source = r"""
struct D3DResourceList {
    unsigned int reserved_header;
    unsigned int flags;
    void* pending_008;
    void* pending_00C;
    void* pending_010;
    D3DResourceList* owner;
    void* first;
    void* last;
};

struct D3DResourceManager {
    D3DResourceList primary;
    unsigned int gap[1];
    D3DResourceList secondary;
};

extern "C" void __stdcall ProbeExternal();

static __declspec(noinline) void ClearPending(D3DResourceList* list) {
    list->pending_008 = 0;
    list->pending_00C = 0;
    list->pending_010 = 0;
}

static __declspec(noinline) void InitializeManager(D3DResourceManager* manager) {
    D3DResourceList* primary = &manager->primary;
    unsigned int primary_flags = primary->flags;
    primary->pending_008 = 0;
    primary->pending_00C = 0;
    primary->pending_010 = 0;
    primary->reserved_header = 0;
    primary->flags = primary_flags & 0xfffffffe;
    primary->owner = primary;
    primary->first = 0;
    primary->last = 0;

    D3DResourceList* secondary = &manager->secondary;
    secondary->flags &= 0xfffffffe;
    secondary->pending_008 = 0;
    secondary->pending_00C = 0;
    secondary->pending_010 = 0;
    secondary->reserved_header = 0;
    secondary->owner = secondary;
    secondary->first = 0;
    secondary->last = 0;
}

void D3DResourceProbeRoot(D3DResourceManager* manager, int initialize) {
    if (initialize)
        InitializeManager(manager);
    else
        ClearPending(&manager->primary);
    ProbeExternal();
}
"""
        stub = 'extern "C" void __stdcall ProbeExternal() {}\n'
        clear_symbol = "?ClearPending@@YGXPAUD3DResourceList@@@Z"
        initialize_symbol = "?InitializeManager@@YGXPAUD3DResourceManager@@@Z"
        entry_symbol = "?D3DResourceProbeRoot@@YGXPAUD3DResourceManager@@H@Z"
        with tempfile.TemporaryDirectory() as temporary:
            directory = Path(temporary)
            (directory / "cluster.cpp").write_text(source)
            (directory / "stubs.cpp").write_text(stub)
            manifest = {
                "schema_version": 1,
                "name": "d3d-ltcg-fixture",
                "sources": [
                    {"path": "cluster.cpp", "role": "cluster"},
                    {"path": "stubs.cpp", "role": "stub"},
                ],
                "entry_symbol": entry_symbol,
                "functions": [
                    {
                        "name": "ClearPending",
                        "symbol": clear_symbol,
                        "visibility": "static",
                        "size": 12,
                        "expected_offset": 0,
                        "expected_hex": CLEAR_BYTES.hex(" "),
                    },
                    {
                        "name": "InitializeManager",
                        "symbol": initialize_symbol,
                        "visibility": "static",
                        "size": 64,
                        "expected_offset": 0x10,
                    },
                ],
            }
            manifest_path = directory / "manifest.json"
            manifest_path.write_text(json.dumps(manifest, indent=2))
            report = run_pipeline(manifest_path, directory / "out")
            self.assertEqual([item["map_offset"] for item in report["functions"]],
                             ["0x00000000", "0x00000010"])
            self.assertEqual(report["functions"][0]["bytes_hex"], CLEAR_BYTES.hex(" "))
            self.assertEqual(report["functions"][0]["size"], 12)
            self.assertEqual(report["validation"]["raw_code_emission"], False)
            self.assertEqual(report["compiled_sources"][1]["role"], "stub")
            self.assertNotIn("/GL", report["compiled_sources"][1]["flags"])
            self.assertTrue((directory / "out/report.json").is_file())


if __name__ == "__main__":
    unittest.main()
