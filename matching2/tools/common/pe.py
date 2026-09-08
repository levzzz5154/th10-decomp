"""Shared x86 PE32 section reader for exact-byte build tools."""
import struct

class PEImage:
    def __init__(self, data):
        self.data = data
        if data[:2] != b"MZ" or len(data) < 64:
            raise ValueError("not a DOS/PE image")
        self.pe = struct.unpack_from("<I", data, 0x3C)[0]
        if data[self.pe:self.pe + 4] != b"PE\0\0":
            raise ValueError("missing PE signature")
        machine, count, self.timestamp, _, _, optional_size, _ = struct.unpack_from(
            "<HHIIIHH", data, self.pe + 4)
        optional = self.pe + 24
        if machine != 0x14C or struct.unpack_from("<H", data, optional)[0] != 0x10B:
            raise ValueError("expected x86 PE32")
        self.image_base = struct.unpack_from("<I", data, optional + 28)[0]
        self.entry = self.image_base + struct.unpack_from("<I", data, optional + 16)[0]
        self.sections = []
        for index in range(count):
            fields = struct.unpack_from("<8sIIIIIIHHI", data, optional + optional_size + index * 40)
            name, virtual_size, rva, size, raw = fields[:5]
            if raw + size > len(data):
                raise ValueError("truncated section")
            self.sections.append({"name": name.rstrip(b"\0").decode("ascii"),
                                  "address": self.image_base + rva,
                                  "virtual_size": virtual_size, "raw_size": size, "raw_offset": raw,
                                  "characteristics": fields[9]})

    def read(self, address, size):
        for section in self.sections:
            offset = address - section["address"]
            if 0 <= offset and offset + size <= section["raw_size"]:
                start = section["raw_offset"] + offset
                return self.data[start:start + size]
        raise ValueError(f"range {address:#x}+{size:#x} is not backed by PE section data")


