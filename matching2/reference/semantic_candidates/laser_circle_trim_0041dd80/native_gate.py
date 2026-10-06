from pathlib import Path
import json,shutil,sys,struct,traceback,hashlib
ROOT=Path.cwd();sys.path.insert(0,str(ROOT))
from matching2.tools.matching.ltcg_cluster import load_cluster,build_cluster,BASE_FLAGS
from matching2.tools.common.wine import DEFAULT_TOOLKIT
from matching2.tools.common.pe import PEImage
r=(ROOT/'matching2/build/experiments/laser_circle_cut_native_2026_10_06').resolve();kind='circle_trim'
address=0x41dd80;size=1238;name='laser_'+kind+'_00'+format(address,'x')
c=Path(__file__).parent.resolve();diag=c/'evidence'
p=r/(kind+'_followup_project');shutil.copytree(ROOT/'matching2/msvc',p,dirs_exist_ok=True)
folder=Path('layout/ltcg')/name;d=p/folder;d.mkdir(exist_ok=True);source='src/game/'+name+'.cpp'
s=json.loads((c/'layout.json').read_text());comparison=json.loads((diag/'diagnostic_comparison.json').read_text());extents={f['symbol']:f['extent'] for f in comparison['functions']}
for file in [*c.glob('*.cpp'),*c.glob('*.hpp')]:
 if file.name=='laser.cpp':continue
 text=file.read_text().replace('"th10/game/item_spawn_0041bb00.hpp"','"item_types.hpp"');(d/file.name).write_text(text)
(d/'item_types.hpp').write_bytes((c/'include/th10/game/item_spawn_0041bb00.hpp').read_bytes());(p/'include/th10/game/laser_spawn_0041c510.hpp').write_bytes((c/'include/th10/game/laser_spawn_0041c510.hpp').read_bytes())
(p/source).write_text((c/'laser.cpp').read_text().replace('"types.hpp"','"../../'+str(folder/'types.hpp')+'"'))
(d/'driver.cpp').write_text('#include "../../../'+source+'"\nstruct StageUpdateContext;\nextern "C" int __stdcall StageUpdate(StageUpdateContext*);\n#pragma code_seg(".text$entry")\nvoid __fastcall StageUpdateCompilerCaller_004187c0(void* context) {StageUpdate(reinterpret_cast<StageUpdateContext*>(context));}\n#pragma code_seg()\n')
entries=sorted(s['functions']+[['?StageUpdateCompilerCaller_004187c0@@YIXPAX@Z','.text$entry',0x4187c0,7]],key=lambda f:f[2]);functions=[];anchors=[];context=None;gaps=[];sections={};previous=0x401000
for i,(symbol,old_section,a,required) in enumerate(entries):
 section=f'.text${i:02d}bbody';extent=extents.get(symbol,required);declared=size if a==address else extent
 if a>previous:gaps.append({'section':f'.text${i:02d}agap','address':hex(previous),'size':a-previous})
 item={'name':symbol,'symbol':symbol,'section':section,'address':hex(a),'size':declared}
 if a==address:functions.append(item|{'actual_abi':'Public ECX member; three stack arguments, integer EAX hit count, RET12; complete required extent.'})
 elif a==0x4187c0:context={k:v for k,v in item.items() if k!='name'}|{'description':'Complete actual StageUpdate wrapper; no synthetic caller.'}
 else:anchors.append(item)
 sections[old_section]=section;previous=a+declared
for file in [p/source,*d.glob('*.cpp')]:
 text=file.read_text()
 for old,new in sections.items():text=text.replace('"'+old+'"','"'+new+'"')
 file.write_text(text)
