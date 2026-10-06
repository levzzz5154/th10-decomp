"""Verify sealed whole-owner evidence; this audit does not promote production."""
import hashlib
import json
from pathlib import Path
import sys

sys.path.insert(0, str(Path.cwd()))
from matching2.tools.common.pe import PEImage
from matching2.tools.common.wine import DEFAULT_TOOLKIT
from matching2.tools.matching.equivalence import MAP_SYMBOL

root = Path(__file__).resolve().parent
sha = lambda data: hashlib.sha256(data).hexdigest()
read = lambda path: json.loads(path.read_text())
receipt = read(root / 'receipt.json')
for collection in ['candidate_sources', 'evidence_files', 'reference_inputs']:
    for name, expected in receipt[collection].items():
        path = Path(name) if collection == 'reference_inputs' else root / name
        assert sha(path.read_bytes()) == expected, name
current = root / 'evidence/corrected_graph'
for name, expected in read(current / 'input_hashes.json').items():
    assert sha(Path(name).read_bytes()) == expected, name
for name, expected in read(current / 'compiler_hashes.json').items():
    assert sha((Path(DEFAULT_TOOLKIT) / 'bin' / name).read_bytes()) == expected
layout = read(root / 'layout.json')
assert len(layout['functions']) == len({row[2] for row in layout['functions']}) == 28
assert len(layout['roots']) == 5
rows = read(current / 'comparison.json')['functions']
assert len(rows) == 28
assert sum(row['exact'] for row in rows) == 24
assert sum(row['extent'] for row in rows if row['exact']) == 2731
native = PEImage((current / 'model.exe').read_bytes())
symbols = {name: int(address, 16) for name, address, _ in MAP_SYMBOL.findall((current / 'model.map').read_text())}
oracle = PEImage(Path('matching2/build/oracle/th10.exe').read_bytes())
assert sha(oracle.data) == receipt['retail_sha256']
prior = root / 'evidence/prior_graph'
changed = []
for row in rows:
    symbol, section, address, size = next(item for item in layout['functions'] if item[0] == row['symbol'])
    body = (current / (section + '_body.bin')).read_bytes()
    original = (current / (section + '_retail_full.bin')).read_bytes()
    assert len(body) == row['extent'] and original == oracle.read(address, size)
    assert (body == original) == row['exact']
    assert sum(a != b for a, b in zip(body, original)) == row['different_overlapping_bytes']
    assert native.read(symbols[symbol], row['extent']) == (current / (section + '_full_native.bin')).read_bytes()
    if (prior / (section + '_body.bin')).exists() and body != (prior / (section + '_body.bin')).read_bytes():
        changed.append(symbol)
assert changed == ['?UpdateSequence@PlayerState@@QAEHXZ']
owner = next(row for row in rows if row['symbol'] == '_PlayerState_Update_00425730@4')
assert (owner['extent'], owner['required'], owner['different_overlapping_bytes'], len(owner['hunks'])) == (3024, 3112, 2812, 136)
assert owner['native_table_bytes'] == owner['retail_table_bytes'] == 20
update = next(row for row in rows if 'UpdateSequence@' in row['symbol'])
assert update['extent'] == 174 and update['exact']

total = 0
for name, count, observations, field in [
    ('differential', 1965, 'observations.json', 'observations_sha256'),
    ('effect_differential', 215, 'effect_observations.json', 'observations_file_sha256'),
    ('sequence_differential', 328, 'sequence_observations.json', 'observations_sha256'),
    ('spawn_differential', 186, 'spawn_observations.json', 'observations_sha256'),
    ('schedule_differential', 312, 'schedule_observations.json', 'observations_sha256'),
    ('player_differential', 947, 'player_observations.json', 'observations_sha256'),
]:
    report = read(current / (name + '.json'))
    assert report['cases'] == count and not report.get('failures')
    assert sha((current / observations).read_bytes()) == report[field]
    if 'native_pe_sha256' in report:
        assert sha(native.data) == report['native_pe_sha256']
    if 'cases_sha256' in report:
        stem = name.split('_')[0]
        assert sha((current / (stem + '_cases.json')).read_bytes()) == report['cases_sha256']
    assert not report.get('smoke') and not report.get('limited_run')
    total += count
