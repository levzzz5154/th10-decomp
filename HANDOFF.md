# th10 decompilation handoff — 2026-10-18

## Where the project stands

- `make` is green and `make EXACT=1` produces the bit-identical executable
  (SHA-256 `2f14760b6fbbf575…`, verified after every promotion).
- **100.0% of game code recovered** (322,064 of 322,064 bytes, 2,322 of 2,322
  regions); no inline assembly in the default build.
- **83.4% byte-exact C++** (2,309 regions), **99.4%** counting the identical
  instructions of the 22 equivalent regions.
- `callsite_abi.py`, the 129 unit tests and `git diff --check` pass.

![Project status](docs/status.png)

## The 2026-10-18 campaign (this document's previous edition was 2026-10-17)

Every equivalent region was attacked in parallel (per-region sandboxes,
byte-gated variant sweeps, Ghidra semantic audits, c2 tracer archaeology).
**Eight regions were closed byte-exact and promoted** (asm owners deleted,
LTCG clusters registered, every promotion gate-checked with `make`,
`make EXACT=1`, `probe.py` and the unit tests):

| Promoted region | Bytes | Closing lever |
| --- | ---: | --- |
| 0x00417C80 `manager_teardown` | 1,105 | mis-transcribed `g_func_ctrl` re-read + in-link callee convention + escaped supervisor aggregate |
| 0x004084A0 `projectile_point_count` | 370 | re-derived `corner[2].y` expression + statement position (x87 asymmetry) |
| 0x0041A200 `hint_save` | 2,247 | walked-pointer loop (stack-colour weight), `rows == 0` guard scope, skip-arm polarity |
| 0x00415E90 `front_script_tick` | 4,480 | count expression written twice at both clear sites (register-candidate lever) |
| 0x00437FE0 `font_atlas_draw_text` | 509 | direct-call link context flips the Spillcosts contest |
| 0x0043E8B0 `animation_change_script` | 287 | doubled slot read in the guard + `(flags\|8)^0x200` spelling |
| 0x004236F0 `replay_submenu` | 3,260 | rows.selection semantic fix, scoped pointer range split, second-assignment `lea` materialisation |
| 0x004247F0 `player_reset_block_initialize` | 1,435 | receiver-last callee-parameter order (call-lowering tie-break) |

Every other region was improved to a measured best state (below); the
campaign closed ~25,000 differing bytes in total. Several residuals are now
**proven retail-IR properties** (see each recovery note): exhaustive sweeps
show the original source's symbol/temp populations cannot be reconstructed by
any honest spelling — those parks are recorded with the decoded mechanism and
the ruled-out inventory, not left open.

## Equivalent recoveries (21)

Current measurements; each layout's `note` points at its recovery note in
`matching2/reference/recovery_notes/` (all have dated 2026-10-18 sections with
the decoded mechanisms).

