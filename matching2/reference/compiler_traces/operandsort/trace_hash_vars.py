# usage: trace_hash_vars.py cmds.json out.txt FUNCTION_SUBSTRING
# Logs every global-optimizer hash variable (HshInsertEntry -> SymMakeHashVar) created while c2
# compiles the target: "H <sym id> ecx=.. edx=.. a1=<expr hash> a2=<opcode> ra=<caller>". An
# address expression `X + disp` shows edx=(24b k7 disp) and a2=278. ~35 s per link.
# cmds.json comes from compiler_traces/capture_equivalent.py.
import subprocess, json, re, sys
from pathlib import Path
sys.path.insert(0, '/home/levzzz/Games/th10Decomp')
from matching2.tools.common.wine import DEFAULT_TOOLKIT, compiler_environment
cmds = json.load(open(sys.argv[1])); out = Path(sys.argv[2]).resolve(); target = sys.argv[3]
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
gdb.execute('hbreak *0x1074aee0')
gdb.execute('hbreak *0x1074af10')
def node(n, depth=0):
    if n < 0x10000: return '<%x>' % n
    try:
        op=u32(n+4)&0xffff; kind=u32(n+8)&0xff; h=u32(n+0x10)
    except Exception: return '<bad %x>' % n
    s='(%x k%x' % (op, kind)
    first=u32(n+0x28)
    if kind in (0xd,0xc,0xb,0xe) and first > 0x10000 and depth<4:
        c=first; k=0
        while c > 0x10000 and k<6:
            s+=' '+node(c, depth+1); c=u32(c); k+=1
    else:
        v=u32(n+0x18)
        if kind==2 and v>0x10000:
            s+=' sym#%d/%d' % (u32(v+0x1c), u32(v+4)&0xff)
        elif kind==6:
            bse=u32(n+0x34)
            s+=' mem[' + (node(bse, depth+1) if depth<4 else '?') + '+%x]' % v
        else: s+=' %x' % v
    return s+')'
pending=None
while True:
    try: gdb.execute('continue')
    except gdb.error: break
    try:
        if 'TARGET' not in fname():
            continue
        r = lambda n: int(gdb.parse_and_eval('$'+n)) & 0xffffffff
        pc = r('eip')
        if pc == 0x1074aee0:
            esp=r('esp')
            pending='ecx=%s edx=%s a1=%x a2=%x ra=%x' % (node(r('ecx')), node(r('edx')), u32(esp+4), u32(esp+8), u32(esp))
        else:
            rec=r('eax')
            out.write('H %d %s\n' % (u32(rec+0x1c), pending))
    except Exception as e:
        out.write('ERR %s\n' % e)
out.close()
try: gdb.execute('kill')
except gdb.error: pass
'''.replace('PORT', port).replace('OUTPUT', str(out)).replace('TARGET', target)
(S / 'trace_hsh.gdb.py').write_text(script)
try:
    r = subprocess.run(['gdb', '-q', '-batch', '-x', str(S / 'trace_hsh.gdb.py')], capture_output=True, text=True, timeout=10000)
    (S / 'trace_hsh.gdb.log').write_text(r.stdout + r.stderr)
    print('gdb exit', r.returncode)
finally:
    try: p.wait(timeout=20)
    except Exception: p.kill()
print('lines', len(out.read_text().splitlines()) if out.exists() else 0)
