"""Compare two rtrace.exe traces from the same replay and report the first divergence.

    compare.py <retail.bin> <candidate.bin> [--start-a N --start-b M]

Records are aligned by hit index after each trace's replay start (the first hit recorded
after the run's meta.json `start_hit`, defaulting to 0).
"""
import json
import struct
import sys
from pathlib import Path

RECORD = struct.Struct('<4I64I16sI16I')
FIELDS = (['magic', 'hit', 'mode', 'flags'] + [f'g+{i * 4:#04x}' for i in range(64)]
          + ['rng'] + ['player'] + [f'p+{0x3b0 + i * 4:#05x}' for i in range(16)])
# Heap pointers can legitimately differ between executables. g+0x70.. holds obfuscated/clock-derived
# bytes; g+0x38 and g+0x68 keep values left by an attract demo that ran before the replay.
IGNORED = {'magic', 'hit', 'player', 'g+0x38', 'g+0x68'} | {f'g+{i * 4:#04x}' for i in range(0x70 // 4, 64)}


def load(path):
    data = Path(path).read_bytes()
    n = len(data) // RECORD.size
    return [RECORD.unpack_from(data, i * RECORD.size) for i in range(n)]


def flatten(rec):
    # rng[0:8] is 0x004918A8, seeded from the clock; rng[8:16] is the replay-seeded 0x004918B0.
    values = list(rec[:4 + 64]) + [rec[68][8:].hex()] + [rec[69]] + list(rec[70:])
    return dict(zip(FIELDS, values))


def start_hit(path):
    meta = Path(str(path) + '.meta.json')
    return json.loads(meta.read_text()).get('start_hit', 0) if meta.exists() else 0


def pointerish(field, a, b):
    return all(0x00400000 <= v < 0x80000000 and v & 3 == 0 for v in (a, b) if isinstance(v, int)) and a and b


def main(argv):
    a_path, b_path = argv[0], argv[1]
    a, b = load(a_path), load(b_path)
    sa, sb = start_hit(a_path), start_hit(b_path)
    a, b = a[sa:], b[sb:]
    n = min(len(a), len(b))
    print(f'{a_path}: {len(a)} frames after start; {b_path}: {len(b)} frames after start')
    # Fields that are pointer-valued and differ from the first frame are heap addresses, not state.
    first_a, first_b = flatten(a[0]), flatten(b[0])
    ignored = set(IGNORED)
    for f in FIELDS:
        if f not in ignored and first_a[f] != first_b[f] and pointerish(f, first_a[f], first_b[f]):
            ignored.add(f)
    if len(ignored) > len(IGNORED):
        print('ignoring pointer-valued fields:', sorted(ignored - IGNORED))
    for i in range(n):
        fa, fb = flatten(a[i]), flatten(b[i])
        diff = [f for f in FIELDS if f not in ignored and fa[f] != fb[f]]
        if diff:
            print(f'FIRST DIVERGENCE at frame {i} (hits {sa + i} / {sb + i}):')
            for f in diff:
                va, vb = fa[f], fb[f]
                show = (lambda v: v if isinstance(v, str) else f'{v:#010x} ({v})')
                print(f'  {f:>8}: retail {show(va)}  candidate {show(vb)}')
            prev = flatten(a[i - 1]) if i else None
            if prev:
                print(f'  score before: {prev["g+0x04"]}, mode {prev["mode"]}')
            return 1
    if len(a) != len(b):
        print(f'IDENTICAL for {n} common frames, but lengths differ ({len(a)} vs {len(b)})')
        return 1
    last = flatten(a[n - 1])
    print(f'IDENTICAL: {n} frames, final score {last["g+0x04"]}')
    return 0


if __name__ == '__main__':
    sys.exit(main(sys.argv[1:]))
