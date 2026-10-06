"""Read MSVC 13.10 temporary-register allocation without forcing its choices.

Usage: python trace_temporary_cursor.py commands.json output_dir [name_fragment]
commands.json must include a native /BASE:0x400000 LTCG link. The replay writes
its PE and MAP to output_dir; it never overwrites the measured original link.
The offsets below are specific to the checked c2.dll, not other compiler builds.
"""
import hashlib
import json
import re
import subprocess
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[4]))
from matching2.tools.common.wine import DEFAULT_TOOLKIT, compiler_environment, winpath

commands = json.loads(Path(sys.argv[1]).read_text())
out = Path(sys.argv[2]).resolve()
out.mkdir(parents=True, exist_ok=True)
focus = sys.argv[3] if len(sys.argv) > 3 else 'Spawn@ItemSpawnManager'
c2 = Path(DEFAULT_TOOLKIT) / 'bin/c2.dll'
expected = '7a6f6d8e4da7b518384ff78f2c41028805d3a1d1a40dc2cc857c391ec81763f5'
if hashlib.sha256(c2.read_bytes()).hexdigest() != expected:
    raise RuntimeError('The register-allocation offsets require c2.dll 13.10.6030.')
command = next(command for command in commands if '/BASE:0x400000' in command)
args = [('/OUT:' + winpath(out / 'trace.exe') if arg.startswith('/OUT:') else
         '/MAP:' + winpath(out / 'trace.map') if arg.startswith('/MAP:') else arg)
        for arg in command[1:]]
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
breakpoints = {
    0x1079c134: 'RegAssign_entry', 0x1079c23b: 'RegAssign_pick',
    0x1079bdf3: 'Function_cursor_reset', 0x107e1763: 'Marker_cursor_reset',
    0x1079c39d: 'Cursor_update',
}
# The DLL is loaded when the first hardware breakpoint hits. Then install
# debugger breakpoints; no program data, allocation result, or register is set.
gdb.execute('hbreak *0x1079c134')
armed = False
completed = False
for event in range(30000):
    try:
        gdb.execute('continue')
    except gdb.error:
        completed = True
        break
    if not inf.is_valid() or inf.pid == 0:
        completed = True
        break
    pc = register('pc')
    if pc not in breakpoints:
        completed = True
        break
    if not armed:
        gdb.execute('delete breakpoints')
        for address in breakpoints:
            gdb.execute('break *0x%x' % address)
        armed = True
    function = u32(0x108ab128)
    name = function_name(function)
    if FOCUS not in name:
        continue
    esp = register('esp')
    kind = breakpoints[pc]
    record = dict(event=kind, function=name, next_int_pos=hex(u32(0x108a9d0c)),
                  marker_reset_flag=u32(0x108ab138))
    if kind == 'RegAssign_entry':
        operand = u32(esp + 4)
        instruction = register('ecx')
        record.update(instruction=hex(instruction),
                      ir_opcode=hex(u32(instruction + 4)),
                      source_memory_displacements=memory_displacements(instruction, 0x28),
                      destination_memory_displacements=memory_displacements(instruction, 0x2c),
                      temporary=hex(u32(u32(operand + 0x1c) + 0x1c)),
                      following_store_displacements=following_store(instruction))
    elif kind == 'RegAssign_pick':
        record.update(instruction=hex(u32(esp + 4)), temporary=hex(u32(esp + 0x14)),
                      physical_register=register('esi'))
    elif kind == 'Cursor_update':
        record['new_cursor'] = hex(register('eax'))
    elif kind == 'Marker_cursor_reset':
        record['ir_opcode'] = hex(u32(register('esi') + 4))
    out.write(json.dumps(record) + '\n')
    out.flush()
out.write(json.dumps(dict(trace_completed=completed)) + '\n')
out.close()
try:
    gdb.execute('detach')
except gdb.error:
    pass
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
print(json.dumps(dict(function_resets=sum(r.get('event') == 'Function_cursor_reset' for r in records),
                      marker_resets=sum(r.get('event') == 'Marker_cursor_reset' for r in records),
                      events=len(records) - 1)))