| Address | Layout | Bytes | Identical | Recorded diffs | Swaps |
| --- | --- | ---: | ---: | ---: | ---: |
| 0x004067D0 | `projectile_spawn_cell` | 1,472 | 348/354 | 1 | 0 |
| 0x0040BD80 | `recovery_script_executor` | 1,568 | 429/444 | 8 | 0 |
| 0x0040E770 | `enemy_execute` | 14,416 | 3,832/3,926 | 46 | 0 |
| 0x0041DD80 | `laser_circle_trim` | 1,238 | 274/345 | 53 | 0 |
| 0x0041EB00 | `laser_rectangle_split` | 1,171 | 315/316 | 1 | 0 |
| 0x0041EFA0 | `laser_circle_split` | 1,108 | 236/302 | 47 | 0 |
| 0x0041AFD0 | `item_update` | 2,320 | 549/601 | 33 | 0 |
| 0x00428F60 | `replay_runtime_bootstrap` | 1,344 | 387/389 | 3 | 0 |
| 0x00429B60 | `replay_save` | 1,681 | 447/535 | 29 | 0 |
| 0x0042A3E0 | `replay_frame_step` | 68 | 22/22 | 0 | 0 |
| 0x0042CDF0 | `title_dispatcher` | 1,128 | 285/291 | 5 | 0 |
| 0x00432CB0 | `name_entry_update` | 1,400 | 368/378 | 10 | 0 |
| 0x00433EF0 | `ui_final_runtime` | 2,796 | 733/741 | 8 | 0 |
| 0x00436DA0 | `font_atlas_fill_transparent` | 946 | 285/316 | 16 | 0 |
| 0x0043C550 | `camera_shake` | 439 | 133/134 | 2 | 0 |
| 0x0043EE30 | `anm_vm_tick` | 9,964 | 2,730/2,755 | 13 | 0 |
| 0x004465B0 | `anm_texture_fill_transparent` | 1,463 | 369/499 | 73 | 0 |
| 0x0044A190 | `joystick_poll` | 833 | 271/282 | 5 | 0 |
| 0x0044DF70 | `ecl_start_child` | 550 | 144/165 | 21 | 0 |
| 0x0044E1A0 | `ecl_core_interpreter` | 7,020 | 1,769/1,790 | 10 | 9 |
| 0x00450220 | `ecl_name_table` | 589 | 194/198 | 4 | 0 |

Promoted since: `game_main` (0x00438AD0) is byte-exact through its LTCG
cluster `layout/ltcg/game_main.json` (2026-10-17); its three `/EHsc` callees
are shaped stand-ins, because an ordinary non-`/GL` context cannot give them
their private stack-receiver conventions (`game_main_00438ad0_exact_2026_10_17.md`).
`familiar_refresh` (0x00426F70) is byte-exact through
`layout/ltcg/familiar_refresh_00426f70.json`: one scaled-row accessor at the
carried offset gives the x-pair loads retail's temporary parity
(`familiar_refresh_00426f70_exact_2026_10_17.md`). `midi_tick` (0x0043AF30) is
byte-exact through `layout/ltcg/midi_tick_0043af30.json`: the track element
pointer written as `&table[index]` keeps retail's named-value order
(`midi_tick_0043af30_exact_2026_10_17.md`). `enemy_data_start` (0x0040DC80) is
byte-exact through `layout/ltcg/enemy_data_start_0040dc80.json`: permuting the
BindName helper's parameters fixes the result register and the argument load
order (`enemy_data_start_0040dc80_exact_2026_10_17.md`).

`result_rows` (0x00422660, 1,062 bytes) is byte-exact through
`layout/ltcg/result_rows.json`: escaping both selection-word addresses
reproduces retail's load order without a barrier. `replay_save_update`
(0x00433570, 1,460 bytes) is byte-exact through
`layout/ltcg/replay_save_update.json`: sixteen named, used menu predicates
reach the operand-hash window and close both SIB bytes. See their
`*_exact_2026_10_17.md` notes. This supersedes the earlier claim below that
readable source cannot reach the replay-save window.

## How to continue

- **The 2026-10-18 campaign's operating rules** (all learned the hard way):
  (1) the byte gate is the only gate — instruction-hunk movement without byte
  closure is not progress; (2) semantic audit BEFORE codegen levers — most
  closing levers were mis-transcriptions (a re-read, a guard scope, a store
  order, a case gate); (3) shared production-cluster files are byte-pinned by
  the whole-.text gate — region-local decls/stand-ins live in
  `build_support/contexts/equivalent/game/context/` and any change touching
  shared files needs a full `build_msvc.py` gate in the sandbox first;
  (4) dead scaffolding that only moves symbol ids is padding and is not
  shipped (ecl_core_interpreter's SIB window is reachable only that way —
  recorded as mechanism knowledge); (5) per-region sandboxes + a
  `STATUS.md` per milestone make the work resumable.
