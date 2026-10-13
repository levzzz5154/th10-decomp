# ItemUpdate 0x0041AFD0 as an equivalent C++ model (2026-10-13)

**Status: accepted equivalent-recovery draft.** `equivalence.py` verifies the model with no
gate reasons: 448 of 601 instructions identical, 2,284 of 2,320 bytes used, 0 base/index
swaps, 22 frame-offset instructions, 131 instructions in 84 recorded differences
(structural 68 of 601 = 11.3%, budget 12.5%; total 183 of 601 = 30.4%, budget 33.3%).
The layout is `layout/equivalent/item_update_0041afd0.json`; it stays unregistered until
the orchestrator adds `{"region": "asm_FUN_0041afd0_0041afd0",
"layout": "layout/equivalent/item_update_0041afd0.json"}` to `equivalent_recoveries`.

## Model

`equivalent/game/item_update_0041afd0.cpp` — the complete 2,198-slot pool walk: idle
short-circuit, delayed script activation (state 5, kind + 374), falling integration with
retail's extended-precision planar adds and binary32 Z boundary, player-seeking with the
FPATAN angle and the π/2 degenerate case, magnetized pursuit, the collection box with the
kind switch (power/point/retirement payouts), the focused/unfocused magnet boxes, the
animation tick, the frame-timer expansion and the terminal ConvertItems tail call.

## What made it converge

The BLOCKED note's lever — native LTCG with the real scene caller, production state
layout and helper prototypes — plus four nonobvious source shapes:

1. **Genuine helper graph as one translation unit.** The context TU includes the complete
   `item_collection_runtime` graph *minus the former unselected update body*, so every
   helper keeps exactly the region's own call sites. The whole-program link then derives
   each retail private convention from those sites: script index in EAX and entity in ESI
   for `Entity_StartScript`, HUD owner in ESI for `SetPowerDigits`, run counters in EAX
   for `AddPower`/`AddLives`/`AdjustPower`, converting manager in ESI for `ConvertItems`,
   and the collection point in EAX for `AngleFromPoint`. Twelve helper symbols are bound
   to their retail addresses through `bindings`; the two assembly callees
   (`ItemCollector_PowerChanged`, the ANM tick) and `__ftol2` arrive as absolute code.
2. **Y-anchored motion view.** Retail keeps EBP at `position.y` for the whole walk, so
   every displacement is +4 from the record base. The model iterates a view struct whose
   first member is `position.y` (state at +0x2c, timer at +0x18, variant at +0x3c), with
   `position.x` one float below the anchor. This one change moved the measurement from
   49% to 66% identical on its own.
3. **Case blocks in retail's emission order.** MSVC 7.1 emits switch bodies in source
   order; retail's jump-table targets run 1, 2, 5, 3, 8, 9, 4, 7 — the original source's
   case order. Reordering the switch to that sequence removed the 76-instruction
   block-relocation hunk cluster and brought the total under budget.
4. **Loop and box spellings.** A `step:` label shared by every `continue` and the body
   tail reproduces retail's single `dec/jnz` back edge, and `OutsideItemBox` taking the
   point coordinates as floats reproduces retail's four stack-slot temps for the
   collection and magnet box tests.

## Recorded differences (84 hunks, 183 instructions)

- 48 `register-choice` (idle constant in EDI against retail ECX, player in ECX against
  EDX, item slot against register, the SetPolar/AngleFromPoint argument staging).
- 14 `evaluation-order` (x87 product scheduling in the two falling branches, the gravity
  and seek-speed constant/variable loads, the state-2 penalty chain).
- 10 `code-shape` (the merged seek tail with the state-4 test inlined, the focused-box
  test sequence restructured, x87 fxch padding).
- 6 `branch-target` (branches entering the differently merged magnet and retire tails;
  every destination was checked to run the same instructions).
- 3 `operand-order`, 2 `stack-slot-order` (the 0x2c frame against retail 0x58), and
  1 `alignment-padding` (`nop` against `lea ecx,[ecx+0x0]` before the jump tables).
- 22 further frame-offset instructions are recognized by the recorded `frame_shift`
  deltas rather than listed.

`code_bytes` is 2256: the three bytes of `lea ecx,[ecx+0x0]` table alignment count as an
instruction on both sides, and the 64 jump-table bytes agree entry for entry.

## Verification

```
PYTHONPATH=. python3 matching2/tools/matching/equivalence.py \
    --name item_update_0041afd0 --output matching2/build/probe-itemupd
```

after the orchestrator registers the recovery (the layout references the assembly region,
which keeps its exact-link source). Note `--layout`/`--record` runs always print the
structural-budget line because unclassified hunks are held to the structural budget; the
registered check applies the recorded classes and passes.

## Semantics provenance

The body is the long-validated complete item-update candidate (405 bounded
retail/native execution comparisons, see
`item_update_collaborators_0041afd0_2026_10_06.md` and the precision follow-up)
restructured with semantics-preserving spellings: case reordering, value-identical
π/2 immediate (retail materializes `0x3FC90FDB` instead of loading `0x00470B94`),
float-argument box helper, and the label-based loop tail. The volatile Z displacement
and the stored-Y read that guard retail's binary32 boundaries are unchanged.
