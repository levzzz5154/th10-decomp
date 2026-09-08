#!/usr/bin/env python3
"""Synthetic COFF tests for the lossless section normalizer."""

import hashlib
from pathlib import Path
import struct
import tempfile
import unittest

from matching2.tools.coff_regions import CoffRegionError, normalize_object


ROOT = Path(__file__).resolve().parents[2]


def _coff_name(name, strings):
    encoded = name.encode("ascii")
    if len(encoded) <= 8:
        return encoded.ljust(8, b"\0")
    offset = len(strings)
    strings.extend(encoded + b"\0")
    return b"\0\0\0\0" + struct.pack("<I", offset)


def _make_coff(path, sections, symbols):
    """Build the subset of an object needed by the normalizer tests.

    ``symbols`` entries are ``(name, value, section, type, storage, aux)`` and
    ``sections`` entries are ``(name, raw, relocations, characteristics)``.
    Relocations use ``(virtual_address, symbol_table_index, type)`` indexes.
    """

    strings = bytearray(struct.pack("<I", 4))
    symbol_bytes = bytearray()
    for name, value, section, symbol_type, storage, aux in symbols:
        symbol_bytes.extend(struct.pack("<8sIhHBB", _coff_name(name, strings), value,
                                        section, symbol_type, storage, len(aux)))
        for record in aux:
            assert len(record) == 18
            symbol_bytes.extend(record)
    struct.pack_into("<I", strings, 0, len(strings))

    section_count = len(sections)
    cursor = 20 + section_count * 40
    raw_offsets = []
    for _, raw, _, _ in sections:
        raw_offsets.append(cursor if raw else 0)
        cursor += len(raw)
    reloc_offsets = []
    for _, _, relocs, _ in sections:
        reloc_offsets.append(cursor if relocs else 0)
        cursor += len(relocs) * 10
    symbol_offset = cursor
    cursor += len(symbol_bytes) + len(strings)
    output = bytearray(cursor)
    struct.pack_into("<HHIIIHH", output, 0, 0x14C, section_count, 0x12345678,
                     symbol_offset, len(symbols) + sum(len(x[5]) for x in symbols), 0, 0)
    for i, (name, raw, relocs, characteristics) in enumerate(sections):
        header = struct.pack("<8sIIIIIIHHI", name.encode("ascii").ljust(8, b"\0"), 0,
                             0, len(raw), raw_offsets[i], reloc_offsets[i], 0,
                             len(relocs), 0, characteristics)
        offset = 20 + i * 40
        output[offset:offset + 40] = header
        if raw:
            output[raw_offsets[i]:raw_offsets[i] + len(raw)] = raw
        for j, (virtual_address, symbol_index, relocation_type) in enumerate(relocs):
            struct.pack_into("<IIH", output, reloc_offsets[i] + j * 10,
                             virtual_address, symbol_index, relocation_type)
    output[symbol_offset:symbol_offset + len(symbol_bytes)] = symbol_bytes
    output[symbol_offset + len(symbol_bytes):] = strings
    path.write_bytes(output)


def _read_output(path):
    data = path.read_bytes()
    machine, section_count, _, symbol_offset, symbol_count, optional_size, _ = struct.unpack_from("<HHIIIHH", data)
    sections = []
    for i in range(section_count):
        fields = struct.unpack_from("<8sIIIIIIHHI", data, 20 + i * 40)
        raw = data[fields[4]:fields[4] + fields[3]]
        relocs = [struct.unpack_from("<IIH", data, fields[5] + j * 10)
                  for j in range(fields[7])]
        sections.append((fields, raw, relocs))
    strings = data[symbol_offset + symbol_count * 18:]
    symbols = []
    index = 0
    while index < symbol_count:
        raw_name, value, section, symbol_type, storage, aux = struct.unpack_from(
            "<8sIhHBB", data, symbol_offset + index * 18
        )
        if raw_name[:4] == b"\0\0\0\0":
            off = struct.unpack_from("<I", raw_name, 4)[0]
            end = strings.find(b"\0", off)
            name = strings[off:end].decode("ascii")
        else:
            name = raw_name.rstrip(b"\0").decode("ascii")
        symbols.append((name, value, section, symbol_type, storage, aux))
        index += 1 + aux
    return machine, optional_size, sections, symbols


