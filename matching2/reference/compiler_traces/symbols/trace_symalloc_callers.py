# usage: trace_symalloc_callers.py cmds.json out.txt FUNCTION_SUBSTRING
# Log every SymAlloc return (record id, kind) while c2 compiles the target function, plus OptCmpHashVal pairs.
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
names = {0x10791df7:'pop', 0x1074a357:'A', 0x1074b88e:'fresh'}
for a in names: gdb.execute('hbreak *0x%x' % a)
gdb.execute('hbreak *0x10795bc5')
bps=[b for b in gdb.breakpoints()]
n=0
while True:
    try: gdb.execute('continue')
    except gdb.error: break
    try:
        if 'TARGET' not in fname():
            continue
        r = lambda n: int(gdb.parse_and_eval('$'+n)) & 0xffffffff
        pc = r('eip')
        if pc == 0x10795bc5:
            a=r('ecx'); b=r('edx')
            def d(x):
                h=u32(x+0x10); k=u32(x+8)&0xff; op=u32(x+4)&0xffff
                v=u32(x+0x18); extra=''
                if k==2 and v>0x10000: extra=' sym#%d' % u32(v+0x1c)
                if k==6:
                    bse=u32(x+0x34)
                    if bse>0x10000 and (u32(bse+8)&0xff)==2:
                        vv=u32(bse+0x18)
                        if vv>0x10000: extra=' base sym#%d' % u32(vv+0x1c)
                return '%x/k%x/h%x%s' % (op,k,h,extra)
            out.write('CMP %s <> %s\n' % (d(a), d(b)))
            continue
        rec = r('eax'); esp=r('esp')
        ra = u32(esp) if pc != 0x1074b88e else u32(esp+8)
        if ra == 0x1074b014: ra = (ra << 0) ; ra2 = u32(esp+8)
        else: ra2 = 0
        out.write('%s %d k%x ra=%x ra2=%x\n' % (names.get(pc,'?'), u32(rec+0x1c) if pc != 0x1074b88e else -1, u32(rec+4)&0xff, ra, ra2))
    except Exception as e:
        out.write('ERR %s\n' % e)
out.close()
try: gdb.execute('kill')
except gdb.error: pass
'''.replace('PORT', port).replace('OUTPUT', str(out)).replace('TARGET', target)
(S / 'trace_symalloc.gdb.py').write_text(script)
try:
    r = subprocess.run(['gdb', '-q', '-batch', '-x', str(S / 'trace_symalloc.gdb.py')], capture_output=True, text=True, timeout=10000)
    (S / 'trace_symalloc.gdb.log').write_text(r.stdout + r.stderr)
    print('gdb exit', r.returncode)
finally:
    try: p.wait(timeout=20)
    except Exception: p.kill()
print('lines', len(out.read_text().splitlines()) if out.exists() else 0)
