# Linear camera shake C++ equivalence recovery, 2026-10-05

The complete 439-byte callback at `0x0043C550` is now an equivalent recovery
using `equivalent/platform/camera_shake_0043c550.cpp`. The default build uses
its compiled C++; `make EXACT=1` retains the byte-exact assembly owner.

This uses the complete controller/timer model and RNG storage model from
`camera_shake_0043c550_genuine_graph_2026_10_02.md`. Each axis discards one RNG
advance and duplicates the second word into both halves before reducing it
modulo 3. The model preserves the high seed-storage word and generation count.
The same callback code is reproduced with a compiler-only escaping callback
pointer as the root, without copying the large selector/scheduler graph. The
callback pointer preserves the genuine public ECX argument boundary; it and
its wrapper are not part of the game output.

The existing equivalence gate reports 134 instructions, with only FIDIV
scheduled differently. The manifest records its insertion at `+0xB6` and
removal at `+0xCE` as two exact `evaluation-order` entries. Between these
positions retail executes only:

```text
xor eax,0x9630
sub eax,0x6553
mov cx,ax
shr cx,0xe
lea edx,[eax*4]
```

These instructions read/write only EAX, ECX, EDX and integer arithmetic flags.
FIDIV reads the unchanged divisor at `[esp+8]`, operates on x87 ST(0), and
does not read/write those general registers or integer flags. No intervening
instruction writes memory, changes ESP, calls, branches, or uses x87 state.
Both schedules therefore reach the next instruction with identical live
integer and x87 values and the same memory; neither introduces an extra
rounding/store step. As with native compiler scheduling, this comparison is
of normal execution, not debugger snapshots during an unmasked arithmetic
exception.

Everything else, including branch destinations, instruction encodings,
addresses, and the 439-byte extent, is checked without another allowance.
The equivalence tool and compiler flags are unchanged. The focused production
equivalence probe passes; full gates are run with the surrounding recovery
batch.

## 2026-10-17: the fidiv position sweep, still parked

The queue's "inlined RNG ordered differently around a fidiv" was re-attacked
with the x87 and scheduler levers. Everything tried leaves the model at 133 of
134 with the same two `evaluation-order` hunks (the FIDIV at +0xB6 where
retail has it at +0xCE):

- the 0x004452F0 conversion shape on either operand (`(float)delta` as a
  named local, the product split into named locals, both conversions named):
  each moves the fidiv earlier and adds the `fld`/`fadd` operand-order hunk at
  +0x48 (130-131 of 134); naming the divisor conversion replaces the `fidiv`
  by `fild`/`fdivp` outright (124 of 134);
- the +-one-temp-class shapes near the amount statement (a named `elapsed`
  local, a second `limit` local, a named dropped RNG advance): unchanged;
- moving the discarded `ShakeRandom()` advance before the amount computation
  (RNG order preserved, the amount is RNG-free): shifts the whole register
  assignment to EDI (119 of 134).

The residual is the list scheduler's per-cycle pick between the x87 FIDIV and
the integer RNG chain (`msvc-c2-list-scheduler-priority`: priority = path +
successors + 32-if-load, ties by sequence number). Closing it needs the
scheduler trace (`compiler_traces/scheduler/`) to compute which priority must
change by one and which dependency edge produces it. Region stays equivalent.

The remaining question was whether symbol count — which moves base/index
encoding in `replay_save_update` and `ecl_core_interpreter` — also moves this
scheduler placement. It does not. Ten variants measured with the byte script,
all identical to the baseline 133/134, 2 hunks, 27 differing bytes:

| variant | identical | hunks | differing bytes |
| --- | --- | ---: | ---: |
| baseline | 133/134 | 2 | 27 |
| `pressure-8` … `pressure-128` | 133/134 | 2 | 27 |
| `named-constants` | 133/134 | 2 | 27 |
| `constants-plus-32` | 133/134 | 2 | 27 |

