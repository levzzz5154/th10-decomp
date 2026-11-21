# ItemUpdate 0x0041AFD0 as an equivalent C++ model (2026-10-13)

The [maintained update](../../msvc/src/game/item/item_update.cpp) occupies all
2,320 bytes. It matches 2,312 at their retail offsets, including both switch
tables. The only remaining difference is the order of two loads in the
magnetized pursuit path: retail reads the pursued player's state before
reloading the active collector; the compiler reads the collector first. The
[layout](../../msvc/build_support/layout/equivalent/item_update.json) permits
only this order difference, not changes to the stack frame or branch targets.

The model's entry is the real [item scheduler callback](../../msvc/src/game/item/item_manager_on_update.cpp),
not a volatile function pointer. The callback is 48/48 bytes exact and calls
the update directly. `UpdateItemContact` checks pickup before magnet attraction;
only a completed pickup skips the animation and timer. `CollectItem` handles
rewards and retirement. Small and large power pickups share the HUD update but
preserve their different sound, score-text and full-power check order.
The [shared velocity layout](../../msvc/include/th10/game/item_velocity.hpp)
separates the two floats written by `SetPolar` from the depth velocity at
item offset `0x3C0`. Spawning clears that float; movement integrates it.
The shipped body passed 473 bounded differential cases against retail; that
is a behavior check, not a byte match.

The allocator, update, converter and pool lifecycle use the same
[item record](../../msvc/include/th10/game/item_record.hpp). Both constructor
entry points clear the animation base, then clear only bit 0 of the motion
timer's flags at `+0x3D8`; no byte past a nominal `Entity` is accessed.
The scheduler graph compiles the update as an independent translation unit.
The fixed-address graph for `ConvertItems`, `AddPower` and `AddLives` includes
that same source instead of a separate 227-line implementation. Its update is
unselected (2,340 bytes); all three helper bodies remain exact.

The native `Player::AngleFromPoint` context matches its complete 67-byte
retail callee. Compiling the real 30-byte `SetPolar` as an external object
leaves MSVC unable to see that it preserves EDX; the caller then differs at
2,166 positions. A visible C++ leaf with the same integer-register and memory
effects retains the shared comparison but does not correct the load order.

In a scheduler-rooted native link with 30 bodies placed at their retail entry
addresses, the raw update still differed in the same eight bytes. Both tables,
all 44 call sites and the 48-byte scheduler callback matched without relocation
adjustments. This is not a promotable cluster: its 36-byte `SetPolar` overlaps
the following retail function. Using the 30-byte scalar version instead grows
the update to 2,340 bytes, overlapping `Draw` by 20.

Linking the full ANM interpreter instead of its external declaration also
leaves those same eight bytes different. This holds with the real recursive
primary-back creator, timer and RNG helpers, and the bullet callback that
consumes the interpreter's return value. All 44 item call sites still match.

MSVC 13.10.3052 and 6030 produced the same eight differing bytes. Tracing the
6030 optimizer shows where the order changes: `GoptSingleUseCopyProp` moves
the state read past the collector lookup to its only use, the hit comparison.
`Riscify` later separates the load from the compare; the two loads reach the
scheduler with equal priority. Looking up the collector on each arm of a
hit/default switch lets `FgDoHeadMerge` put the reads in retail order. It also
swaps the target and velocity registers. Joining both pursuit states before
the hit test likewise gets the order right, but compares ESI instead of EAX.
Neither version matches the complete function.

With the shared motion layout, looking up the collector on both hit/no-hit
paths can produce both loads **in retail order and in the retail registers**.
Using a `bool` for the deferred conversion request also keeps one in EBX, but
the request then uses 8-bit stores instead of 32-bit stores, and the script
start call loses its register contract. The complete body is 2,308 bytes.
Standard C++98 `register` hints did not change the optimized object sections.

Walking only a `SpawnItem*` put `position.x` in EBP and grew the update to
2,332 bytes. The maintained `ItemMotionCursor` instead carries the native
address of `position.y` and recovers the real `Item::motion` on access.
There is no duplicate motion struct or `(&position_y)[-1]` access. The last
stride increments an integer, not an out-of-bounds pointer. `ApplyItemGravity`
tests the extended sum; the subsequent falling-speed cap reloads binary32.

A compiler barrier between the state and collector reads split the shared
comparison and produced 2,344 bytes.
MSVC 13.10.6030 does not implement the narrower `_ReadBarrier`: `/we4163`
rejects it and permissive compilation emits an external call. Making both
real reads volatile does order them, but the split form tests ESI before
loading the collector. The common-test form loads the collector before
testing ESI, not EAX.

## Model

The maintained update performs the complete 2,198-slot pool walk: idle
short-circuit, delayed script activation (state 5, kind + 374), falling integration with
retail's extended-precision planar adds and binary32 Z boundary, player-seeking with the
FPATAN angle and the π/2 degenerate case, magnetized pursuit, the collection box with the
kind switch (power/point/retirement payouts), the focused/unfocused magnet boxes, the
animation tick, the frame-timer expansion and the terminal ConvertItems tail call.

## What made it converge

The BLOCKED note's lever — native LTCG with the real scene caller, production state
layout and helper prototypes — plus four nonobvious source shapes:

1. **Genuine helper graph.** The context unit supplies the complete item,
   animation and sound helpers. The native linker sees both that unit and
   the separately compiled update, and derives
   each retail private convention from those sites: script index in EAX and entity in ESI
   for `Entity_StartScript`, HUD owner in ESI for `SetPowerDigits`, run counters in EAX
   for `AddPower`/`AddLives`/`AdjustPower`, converting manager in ESI for `ConvertItems`,
   and the collection point in EAX for `AngleFromPoint`. Twelve helper symbols are bound
   to their retail addresses through `bindings`; `Player_RefreshOptions`,
   `RunAnimationVm` and `__ftol2` are external calls in this item graph.
2. **Y-anchored motion walk.** Retail keeps EBP at `position.y`, with the
   state, timer and variant at offsets `+0x2c`, `+0x18` and `+0x3c`.
   Discovering that anchor first raised the instruction match from 49% to
   66%. The cursor now derives it from the layout used by the allocator.
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

## 2026-10-19: gauge reads (case 2), blocked by the size gate

Retail reads `g_globals.gauge` inside each arm of case 2 (`mov eax,ds:0x474c4c`
at +0x4ED and +0x532, plus the `fild` in the else arm). The model hoists
`int gauge = g_globals.gauge;` into EBX before the `position.y < 144` test
(+0x4E0). Writing the first arm as
`int scaled = g_globals.gauge * 10; value = scaled - scaled % 10;` and the
else arm as `g_globals.gauge * 10 / 2 - penalty` closes all three hunks
(557/601 identical, 29 hunks; `value = g_globals.gauge*10` without the named
temporary loads straight into EBX). It also flips the +0x870 `fld/fadd` pair
(temp parity), and the body becomes 2,324 bytes against the region's
2,320, so the size gate fails. The shipped model was 4 bytes shorter at the
gauge (one 6-byte EBX load against retail's two 5-byte EAX loads). That
offset the 4 bytes the zero-register family (EDI against retail's ECX, the
+0xA..+0x15B hunks) costs. The gauge fix can ship only together with the
zero-register fix.