- **Promote what already matches.** Compare a model's relocated bytes with
  retail, not only the gate's verdict (it accepts branches to identical tail
  copies). The promotion recipe (cluster + regions.json cutover + measured
  contribution sizes) is in `th10-new-cluster-from-existing-context` (memory)
  with worked artifacts under `/tmp/campaign/{mgr_teardown,point_count,hint,
  front_tick,font_draw,anim_change,replay_menu,player_reset}/`.
- **Per region:** read its recovery note (each ends with what is left and
  the levers already tried), measure with
  `equivalence.py --layout build_support/layout/equivalent/<name>.json`, and
  compare retail and model listings side by side.
- **Fix context before the body.** Earlier "impossible" allocator residuals
  were closed by changing the cluster context (real callee bodies,
  escaped-global structs, callee parameter order/convention, opaque callees
  where retail reloads `this`), not the function body.
- **Check the semantics and sibling decomps first.** The laser interpreter
  0x0041CA80 went byte-exact once its model was made semantically right; the
  joystick reader went 156 → 16 differences in the th06 decomp's shape.
- **After changing any shipped model:** re-record its differences with
  reviewed classes (never dedupe the lists), run `make`, `make EXACT=1`,
  `make abi-check`, the unit tests, and, for gameplay code, a
  `matching2/tests/replay_sync/` replay.
- **Runtime work** happens in `matching2/build/behavior/` (copied game files,
  separate Wine prefixes `wineprefix`/`wineprefix2`, Xvfb :91/:92). Never kill
  the default Wine server: the MSVC toolchain uses it.
- The c2 tracers live in `matching2/reference/compiler_traces/` (usage line at
  the top of each); they replay a recorded compile/link command from the
  model's work directory.

## What was learned about the compiler (the reusable assets)

1. **The c2 priority law is decoded and validated** (joystick note,
   addenda 3–6): priority = Σ covered-block W×A×L − Σ uncovered-block
   A×L; W = 4 ordinary / 2 addressing-base / loop-depth+1 loop tuples.
   Live tracers: `matching2/reference/compiler_traces/regalloc/trace_accum.py`, `trace_refs.py`;
   landmarks: ChoosePhysReg 0x107AAB62, driver 0x107A926D, picker
   0x107A9D71, per-reference value 0x107A99D9.
2. **Parameter-lowering rule**: an incoming register parameter that is
   live across a call AND written after it gets a memory home — the
   0x0044A190 spill is unavoidable at source level.
3. **/INCLUDE roots freeze declared ABIs**; interprocedural register
   reassignment only reaches call-graph-reached receivers (frame_timer
   bisection).
4. ** volatile parameter splitting** defeats CSE and reproduces retail's
   disjoint live ranges (projectile Spawn prologue breakthrough).
5. **Volatile on storage forces retail's x87 operand order** (frame_timer
   precedent, reused by familiar refresh).
6. Scope-size ladder (does a bigger /GL scope reproduce retail's
   choices?): **final verdict delivered** — no movement at 0/9 extras;
   the 100+/150 rungs are unmeasurable under this wine (cl's
   /showIncludes emission truncates nondeterministically as TU count
   grows, even with file redirection). Combined with the decoded-formula
   proof (priority is a fixed function of the reference structure,
   identical between draft and retail), retail's flip must come from a
   c2-internal component outside the decoded accumulation — the two
   remaining RE targets are the block-weight assignment and the
   initial-home pass. The batched-ladder harness lived in
   `scratch/eclstart/` and was deleted with the scratch trees on 2026-10-14;
   it has to be rebuilt for a future wine upgrade.