class CoffRegionsTest(unittest.TestCase):
    def test_selects_whole_section_and_preserves_raw_relocations(self):
        with tempfile.TemporaryDirectory() as temporary:
            directory = Path(temporary)
            source = directory / "input.obj"
            destination = directory / "normalized.obj"
            # A function section with both REL32 and DIR32 relocations.
            text = b"\xE8\0\0\0\0\xFF\x15\0\0\0\0"
            data = b"discarded-data"
            function_aux = b"\0" * 18
            symbols = [
                (".text$foo", 0, 1, 0, 3, []),
                ("?Foo@@YAXXZ", 0, 1, 0x20, 2, [function_aux]),
                ("?Bar@@YAXXZ", 0, 0, 0x20, 2, []),
                (".rdata$bar", 0, 2, 0, 3, []),
                ("??_C@discarded", 0, 2, 0, 2, []),
            ]
            # The auxiliary record makes the relocation indexes exercise the
            # primary/auxiliary remapping rather than assuming dense symbols.
            relocs = [(1, 2, 0x14), (7, 2, 0x06)]
            _make_coff(source, [
                (".text$fo", text, relocs, 0x60501020 | 0x1000),
                (".rdata$bar", data, [], 0x40501040 | 0x1000),
            ], symbols)

            report = normalize_object(source, destination, [{
                "name": "foo",
                "symbol": "?Foo@@YAXXZ",
                "address": "0x401000",
                "size": len(text),
            }])
            self.assertEqual(report["selected_section_count"], 1)
            region = report["regions"][0]
            self.assertEqual(region["section"], ".r000001")
            self.assertEqual(region["source_section"], ".text$fo")
            self.assertEqual(region["sha256"], hashlib.sha256(text).hexdigest())
            self.assertEqual([r["type"] for r in region["original_relocations"]], [0x14, 0x06])
            self.assertEqual([r["virtual_address"] for r in region["original_relocations"]], [1, 7])

            machine, optional_size, sections, output_symbols = _read_output(destination)
            self.assertEqual(machine, 0x14C)
            self.assertEqual(optional_size, 0)
            self.assertEqual(len(sections), 1)
            fields, output_raw, output_relocs = sections[0]
            self.assertEqual(fields[0].rstrip(b"\0"), b".r000001")
            self.assertEqual(fields[9] & 0x1000, 0)
            self.assertEqual(output_raw, text)
            self.assertEqual([(r[0], r[2]) for r in output_relocs], [(1, 0x14), (7, 0x06)])
            # Aux records are omitted, and discarded external definitions are
            # declarations for the root linker rather than COMDAT definitions.
            self.assertTrue(all(symbol[-1] == 0 for symbol in output_symbols))
            by_name = {symbol[0]: symbol for symbol in output_symbols}
            self.assertEqual(by_name["??_C@discarded"][2], 0)
            self.assertEqual(by_name["?Bar@@YAXXZ"][2], 0)
            self.assertEqual(by_name["?Foo@@YAXXZ"][2], 1)

    def test_wrong_extent_is_rejected(self):
        with tempfile.TemporaryDirectory() as temporary:
            source = Path(temporary) / "input.obj"
            _make_coff(source, [(".text$foo", b"1234", [], 0x60501020 | 0x1000)], [
                ("?Foo@@YAXXZ", 0, 1, 0x20, 2, []),
            ])
            with self.assertRaisesRegex(CoffRegionError, "extent 4 differs from requested size 5"):
                normalize_object(source, Path(temporary) / "out.obj", [{
                    "symbol": "?Foo@@YAXXZ", "address": 0x401000, "size": 5,
                }])

    def test_multiple_comdats_with_same_static_text_symbol_are_split(self):
        with tempfile.TemporaryDirectory() as temporary:
            source = Path(temporary) / "input.obj"
            _make_coff(source, [
                (".text", b"AAAA", [], 0x60501020 | 0x1000),
                (".text", b"BBBBB", [], 0x60501020 | 0x1000),
            ], [
                # This is the layout produced by MSVC /Gy: every COMDAT has
                # its own local section symbol with the same spelling.
                (".text", 0, 1, 0, 3, []),
                ("?First@@YAXXZ", 0, 1, 0x20, 2, []),
                (".text", 0, 2, 0, 3, []),
                ("?Second@@YAXXZ", 0, 2, 0x20, 2, []),
            ])
            report = normalize_object(source, Path(temporary) / "out.obj", [
                {"symbol": "?First@@YAXXZ", "address": 0x401000, "size": 4},
                {"symbol": "?Second@@YAXXZ", "address": 0x401004, "size": 5},
            ])
            self.assertEqual([r["section"] for r in report["regions"]], [".r000001", ".r000002"])
            _, _, sections, symbols = _read_output(Path(temporary) / "out.obj")
            self.assertEqual([s[0][0].rstrip(b"\0").decode("ascii") for s in sections], [".r000001", ".r000002"])
            self.assertEqual([s[1] for s in sections], [b"AAAA", b"BBBBB"])
            section_symbols = [s for s in symbols if s[3] == 0 and s[4] == 3]
            self.assertEqual({s[0] for s in section_symbols}, {".r000001", ".r000002"})
            self.assertEqual({s[2] for s in section_symbols}, {1, 2})

    def test_ambiguous_decorated_definitions_are_rejected(self):
        with tempfile.TemporaryDirectory() as temporary:
            source = Path(temporary) / "input.obj"
            _make_coff(source, [
                (".text$a", b"a", [], 0x60501020 | 0x1000),
                (".text$b", b"b", [], 0x60501020 | 0x1000),
            ], [
                ("?Foo@@YAXXZ", 0, 1, 0x20, 2, []),
                ("?Foo@@YAXXZ", 0, 2, 0x20, 2, []),
            ])
            with self.assertRaisesRegex(CoffRegionError, "ambiguous definitions"):
                normalize_object(source, Path(temporary) / "out.obj", [{
                    "symbol": "?Foo@@YAXXZ", "address": 0x401000, "size": 1,
                }])

    def test_discarded_local_relocation_requires_explicit_binding(self):
        with tempfile.TemporaryDirectory() as temporary:
            source = Path(temporary) / "input.obj"
            _make_coff(source, [
                (".text$foo", b"\0\0\0\0", [(0, 1, 0x06)], 0x60501020 | 0x1000),
                (".rdata$local", b"DATA", [], 0x40501040 | 0x1000),
            ], [
                ("?Foo@@YAXXZ", 0, 1, 0x20, 2, []),
                ("local_constant", 0, 2, 0, 3, []),
            ])
            with self.assertRaisesRegex(CoffRegionError, "local symbol"):
                normalize_object(source, Path(temporary) / "out.obj", [{
                    "symbol": "?Foo@@YAXXZ", "address": 0x401000, "size": 4,
                }])
            report = normalize_object(source, Path(temporary) / "bound.obj", [{
                "symbol": "?Foo@@YAXXZ", "address": 0x401000, "size": 4,
            }], bindings={"local_constant": "_retail_local_constant"})
            self.assertEqual(report["selected_section_count"], 1)
            symbols = _read_output(Path(temporary) / "bound.obj")[3]
            self.assertIn("_retail_local_constant", {symbol[0] for symbol in symbols})


if __name__ == "__main__":
    unittest.main()
