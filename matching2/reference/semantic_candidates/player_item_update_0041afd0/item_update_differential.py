"""Execute the complete 2198-slot retail/native update with bounded collaborators.

Real compiled score, timer, angle, floating-text, sound, HUD, resource
configuration, full banner creation/initialization and animation lookup/removal
helpers execute. The suite also
probes intermediate float rounding, banner lists and queued sounds.
The complete compiled Entity_Init executes. The allocator constructor call
executes retail's already-recovered constructor in both runs. Successful
operator new, VM callbacks, player PowerChanged and terminal ConvertItems
are scripted shared boundaries. This is behavior
evidence, not a raw matching gate or complete game integration.
"""
import hashlib
import json
import random
import struct
import sys
from dataclasses import asdict, dataclass, replace
from pathlib import Path

sys.path[:0]=[str(Path.cwd()),str(Path('matching2/build/experiments/joystick_binding_reader_0044a190_2026_10_06/dependencies').resolve())]
from matching2.tools.common.pe import PEImage
from matching2.tools.matching.equivalence import MAP_SYMBOL
from unicorn import Uc, UcError, UC_ARCH_X86, UC_MODE_32, UC_HOOK_CODE
from unicorn.x86_const import *

HEAP=0x4800000
POOL,PLAYER,MOVEMENT,BANK,RESOURCE,SCRIPTS,HUD,TEXT,ANM,BLOCKER,STACK,STOP=(
    0x1000000,0x1300000,0x1310000,0x3000000,0x1900000,0x1910000,
    0x1800000,0x1700000,0x4000000,0x1320000,0x2000000,0x7F000000)
PRESERVED={UC_X86_REG_EBX:0x12345678,UC_X86_REG_ESI:0x23456789,
           UC_X86_REG_EDI:0x3456789A,UC_X86_REG_EBP:0x456789AB}

@dataclass(frozen=True)
class Case:
    label:str='base'
    state:int=1
    kind:int=6
    slot:int=0
    position:tuple=(50.,200.,3.)
    velocity:tuple=(0.5,-1.,0.25)
    player_position:tuple=(0.,200.,0.)
    player_state:int=0
    collection:tuple=(-10.,190.,10.,210.)
    focused_magnet:tuple=(-40.,160.,40.,240.)
    unfocused_magnet:tuple=(-20.,180.,20.,220.)
    focused:int=0
    blocker:int=0
    speed:float=1.
    timer_speed:float=1.
    timer_elapsed:float=0.25
    magnet_speed:float=2.
    delay:int=1
    power:int=19
    gauge:int=10000
    tier:int=0
    lives:int=8
    score:int=1234
    accumulator:int=1010
    text_cursor:int=0
    active_slots:tuple=()
    gauge_timer_current:int=0
    gauge_timer_elapsed:float=0.
    gauge_timer_flags:int=1
    vm_timer_delta:int=0
    power_changed_value:int=-1
    resources_ready:bool=False
    banner_mode:int=0
    queue_mode:int=0
    creation_mode:int=0
    animation_cursor:int=0
    item_scripts:bool=False
    script_loading:int=0


