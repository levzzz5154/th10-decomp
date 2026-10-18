# Replay frame-step C++ equivalence recovery, 2026-10-05

The 68-byte callback at `0x0042A3E0` is now covered by
`layout/equivalent/replay_frame_step_0042a3e0.json`. The default build uses
`equivalent/game/replay_frame_step_0042a3e0.cpp`; the exact build retains its
assembly owner. This is an equivalent recovery, not a byte-exact promotion.

The C++ follows the model and field evidence in `0042a3e0_wave16.md`. It
returns 6 only when a scene exists, its `+0x58` flag bit 4 is clear, callback
state `+0x10` is 1, global flag `0x100` is set, and signed frame `+0x1C8`
has nonzero remainder modulo 4. All other paths return 1. Offset assertions
cover every object field used by the function. Its ECX receiver is retained
by rooting the member itself as the compiler-only executable entry.

All 22 instructions match. The four previously blocking branch displacements
select different copies of the same one-byte RET: retail goes to `+0x3D`,
the compiler goes to `+0x43`. Both copies immediately return with the same
registers, flags, stack, and memory. The null path still executes its own
`mov eax,1; ret`, and the nonzero-remainder path still executes `mov eax,6;
ret`. No branch skips a required result assignment.

The existing equivalence checker proves these tails reach the same code
automatically. The layout therefore has **no listed differences**, no
base/index allowance, no frame shift, and no unproven branch-target exception.
There was no change to the checker and no copying of oracle instruction bytes
into the C++ output.

Validation: the named equivalence probe reports 22 of 22 instructions
identical and zero recorded differences. Both `make` and `make EXACT=1`
passed after integration with the MIDI tick recovery; the latter verified
all 487936 executable bytes.

## 2026-10-17: the four bytes stay parked

The queue's "single shared return versus early returns" reshapes were
re-tested on the renamed model (`goto`-join shared return, `&&`-chain single
exit, inline-helper body, null-path-first orders): every variant reproduces
the identical 68-byte body with the same four `rel8` bytes, the branches
picking the second identical `ret`. This matches `0042a3e0_wave16.md`, which
compiled ~2,200 variants across source spellings, 39 compiler flags and the
native-LTCG path and proved the four bytes are not source-controllable: the
compiler always gives the shared "return 1" label to the `mov eax,1` epilogue
copy instead of the `mov eax,6` one. Region stays equivalent.

# 2026-10-18: wave 17 follow-ups (H1 flag-mismatch, H2 rotation/K) — parked

Sandbox `frame_step` (~120 compiled shapes; `variant.py` batches 1–10, plain-cl
spray harness with objdump verification, flowgraph/Spillcosts/ChoosePhysReg
tracers). Region unchanged: 22/22 instructions identical, 4 rel8 bytes
(0x13/0x18/0x22/0x37) still route to the exit `ret` at +0x43 instead of the
`mov eax,6` fallthrough `ret` at +0x3D. Model and layout untouched.

## (a) H1 — flag-mismatch identity move: exact rule + spellings tried

The join's phi copy `mov eax,eax` is deleted at the end of FgDoLateFlowOpts
pass 1 by the per-tuple peephole (caseD_2 @ c2 0x1079d14c): a `mov` (op 0x1)
is TupRemoved only when dst.kind==0x01 AND dst.reg==src.reg AND
`(*(byte*)(src-node+6) ^ *(byte*)(dst-node+6)) & 0x40 == 0`, with a global
bypass (DAT_108b2268==0 || DAT_108b2264!=0). A node-flag mismatch at +6 bit
0x40 would keep the identity move — a real-class (kind 0x0d) tuple that emits
no bytes at codegen — which would block FUN_107a46e6's forward scan (it
forwards the join label only when the first non-transparent tuple after the
label is a plain unconditional jump).

