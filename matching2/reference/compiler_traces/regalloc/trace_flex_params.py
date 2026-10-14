#!/usr/bin/env python3
# usage: trace_flex_params.py cmds.json out.txt
# Log c2's LTCG private-convention decisions: every MdmFlexParams entry (0x107adbe0)
# and every MdmAllocateFlexParam call (0x1077fdc4, args: ctx, params, tuple, reg, ...)
# with the register number (1 EAX 2 ECX 3 EDX 4 EBX 6 EBP 7 ESI 8 EDI) and the
# parameter's symbol index; compare two builds' logs to see which function's
# convention changed.  Same cmds.json format as trace_choose_physreg.py.
import subprocess, json, re, sys
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parents[4]))
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
r=lambda n: int(gdb.parse_and_eval('$'+n))&0xffffffff
gdb.execute('hbreak *0x107adbe0')
gdb.execute('hbreak *0x1077fdc4')
gdb.execute('hbreak *0x1077fa47')
gdb.execute('hbreak *0x1073e828')
def bits(st):
    res=[]; n=u32(st) if st else 0
    while n and len(res)<64:
        b=u32(n); w=u32(n+8)
        res+=[b+k for k in range(32) if w>>k&1]; n=u32(n+4)
    return res
def ops(lst):
    res=[]; n=lst
    while n and len(res)<6:
        k=inf.read_memory(n+8,1).tobytes()[0]
        try:
            if k==2: res.append('sym%d'%u32(u32(u32(n+0x18)+8)+0x1c))
            elif k==1: res.append('reg%d'%u32(u32(u32(n+0x1c)+8)+0x1c))
            else: res.append('k%d'%k)
        except Exception: res.append('k%d?'%k)
        n=u32(n)
    return ','.join(res)
for event in range(20000):
    try: gdb.execute('continue')
    except gdb.error: break
    try:
        pc=r('pc'); esp=r('esp')
        if pc==0x1073e828:
            t=r('ebx'); out.write('  DEFER src=[%s] dst=[%s] blocked=%s\n'%(ops(u32(t+0x28)),ops(u32(t+0x2c)),bits(r('eax'))))
        elif pc==0x1077fa47:
            t=r('ebx')
            out.write('  TUPLE op=%x kind=%d f9=%02x src=[%s] dst=[%s]\n'%(u32(t+4),inf.read_memory(t+8,1).tobytes()[0],inf.read_memory(t+9,1).tobytes()[0],ops(u32(t+0x28)),ops(u32(t+0x2c))))
        elif pc==0x107adbe0:
            out.write('FUNC\n')
        else:
            a=[u32(esp+4+4*i) for i in range(6)]
            tup=a[2]
            # source operand of the copy tuple -> symbol -> number at +0x1c / +0x20
            src=u32(tup+0x28); sym=u32(u32(src+0x18)+8) if src else 0
            out.write('ASSIGN reg=%d tuple=%08x sym=%08x symnum=%d late=%d\n'%(a[3],tup,sym,u32(sym+0x1c) if sym else -1,a[5]))
            # every parameter of the function: symbol number, flag bytes +5/+6 and the
            # disqualify byte +0x35 (1 = stays on the stack)
            node=u32(a[1]+0x1c); i=0
            while node and i<12:
                ps=u32(u32(node+0x18)+8)
                fl=inf.read_memory(ps,0x38).tobytes()
                out.write('    param %d sym=%08x num=%d b5=%02x b6=%02x b35=%02x kind=%d\n'%(i,ps,u32(ps+0x1c),fl[5],fl[6],fl[0x35],inf.read_memory(node+8,1).tobytes()[0]))
                node=u32(node); i+=1
        out.flush()
    except Exception as e:
        out.write('ERR %s\n'%e); out.flush()
out.close()
try: gdb.execute('kill')
except gdb.error: pass
'''.replace('PORT', port).replace('OUTPUT', str(out))
gdbpy = out.with_suffix('.gdb.py'); gdbpy.write_text(script)
try:
    r = subprocess.run(['gdb', '-q', '-batch', '-x', str(gdbpy)], capture_output=True, text=True, timeout=900)
    out.with_suffix('.gdb.log').write_text(r.stdout + r.stderr)
finally:
    try: p.wait(timeout=20)
    except Exception: p.kill()
print('lines', len(out.read_text().splitlines()) if out.exists() else 0)
