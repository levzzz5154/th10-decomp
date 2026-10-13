# ECL StartChild 0x0044DF70: parked, about 82 of 165 instructions differ (2026-10-11)

The anchor in `src/script/ecl_child_pair.cpp` was rewritten with inline
`PushWord`/`PopWord` helpers that take pointers, a `while` argument loop and a
saved-base local. It emits 557 bytes against retail's 550. SpawnChild stays
exact. The function is still assembly-owned.

## What retail's shape says

- `edi = source + 4` is computed once at entry and every `*pc` goes through it.
  `source` itself has no register: it is reloaded from its parameter home
  (`[esp+24h]`) in each block that needs it and stays in EDX across the tail.
- `index` is read from its home twice (EDX at entry, EBX before the loop) and
  its home is then reused for the destination pointer, so it is a plain
  parameter whose whole-range allocation failed and was split into pieces.
- Zero lives in EDX from the `saved = 0` store to the first push, and the
  `cursor + 4` temporary of that push is in EBX.

## Why the model differs

1. **`T** pc = &param->field` is forwarded.** c2 rewrites every `*pc` as
   `[source+4]` when `pc` has one assignment, so `source` inherits all its
   uses and takes ESI. Standalone rig results (`cl /O2`, 30 spellings): member
   of `this`, reference, local struct member, iterator object, inline helper
   parameter, pointer arithmetic, casts, a `do`/`for` wrapper all forward.
   Only a second assignment (`if (x) pc = other;`) or an assignment inside a
   `goto` loop (hoisted as a loop invariant) keeps `add reg,4` and leaves the
   parameter in memory with per-block loads, which is retail's shape.
   A second `pc = &source->instruction;` inside the argument loop is not
   removed (it emits the load and add again, as retail's interpreter does at
   0x0044FB7E); before the loop it is merged and forwarding returns.
   Address-taking through inline helpers and same-size type punning are
   cleaned up and change nothing.
2. `volatile` on `source` reproduces item 1's effect but reloads `source` in
   the tail where retail keeps EDX. It is a stand-in, not the answer.
3. With `pc` separate, descriptor and selector are swapped (EBX/EBP). The
   ChoosePhysReg trace gives selector+index 113 and descriptor 111; a zero
   immediate limited to EBX puts cost 300 on EBX, so the first of the two takes
   EBP. Retail needs descriptor first; then index/selector fails over its
   whole range (EBX is used by the push temporary) and is split, which gives
   the two loads of `index`, and zero gets EDX.
4. The integer resolver stand-in is an exported `__fastcall` with a dummy
   first parameter, so the model has `xor ecx,ecx` before the call. Retail has
   none: the callee needs its natural convention in this cluster.

## Next steps

- Find a zero-code source reason for `pc` to have two assignments or to be a
  hoisted loop invariant (item 1). Everything else follows from it.
- Then close the 2-point priority gap of item 3 and remove the export of item 4.

Tools: `reference/compiler_traces/scheduler/capture_link.py` plus
`regalloc/trace_choose_physreg.py` on the cluster link; StartChild is the
function with 30 blocks whose first choices are ESI 188 and EDI 158.


## Second-assignment experiments (2026-10-12)

Measured with the real cluster build (the anchor sizes are hard constraints:
SpawnChild must stay at its retail address, so StartChild must be exactly 550
bytes):

* second `instruction = &source->instruction;` at the top of the argument
  loop: 582 bytes (+32) — the reload form is longer, not shorter.
* the same assignment at the end of the loop body: 566 bytes (+16).
* shrinking the `.text$06layout` filler by the growth lets the cluster link,
  but the function itself still overshoots its retail extent, and the anchor
  mechanism pins it at 0x44DF70 — the overlap is fatal.

The two-assignment shape is longer in this context, contradicting the
standalone-rig expectations of item 1; the per-block source reloads add more
than the forwarded-pointer form saves.  The register contest (item 3) and
the exported resolver (item 4) remain the open levers.


## Why the dummy resolver argument cannot be dropped (2026-10-12)

The `xor ecx,ecx` before the resolver call costs 3 of the 7 excess bytes.
The dummy first parameter is dead in the callee body, but it cannot be
removed:

