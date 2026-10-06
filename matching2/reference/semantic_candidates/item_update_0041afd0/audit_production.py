from pathlib import Path
import json,hashlib,sys
sys.path.insert(0,str(Path.cwd()))
from matching2.tools.common.pe import PEImage
p=Path('matching2/msvc');m=json.loads((p/'regions.json').read_text());built=Path('matching2/build/msvc/th10.exe').read_bytes();oracle_bytes=Path('matching2/build/oracle/th10.exe').read_bytes();assert built==oracle_bytes;oracle=PEImage(oracle_bytes)
inputs={};functions=0
for name in m['ltcg_clusters']:
 layout=json.loads((p/name).read_text());report=json.loads((Path('matching2/build/msvc/clusters')/layout['name']/'report.json').read_text());assert report['instruction_bytes_changed']==report['masked_bytes']==0;assert not report['reference_bytes_used_for_build']
 for path,digest in report['input_sha256'].items():
  assert path not in inputs or inputs[path]==digest;inputs[path]=digest
 for entry in report['compiler_includes']:
  path,digest=entry['path'],entry['sha256'];assert path not in inputs or inputs[path]==digest;inputs[path]=digest
 for f in report['functions']:
  assert hashlib.sha256(oracle.read(int(f['address'],0),f['size'])).hexdigest()==f['sha256'];functions+=1
for path,digest in inputs.items():assert hashlib.sha256(Path(path).read_bytes()).hexdigest()==digest,path
semantic=[x for x in m['regions'] if x['kind']=='semantic'];equivalent={x['region'] for x in m['equivalent_recoveries']};assembly=[x for x in m['regions'] if x['kind']=='asm' and x['name'] not in equivalent]
result={'whole_executable':{'bytes':len(built),'raw_exact':True,'sha256':hashlib.sha256(built).hexdigest()},'current_native_layouts':len(m['ltcg_clusters']),'selected_functions':functions,'current_unique_compiler_inputs_verified':len(inputs),'ordinary_cpp_regions':len(semantic),'ordinary_cpp_bytes':sum(x['size'] for x in semantic),'actual_remaining_assembly_regions':len(assembly),'actual_remaining_assembly_bytes':sum(x['size'] for x in assembly),'all_four_cutters_remain_assembly':all(next(x for x in m['regions'] if int(x['address'],0)==a)['kind']=='asm' for a in [0x41d880,0x41dd80,0x41eb00,0x41efa0]),'new_recovered_bytes':0,'instruction_bytes_changed':0,'masked_bytes':0,'reference_bytes_used_for_build':False}
Path('matching2/build/experiments/item_update_2026_10_06/production_audit.json').write_text(json.dumps(result,indent=2)+'\n');print(json.dumps(result,indent=2))
