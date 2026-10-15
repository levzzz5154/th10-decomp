#!/usr/bin/env python3
"""Register a hand-written native-LTCG cluster in regions.json.

Reads a small spec (JSON) naming the recovered source, its functions
(address, decorated symbol, section), any anchors, the context and the
absolute symbols, then writes the layout with computed gaps and converts
the owned regions from assembly to semantic records.

    adopt_cluster.py spec.json
"""
import json, sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2] / 'msvc'
TEXT_START, RDATA_START = 0x401000, 0x470000
XDATA_BASE = 0x466000


import sys as _project_sys
from pathlib import Path as _ProjectPath
_project_sys.path.insert(0, str(_ProjectPath(__file__).resolve().parents[3]))
from matching2.tools.common.project_paths import project_support
def main():
    spec = json.loads(Path(sys.argv[1]).read_text())
    text = (project_support(ROOT, 'regions.json')).read_text()
    manifest = json.loads(text)
    by_address = {int(r['address'], 16): r for r in manifest['regions']}
    old_sources = set()
    for function in spec['functions']:
        region = by_address[int(function['address'], 16)]
        function.setdefault('size', region['size'])
        if region['kind'] != 'semantic' or region['symbol'] != function['symbol']:
            previous = dict(region)
            old_sources.add(region['source'])
            region.clear()
            region.update({'name': 'semantic_' + function['name'] + '_' + function['address'][2:].lower(),
                           'source': spec['source'], 'symbol': function['symbol'],
                           'address': previous['address'], 'size': previous['size'], 'kind': 'semantic',
                           'owner': previous.get('owner'), 'previous_record': previous})
    placed = sorted(spec['functions'] + spec.get('anchors', []) + [spec['context']],
                    key=lambda item: int(item['address'], 16))
    gaps, cursor, section = [], TEXT_START, '.text$00before'
    for item in placed:
        address = int(item['address'], 16)
        if address > cursor:
            gaps.append({'section': section, 'address': cursor, 'size': address - cursor})
        cursor, section = address + item['size'], item['section'] + 'z'
    constants = spec.get('constants', [])
    if constants:
        # The trailing .text gap makes .rdata start at RDATA_START; one .rdata
        # gap then places the single compiler literal at its retail address.
        if len(constants) != 1:
            raise SystemExit('only one compiler constant is supported')
        gaps.append({'section': section, 'address': cursor, 'size': RDATA_START - cursor})
        gaps.append({'section': '.rdata', 'address': RDATA_START,
                     'size': int(constants[0]['address'], 16) - RDATA_START})
    if spec.get('native_data'):
        # Exception tables live in .xdata$x; one .rdata gap places them.
        table = min(int(item['address'], 16) for item in spec['native_data'])
        gaps.append({'section': '.rdata$0before', 'address': XDATA_BASE, 'size': table - XDATA_BASE})
    layout = {'schema_version': 1, 'name': spec['name'], 'source': spec['source'], 'driver': spec['driver'],
              'headers': spec.get('headers', []), 'image_base': '0x00400000',
              'description': spec['description'], 'functions': spec['functions'],
              'context': spec['context'], 'gaps': gaps, 'constants': spec.get('constants', []),
              'absolute_symbols': spec.get('absolute_symbols', [])}
    for key in ('exceptions', 'native_data', 'anchors', 'included_sources', 'roots', 'additional_sources', 'data_aliases', 'constant_aliases'):
        if spec.get(key):
            layout[key] = spec[key]
    layout_name = 'layout/ltcg/' + spec['name'] + '.json'
    (ROOT / layout_name).write_text(json.dumps(layout, indent=2) + '\n')
    units = manifest['translation_units']
    still_used = {r['source'] for r in manifest['regions']}
    for source in old_sources - still_used:
        units.remove(source)
    if spec['source'] not in units:
        units.append(spec['source'])
    if layout_name not in manifest['ltcg_clusters']:
        manifest['ltcg_clusters'].append(layout_name)
    (project_support(ROOT, 'regions.json')).write_text(json.dumps(manifest, indent=2) + '\n')
    print('wrote', layout_name, 'dropped units', sorted(old_sources - still_used))


if __name__ == '__main__':
    main()
