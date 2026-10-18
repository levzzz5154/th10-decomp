#!/usr/bin/env python3
"""Report, for every equivalent recovery, whether its relocated C++ body is byte-identical to retail.

The gate accepts instruction-equivalence (base/index swaps, listed differences).
Promotion to `semantic` needs byte equality, so this measures that directly:
`make` first, then run this script.
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


def first_difference(retail, body):
    for offset, (left, right) in enumerate(zip(retail, body)):
        if left != right:
            return offset
    return None if len(retail) == len(body) else min(len(retail), len(body))


def main():
    parser = argparse.ArgumentParser(description=__doc__,
                                     formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('--project', type=Path, default=DEFAULT_PROJECT)
    parser.add_argument('--output', type=Path, default=DEFAULT_OUTPUT)
    parser.add_argument('--name', help='only this recovery')
    parser.add_argument('--json', action='store_true', help='machine-readable output')
    args = parser.parse_args()
    project, output = args.project.resolve(), args.output.resolve()
    config = json.loads((project_support(project, 'regions.json')).read_text())
    text = (output / 'text.bin').read_bytes()
    recoveries = equivalence.load_recoveries(project, config, config['regions'])
    if args.name:
        recoveries = [item for item in recoveries if item['name'] == args.name]
        if not recoveries:
            parser.error('no such equivalent recovery: ' + args.name)
    rows = []
    for recovery in recoveries:
        report, body = equivalence.verify_recovery(recovery, project, equivalence.DEFAULT_TOOLKIT.resolve(),
                                                   config['flags'], text, output, record=True)
        start, size = recovery['address'], recovery['size']
        retail = text[start - equivalence.TEXT_START:start - equivalence.TEXT_START + size]
        used = report['code_bytes']
        code = min(used, size)
        offset = first_difference(retail[:code], body[:code])
        tail_bad = first_difference(retail[code:size], body[code:size])
        rows.append({'name': recovery['name'], 'region': recovery['region'], 'address': hex(start),
                     'bytes': size, 'code_bytes': used, 'instructions': report['instructions'],
                     'identical': report['identical'], 'swaps': report['base_index_order'],
                     'listed': report['listed_differences'],
                     'listed_instructions': report['listed_instructions'],
                     'code_exact': offset is None, 'tail_exact': tail_bad is None,
                     'first_diff': offset, 'tail_first_diff': tail_bad,
                     'gate': report['not_equivalent']})
    if args.json:
        print(json.dumps(rows, indent=2))
        return
    print(f"{'address':<12}{'name':<38}{'bytes':>7}{'ident':>7}{'swaps':>6}{'diffs':>6}"
          f"{'code':>7}{'tail':>7}  first diff")
    for row in rows:
        print(f"{row['address']:<12}{row['name']:<38}{row['bytes']:>7,}{row['identical']:>7}"
              f"{row['swaps']:>6}{row['listed']:>6}"
              f"{'OK' if row['code_exact'] else '-':>7}{'OK' if row['tail_exact'] else '-':>7}"
              f"  {row['first_diff'] if row['first_diff'] is not None else '-'}"
              f"{' tail@%#x' % row['tail_first_diff'] if row['tail_first_diff'] is not None else ''}")
    exact = [row for row in rows if row['code_exact'] and row['tail_exact'] and not row['gate']]
    print(f"\nbyte-exact bodies: {len(exact)} of {len(rows)}")
    for row in exact:
        print('  ', row['address'], row['name'])


if __name__ == '__main__':
    main()
