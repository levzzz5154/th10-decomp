"""psearch variant module: write external float constants as literals.

A float literal and an external `float` global with the same value read the
same retail data cell, but the compiler gives them different symbol classes,
which changes x87 operand order and register tie-breaks (this closed
front_hud_update and projectile_spawn_cell). For one equivalent layout this
module yields every single replacement, all replacements together, and each
leave-one-out set. It writes a temporary layout with the extra `__real@`
bindings; run psearch on that layout with EQUIV_LENIENT_BINDINGS=1.

Environment: SWEEP_LAYOUT=build_support/layout/equivalent/<name>.json
             SWEEP_MAX_SINGLES (optional cap)
Usage:
    SWEEP_LAYOUT=... EQUIV_LENIENT_BINDINGS=1 python3 psearch.py \
        --layout build_support/layout/equivalent/_lit_<name>.json \
        --variants literal_sweep.py
"""
import json
import os
import re
import struct
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[3]
sys.path.insert(0, str(ROOT))
from matching2.tools.matching.equivalence import PEImage

PROJECT = ROOT / 'matching2/msvc'
RDATA = (0x466000, 0x466000 + 0xca46)
IMAGE = ROOT / 'matching2/build/msvc/th10.exe'


def literal(value):
    for digits in range(1, 10):
        text = '%.*g' % (digits, value)
        if struct.unpack('<f', struct.pack('<f', float(text)))[0] == value:
            break
    if 'e' not in text and '.' not in text:
        text += '.0'
    return text + 'f'


def source_name(symbol):
    if symbol.startswith('?') and symbol.endswith('@@3MA'):
        return symbol[1:-5]
    if symbol.startswith('_') and not symbol.startswith('__'):
        return symbol[1:]
    return None


def plan(layout_rel):
    layout = json.loads((PROJECT / layout_rel).read_text())
    image = PEImage(IMAGE.read_bytes())
    sources = {}
    pending = list(layout['sources'])
    while pending:
        path = pending.pop()
        if path in sources or not (PROJECT / path).is_file():
            continue
        sources[path] = (PROJECT / path).read_text()
        for include in re.findall(r'#include\s+"([^"]+)"', sources[path]):
            target = os.path.normpath(os.path.join(os.path.dirname(path), include))
            if not target.startswith('..') and target.endswith(('.cpp', '.hpp', '.h')):
                pending.append(target)
    candidates = []
    for symbol, entry in layout.get('absolute_symbols', {}).items():
        if entry.get('kind') != 'data':
            continue
        name = source_name(symbol)
        if not name:
            continue
        pattern = re.compile(r'(?<![\w&.>])' + re.escape(name) + r'(?![\w(\[])')
        uses = {path: len(pattern.findall(text)) for path, text in sources.items()}
        if not any(uses.values()):
            continue
        address = int(entry['address'], 0)
        if not RDATA[0] <= address < RDATA[1]:
            continue  # writable data holds variables, not constants
        try:
            raw = image.read(address, 4)
        except Exception:
            continue
        value = struct.unpack('<f', raw)[0]
        if value != value or abs(value) > 1e9 or (value != 0 and abs(value) < 1e-9):
            continue
        # A float declaration somewhere in the sources or the project headers.
        declared = any(re.search(r'\bfloat\b[^;]*\b' + re.escape(name) + r'\b', text)
                       for text in sources.values())
        if not declared and not symbol.endswith('@@3MA'):
            continue
        candidates.append((name, pattern, literal(value), raw, address))
    return layout, sources, candidates


def write_layout(layout_rel, layout, candidates):
    extra = dict(layout.get('bindings', {}))
    for _, _, _, raw, address in candidates:
        extra.setdefault('__real@%08x' % struct.unpack('<I', raw)[0], hex(address))
    temp = dict(layout, bindings=extra)
    out = Path(layout_rel).with_name('_lit_' + Path(layout_rel).name)
    (PROJECT / out).write_text(json.dumps(temp, indent=2))
    return out


def apply(sources, chosen):
    files = {}
    for path, text in sources.items():
        new = text
        for name, pattern, value, _, _ in chosen:
            lines = new.split('\n')
            for i, line in enumerate(lines):
                if re.match(r'\s*(extern\b|//)', line) or re.search(r'\bfloat\b[^;=()]*\b' + re.escape(name) + r'\b', line):
                    continue
                lines[i] = pattern.sub(value, line)
            new = '\n'.join(lines)
        if new != text:
            files[path] = new
    return files


