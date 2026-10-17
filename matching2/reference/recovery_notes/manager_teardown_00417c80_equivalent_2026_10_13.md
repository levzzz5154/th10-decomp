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

Region stays equivalent (179 differing bytes). The byte residuals sit in the
evaluation-order runs (+0x3f0..+0x436) and the block-order pair; they need
the c2 list-scheduler trace before another source sweep.
