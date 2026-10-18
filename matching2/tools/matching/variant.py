#!/usr/bin/env python3
"""Try source variants for one equivalent recovery and report byte-exactness.

Each variant is a (name, {relative path: new contents}) pair supplied by a
Python file that defines VARIANTS. The original files are restored afterwards
unless --keep is given.

Usage:
    python3 variant.py --layout build_support/layout/equivalent/camera_shake.json \
        --variants /tmp/variants.py [--keep] [--filter name]
"""
import argparse
import importlib.util
import json
import shutil
import sys
from pathlib import Path

if __package__ in (None, ""):
    sys.path.insert(0, str(Path(__file__).resolve().parents[3]))

from matching2.tools.common.project_paths import project_support
from matching2.tools.matching import equivalence

ROOT = Path(__file__).resolve().parents[3]
DEFAULT_PROJECT = ROOT / 'matching2/msvc'
DEFAULT_OUTPUT = ROOT / 'matching2/build/msvc'


def measure(layout_path, project, output, config, text):
    layout = json.loads((project / layout_path).read_text())
    cfg = {**config, 'equivalent_recoveries': [{'region': layout['region'], 'layout': layout_path}]}
    recovery = equivalence.load_recoveries(project, cfg, cfg['regions'])[0]
    report, body = equivalence.verify_recovery(recovery, project, equivalence.DEFAULT_TOOLKIT.resolve(),
                                               config['flags'], text, output, record=True)
    start, size = recovery['address'], recovery['size']
    retail = text[start - equivalence.TEXT_START:start - equivalence.TEXT_START + size]
    code = min(report['code_bytes'], size)
    diffs = sum(1 for offset in range(code) if retail[offset] != body[offset])
    tail = sum(1 for offset in range(code, size) if retail[offset] != body[offset])
    return {'identical': report['identical'], 'total': report['instructions'],
            'swaps': report['base_index_order'], 'listed': report['listed_differences'],
            'diff_bytes': diffs, 'tail_bytes': tail, 'code_bytes': report['code_bytes'],
            'gate': report['not_equivalent'], 'body': body, 'retail': retail, 'size': size}


def main():
    parser = argparse.ArgumentParser(description=__doc__,
                                     formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('--layout', required=True)
    parser.add_argument('--variants', required=True, type=Path)
    parser.add_argument('--project', type=Path, default=DEFAULT_PROJECT)
    parser.add_argument('--output', type=Path, default=DEFAULT_OUTPUT)
    parser.add_argument('--keep', action='store_true', help='leave the last variant in place')
    parser.add_argument('--filter', help='only variants whose name contains this')
    args = parser.parse_args()
    project, output = args.project.resolve(), args.output.resolve()
    config = json.loads((project_support(project, 'regions.json')).read_text())
    text = (output / 'text.bin').read_bytes()
    spec = importlib.util.spec_from_file_location('variants', args.variants)
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    paths = set()
    for _, files in module.VARIANTS:
        paths.update(files)
    backup = {path: (project / path).read_text() for path in paths}
    print(f"{'variant':<34}{'ident':>7}{'swaps':>6}{'diffs':>6}{'bytes':>8}{'tail':>6}  gate")
    try:
        for name, files in module.VARIANTS:
            if args.filter and args.filter not in name:
                continue
            for path, body in files.items():
                (project / path).write_text(body)
            try:
                row = measure(args.layout, project, output, config, text)
            except equivalence.EquivalenceError as error:
                detail = str(error).splitlines()
                print(f"{name:<34}  ERROR {detail[0]}")
                for line in detail[1:6]:
                    print(f"{'':<34}        {line}")
                continue
            flag = '' if not row['gate'] else ' drafts'
            star = ' *EXACT*' if row['diff_bytes'] == 0 and row['tail_bytes'] == 0 else ''
            print(f"{name:<34}{row['identical']:>5}/{row['total']:<3}{row['swaps']:>6}"
                  f"{row['listed']:>6}{row['diff_bytes']:>8}{row['tail_bytes']:>6}{flag}{star}")
            sys.stdout.flush()
    finally:
        if not args.keep:
            for path, body in backup.items():
                (project / path).write_text(body)


if __name__ == '__main__':
    main()
