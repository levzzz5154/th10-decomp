# 0041E260 complete registrar lifetimes: terminal four-byte residual

No routine is promoted. The canonical complete E260 source still emits the
original 609-byte extent with four differences in its normal selected gate.
The new work establishes that complete registrar and creator source boundaries
alone do not change this counter register assignment. Explicit old-counter
retention changes the counter home to the retail ECX but changes the instruction
sequence and extent; the local-update refinement loses the tested copy.

The isolated scratch is
`matching2/build/experiments/item_e260_registrar_lifetimes_2026_09_28`.
Canonical `attempt02.json` is the whole original 609 normal gate;
`attempt02_measurement.json` and `attempt02_complete/` are read-only complete
contribution diagnostics. `terminal_summary.json`, `terminal_input_hashes.json`,
and `terminal_inputs/` freeze all 14 canonical native compiler inputs.
`attempt02_full_creator_source.cpp` preserves the canonical selected source.
All prior artifacts listed by `preserved_prior_state.json` retained their
hashes, and maintained sources, manifests, and tools were not edited.

| Model | E260 actual / original | Normal result | Complete diagnostic |
| --- | ---: | --- | --- |
| Frozen prior counter-subrecord baseline | 609 / 609 | 4 differing bytes, first 0041E3A9; failures[] | Native body 3e2329… |
| attempt01 complete inline registrar with unused real output | 609 / 609 | 4 differing bytes, first 0041E3A9; failures[] | Same native body |
| attempt02 full offset creator plus full inline registrar | 609 / 609 | 4 differing bytes, first 0041E3A9; failures[] | Same native body; canonical |
| attempt03 retained old counter, old+1 / old+2 stores | 611 / 609 | Rejects image/entry placement; no normal region comparison | 266 overlap differences, first 0041E286 |
| attempt04 local counter increment and tested-copy correction | 608 / 609 | Rejects original 609 extent outside MAP CODE contribution; no normal region comparison | 268 overlap differences, first 0041E2E7 |

The canonical complete unselected allocator remains 819/819, 736 differing bytes,
first 0041BB0E, and the complete F400 bounded sweep remains 623/623 exact at its
retail address. These are entire contribution diagnostics in this single-root
E260 experiment; F400's earlier independent normal exact gate is preserved.
Attempt03 pushes F400's actual address to 0041F410 and changes one relative-call
byte; it does not retain an exact F400 closure and is rejected. Attempt04 keeps
F400623 exact and allocator819 unchanged but its E260 extent fails the gate.
Neither rejected model supplies recovered coverage or a byte-match claim.

All canonical normal checks use the original 609 bytes, without masks or extent
changes. The normal report has zero instruction-byte changes, zero
address-operand changes, zero masked bytes, and
`reference_bytes_used_for_build: false`. Its root remains the public ECX E260
receiver, one stack flag, RET4, integer count in EAX. Full unselected dependencies
keep accurate emitted extents: configure204, loader203, outlined registrar114,
positioned creator111, allocate165, line-polar30, allocator819, and F400623.
No assembly, forced registers, byte patches, or shortened helper was added.

Fresh live Ghidra records are `fresh_program_info.json`,
`fresh_e260_disassembly.json`, `fresh_e260_decompile.json`,
`fresh_registrar_disassembly.json`, `fresh_registrar_decompile.json`,
`fresh_creator_disassembly.json`, and `fresh_creator_decompile.json`. They
identify th10.exe from `/home/levzzz/Games/TH10 - Mountain of Faith/th10.exe`
through the active 2136235 Ghidra instance. The read-only supporting analysis is
`analysis/registrar_lifetimes.md`.

The frozen older dependency is a complete **noinline** registrar model, rather
than an inline counter model. It emits114 bytes while retail4489D0..448A45 is118
bytes; no exact recovery is asserted for it. It caches the successor once. Both
retail4489D0 and E260 instead reload `tail->next` after storing `node->next`.
The new full typed inline registrar preserves those two source reads, all list
links, new-tail publication, counter zero correction, entity handle stamp,
second counter reload into the real output slot, and returned output pointer.
Its caller uses a genuine unused local output; ordinary inlining removes its
dead output store and return. No live or volatile output was introduced to force
register pressure. Its `__forceinline` body is complete, unlike the previous
counter-only `Advance()` helper.

Fresh 448DB0..448E25 contains Allocate, flags, render bucket, offset position
writes, script loading, full outlined registration, and returned output. The
new complete inline creator contains all of these operations and calls the new
full inline registrar. Both attempt01 and attempt02 preserve the recovered
count/resource/script schedule, float position view, unordered comparisons,
actual floating zero addition, optional item spawn, progress, retirement, and
count return. Their source topology is a measured model of the real complete
operations, not proof of the original source boundaries.

Canonical E260 still loads/increments/stores the counter in EDX at0041E3A8,
copies it into EAX for the zero test, and reloads the final memory counter for
the entity. Retail performs the same sequence with ECX instead of EDX. The
four differing encodings are0041E3A9,0041E3AE,0041E3B0,0041E3B4. Their identical
body across the counter-only baseline and both complete helper topologies shows
that simply exposing those complete boundaries does not alter the final
allocation in this compiler context.

Attempt03 supplies new lifetime evidence. The old counter survives through the
zero arm and is placed in ECX, while EAX receives `LEA [ECX+1]`; the zero arm
uses `ADD ECX,2`. That requires 611 bytes and displaces later anchors. It confirms
that ECX is available to a genuine counter value but does not reproduce retail's
incremented-counter/tested-copy intervals. Attempt04 reads a local working
counter, increments and publishes it, then uses its copied value for handle+1
correction. C2 folds this into `INC EAX`, a flags branch, and immediate1 store,
removing the distinct tested copy and producing 608 bytes.

The next action should investigate the real surviving counter-result and
alias/output dependencies that preserve retail's separate incremented value
and tested copy. One remaining concrete topology is a **shared complete**
registrar implementation used by both the genuine full outlined4489D0 anchor
and the E260 inline path. These trials used a separate complete inline model
alongside the retained outlined model. A shared implementation must retain all
outlined output effects, use its actual newly emitted extent, and revalidate
the entire F400623 closure; it must not be replaced with a register stub. Merely
varying source scopes, splitting helper boundaries, or keeping a fictitious
output live is not supported by these measurements. Any future exact handoff
must use unique E260 cluster, context, and headers so that the maintained F400
closure is not overwritten.

Canonical selected source SHA-256:
`6518e9f818538ab20cd853e0c59bf0d48ce307c631d3f0cbb1fb4a4f6809b0fc`.
Canonical E260 body SHA-256:
`3e2329f7941f10e0a05c6b4455004ca9ab90242f12e522752f16c4305bbdd502`.
Retail E260 body SHA-256:
`0f407d65898d373dc40df48afc5f748b24a84dc543e9d14df6bd21cbaec02745`.
Retained complete F400 body SHA-256:
`f064ada0633637ffbd6631367e900d6d1415569100052bf52bae824735db874f`.
Retained complete allocator body SHA-256:
`6393e9877e1387e611de9fd74e1e64491346bc64f4bc5c9cb8b52a08faee4d59`.
