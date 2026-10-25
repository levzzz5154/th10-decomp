# usage: trace_riscify.py cmds.json out.txt FUNCTION_NAME_SUBSTRING
# Dump what c2.dll 13.10.6030's Riscify pass sees for one function: at Riscify
# entry every block's instruction list (opcode, register/memory operands), then
# each GetReg call (PrevRegUsed, live set) and the register it returns. Riscify
# walks each block backwards and GetReg is round-robin from PrevRegUsed (reset
# per block), so a scratch register that differs from retail means the
# instruction list or the live set differs. Addresses: see
# reference/recovery_notes/animation_register_004489d0_riscify_2026_10_03.md.
# cmds.json comes from ../capture_equivalent.py or ../scheduler/capture_link.py.
import subprocess, json, re, sys
from pathlib import Path
sys.path.insert(0, '/home/levzzz/Games/th10Decomp')
from matching2.tools.common.wine import DEFAULT_TOOLKIT, compiler_environment
from matching2.tools.common.wine import winpath
cmds = json.load(open(sys.argv[1])); out = Path(sys.argv[2]).resolve(); target = sys.argv[3]
command = next(c for c in cmds if '/BASE:0x400000' in c)
args = [('/OUT:' + winpath(out.with_suffix('.exe')) if a.startswith('/OUT:') else
         '/MAP:' + winpath(out.with_suffix('.map')) if a.startswith('/MAP:') else a) for a in command[1:]]
env = compiler_environment(DEFAULT_TOOLKIT)
p = subprocess.Popen(['winedbg', '--gdb', '--no-start', *args], stdout=subprocess.PIPE, stderr=subprocess.STDOUT,
                     text=True, env=env)
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
def reg(n): return int(gdb.parse_and_eval('$' + n)) & 0xffffffff
REGS = {1:'eax',2:'ecx',3:'edx',4:'ebx',5:'esp',6:'ebp',7:'esi',8:'edi'}
def cstr(a, n=160):
    b = b''
    for i in range(0, n, 8):
        try: chunk = inf.read_memory(a + i, 8).tobytes()
        except Exception:
            chunk = b''
            for j in range(8):
                try: chunk += inf.read_memory(a + i + j, 1).tobytes()
                except Exception: break
        b += chunk
        if b'\0' in chunk or len(chunk) < 8: break
    return b.split(b'\0')[0]
names = {}
def fname():
    fn = u32(0x108ab128)
    key = (fn, u32(fn) if fn else 0)
    if key not in names:
        try:
            pp = u32(key[1] + 4)
            s = cstr(pp)
            if s and all(32 <= x < 127 for x in s): names[key] = s.decode()
            else: names[key] = cstr(u32(pp)).decode()
        except Exception: return '?'
    return names[key]
def raw(a, n=0x40):
    try: return ' '.join('%08x' % x for x in struct.unpack('<%dI' % (n // 4), inf.read_memory(a, n).tobytes()))
    except Exception: return '?'
def s32(x): return struct.unpack('<i', struct.pack('<I', x))[0]
def regname(sym):
    try: r = u32(sym + 0x1c)
    except Exception: return '?'
    return REGS.get(r, 'v%x' % sym)
def operand_list(first):
    # memory operands are followed in the list by their base/index operands
    items = []; o = first; j = 0
    while o > 0x10000 and j < 10:
        try:
            kind = u32(o + 8) & 0xff; code = u32(o + 4)
        except Exception:
            items.append('?'); break
        if kind == 1 or kind == 2: items.append(regname(u32(o + 0x1c)))
        elif kind == 6 or kind == 5:
            items.append('%s[%+d]' % ('&' if kind == 5 else '', s32(u32(o + 0x30))))
        elif kind == 7: items.append('#%x' % u32(o + 0x1c))
        else: items.append('k%x/%x' % (kind, code))
        o = u32(o); j += 1
    return ' '.join(items)
def dump_function(fn, tag):
    first = u32(u32(fn + 8)); blk = first; b = 0
    while blk > 0x10000 and b < 400:
        ins, last = u32(blk + 0x1c), u32(blk + 0x20)
        out.write('%s BLOCK %x\n' % (tag, blk))
        k = 0
        while ins > 0x10000 and k < 600:
            op = u32(ins + 4)
            if op not in (0x2c4, 0x2c5):
                out.write('  %x op=%x  D: %s  S: %s\n' % (ins, op, operand_list(u32(ins + 0x2c)), operand_list(u32(ins + 0x28))))
            if ins == last: break
            ins = u32(ins); k += 1
        blk = u32(blk); b += 1
        if blk == first: break
    out.flush()
gdb.execute('hbreak *0x107ad4fe')
armed = False
for event in range(200000):
    try: gdb.execute('continue')
    except gdb.error: break
    try:
        pc = reg('pc')
    except Exception: break
    if pc not in (0x107ad4fe, 0x107ad5fb, 0x107ad33b, 0x107ad44e): break
    if not armed:
        gdb.execute('delete breakpoints')
        for a in (0x107ad4fe, 0x107ad5fb, 0x107ad33b, 0x107ad44e): gdb.execute('break *0x%x' % a)
        armed = True
    try:
        name = fname()
        if 'TARGET' not in name: continue
        if pc == 0x107ad4fe:
            fn_now = u32(reg('esp') + 4)
            out.write('RISCIFY %s\n' % name); dump_function(fn_now, 'IN')
        elif pc == 0x107ad5fb:
            out.write('RISCIFY_EXIT\n'); dump_function(fn_now, 'OUT')
        elif pc == 0x107ad33b:
            out.write('GETREG prev=%x live=%s regs=%s stack=%s\n' % (u32(0x108b2238), raw(u32(u32(reg('esp') + 4)), 8),
                      ' '.join('%s=%x' % (r, reg(r)) for r in ('ebx', 'esi', 'edi', 'ebp')), raw(reg('esp'), 0x30)))
        elif pc == 0x107ad44e:
            out.write('  -> %d\n' % reg('esi')); out.flush()
    except Exception as e:
        out.write('ERR %s\n' % e); out.flush()
out.close()
try: gdb.execute('kill')
except gdb.error: pass
'''.replace('PORT', port).replace('OUTPUT', str(out)).replace('TARGET', target)
gdb_script = out.with_suffix('.gdb.py')
gdb_script.write_text(script)
try:
    r = subprocess.run(['gdb', '-q', '-batch', '-x', str(gdb_script)], capture_output=True, text=True, timeout=3000)
    out.with_suffix('.gdb.log').write_text(r.stdout + r.stderr)
finally:
    try: p.wait(timeout=20)
    except Exception: p.kill()
print('lines', len(out.read_text().splitlines()) if out.exists() else 0)
