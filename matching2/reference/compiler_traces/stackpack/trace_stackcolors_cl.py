# usage (repo root): trace_stackcolors_cl.py source.cpp out.txt
# Compile one source with plain cl /O2 under winedbg+gdb and dump c2.dll's
# stack packing: every element handed to colorElemental (0x1076953f; size at
# +0x20, weight at +0x38, index at +0x3c), the colour table after each call
# (0x1c-byte records at [0x108a9890], count at [0x108a988c]) and the order in
# which ColorStackElements allocates the colours (allotemp call 0x10768f40).
# LIST lines show the whole element list first; a parameter (kind 5) with
# flag 4 was marked by MdmFlagUnsafeForStackPackParams and shares with nothing.
import subprocess, re, sys
from pathlib import Path
sys.path.insert(0, str(Path.cwd()))
from matching2.tools.common.wine import DEFAULT_TOOLKIT, compiler_environment, winpath
src = Path(sys.argv[1]).resolve(); out = Path(sys.argv[2]).resolve()
env = compiler_environment(DEFAULT_TOOLKIT)
args = [str(DEFAULT_TOOLKIT/'bin/cl.exe'), '/nologo', '/I' + winpath(Path('matching2/msvc/include').resolve()), '/c', '/O2', '/Gz', '/MT', '/Gy', '/G6', '/GF', '/GS', '/Zl', '/Fo' + winpath(out.with_suffix('.obj')), winpath(src)]
p = subprocess.Popen(['winedbg', '--gdb', '--no-start', *args], stdout=subprocess.PIPE, stderr=subprocess.STDOUT, text=True, env=env)
port = None; lines = []
for line in p.stdout:
    lines.append(line)
    m = re.search(r'target remote localhost:(\d+)', line)
    if m: port = m[1]; break
if not port: raise RuntimeError(''.join(lines))
script = r"""import gdb, struct
gdb.execute('set pagination off'); gdb.execute('set confirm off')
gdb.execute('target remote localhost:PORT')
out = open('OUTPUT', 'w')
inf = gdb.selected_inferior()
def u32(a): return struct.unpack('<I', inf.read_memory(a, 4).tobytes())[0]
def dump(why, lo, hi):
    base = u32(0x108a9890)
    out.write('%s lo=%d hi=%d\n' % (why, lo, hi))
    for k in range(lo, hi+1):
        e = base + k*0x1c
        w = [u32(e+o) for o in range(0, 0x1c, 4)]
        out.write('  [%d] %s  size=%d weight=%d ratio=%d\n' % (k, ' '.join('%08x' % x for x in w), w[2], w[3], (w[3]*1000//w[2]) if w[2] else -1))
    out.flush()
DEBUGSYM = DBGFLAG
def name(sym):
    try:
        n = u32(sym+4)
        s = inf.read_memory(n, 24).tobytes().split(bytes(1))[0]
        return s.decode('latin1') if s and all(32 <= c < 127 for c in s) else ''
    except Exception:
        return ''
def colors(why):
    base = u32(0x108a9890); n = u32(0x108a988c)
    out.write('%s ncolors=%d\n' % (why, n))
    for k in range(n):
        e = base + k*0x1c
        w = [u32(e+o) for o in range(0, 0x1c, 4)]
        out.write('  color[%d] size=%d weight=%d class=%d\n' % (k, w[2], w[3], w[6] & 0xff))
    out.flush()
gdb.execute('hbreak *0x1076953f')
armed = False; n_alloc = 0
for event in range(4000):
    try: gdb.execute('continue')
    except gdb.error: break
    try:
        r = lambda n: int(gdb.parse_and_eval('$'+n)) & 0xffffffff
        pc = r('pc'); esp = r('esp')
        if pc == 0x1076953f:
            if not armed:
                for a in (0x10768ce7, 0x1072f38a, 0x10768f40): gdb.execute('break *0x%x' % a)
                armed = True
                # every stack element (params are kind 5; flag 4 = unsafe to share)
                e = u32(0x108a98a4)
                while e:
                    # conflict set: sparse bit vector at [0x108a9894][index], nodes {base, next, bits}
                    conf = []; node = u32(u32(u32(0x108a9894) + 4*u32(e+0x3c)))
                    while node:
                        conf += [u32(node) + k for k in range(32) if u32(node+8) >> k & 1]; node = u32(node+4)
                    out.write('LIST %x kind=%d flags6=%02x index=%d size=%d weight=%d %s conflicts=%s\n' % (e, u32(e+4) & 0xff, (u32(e+4) >> 16) & 0xff, u32(e+0x3c), u32(e+0x20), u32(e+0x38), name(u32(e)) or name(e), conf))
                    e = u32(e+0x30)
            el = u32(esp+4)
            if DEBUGSYM:
                sy = u32(el)
                for o in range(0, 0x70, 4):
                    v = u32(sy+o); s = ''
                    try:
                        if v > 0x10000: s = repr(inf.read_memory(v, 16).tobytes())
                    except Exception: pass
                    out.write('    sym+%02x %08x %s\n' % (o, v, s))
            out.write('ELEMENT %x index=%d size=%d weight=%d sym=%x %s raw=%s\n' % (el, u32(el+0x3c), u32(el+0x20), u32(el+0x38), u32(el), name(u32(el)) or name(el), ' '.join('%08x' % u32(el+o) for o in range(0, 0x40, 4))))
        elif pc in (0x10768ce7, 0x1072f38a):
            out.write('  -> eax=%d\n' % r('eax')); colors('  COLORS')
        elif pc == 0x10768f40:
            out.write('ALLOTEMP ecx(size)=%d esi/0x1c=%d\n' % (r('ecx'), r('esi')//0x1c)); n_alloc += 1
        out.flush()
    except Exception as e:
        out.write('ERR %r\n' % (e,)); out.flush()
out.close()
gdb.execute('kill')
gdb.execute('quit')
""".replace('DBGFLAG', repr(len(sys.argv) > 3)).replace('PORT', port).replace('OUTPUT', str(out))
gs = out.with_suffix('.gdb.py'); gs.write_text(script)
r = subprocess.run(['gdb', '-q', '-batch', '-x', str(gs)], capture_output=True, text=True, timeout=900)
out.with_suffix('.gdb.log').write_text(r.stdout + r.stderr)
p.kill()
print(out, out.stat().st_size if out.exists() else 'no output')
