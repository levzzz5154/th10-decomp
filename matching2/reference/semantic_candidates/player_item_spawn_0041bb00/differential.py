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
SWEEP='?Sweep@PickupSweepResult@@QAEHPAUPlayerState@@PBUPickupPoint@@1@Z'
PRIMARY='?Pickup_CreatePrimaryBack@@YG?AUAnimationRef@@PAXHH@Z'
EFFECT='_EffectPoolUpdate@4'
INITIALIZE='?InitializeObject@AnimationResource_00449870@@QAEXPAUEntity@@H@Z'
MARK='?MarkForRemoval@PickupAnimationLists@@QAEPAXUAnimationRef@@@Z'
SPAWN='_StageSchedule_Fire_00427e90@12'
SPAWN_MEMBER='?Fire@PlayerState@@QAGHPAUPickupDescriptor@@H@Z'
PAN='?QueuePan@SoundQueue@@QAEXHM@Z'
SEQUENCE='?UpdateSequence@PlayerState@@QAEHXZ'
STATE_UPDATE='_PlayerState_Update_00425730@4'
COLLISIONS,FRONT,BULLETS,ITEMS=0x1800000,0x1700000,0x1c00000,0x1d00000

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
    w(ANM+0x732454,case.get('next_id',8))
    if case.get('loaded_script'):w(CONFIG+0x800+17*4,CONFIG+0xf00)
    w(CONFIG+0x124,case.get('loading',0))
    if case.get('allocation'):
        uc.mem_write(ANM+0x3ac068,b'\x01')
        if case['allocation']>=2:uc.mem_write(ANM+0x3ac069,b'\x01')
    uc.mem_write(OBJECT+0x4000,bytes([0xa5])*0x3ac)
    # Real lookup lists include an old object and its children. Creation adds
    # a new object with id 9 through the shared boundary below.
    node=ANM+0x1000;old=OBJECT;new=OBJECT+0x1000
    w(ANM+0x72dad4,node);w(ANM+0x72dad8,node);w(node,old);w(old,case.get('object_id',7))
    w(old+0x2c,case.get('angle_bits',1234567));w(old+0x35c,0x20)
    if case.get('helper')=='initialize':
        uc.mem_write(old,bytes([0xa5])*0x3ac)
        w(old+0x35c,case['initial_flags']);w(CONFIG,0x1234)
        if case.get('loaded_script'):
            w(CONFIG+0x800+case['script_index']*4,CONFIG+0xf00)
    if case.get('children'):
        w(old+0x14,node+0x40);w(old+0x18,case.get('children_flagged',0))
        w(node+0x40,OBJECT+0x2000);w(node+0x44,node+0x80)
        w(node+0x80,OBJECT+0x3000)
        w(OBJECT+0x2000+0x35c,0x80);w(OBJECT+0x3000+0x35c,0x100)
    if case.get('tail_next'):
        following_node=node+0x200
        following_object=OBJECT+0x7000
        w(node+4,following_node);w(following_node,following_object)
        w(following_node+8,node);w(following_object,42)
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
    # These cases execute both genuine callers on the same records and lists.
    if case.get('sequence'):
        w(0x47770c,0)
        w(MANAGER+0x464,case.get('stage_frame',10))
        w(MANAGER+0x3500,case.get('familiar_level',3))
        sprite=OBJECT+0x6000
        f(sprite+0x30,16.,32.);w(old+0x394,sprite);f(old+0x3c,1.,1.)
        secondary_object=OBJECT+0x5000;secondary_node=node+0x200
        w(secondary_object,8);w(secondary_node,secondary_object)
        w(ANM+0x72dadc,secondary_node)
        for index,item in enumerate(pickups):
            p=MANAGER+0x49c+item.get('slot',index)*0x5c;d=u(p+0x58)
            f(p+8,float(item.get('current',4)));w(p+0xc,0x476f78);w(p+0x10,1)
            f(p+0x30,item.get('motion_angle',0.),item.get('motion_radius',5.),item.get('radius_step',1.))
            uc.mem_write(p+0x3c,bytes([int(item.get('orbit',False))]))
            w(p+0x48,8 if case.get('effect_secondary') else 0)
            uc.mem_write(d+0x1c,bytes([case.get('ordinal',1)]))
            w(d+0x28,FILTER+0x100 if case.get('effect_callback') else 0)
    if case.get('spawn'):
        descriptor=MANAGER+0x8000
        f(MANAGER+0x3c0,*case.get('spawn_origin',(12.,200.,3.)))
        for index in range(4):
            x,y=case.get('familiar_position',(1234,20001))
            w(MANAGER+0x32dc+index*0x98,x+index*137)
            w(MANAGER+0x32e0+index*0x98,y-index*131)
        for index in range(128 if case.get('spawn_full') else case.get('spawn_slot',0)):
            p=MANAGER+0x49c+index*0x5c
            w(p+0x40,2)
            w(p+0x58,descriptor)
            w(p+0xc,0x476f78)
        slot=MANAGER+0x49c+case.get('spawn_slot',0)*0x5c
        w(slot+0x10,case.get('timer_flags',0))
        w(slot+0xc,0x476f78)
        uc.mem_write(slot+0x3c,bytes([case.get('motion_flags',0)]))
        f(slot+0x20,*case.get('initial_velocity',(1.,2.,9.)))
        f(slot+0x34,case.get('orbit_radius',2.),case.get('radius_step',0.5))
        uc.mem_write(descriptor,bytes([2,0]))
        uc.mem_write(descriptor+2,struct.pack('<h',30))
        f(descriptor+4,*case.get('spawn_offset',(5.,-7.)))
        f(descriptor+0xc,8.,8.)
        f(descriptor+0x14,case.get('spawn_angle',0.5),case.get('spawn_speed',1.))
        uc.mem_write(descriptor+0x1c,bytes([case.get('spawn_ordinal',0),case.get('spawn_type',0)]))
        uc.mem_write(descriptor+0x1e,struct.pack('<hhh',case.get('spawn_script',12),12,case.get('spawn_sound',-1)))
        w(descriptor+0x24,FILTER+0x200 if case.get('spawn_callback') else 0)
        if case.get('spawn_blocked'):
            w(MANAGER+0x42f4+case.get('spawn_ordinal',0)*4,1)
        uc.mem_write(0x492590,bytes(0x1e80))
        for index in range(12):
            w(0x492590+0x620+index*4,case.get('sound_id',3) if index<case.get('sound_slots',0) else -1)
            w(0x492590+0x650+index*4,case.get('sound_count',0))
        if case.get('loaded_script'):
            w(CONFIG+0x800+(case.get('spawn_script',12)+5)*4,CONFIG+0xf00)
            w(CONFIG+0x800+16*4,CONFIG+0xf00)
    if case.get('schedule'):
        schedule_file=MANAGER+0x9000
        w(MANAGER+0x45c,schedule_file)
        for index in range(10):
            entry=MANAGER+0x8000+index*0x100
            uc.mem_write(entry,bytes(uc.mem_read(MANAGER+0x8000,0x34)))
            uc.mem_write(entry,bytes([2,index%2]))
            uc.mem_write(entry+0x1c,bytes([index%5, [0,2,3][index%3]]))
            f(entry+4,5.+index*2,-7.)
            uc.mem_write(entry+0x34,b'\xff')
            w(schedule_file+0x110+index*8,entry)
        uc.mem_write(0x474c48,struct.pack('<H',case.get('schedule_rank',0)))
        w(0x474e5c,case.get('schedule_repeat',0))
        w(MANAGER+0x4474,case.get('schedule_alternate',0))
        w(MANAGER+0x458,case.get('schedule_running',1))
        current=case.get('schedule_frame',0)
        w(MANAGER+0x460,case.get('schedule_previous',current-1))
        w(MANAGER+0x464,current)
        f(MANAGER+0x468,case.get('schedule_elapsed',float(current)))
        w(MANAGER+0x46c,0x476f78)
        w(MANAGER+0x470,case.get('schedule_timer_flags',1))
        f(0x476f78,case.get('schedule_speed',1.))
        w(MANAGER+0x3504,0x12345678)
        uc.mem_write(MANAGER+0x3508,b'\x55')
    if case.get('player_state'):
        for address,size in [(COLLISIONS,0x400000),(FRONT,0x10000),(BULLETS,0x10000),(ITEMS,0x220000)]:
            uc.mem_map(address,size)
        w(0x4776f0,COLLISIONS);w(0x47770c,FRONT);w(0x47781c,BULLETS)
        w(0x477818,ITEMS);w(0x477830,BULLETS+0x6000);w(0x477838,BULLETS+0x6100)
        w(BULLETS+0x6110,case.get('practice_mode',0))
        w(FRONT+0x9eb8,case.get('front_script',0))
        w(CONFIG+0x60,case.get('config_enabled',0))
        if case.get('missing_config'):w(0x477704,0)
        w(0x474c70,case.get('lives',0));w(0x474c98,case.get('hold_counter',0))
        uc.mem_write(0x474c48,struct.pack('<H',case.get('power',100)&0xffff))
        w(0x474e5c,case.get('input_flags',0))
        w(MANAGER+0x458,case.get('player_phase',5))
        frame=case.get('player_frame',0)
        w(MANAGER+0x474,case.get('player_previous',frame-1));w(MANAGER+0x478,frame)
        f(MANAGER+0x47c,case.get('player_elapsed',float(frame)))
        w(MANAGER+0x480,0x476f78);w(MANAGER+0x484,case.get('state_timer_flags',1))
        w(MANAGER+0x488,-1);w(MANAGER+0x48c,0);f(MANAGER+0x490,0.)
        w(MANAGER+0x494,0x476f78);w(MANAGER+0x498,1)
        f(0x476f78,case.get('player_speed',1.))
        w(MANAGER+0x3cc,1234);w(MANAGER+0x3d0,20001)
        f(MANAGER+0x3c0,*case.get('player_origin',(12.34,200.01,3.)))
        f(MANAGER+0x41c,2.,3.,4.);f(MANAGER+0x428,8.,10.,12.);f(MANAGER+0x434,6.,7.,8.)
        f(MANAGER+0x440,11.,190.,2.)
        w(MANAGER+0x3500,case.get('familiar_level',3))
        for index in range(33):w(MANAGER+0x436c+index*8,1000+index);w(MANAGER+0x4370+index*8,2000+index)
        w(COLLISIONS+0x3e0b50,CONFIG)
        normal_slot=case.get('item_normal_slot',0)
        for index in range(150 if case.get('item_normal_full') else normal_slot):
            w(ITEMS+0x14+index*0x3f0+0x3dc,1)
        if normal_slot<150:
            item=ITEMS+0x14+normal_slot*0x3f0
            uc.mem_write(item,bytes([0xa5])*0x3ac)
            w(item+0x3e0,case.get('item_previous_kind',0))
            w(item+0x3c8,4);w(item+0x3cc,5);f(item+0x3d0,5.)
            w(item+0x3d4,0x476f78);w(item+0x3d8,case.get('item_timer_flags',0))
        cursor=case.get('item_cursor',0)
        w(ITEMS+0x21ceb8,cursor);w(ITEMS+0x21cebc,case.get('item_count',0))
        special=ITEMS+0x24eb4+cursor*0x3f0
        w(special+0x3dc,case.get('item_occupied',0))
        w(special+0x3d8,case.get('item_timer_flags',0))
        if case.get('item_loaded_scripts'):
            for index in range(373,402):w(CONFIG+0x800+index*4,CONFIG+0xf00)
        records=case.get('collision_records',[{'slot':index,'state':index%5,
            'countdown':5 if index%2 else 0} for index in [0,1,2,3,4,1995,1996,1997,1998,1999]])
        for item in records:
            record=COLLISIONS+0x60+item['slot']*0x7f0
            uc.mem_write(record+0x446,struct.pack('<H',item.get('state',1)))
            uc.mem_write(record+0x30c,struct.pack('<H',7))
            w(record,item.get('flags',0x10));w(record+4,item.get('countdown',0))
            f(record+0x3b4,*item.get('position',(0.,0.,0.)))
            f(record+0x3f0,item.get('diameter',8.))
            w(record+0x438,item.get('animation_index',-1))
            w(record+0x3f8,4);w(record+0x3fc,5);f(record+0x400,5.)
            w(record+0x404,0x476f78);w(record+0x408,item.get('timer_flags',0))
            if item.get('loaded_script'):
                w(CONFIG+0x800+item.get('animation_index',17)*4,CONFIG+0xf00)
        w(BULLETS+0x18,BULLETS+0x100)
        w(BULLETS+0x800+5*4,FILTER+0x300)
        for index in range(3):
            bullet=BULLETS+0x100+index*0x100
            w(bullet,BULLETS+0x800);w(bullet+8,bullet+0x100 if index<2 else 0)
            w(bullet+0xc,index)
        w(MANAGER+0x430c,9);w(MANAGER+0x4310,case.get('invulnerable',0))
        f(MANAGER+0x4314,float(case.get('invulnerable',0)))
        w(MANAGER+0x4318,0x476f78);w(MANAGER+0x431c,1)
        w(MANAGER+0x370,case.get('animation_flags',0x40008020));w(MANAGER+0x314,0x11223344)
        for slot in case.get('indicator_slots',[]):
            region=MANAGER+0x350c+slot*0x6c
            f(region,8.,0.5,0.125,0.25,8.,8.)
            f(region+0x18,12.345,200.125,3.,1.25,-2.5,4.)
            f(region+0x30,2.,0.5,3.,0.25)
            w(region+0x40,case.get('indicator_motion_flags',0))
            w(region+0x44,4);w(region+0x48,case.get('indicator_frames',5))
            f(region+0x4c,float(case.get('indicator_frames',5)))
            w(region+0x50,0x476f78);w(region+0x54,1);w(region+0x68,3)
        # The angle helper's scripted x87 result is supplied by a separate
        # boundary implementation. The retail/native instruction bodies are intact.
        f(INPUT+0x100,0.375)
        angle_cleanup=8 if native else 0
        code=b'\xd9\x05'+struct.pack('<I',INPUT+0x100)+(b'\xc2'+struct.pack('<H',angle_cleanup) if angle_cleanup else b'\xc3')
        uc.mem_write(FILTER+0x400,code)
    if case.get('collision_unit'):
        f(INPUT,*case.get('collision_point',(11.,190.,2.)))
    calls=[]
    coverage={}
    collision_helpers={}
    if case.get('player_state'):
        for symbol,address,name in [
                ('?Activate@PlayerCollisionRecord@@QAEHXZ',0x408030,'activate'),
                ('?Check@PlayerCollisionEngine@@QAEHPBUVec3@@MHH@Z',0x408100,'check'),
                ('?OutsideBounds@PlayfieldPoint@@QBEHMM@Z',0x4086b0,'bounds'),
                ('?LoadScript@AnimationResource_0043e710@@QAEPAXPAUEntity@@H@Z',0x43e710,'loader'),
                ('?CreateOffset@AnimationResource_0043e710@@QAE?AUAnimationRef@@HPBUVector3@@@Z',0x448db0,'creator'),
                ('?Spawn@PlayerItemManager@@QAEHPBUVector3@@HHMM@Z',0x41bb00,'item_spawn'),
                ('?Entity_StartScript_00404f30@@YGXPAUAnimationResource_0043e710@@PAUEntity@@H@Z',0x404f30,'start_script'),
                ('?SetPolar@ItemPolarVelocity_0041bb00@@QAEPAU1@MM@Z',0x41beb0,'item_polar')]:
            collision_helpers[symbols[symbol] if native else address]=name
    collision_calls={name:0 for name in collision_helpers.values()}
    primary=symbols[PRIMARY] if native and full_creation else 0x448d00
    schedule_helpers={}
    if case.get('schedule'):
        for symbol,address,name in [
                (SEQUENCE,0x4281d0,'update'),
                ('?Dispatch@PlayerState@@QAEHH@Z',0x428160,'dispatch'),
                ('?SetSchedulerValue@PlayerSchedulerRecord@@QAEXH@Z',0x405410,'set'),
                ('?Tick@FrameTimer@@QAEXXZ',0x404ed0,'tick'),
                ('?Advance@FrameTimer@@QAEXM@Z',0x44bf40,'advance'),
                (SPAWN,0x427e90,'spawn')]:
            schedule_helpers[symbols[symbol] if native else address]=name
    def hook(machine,address,size,user):
        sp=reg('esp')
        if address in collision_helpers:
            name=collision_helpers[address]
            collision_calls[name]+=1
            if name=='item_spawn':
                calls.append(('item_spawn',reg('eax')-ITEMS,bytes(uc.mem_read(reg('ecx'),12)).hex(),
                    *[u(sp+4+i*4) for i in range(4)]))
        if case.get('player_state'):
            if address==FILTER+0x300:
                bullet=reg('ecx');assert u(sp+4)==0
                calls.append(('bullet_retire',bullet-BULLETS))
                w(bullet+0xc,1)
                if case.get('mutate_bullet_next'):w(bullet+8,0)
                ret(4,0);return
            if address==0x41c800:
                manager=reg('ecx' if native else 'eax')
                point=u(sp+4) if native else reg('ebx')
                offset=8 if native else 4
                calls.append(('bullet_evaluate',manager-BULLETS,bytes(uc.mem_read(point,12)).hex(),u(sp+offset),u(sp+offset+4)))
                ret(12 if native else 8,0);return
            if address==0x41c850:
                calls.append(('bullet_reset',reg('ecx' if native else 'eax')-BULLETS));w(BULLETS+0x18,0)
                ret(0,0);return
            if address==0x4250b0:
                player=reg('ecx' if native else 'edi');assert player==MANAGER
                calls.append(('move',player-MANAGER))
                if case.get('movement_changes_position'):f(MANAGER+0x3c0,80.,220.,5.)
                ret(0,0);return
            if address in [0x426f70,0x4269d0,0x405860]:
                calls.append(({0x426f70:'refresh',0x4269d0:'contact',0x405860:'initialize_player'}[address],u(sp+4)))
                if address==0x405860:w(PLAYER+0x28,1)
                ret(4,0);return
            if address==0x4054b0:
                owner=reg('ecx' if native else 'esi');assert owner==FRONT
                whole=u(sp+4) if native else reg('edx');fraction=u(sp+8) if native else u(sp+4)
                calls.append(('power_digits',whole,fraction));w(FRONT+0x800,whole);w(FRONT+0x804,fraction)
                ret(8 if native else 4,0);return
            if address==0x412e70:
                assert reg('ecx')==0x474c40
                calls.append(('gauge_add',u(sp+4)));w(0x474c40,u(0x474c40)+u(sp+4))
                ret(4,0);return
            if address==0x426610:
                player=u(sp+4) if native else reg('ecx');point=u(sp+8) if native else reg('eax')
                calls.append(('angle_to_point',player-MANAGER,bytes(uc.mem_read(point,12)).hex()))
                uc.reg_write(UC_X86_REG_EIP,FILTER+0x400);return
            if address==0x4231d0:
                calls.append(('death_scene',reg('ecx' if native else 'edi')-BULLETS));ret(0,0);return
            if address==0x40ac90:
                calls.append(('input_mode',reg('ecx' if native else 'eax'),u(sp+4)));w(0x491c28,u(sp+4))
                ret(4,0);return
        if address in schedule_helpers:
            name=schedule_helpers[address]
            calls.append(('schedule_helper',name))
            if name=='dispatch':
                assert reg('edi')==MANAGER
            elif name in ['tick','advance']:
                assert reg('esi')==MANAGER+0x460
            elif name=='set':
                assert reg('eax')==MANAGER+0x460
            elif name=='spawn':
                assert u(sp+4)==MANAGER
                calls.append(('scheduled_entry',u(sp+8)-MANAGER,u(sp+12)))
        if case.get('spawn'):
            if address in [0x427f05,0x427f3a,0x427fc9,0x427fd7,0x4280bb,0x4280d0,0x428130,0x42814d]:
                coverage[hex(address)]=coverage.get(hex(address),0)+1
            if address==FILTER+0x200:
                p=reg('edx')
                assert reg('ecx')==MANAGER
                assert MANAGER+0x49c<=p<MANAGER+0x49c+128*0x5c and (p-MANAGER-0x49c)%0x5c==0
                assert u(sp+4)==case.get('spawn_frame',15)&0xffffffff
                calls.append(('spawn_callback',p-MANAGER,u(sp+4)))
                action=case['spawn_callback']
                if action=='move':f(p+0x14,100.,250.,6.)
                elif action=='clear_state':w(p+0x40,0)
                elif action=='sound':uc.mem_write(MANAGER+0x8022,struct.pack('<h',3))
                elif action=='swap_descriptor':w(p+0x58,MANAGER+0x8040)
                uc.reg_write(UC_X86_REG_ECX,0x11112222)
                uc.reg_write(UC_X86_REG_EDX,0x33334444)
                ret(4,0x55667788);return
            if address==(symbols[PAN] if native else 0x43dd10):
                assert reg('esi')==0x492590
                calls.append(('queue_pan',reg('ebx'),u(sp+4)))
        if address==FILTER+0x100:
            p=reg('edx')
            assert reg('ecx')==MANAGER
            calls.append(('effect_callback',p-MANAGER))
            if case['effect_callback']=='clear_state':w(p+0x40,0)
            elif case['effect_callback']=='clear_primary':w(p+0x44,0)
            elif case['effect_callback']=='move':f(p+0x14,400.,500.,3.)
            uc.reg_write(UC_X86_REG_ECX,0x11112222)
            uc.reg_write(UC_X86_REG_EDX,0x33334444)
            ret(0,0);return
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
            if case.get('spawn'):
                if case.get('rotate_primary'):
                    object_address=u(sp+4)
                    w(object_address+0x35c,u(object_address+0x35c)|0x8000000)
            if case.get('sequence'):
                # The scripted loaded animation supplies a valid sprite for
                # the next effect update's real culling calculation.
                object_address=u(sp+4)
                w(object_address+0x394,OBJECT+0x6000)
                f(object_address+0x3c,1.,1.)
            ret(4,0);return
    for address in [FILTER,FILTER+0x100,primary,0x452493,0x402050,0x43ee30]:
        uc.hook_add(UC_HOOK_CODE,hook,begin=address,end=address)
    if case.get('spawn'):
        for address in [FILTER+0x200,symbols[PAN] if native else 0x43dd10,
                         0x427f05,0x427f3a,0x427fc9,0x427fd7,0x4280bb,0x4280d0,0x428130,0x42814d]:
            uc.hook_add(UC_HOOK_CODE,hook,begin=address,end=address)
    if case.get('player_state'):
        for address in [FILTER+0x300,0x41c800,0x41c850,0x4250b0,0x426f70,0x4269d0,0x405860,0x4054b0,0x412e70,0x426610,0x4231d0,0x40ac90]:
            uc.hook_add(UC_HOOK_CODE,hook,begin=address,end=address)
    for address in collision_helpers:
        uc.hook_add(UC_HOOK_CODE,hook,begin=address,end=address)
    for address in schedule_helpers:
        uc.hook_add(UC_HOOK_CODE,hook,begin=address,end=address)
    sequence_results=[]
    uc.reg_write(UC_X86_REG_FPCW,case.get('fpcw',0x37f))
    uc.reg_write(UC_X86_REG_FPTAG,0xffff);uc.reg_write(UC_X86_REG_FPSW,0)
    for operation in case.get('sequence',['sweep']):
        sp=STACK+0x8000;w(sp,STOP)
        for register,value in PRESERVED.items():uc.reg_write(register,value)
        uc.reg_write(UC_X86_REG_ESP,sp)
        if operation=='itemspawn':
            f(INPUT,*case.get('item_position',(11.,190.,2.)))
            uc.reg_write(UC_X86_REG_EAX,ITEMS);uc.reg_write(UC_X86_REG_ECX,INPUT)
            w(sp+4,case.get('item_kind',1));w(sp+8,case.get('item_identifier',0xffffff))
            f(sp+12,case.get('item_angle',0.375),case.get('item_speed',3.))
            entry=symbols['?Spawn@PlayerItemManager@@QAEHPBUVector3@@HHMM@Z'] if native else 0x41bb00
        elif operation=='collisioncheck':
            uc.reg_write(UC_X86_REG_EAX,COLLISIONS)
            uc.reg_write(UC_X86_REG_EBX,INPUT)
            f(sp+4,case.get('collision_radius',64.))
            w(sp+8,case.get('spawn_item',0));w(sp+12,case.get('filter_countdown',0))
            symbol='?Check@PlayerCollisionEngine@@QAEHPBUVec3@@MHH@Z'
            entry=symbols[symbol] if native else 0x408100
        elif operation=='activate':
            uc.reg_write(UC_X86_REG_ESI,COLLISIONS+0x60+case.get('activate_slot',0)*0x7f0)
            entry=symbols['?Activate@PlayerCollisionRecord@@QAEHXZ'] if native else 0x408030
        elif operation=='stateupdate':
            w(sp+4,MANAGER)
            entry=symbols[STATE_UPDATE] if native else 0x425730
        elif operation=='schedule':
            uc.reg_write(UC_X86_REG_EAX,MANAGER)
            entry=symbols[SEQUENCE] if native else 0x4281d0
        elif operation=='spawn':
            w(sp+4,MANAGER);w(sp+8,MANAGER+0x8000);w(sp+12,case.get('spawn_frame',15))
            entry=symbols.get(SPAWN,symbols.get(SPAWN_MEMBER)) if native else 0x427e90
        elif operation=='effect':
            w(sp+4,MANAGER)
            entry=symbols[EFFECT] if native else 0x428280
        elif case.get('helper')=='initialize':
            uc.reg_write(UC_X86_REG_ECX,CONFIG)
            w(sp+4,old);w(sp+8,case['script_index'])
            entry=symbols[INITIALIZE] if native else 0x449870
        elif case.get('helper')=='mark':
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
        expected_preserved={register:uc.reg_read(register) for register in PRESERVED}
        error=None
        try:uc.emu_start(entry,STOP,count=case.get('instruction_budget',100000))
        except UcError as exc:error=str(exc)
        if error:
            if not case.get('fault'):raise AssertionError({'label':case['label'],'native':bool(native),
                'pc':hex(reg('eip')),'error':error,'calls':calls})
            return {'fault':error,'calls':calls}
        assert not case.get('fault'),case['label']+' expected fault'
        assert reg('eip')==STOP,'instruction budget'
        cleanup=20 if operation=='itemspawn' else (16 if operation=='collisioncheck' else (4 if operation=='activate' else (8 if operation=='stateupdate' else (4 if operation=='schedule' else (16 if operation=='spawn' else (12 if case.get('helper')=='initialize' else (8 if operation=='effect' else (8 if case.get('helper')=='mark' else (4 if leaf else 16)))))))))
        assert reg('esp')==sp+cleanup,'return cleanup'
        for register,value in expected_preserved.items():assert uc.reg_read(register)==value,'preserved register'
        assert (reg('fpsw')>>11)&7==0,'x87 stack balance'
        sequence_results.append((operation,reg('eax')))
    return {'result':reg('eax'),**({'sequence_results':sequence_results} if case.get('sequence') else {}),'calls':calls,'manager_sha256':hashlib.sha256(uc.mem_read(MANAGER,0x10000)).hexdigest(),
        'objects_sha256':hashlib.sha256(uc.mem_read(OBJECT,0x10000)).hexdigest(),
        'lists_sha256':hashlib.sha256(uc.mem_read(ANM,0x740000)).hexdigest(),
        **({'collision_calls':collision_calls,'collisions_sha256':hashlib.sha256(uc.mem_read(COLLISIONS,0x400000)).hexdigest(),
             'front_sha256':hashlib.sha256(uc.mem_read(FRONT,0x10000)).hexdigest(),
             'bullets_sha256':hashlib.sha256(uc.mem_read(BULLETS,0x10000)).hexdigest(),
             'items_sha256':hashlib.sha256(uc.mem_read(ITEMS,0x220000)).hexdigest(),
             'player_globals':{hex(a):u(a) for a in [0x474c40,0x474c48,0x474c70,0x474c98,0x476f78,0x491c28]}} if case.get('player_state') else {}),
        'score':u(0x474c44),'input':bytes(uc.mem_read(INPUT,20)).hex(),'fpcw':reg('fpcw'),
        **({'sound_queue_sha256':hashlib.sha256(uc.mem_read(0x492590,0x1e80)).hexdigest(),
            'retail_coverage':coverage if not native else {}} if case.get('spawn') else {})}

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
    for word,matched,secondary,flagged in itertools.product(
            [0,1,7,0x7fffffff,0x80000000,0xffffffff], [False,True], [False,True], [0,1]):
        yield {'label':f'reference_bits_{word:08x}_{matched}_{secondary}_{flagged}',
               'helper':'mark','object_id':word,
               'handle':word if matched else word^0x40000000,
               'secondary':secondary,'children':True,'children_flagged':flagged}
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
    for next_id,tail_next,loaded,kind in itertools.product(
            [0,7,0xfffffffe,0xffffffff],[False,True],[False,True],[0,2]):
        yield {'label':f'registration_{next_id:08x}_{tail_next}_{loaded}_{kind}',
            'next_id':next_id,'tail_next':tail_next,'loaded_script':loaded,
            'pickups':[{'type':kind}]}
    for flags,index,loaded,loading in itertools.product(
            [0,0x500,0x40000000,0xffffffff],[1,17,63],[False,True],[0,1]):
        yield {'label':f'public_initialize_{flags:08x}_{index}_{loaded}_{loading}',
            'helper':'initialize','initial_flags':flags,'script_index':index,
            'loaded_script':loaded,'loading':loading}
    rng=random.Random(0x4059f0)
    for index in range(80):
        yield {'label':f'random_{index}','center':(rng.uniform(-40,40),rng.uniform(-10,80)),
            'size':(rng.uniform(0,32),rng.uniform(0,32)),
            'regions':[{'slot':rng.randrange(32),'flags':rng.choice([1,3]),'angle':rng.uniform(-3,3),
                'size':(rng.uniform(0,64),rng.uniform(0,64)),
                'center':(rng.uniform(-40,40),rng.uniform(-10,80),0.),'radius':rng.uniform(0,64)}]}

def main():
    work=Path('matching2/build/experiments/player_item_spawn_2026_10_06')/(sys.argv[1] if len(sys.argv)>1 else 'initial_graph')
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
