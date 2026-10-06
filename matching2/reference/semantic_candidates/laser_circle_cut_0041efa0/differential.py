"""Bounded behavior evidence for complete circular cutter and native full callees.
This never supplies bytes to production and is not a byte equality gate.
"""
import json,hashlib,struct,sys,random
from pathlib import Path
from dataclasses import dataclass,replace,asdict
ROOT=Path.cwd();sys.path[:0]=[str(ROOT),str(ROOT/'matching2/build/experiments/joystick_binding_reader_0044a190_2026_10_06/dependencies')]
from matching2.tools.common.pe import PEImage
from matching2.tools.matching.equivalence import MAP_SYMBOL
from unicorn import Uc,UC_ARCH_X86,UC_MODE_32,UC_HOOK_CODE
from unicorn.x86_const import *
OWNER,POOL,ITEMS,MANAGER,RESOURCE,HEAP,STACK,STOP=0x1000000,0x2000000,0x3000000,0x4000000,0x5000000,0x6000000,0x8000000,0x9000000
PRESERVED={UC_X86_REG_EBX:0x12345678,UC_X86_REG_ESI:0x23456789,UC_X86_REG_EDI:0x3456789a,UC_X86_REG_EBP:0x456789ab}
@dataclass(frozen=True)
class Case:
 length:float=120.0
 position:tuple=(0.,100.,3.)
 center:tuple=(50.,100.,0.)
 radius:float=12.
 angle:float=0.
 items:int=1
 width:float=4.
 total:float=200.
 type:int=2
 script:int=6
 seed_id:int=17
 cursor:int=0
 special_count:int=0
 occupied:bool=False

def run(retail,native,entry,symbols,case):
 uc=Uc(UC_ARCH_X86,UC_MODE_32);uc.mem_map(0x400000,0x100000)
 for image in [retail,native]:
  if image:
   for sec in image.sections:
    if sec['raw_size']: uc.mem_write(sec['address'],image.read(sec['address'],sec['raw_size']))
 for addr,size in [(OWNER,0x10000),(POOL,0x740000),(ITEMS,0x230000),(MANAGER,0x10000),(RESOURCE,0x10000),(HEAP,0x100000),(STACK,0x10000),(STOP,0x1000)]:uc.mem_map(addr,size)
 uc.mem_write(STACK,b'\xa5'*0x10000)
 def w(addr,v):uc.mem_write(addr,struct.pack('<I',v&0xffffffff))
 def u(addr):return struct.unpack('<I',uc.mem_read(addr,4))[0]
 def f(addr,values):uc.mem_write(addr,struct.pack('<'+'f'*len(values),*values))
 def ret(extra=0):
  sp=uc.reg_read(UC_X86_REG_ESP);uc.reg_write(UC_X86_REG_EIP,u(sp));uc.reg_write(UC_X86_REG_ESP,sp+4+extra)
 w(0x491c10,POOL);w(0x477818,ITEMS);w(0x47781c,MANAGER);f(0x476f78,[1.]);w(0x473660,0x31415926)
 f(OWNER+0x24,case.position);f(OWNER+0x3c,[case.angle,case.length,case.width]);f(OWNER+0x444,[case.total]);uc.mem_write(OWNER+0x464,struct.pack('<hh',case.type,case.script))
 w(MANAGER+0x434,MANAGER+0x1000);w(MANAGER+0x458,RESOURCE);w(MANAGER+0x43c,case.seed_id)
 w(RESOURCE+0x11c,RESOURCE+0x1000);uc.mem_write(RESOURCE,struct.pack('<H',7))
 for i in range(512):w(RESOURCE+0x1000+i*4,RESOURCE+0x4000+i*8)
 f(OWNER+0x1000,case.center)
 w(ITEMS+0x21ceb8,case.cursor);w(ITEMS+0x21cebc,case.special_count)
 if case.occupied:w(ITEMS+0x24eb4+case.cursor*0x3f0+0x3dc,5)
 sp=STACK+0x8000;uc.mem_write(sp,struct.pack('<IIfI',STOP,OWNER+0x1000,case.radius,case.items))
 for reg,v in PRESERVED.items():uc.reg_write(reg,v)
 uc.reg_write(UC_X86_REG_ECX,OWNER);uc.reg_write(UC_X86_REG_EDX,0xd2d2d2d2);uc.reg_write(UC_X86_REG_EAX,0xa0a0a0a0);uc.reg_write(UC_X86_REG_ESP,sp)
 uc.reg_write(UC_X86_REG_FPCW,0x37f);uc.reg_write(UC_X86_REG_FPTAG,0xffff);uc.reg_write(UC_X86_REG_FPSW,0)
 calls=[];allocations=[];spawned=[];effects=[]
 def api(machine,address,size,user):
  if address==0x452493:
   n=u(uc.reg_read(UC_X86_REG_ESP)+4);p=HEAP+len(allocations)*0x1000;allocations.append((n,p));uc.reg_write(UC_X86_REG_EAX,p);ret();return
  if address==0x41c8c0:
   p=u(uc.reg_read(UC_X86_REG_ESP)+4);o=uc.reg_read(UC_X86_REG_ECX);spawned.append(bytes(uc.mem_read(p,0x1dc)).hex());calls.append('laser');ret(4);return
  if address==0x43ee30:
   p=u(uc.reg_read(UC_X86_REG_ESP)+4);effects.append({'script':struct.unpack('<h',uc.mem_read(p+0x38a,2))[0],'position':bytes(uc.mem_read(p+0x340,12)).hex()});calls.append('effect');ret(4);return
  if address==0x401de0:
   # Script initialization is a shared scripted boundary, preserving the three
   # position words already placed by the cutter. The complete loader executes.
   ret();return
  if address==0x402050:
   raise AssertionError('unexpected overflow Entity allocation')
 for address in [0x452493,0x41c8c0,0x43ee30,0x401de0,0x402050]:uc.hook_add(UC_HOOK_CODE,api,begin=address,end=address)
 item_entry=symbols.get('?Spawn@ItemSpawnManager_0041bb00@@QAEHPBUVector3@@HHMM@Z',0x41bb00)
 def item_call(machine,address,size,user):calls.append('item')
 uc.hook_add(UC_HOOK_CODE,item_call,begin=item_entry,end=item_entry)
 uc.emu_start(entry,STOP,count=1000000)
 assert uc.reg_read(UC_X86_REG_EIP)==STOP,'instruction budget'
 assert uc.reg_read(UC_X86_REG_ESP)==sp+16,'RET12'
 for reg,v in PRESERVED.items():assert uc.reg_read(reg)==v,'preserved registers'
 assert (uc.reg_read(UC_X86_REG_FPSW)>>11)&7==0,'x87 stack'
 return {'result':uc.reg_read(UC_X86_REG_EAX),'owner':bytes(uc.mem_read(OWNER,0x468)).hex(),'items_sha256':hashlib.sha256(uc.mem_read(ITEMS,0x230000)).hexdigest(),'pool_sha256':hashlib.sha256(uc.mem_read(POOL,0x740000)).hexdigest(),'manager':bytes(uc.mem_read(MANAGER,0x440)).hex(),'heap_sha256':hashlib.sha256(uc.mem_read(HEAP,0x100000)).hexdigest(),'spawned':spawned,'effects':effects,'calls':calls,'fpcw':uc.reg_read(UC_X86_REG_FPCW),'x87_tags':uc.reg_read(UC_X86_REG_FPTAG)}

