# Player effect update, 0x00428280, 2026-10-06

Status: complete ordinary C++ candidate, **unselected and not byte-exact**.
The maintained source is `reference/semantic_candidates/effect_update_00428280/`.
Production `src/game/effect_pool_update.cpp` and its 876-byte ownership are
unchanged. No equivalence, mask, opcode patch, partial helper, or synthetic
caller is introduced.

The October 2 full candidate had never reached a useful instruction comparison:
the fixed-layout check failed because its declared 876-byte contribution did not
fit the emitted MAP section. Its actual ordinary body reproduces at 832 bytes
with 79 reported difference groups. The old production D3403 comment's 876/876
count describes the naked baseline, not an exact ordinary C++ recovery.

## Saved result and reproduction

The saved model emits **874 bytes versus 876**, with **3 diagnostic instruction
groups** remaining. Literal comparison gives 205 unequal overlapping bytes plus
2 missing bytes. The overlapping count includes consequences of changed
registers, code placement, and instruction offsets; it is not an independent
semantic failure count. All comparisons include complete contributions and
retain complete retail reference bodies separately.

Six complete helpers have literal equality after diagnostic address
normalization:

| Retail address | Complete helper | Bytes |
| --- | --- | ---: |
| 0x00409E50 | StopAtFrame1 | 65 |
| 0x0040C4D0 | StopAtFrame3 | 65 |
| 0x004491C0 | FindAnimation | 73 |
| 0x004492A0 | FlagAnimation | 66 |
| 0x0044C2A0 | Motion::Advance | 171 |
| 0x00428D70 | OutsideViewport | 91 |

These are supporting graph results, not six new production promotions. A raw
fixed-address proof of the whole owner is still required before its selection.
Other imported boundaries are the existing ordinary polar setter, angle
normalizer, and CRT floating-point helpers; they are declarations and fixed
address bindings, not substitute bodies.

From the repository root:

```sh
python matching2/reference/semantic_candidates/effect_update_00428280/measure.py saved_candidate
```

The runner builds native PEs at two bases before opening the retail oracle.
The second base supplies diagnostic relocation information only. Outputs are
under `build/experiments/effect_update_00428280_2026_10_06/results/saved_candidate/`.
`receipt.json` hashes the source, typed header, runner, layout, compiler tools,
shared timer header, and captured Ghidra evidence. The full native body and
code-only disassembly inputs use separate filenames.

The earlier saved 858-byte / 52-group result is preserved in the receipt's
`prior_saved_result` and the `saved_nonvolatile_858` control. The current source
reuses one complete `FindInBuckets` body for the two inlined lookups and the
outlined 73-byte lookup. This cleanup preserves all measured function bytes.

## Corrections established by current evidence

The root's real contract is one player pointer on the stack, RET4, result zero.
The descriptor callback takes that player pointer in ECX and the current effect
in EDX. The 128 records start at player +0x49C and have stride 0x5C. Typed checks
cover the motion, timer, state, handles, descriptor, callback and owner fields.

The earlier model named the word at player +0x464 `phase`. The maintained
`pause_result_open_004231d0/player/player_state.hpp` places the actual phase at
+0x458, and `stage_timer.current` at +0x464. The candidate now names the genuine
timer and uses its current frame in the familiar-level retirement condition.
The owner extent is checked at 0x4478; effect records and the familiar counters
occupy the existing player's previously unnamed storage.

Animation words +0x14/+0x18 are intrusive child-node next/previous pointers,
consistent with the maintained Entity layout. The old `children_flagged` integer
name was removed. The animation object is checked at 0x3AC and its sprite
pointer at +0x394. Pointer and record corrections preserve the measured output.

The old motion helper multiplied the double floor result by the snap scale
before casting to float. The selected `polar_motion_advance.cpp` casts the
floor result first, then multiplies by 0.01f. Reusing that ordinary calculation,
its vector operations and separate path returns makes all 171 helper bytes
exact. Expanding the real motion Update method also produces the root's retail
velocity cursor at effect +0x20, rather than a cursor at the record base.

The old flag helper always returned the found object. Retail returns the
traversal cursor after a child walk, which is null at completion. Preserving
that actual value through a `void*` result makes its full 66 bytes exact and
avoids viewing a child-node pointer as an unrelated animation-object pointer.
Replacing the computed cursor with literal zero adds an unwanted two-byte XOR;
the saved source returns the actual cursor.

