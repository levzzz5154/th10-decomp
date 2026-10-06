"""Read and checksum a PE Rich header without assigning product names.

The numeric product identifiers are deliberately retained: compare them with
outputs of a known compiler instead of inferring tool provenance from names.
Usage: python read_rich_header.py executable [executable ...]
"""
import hashlib
import json
import struct
import sys
from pathlib import Path


def rotate_left(value, count):
    count &= 31
    return ((value << count) | (value >> ((32 - count) & 31))) & 0xFFFFFFFF


def read_header(path):
    data = path.read_bytes()
    if data[:2] != b'MZ':
        raise ValueError(f'{path}: not a DOS executable')
    pe_offset = struct.unpack_from('<I', data, 0x3C)[0]
    if data[pe_offset:pe_offset + 4] != b'PE\0\0':
        raise ValueError(f'{path}: missing PE signature')
    rich_offset = data.find(b'Rich', 0x40, pe_offset)
    if rich_offset < 0 or rich_offset + 8 > pe_offset:
        raise ValueError(f'{path}: missing Rich header')
    key = struct.unpack_from('<I', data, rich_offset + 4)[0]
    marker = struct.pack('<I', 0x536E6144 ^ key)
    dans_offset = data.rfind(marker, 0x40, rich_offset)
    if dans_offset < 0 or (rich_offset - dans_offset - 16) % 8:
        raise ValueError(f'{path}: invalid DanS header')
    padding = struct.unpack_from('<III', data, dans_offset + 4)
    if any(word ^ key for word in padding):
        raise ValueError(f'{path}: invalid DanS padding')
    checksum = dans_offset
    for offset, byte in enumerate(data[:dans_offset]):
        if not 0x3C <= offset < 0x40:
            checksum = (checksum + rotate_left(byte, offset)) & 0xFFFFFFFF
    records = []
    for offset in range(dans_offset + 16, rich_offset, 8):
        tag, count = struct.unpack_from('<II', data, offset)
        tag ^= key
        count ^= key
        checksum = (checksum + rotate_left(tag, count)) & 0xFFFFFFFF
        records.append({'product_id': tag >> 16, 'build': tag & 0xFFFF,
                        'count': count})
    if checksum != key:
        raise ValueError(f'{path}: Rich checksum mismatch')
    return {'path': str(path), 'sha256': hashlib.sha256(data).hexdigest(),
            'dans_offset': hex(dans_offset), 'rich_offset': hex(rich_offset),
            'key': hex(key), 'checksum': hex(checksum),
            'checksum_valid': True, 'records': records}


if __name__ == '__main__':
    print(json.dumps([read_header(Path(arg)) for arg in sys.argv[1:]], indent=2))
