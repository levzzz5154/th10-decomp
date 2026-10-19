# Script executor 0x0040BD80: accepted as an equivalent recovery (2026-10-14)

`equivalent/game/recovery_script_executor_0040bd80.cpp` through
`layout/equivalent/recovery_script_executor_0040bd80.json`: 1,564 of 1,568
bytes (code plus the 18-entry jump table), **400 of 444 instructions
identical**, 28 classified hunks (register-choice, evaluation-order, a
3-instruction code-shape, the case 13/14 block order and one table target).

The context is the marktext dispatcher cluster's driver and anchors, minus
its executor copy. Two of its files are replaced by equivalent-only copies
under `equivalent/game/context/`, so the registered marktext cluster keeps
building unchanged.

## What moved the count (305 -> 400)

- **Switch case order.** Source cases follow retail block order: 0, 3, 4, 5,
  6, 7, 8, 15, 16, 17, 9, 10, 11, 12, 13, 14. Case 10 is
  `strcmp(name, "bgm/th10_13.wav")`; with a real literal it folds to
  `repe cmpsb`.
- **ASCII factory 0x43C8B0 in its real shape** (as in
  `src/game/ascii_manager_create_retail_0043c8b0.cpp`). A constructor wipes
  the object and sets flag 2, then a noinline *member* `Configure` runs.
  With that context, LTCG passes draw priority 0x31 in EBX and the five
  stack words exactly as retail does. The old anchor (memset plus a free
  stdcall register function) passed the mode in EBX instead.
- **Handle validation 0x449450 is a free function** with the handle in ESI.
  Retail pushes no receiver for it. The shared context's `__cdecl` member
  spelling pushes the manager and then pops it.
- **Case 8 handle pointer:** `unsigned int* handle = &animation_handles[arg0]`,
  then SetFlag(*handle) and `*handle = 0`. This alone was worth +30. The
  out-record is a case-scoped local.
- **Case 3, ring == 0:** the post-loop MarkText reuses the `manager` local
  read for Find. The else branch is one expression,
  `Validate(...)->MarkText(data_00491c10, color, Decode(...))`.
- **Case 12:** an index loop with a plain manager read per iteration.

## Recorded residuals

- ESI/EDI and EBX/EDI choices in case 3 and case 12. Retail hoists the
  manager into EBX for case 12. The model re-reads it, a 3-instruction
  code-shape hunk.
- The else branch reads the manager before the Validate call; retail reads
  it after.
- LoadAsset: the owner load and the command-pointer store are emitted in
  another order.
- Cases 13 and 14 share their factory tail. Retail places case 13 first and
  jumps forward; the model places case 14 first.
- The flags `or 4` in case 7 uses EDX vs ECX.

## 2026-10-17: case-tail survivor levers probed; parked

The case 13/14 factory-tail placement (block-order hunk) does not move on the
documented survivor levers: swapping the case labels in source (the
switch-case-order lever) and ending the cases with `goto advance` to a shared
label (the screenshot-capture survivor flip) both leave the 28 hunks
identical — the two calls take different arguments, so the tail is a real
merge of two distinct blocks, not the duplicated-block shape those levers
target.

Region stays equivalent (505 differing bytes). The register-choice and
evaluation-order residuals are the same SpillCosts/scheduler families as the
other parked regions.

# recovery_script_executor 0x0040BD80 — append to
# matching2/reference/recovery_notes/recovery_script_executor_0040bd80_accepted_2026_10_14.md

## 2026-10-18: byte campaign — 505 -> 35 differing bytes (428/444 identical)

Work in `/tmp/campaign/recovery_exec` (layout `build_support/layout/equivalent/
recovery_script_executor.json`). Start: 400/444, 28 hunks, 501 code + 4 tail
bytes. Now: 428/444, 8 hunks, 35 code bytes, tail 0, jump table byte-exact,
`not_equivalent: []`, `base_index_order: 0`, `frame_offset: 0`.

### Levers that closed bytes

1. **SetFlag anchor: forward `id` without an entry-block copy.**
   `RecoveryScriptId script_id = { id }; Find(context, script_id);` made
   MdmFlexParams promote `id` to a register parameter (callers kept it in EAX
   and pushed the receiver). `Find(context, *reinterpret_cast<const
   RecoveryScriptId*>(&id))` reproduces retail's `MOV EAX,[ESP+4]; PUSH EAX`
   forwarding and keeps `id` stacked. 400->414 ident, tail 4->0 (the jump-table
   drift was this same flex move).
