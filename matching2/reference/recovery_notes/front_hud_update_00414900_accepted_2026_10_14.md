# Front HUD update 0x00414900: accepted as an equivalent recovery (2026-10-14)

`equivalent/game/front_hud_update_00414900.cpp`, built through
`layout/equivalent/front_hud_update_00414900.json` with
`src/game/front_script_tick_00415e90.cpp` as context. Result: all 3,836
bytes, **1,064 of 1,089 instructions identical**, 22 recorded hunks (block-order 18,
evaluation-order 10, code-shape 7, alignment-padding 2). The structural
weight is 25. The parked model stood at 502.

## Semantic fixes (the bulk of the distance)

- **The dispatcher takes the sequence runtime.** Retail pushes
  `front->sequence_9eb8` (ESI) into 0x415E90. The model passed `front`.
- **The notice-slot loop runs only while the boss gauge is active.** It
  follows the pending-banner create inside the gauge branch. The inactive
  branch flags the pending banner, clears the gauge fields and goes
  straight to the sequence tick.
- **The 0x474C84 progress counter is signed** (`jl`/`setge`). The shared
  header declares it unsigned, so the switch casts to `int` at each read,
  and retail reloads it at each read.
- **The gauge flag test.** `if (flags & 8)`: the stop-frame-2 (close) path
  falls through, and the stop-frame-3 (open) path is the branch target.

## Shape facts

- **Drop the ABI-freezing roots.** Only the 0x415AE0 callback stays
  rooted. Rooting every helper froze their declared ABI (502 -> 579).
- **The resource pointer is read before `Allocate`** in both creates.
  Retail keeps it in a callee-saved register across the call. For the
  slot-loop create, this single change took the count from 674 to 995.
