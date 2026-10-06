#!/usr/bin/env python3
"""Build a complete native candidate, then compare its diagnostic relocation.

The default is the project's ordinary MSVC compile. --ltcg selects /GL and
/LTCG for a separate control. Native modules have no synthetic entry function;
/INCLUDE retains the real public reader. Retail bytes are read after linking.
Diagnostic relocation is never accepted as a production fixed-layout proof.
"""
import argparse
import hashlib
import json
from pathlib import Path
import re
import subprocess
import sys

ROOT = Path(__file__).resolve().parents[4]
sys.path.insert(0, str(ROOT))
from matching2.tools.common.pe import PEImage
from matching2.tools.common.wine import DEFAULT_TOOLKIT
from matching2.tools.matching.equivalence import (
    MAP_SYMBOL, build_model, disassemble, relocate, normalize, find_differences,
)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('name', nargs='?', default='saved_candidate')
    parser.add_argument('--ltcg', action='store_true')
    parser.add_argument('--plain', action='store_true', help='explicit default mode')
    parser.add_argument('--reuse', action='store_true')
    args = parser.parse_args()
    source_root = Path(__file__).resolve().parent
    project = ROOT / 'matching2/msvc'
    work = ROOT / 'matching2/build/experiments/joystick_binding_reader_0044a190_2026_10_06/results' / args.name
    work.mkdir(parents=True, exist_ok=True)
    spec = json.loads((source_root / 'layout.json').read_text())
    spec['source_paths'] = [source_root / name for name in spec['sources']]
    flags = json.loads((project / 'regions.json').read_text())['flags']
    commands = []
    ordinary_run = subprocess.run

    def native_run(command, *positional, **options):
        command = list(command)
        if len(command) > 1 and str(command[1]).endswith('/cl.exe') and not args.ltcg:
            command = [value for value in command if value != '/GL']
        if len(command) > 1 and str(command[1]).endswith('/link.exe'):
            command = [value for value in command if not str(value).startswith('/ENTRY:')]
            if not args.ltcg:
                command = [value for value in command if value != '/LTCG']
            command.extend(['/DLL', '/NOENTRY', '/SAFESEH:NO', '/INCLUDE:' + spec['entry_symbol']])
        commands.append([str(value) for value in command])
        (work / 'commands.json').write_text(json.dumps(commands, indent=2) + '\n')
        return ordinary_run(command, *positional, **options)

    if args.reuse:
        native = (work / 'model.exe').read_bytes()
        moved = (work / 'moved.exe').read_bytes()
        link_map = (work / 'model.map').read_text()
    else:
        for path in [source_root / 'layout.json', *spec['source_paths'], *source_root.glob('*.hpp')]:
            (work / path.name).write_bytes(path.read_bytes())
        subprocess.run = native_run
        try:
            native, link_map, moved = build_model(spec, project, DEFAULT_TOOLKIT, flags, work)
        finally:
            subprocess.run = ordinary_run
    pe, moved_pe = PEImage(native), PEImage(moved)
    symbols = {name: int(value, 16) for name, value, _ in MAP_SYMBOL.findall(link_map)}
    owned = sorted(int(value, 16) for _, value, origin in MAP_SYMBOL.findall(link_map) if origin != '<absolute>')
    bindings = {symbols[name]: int(address, 0) for name, address in spec['bindings'].items() if name in symbols}
    bindings.update({int(item['address'], 0): int(item['address'], 0)
                     for item in spec['absolute_symbols'].values() if item['kind'] == 'code'})
    extents = {section: int(size, 16) for size, section in re.findall(
        r'^\s*\d+:[0-9a-f]+\s+([0-9a-f]+)H\s+(\S+)\s+CODE', link_map, re.M | re.I)}
    oracle = PEImage((ROOT / 'matching2/build/oracle/th10.exe').read_bytes())
    report = {'diagnostic_only': True, 'mode': 'ltcg' if args.ltcg else 'ordinary',
              'reference_bytes_used_for_build': False, 'functions': []}
    for symbol, section, address, required in spec['functions']:
        start, extent = symbols[symbol], extents[section]
        native_rows = disassemble(pe.read(start, extent), start, work, section + '_native')
        body = relocate(pe, moved_pe, native_rows, start, extent, 0, address, bindings, owned)
        original = oracle.read(address, required)
        (work / (section + '_body.bin')).write_bytes(body)
        (work / (section + '_retail_full.bin')).write_bytes(original)
        identity = lambda value, spelling: spelling
        retail_rows = normalize(disassemble(original, address, work, section + '_retail'),
                                address, required, required, identity)
        model_rows = normalize(disassemble(body, address, work, section + '_body_code'),
                               address, extent, extent, identity)
        swaps, hunks, _ = find_differences(retail_rows, model_rows, (), {}, True)
        report['functions'].append({
            'symbol': symbol, 'extent': extent, 'required': required, 'exact': body == original,
            'different_overlapping_bytes': sum(a != b for a, b in zip(body, original)),
            'normalized_full_body_sha256': hashlib.sha256(body).hexdigest(),
            'retail_full_body_sha256': hashlib.sha256(original).hexdigest(),
            'base_index_swaps': swaps, 'hunks': hunks,
        })
    (work / 'comparison.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps({key: value for key, value in report.items() if key != 'functions'} |
                     {'functions': [{key: value for key, value in row.items() if key != 'hunks'} |
                                    {'hunks': len(row['hunks'])} for row in report['functions']]}, indent=2))


if __name__ == '__main__':
    main()