The viewport calculation now operates on the genuine position object through
its own member, removing the unrelated ViewportPosition pointer view. Its
complete ordinary body reproduces all 91 bytes.

The old timer condition `speed <= lower || speed >= upper` sends unordered
values into the unit-speed path. Retail's first `test ah,41h; jne` sends an
unordered comparison to the other path. The candidate now embeds the existing
FrameTimer and calls its positive `speed > lower && speed < upper` predicate.
This fixes NaN behavior and reproduces the observed comparison instructions.
The floor conversion still uses the existing CRT helper; no new conversion is
substituted.

The screen origins are immutable .rdata floats: 224.0 at 0x00470B4C and 16.0 at
0x00470B48. Their ordinary literals, with diagnostic constant bindings, preserve
the retail order of all four position additions. FrameTimer's literal 1.0 also
preserves the timer addition's load order. These values are checked against the
retail PE, including its read-only section flags.

## Remaining work and rejected controls

Read-only compiler tracing established that the 858-byte body reused EBP for
zero and the primary lookup result, requiring a new XOR each iteration. The
primary candidate selected EBP from EBX/EBP/ESI with costs 1400/0/1. Both the
global-allocation replay and the later temporary-allocation replay reproduce
all seven measured native bodies without forcing allocation choices.

The candidate now stores the handle words as volatile integers. This preserves
the observed culling reload and all three retirement clears. Lookup IDs are
read once into ordinary four-byte records. The late secondary lookup also uses
one snapshot for both its test and argument, matching retail's single read.
The effect state word is volatile, with one initial snapshot used by the first
two state tests. This preserves its clear before the missing-primary handle
lookup. These access-order controls bring the instruction differences from 52
to 3 while keeping every complete helper exact after diagnostic normalization.
The player, zero and position homes, loop entry/reload/alignment blocks, lookup
walks, removal blocks and timer instruction sequences now reproduce retail.

The remaining groups are:

| Retail offset | Remaining difference |
| --- | --- |
| +0x263 | FlagAnimation's ID load/push uses EAX instead of ECX. |
| +0x294 | The primary position's Z copy uses ECX instead of EAX. |
| +0x2A4 | FindAnimation's ID argument directly pushes EAX instead of copying EAX to ECX and pushing ECX. |

The missing two-byte argument copy accounts for the size difference; subsequent
instruction offsets and relative branch/call bytes also shift. None of these
differences is accepted, masked or repaired by a byte patch.

`trace_evidence.json` records the checked compiler traces and replay equality.
The maintained temporary tracer now records source memory displacements as
well as following stores. The primary Z copy starts at the ECX cursor and
selects ECX; the secondary Z copy starts at EDX and selects EDX, already matching
retail. There is one function cursor reset and no marker reset in the owner.
The two helper argument copies are not identified as temporary-allocation
events; their call-argument lowering needs separate investigation.

`source_controls.json` records 62 full measured controls. Separate lookup
helpers, component cursors, structured loop forms, early inactive exits,
effect-member expansion, lookup-node returns, unsigned handle storage, and
pointer/id helper conventions do not close the gap. A whole-object byte cursor
is rejected on its emitted result; its earlier array-only spelling is also
marked invalid because the final advance leaves that array's representation.
That spelling is not retained. The saved source traverses the actual typed
EffectEntry array. Constructor, assignment, member and stdcall lookup forms,
early tail exits and position setters do not close the remaining gap. A
nontrivial ID copy constructor also regresses three supporting helpers.
The integer-ID member control shortens FlagAnimation to 64 bytes and also fails
the owner, so it is not retained.

A useful next investigation is native call-argument copying of the real
four-byte ID, together with the temporary allocation of the primary Z copy. Avoid
adding unused work or an opaque stand-in to manufacture register pressure.
The full source graph is saved so those questions can be measured without
reconstructing the old failed fixed-layout rig.

## Call lowering trace follow-up

`call_lowering_evidence.json` correlates the saved source with read-only native
compiler traces. Both helper IDs are scalarized before Riscify and participate
in global register allocation. The removal ID is candidate 19 (declaration
0xB, priority 32), assigned EAX; the late secondary snapshot is candidate 20
(declaration 0xC, priority 56), also assigned EAX. Neither call triggers the
aggregate-argument LoMbArg path. The corrected trace covers 12 lowering calls,
29 global-allocation choices and the full pre-Riscify owner, and its replay
reproduces all seven native bodies. No allocation choice is forced.

