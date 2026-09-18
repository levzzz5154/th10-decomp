#!/usr/bin/env python3
"""Promote one region's artifacts from an agent's scratch copy into the tree.

The wave agents work in `/tmp/<id>/msvc` copies. Integrating their result by hand
is four steps that are easy to get wrong: copy the region's source, copy the
cluster layout and its driver, rewrite the region's manifest record, and never
copy anything else - a scratch copy is stale by the time it is integrated, so a
bulk `cp -a` or `diff -r` would revert whatever landed in the meantime.

Usage:
    python3 promote_scratch.py --scratch /tmp/<id>/msvc --address 0x405ED0
    python3 promote_scratch.py --scratch /tmp/<id>/msvc --address 0x405ED0 --apply

Without --apply it prints the plan and changes nothing. A cluster layout that the
scratch lists in its `ltcg_clusters` is copied and registered, unless the same
layout path is already registered, in which case the scratch's copy overwrites
the maintained one (the merge pattern the wave agents use for a second function in
an existing cluster).
"""
from __future__ import annotations

import argparse
import fcntl
import json
import shutil
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[3]
MAINTAINED = ROOT / 'matching2/msvc'


def load(path):
    return json.loads(path.read_text())


def merge_layout(maintained_layout, scratch_layout):
    """Extend the maintained layout with the scratch's functions and bindings.

    A scratch copy is a snapshot, so overwriting the maintained layout with it
    silently reverts every function another agent landed into the same span.
    Functions are unioned by address, the binding lists by content, the source
    list is recomputed from the union, and the gaps are rebuilt as the complement
    of every declared extent so a new function keeps its own gap. A gap's section
    is named after the function it follows with a 'z' suffix, which sorts after
    that function and before the next one.
    """
    merged = json.loads(json.dumps(maintained_layout))
    have = {function['address'].upper() for function in merged['functions']}
    for function in scratch_layout.get('functions') or []:
        if function['address'].upper() not in have:
            merged['functions'].append(function)
            have.add(function['address'].upper())
    for key in ('absolute_symbols', 'constants', 'constant_aliases', 'roots'):
        seen = {json.dumps(item, sort_keys=True) for item in merged.get(key) or []}
        for item in scratch_layout.get(key) or []:
            marker = json.dumps(item, sort_keys=True)
            if marker not in seen:
                merged.setdefault(key, []).append(item)
                seen.add(marker)
    sources = {f['source'] for f in merged['functions'] if f.get('source')}
    merged['additional_sources'] = sorted(sources - {merged['source']})
    # Only split the gaps a *new* function lands inside: rebuilding every gap
    # coalesces the leading ones and changes section names, which changes the
    # link order and shifts the whole span.
    gaps = merged['gaps']
    declared = {f['address'].upper() for f in maintained_layout['functions']}
    for function in scratch_layout.get('functions') or []:
        if function['address'].upper() in declared:
            continue  # already an extent in the maintained layout
        address = int(function['address'], 16)
        for index, gap in enumerate(gaps):
            start = int(gap['address'], 16)
            end = start + gap['size']
            if start < address < end:
                size = function['size']
                if address + size > end:
                    raise SystemExit(f'{function["address"]} does not fit in {gap["section"]}')
                tail = {'section': function['section'] + 'z',
                        'address': hex(address + size), 'size': end - (address + size)}
                gaps[index] = {'section': gap['section'], 'address': gap['address'],
                               'size': address - start}
                gaps.insert(index + 1, tail)
                break
        else:
            raise SystemExit(f'{function["address"]} falls inside no gap; declare it in the layout')
    items = sorted([(int(f['address'], 16), f['size']) for f in merged['functions']] +
                   [(int(g['address'], 16), g['size']) for g in gaps] +
                   [(int(merged['context']['address'], 16), merged['context']['size'])])
    clashes = [(a, e) for (a, s), (e, _) in zip(items, items[1:]) if a + s > e]
    if clashes:
        raise SystemExit(f'merged layout overlaps at {clashes[:3]}')
    return merged


def record_of(manifest, address):
    for region in manifest['regions']:
        if int(region['address'], 0) == address:
            return region
    raise SystemExit(f'no region at {address:#x}')