2. **SetFlag is a free function with an unused receiver parameter**
   (`RecoverySetFlag(void* receiver, RecoveryLookupContext*, int)`, binding
   renamed). An unused receiver is dropped outright (like `Find`'s); when it is
   forwarded to an inner call it takes a stack slot and every call site grows a
   second push. Retail's 0x00449630 (`push eax; call`) proved the one-push ABI.
3. **Case 12 manager hoist** — `RecoveryLookup* manager = ...g_sprt_ctrl;`
   before the loop. Retail hoists into EBX and copies `mov edx,ebx` per
   iteration; the per-iteration reload cost 4 bytes per loop body and the
   2-byte block delta. 424->61 bytes (biggest single lever).
4. **LoadAsset parameter permutation** (decl + anchor def + call + binding
   `?LoadAsset@@YGPADPAUAssetBuffer@@PBD@Z`) — the declared parameter order sets
   the caller's argument load order
   ([[msvc-ltcg-callee-param-order-sets-caller-load-order]]). 61->50.
5. **Case 7 statement swap** (`flags |= 4u` before `background_data = ...`).
   50->42.
6. **Else branch: named locals `else_text` then `else_color`** — shifts the
   RegAssign rotation ([[msvc-c2-temp-register-rotation-named-local]]); also
   cleaned the case-5 register hunk completely. 42->35.

### Ruled out (evidence)

- Overnight's case-order / goto-advance survivor levers (inert) — not repeated.
- `SetFlag` id typed `RecoveryScriptId` (member or free): 401/796, 402/502.
- Receiver forwarded to Find (member or free3): two pushes everywhere (424).
- Receiver unused but ctx re-read from the global in the body: one-push callee
  but callers spill the manager local (852).
- Free2/static without the case-12 hoist: 492.
- Else: volatile manager, volatile color, volatile-in-Validate-body ordering,
  split text, uncast receiver, ring named local, color/mgr local permutations
  (m1-m5), ring-position permutations (p1-p3): all unchanged at 35-53 or
  catastrophic (1198-1261 bytes when the Validate object becomes a local).
- Post-loop: color local, id int local, handle-local reset, ctx/first named
  locals, plain-g_sprt_ctrl manager, statement swap, MakeScriptId helper,
  unused dummies, for-increment swap, CreateModeSlotAnimation parameter swap:
  all no-ops at 35.

### What remains (35 bytes, 8 hunks)

- Case-3 post-loop 0xc8-0xfe: `id` in ECX vs EAX, manager EBX vs EDI, the
  handle pointer EDI vs EBX, and the MarkText color load (retail `mov
  edx,[ebp+0x7c]` before `push eax`; model pushes text then loads color into
  EAX — an EAX anti-dependence that pins the schedule).
- Case-3 else 0x114-0x12c: retail loads ring (ECX) then color (EAX); model
  color (ECX) then ring (EDX); retail loads+pushes `g_sprt_ctrl` after the
  Validate call, model before it.

Best mechanism hypothesis: the scratch rotation (RegAssign) is off by one at
the post-loop's first temporary and the callee-saved pair (ChoosePhysReg
EBX/EDI) is placed in the opposite order; per the rules these come from
Spillcosts priority / candidate numbering and the c1xx argument-tuple order of
the varargs `MarkText(void*, ...)`, not from statement spelling — the next
step is `trace_choose_physreg.py` symbol correlation (the trace for the
current build is at `/tmp/campaign/recovery_exec/tracework/phys.log`) rather
than more source sweeps.

# recovery_script_executor 0x0040BD80 — append to
# matching2/reference/recovery_notes/recovery_script_executor_0040bd80_accepted_2026_10_14.md

## 2026-10-18: byte campaign — 505 -> 35 differing bytes (428/444 identical)

Work in `/tmp/campaign/recovery_exec` (layout `build_support/layout/equivalent/
recovery_script_executor.json`). Start: 400/444, 28 hunks, 501 code + 4 tail
bytes. Now: 428/444, 8 hunks, 35 code bytes, tail 0, jump table byte-exact,
`not_equivalent: []`, `base_index_order: 0`, `frame_offset: 0`, and the layout's
`differences` records exactly the 8 remaining hunks (the whole-.text gate's
recorded-set check passes).

