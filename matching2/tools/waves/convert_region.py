#!/usr/bin/env python3
"""Point assembly regions at a recovered C++ source in the manifest.

Usage:
    convert_region.py --source src/game/x.cpp [--cluster layout/ltcg/x.json]
        ADDRESS=NAME=SYMBOL [ADDRESS=NAME=SYMBOL ...]

Each region keeps its old record under ``previous_record`` and its old symbol
stays in the symbol table as an alias for the assembly callers that remain.
Sources that no longer own a region leave ``translation_units``.
"""
import argparse
import fcntl
import json
import os
from pathlib import Path

parser = argparse.ArgumentParser()
parser.add_argument('--project', default='matching2/msvc')
parser.add_argument('--source')
parser.add_argument('--revert', action='store_true',
                    help='restore each ADDRESS to its previous_record')
parser.add_argument('--cluster')
parser.add_argument('regions', nargs='+')
args = parser.parse_args()
if not args.revert and not args.source:
    parser.error('--source is required')

import sys as _project_sys
from pathlib import Path as _ProjectPath
_project_sys.path.insert(0, str(_ProjectPath(__file__).resolve().parents[3]))
from matching2.tools.common.project_paths import project_support
path = project_support(Path(args.project), 'regions.json')
# Other tools and agents update the manifest concurrently; hold the shared lock.
lock = open(path.with_suffix('.json.lock'), 'w')
fcntl.flock(lock, fcntl.LOCK_EX)
manifest = json.loads(path.read_text())
if args.revert:
    targets = {int(item, 16) for item in args.regions}
    for index, region in enumerate(manifest['regions']):
        if int(region['address'], 16) in targets:
            manifest['symbols'].pop(region['symbol'], None)
            manifest['regions'][index] = region['previous_record']
            manifest['symbols'][region['previous_record']['symbol']] = region['previous_record']['address']
    owners = {region['source'] for region in manifest['regions']}
    units = [u for u in manifest['translation_units'] if u in owners]
    units += sorted(owners - set(units))
    manifest['translation_units'] = units
    temporary = path.with_suffix('.json.tmp')
    temporary.write_text(json.dumps(manifest, indent=2) + '\n')
    os.replace(temporary, path)
    raise SystemExit(0)
wanted = {}
for item in args.regions:
    address, name, symbol = item.split('=', 2)
    wanted[int(address, 16)] = (name, symbol)
old_sources = set()
for region in manifest['regions']:
    address = int(region['address'], 16)
    if address not in wanted:
        continue
    name, symbol = wanted.pop(address)
    previous = dict(region)
    old_sources.add(region['source'])
    region['previous_record'] = previous
    region.pop('previous_records', None)
    region.update(name=name, source=args.source, symbol=symbol, kind='semantic')
    manifest['symbols'][symbol] = region['address']
if wanted:
    raise SystemExit('no region at ' + ', '.join(hex(a) for a in wanted))
owners = {region['source'] for region in manifest['regions']}
units = [u for u in manifest['translation_units'] if u in owners or u not in old_sources]
if args.source not in units:
    units.append(args.source)
manifest['translation_units'] = units
if args.cluster and args.cluster not in manifest['ltcg_clusters']:
    manifest['ltcg_clusters'].append(args.cluster)
temporary = path.with_suffix('.json.tmp')
temporary.write_text(json.dumps(manifest, indent=2) + '\n')
os.replace(temporary, path)
