#!/usr/bin/env python3
"""Recompute familiar_refresh cluster gaps + anchor sizes from the latest map."""
import json, re, sys
from pathlib import Path

ROOT = Path('/home/levzzz/Games/th10Decomp')
BUILD = ROOT / 'matching2/build/probe-gfr/clusters/familiar_refresh_00426f70'
TEXT_END = 0x465A81

maps = sorted(BUILD.glob('native-*/cluster.map'), key=lambda p: p.stat().st_mtime)
if not maps:
    sys.exit('no cluster.map found')
lines = maps[-1].read_text().splitlines()

# all section-0001 entries in address order
entries = []
for line in lines:
    m = re.match(r' 0001:([0-9a-f]+)\s+(\S+)\s+([0-9a-f]+)', line)
    if m:
        entries.append((int(m.group(3), 16), m.group(2)))
entries.sort()

mpath = ROOT / 'matching2/msvc/layout/ltcg/familiar_refresh_00426f70.json'
man = json.loads(mpath.read_text())

# declared target for every function and anchor
targets = {}
for f in man['functions']:
    targets[f['symbol']] = int(f['address'], 16)
for a in man['anchors']:
    targets[a['symbol']] = int(a['address'], 16)

end = {}
for i, (addr, name) in enumerate(entries):
    if name in targets:
        nxt = entries[i + 1][0] if i + 1 < len(entries) else TEXT_END
        end[name] = targets[name] + (nxt - addr)

for f in man['functions']:
    sym = f['symbol']
    actual = end[sym] - targets[sym]
    if sym == man['entry']:
        print(f"function size now {actual} (target {f['size']})")
    else:
        flag = '' if actual == f['size'] else f'  (was {f["size"]}, retail {f["size"]})'
        print(f"{f['name']:42} {actual}{flag}")
    f['size'] = actual
for a in man['anchors']:
    a['size'] = end[a['symbol']] - targets[a['symbol']]

# gaps: consecutive contributions in address order
seq = [(targets[f['symbol']], end[f['symbol']]) for f in man['functions']]
seq += [(targets[a['symbol']], end[a['symbol']]) for a in man['anchors']]
seq.sort()
seq.append((TEXT_END, None))
gaps = []
prev_end = None
covered_to = None
for target, e in seq:
    if covered_to is None:
        covered_to = e
        continue
    if target > covered_to:
        gaps.append({'section': f'.text${covered_to:08x}_gap',
                     'address': f'{covered_to:#08x}', 'size': target - covered_to})
        covered_to = target
    if e is not None and e > covered_to:
        covered_to = e
# remaining space after the last contribution
if covered_to < TEXT_END:
    gaps.append({'section': f'.text${covered_to:08x}_gap',
                 'address': f'{covered_to:#08x}', 'size': TEXT_END - covered_to})
man['gaps'] = gaps

for p in [mpath, ROOT / 'scratch/gfr/msvc/layout/ltcg/familiar_refresh_00426f70.json']:
    Path(p).write_text(json.dumps(man, indent=1) + '\n')
print('gaps:', [(g['address'], g['size']) for g in gaps])
