# Equivalent recovery: `0x004236F0` — replay/result submenu dispatch

Date: 2026-10-13

## Status

Accepted equivalent recovery (not exact). The verdict of
`matching2/tools/matching/equivalence.py` over
`layout/equivalent/replay_submenu_004236f0.json`:

```text
replay_submenu_004236f0: 3,224 of 3,260 bytes used, 751 of 923 instructions
identical, 1 base/index swaps, 0 frame-offset, 171 instructions in 80 recorded
differences
```

(exit code 0; gate passed: external references equal, no call/branch
substitutions in tie-break hunks, structural weight 108/923 ≤ 12.5%, total
weight ≤ 33%.)

The production region stays `asm` (`_asm_FUN_004236f0_004236f0`,
3260 bytes); the C++ model ships as an equivalent recovery and is registered
by adding to `equivalent_recoveries` in `matching2/msvc/regions.json`:

```json
{"region": "asm_FUN_004236f0_004236f0",
 "layout": "layout/equivalent/replay_submenu_004236f0.json"}
```

No other `regions.json` change is required. `main_menu_dispatch.cpp` keeps the
naked body (the exact link still builds it); the equivalent model lives in the
new files listed below and is compiled only by the recovery build.

## Model

`src/game/replay_submenu_update_004236f0.cpp` is the readable state machine
(states 6–13 of the result-screen record: confirm gate, ranking-gate
high-score publication or `PrepareNameEntry`, the three-row save choice, the
25-row replay browser with manager creation/release, the 13-column keyboard
editor with letter/space/backspace/save cells, the alternate (`no_entry`)
keyboard path, and the final-choice dispatch). The record view and every
global live in `include/th10/game/replay_submenu_004236f0/state.hpp`
(`SubmenuState_004236f0`: `state` +0x4, timer +0x10, rows cursor +0x24, grid
cursor +0xFC, handle +0x1D4, `name_length` +0x1E0, `extra_cleared` +0x1E4,
`no_entry` +0x1E8, 25 replay managers +0x1EC, name +0x2B4).

The private-ABI dependency bodies are scoped copies compiled into the model
translation unit (`layout/ltcg/replay_submenu_004236f0/*.cpp`: the animation
find/setstop/child/mark6/stop3/stop1/node-flag family, the sound queue, the
scheduler value, the menu cursor trio, the input-mode publisher, the
frame-maximum update, the timed-state reset and the platform-resource
release), plus `?InputMaskActive@KeyRepeatState@@QAEHG@Z` linked from its
maintained source. `0x00429B60` is called through a `__fastcall` binding
(ECX = replay manager, EDX = target path, name on the stack) bound at its
retail address; the `ReplayManager` destructor (0x004294A0, receiver on the
stack, RET 4) is bound through a stdcall alias; `PrepareNameEntry`,
`ReplayManager_Create`, `UpdateBoundedCounter`, the sprintf/time32/free shims
and the security cookie bind at their retail addresses. The pooled literals
("th10_%.2d.rpy" and the eight-space name) are `data_aliases` at 0x0046E0C8 /
0x0046E354.

## What the recorded differences are

80 hunks, 171 instructions, all tie-breaks or reviewed block placements:

- `block-order` (the only structural runs): state B/C's shared length-bump and
  clamp block sits after the two write cells in retail and partially inline in
  the model; the state C cancel region (`selection < 0` branch) and the
  state-C timer gate are placed at the other end of the same tail; the
  state-B cancel test is reached with an inverted branch over the same code.
- `branch-target` (8): the jump table (0x42438C) plus seven tail jumps whose
  targets were proven equivalent by following unconditional jumps.
- `code-shape` (4): `lea` vs `add` for the child-lookup script id, the state D
  dispatch (`sub eax,0` + dec chain vs `test`/`cmp` chain), and the state C
  row-select compare (immediate vs register-held 2).
- `evaluation-order` (15): the strlen/grid/selection loads, the summary-slot
  loads around the time32 call, the save-cell sprintf arguments, and the
  stage-table write addressing chain.
- `register-choice` (37) and `alignment-padding` (4): scratch-register
  renames (EBX=0xA/1 materializations, ESI/EBX cursor pointers) and nop
  fillers.

## Nonobvious insights recovered on the way

- The two legacy "flag" fields are the `MenuCursor` wrap flags: +0xF4 is the
  rows cursor's wrap and +0x1CC the grid cursor's wrap; +0x2C/+0x104 are the
  two `item_count`s, so the whole record is `state; timer; MenuCursor rows;
  MenuCursor list; handle; ...; managers[25]; name[8]`.