LAYOUT = os.environ.get('SWEEP_LAYOUT')
if LAYOUT:
    _layout, _sources, CANDIDATES = plan(LAYOUT)
    TEMP_LAYOUT = write_layout(LAYOUT, _layout, CANDIDATES)


def variants():
    yield 'base', dict(_sources)
    for index, candidate in enumerate(CANDIDATES):
        yield f'lit_{candidate[0]}', apply(_sources, [candidate])
    if len(CANDIDATES) > 1:
        yield 'lit_all', apply(_sources, CANDIDATES)
        for index, candidate in enumerate(CANDIDATES):
            rest = CANDIDATES[:index] + CANDIDATES[index + 1:]
            yield f'all_but_{candidate[0]}', apply(_sources, rest)


if __name__ == '__main__':
    os.environ.setdefault('SWEEP_LAYOUT', sys.argv[1])
    _layout, _sources, cands = plan(sys.argv[1])
    for name, _, value, raw, address in cands:
        print(name, value, raw.hex(), hex(address))


# Reverse mode (SWEEP_REVERSE=1): each float literal whose value the layout
# binds through `__real@` becomes an external float at that address.
FLOAT_LITERAL = re.compile(r'(?<![\w.])(-?(?:\d+\.\d*|\.\d+|\d+)(?:[eE][-+]?\d+)?)f\b')


def reverse_plan(layout_rel):
    layout = json.loads((PROJECT / layout_rel).read_text())
    main = layout['sources'][0]
    sources = {main: (PROJECT / main).read_text()}
    by_bits = {}
    for symbol, address in layout.get('bindings', {}).items():
        m = re.fullmatch(r'__real@([0-9a-f]{8})', symbol)
        if m:
            by_bits[int(m[1], 16)] = int(address, 0)
    found = {}
    for path, text in sources.items():
        for m in FLOAT_LITERAL.finditer(text):
            bits = struct.unpack('<I', struct.pack('<f', float(m[1])))[0]
            if bits in by_bits:
                found.setdefault(bits, set()).add(m[1])
    return layout, sources, main, found, by_bits


def reverse_variants():
    layout, sources, main, found, by_bits = reverse_plan(LAYOUT)
    temp = dict(layout, absolute_symbols=dict(layout.get('absolute_symbols', {})))
    for bits in found:
        temp['absolute_symbols']['_sweep_c_%08x' % bits] = {'address': hex(by_bits[bits]), 'kind': 'data'}
    out = Path(LAYOUT).with_name('_rev_' + Path(LAYOUT).name)
    (PROJECT / out).write_text(json.dumps(temp, indent=2))

    # Occurrences in order: (line, start, bits).
    occurrences = []
    for i, line in enumerate(sources[main].split('\n')):
        if line.lstrip().startswith(('#', '//')):
            continue
        for m in FLOAT_LITERAL.finditer(line):
            bits = struct.unpack('<I', struct.pack('<f', float(m[1])))[0]
            if bits in found:
                occurrences.append((i, m.start(), m.end(), bits))

    def make(chosen, only=None):
        lines = sources[main].split('\n')
        picked = [o for o in occurrences if o[3] in chosen and (only is None or o in only)]
        for i, start, end, bits in sorted(picked, key=lambda o: (o[0], -o[1])):
            lines[i] = lines[i][:start] + 'sweep_c_%08x' % bits + lines[i][end:]
        decls = ''.join('extern "C" float sweep_c_%08x;\n' % b for b in sorted({o[3] for o in picked}))
        body = '\n'.join(lines)
        # Declarations go after the last top-level #include.
        at = body.rfind('\n#include')
        at = body.index('\n', at + 1) + 1 if at >= 0 else 0
        return {main: body[:at] + decls + body[at:]}

    yield 'base', dict(sources)
    keys = sorted(found)
    for bits in keys:
        yield 'ext_%08x' % bits, make({bits})
    if len(keys) > 1:
        yield 'ext_all', make(set(keys))
    import itertools
    for bits in keys:
        mine = [o for o in occurrences if o[3] == bits]
        if len(mine) < 2:
            continue
        subsets = [c for r in range(1, len(mine)) for c in itertools.combinations(mine, r)]
        for subset in subsets[:int(os.environ.get('SWEEP_MAX_SUBSETS', '64'))]:
            tag = '_'.join(str(mine.index(o)) for o in subset)
            yield 'ext_%08x_at_%s' % (bits, tag), make({bits}, set(subset))


if os.environ.get('SWEEP_REVERSE'):
    variants = reverse_variants
