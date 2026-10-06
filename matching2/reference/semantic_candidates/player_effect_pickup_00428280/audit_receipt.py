"""Verify current shared-graph inputs, complete bodies, observations and production proof."""
import hashlib
import json
from pathlib import Path
import sys

sys.path.insert(0, str(Path.cwd()))
from matching2.tools.common.wine import DEFAULT_TOOLKIT

root = Path(__file__).resolve().parent
receipt = json.loads((root / 'receipt.json').read_text())
for collection in ['candidate_sources', 'evidence_files']:
    for name, digest in receipt[collection].items():
        assert hashlib.sha256((root / name).read_bytes()).hexdigest() == digest, name
current = root / 'evidence/hit_exact_graph'
for name, digest in json.loads((current / 'input_hashes.json').read_text()).items():
    assert hashlib.sha256(Path(name).read_bytes()).hexdigest() == digest, name
for name, digest in json.loads((current / 'compiler_hashes.json').read_text()).items():
    assert hashlib.sha256((Path(DEFAULT_TOOLKIT) / 'bin' / name).read_bytes()).hexdigest() == digest
layout = json.loads((root / 'layout.json').read_text())
assert len(layout['functions']) == len({entry[2] for entry in layout['functions']}) == 20
assert len(layout['roots']) == 3
comparison = json.loads((current / 'comparison.json').read_text())
assert len(comparison['functions']) == 20
assert sum(row['exact'] for row in comparison['functions']) == 18
assert sum(row['extent'] for row in comparison['functions'] if row['exact']) == 2086
for row in comparison['functions']:
    symbol, section, address, size = next(entry for entry in layout['functions'] if entry[0] == row['symbol'])
    body = (current / (section + '_body.bin')).read_bytes()
    original = (current / (section + '_retail_full.bin')).read_bytes()
    assert len(body) == row['extent'] and len(original) == size
    assert (body == original) == row['exact']
    assert sum(a != b for a, b in zip(body, original)) == row['different_overlapping_bytes']
    if address not in (0x4059f0, 0x40c480, 0x4489d0, 0x448d00, 0x428630, 0x449870):
        assert body == (root / 'evidence/shared_member_graph' / (section + '_body.bin')).read_bytes()
targets = {0x4059f0: (202, 202, 0, 0), 0x428630: (1171, 1170, 1013, 62),
           0x428280: (874, 876, 205, 3)}
for address, expected in targets.items():
    symbol = next(entry[0] for entry in layout['functions'] if entry[2] == address)
    row = next(entry for entry in comparison['functions'] if entry['symbol'] == symbol)
    assert (row['extent'], row['required'], row['different_overlapping_bytes'], len(row['hunks'])) == expected
pickup = json.loads((current / 'differential.json').read_text())
effect = json.loads((current / 'effect_differential.json').read_text())
sequence = json.loads((current / 'sequence_differential.json').read_text())
assert pickup['cases'] == 1965 and not pickup['failures']
assert effect['cases'] == 215 and effect['passed'] and not effect['limited_run']
assert all(effect['executed_helper_calls'].values())
assert sequence['cases'] == 328 and not sequence['failures']
assert sequence['caller_invocations'] == {'effect': 410, 'sweep': 410}
for name, report, field in [('observations.json', pickup, 'observations_sha256'),
                            ('effect_observations.json', effect, 'observations_file_sha256'),
                            ('sequence_observations.json', sequence, 'observations_sha256')]:
    assert hashlib.sha256((current / name).read_bytes()).hexdigest() == report[field]
for report in [effect, sequence]:
    assert hashlib.sha256((current / 'model.exe').read_bytes()).hexdigest() == report['native_pe_sha256']
controls=json.loads((root/'evidence/layout_controls/ledger.json').read_text())
assert len(controls)==23 and all(row['complete_functions']==20 for row in controls)
selected_controls = [row for row in controls if row['selected']]
assert len(selected_controls)==1 and selected_controls[0]['control']=='hit_flag_only_second_arm'
assert selected_controls[0]['selected_bytes']==202
assert len([case for case in json.loads((current/'cases.json').read_text()) if case['label'].startswith('registration_')])==32
assert len([case for case in json.loads((current/'cases.json').read_text()) if case['label'].startswith('public_initialize_')])==48
assert len([case for case in json.loads((current/'cases.json').read_text()) if case['label'].startswith('reference_bits_')])==48
unchanged = json.loads((current/'unchanged_bodies.json').read_text())
assert len(unchanged) == 20 and sum(row['unchanged'] for row in unchanged)==19
for row in unchanged:
    for suffix,field in [('_body.bin','complete_rebound_sha256'),('_full_native.bin','complete_native_sha256')]:
        body=(current/(row['section']+suffix)).read_bytes()
        assert hashlib.sha256(body).hexdigest()==row[field]
        equal=body==(root/'evidence/shared_reference_graph'/(row['section']+suffix)).read_bytes()
        assert equal==row['unchanged']
        assert equal==(row['address']!='0x4059f0')
