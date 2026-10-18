# Core ECL interpreter at 0x0044E1A0: equivalent recovery, not byte-exact

The 7,020-byte region (6,692 bytes of code plus jump tables) is registered
under `equivalent_recoveries`: readable C++ that compiles to the same
instructions as retail apart from compiler tie-breaks. The default build
compiles it into the executable after `tools/matching/equivalence.py` has
checked it against the exact bytes. The inline assembly in
`msvc/src/script/ecl_core_interpreter.cpp` is kept for the exact link that
check compares against and for `make EXACT=1`. This note records the model, the accepted
differences, and why they were not closed.

## Files

- `msvc/equivalent/script/ecl_core_interpreter_0044e1a0.cpp`: `EclVm::Run(float delta)`.
- `msvc/equivalent/script/ecl_core_interpreter_0044e1a0.hpp`: the VM, stack,
  and owner types, with the three force-inlined typed pops.
- `msvc/equivalent/script/ecl_core_interpreter_0044e1a0_context.cpp`: models of
  the helpers and the caller, needed only so the checking `/GL` + `/LTCG` link
  derives the same private register conventions. Only `Run` is compared.
- `msvc/layout/equivalent/ecl_core_interpreter_0044e1a0.json`: symbol bindings
  and the recorded differences.

## How close it is

Compiled with the project flags plus `/GL`, linked with `/LTCG`, and compared
against the built region by instruction, with branch targets and jump-table
entries followed through the alignment and callee and data symbols bound to
their retail addresses:

| Instructions | Count |
| --- | --- |
| Total | 1,790 |
| Identical | 1,679 (93.8%) |
| Base/index order only | 96 |
| Recorded differences | 15, in 12 places |

Frame size (0x108), prologue, register roles, case order, jump tables, every
call target, and every opcode's structure match. What differs:

1. **Base/index order in the inlined pops** (96 instructions).
   `mov ecx,[eax+esi+8]` versus `mov ecx,[esi+eax+8]`: the same address with
   the two registers encoded in the other order.
2. **Stack slots in opcodes 50 and 52** (12 instructions, class
   `stack-slot-order`). Opcode 50's second operand and result are at 0x20 and
   0x28 in retail and at 0x24 and 0x2c in the model; opcode 52 is the reverse.
   The locals are scoped to their case, so this is a renaming.
3. **Opcode 30 type lookup** (3 instructions, class `operand-order`). Retail
   adds the argument offset to the instruction's first word and then indexes
   from the instruction pointer; the model adds the pointer first. Same address.

All three are different encodings or orderings of the same computation. No
runtime test was performed; the equivalence claim rests on the instruction
comparison alone.

## What the source had to look like

- `PopRaw` returns whether it took a value, and `PopInt` / `PopFloat` consume
  the tag word only on success. Forms that repeat the `sp - 4 >= 0` test, or
  nest a raw pop inside a second test, give `sub eax,4` where retail has
  `add eax,-4`, or put the value and tag loads out of phase.
- Opcode 10 takes the first raw pop through a local `EclStack*` and the second
  through the member. Retail orders the two loads differently and no single
  spelling reproduces that.
- `IntValue` pops into its own `value` parameter, which is what makes the
  parameter a stack argument in the LTCG convention (matches 0x0044FF00).
- `FloatValue` is static: `(int selector, EclVm* vm, float value)`.
- The polar temporary in opcode 81 is three floats, giving the 0x108 frame.
- Opcode 30 uses one argument counter incremented in both arms, and calls an
  empty variadic log function. The empty call is what keeps the `'%'` compare.
- Opcode 87 computes `y = atan2(y, x)` into the existing local.

## Why exactness was not reached

The cause was read out of the compiler backend. Microsoft's public symbol
server holds the PDB for this exact `c2.dll` (`c2.pdb`, GUID
`5360F7BD-AFB5-4288-A53F-1FBE04D63911`, age 2). It is stripped to public
names and the DLL is block-reordered, so addresses have to go through the
PDB's OMAP streams, but about 3,400 backend functions get their names.

- `FactCanonSort` merge-sorts the operands of a commutative node with
  `OptCmpHashVal`, an unsigned compare of each operand's hash value.
