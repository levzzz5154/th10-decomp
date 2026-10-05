# usage (repo root): trace_blocks_cl.py source.cpp out.txt
# Compile one source with plain cl /O2 under winedbg+gdb and dump the block and
# instruction lists c2.dll holds at Riscify entry (after register allocation,
# before final branch layout). Raw words are printed so that branch targets
# (block/label pointers) can be followed by eye.
import subprocess, re, sys
from pathlib import Path
sys.path.insert(0, str(Path.cwd()))
from matching2.tools.common.wine import DEFAULT_TOOLKIT, compiler_environment, winpath
src = Path(sys.argv[1]).resolve(); out = Path(sys.argv[2]).resolve()
env = compiler_environment(DEFAULT_TOOLKIT)
args = [str(DEFAULT_TOOLKIT/'bin/cl.exe'), '/nologo', '/c', '/O2', '/Gz', '/MT', '/Gy', '/G6', '/GF', '/GS', '/Zl', '/Fo' + winpath(out.with_suffix('.obj')), winpath(src)]
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
def raw(c, n): return ' '.join('%08x' % u32(c+o) for o in range(0, n, 4))
BPS = EXTRA
gdb.execute('hbreak *0x107ad4fe')
armed = False
for event in range(400):
    try: gdb.execute('continue')
    except gdb.error: break
    try:
        r = lambda n: int(gdb.parse_and_eval('$'+n)) & 0xffffffff
        pc = r('pc'); esp = r('esp')
        if not armed:
            for a in BPS: gdb.execute('break *0x%x' % a)
            armed = True
        if pc != 0x107ad4fe:
            out.write('HIT %s eax=%x ecx=%x edx=%x esi=%x edi=%x stack=[%s]\n' % (BPS.get(pc, hex(pc)), r('eax'), r('ecx'), r('edx'), r('esi'), r('edi'), ' '.join('%x' % u32(esp+o) for o in range(0, 0x20, 4))))
            out.flush(); continue
        fn = u32(esp+4)
        out.write('RISCIFY fn=%x\n' % fn)
        b = u32(u32(fn+8)); nb = 0
        while b and nb < 200:
            out.write(' BLOCK %x: %s\n' % (b, raw(b, 0x40)))
            i = u32(b+0x1c); last = u32(b+0x20); ni = 0
            while i and ni < 200:
                out.write('   I %x op=%x: %s\n' % (i, u32(i+4), raw(i, 0x40)))
                if u32(i+4) < 0x2c0:
                  for off, tag in ((0x28, 'src'), (0x2c, 'dst')):
                    try:
                        o = u32(i+off); no = 0
                        while o > 0x10000 and no < 6:
                            out.write('      %s %x kind=%x: %s\n' % (tag, o, u32(o+8) & 0xff, raw(o, 0x38)))
                            o = u32(o); no += 1
                    except Exception as e: out.write('      operr %r\n' % (e,))
                if i == last: break
                i = u32(i); ni += 1
            b = u32(b); nb += 1
        out.flush()
    except Exception as e:
        out.write('ERR %r\n' % (e,)); out.flush()
out.close()
gdb.execute('kill')
gdb.execute('quit')
'''.replace('PORT', port).replace('OUTPUT', str(out)).replace('EXTRA', sys.argv[3] if len(sys.argv) > 3 else '{}')
gs = out.with_suffix('.gdb.py'); gs.write_text(script)
r = subprocess.run(['gdb', '-q', '-batch', '-x', str(gs)], capture_output=True, text=True, timeout=600)
out.with_suffix('.gdb.log').write_text(r.stdout + r.stderr)
p.kill()
print(out, out.stat().st_size if out.exists() else 'no output')