### Levers that closed bytes

1. **SetFlag stand-in: forward `id` without an entry-block copy.**
   `RecoveryScriptId script_id = { id }; Find(context, script_id);` makes
   MdmFlexParams promote `id` to a register parameter (callers keep it in EAX
   and push the receiver). Forwarding the slot directly reproduces retail's
   `MOV EAX,[ESP+4]; PUSH EAX` and keeps `id` stacked. 400->414, tail 4->0
   (the jump-table drift was the same flex move).
2. **SetFlag is a free function with an unused receiver parameter**
   (`RecoverySetFlag(void* receiver, RecoveryLookupContext*, int)`). An unused
   parameter is dropped outright (like `Find`'s `this`); when the receiver is
   forwarded to an inner call it takes a stack slot and every call site grows a
   second push. Retail's 0x00449630 (`mov eax,[esi]; push eax; call`) proves
   the one-push ABI. Declared locally, see "localized form" below.
3. **Case 12 manager hoist** — `RecoveryLookup* manager = ...g_sprt_ctrl;`
   before the loop. Retail hoists into EBX and copies `mov edx,ebx` per
   iteration. 424->61 bytes (biggest lever).
4. **LoadAsset parameter permutation** — the declared parameter order sets the
   caller's argument load order
   ([[msvc-ltcg-callee-param-order-sets-caller-load-order]]); retail's caller
   loads the name first. 61->50.
5. **Case 7 statement swap** (`flags |= 4u` before `background_data = ...`).
   50->42.
6. **Else branch named locals `else_text` then `else_color`** — shifts the
   RegAssign rotation ([[msvc-c2-temp-register-rotation-named-local]]); also
   cleaned the case-5 register hunk entirely. 42->35.

### Localized form (2026-10-18, after the integration incident)

The shared marktext cluster files are byte-pinned by the whole-.text gate, so
none of the call-convention shapes may live there. They are re-landed in the
region's own measurement context:

- `build_support/contexts/equivalent/game/context/recovery_script_executor_setflag.cpp`
  (new, this region's context only) defines the free `?RecoverySetFlag@@
  YIPAXPAURecoveryLookupContext@@H@Z` and the swapped-order overload
  `?LoadAsset@@YGPADPAUAssetBuffer@@PBD@Z` stand-ins.
- The declarations live in `src/game/ending/recovery_script_executor.cpp`
  (both are mangled names distinct from the shared declarations, so no
  conflict: the shared `?SetFlag@RecoveryLookup@@QAIPAXPAURecoveryLookupContext@@H@Z`
  member and `?LoadAsset@@YGPADPBDPAUAssetBuffer@@@Z` stay defined by the
  shared anchors for the marktext cluster).
- The layout's `bindings` bind the local symbols to 0x004492A0 / 0x0040B480;
  `context_sources` names the new file. The shared header, `archive_callers.hpp`,
  `recovery_script_executor_core_anchors.cpp` and
  `recovery_script_executor_anchor.cpp` are byte-identical to the pre-session
  state. Re-measured identical: 428/444, 35 bytes.

### Ruled out (evidence)

- Overnight's case-order / goto-advance survivor levers (inert) — not repeated.
- `SetFlag` id typed `RecoveryScriptId` (member or free): 401/796, 402/502.
- Receiver forwarded to Find (member or free3): two pushes everywhere (424).
- Receiver unused but ctx re-read from the global in the body: one-push callee
  but callers spill the manager local (852).
- Free2/static without the case-12 hoist: 492.
- Else: volatile manager, volatile color, volatile ordering through the
  Validate body, `unsigned int`/`void*` typed aliasing reads and stores,
  split text, uncast receiver, ring named local, color/mgr local permutations
  (m1-m5), ring-position permutations (p1-p3, f1-f2): unchanged at 35-53 or
  catastrophic (1137-1263 bytes when the Validate object becomes a local).
- Post-loop: color local (before/after), id int local, handle-local reset,
  ctx/first named locals, plain-g_sprt_ctrl manager, statement swap,
  MakeScriptId helper, unused dummies, for-increment swap,
  CreateModeSlotAnimation parameter swap: all no-ops at 35.

### What remains (35 bytes, 8 hunks)

- Case-3 post-loop 0xc8/0xe2/0xef/0xf3/0xfd: `id` in ECX vs EAX, manager
  EBX vs EDI, handle pointer EDI vs EBX; and the MarkText color load (retail
  `mov edx,[ebp+0x7c]` before `push eax`; model pushes text then loads color
  into EAX — an EAX anti-dependence pins the schedule).
- Case-3 else 0x114/0x118/0x125: retail loads ring (ECX) then color (EAX);
  model color (ECX) then ring (EDX); retail loads+pushes `g_sprt_ctrl` after
  the Validate call, model before it.

Best mechanism hypothesis: RegAssign/ChoosePhysReg priority and candidate
numbering (retail places the handle pointer before the manager; the model the
reverse) plus the c1xx argument-tuple order of varargs `MarkText(void*, ...)`.
Per the rules these are trace-correlation territory, not source sweeps; traces
of the current build: `/tmp/campaign/recovery_exec/tracework/{phys.log,flex.log}`.

## 2026-10-18 (later): localized re-land and the symbolized-trace park

The SetFlag free-fn and swapped-LoadAsset shapes re-landed LOCALIZED (new
context file build_support/contexts/equivalent/game/context/
recovery_script_executor_setflag.cpp with distinct mangled names bound to
0x004492A0 / 0x0040B480); the shared marktext cluster files stay pristine
(they are byte-pinned by the whole-.text gate — a first integration attempt
that edited them broke the production cluster's anchors and was reverted).
470 of 505 differing bytes closed; the body, jump table and extent are exact.

The 35-byte residual is parked as a retail-IR property. C2_SYMS-symbolized
ChoosePhysReg tracing maps the case-3 post-loop trio: object→ESI (num 56,
prio 38), manager→EDI (num 128, prio 36), handle ptr→EBX (num 31, prio 34,
avail FORCED to EBX alone). Retail's order needs the handle pointer picked
first (prio ≥ 36; ties favour the lower candidate number). The margin is 2
points and byte-stable across builds; every documented K-shape (named locals,
two-locals-same-member, constant-true re-reads at real call arguments and
branch conditions, double write-outs) folds away or collapses the function.
Same class as laser_circle_split's literal-pair K gap and ecl_name_table's
rotation coupling.

## 2026-10-19: the else branch's argument order (34 → 18 bytes)

Retail's case-3 else branch pushes the text, pushes the color, calls the
handle validation (0x449450), and only then loads and pushes `g_sprt_ctrl`.
A `__cdecl` member `vm->MarkText(manager, color, text)` evaluates the
receiver as its hidden leftmost argument, so the model loaded the manager
before the validate call. Retail's order is that of a callee shaped
`(manager, vm, color, format, ...)`, evaluated right to left.

Landed: an equivalent-only stand-in `RecoveryMarkText(void* manager,
RecoveryTextVm* vm, ...)` in the new context file
`build_support/contexts/equivalent/game/context/recovery_script_executor_marktext.cpp`,
bound to 0x00447A50 next to the real member. Only the else site calls it;
the two Find sites keep `object->MarkText` (switching them changes nothing).
Points:

- The body builds its va_list from `&manager`. A first draft used
  `va_start(args, vm)`, which takes vm's address, so LTCG pushed vm instead
  of passing it in ESI (1,320 bytes). From `&manager`, vm goes to ESI like
  the member's receiver and the call site matches.
- A non-varargs `(manager, vm, color, format)` stand-in gets the manager
  in EDX (1,329 bytes).
- Writing the handle inline in the validate argument (no `else_handle`
  local) gives 22 → 18 bytes.

Tried with no effect: a stdcall validate, validate as a member of a derived
handle, inline/forceinline/reference accessors for the manager, comma
spellings (worse), text/color/handle inline-or-local in every combination
with the old member call, and reusing the loop's `handle` variable (or a
named `first` pointer) for the `text_handles[0]` block.

Left (18 bytes in 7 hunks):

- 0xc8..0xfd: the EBX/EDI handle-pointer/manager swap parked above.
- 0x114/0x117: the color load is scheduled before the text push, so it takes
  ECX where retail reuses EAX.
