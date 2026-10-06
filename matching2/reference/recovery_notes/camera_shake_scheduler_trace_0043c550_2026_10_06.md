# Camera shake 0x0043C550: native scheduler trace

The 439-byte camera-shake callback remains an equivalent recovery. No game
source, layout, region ownership, compiler flag or equivalence allowance was
changed in this pass. Its existing 27-byte difference window still consists
only of the FIDIV placement described in
`camera_shake_equivalent_2026_10_05.md`.

Evidence is retained under
`matching2/build/experiments/camera_shake_exact_2026_10_06/`.
`baseline/scheduler.txt` traces the native MSVC 13.10.6030 list scheduler with
`reference/compiler_traces/scheduler/trace_scheduler.py`.
`baseline/trace_commands.json` preserves the replayed link command, and
`baseline/scheduler_proof.json` records the complete callback hashes, scheduler
picks and original comparison. The traced 439-byte contribution is identical
to the uninstrumented baseline contribution. Both use the maintained flags,
including `/G6`; tracing neither patches instructions nor changes compilation.

The relevant scheduler region is graph 9, numbered from zero. Comparing its
pick sequence with the emitted native disassembly identifies sequence 7 as
FMUL, sequence 8 as FIDIV, and sequence 21 as the second seed load. FMUL is
issued at cycle 15 and has a three-cycle edge to FIDIV. The division becomes
ready at cycle 18, has priority 79,872 and is picked in the same cycle as the
seed load (priority 111,616). The subsequent integer instructions are:

| Sequence | Emitted instruction | Pick cycle | Priority |
| --- | --- | --- | --- |
| 22 | XOR EAX,0x9630 | 19 | 81,920 |
| 23 | SUB EAX,0x6553 | 20 | 80,896 |
| 25 | MOV CX,AX | 21 | 76,800 |
| 26 | SHR CX,0xE | 22 | 73,728 |
| 27 | LEA EDX,[EAX*4] | 23 | 68,608 |

Retail places the division after these five instructions, at +0xCE, rather
than the model's +0xB6. Thus the observed difference originates inside the
native list scheduler: it is already present in the recorded picks before
instruction encoding or model relocation. Register allocation, instruction
selection, contribution size and the later branch addresses remain equal.
The trace establishes the model's decision; it does not establish the original
compiler's dependency graph or pairing policy.

A seven-shape source check, including the unchanged baseline, preceded the
trace. Splitting the numerator, quotient or elapsed value, staging the RNG and
using an inline interpolation helper all retained a 439-byte contribution and
the scheduling residual. Some also reversed the independent timer-add load
order. These overlap the older amplitude/helper work and provide no new exact
candidate. The trace is the new evidence from this pass; repeating those source
shapes or the prior volatile/optimization controls is not justified.

The next useful investigation is the division's scheduler dependencies and
issue pairing, preferably against a source-grounded candidate or another exact
retail FIDIV/FMUL window. A source change must still reproduce the complete
439-byte contribution under the shared compiler contract before promotion.
No compiler-output instruction move was made or accepted.
