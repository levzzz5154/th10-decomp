"""Execute the full retail/native sweep and its genuine helper/creation graph.

The initial graph scripts creation at its ordinary declaration. The maintained
graph executes complete creation/allocation/initialization and only scripts
successful operator new, VM execution and descriptor filters. The allocator's
already-recovered constructor executes retail in both runs. This is bounded
behavior evidence, never selection or full game integration.
"""
import hashlib
import itertools
import json
import math
import random
import struct
import sys
from pathlib import Path

sys.path[:0]=[str(Path.cwd()),str(Path('matching2/build/experiments/joystick_binding_reader_0044a190_2026_10_06/dependencies').resolve())]
from matching2.tools.common.pe import PEImage
from matching2.tools.matching.equivalence import MAP_SYMBOL
from unicorn import Uc, UcError, UC_ARCH_X86, UC_MODE_32, UC_HOOK_CODE
from unicorn.x86_const import *

MANAGER,PLAYER,GAME,CONFIG,INPUT,ANM,OBJECT,STACK,STOP,FILTER=(
    0x1000000,0x1300000,0x1400000,0x1500000,0x1600000,0x4000000,
    0x4800000,0x2000000,0x7f000000,0x7e000000)
PRESERVED={UC_X86_REG_EBX:0x12345678,UC_X86_REG_ESI:0x23456789,
           UC_X86_REG_EDI:0x3456789a,UC_X86_REG_EBP:0x456789ab}
HIT='?HitTest@PickupPlayer@@QAEHPBUPickupPoint@@@Z'
SWEEP='?Sweep@PickupSweepResult@@QAEHPAUPickupManager@@PBUPickupPoint@@1@Z'
PRIMARY='?Pickup_CreatePrimaryBack@@YGPAUPickupHandle@@PAXPAU1@HH@Z'
MARK='?MarkForRemoval@PickupAnimationLists@@QAEPAXUPickupHandle@@@Z'

