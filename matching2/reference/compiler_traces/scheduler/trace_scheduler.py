# usage: trace_scheduler.py cmds.json out.txt [event limit]
# Replay the last link command recorded by capture_link.py under winedbg and
# dump c2.dll's (13.10.6030) list scheduler: GRAPH per scheduled region, READY
# list per cycle, PICK per chosen node with its successor edges.
# priority = (path + successor count + 32 if load) << 10; ties go to lower seq.
import subprocess, json, re, sys, os
from pathlib import Path
sys.path.insert(0, '/home/levzzz/Games/th10Decomp')
from matching2.tools.common.wine import DEFAULT_TOOLKIT, compiler_environment
S = Path(sys.argv[2]).resolve().parent
cmds = json.load(open(sys.argv[1])); out = Path(sys.argv[2]); limit = int(sys.argv[3]) if len(sys.argv) > 3 else 6000
args = cmds[-1][1:]
env = compiler_environment(DEFAULT_TOOLKIT)
p = subprocess.Popen(['winedbg', '--gdb', '--no-start', *args], stdout=subprocess.PIPE, stderr=subprocess.STDOUT, text=True, env=env)
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
def u16(a): return struct.unpack('<H', inf.read_memory(a, 2).tobytes())[0]
def u8(a): return inf.read_memory(a, 1).tobytes()[0]
def node(n):
    t = u32(n + 0x1c)
    tup = ''
    if t:
        tup = ' '.join('%08x' % u32(t + o) for o in range(0, 0x20, 4))
    return 'n=%x seq=%d prio=%d static=%d path=%d t30=%d pred=%d/%d succ22=%d fl=%02x tup=%x [%s]' % (
        n, u16(n + 0x36), u32(n + 0x2c), u32(n + 0x28), u16(n + 0x34), u32(n + 0x30), u16(n + 0x20), u16(n + 0x24), u16(n + 0x22), u8(n + 0x3c), t, tup)
gdb.execute('hbreak *0x107b08b2')
gdb.execute('hbreak *0x107b0527')
gdb.execute('hbreak *0x107b0b9b')
for event in range(LIMIT):
    try: gdb.execute('continue')
    except gdb.error: break
    try:
        pc = int(gdb.parse_and_eval('$pc')) & 0xffffffff
        if pc == 0x107b0b9b:
            out.write('GRAPH\n')
        elif pc == 0x107b0527:
            esp = int(gdb.parse_and_eval('$esp')) & 0xffffffff
            out.write('CYCLE time=%d\n' % (int(gdb.parse_and_eval('$esi')) & 0xffffffff))
            n = u32(0x108aa044); k = 0
            while n and k < 40:
                out.write('  READY ' + node(n) + '\n'); n = u32(n + 0x10); k += 1
        else:
            n = int(gdb.parse_and_eval('$edi')) & 0xffffffff
            out.write('PICK ' + node(n) + '\n')
            d = u32(n + 0xc); k = 0
            while d and k < 40:
                out.write('    SUCC seq=%d lat=%d type=%08x w16=%04x\n' % (u16(u32(d + 0xc) + 0x36), u16(d + 0x14), u32(d + 0x10), u16(d + 0x16))); d = u32(d); k += 1
        out.flush()
    except Exception as e:
        out.write('ERR %s\n' % e); out.flush()
out.close()
try: gdb.execute('kill')
except gdb.error: pass
'''.replace('PORT', port).replace('OUTPUT', str(out)).replace('LIMIT', str(limit))
(S / 'schtrace.gdb.py').write_text(script)
try:
    r = subprocess.run(['gdb', '-q', '-batch', '-x', str(S / 'schtrace.gdb.py')], capture_output=True, text=True, timeout=900)
    (S / 'schtrace.gdb.log').write_text(r.stdout + r.stderr)
    print('gdb exit', r.returncode)
finally:
    try: p.wait(timeout=20)
    except Exception: p.kill()
print('lines', len(out.read_text().splitlines()) if out.exists() else 0)
