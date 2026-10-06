"""Read MSVC 13.10.6030 immediate spilling and operand replacement for one function in a real LTCG link.

Usage: trace_target_spill_link.py commands.json output_dir function_substring
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
profile = 'spill'
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
        if k==1:
            symbol=u32(o+0x1c);number=u32(symbol+0x1c)
            return REG.get(number,'v%x@%x'%(number,symbol)) if pc==0x107ad4fe else 'virtual(sym=%x,reg=%x,n=%x)'%(u32(o+0x18),symbol,number)
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
def tuple_list(fn):
    block=u32(u32(fn+8));first=u32(block+0x1c);t=first;records=[];seen=set()
    while t>0x10000 and t not in seen and len(records)<5000:
        seen.add(t);record={'tuple':hex(t),'op':hex(u32(t+4)),'flags':hex(u32(t+8))}
        if u32(t+4)<0x2c0:
            record.update(machine_op=hex(u32(t+0x20)),source=operands(t,0x28),destination=operands(t,0x2c))
        else:
            record['metadata']=[hex(u32(t+o)) for o in range(0x18,0x30,4)]
        if u32(t+4)==0x2f:
            o=u32(t+0x28);types=[]
            for j in range(8):
                if o<0x10000:break
                types.append(dict(kind=u32(o+8)&255,type=u16(o+0xa)&0xfff));o=u32(o)
            record['source_operand_types']=types
        records.append(record);t=u32(t)
    return {'first':hex(first),'truncated':len(records)==5000,'tuples':records}
breakpoints={0x1076a4b0:'CmdSpillImmedBytes',0x1076a4ac:'AfterCmdSpillImmedBytes',0x107a6bb3:'GrgChangeRegToImmed',0x107ad4fe:'Riscify'}
active_spills=[]
for a in breakpoints:gdb.execute('hbreak *0x%x'%a)
completed=False
for event in range(50000):
    try:gdb.execute('continue')
    except gdb.error:completed=True;break
    if not inf.is_valid() or inf.pid==0:completed=True;break
    pc=register('pc')
    if pc not in breakpoints:completed=True;break
    fn=u32(register('esp')+4) if pc==0x107ad4fe else u32(0x108ab128)
    name=name_of(fn)
    if FOCUS not in name:continue
    if pc==0x1076a4b0:active_spills.append((register('esp'),register('edi')))
    if pc==0x1076a4ac:
        if not active_spills or active_spills[-1][0]!=register('esp')+12:continue
        active_spills.pop()
    record={'event':breakpoints[pc],'function':name,'function_descriptor':hex(fn)}
    if pc!=0x107a6bb3:record.update(tuple_list(fn))
    if pc==0x1076a4b0:
        state=register('edi');record['immediate_state']=dict(address=hex(state),number=u32(state+0x1c),symbol=hex(u32(state)))
    if pc==0x107a6bb3:
        stack=register('esp');symbol=register('eax');use=u32(stack+4);op=u32(stack+8);value=u32(symbol+0x28)
        record['replacement']=dict(symbol=hex(symbol),constant_operand=operand(value),use_tuple=hex(use),use_opcode=hex(u32(use+4)),operand=hex(op),operand_kind=u32(op+8)&255,operand_type=u16(op+0xa)&0xfff)
    out.write(json.dumps(record)+'\n');out.flush()
out.write(json.dumps({'trace_completed':completed})+'\n');out.close()
try:gdb.execute('detach')
except gdb.error:pass
'''.replace('PORT', port).replace('OUTPUT', repr(str(output/'events.jsonl'))).replace('FOCUS', repr(focus)).replace('PROFILE',repr(profile))
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
print(json.dumps({'events':len(events)-1,'phases':[x.get('event') for x in events[:-1]],'trace_completed':True}))
