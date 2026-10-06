"""Execute complete collision callees and their real owner; no compiler test callers."""
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
    positions=[(0.,200.,7.),(-200.,200.,7.),(-199.99,200.,7.),
        (199.99,200.,7.),(200.,200.,7.),(0.,-8.,7.),(0.,-7.99,7.),
        (0.,455.99,7.),(0.,456.,7.),(float('nan'),200.,7.)]
    for slot,state,position,timer_flags,creation in itertools.product(
            [0,1999],[0,1,2,3,4,65535],positions,[0,1],['none','empty','loaded']):
        record={'slot':slot,'state':state,'position':position,'timer_flags':timer_flags,
                'animation_index':-1 if creation=='none' else 17,'loaded_script':creation=='loaded'}
        yield {'label':f'activation_{slot}_{state}_{position}_{timer_flags}_{creation}',
               'activate_slot':slot,'collision_records':[record], 'sequence':['activate']}
    for slot,state,position,countdown,filtered,spawn in itertools.product(
            [0,1999],[0,1,2,3,4],[(11.,190.,2.),(79.,190.,99.),(79.01,190.,99.),
            (-194.,190.,2.),(float('nan'),190.,2.)],[0,5],[0,1],[0,1]):
        yield {'label':f'check_{slot}_{state}_{position}_{countdown}_{filtered}_{spawn}',
               'collision_records':[{'slot':slot,'state':state,'position':position,'countdown':countdown}],
               'filter_countdown':filtered,'spawn_item':spawn,'sequence':['collisioncheck']}
    for phase,frame,slot,loaded,allocation,loading,control in itertools.product(
            [0,1,3],[0,29],[0,1999],[False,True],[0,1,2],[0,1],[0x37f,0x27f,0x7f]):
        yield {'label':f'owner_{phase}_{frame}_{slot}_{loaded}_{allocation}_{loading}_{control}',
               'player_phase':phase,'player_frame':frame,'allocation':allocation,
               'loading':loading,'fpcw':control,'sequence':['stateupdate'],
               'collision_records':[{'slot':slot,'state':1,'position':(11.,190.,2.),
                   'animation_index':17,'loaded_script':loaded}]}
    for phase in [0,1,3]:
        yield {'label':f'all_2000_{phase}','player_phase':phase,'player_frame':29,
               'collision_records':[{'slot':i,'state':1,'position':(11.,190.,2.)} for i in range(2000)],
               'sequence':['stateupdate'],'instruction_budget':1000000}
    for phase in [0,1]:
        yield {'label':f'repeated_loaded_{phase}','player_phase':phase,'player_frame':0,
               'collision_records':[{'slot':0,'state':1,'position':(11.,190.,2.),
                    'animation_index':17,'loaded_script':True}],
               'sequence':['stateupdate','stateupdate']}


if __name__=='__main__':
    work=Path('matching2/build/experiments/player_item_spawn_2026_10_06')/(
        sys.argv[1] if len(sys.argv)>1 else 'genuine_graph')
    retail=PEImage(Path('matching2/build/oracle/th10.exe').read_bytes())
    native=PEImage((work/'model.exe').read_bytes())
    symbols={n:int(a,16) for n,a,_ in MAP_SYMBOL.findall((work/'model.map').read_text())}
    suite=[{'player_state':True,'collision_unit':True,**case} for case in cases()]
    if '--smoke' in sys.argv:suite=suite[::100]
    (work/'collision_cases.json').write_text(json.dumps(suite,indent=2)+'\n')
    observations,failures=[],[]
    totals={name:0 for name in ['activate','check','bounds','loader','creator','item_spawn','start_script','item_polar']}
    for case in suite:
        expected=run(retail,None,{},case,full_creation=True)
        actual=run(retail,native,symbols,case,full_creation=True)
        observations.append({'case':case['label'],'retail':expected,'native':actual})
        for name,count in expected['collision_calls'].items():totals[name]+=count
        if expected!=actual:
            failures.append({'case':case['label'],'fields':[k for k in expected if expected[k]!=actual.get(k)]})
    path=work/'collision_observations.json';path.write_text(json.dumps(observations,indent=2)+'\n')
    report={'cases':len(suite),'failures':failures,'executed_helper_calls':totals,
        'cases_sha256':hashlib.sha256((work/'collision_cases.json').read_bytes()).hexdigest(),
        'observations_sha256':hashlib.sha256(path.read_bytes()).hexdigest(),
        'native_pe_sha256':hashlib.sha256(native.data).hexdigest(),
        'smoke':'--smoke' in sys.argv,'instruction_patches':0,'selection_evidence':False,
        'scope':'Full owner plus direct execution of complete collision and activation bodies; 2000 records, first/last slots, all states, boundary/unordered positions, countdown filter, spawn path, timer flags, loaded/empty/loading resources and pool/heap allocation.',
        'boundaries':['VM and bottom player-state collaborators scripted; collision/activation/bounds/offset creation/script loading execute genuine complete bodies.',
                      'Direct private-entry tests use emulator input registers; no compiler test caller or wrapper exists.']}
    (work/'collision_differential.json').write_text(json.dumps(report,indent=2)+'\n')
    print(json.dumps(report,indent=2))
    assert not failures
