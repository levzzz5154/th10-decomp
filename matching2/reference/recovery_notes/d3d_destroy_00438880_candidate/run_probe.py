from pathlib import Path
import sys,json,subprocess,struct,os
ROOT=Path('/home/levzzz/Games/th10Decomp');sys.path.insert(0,str(ROOT))
from matching2.tools.matching.ltcg_cluster import _absolute_object,_prepare_padding_object,BASE_FLAGS
from matching2.tools.matching.ltcg_semantic import PEImage,parse_map,_run_logged
from matching2.tools.common.wine import compiler_environment,winpath
P=Path(__file__).parent;project=P/'msvc';tool=Path.home()/'.local/share/th10-toolchains/msvc-13.10.6030';env=compiler_environment(tool)
variant=sys.argv[1] if len(sys.argv)>1 else 'attempt01';out=P/variant;out.mkdir(exist_ok=True)
src=out/'cluster.cpp'
incs=['src/render/d3_d_resource_manager_destroy_00438880.cpp','layout/ltcg/destroy_release_adapter.cpp','src/platform/platform_stop_worker_0044c150.cpp','src/platform/platform_stop_worker_no_delete_0044c130.cpp','layout/ltcg/d3d_list_release_context.cpp']
src.write_text('\n'.join('#include "'+str(project/x)+'"' for x in incs[:4])+'\n#pragma code_seg(".text$30context")\nvoid __stdcall ReleaseContext(ResourceList_DestroyABI_00449e50** lists, int n, Scheduler* owner) { while(n--) (*lists++)->Release(owner); }\n')
abs=[]
for j in ['d3d_list_release.json','dtor_delete_0040b920.json']:
 for a in json.loads((project/'layout/ltcg'/j).read_text())['absolute_symbols']:
  if a['symbol'] not in [x['symbol'] for x in abs]:abs.append(a)
abs += [{'symbol':'__except_list','address':0,'kind':'metadata'},{'symbol':'??3@YAXPAX@Z','address':0x4524a1,'kind':'relative_code'},{'symbol':'?g_destroy_worker_00438880@@3UPlatformWorker@@A','address':0x492254,'kind':'data'},{'symbol':'___CxxFrameHandler','address':0x46276d,'kind':'relative_code'}]
for a in abs:
 a['address']=int(a['address'],0) if isinstance(a['address'],str) else a['address'];a['coff_value']=a['address']-0x400000 if a['kind']=='relative_code' else a['address']
_absolute_object(out/'bindings.obj',abs)
_run_logged(['wine',str(tool/'bin/cl.exe'),*BASE_FLAGS,'/EHsc','/GL','/I'+winpath(project/'include'),'/Fo'+winpath(out/'cluster.obj'),winpath(src)],env,out,out/'compile.log',180)
# Place actual complete contributions, never adjust emitted instruction bytes.
gaps=[('.text$000gap',0x438880-0x401000)]
if (P/'sizes.json').exists():
 sizes=json.loads((P/'sizes.json').read_text())
 if '.text$00listclear' in sizes:
  gaps += [('.text$00destroyz',0x449a90-0x438880-sizes['.text$00destroy']),('.text$00listclearz',0x449e50-0x449a90-sizes['.text$00listclear']),('.text$01releasez',0x44c130-0x449e50-sizes['.text$01release']),('.text$10callerz',0x44c150-0x44c130-sizes['.text$10caller'])]