def cases():
 base=Case()
 for length in [-1.,0.,6.,12.,12.00001,18.,24.,30.,48.,120.,3072.]:
  for center,radius in [((50.,100.,0.),12.),((0.,100.,0.),12.),((0.,100.,0.),10000.),((1000.,1000.,0.),1.)]:yield replace(base,length=length,center=center,radius=radius)
 for position in [(-224.,100.,-0.),(-223.99,100.,2.),(223.99,100.,3.),(224.,100.,1.),(0.,-32.,5.),(0.,-31.99,0.),(0.,480.,2.),(0.,479.99,4.)]:
  yield replace(base,position=position,center=position,radius=1000.)
 for angle in [0.,0.5,1.5707963267948966,-1.5707963267948966,3.,-3.]:
  for items in [0,1]:yield replace(base,angle=angle,items=items,center=(0.,100.,0.),radius=30.)
 for radius in [0.,6.,-6.,float('nan'),float('inf')]:yield replace(base,radius=radius)
 for center in [(float('nan'),100.,0.),(50.,float('nan'),0.),(float('inf'),100.,0.)]:yield replace(base,center=center)
 for n in [0,255,256,511,512,1023,1024]:
  for occupied in [False,True]:yield replace(base,special_count=n,cursor=31,occupied=occupied)
 rng=random.Random(0x41efa0)
 for _ in range(100):yield replace(base,length=rng.uniform(12,300),position=(rng.uniform(-250,250),rng.uniform(-50,500),rng.uniform(-5,5)),angle=rng.uniform(-3,3),center=(rng.uniform(-250,250),rng.uniform(-50,500),0.),radius=rng.uniform(1,200),items=rng.randrange(2),width=rng.uniform(1,20),total=rng.uniform(0,500),type=rng.randrange(10),script=rng.randrange(50),seed_id=rng.choice([0,17,0xffffffff]))

def main():
 folder=ROOT/'matching2/build/experiments/laser_circle_cut_native_2026_10_06'/(sys.argv[1] if len(sys.argv)>1 else 'circle_current');retail=PEImage((ROOT/'matching2/build/oracle/th10.exe').read_bytes());native=PEImage((folder/'model.exe').read_bytes());symbols={s:int(a,16) for s,a,_ in MAP_SYMBOL.findall((folder/'model.map').read_text())};observations=[]
 for i,case in enumerate(cases()):
  expected=run(retail,None,0x41efa0,{},case);actual=run(retail,native,symbols['?CutCircle@CutLaser@@QAEHPBUCutVector@@MH@Z'],symbols,case)
  if actual!=expected:
   diff={k:{'retail':expected[k],'native':actual[k]} for k in expected if expected[k]!=actual[k]};(folder/'differential_failure.json').write_text(json.dumps({'case':i,'input':asdict(case),'difference':diff},indent=2)+'\n');raise AssertionError(f'case {i}: differing {list(diff)}')
  observations.append(actual)
  if i%25==0:print('passed',i+1,flush=True)
 report={'passed':True,'cases':len(observations),'native_pe_sha256':hashlib.sha256(native.data).hexdigest(),'retail_body_sha256':hashlib.sha256(retail.read(0x41efa0,1108)).hexdigest(),'instruction_patches':0,'scope':'Full cutter, real native item/spawn/constructor/loader/registrar/allocator bodies; complete owner, item, animation, manager and heap state; effect/item/laser order and complete 476-byte spawn parameters; return, RET12, preserved registers and x87 balance. Script initialization and animation VM/laser Initialize callbacks are scripted shared boundaries. Raw retail SetPolar and cookie check execute. This is bounded behavioral evidence, not a raw byte match.','calls':{k:sum(x['calls'].count(k) for x in observations) for k in ['item','effect','laser']},'observation_sha256':hashlib.sha256(json.dumps(observations,sort_keys=True).encode()).hexdigest()};(folder/'differential_report.json').write_text(json.dumps(report,indent=2)+'\n');print(json.dumps(report,indent=2))
if __name__=='__main__':main()
