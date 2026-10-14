# Projectile cell spawner `0x004067D0` — accepted as an equivalent recovery (2026-10-14)

Verdict: 327 of 354 instructions identical, 1,460 of 1,472 bytes used, 17 recorded
differences covering 39 instructions (total budget 118). Structural differences
cover 24 instructions (budget 44): block-order 7, code-shape 17; plus
evaluation-order 14 and alignment-padding 1.

Model: `matching2/msvc/equivalent/game/projectile_spawn_cell_004067d0.cpp`
(renamed from the old `enemy_projectile_spawn_004067d0_model.cpp`). Layout:
`matching2/msvc/layout/equivalent/projectile_spawn_cell_004067d0.json`. The
region already contains its two jump tables, so the extent is unchanged.

## What the old parked model got wrong (semantics)

- **The lit step.** Retail sets `state = 2` and steps the position back by one
  frame of velocity only when shape flag 2, 4 or 8 picks a stop frame (7/8/9).
  The default stop frame 2 skips both. The model did them unconditionally.
  Retail's shared block is the compiler's tail merge of three identical
  branch tails. The source calls a forceinline `SpawnRecord_Light` in each
  branch.
- **The cursor advance.** Retail advances one record (`add ebp,0x7f0`); the
  model advanced two.
- The entry-copy (`*reinterpret_cast<...* const*>(&param)`) and volatile
  manager hacks are gone; plain parameter reads give retail's two hoisted
  loads.

## Context that made the convention right (1476 -> 1460 bytes, 228 -> 327)

- Caller: the real grid scanner 0x4073E0 with its sound-queue anchor, plus a
  synthetic entry (`equivalent/game/context/projectile_spawn_cell_scan_cells_004073e0.cpp`).
- **Script starter 0x404F30 in its own cluster's context**: the compiled script
  loader 0x43E710 takes the index in EBX, so the starter takes it in EAX
  (`push ebx; mov ebx,eax`), and the spawner computes `table[colour] + offset`
  straight into EAX. With the loader as a plain stdcall external, the starter
  flexed the index into EDI, which cost +4 bytes and broke the size gate
  (`equivalent/game/context/projectile_spawn_cell_start_script_00404f30.cpp`).
- The RNG 0x44BB20 and angle 0x44BC10 bodies as context (`src/math/rng.cpp`,
  `src/math/angle.cpp`). The polar setter 0x408750 (GCC-compiled), the
  interpreter 0x406D90 and the animation VM 0x43EE30 are absolute symbols.

## Source shapes

- `Rng_RangeFloat(&rng, hi - lo)` (th06's `GetRandomF32InRange`): the range
  argument is evaluated before the call and kept on the x87 stack across it,
  as in retail. `(hi - lo) * Rng_NextFloat(&rng)` calls first.
- `const float head = blueprint->y_head;` gives the `fld st(0)` / `fsubr st,st(1)`
  interpolation.
- `Vec3& position = record->position;` keeps the position pointer in EDI from
  the copy to the lit step (retail `[edi]`, `[edi+4]`, `[edi+8]`).
- `(float)blueprint->columns` written twice in case 4/5. A `const float columns`
  local made c2 divide by a reciprocal and name an unbound 1.0f constant.

## Remaining differences (recorded)

The loop exit's duplicated `return 1` epilogue (block-order), the operand order
of `velocity * scale`, `flags |= 1` as a register round trip instead of `or`
on memory, the position of the aim term in the case 2/3 and case 4/5 sums,
and one push/store swap before the angle call.
