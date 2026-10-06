# Complete linked-record manager operations in the player graph

The [42-function candidate](../semantic_candidates/player_bullet_state_0041c800/)
adds both complete manager walks to the real player-state/movement graph:
0x41C800 evaluation (76 bytes) and 0x41C850 cleanup (44 bytes). Actual C++ callers
derive the retail private conventions: EAX manager/EBX point/two stack values
for evaluation with RET8, and EAX manager/EBX mode for cleanup with RET0.
Neither helper has an added root, synthetic caller, register constraint or
unused formal input. Both full native bodies match retail raw.

The real cleanup also corrects the owner model. Retail loads EBX with **1** at
0x425D68 and calls cleanup at 0x425D6D, in state 3/frame 15. The earlier external
`Reset()` declaration omitted that mode, and its fixture skipped the body and
cleared the head. The actual function does not clear the head; it saves each
next pointer, calls virtual slot 5 for non-retired records and returns one.
The owner now calls `Reset(1)` and the entire function executes. Evaluation
copies the three-component point at manager+0x440, saves each next pointer,
invokes virtual slot 7 for eligible records and returns the sum.

All 9,812 bounded comparisons pass, including 542 new manager cases. The new
suite exercises evaluation 293 times and cleanup 234 times. It covers all three
record eligibility positions, mode bit patterns, empty and single lists,
callback mutation of next/state/point, repeated cleanup/evaluation and real
owner calls, including the newly explicit state-3 transition. Only virtual
record effects and the existing declared VM/player/callback boundaries are
scripted. The 947 full-owner cases also pass with the real manager bodies.

Four existing selected whole functions / 264 bytes now share this genuine
production layout: manager evaluation/cleanup and animation stop/position.
The two former synthetic manager layouts and the prior genuine 40-function
movement layout are retired from active ownership. Historical sources and
archives stay unchanged. Remaining functions in the other legacy layouts and
the separate 36-function collision layout retain their previous ownership.
No new recovered-byte credit is claimed.

Diagnostic comparison verifies 32 full functions / 3,656 bytes; independent raw
extraction verifies 28 / 3,153 in the fixed native image. The new layout has no
aliases, masks or instruction edits. Both full build modes pass. Exact output
is byte-identical to retail; normal output is unchanged and differs solely in
the eight existing equivalent owners. The fresh production audit covers 963
layouts, 1,484 selected functions and 4,064 current compiler inputs.

The full owner remains 3,044/3,112 and movement 1,640/1,656. Item spawning remains
823/819; script startup's EDX object input still differs from retail ESI. These
are whole unselected functions. Extending the genuine item-update caller graph
is a concrete next source of evidence for the script startup convention.
The strict goal remains active with 59 actual assembly regions / 89,043 bytes
and eight equivalent owners outstanding.