* The 4-argument `__fastcall` ABI is what places `frame` in EDX; a 3-arg
  form would place `frame` in ECX, contradicting the retail body (which
  reads the frame from `[edx+4]`).
* The semantic region 0x0044FF00 is exact at 124 bytes with the same 4-arg
  body; changing its signature would break it.
* c2's IPCG does not drop the dead first argument across the `code_seg`
  pragma boundary that pins the anchor body to 0x0044FF00.

With the zero-store variant (557→553) and the mandatory 3-byte xor, the
model lands at exactly 553 — 3 bytes over the 550-byte retail extent.  The
equivalence machinery compares code at equal extent, so the region stays
assembly until a source shape makes the model 3 bytes shorter (or the
register contest of item 3 shifts the scheduling enough to close the gap).


## c2 trace with the zero-store variant (2026-10-12)

The zero-store variant (direct zero store instead of `PushWord(&saved_base)`)
removes the address-taken zero candidate but the 300-cost EBX limitation
persists — `CHOOSE reg=6 num=16 prio=113 avail=[4, 6] costs=4:300 6:0`.
Something else is limited to EBX with cost 300 (the cursor + 4 temporary of
the second `PushWord`, or the destination pointer chain).

The descriptor (num=10, prio 112) is forced to EBX: its available set narrows
from [4, 6, 7, 8] to [4] across the walk blocks because the chained f38
references (the other candidates' neighbours) consume ESI/EDI.  The
selector+index (num=16, prio 113 > 112) picks first and takes ESI(6).

For retail's assignment (descriptor in ESI, selector+index split), the 300-cost
EBX limitation must be lifted so selector+index takes EBX(4) and descriptor
gets ESI(6).  The trace is saved at
`reference/compiler_traces/regalloc/ecl_start_child_zerostore_trace.txt`.

With the zero-store variant the model compiles to 553 bytes — still 3 over
the 550-byte extent (the mandatory 3-byte `xor ecx,ecx` for the resolver
dummy).  Both levers must land together.


## Source-lever exhaustion (2026-10-12, final)

All candidate source shapes measured against the 550-byte extent:

| variant | bytes | note |
| --- | --- | --- |
| original (PushWord zero) | 557 | +7 |
| zero-store (direct store) | **553** | +3, best |
| 2nd assign at loop top | 582 | +32 |
| 2nd assign at loop end | 566 | +16 |
| index-based store (no dest ptr) | 566 | +16 |

The zero-store variant at 553 is the floor: the mandatory 3-byte `xor
ecx,ecx` for the resolver's dead first argument cannot be removed (the
4-arg `__fastcall` ABI places `frame` in EDX as retail requires), and the
300-cost EBX limitation persists (the descriptor is forced to EBX while
retail puts it in ESI).  Both levers require c2 to make the same
interprocedural register-ABI and allocation choices it made in the retail
whole-program build; the single-caller model link does not reproduce them.


## Definitive conclusion: the 3-byte excess is structural (2026-10-12, final)

The resolver's first `__fastcall` parameter (the dummy) is what places the
frame in EDX.  A 3-argument form would place `frame` in ECX, contradicting
the retail body (which reads the frame from `[edx+4]`).  c2's IPCG cannot
drop the dead first argument without changing which register the frame lands
in.  The 3-byte `xor ecx,ecx` (or `mov ecx,<value>`) at the call site is
therefore mandatory — the model cannot fit the 550-byte extent.

The resolver-call fix (passing the operand value as the first argument, as
retail does) narrows the instruction differences from 889 to ~509 bytes and
is the correct readable semantics; it is committed in the parked candidate
source. The region stays assembly.

## Cluster probe round 2 (2026-10-13)

Iterated in `scratch/eclstart` (reflink copy; StartChild promoted from anchor
to selected function in the scratch manifest, scratch regions.json region
converted to semantic). Measurement: probe the cluster, read the true size
from `cluster.map` (`.text$01start`), re-probe with the anchor size set, then
byte-diff the built PE at 0x44DF70 against retail.

