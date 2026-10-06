"""Audit the retained, unselected scheduled-effect graph and its sealed evidence."""
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
for collection in ['candidate_sources', 'evidence_files']:
    for name, expected in receipt[collection].items():
        assert sha((root / name).read_bytes()) == expected, name
current = root / 'evidence/sequence_graph'
for name, expected in read(current / 'input_hashes.json').items():
    assert sha(Path(name).read_bytes()) == expected, name
for name, expected in read(current / 'compiler_hashes.json').items():
    assert sha((Path(DEFAULT_TOOLKIT) / 'bin' / name).read_bytes()) == expected

layout = read(root / 'layout.json')
assert len(layout['functions']) == len({row[2] for row in layout['functions']}) == 27
assert len(layout['roots']) == 5
comparison = read(current / 'comparison.json')['functions']
assert len(comparison) == 27
assert sum(row['exact'] for row in comparison) == 23
assert sum(row['extent'] for row in comparison if row['exact']) == 2557
native = PEImage((current / 'model.exe').read_bytes())
symbols = {name: int(address, 16) for name, address, _ in
           MAP_SYMBOL.findall((current / 'model.map').read_text())}
oracle = PEImage(Path('matching2/build/oracle/th10.exe').read_bytes())
assert sha(oracle.data) == receipt['retail_sha256']
prior = root / 'evidence/prior_graph'
for row in comparison:
    symbol, section, address, size = next(x for x in layout['functions'] if x[0] == row['symbol'])
    body = (current / (section + '_body.bin')).read_bytes()
    original = (current / (section + '_retail_full.bin')).read_bytes()
    assert len(body) == row['extent'] and len(original) == size
    assert original == oracle.read(address, size)
    assert (body == original) == row['exact']
    assert sum(a != b for a, b in zip(body, original)) == row['different_overlapping_bytes']
    assert native.read(symbols[symbol], row['extent']) == (current / (section + '_full_native.bin')).read_bytes()
    if (prior / (section + '_body.bin')).exists():
        assert body == (prior / (section + '_body.bin')).read_bytes()
spawn = next(row for row in comparison if row['symbol'] == '_StageSchedule_Fire_00427e90@12')
assert (spawn['extent'], spawn['required'], spawn['different_overlapping_bytes'], len(spawn['hunks'])) == (717, 717, 61, 9)
assert (current / '.text$b00spawn_body.bin').read_bytes()[:457] == oracle.read(0x427e90, 457)
dispatch = next(row for row in comparison if 'Dispatch@' in row['symbol'])
assert dispatch['extent'] == 105 and dispatch['exact']
update = next(row for row in comparison if 'UpdateSequence@' in row['symbol'])
assert (update['extent'], update['different_overlapping_bytes']) == (174, 1)

reports = {}
for name, count, observations, field in [
    ('differential', 1965, 'observations.json', 'observations_sha256'),
    ('effect_differential', 215, 'effect_observations.json', 'observations_file_sha256'),
    ('sequence_differential', 328, 'sequence_observations.json', 'observations_sha256'),
    ('spawn_differential', 186, 'spawn_observations.json', 'observations_sha256'),
    ('schedule_differential', 312, 'schedule_observations.json', 'observations_sha256'),
]:
    report = read(current / (name + '.json'))
    assert report['cases'] == count and not report.get('failures')
    assert sha((current / observations).read_bytes()) == report[field]
    if 'native_pe_sha256' in report:
        assert sha(native.data) == report['native_pe_sha256']
    reports[name] = report
assert reports['effect_differential']['passed'] and not reports['effect_differential']['limited_run']
assert all(reports['effect_differential']['executed_helper_calls'].values())
assert reports['sequence_differential']['caller_invocations'] == {'effect': 410, 'sweep': 410}
spawn_report = reports['spawn_differential']
assert sha((current / 'spawn_cases.json').read_bytes()) == spawn_report['cases_sha256']
assert len(read(current / 'spawn_cases.json')) == 186
assert set(spawn_report['retail_branch_coverage']) == {
    '0x427f05', '0x427fc9', '0x427fd7', '0x4280d0',
    '0x427f3a', '0x428130', '0x42814d', '0x4280bb'}
