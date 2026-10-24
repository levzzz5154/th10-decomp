# usage: trace_regalloc_func.py cmds.json out.txt FUNCTION_SUBSTRING [event limit]
# Spillcosts per-block state (K, block weight, both candidate lists with refs and
# running priority) and every ChoosePhysReg pick, only while c2 compiles functions
# whose name contains FUNCTION_SUBSTRING (current function name read from
# 0x108ab128).  cmds.json comes from compiler_traces/capture_equivalent.py.
# Candidate records: number +0x1C, block refs +0x18, priority +0x0C, symbol +0,
# f40 (benefit) +0x40.  Register numbers: 1 EAX 2 ECX 3 EDX 4 EBX 6 EBP 7 ESI 8 EDI.
import subprocess, json, re, sys
from pathlib import Path
sys.path.insert(0, '/home/levzzz/Games/th10Decomp')
from matching2.tools.common.wine import DEFAULT_TOOLKIT, compiler_environment
cmds = json.load(open(sys.argv[1])); out = Path(sys.argv[2]).resolve(); target = sys.argv[3]
limit = int(sys.argv[4]) if len(sys.argv) > 4 else 200000
S = out.parent
args = cmds[-1][1:]
env = compiler_environment(DEFAULT_TOOLKIT)
p = subprocess.Popen(['winedbg', '--gdb', '--no-start', *args], stdout=subprocess.PIPE, stderr=subprocess.STDOUT, text=True, env=env)
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
fnames={}
def fname():
    fn=u32(0x108ab128)
    if fn not in fnames:
        try:
            pp=u32(u32(fn)+4)
            s=inf.read_memory(pp,120).tobytes().split(b'\0')[0]
            if s and all(32<=x<127 for x in s): fnames[fn]=s.decode()
            else: fnames[fn]=inf.read_memory(u32(pp),120).tobytes().split(b'\0')[0].decode()
        except Exception: fnames[fn]='?'
    return fnames[fn]
seen={}
def symname(sy):
    if sy in seen: return seen[sy]
    txt=''
    try:
        for o in range(0,0x60,4):
            x=u32(sy+o)
            if 0x1000000<x<0x7fffffff:
                try:
                    t=inf.read_memory(x,40).tobytes().split(b'\0')[0]
                    if len(t)>=2 and all(32<=ch<127 for ch in t): txt=t.decode(); break
                except Exception: pass
    except Exception: pass
    seen[sy]=txt; return txt
def cand(c):
    sy=u32(c)
    return 'num=%d refs=%d prio=%d f40=%d flags=%08x sym=%x %s' % (u32(c+0x1c), s32(c+0x18), s32(c+0xc), s32(c+0x40), u32(c+4), sy, symname(sy))
gdb.execute('hbreak *0x107a98ee')
gdb.execute('hbreak *0x107aac16')
gdb.execute('hbreak *0x107b3c97')
last=None
for event in range(LIMIT):
    try: gdb.execute('continue')
    except gdb.error: break
    try:
        f=fname()
        if 'TARGET' not in f: continue
        if f != last: out.write('FUNC %s\n' % f); last=f
        r = lambda n: int(gdb.parse_and_eval('$'+n)) & 0xffffffff
        pc=r('pc'); esp=r('esp')
        if pc==0x107a98ee:
            out.write('BLOCK K=%d weight=%d\n' % (r('eax'), u32(esp+0x24)))
            for nm in ('ebx', 'esi'):
                c = r(nm); k = 0
                while c and k < 60:
                    out.write('  %s %s\n' % (nm, cand(c))); c = u32(c+0x14); k += 1
        elif pc==0x107aac16:
            c=u32(esp+0x20)
            avail=[]; node=u32(u32(c+0x20)) if u32(c+0x20) else 0
            while node:
                avail+=[u32(node)+k for k in range(32) if u32(node+8)>>k&1]; node=u32(node+4)
            costs=' '.join('%d:%d'%(k,s32(0x10882678+4*k)) for k in avail)
            out.write('CHOOSE reg=%d %s avail=%s costs=%s\n'%(u32(esp+0x10),cand(c),avail,costs))
        else:
            c=u32(esp+8); out.write('SPILL %s\n'%cand(c))
        out.flush()
    except Exception as e:
        out.write('ERR %s\n' % e); out.flush()
out.close()
try: gdb.execute('kill')
except gdb.error: pass
'''.replace('PORT', port).replace('OUTPUT', str(out)).replace('TARGET', target).replace('LIMIT', str(limit))
(S / (out.stem + '.gdb.py')).write_text(script)
try:
    r = subprocess.run(['gdb', '-q', '-batch', '-x', str(S / (out.stem + '.gdb.py'))], capture_output=True, text=True, timeout=3000)
    (S / (out.stem + '.gdb.log')).write_text(r.stdout + r.stderr)
    print('gdb exit', r.returncode)
finally:
    try: p.wait(timeout=20)
    except Exception: p.kill()
print('lines', len(out.read_text().splitlines()) if out.exists() else 0)
