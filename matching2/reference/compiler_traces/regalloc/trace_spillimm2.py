#!/usr/bin/env python3
# usage: trace_spillimm2.py cmds.json out.txt
# At SpillImmedBytes for candidate num=5, deep-dump the argument nodes.
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
gdb.execute('hbreak *0x1076a4b0')
def u32(a): return struct.unpack('<I', inf.read_memory(a, 4).tobytes())[0]
def words(a,n=0x14):
    try: return ' '.join('%08x'%u32(a+4*i) for i in range(n))
    except Exception: return '?'
r=lambda n: int(gdb.parse_and_eval('$'+n))&0xffffffff
for event in range(3000):
    try: gdb.execute('continue')
    except gdb.error: break
    c=r('edi')
    if u32(c+0x1c)!=5: continue
    out.write('SPILLIMM num=5 cand=%x\n'%c)
    esp=r('esp')
    for name,a in (('arg1',u32(esp+4)),('arg2',u32(esp+8)),('arg3',u32(esp+0xc)),('arg5',u32(esp+0x14)),('cand+0x14',u32(c+0x14)),('cand+0x18',u32(c+0x18))):
        out.write('  %s @%08x: %s\n'%(name,a,words(a)))
    out.flush()
    break
out.close()
try: gdb.execute('kill')
except gdb.error: pass
'''.replace('PORT', port).replace('OUTPUT', str(out))
Path('/tmp/spillimm2.gdb.py').write_text(script)
try:
    r = subprocess.run(['gdb', '-q', '-batch', '-x', '/tmp/spillimm2.gdb.py'], capture_output=True, text=True, timeout=600)
    Path('/tmp/spillimm2.gdb.log').write_text(r.stdout + r.stderr)
    print('gdb exit', r.returncode)
finally:
    try: p.wait(timeout=20)
    except Exception: p.kill()
