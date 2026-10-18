#!/usr/bin/env python3
"""Measure equivalent-recovery drafts that vary the compilation context.

HANDOFF records that earlier "impossible" allocator residuals were closed by
changing the cluster context -- real callee bodies, the /INCLUDE roots, opaque
callees -- rather than the function body.  The equivalence tool already
measures unregistered draft layouts under layout/equivalent/, so this writes a
draft per context variant and reports the byte-difference count for each.

Usage:
    python3 context_probe.py --layout laser_rectangle_split [--dry-run]
"""
import argparse
import json
import shutil
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[3]
PROJECT = ROOT / 'matching2/msvc'
EQUIV = PROJECT / 'build_support/layout/equivalent'
sys.path.insert(0, str(ROOT))

from matching2.tools.common.project_paths import project_support
from matching2.tools.matching import equivalence


def measure(layout_path, config, text):
    layout = json.loads((PROJECT / layout_path).read_text())
    cfg = {**config, 'equivalent_recoveries': [{'region': layout['region'], 'layout': str(layout_path)}]}
    recovery = equivalence.load_recoveries(PROJECT, cfg, cfg['regions'])[0]
    report, body = equivalence.verify_recovery(recovery, PROJECT, equivalence.DEFAULT_TOOLKIT.resolve(),
                                               config['flags'], text, equivalence.DEFAULT_OUTPUT.resolve(),
                                               record=True)
    start, size = recovery['address'], recovery['size']
    retail = text[start - equivalence.TEXT_START:start - equivalence.TEXT_START + size]
    code = min(report['code_bytes'], size)
    diffs = sum(1 for off in range(size) if retail[off] != body[off])
    return {'identical': report['identical'], 'total': report['instructions'],
            'swaps': report['base_index_order'], 'listed': report['listed_differences'],
            'diff_bytes': diffs, 'gate': report['not_equivalent']}


def main():
    parser = argparse.ArgumentParser(description=__doc__,
                                     formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('--layout', required=True, help='layout name under layout/equivalent/, without .json')
    parser.add_argument('--dry-run', action='store_true')
    args = parser.parse_args()
    src = EQUIV / f'{args.layout}.json'
    base = json.loads(src.read_text())
    config = json.loads((project_support(PROJECT, 'regions.json')).read_text())
    text = (equivalence.DEFAULT_OUTPUT / 'text.bin').read_bytes()

    roots = list(base.get('roots', []))
    variants = {}

    # Every prefix of the current root set: does dropping /INCLUDE roots move
    # the allocation?  HANDOFF notes roots freeze declared ABIs.
    for keep in range(len(roots) + 1):
        variants[f'roots-{keep}'] = {'roots': roots[:keep]}
    # Each root dropped on its own.
    for index in range(len(roots)):
        variants[f'drop-{index}'] = {'roots': [r for i, r in enumerate(roots) if i != index]}
    # No context cluster at all: the model alone.
    variants['no-cluster'] = {'context_cluster': None}
    # Extra roots: bind the region's own callees explicitly.
    variants['roots-plus-self'] = {'roots': roots + [base['function']]}

    print(f"{'variant':<22}{'ident':>9}{'swaps':>6}{'listed':>7}{'bytes':>7}  gate")
    for name, patch in variants.items():
        draft = dict(base)
        draft.update(patch)
        if patch.get('context_cluster', 'keep') is None:
            draft.pop('context_cluster', None)
        path = EQUIV / f'{args.layout}__{name}.json'
        if args.dry_run:
            print(f'{name:<22} {json.dumps(patch)[:90]}')
            continue
        path.write_text(json.dumps(draft, indent=2) + '\n')
        try:
            row = measure(path.relative_to(PROJECT), config, text)
        except equivalence.EquivalenceError as error:
            print(f'{name:<22}  ERROR {str(error).splitlines()[0]}')
        else:
            star = ' *EXACT*' if row['diff_bytes'] == 0 else ''
            print(f"{name:<22}{row['identical']:>5}/{row['total']:<3}{row['swaps']:>6}"
                  f"{row['listed']:>7}{row['diff_bytes']:>7}{star}")
        finally:
            path.unlink(missing_ok=True)


if __name__ == '__main__':
    main()