So the operand-hash lever and the scheduler are independent: symbol count
governs `OptCmpHashVal` (base/index encoding) and nothing else. The `fidiv`
placement is the list scheduler's pick, decided by the priority law and the
node's readiness, and no amount of symbol pressure perturbs it. Region stays
equivalent.

## 2026-10-17: actual scheduler readiness captured

A completed real-link trace is now preserved in
`build/experiments/remaining_exact_2026_10_17/camera_target/events.jsonl`
(337 events, 11 graphs; `trace_completed: true`). In the RNG/interpolation
block, FIDIV is node 8: path 45, one successor, static priority 79872,
including its 32-point load bonus. Its FMUL predecessor is picked at cycle
15, and their latency-3 edge makes the divide ready at cycle 18. At that
cycle the second RNG seed load (node 21, priority 111616) issues first and
the divide issues in the other slot. The higher-priority RNG XOR (node 22,
81920) cannot issue until cycle 19 because of the load-to-use edge.

Thus this is a readiness/critical-path difference, not an equal-priority
sequence-number tie. Retail's divide comes after the XOR/SUB/word-copy/shift/
LEA chain; the model begins it while the XOR still waits for its input.
Changing source statement order alone cannot order two already independent
nodes. A source solution must change that dependency or relative priority
without changing the emitted operations.

New negative controls: escaping the RNG/output globals, named predicates,
integer-type/precision variants and G3/G4/G5 compilation all retain the move
or regress; G7 changes extent. No compiler flag or camera source change is
shipped. The isolated memory-view controls, if revisited, live under
`camera_mirror/` in the same experiment directory and do not mutate production
sources during full-build validation.

The memory-view control is complete: the mirror reproduces the baseline
27 differing bytes. Nine full-word read/store aliases, named references and
a scalar-with-accessor representation are identical to it; reading the low
word instead regresses to 105/134. No camera candidate was installed.

## 2026-10-18: the scheduler decoded from c2.dll; the fidiv knob is the x87 edge latency

No spelling closed the 27 bytes this round (~70 variants, all measured), but
the c2 list scheduler was decoded directly from c2.dll (Ghidra, project
`compiler_reference/c2.dll`) and the placement mechanism is now exact. The
residual is no longer opaque; it is a single missing graph edge.

Scheduler facts (functions at 0x107b0b9b / 0x107b050d / 0x107b0d4c /
0x107b04fd / 0x107b049a / 0x10745039):

- Emission order = pick order (the driver appends each cycle's picks to the
  output list). Verified on three builds (39/39 node mapping).
- The ready list is kept sorted by dynamic priority descending, ties by
  sequence ascending (FUN_107b049a). Each cycle FUN_107b0d4c resets
  `dyn = static` and adds a `(1 << shift)` boost to any available node when
  another available node is critical-path, or when its zero-latency
  last-remaining-pred successor is critical and available — this
  successor-consulting boost is the "node pinned by its successor" in the
  handoff. FUN_107b04fd re-sorts the list every cycle, so the boost does
  affect pick order.
- A node is picked when (a) its unit is free this cycle (unit occupancy
  table at 0x108a9d90; per-op occupancy added from 0x108a9db8+4+op*12,
  decaying 1/cycle; the x87 multiply occupies 3) and (b) its ready-cycle
  (node+0x30) `<= cycle + unit_counter`.
- `ready_cycle = max over pred edges of (pred_pick + pred_unit_counter +
  edge_latency)`. The edge latency is the producer's result latency
  (fmul 3, fidiv 42, div 41, partial-register 7, most 1, "stack-order"
  x87 edges 0).

The fidiv placement is exactly `first free x87 cycle after ready_cycle`:
baseline ready = fmul(15) + 3 = 18 → pick 18 → stream +0xb6. Retail's
position (+0xce) means its fidiv was picked after the `lea` (node 27, pick
23), so retail's ready_cycle was >= 24, i.e. six cycles later than the
fmul+3 this source produces. The tracer now reports this field directly
(`t30` in `trace_scheduler.py` output); the target for any future candidate
is `t30 = 24`.

