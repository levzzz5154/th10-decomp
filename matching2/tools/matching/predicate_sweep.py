"""psearch variant module: name `if` conditions as `const bool` predicates.

`const bool moved = (a != b); if (moved) ...` evaluates exactly what
`if (a != b)` does, but each named, used predicate is one more symbol in the
compiler's table. The symbol numbering decides base/index (SIB) order and
some operand-order tie-breaks (replay_save_update closed this way). This
module hoists the condition of plain `if` statements (not `else if`, not the
unbraced body of another statement) into a predicate declared on the line
before, and yields every single hoist plus random subsets.

Environment: SWEEP_LAYOUT=build_support/layout/equivalent/<name>.json
             SWEEP_FILE (optional; default the layout's first source)
             SWEEP_RANDOM (number of random subsets, default 300)
             SWEEP_SEED (default 1)
"""
import json
import os
import random
import re
from pathlib import Path

ROOT = Path(__file__).resolve().parents[3]
PROJECT = ROOT / 'matching2/msvc'

IF_HEAD = re.compile(r'^(\s*)if\s*\(')


def balanced(text, start):
    """Index just past the parenthesis group opening at text[start]."""
    depth = 0
    for i in range(start, len(text)):
        if text[i] == '(':
            depth += 1
        elif text[i] == ')':
            depth -= 1
            if depth == 0:
                return i + 1
    return None


def find_ifs(text):
    lines = text.split('\n')
    offsets, total = [], 0
    for line in lines:
        offsets.append(total)
        total += len(line) + 1
    found = []
    for n, line in enumerate(lines):
        m = IF_HEAD.match(line)
        if not m:
            continue
        # The previous code line must end a statement or open a block.
        k = n - 1
        while k >= 0 and (not lines[k].strip() or lines[k].strip().startswith('//')):
            k -= 1
        if k < 0:
            continue
        prev = lines[k].rstrip()
        if not (prev.endswith(';') or prev.endswith('{') or prev.endswith('}')):
            continue
        if re.search(r'\b(case\s+[^:]+|default)\s*:\s*$', prev):
            continue
        open_at = offsets[n] + line.index('(')
        close_at = balanced(text, open_at)
        if close_at is None:
            continue
        cond = text[open_at + 1:close_at - 1]
        if '=' in re.sub(r'[=!<>]=', '', cond) or '++' in cond or '--' in cond:
            continue  # assignments or side effects in the condition
        found.append((n, m[1], open_at, close_at, cond))
    return found


def hoist(text, chosen):
    for n, indent, open_at, close_at, cond in sorted(chosen, key=lambda c: -c[2]):
        name = f'cond_{n + 1}'
        line_start = text.rfind('\n', 0, open_at) + 1
        text = (text[:line_start] + f'{indent}const bool {name} = ({cond});\n' +
                text[line_start:open_at + 1] + name + text[close_at - 1:])
    return text


LAYOUT = os.environ.get('SWEEP_LAYOUT')


def variants():
    layout = json.loads((PROJECT / LAYOUT).read_text())
    path = os.environ.get('SWEEP_FILE') or layout['sources'][0]
    text = (PROJECT / path).read_text()
    ifs = find_ifs(text)
    yield 'base', {path: text}
    for item in ifs:
        yield f'p{item[0] + 1}', {path: hoist(text, [item])}
    if len(ifs) > 1:
        yield 'p_all', {path: hoist(text, ifs)}
        rnd = random.Random(int(os.environ.get('SWEEP_SEED', '1')))
        seen = set()
        for _ in range(int(os.environ.get('SWEEP_RANDOM', '300'))):
            k = rnd.randint(2, max(2, len(ifs) - 1))
            subset = tuple(sorted(rnd.sample(range(len(ifs)), min(k, len(ifs)))))
            if subset in seen:
                continue
            seen.add(subset)
            chosen = [ifs[i] for i in subset]
            yield 'ps_' + '_'.join(str(ifs[i][0] + 1) for i in subset), {path: hoist(text, chosen)}


if __name__ == '__main__':
    import sys
    layout = json.loads((PROJECT / sys.argv[1]).read_text())
    path = layout['sources'][0]
    for item in find_ifs((PROJECT / path).read_text()):
        print(item[0] + 1, item[4][:80])
