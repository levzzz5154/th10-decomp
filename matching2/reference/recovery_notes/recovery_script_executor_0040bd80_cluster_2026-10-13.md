# Recovery script executor 0040BD80: schema-1 native-LTCG cluster in progress

Date: 2026-10-13
Region: `0x0040BD80`, 1568 bytes, source `layout/ltcg/recovery_script_executor_cluster/recovery_script_executor_0040bd80.cpp`.
Status: **cluster links and the byte gate reaches the executor comparison; native extent 1488/1568, 1287 differing bytes, head matches exactly through 0x40BDBE.**

## What was built (all files exclusively owned by this function)

- `matching2/msvc/layout/ltcg/recovery_script_executor_cluster/` — 20 per-context
  copies of the anchor TUs plus the executor source copy. Copies were REQUIRED:
  `load_clusters` enforces distinct maintained sources across clusters, and
  `src/game/recovery_script_executor_0040bd80.cpp` plus every
  `layout/ltcg/recovery_script_executor_*.cpp` anchor TU are already claimed by
  the registered `recovery_animation_slot_frames_0042c6d0` cluster.
- `matching2/msvc/layout/ltcg/recovery_script_executor_0040bd80_context.cpp` —
  synthetic compiler context (entry) at `0x00401000`, invoking the executor.
- `matching2/msvc/layout/ltcg/recovery_script_executor_0040bd80.json` — schema-1
  cluster manifest: 1 selected function (executor, extent currently probed at its
  native 1452 bytes; acceptance needs the retail 1568), 41 anchors placed at
  retail addresses, gaps recomputed per build.
- `scratch/bd80/` — reflink scratch project, `gen_manifest.py` (manifest
  assembler from the marktext manifest + latest native MAP), `gen_headers.py`
  (transitive header closure), `iterate.py` (map-driven size/gap repair + probe
  driver), `run.sh` (full cycle).

## Key structural discoveries (blocking facts for any future attempt)

1. **Schema 2 is impossible for this function as specified.** Schema 2 requires
   `calls` with both ends selected in the same link and every additional source
   owning a selected region. All named dependency-group callees (0x00405410,
   0x0040C480, 0x0040C4D0, 0x00417010, 0x0043C8B0, 0x00447A50, 0x00449630) and
   the real caller 0x0040BD20 are semantic regions owned by *other registered
   clusters* (`stop_at_frame_pair_0040c480`, `path_decode_xor_00417010`,
   `native_ascii_factory_0043c8b0`, `cl_00449630`,
   `recovery_mark_text_and_dispatcher_004479d0`, `recovery_tick_state_0040bd20`),
   and `load_clusters` rejects shared sources. Co-ownership would break those
   clusters' verified exactness. Schema 1 (synthetic context) is the only
   workable shape; the executor's own ABI is an ordinary `__stdcall` stack
   argument (retail `sub esp,0xc; push ebp; mov ebp,[esp+0x14]`), so the
   synthetic context suffices.
2. **Co-compiled callee bodies are mandatory for byte-exactness.** Retail's
   call sites use LTCG-reassigned private registers everywhere: Timer::Set this
   in **EAX** (`lea eax,[ebp+0x18]; call 0x00405410`), Stop2/Stop3 this in EAX,
   Advance this in ESI, Find/SetFlag context in EDX, Validate handle in ESI,
   Queue second arg register-passed. No declaration can express these; opaque
   absolute-bound callees would emit `__thiscall ECX` sites that differ from
   retail. Hence the genuine-anchor design.
