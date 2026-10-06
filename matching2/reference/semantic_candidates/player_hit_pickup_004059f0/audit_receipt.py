"""Verify maintained inputs, archived artifacts and the production audit."""
import hashlib
import json
import sys
from pathlib import Path
sys.path.insert(0,str(Path.cwd()))
from matching2.tools.common.pe import PEImage

root=Path(__file__).resolve().parent
receipt=json.loads((root/'receipt.json').read_text())
for key in ['candidate_sources','evidence_files']:
    for name,digest in receipt[key].items():
        path=root/name
        assert hashlib.sha256(path.read_bytes()).hexdigest()==digest,name
for name,digest in json.loads((root/'evidence/retained_corner_graph/input_hashes.json').read_text()).items():
    assert hashlib.sha256(Path(name).read_bytes()).hexdigest()==digest,name
comparison=json.loads((root/'evidence/retained_corner_graph/comparison.json').read_text())
assert len(comparison['functions'])==15
assert sum(x['exact'] for x in comparison['functions'])==9
sweep=next(x for x in comparison['functions'] if 'Sweep@' in x['symbol'])
assert (sweep['extent'],sweep['required'],sweep['different_overlapping_bytes'],len(sweep['hunks']))==(1171,1170,1012,61)
native_body=(root/'evidence/retained_corner_graph/.text$20sweep_body.bin').read_bytes()
retail_body=(root/'evidence/retained_corner_graph/.text$20sweep_retail_full.bin').read_bytes()
assert next(i for i,(a,b) in enumerate(zip(native_body,retail_body)) if a!=b)==0x17
assert native_body[2]==retail_body[2]==64
behavior=json.loads((root/'evidence/retained_corner_graph/differential.json').read_text())
assert behavior['cases']==1837 and not behavior['failures']
assert hashlib.sha256((root/'evidence/retained_corner_graph/observations.json').read_bytes()).hexdigest()==behavior['observations_sha256']
controls=json.loads((root/'evidence/frame_controls/ledger.json').read_text())
assert len(controls)==23 and all(x['genuine_functions']==15 and not x['selected'] for x in controls)
for control in controls:
    name=control['control']
    archive=root/'evidence/frame_controls'/name/'native'
    source_root=Path('matching2/build/experiments/player_hit_pickup_2026_10_06/shape_controls').resolve()/name
    for path,digest in json.loads((archive/'input_hashes.json').read_text()).items():
        path=Path(path)
        if path.is_relative_to(source_root):
            assert hashlib.sha256((archive/'inputs'/path.relative_to(source_root)).read_bytes()).hexdigest()==digest,(name,path)
for trace,control in [('trace_corner_globals','four_vec3_yfloat_early'),
                      ('trace_corner_stack_conflicts','angle_float_vec3')]:
    traced=PEImage((root/'evidence/compiler_traces'/trace/'trace.exe').read_bytes())
    native=PEImage((root/'evidence/frame_controls'/control/'native/model.exe').read_bytes())
    proof=json.loads((root/'evidence/compiler_traces'/trace/'proof.json').read_text())
    assert proof['native_code_equal'] and proof['compiler_data_writes']==proof['instruction_patches']==0
    for section in proof['code_sections']:
        address=next(x['address'] for x in native.sections if x['name']==section['section'])
        code=native.read(address,section['bytes'])
        assert code==traced.read(address,section['bytes'])
        assert hashlib.sha256(code).hexdigest()==section['sha256']
audit=json.loads((root/'evidence/production_audit.json').read_text())
assert audit['whole_executable']['raw_exact'] and audit['actual_remaining_assembly_regions']==60
assert receipt['new_recovered_bytes']==0 and receipt['selected'] is False
print(json.dumps({'candidate_inputs':len(receipt['candidate_sources']),
    'archived_artifacts':len(receipt['evidence_files']),'genuine_functions':15,
    'bounded_comparisons':behavior['cases'],'selected':False,'new_recovered_bytes':0,
    'whole_executable':audit['whole_executable']},indent=2))
