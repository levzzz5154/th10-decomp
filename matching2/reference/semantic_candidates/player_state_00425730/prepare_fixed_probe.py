"""Prepare an isolated project for the unchanged normal fixed-address probe."""
import json
from pathlib import Path
import shutil
import sys

root = Path(__file__).resolve().parent
work = Path('matching2/build/experiments/player_state_2026_10_06')
checkpoint = work / (sys.argv[1] if len(sys.argv) > 1 else 'corrected_graph')
project = work / 'sequence_fixed_gate/project'
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
update = next(row for row in functions if 'UpdateSequence@' in row['symbol'])
update['actual_abi'] = 'private EAX receiver; RET0 derived through the complete real player state caller'
owner = next(row for row in functions if row['symbol'] == '_PlayerState_Update_00425730@4')
context = {key: value for key, value in owner.items() if key != 'name'}
context['description'] = 'Complete ordinary C++ player state owner; unmatched unselected context; no synthetic caller.'
anchors = [row for row in functions if row not in [update, owner]]
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
manifest = {'schema_version': 1, 'name': 'player_state_sequence_genuine_004281d0',
            'source': 'graph/schedule_update.cpp', 'driver': 'graph/runtime.cpp',
            'additional_sources': ['graph/creation.cpp'],
            'included_sources': ['graph/' + source.name for source in root.glob('*.cpp')
                                 if source.name not in ['runtime.cpp', 'creation.cpp', 'schedule_update.cpp']],
            'headers': ['graph/' + source.name for source in root.glob('*.hpp')] +
                       ['include/' + name for name in headers],
            'image_base': '0x400000', 'functions': [update], 'context': context,
            'anchors': anchors, 'anchor_roots': [symbol for symbol in layout['roots'] if symbol != owner['symbol']],
            'roots': [], 'gaps': gaps, 'constants': [], 'absolute_symbols': absolute,
            'description': 'Complete real 28-function player-state graph; isolated raw-equality probe only; production untouched.'}
(project / 'cluster.json').write_text(json.dumps(manifest, indent=2) + '\n')
config = json.loads(Path('matching2/msvc/regions.json').read_text())
config['regions'] = [{'name': 'probe_sequence_update', 'source': 'graph/schedule_update.cpp',
                      'symbol': update['symbol'], 'address': '0x4281d0', 'size': 174,
                      'kind': 'semantic', 'section': update['section']}]
config['dos_regions'] = []
config['translation_units'] = ['graph/schedule_update.cpp', 'graph/creation.cpp']
config['ltcg_clusters'] = ['cluster.json']
config.pop('source_compilers', None)
(project / 'regions.json').write_text(json.dumps(config, indent=2) + '\n')
shutil.copy2('matching2/msvc/pe_layout.json', project / 'pe_layout.json')
print(project)
