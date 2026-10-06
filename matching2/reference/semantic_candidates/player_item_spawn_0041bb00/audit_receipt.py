"""Audit sealed complete native and behavioral evidence; verify selected production context."""
import hashlib
import json
from pathlib import Path
import sys

sys.path.insert(0,str(Path.cwd()))
from matching2.tools.common.pe import PEImage
from matching2.tools.common.wine import DEFAULT_TOOLKIT
from matching2.tools.matching.equivalence import MAP_SYMBOL

root=Path(__file__).resolve().parent
sha=lambda data:hashlib.sha256(data).hexdigest()
read=lambda p:json.loads(p.read_text())
receipt=read(root/'receipt.json')
for group in ['candidate_sources','evidence_files','reference_inputs']:
    for name,digest in receipt[group].items():
        p=Path(name) if group=='reference_inputs' else root/name
        assert sha(p.read_bytes())==digest,name
current=root/'evidence/genuine_graph'
for name,digest in read(current/'input_hashes.json').items():
    path=Path(name)
    if path.resolve()==Path('matching2/msvc/regions.json').resolve():path=root/'evidence/production_before/regions.json'
    assert sha(path.read_bytes())==digest,name
for name,digest in read(current/'compiler_hashes.json').items():
    assert sha((Path(DEFAULT_TOOLKIT)/'bin'/name).read_bytes())==digest
layout=read(root/'layout.json');rows=read(current/'comparison.json')['functions']
assert len(layout['functions'])==len({f[2] for f in layout['functions']})==len(rows)==36
assert len(layout['roots'])==6 and layout['roots'][:-1]==read(root/'evidence/prior_graph/layout.json')['roots']
assert sum(r['exact'] for r in rows)==27
assert sum(r['extent'] for r in rows if r['exact'])==3281
native=PEImage((current/'model.exe').read_bytes())
symbols={n:int(a,16) for n,a,_ in MAP_SYMBOL.findall((current/'model.map').read_text())}
oracle=PEImage(Path('matching2/build/oracle/th10.exe').read_bytes())
assert sha(oracle.data)==receipt['retail_sha256']
changed=[]
for r in rows:
    symbol,section,address,size=next(f for f in layout['functions'] if f[0]==r['symbol'])
    body=(current/(section+'_body.bin')).read_bytes()
    assert len(body)==r['extent'] and (body==oracle.read(address,size))==r['exact']
    assert (current/(section+'_retail_full.bin')).read_bytes()==oracle.read(address,size)
    assert sum(a!=b for a,b in zip(body,oracle.read(address,size)))==r['different_overlapping_bytes']
    assert native.read(symbols[symbol],r['extent'])==(current/(section+'_full_native.bin')).read_bytes()
    prior=root/'evidence/prior_graph'/(section+'_body.bin')
    if prior.exists() and prior.read_bytes()!=body:changed.append(symbol)
assert changed==['_PlayerState_Update_00425730@4','?Check@PlayerCollisionEngine@@QAEHPBUVec3@@MHH@Z']
owner=next(r for r in rows if r['symbol']=='_PlayerState_Update_00425730@4')
assert (owner['extent'],owner['required'],owner['different_overlapping_bytes'],len(owner['hunks']))==(3060,3112,2856,124)
assert owner['native_table_bytes']==owner['retail_table_bytes']==20
assert next(r for r in rows if 'Activate@PlayerCollisionRecord' in r['symbol'])['exact']
assert next(r for r in rows if 'UpdateSequence@' in r['symbol'])['exact']
# Every historical control preserves its whole layout, emitted extents and input snapshot.
for name in receipt['whole_function_controls']:
    folder=root/'evidence/controls'/name
    control=read(folder/'layout.json');comparison=read(folder/'comparison.json')['functions']
    assert len(control['functions'])==len(comparison)==36
    for path,digest in read(folder/'input_hashes.json').items():
        p=Path(path)
        if p.is_relative_to(root):p=folder/'inputs'/p.relative_to(root)
        if p.resolve()==Path('matching2/msvc/regions.json').resolve():p=root/'evidence/production_before/regions.json'
        assert sha(p.read_bytes())==digest,str(p)
    for row in comparison:
        section=next(f[1] for f in control['functions'] if f[0]==row['symbol'])
        assert len((folder/(section+'_body.bin')).read_bytes())==row['extent']