def run(retail,native,symbols,case,leaf=False,full_creation=False):
    uc=Uc(UC_ARCH_X86,UC_MODE_32)
    uc.mem_map(0x400000,0x100000)
    if native: uc.mem_map(0x100000,0x10000)
    for image in (retail,native):
        if image:
            for section in image.sections:
                if section['raw_size']:
                    uc.mem_write(section['address'],image.read(section['address'],section['raw_size']))
    for address,size in [(MANAGER,0x10000),(PLAYER,0x1000),(GAME,0x4000),
            (CONFIG,0x1000),(INPUT,0x1000),(ANM,0x740000),(OBJECT,0x10000),
            (STACK,0x10000),(STOP,0x1000),(FILTER,0x1000)]:
        uc.mem_map(address,size)
    def w(a,v):uc.mem_write(a,struct.pack('<I',v&0xffffffff))
    def u(a):return struct.unpack('<I',uc.mem_read(a,4))[0]
    def f(a,*values):uc.mem_write(a,struct.pack('<'+'f'*len(values),*values))
    def reg(name):return uc.reg_read(globals()['UC_X86_REG_'+name.upper()])
    def ret(cleanup,result):
        sp=reg('esp');uc.reg_write(UC_X86_REG_EIP,u(sp));uc.reg_write(UC_X86_REG_ESP,sp+4+cleanup)
        uc.reg_write(UC_X86_REG_EAX,result&0xffffffff)
    w(0x4776ec,PLAYER);w(0x4776f4,GAME);w(0x477704,CONFIG);w(0x491c10,ANM)
    w(0x474c68,case.get('state',0));w(0x474c44,case.get('score',1234))
    uc.mem_write(GAME+0x378c,bytes([case.get('flags',0)]))
    w(CONFIG+0x10,case.get('config',0));w(PLAYER+0x28,case.get('active',0))
    f(PLAYER+0x30,*case.get('player',(0.,200.)));f(PLAYER+0x3c,case.get('radius',8.))
    w(PLAYER+0x44,case.get('mode',0));f(INPUT,*case.get('center',(0.,200.)))
    f(INPUT+8,*case.get('size',(8.,8.)));w(INPUT+16,0xdadabeef)
    w(MANAGER+0x474,5);w(MANAGER+0x478,5 if case.get('early') else 6)
    w(MANAGER+0x10,CONFIG);f(0x476f78,1.);w(CONFIG+0x11c,CONFIG+0x800)
    w(ANM+0x732454,8)
    if case.get('loaded_script'):w(CONFIG+0x800+17*4,CONFIG+0xf00)
    w(CONFIG+0x124,case.get('loading',0))
    if case.get('allocation'):
        uc.mem_write(ANM+0x3ac068,b'\x01')
        if case['allocation']>=2:uc.mem_write(ANM+0x3ac069,b'\x01')
    uc.mem_write(OBJECT+0x4000,bytes([0xa5])*0x3ac)
    # Real lookup lists include an old object and its children. Creation adds
    # a new object with id 9 through the shared boundary below.
    node=ANM+0x1000;old=OBJECT;new=OBJECT+0x1000
    w(ANM+0x72dad4,node);w(ANM+0x72dad8,node);w(node,old);w(old,7)
    w(old+0x2c,case.get('angle_bits',1234567));w(old+0x35c,0x20)
    if case.get('children'):
        w(old+0x14,node+0x40);w(old+0x18,case.get('children_flagged',0))
        w(node+0x40,OBJECT+0x2000);w(node+0x44,node+0x80)
        w(node+0x80,OBJECT+0x3000)
        w(OBJECT+0x2000+0x35c,0x80);w(OBJECT+0x3000+0x35c,0x100)
    if case.get('secondary'):
        w(ANM+0x72dad4,0);w(ANM+0x72dadc,node)
    pickups=case.get('pickups',[])
    for index,item in enumerate(pickups):
        slot=item.get('slot',index);p=MANAGER+0x49c+slot*0x5c;d=MANAGER+0x5000+index*0x80
        w(p,item.get('previous',3));w(p+4,item.get('current',4))
        f(p+0x14,*item.get('position',(0.,200.,7.)))
        f(p+0x2c,item.get('velocity_scale',16.));w(p+0x40,item.get('state',1))
        w(p+0x44,item.get('handle',7));w(p+0x54,item.get('initialized',0))
        w(p+0x58,0 if item.get('null_descriptor') else d)
        uc.mem_write(d+2,struct.pack('<h',item.get('value',30)))
        f(d+0xc,*item.get('size',(8.,8.)));uc.mem_write(d+0x1d,bytes([item.get('type',3)]))
        uc.mem_write(d+0x20,struct.pack('<h',item.get('script',12)))
        w(d+0x30,FILTER if item.get('filter') else 0)
        if item.get('mutate'):
            alt=d+0x40;uc.mem_write(alt,bytes(uc.mem_read(d,0x34)))
            uc.mem_write(alt+2,struct.pack('<h',-21));uc.mem_write(alt+0x1d,b'\x03')
    for index,region in enumerate(case.get('regions',[])):
        p=MANAGER+0x350c+region.get('slot',index)*0x6c
        f(p,region.get('radius',8.),0.,region.get('angle',0.))
        f(p+0x10,*region.get('size',(8.,8.)));f(p+0x18,*region.get('center',(0.,200.,0.)))
        w(p+0x44,region.get('previous',4));w(p+0x48,region.get('current',4))
        w(p+0x58,region.get('value',30));w(p+0x5c,region.get('accumulated',0))
        w(p+0x60,region.get('limit',999999));w(p+0x64,region.get('interval',4))
        w(p+0x68,region.get('flags',1))
    if case.get('full_indicators'):
        for index in range(32):w(MANAGER+0x350c+index*0x6c+0x68,3)
    calls=[]
    primary=symbols[PRIMARY] if native and full_creation else 0x448d00
    def hook(machine,address,size,user):
        sp=reg('esp')
        if address==FILTER:
            p=reg('edx');item=next(x for i,x in enumerate(pickups)
                if p==MANAGER+0x49c+x.get('slot',i)*0x5c)
            calls.append(('filter',reg('ecx')-MANAGER,p-MANAGER,u(sp+4)-INPUT))
            if item.get('mutate'):w(p+0x58,u(p+0x58)+0x40)
            if item.get('move_center'):f(INPUT,*item['move_center'])
            ret(4,item.get('filter_result',0));return
        if address==primary:
            if native and not full_creation:
                resource,out,script,layer=(u(sp+i) for i in [4,8,12,16]);cleanup=16
            else:
                resource,out,script,layer=u(sp+4),reg('edi'),u(sp+8),u(sp+12);cleanup=12
            calls.append(('create',resource,script,layer))
            if full_creation:return
            w(out,9);w(new,9);w(new+0x35c,0x40000000)
            new_node=node+0xc0;w(new_node,new);w(node+4,new_node)
            ret(cleanup,out);return
        if address==0x452493:
            calls.append(('operator_new',u(sp+4)))
            assert u(sp+4)==0x3ac
            ret(0,OBJECT+0x4000);return
        if address==0x402050:
            calls.append(('constructor',reg('ecx')-OBJECT));return
        if address==0x43ee30:
            calls.append(('vm',u(sp+4)-ANM if u(sp+4)<OBJECT else u(sp+4)-OBJECT))
            ret(4,0);return
    for address in [FILTER,primary,0x452493,0x402050,0x43ee30]:
        uc.hook_add(UC_HOOK_CODE,hook,begin=address,end=address)
    sp=STACK+0x8000;w(sp,STOP)
    for register,value in PRESERVED.items():uc.reg_write(register,value)
    uc.reg_write(UC_X86_REG_ESP,sp);uc.reg_write(UC_X86_REG_FPCW,case.get('fpcw',0x37f))
    uc.reg_write(UC_X86_REG_FPTAG,0xffff);uc.reg_write(UC_X86_REG_FPSW,0)
    if case.get('helper')=='mark':
        w(sp+4,case['handle']);uc.reg_write(UC_X86_REG_EDX,ANM)
        entry=symbols[MARK] if native else 0x4492a0
    elif leaf:
        uc.reg_write(UC_X86_REG_ECX,PLAYER)
        uc.reg_write(UC_X86_REG_EAX,0x71000000 if case.get('invalid_input') else INPUT)
        entry=symbols[HIT] if native else 0x4059f0
    else:
        w(sp+4,MANAGER)
        w(sp+8,0x71000000 if case.get('invalid_input') else INPUT)
        w(sp+12,0x71001000 if case.get('invalid_input') else INPUT+8)
        uc.reg_write(UC_X86_REG_ECX,0 if case.get('nullable') else INPUT+16)
        entry=symbols[SWEEP] if native else 0x428630
    error=None
    try:uc.emu_start(entry,STOP,count=100000)
    except UcError as exc:error=str(exc)
    if error:
        if not case.get('fault'):raise AssertionError({'label':case['label'],'native':bool(native),
            'pc':hex(reg('eip')),'error':error,'calls':calls})
        return {'fault':error,'calls':calls}
    assert not case.get('fault'),case['label']+' expected fault'
    assert reg('eip')==STOP,'instruction budget'
    cleanup=8 if case.get('helper')=='mark' else (4 if leaf else 16)
    assert reg('esp')==sp+cleanup,'return cleanup'
    for register,value in PRESERVED.items():assert uc.reg_read(register)==value,'preserved register'
    assert (reg('fpsw')>>11)&7==0,'x87 stack balance'
    return {'result':reg('eax'),'calls':calls,'manager_sha256':hashlib.sha256(uc.mem_read(MANAGER,0x10000)).hexdigest(),
        'objects_sha256':hashlib.sha256(uc.mem_read(OBJECT,0x10000)).hexdigest(),
        'lists_sha256':hashlib.sha256(uc.mem_read(ANM,0x740000)).hexdigest(),
        'score':u(0x474c44),'input':bytes(uc.mem_read(INPUT,20)).hex(),'fpcw':reg('fpcw')}

