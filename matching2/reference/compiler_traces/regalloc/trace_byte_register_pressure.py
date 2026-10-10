# usage: C2_SYMS=syms.json C2_CANDS=37,38 trace_byte_register_pressure.py cmds.json out.txt [event limit]
# Before a global candidate gets its register, c2 walks every tuple of its
# lifetime (routine at 0x107AA78F in the loaded c2.dll, called from the
# allocation driver just before ChoosePhysReg).  At a tuple that names another
# candidate which still has no register and carries the byte-register flag
# (0x80 in the byte at candidate+5), it compares
#     need = byte-flagged candidates holding a register here (a24) + that operand (a34)
# with have - 1, where have = 4 byte registers.  On equality the candidate is
# restricted to ESI/EDI/EBP (SbvAnd with the set at 0x108B205C).
# This prints one row per tuple for the candidates listed in C2_CANDS with
# those counters and the tuple's operand lists (list at +0x2C, then +0x28).
# Candidate numbers are the ones trace_choose_physreg.py prints.
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
WANT=set(int(x) for x in os.environ.get('C2_CANDS','').split(',') if x)
gdb.execute('hbreak *0x107aa5a6')
gdb.execute('hbreak *0x107aac16')
for event in range(LIMIT):
    try: gdb.execute('continue')
    except gdb.error: break
    try:
        r = lambda n: int(gdb.parse_and_eval('$'+n)) & 0xffffffff
        pc=r('pc'); esp=r('esp')
        if pc==0x107aac16:
            c=u32(esp+0x20); out.write('CHOOSE num=%d reg=%d prio=%d\n'%(u32(c+0x1c),u32(esp+0x10),s32(c+0xc)))
        else:
            c=u32(esp+0x88); t=u32(esp+0x20)
            if u32(c+0x1c) in WANT:
                for nm,off in (('S',0x2c),('D',0x28)):
                    o=u32(t+off)
                    while o:
                        d='    %s op=%x kind=%d f14=%08x'%(nm,o,u32(o+8)&0xff,u32(o+0x14))
                        if u32(o+8)&0xff==1:
                            g=u32(o+0x1c)
                            try: d+=' cand=%x ckind=%d cf5=%02x num=%d prio=%d reg10=%x sym=%x'%(g,u32(g+4)&0xff,(u32(g+4)>>8)&0xff,u32(g+0x1c),s32(g+0xc),u32(g+0x10),u32(g))
                            except Exception as e: d+=' ?'
                        out.write(d+'\n'); o=u32(o)
                out.write('  T cand=%d op=%x src=%d dst=%d a24=%d a38=%d a54=%d f50=%d a58=%d a70=%d ebx=%d a28=%d a34=%d lim=%d [%s]\n'%(u32(c+0x1c),u32(t+4),u32(esp+0x1c),u32(esp+0x30),u32(esp+0x24),u32(esp+0x38),u32(esp+0x54),u32(esp+0x50),u32(esp+0x58),u32(esp+0x70),r('ebx'),u32(esp+0x28),u32(esp+0x34),u32(esp+0x9c),raw(t,0x30)))
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
