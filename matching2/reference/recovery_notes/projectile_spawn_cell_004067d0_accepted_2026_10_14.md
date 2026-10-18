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

## 2026-10-17: state reviewed; parked

The 17 hunks are the five recorded residuals the list above names (the
duplicated return epilogue's block order, the `velocity * scale` operand
order, the `flags |= 1` register round trip, the aim-term position in the
case 2/3 and 4/5 sums, and the push/store swap before the angle call). Each
already sits at the end of a documented lever chain: the operand order is
the memory-operand canonicalization, the aim-term position is the x87
schedule, and the flags round trip is the load/or/store split the model
needs for its other constraints.

Region stays equivalent (1162 differing bytes).

## 2026-10-18: residual chains closed down to the product operands

15 of the 17 hunks are gone (1,150 differing bytes -> 24; 348/354 identical;
the body now fills the 1,472-byte region exactly and the tail is clean).

Levers that closed bytes, in order:

- **Scan loop as `do { ... } while (attempts < 2000);`** with the post-loop
  `if (attempts >= 2000) return 1;`: the loop-exit test now falls into its own
  return-1 epilogue copy and the break join keeps the second copy, matching
  retail's duplicated epilogues (hunk @0xe2, 735 bytes left).
- **`record->flags |= 1u` written after the timer_3f8 block**, the two timer
  resets through one `int*` words view per timer (configure.cpp spelling,
  block order [1][2][0] and [0][1][2]), and the record flag/state updates
  through pointer locals before the timer checks: the RMW folds to
  `or [mem],1` and the may-alias edges keep the timer flag loads behind the
  stores (hunks @0x2af-@0x306, 164 -> 80 bytes).
- **Per-statement `x +=` accumulation** in the case 2/3 and 4/5 sums (the same
  rounded operation sequence as the left-associated sum) plus `const float
  half_step = flt_pi / cols;` as its own statement: retail's x87 evaluation
  order returns (hunks @0x1bd-@0x213, 80 -> 33 bytes).
- **`(void)&flt_4;` early in the function**: orders flt_4's symbol among the
  function's temporaries and unpicks the hoisted constant load before the
  `state = 2` store (33 -> 24 bytes).

Ruled out (all bit-identical to their base, ~110 spellings): operand source
swaps in the Vec3 operator; accessor/operator/ctor spellings; pointer,
reference and named locals at the use; statement-split products; helper
parameter shapes (order, ref/value, extra params); extern declaration order;
first-use permutations; empty loops and other code that emits nothing; dead
references to any global except flt_4; live-across pointer locals; member
accessors at five earlier positions.

Remaining: 1 hunk at 0x49f (24 bytes). The lit step's three products
`record->velocity.{x,y,z} * flt_4` load the constant first
(`fld ds:0x470c40; fmul [ebp+0x3cN]`) where retail loads the component first
(`fld [ebp+0x3cN]; fmul ds:0x470c40`). The operand order is canonicalised
from symbol classes (OptHashNode `0x10008 + ((id & 7) << 13)` on the load
bases; the product pairs share flt_4's low-numbered symbol against the
components' late address temporaries) and no source spelling moved it. This
is the same family as the open x87 memory-operand swaps
(projectile_point_count, 0x00408210).

### 2026-10-19: the addend as a literal — EXACT

`variant.py` `*EXACT*` (354/354 instructions, 0 differing code bytes, 0 tail);
`equivalence.py` `"differences": []`, `"not_equivalent": []`,
`base_index_order: 0`, `frame_offset: 0`.

The closing lever is the same one that closed `front_hud_update` the same day:
**write the scale as a literal** in the lit step,

    const Vec3 shift = record->velocity * 4.0f;

instead of `* flt_4` (an external `float` at 0x470C40). The compiler then pools
its own `__real@40800000`, which has a different symbol class from an extern
object, so the operand hash no longer ties and the emitter produces retail's
`fld [component]; fmul ds:0x470C40` order for all three products. The layout
gains the binding `__real@40800000` -> `0x00470C40`; `differences` is `[]`.

Ruled out before this (all bit-identical, ~110 spellings): operand source
swaps, accessor/operator/ctor spellings, pointer/reference/named locals at the
use, statement-split products, helper parameter shapes, extern declaration
order, first-use permutations, empty loops, dead references to other globals,
live-across pointer locals, and member accessors at five earlier positions.
The lesson recorded for the remaining x87 parks: an extern `float` operand can
always be replaced by its literal, which changes the symbol class the operand
hash sorts on.
