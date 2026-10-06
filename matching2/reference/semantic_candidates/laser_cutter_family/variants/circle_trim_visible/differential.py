from pathlib import Path
import json,hashlib,sys,importlib.util
sys.path.insert(0,str(Path.cwd()))
from matching2.tools.common.pe import PEImage
from matching2.tools.matching.equivalence import MAP_SYMBOL
path=Path('matching2/reference/semantic_candidates/laser_circle_trim_0041dd80/differential.py');spec=importlib.util.spec_from_file_location('circle_fixture',path);m=importlib.util.module_from_spec(spec);sys.modules['circle_fixture']=m;spec.loader.exec_module(m)
folder=Path('matching2/build/experiments/laser_circle_cut_native_2026_10_06')/(sys.argv[1] if len(sys.argv)>1 else 'circle_trim_visible_creator_maintained');retail=PEImage(Path('matching2/build/oracle/th10.exe').read_bytes());native=PEImage((folder/'model.exe').read_bytes());symbols={s:int(a,16) for s,a,_ in MAP_SYMBOL.findall((folder/'model.map').read_text())};old=m.Uc
m.Uc=lambda *args,**kwargs: new_uc(*args,**kwargs)
def new_uc(*args,**kwargs):
 uc=old(*args,**kwargs);uc.mem_map(0x100000,0x10000);return uc
observations=[]
for i,case in enumerate(m.cases()):
 expected=m.run(retail,None,0x41dd80,{},case);actual=m.run(retail,native,symbols['?TrimCircle@TrimLaser@@UAEHPBUCutVector@@MH@Z'],symbols,case)
 if actual!=expected:
  (folder/'differential_failure.json').write_text(json.dumps({'case':i,'input':m.asdict(case),'difference':{k:{'retail':expected[k],'native':actual[k]} for k in expected if expected[k]!=actual[k]}},indent=2)+'\n');raise AssertionError(i)
 observations.append(actual)
 if i%25==0:print('passed',i+1,flush=True)
report={'passed':True,'cases':len(observations),'native_pe_sha256':hashlib.sha256(native.data).hexdigest(),'fixture_sha256':hashlib.sha256(path.read_bytes()).hexdigest(),'instruction_patches':0,'execution_image_base':'0x100000','calls':{k:sum(x['calls'].count(k) for x in observations) for k in ['item','effect','laser']},'observation_sha256':hashlib.sha256(json.dumps(observations,sort_keys=True).encode()).hexdigest(),'scope':'Complete circular trim with fully visible typed creator, complete supporting native graph, and unchanged maintained fixtures and scripted shared boundaries. Bounded execution evidence only; extent is still one byte short.'}
(folder/'differential_report.json').write_text(json.dumps(report,indent=2)+'\n');print(json.dumps(report,indent=2))
