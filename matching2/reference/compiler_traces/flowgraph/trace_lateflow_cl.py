# usage (repo root): trace_lateflow_cl.py source.cpp out.txt
# Compile one source with plain cl /O2 under winedbg+gdb and log c2.dll's late
# flow optimisations (tail/head/epilog merges, label coalescing, branch
# retargeting, code motion). The linear tuple list is dumped at
# FgDoLateFlowOpts, FgCodeMotion and MscClean entry.
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
REG = {1:'eax',2:'ecx',3:'edx',4:'ebx',5:'esp',6:'ebp',7:'esi',8:'edi'}
def opnd(o):
    try:
        k = u32(o+8) & 0xff
        if k == 1:
            return REG.get(u32(u32(o+0x1c)+0x1c), 'r?')
        if k == 6:
            b = u32(o+0x34)
            return '[%s%+x]' % (opnd(b) if b > 0x10000 else 'G', struct.unpack('<i', struct.pack('<I', u32(o+0x30)))[0])
        return 'k%x(%x,%x)' % (k, u32(o+0x18), u32(o+0x1c))
    except Exception as e:
        return 'o?'
def opnds(i, off):
    r = []; o = u32(i+off); n = 0
    while o > 0x10000 and n < 5:
        r.append(opnd(o)); o = u32(o); n += 1
    return ','.join(r)
def dump(first, why):
    out.write('DUMP %s\n' % why)
    i = first; n = 0
    while i and n < 400:
        op = u32(i+4)
        if op >= 0x2c0:
            out.write('  %x op=%x %s\n' % (i, op, raw(i+0x18, 0x18)))
        else:
            out.write('  %x op=%x w=%08x dst=%s src=%s\n' % (i, op, u32(i+8), opnds(i, 0x2c), opnds(i, 0x28)))
        i = u32(i); n += 1
    out.flush()
BPS = {0x1079c3f3:'FgDoLateFlowOpts',0x1079c77f:'LateOnce',0x107ae984:'TryCommonTailMerge',0x107ae9f5:'TryCommonHeadMerge',0x10803d67:'TryEpilogMerge',0x107af8da:'TryTailMerge',0x107b37f8:'CrossJumpRemove',0x1079c49d:'AdjustJumpToExitGoto',0x107ae937:'TryHeadMerge',0x107b6aa0:'DoCommonTailMerge',0x10799204:'ReplaceBranchTarget',0x107b7407:'TransferLabelRefs',0x1077dc42:'CoalesceLabel',0x107b016b:'FgCodeMotion',0x107994df:'RemoveJumpToNextInstr',0x107b03a0:'MscClean',0x107ae767:'RemoveRedundantJcc',0x107992d8:'TupRemove',0x107a08f6:'TupMoveBefore',0x107b73cc:'TupMoveRangeBefore',0x10776c37:'DoCommonHeadMerge',0x107970c8:'TupRemoveLabel',0x10789625:'TupRemoveBranch'}
DUMPAT = ('FgDoLateFlowOpts', 'LateOnce', 'FgCodeMotion', 'MscClean')
gdb.execute('hbreak *0x107ad4fe')
first = 0; armed = False
for event in range(3000):
    try: gdb.execute('continue')
    except gdb.error: break
    try:
        r = lambda n: int(gdb.parse_and_eval('$'+n)) & 0xffffffff
        pc = r('pc'); esp = r('esp')
        if pc == 0x107ad4fe:
            fn = u32(esp+4); b = u32(u32(fn+8)); first = u32(b+0x1c)
            out.write('RISCIFY fn=%x first=%x\n' % (fn, first))
            if not armed:
                for a in BPS: gdb.execute('break *0x%x' % a)
                armed = True
            continue
        name = BPS.get(pc, hex(pc))
        out.write('%s eax=%x ecx=%x edx=%x ebx=%x esi=%x edi=%x stack=[%s]\n' % (name, r('eax'), r('ecx'), r('edx'), r('ebx'), r('esi'), r('edi'), ' '.join('%x' % u32(esp+o) for o in range(0, 0x18, 4))))
        if name in DUMPAT and first: dump(first, name)
        out.flush()
    except Exception as e:
        out.write('ERR %r\n' % (e,)); out.flush()
out.close()
gdb.execute('kill')
gdb.execute('quit')
'''.replace('PORT', port).replace('OUTPUT', str(out))
gs = out.with_suffix('.gdb.py'); gs.write_text(script)
r = subprocess.run(['gdb', '-q', '-batch', '-x', str(gs)], capture_output=True, text=True, timeout=900)
out.with_suffix('.gdb.log').write_text(r.stdout + r.stderr)
p.kill()
print(out, out.stat().st_size if out.exists() else 'no output')