3. **LTCG placement feedback loop.** Native contribution sizes are not fully
   intrinsic: the linker/LTCG does final placement, so section sizes can shift
   by 1-4 bytes when the surrounding layout shifts. Manifest gaps must be
   re-derived from each build's MAP until a fixed point (`scratch/bd80/iterate.py
   repair` automates this).
4. **Anchor fit rule.** Every genuine anchor body must fit its retail slot
   (distance to the next retail contribution). Bodies that overflowed were
   either shrunk at the source level (ClearResourceSlot -2 bytes via redundant
   bounds-check removal; CreatePrimaryBack -8 via read-modify-write flag update;
   MarkText va_list restructure) or converted to absolute bindings with their
   definitions removed from the cluster TUs (SetTimerTarget 0x0042C620,
   InstallSlot 0x0042C670, SkipLine 0x004349E0, DispatchText 0x004479D0,
   PositionedCreate 0x00448D50, Scheduler register pair 0x00449AE0/0x00449B70,
   AsciiRegisterPrimary 0x0044A000).
5. **Never declare a symbol absolute-bound while a cluster TU still defines it**
   (`/FORCE:MULTIPLE` duplicates are rejected unless declared as constant
   aliases), and never leave a defined+referenced function unanchored (the
   stray `.text$x` contribution silently shifts the whole layout).

## Measured state

- Executor native contribution: **1452 bytes** at `0x0040BD80` (marktext-cluster
  baseline was 1500; retail 1568). First probe gate not yet reached: validation
  stops at `native layout gap address/origin differs: _ltcg_gap_24` — a 1-byte
  oscillation of `FormatRightAligned_00447ae0` (207↔208 native) inside its
  208-byte slot absorbs the 1-byte gap at `0x004447BAF` and shifts everything.
- Probe harness: `scratch/bd80/run.sh` (sync → gen_manifest → gen_headers →
  map repair → probe). Each cycle ≈ 9 s.

## Progress log (2026-10-13, later)

1. **Byte gate reached.** The probe now compiles, links, validates the layout
   and compares the executor body every cycle (~9 s):
   `scratch/bd80/run.sh` (sync → gen_manifest → gen_headers → map repair → probe).
2. **Volatile-reload idiom.** Retail re-reads every mutable game global at each
   use (`data_00491c10`, `data_00477700`, `data_00474e30`, `data_00474e36`,
   `data_00474c74`, `data_004918a4`); the plain-extern C++ let MSVC CSE them
   into EBX for the whole function. Volatile-qualified lvalue reads
   (`*(const volatile unsigned int*)&data_00474e30` — an established idiom in
   this tree) restored the retail reloads; the prologue, guard chain and
   frame size (`sub esp,0xc`) now match retail exactly through 0x40BDBE.
3. **Frame locals.** Retail reserves 12 bytes (three dword out-slots for the
   four CreatePrimaryBack sites, plus arg-home reuse for opcode 8). The C++
   shapes that currently reproduce a 12-byte frame are per-case `void* created`
   locals with the `result` temporary removed
   (`state->animation_handles[...] = *AnimationManager_CreatePrimaryBack_(...)`
   directly).
4. **Switch comparison.** `while (current >= frame)` (memory operand first)
   emits retail's `cmp [ebp+0x1c],edx`; `frame <= current` emits the reversed
   `3b` form.
5. **Opaque callees where the body hurts.** MarkText, DispatchText, the
   right-aligned/centered formatters, SetTimerTarget, InstallSlot, SkipLine,
   PositionedCreate and the scheduler register pair are absolute-bound to their
   retail addresses with their definitions removed from the cluster TUs. This
   keeps the executor's variadic MarkText call sites prototype-driven (retail
   pushes all three fixed arguments) instead of letting the pass exploit the
   unused manager argument, and removes the anchor-fit oscillators.

## Current residual (exact)

Native 1488 bytes; 1287 differing bytes; 69 diff runs; first difference at
`0x0040BDBF`: every `RecoveryTimer::Set` call site passes `this` in **ECX**
(`lea ecx,[ebp+0x18]`) where retail passes it in **EAX** (`lea eax`). The
callee 0x00405410 reads EAX in retail (`mov ecx,[eax+0x10]` — its own recovery
is EXACT inside the `frame_timer` cluster, whose family context made the
interprocedural pass assign EAX). In this cluster the pass keeps the declared
`__thiscall` ECX. Experiments that did **not** flip it: splitting Set/Advance
into their own /GL module with the proven TU shape, and synthetic-context call
loops over `timers[i].Set/Advance`. All 8 Set sites contribute 1 byte each;
the remaining ~1280 bytes are the cascading register-allocation and block-order
differences downstream (ring loops, wait paths, mode cases, switch-table
placement at the function end).

## Next levers (updated order)

1. **EAX-this for Set.** The only mechanism known to produce it is the
   interprocedural pass over a family like `frame_timer`'s. The `frame_timer`
   cluster was cloned into a scratch project and re-probed EXACT in isolation
   (mechanism confirmed reproducible), and a driver-call bisection was started
   to identify which family member forces EAX. The bisection needs a
   repair-aware harness (adding `/INCLUDE` roots changes IPSA's global
   assignment and shifts placement, so every variant must re-converge its gap
   layout before its verdict is readable). Once the trigger sibling is found,
   reconstruct its equivalent shape inside this cluster (its own source is
   cluster-owned, so the shape — not the file — must be transplanted).
2. After Set: chase the remaining diff runs in address order with the fast
   cycle; each cycle is 9 s and the report gives the next first-difference.
3. Grow the extent to 1568 (retail jump table at 0x0040C358, 18 entries ending
   exactly at 0x0040C3A0) and register the real extent.
4. Integration delta (when EXACT): replace region `asm_FUN_0040bd80_0040bd80`
   with `semantic_RecoveryScript_Execute_0040bd80` (source
   `layout/ltcg/recovery_script_executor_cluster/recovery_script_executor_0040bd80.cpp`,
   symbol `_RecoveryScript_Execute_0040bd80@4`, `previous_record` preserved) and
   append `layout/ltcg/recovery_script_executor_0040bd80.json` to
   `ltcg_clusters`. Do NOT repoint `src/game/recovery_script_executor_0040bd80.cpp`
   without re-probing `recovery_animation_slot_frames_0042c6d0` — that cluster
   compiles the src file as whole-program context.

## Progress log (2026-10-13, evening): bisection results and frame packing

1. **`/INCLUDE` roots freeze ABIs — confirmed experimentally.** The cloned
   `frame_timer` cluster was probed with `roots` added: `SetSchedulerValue`'s
   body changed to `mov ecx,[ecx+0x10]` (receiver ECX); without roots it is
   `mov ecx,[eax+0x10]` (receiver EAX). Forced `/INCLUDE` symbols are treated
   as address-escaping and keep their declared `__thiscall` ABI; the
   interprocedural pass only reassigns receivers of functions reached purely
   through the call graph. Consequence: `anchor_roots` must stay empty for the
   executor's direct callees. (Extraction note: MAP group columns are
   RVA-0x1000, i.e. VA = 0x401000 + column; symbol VAs are absolute.)
2. **Dual call sites do not flip it.** `frame_timer` with two
   `SetSchedulerValue` call sites and no roots still yields EAX; in the
   executor cluster (8 sites inside one large caller) the pass still picks
   ECX. The remaining difference is the whole-family register coloring; a
   call-site-count trigger is ruled out.
3. **Stack-packing sensitivity.** The executor's 12-byte retail frame
   (`sub esp,0xc`, three dword out-slots) reproduces only under specific
   global register-pressure states: a single shared `created` slot yields
   either no frame at all or (with the volatile reloads in place and the
   pre-cleanup anchor set) the correct 12 bytes; per-case locals yield 16
   bytes; three distinct per-mode-case names still yield 16. The frame size
   and the register assignment move together; they cannot be tuned
   independently by source shape.
4. **Context pressure.** Family-style synthetic contexts (calls to Stop2/3,
   MarkForRemoval, SetFlag, Find) change the assignment globally and currently
   regress the head match; the minimal Set/Advance-exercising context is the
   best measured configuration (1488/1287, head exact through 0x40BDBE).
5. **Dead-context cleanup.** With Drain, the music-room family and the
   formatters absolute-bound, their TUs became unreachable and were removed
   (caller_00419120, indicator_anchors, text_sibling_anchors,
   caller_00433ef0, slot_frames, and the 0x0043E710 LoadScript body,
   absolute-bound). Their empty `.text$` sections produced zero-size MAP rows
   that the map parser rejects as duplicate contributions.

## State at hand-off

Cluster links and probes end-to-end; current best reproducible states:
- 1488 bytes native, 1287 differing, head exact through 0x40BDBE (pre-cleanup
  anchor set, per-case locals, minimal Set/Advance context) — needs the removed
  context TUs restored to reproduce.
- 1524 bytes native, 1329 differing, first difference at the frame size
  (post-cleanup anchor set — the maintained state of this cluster).

The blocking problem is now precisely characterized: reproduce MSVC 13.10's
interprocedural receiver assignment (EAX for 0x00405410) and stack packing
(three dword slots) simultaneously. Both were observed in this toolchain; the
search space over context shapes is combinatorial. The fastest route forward
is a dedicated experiment cluster that isolates Set with a parameterized
driver, characterizing which driver shapes yield EAX and 12-byte frames, then
transplanting the winning shape.

## Progress log (2026-10-13, night): receiver solved, frame solved

**The executor head now matches retail byte-for-byte through 0x40BDD3** (85
bytes: prologue `sub esp,0xc`, all four guards with their exact jcc forms,
the `command_timer.Set` call with `lea eax,[ebp+0x18]; call 0x405410`, the
loop compare `cmp [ebp+0x1c],edx`, the three callee-saved pushes, the
`lea ebx,[ebx]` alignment pad, and the signed `jl` exit). The dispatch
`jmp [ecx*4+table]` form matches; only the table address and the exit-target
block position still differ (retail tail at 0x40C27C, table at 0x40C358).

What produced the breakthrough:
1. **Dead-context removal.** After Drain, the music-room family, the
   formatters and the LoadScript body became absolute-bound, their TUs were
   deleted outright (they had become unreachable; their empty `.text$`
   sections produced zero-size MAP rows that the parser rejects). The cleaned
   16-TU cluster changed the interprocedural coloring globally.
2. With the cleaned set (and `anchor_roots` restricted to non-executor-callee
   anchors), **the pass assigns Set's receiver to EAX** (`8b 48 10` body,
   `lea eax` call sites) — the frame_timer bisection's mechanism confirmed in
   this cluster. No driver-shape change was needed; the earlier shapes were
   indistinguishable because the coloring was dominated by the stale anchor
   set.
3. **The 12-byte frame reproduced** via the output-record array shape: a
   function-scope `void* output_records[3]` with the three mode-case
   expansions taking `&output_records[0..2]` and the opcode-eight site reusing
   `&output_records[0]` (retail reuses the incoming argument home for that
   record). Earlier single-local shapes packed to 0 or 16 bytes; the array
   packs to exactly 12.
4. The signed loop exit (`jl`) required the `>=` spelling with the memory
   operand first (`current >= frame`); the reversed spelling emitted the
   unsigned `3b` compare form.

## Current residual

1524 bytes native (retail 1568), 1326 differing bytes, first difference at
0x40BDD4: the loop-exit `jl` targets 0x40C24E instead of retail's 0x40C27C —
the tail block sits 46 bytes early, and the switch table follows at the
matching offset instead of 0x40C358. Downstream of that, case bodies still
differ in private register allocation and spill placement (the bulk of the
1326 bytes).

## Next steps (in order)

1. Chase the downstream diffs in address order with the 9-second cycle: each
   fix shifts block weights and can move the tail/table into retail position.
   The first block-order targets are the opcode-3/4 text paths (retail's ring
   loop at 0x40BDF7-0x40BEA5 with `mov ebx,5` and the `Find`/`MarkText`
   sequences) and the opcode-5/6 wait paths.
2. Grow the extent to exactly 1568 once the tail lands at 0x40C27C and the
   table at 0x40C358 (72 bytes of entries ending at 0x0040C3A0), register the
   real extent in the scratch regions.json, and take the definitive verdict.

## Residual catalog (superseded — see the evening entry below)

### State before the MarkText restructure (1524/1568, 1326 bytes in 58 runs)

Exact through 0x40BDD3. Difference classes in address order:
1. `+0x54, +0x6c, +0x73, +0x7e, +0x83` — shifted jump targets only (exit tail
   and default case sit 0x2E bytes early; the jcc forms/encodings match).
2. `+0x85..+0x93` — case-3 ring loop register assignment: retail
   `MOV EBX,5` (counter in EBX) + `LEA EBX,[EBX]` pad + handle in EDI; mine
   `MOV ESI,EBX; MOV EDI,5` — the manager lives in a callee-saved register in
   mine while retail reloads `[0x491c10]` per iteration (both sides issue two
   volatile loads per iteration; only the register classes differ).
3. `+0xb8..` — the MarkText call sites: retail pushes
   `0x46cfd4 / 0xffffff / ESI(vm)` with `add esp,0xc`; mine pushes in a
   different materialization order (args match, register homes differ).
4. Further runs are the same two classes propagated through opcodes 5-17 and
   the tail.

The next lever is purely the ring-loop register class (counter in EBX, handle
in EDI, manager reloaded per iteration into ESI) — likely inducible by making
the loop counter's decrement the loop's only carried state (e.g. spelling the
loop over a pointer endpoint) or by register-pressure shaping in the synthetic
context. Everything else follows from block weights once the ring loop and
MarkText sites match.


## Progress log (2026-10-13, late night): MarkText restructure

The ring-loop and MarkText call shapes revealed MarkText's true retail
signature: the VM travels in the __thiscall receiver register (IPSA assigns
ESI at the executor's call sites) with manager, color and format on the stack
in that order, and the body never reads the manager slot. The declaration was
restructured from a variadic __cdecl member (which pushes `this` and forces
`add esp,0x10`) to a non-variadic member taking (manager, color, format) —
MSVC converts variadic members to __cdecl, so the ellipsis had to go; the
executor's format strings carry no conversions, so the vararg pack was never
populated. The body now lives in the cluster's text_anchors TU again (genuine,
unrooted) and the cluster-local header carries the new signature.

Additionally: the Find/SetFlag context arguments now reuse the manager local
instead of re-reading the volatile global (retail issues a single load per
call site; the volatile macro had doubled them), and the ring loop keeps the
counter as its only carried state.

**Current measured state: 1496 bytes native (retail 1568), 1239 differing
bytes in 63 runs, head exact through 0x40BDD3.** The first difference remains
the loop-exit `jl` rel32 (tail block 0x46 bytes early). The remaining runs are
single-byte register/branch-coloring choices (jge vs jne forms, register
classes in the ring loop, MarkText argument homes) — each an interprocedural
coloring decision, not a source-semantics gap.

The definitive next lever: an IPSA coloring chase in address order. The
methodology that produced every win so far — restructure the source to the
retail value flow, keep the volatile reads only where retail reloads, let the
pass choose registers, and re-converge the layout from each build's MAP —
continues to apply directly. Each cycle costs ~9 seconds.

## Addendum: MarkText ABI characterization (final for this session)

The ring loop now matches retail instruction-for-instruction except register
names: handle ESI (retail EDI), counter EBX (retail EBX ✓), manager EDI
(retail ESI), MarkText receiver ECX (retail ESI). Loop restructurings
(counter-primary preheader, id-before-manager declarations) do not move the
coloring — it is a global IPSA decision.

MarkText's retail contract was characterized exhaustively:
- VM in ESI, stack args (manager, color, format) pushed in that order,
  caller-cleans 12 (`add esp,0xc`), body reads the VM from ESI and never the
  manager slot.
- No MSVC 13.10 declaration produces this shape directly: __cdecl member
  pushes `this` (4 pushes, `add esp,0x10`); __thiscall member is
  callee-cleans; __fastcall forces callee-cleanup and register homes for the
  first args; variadic members/functions convert to __cdecl. The VM-in-ESI
  contract is IPSA-created — the pass reassigned a declared register receiver
  to ESI and spilled the manager to its stack home.
- The current thiscall form (3 pushes, receiver in ECX) is the closest
  declarable shape; converting it requires the pass to reassign the receiver
  of a 3-stack-arg member — the same class of coloring decision as the ring
  loop's ESI/EDI swap.

Every mechanism needed for EXACT is now identified; the remaining 1239 bytes
are IPSA coloring decisions whose search requires either finding source shapes
that bias the coloring (as the output-record array did for the frame) or
accepting the equivalent-layout path.

## Addendum 2: __fastcall MarkText experiment (reverted)

A `__fastcall` member MarkText (VM in ECX, manager in EDX, color/format on
the stack) links and probes but colors the call site as
`push format / push color / mov edx,manager / mov ecx,vm / call` — two pushes
plus register homes, 5 bytes WORSE than the thiscall form (3 pushes,
receiver in ECX). Reverted to the thiscall member; the maintained state stands
at 1496 bytes native, 1239 differing, head exact through 0x40BDD3.

The two remaining structural differences at the MarkText sites are (a) the
receiver register (ECX vs retail ESI) and (b) the cleanup form (callee-cleans
RET 12 vs retail's caller-side `add esp,0xc`). Both would require the pass to
reassign a __cdecl member's stack-resident `this` into ESI, which MSVC 13.10's
IPSA does not do for stack parameters — the retail shape is only reachable
from a source whose MarkText was not a member at all, or whose receiver the
original inlining pipeline had already materialized into ESI before
stack-packing. This closes the declarable-shape search for MarkText.

## Addendum 3: systematic receiver/coloring study (final)

Minimal experiment clusters (mt_probe) isolating MarkText's receiver with the
executor-like provenances — receiver from a parameter, from a call result,
carried across another call, from a global — ALL assign the VM receiver to
ESI (retail's register), including with the executor TU itself as the caller
and with the full 16-TU anchor set. The real cluster's ECX could NOT be
reproduced in any minimal configuration.

A driver-symbol rename experiment initially appeared to flip the real
cluster's coloring, but re-verification against the current build showed the
reading came from a stale MAP (rapid successive builds share mtime
granularity). With verified per-build reads, the driver name has no effect.

Conclusion of the study: the executor cluster's ECX receiver for MarkText is
a whole-link interprocedural coloring outcome that does not decompose into
any single caller-shape or naming factor I could isolate. The identified
contributing structure — three call sites whose receivers are Find results,
inside a ring loop whose counter/handle/manager occupy EBX/EDI/ESI differently
than retail — is documented above; retail's own assignment (ESI for both the
ring manager and the MarkText receiver) suggests the retail coloring reused
ESI because its ring loop's manager load flowed directly into the MarkText
receiver expression. Reproducing that requires the ring loop's manager to be
the SAME expression as the MarkText receiver argument — which the current
source already does via the manager local, yet the pass still splits them.

## Final maintained state

- 1496 bytes native (retail 1568), 1239 differing bytes in 63 runs.
- Byte-exact through 0x40BDD3: prologue + 12-byte frame + guards + EAX-receiver
  Timer::Set call sites + loop compare + callee-saved pushes + pad + signed jl.
- Remaining: tail/table block placement (the jl rel32 target) and per-case
  register coloring.

## Addendum 4: corrected receiver readings and the ring-loop swap (final)

Re-measurement with entry-copy detection (`mov esi,ecx` at the MarkText entry)
reveals the earlier "vm in esi" readings were misreads: the flags_360 read's
ESI base is an internal copy of the receiver, which arrives in ECX in BOTH the
minimal clusters and the real cluster. The unambiguous signal is the call
site's receiver setup.

The genuinely open difference is the ring loop's register roles:
- retail: handle=EDI (loop-carried), counter=EBX ✓ (matches), manager=ESI
  (reloaded per iteration; the Find result then REPLACES it, so the MarkText
  receiver naturally inherits ESI);
- mine: handle=ESI (loop-carried), counter=EBX ✓, manager=EDI (reloaded per
  iteration; the object moves to ECX at the MarkText call).

Because retail's object overwrites the manager's register, MarkText's ESI
receiver falls out of the ring loop's manager placement. Fixing the
handle/manager swap is therefore the single remaining lever: everything
downstream (MarkText's receiver, its 3-push shape) follows. Spelling levers
tried for the swap (preheader order, id/manager declaration order,
counter-primary form, manager-local reuse) did not move it; the swap is an
IPSA coloring decision on two loop-carried/per-iteration values.

Final state: 1496 bytes native (retail 1568), 1239 differing bytes in 63 runs,
head exact through 0x40BDD3.

## Addendum 5: ring-loop swap variant sweep (parked)

Eight spellings of the ring loop were measured against the handle/manager
register swap (mine: handle=ESI/manager=EDI; retail: handle=EDI/manager=ESI):
preheader order (counter-first/counter-in-init), id-first vs manager-first
body declarations, counter-primary `&text_handles[5-remaining]` form, distinct
per-case local names, shared output-record array, manager-local reuse for the
MarkText argument, per-site volatile manager loads, and un-cached id
temporaries. The swap is invariant to all of them — the candidates' reference
counts match retail's exactly (handle: init/id-load/null-store/Stop3-this/
advance; manager: one load + Find-ctx + MarkText-arg per iteration), so the
priority inputs are equal and the differing assignment must come from
priority inputs outside the loop (whole-function weighting), which spelling
cannot reach.

Parked per the session rule. Final maintained state: 1496 bytes native
(retail 1568), 1239 differing bytes in 63 runs, head byte-exact through
0x40BDD3. All structural mechanisms (receiver EAX for the timer store, the
12-byte output-record frame, the signed loop exit, the single manager loads,
the thiscall MarkText shape) are solved and documented; the residue is the
ring-loop ESI/EDI swap, the tail-block placement that follows from it, and
the per-case coloring downstream.

## Addendum 6: whole-function register map and the tail (final verification)

Whole-function register reference counts: MINE esi=39 edi=34 ebx=22; RETAIL
esi=40 edi=34 ebx=26 — near-identical; no handle/manager reference deficit
exists outside the ring loop. The per-block deltas concentrate in the case
bodies (0x40BF87, 0x40C088) and the tail window (an artifact of the tails
sitting at different offsets).

The timer-tail block itself is instruction-for-instruction identical to
retail (mov edx,[ebp+0x1c]; mov ecx,[ebp+0x24]; mov [ebp+0x18],edx; flds/
fcomps window; pops edi/esi/ebx; ret 4) — my earlier "previous=frame" concern
was a misaligned disassembly view. The ONLY tail difference is its address:
mine at 0x40C233, retail at 0x40C27C, because the case bodies between the
dispatch and the tail are cumulatively 73 bytes shorter.

Final accounting of the 1239 differing bytes: the ring-loop ESI/EDI swap
(parked), the tail/table positions that follow from it, and per-case register
coloring in the opcode bodies. Every structural and ABI mechanism is solved;
the pipeline (9-second cycle, map-converged layout, verified reads) is in
place for the next session's per-case chase.