Eleven further measured controls include unsigned, immutable and bitfield ID
words, argument reordering, ID reuse, temporary constructors, a local culling
result, a switch-form culling branch and a void removal result. None improves
the saved three-group result. Copying the whole rendering position regresses
to 926 bytes and 21 groups. The volatile integer-ID member again shortens the
removal helper to 64 bytes. The maintained source and production selection are
unchanged. The remaining investigation concerns original source lifetimes and
temporary allocation, rather than aggregate-call memcpy lowering.


### Additional measured source controls

The ledger now records 65 measured controls. Copying the single primary Z
float through ordinary `memcpy` reproduces the saved 874-byte body with three
diagnostic groups. A volatile Z read and a late whole-ID record snapshot each
produce 874 bytes with four groups. All six supporting helpers remain exact.
These controls are unselected; the canonical three-group body is unchanged.
At that checkpoint, the prepared culling-ID copy variant had not been built and was not counted.


## Complete native differential validation and source readability

The retained `differential.py` now executes the complete raw native owner and
all six complete native helpers against retail. It overlays the raw native PE
onto the original loaded image so both runs share the existing raw polar,
angle-normalization and CRT math routines. No instruction is patched and no
math helper is replaced with an invented approximation. Only the descriptor's
actual callback boundary is scripted; it checks player/effect arguments,
records invocation order and can mutate handles, position or state before
clobbering the caller-saved registers and returning.

All **215 cases pass**. They cover empty/inactive records, first/middle/last
records, both animation buckets and missing IDs, child chains, familiar-level
and script-dependent retirement, touched/started transitions, sprite culling,
linear and orbit motion, rotating sprites, timer speed boundaries, NaN and
infinite timer speeds, callback mutation, random finite combinations, and
whole 128-record sweeps. Each comparison checks the complete 0x4478-byte player
and the 0xA0000-byte animation/node/descriptor pool, not just returned flags.
Assertions also check result zero, callee-saved registers, RET4 cleanup, x87
stack balance and control state. `differential_receipt.json` records artifact
hashes, the observation digest and executed helper counts. Coverage counters
confirm every advertised helper executes; for example, Advance executes 565
times, FindAnimation 396 times, StopAtFrame1 64 times and StopAtFrame3 once.

This remains bounded emulator evidence with scripted callbacks. It is not
byte equality or an execution of the complete game on real hardware. The
NaN/infinite timer cases describe this compiler's emitted conversion code;
they do not establish portable C++ float-to-int conversion semantics for
nonfinite values. The test deliberately exercises the original CRT conversion
rather than substituting Python conversion behavior.

Reproduce against the saved current native module:

```sh
python matching2/reference/semantic_candidates/effect_update_00428280/measure.py saved_candidate
python matching2/reference/semantic_candidates/effect_update_00428280/differential.py \
  --candidate matching2/build/experiments/effect_update_00428280_2026_10_06/results/saved_candidate/model.exe
```

Unicorn 2.1.2 is available through the existing ignored joystick-experiment
dependency directory or a normal Python installation. The formatted source and
header are easier to review. A fresh native compile preserves all seven
complete diagnostic bodies. The raw 1536-byte native .text also equals the
independently measured single-Z bitcopy control, SHA-256
`69ff6b28b7c408569b32915b55c5c8d4937726631e7bb61957957b212c8b492a`.
Historical compiler traces retain their original source hashes; the receipt
records the relationship to the formatted source through unchanged body
hashes. The new native PE hash is refreshed after linking and rerunning the
215-case test.

The ledger now contains **70 measured controls**. The previously prepared
culling-ID bitcopy reproduces the canonical 874-byte, three-group body. A
screen-position value return grows the owner to 913 bytes / 16 groups. An
animation-object position setter, a typed handle snapshot and an implicit
handle-to-ID conversion each emit 874 bytes / four groups. All six supporting
helpers remain exact after diagnostic normalization in these controls. None
is promoted. The canonical owner remains 874/876 bytes with the same three
instruction differences and full-body diagnostic SHA-256 reported above.

A fresh whole-file audit confirms the 487,936-byte production executable is
still identical to retail, SHA-256
`2f14760b6fbbf57549541583283badb9a19a4222b90f0a146d5aa17f01dc9040`.
Exact ordinary C++ coverage remains 61.3%, with 62 inline-assembly regions
remaining. Production sources, manifests and matching tools are unchanged in
this follow-up. The byte recovery remains open on the two actual ID argument
copies and the primary Z temporary allocation.