def run(retail,native,symbols,case):
    uc=Uc(UC_ARCH_X86,UC_MODE_32)
    uc.mem_map(0x400000,0x100000)
    if native: uc.mem_map(0x100000,0x10000)
    for image in (retail,native):
        if image:
            for section in image.sections:
                if section['raw_size']:
                    uc.mem_write(section['address'],image.read(section['address'],section['raw_size']))
    for address,size in [(POOL,0x230000),(PLAYER,0x10000),(MOVEMENT,0x1000),
            (BLOCKER,0x1000),(BANK,0x400000),(RESOURCE,0x10000),(SCRIPTS,0x1000),
            (HUD,0x10000),(TEXT,0x10000),(ANM,0x740000),(HEAP,0x10000),(STACK,0x10000),(STOP,0x1000)]:
        uc.mem_map(address,size)
    def w(address,value):uc.mem_write(address,struct.pack('<I',value&0xFFFFFFFF))
    def u(address):return struct.unpack('<I',uc.mem_read(address,4))[0]
    def f(address,*values):uc.mem_write(address,struct.pack('<'+'f'*len(values),*values))
    def reg(name):return uc.reg_read(globals()['UC_X86_REG_'+name.upper()])
    def ret(cleanup=0,result=None):
        if result is not None:uc.reg_write(UC_X86_REG_EAX,result)
        sp=reg('esp');uc.reg_write(UC_X86_REG_EIP,u(sp));uc.reg_write(UC_X86_REG_ESP,sp+4+cleanup)
    w(0x477834,PLAYER);w(0x4776EC,BLOCKER);w(BLOCKER+0x28,case.blocker)
    w(0x4776F0,BANK);w(BANK+0x3E0B50,RESOURCE);w(RESOURCE+0x11C,SCRIPTS)
    w(RESOURCE+0x124,case.script_loading)
    if case.item_scripts:
        for script in range(374,387):w(SCRIPTS+script*4,RESOURCE+0xF000)
    w(0x47770C,HUD);w(HUD+0x9EC8,RESOURCE);w(HUD+0x9E18,123)
    if case.resources_ready:
        w(RESOURCE+0x108,RESOURCE+0x4000);w(RESOURCE+0x118,RESOURCE+0x2000)
        for index in range(256):
            record=RESOURCE+0x2000+index*0x44
            f(record+0x18,1.,1.);f(record+0x30,12.,16.,1.,1.)
    w(0x477840,TEXT);w(TEXT+0x14,case.text_cursor);w(0x491C10,ANM)
    w(0x474E5C,case.focused);f(0x476F78,case.speed);f(RESOURCE+0x800,case.timer_speed)
    f(PLAYER+0x3C0,*case.player_position);w(PLAYER+0x458,case.player_state)
    w(PLAYER+0x45C,MOVEMENT);f(MOVEMENT+8,6.)
    for offset,box in [(0x4324,case.collection),(0x433C,case.focused_magnet),(0x4354,case.unfocused_magnet)]:
        f(PLAYER+offset,box[0],box[1],0.,box[2],box[3],0.)
    uc.mem_write(0x474C48,struct.pack('<h',case.power));w(0x474C44,case.score)
    w(0x474C4C,case.gauge);w(0x474C70,case.lives);w(0x474C74,case.tier);w(0x474C98,case.accumulator)
    w(0x474C54,-1);w(0x474C58,case.gauge_timer_current);f(0x474C5C,case.gauge_timer_elapsed)
    w(0x474C60,0x476F78);w(0x474C64,case.gauge_timer_flags)
    w(POOL+0x21CEB4,17);w(POOL+0x21CEBC,31)
    for slot in range(12):w(0x492590+0x620+slot*4,0xFFFFFFFF)
    if case.queue_mode:
        if case.queue_mode in [1,2]:
            w(0x492590+0x620,44)
            w(0x492590+0x650,127 if case.queue_mode==1 else 128)
        else:
            for index in range(12):
                w(0x492590+0x620+index*4,index)
                w(0x492590+0x650+index*4,1)
    w(ANM+0x3AD068,case.animation_cursor)
    uc.mem_write(HEAP,bytes([0xA5])*0x3AC)
    if case.creation_mode:
        for script in [73,75]:w(SCRIPTS+script*4,RESOURCE+0xF000)
        if case.creation_mode>=2:
            # One busy slot tests ring advance; two busy slots reach the heap.
            uc.mem_write(ANM+0x3AC068+case.animation_cursor,b'\x01')
        if case.creation_mode>=3:
            successor=(case.animation_cursor+1)%4096
            uc.mem_write(ANM+0x3AC068+successor,b'\x01')
    if case.banner_mode:
        node=ANM+0x1000
        w(ANM+(0x72DADC if case.banner_mode==2 else 0x72DAD4),node)
        if case.banner_mode!=2:w(ANM+0x72DAD8,node)
        w(node,node+0x400);w(node+0x400,123)
        w(node+0x400+0x35C,0x20)
        w(node+0x400+0x18,1 if case.banner_mode==3 else 0)
        if case.banner_mode in [1,2]:
            w(node+0x400+0x14,node+0x800)
            w(node+0x800,node+0xC00);w(node+0xC00+0x35C,0x80)
            w(node+0x804,node+0x1000)
            w(node+0x1000,node+0x1400);w(node+0x1400+0x35C,0x100)
    slots=case.active_slots or ((case.slot,case.state,case.kind),)
    for slot,state,kind in slots:
        item=POOL+0x14+slot*0x3F0
        f(item+0x3AC,*case.position);f(item+0x3B8,*case.velocity)
        w(item+0x3DC,state);w(item+0x3E0,kind);f(item+0x3E8,case.magnet_speed);w(item+0x3EC,case.delay)
        w(item+0x3C8,5);w(item+0x3CC,7);f(item+0x3D0,case.timer_elapsed)
        w(item+0x3D4,RESOURCE+0x800);w(item+0x3D8,1)
    calls=[]
    is_native=bool(native)
    convert=symbols.get('?ConvertItems@ItemSpawnManager_0041bb00@@QAEHXZ',0x41BA50)
    resource_symbol='?ConfigureObject@Resource_0043e5a0@@QAEHPAUAnimationObject_0043e5a0@@H@Z'
    configure=symbols.get(resource_symbol,0x43E5A0)
    create=symbols.get('?ItemAnimation_CreatePrimaryBack@@YGPAPAXPAXPAPAXHH@Z',0x448D00)
    remove=symbols.get('?MarkForRemoval@ItemAnimationLists@@QAEPAXUItemAnimationHandle@@@Z',0x4492A0)
    icons=symbols.get('?SetActiveCount@ItemHud@@QAEXH@Z',0x413790)
    queue=symbols.get('?Queue@SoundQueue@@QAEHHH@Z',0x43DC90)
    initialize=symbols.get('?Entity_Init@@YGXPAUEntity@@@Z',0x401DE0)
    def hook(machine,address,size,user):
        sp=reg('esp')
        if address==0x402050:
            calls.append(('constructor',reg('ecx')-HEAP));return
        if address==0x452493:
            requested=u(sp+4)
            assert requested==0x3AC
            calls.append(('operator_new',requested));ret(0,HEAP);return
        if address==initialize:
            calls.append(('init',reg('edx')-POOL));return
        if address==0x43EE30:
            obj=u(sp+4)
            calls.append(('animate',obj-POOL))
            if case.vm_timer_delta:
                w(obj+0x3CC,u(obj+0x3CC)+case.vm_timer_delta)
                elapsed=struct.unpack('<f',uc.mem_read(obj+0x3D0,4))[0]
                f(obj+0x3D0,elapsed+case.vm_timer_delta)
            ret(4,0);return
        if address==0x426F70:
            calls.append(('power_changed',u(sp+4)))
            if case.power_changed_value>=0:uc.mem_write(0x474C48,struct.pack('<h',case.power_changed_value))
            ret(4,0);return
        if address==convert:
            calls.append(('convert',reg('esi')));ret(0,0);return
        if address==configure:
            resource=reg('ecx')
            opaque=is_native and configure==0x43E5A0
            obj=u(sp+4) if opaque else reg('eax')
            index=u(sp+8) if opaque else reg('edx')
            calls.append(('digit',resource,obj-HUD,index))
            if opaque:ret(8,0xFFFFFFFF)
            return
        if address==remove:
            calls.append(('remove_banner',reg('edx'),u(sp+4)))
            return
        if address==create:
            calls.append(('banner',u(sp+4),u(sp+8),u(sp+12)))
            return
        if address==queue:
            calls.append(('queue',reg('ecx'),reg('edi'),u(sp+4)))
            return
        if address==icons:
            calls.append(('life_icons',reg('eax'),reg('ecx')))
            return
    for address in [0x402050,0x452493,initialize,0x43EE30,0x426F70,convert,configure,remove,create,queue,icons]:
        uc.hook_add(UC_HOOK_CODE,hook,begin=address,end=address)
    sp=STACK+0x8000;w(sp,STOP);w(sp+4,POOL)
    for register,value in PRESERVED.items():uc.reg_write(register,value)
    uc.reg_write(UC_X86_REG_ESP,sp);uc.reg_write(UC_X86_REG_FPCW,0x37F)
    uc.reg_write(UC_X86_REG_FPTAG,0xFFFF);uc.reg_write(UC_X86_REG_FPSW,0)
    entry=symbols['_ItemManager_UpdateItems@4'] if is_native else 0x41AFD0
    try:uc.emu_start(entry,STOP,count=1000000)
    except UcError as error:
        raise AssertionError({'case':case.label,'native':is_native,'pc':hex(reg('eip')),
            'esp':hex(reg('esp')),'eax':hex(reg('eax')),'ecx':hex(reg('ecx')),
            'edx':hex(reg('edx')),'error':str(error),'calls':calls}) from error
    assert reg('eip')==STOP,'instruction limit'
    assert reg('esp')==sp+8,'RET4'
    for register,value in PRESERVED.items():assert uc.reg_read(register)==value,'preserved register'
    assert (reg('fpsw')>>11)&7==0,'x87 stack balance'
    return {'result':reg('eax'),'calls':calls,'items_sha256':hashlib.sha256(uc.mem_read(POOL,0x230000)).hexdigest(),
        'active_items':[bytes(uc.mem_read(POOL+0x14+s*0x3F0,0x3F0)).hex() for s,_,_ in slots],
        'live_count':u(POOL+0x21CEB4),'special_count':u(POOL+0x21CEBC),
        'run':bytes(uc.mem_read(0x474C40,0x5C)).hex(),
        'texts_sha256':hashlib.sha256(uc.mem_read(TEXT,0x10000)).hexdigest(),
        'hud_sha256':hashlib.sha256(uc.mem_read(HUD,0x10000)).hexdigest(),
        'sound_sha256':hashlib.sha256(uc.mem_read(0x492590,0x1E80)).hexdigest(),
        'heap_sha256':hashlib.sha256(uc.mem_read(HEAP,0x10000)).hexdigest(),
        'animation_lists_sha256':hashlib.sha256(uc.mem_read(ANM,0x740000)).hexdigest(),
        'fpcw':reg('fpcw')}