def cases():
    yield {'label':'empty'}
    yield {'label':'generation_early','early':True,'active':1}
    yield {'label':'nullable_result','nullable':True,'active':1}
    yield {'label':'generation_early_invalid_inputs','early':True,'invalid_input':True}
    yield {'label':'inactive_leaf_invalid_point','leaf':True,'invalid_input':True}
    yield {'label':'active_leaf_invalid_point','leaf':True,'active':1,'invalid_input':True,'fault':True}
    yield {'label':'active_null_descriptor','pickups':[{'null_descriptor':True}],'fault':True}
    yield {'label':'inactive_null_descriptor','pickups':[{'null_descriptor':True,'state':0}]}
    yield {'label':'stale_handle','pickups':[{'type':0,'handle':123}],'fault':True}
    yield {'label':'signed_remainder_overflow','regions':[{'current':-2147483648,
        'previous':0,'interval':-1}],'fault':True}
    for handle,flagged in itertools.product([0,7,123],[0,1]):
        yield {'label':f'mark_result_{handle}_{flagged}','helper':'mark','handle':handle,
               'children':True,'children_flagged':flagged}
    points=[(0.,200.),(8.,200.),(9.,200.),(float('nan'),200.),(0.,float('nan')),(float('inf'),200.)]
    for mode,flags,config,state,point in itertools.product([-1,0,1,2],[0,1,0x80,0xff],[0,1,-1],[0,1,-1],points):
        yield {'label':f'player_{mode}_{flags}_{config}_{state}_{point}',
            'active':1,'mode':mode,'flags':flags,'config':config,'state':state,'center':point}
    for slot,state,type_ in itertools.product([0,1,127],[0,1,2],[0,2,3]):
        yield {'label':f'pickup_{slot}_{state}_{type_}',
               'pickups':[{'slot':slot,'state':state,'type':type_}],'children':True}
    for current,previous,value in itertools.product([3,4,5,-4],[3,4],[-32768,-21,0,32767]):
        yield {'label':f'interval_{current}_{previous}_{value}',
               'pickups':[{'current':current,'previous':previous,'value':value}]}
    for filter_case in [{'filter_result':1},{'mutate':True},{'move_center':(100.,200.)}]:
        yield {'label':f'filter_{filter_case}','pickups':[dict(filter=True,**filter_case)],'active':1}
    yield {'label':'record_clocks','pickups':[{'slot':1,'current':5},{'slot':127,'current':8}]}
    yield {'label':'secondary_lookup','secondary':True,'pickups':[{'type':2}],'children':True}
    yield {'label':'flagged_children','children':True,'children_flagged':1,'pickups':[{'type':0}]}
    yield {'label':'full_indicator_pool','full_indicators':True,'pickups':[{'type':2}]}
    for allocation,loaded,loading in itertools.product([0,1,2],[False,True],[0,1]):
        yield {'label':f'creation_{allocation}_{loaded}_{loading}','allocation':allocation,
            'loaded_script':loaded,'loading':loading,'pickups':[{'type':2}]}
    for player_y,pickup_y,type_ in itertools.product([-8.,0.,8.],[-8.,0.,8.],[0,3]):
        yield {'label':f'screen_{player_y}_{pickup_y}_{type_}','center':(0.,player_y),
            'pickups':[{'type':type_,'position':(0.,pickup_y,3.),'size':(32.,32.)}]}
    for slot,flags,angle,x in itertools.product([0,1,31],[1,3],[0.,0.5,-1.5,float('nan')],[0.,8.,9.,float('nan')]):
        yield {'label':f'region_{slot}_{flags}_{angle}_{x}',
            'regions':[{'slot':slot,'flags':flags,'angle':angle,'center':(x,200.,0.)}]}
    for current,previous,interval in itertools.product([0,3,4,-4],[3,4],[0,1,4]):
        yield {'label':f'region_interval_{current}_{previous}_{interval}',
            'regions':[{'current':current,'previous':previous,'interval':interval}],
            'fault':current!=previous and interval==0}
    for value,accumulated,limit,score in itertools.product([-30,0,30],[0,60],[30,90],[0,999999998,0x7ffffffe]):
        yield {'label':f'score_{value}_{accumulated}_{limit}_{score}','score':score,
            'regions':[{'value':value,'accumulated':accumulated,'limit':limit}]}
    yield {'label':'individual_radii','regions':[
        {'flags':3,'radius':1.,'center':(10.,200.,0.)},
        {'flags':3,'radius':20.,'center':(10.,200.,0.),'slot':31}]}
    # Retail rounds three pickup edges to binary32 before rejection tests.
    # These edges are unequal in x87 precision but round onto the player's
    # exactly representable boundary. The fourth edge (bottom) stays extended.
    for exponent,fpcw in itertools.product([-60,-20,0,20,60],[0x37f,0x27f,0x7f]):
        edge=2.**exponent;ulp_above=2.**(exponent-23);ulp_below=ulp_above/2
        for axis in [0,1]:
            center=[edge,edge];point=[edge,edge,3.];size=[0.,0.];extent=[0.,0.]
            point[axis]=edge+ulp_above;extent[axis]=1.5*ulp_above
            yield {'label':f'rounded_min_{axis}_{exponent}_{fpcw}','fpcw':fpcw,'center':tuple(center),'size':tuple(size),
                'pickups':[{'position':tuple(point),'size':tuple(extent)}]}
        yield {'label':f'rounded_right_{exponent}_{fpcw}','fpcw':fpcw,'center':(edge,edge),'size':(0.,0.),
            'pickups':[{'position':(edge-ulp_below,edge,3.),'size':(1.5*ulp_below,0.)}]}
        yield {'label':f'extended_bottom_{exponent}_{fpcw}','fpcw':fpcw,'center':(edge,edge),'size':(0.,0.),
            'pickups':[{'position':(edge,edge-ulp_below,3.),'size':(0.,1.5*ulp_below)}]}
    # Smallest binary32 dimensions expose premature rounding of half sizes.
    tiny=2.**-149
    for axis,c,p,h,cw in itertools.product([0,1],[1,2,3,4],[0,1,2,3,4],[1,3,5,7],[0x37f,0x27f,0x7f]):
        center=[0.,200.];position=[0.,200.,3.];extent=[8.,8.]
        center[axis]=c*tiny;position[axis]=p*tiny;extent[axis]=h*tiny
        yield {'label':f'subnormal_{axis}_{c}_{p}_{h}_{cw}','center':tuple(center),
            'size':(0.,0.),'fpcw':cw,'pickups':[{'position':tuple(position),'size':tuple(extent)}]}
    # The Z-rotation snapshot is copied without changing its bit image.
    for bits,cw,loaded in itertools.product([0,0x80000000,1,0x7fffff,0x3f800000,0xbf800000,
            0x7f800000,0xff800000,0x7fc12345,0x7f812345,0xffc12345,0xff812345,
            0x7fffffff,0xffffffff],[0x37f,0x27f,0x7f],[False,True]):
        yield {'label':f'angle_bits_{bits:08x}_{cw}_{loaded}','angle_bits':bits,
            'fpcw':cw,'loaded_script':loaded,'pickups':[{'type':0}]}
    rng=random.Random(0x4059f0)
    for index in range(80):
        yield {'label':f'random_{index}','center':(rng.uniform(-40,40),rng.uniform(-10,80)),
            'size':(rng.uniform(0,32),rng.uniform(0,32)),
            'regions':[{'slot':rng.randrange(32),'flags':rng.choice([1,3]),'angle':rng.uniform(-3,3),
                'size':(rng.uniform(0,64),rng.uniform(0,64)),
                'center':(rng.uniform(-40,40),rng.uniform(-10,80),0.),'radius':rng.uniform(0,64)}]}