assert total == 3953
assert read(current / 'effect_differential.json')['passed']
assert all(read(current / 'schedule_differential.json')['executed_helper_calls'].values())

trace = root / 'evidence/player_global_trace'
proof = read(trace / 'verification.json')
assert proof['events'] == 109 and len(proof['complete_functions']) == 28
assert proof['all_complete_bodies_equal'] and proof['all_emitted_code_sections_equal']
assert proof['hardware_breakpoints_only'] and proof['compiler_program_data_writes'] == proof['forced_choices'] == 0
assert not proof['retail_raw_equality_claimed'] and not proof['selected']
assert sha((trace / 'events.jsonl').read_bytes()) == proof['events_sha256']
assert sha((trace / 'command.json').read_bytes()) == proof['command_sha256']
assert sha((root / 'evidence/tools/trace_target_globals_link.py').read_bytes()) == proof['tracer_sha256']
assert sha((root / 'evidence/tools/verify_graph_trace.py').read_bytes()) == proof['verifier_sha256']
traced = PEImage((trace / 'trace.exe').read_bytes())
trace_symbols = {n: int(a, 16) for n, a, _ in MAP_SYMBOL.findall((trace / 'trace.map').read_text())}
assert sha(native.data) == proof['baseline_pe_sha256'] and sha(traced.data) == proof['trace_pe_sha256']
for row in proof['complete_functions']:
    name, size = row['symbol'], row['complete_extent']
    body = native.read(symbols[name], size)
    assert body == traced.read(trace_symbols[name], size) and sha(body) == row['native_body_sha256']
for section in proof['code_sections']:
    native_section = next(item for item in native.sections if item['name'] == section['name'])
    body = native.read(native_section['address'], section['bytes'])
    assert sha(body) == section['sha256'] and body == traced.read(native_section['address'], section['bytes'])

fixed = root / 'evidence/fixed_sequence'
normal = read(fixed / 'probe/normal_probe.json')
assert normal['exact'] and not normal['failures'] and len(normal['regions']) == 1
assert normal['regions'][0]['exact'] and normal['regions'][0]['size'] == 174
report = read(fixed / 'probe/clusters/player_state_sequence_genuine_004281d0/report.json')
assert report['instruction_bytes_changed'] == report['masked_bytes'] == 0
assert not report['reference_bytes_used_for_build'] and not report['constant_aliases']
assert report['normalization']['instruction_bytes_changed'] == report['normalization']['address_operands_changed'] == 0
for name, expected in report['input_sha256'].items():
    assert sha(Path(name).read_bytes()) == expected, name
cluster = fixed / 'probe/clusters/player_state_sequence_genuine_004281d0'
exe_path = cluster / Path(report['native_executable']).parent.name / 'cluster.exe'
fixed_pe = PEImage(exe_path.read_bytes())
assert sha(fixed_pe.data) == report['pe_sha256']
raw = read(fixed / 'probe/complete_raw_bodies.json')
assert len(raw) == 28 and sum(row['raw_equal_at_fixed_va'] for row in raw) == 21
assert sum(row['selected_by_isolated_probe'] for row in raw) == 1
for row in raw:
    address, size = int(row['address'], 0), row['complete_native_extent']
    body = fixed_pe.read(address, size)
    assert sha(body) == row['native_sha256']
    assert (body == oracle.read(address, size)) == row['raw_equal_at_fixed_va']
body = fixed_pe.read(0x4281d0, 174)
assert body == oracle.read(0x4281d0, 174)
assert sha(body) == 'd01d87b0ca6e43943e25ff6ba7107d5857b6ec7478a4093ad0a2efabe65d611c'
assert receipt['new_recovered_bytes'] == 0 and not receipt['production_selected']
print(json.dumps({'passed': True, 'genuine_functions': 28, 'diagnostic_exact_functions': 24,
                  'cases': total, 'whole_owner_native_bytes': 3024,
                  'isolated_raw_sequence_bytes': 174, 'production_selected': False,
                  'new_recovered_bytes': 0, 'archived_files': len(receipt['evidence_files'])}))