The knob is the x87 chain's edge structure, confirmed by tracing candidate
graphs (`t30` values): named product `float scaled = (float)delta *
elapsed;` inserts a phantom x87 stack copy (op 0x269, emits no bytes) and
the divide then hangs on a lat-0 stack-order edge → ready 15 (fidiv moves
earlier, to +0xaa). The `fimul` operand order (see below) gives ready 19
(fidiv +0xbb). Nothing swept reaches 24 with the retail `fild;fmul`
opcode pair.

Ruled out this round (all byte-gated, none closes; several pin the exact
collateral):

- Timer shape: the shared `FrameTimer::TickInline()` helper replaces the
  hand-rolled tick and *decouples* the +0x48 `fld/fadd` operand-order
  hunk — every amount-statement shape that used to drag that hunk in is
  now measurable in isolation (but none moves the fidiv later).
- Operand-order coupling: `volatile float elapsed` (the sibling's exact
  idiom) or renaming the RNG struct shifts the OptCmpHashVal symbol
  numbers, flipping the multiply to `fld [esi+38]; fimul [esp+4]`; that
  graph moves the fidiv to +0xbb but changes the opcode (unacceptable),
  and adding one named delta local restores the retail opcode and with it
  the +0xb6 placement. The fidiv movement is entirely secondary to the
  opcode flip.
- Divisor spellings: named divisor, const reference, volatile local (branch
  range error), volatile read-through (reload storm, 304 bytes), second
  local copy — all 133/134 at 27 bytes or worse.
- Statement splits (product/quotient/amount locals, pair declarations,
  one/two/three copy chains): copies collapse to one phantom and the fidiv
  only moves earlier (+0xaa, +0xa2).
- Addition operand order, start inlined into delta, delta inline in the
  expression, switch on a named choice, choice evaluated before the amount
  statement (119/134, register assignment shifts to EDI — same family as
  the previously tried RNG-advance move), elapsed accessor/local/volatile
  read, member-function shape (`Screen::LinearShakeUpdate`, 130/134),
  rng.hpp RngState class (u16 recurrence loses the widened seed read,
  113-131/134), local struct with volatile elapsed (128/134).

