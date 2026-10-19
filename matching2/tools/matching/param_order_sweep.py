"""psearch variant module: permute the parameters of a stand-in callee.

In an LTCG cluster the callee's parameter order decides the order in which a
caller loads its arguments (and which registers private conventions use).
Equivalent-only stand-ins in `build_support/contexts/equivalent/` can take
any order; this rewrites the declaration, the definition and every call of
one function in the given files with each permutation of its parameters.

Environment: SWEEP_FUNC=<function name>
             SWEEP_FILES=<comma-separated project-relative files>
             SWEEP_MAX (optional cap on permutations, default 720)
"""
import itertools
import os
import re
from pathlib import Path

ROOT = Path(__file__).resolve().parents[3]
PROJECT = ROOT / 'matching2/msvc'


def split_args(text):
    parts, depth, start = [], 0, 0
    for i, ch in enumerate(text):
        if ch in '([{<':
            depth += 1
        elif ch in ')]}>':
            depth -= 1
        elif ch == ',' and depth == 0:
            parts.append(text[start:i])
            start = i + 1
    parts.append(text[start:])
    return parts


def occurrences(text, name):
    for m in re.finditer(r'\b' + re.escape(name) + r'\s*\(', text):
        open_at = m.end() - 1
        depth = 0
        for i in range(open_at, len(text)):
            if text[i] == '(':
                depth += 1
            elif text[i] == ')':
                depth -= 1
                if depth == 0:
                    yield open_at + 1, i
                    break


def permute(text, name, perm):
    spans = list(occurrences(text, name))
    for start, end in reversed(spans):
        args = split_args(text[start:end])
        if len(args) != len(perm):
            raise ValueError(f'{name}: {len(args)} arguments where {len(perm)} expected')
        # Keep each slot's leading whitespace (line breaks in long lists).
        lead = [re.match(r'\s*', a).group(0) for a in args]
        body = [a.strip() for a in args]
        text = text[:start] + ','.join(lead[i] + body[p] for i, p in enumerate(perm)) + text[end:]
    return text


def variants():
    name = os.environ['SWEEP_FUNC']
    files = os.environ['SWEEP_FILES'].split(',')
    texts = {f: (PROJECT / f).read_text() for f in files}
    count = None
    for text in texts.values():
        for start, end in occurrences(text, name):
            count = len(split_args(text[start:end]))
            break
        if count:
            break
    cap = int(os.environ.get('SWEEP_MAX', '720'))
    for n, perm in enumerate(itertools.permutations(range(count))):
        if n >= cap:
            break
        yield 'p' + ''.join(map(str, perm)), {f: permute(t, name, perm) for f, t in texts.items()}
