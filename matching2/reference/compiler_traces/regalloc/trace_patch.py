#!/usr/bin/env python3
# usage: trace_patch.py cmds.json out.txt
# At StartChild's selector choose (num=16 prio=117), zero the EBX cost in the
# cost table and continue the link, so the resulting image shows what the
# allocator would do without the 300-cost poison.
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
import struct
gdb.execute('hbreak *0x107aac16')
def u32(a): return struct.unpack('<I', inf.read_memory(a, 4).tobytes())[0]
def s32(a): return struct.unpack('<i', inf.read_memory(a, 4).tobytes())[0]
def w32(a,v): inf.write_memory(a, struct.pack('<i', v))
r=lambda n: int(gdb.parse_and_eval('$'+n))&0xffffffff
patched=0
for event in range(4000):
    try: gdb.execute('continue')
    except gdb.error: break
    pc=r('pc'); esp=r('esp')
    if pc!=0x107aac16: continue
    c=u32(esp+0x20)
    num=u32(c+0x1c); prio=s32(c+0xc)
    out.write('CHOOSE num=%d prio=%d\n'%(num,prio)); out.flush()
    if patched==0 and num==16 and prio==117:
        w32(0x10882678+16, 0)
        out.write('PATCHED EBX cost 300->0 at num=16 choose\n'); out.flush()
        patched=1
    if patched==1 and num==10:
        out.write('num=10 choose costs now\n'); out.flush()
        patched=2
out.close()
try: gdb.execute('kill')
except gdb.error: pass
'''.replace('PORT', port).replace('OUTPUT', str(out))
Path('/tmp/patch.gdb.py').write_text(script)
try:
    r = subprocess.run(['gdb', '-q', '-batch', '-x', '/tmp/patch.gdb.py'], capture_output=True, text=True, timeout=900)
    Path('/tmp/patch.gdb.log').write_text(r.stdout + r.stderr)
    print('gdb exit', r.returncode)
finally:
    try: p.wait(timeout=20)
    except Exception: p.kill()