for control in controls:
    name=control['control']
    archive=root/'evidence/layout_controls'/name/'native'
    source_root=Path('matching2/build/experiments/player_effect_pickup_2026_10_06/controls').resolve()/name
    for path,digest in json.loads((archive/'input_hashes.json').read_text()).items():
        path=Path(path)
        if path.is_relative_to(source_root):
            assert hashlib.sha256((archive/'inputs'/path.relative_to(source_root)).read_bytes()).hexdigest()==digest,(name,path)
audit = json.loads((root / 'evidence/production_audit.json').read_text())
assert audit['whole_executable']['raw_exact']
assert audit['actual_remaining_assembly_regions'] == 59 and audit['actual_remaining_assembly_bytes'] == 89043
proof_root = root / 'evidence/initializer_genuine_reference_production'
proof = json.loads((proof_root / 'production_probe/clusters/animation_resource_initialize_object_00449870/report.json').read_text())
project = Path('matching2/msvc').resolve()
for name, digest in proof['input_sha256'].items():
    source = Path(name)
    assert hashlib.sha256((proof_root / 'inputs' / source.relative_to(project)).read_bytes()).hexdigest() == digest, name
assert len(proof['functions']) == 1 and proof['functions'][0]['size'] == 217
assert proof['functions'][0]['sha256'] == 'c4be92e1096f74b7be92e5fe32adee65afee5fa061b3775559c574a83ecc5267'
assert proof['compiler_context']['symbol'] == '_EffectPoolUpdate@4'
assert not proof['instruction_bytes_changed'] and not proof['masked_bytes'] and not proof['reference_bytes_used_for_build']
fixed = json.loads((proof_root / 'fixed_graph_comparison.json').read_text())
assert len(fixed) == 20 and sum(row['exact'] for row in fixed) == 16
assert next(row for row in fixed if row['address'] == '0x449870')['exact']
assert not (project / 'layout/ltcg/animation_resource_initialize_object_00449870_context.cpp').exists()
assert not (project / 'layout/ltcg/animation_resource_initialize_object_00449870_loader.cpp').exists()
trace_root=proof_root/'effect_global_trace'
trace=json.loads((trace_root/'verification.json').read_text())
assert trace['trace_completed'] and trace['events']==39 and trace['allocation_events']==29
assert trace['hardware_breakpoints_only'] and not trace['compiler_program_data_writes'] and not trace['forced_choices']
assert trace['all_complete_bodies_equal'] and trace['all_emitted_code_sections_equal']
assert len(trace['complete_functions'])==20
for address,number,priority in [('0x24',19,32),('0x28',20,56)]:
    row=next(row for row in trace['ID_load_candidate_correlations'] if row['candidate']==number)
    assert row['source_offset']==address and row['priority']==priority and row['chosen_register']==1
assert trace['current_source_sha256']==proof['input_sha256']
from matching2.tools.common.pe import PEImage
native_root=proof_root/'production_probe/clusters/animation_resource_initialize_object_00449870'/Path(proof['native_executable']).parent.name
native=PEImage((native_root/'cluster.exe').read_bytes())
traced=PEImage((trace_root/'trace.exe').read_bytes())
assert hashlib.sha256(native.data).hexdigest()==proof['pe_sha256']
assert hashlib.sha256((native_root/'cluster.map').read_bytes()).hexdigest()==proof['map_sha256']
for row in fixed:
    address=int(row['address'],0)
    actual=native.read(address,row['extent'])
    original_section=next(entry[1] for entry in layout['functions'] if entry[0]==row['symbol'])
    original=(current/(original_section+'_retail_full.bin')).read_bytes()
    assert (actual==original)==row['exact']
    traced_body=traced.read(address,row['extent'])
    assert actual==traced_body
    record=next(record for record in trace['complete_functions'] if record['symbol']==row['symbol'])
    assert record['complete_extent']==row['extent']
    assert hashlib.sha256(actual).hexdigest()==record['native_body_sha256']
for section in trace['code_sections']:
    actual=next(record for record in native.sections if record['name']==section['name'])
    body=native.read(actual['address'],actual['raw_size'])
    assert len(body)==section['bytes'] and hashlib.sha256(body).hexdigest()==section['sha256']
    assert body==traced.read(actual['address'],actual['raw_size'])

from matching2.tools.matching.equivalence import MAP_SYMBOL

