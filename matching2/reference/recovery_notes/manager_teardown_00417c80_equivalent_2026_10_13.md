# Manager-state teardown 0x00417C80: equivalent recovery

**Current status (2026-10-14): C++ repaired and registered; current validation is listed in the execution investigation.** The historical measurements below are superseded by [the execution investigation](equivalent_runtime_failures_2026_10_14.md).

Date: 2026-10-13

## Scope and result

`asm_FUN_00417c80_00417c80` (0x00417C80, 1105 bytes, 309 instructions) is
recovered as an **equivalent recovery**: the readable C++ under
`matching2/msvc/equivalent/game/manager_teardown_00417c80.cpp` compiles, in a
native /GL + /LTCG link that carries the whole-program context of the cluster
`layout/ltcg/manager_state_release_00417c80.json`, to a body that agrees with
retail on 283 of 309 instructions; the remaining 26 instructions in 18 hunks
are recorded, reviewed differences (4 register-choice, 8 evaluation-order,
2 block-order, 4 code-shape) well inside the equivalence budgets. The verifying
layout is `matching2/msvc/layout/equivalent/manager_teardown_00417c80.json`;
`equivalence.py --layout` reports `not_equivalent: []`.

The region keeps its `asm` record for the exact link; registering the layout is
one `equivalent_recoveries` entry:

```json
{"region": "asm_FUN_00417c80_00417c80",
 "layout": "layout/equivalent/manager_teardown_00417c80.json"}
```

## Why not exact

The body is shaped by whole-program register allocation that a standalone
compilation cannot reproduce:

- Seven callees take an argument in a register no MSVC declaration names:
  the score archive reaches `Save` in EBX, the game thread reaches
  `EnsureAnimationResource` in ESI, the positioned-primary creation gets the
  position record in EDI, the enemy manager reaches `Destroy` in EAX, the score
  record reaches `IncrementCappedCount` in EAX, the resource registrar takes
  the manager in EAX and the name in EDX, and the side panel reaches
  `ReleaseStageParts` in EBX.
- `mov ebx,2` at the top materializes the replay-session flag into EBX; a
  standalone compile folds the constant into the `or`/`test` immediates. The
  byte-grain form returns once the rest of the body pins the allocator the way
  retail does (byte-typed variable, live across the Ensure calls).

## What the context link must contain

The layout's `context_cluster` names the cluster manifest, whose driver and
additional sources are linked beside the model so the whole-program pass derives
the register conventions above:

- the driver `layout/ltcg/manager_state_release_00417c80/context.cpp` carries
  the synthetic array-walking caller plus compiled ABI models for the
  positioned-primary creation's three private-argument callees (the pool
  allocator 0x00449950, the script loader 0x0043E710, the primary-list
  registration 0x004489D0) and of the creation itself, the same modelling the
  lazy-animation-fetch cluster carries;
- `src/game/score_manager_save.cpp` (Save) and
  `src/game/animation_resource_lazy_fetch.cpp` (Ensure) are included by the
  driver so their recovered bodies fix the EBX/ESI receiver conventions;
- `src/game/fun_0040d530_0040d530.cpp` (EnemyManager::Destroy, receiver in EAX)
  and the anchor models for `IncrementCappedCount` (EAX) and `RegisterResource`
  (EAX with the name in EDX) are additional sources.

In the equivalence link the compiled-in-link callees are bound through the
layout's `bindings` table (their model addresses resolve to the retail
addresses); everything else goes through `absolute_symbols`.

## Nonobvious points

1. **The mode 10 (0xA) arm is `EnsureAnimationResource` inlined.** Retail
   inlines exactly one instance - the first mode arm - and calls the function
   out of line in the 0xB/4/0xF/0xD arms. The arm is therefore hand-inlined
   with the body order of the recovered Ensure (position record built before
   the handle test). The handle is reached through the *loaded* game-thread
   value (`void** handle_slot = &data_004776e0->animation_handle;`), never
   through a kept base pointer: that is what makes the compiler materialize
   `lea esi,[ecx+0x89a4]` ahead of the creation call and free the game thread
   (ECX, caller-saved) before it. Spelling the store through the base pointer
   keeps the thread alive across the call and loses the byte-exact head.
2. **The position record and the out slot are separate locals** declared
   out-slot-first; the creation call receives `&slot_handle` on the stack and
   the position in EDI, and the handle store reads through the returned slot
   (`mov edx,[eax]; mov [esi],edx`).
3. **The mode flag is byte-typed and read back after the switch.** A dword
   flag folds into `test byte [flags],2`; the byte variable that lives across
   the Ensure calls is what retail materializes as `mov ebx,2` and tests with
   `test byte [0x474CA0],bl`.
