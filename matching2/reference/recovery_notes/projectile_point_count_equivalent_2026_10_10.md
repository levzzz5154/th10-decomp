# 0x004084A0 projectile point count: equivalent recovery, 2026-10-10

`ProjectileManager::CountNearPoint` weighs the projectiles that have a corner
within a radius of a point (weight 1 for sprites up to 16 wide, 4 up to 32, 10
up to 64). Nothing in retail calls it or takes its address. The C++ is
`matching2/msvc/equivalent/game/projectile_point_count_004084a0.cpp`: 120 of
126 instructions identical, same frame, same registers, 358 bytes against 370.

## What decided the shape

- **The four corners are one `Vec3 corner[4]`** in the order top-right,
  top-left, bottom-left, bottom-right (retail slots 0x08, 0x14, 0x20, 0x2C).
  Four separate vectors are split into scalars and the frame shrinks to 0x24.
- **The array is declared at function scope**, outside the loop. Inside the
  loop body the pointer that walks the records is based at `position` instead
  of `width` (`add ecx,0x414` against retail `add ecx,0x450`).
- **Field-wise corner setup and copies.** A struct copy (`corner[2] =
  corner[1]`) moves the floats through integer registers; vector operators
  spill a `half` temporary.
- **The distance test is one direct expression**,
  `(a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y)`, in an inline helper
  taking references. That is what lets the squared x distance be shared by the
  two corners of each side (kept on the x87 stack for the left side, spilled
  for the right). A helper with a difference vector or named `dx`/`dy` locals
  shares only `dx` and squares it again per corner.
- Four `distance > reach` conditions joined by `&&` with `continue` give the
  `test ah,0x41 / jne` chain; the size classes are plain `<=` comparisons.
- The private convention (manager ECX, point EDI, radius on the stack) comes
  from any direct caller that passes the point from a walked array.

## The residual

Retail stores `corner[1].y` and `corner[0].y` (`fst`), computes
`corner[2].y` from the still-extended value, then reads both back from memory
for `corner[0].y -= height` and for the first distance. The model keeps both
values on the x87 stack (`fld st(2)`, `fsub st,st(2)`, `fstp st(1)`) and never
stores them. Five listed differences, all `code-shape`.

Spellings that all compile to the same 358 bytes: every statement order of the
copies and the two adjustments; `c2.y = c1.y + h` against copy then `+=`;
pointer and reference helpers for the adjustment; a `float*` view in the
distance helper; a user-defined field-wise `operator=`; explicit `(float)`
casts; a pointer alias of the array. Double arithmetic for the y values
(`* 0.5`) does force the store and reload, but with a qword constant and a
rounded `corner[2].y`, so it is not the retail source either. A store through
a genuinely variable index makes the whole array memory, x included, which
retail does not do: its top-left x is never stored.

Next lever if this is revisited: find what makes the compiler treat the two
y values as memory while x stays an x87 candidate; the sibling sweep at
0x00408210 shows the same asymmetry (half width on the stack, half height
spilled to `[esp+8]`), so solving one should solve the other.

## 2026-10-17: declared-then-assigned y lever probed; parked

The `msvc-declared-then-assigned-result-keeps-float-locals` form applied to
the corner y computation (`float half_y; half_y = size.y * 0.5f;`) leaves
the five code-shape hunks unchanged: the y values are array-element stores
the compiler forwards over, not declared locals whose assignment shape
selects the memory home. Consistent with the note's "a store through a
genuinely variable index makes the whole array memory, x included" — the
asymmetry (y in memory, x on the x87 stack) is still the unexplained
residual shared with 0x00408210.

Region stays equivalent (281 differing bytes).

## 2026-10-17: the x87 storage levers tested negative

HANDOFF's frame_timer lever ("volatile on storage forces retail's x87 operand
order") was applied here directly, plus four ways to force the y values through
memory. Eleven variants, measured with the byte script:

