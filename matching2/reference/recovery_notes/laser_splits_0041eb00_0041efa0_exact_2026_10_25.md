# Laser splits 0x0041EB00 and 0x0041EFA0: byte-exact (2026-10-25)

`CutLaser::CutRectangle` (1,171 bytes, `src/game/laser/laser_rectangle_split.cpp`)
and `CutLaser::CutCircle` (1,108 bytes, `src/game/laser/laser_circle_split.cpp`)
are now selected by the `laser_cut` cluster, next to the two trims. All four
laser cutters are byte-exact. The equivalent layouts, the cluster's old
`CutCircle` context body (`layout/ltcg/laser_cut/circle_cut.cpp`), and the asm
owner `build_support/exact/game/laser/laser_segment_cut.cpp` are removed.

Both closed only after the circle trim promotion
(`laser_circle_trim_0041dd80_exact_2026_10_25.md`) gave the cluster a visible
`CutVector::SetPolar` that leaves EDX alone. Retail zeroes the counter homes
and `point.z` from one EDX held across that call; with the opaque SetPolar no
spelling could reproduce it.

## Measuring in the cluster

`build/experiments/goal_2026_10_25/cs_try.py` builds `laser_cut` in a worker
copy of the project with one candidate body (7 s per build), resizes the anchor
or context and the next gap to the compiled size, and compares with retail.
The sweeps are `csv/v1.py` (circle) and `csv/r1.py` (rectangle).

## Circle split: the circle trim's spellings

From 237/302 (the old view-struct model) to 302/302:

- `int hit_count=0; int count=0;` before `CutVector origin=position;`
  (origin first: 245/302 at best);
- the loop reads the sample only through `CutVector* sample=&point;`
  (direct `point.x` reads: 298/302);
- the line-animation creation spelled out (Allocate, flags, the render-bucket
  clear through `int* bucket`, position x/z/y, LoadScript2,
  RegisterPrimaryBack). The `CreateOffset` call, inlined by LTCG, gives
  300/302; named index/resource locals with the call, 298/302.

`origin+step*start` and `origin+start*step` give the same bytes here.

## Rectangle split: counters first, one guard

The last byte was `je` against `jle` at +0x2AC. The model guarded the run loop
with `if (hit_count) { if (hit_count > 0) ...` because a single test used to
cost more elsewhere. With the counters declared before the origin copy, the
single `if (hit_count)` is exact (316/316). The rectangle hit test keeps the
direct `point.x`/`point.y` reads and the named `index`/`resource` locals; the
sample pointer here costs 4 instructions, and the spelled-out creation does not
fit (1,267 bytes).

## Cluster changes

`laser_cut.json`: both splits are `functions`/`roots` with their sources. A
version-1 cluster needs an unselected link entry, so the context is now the
`ItemPolarVelocity2::SetPolar` anchor (0x0041BEB0), which was already an
`anchor_root`; `CutRectangle` and that anchor left `anchors`/`anchor_roots`.
Gaps are unchanged. Generator:
`build/experiments/goal_2026_10_25/promote_splits.py`.

## Validation

`make` (byte-exact C++ 85.1% -> 85.8%, equivalent regions 17 -> 15),
`make EXACT=1` (SHA-256 `2f14760b6fbbf575…`), `callsite_abi.py`, 127 tool unit
tests, `git diff --check`.