4. **The destroy list keeps each pointer in a local.** Spelling the global at
   each use makes the compiler re-load it between the destructor and the free
   (it cannot prove the destructor keeps the global); a local is held in ESI
   across both calls, exactly as retail does. The replay-path state is the
   same shape.
5. **The tail reads the stage-end marker through a byte view.** Declaring the
   low byte of the run flags as its own `unsigned char` symbol
   (`flags_byte_00474ca0`, bound to 0x00474CA0) and spelling the bias as the
   ternary `(flags_byte_00474ca0 & 1) ? 0 : -0x1000000` produces retail's
   byte-grain `and al,1 / neg al / sbb eax,eax` (in the model it lands in DL -
   a recorded register-choice); the dword view produces the wider
   `and eax,1 / neg eax` form and a one-byte-shorter body, which also breaks
   the extraction window (the `IncrementCappedCount` call target then sits
   inside the code extent and cannot be relocated to 0x00418A90).
6. **`code_bytes` is 1105** even though the model body is one byte shorter:
   with the full extent declared the tail comparison is empty and the
   trailing-byte artifact is recorded as a `code-shape` difference instead.

## Remaining differences (all recorded, 26 of 309 instructions)

- `register-choice` (4): the resource load and out-slot lea registers in the
  mode-0xA block; the stage-end byte in DL instead of AL.
- `evaluation-order` (8): the mode reload vs the handle store; the
  `mov ecx,esi`/`mov edx,edi` pair order; the scheduler and import-pointer
  load order in the removal block.
- `block-order` (2): the enemy-manager Clear call block sits after the 0xD
  check in the model instead of before it.
- `code-shape` (4): the resource-index ternary compiled branchlessly
  (`mov cl/and cl/neg cl/sbb`) instead of the retail `test/je/push` pair, and
  the one-byte trailing artifact of the shorter body.

No call, branch or return is added or removed; the model calls exactly the
callees retail calls and names exactly the image addresses retail names.

## Files

- `matching2/msvc/equivalent/game/manager_teardown_00417c80.cpp` - the model.
- `matching2/msvc/layout/equivalent/manager_teardown_00417c80.json` - the
  verifying layout (registered by the `equivalent_recoveries` entry above).
- `matching2/msvc/layout/ltcg/manager_state_release_00417c80.json` with
  `context.cpp` and `anchors.cpp` - the context cluster (unregistered; only
  its source list is consumed through `context_cluster`).
- `matching2/msvc/include/th10/game/manager_teardown_00417c80.hpp` - the
  object views and global bindings the model shares with the cluster.

`matching2/msvc/regions.json` is unchanged; `src/game/manager_teardown.cpp`
still carries the naked region for the exact link.

## 2026-10-17: the branchless ternary probed; parked

The resource-index ternary (`(g_sound_flags & 0x10u) ? 4 : 3`) rewritten as
an `if`/`else` with the `RegisterResource` call in both arms (the retail
`test`/`je`/`push` tail-merged shape) removes the three code-shape
instruction hunks and adds only the two-byte trailing artifact. Measured
with the real byte gate afterwards: **the region's differing bytes are
unchanged at 179** — the ternary area still differs at the byte level even
where the instruction text matches, exactly the case the instruction verdict
hides. Reverted: the change is instruction-level churn with no byte benefit.

Region stays equivalent (179 differing bytes).

## 2026-10-17: the temp-rotation lever fixes the register rotation

`msvc-c2-temp-register-rotation-named-local` names this residual exactly:
"same instructions, but from some call on every reloaded pointer is one
register further (ECX/EDX where retail has EAX/ECX)", with the fix being to
name the first diverging call's argument. Applied here to
`AnimationManager_CreatePositionedPrimary(g_ascii_manager->animation_resource,
&slot_handle, 6, &position)`, against the baseline 291/309, 15 hunks, 179
differing bytes:

| variant | identical | hunks | differing bytes |
| --- | --- | ---: | ---: |
| baseline | 291/309 | 15 | 179 |
| **`name-arg`** (`void* anim_resource = …` before the call) | **294/309** | **12** | **175** |
| `name-both-args`, `name-at-scope` | 294/309 | 12 | 175 |
| `name-slot-arg` (only the stack address named) | 291/309 | 15 | 179 |
| `inline-the-local` | — | — | a branch retargets |

Naming the resource argument removes the first three hunks (@0x68, @0x70,
@0x75) outright — the `mov eax,[ecx+0x8994]` / `lea ecx,[esp+0x14]` / `push`
triple now matches retail register for register. The residual starts at
@0x81, a load-position difference, and @0x307, a block-order pair. Naming
only the stack-address argument does nothing, so it is the *expression*
argument that advances the rotation, as the rule says.