Spellings tried to force the mismatch (6 constructions, byte/short origins on
either phi arm and on the init; all on the goto-join body):
`char c = 6; result = c;`, `unsigned char c = 6; result = c;`,
`short c = 6; result = c;`, `char one = 1; int result = one;` (6-arm plain),
both arms byte-temp, `result = (char)6;`. All constant-propagate before
regalloc: the join dump is byte-identical to the plain model
(`LABEL; mov eax,eax; 2ab; jmp EXIT`, 1 TransferLabelRefs event), i.e. the
byte origin leaves no byte-width varnode behind. The only non-deleted join
tuple ever observed is `movzx` (op 0xc2) from a genuinely byte-typed result
variable (`unsigned char r`) — 0 TransferLabelRefs (forwarding blocked, all
five 1-paths on the join, null path last) but it emits 2–3 bytes
(`mov al,6`/`0f b6 c0` vs `mov eax,6`) and the family cannot reach the retail
encoding. `return (unsigned char)result` truncation spelling likewise keeps
`movzbl %al,%eax` (c2 does not elide the conversion of constant-clean
values). Conclusion: the flag-mismatch needs a varnode flagged only by a
movzx/and-class definition without a real conversion instruction; no such
source spelling found that preserves the 68-byte stream.

## (b) H2 — rotation/K levers: exercised, measured, not flipped

Per-block Spillcosts tables captured (trace_spillcosts.py, summarize with
per-block selector) for the base model vs the goto-join:

    base  (9 blocks): K=2,1,2,1,0,1,3,1,1
    gj    (7 blocks): K=2,3,2,0,3,1,1

Priorities reconcile exactly with ChoosePhysReg's order
(`p_next = p + 2*K*weight` on a reference, `p - K*weight` on a live-through):
base `this`=13 (4-1+4+6), globals 10/10; gj `this`=11 (4-3+4+6), globals
14/14. The entire gap is the this candidate's live-through loss in the second
block: K=1 (base, -1) vs K=3 (gj, -3). That block carries two extra K units in
the gj: the second global's def and the repeated-immediate candidate (marked
`i` in the table; the constant 1 used twice). Fixing the rotation therefore
needs K=1-equivalent in the this live-through block while keeping the goto-join
CFG.

K-levers exercised (6 spellings, all fold away before Spillcosts — identical
63-byte join output, scene still EDX): fresh second deref of the same global
in the flags test (`((ReplayScene*)*(void**)&g_game)->flags` — CSE'd to one
instruction), dead comma reads `(void)(g_game, 0)` / `(void)(g_input_keys_raw, 0)`,
both together, redundant second `this->state` read, semantically-neutral
repeated-immediate statements (`if (result == 6) result = 6;`,
`if (state == 1) result = 1;`, `if (frame % 4 == 0) result = 1;`,
double `result = 1;` write). Dead/self-assigning statements are removed before
candidate creation, so they cannot raise or lower K. A surviving extra
reference necessarily emits an instruction and breaks the 68-byte stream.

## Consequence

Retail's construction is now pinned down mechanically: value-join for the four
checks (the fail paths must reach the shared `return result`) + a NULL block
that owns its ret (terminal, RPO after the exit: `[mov eax,6; ret 0x3D;
mov eax,1; ret 0x43]`) + scene pointer in EAX (the base's rotation). The
goto-join family delivers the branch assignment but flips the rotation (scene
→ EDX, `mov eax,1` hoists, NULL block CSEs to 63 bytes); the flat-return
family delivers the rotation but not the assignment. The two requirements
converge only through the K change above (or the H1 flag-mismatch tuple).
Region parks as equivalent with every mechanism decoded.
## 2026-10-18 addendum 2: K block-membership moves — fold away, region parks

Main's final construction (move the two K-offending defs out of the `this`
live-through block, same instructions, different block membership) tested as
7 single-statement moves: keys load hoisted to the entry block
(k1_keystop), keys load as first inner statement (k3_keysinner), keys
hoisted + flags check as flat `return result` (k4), keys hoisted + fresh
second deref of g_game (k5), keys hoisted + `int result; result = 1;` split
(k6), keys hoisted + first two checks flat (k7), keys hoisted + flags flat +
no second def (k8). All 7 produce the byte-identical join output (63 B,
20 instructions, scene in EDX, `13/18/22/37 -> +0x3e`). The per-block
Spillcosts table of k1_keystop is bit-identical to the plain goto-join
(K = 2,3,2,0,3,1,1; this 11 vs globals 14/14): c2 normalizes the global
load and the init materialization back to their original blocks before
candidate creation, so per-block K is not movable by statement placement.
With added references and repeated immediates also folding away (previous
addendum), all three K levers are exercised and inert. Region parks: 22/22
identical, 4 rel8 bytes, every mechanism decoded down to the per-block K
table and the label-forwarding predicate.
