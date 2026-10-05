# usage: C2_SYMS=syms.json trace_choose_physreg.py cmds.json out.txt [event limit]
# Dump, per function, the register ChoosePhysReg gives each global candidate
# (reg numbers: 1 EAX 2 ECX 3 EDX 4 EBX 6 EBP 7 ESI 8 EDI) and every Spill /
# CmdSpillImmedBytes call with a symbolised return-address chain.  C2_SYMS is
# the address->name JSON built from c2.pdb (optional; raw addresses otherwise).
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
BP={0x1076a4b0:'SpillImmedBytes',0x107b3c97:'Spill',0x107a98ee:'blk',0x107aac16:'choose'}
for a in BP: gdb.execute('hbreak *0x%x'%a)
for event in range(LIMIT):
    try: gdb.execute('continue')
    except gdb.error: break
    try:
        r = lambda n: int(gdb.parse_and_eval('$'+n)) & 0xffffffff
        pc=r('pc'); esp=r('esp')
        if pc==0x107a98ee: out.write('BLOCK\n')
        elif pc==0x107aac16:
            c=u32(esp+0x20)
            # available registers (sparse bit vector at +0x20) and the per-register
            # cost table at 0x10882678 the pick minimises (ties: class order)
            avail=[]; node=u32(u32(c+0x20)) if u32(c+0x20) else 0
            while node:
                avail+=[u32(node)+k for k in range(32) if u32(node+8)>>k&1]; node=u32(node+4)
            costs=' '.join('%d:%d'%(k,s32(0x10882678+4*k)) for k in avail)
            out.write('CHOOSE reg=%d num=%d prio=%d avail=%s costs=%s [%s]\n'%(u32(esp+0x10),u32(c+0x1c),s32(c+0xc),avail,costs,raw(c)))
            # every candidate still limited to one register (it adds its weight to
            # that register's cost for its neighbours): hash table at 0x108827b0
            for bucket in range(0x400):
                g=u32(0x108827b0+4*bucket)
                while g:
                    av=[]; node=u32(u32(g+0x20)) if u32(g+0x20) else 0
                    while node:
                        av+=[u32(node)+k for k in range(32) if u32(node+8)>>k&1]; node=u32(node+4)
                    if s32(g+0x40)>0 or len(av)==1:
                        out.write('    cand num=%d prio=%d f40=%d f38=%x avail=%s sym=%08x flags=%08x\n'%(u32(g+0x1c),s32(g+0xc),s32(g+0x40),u32(g+0x38),av,u32(g),u32(g+4)))
                    g=u32(g+0x30)
        elif pc==0x1076a4b0:
            c=r('edi'); out.write('SPILLIMM num=%d prio=%d [%s] bt: %s\n'%(u32(c+0x1c),s32(c+0xc),raw(c),bt(esp)))
        else:
            c=u32(esp+8); out.write('SPILL num=%d prio=%d [%s] bt: %s\n'%(u32(c+0x1c),s32(c+0xc),raw(c),bt(esp)))
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