This is the first lever this pass has found that removes hunks outright on a
register-choice region. It is not landed: 12 hunks remain and shipping it
would mean re-recording the whole difference list. The next session should
start from `name-arg` and work the remaining @0x81 and @0x307. Region stays
equivalent. The byte residuals sit in the
evaluation-order runs (+0x3f0..+0x436) and the block-order pair; they need
the c2 list-scheduler trace before another source sweep.

## 2026-10-18: byte-exact — the head rotation, the tail shift and the escaped block

The region is now byte-identical: `variant.py` reports `*EXACT*` (309/309
instructions, 0 differing bytes, 0 tail bytes) and `equivalence.py --layout`
reports `"differences": []`, `"not_equivalent": []`, `base_index_order: 0`,
`frame_offset: 0`. All 15 recorded hunks closed with six levers; the last
difference was closed by the escaped-aggregate lever (item 6).

1. **`name-arg` landed** (the 2026-10-17 probe, unlanded until now): naming
   the positioned-primary creation's resource argument (`void* anim_resource =
   g_ascii_manager->animation_resource;`) fixes the head's register rotation —
   `mov eax,[ecx+0x8994]` / `lea ecx,[esp+0x14]` / retail push order return
   as recorded.
2. **The tail shift was a transcription bug**: retail re-reads `g_func_ctrl`
   (0x00491BE4) before *each* removal block (`mov edi,[0x491be4]` at
   0x418005 and again at 0x418045 — the locked remove may republish it). The
   model read it once and reused the register, and the missing 6-byte load
   shifted everything from +0x3c5 to the epilogue. Re-spelling the second read
   (`scheduler = g_func_ctrl;`) collapses that entire recorded run. This is
   what the old note called "the evaluation-order runs (+0x3f0..+0x436)".
3. **The enemy if/else inverted** (`if (!(g_globals_flags & 9u)) { destroy }
   else { EnemyCtrl_Clear2(...) }`): the negative condition puts the destroy
   path on the fallthrough and the Clear call block after it — retail's block
   order (c2 lays the branch fallthrough first, so the old spelling's
   then-block-on-fallthrough placed Clear first).
4. **The resource-index ternary spelled as an `if`/`else` with one
   `RegisterResource` call per arm** yields retail's tail-merged
   `test byte [0x491d78],0x10 / je / push 4 / jmp / push 3` shape. The
   2026-10-17 probe's "differing bytes unchanged" verdict was an artifact of
   the tail shift (item 2) masking the area; on the fixed tail the same
   spelling closes the code-shape hunks and their byte shift.
5. **`FuncCtrl_Remove` compiled in-link** (the driver now includes
   `src/core/zunlib/scheduler_tasks.cpp` under `TH10_SCHEDULER_REMOVE_ONLY`;
   the layout binds `_FuncCtrl_Remove@8` to 0x00449F60 — verified by the
   semantic region `semantic_FuncCtrl_Remove_00449f60` — and drops the same
   symbol from `absolute_symbols` so the compiled body can define it). The
   whole-program pass then derives the private convention (task in ECX, the
   scheduler in EDX) and, as the func_ctrl.hpp note says, loads ECX first at
   the call: both `mov ecx,esi`/`mov edx,edi` pairs emit in retail order. The
   bare `__fastcall FuncCtrl_RemoveTask` spelling loads EDX first. This is the
   same in-link body spelling the sibling teardown clusters use.
6. **The escaped-aggregate lever closed the last difference** (@0x81, 7 bytes
   at 0x81-0x87): retail stores the created handle (`mov [esi],edx`) before
   the mode reload (`mov eax,[0x491fb8]`), the model reversed them. The two
   are independent scheduler nodes (the load carries the +32 bonus) unless the
   store may alias the loaded global. Reading the mode through the application
   state block — `g_supervisor.next_state` (0x00491FB8 = Supervisor +0x3B8,
   `th10/app/supervisor.hpp`) — and letting the block's address escape in the
   context driver (`if (count < 0) states[0] = &g_supervisor;`) forces the
   store first. This is exactly the `msvc-escaped-global-struct-aliasing`
   symptom "a store of a call result placed after the next global load where
   retail stores first".

Ruled out, with measurements:

- `name-arg` alone: 175 differing bytes / 12 hunks (confirms the 2026-10-17
  probe); `reload-assign` alone: 119 bytes; both together: 115.
- `reload-assign` vs `reload-local` (a second named local): byte-identical —
  any spelling of the per-block re-read works.
- `enemy-goto` (`if (c) goto clear; ...; goto done; clear: ...`): does not
  flip the block order (179 bytes on base, 44 with the other levers); only the
  inverted condition does.
- The ternary→if/else rewrite alone keeps bytes at 179 while clearing three
  instruction hunks (re-confirms the overnight finding) — it pays only after
  item 2.
- `sup-noesc`: supervisor member reads without the address escape keep the
  7-byte residual unchanged — membership alone is not the lever, the escape
  is. The `esc-cond`, `esc-star` and `esc-uncond` escape spellings are
  byte-identical; the kept one is the guarded `if (count < 0)`.
- The scheduler trace was not needed in the end: the "heavy node pinned
  second-to-last before the epilogue" residual was the missing reload and the
  per-site move order, both transcription/ABI questions.

Files touched: the model, its header (the stale `g_main_state` extern is
replaced by a note pointing at the supervisor view), the cluster driver
(scheduler-remove body + address escape) and this layout (bindings gains
`_FuncCtrl_Remove@8`, `absolute_symbols` drops it and gains `_g_supervisor`,
`differences` is empty again). Region is byte-exact.

## 2026-10-18: promoted to exact — the region moves to the manager_state_release cluster

`semantic_Game_Destroy_00417c80` (`_Game_Destroy@4`, 0x00417C80, 1105 bytes)
is now a native-LTCG region of
`build_support/layout/ltcg/manager_state_release.json`; the assembly carrier
`build_support/exact/game/game/game_destroy.cpp` and the equivalent layout are
deleted. `build_msvc.py` links the whole .text to retail SHA-256
(`c1acff41…f56998`), `probe.py --source src/game/game/manager_teardown.cpp`
reports `0x00417c80  1105 bytes  _Game_Destroy@4  EXACT`, and both tool test
suites pass (60 + 27 tests).

Cluster-side mechanics, for the next promotion of this shape:

- **Schema 1 compiles the selected source only through the driver**: the
  driver now includes `manager_teardown.cpp` first (after
  `score_manager_save.cpp`/`animation_resource_lazy_fetch.cpp`, whose bodies
  the driver already carries). The lazy-fetch body brings the shared type
  declarations, so the driver defines
  `TH10_MANAGER_TEARDOWN_SHARED_TYPES_EXTERNAL` before the model include —
  exactly the contract the teardown header documents.
- **Section names order the link**: COFF concatenates `.text$…` sections
  lexically, so the contribution names must sort in retail-address order. The
  renamed pragmas: `Game_Destroy` `.text$05release` (was `$9release`),
  `IncrementCappedCount` `.text$05zzincr`, `RegisterResource` `.text$07reg`,
  `AnimationObject_LoadScript` `.text$07zzload`,
  `PanelResource2::Release` `.text$08resource`,
  `RegisterPrimaryBack` `.text$08zregback`,
  `CreatePositionedPrimary` `.text$08zsetprim`,
  `PoolAllocator` `.text$08zspool`; gap sections are the preceding
  contribution's name plus `z` (first gap `.text$00gap`), keeping the
  title_teardown naming discipline. The four shared-source sections
  (`.text$01lazy`, `.text$02b`, `.text$06score`, `.text$70remove`) were left
  untouched and already sort in address order.
- **Measured contribution sizes** (the loader requires each declared size to
  equal the compiled contribution; these are this link's actuals):
  `Game_Destroy` 1105, `EnemyCtrl_Destroy` **289** (the old anchor said 305 —
  stale), `ScoreArchive_Save` 567, `FuncCtrl_Remove` 114 (new anchor at
  0x00449F60 in `.text$70remove`, the scheduler-remove body from
  `scheduler_tasks.cpp`), and the compiler context
  `_ManagerReleaseContext_00417c80@8` **54** (was 39; the supervisor-escape
  line costs 15 bytes).
- **Wrappers keep ownership clean**: `enemy_ctrl_destroy.cpp` is compiled
  through the new one-line wrapper
  `build_support/layout/ltcg/manager_state_release/destroy_body.cpp` (it owns
  the 0x0040D530 region, which would otherwise collide with the cluster's
  function/ownership check) and is listed in `included_sources` beside
  `scheduler_tasks.cpp`. `CreatePositionedPrimary`'s anchor symbol was stale
  (an old four-argument spelling) and now carries the model's real mangled
  name.
- `regions.json`: the region record converts with `previous_record`, the
  cluster joins `ltcg_clusters`, `translation_units` swaps the carrier for
  `src/game/game/manager_teardown.cpp`, and the `equivalent_recoveries` entry
  goes. The stale `symbols` aliases for the old asm name stay, as in the
  enemy_data_start promotion.

Region is exact.
