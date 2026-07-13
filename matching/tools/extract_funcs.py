#!/usr/bin/env python3
"""Extract function boundaries and categorize for matching decomp."""

import json
import subprocess
import struct
import sys

ORIG_EXE = "/home/levzzz/Games/TH10 - Mountain of Faith/th10.exe"
PROJECT = "/home/levzzz/Games/th10Decomp/matching"

def get_ghidra_functions():
    """Get all function addresses from Ghidra MCP via the project file."""
    # We'll parse from the function list we already have
    # For now, manual list
    funcs = {}
    # Read from the list_functions output we already captured
    return funcs

def read_original_text():
    """Read .text section bytes."""
    with open(ORIG_EXE, 'rb') as f:
        pe_off = struct.unpack('<I', f.read()[0x3C:0x40])[0]
        f.seek(pe_off)
        f.read(2)  # machine
        num_sec = struct.unpack('<H', f.read(2))[0]
        f.read(20)  # COFF + size of optional header
        opt_hdr_size = struct.unpack('<H', f.read(2))[0]
        f.read(opt_hdr_size - 2)
        for i in range(num_sec):
            name = f.read(8).split(b'\x00')[0].decode('ascii')
            vsize = struct.unpack('<I', f.read(4))[0]
            vaddr = struct.unpack('<I', f.read(4))[0]
            raw_sz = struct.unpack('<I', f.read(4))[0]
            raw_off = struct.unpack('<I', f.read(4))[0]
            f.read(16)
            if name == '.text':
                pos = f.tell()
                f.seek(raw_off)
                data = f.read(raw_sz)
                f.seek(pos)
                return data, vaddr, raw_off
    return None, 0, 0

def extract_function_bytes(text_data, text_vaddr, func_addr, func_end):
    """Extract raw bytes for a function."""
    offset = func_addr - text_vaddr
    length = func_end - func_addr
    return text_data[offset:offset+length]

# Define function boundaries (from Ghidra list - just some game code examples)
# Format: name -> (start_addr, next_func_addr or end_addr, is_crt)
KNOWN_FUNCTIONS = {
    # Entry / CRT
    "entry": (0x004537DC, 0x004539B0, True),
    "GameMain": (0x00438AD0, 0x004390E0, False),
    
    # Small game functions to start with
    "FUN_0040cf60": (0x0040CF60, 0x0040CF76, False),
    "FUN_0040cf90": (0x0040CF90, 0x0040D280, False),
    
    # CRT (will use libcmt.lib)
    "operator_new": (0x00452493, 0x004524A1, True),
    "operator_delete": (0x00452475, 0x00452493, True),
    "__amsg_exit": (0x0045373D, 0x00453762, True),
    "fast_error_exit": (0x00453762, 0x004537DC, True),
}

if __name__ == "__main__":
    text_data, text_vaddr, _ = read_original_text()
    print(f".text section: vaddr=0x{text_vaddr:08X}, size=0x{len(text_data):X}")
    
    game_funcs = 0
    crt_funcs = 0
    game_bytes = 0
    crt_bytes = 0
    
    for name, (start, end, is_crt) in sorted(KNOWN_FUNCTIONS.items(), key=lambda x: x[1][0]):
        size = end - start
        category = "CRT" if is_crt else "GAME"
        bytes_hex = extract_function_bytes(text_data, text_vaddr, start, end)[:16].hex()
        print(f"0x{start:08X}  {name:28s}  {size:5d}B  {category}  {bytes_hex}")
        if is_crt:
            crt_funcs += 1
            crt_bytes += size
        else:
            game_funcs += 1
            game_bytes += size
    
    print(f"\nGame: {game_funcs} funcs, {game_bytes}B   CRT: {crt_funcs} funcs, {crt_bytes}B")
