"""psearch variant module: swap the arms of braced `if (c) {A} else {B}`.

`if (!(c)) {B} else {A}` runs the same code, but c2 visits the branch target
before the fallthrough, so the arm order can change block layout and branch
polarity. Yields each single swap, all swaps, and random subsets.

Environment: SWEEP_LAYOUT=build_support/layout/equivalent/<name>.json
             SWEEP_FILE (optional; default the layout's first source)
             SWEEP_RANDOM (default 200), SWEEP_SEED (default 1)
"""
import json
import os
import random
import re
from pathlib import Path

ROOT = Path(__file__).resolve().parents[3]
PROJECT = ROOT / 'matching2/msvc'
IF = re.compile(r'(?<![\w#])if\s*\(')


def match(text, start, open_ch, close_ch):
    depth = 0
    for i in range(start, len(text)):
        if text[i] == open_ch:
            depth += 1
        elif text[i] == close_ch:
            depth -= 1
            if depth == 0:
                return i + 1
    return None


def find(text):
    found = []
    for m in IF.finditer(text):
        before = text[:m.start()].rstrip()
        if before.endswith('else'):
            continue  # else-if chains
        paren = m.end() - 1
        cond_end = match(text, paren, '(', ')')
        if cond_end is None:
            continue
        rest = text[cond_end:]
        lead = len(rest) - len(rest.lstrip())
        if not rest.lstrip().startswith('{'):
            continue
        a_start = cond_end + lead
        a_end = match(text, a_start, '{', '}')
        if a_end is None:
            continue
        tail = text[a_end:]
        em = re.match(r'\s*else\s*\{', tail)
        if not em:
            continue
        b_start = a_end + em.end() - 1
        b_end = match(text, b_start, '{', '}')
        if b_end is None:
            continue
        cond = text[paren + 1:cond_end - 1]
        found.append((m.start(), b_end, cond, text[a_start:a_end], text[b_start:b_end]))
    # keep non-overlapping-at-same-start; nested ones are fine if applied innermost first
    return found


def apply(text, chosen):
    # Apply innermost (latest start) first so outer spans stay valid in length terms.
    for start, end, cond, arm_a, arm_b in sorted(chosen, key=lambda c: -c[0]):
        cur = text[start:end]
        # recompute arms inside current text in case nested swaps changed them
        sub = find(cur)
        if not sub or sub[0][0] != 0:
            continue
        _, e, cond, arm_a, arm_b = sub[0]
        text = text[:start] + f'if (!({cond})) {arm_b} else {arm_a}' + text[start + e:]
    return text


LAYOUT = os.environ.get('SWEEP_LAYOUT')


def variants():
    layout = json.loads((PROJECT / LAYOUT).read_text())
    path = os.environ.get('SWEEP_FILE') or layout['sources'][0]
    text = (PROJECT / path).read_text()
    items = find(text)
    yield 'base', {path: text}
    for i, item in enumerate(items):
        yield f's{text.count(chr(10), 0, item[0]) + 1}', {path: apply(text, [item])}
    if len(items) > 1:
        yield 's_all', {path: apply(text, items)}
        rnd = random.Random(int(os.environ.get('SWEEP_SEED', '1')))
        seen = set()
        for _ in range(int(os.environ.get('SWEEP_RANDOM', '200'))):
            k = rnd.randint(2, max(2, len(items) - 1))
            subset = tuple(sorted(rnd.sample(range(len(items)), min(k, len(items)))))
            if subset in seen:
                continue
            seen.add(subset)
            name = 'ss_' + '_'.join(str(text.count(chr(10), 0, items[i][0]) + 1) for i in subset)
            yield name, {path: apply(text, [items[i] for i in subset])}


if __name__ == '__main__':
    import sys
    layout = json.loads((PROJECT / sys.argv[1]).read_text())
    text = (PROJECT / layout['sources'][0]).read_text()
    for item in find(text):
        print(text.count('\n', 0, item[0]) + 1, item[2][:70])
