"""Full manager walks, including snapshot-before-callback and actual player owner callers."""
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
    for states,mode,alias in itertools.product(list(itertools.product([0,1,2],repeat=3)),
            [0,1,-1,0x80000000],[False,True]):
        yield {'label':f'evaluate_{states}_{mode}_{alias}','sequence':['bulletevaluate'],
               'bullet_records':[{'state':state,'evaluate_result':[-7,13,29][i]} for i,state in enumerate(states)],
               'evaluation_mode':mode,'alias_evaluation_point':alias}
    for states,mode,mutate in itertools.product(list(itertools.product([0,1,2],repeat=3)),
            [0,1,-1,0x80000000],[False,True]):
        yield {'label':f'reset_{states}_{mode}_{mutate}','sequence':['bulletreset'],
               'bullet_records':[{'state':state} for state in states],
               'cleanup_mode':mode,'mutate_bullet_next':mutate}
    for records in [[],[{'state':0}],[{'state':1}],[{'state':-1}],[{'state':0,'evaluate_result':2147483647}]]:
        for operation in ['bulletevaluate','bulletreset']:
            yield {'label':f'length_{records}_{operation}','sequence':[operation],'bullet_records':records}
    for slot,action in itertools.product(range(3),['change_next','retire_self','change_point','change_next_state']):
        records=[{'state':0} for _ in range(3)]
        records[slot][action]={'change_point':[100.,-27.,5.],'change_next_state':1}.get(action,True)
        yield {'label':f'callback_{slot}_{action}','sequence':['bulletevaluate','bulletevaluate'],
               'bullet_records':records}
    for mode,following in itertools.product([0,1,-1],[0,1,2]):
        yield {'label':f'cleanup_mutates_following_{mode}_{following}','sequence':['bulletreset'],
               'cleanup_mode':mode,'retire_next_state':following,'bullet_records':[{'state':0} for _ in range(3)]}
    for bits,alias,mode in itertools.product([0,0x80000000,0x7f800000,0xff800000,0x7fc12345,0x7fa12345,0xffa12345],
            [False,True],[0,-1]):
        yield {'label':f'bit_copy_{bits:x}_{alias}_{mode}','sequence':['bulletevaluate'],
               'evaluation_point_bits':[bits,bits^0x80000000,0x80000000],
               'evaluation_radius_bits':bits,'alias_evaluation_point':alias,'evaluation_mode':mode}
    for phase,frame,mutate in itertools.product([0,2,3,4,5],[0,15,29,30,60],[False,True]):
        yield {'label':f'owner_{phase}_{frame}_{mutate}','sequence':['stateupdate','stateupdate'],
               'player_phase':phase,'player_frame':frame,'mutate_bullet_next':mutate,
               'bullet_records':[{'state':0,'evaluate_result':17,'change_next':mutate},
                                {'state':1},{'state':2,'evaluate_result':-8}]}
    yield {'label':'walk_evaluate_cleanup_evaluate','sequence':['bulletevaluate','bulletreset','bulletevaluate','bulletreset']}

if __name__=='__main__':
    work=Path('matching2/build/experiments/player_bullet_state_2026_10_06')/(sys.argv[1] if len(sys.argv)>1 else 'genuine_graph')
    retail=PEImage(Path('matching2/build/oracle/th10.exe').read_bytes())
    native=PEImage((work/'model.exe').read_bytes())
    symbols={name:int(address,16) for name,address,_ in MAP_SYMBOL.findall((work/'model.map').read_text())}
    suite=[{'player_state':True,'collision_records':[],**case} for case in cases()]
    if '--smoke' in sys.argv:suite=suite[::30]
    (work/'bullet_cases.json').write_text(json.dumps(suite,indent=2)+'\n')
    observations=[];failures=[];counts={}
    for case in suite:
        expected=run(retail,None,{},case,full_creation=True)
        actual=run(retail,native,symbols,case,full_creation=True)
        observations.append({'case':case['label'],'retail':expected,'native':actual})
        for name,count in actual['collision_calls'].items():counts[name]=counts.get(name,0)+count
        if actual!=expected:failures.append({'case':case['label'],'fields':[k for k in expected if expected[k]!=actual.get(k)]})
    output=work/'bullet_observations.json';output.write_text(json.dumps(observations,indent=2)+'\n')
    report={'cases':len(suite),'failures':failures,'executed_helper_calls':counts,
        'cases_sha256':hashlib.sha256((work/'bullet_cases.json').read_bytes()).hexdigest(),
        'observations_sha256':hashlib.sha256(output.read_bytes()).hexdigest(),
        'native_pe_sha256':hashlib.sha256(native.data).hexdigest(),'smoke':'--smoke' in sys.argv,
        'instruction_patches':0,'selection_evidence':False,
        'scope':'Both full manager walks and real player-state callers; list snapshots, virtual callbacks, eligibility, totals, modes, bitwise vector copies, preserved registers, RET8/RET0 and x87 balance.',
        'boundaries':['Virtual record evaluation and retirement scripted; the complete manager bodies execute intact',
                      'Other explicit player/VM/allocation/callback boundaries retain the shared fixture contract']}
    (work/'bullet_differential.json').write_text(json.dumps(report,indent=2)+'\n')
    print(json.dumps(report,indent=2));assert not failures