assert all(spawn_report['retail_branch_coverage'].values())
schedule = reports['schedule_differential']
assert all(schedule['executed_helper_calls'].values())
assert schedule['instruction_patches'] == 0 and not schedule['selection_evidence']
assert sha((current / 'schedule_cases.json').read_bytes()) == schedule['cases_sha256']
assert len(read(current / 'schedule_cases.json')) == 312

controls = read(root / 'evidence/source_controls/ledger.json')
assert len(controls) == 16 and not any(row['selected'] for row in controls)
for control in controls:
    archive = root / 'evidence/source_controls' / control['control']
    rows = read(archive / 'comparison.json')['functions']
    assert len(rows) == control['complete_functions']
    assert len(rows) in [23, 27]
    assert sum(row['exact'] for row in rows) == control['diagnostic_exact_functions'] == (19 if len(rows) == 23 else 23)
    row = next(row for row in rows if 'Fire' in row['symbol'])
    assert (row['extent'], row['different_overlapping_bytes'], len(row['hunks'])) == (
        control['spawn_extent'], control['different_overlapping_bytes'], control['difference_groups'])
    for symbol, section, address, size in layout['functions'][:20]:
        assert (archive / (section + '_body.bin')).read_bytes() == (prior / (section + '_body.bin')).read_bytes()
effect_controls = read(root / 'evidence/effect_controls/ledger.json')
assert len(effect_controls) == 4
assert sum(row['status'] == 'rejected_missing_complete_symbol' for row in effect_controls) == 2
for control in effect_controls:
    if control['status'] != 'complete_bodies_unchanged':
        assert not control['complete_comparison_claimed']
        continue
    archive = root / 'evidence/effect_controls' / control['control']
    assert len(read(archive / 'comparison.json')['functions']) == 20
    for path in prior.glob('*_body.bin'):
        assert path.read_bytes() == (archive / path.name).read_bytes()

for trace_name, baseline in [('sequence_global_trace', current),
                             ('retained_global_trace', root / 'evidence/retained_graph'),
                             ('spawn_pool_global_trace', root / 'evidence/source_controls/spawn_pool_while')]:
    trace = root / 'evidence' / trace_name
    proof = read(trace / 'verification.json')
    assert proof['trace_completed'] and proof['all_complete_bodies_equal']
    assert proof['all_emitted_code_sections_equal'] and proof['hardware_breakpoints_only']
    assert proof['compiler_program_data_writes'] == proof['forced_choices'] == 0
    assert len(proof['complete_functions']) == (27 if trace_name == 'sequence_global_trace' else 23)
    assert not proof['retail_raw_equality_claimed'] and not proof['selected']
    assert sha((trace / 'events.jsonl').read_bytes()) == proof['events_sha256']
    assert sha((trace / 'command.json').read_bytes()) == proof['command_sha256']
    assert sha((root / 'evidence/tools/trace_target_globals_link.py').read_bytes()) == proof['tracer_sha256']
    assert sha((root / 'evidence/tools/verify_graph_trace.py').read_bytes()) == proof['verifier_sha256']
    traced = PEImage((trace / 'trace.exe').read_bytes())
    base = PEImage((baseline / 'model.exe').read_bytes())
    assert sha(base.data) == proof['baseline_pe_sha256']
    assert sha(traced.data) == proof['trace_pe_sha256']
    base_symbols = {n: int(a, 16) for n, a, _ in MAP_SYMBOL.findall((baseline / 'model.map').read_text())}
    trace_symbols = {n: int(a, 16) for n, a, _ in MAP_SYMBOL.findall((trace / 'trace.map').read_text())}
    for row in proof['complete_functions']:
        symbol, extent = row['symbol'], row['complete_extent']
        body = base.read(base_symbols[symbol], extent)
        assert body == traced.read(trace_symbols[symbol], extent)
        assert sha(body) == row['native_body_sha256']
    for row in proof['code_sections']:
        section = next(s for s in base.sections if s['name'] == row['name'])
        assert sha(base.read(section['address'], row['bytes'])) == row['sha256']
        assert base.read(section['address'], row['bytes']) == traced.read(section['address'], row['bytes'])

assert receipt['new_recovered_bytes'] == 0 and not receipt['selected']
print(json.dumps({'passed': True, 'complete_functions': 27,
                  'diagnostic_exact_functions': 23, 'cases': 3006,
                  'spawn_extent': 717, 'spawn_different_bytes': 61,
                  'archived_files': len(receipt['evidence_files']),
                  'selected': False, 'new_recovered_bytes': 0}))
