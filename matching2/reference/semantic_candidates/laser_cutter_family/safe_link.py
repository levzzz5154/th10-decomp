"""Replay the actual native link below retail code to avoid callback collisions.
Only linker addresses and COFF symbol metadata change; no instruction is patched.
"""
from pathlib import Path
import json,subprocess,sys,hashlib,re
sys.path.insert(0,str(Path.cwd()))
from matching2.tools.common.wine import DEFAULT_TOOLKIT,winpath,compiler_environment
from matching2.tools.matching.ltcg_cluster import _absolute_object
from matching2.tools.matching import equivalence as eq
from matching2.tools.common.pe import PEImage
r=Path('matching2/build/experiments/laser_circle_cut_native_2026_10_06');w=r/(sys.argv[1] if len(sys.argv)>1 else 'cutter_family_current');spec=json.loads((w/'layout.json').read_text());base=0x100000
_absolute_object(w/'safe_bindings.obj',[{'symbol':n,'kind':'relative_code' if x['kind']=='code' else 'data','coff_value':int(x['address'],0)-(base if x['kind']=='code' else 0)} for n,x in sorted(spec['absolute_symbols'].items())])
command=next(x for x in json.loads((w/'commands.json').read_text()) if '/BASE:0x400000' in x);commands=[]
for address,stem in [(base,'safe'),(0x10000000,'safe_moved')]:
 arguments=[f'/BASE:{address:#x}' if x.startswith('/BASE:') else '/OUT:'+winpath(w/(stem+'.exe')) if x.startswith('/OUT:') else '/MAP:'+winpath(w/(stem+'.map')) if x.startswith('/MAP:') else winpath(w/'safe_bindings.obj') if x.endswith('\\bindings.obj') else x for x in command]
 p=subprocess.run(arguments,capture_output=True,text=True,env=compiler_environment(DEFAULT_TOOLKIT));commands.append(arguments);(w/(stem+'_link.log')).write_text(p.stdout+p.stderr);assert p.returncode==0,p.stdout+p.stderr
(w/'safe_commands.json').write_text(json.dumps(commands,indent=2)+'\n')
pe=PEImage((w/'safe.exe').read_bytes());moved=PEImage((w/'safe_moved.exe').read_bytes());linkmap=(w/'safe.map').read_text();symbols={n:int(v,16) for n,v,_ in eq.MAP_SYMBOL.findall(linkmap)};owned=sorted(int(v,16) for _,v,where in eq.MAP_SYMBOL.findall(linkmap) if where!='<absolute>');extents={section:int(size,16) for size,section in re.findall(r'^\s*\d+:[0-9a-f]+\s+([0-9a-f]+)H\s+(\S+)\s+CODE',linkmap,re.M|re.I)};bindings={symbols[n]:int(a,0) for n,a in spec['bindings'].items() if n in symbols};bindings.update({int(x['address'],0):int(x['address'],0) for x in spec['absolute_symbols'].values() if x['kind']=='code'})
# Use the ordinary diagnostic relocation algorithm at the actual first base.
# This changes only its base parameter in this process, never compiler output.
eq.IMAGE_BASE=base;records=[]
for symbol,section,address,required in spec['functions']:
 extent=extents[section];start=symbols[symbol];rows=eq.disassemble(pe.read(start,extent),start,w,section+'_safe_native');code=eq.relocate(pe,moved,rows,start,extent,0,address,bindings,owned);old=(w/(section+'_body.bin')).read_bytes();records.append({'symbol':symbol,'extent':extent,'safe_body_equals_original_after_address_binding':code==old,'body_sha256':hashlib.sha256(code).hexdigest()});assert code==old,symbol
proof={'compiler_data_writes':0,'instruction_patches':0,'ordinary_linker_relocations_only':True,'execution_image_base':hex(base),'native_pe_sha256':hashlib.sha256(pe.data).hexdigest(),'functions':records};(w/'safe_link_proof.json').write_text(json.dumps(proof,indent=2)+'\n');print(json.dumps(proof,indent=2))
