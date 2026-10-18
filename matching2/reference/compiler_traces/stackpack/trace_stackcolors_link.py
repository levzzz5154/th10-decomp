#!/usr/bin/env python3
"""Trace stack-slot colours in an actual MSVC 13.10.6030 LTCG link.

Usage: trace_stackcolors_link.py commands.json output.txt [function_substring]
Accepts prepare.py's [working-directory, wine, executable, ...] commands or
commands with the leading wine removed. Only the final /LTCG link is replayed.
Reports per-function elements, conflict sets, weights, colour assignments and
allocation order. Compiler breakpoints are diagnostic; emitted bodies are not
modified or selected as recovery output.
"""
import hashlib
import subprocess, re, sys
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parents[4]))
from matching2.tools.common.wine import DEFAULT_TOOLKIT, compiler_environment, winpath
import json
cmds=json.loads(Path(sys.argv[1]).read_text());out=Path(sys.argv[2]).resolve()
out.parent.mkdir(parents=True, exist_ok=True)
focus=sys.argv[3] if len(sys.argv)>3 else ''
link=next(command for command in reversed(cmds) if '/LTCG' in command)
if hashlib.sha256((DEFAULT_TOOLKIT/'bin/c2.dll').read_bytes()).hexdigest() != '7a6f6d8e4da7b518384ff78f2c41028805d3a1d1a40dc2cc857c391ec81763f5':
    raise RuntimeError('This tracer requires the pinned c2.dll 13.10.6030 binary.')
env=compiler_environment(DEFAULT_TOOLKIT)
args=link[1:]
if args[0]=='wine':args=args[1:]
p = subprocess.Popen(['winedbg', '--gdb', '--no-start', *args], stdout=subprocess.PIPE, stderr=subprocess.STDOUT, text=True, env=env, cwd=link[0] or None)
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
def members(vector):
    indices = []
    node = u32(vector)
    while node:
        indices += [u32(node)+k for k in range(32) if u32(node+8) >> k & 1]
        node = u32(node+4)
    return indices

def dump(why, lo, hi):
    base = u32(0x108a9890)
    out.write('%s lo=%d hi=%d\n' % (why, lo, hi))
    for k in range(lo, hi+1):
        e = base + k*0x1c
        w = [u32(e+o) for o in range(0, 0x1c, 4)]
        out.write('  [%d] %s  size=%d weight=%d ratio=%d\n' % (k, ' '.join('%08x' % x for x in w), w[2], w[3], (w[3]*1000//w[2]) if w[2] else -1))
        out.write('    members=%s\n' % members(w[0]))
    out.flush()
DEBUGSYM = DBGFLAG

def function_name():
    try:
        fn=u32(0x108ab128);p=u32(u32(fn)+4)
        raw=inf.read_memory(p,180).tobytes().split(b'\0')[0]
        if raw and all(32<=x<127 for x in raw):return raw.decode()
        return inf.read_memory(u32(p),180).tobytes().split(b'\0')[0].decode()
    except Exception:return ''
seen_functions=set()
listed_functions=set()

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
# c2.dll is not mapped yet when the debug session attaches, so a breakpoint on
# one of its addresses is parked ("Temporarily disabling breakpoints for
# unloaded shared library") and never re-armed before cl.exe exits.  Wait for
# the module to load before arming.
gdb.execute('set stop-on-solib-events 1')
for _ in range(200):
    try:
        gdb.execute('continue')
    except gdb.error:
        break
    if any('c2.dll' in (m.filename or '') for m in gdb.objfiles()):
        break
gdb.execute('set stop-on-solib-events 0')
gdb.execute('hbreak *0x1076953f')
armed = False; n_alloc = 0; completed = False
for event in range(4000):
    try: gdb.execute('continue')
    except gdb.error:
        completed = not inf.is_valid() or inf.pid == 0 or gdb.selected_thread() is None
        break
    if not inf.is_valid() or inf.pid == 0 or gdb.selected_thread() is None:
        completed = True
        break
    try:
        r = lambda n: int(gdb.parse_and_eval('$'+n)) & 0xffffffff
        pc = r('pc'); esp = r('esp')
        fn_name=function_name()
        if fn_name not in seen_functions:
            out.write('FUNCTION '+repr(fn_name)+'\n');seen_functions.add(fn_name)
        if FOCUS not in fn_name:continue
        if pc == 0x1076953f:
            if not armed:
                for a in (0x10768ce7, 0x1072f38a, 0x10768dba, 0x10768df7, 0x10768f40, 0x10768f45): gdb.execute('break *0x%x' % a)
                armed = True
            if fn_name not in listed_functions:
                listed_functions.add(fn_name)
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
        elif pc in (0x10768dba, 0x10768df7):
            # Snapshot the complete records around the optional unstable sort.
            # Keep every record word and its member indices to track equal keys.
            dump('PRESORT' if pc == 0x10768dba else 'POSTSORT', 0, u32(0x108a988c)-1)
        elif pc == 0x10768f45:
            out.write('ALLOCATED offset=%d colour=%d\n' % (r('eax'), r('esi')//0x1c))
        elif pc == 0x10768f40:
            out.write('ALLOTEMP ecx(size)=%d esi/0x1c=%d\n' % (r('ecx'), r('esi')//0x1c)); n_alloc += 1
        out.flush()
    except Exception as e:
        out.write('ERR %r\n' % (e,)); out.flush()
out.write('TRACE completed=%s allocated_colours=%d\n' % (str(completed).lower(), n_alloc))
out.close()
try: gdb.execute('kill')
except gdb.error: pass
gdb.execute('quit')
""".replace('DBGFLAG', 'False').replace('FOCUS', repr(focus)).replace('PORT', port).replace('OUTPUT', str(out))
gs = out.with_suffix('.gdb.py'); gs.write_text(script)
r = subprocess.run(['gdb', '-q', '-batch', '-x', str(gs)], capture_output=True, text=True, timeout=900)
out.with_suffix('.gdb.log').write_text(r.stdout + r.stderr)
if p.poll() is None: p.kill()
if not out.exists() or not out.read_text().splitlines()[-1].startswith('TRACE completed=true'):
    raise RuntimeError('Stack trace did not complete; inspect '+str(out.with_suffix('.gdb.log')))
print(out, out.stat().st_size if out.exists() else 'no output')
