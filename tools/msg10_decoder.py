#!/usr/bin/env python3
"""TH10 MSG file full decoder/encoder.

Format (msg10):
  uint32_t    entry_count
  int32_t[entry_count * 2]  entry_offsets (2 int32 per entry)
  then message instructions:
    uint16_t  time
    uint8_t   opcode
    uint8_t   data_length
    uint8_t[data_length]  data (padded to 4 bytes)
"""

import struct
import sys
from dataclasses import dataclass, field

# util_xor(0x77, 7, 16) used for 'm' type text fields
XOR_KEY = 0x77
XOR_STEP1 = 7
XOR_STEP2 = 16

# TH10 message opcode format types
# S = Shift-JIS string (not XOR'd)
# m = XOR-encrypted text
# z = zero-terminated string
# "" = no data / integer
TH10_MSG_FMTS = {
    1: "S", 2: "S", 3: "", 4: "", 5: "",
    7: "", 8: "", 10: "S", 12: "S", 14: "S",
    16: "m", 17: "m", 18: "", 19: "", 20: "",
    21: "", 22: "", 23: "", 25: "S",
}

TH10_MSG_ED_FMTS = {
    0: "", 3: "m", 5: "S", 6: "S", 7: "Sz",
    8: "SSS", 9: "S", 10: "z", 11: "", 12: "z",
    14: "S", 15: "SSS", 16: "SSS", 17: "SSS",
}


def util_xor(data: bytearray, key: int = XOR_KEY, step1: int = XOR_STEP1, step2: int = XOR_STEP2):
    """XOR decrypt/encrypt in-place using ZUN's util_xor."""
    key &= 0xFF
    step1 &= 0xFF
    step2 &= 0xFF
    for i in range(len(data)):
        data[i] ^= key
        key = (key + step1) & 0xFF
        step1 = (step1 + step2) & 0xFF


@dataclass
class MsgInstruction:
    time: int
    opcode: int
    data: bytes = b""
    text: str = ""

    def decode(self, is_ending: bool = False, encoding: str = 'shift-jis') -> str:
        fmts = TH10_MSG_ED_FMTS if is_ending else TH10_MSG_FMTS
        fmt = fmts.get(self.opcode, "")
        if not self.data:
            return str(int.from_bytes(b'', 'little'))

        if 'm' in fmt:
            decrypted = bytearray(self.data)
            util_xor(decrypted)
            self.text = decrypted.decode(encoding, errors='replace')
            return self.text
        elif 'S' in fmt or 'z' in fmt:
            # Count S/z specifiers, split data accordingly
            pass  # handled below

        if not fmt:
            # Unknown opcode, show as raw numbers
            if len(self.data) <= 4:
                val = int.from_bytes(self.data.ljust(4, b'\x00'), 'little', signed=True)
                return str(val)
            return self.data.hex()

        if fmt == "S":
            self.text = self.data.rstrip(b'\x00').decode(encoding, errors='replace')
            return self.text
        elif fmt == "Sz":
            parts = self.data.split(b'\x00', 1)
            s = parts[0].decode(encoding, errors='replace') if parts[0] else ""
            z = int.from_bytes(parts[1].ljust(4, b'\x00')[:4], 'little') if len(parts) > 1 and parts[1] else 0
            return f"{s}, {z}"
        elif fmt == "SSS":
            parts = self.data.split(b'\x00')
            strs = [p.decode(encoding, errors='replace') for p in parts if p]
            return ", ".join(strs)
        elif fmt == "z":
            self.text = self.data.rstrip(b'\x00').decode(encoding, errors='replace')
            return self.text
        elif fmt == "":
            if len(self.data) == 4:
                return str(struct.unpack('<i', self.data)[0])
            elif len(self.data) == 2:
                return str(struct.unpack('<H', self.data)[0])
            elif len(self.data) == 1:
                return str(self.data[0])
            return self.data.hex()

        return self.data.hex()


@dataclass
class MsgEntry:
    index: int
    extra: int
    instructions: list[MsgInstruction] = field(default_factory=list)


def parse_msg(data: bytes, encoding: str = 'shift-jis', is_ending: bool = False) -> list[MsgEntry]:
    """Parse a TH10 .msg file."""
    if len(data) < 4:
        return []
    entry_count = struct.unpack_from('<I', data, 0)[0]
    offset_table = 4
    entry_info_size = entry_count * 2 * 4

    entries = []
    for i in range(entry_count):
        off1 = struct.unpack_from('<i', data, offset_table + i * 8)[0]
        off2 = struct.unpack_from('<i', data, offset_table + i * 8 + 4)[0]
        entries.append(MsgEntry(index=i, extra=off2))

    msg_start = offset_table + entry_info_size
    pos = msg_start
    current_entry_idx = -1

    while pos + 4 <= len(data):
        time_val = struct.unpack_from('<H', data, pos)[0]
        opcode = data[pos + 2]
        length = data[pos + 3]
        pos += 4

        ins = MsgInstruction(time=time_val, opcode=opcode)

        if length > 0 and pos + length <= len(data):
            ins.data = bytes(data[pos:pos + length])
            pos += length

        padded = (length + 3) & ~3
        pos += padded - length

        if ins.time == 0 and ins.opcode == 0:
            current_entry_idx += 1
            if current_entry_idx < entry_count:
                entries[current_entry_idx].instructions.clear()
            continue

        if 0 <= current_entry_idx < entry_count:
            ins.decode(is_ending, encoding)
            entries[current_entry_idx].instructions.append(ins)

    return entries


def dump_msg(data: bytes, encoding: str = 'shift-jis', is_ending: bool = False) -> str:
    lines = []
    entries = parse_msg(data, encoding, is_ending)
    for entry in entries:
        lines.append(f"entry {entry.index} ({entry.extra})")
        current_time = -1
        for ins in entry.instructions:
            if ins.time != current_time:
                current_time = ins.time
                lines.append(f"@{ins.time}")
            text = ins.text or str(ins.data, encoding, errors='replace')
            lines.append(f"\t{ins.opcode};{text}")
        lines.append("")
    return "\n".join(lines)


def decode_msg_file(inpath: str, outpath: str = None, encoding: str = 'shift-jis', is_ending: bool = False):
    with open(inpath, 'rb') as f:
        data = f.read()
    result = dump_msg(data, encoding, is_ending)
    if outpath:
        with open(outpath, 'w', encoding='utf-8') as f:
            f.write(result)
        print(f"Decoded: {inpath} -> {outpath}")
    else:
        print(result)


if __name__ == '__main__':
    import argparse
    ap = argparse.ArgumentParser(description='TH10 MSG decoder')
    ap.add_argument('input', help='Input .msg file')
    ap.add_argument('output', nargs='?', help='Output text file')
    ap.add_argument('-e', '--ending', action='store_true', help='Ending format')
    ap.add_argument('--encoding', default='shift-jis', help='Text encoding (default: shift-jis)')
    args = ap.parse_args()
    decode_msg_file(args.input, args.output, args.encoding, args.ending)
