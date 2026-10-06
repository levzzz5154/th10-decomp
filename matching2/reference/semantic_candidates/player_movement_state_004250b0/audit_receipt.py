"""Verify the sealed genuine graph, bounded behavior, raw selection and production result."""
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
read=lambda path:json.loads(path.read_text())
receipt=read(root/'receipt.json')
for group in ['candidate_sources','evidence_files','reference_inputs']:
    for name,digest in receipt[group].items():
        path=Path(name) if group=='reference_inputs' else root/name
        assert sha(path.read_bytes())==digest,name
checkpoint=root/'evidence/genuine_graph'
for name,digest in read(checkpoint/'input_hashes.json').items():
    path=Path(name)
    if path.resolve()==Path('matching2/msvc/regions.json').resolve():path=root/'evidence/production_before/regions.json'
    assert sha(path.read_bytes())==digest,name
for name,digest in read(checkpoint/'compiler_hashes.json').items():
    assert sha((Path(DEFAULT_TOOLKIT)/'bin'/name).read_bytes())==digest,name
layout=read(root/'layout.json');rows=read(checkpoint/'comparison.json')['functions']
assert len(layout['functions'])==len({f[2] for f in layout['functions']})==len(rows)==40
assert len(layout['roots'])==6 and not any('Move@' in symbol for symbol in layout['roots'])
assert '?Move@PlayerState@@QAEHXZ' not in layout['absolute_symbols']
assert sum(r['exact'] for r in rows)==30
assert sum(r['extent'] for r in rows if r['exact'])==3536
native=PEImage((checkpoint/'model.exe').read_bytes())
symbols={name:int(address,16) for name,address,_ in MAP_SYMBOL.findall((checkpoint/'model.map').read_text())}
retail=PEImage(Path('matching2/build/oracle/th10.exe').read_bytes())
assert sha(retail.data)==receipt['retail_sha256']
changed=[]
for symbol,section,address,size in layout['functions']:
    row=next(r for r in rows if r['symbol']==symbol)
    body=(checkpoint/(section+'_body.bin')).read_bytes()
    assert len(body)==row['extent'] and (body==retail.read(address,size))==row['exact']
    assert sum(a!=b for a,b in zip(body,retail.read(address,size)))==row['different_overlapping_bytes']
    assert (checkpoint/(section+'_retail_full.bin')).read_bytes()==retail.read(address,size)
    assert native.read(symbols[symbol],row['extent'])==(checkpoint/(section+'_full_native.bin')).read_bytes()
    prior=root/'evidence/prior_graph'/(section+'_body.bin')
    if prior.exists() and prior.read_bytes()!=body:changed.append(symbol)
assert changed==['_PlayerState_Update_00425730@4']
for symbol,extent,required,tables in [('?Move@PlayerState@@QAEHXZ',1640,1656,64),('_PlayerState_Update_00425730@4',3044,3112,20)]:
    row=next(r for r in rows if r['symbol']==symbol)
    assert (row['extent'],row['required'],row['native_table_bytes'],row['retail_table_bytes'])==(extent,required,tables,tables)

total=0
for name,count,artifact,field in [
    ('differential',1965,'observations.json','observations_sha256'),
    ('effect_differential',215,'effect_observations.json','observations_file_sha256'),
    ('sequence_differential',328,'sequence_observations.json','observations_sha256'),
    ('spawn_differential',186,'spawn_observations.json','observations_sha256'),
    ('schedule_differential',312,'schedule_observations.json','observations_sha256'),
    ('player_differential',947,'player_observations.json','observations_sha256'),
    ('collision_differential',1557,'collision_observations.json','observations_sha256'),
    ('item_differential',1574,'item_observations.json','observations_sha256'),
    ('movement_differential',2186,'movement_observations.json','observations_sha256')]:
    report=read(checkpoint/(name+'.json'))
    assert report['cases']==count and not report.get('failures')
    assert not report.get('smoke') and not report.get('limited_run')
    assert sha((checkpoint/artifact).read_bytes())==report[field]
    if 'native_pe_sha256' in report:assert report['native_pe_sha256']==sha(native.data)
    if 'cases_sha256' in report:assert sha((checkpoint/(name.split('_')[0]+'_cases.json')).read_bytes())==report['cases_sha256']
    total+=count
assert total==9270 and read(checkpoint/'effect_differential.json')['passed']
movement=read(checkpoint/'movement_differential.json')
for name,count in {'movement':1923,'stop_frame':700,'set_position':552,'translated_position':1352,'loader':1169}.items():
    assert movement['executed_helper_calls'][name]==count
# Hooks observe the complete movement entry; only separate callbacks are scripted.
fixture=(root/'differential.py').read_text()
assert "if address==0x4250b0:" not in fixture
assert "(MOVE,0x4250b0,'movement')" in fixture

