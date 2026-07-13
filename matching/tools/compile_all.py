#!/usr/bin/env python3
"""Compile all generated naked asm source files and verify byte match."""

import subprocess, os, re, struct, sys, csv

WINE = "wine"
CL_EXE = os.path.expanduser("~/.wine/drive_c/Program Files (x86)/Microsoft Visual C++ Toolkit 2003/bin/cl.exe")
MATCHING = "/home/levzzz/Games/th10Decomp/matching"
SRC_DIR = os.path.join(MATCHING, "src", "th10")
BUILD_DIR = os.path.join(MATCHING, "build")
ORIG_EXE = "/home/levzzz/Games/TH10 - Mountain of Faith/th10.exe"
IMAGE_BASE = 0x400000
TEXT_RVA = 0x1000
TEXT_RAW = 0x400

os.makedirs(BUILD_DIR, exist_ok=True)

def compile_file(cpp_path):
    """Compile a single .cpp to .obj using MSVC."""
    base = os.path.splitext(os.path.basename(cpp_path))[0]
    obj_path = os.path.join(BUILD_DIR, base + ".obj")
    
    wine_path = "Z:\\\\" + cpp_path.replace("/", "\\\\")
    wine_obj = "Z:\\\\" + obj_path.replace("/", "\\\\")
    
    cmd = [
        WINE, CL_EXE,
        "/nologo", "/c", "/O2", "/Gd", "/MT",
        f"/Fo{wine_obj}",
        wine_path
    ]
    
    result = subprocess.run(cmd, capture_output=True, text=True, timeout=30,
                           cwd=BUILD_DIR,
                           env={**os.environ, "WINEDEBUG": "-all"})
    
    if result.returncode != 0:
        return None, result.stderr
    return obj_path, None

def get_obj_bytes(obj_path):
    """Extract .text section bytes from .obj file."""
    result = subprocess.run(
        ['objdump', '-d', '-j', '.text', obj_path],
        capture_output=True, text=True
    )
    if result.returncode != 0:
        return None
    
    bytes_data = b''
    for line in result.stdout.split('\n'):
        m = re.match(r'\s+[0-9a-f]+:\t((?:[0-9a-f]{2} )+)', line)
        if m:
            hex_str = m.group(1).replace(' ', '')
            bytes_data += bytes.fromhex(hex_str)
    return bytes_data

def read_original_bytes(func_addr, size):
    """Read function bytes from original EXE."""
    rva = func_addr - IMAGE_BASE
    offset = TEXT_RAW + (rva - TEXT_RVA)
    with open(ORIG_EXE, 'rb') as f:
        f.seek(offset)
        return f.read(size)

def compare_bytes(original, ours):
    """Compare two byte arrays, return similarity and detailed diff."""
    min_len = min(len(original), len(ours))
    matches = sum(1 for a, b in zip(original[:min_len], ours[:min_len]) if a == b)
    total = max(len(original), len(ours))
    pct = (matches / total * 100) if total > 0 else 0
    
    # Find first mismatch
    first_diff = None
    for i in range(min_len):
        if original[i] != ours[i]:
            first_diff = i
            break
    
    return {"similarity": pct, "matches": matches, "total": total,
            "first_diff": first_diff, "orig_size": len(original), "our_size": len(ours)}

def main():
    # Read tracking CSV to get function list
    with open(os.path.join(MATCHING, 'tracking.csv')) as f:
        reader = csv.DictReader(f)
        funcs = {r['address']: r for r in reader}
    
    # Find all generated .cpp files
    cpp_files = sorted([f for f in os.listdir(SRC_DIR) if f.endswith('.cpp')])
    print(f"Found {len(cpp_files)} source files to compile\n")
    
    results = []
    matched = 0
    failed = 0
    total_bytes_matched = 0
    total_bytes = 0
    
    for cpp_file in cpp_files:
        cpp_path = os.path.join(SRC_DIR, cpp_file)
        base = os.path.splitext(cpp_file)[0]
        
        # Look up function address from name
        # Name format: FUN_XXXXXXXX or Catch_XXXXXXXX
        addr_str = base.replace('FUN_', '').replace('Catch@', '').replace('_004', '0x004')
        # Better: read from function map
        func_addr = None
        func_size = None
        for addr, info in funcs.items():
            safe = info['name'].replace('@', '_').replace('`', '_').replace("'", "_")
            if safe == base:
                func_addr = int(addr, 16)
                func_size = int(info['size_bytes'])
                break
        
        if func_addr is None:
            print(f"  SKIP {base}: not in tracking CSV")
            continue
        
        # Compile
        obj_path, err = compile_file(cpp_path)
        if err:
            print(f"  FAIL {base}: compile error - {err[:100]}")
            failed += 1
            continue
        
        # Get our bytes
        our_bytes = get_obj_bytes(obj_path)
        if our_bytes is None:
            print(f"  FAIL {base}: couldn't extract obj bytes")
            failed += 1
            continue
        
        # Get original bytes
        orig_bytes = read_original_bytes(func_addr, func_size)
        
        # Compare
        result = compare_bytes(orig_bytes, our_bytes)
        total_bytes_matched += result['matches']
        total_bytes += result['total']
        
        status = "MATCH" if result['similarity'] >= 100 else f"{result['similarity']:.0f}%"
        if result['similarity'] >= 100:
            matched += 1
        else:
            print(f"  PARTIAL {base}: {result['similarity']:.0f}% (match={result['matches']}/{result['total']}, first_diff at +{result['first_diff']}, orig={result['orig_size']}B, ours={result['our_size']}B)")
        
        results.append((base, func_addr, status, result))
    
    # Summary
    total_funcs = len(cpp_files)
    print(f"\n{'='*60}")
    print(f"Results: {matched}/{total_funcs} matched ({matched/total_funcs*100:.1f}%)")
    print(f"Failed: {failed}")
    print(f"Total byte similarity: {total_bytes_matched}/{total_bytes} = {total_bytes_matched/total_bytes*100:.1f}%")

if __name__ == "__main__":
    main()