def cases():
    base=Case()
    yield replace(base,label='empty',state=0)
    for slot in [0,149,150,2197]:
        for state in [1,2,3,4,5,6]:yield replace(base,label=f'slot{slot}_state{state}',slot=slot,state=state)
    for delay in [-1,0,1,31]:yield replace(base,label=f'delay{delay}',state=5,delay=delay)
    for state in [1,2,3,4]:
        for ps in [0,2,4]:
            for y in [100.,200.]:yield replace(base,label=f'motion{state}_{ps}_{y}',state=state,player_state=ps,player_position=(0.,y,0.))
    for kind in range(0,13):
        for power in [19,99,100]:yield replace(base,label=f'collect{kind}_power{power}',kind=kind,power=power,position=(0.,200.,3.),velocity=(0.,0.,0.))
    for tier in [-1,0,1,2,3,4,5]:yield replace(base,label=f'tier{tier}',kind=3,tier=tier,position=(0.,200.,3.))
    for y in [143.,144.,200.,448.]:yield replace(base,label=f'point_height{y}',kind=2,player_position=(0.,y,0.),position=(0.,200.,3.),velocity=(0.,0.,0.))
    for focused in [0,4]:
        for x in [-41.,-40.,-20.,-10.,10.,20.,40.,41.]:yield replace(base,label=f'magnet{focused}_{x}',focused=focused,position=(x,200.,3.),velocity=(0.,0.,0.))
    for scale in [0.,0.5,1.,1.5]:
        for timer_scale in [0.5,1.,1.5]:yield replace(base,label=f'scales{scale}_{timer_scale}',speed=scale,timer_speed=timer_scale)
    for state in [1,2]:yield replace(base,label=f'offscreen{state}',state=state,position=(0.,473.,3.))
    for lives in [8,9]:yield replace(base,label=f'life{lives}',kind=7,lives=lives,position=(0.,200.,3.),velocity=(0.,0.,0.))
    yield replace(base,label='text_wrap',kind=9,text_cursor=720,position=(0.,200.,3.))
    yield replace(base,label='mixed_all_pool',active_slots=((0,1,1),(149,2,2),(150,3,9),(2197,5,8)),position=(0.,200.,3.))
    for current,flags in [(0,0),(129,0),(129,1),(130,1),(131,1)]:
        yield replace(base,label=f'gauge_timer{current}_{flags}',kind=9,position=(0.,200.,3.),
            gauge_timer_current=current,gauge_timer_elapsed=float(current),gauge_timer_flags=flags)
    for changed in [19,99,100]:
        for kind in [1,4]:yield replace(base,label=f'power_callback{kind}_{changed}',kind=kind,
            position=(0.,200.,3.),velocity=(0.,0.,0.),power_changed_value=changed)
    yield replace(base,label='vm_timer_change',vm_timer_delta=3,timer_speed=0.5)
    for label,position in [('nan_x',(float('nan'),200.,3.)),('nan_y',(0.,float('nan'),3.)),
            ('inf_x',(float('inf'),200.,3.)),('inf_y',(0.,float('inf'),3.))]:
        yield replace(base,label=label,position=position,velocity=(0.,0.,0.))
    for kind in [2,9]:yield replace(base,label=f'negative_point_value{kind}',kind=kind,gauge=-99,position=(0.,200.,3.))
    for kind in [1,4,11]:yield replace(base,label=f'configured_digits{kind}',kind=kind,position=(0.,200.,3.),resources_ready=True)
    rng=random.Random(0x41AFD0)
    for i in range(80):
        yield replace(base,label=f'random{i}',state=rng.randrange(1,7),kind=rng.randrange(0,13),slot=rng.randrange(2198),
            position=(rng.uniform(-100,100),rng.uniform(100,490),rng.uniform(-5,5)),
            velocity=(rng.uniform(-3,3),rng.uniform(-3,3),rng.uniform(-2,2)),player_state=rng.choice([0,2,4]),
            power=rng.randrange(0,101),tier=rng.randrange(0,6),focused=rng.choice([0,4]),speed=rng.choice([0.5,1.,1.5]))

    # Pick actual float inputs whose rounded and retained products yield
    # different final position bits. This exposed the falling Y spill and
    # also protects the required Z displacement store in the other branch.
    quantize=lambda value:struct.unpack('<f',struct.pack('<f',value))[0]
    rounding_rng=random.Random(0x41AFD001)
    triples=[]
    while len(triples)<20:
        position=quantize(rounding_rng.uniform(-2,2))
        velocity=quantize(rounding_rng.uniform(-2,2))
        scale=quantize(rounding_rng.uniform(.2,2))
        if quantize(position+velocity*scale)!=quantize(position+quantize(velocity*scale)):
            triples.append((position,velocity,scale))
    for axis in range(3):
        for state in [1,2]:
            for index,(position,velocity,scale) in enumerate(triples):
                coordinates=[50.,200.,3.]
                motion=[0.,-.5,0.]
                coordinates[axis]=position
                motion[axis]=velocity
                yield replace(base,label=f'axis{axis}_state{state}_round{index}',state=state,
                    position=tuple(coordinates),velocity=tuple(motion),speed=scale,player_state=2)

    # Retail reloads the stored float before its offscreen test. Some sums
    # lie above 472 in x87 but still round to the visible boundary in memory.
    for state in [1,2]:
        for speed in [1.e-6,1.e-5,1.e-4]:
            for velocity in [-1.,1.]:
                yield replace(base,label=f'rounded_offscreen{state}_{speed}_{velocity}',
                    state=state,position=(50.,472.,3.),velocity=(0.,velocity,0.),
                    speed=speed,player_state=2)

    for banner_mode in [0,1,2,3]:
        for queue_mode in [0,1,2,3]:
            yield replace(base,label=f'life_banner{banner_mode}_queue{queue_mode}',
                kind=7,lives=8,position=(0.,200.,3.),velocity=(0.,0.,0.),
                banner_mode=banner_mode,queue_mode=queue_mode)
    for banner_mode in [1,2,3]:
        yield replace(base,label=f'power_banner{banner_mode}',kind=4,power=99,
            position=(0.,200.,3.),velocity=(0.,0.,0.),banner_mode=banner_mode)

    for creation_mode in [1,2]:
        for banner_mode in [0,1,2,3]:
            for kind in [4,7]:
                yield replace(base,label=f'create{creation_mode}_banner{banner_mode}_kind{kind}',
                    kind=kind,power=99,lives=8,position=(0.,200.,3.),velocity=(0.,0.,0.),
                    banner_mode=banner_mode,creation_mode=creation_mode)

    for cursor in [0,4095]:
        for creation_mode in [1,2,3]:
            for banner_mode in [0,1,2,3]:
                for kind in [4,7]:
                    yield replace(base,label=f'allocate_cursor{cursor}_mode{creation_mode}_banner{banner_mode}_kind{kind}',
                        kind=kind,power=99,lives=8,position=(0.,200.,3.),velocity=(0.,0.,0.),
                        banner_mode=banner_mode,creation_mode=creation_mode,animation_cursor=cursor)

    for kind in [0,1,6,9,12]:
        for script_loading in [0,1]:
            for delay in [-1,0]:
                yield replace(base,label=f'valid_item_script{kind}_loading{script_loading}_delay{delay}',
                    state=5,kind=kind,delay=delay,item_scripts=True,script_loading=script_loading)


