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
