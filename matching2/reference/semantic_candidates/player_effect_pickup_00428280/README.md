# Shared player effect and pickup graph

This ordinary-C++ graph joins the complete real effect update
and pickup collision sweep, with 20 complete genuine functions. The effect update, pickup sweep and public object initializer are the three
real roots. One shared animation object/node/list
layout and one bucket-walk implementation serve both callers, the outlined
lookup, removal, stopping and validation. No synthetic caller, inline assembly,
register prescription, instruction patch, mask or truncated body is used.

The animation layout covers its actual angle, scale, stop frame, position,
flags and sprite fields, with checks through the complete 3AC-byte extent.
Each retail function has one native contribution and one binding. Complete
creation, registration, allocation and object/script/entity initialization
remain present. Both callers now use one 4478-byte player declaration, one
5C-byte record and one descriptor declaration. The words at 474/478 are the
state timer's previous/current fields; each record contains a full FrameTimer
and Motion. Handle/state storage preserves observed volatile accesses; lookup
IDs are ordinary four-byte AnimationRef snapshots. Creation, registration,
lookup and removal share that recovered value type; the duplicate ID record
and its alias are removed. The complete registrar body remains present.

The complete 202-byte hit-test is now selected through the normal fixed-address
gate. Its second direct-hit arm tests only the focus flag; the redundant
`mode != 0` condition is removed. This ordinary control flow produces every
retail instruction and the private ECX-player/EAX-point convention naturally.
The other 19 complete native and diagnostic bodies are unchanged. Seventeen
collaborators still match after diagnostic address rebinding, including all
three stop variants, the 118-byte registrar, 73-byte creator and 217-byte
initializer. Eighteen full bodies are diagnostic-exact, totaling 2086 bytes.
The effect update remains 874/876 and the sweep 1171/1170 with 1013 unequal
overlapping bytes and 62 instruction groups; these two owners are unselected.
The production graph exports the complete hit-test and already selected
initializer, with raw equality for both. New recovery credit is 202 bytes.

All **2508** bounded comparisons pass: 1965 pickup/helper cases, 215 effect cases and
328 sequences executing the real callers against the same records and lists.
The sequences execute each caller 410 times. They cover both orders, repeated
updates/sweeps, creation followed by culling, secondary handles, callback
mutation, collection, first/middle/last records, 128-record loops, indicator
regions, orbit motion and three x87 controls. The fixture retains FPU state
between calls and checks each caller's register preservation and stack cleanup.
The 32 additional creation cases cover ID wraparound, a nonempty tail-next link,
script loading and both collection/indicator types. Another 48 cases invoke
the public initializer directly with four flag patterns, three script indices,
loaded/unloaded scripts and both loading states. Retaining its real public ABI
also restores the creator's complete retail instruction sequence. Another 48
cases exercise zero and high-bit reference IDs through direct removal in both
lookup buckets and both child-link states. All 20 complete native bodies remain
identical except for the recovered hit-test. The other 19 bodies equal the
shared-reference checkpoint.

These are bounded emulator comparisons. Successful allocation, descriptor
callbacks and animation VM effects are scripted. For sequence cases the VM
boundary supplies a valid sprite, allowing the following real culling pass.
Both runs execute the already-recovered original constructor and original
polar/angle/CRT routines at the stated boundaries. Arbitrary VM effects,
allocation failure and complete-game integration remain untested.

From the repository root:

```sh
python3 matching2/reference/semantic_candidates/player_effect_pickup_00428280/measure.py hit_exact_graph --fresh
python3 matching2/reference/semantic_candidates/player_effect_pickup_00428280/differential.py hit_exact_graph
python3 matching2/reference/semantic_candidates/player_effect_pickup_00428280/effect_differential.py --candidate matching2/build/experiments/player_effect_pickup_2026_10_06/hit_exact_graph/model.exe --output matching2/build/experiments/player_effect_pickup_2026_10_06/hit_exact_graph/effect_differential.json
python3 matching2/reference/semantic_candidates/player_effect_pickup_00428280/sequence_differential.py hit_exact_graph
python3 matching2/reference/semantic_candidates/player_effect_pickup_00428280/audit_receipt.py
```

The runner uses ordinary project compiler flags, `/GL`, `/LTCG`, two real image
bases and `/DLL /NOENTRY`. Executed images retain native addresses; rebound
copies serve only as comparison operands. The receipt hashes maintained inputs
and archived snapshots, compiler identities, commands, full PE/maps/bodies,
cases, observations, comparisons and production audit. See the
[common layout and value-interface note](../../recovery_notes/player_effect_pickup_layout_2026_10_06.md)
and [shared reference follow-up](../../recovery_notes/player_effect_pickup_reference_2026_10_06.md).
The [hit-test recovery](../../recovery_notes/player_hit_test_exact_2026_10_06.md)
records the complete native proof, 14 new controls and seven byte-preserving
compiler traces. Both `make` and `make EXACT=1` pass. The exact executable is
identical to retail; 59 actual assembly regions totaling 89043 bytes remain.
