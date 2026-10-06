# Genuine shared effect/pickup caller graph

The previous turn made progress on the
[pickup frame and types](player_pickup_frame_00428630_2026_10_06.md).
This follow-up joins that complete 15-function source with the
[complete effect update](effect_update_native_00428280_2026_10_06.md), using
one shared animation lookup and removal implementation. There are **20** full
genuine functions: 15 pickup/creation bodies and the effect owner, two stop
variants, motion advancement and viewport test. No synthetic caller or helper
is introduced. The two actual entries are the public roots of a native DLL
with no startup code.

The shared animation layout now covers the actual 3AC-byte object, including
its intrusive child links, Z rotation, scales, stop frame, screen position,
flags and sprite resource. The common lookup walk supplies both real inlined
lookups in effect update and the one outlined 73-byte lookup. All stopping,
validation and removal calls reach that same implementation. The canonical
source retains the complete typed arrays and creation/initialization bodies;
no part of a target is omitted or replaced with an opaque substitute.

| Complete body | Native / retail | Unequal overlap | Instruction groups |
|---|---:|---:|---:|
| Hit-test | 203 / 202 | 144 | 7 |
| Pickup sweep | 1171 / 1170 | 1012 | 61 |
| Effect update | 874 / 876 | 205 | 3 |

Thirteen supporting bodies are diagnostic-exact after address-only rebinding.
The first control combined the genuine callers while retaining a separate
inline lookup spelling. The retained control centralizes that walk in the
shared list type. All 20 diagnostic bodies equal the first control, and both
owners equal their isolated checkpoints. Thus the extra genuine caller context
and shared lookup source do not resolve the remaining byte differences. That
negative result narrows the next investigation toward the actual ID-copy and
position temporary lifetimes, rather than missing caller visibility. It does
not establish that ordinary C++ cannot match them.

The full 1837-case pickup suite and 215-case effect suite pass against the new
raw native module. The effect observations confirm the common native lookup
executes 396 times, common removal 7 times, StopAtFrame1 64 times,
StopAtFrame3 once, Advance 565 times and the viewport helper 227 times.
These counters verify real helper execution rather than checking declarations.

A further **328** cases execute the two complete retail/native callers in
sequence on the same record arrays, manager storage and animation lists. The
orders are effect/sweep, sweep/effect, effect/sweep/effect and
sweep/effect/sweep: **410 calls to each owner**. They check complete manager,
object and list memory, return values, callback/creation order, score, caller
register preservation, stack cleanup and x87 stack balance. FPU state remains
live between calls. Cases include shared timer progression, collection flags,
creation followed by culling, secondary handles, callback mutation, first and
last records/regions, full 128-record loops, orbit motion and three precision
controls. Sequence observation SHA-256:
`75ee0172ba7fd89e71c2565910b5f3db3d61553c3ee36d2c2dfaa651f2adccbc`.
Together the three suites provide **2380 passing bounded comparisons**.

The initial sequence fixture's scripted VM performed no sprite setup. Retail
faulted in the next culling pass after creation, before any retail/native
equivalence claim. The corrected scripted VM boundary supplies a valid sprite
and scales; the actual culling and animation/creation helpers still execute.
That failed fixture log is retained separately, not counted as a source failure
or as passing evidence. Successful allocation, callbacks and VM effects remain
explicit scripted boundaries. Both runs use the already-recovered constructor
and original polar/angle/CRT code. These tests do not prove arbitrary VM
behavior, failed allocation, portable nonfinite conversions or whole-game
execution.

The stale production effect comment saying `876/876; first_diff=none` described
the naked baseline. It now states the measured ordinary-C++ result and links
the maintained candidate. Function ownership and emitted production
instructions remain unchanged. Sources, snapshots, input hashes, two-base
native images/maps, complete comparison bodies, compiler commands and all
execution observations are sealed in
[the candidate archive](../semantic_candidates/player_effect_pickup_00428280/README.md).
The whole-file production audit remains byte-identical to retail, with
**60 assembly regions / 89245 bytes** remaining. No fixed-address C++ proof,
selection, comparison mask, instruction patch or new recovered byte credit is
claimed. The full executable decompilation goal remains active.