- State A navigates the rows cursor; confirming hands the grid cursor to the
  keyboard editor (states B/C).
- The append/space paths of both keyboard editors queue sound 10 and FALL
  THROUGH into the cancel test in the same frame (no return); only the
  backspace and save cells return early, and the state C armed
  (`no_entry != 0`) path queues no sound at all.
- State C's three row re-selections use `Select(0)` (not `Select(2)` as the
  legacy host model claimed), and state D's selection 1 and 2 both dispatch
  `SetInputMode(&data_00491C28, 4)` through the same dec/dec chain.
- The `0x00429B60` serialize call takes the manager in ECX, the target path in
  EDX and the name on the stack — expressible from ordinary C++ as a
  three-argument `__fastcall` declaration bound at the retail address.

## Files

- `src/game/replay_submenu_update_004236f0.cpp` (model body; also includes the
  scoped dependency bodies at the bottom)
- `include/th10/game/replay_submenu_004236f0/state.hpp`
- `layout/ltcg/replay_submenu_004236f0/{animation.hpp,find.cpp,setstop.cpp,
  child.cpp,mark6.cpp,stop3.cpp,stop1.cpp,nodeflag.cpp,inputmode.cpp,
  timer.cpp,queue.cpp,cursor.cpp,frame.cpp,timed.cpp,destroy.cpp}`
- `layout/ltcg/replay_submenu_004236f0_context.cpp` +
  `layout/ltcg/replay_submenu_004236f0_context.json` (the equivalence build's
  context cluster: driver + the maintained `input_mask_active` source)
- `equivalent/game/replay_submenu_004236f0_stub.cpp`
- `layout/equivalent/replay_submenu_004236f0.json` (the layout to register)

The scratch lab lives under `scratch/submenu_004236f0/` (reflink copy; the
schema-2 cluster manifest tried there was removed after the equivalent path
succeeded).

## 2026-10-17: state reviewed; parked

The 78 hunks are the tie-breaks and reviewed block placements the class list
names (the scratch-register renames, the block-order tail placements, the
`lea`-versus-`add` child-lookup id and the dispatch chains). The
`lea [eax+disp]` against `add reg,disp` form is the same addressing-mode
decision `replay_runtime_bootstrap` re-confirmed this session as
unsteerable from source spelling.

Region stays equivalent (2088 differing bytes).

## 2026-10-18: two real levers; base/index swap closed; 2088 -> 1686 differing bytes

The single base/index swap was the state-C save column's second name copy
(retail `mov BYTE PTR [edx+eax*1],cl`, base = the `dst-src` stride, against the
model's `[eax+edx*1]`, base = the walking source pointer). It is now closed
together with 400 more bytes by three source levers, none of them codegen
tricks. The registered gate passes again: 3,252 of 3,260 bytes used, 769 of
908 instructions identical (was 753), 0 base/index swaps (was 1), 0
frame-offset, 139 instructions in 72 recorded differences (was 171 in 80);
1,678 code bytes + 8 tail bytes differ (was 2,080 + 8).

1. **Per-branch summary reference (state A confirm, `g_replay->summary`).**
   The model bound `ReplayHeaderView*& summary` once before the branch, so c2
   materialised `&g_replay->summary` before the field load and shared it across
   both arms. Declaring the reference inside each arm reproduces retail's
   per-arm shape: the folded `[esi+0x18]` load first, the `add esi,0x18`
   materialisation after the call for the reload. Six recorded hunks around
   0x447..0x48c close (-399 bytes) and the register allocation downstream
   improves. This is the "named element pointer" observation of
   `msvc-c2-operand-order-mechanism` from the other side: the named pointer
   keeps the materialised order, the folded per-use form defers it.

2. **Copy #1 of the save column spelled as a two-pointer walk.**
   `strcpy(slot, state->name)` is strength-reduced by c2 into a walk+diff loop
   (`[walk+diff]` store); retail's copy #1 is the plain `*d++ = *s++` walk.
   Spelling it `while ((*dst_walk++ = *src_walk++)) {}` matches retail's loop
   (identical instructions 760 -> 768). The indexed form
   (`for ((slot[i] = name[i]) != 0)`) is even closer instruction-wise (767
   identical, only 1,591 differing bytes) but grows the body to 3,264 bytes
   against the 3,260-byte region: "a draft may be measured while it is still
   too long; it cannot be built in". Kept as a measured draft only.

3. **35 named menu predicates steer the symbol window.** The swap itself is
   decided by `OptCmpHashVal` over the two address temporaries of the inlined
   copy-#2 store (rule `msvc-c2-operand-order-mechanism`, the 0x00433570
   `[walk + diff]` case). Naming existing menu conditions as used `bool`
   locals at their original evaluation points (the `replay_save_update`
   2026-10-17 recipe; case-level declarations wrapped in a scope so no case
   label skips an initialisation) flips the comparison into retail's order.
   Window measured over 48 candidate predicates: on this model the source-order
   prefix 35..37, 40 and 44..48 give the retail order, 34 or fewer do not -
   non-monotonic, as expected from the id wrap. Every predicate is
   codegen-neutral alone: all 48 measured singly leave every byte unchanged.

