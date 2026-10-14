#!/usr/bin/env python3
# usage: trace_accum.py cmds.json out.txt [max events]
# Log c2's per-block priority accumulation: at 0x107a991c (eax=candidate,
# edx=block weight) dump candidate num, f18, and the priority delta.
import subprocess, json, re, sys
from pathlib import Path
sys.path.insert(0, '/home/levzzz/Games/th10Decomp')
from matching2.tools.common.wine import DEFAULT_TOOLKIT, compiler_environment
cmds = json.load(open(sys.argv[1])); out = Path(sys.argv[2]).resolve()
limit = int(sys.argv[3]) if len(sys.argv) > 3 else 40000
env = compiler_environment(DEFAULT_TOOLKIT)
p = subprocess.Popen(['winedbg', '--gdb', '--no-start', *cmds[-1][1:]], stdout=subprocess.PIPE, stderr=subprocess.STDOUT, text=True, env=env)
port = None; lines = []
for line in p.stdout:
    lines.append(line)
    m = re.search(r'target remote localhost:(\d+)', line)
    if m: port = m[1]; break
if not port: raise RuntimeError(''.join(lines))
script = r'''import gdb, struct
gdb.execute('set pagination off'); gdb.execute('set confirm off')
gdb.execute('target remote localhost:PORT')
out = open('OUTPUT', 'w')
inf = gdb.selected_inferior()
def u32(a): return struct.unpack('<I', inf.read_memory(a, 4).tobytes())[0]
def s32(a): return struct.unpack('<i', inf.read_memory(a, 4).tobytes())[0]
r=lambda n: int(gdb.parse_and_eval('$'+n))&0xffffffff
gdb.execute('hbreak *0x107a991c')
gdb.execute('hbreak *0x107a9951')
gdb.execute('hbreak *0x107a997e')
for event in range(LIMIT):
    try: gdb.execute('continue')
    except gdb.error: break
    pc=r('pc'); 
    if pc not in (0x107a991c,0x107a9951,0x107a997e): continue
    a=r('eax'); edx=r('edx')
    out.write('%s num=%d f18=%d w=%d prio=%d esi=%d\n'%({0x107a991c:'ADDa',0x107a9951:'ADDb',0x107a997e:'SUB'}[pc],u32(a+0x1c),s32(a+0x18),s32(a+0x40),s32(a+0xc),r('esi')))
out.close()
try: gdb.execute('kill')
except gdb.error: pass
'''.replace('PORT', port).replace('OUTPUT', str(out)).replace('LIMIT', str(limit))
Path('/tmp/accum.gdb.py').write_text(script)
try:
    r = subprocess.run(['gdb', '-q', '-batch', '-x', '/tmp/accum.gdb.py'], capture_output=True, text=True, timeout=900)
    Path('/tmp/accum.gdb.log').write_text(r.stdout + r.stderr)
    print('gdb exit', r.returncode)
finally:
    try: p.wait(timeout=20)
    except Exception: p.kill()
