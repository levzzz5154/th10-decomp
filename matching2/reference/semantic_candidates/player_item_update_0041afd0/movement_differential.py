"""Execute complete movement and animation trees with only VM/callback boundaries scripted."""
import hashlib
import itertools
import json
from pathlib import Path
import sys
sys.path[:0]=[str(Path.cwd()),str(Path(__file__).resolve().parent)]
from differential import run
from matching2.tools.common.pe import PEImage
from matching2.tools.matching.equivalence import MAP_SYMBOL

def cases():
    for directions,focus,previous,loaded in itertools.product(range(16),[0,4],[-1,0,1],[False,True]):
        yield {'label':f'direction_{directions}_{focus}_{previous}_{loaded}',
               'input_flags':directions*16+focus,'previous_movement':[previous,17],
               'config_enabled':1,'auxiliary_frame':4,'movement_loaded_scripts':loaded}
    for missing,enabled,frame,character,shot,age,focus in itertools.product(
            [False,True],[0,1],[-1,3,4,30],[0,1],[0,2],[-1,0,29,30,99],[0,4]):
        yield {'label':f'focus_{missing}_{enabled}_{frame}_{character}_{shot}_{age}_{focus}',
               'missing_config':missing,'config_enabled':enabled,'auxiliary_frame':frame,
               'state':character,'shot_type':shot,'transition_age':age,
               'input_flags':0x90|focus,'slow_handle':7,'children':True}
    for x,y,speed,cw in itertools.product([-19000,-18400,-18399,18399,18400,19000],
            [0,3199,3200,3201,43199,43200,43201],[0.5,1.,2.],[0x37f,0x27f,0x7f]):
        yield {'label':f'clamp_{x}_{y}_{speed}_{cw}', 'integer_position':[x,y],
               'input_flags':0xa0,'player_speed':speed,'fpcw':cw}
    for level,directions,focus in itertools.product(range(5),[0,0x10,0x40,0xa0],[0,4]):
        yield {'label':f'history_{level}_{directions}_{focus}', 'familiar_level':level,
               'input_flags':directions|focus,'config_enabled':1,'auxiliary_frame':4}
    for slot,age,reset,delta,focus in itertools.product(range(4),[-1,0,29,30,33,99,100],
            [0,1],[0,1,3,-3,10001],[0,4]):
        desired=[1234+200,20001-100] if not focus else [1234-300,20001+400]
        yield {'label':f'orbit_{slot}_{age}_{reset}_{delta}_{focus}',
               'config_enabled':1,'auxiliary_frame':4,'input_flags':focus,
               'transition_age':age,'state':0,'orbits':[{'slot':slot,
                   'reset':reset,'current':[desired[0]-delta,desired[1]+delta]}]}
    for reset,age,current,handle in itertools.product([0,1],[-1,0,29,30,100],
            [[0,0],[1234,20001]],[0,7,123]):
        yield {'label':f'callback_{reset}_{age}_{current}_{handle}',
               'orbits':[{'callback':True,'callback_reset':reset,'callback_age':age,
                    'callback_current':current,'callback_desired':[-171,129],
                    'callback_handle':handle}]}
    yield {'label':'four_orbits_repeated','sequence':['move','move'],
           'input_flags':0x60,'config_enabled':1,'auxiliary_frame':4,'orbits':[
               {'slot':index,'callback':True,'callback_desired':[100+index,200-index],
                'reset':index%2} for index in range(4)],'children':True}
    for operation,handle,secondary,children,flagged,cw in itertools.product(
            ['stop_frame','set_position','translated_position'],[0,7,8,123],
            [False,True],[False,True],[0,1],[0x37f,0x27f,0x7f]):
        yield {'label':f'helper_{operation}_{handle}_{secondary}_{children}_{flagged}_{cw}',
               'sequence':[operation],'slow_handle':handle,'secondary':secondary,
               'children':children,'children_flagged':flagged,'fpcw':cw}
    for handle,children,flagged,focus in itertools.product([0,7,123],[False,True],[0,1],[0,4]):
        yield {'label':f'slow_handle_{handle}_{children}_{flagged}_{focus}',
               'slow_handle':handle,'children':children,'children_flagged':flagged,
               'config_enabled':1,'auxiliary_frame':4,'input_flags':focus,
               'sequence':['move','move'],'movement_loaded_scripts':True}
    for speeds in [[0,0,0,0],[1,1,1,1],[399,199,281,140]]:
        yield {'label':f'custom_speeds_{speeds}','movement_speeds':speeds,'input_flags':0x50}

if __name__=='__main__':
    work=Path('matching2/build/experiments/player_item_update_2026_10_06')/(sys.argv[1] if len(sys.argv)>1 else 'genuine_graph')
    retail=PEImage(Path('matching2/build/oracle/th10.exe').read_bytes())
    native=PEImage((work/'model.exe').read_bytes())
    symbols={name:int(address,16) for name,address,_ in MAP_SYMBOL.findall((work/'model.map').read_text())}
    suite=[{'player_state':True,'sequence':['move'],'collision_records':[],**case} for case in cases()]
    if '--smoke' in sys.argv:suite=suite[::100]
    observations=[];failures=[];counts={}
    (work/'movement_cases.json').write_text(json.dumps(suite,indent=2)+'\n')
    for case in suite:
        expected=run(retail,None,{},case,full_creation=True)
        actual=run(retail,native,symbols,case,full_creation=True)
        observations.append({'case':case['label'],'retail':expected,'native':actual})
        for name,count in actual['collision_calls'].items():counts[name]=counts.get(name,0)+count
        if actual!=expected:failures.append({'case':case['label'],'fields':[k for k in expected if expected[k]!=actual.get(k)]})
    output=work/'movement_observations.json';output.write_text(json.dumps(observations,indent=2)+'\n')
    report={'cases':len(suite),'failures':failures,'executed_helper_calls':counts,
        'cases_sha256':hashlib.sha256((work/'movement_cases.json').read_bytes()).hexdigest(),
        'observations_sha256':hashlib.sha256(output.read_bytes()).hexdigest(),
        'native_pe_sha256':hashlib.sha256(native.data).hexdigest(),'smoke':'--smoke' in sys.argv,
        'instruction_patches':0,'selection_evidence':False,
        'scope':'Complete movement, both native switch tables, fixed positions, clamping, history, four orbit records and complete animation tree operations.',
        'boundaries':['VM scripted; constructor retail executes in both runs',
                      'orbit callbacks scripted with canonical arguments and field mutations; all 42 graph bodies execute intact']}
    (work/'movement_differential.json').write_text(json.dumps(report,indent=2)+'\n')
    print(json.dumps(report,indent=2));assert not failures
