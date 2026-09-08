"""Read COFF function bytes and relocation locations without applying them."""
import struct
from pathlib import Path

def coff_name(raw_name, string_table):
    if raw_name[:4] == b"\0\0\0\0":
        offset = struct.unpack_from("<I", raw_name, 4)[0]
        end = string_table.find(b"\0", offset)
        return string_table[offset:end].decode("ascii")
    return raw_name.rstrip(b"\0").decode("ascii")


def read_coff_function(path, requested_symbol):
    data = Path(path).read_bytes()
    _, section_count, _, symbol_offset, symbol_count, optional_size, _ = \
        struct.unpack_from("<HHIIIHH", data, 0)
    section_table = 20 + optional_size
    sections = []
    for index in range(section_count):
        offset = section_table + index * 40
        fields = struct.unpack_from("<8sIIIIIIHHI", data, offset)
        sections.append({
            "size": fields[3],
            "raw": fields[4],
            "reloc": fields[5],
            "reloc_count": fields[7],
        })

    string_offset = symbol_offset + symbol_count * 18
    string_table = data[string_offset:]
    symbols = []
    index = 0
    while index < symbol_count:
        offset = symbol_offset + index * 18
        raw_name, value, section, symbol_type, storage, aux_count = \
            struct.unpack_from("<8sIhHBB", data, offset)
        symbols.append((coff_name(raw_name, string_table), value, section,
                        symbol_type, storage))
        index += 1 + aux_count

    exact = [symbol for symbol in symbols if symbol[0] == requested_symbol]
    matches = exact or [symbol for symbol in symbols
                        if requested_symbol in symbol[0] and symbol[2] > 0]
    if len(matches) != 1:
        names = ", ".join(symbol[0] for symbol in matches) or "none"
        raise ValueError("symbol must identify exactly one function; matches: " + names)

    name, value, section_number, _, _ = matches[0]
    section = sections[section_number - 1]
    function = data[section["raw"] + value:section["raw"] + section["size"]]

    # Link-time address operands are zero in an object. Ignore those four-byte
    # fields instead of reporting them as source/code-generation mismatches.
    ignored = set()
    for index in range(section["reloc_count"]):
        offset = section["reloc"] + index * 10
        virtual_address, _, relocation_type = struct.unpack_from("<IIH", data, offset)
        if virtual_address >= value and relocation_type in (0x0006, 0x0014):
            start = virtual_address - value
            ignored.update(range(start, start + 4))
    return name, function, ignored