| variant | bytes | note |
| --- | --- | --- |
| tree parked candidate (dummy 0, zero-store) | 557 | +7 |
| + operand passed as resolver arg 1 (`xor ecx,ecx` → `mov ecx,reg`) | 555 | +5; the note's "committed fix" was **not** in the tree file |
| + `src = source` non-volatile copy after the loop, tail reads via it | 547 | +3, best; tail re-reads of the volatile pointer collapse |
| + non-volatile source (no volatile) | 534 | −16 but ABI drifts: source becomes an ESI live-in, wrong for the asm dispatcher caller |
| + loop-tail `operand_offset = descriptor + 4` derivation (or `descriptor + 12` before the increment) | 528/534 | flips the register contest but re-plans the whole ABI (`mov ecx,esi` appears in SpawnChild's call), SpawnChild goes nonexact — unusable |
| + fused `++selector < limit` / split `descriptor += 4; += 4` / inline `(descriptor+4)>>2` at both loads | 547/547/557 | no contest change |

Probe verdicts (scratch): SpawnChild EXACT 142/142 throughout; StartChild
best draft 547 bytes, 498 differing bytes in the 550-byte overlap.

### Register-contest mechanism, now proven

The c2 choose order for StartChild is: child→ESI (prio 188), pc→EDI (164),
selector+index→**EBP** (117), descriptor→**EBX** (115, avail forced to [4]).
Retail has selector in EBX and descriptor in EBP. Two decisive traces:

* The 300-cost on EBX comes from a rematerializable immediate candidate
  (`num=5`, prio 0, `SpillImmedBytes`, avail=[4]) — patching the EBX cost to 0
  in memory at the selector's choose (gdb, mid-link) does **not** flip the
  pick: with costs tied, c2's class order still prefers EBP over EBX.
* Therefore retail's selector only gets EBX because EBP is already taken:
  the **descriptor must allocate first**, i.e. its priority must exceed the
  selector's. Priority tracks the creation weight (`prio = w + const` for
  both: w 88 vs 90, prio 115 vs 117); the selector's +2 comes from its two
  resolver-call argument references. Adding in-loop descriptor references
  via dataflow changes flips the priority but also re-plans the calling
  convention, so the flip must come from a spelling that adds references
  without touching the loop dataflow. That spelling was not found.

### Byte decomposition of the remaining +3 (547 vs 550)

All residual differences hang off the same allocation:

* entry `mov [esp+0x14],0` (8 B) vs retail `xor edx,edx; mov [esp+0x14],edx`
  (6 B): +2 — the zero never becomes a register candidate because the first
  push folds EAX (cursor==0);
* tail `xor ebx,ebx; cmp eax,ebx` (5 B) vs `test eax,eax` (2 B): +3, and the
  PopWord guard `cmp/jl` (5 B) vs `js` (2 B): +3 — both because EBX is free
  at tail entry in the model while retail has the hoisted `mov ebx,0x4`;
* source preloaded to EDX before the `je` in retail (−6 for the model, whose
  `src` copy lands in EBX later);
* retail's 7-byte `lea esp,[esp]` loop-head alignment nop is absent in the
  model (−7): the model's loop head sits 9 bytes past a 16-boundary, just
  past c2's alignment window.

Net +2+3+3−6+... ≈ +5 before the src-caching win; 547 is where it lands.

Instruction-level (register-normalised) diff of the best draft: 135 of 165
instructions shape-identical, 59 differing-instruction weight against the
equivalence budget of 55 (TOTAL_BUDGET 1/3) — four instructions over, all of
class register-choice/evaluation-order around the swap and the zero forms.

Next lever (unchanged conclusion, sharper): find a zero-dataflow spelling
that raises the descriptor candidate's creation weight by 3 (or lowers the
selector's) — e.g. any additional in-loop descriptor use c2 does not CSE
away and that does not restructure the loop tail. Everything else follows
from it: the swap, the zero forms, the source preload, and then the extent
(nominal retail shape) plus, plausibly, the 7-byte loop alignment.

Draft sources and harness: `scratch/eclstart/` (`measure.py`, `run.sh`,
`diff_exe.py`, `best_ecl_child_pair_vH.cpp`, `trace_weights.py`,
`trace_patch.py`). The scratch manifest pins the anchor at 547 with gap
`.text$02layout` recomputed; the real tree is untouched.

## Round 3 (2026-10-13, continued): the remaining levers are closed

