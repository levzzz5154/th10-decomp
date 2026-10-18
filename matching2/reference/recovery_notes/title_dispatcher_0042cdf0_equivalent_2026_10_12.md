# Title dispatcher 0x0042CDF0: equivalent recovery (2026-10-12)

**Status (2026-10-12, later the same day): registered equivalent recovery, 279 of 291 instructions identical.**
What changed since the parked draft:

- the key configuration handler 0x0042F540 and its leaves are linked from their real sources
  (`context_sources`), so the call passes the room in EBX with no push, as retail does;
- the idle test is `switch (mode) { case 1: case 2:`; with `mode == 1 || mode == 2` the compiler
  keeps the constant 2 in EBP (retail never touches EBP) and the body is 4 bytes too long. The
  switch costs three instructions at the top (`test/jle/cmp/jg` for retail's `cmp 1/je/cmp 2/jne`),
  recorded as code-shape; the natural spelling that keeps 2 out of EBP is still unknown;
- the timer tick uses float literals.

The other recorded differences: the demo block schedules the stage-record store and the
difficulty load in another order (4 hunks), one alignment filler, one x87 operand order.
Everything below this paragraph describes the earlier parked draft.

The readable candidate that already lived in the title cluster context
(`layout/ltcg/ending_screen_dependencies/title_dispatcher.cpp`, compiled
in-cluster by `difficulty_select_update_dependencies/title_dispatcher.cpp`)
is now a registered equivalent recovery
(`layout/equivalent/title_dispatcher_0042cdf0.json`): 1,088 of 1,128 bytes
used, 187 of 291 instructions identical, 104 instructions in 54 recorded
differences.

## Recorded differences

* 30 code-shape hunks: evaluation-order and scheduling differences through
  the demo path, the phase dispatch and the mode-call sequences.
* 14 register-choice hunks: counter and pointer homes differ (the same
  contest family as the other equivalent recoveries).
* 10 branch-target hunks: the model merges or splits the phase-table
  branches; `listed_branch_targets` records them with both destinations.

## Structure notes

* `code_bytes` = 1060: the retail region contains its phase jump table at
  offset +0x424 (`ff 24` at +0x147 targeting 0x42D214), so the code extent
  excludes the table; the tail comparison covers the table.
* The model calls `TitleOptions` and other in-context functions; each
  context-defined callee is bound in `bindings` to its retail address so
  `relocate()` can rewrite the call displacements.
* The demo path string `bgm/th10_02.wav` (0x0046F018) is bound the same way.

## Remaining

None for the equivalence route.  A byte-exact recovery would additionally
need c2 to reproduce the retail scheduling; the model keeps the readable
semantics either way.

## 2026-10-17: the residual nine hunks probed; parked

The layout now records 9 hunks (the 2026-10-12 text above predates the
improvement to 279/291). Probed each shape against the documented levers,
each measured with `equivalence.py --layout`:

- The x87 `fld`/`fadd` operand order at +0x401 (`elapsed += *speed` versus
  `elapsed = *speed + elapsed`) compiles byte-identically: the
  `msvc-c2-oper-order-mechanismism` rule holds (the operand swap moves
  codegen only register-register, both operands here are memory).
- The `g_main_state = 12` store versus the `difficulty` load (hunks +0xc9 to
  +0xf2): making either side go through a pointer local (the
  `msvc-c2-pointer-store-adds-scheduler-edge` lever) leaves the schedule
  unchanged in both directions.
- The `switch (title->mode) { case 1: case 2: }` head (hunks +0x6..+0x10) as
  an unsigned range test overshoots to 28 hunks.
- The +0x7e `mov edi,edi` versus `lea ecx,[ecx]` filler is the same
  head-position family as the joystick poll loop head.

Region stays equivalent (167 differing bytes).

## 2026-10-17: semantic walk against the decompilation

`th10-parked-models-may-be-semantically-wrong` records that a register or
scheduling residual is often the symptom of a different CFG, and that a c2
trace cannot reveal a missing case. This region's switch tree was therefore
walked against `decompiled/ghidra_augmented/functions/0042CDF0.c`.

**Case sets match.** Retail dispatches 0..0x10 (0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
10, 0xb, 0xc, 0xd, 0xe, 0xf, 0x10) and so does the model — no missing case.

**Two structural differences in the idle-demo block** (the `__forceinline`
`UpdateIdleDemo`):

1. Retail tests the mode as an if-chain — `if ((mode == 1) || (mode == 2))` —
   where the model uses `switch (title->mode) { case 1: case 2: ... }`. That is
   exactly the head residual (`cmp eax,0x1; je` + `cmp eax,0x2; jne` against
   the model's range test `test eax,eax; jle` + `cmp eax,2; jg`). The
   `or-chain` spelling was already tested and is *worse* (271/291 against
   279/291), so the head form alone is not the fix.
2. Retail computes the increment into a temporary first —
   `param_1 = idle_frames + 1;` then, only if the key mask is clear,
   `idle_frames = param_1;` and tests `899 < param_1` — where the model does
   `++g_globals_score.idle_frames;` and then tests the stored value. Same
   semantics, different store position.

So this region is not mis-transcribed; the case list is complete. The two
differences above are the residual's real shape, and (1) has been shown not to
move on its own. Region stays equivalent. The scheduling and
head-alignment residuals need the c2 list-scheduler trace
(`msvc-c2-list-scheduler-priority`) before another source sweep.

## 2026-10-18: demo block closed by the evaluation-order rotation (167 -> 123 bytes)

The four demo-block hunks (+0xc9..+0x10a, the stage-route / difficulty store
order) are gone.  The lever is one statement swap: `g_globals_score.shot =
header->shot;` evaluates *before* `g_globals_score.menu_difficulty =
g_globals_score.difficulty;`.  279/291 -> 285/291, 167 -> 123 differing bytes,
9 -> 5 hunks.

Mechanism (from the c2 list-scheduler trace of this function,
`trace_target_link.py` run kept in the scratchpad as `trace_out/`): the
scheduler runs on physical registers, so anti-edges run from every earlier
reference of a register to each later definition, and the colours rotate with
the temporary creation order (route address ECX, character EDX, shot ECX,
saved difficulty EDX, new difficulty EAX).  With the shot statement first, the
shot load (def ECX) waits for the route store (ref ECX) and the difficulty
load (def EDX) waits for the character store (ref EDX), which is exactly
retail's interleaving; with the old order the two colours swapped and the
stores reordered with them.

Ruled out for this hunk family (each measured with `variant.py`):
- moving the route statement anywhere else (after the character store, last,
  after the header load, split through a named local): 899..960 bytes, every
  one worse -- the route address must keep its early `lea` (the stage value
  dies in EAX at the header load) while its `shl`/`add` stay late;
- escaping `&g_stage_route_current` in the context (`TitleDispatcherEscape`):
  181 bytes, the block moves the wrong way (the `shl`/`add`/store clump at the
  top); escaping `g_replay_path`, `g_title_demo_paths`, `g_stage_routes` or
  `g_main_state` as well changes nothing further;
- named locals alone (`saved_difficulty`, `character`): canonical, same bytes
  as the swap (they fold to temporaries).

## 2026-10-18: what is left (123 bytes, 5 hunks)

* the idle-demo head (+0x6..+0x10) and its one-byte-shift cascade through the
  strcpy loop head (+0x22..+0x7f, the `mov edi,edi` filler at +0x7e and the
  `jmp` displacement byte at +0x142): 116 bytes.  Retail's `cmp eax,1 / je /
  cmp eax,2 / jne` is an if-chain (`mode == 1 || mode == 2`); every spelling
  that produces it (or-chain, or-chain with a local, `>= 1 && <= 2`, early
  returns, goto forms, swapped operands, unsigned mode) also makes c2
  materialise the constant 2 in EBP (`push ebp / mov ebp,2` at the top, every
  use becomes `cmp/or/mov ...,ebp`): 914 bytes, a draft.  The switch spelling
  keeps the body exact but costs the range test (`test eax,eax / jle` vs
  retail's 3-byte `cmp eax,1`) and therefore the whole shift cascade.
  Probed and dead for the materialisation: constant type splits (`2u`,
  unsigned mode/transition), operand order (`2 == x`), deleting the body's
  `transition == 2` compare, escaping any global, 0..8 dead symbol-churn
  locals, accessor uses.  The regalloc trace (`regalloc/trace_target_globals_link.py`,
  kept as `trace_reg/` for the or-chain and `trace_reg_base/` for the switch
  head) shows the constant-2 candidate as the last, EBP-only entry of the
  ChoosePhysReg table in both builds -- priority -91 with the if-chain against
  -17 with the range test -- and the difference is the deciding input of the
  EBP cost/benefit step that normally rematerialises EBP constants; which
  quantity feeds -91 vs -17 is not yet identified.
* the x87 `fld`/`fadd` operand order at +0x401: 7 bytes.  Operand swaps,
  accessor uses at both operands, named locals and extra statement locals are
  all canonical (167/123 unchanged); a pointer local for `elapsed` overshoots
  to 143 bytes (and `timer.speed` is `const float *`, which rejects the
  pointer-local spelling for the speed operand).  Consistent with the tied-pair
  case of `msvc-c2-operand-order-mechanism` (immune to every global shift).

# title_dispatcher 0x0042CDF0 -- dated addendum (2026-10-18/19)

Append verbatim to matching2/reference/recovery_notes/title_dispatcher_0042cdf0_equivalent_2026_10_12.md

## 2026-10-18: demo block closed by the evaluation-order rotation (167 -> 123 bytes)

The four demo-block hunks (+0xc9..+0x10a, the stage-route / difficulty store
order) are gone.  The lever is one statement swap: `g_globals_score.shot =
header->shot;` evaluates *before* `g_globals_score.menu_difficulty =
g_globals_score.difficulty;`.  279/291 -> 285/291, 167 -> 123 differing bytes,
9 -> 5 hunks.

Mechanism (from the c2 list-scheduler trace of this function,
`trace_target_link.py` run kept in the scratchpad as `trace_out/`): the
scheduler runs on physical registers, so anti-edges run from every earlier
reference of a register to each later definition, and the colours rotate with
the temporary creation order (route address ECX, character EDX, shot ECX,
saved difficulty EDX, new difficulty EAX).  With the shot statement first, the
shot load (def ECX) waits for the route store (ref ECX) and the difficulty
load (def EDX) waits for the character store (ref EDX), which is exactly
retail's interleaving; with the old order the two colours swapped and the
stores reordered with them.

Ruled out for this hunk family (each measured with `variant.py`):
- moving the route statement anywhere else (after the character store, last,
  after the header load, split through a named local): 899..960 bytes, every
  one worse -- the route address must keep its early `lea` (the stage value
  dies in EAX at the header load) while its `shl`/`add` stay late;
- escaping `&g_stage_route_current` in the context (`TitleDispatcherEscape`):
  181 bytes, the block moves the wrong way (the `shl`/`add`/store clump at the
  top); escaping `g_replay_path`, `g_title_demo_paths`, `g_stage_routes` or
  `g_main_state` as well changes nothing further;
- named locals alone (`saved_difficulty`, `character`): canonical, same bytes
  as the swap (they fold to temporaries).

## 2026-10-18: what is left (123 bytes, 5 hunks)

* the idle-demo head (+0x6..+0x10) and its one-byte-shift cascade through the
  strcpy loop head (+0x22..+0x7f, the `mov edi,edi` filler at +0x7e and the
  `jmp` displacement byte at +0x142): 116 bytes.  Retail's `cmp eax,1 / je /
  cmp eax,2 / jne` is an if-chain (`mode == 1 || mode == 2`); every spelling
  that produces it (or-chain, or-chain with a local, `>= 1 && <= 2`, early
  returns, goto forms, swapped operands, unsigned mode) also makes c2
  materialise the constant 2 in EBP (`push ebp / mov ebp,2` at the top, every
  use becomes `cmp/or/mov ...,ebp`): 914 bytes, a draft.  The switch spelling
  keeps the body exact but costs the range test (`test eax,eax / jle` vs
  retail's 3-byte `cmp eax,1`) and therefore the whole shift cascade.
  Probed and dead for the materialisation: constant type splits (`2u`,
  unsigned mode/transition), operand order (`2 == x`), deleting the body's
  `transition == 2` compare, escaping any global, 0..8 dead symbol-churn
  locals, accessor uses.  The regalloc trace (`regalloc/trace_target_globals_link.py`,
  kept as `trace_reg/` for the or-chain and `trace_reg_base/` for the switch
  head) shows the constant-2 candidate as the last, EBP-only entry of the
  ChoosePhysReg table in both builds -- priority -91 with the if-chain against
  -17 with the range test -- and the difference is the deciding input of the
  EBP cost/benefit step that normally rematerialises EBP constants; which
  quantity feeds -91 vs -17 is not yet identified.
* the x87 `fld`/`fadd` operand order at +0x401: 7 bytes.  Operand swaps,
  accessor uses at both operands, named locals and extra statement locals are
  all canonical (167/123 unchanged); a pointer local for `elapsed` overshoots
  to 143 bytes (and `timer.speed` is `const float *`, which rejects the
  pointer-local spelling for the speed operand).  Consistent with the tied-pair
  case of `msvc-c2-operand-order-mechanism` (immune to every global shift).

## 2026-10-19: head family -- proven blocker (the constant-2 register candidate)

Traced both spellings through c2's global-register machinery (artifacts kept
in the campaign sandbox: turn-back, spill, budget and candidate-table traces
of each build):

* The `FUN_107a6a05` turn-back pass is not the delta: the per-use bit 0x10
  and the per-block flag at +0x9c are identical in both builds (the value-2
  candidate: 8 uses, bit set, block flags 0, kept at that pass both times).
* The rematerialisation happens at `SpillOrDefer` (the `FUN_107a8969` list
  walk) -> `FUN_107b3c97` -> `GrgChangeRegToImmed` for kind-13 uses. The
  gate is `candidate.f40 benefit < 1` (with the kind-13 clause). The range
  head spills the value-2 pieces with benefit 0 / -1; the if-chain keeps one
  merged value-2 group (refs 8, benefit 3) which reaches ChoosePhysReg and
  sits in EBP. The -91 vs -17 field seen at ChoosePhysReg is downstream
  bookkeeping of the same accounting, not the gate.
* The f40 benefit counts store/push-classified uses of the value (the
  `mov ecx,2` argument setup and the `or [mem],2` store-RMW) and is
  decremented per piece as uses are reclassified; the switch-lowered
  `cmp eax,2` of the range head groups its value-2 use differently from the
  source-level compare of the if-chain, which is what changes the pieces the
  gate sees.
* Zero-cost lever: not found. Every spelling that emits retail's head bytes
  produces the same source-level compare forms and the same grouping, and
  both the head compare forms and the body's value-2 use positions are
  pinned by retail's required bytes (the body matches instruction for
  instruction apart from the x87 pair). Accounting-input probes that cost no
  bytes are exhausted (symbol churn, no-op inline calls, escapes, accessor
  uses, statement orders, deleting the body's `transition == 2` compare --
  the head's own group keeps the benefit above the gate there too). A +-1 in
  the f40 update is the only remaining surface and is not reachable from
  source spellings that keep the required bytes. Head family recorded as a
  proven blocker; the range head (285/291, 123 bytes) stands.

## 2026-10-19 (later): the x87 pair closes with one expression temporary

The closing timer add at +0x401 (`fld [ecx]` / `fadd [ebx+0x2b8]`, recorded as
`operand-order`) is not immune after all. Writing the `transition == 0` arm's
call as `room->DisableTimerWithOwner(transition + 1)` (transition is 0 there)
adds one expression temporary and puts the pair in retail's order: 285/291,
123 bytes -> 287/291, 116 bytes; the head family is unchanged. Any one of
`transition + 1` for the 2 in the `transition == 1` arm, `transition + 10` for
the 12 or `transition + 12` for the 15 does the same; doing all four flips it
back (123). This is the temp-parity lever of `msvc-c2-operand-order-mechanism`.
The `if (mode == 1 || mode == 2)` head with all those combinations and with
unsigned/short/char compares of 2 stays at 912-914 bytes.