- For a symbol leaf, `OptHashNode` derives that hash from the symbol record's
  sequence number: `id << 6` truncated to 16 bits for a temporary, and
  `(id & 0x7ff) << 5` for a local or parameter. The value wraps every 1,024
  temporaries and every 2,048 locals.
- `SymAlloc` takes records from LIFO free lists (`SymTmpFreeList`,
  `SymLocalFreeList`) and a recycled record keeps its old sequence number.
  Numbering appears to restart per function: helper functions in the same
  link see small numbers again.

Each inlined pop adds `this + sp`, where `this` is the inlined helper's
parameter symbol and `sp` is a temporary. Which of the two becomes the base
register is therefore decided by two sequence numbers, and those depend on
every symbol the function allocated and freed before that point: locals,
call arguments, expression temporaries, earlier inline instances. Code that
compiles to nothing still moves them.

A gdb breakpoint on `OptCmpHashVal` (through `winedbg --gdb`, on `link.exe`
during the `/LTCG` link) logs both operands of every comparison. With the
numbers from that trace, the hash rule predicts the model's operand order for
every pop.

Retail's pattern is reproduced exactly by shifting three sequences by
constants relative to the model:

| Sequence | Shift needed |
| --- | --- |
| Helper `this` symbols | +377 to +380 (mod 2048) |
| Value-load temporaries | +507 to +526 (mod 1024) |
| Tag-load temporaries | +484 to +502 (mod 1024) |

These figures are for the model as saved; other pop-helper layerings need
different constants but the same shape, with the value shift 5 to 42 above
the tag shift. A constant shift fitting all 63 remaining pops means the
difference sits before the first pop or in function-wide totals, not in the
per-pop code.

Dead statements can supply the first two shifts. A function-scope
`int u = 0;` moves all three sequences by one; `DebugLog("z")` moves the two
temporary sequences by one half each. That is why about 500 dead statements
reached 1769 of 1789 strict matches (counted without the trailing alignment instruction). No construct tried moves the value and
tag sequences apart by the 5 to 42 required, which is the one tag load that
never matched. The stack-slot pair and the opcode 30 ordering have not been
traced; opcode 30's is a three-operand sort through the same comparison.

So the missing information is the original function's exact sequence of
symbol allocations, which the binary does not record beyond these three
residues. An exact build could be engineered with filler once a construct
for the third shift is found, but that would be fitted, not recovered. The
earlier guess that the original contained compiled-out debug output is one
possible source of the shift and nothing more.

## If this is picked up again

- Fetch the PDB from
  `https://msdl.microsoft.com/download/symbols/c2.pdb/5360F7BDAFB54288A53F1FBE04D639112/c2.pdb`
  and map names through the OMAP-from-source stream. `OptCmpHashVal` is at
  0x10795BC5 in the loaded DLL (preferred base 0x10700000); operands arrive in
  ECX and EDX, hash at `+0x10`, symbol at `+0x18`, sequence number at
  `symbol+0x1c`, kind at `symbol+4` (3 temporary, 4 local, 5 parameter).
- Measure, do not sweep: trace a variant, read the three sequence numbers at
  the first pops, and compare with the shifts above. A trace takes about 25
  seconds.
- Opcode 10's first raw pop goes through a local `EclStack*` in the model
  because retail's base symbol there has a small hash. With the mechanism
  known, that spelling is a fit to one data point and may not be the original.
- The extended ECL opcode handler at 0x0040E770 very likely inlines the same
  pops and will depend on the same numbering; that has not been checked. Any
  function whose only mismatch is commutative operand order is the same
  problem.

## 2026-10-17: the stack-slot pair traced; parked

All 12 remaining hunks are the swapped slot pair (`stack-slot-order` class,
base/index 96): two locals sit in each other's slots across two blocks
(the model's `[esp+0x24]` where retail has `[esp+0x20]` and vice versa, plus
the `[esp+0x28]`/`[esp+0x2c]` pair).

Ran the documented `stackpack/trace_stackcolors_cl.py` tracer on the unit and
on a combined unit+context TU (so the `EclVm::FloatValue`/`IntValue` inlining
shows). Findings:

