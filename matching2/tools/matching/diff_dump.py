#!/usr/bin/env python3
"""Dump what keeps one equivalent recovery from being byte-identical.

Shows the recorded instruction differences and, around each byte that differs,
the retail and model instructions that contain it.

Usage:
    python3 diff_dump.py --layout build_support/layout/equivalent/<name>.json
    python3 diff_dump.py --name <recovery-name> [--context 8] [--raw]
"""
import argparse
import json
import sys
from pathlib import Path

if __package__ in (None, ""):
    sys.path.insert(0, str(Path(__file__).resolve().parents[3]))

from matching2.tools.common.project_paths import project_support
from matching2.tools.matching import equivalence

ROOT = Path(__file__).resolve().parents[3]
DEFAULT_PROJECT = ROOT / 'matching2/msvc'
DEFAULT_OUTPUT = ROOT / 'matching2/build/msvc'


def main():
    parser = argparse.ArgumentParser(description=__doc__,
                                     formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('--project', type=Path, default=DEFAULT_PROJECT)
    parser.add_argument('--output', type=Path, default=DEFAULT_OUTPUT)
    parser.add_argument('--layout', help='a layout under build_support/layout/equivalent/')
    parser.add_argument('--name', help='or a registered recovery name')
    parser.add_argument('--context', type=int, default=6, help='instructions shown around a byte diff')
    parser.add_argument('--raw', action='store_true', help='also print raw byte hex of differing runs')
    args = parser.parse_args()
    project, output = args.project.resolve(), args.output.resolve()
    config = json.loads((project_support(project, 'regions.json')).read_text())
    text = (output / 'text.bin').read_bytes()
    if args.layout:
        layout = json.loads((project / args.layout).read_text())
        config = {**config, 'equivalent_recoveries': [{'region': layout['region'], 'layout': args.layout}]}
    elif args.name:
        pass
    else:
        parser.error('--layout or --name is required')
    recoveries = equivalence.load_recoveries(project, config, config['regions'])
    if args.name:
        recoveries = [item for item in recoveries if item['name'] == args.name]
    if not recoveries:
        parser.error('no such recovery')
    recovery = recoveries[0]
    start, size = recovery['address'], recovery['size']
    retail = text[start - equivalence.TEXT_START:start - equivalence.TEXT_START + size]
    report, body = equivalence.verify_recovery(recovery, project, equivalence.DEFAULT_TOOLKIT.resolve(),
                                               config['flags'], text, output, record=True)
    code = min(report['code_bytes'], size)
    print(f"{recovery['name']} {hex(start)} size={size} code={report['code_bytes']} "
          f"identical={report['identical']}/{report['instructions']} "
          f"swaps={report['base_index_order']} listed={report['listed_differences']}")
    if report['not_equivalent']:
        print('gate:', *report['not_equivalent'], sep='\n  ')
    diffs = [offset for offset in range(code) if retail[offset] != body[offset]]
    if not diffs:
        print('CODE IS BYTE-IDENTICAL')
    else:
        print(f"{len(diffs)} differing bytes in code: "
              f"{[hex(offset) for offset in diffs[:40]]}{' ...' if len(diffs) > 40 else ''}")
    tail = [offset for offset in range(code, size) if retail[offset] != body[offset]]
    if tail:
        print(f"{len(tail)} differing tail bytes at {[hex(code + offset) for offset in tail[:20]]}")
    print('\nrecorded differences:')
    for hunk in report['differences']:
        print(f"  @{int(hunk['offset'], 0):#x} class={hunk.get('class')}")
        for line in hunk['retail']:
            print(f"    retail {line}")
        for line in hunk['model']:
            print(f"    model  {line}")
    rows_retail = equivalence.disassemble(retail[:code], start, Path('/tmp'), 'retail')
    rows_model = equivalence.disassemble(body[:code], start, Path('/tmp'), 'model')
    by_offset = {}
    for offset, text_ in rows_retail:
        by_offset[offset] = [text_]
    for offset, text_ in rows_model:
        by_offset.setdefault(offset, []).append(text_)
    shown = set()
    print('\nneighbourhood of the first differing bytes:')
    for offset in diffs[:12]:
        lo = max(0, offset - 16)
        near = sorted(item for item in by_offset if lo <= item <= offset + 16)
        for item in near:
            if item in shown:
                continue
            shown.add(item)
            left = by_offset[item][0]
            right = by_offset[item][1] if len(by_offset[item]) > 1 else ''
            flag = '  <-- DIFFERS' if left != right else ''
            print(f"  {item:#06x}  retail {left}")
            if right and right != left:
                print(f"         model  {right}{flag}")
        print('  ---')
    if args.raw:
        print('\nraw differing runs:')
        run = []
        for offset in range(size):
            if retail[offset] != body[offset]:
                run.append(offset)
            elif run:
                lo, hi = run[0], run[-1] + 1
                print(f"  {lo:#06x}-{hi:#06x} retail {retail[lo:hi].hex()}  model {body[lo:hi].hex()}")
                run = []
        if run:
            lo, hi = run[0], run[-1] + 1
            print(f"  {lo:#06x}-{hi:#06x} retail {retail[lo:hi].hex()}  model {body[lo:hi].hex()}")


if __name__ == '__main__':
    main()