Ruled out with evidence (2026-10-18):

- copy-#2 respellings (indexed, pointer, split while) on the per-branch base:
  all +108 to +121 bytes; retail's copy #2 is the `strcpy` walk+diff shape and
  only its base/index order was wrong.
- naming the state-7 ranking-gate predicate (initialised or
  declared-then-assigned): perturbs the stage/mode/subslot addressing chain,
  +790 bytes and four new hunks. Every other predicate is byte-neutral alone.
- `SubmenuCursor` held as a reference instead of a pointer local (cases 8-12,
  rows and list): byte-identical, the ESI/EBX cursor-pointer contest does not
  move with that spelling. The 34 remaining register-choice hunks
  (scratch-register renames, the EBX `0x1`/`0xA` materialisations) stay, per
  the HANDOFF table, unresponsive to symbol count; they need per-block
  ChoosePhysReg work (`compiler_tracers/regalloc/`).
- the `lea [eax+disp]` vs `add reg,disp` child-lookup id remains closed
  (2026-10-17 review), not retried.

Remaining (all 72 recorded in the layout, classes kept from the reviewed set):
the state-B/C shared length-bump/clamp block placements and the state-C cancel
region (block-order), the state-D `sub eax,0` + dec chain (code-shape), the
strlen/selection load orders (evaluation-order), 34 register-choice renames
and two alignment fillers. The 8 differing tail bytes are the state-D jump
table: the model's pre-table code is 3,220 bytes against retail's 3,228, so
the 8-entry table lands 8 bytes early and its last entries fall in the tail.
Closing that needs eight bytes of code growth at source level; every naming
set measured holds the extent constant at 3,252.

## 2026-10-18: byte-exact — 908/908 instructions, 0 recorded differences

Final spelling `final14` (sandbox /tmp/campaign/replay_menu): `variant.py`
`final14  908/908  0  0  0  0  *EXACT*`; registered
`equivalence.py --name replay_submenu`: `3,260 of 3,260 bytes used, 908 of 908
instructions identical, 0 base/index swaps, 0 frame-offset, 0 instructions in 0
recorded differences`, exit 0. Layout: `"differences": []`,
`base_index_order: 0`, no `frame_shift`. Campaign total: 2,088 -> 0 differing
code bytes (753 -> 908 identical instructions).

