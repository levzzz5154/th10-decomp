# usage: trace_spillcosts.py cmds.json out.txt [event limit]
# Replay the last link command recorded by ../scheduler/capture_link.py under
# winedbg and dump c2.dll's (13.10.6030) Spillcosts state once per basic block:
# K, block weight and both candidate lists (number, refs in the block, running
# priority, symbol record).  summarize_spillcosts.py turns it into one line per
# block; immediates rewritten as register candidates are marked with 'i'.
import subprocess, json, re, sys
from pathlib import Path
sys.path.insert(0, '/home/levzzz/Games/th10Decomp')
from matching2.tools.common.wine import DEFAULT_TOOLKIT, compiler_environment
S = Path(sys.argv[2]).resolve().parent
cmds = json.load(open(sys.argv[1])); out = Path(sys.argv[2]).resolve(); limit = int(sys.argv[3]) if len(sys.argv) > 3 else 3000
args = cmds[-1][1:]
env = compiler_environment(DEFAULT_TOOLKIT)
p = subprocess.Popen(['winedbg', '--gdb', '--no-start', *args], stdout=subprocess.PIPE, stderr=subprocess.STDOUT, text=True, env=env, cwd=cmds[-1][0] if False else None)
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
                b=inf.read_memory(x,24).tobytes()
                t=b.split(b'\0')[0]
                if len(t)>=3 and all(32<=ch<127 for ch in t): txt+=' "'+t.decode()+'"'
            except Exception: pass
    d=' '.join('%08x'%x for x in w)+txt
    seen[sy]=d; return d
def cand(c):
    return 'c=%x num=%d refs=%d prio=%d flags=%08x sym=%x {%s}' % (c, u32(c+0x1c), s32(c+0x18), s32(c+0xc), u32(c+4), u32(c), symdesc(u32(c)))
gdb.execute('hbreak *0x107a98ee')
for event in range(LIMIT):
    try: gdb.execute('continue')
    except gdb.error: break
    try:
        r = lambda n: int(gdb.parse_and_eval('$'+n)) & 0xffffffff
        esp = r('esp')
        out.write('BLOCK K=%d weight=%d\n' % (r('eax'), u32(esp+0x24)))
        for nm in ('ebx', 'esi'):
            c = r(nm); k = 0
            while c and k < 40:
                out.write('  %s %s\n' % (nm, cand(c))); c = u32(c+0x14); k += 1
        out.flush()
    except Exception as e:
        out.write('ERR %s\n' % e); out.flush()
out.close()
try: gdb.execute('kill')
except gdb.error: pass
'''.replace('PORT', port).replace('OUTPUT', str(out)).replace('LIMIT', str(limit))
(S / (Path(__file__).stem + '.gdb.py')).write_text(script)
try:
    r = subprocess.run(['gdb', '-q', '-batch', '-x', str(S / (Path(__file__).stem + '.gdb.py'))], capture_output=True, text=True, timeout=900)
    (S / (Path(__file__).stem + '.gdb.log')).write_text(r.stdout + r.stderr)
    print('gdb exit', r.returncode)
finally:
    try: p.wait(timeout=20)
    except Exception: p.kill()
print('lines', len(out.read_text().splitlines()) if out.exists() else 0)
