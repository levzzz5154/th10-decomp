# ItemUpdate 0x0041AFD0 as an equivalent C++ model (2026-10-13)

**Current status (2026-10-14): C++ repaired and registered; current validation is listed in the execution investigation.** The historical measurements below are superseded by [the execution investigation](equivalent_runtime_failures_2026_10_14.md).

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

## 2026-10-17: state reviewed; parked

The 64 hunks (down from the recorded 84) are the same families the class
list names: the register contest (25, the idle-constant/player/slot/argument
staging), the x87 product scheduling (19), the frame colours (8, the 0x2c
against retail 0x58 — the stack-slot weight rule again), and the merged
tails (6 branch-target). Each is a trace-guided lever family already
documented; no new source spelling applies.

Region stays equivalent (1991 differing bytes).

## 2026-10-17: the frame gap is one 8-byte slot, and `volatile double` closes it

The first hunk is `retail sub esp,0x58` against `model sub esp,0x50` — the
frame is exactly **8 bytes** short, the same gap `joystick_poll` shows
(`0x154` against `0x14c`). This function computes two `double` planar
products, and the file already spells x87 control with `volatile`
(`volatile float dz`, `const volatile float& stored_y`).

Marking just one of the two products `volatile double` closes the gap and
improves the match materially:

| spelling | identical | hunks | differing bytes |
| --- | --- | ---: | ---: |
| baseline | 494/601 | 64 | 1,983 |
| **`volatile double dx`** | **505/601** | **62** | **1,769** |
| `volatile double dx` + named `volatile float` sum | 507/601 | 62 | 1,953 |
| `volatile double dx` + split additions | 504/601 | 62 | 1,771 |
| `volatile double dx` reordered with `dz` | 505/601 | 62 | 1,770 |
| both products `volatile` | 494/601 | 63 | 2,002 |
| `volatile double dx` + `const volatile double& dy` | 494/601 | 63 | 2,002 |

With `volatile double dx` the `sub esp` hunk disappears entirely and the body
fills its full 2,320 bytes (it was 2,312). Forcing *both* products to memory
overshoots by the same 8 bytes, so the slot is one 8-byte home, not two.

This is the first lever this pass has found that moves a region by more than a
hunk or two. It is not landed: the model is still equivalent at 62 hunks, and
shipping it would mean re-recording the whole difference list for a partial
improvement. The next session should start from `volatile double dx` and work
the remaining 62, which now begin at +0xa (`retail xor ecx,ecx` against
`model push edi; xor edi,edi`) instead of at the prologue. Region stays
equivalent.

### Later precision check: keep the volatile-double experiment unshipped

The retail body has no `fst`/`fstp` qword stores. Forcing a volatile double
may introduce a 64-bit rounding point that the retail x87 expression does not
have. Closing the frame-size gap alone does not establish equivalent
floating-point behavior. Inspect the candidate stores and rounding before
using this experiment as a recovery baseline; the maintained source remains
unchanged.

### 2026-10-18: the frame gap is the fourth displacement aggregate; steering line recorded

The 8-byte frame gap was the state-1 falling block's integration. Retail spells
it like `IntegrateItem` (a 12-byte `Vector3Value displacement` aggregate whose
only emitted store is the dword `fstp` of the z product), while the model used
`double dx/dy + volatile float dz`, producing one 4-byte `dz` home instead.
Replacing the block with `IntegrateItem(motion)` closes `sub esp,0x50` ->
`0x58` **without any qword floating-point store**: the new home is the
aggregate's z member (`fstp DWORD` at 0x40), exactly retail's form. The
`volatile double dx` experiment is thereby ruled out — retail has no
`fst`/`fstp qword`; its four z homes at 0x40/0x4c/0x58/0x64 are the four
displacement aggregates' members.

Frame colours now match retail exactly: two 12-byte `Vector3` point copies
declared at the collect test (x/y homes at 0x20/0x24 and 0x2c/0x30, z members
never touched at 0x28/0x34) feeding the four terms of
`OutsideItemBox(min_x,min_y,max_x,max_y,box)`; `short focused2` keeps focused
out of the frame and restores retail's `test cx,cx` re-test at the magnet
fail-edge join; `seek_player:` moved above `player=g_player;` reproduces
retail's duplicated seek setups (merged-tails family).

New lever recorded: **the `g_globals` staging** (7 sites of retail
`mov edi,0x474c40` against model `mov edi,eax`). c2 chains the this value
between two calls spelled with the same expression through the previous call's
preserved argument register, and rematerialises across different spellings;
retail chains only once (`mov ecx,edi` at case 8, through callee-saved EDI)
and rematerialises everywhere else. A selective receiver alias
(`ItemRunState& run=g_globals;` — `run` at the AdvanceGaugeTimer sites, case 2
spelling AdjustPower/AddScore/Advance alternately, case 8 spelling its
AdvanceGaugeTimer/AddScore pair alike) reproduces retail's pattern exactly
with live code; the earlier clobbering-ghost-body probe is withdrawn. A named
`int gauge=g_globals.gauge;` in case 2 (the same value read twice with no call
in between) restores the `mov eax,[0x474c4c]` short form and brings the body
to retail's exact 2,320-byte extent.

