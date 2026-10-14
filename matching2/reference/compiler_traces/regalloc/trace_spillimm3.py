#!/usr/bin/env python3
# usage: trace_spillimm3.py cmds.json out.txt
# At SpillImmedBytes for candidate num=5 in StartChild, walk arg list nodes
# two levels deep looking for small immediates.
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
def words(a,n=0x10):
    try: return ' '.join('%08x'%u32(a+4*i) for i in range(n))
    except Exception: return '?'
r=lambda n: int(gdb.parse_and_eval('$'+n))&0xffffffff
done=False
for event in range(3000):
    try: gdb.execute('continue')
    except gdb.error: break
    c=r('edi')
    if u32(c+0x1c)!=5 or done: continue
    done=True
    out.write('SPILLIMM num=5 cand=%x flags=%08x\n'%(c,u32(c+4)))
    esp=r('esp')
    for name,a in (('arg1',u32(esp+4)),('arg2',u32(esp+8))):
        out.write('%s @%08x\n'%(name,a))
        for i in range(8):
            node=u32(a+0xc*i)
            if not node: break
            out.write('  node %d @%08x: %s\n'%(i,node,words(node)))
            for j in range(4):
                sub=u32(node+4*j)
                if 0x34000000<sub<0x36000000:
                    out.write('    sub@%d %08x: %s\n'%(j,sub,words(sub,6)))
    out.flush()
out.close()
try: gdb.execute('kill')
except gdb.error: pass
'''.replace('PORT', port).replace('OUTPUT', str(out))
Path('/tmp/spillimm3.gdb.py').write_text(script)
try:
    r = subprocess.run(['gdb', '-q', '-batch', '-x', '/tmp/spillimm3.gdb.py'], capture_output=True, text=True, timeout=600)
    Path('/tmp/spillimm3.gdb.log').write_text(r.stdout + r.stderr)
    print('gdb exit', r.returncode)
finally:
    try: p.wait(timeout=20)
    except Exception: p.kill()