7. **The operand-order hash window is decoded** (`replay_save_update`
   note): `OptCmpHashVal` gives a temporary `0x10000 + ((id << 6) & 0xFFFF)`
   and the larger hash becomes the first operand, so the **base/index
   encoding choice** is a pure function of the two temps' symbol ids. The
   symbol table grows in **slabs of 32**, and only *expression-valued*
   declarations move it (bare declarations fold away first). Consequence
   for the 33 equivalent regions: symbol pressure reaches base/index
   **only**, and the window is narrow and non-monotonic, so the target is a
   specific id range rather than "more symbols". Its boundary is now
   measured, not assumed:

   | residual class | moves with symbol count? | measured on |
   | --- | --- | --- |
   | `base-index` encoding | **yes** | `replay_save_update` 2->1 swap, `ecl_core_interpreter` 96->4 |
   | `register-choice` | no | 18 variants on `laser_rectangle_split`, zero movement |
   | `operand-order` instruction | no | 9 pressure levels on `player_reset_block_initialize`, all identical |
   | `evaluation-order` | no | 15 variants on `camera_shake` |

   Only three regions carry base/index swaps at all (`ecl_core_interpreter` 96,
   `replay_save_update` 2, `replay_submenu` 1), so this lever cannot close the
   other 30. Named constants are genuine source and land one of
   `replay_save_update`'s two swaps; the rest of the window needs declarations
   that leave no code and no structural trace (IDA and Ghidra agree the bodies
   are complete).

   Tools for this: `tools/matching/byte_exact_survey.py` (is any region
   byte-identical yet), `tools/matching/diff_dump.py` (what bytes differ and
   around which instructions), `tools/matching/variant.py` (sweep source
   spellings, ~2 s per build), `tools/matching/context_probe.py` (sweep the
   `/INCLUDE` roots and cluster context).

   Update from the two promotions above: **used boolean predicates** are
   another legitimate way to reach the symbol window. Naming 12 existing
   replay-save conditions fixes one SIB byte; naming 16 fixes both. The
   earlier conclusion that only invented padding can reach it is superseded.
   For load-order residuals, escape the exact global symbols the model reads:
   result rows closes both loads this way; escaping an unrelated aggregate
   symbol or the score-pointer global is insufficient.

   For scheduling residuals, `compiler_traces/scheduler/trace_scheduler.py`
   (fed a `commands.json` from
   `build/experiments/allocator_oracle_2026_10_17/prepare.py`, with the
   leading `wine` stripped) prints every pick with its priority. Decoded from
   the `fl` flag, `static = (path + succ22) << 10 + bonus`, where the bonus
   class is:

   | `fl` | bonus | meaning |
   | --- | ---: | --- |
   | `04`, `05`, `25` | `32` | memory read (the item-1 `+32 if load`) |
   | `02`, `03` | `8192` | a second, much heavier class (seen in `manager_teardown`) |
   | `00`, `01`, `08`, `09`, `21` | `0` | ordinary |

   The `8192` class is worth 256 loads, so where such a node is *ready* it
   wins outright. In practice readiness usually gates it: across 45 graphs in
   `projectile_command_runtime2` the eight `fl=03` nodes are picked
   second-to-last, immediately before the `fl=21` node that closes every graph
   (almost certainly the epilogue). So the class explains a schedule being
   pinned rather than merely weighted — the residual is what sits *before* it,
   and no amount of source reshaping moves a node whose successor is the
   epilogue. Verified over 86 picks (`result_rows`), 204 (`manager_teardown`)
   and 215 (`projectile_command_runtime2`); one `fl=01` node in `result_rows`
   carries `-1`, an unexplained single-node anomaly.

   For stack-layout residuals, `compiler_traces/stackpack/trace_stackcolors_cl.py`
   dumps `colorElemental`'s element list (kind, size, weight, conflict set)
   and the `ColorStackElements` colour order. It was broken here — it armed
   its breakpoint before `c2.dll` was mapped, so gdb parked it and every run
   ended in `ERR error('No registers.')`; it now waits on
   `set stop-on-solib-events 1` until the module is in `gdb.objfiles()`
   before arming. Verified on two units. Note that a unit whose compile never
   reaches the colour pass produces no dump at all (that is the case for
   `name_entry_update`).