manifest=read(root/'evidence/production_source/layout/ltcg/player_movement_animation_genuine_00449210_004492f0.json')
assert len(manifest['functions'])==2 and len(manifest['anchors'])==37
assert not manifest['constants'] and not manifest.get('constant_aliases') and not manifest.get('data_aliases')
raw=read(root/'evidence/raw_fixed_graph.json')
assert raw['complete_functions']==40 and (raw['raw_exact_functions'],raw['raw_exact_bytes'])==(26,3033)
fixed_folder=root/'evidence/production_probe/clusters'/manifest['name']
fixed=PEImage(next(fixed_folder.glob('native-*/cluster.exe')).read_bytes())
for row in raw['functions']:
    body=fixed.read(int(row['address'],0),row['extent'])
    assert sha(body)==row['sha256']
    assert row['raw_exact']==(row['extent']==row['required'] and body==retail.read(int(row['address'],0),row['required']))
for f in manifest['functions']:
    address=int(f['address'],0)
    assert fixed.read(address,f['size'])==retail.read(address,f['size'])
probe=read(root/'evidence/production_probe.json');assert probe['exact'] and not probe['failures']
assert all(row['exact'] and row['different_bytes']==0 for row in probe['regions'])
for source in [*root.glob('*.cpp'),*root.glob('*.hpp'),*(root/'include').rglob('*.hpp')]:
    assert '__asm' not in source.read_text() and '__declspec(naked)' not in source.read_text(),source

config=read(Path('matching2/msvc/regions.json'))
current_manifest=Path('matching2/msvc/layout/ltcg')/(manifest['name']+'.json')
assert read(current_manifest)==manifest
assert len(config['ltcg_clusters'])==965
before=read(root/'evidence/production_before/regions.json')
assert len(config['regions'])==len(before['regions'])
assert config['equivalent_recoveries']==before['equivalent_recoveries']
deltas=[]
for old,new in zip(before['regions'],config['regions']):
    if old!=new:
        assert int(old['address'],0) in [0x449210,0x4492f0]
        assert {k:v for k,v in old.items() if k not in ['source','symbol','section']}=={k:v for k,v in new.items() if k not in ['source','symbol','section']}
        deltas.append(int(old['address'],0))
assert deltas==[0x449210,0x4492f0]
assert config['ltcg_clusters'][:-1]==before['ltcg_clusters']
# Check every current production native report and its compiler inputs.
inputs={};selected=0
for name in config['ltcg_clusters']:
    item=read(Path('matching2/msvc')/name)
    report=read(Path('matching2/build/msvc/clusters')/item['name']/'report.json')
    assert report['instruction_bytes_changed']==report['masked_bytes']==0
    assert not report['reference_bytes_used_for_build']
    for path,digest in report['input_sha256'].items():
        assert path not in inputs or inputs[path]==digest
        inputs[path]=digest
    for include in report['compiler_includes']:
        path,digest=include['path'],include['sha256']
        assert path not in inputs or inputs[path]==digest
        inputs[path]=digest
    for f in report['functions']:
        assert sha(retail.read(int(f['address'],0),f['size']))==f['sha256']
        selected+=1
assert selected==1484 and len(inputs)==4069
for path,digest in inputs.items():assert sha(Path(path).read_bytes())==digest,path
assert Path('matching2/build/msvc/th10.exe').read_bytes()==retail.data
assert (root/'evidence/production_exact/th10.exe').read_bytes()==retail.data
normal=PEImage((root/'evidence/production_normal/th10.exe').read_bytes())
proof=read(root/'evidence/production_normal/validation.json')
assert sha(normal.data)==proof['sha256']=='90baebd89fba038d46f807881bdfa76f218742f446f8f4c4b3b93b732cabcaab'
equivalent={r['region'] for r in config['equivalent_recoveries']}
ranges=[(int(r['address'],0),int(r['address'],0)+r['size']) for r in config['regions'] if r['name'] in equivalent]
assert len(normal.data)==len(retail.data)==487936
unequal=0
for offset,(a,b) in enumerate(zip(normal.data,retail.data)):
    if a==b:continue
    address=next((s['address']+offset-s['raw_offset'] for s in retail.sections if s['raw_offset']<=offset<s['raw_offset']+s['raw_size']),None)
    assert address is not None and any(lo<=address<hi for lo,hi in ranges)
    unequal+=1
assert unequal==proof['different_bytes']==20828
print(json.dumps({'genuine_complete_functions':40,'diagnostic_exact_functions':30,'raw_fixed_functions':26,'bounded_cases':total,'selected_whole_functions':2,'selected_bytes':144,'production_native_layouts':965,'selected_native_functions':selected,'current_compiler_inputs_verified':len(inputs),'raw_exact_executable_bytes':len(retail.data),'new_recovered_bytes':0,'remaining_assembly_regions':59,'remaining_assembly_bytes':89043,'equivalent_owners':8,'evidence_files_verified':len(receipt['evidence_files'])},indent=2))
