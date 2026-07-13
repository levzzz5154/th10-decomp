#!/usr/bin/env python3
"""Matching decompilation build script for TH10.
Uses MSVC 7.1 (Visual C++ Toolkit 2003) via Wine.
Compiles individual .cpp files to .obj and compares against original.
"""

import os
import subprocess
import sys
import struct
import hashlib

WINE = "wine"
CL_EXE = os.path.expanduser(
    "~/.wine/drive_c/Program Files (x86)/Microsoft Visual C++ Toolkit 2003/bin/cl.exe"
)
LINK_EXE = os.path.expanduser(
    "~/.wine/drive_c/Program Files (x86)/Microsoft Visual C++ Toolkit 2003/bin/link.exe"
)
LIBCMT = os.path.expanduser(
    "~/.wine/drive_c/Program Files (x86)/Microsoft Visual C++ Toolkit 2003/lib/libcmt.lib"
)

PROJECT_ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
SRC_DIR = os.path.join(PROJECT_ROOT, "src")
INCLUDE_DIR = os.path.join(PROJECT_ROOT, "include")
BUILD_DIR = os.path.join(PROJECT_ROOT, "build")
ORIG_EXE = "/home/levzzz/Games/TH10 - Mountain of Faith/th10.exe"

CFLAGS = "/nologo /c /O2 /Gd /MT /Gy /G6 /Gz"

def cl_compile(cpp_file, obj_file=None, asm_file=None):
    """Compile a single .cpp file with MSVC 7.1."""
    if obj_file is None:
        base = os.path.splitext(os.path.basename(cpp_file))[0]
        obj_file = os.path.join(BUILD_DIR, base + ".obj")
    if asm_file is None:
        base = os.path.splitext(os.path.basename(cpp_file))[0]
        asm_file = os.path.join(BUILD_DIR, base + ".asm")

    wine_path = cpp_file.replace("/", "\\\\")

    cmd = [
        WINE, CL_EXE,
        CFLAGS,
        f"/I{INCLUDE_DIR.replace('/', '\\\\')}",
        f"/Fo{obj_file.replace('/', '\\\\')}",
        f"/FAsc",
        f"/Fa{asm_file.replace('/', '\\\\')}",
        wine_path
    ]

    result = subprocess.run(cmd, capture_output=True, text=True,
                           cwd=BUILD_DIR,
                           env={**os.environ, "WINEDEBUG": "-all"})
    if result.returncode != 0:
        print(f"CL ERROR: {result.stderr}")
        return False
    return obj_file

def hash_file(path):
    """Compute MD5 of file contents."""
    with open(path, 'rb') as f:
        return hashlib.md5(f.read()).hexdigest()

def compare_bytes(our_bin, original_offset, original_size):
    """Compare our compiled bytes against original binary section."""
    with open(ORIG_EXE, 'rb') as f:
        f.seek(original_offset)
        original = f.read(original_size)

    with open(our_bin, 'rb') as f:
        ours = f.read()

    matches = sum(1 for a, b in zip(original, ours) if a == b)
    total = max(len(original), len(ours))
    similarity = (matches / total) * 100 if total > 0 else 0
    return similarity, matches, total

def extract_code_section():
    """Extract .text section from original EXE."""
    os.makedirs(BUILD_DIR, exist_ok=True)
    with open(ORIG_EXE, 'rb') as f:
        f.read(0x3C)
        pe_offset = struct.unpack('<I', f.read(4))[0]
        f.seek(pe_offset)
        pe_sig = f.read(4)
        if pe_sig != b'PE\x00\x00':
            raise ValueError("Not a valid PE file")
        file_header = f.read(20)
        num_sections = struct.unpack('<H', file_header[2:4])[0]
        opt_header_size = struct.unpack('<H', file_header[16:18])[0]
        f.read(opt_header_size)
        for i in range(num_sections):
            name = f.read(8).rstrip(b'\x00')
            vsize = struct.unpack('<I', f.read(4))[0]
            vaddr = struct.unpack('<I', f.read(4))[0]
            raw_size = struct.unpack('<I', f.read(4))[0]
            raw_offset = struct.unpack('<I', f.read(4))[0]
            f.read(16)
            if name == b'.text':
                f.seek(raw_offset)
                data = f.read(raw_size)
                return data, vaddr, vaddr + vsize
    raise ValueError("No .text section found")

def unlink(pe_offset, pe_file):
    """Read function code given PE virtual address."""
    with open(pe_file, 'rb') as f:
        pass

if __name__ == "__main__":
    os.makedirs(BUILD_DIR, exist_ok=True)
    if len(sys.argv) < 2:
        print("Usage: build.py <source.cpp>")
        sys.exit(0)
    
    cpp_file = sys.argv[1]
    obj = cl_compile(cpp_file)
    if obj:
        print(f"Compiled: {obj}")