def main():
    parser = argparse.ArgumentParser(description=__doc__,
                                     formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('--scratch', type=Path, required=True)
    parser.add_argument('--address', type=lambda v: int(v, 0), required=True)
    parser.add_argument('--apply', action='store_true')
    args = parser.parse_args()

    scratch = args.scratch.resolve()
    if not (scratch / 'regions.json').exists():
        raise SystemExit(f'{scratch} is not a project copy (no regions.json)')

    scratch_manifest = load(scratch / 'regions.json')
    maintained_path = MAINTAINED / 'regions.json'
    maintained = load(maintained_path)

    source = record_of(scratch_manifest, args.address)
    current = record_of(maintained, args.address)
    print(f'region   {args.address:#010x}  {current["name"]} ({current["kind"]})')
    print(f'scratch  {source["name"]} ({source["kind"]}) size {source["size"]}'
          f' symbol {source.get("symbol")}')

    if source['kind'] != 'semantic':
        raise SystemExit('scratch has not flipped this region to semantic; nothing to promote')

    files = [MAINTAINED / source['source']]
    scratch_source = scratch / source['source']
    if not scratch_source.exists():
        raise SystemExit(f'scratch has no {source["source"]}')

    layouts = []
    maintained_clusters = set(maintained.get('ltcg_clusters') or [])
    for rel in scratch_manifest.get('ltcg_clusters') or []:
        if rel not in maintained_clusters:
            layouts.append(rel)
    # A layout already registered may still have grown a function (merge pattern).
    for candidate in sorted((scratch / 'layout/ltcg').glob('*.json')):
        rel = str(candidate.relative_to(scratch))
        if rel in maintained_clusters:
            layout = load(candidate)
            for function in layout.get('functions') or []:
                if int(function['address'], 0) == args.address:
                    layouts.append(rel)
                    break
    merges = {}
    for rel in sorted(set(layouts)):
        if rel in maintained_clusters:
            print(f'layout   {rel} (already registered - merging into it, siblings kept)')
            merges[rel] = True
        else:
            print(f'layout   {rel} (new - will be registered)')
            files.append(MAINTAINED / rel)
        layout = load(scratch / rel)
        driver = layout.get('driver')
        if driver:
            files.append(MAINTAINED / driver)

    for path in files:
        print(f'copy     {path.relative_to(MAINTAINED)}')

    if not args.apply:
        print('\n(dry run; pass --apply)')
        return 0

    for path in files:
        shutil.copy2(scratch / path.relative_to(MAINTAINED), path)
    # Take the same exclusive lock register_cluster.py uses, and re-read the
    # manifest inside it: promoting from a snapshot taken before the lock can drop
    # a record another agent registered in the meantime.
    with open(MAINTAINED / 'regions.json.lock', 'w') as lock:
        fcntl.flock(lock, fcntl.LOCK_EX)
        # Merge inside the lock, against the current maintained layout, so a
        # sibling landing into the same span between our read and our write is
        # carried over instead of reverted.
        for rel in merges:
            merged = merge_layout(load(MAINTAINED / rel), load(scratch / rel))
            (MAINTAINED / rel).write_text(json.dumps(merged, indent=2) + '\n')
            print(f'merged   {rel}: {len(merged["functions"])} functions, {len(merged["gaps"])} gaps')
        maintained = load(maintained_path)
        current = record_of(maintained, args.address)
        current.clear()
        current.update(source)
        maintained['translation_units'] = sorted({r['source'] for r in maintained['regions']})
        maintained_path.write_text(json.dumps(maintained, indent=2) + '\n')
    for rel in sorted(set(layouts)):
        if rel in maintained_clusters:
            continue
        result = subprocess.run([sys.executable, str(ROOT / 'matching2/tools/waves/register_cluster.py'),
                                 '--project', str(MAINTAINED), '--layout', rel, '--apply'],
                                capture_output=True, text=True, cwd=MAINTAINED, timeout=120)
        print(result.stdout.strip() or result.stderr.strip())
    print(f'promoted {args.address:#010x}')
    return 0


if __name__ == '__main__':
    sys.exit(main())