def main():
    work=Path('matching2/build/experiments/player_hit_pickup_2026_10_06')/(sys.argv[1] if len(sys.argv)>1 else 'maintained_graph')
    retail=PEImage(Path('matching2/build/oracle/th10.exe').read_bytes());native=PEImage((work/'model.exe').read_bytes())
    symbols={name:int(value,16) for name,value,_ in MAP_SYMBOL.findall((work/'model.map').read_text())}
    full_creation=PRIMARY in symbols
    observations=[];failures=[];suite=list(cases())
    (work/'cases.json').write_text(json.dumps(suite,indent=2)+'\n')
    for case in suite:
        actual=run(retail,None,{},case,leaf=case.get('leaf',False),full_creation=full_creation)
        candidate=run(retail,native,symbols,case,leaf=case.get('leaf',False),full_creation=full_creation)
        observations.append({'case':case['label'],'retail':actual,'native':candidate})
        if actual!=candidate:failures.append({'case':case['label'],'fields':[k for k in actual if actual[k]!=candidate.get(k)]})
    (work/'observations.json').write_text(json.dumps(observations,indent=2)+'\n')
    report={'cases':len(observations),'failures':failures,
        'observations_sha256':hashlib.sha256((work/'observations.json').read_bytes()).hexdigest(),
        'boundaries':(['successful operator new scripted','VM execution scripted','descriptor filters scripted',
            'already-recovered retail constructor executes in both runs'] if full_creation else
            ['animation creation scripted with actual respective call ABIs','descriptor filters scripted']),
        'executed':'complete sweep, hit-test, interval, find, mark, stop, validate, retire, indicator allocation'+
            (', primary creation, registration, allocation, object/script/entity initialization' if full_creation else ''),
        'selection_evidence':False}
    (work/'differential.json').write_text(json.dumps(report,indent=2)+'\n')
    print(json.dumps(report,indent=2),flush=True)
    return bool(failures)

if __name__=='__main__':sys.exit(main())
