"""Execute complete scheduled creation and its genuine native helper graph."""
import hashlib
import itertools
import json
from pathlib import Path
import sys

sys.path.insert(0, str(Path(__file__).resolve().parent))
from differential import run
from matching2.tools.common.pe import PEImage
from matching2.tools.matching.equivalence import MAP_SYMBOL

def cases():
    for ordinal,type_,timer_flags,motion_flags in itertools.product(range(5),[0,2,3],[0,1],[0,1]):
        yield {'label':f'spawn_{ordinal}_{type_}_{timer_flags}_{motion_flags}',
               'spawn_ordinal':ordinal,'spawn_type':type_, 'timer_flags':timer_flags,
               'motion_flags':motion_flags}
    for slot,type_ in itertools.product([1,63,127],[0,3]):
        yield {'label':f'spawn_slot_{slot}_{type_}','spawn_slot':slot,'spawn_type':type_}
    yield {'label':'spawn_full','spawn_full':True}
    for ordinal in range(5):
        yield {'label':f'spawn_blocked_{ordinal}','spawn_ordinal':ordinal,
               'spawn_type':3,'spawn_blocked':True}
    for callback,frame in itertools.product(['move','clear_state','sound','swap_descriptor'],[-1,0,15,2147483647]):
        yield {'label':f'spawn_callback_{callback}_{frame}','spawn_callback':callback,'spawn_frame':frame}
    for type_,loading,loaded,allocation in itertools.product([0,3],[0,1],[False,True],[0,1,2]):
        yield {'label':f'spawn_resource_{type_}_{loading}_{loaded}_{allocation}',
               'spawn_type':type_,'loading':loading,'loaded_script':loaded,'allocation':allocation,
               'next_id':0xfffffffe,'tail_next':True}
    for type_,cw,ordinal in itertools.product([0,3],[0x37f,0x27f,0x7f],[0,1,4]):
        yield {'label':f'spawn_fp_{type_}_{cw}_{ordinal}','spawn_type':type_,
               'fpcw':cw,'spawn_ordinal':ordinal,'familiar_position':(-1234567,9876543),
               'spawn_angle':-7.5,'spawn_speed':0.125,'spawn_sound':3}
    for slots,count,pan in itertools.product([0,1,12],[0,127,128],[-256.,0.,100.,224.]):
        yield {'label':f'spawn_sound_{slots}_{count}_{pan}','spawn_sound':3,
               'sound_slots':slots,'sound_count':count,'spawn_origin':(pan,200.,3.)}
    for type_,cw,order in itertools.product([0,3],[0x37f,0x27f,0x7f],
            [['spawn','effect','sweep'],['spawn','spawn','sweep','effect'],['spawn','effect','spawn','effect']]):
        yield {'label':f'spawn_sequence_{type_}_{cw}_{order}','spawn_type':type_,
               'fpcw':cw,'sequence':order,'spawn_callback':'move','loaded_script':True}
    yield {'label':'spawn_rotate','rotate_primary':True,'loaded_script':True}
    yield {'label':'spawn_sound_full_unmatched','spawn_sound':3,'sound_slots':12,'sound_id':7}

if __name__=='__main__':
    work=Path('matching2/build/experiments/player_movement_state_2026_10_06')/(sys.argv[1] if len(sys.argv)>1 else 'genuine_graph')
    retail=PEImage(Path('matching2/build/oracle/th10.exe').read_bytes())
    native=PEImage((work/'model.exe').read_bytes())
    symbols={name:int(address,16) for name,address,origin in MAP_SYMBOL.findall((work/'model.map').read_text())}
    observations=[];failures=[];coverage={}
    suite=[{'spawn':True,'sequence':['spawn'],**case} for case in cases()]
    case_path=work/'spawn_cases.json'
    case_path.write_text(json.dumps(suite,indent=2)+'\n')
    for case in suite:
        actual=run(retail,None,{},case,full_creation=True)
        candidate=run(retail,native,symbols,case,full_creation=True)
        for key,count in actual.pop('retail_coverage').items():coverage[key]=coverage.get(key,0)+count
        candidate.pop('retail_coverage')
        observations.append({'case':case['label'],'retail':actual,'native':candidate})
        if actual!=candidate:failures.append(case['label'])
    path=work/'spawn_observations.json';path.write_text(json.dumps(observations,indent=2)+'\n')
    report={'cases_sha256':hashlib.sha256(case_path.read_bytes()).hexdigest(),
            'cases':len(observations),'failures':failures,'retail_branch_coverage':coverage,
            'observations_sha256':hashlib.sha256(path.read_bytes()).hexdigest(),
            'native_pe_sha256':hashlib.sha256((work/'model.exe').read_bytes()).hexdigest(),
            'executed':'complete scheduled spawn, native creation/registration/lookup/initialization, actual motion and sound queue',
            'boundaries':['successful operator new scripted','animation VM effects scripted','descriptor initialization callback scripted',
                          'retail constructor, polar/angle and CRT math run in both executions'],
            'selection_evidence':False}
    (work/'spawn_differential.json').write_text(json.dumps(report,indent=2)+'\n')
    print(json.dumps(report,indent=2));assert not failures