The ECL core now has only 23 differing bytes: 11 SIB bytes and 12 bytes
addressing the swapped integer-add/subtract result homes. The apparent
`esp+0x28/0x2c` pair is the same storage after two pushes. Use
`compiler_traces/stackpack/trace_stackcolors_link.py commands.json out.txt
Run@EclVm` for actual LTCG colours; the pre-change trace has 95 elements,
64 colours and both result homes at weight 6. The camera scheduler trace
also establishes readiness, rather than a sequence-number tie, as the cause
of its remaining FIDIV move. Their recovery notes link the complete traces.

## Whole-value signatures (survey all 33, do not guess per region)

Comparing every equivalent layout against retail found three residual classes
that are *whole-value* mismatches rather than per-instruction drift. These are
the ones a source change can be decisive about, and they are best attacked by
surveying all 33 first:

| class | extent | signature |
| --- | --- | --- |
| frame gap | 4 regions | the prologue's `sub esp` differs by whole slots |
| `push ecx` dead slot | 39 hunks, 10 regions | retail keeps an argument slot and `pop ecx` on each exit |
| alignment filler | 49 hunks, 15 regions | `lea reg,[reg+0x0]` differing only in the register |

**The alignment fillers are symptoms, not causes.** In all 16 regions that
carry one, every filler sits *after* the region's first differing byte —
verified by comparing each layout's earliest difference offset with its
filler offsets. They follow from an earlier length change (a 3-byte
`cmp eax,1` against a 2-byte `test eax,eax`, a missing `push ecx`), so the
filler's form and register are whatever the compiler needs at that alignment.
Do not chase the 49 hunks directly: fix the earlier length difference and
they resolve.

**Root causes** (earliest non-filler difference in each layout, surveyed over
all 33) cluster into five families:

| family | regions | first difference |
| --- | --- | --- |
| register choice | `manager_teardown`, `ui_final_runtime`, `recovery_script_executor`, `font_atlas_fill_transparent`, `replay_submenu`, `laser_rectangle_split`, `anm_vm_tick`, `ecl_name_table` | `mov eax,X` against `mov ecx/edx/ebx/esi,X` |
| frame / prologue | `item_update`, `name_entry_update`, `replay_save`, `enemy_execute`, `joystick_poll`, `anm_texture_fill_transparent`, `font_atlas_draw_text` | `sub esp` size, or a `push` the model omits |
| scheduling | `camera_shake`, `result_rows`, `projectile_command_runtime`, `front_script_tick`, `projectile_point_count` | an x87 op or a load hoisted across a store |
| control flow | `title_dispatcher`, `ecl_start_child`, `projectile_spawn_cell`, `laser_circle_split`, `laser_circle_trim` | `cmp`/`test`, `jl`/`jge`, or a store against a load |
| missing store | `replay_runtime_bootstrap`, `ecl_core_interpreter`, `animation_change_script`, `player_reset_block_initialize`, `hint_save` | retail has an instruction the model does not |

`replay_frame_step` and `replay_save_update` have no recorded hunks at all —
their residuals are pure encoding (four `rel8` bytes; two `SIB` bytes).

**Shape ranking** — comparing instruction *shapes* (registers and literals
normalised away) separates "structurally wrong" from "same structure, different
register or schedule". Seven regions have **no shape difference at all**, so
their entire residual is register assignment, scheduling or position:

| layout | shapeΔ | recorded hunks |
| --- | ---: | ---: |
| `replay_frame_step` | 0 | 0 |
| `replay_save_update` | 0 | 0 |
| `camera_shake` | 0 | 2 |
| `front_script_tick` | 0 | 3 |
| `result_rows` | 0 | 3 |
| `ecl_core_interpreter` | 0 | 12 |
| `projectile_command_runtime` | 0 | 17 |