Best remaining hypothesis: retail's graph carries one extra predecessor
edge into the fidiv (ready = lea's pick + 1). No swept spelling creates
it; the only register the RNG chain (xor/sub/mov/shr/lea) and the fidiv
could share is the flags pseudo-register (the fidiv writes the x87 status
word), and the model's traced fidiv node has exactly one pred and one
succ, so c2 does not model that edge for this source. The tracer rig is
preserved (sandbox `mkcmds.py`, `build_model.py`, `probe*.py`; run
`matching2/reference/compiler_traces/scheduler/trace_scheduler.py
cmds.json out.txt` and read the fidiv's `t30`) so the next attempt can
verify any candidate graph in minutes instead of re-deriving the
scheduler.

## 2026-10-18 (pass 2): the lea->fidiv edge hypothesis audited; all three edge kinds ruled out by retail's stream

The scheduler arithmetic from the section above proves the retail fidiv was
picked at cycle 24 (its stream slot is strictly between the `lea` at pick 23
and `inc esi`, and `t30 = 24` exactly reproduces that slot: the fidiv then
wins the walk against `inc esi` on priority 79872 > 8192 and is emitted
before it). The model's fidiv has ready = 18 = fmul(15) + 3, and the
fmul->fidiv distance can never reach 24: the fmul is stream-pinned at least
6 integer picks before the lea (gen-load, add, seed-store, seed-load, xor,
sub, mov-cx, shr, lea all follow it), while the fidiv is only 3 cycles
behind the fmul. So retail's graph carries one extra predecessor edge into
the fidiv — the candidate being the `lea` (pick 23, lat 1). The three ways
such an edge could arise are all contradicted by retail's own instruction
bytes:

1. DATA edge (divisor derived from the chain's output, or the chain's value
   spilled into the divisor's home). The divisor home `[esp+0x8]` has
   exactly ONE writer in the whole 439-byte region: `mov [esp+0x8],eax` at
   +0x5e, where EAX came from `[esi+0x1c]` (duration_or_strength) at +0x58.
   The `lea edx,[eax*4]` value flows only into `add ecx,edx` (+0xd3) ->
   `mov [0x4918b0],cx` (the RNG seed store); EDX dies at `xor edx,edx`
   (+0xe6). No chain value reaches ST0 (the dividend is the fild/fmul
   product) or [esp+8] — even through a stack home. A shared-home spelling
   would need a visible spill/reload pair; none exists.

2. ADDRESS edge (the lea is address-shaped). The fidiv's operand encoding is
   `[esp+0x8]` — base ESP + displacement, no index register — so its address
   is not computed at all; the lea's EDX is consumed as data by
   `add ecx,edx`, never as an address.

3. x87-status linkage (fnstsw/sahf round-trip linking the divide to the
   chain's flag writes). The only status-word round-trips in the region are
   `fnstsw ax` at +0x20 and +0x2f, both before the `jl` at +0x62 — a
   different scheduling region (the scheduler emits no edges across control
   points). Between the `fild` (+0x99) and the `fiadd` (+0xf0) there is no
   fnstsw/sahf/fstsw at all, so nothing reads the status word the fidiv
   writes; the chain's flag writes are consumed only by `sub edx,0; je`.

The fused-load phantom (a split divisor load whose node would be blocked by
the chain's priorities and fused back into `fidiv [esp+8]`) is also ruled
out empirically: c2 fuses the memory operand into the fidiv node for every
operand spelling measured — named local, const reference, pointer local,
struct/union member, and `__forceinline` helper parameters by value,
reference and pointer (8 shapes) — all give byte-identical placement
(fidiv at +0xb6, t30 = 18), and the traced fidiv node carries the memory
operand inline with exactly one pred (the fmul) and one succ (the fiadd).

The one mechanism that DOES move nodes is the phantom copy (op 0x269) that
named intermediates create (`float scaled = (float)delta * elapsed;`).
Its arithmetic almost works: such a copy is an integer-unit node, and a
copy *in the fidiv's data path* would carry path ~46 (priority ~48k), so
the RNG-2 chain (68608..81920) would beat it on every cycle until 24,
where it would take the int slot and hand the fidiv ready = 24 in the
x87 slot of the same cycle — exactly retail's stream. But every spelling
that creates the copy leaves it DEAD (path 2, its only successor is the
region barrier): the front end propagates the dividend to the fmul's
result and gives the fidiv a lat-0 stack edge instead, so the copy never
mediates. Measured copy-forcing shapes — named product (two, three copy
chains), pair declarations, split assignments, `__forceinline` helper
params (by value/reference/pointer), out-param and in/out-param helpers,
comma operator, struct field, union type-pun — all move the fidiv only
*earlier* (+0xaa..+0xa2), because the copy takes the lat-3 edge and the
fidiv drops to lat 0.

Region parked with a proven blocker: retail's placement requires
`t30 = 24`; every edge kind that could raise the fidiv's ready-cycle from
18 to 24 is contradicted by retail's bytes (single writer of [esp+8], lea's
result consumed only by the seed store, ESP-relative operand encoding, no
status test in the region), and no spelling produces the live phantom copy
that the priority arithmetic would otherwise allow. The next lead is a
graph-level one — find what c2 construct yields a LIVE op-0x269-class node
in an x87 value's data path (or an anti/output edge into the fidiv that
the model's source lacks) — and verify with the t30 oracle before sweeping.