Recorded line (layout `equivalent/item_update.json`, 33 differences reviewed):
554/601 identical, 0 base/index swaps, 3 frame-offset, 2,320 of 2,320 bytes
used, 1,776 differing bytes (baseline 494/601, 64 hunks, 1,983), gate clean.

Remaining families, all register-allocation or scheduling:

- the zero (`idle`) sits in EDI; retail keeps it in ECX and uses immediate
  stores in the call-clobbered tails. This is the Riscify immediate-rewrite
  rotation plus ChoosePhysReg tie costs; the EDI-only avail set follows from
  the zero's live range spanning the calls (the register-form tail stores
  extend it). Ruled out: idle/seeking types, literals, declaration position,
  statement order, pointer candidates, focused typings.
- the SetPolar staging and the seek-setup copy registers (one register off),
  the gauge-load register, and the state-4 tail: retail merges one copy of the
  `if (player->state==4)` action where the model keeps two (they differ in the
  zero form and the pointer register).
- three x87 operand orders (`magnet_speed += flt_0_2`, the seek-speed product,
  the TickInline add) and the case-2 penalty chain's position resist every
  spelling tried (+=, x+c, c+x, named temporaries on either side, hoisted
  reads).

### 2026-10-18: frame colours + g_globals steering + stream alignment (900 bytes)

The 8-byte frame gap was the state-1 falling block's integration: retail spells
it like `IntegrateItem` (a 12-byte `Vector3Value displacement` whose only
emitted store is the dword `fstp` of the z product), the model used
`double dx/dy + volatile float dz`. `IntegrateItem(motion)` closes
`sub esp,0x50` -> `0x58` without any qword floating-point store; the
`volatile double dx` experiment is ruled out (retail has no `fst`/`fstp qword`;
its four z homes at 0x40/0x4c/0x58/0x64 are the displacement aggregates'
members). Frame colours match retail exactly: two 12-byte `Vector3` point
copies at the collect test (z members untouched at 0x28/0x34) feeding
`OutsideItemBox(min_x,min_y,max_x,max_y,box)`, `short focused2` keeping focused
out of the frame with retail's `test cx,cx` re-test join, `seek_player:` above
`player=g_player;` reproducing retail's duplicated seek setups.

Two further levers recorded this pass:

- **g_globals staging**: c2 chains the this value between two calls spelled
  with the same expression through the previous call's preserved argument
  register (`mov edi,eax`) and rematerialises across different spellings;
  retail chains once (`mov ecx,edi`, case 8, through callee-saved EDI) and
  rematerialises the other 19 sites. A selective receiver alias (`ItemRunState&
  run=g_globals`) reproduces that pattern exactly in live code. A named
  `int gauge=g_globals.gauge;` in case 2 restores the `mov eax,[0x474c4c]`
  short form and lands the body on retail's 2,320-byte extent.
- **stream alignment**: the seek-action tails written through
  `motion->velocity` directly (the pointer local out of those blocks) and the
  case-2 penalty chain split as `float scaled=(y-flt_144)*flt_0_003289474;`
  align the instruction streams with retail — the remaining differences are
  one-byte register/opcode diffs instead of shifted runs. 1,776 -> 900
  differing bytes.

Recorded line (layout `equivalent/item_update.json`, 33 differences reviewed):
549/601 identical, 0 base/index swaps, 3 frame-offset, 2,320 of 2,320 bytes
used, **900 differing bytes** (baseline 1,983), gate clean.

Remaining 33 differences (49 instructions): the zero (`idle`) in EDI against
retail's ECX (register-choice, ~14 hunks — the Riscify immediate-rewrite
rotation; its EDI-only avail set follows the live range spanning the calls),
the SetPolar/seek-setup/gauge-load registers (register-choice, ~13), the
state-4 tail (code-shape x2: retail merges one copy of the
`if (player->state==4)` action; the model's copies differ in the zero form and
the pointer register), two `fld/fadd` sums (operand-order), the magnet-tail
load order (evaluation-order x3), two jmp offsets (branch-target). Ruled out
this pass: goto-shared tails (both directions, 2,000+ bytes), the zero-store
forms (int literals, int puns, per-block zero defs — all inert), the
named-argument rotation at SetPolar (propagates away), the state-variable
split without stream alignment (adds 4 bytes), the hoisted velocity pointer
(2,100+ bytes).

## 2026-10-19: float constants as literals

Writing every float constant of `item_update.cpp` as a literal instead of the
address-named externs (`flt_0_2`, `flt_12`, `flt_0_33333334`, ...) reads the
same retail cells through `__real@` bindings and changes their symbol class:
the two `fld [ebp+0x38]` / `fadd 0.2f` operand-order hunks at +0x2BA/+0x342
close and the +0x814 store-order hunk shrinks to one moved store. 549 -> 555
of 601 identical, 33 -> 31 hunks, 900 -> 894 differing bytes. Found with
`tools/matching/literal_sweep.py`; the replay_sync run of replay 1 stays
identical to retail's trace (11,745 frames).
