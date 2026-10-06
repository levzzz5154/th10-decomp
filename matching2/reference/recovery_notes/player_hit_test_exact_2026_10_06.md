# Complete player hit-test recovery, 2026-10-06

The complete 202-byte function at 004059F0 is now ordinary C++ in
`msvc/src/game/player_hit_test_004059f0.cpp`. The normal fixed-address native
LTCG gate compares all 202 bytes without masks, instruction patches, address
rewrites or reference instructions in the compiler inputs. Its raw SHA-256 is
`65a18b997df4b896439672bbdf9abfbd2fb64cf29af75d0cd86c7d0b78f66ece`.
The maintained assembly body is removed. New recovery credit is 202 bytes.

The successful change is the second condition in the direct-hit arm:

```cpp
if (mode == 0 && (data_004776f4->flags & 1)) result = 3;
else if (data_004776f4->flags & 1) result = 38;
else result = data_00477704->alternate_mode ? 38 : 5;
```

The former second arm repeated `mode != 0`. With no intervening writes or
calls, reaching this arm with the focus flag set establishes that the first
mode comparison failed. Removing that redundant condition preserves behavior.
The ordinary source now produces retail's single mode test, byte flag load and
separate hit/miss game-pointer loads. It also retains the actual private ABI:
player in ECX, point in EAX, no stack arguments or cleanup. No declaration
prescribes those registers.

The complete genuine graph contains twenty functions across two translation
units. The real effect callback, pickup sweep and public object initializer
are its three entry roots. The hit-test is reached from the genuine sweep;
it is not declared an independent public root. The selected hit-test source
also compiles its real sweep, effect and shared helper context. The duplicated
context-only `runtime.cpp` and `hit.cpp` are removed from the production layout.
The existing initializer manifest now selects both complete exact functions.
Seventeen genuine ABI anchors and the complete 874-byte effect callback remain
unselected. The next layout gap grows by one zero byte because the hit-test's
complete native contribution decreases from 203 to 202 bytes.

The normal production probe passes the hit-test and existing 217-byte object
initializer. All other nineteen diagnostic/native contributions equal the
previous shared-reference checkpoint. Eighteen full functions totaling 2086
bytes match after diagnostic address rebinding; seventeen match raw bytes in
the fixed-address image. Motion still uses native pooled literal addresses.
Only the hit-test and initializer are exported. The effect update and pickup
sweep remain assembly-owned and have no new recovery credit.

Fourteen new complete graph controls are archived in the shared candidate's
`evidence/layout_controls` ledger. Three examine the recovered lookup receiver
and explicit context contract. Six examine flag storage, flag snapshots,
pointer volatility and branch order. Four split the hit arm by mode. The last
removes the redundant second mode predicate and is the successful control.
The preceding thirteen are measurement-only; no behavioral claim or production
selection is attached to them. Both the successful control and the maintained
graph pass 1965 pickup/helper, 215 effect and 328 sequence cases: 2508 total.
Each real caller executes 410 times in the sequence cases. The existing
successful-allocation, VM and descriptor callback boundaries are scripted;
these bounded comparisons do not establish arbitrary VM or complete-game
behavior.

Seven fresh compiler traces use hardware breakpoints and complete normally.
Every trace preserves all twenty complete native bodies and its whole emitted
code section. Before the source correction, the mode load at +44 is anonymous
global candidate 10, priority 22, assigned ECX. The game pointer remains loaded
twice at Riscify and at both late-flow entries, then collapses during the
common-head-merge stage. A hit-only flag snapshot does not prevent that merge.
In the exact source's global-allocation trace, the mode expression has no
anonymous global allocation candidate. The receiver has priority 44 and takes
ECX; the result has priority 40 and takes EDX. The compiler derives the matching
temporary sequence without an artificial lifetime or forced allocation.

Early and late analysis tracers now preserve the first recorded native LTCG
image base when no fixed-address link is present. Their fixed-address behavior
is unchanged. The late tracer's optional `head` mode observes common-head merge
entries. These analysis changes do not modify the matching gate. The verifier
checks all complete bodies, emitted code sections, compiler/source/object
fingerprints and trace completion. The PE/MAP, executable trace scripts,
tuple/allocation events, verification records and analysis tool snapshots are
archived. The six earlier traces remain historical evidence for the rejected
203-byte source; the seventh traces the exact fixed-address source.

Both `make` and `make EXACT=1` pass. The exact executable has all 487936 retail
bytes and SHA-256
`2f14760b6fbbf57549541583283badb9a19a4222b90f0a146d5aa17f01dc9040`.
The production audit validates 963 native layouts, 1484 selected functions and
3997 distinct compiler inputs. Ordinary exact C++ now owns 2255 regions and
199264 bytes. The 59 actual assembly regions total 89043 bytes; eight equivalent
C++ owners still need byte-exact recovery. The overall decompilation remains
incomplete.

The current complete proof is
`build/experiments/player_hit_test_exact_2026_10_06/production_probe/clusters/animation_resource_initialize_object_00449870/report.json`.
The maintained candidate's receipt checks its current inputs, complete body
measurements, archived control inputs, observation digests, all seven traces,
the historical initializer proof and the fresh two-function production proof.
Evidence is in `reference/semantic_candidates/player_effect_pickup_00428280/evidence/`.