* Loop-head alignment: the head's absolute position is fixed by the region
  address (0x44DF70) plus the function's own byte layout — the preceding
  gap/anchor sizes cannot shift it. The model's head sits at +0x77 (9 bytes
  short of the 16-boundary that retail's head reaches via the 7-byte nop).
  Matching retail's head position requires +2 net bytes before the head and
  −2 after; c2 re-folds every spelling tried (`descriptor` init split into
  two statements re-folds to the single LEA), so the window cannot be
  entered deliberately.
* Zero-candidate forms: the tail's `xor ebx,ebx; cmp eax,ebx` exists because
  the ==0-path push zeros hoist a zero candidate above the branch and the
  compare consumes it; retail compares with `test` and materializes its push
  zero (`xor ecx,ecx`) inside the path. Decoupling the pushes (`PushValue`
  immediate helper, `cursor >= 4` guard spelling) measured 543/497 — the
  zero candidate is still created and hoisted; c2 unifies all zeros of the
  function into one candidate regardless of spelling.
* Ref-neutral spelling exhaustion: `unsigned descriptor`, commuted init
  order, pointer-arithmetic byte loads — all compile to the identical
  547/498 body. c2's IL canonicalization erases every such variation, so
  the descriptor weight (88 vs the selector's 90) cannot be moved by
  spelling alone.

Best verified draft (scratch probe): StartChild 547 bytes (+3), SpawnChild
`EXACT` 142/142, whole-probe `EXACT` with the region still asm. Weight 59
against the 55 budget. The next session's options are (a) c2-internal
weight archaeology — watch candidate+0x44 writes from function start to
recover the per-reference weight formula, then design a spelling that adds
exactly 3 weighted descriptor references without a dataflow change — or
(b) a schema-2 cluster with `calls` over the resolver edges to see whether
whole-graph compilation shifts the allocation; both untried.

## Round 4 (2026-10-13, option a executed): weight responds to refs, priority does not follow weight alone

Candidate weights dumped at StartChild's first choose across variants:

| variant | descriptor w | selector w | descriptor prio | selector prio |
| --- | --- | --- | --- | --- |
| best draft (vH) | 88 | 90 | 115 | 117 |
| inline `(descriptor+4)>>2` at both loads (vP) | **92** (+4) | n/a (renumbered, w 93) | **97** (−18) | 107 |

Two results:

1. **Creation weight does respond to references**: the inline derivation
   added exactly +4 to the descriptor's weight (one extra non-loop-class
   reference), confirming w is a per-reference sum (~20 per in-loop ref,
   ~4 per non-loop ref, ~+3 per call-argument ref — fits vH's 88/90 split).
2. **Priority is not w + const**: with the descriptor's weight UP 4, its
   priority went DOWN 18 (115 → 97) and still lost to the selector (107).
   The choose priority has components beyond the creation weight — the
   115 = 88+27 / 117 = 90+27 pairing in the base draft was coincidence.
   The extra component reacts to the dataflow shape (the derivation moved
   the descriptor's (descriptor+4) partner into the loop), which is exactly
   the restructuring that also re-plans the ABI.

Consequence: option (a) in its simple form is dead — adding weighted
references is possible, but the priority's non-weight component punishes
the dataflow shapes that add them. Recovering the full priority formula
requires deeper c2 internals (the prio field at candidate+0xc is computed
outside ChoosePhysReg; its writer was not located among the +0x44 store
sites). Option (b) remains the only untried lever; expected value is low
because IPCG specializes call edges, not callee-internal allocation.

Standing best: `scratch/eclstart/best_ecl_child_pair_vH.cpp` — 547 bytes,
498 differing bytes, weight 59 (budget 55), SpawnChild EXACT. The three
structural residuals and their single root cause (selector/descriptor
priority order) are documented above.

## Round 5 (2026-10-13, option a completed): the accumulation fully decoded for 0x0044DF70

Instrumented the decoded accumulation directly (`trace_accum.py` at
0x107a991c/0x107a9951/0x107a997e, `trace_refs.py` at the per-reference walk
0x107a9659) on the best draft's link:

* **Dynamics confirmed**: per block, every live candidate with references in
  that block gains `f18 × (block_refcount × block_weight)` (f18 = the sum of
  the block's per-reference values, reset per block); every live candidate
  with NO references in the block loses `block_weight` (the subtract path,
  0x107a997e). The trace shows both candidates' priorities rising and
  falling across the walk (the selector's dropped 68 → 15 mid-walk).
* **Per-reference values are symmetric**: in the captured window both the
  descriptor and the selector accumulate 8 references of value 2 each — the
  references are the same tuple type. No reference-class lever exists.
* **The selector's edge is structural**: its preheader pair
  (home-load + inc, or entry-load + inc) and its tail pair (inc + compare)
  are two-reference blocks (f18=4) at the highest block weights — one
  captured add was `f18=4 × w=20 = 80`. The descriptor has exactly one
  reference per block everywhere (entry LEA, preheader operand-LEA, head
  type load, two kind loads, tail increment). Both shapes are identical in
  retail's own body (`inc ebx; cmp ebx,ecx` tail pair is retail's).
* Every spelling that would give the descriptor a second same-block
  reference folds (`descriptor += 4; += 4`, `+ 2 + 2`, split init) and every
  one that adds a real reference restructures the loop (hoisted kind byte:
  581 bytes, full re-plan, selector moved to EDI) or extends the live range
  into subtract-weighted blocks (the earlier derivations).

**Conclusion**: under the decoded formula the two candidates' reference
structures are symmetric in value and per-block count except for the
selector's two intrinsic two-reference blocks, which retail's own body also
has. The retail flip therefore cannot be produced by the reference
structure available to a semantically equivalent source; it must come from
a c2-internal component outside the decoded accumulation (block-weight
assignment or the initial-home pass), consistent with the joystick note's
open unknowns. Bounded effort spent; parking again with the mechanism fully
mapped.

## Round 6 (2026-10-13): scope-size probe — harness built, first data point

`scope_probe.py` grows the cluster's `additional_sources` with verbatim
copies of real semantic sources (copies under `layout/ltcg/scope/`, manifest
headers recomputed per attempt, link-failing sources dropped automatically
across up to 6 attempts). Pool pre-filters: no `asm_*` externals, no float
literals (`__real@` pooling duplicates across modules), no
relative-escaping or unresolvable includes.

First data points:

| scope | extras live | StartChild size | loop regs |
| --- | --- | --- | --- |
| 0 | 0 | 547 | selector EBP (swapped) |
| 20 script | 9 | 547 | selector EBP (swapped) |

No movement at +9 co-compiled TUs. The game-area 50-source run was consumed
by source hygiene (per-function headers living outside `include/`,
duplicate pooled-literal modules, relative-escaping includes) and its retry
budget expired before a measurement — the harness now handles each of
those; a future session can raise the retry cap and re-run at 50/100+.
If later measurements also show no movement, the allocator wall is
scope-independent and the mega-cluster endgame is dead; if the size or the
loop registers move as scope grows, it changes the endgame for every parked
region.

## Round 6 status (end of run): ladder blocked on harness convergence, not on c2

**Final debugging state (second end-of-run pass).** The /showIncludes
pre-pass is implemented and works (per-TU union == 49 headers, matching the
probe's own reports), but the 50-exit probe still fails
`compiler did not report every declared implementation/header include`
with 26 surviving extras, 33 compile logs present, only 16 containing
include notes, and even common headers (`include/th10/types.hpp`)
unreported — while the same TUs' /showIncludes pre-pass reports them fine.
The quirk is inside `_verify_includes`'s view of the merged include logs
(33 logs, 16 with notes — most extra-TU compiles in the probe run appear to
produce no include output at all), not in the header computation.
`scope_probe.py` now has: 12 attempts, mixed-area pool, auto-declaration of
address-embedded `_data_*`/`asm_*` unresolved symbols, source drops by
object index for any fatal error, per-run header relearning from compile
logs, and the winpath `/Fo` fix for the pre-pass. Ladder table unchanged:

| scope extras | StartChild size | loop regs |
| --- | --- | --- |
| 0 | 547 | selector EBP (swapped) |
| 9 | 547 | selector EBP (swapped) |

Next session: debug `_verify_includes` with the saved diag logs
(`matching2/build/probe-eclstart-m50d9/`) — check which include_reports the
merged log actually contains for the extra TUs (the per-TU .obj.log files
there have the reports; the failure says the merged view does not) — then
run the 50/100+ rungs and apply the decision rule. Everything else in this
note stands.

**Sharp final observation for that session**: at 50 extras the per-TU
`.obj.log` files themselves are truncated — e.g. `source_010.obj.log`
(scope_014) contains the source banner and exactly ONE `Note: including
file:` line, `source_020.obj.log` two lines, where the same TUs at 9 extras
(or run standalone via the pre-pass with identical flags) emit dozens. The
compiles succeed and the objects are fresh, so this is an output-capture
truncation of cl's /showIncludes stream at larger TU counts (wine stdout
pipe interaction), not a compiler or header-set problem. `_run_logged`
(`ltcg_semantic.py:472`) does a plain `subprocess.run(capture_output=True)`
with no cap, so the truncation happens inside wine's console emulation —
the pre-pass (which invokes cl the same way one TU at a time and captured
complete reports) is the workaround template: if `_run_logged`'s capture is
replaced by an explicit file redirect for the compile step (cl writes
/showIncludes to stdout; redirecting via a shell or reading the log file cl
itself writes with `/Fs`-style options is not available, so a small
`cmd /c cl ... > log 2>&1` wrapper under wine is the likely fix), the
50/100+ rungs measure directly.

**Redirect experiment result (final)**: the file-redirect wrapper (probe run
in-process with `_run_logged` patched to `subprocess.run(stdout=open(log))`)
was implemented and tested — the truncation PERSISTS with the redirect, so
it happens inside wine/cl's own emission at larger TU counts, not in the
Python capture path. The wrapper also regressed the previously-passing
9-extras control (through accumulated cross-run drop state), so it was
reverted; the scope harness is back to its last-working pipe-capture form
with pristine manifest, empty scope dir and cleared state. The scratch tree
is restored to the verified best draft (547/498, SpawnChild EXACT, whole
probe EXACT). The scope ladder stands at: 0 and 9 extras measured (no
movement); 50+ requires either solving the wine /GL /showIncludes emission
truncation at scale (e.g. running the probe's compiles with the toolchain's
console allocation changed, or batching extras into fewer, larger TUs so
the TU count stays small) or accepting the two-point evidence as
inconclusive on scope dependence.

## Round 7 (2026-10-13): batch mode built (Main's option a), convergence in progress

`scope_batch.py` implements the batching: 100 mixed sources → 10 combined
TUs (unique includes hoisted to the top, source bodies concatenated with
`// ==== <name>` section markers, literal-pool/asm/relative-include
pre-filters), per-TU /showIncludes pre-pass for the exact header set, and a
convergence loop that parses each failed attempt and drops the offending
sources: header redefinition collisions (C2371 naming a header → drop a
late includer), batch-body errors (mapped back to their source section by
line), unresolved address-embedded symbols (auto-declared), unresolvable
C++ symbols and pooled-literal duplicates (source dropped). Link errors at
the first batched attempt collapsed to 13 (vs 91 unbatched) — batching
itself works.

**Current blocker (exact)**: the convergence loop's failure classes are
handled but their ORDERING lets a stale link.log shadow the compile-error
branch: after the compile-error/collision branch finds nothing in the
per-TU logs it did scan, the link branch re-globs `link.log` and can match
a stale phase-b log, printing `no actionable failures` and stopping.
Additionally the C1083 class (per-function files outside `include/`, e.g.
`score_manager_factory_context.cpp` — its pool filter is now added) and the
C2371 header-collision class (e.g. `data_00491be4` defined in
`manager_teardown_native_0041adf0.hpp`, `ending_screen_0042d300.hpp` and
`scheduler_remove_locked.hpp` — its pool filter is now added) are handled
but each attempt only surfaces the first few, so convergence takes several
persisted runs. Fix for next session (small): in the no-map branch, always
parse the per-TU source logs of the CURRENT attempt first (both fatal and
C-error classes, mapping batch lines to sections), and only treat a
non-empty CURRENT link.log as a link failure; delete the stale phase-b
output dir (`probe-eclstart-scope_<tag>b`) alongside phase-a each attempt.

Standing result: StartChild best draft 547 bytes (+3), SpawnChild EXACT,
whole probe EXACT, region still assembly — re-verified after the restore.

**Final batch-convergence finding**: after pragma-once/guard fixes and
filter hardening, the remaining 100-source blocker is cross-cluster
context-header collisions — the per-cluster context headers that other
clusters copy into `include/` define the same struct/function names
(`struct TaskLink`/`Scheduler` in
`marktext_dispatcher_context/scheduler.hpp`,
`right_aligned_text_context/scheduler.hpp` and `th10/game/scheduler.hpp`;
`data_00491be4`/`data_00491c10` in three manager headers), and a batch TU
that pulls two of them collides. These headers reach the batch TUs
transitively (no batch source includes them directly), so the drop loop
cannot attribute them to a source without walking the header include graph.
Next session's options: (a) walk the transitive header graph to find and
drop the includer sources; (b) rename/guard the colliding scratch-header
definitions (scratch-only); or (c) restrict the batch pool to sources whose
headers are collision-free. The batch harness itself (scope_batch.py) is
complete: batching, per-TU header pre-pass, auto-declaration, per-class
drop handling, persisted state, and the relearn path — re-verified working
through to real link stages (link errors collapsed 91 → 13 → a handful).

**Final batch-convergence finding**: after pragma-once/guard fixes and
filter hardening, the remaining 100-source blocker is cross-cluster
context-header collisions — the per-cluster context headers that other
clusters copy into `include/` define the same struct/function names
(`struct TaskLink`/`Scheduler` in
`marktext_dispatcher_context/scheduler.hpp`,
`right_aligned_text_context/scheduler.hpp` and `th10/game/scheduler.hpp`;
`data_00491be4`/`data_00491c10` in three manager headers), and a batch TU
that pulls two of them collides. These headers reach the batch TUs
transitively (no batch source includes them directly), so the drop loop
cannot attribute them to a source without walking the header include graph.
Next session's options: (a) walk the transitive header graph to find and
drop the includer sources; (b) rename/guard the colliding scratch-header
definitions (scratch-only); or (c) restrict the batch pool to sources whose
headers are collision-free. The batch harness itself (scope_batch.py) is
complete: batching, per-TU header pre-pass, auto-declaration, per-class
drop handling, persisted state, and the relearn path — re-verified working
through to real link stages (link errors collapsed 91 → 13 → a handful).

**Option (b) result (final)**: the namespace wrap was implemented (headers
wrapped with includes hoisted outside the namespace to avoid a `size_t`
ambiguity) and worked until a second-order ambiguity surfaced: a TU that
includes BOTH wrapped headers hits `using namespace` ambiguity on the
shared type names when a nested header uses them unqualified
(`recovery_script_executor_ascii_anchors.hpp` on `SchedulerTask`). Removing
the md header's using-directive fixed that class; the next divergence was
the manifest header set itself: per-TU pre-pass reports match the probe's
per-TU reports exactly (verified batch-by-batch, pre==post for all 7 TUs),
but the manifest's declared set retains headers from earlier attempts' TUs
(`ending_screen_0042d300.hpp`, `item_0041b8e0.hpp`, … — 12 stale entries)
because apply_manifest is not re-invoked between the drop and the re-probe
in every path, and the relearn-from-logs path re-persists a union. The fix
is to make scope_batch's header/manifest management stateless: derive
`headers` inside the attempt loop from the pre-pass over the CURRENT extras
immediately before each probe call, and never persist them in the manifest
file (pass them via the same apply_manifest call that writes
additional_sources). With that, the b100 rung measures directly: the
compiles are clean, the link runs, and the remaining verdict is the byte
comparison. Scratch restored to the verified best state after this run.

**Stateless refactor applied (final state)**: apply_manifest(extras) now
runs at the top of every attempt (line-verified: calls at script start, loop
top, and both drop paths), deriving headers from the /showIncludes pre-pass
over the current TUs with no persistence. Residual: one diagnostic pass
showed the manifest still lagging a drop iteration in the final converged
state (10 headers of dropped TUs declared while absent from the current
TUs' reports) — the next session should add a one-line guard that asserts
`declared == ORIGINAL ∪ per-TU pre-pass union` right before the probe call
and re-derives on mismatch. With that asserted, the b100 rung produces its
first clean measurement and the ladder decision rule applies. The verified
best state (547/498, SpawnChild EXACT, whole probe EXACT) is restored.
