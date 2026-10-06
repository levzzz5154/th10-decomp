"""Execute all four full cutter owners and the shared native helper graph."""
import importlib.util,json,sys,hashlib
from pathlib import Path
sys.path.insert(0,str(Path.cwd()))
from matching2.tools.common.pe import PEImage
from matching2.tools.matching.equivalence import MAP_SYMBOL
r=Path('matching2/build/experiments/laser_circle_cut_native_2026_10_06');folder=r/(sys.argv[1] if len(sys.argv)>1 else 'cutter_family_current');retail=PEImage(Path('matching2/build/oracle/th10.exe').read_bytes());native=PEImage((folder/'safe.exe').read_bytes());symbols={s:int(a,16) for s,a,_ in MAP_SYMBOL.findall((folder/'safe.map').read_text())};reports=[]
for owner,address,method,size in [('laser_rectangle_trim_0041d880',0x41d880,'TrimRectangle',1269),('laser_circle_trim_0041dd80',0x41dd80,'TrimCircle',1238),('laser_rectangle_cut_0041eb00',0x41eb00,'CutRectangle',1171),('laser_circle_cut_0041efa0',0x41efa0,'CutCircle',1108)]:
 path=Path('matching2/reference/semantic_candidates')/owner/'differential.py';spec=importlib.util.spec_from_file_location(owner,path);m=importlib.util.module_from_spec(spec);sys.modules[owner]=m;spec.loader.exec_module(m)
 # The execution image is linked below retail so shared API hooks cannot hit
 # a native instruction with the same numeric address. Map the real PE pages.
 original_uc=m.Uc
 def execution_uc(*args,**kwargs):
  uc=original_uc(*args,**kwargs);uc.mem_map(0x100000,0x10000);return uc
 m.Uc=execution_uc
 assert all(0x100000<=sec['address'] and sec['address']+sec['raw_size']<=0x110000 for sec in native.sections)
 entry=next(symbols[x] for x in symbols if x.startswith('?'+method+'@') and '@@UAEH' in x);observations=[]
 for i,case in enumerate(m.cases()):
  expected=m.run(retail,None,address,{},case);actual=m.run(retail,native,entry,symbols,case)
  if expected!=actual:
   (folder/(method+'_failure.json')).write_text(json.dumps({'case':i,'input':m.asdict(case),'difference':{k:{'retail':expected[k],'native':actual[k]} for k in expected if expected[k]!=actual[k]}},indent=2)+'\n');raise AssertionError((method,i))
  observations.append(actual)
  if i%25==0: print(method,'passed',i+1,flush=True)
 report={'method':method,'address':hex(address),'passed':True,'cases':len(observations),'native_pe_sha256':hashlib.sha256(native.data).hexdigest(),'retail_body_sha256':hashlib.sha256(retail.read(address,size)).hexdigest(),'fixture_sha256':hashlib.sha256(path.read_bytes()).hexdigest(),'instruction_patches':0,'calls':{k:sum(x['calls'].count(k) for x in observations) for k in ['item','effect','laser']},'observation_sha256':hashlib.sha256(json.dumps(observations,sort_keys=True).encode()).hexdigest()}
 reports.append(report);(folder/'family_differential_report.json').write_text(json.dumps({'scope':'Full native cutter family with complete shared helpers. Individual maintained fixtures and shared scripted boundaries apply. Bounded execution evidence, not raw equality or full game integration.','functions':reports},indent=2)+'\n');print(report,flush=True)
