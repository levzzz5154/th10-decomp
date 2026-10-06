"""Prove conversion, power and lives under the complete genuine item graph.

The default gate selects three complete existing recoveries. --allocator
adds the complete existing allocator for an independent proof; production
keeps its player-initialization owner. Other graph bodies remain unselected.
"""
import hashlib,json,shutil,sys
from pathlib import Path
sys.path.insert(0,str(Path.cwd()))
from matching2.tools.common.pe import PEImage
from matching2.tools.common.wine import DEFAULT_TOOLKIT
from matching2.tools.matching.ltcg_cluster import load_cluster,build_cluster

def prepare():
    candidate=Path(__file__).resolve().parent
    base=Path('matching2/build/experiments/item_update_2026_10_06')
    gate='fixed_collection_allocator' if '--allocator' in sys.argv else 'fixed_collection'
    project=(base/(gate+'_project')).resolve()
    graph=project/'layout/ltcg/item_collection_runtime'
    graph.mkdir(parents=True,exist_ok=True);(graph/'types').mkdir(exist_ok=True)
    (project/'src/game').mkdir(parents=True,exist_ok=True)
    shutil.copytree('matching2/msvc/include',project/'include',dirs_exist_ok=True)
    names={'th10/game/item_spawn_0041bb00.hpp':'types/item_spawn.hpp',
        'th10/game/line_effect_sweeps_0041e260_0041f400.hpp':'types/line_sweeps.hpp',
        'th10/game/item_update_0041afd0.hpp':'types/update.hpp',
        'th10/render/animation_public_callers.hpp':'types/animation_public.hpp'}
    for original,local in names.items():
        text=(candidate/'include'/original).read_text()
        for old,new in names.items():text=text.replace(old,Path(new).name)
        (graph/local).write_text(text)
    spec=json.loads((candidate/'layout.json').read_text())
    comparison=json.loads((base/'saved_collection_graph/comparison.json').read_text())
    extents={f['symbol']:f['extent'] for f in comparison['functions']}
    sections={f[1]:'.text$f%08xF'%f[2] for f in spec['functions']}
    included=[]
    for cpp in candidate.glob('*.cpp'):
        if cpp.name=='runtime_graph.cpp':continue
        text=cpp.read_text()
        for old,new in names.items():text=text.replace(old,new)
        for old,new in sections.items():text=text.replace(old,new)
        target=graph/cpp.name;target.write_text(text)
        if cpp.name!='all.cpp':included.append(str(target.relative_to(project)))
    text=(candidate/'runtime_graph.cpp').read_text()
    for old,new in names.items():text=text.replace(old,'../../layout/ltcg/item_collection_runtime/'+new)
    for old,new in sections.items():text=text.replace(old,new)
    for cpp in candidate.glob('*.cpp'):
        if cpp.name!='runtime_graph.cpp':text=text.replace('"'+cpp.name+'"','"../../layout/ltcg/item_collection_runtime/'+cpp.name+'"')
    source='src/game/item_collection_genuine_0041afd0.cpp'
    (project/source).write_text(text)
    # The source contains the real graph. The required compiler driver only
    # includes it; it defines no compiler entry or synthetic caller function.
    (graph/'driver.cpp').write_text('#include "../../../'+source+'"\n')
    selected={'?ConvertItems@ItemSpawnManager_0041bb00@@QAEHXZ':('ConvertItems',165,'manager ESI; EAX zero return; RET'),
        '?AddPower@ItemRunState@@QAEHH@Z':('AddPower',166,'run counters EAX; amount on stack; RET4'),
        '?AddLives@ItemRunState@@QAEXH@Z':('AddLives',141,'run counters EAX; amount ECX; RET')}
    if '--allocator' in sys.argv:
        selected['?Allocate@AnimationPool@@QAEPAUEntity@@XZ']=('Allocate',161,'pool ESI; EAX result; RET')
    items=[];functions=[];anchors=[];context=None
    for symbol,section,address,required in spec['functions']:
        item={'name':selected[symbol][0] if symbol in selected else 'function_%08x'%address,
              'symbol':symbol,'section':sections[section],'address':hex(address),'size':extents[symbol]}
        items.append(item)
        if symbol in selected:
            name,size,abi=selected[symbol];assert size==item['size'];functions.append({**item,'actual_abi':abi})
        elif symbol=='_ItemManager_UpdateItems@4':
            context={k:v for k,v in item.items() if k!='name'};context['description']='Complete genuine item-update callback, unselected; native %s bytes versus 2320 retail bytes.'%item['size']
        else:anchors.append(item)
    gaps=[];cursor=0x401000
    for item in sorted(items,key=lambda x:int(x['address'],0)):
        address=int(item['address'],0);assert address>=cursor,(item,cursor)
        if address>cursor:gaps.append({'section':'.text$f%08xA'%address,'address':hex(cursor),'size':address-cursor})
        cursor=address+item['size']
    headers=['include/th10/game/entity.hpp','include/th10/types.hpp','include/th10/math/timer.hpp',
        'include/th10/render/animation_object_0043e5a0.hpp','include/th10/render/animation_byte_interpolator.hpp',
        'include/th10/game/entity_script_start.hpp','include/th10/platform/sound_queue.hpp']
    headers.extend(str(p.relative_to(project)) for p in sorted((graph/'types').glob('*.hpp')))
    layout={'schema_version':1,'name':'item_collection_genuine_0041afd0','source':source,
        'driver':'layout/ltcg/item_collection_runtime/driver.cpp','additional_sources':['layout/ltcg/item_collection_runtime/all.cpp'],
        'included_sources':included,'headers':headers,'image_base':'0x00400000',
        'description':'Existing conversion/power/life recoveries under the complete genuine item-update, line, animation and sound graph. No synthetic caller or compiler entry.',
        'functions':functions,'anchors':anchors,'context':context,'gaps':gaps,'constants':[],
        'constant_aliases':[],'absolute_symbols':[{'symbol':s,**v,'kind':('relative_code' if v['kind']=='code' else 'metadata' if s=='__fltused' else v['kind'])} for s,v in spec['absolute_symbols'].items()],
        'anchor_roots':spec['roots'][:-1]}
    path='layout/ltcg/item_collection_genuine_0041afd0.json';(project/path).write_text(json.dumps(layout,indent=2)+'\n')
    regions=[{'name':'semantic_'+f['name'],'source':source,'symbol':f['symbol'],'address':f['address'],'size':f['size'],'kind':'semantic'} for f in functions]
    (project/'regions.json').write_text(json.dumps({'regions':regions},indent=2)+'\n')
    return project,path,regions

if __name__=='__main__':
    project,path,regions=prepare();spec=load_cluster(project,path,regions)
    flags=json.loads(Path('matching2/msvc/regions.json').read_text())['flags'];output=project.parent/('fixed_collection_allocator_gate' if '--allocator' in sys.argv else 'fixed_collection_gate')
    result=build_cluster(spec,DEFAULT_TOOLKIT,output,flags);report=result['native_build'];oracle=PEImage(Path('matching2/build/oracle/th10.exe').read_bytes())
    for f in report['functions']:assert f['sha256']==hashlib.sha256(oracle.read(int(f['address'],0),f['size'])).hexdigest(),f
    proof={'complete_raw_fixed_address_match':True,'functions':[{'address':f['address'],'size':f['size'],'sha256':f['sha256']} for f in report['functions']],
        'normal_report_sha256':hashlib.sha256((output/'report.json').read_bytes()).hexdigest(),
        'instruction_bytes_changed':report['instruction_bytes_changed'],'masked_bytes':report['masked_bytes'],'reference_bytes_used_for_build':report['reference_bytes_used_for_build']}
    (output/'oracle_proof.json').write_text(json.dumps(proof,indent=2)+'\n');print(json.dumps(proof,indent=2))
