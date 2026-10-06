# Scheduled effect creation: genuine graph, 2026-10-06

The complete ordinary C++ creator at `0x00427e90` now has the retail 717-byte
extent, with 61 differing bytes in nine instruction groups under address-only
diagnostic rebinding. Its first 457 diagnostic bytes agree. The function is
still assembly-owned, and this work selects no new bytes. Production remains
at 59 actual assembly regions / 89,043 bytes and eight equivalent C++ owners.

Candidate: [scheduled_effect_00427e90](../semantic_candidates/scheduled_effect_00427e90/).
The retained graph has 27 genuine functions and five real roots. It retains the earlier
20 function bodies unchanged under diagnostic address rebinding. Raw native
bodies for sweep, effect update and motion have different pooled constant
addresses in this larger image; this is not a claim that those three raw
bodies remain identical. Twenty-three full functions / 2,557 bytes are diagnostic
exact, including the genuine 149-byte sound queue at `0x0043dd10`.

The complete schedule walker at `0x00428160` now matches all 105 diagnostic
bytes and naturally takes the player in EDI and frame in EBX. The genuine
`0x004281d0` sequence Update caller establishes this convention, with complete
scheduler store (57), timer tick (72) and timer advance (88) helpers. Update
itself is 174/174 with one byte different: its independently rooted ordinary
member entry receives ECX, while retail's outer caller supplies EAX. This
entry difference is neither patched nor credited as an exact recovery.

## Source reconstruction and controls

The actual 0x34-byte descriptor now has period/phase at 0/1, spawn offset at
4/8, angle/speed at 0x14/0x18, ordinal/type at 0x1c/0x1d, primary script at
0x1e, sound at 0x22 and fastcall initialization callback at 0x24. The existing
effect callback remains at 0x28. The 0x4478-byte player has spawn origin at
0x3c0, a schedule file pointer at 0x45c and four 0x98-byte familiar records;
the first fixed-point x/y pair is at 0x32dc/0x32e0. Compile-time offset and size
checks cover these declarations.

The initial full graph measured 794/717, substantially improving on the old
isolated 528-byte probe, but it read resource/script arguments after allocation.
That timing was corrected before retaining a candidate. The explicit familiar
position conversion reproduces retail's pointer origin. Returning from inside
the genuine first-free-slot loop reproduces the full-pool exit and front-loaded
state test. Expressing the real timer reset stores in retail's order and moving
the actual pool cursor before the type guard give the retail descriptor and
position register allocation. A named secondary AnimationRef reproduces the
actual return-object load and restores the 717-byte extent.

Sixteen complete source graph measurements are sealed in
`evidence/source_controls/ledger.json`, including the initial graph, fourteen bounded
23-function source controls and the genuine 27-function sequence context. They use ordinary compiler/linker options without
instruction replacement, register forcing, artificial work or synthetic roots.
All preserve the previous 20 diagnostic bodies and have 19 diagnostic-exact functions in the 23-function measurements,
or 23 in the 27-function sequence context. The retained source extends the named-secondary-ID control with the complete
real sequence caller and timer helpers, formatting and a self-contained include. The ledger makes no behavioral-validation claim
for historical controls; the current retained graph was freshly tested.

Four additional old-owner controls are sealed separately. Automatic retirement
inlining and an assignment in the secondary-handle condition leave all 20
complete bodies unchanged. Forced retirement inlining loses the complete
Retire symbol; removing Find/Mark hints loses the complete Find symbol. Those
two failed comparisons are explicitly rejected, rather than counted as full
graphs or exact results.

## Behavioral evidence

The fresh retained graph passes 3,006 cases: pickup 1,965, effect 215, shared
sequences 328, spawn 186 and sequence updates 312. The spawn fixture compares complete player,
animation manager, allocated object and sound queue state, call results/order,
fastcall callback arguments, callee-saved registers, stack cleanup and x87
balance/control word. It covers first and last slots, a full pool, type-3
suppression, all five valid ordinals, timer/motion modes, resource/script and
allocation variants, ID wrap, callbacks, rotation, sound slot/count/pan limits,
three floating-point precision controls and sequences that repeatedly spawn
then execute the real effect and pickup callers.

All eight instrumented retail branch locations are reached, including the
rotation store at `0x004280bb`. The cases and observations are hash-sealed.
Successful operator new, VM effects and descriptor callbacks are scripted;
retail constructor, polar/angle and CRT math execute in both runs. There are
no instruction patches or adapters that turn a mismatched body into retail.

During fixture development a callback assertion incorrectly required every
repeated spawn to use the first slot. Retail legitimately chooses the next
free slot. The assertion was corrected to require a valid record address and
compare its exact pointer/state against retail. The failed fixture run is not
passing evidence. An earlier rotation case had no loaded script, so the final
fresh suite explicitly loads it and verifies retail rotation coverage.

## Remaining compiler differences

The retained creator's nine instruction groups involve the primary returned
AnimationRef copy/store and its alignment consequence, the player load for
secondary creation, secondary ID load/store, callback frame/receiver argument
scheduling, and the final sound pan load/push. The pool, timer, position,
motion, allocation, object flags and initializer prefix agree through offset
0x1c9. The source is not patched to encode the remaining register choices.

Three hardware-breakpoint-only traces are sealed. The intermediate 722-byte
while-loop graph has 33 events and the initial retained 717-byte graph has 32.
Both preserve all 23 complete native bodies and their 5,632-byte code sections.
The final sequence graph trace preserves all 27 complete native bodies and its
entire 6,144-byte code section (SHA-256
`0b3eca1e883cdb0ef5d63c28c6a74e7a5af23dfba5456df02c27634d746493ec`).
Compiler program/data writes and forced allocation
choices are zero. Hashes and event counts are recorded in each verification.

The intermediate graph allocates the position-derived candidate first
(priority 79, ESI), leaving the early descriptor (76) in EBP. In the retained
graph the descriptor priority is 83 and chooses ESI before the position
candidate (79), which chooses EBP. The returned primary ID still chooses EAX
(priority 50). These traces explain the source-control improvement without
claiming that a forced register choice is a recovery.

The final 312 sequence cases execute Update 318 times, Dispatch 288 times,
setter 79 times, Tick 160 times, Advance 85 times and spawn 162 times. Read-only
hooks verify the naturally derived EDI/EBX walker convention, EAX scheduler
receiver and ESI timer receivers. Each rank table points to a distinct real
schedule descriptor; tests include rank saturation, alternate tables, no frame
change, inactive states, stopping/wrapping, timer initialization, three speeds
and precision controls, and complete follow-up effect/pickup sequences.

The next genuine outer caller is the complete `0x00425730` player update,
which calls sequence Update at its EAX boundary. The existing production
frame_timer cluster contains a synthetic context driver; it was not imported
as a genuine caller into this graph. Derive Update's private entry through real
callers, then continue ordinary source/type investigation of the remaining
handle and call argument lowering. Any promotion still requires the normal
complete raw fixed-address gate and both maintained build modes.