**The lever that closed the last two hunks** (`lea ebx,[eax+0x7c]` vs
`add ebx,0x7c` @0x22f and the `mov eax` vs `mov ebx` load @0x226): the
second-assignment form of `msvc-c2-field-address-pointer-forwarding` — the
child-lookup id is re-derived at its two live points:

    int id = rows->selection;
    state->background.FindChildRef(id + 0x7C).StopAtFrame6();
    ... the setup calls ...
    id = rows->selection;
    switch (id) {

A single-assignment `id` is forwarded into the add (one coalesced candidate:
`mov ebx,[ebp+0x24]` + `add ebx,0x7c`); the second assignment stops the
forwarding, `id` stays its own register candidate and the add materialises as
retail's `lea ebx,[eax+0x7c]` from the EAX load. The switch re-derives the
selection exactly as retail's second `[ebp+0x24]` load at 0x26e.

Also measured exact on the same base (sweep of 20 spellings, `v_end1.py`): the
same re-derivation with the two assignments before the use (`a2`), through two
lvalues `rows->selection` / `state->rows.selection` (`a3`, `a3b`), with the
second assignment immediately before the add (`a4`), and the constant-true
re-read copy-block lever (`d1` `if ((base == base) ? true : true)`,
`d2` `if ((base == rows->selection) ? true : true)`, `d3` the ternary as the
Queue argument `(base == rows->selection) ? 10 : 10`) — all 908/908.

**Ruled out on final13** (the closed-2026-10-17 verdict's four spellings stay
dead, and the new mechanisms measure as follows):
- forwarded single-assignment forms — named id, flipped operand order,
  two-step `+=` accumulate, split constant `0x40+0x3C`, named `off` — the
  folded class of the forwarding rule; all keep `add ebx,0x7c`;
- scoped pointer ranges (b1: `rows` dying before the confirm block with folded
  `state->rows.` uses, b2: add-only scoped pointer, b3: surviving add+switch
  pointer): 906/908, the same 3 bytes;
- receiver/base first-mentions (c1 statement-scope `SubHandle4* bg` = no move;
  c2 early receiver = 842/908 / 2,732 bytes, the whole dispatch perturbs;
  c3 base first-mention with three uses = 874/908 / 766 bytes);
- conditional self-assignment `if (id != rows->selection) id = rows->selection;`
  (7 hunks / 26 bytes) and the ternary-on-the-argument form `d4` (7 / 26) —
  both emit the compare;
- multi-use named reference `int& sel` (h4) and single-use (h5), self-compare
  argument form `d5`: no move, the same 3 bytes.

## 2026-10-18: promotion rehearsal — the region ships as a native-LTCG cluster

Sandbox cutover (`/tmp/campaign/replay_menu`, `spec.json` +
`adopt_promotion.py` + `regions_edit_spec.json`), reference artifacts
`/tmp/campaign/{mgr_teardown,point_count,hint,front_tick,font_draw,anim_change}/`:

- Cluster `build_support/layout/ltcg/replay_submenu_004236f0.json`
  (schema 1): the model `src/game/pause/replay_submenu_update.cpp` selects
  `_SubmenuUpdate@4` at 0x004236F0, complete contribution 3,260 bytes
  (`.text$02h`, code 3,228 + the 32-byte state-D jump table). 18 ABI anchors
  place the scoped private-ABI bodies at their retail addresses (their
  compiled contributions equal the declared sizes exactly: 57/65/37/33/65/
  28/89/65/18/123/73/65/67/67/70/66/47/128). Compiler context
  `_ReplaySubmenuContext_004236f0@8` = a synthetic record-walking caller at
  0x004243B0 (16-aligned, 39 bytes, measured from cluster.map after a 48-byte
  first guess was rejected), never exported. The two pooled string literals
  bind at their retail .rdata addresses as data aliases.
- The key-repeat mask body needed a scoped copy
  (`build_support/layout/ltcg/replay_submenu/mask.cpp`): the maintained
  `src/game/eclview/input_mask_active.cpp` declares its own record type and
  cannot share the cluster's translation unit (C2011 redefinition).
- regions.json: region record `asm_FUN_004236f0_004236f0` ->
  `semantic_SubmenuUpdate_004236f0` (previous_record kept, source the model);
  `translation_units` swaps the asm owner for the model; `ltcg_clusters` += the
  cluster; `equivalent_recoveries` drops the entry; asm owner
  `build_support/exact/game/pause/main_menu_dispatch.cpp`, the equivalent
  layout, the stub `src/game/pause/replay_submenu_stub.cpp`, the old
  `build_support/contexts/legacy/game/replay_submenu_update.cpp` and the old
  equivalent context cluster JSON deleted.
- Gates: `probe.py --source src/game/pause/replay_submenu_update.cpp`:
  `0x004236f0 3260 bytes _SubmenuUpdate@4 EXACT`; full
  `build_msvc.py --project .../msvc --jobs 8 --verify oracle`: 1,656
  maintained sources, 0 failures, **the whole .text (412,672 bytes) hashes to
  `c1acff416da826334c29a19fa89cd7a094626eb36c32afe7950f705a55f56998` =
  `regions.json` `text_sha256` = retail**; "Remaining assembly: 0 regions /
  0 bytes"; "Recovered: 100.0% of bytes... byte-exact alone 78.5% of bytes"
  (was 77.5% before this promotion). `build_msvc.py --exact`: "Whole EXE
  exact: 487,936 bytes", `th10.exe` SHA-256
  `2f14760b6fbbf57549541583283badb9a19a4222b90f0a146d5aa17f01dc9040`
  = retail. Tests: test_ltcg_cluster 60 OK,
  test_equivalence 27 OK, test_source_ownership / test_gcc_llvm_backend /
  test_project_paths OK.
