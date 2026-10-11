# usage: trace_operand_sort_full.py cmds.json out.txt [event limit]
# Like trace_operand_sort.py but logs every OptCmpHashVal comparison in order with the full
# 32-bit hashes and memory nodes (base printed), and never follows non-pointer child words.
# cmds.json must be re-captured (scheduler/capture_link.py) after every source change.
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
def node(n, depth=0):
    if n < 0x10000: return '<%x>' % n
    op=u32(n+4)&0xffff; kind=u32(n+8)&0xff; h=u32(n+0x10)
    s='(%x k%x h%08x' % (op, kind, h)
    first=u32(n+0x28)
    if kind in (0xd,0xc,0xb,0xe) and first > 0x10000 and depth<6:
        c=first; k=0
        while c > 0x10000 and k<8:
            s+=' '+node(c, depth+1); c=u32(c); k+=1
    else:
        v=u32(n+0x18)
        if kind==2 and v>0x10000:
            s+=' sym#%d/%d' % (u32(v+0x1c), u32(v+4)&0xff)
        elif kind==6:
            bse=u32(n+0x34)
            s+=' mem base=' + (node(bse, depth+1) if depth<6 else '?') + ' w18=%x' % v
        else: s+=' %x' % v
    return s+')'
seen=set()
gdb.execute('hbreak *0x10795bc5')
for event in range(LIMIT):
    try: gdb.execute('continue')
    except gdb.error: break
    try:
        r = lambda n: int(gdb.parse_and_eval('$'+n)) & 0xffffffff
        a=r('ecx'); b=r('edx')
        line='%s  <>  %s' % (node(a), node(b))
        out.write(line+'\n')
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