- `volatile` on the whole `corner` array does not compile (it cannot bind to
  the distance helper's `const Vec3&`); `volatile` on a named y local gives
  87/126, a draft far worse than baseline;
- a `volatile Vec3*` alias over the array (all accesses, or the y stores only)
  either fails to link or lands at 114/126;
- `_ReadWriteBarrier()` fences after/between the stores need `<intrin.h>`,
  which this unit does not include, and the aggregate-store spelling fails
  because `Vec3` has user-defined constructors;
- naming the two y values, reading them back, and reloading explicitly all
  reproduce the baseline exactly (120/126, 5 hunks, 281 differing bytes).

So the residual is not the assignment shape: retail's stores land in memory and
the model's stay on the x87 stack, and none of the storage-visibility levers
move that. The asymmetry noted above (y in memory, x on the x87 stack) is still
unexplained. Region stays equivalent.

## 2026-10-18: byte-exact — re-derived corner[2].y and its statement position

The residual x87 y-in-memory/x-on-stack asymmetry is closed: 126/126
instructions, 370/370 bytes, `equivalence.py` reports `differences: []`,
`not_equivalent: []`, `base_index_order: 0`, `frame_offset: 0`. Two source
shapes do it, both about corner[2].y:

- `corner[2].y = record->position.y - record->size.y * 0.5f + record->size.y;`
  re-derives the halved difference instead of reading `corner[1].y` (or the
  `corner[2].y = corner[1].y` copy then `+=`). The shared extended value is
  consumed in place by the add (`fst DWORD PTR [esp+0x18]` keeps it, `fxch
  st(1); fadd [ecx+0x4]` eats it), so the first distance reloads the stored
  float (`fsub DWORD PTR [esp+0x18]`) exactly like retail. The old spellings
  kept the value on the x87 stack for both uses — that was the residual.
- That statement sits between the `corner[3].y = corner[0].y` copy and
  `corner[0].y -= record->size.y`. There the scheduler emits the corner[0].y
  store pair (`fst [esp+0xc]; fstp [esp+0x30]`) before the corner[2].y add and
  reloads the rounded corner[0].y for the adjustment (`fld [esp+0xc]`). In any
  other position the two independent blocks swap (256 differing bytes) or the
  corner[0].y store sinks past the adjustment.

Ruled out with byte counts (variant.py sweeps, ~130 spellings):

- Statement order of the defs/copies/adjustments in every permutation except
  the winning one: 256–296 differing bytes; `corner[2].y` first or last-but-one
  swaps the two blocks, `corner[2].y` adjacent to the corner[1].y def does not
  help.
- `* 0.5f` vs `/ 2.0f`, `/ 2`, named `float`/`double` half locals,
  declared-then-assigned halves and result ys: 281–286, no movement (the
  double-constant family was already ruled out on 2026-10-10: it forces the
  store/reload but with a qword constant and a rounded corner[2].y; the
  `__real@3f000000` binding must be replaced to even measure it, since the
  model then emits `__real@3fe0000000000000`).
- Sibling 0x00408210 transplant spellings (operand-swapped high sides, block
  groups): 281.
- Block boundaries (`for (int i = 0; i < 0; ++i) {}`) at each gap: either the
  281 baseline or the 256 block-swap, never the target order.
- Pointer stores / `SetY(float*, float)` helpers on each y store (scheduler-edge
  lever): no movement (256/3 hunks unchanged).
- Named square temporaries and `dx`/`dy` locals in the distance helper
  (unchanged 281), vector/refs element spellings (281), loop-scope array
  declaration (281).

Partial levers found on the way (kept here because they name the mechanism):
volatile reads of the corner y in the distance helper force the missing stores
to materialize (49 differing bytes — everything aligned, only in-place x87
choices wrong), and a volatile-ref or `*(volatile float*)&corner[0].y` adjust
fixes the corner[0].y store pair on its own. Neither is needed by the final
spelling; the re-derived expression achieves both shapes from plain C++.
