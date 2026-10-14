#!/usr/bin/env python3
# usage: trace_candnames.py cmds.json out.txt
# Attach to c2 like trace_choose_physreg.py, but at each ChoosePhysReg dump the
# symbol-object strings of every candidate limited to a single register, so the
# limited candidate can be identified by name.
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
script = r'''import gdb
gdb.execute('set pagination off'); gdb.execute('set confirm off')
gdb.execute('target remote localhost:PORT')
out = open('OUTPUT', 'w')
inf = gdb.selected_inferior()
import struct
gdb.execute('hbreak *0x107aac16')
def u32(a): return struct.unpack('<I', inf.read_memory(a, 4).tobytes())[0]
def s32(a): return struct.unpack('<i', inf.read_memory(a, 4).tobytes())[0]
seen={}
def symdesc(sy):
    if sy in seen: return seen[sy]
    w=[u32(sy+o) for o in range(0,0x60,4)]
    txt=''
    for x in w:
        if 0x1000000<x<0x7fffffff:
            try:
                b=inf.read_memory(x,32).tobytes()
                t=b.split(b'\0')[0]
                if len(t)>=3 and all(32<=ch<127 for ch in t): txt+=' "'+t.decode()+'"'
            except Exception: pass
    d=' '.join('%08x'%x for x in w)+txt
    seen[sy]=d; return d
printed=set()
for event in range(4000):
    try: gdb.execute('continue')
    except gdb.error: break
    pc=int(gdb.parse_and_eval('$pc')) & 0xffffffff
    if pc != 0x107aac16: continue
    esp=int(gdb.parse_and_eval('$esp')) & 0xffffffff
    c=u32(esp+0x20)
    out.write('CHOOSE num=%d prio=%d\n'%(u32(c+0x1c),s32(c+0xc)))
    for bucket in range(0x400):
        g=u32(0x108827b0+4*bucket)
        while g:
            av=[]; node=u32(u32(g+0x20)) if u32(g+0x20) else 0
            while node:
                av+=[u32(node)+k for k in range(32) if u32(node+8)>>k&1]; node=u32(node+4)
            if len(av)==1:
                key=(u32(g),tuple(av))
                if key not in printed:
                    printed.add(key)
                    out.write('  LIMITED num=%d prio=%d f40=%d f38=%x avail=%s sym=%x\n    %s\n'%(u32(g+0x1c),s32(g+0xc),s32(g+0x40),u32(g+0x38),av,u32(g),symdesc(u32(g))))
            g=u32(g+0x30)
    out.flush()
out.close()
try: gdb.execute('kill')
except gdb.error: pass
'''.replace('PORT', port).replace('OUTPUT', str(out))
Path('/tmp/candnames.gdb.py').write_text(script)
try:
    r = subprocess.run(['gdb', '-q', '-batch', '-x', '/tmp/candnames.gdb.py'], capture_output=True, text=True, timeout=600)
    Path('/tmp/candnames.gdb.log').write_text(r.stdout + r.stderr)
    print('gdb exit', r.returncode)
finally:
    try: p.wait(timeout=20)
    except Exception: p.kill()
