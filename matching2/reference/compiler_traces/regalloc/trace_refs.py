#!/usr/bin/env python3
# usage: trace_refs.py cmds.json out.txt [max events]
# At c2's per-reference walk (0x107a9659): ESI=candidate, EAX=reference value.
import subprocess, json, re, sys
from pathlib import Path
sys.path.insert(0, '/home/levzzz/Games/th10Decomp')
from matching2.tools.common.wine import DEFAULT_TOOLKIT, compiler_environment
cmds = json.load(open(sys.argv[1])); out = Path(sys.argv[2]).resolve()
limit = int(sys.argv[3]) if len(sys.argv) > 3 else 60000
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
gdb.execute('hbreak *0x107a9659')
for event in range(LIMIT):
    try: gdb.execute('continue')
    except gdb.error: break
    out.write('num=%d val=%d\n'%(u32(r('esi')+0x1c),r('eax')))
out.close()
try: gdb.execute('kill')
except gdb.error: pass
'''.replace('PORT', port).replace('OUTPUT', str(out)).replace('LIMIT', str(limit))
Path('/tmp/refs.gdb.py').write_text(script)
try:
    r = subprocess.run(['gdb', '-q', '-batch', '-x', '/tmp/refs.gdb.py'], capture_output=True, text=True, timeout=900)
    Path('/tmp/refs.gdb.log').write_text(r.stdout + r.stderr)
    print('gdb exit', r.returncode)
finally:
    try: p.wait(timeout=20)
    except Exception: p.kill()
