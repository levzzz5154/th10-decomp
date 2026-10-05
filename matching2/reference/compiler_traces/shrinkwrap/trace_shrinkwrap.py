# usage: trace_shrinkwrap.py cmds.json|source.cpp out.txt [event limit]
# With a .cpp the source is compiled with plain cl /O2 and every function is
# dumped (set MINBLK=0 is implied).
# Dump MscShrinkWrap's per-register save/restore block lists for each
# iteration (SaveRestoreLoc, ExpandSaveLoc, ExpandRestoreLoc) of every function
# compiled after the 196th Spillcosts block; adjust `nb>=196` for other targets.
# Software breakpoints are armed after c2.dll is mapped (first Spillcosts hit).
import subprocess, json, re, sys
from pathlib import Path
sys.path.insert(0, '/home/levzzz/Games/th10Decomp')
from matching2.tools.common.wine import DEFAULT_TOOLKIT, compiler_environment, winpath
import os
S = Path(sys.argv[2]).resolve().parent
out = Path(sys.argv[2]).resolve(); limit = int(sys.argv[3]) if len(sys.argv) > 3 else 3000
if sys.argv[1].endswith('.cpp'):
    cmds = [['', '']]; minblk = 0
    args = [str(DEFAULT_TOOLKIT/'bin/cl.exe'), '/nologo', '/c', '/O2', '/Gz', '/MT', '/Gy', '/G6', '/GF', '/GS', '/Zl', '/Fo' + winpath(out.with_suffix('.obj')), winpath(Path(sys.argv[1]).resolve())]
else:
    cmds = json.load(open(sys.argv[1])); args = cmds[-1][1:]; minblk = int(os.environ.get('MINBLK', '196'))
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
import json
import os
syms=sorted((int(k,16),v) for k,v in json.load(open(os.environ['C2_SYMS'])).items()) if os.environ.get('C2_SYMS') else [(0,'c2')]
import bisect
keys=[k for k,_ in syms]
def sn(a):
    i=bisect.bisect_right(keys,a)-1
    return '%s+%x'%(syms[i][1],a-syms[i][0]) if i>=0 else hex(a)
def raw(c,n=0x50): return ' '.join('%08x' % u32(c+o) for o in range(0, n, 4))
def bt(esp):
    r=[]
    for o in range(0,0x100,4):
        v=u32(esp+o)
        if 0x10701000<=v<0x10868000: r.append(sn(v))
    return ' < '.join(r[:6])
BP={0x107b79b8:'MscShrinkWrap',0x107a98ee:'blk',0x107b9f38:'GatherLiveness',0x107ba66c:'SaveRestoreLoc',0x107baed7:'ExpandSaveLoc',0x107bab89:'ExpandRestoreLoc',0x107ba3fa:'PrepRestoreAirlocks',0x107b9ffa:'Equalize'}
gdb.execute('hbreak *0x107a98ee')
gdb.execute('continue')
for a in BP:
    if a!=0x107a98ee: gdb.execute('break *0x%x'%a)
nb0=1
nb=1;G={}
for event in range(LIMIT):
    try: gdb.execute('continue')
    except gdb.error: break
    try:
        r = lambda n: int(gdb.parse_and_eval('$'+n)) & 0xffffffff
        pc=r('pc'); esp=r('esp')
        if pc==0x107a98ee: nb+=1
        else:
            out.write('%s after %d blocks eax=%x ebx=%x ecx=%x edx=%x esi=%x edi=%x stack=[%s]\n'%(BP[pc],nb,r('eax'),r('ebx'),r('ecx'),r('edx'),r('esi'),r('edi'),' '.join('%x'%u32(esp+o) for o in range(0,0x18,4))))
            def node(n):
                if not n: return '-'
                w=[u32(n+4*i) for i in range(4)]
                d=[]
                for x in w[1:]:
                    try:
                        if x>0x1000000: d.append('blk%d'%struct.unpack('<h',inf.read_memory(x+0xa4,2).tobytes())[0])
                        else: d.append('%x'%x)
                    except Exception: d.append('%x'%x)
                return '{next=%x %s}'%(w[0],' '.join(d))+(node(w[0]) if w[0] else '')
            def arrs(sa,ra):
                for nm,arr in (('save',sa),('restore',ra)):
                    out.write('   %s: %s\n'%(nm,' '.join('r%d=%s'%(i,node(u32(arr+4*i))) for i in range(1,9) if u32(arr+4*i))))
            if pc==0x107ba66c: G['sa']=u32(esp+4);G['ra']=u32(esp+8)
            if pc in (0x107baed7,0x107bab89,0x107ba3fa) and nb>=MINBLK:
                out.write('  reg(ebx)=%d stackreg=%d\n'%(r('ebx'),u32(esp+0x14)))
                arrs(G['sa'],G['ra'])
        out.flush()
    except Exception as e:
        out.write('ERR %s\n' % e); out.flush()
out.close()
try: gdb.execute('kill')
except gdb.error: pass
'''.replace('PORT', port).replace('OUTPUT', str(out)).replace('LIMIT', str(limit)).replace('MINBLK', str(minblk))
(S / (Path(__file__).stem + '.gdb.py')).write_text(script)
try:
    r = subprocess.run(['gdb', '-q', '-batch', '-x', str(S / (Path(__file__).stem + '.gdb.py'))], capture_output=True, text=True, timeout=900)
    (S / (Path(__file__).stem + '.gdb.log')).write_text(r.stdout + r.stderr)
    print('gdb exit', r.returncode)
finally:
    try: p.wait(timeout=20)
    except Exception: p.kill()
print('lines', len(out.read_text().splitlines()) if out.exists() else 0)
