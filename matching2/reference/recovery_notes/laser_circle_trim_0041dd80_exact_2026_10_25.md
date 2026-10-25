# Circle trim 0x0041DD80: byte-exact (2026-10-25)

`TrimLaser::TrimCircle` (1,238 bytes, `src/game/laser/laser_circle_trim.cpp`)
is now selected by the `laser_cut` LTCG cluster next to `TrimRectangle`. Its
equivalent layout, the cluster's old unselected copy
(`layout/ltcg/laser_cut/circle_trim.cpp`) and the stub source are removed. The
asm owner `build_support/exact/game/laser/laser_segment_cut.cpp` stays: two
other regions still use it.

The model went from 274/345 to 345/345 identical instructions. Two separate
causes were behind the residual.

## 1. The SetPolar callee must be visible and must not touch EDX

Retail keeps `&point` / the sample pointer in EDX across the call to
`CutVector::SetPolar` (0x0041F800). That is only legal when the compiler sees a
callee body that preserves EDX. Retail's SetPolar is the original source's
inline-asm `fsincos` routine (`push ecx; mov [esp],ecx; mov eax,[esp]; fld;
fsincos; fmul; fstp [eax]; fmul; fstp [eax+4]; pop ecx; ret 8`): it only writes
EAX and ECX.

With SetPolar bound as an absolute (opaque) symbol, the caller assumes EDX is
clobbered and keeps the pointer in EBX or a stack slot. A plain C++ body gets a
private LTCG convention instead (`this` in EAX), which also breaks
`TrimRectangle`. The context stand-in
`build_support/layout/ltcg/laser_cut/cut_polar.cpp` gives the retail shape in
C++ (no asm):

```cpp
CutVector* CutVector::SetPolar(float angle,float speed) {
 CutVector* volatile self=this;   // push ecx / pop ecx, ECX clobbered
 CutVector* out=self;
 out->x=static_cast<float>(cos(angle)*speed);
 out->y=static_cast<float>(sin(angle)*speed);
 return out;
}
CutVector* (CutVector::*const cut_polar_taken)(float,float) = &CutVector::SetPolar;
```

The member pointer makes it address-taken, so it keeps the public `thiscall`
convention (same lever as the `effect_ring_update` 0x00445620 note). The stand-in
is 36 bytes at 0x0041F800 in the cluster (an anchor, never shipped: the image
keeps `src/game/laser/polar_vector.cpp` there). Under it `TrimRectangle` stays byte-exact
and `CutRectangle` (0x0041EB00) keeps its 1-byte residual.

## 2. x87 operand order follows symbol ids of the point fields

For commutative float `add`/`mul` (c2 opcodes 0x278/0x27A), `OptCmpHashVal`
sorts the children by hash; a symbol leaf hashes to `0x10000 + (id << 5)` and
the larger id is loaded first. Fields of a struct local are split into their
own symbols (parent pointer at `sym+8`, offset at `sym+0x24`, number at
`sym+0x1C`). When the source names a field directly (`point.x`, `point.y`),
the field symbol is created at that statement and gets an early (small) id;
otherwise it is created late. Retail's `point += step` loads `step` first,
which needs the point field ids to be small, so the sample is read only
through `CutVector* sample=&point;` in the loop.

Spellings that ship:

- `int hit_count=0; int count=0;` before `CutVector origin=position;`;
- `int* bucket=&object->render_bucket; *bucket=0;` (store through a pointer
  orders the clear right after the flags store, see
  `msvc-c2-pointer-store-adds-scheduler-edge`);
- the run position `origin+static_cast<float>(start)*step` (scalar first), and
  the cursor advance `position+=step*static_cast<float>(cursor)`;
- `step.z=0.0f;` before `step.SetPolar(...)`, `point=step+position; point.z=0.0f;`.

`step=step*2.0f` and `point=point+step` instead of the compound forms make new
float literals the link cannot bind at retail's pool addresses.

## Cluster changes

`laser_cut.json`: TrimCircle moved from `anchors`/`anchor_roots` to
`functions`/`roots` (with its `source`), the SetPolar absolute symbol replaced
by the stand-in anchor, gaps relaid, and three float literals the body reads
(32.0, 224.0, 16.0) bound by `constant_aliases`. The two split equivalent
layouts now bind SetPolar to 0x0041F800 instead of declaring it absolute;
`laser_circle_split` was re-recorded (236 -> 237 of 302 identical: the visible
SetPolar now lets it use EDX for `&position` where retail uses EBX).

Generator: `build/experiments/goal_2026_10_25/promote_circle_trim.py`.

## Tracer fix

`reference/compiler_traces/operandsort/trace_float_loads.py` cached function
names by the record pointer at `[0x108ab128]`, which c2 reuses for the next
function, and cached failed reads: TrimCircle was skipped silently. The cache
is now keyed by the record and its name pointer, failures are not cached, and
strings are read without crossing an unmapped page.

## Validation

`make` (byte-exact C++ 84.7% -> 85.1%, equivalent regions 18 -> 17),
`make EXACT=1` (SHA-256 `2f14760b6fbbf575…`), `callsite_abi.py`, 127 tool unit
tests, `git diff --check`.