then `animation_change_script` and `laser_rectangle_split` at 2 (each one
`test r,r` against `cmp r,r`), `joystick_poll` at 2, up to `enemy_execute`
at 88. These seven are the ones a register- or schedule-level change would
complete outright; everything above them also needs a structural change.

Measured outcomes:

- **frame gap** — `item_update` (8 short) is closed by `volatile double dx`,
  which also improves the match by 214 differing bytes. It remains unshipped:
  retail has no qword floating-point stores, so the added rounding needs
  investigation. `replay_save` (8 long)
  is half closed by sharing `user_written`/`remainder` into `written`'s slot;
  `joystick_poll` (8 short) does not respond; `enemy_execute` (16 short)
  responds (~9 hunks) but only to declarations with no purpose in the code.
- **`push ecx` dead slot** — six spellings of ordinary state fold away
  byte-identically in `name_entry_update`; the slot is the compiler's choice,
  not a declaration.
- **alignment filler** — the register is the only difference
  (`ebx`/`ecx`/`esp`), and the same filler appears one block earlier or later.

Also measured: **0 of 33 bodies are code-exact, 23 tails are exact**.
`replay_frame_step` is structurally the cleanest (no recorded hunks, tail
exact, four `rel8` bytes out).

## The mechanism rule catalog (read this before attacking a region)

The `msvc-c2-*` / `msvc-*` / `th10-*` rule names the recovery notes cite are
real documents: **61 of them** live in
`/home/levzzz/.claude/projects/-home-levzzz-Games-th10Decomp/memory/`, with
`MEMORY.md` as the index. They are the written-up compiler mechanisms, and
several name levers that a source sweep would never guess. The ones that
matter most for the parked regions:

- `th10-parked-models-may-be-semantically-wrong` — **allocator residuals are
  often the symptom of a different CFG/case set, and a c2 trace cannot reveal
  a missing case.** Four documented regions (0x0041CA80, 0x00426F70,
  0x00414900, 0x004067D0) were parked as register/scheduling problems and were
  actually mis-transcribed: a missing `case`, a reversed ternary, a wrong call
  argument, an unsigned compare against retail's `jl`, a loop in the wrong
  branch, a record base out by a stride. Walk retail's switch tree and every
  block's effect against the model *first*.

  Applied to the 17 regions whose sources contain a `switch`. With a parser
  that handles hex and decimal labels, **9 match exactly**
  (`ecl_core_interpreter`, `front_hud_update`, `name_entry_update`,
  `projectile_spawn_cell`, `recovery_script_executor`, `replay_save_update`,
  `result_rows`, `title_dispatcher`, `ui_final_runtime`); `enemy_execute` also
  matches (129 = 129). **Caveats that make raw counts useless:** ghidra
  enumerates the whole jump-table range (`front_script_tick` 0..23 against the
  source's 0..6), renders some labels as float literals (`item_update`'s
  `case 5.60519e-45`), and decompiles small switches as if-chains
  (`camera_shake`, `font_atlas_fill_transparent` show 0 cases). The residual
  "source-only" labels are mostly the real opcode/flag values ghidra's
  if-chain form does not show: `enemy_execute` 10/15/20/25/30/35,
  `projectile_command_runtime` 1024/16384/131072/1048576/16777216/134217728
  (flag bits), `item_update` 5/7/8/9/10/11. A real gap needs the *distinct*
  values to differ, not the count.
- `msvc-c2-what-adds-a-register-candidate` — what changes `K` without changing
  the code: a named local passed to a real call, an expression written twice
  and merged late, an immediate used twice with one type. Applied to
  `laser_rectangle_split` (six shapes): the three that compile fold back byte
  for byte, so `K` does not decide that contest.

  The trace the rule calls for is runnable:
  `compiler_traces/regalloc/trace_spillcosts.py <commands.json> <out> 3000`
  (fed the `prepare.py`-generated commands with the leading `wine` stripped)
  dumps `BLOCK K=… weight=…` per basic block with each candidate's refs and
  running priority; `summarize_spillcosts.py` reduces it to one line per block.
  Caveat: like `trace_choose_physreg.py` it spans the whole link, so blocks
  still have to be correlated with the target function by hand.
