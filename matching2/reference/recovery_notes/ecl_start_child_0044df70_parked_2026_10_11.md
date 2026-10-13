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
