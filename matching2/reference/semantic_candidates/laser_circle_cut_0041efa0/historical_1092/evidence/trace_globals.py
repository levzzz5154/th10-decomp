"""Inspect MSVC 13.10 global register allocation for a complete reader.

Usage: python trace_joystick_globals.py commands.json output_dir JoystickReadBindings
Replay an ordinary cl.exe command, redirect its object, read allocation events,
and detach normally. The compiler is fingerprinted. No register decision or
compiler data is changed; debugger code breakpoints are restored on detach.
"""
import hashlib
import json
import re
import subprocess
import sys
from pathlib import Path

sys.path.insert(0, str(next(p for p in Path(__file__).resolve().parents if (p/'matching2/msvc/regions.json').is_file())))
from matching2.tools.common.wine import DEFAULT_TOOLKIT, compiler_environment, winpath

commands = json.loads(Path(sys.argv[1]).read_text())
out = Path(sys.argv[2]).resolve()
out.mkdir(parents=True, exist_ok=True)
focus = sys.argv[3] if len(sys.argv) > 3 else 'JoystickReadBindings'
c2 = Path(DEFAULT_TOOLKIT) / 'bin/c2.dll'
expected = '7a6f6d8e4da7b518384ff78f2c41028805d3a1d1a40dc2cc857c391ec81763f5'
if hashlib.sha256(c2.read_bytes()).hexdigest() != expected:
    raise RuntimeError('The register-allocation offsets require c2.dll 13.10.6030.')
command = next(command for command in commands if '/BASE:0x400000' in command)
args = [('/OUT:' + winpath(out / 'trace.exe') if arg.startswith('/OUT:') else '/MAP:' + winpath(out / 'trace.map') if arg.startswith('/MAP:') else arg) for arg in command[1:]]
(out / 'command.json').write_text(json.dumps(['wine', *args], indent=2) + '\n')
process = subprocess.Popen(
    ['winedbg', '--gdb', '--no-start', *args], stdout=subprocess.PIPE,
    stderr=subprocess.STDOUT, text=True, env=compiler_environment(DEFAULT_TOOLKIT))
lines = []
port = None
for line in process.stdout:
    lines.append(line)
    match = re.search(r'target remote localhost:(\d+)', line)
    if match:
        port = match[1]
        break
if not port:
    raise RuntimeError(''.join(lines))

