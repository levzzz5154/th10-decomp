#!/usr/bin/env python3
"""Compare compiled .obj against original th10.exe bytes."""

import subprocess
import struct
import sys
import os
import re

ORIG_EXE = "/home/levzzz/Games/TH10 - Mountain of Faith/th10.exe"
MATCHING = "/home/levzzz/Games/th10Decomp/matching"
BUILD_DIR = os.path.join(MATCHING, "build")

# .text section: RVA 0x1000, raw offset 0x400
TEXT_RVA = 0x1000
TEXT_RAW = 0x400

def read_original_bytes(func_addr, size):
    """Read function bytes from original EXE."""
    rva = func_addr - 0x400000  # convert virtual to RVA
    offset = TEXT_RAW + (rva - TEXT_RVA)
    with open(ORIG_EXE, 'rb') as f:
        f.seek(offset)
        return f.read(size)

def dump_obj_bytes(obj_path):
    """Extract function bytes from .obj using objdump."""
    result = subprocess.run(
        ['objdump', '-d', '-j', '.text', obj_path],
        capture_output=True, text=True
    )
    if result.returncode != 0:
        return None, result.stderr
    
    # Parse objdump output to extract hex bytes
    lines = result.stdout.split('\n')
    bytes_data = b''
    for line in lines:
        # Match: "   0:\t53                   \tpush   %ebx"
        m = re.match(r'\s+([0-9a-f]+):\t((?:[0-9a-f]{2} )+)', line)
        if m:
            hex_str = m.group(2).replace(' ', '')
            bytes_data += bytes.fromhex(hex_str)
    
    return bytes_data, None

def compare(func_addr, func_size, obj_path):
    """Compare .obj function bytes against original."""
    original = read_original_bytes(func_addr, func_size)
    ours, err = dump_obj_bytes(obj_path)
    
    if err:
        return {"error": err}
    
    if ours is None:
        return {"error": "no bytes extracted"}
    
    # Truncate/pad to same length
    min_len = min(len(original), len(ours))
    matches = sum(1 for a, b in zip(original[:min_len], ours[:min_len]) if a == b)
    total = max(len(original), len(ours))
    similarity = (matches / total * 100) if total > 0 else 0
    
    return {
        "original_size": len(original),
        "our_size": len(ours),
        "matches": matches,
        "total": total,
        "similarity": similarity,
        "original_hex": original.hex(),
        "our_hex": ours.hex(),
    }

if __name__ == "__main__":
    if len(sys.argv) < 4:
        print("Usage: compare.py <func_addr_hex> <func_size> <obj_file>")
        print("Example: compare.py 0x401520 16 build/test.obj")
        sys.exit(1)
    
    addr = int(sys.argv[1], 16)
    size = int(sys.argv[2])
    obj = sys.argv[3]
    
    result = compare(addr, size, obj)
    for k, v in result.items():
        print(f"{k}: {v}")
