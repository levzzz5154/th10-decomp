# Genuine player hit-test and pickup sweep candidate

This directory contains the complete ordinary-C++ collision sweep at 00428630
and its 15-function genuine graph. The sweep is the sole public linker root;
there is no synthetic caller, inline assembly, register annotation, instruction
patch, masked comparison or selected candidate.

The hit-test naturally receives player in ECX and point in EAX. It remains
203 / 202 bytes with 144 unequal overlapping bytes and seven instruction
groups. The corrected sweep is 1171 / 1170 bytes with 1012 unequal overlapping
bytes and 61 groups. Its 64-byte frame now matches retail; the first raw
difference is 00428647, the total's stack slot. Function extents come from native linker contributions;
complete bodies are compared, including short or long candidates.

Nine collaborators match after address-only rebinding. That diagnostic result
does not constitute a normal fixed-address proof or new recovery credit. The
retail assembly remains selected for both target regions.

The bounded suite executes the entire sweep and hit-test, interval test,
lookup/removal, stop, validation, indicator allocation, primary creation,
registration, allocation and object/script/entity initialization. Successful
operator new, VM execution and descriptor filters are scripted. Heap fallback
executes the already-recovered retail constructor in both runs. Allocation
failure, arbitrary VM effects and complete game integration are untested.
The optional null result receiver is intentional target-specific MSVC 7.1
behavior, exercised at the public sweep boundary.

The current 1837 comparisons include NaNs, descriptor mutation, distinct clocks,
first/last records and regions, animation children, occupied allocation slots,
loading scripts, score overflow, null/stale-pointer faults and division faults.
Sixty edge cases exercise x87 controls 037F, 027F and 007F. Fifteen newly added
cases exposed retained-precision pickup-edge failures in the earlier candidate;
all are fixed by the three observed binary32 stores. Maximum Y remains extended.
Another 480 comparisons cover subnormal dimensions and 84 preserve arbitrary
angle bits, including signaling NaNs, across creation with and without script
loading. MarkForRemoval's object-or-null return is tested independently.

The saved animation field is the float Z rotation at +2C, copied by integer
instructions in the measured body. The fields at +14/+18 are intrusive child
next/previous links. Four real three-float geometry objects account for retail's
frame; the pickup maximum is reused for the rotated region point, as observed
in retail. Twenty-three complete source controls and read-only register/stack
allocation traces are archived. None earns selection or byte credit.

From the repository root:

```sh
python3 matching2/reference/semantic_candidates/player_hit_pickup_004059f0/measure.py retained_corner_graph
python3 matching2/reference/semantic_candidates/player_hit_pickup_004059f0/differential.py retained_corner_graph
```

The measurement uses project compiler flags, `/GL`, `/LTCG`, a DLL with
`/NOENTRY`, and two image bases. Executed images retain their original native
addresses. Address-rebound diagnostic copies are never executed or selected.
Inputs, commands, full PE/maps, complete native/retail bodies and observations
are archived under `evidence/`. The receipt hashes the maintained inputs and
all archived evidence. See the [frame and type note](../../recovery_notes/player_pickup_frame_00428630_2026_10_06.md)
and the [genuine graph note](../../recovery_notes/player_hit_pickup_genuine_2026_10_06.md).
