#!/usr/bin/env python3
"""Measure many source variants of one equivalent recovery in parallel.

Like variant.py, but each worker owns a private copy of the project tree, so
variants build concurrently and the real tree is never modified. VARIANTS is
a list of (name, {relative path: new contents}) pairs, or the module may
define a generator function `variants()` yielding them.

Usage:
    python3 psearch.py --layout build_support/layout/equivalent/<name>.json \
        --variants v.py [--jobs 8] [--best 20] [--log out.tsv]
"""
import argparse
import importlib.util
import json
import multiprocessing as mp
import shutil
import sys
import tempfile
from pathlib import Path

if __package__ in (None, ""):
    sys.path.insert(0, str(Path(__file__).resolve().parents[3]))

from matching2.tools.common.project_paths import project_support
from matching2.tools.matching import equivalence
from matching2.tools.matching.variant import measure

ROOT = Path(__file__).resolve().parents[3]
DEFAULT_PROJECT = ROOT / 'matching2/msvc'
DEFAULT_OUTPUT = ROOT / 'matching2/build/msvc'

_state = {}


def _init(project, workdir, layout, output, queue):
    index = queue.get()
    copy = Path(workdir) / f'w{index}' / 'msvc'
    # Always resync: a previous run may have left a variant's files behind.
    shutil.copytree(project, copy, symlinks=True, dirs_exist_ok=True)
    config = json.loads(project_support(copy, 'regions.json').read_text())
    text = (Path(output) / 'text.bin').read_bytes()
    _state.update(copy=copy, layout=layout, output=Path(output), config=config, text=text,
                  originals={})


def _run(item):
    name, files = item
    copy = _state['copy']
    originals = _state['originals']
    for path in list(originals):
        if path not in files:
            (copy / path).write_text(originals.pop(path))
    for path, body in files.items():
        if path not in originals:
            originals[path] = (copy / path).read_text()
        (copy / path).write_text(body)
    try:
        row = measure(_state['layout'], copy, _state['output'], _state['config'], _state['text'])
    except equivalence.EquivalenceError as error:
        lines = str(error).splitlines()
        detail = [l for l in lines if 'error' in l.lower()][:3]
        return name, None, ' | '.join([lines[0]] + detail)
    except Exception as error:  # a variant that does not compile
        return name, None, f'{type(error).__name__}: {str(error).splitlines()[0] if str(error) else ""}'
    body, retail = row['body'], row['retail']
    diffs = [i for i in range(min(len(body), len(retail))) if body[i] != retail[i]]
    row = {k: v for k, v in row.items() if k not in ('body', 'retail')}
    row['first'] = hex(diffs[0]) if diffs else '-'
    row['last'] = hex(diffs[-1]) if diffs else '-'
    return name, row, None


def load_variants(path):
    spec = importlib.util.spec_from_file_location('variants', path)
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    if hasattr(module, 'variants'):
        return list(module.variants())
    return list(module.VARIANTS)


def main():
    parser = argparse.ArgumentParser(description=__doc__,
                                     formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('--layout', required=True)
    parser.add_argument('--variants', required=True, type=Path)
    parser.add_argument('--project', type=Path, default=DEFAULT_PROJECT)
    parser.add_argument('--output', type=Path, default=DEFAULT_OUTPUT)
    parser.add_argument('--workdir', type=Path, help='where the per-worker trees live (kept for reuse)')
    parser.add_argument('--jobs', type=int, default=8)
    parser.add_argument('--best', type=int, default=25, help='rows printed at the end')
    parser.add_argument('--log', type=Path, help='tab-separated results, one row per variant')
    args = parser.parse_args()
    variants = load_variants(args.variants)
    workdir = args.workdir or Path(tempfile.mkdtemp(prefix='psearch-'))
    workdir.mkdir(parents=True, exist_ok=True)
    queue = mp.Queue()
    for index in range(args.jobs):
        queue.put(index)
    log = args.log.open('w') if args.log else None
    results = []
    print(f'{len(variants)} variants, {args.jobs} workers, trees in {workdir}', flush=True)
    with mp.Pool(args.jobs, _init, (args.project.resolve(), str(workdir), args.layout,
                                    str(args.output.resolve()), queue)) as pool:
        for done, (name, row, error) in enumerate(pool.imap_unordered(_run, variants), 1):
            if row is None:
                line = f'{name}\tERROR\t{error}'
            else:
                exact = row['diff_bytes'] == 0 and row['tail_bytes'] == 0
                line = (f"{name}\t{row['identical']}/{row['total']}\t{row['listed']}\t"
                        f"{row['diff_bytes']}\t{row['tail_bytes']}\t{'gate' if not row['gate'] else 'draft'}\t{row['first']}..{row['last']}"
                        f"{chr(9) + 'EXACT' if exact else ''}")
                results.append((row['diff_bytes'] + row['tail_bytes'], -row['identical'], name, line))
                if exact:
                    print('EXACT', name, flush=True)
            if log:
                log.write(line + '\n')
                log.flush()
            if done % 25 == 0:
                best = min(results)[3] if results else '-'
                print(f'[{done}/{len(variants)}] best: {best}', flush=True)
    results.sort()
    print('name\tident\thunks\tbytes\ttail\tgate\tdiff-range')
    for row in results[:args.best]:
        print(row[3])


if __name__ == '__main__':
    main()
