# usage: trace_float_loads.py cmds.json out.txt FUNCTION_NAME_SUBSTRING [event limit]
# Log every float memory load (opcode 0x252) that OptHashNode hashes while c2.dll 13.10.6030
# compiles one function: event, base symbol id/kind, node hash, field. The operand with the
# larger hash is loaded first, so this shows which temporary ids decide an fld/fadd order.
# Other functions are skipped 40 breakpoint hits at a time, so a cluster takes about a minute.
# cmds.json comes from ../scheduler/capture_link.py.
import subprocess, json, re, sys
from pathlib import Path
sys.path.insert(0, '/home/levzzz/Games/th10Decomp')
from matching2.tools.common.wine import DEFAULT_TOOLKIT, compiler_environment
S = Path(sys.argv[2]).resolve().parent
cmds = json.load(open(sys.argv[1])); out = Path(sys.argv[2]).resolve(); target = sys.argv[3]; limit = int(sys.argv[4]) if len(sys.argv) > 4 else 3000000
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
    # operator node: +4 opcode word, +8 kind byte, +0x10 hash, +0x18 symbol or
    # constant, +0x28 first child; children are chained through +0.
    op=u32(n+4)&0xffff; kind=u32(n+8)&0xff; h=u32(n+0x10)&0xffff
    s='(%x k%x h%04x' % (op, kind, h)
    first=u32(n+0x28)
    if first and depth<6 and kind not in (2,7,9):
        c=first; k=0
        while c and k<8:
            s+=' '+node(c, depth+1); c=u32(c); k+=1
    else:
        v=u32(n+0x18)
        if kind==2 and v>0x10000:
            s+=' sym#%d/%d' % (u32(v+0x1c), u32(v+4)&0xff)
        else: s+=' %x' % v
    return s+')'
def cstr(a, n=120):
    # Read a C string without crossing into an unmapped page: a 120-byte read
    # near a page end fails although the string itself is readable.
    b=b''
    for i in range(0, n, 8):
        try: chunk=inf.read_memory(a+i, 8).tobytes()
        except Exception:
            chunk=b''
            for j in range(8):
                try: chunk+=inf.read_memory(a+i+j, 1).tobytes()
                except Exception: break
        b+=chunk
        if b'\0' in chunk or len(chunk)<8: break
    return b.split(b'\0')[0]
names={}
fnames={}
def fname():
    # c2 reuses the function record at [0x108ab128] for the next function, so
    # the cache is keyed by the record and the name pointer it holds, and a
    # failed read is not cached (it once hid TrimCircle 0x41DD80 entirely).
    fn=u32(0x108ab128)
    key=(fn, u32(fn) if fn else 0)
    if key not in fnames:
        try:
            pp=u32(key[1]+4)
            s=cstr(pp)
            if s and all(32<=x<127 for x in s): fnames[key]=s.decode()
            else: fnames[key]=cstr(u32(pp)).decode()
        except Exception: return '?'
    return fnames[key]
gdb.execute('hbreak *0x107948bc')
bp=[b for b in gdb.breakpoints()][-1]
# skip quickly through other functions: ignore counts in chunks
for event in range(LIMIT):
    try: gdb.execute('continue')
    except gdb.error: break
    try:
        name=fname()
        if 'TARGET' not in name:
            bp.ignore_count=40
            continue
        n = int(gdb.parse_and_eval('$ecx')) & 0xffffffff
        op=u32(n+4)&0xffff
        if op!=0x252: continue
        base=u32(n+0x34)
        bs=''
        if base>0x10000:
            sy=u32(base+0x18)
            if sy>0x10000: bs='sym#%d/%d' % (u32(sy+0x1c), u32(sy+4)&0xff)
        out.write('%d %s h=%x f=%x\n' % (event, bs, u32(n+0x10), u32(n+0x24))); out.flush()
    except Exception as e:
        out.write('ERR %s\n' % e); out.flush()
out.close()
try: gdb.execute('kill')
except gdb.error: pass
'''.replace('PORT', port).replace('OUTPUT', str(out)).replace('LIMIT', str(limit)).replace('TARGET', target)
(S / (Path(__file__).stem + '.gdb.py')).write_text(script)
try:
    r = subprocess.run(['gdb', '-q', '-batch', '-x', str(S / (Path(__file__).stem + '.gdb.py'))], capture_output=True, text=True, timeout=10000)
    (S / (Path(__file__).stem + '.gdb.log')).write_text(r.stdout + r.stderr)
    print('gdb exit', r.returncode)
finally:
    try: p.wait(timeout=20)
    except Exception: p.kill()
print('lines', len(out.read_text().splitlines()) if out.exists() else 0)