def verify_trace(baseline_root, executable, map_name, trace_root):
    native=PEImage((baseline_root/executable).read_bytes())
    traced=PEImage((trace_root/'trace.exe').read_bytes())
    proof=json.loads((trace_root/'verification.json').read_text())
    assert proof['trace_completed'] and proof['hardware_breakpoints_only']
    assert not proof['compiler_program_data_writes'] and not proof['forced_choices']
    assert proof['all_complete_bodies_equal'] and proof['all_emitted_code_sections_equal']
    assert len(proof['complete_functions'])==20
    assert hashlib.sha256(native.data).hexdigest()==proof['baseline_pe_sha256']
    assert hashlib.sha256(traced.data).hexdigest()==proof['trace_pe_sha256']
    assert hashlib.sha256((trace_root/'events.jsonl').read_bytes()).hexdigest()==proof['events_sha256']
    assert hashlib.sha256((trace_root/'command.json').read_bytes()).hexdigest()==proof['command_sha256']
    symbols=lambda path:{name:int(address,16) for name,address,origin in MAP_SYMBOL.findall(path.read_text())}
    ns,ts=symbols(baseline_root/map_name),symbols(trace_root/'trace.map')
    for row in proof['complete_functions']:
        body=native.read(ns[row['symbol']],row['complete_extent'])
        assert body==traced.read(ts[row['symbol']],row['complete_extent'])
        assert hashlib.sha256(body).hexdigest()==row['native_body_sha256']
    for record in proof['code_sections']:
        section=next(s for s in native.sections if s['name']==record['name'])
        body=native.read(section['address'],section['raw_size'])
        assert len(body)==record['bytes'] and hashlib.sha256(body).hexdigest()==record['sha256']
        assert body==traced.read(section['address'],section['raw_size'])
    return proof

trace_archive=root/'evidence/hit_contract_traces'
for record in json.loads((trace_archive/'ledger.json').read_text()):
    verify_trace(root/'evidence'/record['baseline'],record['executable'],record['map'],trace_archive/record['trace'])
correlation=json.loads((trace_archive/'hit_canonical_global_trace/verification.json').read_text())['mode_load_candidate_correlations']
assert len(correlation)==1 and correlation[0]['source_offset']=='0x44'
assert (correlation[0]['candidate'],correlation[0]['priority'],correlation[0]['chosen_register'])==(10,22,2)

new_root=root/'evidence/hit_exact_production'
new_proof=json.loads((new_root/'production_probe/clusters/animation_resource_initialize_object_00449870/report.json').read_text())
for name,digest in new_proof['input_sha256'].items():
    assert hashlib.sha256(Path(name).read_bytes()).hexdigest()==digest,name
    assert hashlib.sha256((new_root/'inputs'/Path(name).relative_to(project)).read_bytes()).hexdigest()==digest,name
assert len(new_proof['functions'])==2
assert not new_proof['instruction_bytes_changed'] and not new_proof['masked_bytes']
assert not new_proof['reference_bytes_used_for_build']
hit=next(row for row in new_proof['functions'] if int(row['address'],0)==0x4059f0)
assert hit['size']==202 and hit['sha256']=='65a18b997df4b896439672bbdf9abfbd2fb64cf29af75d0cd86c7d0b78f66ece'
assert next(row for row in new_proof['functions'] if int(row['address'],0)==0x449870)['sha256']==proof['functions'][0]['sha256']
new_native_root=new_root/'production_probe/clusters/animation_resource_initialize_object_00449870'/Path(new_proof['native_executable']).parent.name
new_native=PEImage((new_native_root/'cluster.exe').read_bytes())
assert hashlib.sha256(new_native.data).hexdigest()==new_proof['pe_sha256']
new_fixed=json.loads((new_root/'fixed_graph_comparison.json').read_text())
assert len(new_fixed)==20 and sum(row['exact'] for row in new_fixed)==17
for row in new_fixed:
    body=new_native.read(int(row['address'],0),row['extent'])
    assert hashlib.sha256(body).hexdigest()==row['native_sha256']
    section=next(entry[1] for entry in layout['functions'] if entry[0]==row['symbol'])
    assert (body==(current/(section+'_retail_full.bin')).read_bytes())==row['exact']
new_trace=verify_trace(new_native_root,'cluster.exe','cluster.map',new_root/'hit_exact_global_trace')
assert new_trace['events']==7 and new_trace['current_source_sha256']==new_proof['input_sha256']
events=[json.loads(line) for line in (new_root/'hit_exact_global_trace/events.jsonl').read_text().splitlines()]
assert [(event['candidate']['names'],event['candidate']['priority'],event['chosen_register'])
        for event in events if event.get('event')=='ChoosePhysReg' and event['candidate']['names'] in [['_this'],['_result']]]==[(['_this'],44,2),(['_result'],40,3)]
assert not (project/'layout/ltcg/animation_initialize_runtime/hit.cpp').exists()
assert not (project/'layout/ltcg/animation_initialize_runtime/runtime.cpp').exists()
configuration=json.loads((project/'regions.json').read_text())
region=next(row for row in configuration['regions'] if int(row['address'],0)==0x4059f0)
assert region['kind']=='semantic' and region['source']=='src/game/player_hit_test_004059f0.cpp'
assert region['previous_record']['kind']=='asm' and region['size']==202
assert '__asm' not in (project/region['source']).read_text()
assert not receipt['selected'] and receipt['new_recovered_bytes'] == 202
print(json.dumps({'candidate_inputs': len(receipt['candidate_sources']),
                  'archived_artifacts': len(receipt['evidence_files']),
                  'genuine_functions': 20, 'diagnostic_exact_helpers': 17,
                  'bounded_comparisons': pickup['cases'] + effect['cases'] + sequence['cases'],
                  'selected': False, 'selected_complete_hit_test_bytes': 202, 'new_recovered_bytes': 202,
                  'whole_executable': audit['whole_executable']}, indent=2))
