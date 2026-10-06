"""Compare full item spawn, its callers and animation graph under bounded VM effects."""
import hashlib
import itertools
import json
from pathlib import Path
import sys
sys.path.insert(0,str(Path(__file__).resolve().parent))
from differential import run
from matching2.tools.common.pe import PEImage
from matching2.tools.matching.equivalence import MAP_SYMBOL


def cases():
    for kind,power,slot,loaded,control in itertools.product(
            [-1,0,1,3,4,9,10,11,12],[-1,0,99,100,32767],[0,1,149],[False,True],[0x37f,0x27f,0x7f]):
        yield {'label':f'normal_{kind}_{power}_{slot}_{loaded}_{control}','item_kind':kind,
            'power':power,'item_normal_slot':slot,'item_loaded_scripts':loaded,'fpcw':control,
            'item_previous_kind':3 if slot!=1 else 1,'item_timer_flags':slot%4,
            'item_position':(-200. if slot==0 else (200. if slot==149 else 11.),190.,7.),
            'item_identifier':0x89abcdef,'sequence':['itemspawn']}
    for kind,control in itertools.product([1,10,11],[0x37f,0x27f,0x7f]):
        yield {'label':f'full_{kind}_{control}','item_kind':kind,'item_normal_full':True,
            'fpcw':control,'sequence':['itemspawn']}
    for cursor,count,occupied,angle,control in itertools.product(
            [-1,0,1,2047],[-1,0,254,255,256,510,511,512,1023,2147483647],[0,5],
            [-1.5707963705062866,0.,6.2831854820251465],[0x37f,0x27f,0x7f]):
        yield {'label':f'special_{cursor}_{count}_{occupied}_{angle}_{control}','item_kind':8,
            'item_cursor':cursor,'item_count':count,'item_occupied':occupied,'item_angle':angle,
            'item_timer_flags':cursor&3,'fpcw':control,'sequence':['itemspawn']}
    for frame,power,full,loaded in itertools.product([3,4],[0,99,100],[False,True],[False,True]):
        yield {'label':f'death_fan_{frame}_{power}_{full}_{loaded}','player_phase':2,
            'player_frame':frame,'power':power,'item_normal_full':full,'item_loaded_scripts':loaded,
            'sequence':['stateupdate']}
    for slot,kind in itertools.product([0,149],[1,8,10,11]):
        yield {'label':f'repeat_{slot}_{kind}','item_kind':kind,'item_normal_slot':slot,
            'item_loaded_scripts':True,'sequence':['itemspawn','itemspawn']}
    for x in [-192.,192.,float('nan')]:
        yield {'label':f'clamp_{x}','item_position':(x,200.,7.),'sequence':['itemspawn']}


if __name__=='__main__':
    work=Path('matching2/build/experiments/player_item_spawn_2026_10_06')/(
        sys.argv[1] if len(sys.argv)>1 else 'genuine_graph')
    retail=PEImage(Path('matching2/build/oracle/th10.exe').read_bytes())
    native=PEImage((work/'model.exe').read_bytes())
    symbols={n:int(a,16) for n,a,_ in MAP_SYMBOL.findall((work/'model.map').read_text())}
    suite=[{'player_state':True,**case} for case in cases()]
    if '--smoke' in sys.argv:suite=suite[::100]
    (work/'item_cases.json').write_text(json.dumps(suite,indent=2)+'\n')
    observations,failures=[],[];totals={}
    for case in suite:
        expected=run(retail,None,{},case,full_creation=True)
        actual=run(retail,native,symbols,case,full_creation=True)
        observations.append({'case':case['label'],'retail':expected,'native':actual})
        for name,count in expected['collision_calls'].items():totals[name]=totals.get(name,0)+count
        if expected!=actual:failures.append({'case':case['label'],'fields':[k for k in expected if expected[k]!=actual.get(k)]})
    path=work/'item_observations.json';path.write_text(json.dumps(observations,indent=2)+'\n')
    report={'cases':len(suite),'failures':failures,'executed_helper_calls':totals,
        'cases_sha256':hashlib.sha256((work/'item_cases.json').read_bytes()).hexdigest(),
        'observations_sha256':hashlib.sha256(path.read_bytes()).hexdigest(),
        'native_pe_sha256':hashlib.sha256(native.data).hexdigest(),'smoke':'--smoke' in sys.argv,
        'instruction_patches':0,'selection_evidence':False,
        'scope':'Complete normal/special pools, all spawn branches, signed power/remapping, pool exhaustion, retirement, script initialization, ring occupancy/cursor/count thresholds, three x87 precision controls, real death-fan caller and repeated calls.',
        'boundaries':['VM effects and successful allocation scripted; full collision, spawning, script startup and animation graph execute.',
                      'Finite gameplay angle range; direct private entries are emulator fixture inputs, not compiler callers.']}
    (work/'item_differential.json').write_text(json.dumps(report,indent=2)+'\n');print(json.dumps(report,indent=2))
    assert not failures