- The colour→offset map is confirmed: `colorElemental`'s return is the colour
  index x4 and colour k lands at frame offset 0x1c + k*4, so the four heaviest
  elements are exactly the hunks' `0x20/0x24/0x28/0x2c` slots.
- The allocation order is the `colorElemental` **call** order, which is not the
  descending-weight list order: the combined trace starts with the
  inlined-helper symbols (`_operand_offset` w4, `_popped` w3, `_value` w2,
  an unnamed temp w2) before the per-case `_a`/`_b` locals (w7, w6, ...). The
  inlined `FloatValue`'s address-taken `value` parameter is one of the top
  slots; the model's swap pairs an inlined-helper slot with a case-local slot.
- The first four elements of the unit-only trace are `_a` (w7), `_b` (w6),
  `_b` (w6) and an unnamed temp (w6), all conflicting with nearly everything
  (the address-taken out-pointer targets), so almost no colour sharing is
  possible; the ordering is driven purely by the call order and weights.

Not tried: changing the reference counts (the memory's "reuse one variable for
two roles", "split a role", "change which copy a later read comes from" levers)
on the specific inlined-helper parameters, because the four swapped elements
could not be pinned to named source locals: the plain-cl traces cannot see the
LTCG inlining of the same four slots at once (the combined TU inlines under
plain cl but the rig inlines under /GL /LTCG, and the helper bodies in the
context TU differ in what each inlines). Next step if picked up: trace the rig's
actual LTCG cluster (the c2.dll symbols via the OptCmpHashVal route in the
2026-10-02 note above) or weight-probe one candidate helper parameter at a
time with the 7-second `equivalence.py` check as the oracle.

Region stays equivalent (116 differing bytes).

## 2026-10-17: the 96 base/index swaps are symbol-count driven, but not the hunks

`OptCmpHashVal` governs this region's 96 base/index swaps (see the
`replay_save_update` note for the hash law and the 32-record slab behaviour),
and this function responds to symbol count more strongly than any other region
measured. Walking the count from the baseline:

| declarations added at the top of `EclVm::Run` | identical | swaps | differing bytes |
| --- | --- | ---: | ---: |
| 8 | 1682/1790 | 93 | 113 |
| 64 | 1729/1790 | 46 | 66 |
| 128 | 1769/1790 | 6 | 26 |
| 96 `DebugLog` calls with arguments | 1770/1790 | 8 | 20 |
| 105–107 `DebugLog` calls with arguments | 1771/1790 | **4** | 24 |

So the swaps are almost entirely an artifact of the function's symbol count:
96 -> 4. But the 12 recorded differences do **not** move with it
(`stack-slot-order` 10, `operand-order` 2), so no count makes the body
byte-identical; the best measured point is 1771/1790 with 24 differing bytes.

