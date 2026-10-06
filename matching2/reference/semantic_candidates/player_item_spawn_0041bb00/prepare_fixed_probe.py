"""Prepare an isolated project for the unchanged normal fixed-address probe."""
import json
from pathlib import Path
import shutil
import sys

root = Path(__file__).resolve().parent
work = Path('matching2/build/experiments/player_item_spawn_2026_10_06')
checkpoint = work / (sys.argv[1] if len(sys.argv) > 1 else 'genuine_graph')
project = work / 'collision_fixed_gate/project'
project.mkdir(parents=True, exist_ok=True)
graph = project / 'graph'
graph.mkdir(exist_ok=True)
headers = ['th10/game/entity.hpp', 'th10/types.hpp', 'th10/game/entity_script_start.hpp',
           'th10/render/animation_public_callers.hpp', 'th10/math/timer.hpp']
for name in headers:
    source = root / 'include' / name
    if not source.exists():
        source = Path('matching2/msvc/include') / name
    target = project / 'include' / name
    target.parent.mkdir(parents=True, exist_ok=True)
    shutil.copy2(source, target)
layout = json.loads((root / 'layout.json').read_text())
comparison = json.loads((checkpoint / 'comparison.json').read_text())['functions']
by_symbol = {row['symbol']: row for row in comparison}
functions, renames = [], {}
for symbol, section, address, size in layout['functions']:
    fixed_section = f'.text$f{address:08x}F'
    renames[section] = fixed_section
    functions.append({'name': f'function_{address:08x}', 'symbol': symbol,
                      'section': fixed_section, 'address': hex(address),
                      'size': by_symbol[symbol]['extent']})
for source in [*root.glob('*.cpp'), *root.glob('*.hpp')]:
    text = source.read_text()
    for old, new in renames.items():
        text = text.replace('"' + old + '"', '"' + new + '"')
    (graph / source.name).write_text(text)
activation = next(row for row in functions if 'Activate@PlayerCollisionRecord' in row['symbol'])
check = next(row for row in functions if 'Check@PlayerCollisionEngine' in row['symbol'])
check['actual_abi'] = 'private EAX engine / EBX point / three stack words / RET12 derived through full real owner and item-spawn graph'
activation['actual_abi'] = 'private ESI receiver; RET0 derived through complete collision check and player state caller'
owner = next(row for row in functions if row['symbol'] == '_PlayerState_Update_00425730@4')
context = {key: value for key, value in owner.items() if key != 'name'}
context['description'] = 'Complete ordinary C++ player state owner; unmatched unselected context; no synthetic caller.'
anchors = [row for row in functions if row not in [activation, check, owner]]
gaps, cursor = [], 0x401000
for row in sorted(functions, key=lambda item: int(item['address'], 0)):
    address = int(row['address'], 0)
    assert address >= cursor
    if address > cursor:
        gaps.append({'section': row['section'][:-1] + 'A', 'address': hex(cursor),
                     'size': address - cursor})
    cursor = address + row['size']
absolute = [{'symbol': symbol, 'address': item['address'],
             'kind': 'metadata' if symbol == '__fltused' else
                     'relative_code' if item['kind'] == 'code' else 'data'}
            for symbol, item in layout['absolute_symbols'].items()]
manifest = {'schema_version': 1, 'name': 'player_state_collision_genuine_00408030_00408100',
            'source': 'graph/collision.cpp', 'driver': 'graph/runtime.cpp',
            'additional_sources': ['graph/creation.cpp'],
            'included_sources': ['graph/' + source.name for source in root.glob('*.cpp')
                                 if source.name not in ['runtime.cpp', 'creation.cpp', 'collision_activate.cpp', 'collision_check.cpp']],
            'headers': ['graph/' + source.name for source in root.glob('*.hpp')] +
                       ['include/' + name for name in headers],
            'image_base': '0x400000', 'functions': [activation,check], 'context': context,
            'anchors': anchors, 'anchor_roots': [symbol for symbol in layout['roots'] if symbol != owner['symbol']],
            'roots': [], 'gaps': gaps, 'constants': [], 'absolute_symbols': absolute,
            'description': 'Complete real 36-function player-state graph; isolated raw-equality probe only; production untouched.'}
(project / 'cluster.json').write_text(json.dumps(manifest, indent=2) + '\n')
config = json.loads(Path('matching2/msvc/regions.json').read_text())
config['regions'] = [{'name': 'probe_collision_activation', 'source': 'graph/collision.cpp',
                      'symbol': activation['symbol'], 'address': '0x408030', 'size': 199,
                      'kind': 'semantic', 'section': activation['section']},
                     {'name':'probe_collision_check','source':'graph/collision.cpp',
                      'symbol':check['symbol'],'address':'0x408100','size':260,
                      'kind':'semantic','section':check['section']}]
config['dos_regions'] = []
config['translation_units'] = ['graph/collision.cpp', 'graph/creation.cpp']
config['ltcg_clusters'] = ['cluster.json']
config.pop('source_compilers', None)
(project / 'regions.json').write_text(json.dumps(config, indent=2) + '\n')
# The selected source owns both complete functions in their original TU order.
(graph/'collision.cpp').write_text((graph/'collision_activate.cpp').read_text()+'\n'+(graph/'collision_check.cpp').read_text())
path=graph/'runtime.cpp';text=path.read_text().replace('#include "collision_activate.cpp"\n#include "collision_check.cpp"','#include "collision.cpp"');path.write_text(text)
(graph/'collision_activate.cpp').unlink();(graph/'collision_check.cpp').unlink()
shutil.copy2('matching2/msvc/pe_layout.json', project / 'pe_layout.json')
print(project)