- `msvc-c2-choosephysreg-cost-score` — the score is
  `Σ preferences of unallocated conflicting candidates + 100*f40 per rival
  whose only register it is − own preferences`; lowest wins, ties ESI/EDI/EBX.
  "The fix is fewer simultaneously live values in that block, not more
  priority elsewhere."
- `msvc-x87-corner-tests-shape-levers` — for `projectile_point_count`:
  double constants (`* 0.5`) force store+reload rounding and a qword constant,
  which is that region's unsolved y-in-memory/x-on-stack asymmetry. Its
  `0.5f` spelling needs the `__real@3f000000` binding replaced to test.
- `th10-overnight-2026-10-17-lever-outcomes` — what the overnight queue found
  across 30 regions: canonicalization boundaries, overshoots not to repeat,
  and the trace-blocked families.

## History

- 2026-10-19: `projectile_command_runtime` 0x00406D90 is promoted after the
  round-2 model closed byte-exact. The promotion needed a cluster that compiles
  the model's nine callee bodies from their own sources (splitting the two
  merged `zz_` context sections) so each is anchored at its retail address;
  the compiler emits the switch tables inside the contribution, so the region
  is declared at 1,604 bytes rather than its 1,456-byte code extent.
  Byte-exact 82.9% -> 83.4%; 21 equivalent regions remain.
- 2026-10-19: `projectile_spawn_cell` 0x004067D0 closes byte-exact: writing
  its lit-step scale as the literal `4.0f` instead of the external `flt_4`
  gives the operand a different symbol class, so the operand hash orders the
  three products as retail does.
