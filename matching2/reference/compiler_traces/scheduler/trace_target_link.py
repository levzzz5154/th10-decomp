"""Read MSVC 13.10.6030 scheduling for one function in a real LTCG link.

Usage: trace_target_link.py commands.json output_dir function_substring
The command is replayed with separate PE/MAP outputs. Hardware breakpoints only;
no compiler data, allocation decisions or emitted instructions are changed.
"""
import hashlib
import json
import re
import subprocess
import sys
from pathlib import Path

sys.path.insert(0, str(Path.cwd()))
from matching2.tools.common.wine import DEFAULT_TOOLKIT, compiler_environment, winpath

commands = json.loads(Path(sys.argv[1]).read_text())
output = Path(sys.argv[2]).resolve()
output.mkdir(parents=True, exist_ok=True)
focus = sys.argv[3]
compiler = Path(DEFAULT_TOOLKIT) / 'bin/c2.dll'
assert hashlib.sha256(compiler.read_bytes()).hexdigest() == '7a6f6d8e4da7b518384ff78f2c41028805d3a1d1a40dc2cc857c391ec81763f5'
command = next(c for c in commands if '/BASE:0x400000' in c)
arguments = [('/OUT:' + winpath(output/'trace.exe') if a.startswith('/OUT:') else '/MAP:' + winpath(output/'trace.map') if a.startswith('/MAP:') else a) for a in command[1:]]
(output/'command.json').write_text(json.dumps(['wine', *arguments], indent=2)+'\n')
process = subprocess.Popen(['winedbg', '--gdb', '--no-start', *arguments], stdout=subprocess.PIPE, stderr=subprocess.STDOUT, text=True, env=compiler_environment(DEFAULT_TOOLKIT))
lines = []
port = None
for line in process.stdout:
    lines.append(line)
    match = re.search(r'target remote localhost:(\d+)', line)
    if match:
        port = match[1]
        break
if port is None:
    raise RuntimeError(''.join(lines))

script = r'''
import gdb, json, struct
gdb.execute('set pagination off')
gdb.execute('set confirm off')
gdb.execute('target remote localhost:PORT')
out = open(OUTPUT, 'w')
inf = gdb.selected_inferior()
def u32(p): return struct.unpack('<I', inf.read_memory(p,4).tobytes())[0]
def u16(p): return struct.unpack('<H', inf.read_memory(p,2).tobytes())[0]
def register(n): return int(gdb.parse_and_eval('$'+n)) & 0xffffffff
def name_of(fn):
    try:
        p=u32(u32(fn)+4)
        s=inf.read_memory(p,180).tobytes().split(b'\0')[0]
        if s and all(32<=x<127 for x in s):return s.decode()
        return inf.read_memory(u32(p),180).tobytes().split(b'\0')[0].decode()
    except Exception:return ''
REG={1:'eax',2:'ecx',3:'edx',4:'ebx',5:'esp',6:'ebp',7:'esi',8:'edi'}
def operand(o):
    try:
        k=u32(o+8)&255
        if k==1:return REG.get(u32(u32(o+0x1c)+0x1c),'r?')
        if k==6:
            b=u32(o+0x34);d=struct.unpack('<i',struct.pack('<I',u32(o+0x30)))[0]
            return '[%s%+d]'%(operand(b) if b>0x10000 else 'G',d)
        return 'k%x(%x,%x)'%(k,u32(o+0x18),u32(o+0x1c))
    except Exception:return 'o?'
def operands(t,offset):
    result=[];o=u32(t+offset)
    for j in range(8):
        if o<0x10000:break
        result.append(operand(o));o=u32(o)
    return result
def node(n):
    t=u32(n+0x1c)
    record={'sequence':u16(n+0x36),'priority':u32(n+0x2c),'static_priority':u32(n+0x28),'path':u16(n+0x34),'predecessors':u16(n+0x20),'successors':u16(n+0x22),'tuple':hex(t)}
    if t:
        record.update(op=hex(u32(t+4)),machine_op=hex(u32(t+0x20)),flags=hex(u32(t+8)),source=operands(t,0x28),destination=operands(t,0x2c))
    return record
breakpoints={0x107ad4fe:'Riscify',0x107b0b9b:'Graph',0x107b0527:'Cycle',0x107b08b2:'Pick'}
for a in breakpoints:gdb.execute('hbreak *0x%x'%a)
graph=-1;cycle=0;completed=False
for event in range(50000):
    try:gdb.execute('continue')
    except gdb.error:completed=True;break
    if not inf.is_valid() or inf.pid==0:completed=True;break
    pc=register('pc')
    if pc not in breakpoints:completed=True;break
    fn=u32(register('esp')+4) if pc==0x107ad4fe else u32(0x108ab128)
    name=name_of(fn)
    if FOCUS not in name:continue
    record={'event':breakpoints[pc],'function':name}
    if pc==0x107b0b9b:graph+=1
    elif pc==0x107b0527:
        cycle=register('esi');ready=[];n=u32(0x108aa044)
        for j in range(100):
            if not n:break
            ready.append(node(n));n=u32(n+0x10)
        record['ready']=ready
    elif pc==0x107b08b2:
        n=register('edi');record['node']=node(n);successors=[];d=u32(n+0xc)
        for j in range(100):
            if not d:break
            successors.append({'sequence':u16(u32(d+0xc)+0x36),'latency':u16(d+0x14),'type':hex(u32(d+0x10))});d=u32(d)
        record['successors']=successors
    record.update(graph=graph,cycle=cycle)
    out.write(json.dumps(record)+'\n');out.flush()
out.write(json.dumps({'trace_completed':completed})+'\n');out.close()
try:gdb.execute('detach')
except gdb.error:pass
'''.replace('PORT', port).replace('OUTPUT', repr(str(output/'events.jsonl'))).replace('FOCUS', repr(focus))
(output/'trace.gdb.py').write_text(script)
try:
    result = subprocess.run(['gdb','-q','-batch','-x',str(output/'trace.gdb.py')], capture_output=True, text=True, timeout=600)
    (output/'gdb.log').write_text(result.stdout+result.stderr)
    process.wait(timeout=30)
    if result.returncode or process.returncode:
        raise RuntimeError('Compiler trace failed; inspect logs.')
finally:
    if process.poll() is None:process.terminate()
    (output/'winedbg.log').write_text(''.join(lines))
events=[json.loads(line) for line in (output/'events.jsonl').read_text().splitlines()]
assert events[-1].get('trace_completed')
print(json.dumps({'events':len(events)-1,'graphs':sum(x.get('event')=='Graph' for x in events),'trace_completed':True}))