gaps += [('.text$90gap',0x465350-0x44c1f0-5),('.xdata$0gap',0x4713b4-0x466000)]
layout=out/'layout.cpp';layout.write_text('\n'.join('#pragma section("'+s+'",read'+(',execute' if s.startswith('.text') else '')+')\nextern "C" __declspec(allocate("'+s+'")) char gap'+str(i)+'['+str(n)+']={0};' for i,(s,n) in enumerate(gaps)))
_run_logged(['wine',str(tool/'bin/cl.exe'),*BASE_FLAGS,'/Fo'+winpath(out/'layout.obj'),winpath(layout)],env,out,out/'layout.log',180)
_prepare_padding_object(out/'layout.obj',out/'layout-fixed.obj',[{'section':s,'size':n,'symbol':'_gap'+str(i)} for i,(s,n) in enumerate(gaps)])
symbol='??1D3DResourceManager_Destroy_00438880@@QAE@XZ'
entry='?D3DResourceManager_Destroy_00438880@@YGXPAU0@@Z'
cmd=['wine',str(tool/'bin/link.exe'),'/nologo','/LTCG','/MACHINE:X86','/BASE:0x400000','/FILEALIGN:512','/SUBSYSTEM:WINDOWS','/ENTRY:'+entry,'/FIXED','/INCREMENTAL:NO','/NODEFAULTLIB','/OPT:REF','/OPT:NOICF','/SAFESEH:NO','/INCLUDE:?StopNoDelete@PlatformWorker@@QAEXXZ','/INCLUDE:?ReleaseContext@@YGXPAPAUResourceList_DestroyABI_00449e50@@HPAUScheduler@@@Z',*['/INCLUDE:_gap'+str(i) for i in range(len(gaps))],'/OUT:'+winpath(out/'cluster.exe'),'/MAP:'+winpath(out/'cluster.map'),winpath(out/'cluster.obj'),winpath(out/'bindings.obj'),winpath(out/'layout-fixed.obj')]
_run_logged(cmd,env,out,out/'link.log',300)
m=parse_map((out/'cluster.map').read_text());pe=PEImage.from_path(out/'cluster.exe');ret=PEImage.from_path(ROOT/'matching2/build/msvc/th10.exe')
sizes={c.name:c.length for c in m.contributions};(P/'sizes.json').write_text(json.dumps(sizes,indent=2))
report={'commands':cmd,'contributions':sizes,'functions':[]}
for name,target,size in [(symbol,0x438880,103),('?Release@ResourceList_DestroyABI_00449e50@@QAEXPAUScheduler@@@Z',0x449e50,82),('?Stop@PlatformWorker@@QAEXXZ',0x44c150,101)]:
 sy=next(s for s in m.symbols if s.name==name);c=next(c for c in m.contributions if c.segment==sy.segment and c.start<=sy.offset<c.end)
 body=pe.read(sy.address,c.end-sy.offset)[0];oracle=ret.read(target,size)[0];diff=next((i for i,(a,b) in enumerate(zip(body,oracle)) if a!=b),None)
 f={'symbol':name,'address':hex(sy.address),'extent':len(body),'expected_extent':size,'first_diff':diff,'candidate_hex':body.hex(),'retail_hex':oracle.hex(),'exact':body==oracle};report['functions'].append(f)
report['eh_evidence']=[]
for target,size in [(0x449a90,12),(0x465350,29),(0x4713b4,44)]:
 body=pe.read(target,size)[0];oracle=ret.read(target,size)[0]
 report['eh_evidence'].append({'address':hex(target),'size':size,'exact':body==oracle,'candidate_hex':body.hex(),'retail_hex':oracle.hex()})
import hashlib
report['inputs']={str(project/x):hashlib.sha256((project/x).read_bytes()).hexdigest() for x in incs[:4]}
for x in incs[:4]:
 snapshot=out/'inputs'/x;snapshot.parent.mkdir(parents=True,exist_ok=True);snapshot.write_bytes((project/x).read_bytes())
report['toolchain']={x:hashlib.sha256((tool/'bin'/x).read_bytes()).hexdigest() for x in ['cl.exe','c1.dll','c1xx.dll','c2.dll','link.exe']}
report['candidate_exact_requires_extent_and_address']=True
(out/'report.json').write_text(json.dumps(report,indent=2));print(json.dumps(report,indent=2))
res=subprocess.run(['objdump','-d',str(out/'cluster.exe')],capture_output=True,text=True);(out/'disassembly.txt').write_text(res.stdout)
