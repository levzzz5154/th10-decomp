#!/usr/bin/env python3
# usage: trace_prio.py cmds.json out.txt
# Find StartChild's descriptor (num=10) and selector (num=16) candidates at the
# first choose, watch their +0x44 weight fields, and log every writer.
import subprocess, json, re, sys
from pathlib import Path
sys.path.insert(0, '/home/levzzz/Games/th10Decomp')
from matching2.tools.common.wine import DEFAULT_TOOLKIT, compiler_environment
cmds = json.load(open(sys.argv[1])); out = Path(sys.argv[2]).resolve()
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
gdb.execute('hbreak *0x107aac16')
# phase 1: run until StartChild's first choose (high-priority candidate)
found=False
for _ in range(200):
    gdb.execute('continue')
    esp=r('esp'); c=u32(esp+0x20)
    if s32(c+0xc)>150 and u32(c+0x1c)==8:
        found=True; break
if not found:
    out.write('StartChild choose not found\n'); out.close(); gdb.execute('kill')
    import sys; sys.exit(0)
out.write('StartChild first choose num=%d prio=%d\n'%(u32(c+0x1c),s32(c+0xc)))
cands={}
for bucket in range(0x400):
    g=u32(0x108827b0+4*bucket)
    while g:
        num=u32(g+0x1c)
        if num in (10,16) and num not in cands:
            cands[num]=g
            out.write('cand num=%d @%08x w=%d prio=%d\n'%(num,g,s32(g+0x44),s32(g+0xc)))
        g=u32(g+0x30)
gdb.execute('delete')
targets=[(a+0x44) for a in cands.values()]
if targets:
    gdb.execute('watch *(int*)%d'%targets[0])
    if len(targets)>1: gdb.execute('watch *(int*)%d'%targets[1])
hits=0
while hits<40:
    try: gdb.execute('continue')
    except gdb.error: break
    pc=r('pc')
    a=int(gdb.parse_and_eval('$_streq',''))if False else None
    out.write('W %08x eip\n'%pc)
    hits+=1
out.close()
try: gdb.execute('kill')
except gdb.error: pass
'''.replace('PORT', port).replace('OUTPUT', str(out))
Path('/tmp/prio.gdb.py').write_text(script)
try:
    r = subprocess.run(['gdb', '-q', '-batch', '-x', '/tmp/prio.gdb.py'], capture_output=True, text=True, timeout=600)
    Path('/tmp/prio.gdb.log').write_text(r.stdout + r.stderr)
    print('gdb exit', r.returncode)
finally:
    try: p.wait(timeout=20)
    except Exception: p.kill()