absolute=[{'symbol':k,'address':v['address'],'kind':('relative_code' if v['kind']=='code' else 'metadata' if k=='__fltused' else 'data')} for k,v in s['absolute_symbols'].items()];absolute.append({'symbol':'_StageUpdate@4','address':'0x418190','kind':'relative_code'})
constant_symbols=['__real@40c00000','__real@41400000','__real@41900000']+(['__real@42000000','__real@c3400000','__real@43400000','__real@43e00000','__real@43600000','__real@41800000'] if kind=='circle_trim' else ['__real@3f000000'])
aliases=[{'symbol':symbol,'address':s['bindings'][symbol],'value':struct.unpack('<f',bytes.fromhex(symbol[7:])[::-1])[0]} for symbol in constant_symbols]
headers=[str(folder/f.name) for f in d.glob('*.hpp')]+['include/th10/game/laser_spawn_0041c510.hpp','include/th10/game/entity.hpp','include/th10/math/timer.hpp','include/th10/types.hpp','include/th10/render/animation_public_callers.hpp','include/th10/game/entity_script_start.hpp']
layout={'schema_version':1,'name':name,'source':source,'driver':str(folder/'driver.cpp'),'additional_sources':[str(folder/name) for name in s['sources'][1:]],'headers':headers,'included_sources':[],'image_base':'0x400000','description':'Complete cutter with complete actual typed supporting callees. Fixed-address gate, no promotion without complete raw equality.','functions':functions,'anchors':anchors,'context':context,'gaps':gaps,'constants':[],'constant_aliases':aliases,'absolute_symbols':absolute,'roots':[s['entry_symbol']],'anchor_roots':['?SetPolar@ItemPolarVelocity_0041bb00@@QAEPAU1@MM@Z']}
rel=str(folder)+'.json';(p/rel).write_text(json.dumps(layout,indent=2)+'\n')
m=json.loads((p/'regions.json').read_text());target=next(t for t in m['regions'] if int(t['address'],0)==address);oldsource=target['source'];target.update(source=source,symbol=s['entry_symbol'],kind='semantic',ltcg_layout=rel)
old=(p/oldsource).read_text();start=old.index('extern "C" __declspec(naked) void __cdecl asm_FUN_00'+format(address,'x')+'_00'+format(address,'x')+'()');end=old.find('extern "C" __declspec(naked)',start+20);(p/oldsource).write_text(old[:start]+(old[end:] if end>=0 else ''))
(p/'regions.json').write_text(json.dumps(m,indent=2)+'\n')
output=r/(kind+'_followup_native')
try:
 spec=load_cluster(p,rel,m['regions']);result=build_cluster(spec,DEFAULT_TOOLKIT,output,BASE_FLAGS)
 pe=PEImage(Path(result['native_build']['native_executable']).read_bytes());oracle=PEImage(Path('matching2/build/oracle/th10.exe').read_bytes());a=pe.read(address,size);b=oracle.read(address,size)
 supporting=[]
 for f in layout['anchors']:
  a2=pe.read(int(f['address'],0),f['size']);b2=oracle.read(int(f['address'],0),f['size']);supporting.append({'address':f['address'],'symbol':f['symbol'],'bytes':f['size'],'raw_exact':a2==b2,'sha256':hashlib.sha256(a2).hexdigest()})
 record={'native_structural_gate_passed':True,'raw_exact':a==b,'raw_different_bytes':sum(x!=y for x,y in zip(a,b)),'native_body_sha256':hashlib.sha256(a).hexdigest(),'retail_body_sha256':hashlib.sha256(b).hexdigest(),'report':result['native_report'],'supporting':supporting}
except Exception as error:record={'native_structural_gate_passed':False,'raw_exact':False,'exception':type(error).__name__,'reason':str(error),'traceback':traceback.format_exc()}
record.update({'address':hex(address),'required_extent':size,'production_mutated':False,'promotion':False,'instruction_bytes_changed':0,'masked_bytes':0,'reference_bytes_used_for_build':False})
(r/(kind+'_followup_native_receipt.json')).write_text(json.dumps(record,indent=2)+'\n');print(json.dumps({k:v for k,v in record.items() if k!='traceback'},indent=2))
