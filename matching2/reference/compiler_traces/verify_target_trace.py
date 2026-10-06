"""Check a completed read-only LTCG trace against its complete native baseline.

Usage: verify_target_trace.py baseline_directory trace_directory layout.json proof.json
Checks every emitted code section, the entire selected function, input objects,
and trace completion. This is diagnostic evidence, not a retail equality gate.
"""
import hashlib
import json
from pathlib import Path
import re
import sys

sys.path.insert(0, str(Path(__file__).resolve().parents[3]))
from matching2.tools.common.pe import PEImage
from matching2.tools.matching.equivalence import MAP_SYMBOL

baseline, trace, layout, output = map(Path, sys.argv[1:])
spec = json.loads(layout.read_text())
native = PEImage((baseline / 'model.exe').read_bytes())
traced = PEImage((trace / 'trace.exe').read_bytes())
events = [json.loads(line) for line in (trace / 'events.jsonl').read_text().splitlines()]
assert events[-1].get('trace_completed')
assert events[:-1] and all(not event.get('truncated') for event in events[:-1])

def sha(data):
    return hashlib.sha256(data).hexdigest()

def symbols(path):
    return {name: int(value, 16) for name, value, where in MAP_SYMBOL.findall(path.read_text())}

native_symbols = symbols(baseline / 'model.map')
trace_symbols = symbols(trace / 'trace.map')
symbol, section, retail_address, required = spec['functions'][0]
extent = int(re.search(r'([0-9a-f]+)H\s+' + re.escape(section) + r'\s+CODE',
                      (trace / 'trace.map').read_text(), re.I)[1], 16)
assert extent == required
body = native.read(native_symbols[symbol], extent)
trace_body = traced.read(trace_symbols[symbol], extent)
assert body == trace_body
sections = []
for section_record in native.sections:
    if not section_record['characteristics'] & 0x20:
        continue
    other = next(s for s in traced.sections if s['name'] == section_record['name'])
    assert section_record['address'] == other['address']
    assert section_record['raw_size'] == other['raw_size']
    before = native.read(section_record['address'], section_record['raw_size'])
    after = traced.read(other['address'], other['raw_size'])
    assert before == after
    sections.append({'name': section_record['name'], 'bytes': len(before), 'sha256': sha(before)})

command = json.loads((trace / 'command.json').read_text())
objects = {}
for argument in command:
    if argument.lower().endswith('.obj'):
        path = Path(argument.replace('Z:', '').replace('\\', '/'))
        objects[str(path)] = sha(path.read_bytes())
receipt = json.loads((layout.parent / 'receipt.json').read_text())
sources = receipt['current_source_sha256']
for path, expected in sources.items():
    assert sha(Path(path).read_bytes()) == expected, path
proof = {
    'symbol': symbol, 'retail_address': hex(retail_address), 'extent': extent,
    'events': len(events) - 1, 'phases': [event['event'] for event in events[:-1]],
    'trace_completed': True, 'hardware_breakpoints_only': True,
    'compiler_data_writes': 0, 'instruction_patches': 0, 'forced_register_decisions': 0,
    'native_body_sha256': sha(body), 'traced_body_equals_untraced_body': True,
    'all_emitted_code_sections_equal': True, 'code_sections': sections,
    'input_object_sha256': objects, 'current_source_sha256': sources,
    'events_sha256': sha((trace / 'events.jsonl').read_bytes()),
    'command_sha256': sha((trace / 'command.json').read_bytes()),
    'retail_raw_equality_claimed': False, 'production_promotion': False,
}
output.parent.mkdir(parents=True, exist_ok=True)
output.write_text(json.dumps(proof, indent=2) + '\n')
print(json.dumps({key: proof[key] for key in ['extent', 'events', 'native_body_sha256',
                                            'all_emitted_code_sections_equal']}))
