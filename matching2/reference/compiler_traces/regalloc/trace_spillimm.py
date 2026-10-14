#!/usr/bin/env python3
# usage: trace_spillimm.py cmds.json out.txt
# At c2's SpillImmedBytes, dump the candidate and scan nearby memory for the
# immediate value/byte being materialized, plus the tuple operand lists.
import subprocess, json, re, sys
from pathlib import Path
sys.path.insert(0, '/home/levzzz/Games/th10Decomp')
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
script = r'''import gdb
gdb.execute('set pagination off'); gdb.execute('set confirm off')
gdb.execute('target remote localhost:PORT')
out = open('OUTPUT', 'w')
inf = gdb.selected_inferior()
import struct
gdb.execute('hbreak *0x1076a4b0')
gdb.execute('hbreak *0x107aac16')
def u32(a): return struct.unpack('<I', inf.read_memory(a, 4).tobytes())[0]
def s32(a): return struct.unpack('<i', inf.read_memory(a, 4).tobytes())[0]
def words(a,n=0x10):
    try: return ' '.join('%08x'%u32(a+4*i) for i in range(n))
    except Exception as e: return '?'
r=lambda n: int(gdb.parse_and_eval('$'+n))&0xffffffff
for event in range(3000):
    try: gdb.execute('continue')
    except gdb.error: break
    pc=r('pc'); esp=r('esp')
    if pc==0x107aac16:
        c=u32(esp+0x20)
        out.write('CHOOSE num=%d reg=%d prio=%d\n'%(u32(c+0x1c),u32(esp+0x10),s32(c+0xc)))
        out.flush()
        continue
    c=r('edi')
    out.write('SPILLIMM num=%d prio=%d flags=%08x cand=[%s]\n'%(u32(c+0x1c),s32(c+0xc),u32(c+4),words(c,0x14)))
    out.write('  stack: %s\n'%words(esp+4,0x10))
    out.write('  edi-ref: %s\n'%words(u32(c),0x10) if u32(c)>0x10000 else '  edi: %08x\n'%u32(c))
    # scan candidate-referenced nodes for small immediates
    for off in range(0,0x50,4):
        try: v=u32(c+off)
        except Exception: continue
        if 0x34000000<v<0x36000000:
            out.write('  node@+%x: %s\n'%(off,words(v,0x10)))
    out.flush()
out.close()
try: gdb.execute('kill')
except gdb.error: pass
'''.replace('PORT', port).replace('OUTPUT', str(out))
Path('/tmp/spillimm.gdb.py').write_text(script)
try:
    r = subprocess.run(['gdb', '-q', '-batch', '-x', '/tmp/spillimm.gdb.py'], capture_output=True, text=True, timeout=600)
    Path('/tmp/spillimm.gdb.log').write_text(r.stdout + r.stderr)
    print('gdb exit', r.returncode)
finally:
    try: p.wait(timeout=20)
    except Exception: p.kill()
