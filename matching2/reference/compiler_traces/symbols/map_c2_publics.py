"""Resolve public symbols through the matching compiler PDB's OMAP.

Usage: map_c2_publics.py c2.pdb output_directory
The PDB is available from the URL below; it remains an ignored build input.
Requires llvm-pdbutil. Neither the compiler nor its PDB is modified.
"""
import bisect
import hashlib
import json
from pathlib import Path
import re
import struct
import subprocess
import sys

URL = 'https://msdl.microsoft.com/download/symbols/c2.pdb/5360F7BDAFB54288A53F1FBE04D639112/c2.pdb'
GUID = '{5360F7BD-AFB5-4288-A53F-1FBE04D63911}'
COMPILER_SHA = '7a6f6d8e4da7b518384ff78f2c41028805d3a1d1a40dc2cc857c391ec81763f5'
pdb = Path(sys.argv[1]).resolve()
output = Path(sys.argv[2]).resolve()
output.mkdir(parents=True, exist_ok=True)

def dump(*args):
    return subprocess.check_output(['llvm-pdbutil', 'dump', *args, str(pdb)], text=True)

publics = dump('-summary', '-publics')
assert 'GUID: ' + GUID in publics and re.search(r'Age:\s+2\b', publics)
headers = dump('-section-headers')
original = headers.split('Original Section Headers', 1)[1]
sections = {int(number): int(rva, 16) for number, rva in re.findall(
    r'SECTION HEADER #(\d+).*?\n\s*([0-9A-F]+) virtual address', original, re.S)}
omap = output / 'omap_from.bin'
subprocess.run(['llvm-pdbutil', 'export', '-stream=10', '-out=' + str(omap), str(pdb)], check=True)
pairs = list(struct.iter_unpack('<II', omap.read_bytes()))
keys = [source for source, destination in pairs]

def translate(rva):
    index = bisect.bisect_right(keys, rva) - 1
    if index < 0:
        return 0
    source, destination = pairs[index]
    return destination + rva - source if destination else 0

symbols = {}
for name, section, offset in re.findall(
        r'S_PUB32[^\n]*`([^`]+)`\s+flags = [^\n]*addr = (\d+):(\d+)', publics):
    if int(section) not in sections:
        continue
    rva = translate(sections[int(section)] + int(offset))
    if rva:
        symbols[hex(0x10700000 + rva)] = name
assert symbols['0x107ad4fe'] == '@Riscify@4'
assert symbols['0x107aab62'] == '@ChoosePhysReg@12'
(output / 'symbols.json').write_text(json.dumps(symbols, indent=2) + '\n')
(output / 'symbol_receipt.json').write_text(json.dumps({
    'url': URL, 'guid': GUID, 'age': 2,
    'pdb_sha256': hashlib.sha256(pdb.read_bytes()).hexdigest(),
    'compiler_sha256': COMPILER_SHA,
    'image_base': '0x10700000', 'omap_from_stream': 10,
    'original_section_rvas': sections, 'mapped_public_addresses': len(symbols),
    'symbols_sha256': hashlib.sha256((output / 'symbols.json').read_bytes()).hexdigest(),
}, indent=2) + '\n')
print(json.dumps({'mapped_public_addresses': len(symbols), 'guid': GUID, 'age': 2}))
