# Familiar refresh 0x00426F70: accepted as an equivalent recovery (2026-10-14)

`equivalent/game/familiar_refresh_00426f70.cpp` (a wrapper around the cluster
source `src/game/familiar_refresh_00426f70.cpp`) through
`layout/equivalent/familiar_refresh_00426f70.json`: 2,496 of 2,496 code bytes
plus the 24-byte jump table, **641 of 643 instructions identical**, one
recorded `evaluation-order` hunk. The parked model of 2026-10-13 stood at
309/643 by a difflib count; its notes blamed a two-slot argument-home
decision. Most of the distance was the model itself.

## 1. The model was semantically wrong in three places

Re-transcribed from the retail disassembly:

- the applied count lives at player +0x3500 (the model compared +0x34DC);
- the rebuild dispatches with `switch (character) { case 0: …; case 1:
  switch (shot_type) {…} }`. Retail's `sub eax,0; je; dec eax; jne default`
  pairs are switches, so for a character >= 2 the records are only re-anchored
  and marked active. The model used
  `if/else` chains that sent every other character down the second path;
- in the second column the familiar is placed at `anchor + (alternate ?
  focused : carried)` of the *record*, not at a raw schedule row.

## 2. The record layout: 0x98-byte familiars at player +0x32A0

The old view interleaved "slots" at +0x324C with a control block 0xBC
further in, so each familiar touched two strides. The trail-sprite callback
at 0x00427950 sees the same record (position at +0x34, offset at +0x44,
index at +0x88), which pins the real base to +0x32A0: state +0x00, position
+0x34, anchor +0x3C, unfocused offset +0x44, focused offset +0x4C, handle
+0x68, effect handle +0x6C, index +0x88, dirty +0x8C, callback +0x90. The
count at +0x3500 sits right after the four records. Two source facts follow
from this view:

- retail's base register is `player + i*0x98` with the full field offset in
  every operand, so the source indexes `player->familiars[i].field` directly
  (a record pointer folds +0x32A0 into the `lea`);
- the "copy the previous familiar's offset" path reads `familiars[i - 1]`.

## 3. Context: the counters block escapes; the manager does not

`character`, `shot_type` and the power word are members of the address-taken
game counters object at 0x00474C44 (memory note
`msvc-escaped-global-struct-aliasing`). Declared that way, with
`FamiliarRefreshEscape` returning its address, the stores before the
character/shot-type switches stopped being reordered past their reloads.
The animation manager pointer 0x00491C10 has to stay a lone global: as a
Supervisor member it is no longer hoisted out of the call-free stop loops,
while retail hoists it. Read the manager plainly at each use (no volatile).
With the earlier volatile reads, the second stop loop spilled the manager
and kept a constant in a register.

Reading the power through the struct as `const short gauge` widened the load
to 32 bits (one byte that shifted every later alignment filler). Reading
`int power = counters.power` and testing `counters.power >= 100` directly
keeps retail's 16-bit `mov cx`.

## 4. Smaller shape facts

- **desired in the dead argument slot.** Declaring the effect-sweep pointer
  `record = player->familiars` before `desired` lets `desired` share the
  player argument's home (+0x4C) and the counter take +0x10. A local defined
  before the parameter's first read conflicts with that parameter's colour;
  see `msvc-c2-stack-slot-order-by-reference-weight`.
- **Stop loops.** The surplus-stop loop derives the state store from the
  handle pointer (`[edx-0x68]`), so the source takes `&familiars[i].handle`
  and reaches the state through it. It continues the rebuild counter (`for
  (; i < 4; ++i)`).
- **Point copies.** `CopyFrom` (the trail sprite's own idiom) for the anchor
  copy at the loop top and for the previous-offset copy, plus a named
  `position` local copied into position and anchor, give retail's
  load/store order. Plain struct assignment forwards and interleaves the
  stores.
- **Row pointers.** Schedule rows are 12-byte `{x, y, z}` records; one helper
  scales a row into a record offset (`fld [row]; fmul [half]` stays in that
  order through the volatile row floats).

## Remaining difference (recorded)

At 0x4272D7 (third column, rebuild of an idle familiar), retail loads
`anchor.x` before `carried.x` and the model loads them the other way round.
The y pair matches. Pointer-local removal, operand swaps, explicit int
locals, a constructor temporary, a record pointer and `CopyFrom` all leave
it unchanged. It is the commutative-operand hash tie-break of
`msvc-c2-operand-order-mechanism`. Next lever if anyone wants it exact:
trace OptCmpHashVal for that add in the cluster and shift the temporary
count, then register the cluster `layout/ltcg/familiar_refresh_00426f70.json`
as a semantic region.

## Method

`equivalence.py --layout` on the draft layout (about 2 s per build) plus a
difflib comparison of model and retail instruction text. Each hypothesis was
a list of text replacements applied to the source and measured in one batch.