The tempting spelling is this file's own `DebugLog` stub (line 12: `static void
DebugLog(const char* format, ...) {}`), which is exactly "calls that leave no
instructions" and would be genuine source in an interpreter. It is not: real
opcode logging is one call site inside the dispatch loop, whereas closing this
gap needs 105 call sites at the top of `Run`. That is padding in the file's own
vocabulary. Region stays equivalent.

## 2026-10-17: used stack words and operands, 116 -> 23 differing bytes

The maintained model now names the raw word, its source/destination and its
cursor offset in `EclStack::PopRaw`, and the actual converted values in
`PopInt`/`PopFloat`. The first sixteen binary operations distinguish their
mutable Pop/Write storage from their immutable left/right operands. Every
added value is used by the original operation; there are no dummy declarations
or debug calls. Operand evaluation and stack-tag consumption stay at their
original points.

| Source form | Identical instructions | SIB swaps | Other hunks | Different bytes |
| --- | ---: | ---: | ---: | ---: |
| Previous maintained body | 1679/1790 | 96 | 12 | 116 |
| Named raw-pop values | 1728/1790 | 47 | 12 | 67 |
| Plus named typed conversions | 1763/1790 | 15 | 10 | 27 |
| Plus sixteen named operand pairs (shipped) | 1767/1790 | 11 | 10 | 23 |

The two address-order hunks at +0x1951/+0x1954 disappear as well. The layout
removes them and reduces the exact expected SIB-swap count to 11. The ten
remaining hunks match the previous reviewed `stack-slot-order` entries
verbatim; no new instruction difference or branch exception was accepted.
`code_bytes` remains 6692; the complete region is 7020 bytes, including its
328-byte exact table tail. This is still an equivalent recovery.

### Actual LTCG stack slots identified

The new `compiler_traces/stackpack/trace_stackcolors_link.py` replays a real
recorded LTCG link and filters by function name. It checks the pinned c2.dll,
waits for module loading, records list elements/conflicts/weights/colours and
allocation order, and requires a completed trace. It never changes allocation
choices or selects its diagnostic output into the build.

A pre-change Run link, plus a byte-identical control renaming each operand
by opcode, identifies the two swapped homes as **opcode 50's integer-add
left/result storage and opcode 52's integer-subtract left/result storage**.
Both have reference weight 6. The apparent +0x28/+0x2C pair is the same
storage with ESP moved by two argument pushes, not another pair of locals.
The old inference that these were FloatValue's inlined parameter slots was
incorrect. Naming/changing FloatValue's result does not move the body.

The complete filtered trace has 95 elements and 64 allocated colours;
`TRACE completed=true` distinguishes completion from a debugger failure.
A plain-cl or combined-TU colour number must not be assumed to be the same
physical offset in the actual LTCG link. The large-frame path through
ColorStackElements also calls the colour sorter at c2 0x1078CB20 when its
stack-size test exceeds 0x80; that is the remaining tie-order target.

Controls that do not close this tie: declaration order/scope, signedness,
inline pop/operation helpers, union/struct word views, and grouping result
homes. Grouping the homes changes allocation throughout the function and is
not shipped. Naming more booleans, opcode constants or operands is
non-monotonic; instruction shape and complete relocated bytes must both be
checked. The best maintained spelling is the 23-byte form above.

Artifacts: `build/experiments/remaining_exact_2026_10_17/`, including
`core_installed_report.json`, `core_installed_diff.txt`,
`core_named_stack_complete.txt` and the source-control scripts/logs.

### Validation of the maintained 23-byte form

`make`, `make EXACT=1`, and all 129 matching/tool unit tests pass.
`make behavior-check BEHAVIOR_PYTHON=matching2/build/behavior-venv/bin/python`
passes its callsite ABI audit, all 473 item fixtures and all 48 replay-submenu
fixtures. The isolated runtime replay returns to title after 11,745 frames;
`tests/replay_sync/compare.py` reports **IDENTICAL: 11745 frames, final score
648615** against `retail-replay-r1b.bin`.

The normal executable SHA-256 is
`c85f6cbd548a7b1aa9f6989507eba42c9e0e1df9e836abfb5e62239385c2a4ca`;
the exact executable remains retail-identical at
`2f14760b6fbbf57549541583283badb9a19a4222b90f0a146d5aa17f01dc9040`.
Logs are `make.log`, `make_exact.log`, `unit_tests.log`,
`behavior_check.log`, `replay.log`, and `replay_compare.log` under the
experiment directory above. No additional region is promoted by this change;
31 equivalent regions remain.

## 2026-10-18: base/index residuals closed (11 -> 0 SIB bytes); 12 home bytes remain

The 11 remaining SIB bytes are gone: the model now compiles with
`base_index_order: 0`. The 23 differing bytes are down to the 12 bytes of the
stack-slot pair at 0x406-0x4cd (the swapped integer add/subtract result homes,
opcodes 50/52).

### The operand-hash mechanism, decoded exactly

`matching2/reference/compiler_traces/operandsort/trace_operand_sort_full.py`,
fed a captured link (`prepare.py`-style commands with the leading `wine`
stripped) and filtered to `Run@EclVm`, logs both operands of every
`OptCmpHashVal` comparison with their symbol ids. The hash law is confirmed
against the live trace for all 124 pop comparisons:

- temporary: `0x10000 + ((id << 6) & 0xFFFF)` (wraps every 1,024 temps)
- local/parameter: `0x10000 + ((id & 0x7ff) << 5)` (wraps every 2,048 locals)
- the operand with the **larger hash becomes the base register** of the emitted
  `[base+index]` addressing.

All 64 pops map 1:1 onto source positions (case 10's two raw pops, 14, 13, 43,
45, then the two-pop arithmetic/comparison cases in source order, ending 79,
80). The 11 recorded SIB bytes are exactly the comparisons of pops in cases
62 (second pop), 64 (both), 66 (both) - each value and tag load - and case 80's
value load. The id space is banded: locals 4..2656, value-load temps
~3072..4352, conversion temps in the gap, tag-load temps ~5120..6400.

Dead constructs move the bands through the LIFO free lists in 32-record slabs,
so every dead-decl/DebugLog count moves the ids in chunks and the response is
plateaued and non-monotonic. The value and tag bands move in lockstep; the
surviving residuals are wrap-placement problems: e.g. the last value temp sits
just below the 4,096 wrap and the last tag temps straddle the 6,144 wrap, so
the windows are 18-36 units wide while the slab steps are 32.

### The closing lever

The window needs a *fine* shift (a few symbols, not a slab). **Naming operand
copies in one more binary-op case** provides it: `const float left_operand = b;
const float right_operand = a;` in the float-compare cases (59-77) are live
named locals whose symbol records are allocated one at a time, unlike dead
constructs. Naming the operand pair in case 62 (or 64 or 70) on top of the
previously measured 13-byte state closes the last SIB byte:

| form | identical | SIB swaps | other hunks | bytes |
| --- | ---: | ---: | ---: | ---: |
| shipped 2026-10-17 model | 1767/1790 | 11 | 10 | 23 |
| + 20 dead decls + 140/15 dead DebugLog calls at top of Run, PopInt conversion un-named (ic0), tag by reference, one extra named value in the raw pop, operand pair named in case 62 | 1778/1790 | **0** | 10 | **12** |

`equivalence.py` reports `base_index_order: 0`, `not_equivalent: []`; the 10
remaining hunks are exactly the 12 home bytes.

### The 12 remaining bytes: the result-home tie

The two swapped homes are case 50's and case 52's `left_storage`
(`trace_stackcolors_link.py` element list indices 1 and 2, both reference
weight 6, identical conflict sets; their ids track together across every knob
state measured, 19/23 in the plain model up to 391/395 in the closing form).
The frame offsets come from a conflict-aware packer whose per-element
placement is scrambled relative to creation order (retail: 50->0x20, 52->0x24,
58->0x28, 57->0x2c, 51->0x30, 55->0x38, 56->0x3c, 53->0x40, 54->0x44). The
model places 52 at 0x20 and 50 at 0x24; retail is the reverse. The tie order
that decides it is the pair's relative symbol-id order: retail's original build
allocated case 52's home symbol before case 50's (free-list artifact of the
original symbol count). Flipping it needs an id inversion of two adjacent
allocations (or the 2,048-wrap of the pair's hashes), which the free-list slab
movement never produced in ~50 measured states (the pair always moves in
lockstep, or case 50's jumps first by +164).

Ruled out for the tie: weight probes (the weight is the six memory accesses to
the home - pop store, conversion load/store, operand load, Write lea, result
store - pinned by the identical instruction stream); the named-operand copies
fold away and do not count; split/reuse result homes change the instruction
stream (branch gate); declaration order inside the cases shifts both ids the
same way; every dead-construct count, convert-role spelling, tag-reference and
raw-pop spelling measured.

Region status: 12 differing bytes (was 23), `base_index_order: 0`. The closing
form's dead decls/DebugLog calls are probe scaffolding for the slab geometry;
the named operands are ordinary source.

### Final verification of the 12-byte state

- `variant.py`: `1778/1790  swaps=0  hunks=10  bytes=12  tail=0`.
- `equivalence.py`: `base_index_order: 0`, `frame_offset: 0`,
  `not_equivalent: []`, `differences: 10` (the home hunks listed above).
- Layout JSON updated: `base_index_order: 0`; the ten `stack-slot-order`
  difference entries are retained (they are still true).

Additional ruled-out evidence for the home tie: a renaming control
(`left_storage` -> `home_50`/`home_52`, byte-identical) at a free-list state
where the two symbol ids separate widely (316 vs 480) shows the sorted
element list still holds case 50's home first with the lower id - the free
lists hand the pair's records in allocation order at every state probed, so
the tie order never inverts; and the placement map is scrambled beyond the
pair (retail slot order: 85a 0x1c, 50 0x20, 52 0x24, 58 0x28, 57 0x2c, 51
0x30, 84a 0x34, 55 0x38, 56 0x3c, 53 0x40, 54 0x44), so the pair's placement
is one entry of a conflict-aware packing whose tie order for equal-weight
elements follows the symbol sequence. ~2,000 knob states were measured
(dead-decl/DebugLog counts, operand namings per case, early-case namings,
convert-role spellings, tag/reference and raw-pop spellings) without the pair
flipping; the two cases' homes also keep equal reference weight (six memory
accesses each, pinned by the identical instruction stream), so the weight
levers cannot separate them.

Region status: 12 differing bytes (was 23 at the 2026-10-17 hand-off),
`base_index_order: 0` (was 11). Not byte-exact: the home pair remains.

## 2026-10-18: shipped form is the clean one; the SIB-zero form needs dead scaffolding

Integration standard: declarations/calls with no purpose in the code do not
ship (enemy_execute precedent; replay_save_update shipped only named USED
predicates and called no-op inline calls "not source"). The 12-byte closing
form above is therefore recorded as mechanism knowledge, not shipped: its
SIB-zero state requires 20 dead `int uN = 0;` plus 155 dead `DebugLog(...)`
statements on top of an un-named `PopInt` conversion spelling (`c01`, which
breaks the instruction stream without the scaffolding). Measured directly:
every clean combination (no dead constructs) bottoms out at 21 bytes.

### Shipped clean form (this change)

Ordinary source only: the operand-pair naming extended to the float-compare
family - cases 62, 64, 66, 68, 70 gain `const float left_operand = b;
const float right_operand = a;` exactly like the sixteen named binary
operations. This is the fine +-2-symbol lever described above and closes two
of the eleven SIB swaps (case 66's second pop value and tag loads):

| form | identical | SIB swaps | home hunks | bytes |
| --- | ---: | ---: | ---: | ---: |
| 2026-10-17 shipped model | 1767/1790 | 11 | 10 | 23 |
| + float-compare operand naming (62-70) | 1769/1790 | **9** | 10 | **21** |

- `variant.py`: `1769/1790  swaps=9  hunks=10  bytes=21  tail=0`.
- `equivalence.py`: `base_index_order: 9`, `frame_offset: 0`,
  `not_equivalent: []`, `differences: 10` (the home-tie hunks listed above).
- Layout JSON updated honestly for this form: `base_index_order: 9`;
  the ten `stack-slot-order` difference entries retained.

Equal-scoring clean alternatives (not stacked - the levers are non-additive):
the convert-role spelling `c31` alone (PopInt conversion named through
`source_value` + `converted`, PopFloat through `source_value` only) also gives
21 bytes with the same nine swaps; any single operand naming alone gives 25
(pairs it with a second argument-slot tie at 0x181b/0x182b); naming all ten
operand pairs gives 27. The remaining nine SIB swaps after the naming are
cases 62 second pop (value+tag), 64 both pops (value+tag), 66 first pop
(value+tag) and 80's value load - exactly the wrap-sensitive comparisons
identified by the constraint analysis.

### Mechanism conclusion for the record

The region's residual SIB encodings are a symbol-population difference
between retail's original source and any honest reconstruction of it: the
hash window can be positioned exactly (the wrap arithmetic above) but the
only levers that reach it either add purpose-free declarations (unshippable)
or perturb unrelated ties. The 12 home bytes are the weight-6 result-home
tie (cases 50/52) whose tie order follows the pair's symbol sequence; the
free lists never invert the pair in any reachable state and the weight is
pinned by the identical instruction stream.

## 2026-10-18 (session 2): exact 3-band solve; re-read/split levers ruled out; gap quantified

State unchanged: shipped clean form, `variant.py` `1769/1790 swaps=9 hunks=10
bytes=21 tail=0`, strict check `not_equivalent: []`, `base_index_order: 9`.
This session produced an exact mechanism solve and a quantified reachability
gap rather than a byte reduction.

### Exact constraint solve (clean-state operand-sort trace `exp/opsort_clean.txt`)

All 124 pop comparisons mapped 1:1 to (temp, this-copy-local) pairs in 64 pop
groups; hash law verified on every pair (temp `0x10000+((id<<6)&0xFFFF)`, local
`0x10000+((id&0x7ff)<<5)`, larger hash = base). Full 3-band translation solve
(`exp/solve_bands.py`): ZERO-mismatch states exist iff value temps shift
Gv=22..26, tag temps Gg=0..2 (or 1008..1012), locals Gt=167..176 (mod
1024/1024/2048) - equivalently every local +167..173 with value temps +22..26
and tag temps +0..2 flips exactly the 9 target comparisons and holds the other
115. Pure temp movement bottoms at 8 mismatches; local movement is required.

### Knob -> translation map (traces in exp/opsort_*.txt)

Named locals move only the LOCAL band, non-rigidly in a fixed stripe pattern
(one of every ~3.4 pop groups gets the "high" value; the early groups a
separate low value): measured high values +42 (10 late namings), +51 (26
namings), +72/73 (8-9 result namings at cases 50-57, also + one select-compare
temp at case 73). Expression compare temps move the value+tag bands
(slab-stepped: 1-2 temps -> (+1,+3); 3-7 -> (+36,+55); 8+ saturates). The
pair's home pack tie was re-confirmed locked: PRESORT order = the pair's
adjacent element-record allocation order at all 33 traced stack-colors states.

### Reachability gap (why the 21 bytes do not close clean)

Given the observed stripe pattern, the required stripe values are
H (18-34 stripe groups, incl. the four target groups 40-43) >= 167 and
M (24-40 groups) >= 93; the largest clean-knob wobble ever measured is H=+73,
M=+9 (this session, ~500 new states; ~2,500 cumulative with the prior
session). The gap is +94 in free-list chunk offsets - the prior session only
reached +164 class jumps with dead-decl/DebugLog scaffolding (unshippable).
Exact per-state analysis: the v73h19 state (constant-true select-compare in
case 73 + result naming in the ten storage cases) is the closest clean state
ever measured - it flips case 66-pop1 and case 80-value (4 of the 9 target
SIB bytes) but flips 4 wrong comparisons in exchange (net 22 bytes). The
feasibility scan shows its stripe pattern closes completely at stripe values
(H,M)=(167,93..102) with the value/tag bands near (7,0..2); those values are
outside everything reachable with honest source knobs.

### Ruled out this session (measured, not inferred)

- Lever (a) constant-true re-read battery (25 compare shapes x cases
  50/52/both): folds to nothing (zero refs, zero id movement) unless the
  compare is unprovable, which either emits code (branch-gate stream break:
  sub-copy vs home, non-constant compares in Write args) or is neutral. No
  home-byte movement in ~60 states. Cross-region confirmed with JoystickEBX:
  the re-read needs an opaque-call barrier (ecl_name_table had memcpy); no
  such barrier exists in these blocks (_ftol cannot alias).
- Lever (c) scoped pointer / live-range split battery (5 shapes x 3
  placements per home): fold-to-nothing or the +151d class. No home movement.
- Genuine namings in all remaining unnamed cases (71-86, 14/13/86/87),
  interleaved operand copies between the pops (all 21 binary cases), result
  naming, w-shape positions at every case, chain counts 1..20, multi-position
  temp placement, temp x local product classes, incremental deltas around the
  best state: every single-knob delta is a fixed point of the 22-byte class;
  cumulative namings degrade it.
- The home tie's sort key: PRESORT tie order = element-record allocation
  order (pair records physically adjacent), never inverted in any state.

Region status: 21 differing bytes (12 home + 9 SIB), `base_index_order: 9`.
The remaining differences are a symbol-population gap: the SIB window is
exactly characterised (above) and needs clean-knob wobble +94 beyond anything
honest source constructs produced in ~2,500 measured states; the home pair is
an allocation-order artifact of retail's original symbol count.