- **Stop frames are a plain `unsigned short` local** shared by the node and
  its children (retail's `mov ecx,N` reused in the children loop). They are
  not a volatile slot.
- The list registration mirrors 0x4489D0 (`tail->next->previous = node`).
- Gate word: `~(flags >> 4) & 1`, then `~flags & 1`. The difficulty lane
  `(flags >> 1) & 3` is recomputed inside each state branch.
- Boss alpha: `if (offset >= limit) alpha = 0xFF; else ...` (retail's
  fall-through is the 0xFF store).
- The pending stop-frame-2 call is `if (pending) Flag(pending);` followed by a
  single shared `flags &= ~8`.
- Slot index: `unsigned` with an `(int)i < count` test (retail `jb` on the
  ten-slot bound and `jge` on the count).

## Remaining differences (recorded)

- The next-id wrap: retail copies the incremented id to a second register,
  tests it and `inc`s the copy. The model stores the constant 1. The
  standalone 0x4489D0 has the same retail shape. Six source forms all
  give the model's shape inside this function.
- The sequence-slot clear stores (`slots[k] = 0`) are scheduled one load
  later.
- Two `fadd` operand orders and a `test byte [mem]` loaded into `cl` first.

## 2026-10-17: the standalone 0x4489D0 spelling probed; parked

The wrap spelling of the byte-exact sibling 0x004489D0
(`animation_manager_register_primary_back.cpp`: `++next_id; if (next_id == 0)
++next_id;` with the field incremented in place) was transplanted here
through the `lists` pointer: 26 hunks, worse than the shipped 22. The
sibling's register context (the direct member on `this`) is not this
function's (`AnimationListSet* lists`), consistent with the note's six-form
result.

Region stays equivalent (684 differing bytes).

## 2026-10-18: three semantic/codegen families closed; two operand-order residuals recorded

Measured 22 hunks / 684 differing bytes -> **2 hunks / 16 differing bytes,
1,085 of 1,089 instructions identical**. The layout records the two residuals as
`operand-order`. `equivalence.py --name front_hud_update_00414900` passes:
0 base/index swaps, 0 frame-offset, `not_equivalent: []`.

### Levers that closed the differences

- **Next-id wrap (6 hunks: the two sites plus three rel8 targets and two pads).**
  The 0x4489D0 spelling only works here with a *value-returning* wrapper:
  `struct AnimationRef { unsigned value; unsigned operator++() { return ++value; }
  bool operator==(unsigned) const; }` as the `next_id` member, wrap text
  `++lists->next_id; if (lists->next_id == 0) ++lists->next_id;`, tail reads
  `lists->next_id.value` (retail reloads twice). The value-returning `operator++`
  is what makes c2 copy the increment into the return register and test/inc the
  copy (`mov eax,ecx / test eax,eax / inc eax`), while the wrapper member access
  keeps the guard from constant-folding to `mov [mem],1`. The literal sibling
  spelling (reference-returning `operator++`) gives 18 hunks / 555 bytes here;
  plain-unsigned forms (named copy, `old + 2` guard, memory re-reads, field
  pointers) all fold the guard. This closes the note's "six source forms" residual
  and confirms the overnight finding: the spelling is right, its interaction with
  this region's `AnimationLists* lists` context needed the value-returning variant.
- **Sequence-slot clears (5 hunks, 0x92f..0xb1b).** Clear through a reference
  helper (`FlagAndClearSlot(unsigned int& slot)`) or per-slot pointer locals; the
  store then keeps the alias edge and stays before the next slot's load. Plain
  member stores hoist after the next load; an array pointer form folds back.
- **Gate-word test (0xceb/0xcf8 + ~450 bytes of displaced branch displacements
  plus the 0xedd pad).** Load `front->flags_9eb4` *inside both* lane branches
  instead of once before the test. CSE merges the two loads after the byte test,
  the test fuses to `test BYTE PTR [edx+0x378c],0x1` and the knock-on pad at
  0xedd reverts to retail's `lea ecx,[ecx+0x0]`.
- **St5 (shape only):** writing the `y_340` store before the `height_344` store
  merges the boss-fade hunk pair into one recorded difference; the pair stays open.

### Ruled out for the remaining residuals (both `fld A; fadd B` operand order)

The gauge ramp (`front->gauge_disp_9e84 + flt_0_025`, 0x222) and the boss fade
(`body->boss_y_1068 + flt_224`, 0xdda) load the constant first; retail loads the
member first. Measured unchanged by: source operand swaps (`a + b` vs `b + a`
byte-identical), `+=` vs `a = b + a`, named value locals (at/around the statement,
chained, reversed declaration order), pointer/reference locals and their removal,
value/pointer/reference inline helpers in either parameter order, value-returning
accessors, nested casts/muls/adds (these shift the two frame-ramp pairs PB/PD with
period 3 but never PA/PC), dead code, extern declaration order, split reused
pointer locals (`seq`, `runtime`), statement reorders (only relocate the hunk),
bitfield/typed/direct test forms. The operandsort tracers show the two ramp pairs
are hash-sorted via OptCmpHashVal while these two never appear there; the pairs
are immune to every global shift, consistent with tied hash classes where "a tie
keeps the existing order". The remaining lever class is a relative movement of the
two operands' creation order that no constructed spelling produced.

### 2026-10-18 late: bounded creation-order pass on the two operand-order pairs — negative; parked at 16 bytes

Following the campaign's node-creation-order levers (title_dispatcher's rotation,
ui_final's temp-creation swap), 14 byte-gated variants hoisted the operands'
first mentions: the constant local `float step = flt_0_025;` at function start,
at the gauge-block start, immediately before the comparing `if`, and inside the
ramp block; the field load `float d = front->gauge_disp_9e84;` hoisted the same
ways, both declaration orders, with the compare on the local or on the memory
read; the mirrors for the boss fade (`float y`/`float k` between the `height_344`
store and the `y_340` store, both orders; `float anchor = flt_224` at function
start); and both sites together. None changed either pair's operand order.
Function-start hoists additionally break the two frame-ramp pairs (23 hunks);
statement-adjacent hoists break them mildly (3-4 hunks, 23-27 bytes) or are
byte-identical. Correction to the entry above: the st3 if-block swap does NOT
flip the gauge pair — it relocates the same `fld [const]; fadd [member]` order to
the moved block (measured hunk at 0x247 with the const-first order intact).

Conclusion: the two pairs' operand order is decided by tied hash classes whose
tie-break ("the existing order") is invariant under operand swaps, operand kinds
(temp/local/global/param), helper indirection, and first-mention/creation-order
hoists. Parked as two recorded `operand-order` differences (4 instructions).

### 2026-10-18 (round 2): literal addends close both pairs — EXACT

`variant.py` `*EXACT*` (1,089/1,089 instructions, 0 differing code bytes, 0
tail); `equivalence.py` `"differences": []`, `"not_equivalent": []`,
`base_index_order: 0`, `frame_offset: 0`.

The closing lever is the **spelling of the two float addends**: `flt_0_025`
and `flt_224` are replaced by the literals `0.025f` and `224.0f`.

    front->gauge_disp_9e84 = front->gauge_disp_9e84 + 0.025f;
    front->objects[22].y_340 = body->boss_y_1068 + 224.0f;

Why it works: the operand-hash rule (`msvc-c2-operand-order-mechanism`) gives a
compiler float literal (`__real@...`) a *different symbol class* from an
external `float` object, so the hash comparison against the member load no
longer ties; the literal sorts as the second operand and the emitter produces
retail's `fld [member]; fadd [literal]`. With the extern symbol the two hashes
are equal and the tie-break keeps the model's order — which is exactly the
invariance the 2026-10-18 bounded pass measured for every source spelling.

The layout gains the two compiler-literal bindings the literals resolve to:
`__real@3ccccccd` → `0x00470CF8` and `__real@43600000` → `0x00470B4C`.
`differences` is now `[]`.

Ruled out earlier this round (measured, all 16 bytes): source operand swaps,
`+=`/`a = b + a` forms, named value locals, reversed declaration orders,
operator/ctor spellings, nested casts, named pointer locals and their removal,
statement reorders, dead locals, global declaration-order changes.
