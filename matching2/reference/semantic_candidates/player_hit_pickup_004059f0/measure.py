"""Measure complete native extents after address-only rebinding; no promotion."""
import hashlib,json,re,sys,subprocess
from pathlib import Path
sys.path.insert(0,str(Path.cwd()))
from matching2.tools.common.pe import PEImage
from matching2.tools.common.wine import DEFAULT_TOOLKIT,winpath
from matching2.tools.matching.equivalence import MAP_SYMBOL,build_model,disassemble,relocate,normalize,find_differences
from matching2.tools.matching import equivalence as eq
# Keep this larger native graph below retail code. Set the normalizer and
# absolute COFF symbol generator to the same real linker base.
eq.IMAGE_BASE=0x100000
project=Path('matching2/msvc').resolve()
root=Path(__file__).resolve().parent
work=Path('matching2/build/experiments/player_hit_pickup_2026_10_06').resolve()/(sys.argv[1] if len(sys.argv)>1 else 'maintained_graph')
work.mkdir(parents=True,exist_ok=True)
spec=json.loads((root/'layout.json').read_text())
spec['source_paths']=[root/source for source in spec['sources']]
if '--reuse' not in sys.argv:
 inputs=[root/'layout.json',root/'measure.py',root/'differential.py',
         *root.glob('*.cpp'),*root.glob('*.hpp'),*(root/'include').rglob('*.hpp')]
 for source in inputs:
  target=work/'inputs'/source.relative_to(root)
  target.parent.mkdir(parents=True,exist_ok=True)
  target.write_bytes(source.read_bytes())
  if source.suffix=='.cpp' or source.name=='layout.json':
   (work/source.name).write_bytes(source.read_bytes())
 (work/'input_hashes.json').write_text(json.dumps({str(p):hashlib.sha256(p.read_bytes()).hexdigest()
     for p in [*inputs,*(project/'include').rglob('*.hpp')]},indent=2)+'\n')
flags=json.loads((project/'regions.json').read_text())['flags']
commands=[]
ordinary_run=subprocess.run
def rooted_run(command,*args,**kwargs):
 if len(command)>1 and str(command[1]).endswith('/cl.exe'):
  command=[*command[:2],'/I'+winpath(root/'include'),*command[2:]]
  target=next((x[3:] for x in command if str(x).startswith('/Fo')),None)
  if target:
   obj=Path(target.replace('Z:', '').replace('\\','/'))
   source=Path(str(command[-1]).replace('Z:', '').replace('\\','/'))
   headers=[*root.glob('*.hpp'),*(root/'include').rglob('*.hpp'),*root.glob('*.cpp'),*(project/'include').rglob('*.hpp')]
   if obj.exists() and obj.stat().st_mtime>=max(x.stat().st_mtime for x in [source,*headers]):
    return subprocess.CompletedProcess(command,0,'cached unchanged compilation','')
 if len(command)>1 and str(command[1]).endswith('/link.exe'):
  command=[x for x in command if not str(x).startswith("/ENTRY:")]
  command=[*command,"/DLL","/NOENTRY","/SAFESEH:NO",*["/INCLUDE:"+symbol for symbol in spec.get("roots",[])]]
 commands.append([str(x) for x in command])
 (work/'commands.json').write_text(json.dumps(commands,indent=2))
 return ordinary_run(command,*args,**kwargs)
subprocess.run=rooted_run
if '--reuse' in sys.argv:
 native=(work/'model.exe').read_bytes();moved=(work/'moved.exe').read_bytes();link_map=(work/'model.map').read_text()
else:
 native,link_map,moved=build_model(spec,project,DEFAULT_TOOLKIT,flags,work)
pe,moved_pe=PEImage(native),PEImage(moved)
assert pe.image_base==eq.IMAGE_BASE and moved_pe.image_base==eq.SECOND_BASE
symbols={name:int(value,16) for name,value,_ in MAP_SYMBOL.findall(link_map)}
owned=sorted(int(value,16) for _,value,where in MAP_SYMBOL.findall(link_map) if where!='<absolute>')
bindings={symbols[name]:int(address,0) for name,address in spec['bindings'].items() if name in symbols}
bindings.update({int(item['address'],0):int(item['address'],0) for item in spec['absolute_symbols'].values() if item['kind']=='code'})
external_code={int(x['address'],0) for x in spec['absolute_symbols'].values() if x['kind']=='code'}
assert not any(symbols[f[0]] in external_code for f in spec['functions']), 'native/external binding collision'
extents={section:int(size,16) for size,section in re.findall(r'^\s*\d+:[0-9a-f]+\s+([0-9a-f]+)H\s+(\S+)\s+CODE',link_map,re.M|re.I)}
oracle=PEImage(Path('matching2/build/oracle/th10.exe').read_bytes())
functions=spec['functions']
report={'functions':[]}
for symbol,section,address,required in functions:
 start,extent=symbols[symbol],extents[section]
 full_rows=disassemble(pe.read(start,extent),start,work,section+'_full_native')
 table_starts=[]
 for offset,text in full_rows:
  match=re.search(r'jmp DWORD PTR \[[^\]]*\*4\+0x([0-9a-f]+)\]',text)
  if match and start<=int(match[1],16)<start+extent:
   table_starts.append(int(match[1],16)-start)
 code_size=min(table_starts) if table_starts else extent
 table_bytes=extent-code_size
 retail_table_bytes=0
 rows=disassemble(pe.read(start,code_size),start,work,section+'_native')
 body=relocate(pe,moved_pe,rows,start,code_size,extent-code_size,address,bindings,owned)
 (work/(section+'_body.bin')).write_bytes(body)
 original=oracle.read(address,required)
 (work/(section+'_retail_full.bin')).write_bytes(original)
 identity=lambda value,spelling:spelling
 retail_rows=normalize(disassemble(original[:required-retail_table_bytes],address,work,section+'_retail'),address,required,required,identity)
 rows=normalize(disassemble(body[:code_size],address,work,section+'_body_code'),address,extent,extent,identity)
 swaps,hunks,_=find_differences(retail_rows,rows,(),{},True)
 report['functions'].append({'symbol':symbol,'extent':extent,'required':required,'native_table_bytes':table_bytes,'retail_table_bytes':retail_table_bytes,'exact':body==original,'different_overlapping_bytes':sum(a!=b for a,b in zip(body,original)),'base_index_swaps':swaps,'hunks':hunks})
(work/'comparison.json').write_text(json.dumps(report,indent=2)+'\n')
print(json.dumps({'functions':[{k:v for k,v in row.items() if k!='hunks'}|{'hunks':len(row['hunks'])} for row in report['functions'] if not row['exact']]},indent=2),flush=True)