script = r'''
import gdb, json, struct
gdb.execute('set pagination off')
gdb.execute('set confirm off')
gdb.execute('target remote localhost:PORT')
out = open(OUTPUT, 'w')
inf = gdb.selected_inferior()
def u32(address):
    return struct.unpack('<I', inf.read_memory(address, 4).tobytes())[0]
def register(name):
    return int(gdb.parse_and_eval('$' + name)) & 0xffffffff
def function_name(function):
    try:
        pointer = u32(u32(function) + 4)
        name = inf.read_memory(pointer, 180).tobytes().split(b'\0')[0]
        if name and all(32 <= byte < 127 for byte in name):
            return name.decode()
        pointer = u32(pointer)
        return inf.read_memory(pointer, 180).tobytes().split(b'\0')[0].decode()
    except Exception:
        return ''
def following_store(instruction):
    stores = []
    for step in range(1):
        instruction = u32(instruction)
        if not instruction:
            break
        if u32(instruction + 4) != 1:
            continue
        destination = u32(instruction + 0x2c)
        if destination and u32(destination + 8) & 255 == 6:
            stores.append(hex(u32(destination + 0x30)))
    return stores
def memory_displacements(instruction, operand_offset):
    displacements = []
    operand = u32(instruction + operand_offset)
    for step in range(8):
        if operand < 0x10000:
            break
        if u32(operand + 8) & 255 == 6:
            displacements.append(hex(u32(operand + 0x30)))
        operand = u32(operand)
    return displacements
breakpoints = {0x107aac16: 'ChoosePhysReg', 0x107b3c97: 'Spill', 0x1076a4b0: 'SpillImmedBytes', 0x107ad4fe: 'Riscify'}
def raw(pointer, size=0x60):
    return [hex(u32(pointer+offset)) for offset in range(0,size,4)]
def signed(pointer):
    return struct.unpack('<i', inf.read_memory(pointer, 4).tobytes())[0]
def available(candidate):
    node = u32(u32(candidate + 0x20)) if u32(candidate + 0x20) else 0
    values=[]
    while node:
        values += [u32(node)+k for k in range(32) if u32(node+8)>>k&1]
        node=u32(node+4)
    return values
def describe(candidate):
    source=u32(candidate)
    names=[]
    words=raw(source)
    for word in words:
        value=int(word,16)
        if value<0x10000:continue
        try:
            data=inf.read_memory(value,64).tobytes().split(b'\0')[0]
            if len(data)>=3 and all(32<=x<127 for x in data):names.append(data.decode())
            for offset in [0,4]:
                pointer=u32(value+offset)
                if pointer<0x10000:continue
                try:
                    data=inf.read_memory(pointer,100).tobytes().split(b'\0')[0]
                    if len(data)>=3 and all(32<=x<127 for x in data):names.append(data.decode())
                except gdb.MemoryError:pass
        except gdb.MemoryError:pass
    return dict(number=u32(candidate+0x1c),priority=signed(candidate+0xc),refs=signed(candidate+0x18),
                source=hex(source),source_words=words,names=names,available=available(candidate),words=raw(candidate))
for address in breakpoints:gdb.execute('hbreak *0x%x'%address)
completed=False
for event in range(30000):
    try:gdb.execute('continue')
    except gdb.error:completed=True;break
    if not inf.is_valid() or inf.pid==0:completed=True;break
    pc=register('pc')
    if pc not in breakpoints:completed=True;break
    function=u32(register('esp')+4) if pc==0x107ad4fe else u32(0x108ab128)
    name=function_name(function)
    if FOCUS not in name:continue
    esp=register('esp')
    if pc==0x107ad4fe:
        first=u32(u32(function+8));blocks=[];block=first
        for bn in range(200):
            if block<0x10000:break
            inst=u32(block+0x1c);last=u32(block+0x20);rows=[]
            for j in range(400):
                if inst<0x10000:break
                if u32(inst+4)==1:
                    ops={}
                    for label,offset in [('source',0x28),('destination',0x2c)]:
                        op=u32(inst+offset);items=[]
                        for k in range(16):
                            if op<0x10000:break
                            items.append(dict(address=hex(op),words=raw(op,0x3c)))
                            op=u32(op)
                        ops[label]=items
                    rows.append(dict(opcode=hex(u32(inst+0x20)),operands=ops))
                if inst==last:break
                inst=u32(inst)
            blocks.append(dict(index=bn,instructions=rows))
            block=u32(block)
            if block==first:break
        out.write(json.dumps(dict(event='Riscify',function=name,blocks=blocks))+'\n');out.flush();continue
    candidate=u32(esp+0x20) if pc==0x107aac16 else register('edi') if pc==0x1076a4b0 else u32(esp+8)
    record=dict(event=breakpoints[pc],function=name,candidate=describe(candidate))
    if pc==0x107aac16:
        record.update(chosen_register=u32(esp+0x10),costs={str(k):signed(0x10882678+k*4) for k in available(candidate)})
    out.write(json.dumps(record)+'\n');out.flush()
out.write(json.dumps(dict(trace_completed=completed))+'\n');out.close()
try:gdb.execute('detach')
except gdb.error:pass
'''.replace('PORT', port).replace('OUTPUT', repr(str(out / 'events.jsonl'))).replace('FOCUS', repr(focus))
(out / 'trace.gdb.py').write_text(script)
try:
    result = subprocess.run(['gdb', '-q', '-batch', '-x', str(out / 'trace.gdb.py')],
                            capture_output=True, text=True, timeout=300)
    (out / 'gdb.log').write_text(result.stdout + result.stderr)
    process.wait(timeout=30)
    if result.returncode or process.returncode:
        raise RuntimeError('Compiler trace failed; inspect gdb.log and winedbg.log.')
finally:
    if process.poll() is None:
        process.terminate()
    (out / 'winedbg.log').write_text(''.join(lines))
records = [json.loads(line) for line in (out / 'events.jsonl').read_text().splitlines()]
if not records[-1].get('trace_completed'):
    raise RuntimeError('Trace stopped before the compiler finished.')
print(json.dumps(dict(events=len(records)-1,trace_completed=records[-1].get('trace_completed'))))