- 2026-10-18 (round 2): a second 23-region campaign closes and promotes two
  more — `front_hud_update` 0x00414900 (16 bytes: the two `fadd` operand
  orders flip once the addends are written as literals, which gives them the
  compiler-literal symbol class instead of an external `float` symbol) and
  `projectile_command_runtime` 0x00406D90 (84 bytes: the 0x210-byte scan
  buffer moved into its `case 0x400000` block, then the store order
  `rows, y_tail, flags, x_base, x_spacing` and `command_index` after
  `y_head`). Byte-exact rises 81.7% → 83.4%; 21 equivalent regions remain.
  The same round cut the parked residuals: `ui_final_runtime` 1,287 → 32
  bytes (call-site argument permutation, folded id lvalues, in-place
  `MusicCreateInPlace` temp), `laser_rectangle_split` 14 → 1 byte (nested
  guard keeps the counter in EAX for the zero test), `replay_save` 43 → 29
  hunks, `enemy_execute` 53 → 46 hunks, `recovery_script_executor` 35 → 34
  bytes.
  The round's negative results are recorded in the per-region notes with the
  mechanisms that pin them: `camera_shake` (FP true-dependency builder cannot
  produce retail's ready cycle 24), `replay_frame_step` (label forwarding),
  `ecl_core_interpreter` (stack-colour pair order), `ecl_name_table`
  (copy-block candidate), `laser_rectangle_split` (zero materialisation vs
  the guard compare), `replay_runtime_bootstrap` (address-CSE use set),
  `font_atlas_fill_transparent` (piece granularity), `joystick_poll`
  (ChoosePhysReg class order), `anm_vm_tick` (strip rotation vs select phi),
  `ecl_start_child`, `laser_circle_split`/`_trim` (K accounting),
  `recovery_script_executor`, `name_entry_update` (zero-reference colour-0
  element), `item_update`, `anm_texture_fill_transparent`, `replay_save`,
  `enemy_execute`, `title_dispatcher`, `ui_final_runtime`.
- 2026-10-18: the parallel campaign (31 region agents + Ghidra semantic
  audits + c2 tracer archaeology) promotes EIGHT regions to byte-exact —
  manager_teardown 0x00417C80, projectile_point_count 0x004084A0, hint_save
  0x0041A200, front_script_tick 0x00415E90, font_atlas_draw_text 0x00437FE0,
  animation_change_script 0x0043E8B0, replay_submenu 0x004236F0 (its 2,088
  differing bytes closed to zero), player_reset_block_initialize 0x004247F0 —
  and improves every remaining region to a measured best state (replay_submenu
  2,088→0 promoted; enemy_execute 12,139→53 hunks/97.0% identical; item_update
  1,991→900 bytes; laser_rectangle_split 313/316→315/316; front_hud_update
  684→16 bytes; projectile_spawn_cell 1,150→24 bytes; recovery_script_executor
  505→35; player_reset 217→0 promoted; anm_vm_tick 8,185→88; ecl_name_table
  366→23; ui_final 1,640→1,287; replay_save frame gap closed). Byte-exact
  rises 77.4% → 81.7%; identical-instruction share 97.9% → 99.2%.
  Decoded this session (all in the recovery notes + memory): the c2 label-
  forwarding predicate and identity-mov deletion rule; the operand-hash wrap
  arithmetic (slab-32 free lists vs ±1 live locals); the ChoosePhysReg score
  tie-breaks (two full K-accounting reconciliations); the SpillObvious
  piece-formation rule; the stack-colour sort (middle-pivot Lomuto); the
  GrgChangeRegToImmed f40 rematerialisation gate; the CmdCanEnregImmed
  kind-1 exclusion; the disp-less-base address-CSE invariant; the
  callee-parameter-order call-lowering tie. Several residuals are proven
  retail-IR properties (replay_frame_step's 4 rel8 bytes, replay_runtime_
  bootstrap's addressing form, laser_circle_split's literal-pair K gap,
  recovery_script_executor's forced trio, ecl_core's SIB window — each needs
  symbol populations no honest spelling reproduces).

- 2026-10-17: ECL core interpreter improved from 116 to 23 differing bytes
  (96 to 11 SIB swaps); both address-order hunks removed. No new region
  promotion in this pass: 31 equivalent recoveries remain. Actual LTCG
  stack tracing identifies the two remaining result homes as opcodes 50/52.

- 2026-10-17: result rows 0x00422660 and replay-save update 0x00433570
  promoted to byte-exact native LTCG (2,522 bytes); byte-exact rises to
  77.4%, with 31 equivalent regions remaining. The reusable fixes are
  escaping the globals actually read and naming existing used predicates.

- 2026-10-17: 0x00438AD0 GameMain promoted to exact (its LTCG cluster keeps
  fourteen real callee bodies as anchors and shapes stand-ins for the three
  `/EHsc` ones); 0x00426F70 familiar refresh made byte-exact (a scaled-row
  accessor at the carried offset) and promoted; 0x0043AF30 midi tick made
  byte-exact (the `&table[index]` element pointer) and promoted; 0x0040DC80
  enemy data start made byte-exact (BindName parameter order) and promoted;
  0x0043E8B0 animation change script raised to 64/66 (the shared 0x200
  candidate removed, every register right); byte-exact rises to 76.7%.
- 2026-10-16: 0x0042E5A0 options label refresh made byte-exact; font atlas
  blend 0x00437750 and D3D initialize 0x00439890 promoted; 0x00415E90 result
  dispatcher raised to 1,144/1,147.
- 2026-10-16: readability plan completed (globals, identifiers and files named
  by owner); see `matching2/reference/readability_plan_2026_10_16.md`.
- 2026-10-14: last inline-assembly regions replaced by equivalent recoveries;
  runtime validation and `make abi-check` added
  (`equivalent_runtime_failures_2026_10_14.md`).
