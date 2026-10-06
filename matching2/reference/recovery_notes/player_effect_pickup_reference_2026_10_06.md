# Shared recovered animation reference interface

The genuine effect/pickup graph now uses the recovered four-byte `AnimationRef`
for registration results, creation results and every lookup/removal argument.
The separate `PickupAnimationId` record and `AnimationId` alias are removed.
Handle storage remains a volatile word, while a lookup takes an ordinary value
snapshot. This distinguishes the actual stored word from the API value without
inventing a second reference type.

The class is the existing recovered interface in
`msvc/include/th10/game/player_hud_animations.hpp`: an unsigned word, its ordinary
constructor, increment and equality operations. Its implicit copy remains
trivial. A size check establishes the complete four-byte argument. The local
rendering declarations share the same class definition with the actual creator
and registrar. Removal and the late secondary lookup construct this reference
directly at their actual calls; they do not need extra named ID variables.
No ABI wrapper, register prescription, fake caller or added computation is used.

All 20 complete native bodies and all 20 complete rebound diagnostic bodies are
identical to the prior public-initializer checkpoint. Seventeen supporting
bodies, totaling 1884 bytes, remain diagnostic-exact. Effect update remains
874/876 bytes, hit-test 203/202 and pickup sweep 1171/1170. The remaining effect
differences are unchanged: the culling ID load/push uses EAX instead of ECX,
the primary Z copy uses ECX instead of EAX, and the late secondary argument
omits retail's EAX-to-ECX copy. The unified reference constructor alone does not
explain those three allocation/lowering decisions.

Four complete graph controls are archived: sharing the reference type; direct
construction of both remaining call arguments; retaining a typed secondary
snapshot across the test; and using the reference class for the object's ID
comparison. All retain 17 diagnostic-exact supporting bodies. The typed
secondary snapshot adds an x87 load/add ordering difference at +333 without
closing the ID or Z gaps. These controls were measured, not behavior-validated;
no behavioral claim is attached to them. The retained graph is tested separately.

All 2508 bounded comparisons pass: 1965 pickup/helper cases, 215 effect cases
and 328 sequences. The 48 new direct removal cases exercise IDs 0, 1, 7,
7FFFFFFF, 80000000 and FFFFFFFF, matching/missing IDs, both lookup buckets and
both child-link states. They compare the complete object/list state and the
actual helper result. The zero sentinel rejects a lookup even if a zero ID is
placed in a bucket. High bits survive the complete by-value argument path.
The prior 32 registration wraparound and 48 direct initializer cases remain.
Sequence observations are unchanged and invoke each real caller 410 times.
Successful allocation, descriptor callbacks and VM effects retain their
specified scripted boundaries; arbitrary VM and full-game behavior are untested.

The production initializer context uses the same interface. A fresh normal
fixed-address probe passes all 217 selected bytes with the genuine graph.
Sixteen complete contributions match raw bytes in that image; the other helper
uses native pooled literals and the three main owners still differ. Only the
already selected initializer is exported. No new function or byte is credited.

The prior [genuine initializer proof](animation_resource_initialize_object_genuine_2026_10_06.md)
and its source/evidence snapshots remain historical evidence. The new probe is
`build/experiments/initialize_object_genuine_reference_2026_10_06/production_probe/clusters/animation_resource_initialize_object_00449870/report.json`.
The candidate's receipt checks current inputs, archived control snapshots,
all complete body comparisons, unchanged native bodies, observations, the
selected initializer proof and the full production audit.

The current complete fixed-address graph also has a fresh read-only global
allocation trace. It records 39 events and 29 allocation choices using hardware
breakpoints, with no compiler-data writes or forced choices. The replay preserves
all 20 complete bodies and the entire emitted code section.
The direct culling constructor's anonymous candidate 19 has priority 32 and takes
EAX; the named late secondary snapshot, candidate 20, has priority 56 and takes
EAX. The earlier primary/secondary lookup snapshots take ECX. Thus eliminating
the named culling ID does not prevent its promotion into a global candidate.
That result narrows the next investigation to the lowered argument and value
lifetimes, rather than duplicating the now-rejected ID declaration spellings.
The full trace, input object fingerprints, source/tool identities, tuple data,
PE/MAP and complete-body verification are archived with the normal proof.