if __name__=='__main__':
    folder=Path('matching2/build/experiments/player_item_update_2026_10_06')/(sys.argv[1] if len(sys.argv)>1 else 'complete_genuine_graph')
    retail=PEImage(Path('matching2/build/oracle/th10.exe').read_bytes());native=PEImage((folder/'model.exe').read_bytes())
    symbols={s:int(a,16) for s,a,_ in MAP_SYMBOL.findall((folder/'model.map').read_text())}
    observations=[];coverage=[]
    for i,case in enumerate(cases()):
        expected=run(retail,None,{},case);actual=run(retail,native,symbols,case)
        if expected!=actual:
            (folder/'differential_failure.json').write_text(json.dumps({'case':i,'input':asdict(case),
                'difference':{k:{'retail':expected[k],'native':actual[k]} for k in expected if expected[k]!=actual[k]}},indent=2)+'\n')
            raise AssertionError((i,case.label,[k for k in expected if expected[k]!=actual[k]]))
        init_calls=sum(c[0]=='init' for c in actual['calls'])
        heap_calls=sum(c[0]=='operator_new' for c in actual['calls'])
        constructor_calls=sum(c[0]=='constructor' for c in actual['calls'])
        if case.label.startswith('allocate_'):
            assert heap_calls==constructor_calls==int(case.creation_mode==3)
            assert init_calls==heap_calls
        if case.item_scripts:
            assert init_calls==(1 if case.script_loading else 2)
        coverage.append({'case':case.label,'heap_calls':heap_calls,'constructor_calls':constructor_calls,'initializer_calls':init_calls})
        observations.append(actual)
        if i%25==0:print('passed',i+1,flush=True)
    (folder/'execution_coverage.json').write_text(json.dumps(coverage,indent=2)+'\n')
    report={'passed':True,'cases':len(observations),'cases_executing_initializer':sum(c['initializer_calls']>0 for c in coverage),
        'heap_fallback_cases':sum(c['heap_calls']>0 for c in coverage),'constructor_cases':sum(c['constructor_calls']>0 for c in coverage),'native_pe_sha256':hashlib.sha256(native.data).hexdigest(),
        'retail_body_sha256':hashlib.sha256(retail.read(0x41AFD0,2320)).hexdigest(),
        'fixture_sha256':hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),
        'instruction_patches':0,'comparison_masks':0,'scope':__doc__,
        'observation_sha256':hashlib.sha256(json.dumps(observations,sort_keys=True).encode()).hexdigest()}
    (folder/'differential_report.json').write_text(json.dumps(report,indent=2)+'\n');print(json.dumps(report,indent=2))