total=0
for name,count,observations,field in [
    ('differential',1965,'observations.json','observations_sha256'),
    ('effect_differential',215,'effect_observations.json','observations_file_sha256'),
    ('sequence_differential',328,'sequence_observations.json','observations_sha256'),
    ('spawn_differential',186,'spawn_observations.json','observations_sha256'),
    ('schedule_differential',312,'schedule_observations.json','observations_sha256'),
    ('player_differential',947,'player_observations.json','observations_sha256'),
    ('collision_differential',1557,'collision_observations.json','observations_sha256'),
    ('item_differential',1574,'item_observations.json','observations_sha256')]:
    report=read(current/(name+'.json'))
    assert report['cases']==count and not report.get('failures')
    assert sha((current/observations).read_bytes())==report[field]
    assert not report.get('smoke') and not report.get('limited_run')
    if 'native_pe_sha256' in report:assert report['native_pe_sha256']==sha(native.data)
    if 'cases_sha256' in report:
        assert sha((current/(name.split('_')[0]+'_cases.json')).read_bytes())==report['cases_sha256']
    total+=count
assert total==7084 and read(current/'effect_differential.json')['passed']
assert read(current/'collision_differential.json')['executed_helper_calls']=={'activate':5118,'check':694,'bounds':6855,'loader':386,'creator':386,'item_spawn':54,'start_script':0,'item_polar':54}

trace=root/'evidence/item_spawn_trace';proof=read(trace/'verification.json')
assert proof['events']==24 and len(proof['complete_functions'])==36
assert proof['all_complete_bodies_equal'] and proof['all_emitted_code_sections_equal']
assert proof['hardware_breakpoints_only'] and proof['compiler_program_data_writes']==proof['forced_choices']==0
assert not proof['selected'] and not proof['retail_raw_equality_claimed']
assert sha((trace/'events.jsonl').read_bytes())==proof['events_sha256']
assert sha((trace/'command.json').read_bytes())==proof['command_sha256']
for name,key in [('trace_target_globals_link.py','tracer_sha256'),('verify_graph_trace.py','verifier_sha256')]:
    assert sha((root/'evidence/tools'/name).read_bytes())==proof[key]
traced=PEImage((trace/'trace.exe').read_bytes())
tsymbols={n:int(a,16) for n,a,_ in MAP_SYMBOL.findall((trace/'trace.map').read_text())}
assert sha(native.data)==proof['baseline_pe_sha256'] and sha(traced.data)==proof['trace_pe_sha256']
for r in proof['complete_functions']:
    body=native.read(symbols[r['symbol']],r['complete_extent'])
    assert sha(body)==r['native_body_sha256'] and body==traced.read(tsymbols[r['symbol']],r['complete_extent'])
for r in proof['code_sections']:
    section=next(s for s in native.sections if s['name']==r['name'])
    body=native.read(section['address'],r['bytes'])
    assert sha(body)==r['sha256'] and body==traced.read(section['address'],r['bytes'])

fixed=root/'evidence/fixed_collision'
normal=read(fixed/'probe/normal_probe.json')
assert normal['exact'] and not normal['failures'] and len(normal['regions'])==2
assert all(r['exact'] for r in normal['regions']) and sorted(r['size'] for r in normal['regions'])==[199,260]
cluster=fixed/'probe/clusters/player_state_collision_genuine_00408030_00408100'
report=read(cluster/'report.json')
assert report['instruction_bytes_changed']==report['masked_bytes']==0
assert not report['reference_bytes_used_for_build'] and not report['constant_aliases']
assert report['normalization']['instruction_bytes_changed']==report['normalization']['address_operands_changed']==0
for name,digest in report['input_sha256'].items():assert sha(Path(name).read_bytes())==digest,name
fixed_pe=PEImage((cluster/Path(report['native_executable']).parent.name/'cluster.exe').read_bytes())
assert sha(fixed_pe.data)==report['pe_sha256']
raw=read(fixed/'probe/complete_raw_bodies.json')
assert len(raw)==36 and sum(r['raw_equal_at_fixed_va'] for r in raw)==24
assert sum(r['complete_native_extent'] for r in raw if r['raw_equal_at_fixed_va'])==2889
assert sum(r['selected_by_isolated_probe'] for r in raw)==2
for r in raw:
    a=int(r['address'],0);body=fixed_pe.read(a,r['complete_native_extent'])
    assert sha(body)==r['native_sha256'] and (body==oracle.read(a,len(body)))==r['raw_equal_at_fixed_va']
