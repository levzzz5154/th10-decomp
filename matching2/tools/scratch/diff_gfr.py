#!/usr/bin/env python3
"""Diff the compiled PlayerFamiliarRefresh against retail from the newest map."""
import re, struct, subprocess, sys, tempfile, shutil
from pathlib import Path

ROOT = Path('/home/levzzz/Games/th10Decomp')
BUILD = ROOT / 'matching2/build/probe-gfr/clusters/familiar_refresh_00426f70'
ADDR, NATIVE_LEN, RETAIL_LEN = 0x426F70, 2600, 2520
RETAIL_ADDR = 0x426F70

maps = sorted(BUILD.glob('native-*/cluster.map'), key=lambda p: p.stat().st_mtime)
exe = maps[-1].parent / 'cluster.exe'
img = exe.read_bytes()
import re as _re
_entries = []
for _line in maps[-1].read_text().splitlines():
    _m = _re.match(r' 0001:([0-9a-f]+)\s+(\S+)\s+([0-9a-f]+)', _line)
    if _m:
        _entries.append((int(_m.group(3), 16), _m.group(2)))
_entries.sort()
for _i, (_a, _n) in enumerate(_entries):
    if _n == '_PlayerFamiliarRefresh_00426f70@4':
        ADDR = _a
        break
ret = (ROOT / 'matching2/build/oracle/th10.exe').read_bytes()
native = img[512 + (ADDR - 0x401000): 512 + (ADDR - 0x401000) + NATIVE_LEN]
retail = ret[1024 + (RETAIL_ADDR - 0x401000): 1024 + (RETAIL_ADDR - 0x401000) + RETAIL_LEN]

size = int(sys.argv[1]) if len(sys.argv) > 1 else RETAIL_LEN
d = [i for i in range(size) if native[i] != retail[i]]
print(f'first {size} bytes: {len(d)} differ; first at {hex(ADDR + d[0]) if d else "EXACT"}')

objdump = shutil.which('objdump')
def dis(data, addr, n):
    with tempfile.NamedTemporaryFile(delete=False) as f:
        f.write(data[:n]); p = f.name
    r = subprocess.run([objdump, '-D', '-z', '-b', 'binary', '-m', 'i386', '-M', 'intel',
                        '--insn-width=16', f'--adjust-vma={addr:#x}', p],
                       capture_output=True, text=True)
    out = []
    for line in r.stdout.splitlines():
        parts = line.split('\t')
        if len(parts) >= 3 and parts[0].strip().endswith(':'):
            out.append((int(parts[0].strip()[:-1], 16), parts[2].strip()))
    return out

n = int(sys.argv[2]) if len(sys.argv) > 2 else 90
N = dis(native, ADDR, n); R = dis(retail, RETAIL_ADDR, n)
for i in range(min(len(N), len(R))):
    mark = '  ' if N[i][1] == R[i][1] else '!!'
    if mark == '!!' or i >= (len(sys.argv) > 3 and 10**9 or 0):
        print(f'{mark} R {R[i][0]:06x}: {R[i][1]:<46} | N {N[i][0]:06x}: {N[i][1]}')
    else:
        print(f'{mark} R {R[i][0]:06x}: {R[i][1]:<46} | N {N[i][0]:06x}: {N[i][1]}')
