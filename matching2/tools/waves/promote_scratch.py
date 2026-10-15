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
import os
import shutil
import sys
import tempfile
from pathlib import Path

ROOT = Path(__file__).resolve().parents[3]
MAINTAINED = ROOT / 'matching2/msvc'
sys.path.insert(0, str(ROOT))

from matching2.tools.waves.integration_gates import (
    commit_gate,
    full_hash_gate,
    manifest_gate,
    probe_cluster_gate,
    touched_clusters,
    write_gate_report,
)
from matching2.tools.waves.register_cluster import update as register_cluster


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


from matching2.tools.common.project_paths import project_support
def main():
    parser = argparse.ArgumentParser(description=__doc__,
                                     formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('--scratch', type=Path, required=True)
    parser.add_argument('--address', type=lambda v: int(v, 0), required=True)
    parser.add_argument('--apply', action='store_true')
    parser.add_argument('--gate-report', type=Path,
                        help='machine-readable gate record (default: build/waves by address)')
    parser.add_argument('--full-report', type=Path,
                        help='existing whole-image port-report.json to inspect; never runs a build')
    parser.add_argument('--integration-commit',
                        help='manual commit object id to record after the full hash gate')
    args = parser.parse_args()

    scratch = args.scratch.resolve()
    if not (project_support(scratch, 'regions.json')).exists():
        raise SystemExit(f'{scratch} is not a project copy (no regions.json)')

    scratch_manifest = load(project_support(scratch, 'regions.json'))
    maintained_path = project_support(MAINTAINED, 'regions.json')
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
    for candidate in sorted((project_support(scratch, 'layout/ltcg')).glob('*.json')):
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

    gate_path = args.gate_report or (
        ROOT / f'matching2/build/waves/promotion-gates-{args.address:08x}.json'
    )
    if not args.apply:
        full_hash = full_hash_gate(MAINTAINED, args.full_report)
        report = {
            'schema': 'th10-integration-gates/v1',
            'batch': {'apply_requested': False, 'applied': False,
                      'address': f'0x{args.address:08X}', 'status': 'dry_run'},
            'gates': {
                'manifest': {'passed': False, 'status': 'not_run'},
                'touched_cluster_probes': {'passed': False, 'status': 'not_run'},
                'full_hash': full_hash,
            },
        }
        report['integration_commit'] = commit_gate(args.integration_commit, full_hash)
        report['release_ready'] = False
        write_gate_report(gate_path, report)
        print(f'\n(dry run; pass --apply; gate report: {gate_path})')
        return 0

    # Hold the registration lock from the current-project snapshot through the
    # final atomic manifest replacement.  The slow probes run against a staged
    # copy, but no concurrent promotion can invalidate their manifest input.
    manifest_result = {'passed': False, 'status': 'not_run'}
    probes = {'passed': False, 'status': 'not_run', 'cluster_count': 0, 'clusters': []}
    applied = False
    problem = ''
    with open(project_support(MAINTAINED, 'regions.json').with_name('regions.json.lock'), 'w') as lock:
        fcntl.flock(lock, fcntl.LOCK_EX)
        current_manifest = load(maintained_path)
        current_clusters = set(current_manifest.get('ltcg_clusters') or [])
        with tempfile.TemporaryDirectory(prefix='th10-promote-') as directory:
            staged = Path(directory) / 'msvc'
            shutil.copytree(MAINTAINED, staged)

            # Copy only the explicitly planned artifacts into the staged tree.
            artifact_rels = {str(path.relative_to(MAINTAINED)) for path in files}
            artifact_rels.update(layouts)
            for rel in sorted(artifact_rels):
                target = staged / rel
                target.parent.mkdir(parents=True, exist_ok=True)
                shutil.copy2(scratch / rel, target)

            # Merge registered layouts against the lock-protected current copy,
            # never against the agent's stale snapshot.
            for rel in sorted(set(layouts)):
                if rel in current_clusters:
                    merged = merge_layout(load(MAINTAINED / rel), load(scratch / rel))
                    (staged / rel).write_text(json.dumps(merged, indent=2) + '\n')

            staged_manifest_path = project_support(staged, 'regions.json')
            staged_manifest = load(staged_manifest_path)
            staged_record = record_of(staged_manifest, args.address)
            staged_record.clear()
            staged_record.update(source)
            staged_manifest['translation_units'] = sorted(
                {region['source'] for region in staged_manifest['regions']}
            )
            staged_manifest_path.write_text(json.dumps(staged_manifest, indent=2) + '\n')

            # New layouts use the same registration implementation as the
            # maintained workflow, but only inside the disposable candidate.
            for rel in sorted(set(layouts)):
                if rel in current_clusters:
                    continue
                registration_problem, _, _ = register_cluster(staged_manifest_path, rel, True)
                if registration_problem:
                    problem = f'{rel}: {registration_problem}'
                    break

            if not problem:
                try:
                    manifest_result, clusters, _ = manifest_gate(staged)
                    touched = touched_clusters(
                        clusters,
                        sources={source['source']},
                        addresses={args.address},
                        layouts=set(layouts),
                    )
                    probes = probe_cluster_gate(
                        staged, touched,
                        ROOT / f'matching2/build/waves/promotion-probes-{args.address:08x}',
                    )
                except Exception as error:
                    manifest_result = {'passed': False, 'problem': str(error)}
                    probes = {'passed': False, 'cluster_count': 0, 'clusters': [],
                              'problem': 'manifest gate failed'}
            if not manifest_result.get('passed'):
                problem = problem or manifest_result.get('problem', 'manifest validation failed')
            elif not probes.get('passed'):
                failed = [item for item in probes.get('clusters', []) if not item['passed']]
                problem = (failed[0].get('problem') if failed
                           else 'a touched-cluster member probe failed')

            if not problem:
                # The staged artifacts are precisely what passed.  Copy those
                # files, then atomically install the staged manifest while the
                # lock still excludes concurrent registrations.
                for rel in sorted(artifact_rels):
                    target = MAINTAINED / rel
                    target.parent.mkdir(parents=True, exist_ok=True)
                    shutil.copy2(staged / rel, target)
                temporary = maintained_path.with_suffix('.json.tmp')
                shutil.copy2(staged_manifest_path, temporary)
                os.replace(temporary, maintained_path)
                applied = True

    full_hash = full_hash_gate(MAINTAINED, args.full_report)
    report = {
        'schema': 'th10-integration-gates/v1',
        'batch': {
            'apply_requested': True,
            'applied': applied,
            'address': f'0x{args.address:08X}',
            'source': source['source'],
            'layouts': sorted(set(layouts)),
            'problem': problem or None,
            'preintegration_passed': bool(
                manifest_result.get('passed') and probes.get('passed')
            ),
        },
        'gates': {
            'manifest': manifest_result,
            'touched_cluster_probes': probes,
            'full_hash': full_hash,
        },
    }
    report['integration_commit'] = commit_gate(args.integration_commit, full_hash)
    report['release_ready'] = bool(
        applied and manifest_result.get('passed') and probes.get('passed')
        and report['integration_commit']['passed']
    )
    write_gate_report(gate_path, report)
    print(f'manifest gate: {"passed" if manifest_result.get("passed") else "FAILED"}')
    print(f'touched-cluster probes: {"passed" if probes.get("passed") else "FAILED"} '
          f'({probes.get("cluster_count", 0)} cluster(s))')
    print(f'full hash gate: {full_hash["status"]}')
    print(f'gate report: {gate_path}')
    if not applied:
        print(f'refused: {problem}')
        return 1
    print(f'promoted {args.address:#010x}')
    return 0


if __name__ == '__main__':
    sys.exit(main())