body=fixed_pe.read(0x408030,199)
assert body==oracle.read(0x408030,199) and sha(body)=='104d9d3111629b8e843a524b4be11b5d826e0b6c5e10cd08b773d07e30f9f89f'
assert fixed_pe.read(0x4281d0,174)==oracle.read(0x4281d0,174)
assert receipt['production_context_selected'] and receipt['new_recovered_bytes']==0
production=read(root/'evidence/production_exact/production_audit.json')
assert production['whole_executable']['raw_exact'] and production['whole_executable']['sha256']==receipt['retail_sha256']
assert production['actual_remaining_assembly_regions']==59 and production['actual_remaining_assembly_bytes']==89043
assert production['current_native_layouts']==964 and production['selected_functions']==1484 and production['current_unique_compiler_inputs_verified']==4030
assert (root/'evidence/production_exact/th10.exe').read_bytes()==oracle.data
assert Path('matching2/build/msvc/th10.exe').read_bytes()==oracle.data
actual_manifest=read(Path('matching2/msvc/layout/ltcg/player_state_collision_genuine_00408030_00408100.json'))
assert len(actual_manifest['functions'])==2 and len(actual_manifest['anchors'])==33
assert len(actual_manifest['anchor_roots'])==5
assert actual_manifest['context']['symbol']=='_PlayerState_Update_00425730@4'
assert not actual_manifest.get('constant_aliases') and not actual_manifest.get('data_aliases')
production_map=read(Path('matching2/msvc/regions.json'))
for name,expected_count in [('player_state_collision_genuine_00408030_00408100',2),('player_draw_and_collision_complete',6)]:
    live=Path('matching2/build/msvc/clusters')/name/'report.json'
    report=read(live)
    assert len(report['functions'])==expected_count
    assert report['instruction_bytes_changed']==report['masked_bytes']==0 and not report['reference_bytes_used_for_build']
    for path,digest in report['input_sha256'].items():assert sha(Path(path).read_bytes())==digest,path
    for function in report['functions']:
        assert sha(oracle.read(int(function['address'],0),function['size']))==function['sha256']
    artifact=root/'evidence/production_exact/clusters'/name
    archived=read(artifact/'report.json')
    pe=PEImage((artifact/Path(archived['native_executable']).parent.name/'cluster.exe').read_bytes())
    for function in archived['functions']:
        assert pe.read(int(function['address'],0),function['size'])==oracle.read(int(function['address'],0),function['size'])
for address,size,symbol in [(0x408030,199,'?Activate@PlayerCollisionRecord@@QAEHXZ'),(0x408100,260,'?Check@PlayerCollisionEngine@@QAEHPBUVec3@@MHH@Z')]:
    region=next(r for r in production_map['regions'] if int(r['address'],0)==address)
    assert region['kind']=='semantic' and region['symbol']==symbol and region['size']==size
    assert region['source']=='src/game/player_collision_00408030_00408100.cpp'
normal=PEImage((root/'evidence/production_normal/th10.exe').read_bytes())
normal_validation=read(root/'evidence/production_normal/validation.json')
assert normal_validation['passed'] and sha(normal.data)==normal_validation['sha256']
assert normal_validation['different_executable_bytes']==20828
assert normal_validation['changed_bytes_outside_equivalent_regions']==0
names={r['region'] for r in production_map['equivalent_recoveries']}
assert len(names)==8
ranges=[r for r in production_map['regions'] if r['name'] in names]
differences=0
for section in oracle.sections:
    if not section['raw_size']:continue
    a=oracle.read(section['address'],section['raw_size']);b=normal.read(section['address'],section['raw_size'])
    for offset,(x,y) in enumerate(zip(a,b)):
        if x!=y:
            address=section['address']+offset
            assert any(int(r['address'],0)<=address<int(r['address'],0)+r['size'] for r in ranges)
            differences+=1
assert differences==sum(a!=b for a,b in zip(normal.data,oracle.data))==20828
print(json.dumps({'passed':True,'genuine_functions':36,'diagnostic_exact_functions':27,
    'cases':total,'whole_owner_native_bytes':3060,'raw_selected_collision_bytes':459,
    'fixed_raw_exact_functions':24,'production_context_selected':True,'new_recovered_bytes':0,
    'current_compiler_inputs':4030,'archived_files':len(receipt['evidence_files'])}))
