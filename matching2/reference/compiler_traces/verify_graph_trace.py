"""Verify every complete native body and code section after an LTCG trace.

Usage: verify_graph_trace.py baseline.exe baseline.map comparison.json
       input_hashes.json trace_directory tracer.py
This verifies that observation did not change native output. It is not a
retail equality gate and does not select any function.
"""
import hashlib
import json
from pathlib import Path
import sys

sys.path.insert(0, str(Path(__file__).resolve().parents[3]))
from matching2.tools.common.pe import PEImage
from matching2.tools.common.wine import DEFAULT_TOOLKIT
from matching2.tools.matching.equivalence import MAP_SYMBOL

native_path, map_path, comparison_path, inputs_path, trace, tracer = map(Path, sys.argv[1:])
sha = lambda data: hashlib.sha256(data).hexdigest()
native = PEImage(native_path.read_bytes())
traced = PEImage((trace / 'trace.exe').read_bytes())
comparison = json.loads(comparison_path.read_text())
rows = comparison['functions'] if isinstance(comparison, dict) else comparison
sources = json.loads(inputs_path.read_text())
if 'input_sha256' in sources:
    sources = sources['input_sha256']
events = [json.loads(line) for line in (trace / 'events.jsonl').read_text().splitlines()]
assert events[-1].get('trace_completed') and len(events) > 1
assert all(not event.get('truncated') for event in events[:-1])
assert len(rows) == len({row['symbol'] for row in rows})

def symbols(path):
    return {name: int(address, 16) for name, address, origin in MAP_SYMBOL.findall(path.read_text())}

native_symbols, traced_symbols = symbols(map_path), symbols(trace / 'trace.map')
bodies = []
for row in rows:
    symbol, size = row['symbol'], row['extent']
    body = native.read(native_symbols[symbol], size)
    assert body == traced.read(traced_symbols[symbol], size), symbol
    bodies.append({'symbol': symbol, 'complete_extent': size,
                   'native_body_sha256': sha(body), 'unchanged': True})
sections = []
for section in native.sections:
    if not section['characteristics'] & 0x20:
        continue
    other = next(record for record in traced.sections if record['name'] == section['name'])
    assert section == other
    body = native.read(section['address'], section['raw_size'])
    assert body == traced.read(other['address'], other['raw_size'])
    sections.append({'name': section['name'], 'bytes': len(body), 'sha256': sha(body)})
for name, expected in sources.items():
    assert sha(Path(name).read_bytes()) == expected, name
objects = {}
for argument in json.loads((trace / 'command.json').read_text()):
    if argument.lower().endswith('.obj'):
        path = Path(argument.replace('Z:', '').replace('\\', '/'))
        objects[str(path)] = sha(path.read_bytes())
compiler_hashes = {name: sha((Path(DEFAULT_TOOLKIT) / 'bin' / name).read_bytes())
                   for name in ['cl.exe', 'link.exe', 'c2.dll']}
assert compiler_hashes['c2.dll'] == '7a6f6d8e4da7b518384ff78f2c41028805d3a1d1a40dc2cc857c391ec81763f5'
proof = {
    'trace_completed': True, 'events': len(events) - 1,
    'phases': [event['event'] for event in events[:-1]],
    'hardware_breakpoints_only': True, 'compiler_program_data_writes': 0,
    'forced_choices': 0, 'all_complete_bodies_equal': True,
    'all_emitted_code_sections_equal': True, 'complete_functions': bodies,
    'code_sections': sections, 'baseline_pe_sha256': sha(native.data),
    'trace_pe_sha256': sha(traced.data), 'current_source_sha256': sources,
    'input_object_sha256': objects, 'compiler_sha256': compiler_hashes,
    'events_sha256': sha((trace / 'events.jsonl').read_bytes()),
    'command_sha256': sha((trace / 'command.json').read_bytes()),
    'tracer_sha256': sha(tracer.read_bytes()), 'verifier_sha256': sha(Path(__file__).read_bytes()),
    'retail_raw_equality_claimed': False, 'selected': False, 'new_recovered_bytes': 0,
}
(trace / 'verification.json').write_text(json.dumps(proof, indent=2) + '\n')
print(json.dumps({'functions': len(bodies), 'events': len(events) - 1, 'code_sections': sections}))
