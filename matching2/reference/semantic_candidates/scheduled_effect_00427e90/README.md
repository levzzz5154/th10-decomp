# Scheduled effect creation at 0x00427e90

Readable ordinary C++ for the complete 717-byte scheduled effect creator,
co-compiled with 27 genuine functions. The retained creator is 717 bytes with
61 differing bytes in nine instruction groups after address-only rebinding.
The first 457 diagnostic bytes agree. It remains assembly-owned in production;
this candidate earns zero new recovered bytes.

The graph extends the shared [hit-test/effect/pickup graph](../player_effect_pickup_00428280/)
with the actual sequence update, schedule walker, sound queue and timer helpers.
All 20 previous diagnostic bodies are unchanged. Twenty-three full functions, totaling 2,557 bytes, are
diagnostic-exact, including the 149-byte sound queue. This is diagnostic
comparison, not a new fixed-address raw-equality selection gate.

The common player layout now describes the actual spawn origin, four familiar
positions and 0x34-byte schedule descriptors. Creation preserves the pool
search, timer stores, integer-to-world position conversion, motion update,
pre-allocation resource/script reads, primary and optional secondary animation
creation, rotation flag, initialization callback and sound request.

The complete 105-byte schedule walker now naturally has retail's private
EDI/EBX convention through the real sequence Update caller. The 57-byte
scheduler store, 72-byte timer tick and 88-byte timer advance also match
under diagnostic rebinding. Update has the complete 174-byte extent and one
receiver-register byte difference: its ordinary public member root takes ECX,
while retail receives EAX from its outer caller. No entry bytes are patched,
and the entire chain is executed using each actual entry convention.

Run from the repository root:

```sh
python matching2/reference/semantic_candidates/scheduled_effect_00427e90/audit_receipt.py
python matching2/reference/semantic_candidates/scheduled_effect_00427e90/measure.py sequence_graph --fresh
python matching2/reference/semantic_candidates/scheduled_effect_00427e90/differential.py sequence_graph
python matching2/reference/semantic_candidates/scheduled_effect_00427e90/effect_differential.py --candidate matching2/build/experiments/scheduled_effect_2026_10_06/sequence_graph/model.exe --output matching2/build/experiments/scheduled_effect_2026_10_06/sequence_graph/effect_differential.json
python matching2/reference/semantic_candidates/scheduled_effect_00427e90/sequence_differential.py sequence_graph
python matching2/reference/semantic_candidates/scheduled_effect_00427e90/spawn_differential.py sequence_graph
python matching2/reference/semantic_candidates/scheduled_effect_00427e90/schedule_differential.py sequence_graph
```

All 3,006 bounded cases pass: 1,965 pickup/helper cases, 215 effect-update
cases, 328 shared effect/pickup sequences, 186 new spawn cases and 312
sequence-update cases. The spawn
suite compares whole player, animation manager, allocated object and sound
queue state, call order/results, callback argument ABI, preserved registers,
RET12 cleanup, x87 balance and control word. It exercises ordinals 0–4,
type-3 suppression, the first/last/full pool, first-use timers, both motion
modes, callbacks, animation resources and ID wrap, three precision controls,
rotation, repeated creation, follow-up effect/pickup updates and sound queue
reuse/full capacity. The sequence suite covers rank saturation/alternate tables,
changed and unchanged frames, inactive states, wrapping/stopping, first-use
clocks, fractional speed and follow-up effect/pickup updates.

Successful allocation, VM effects and descriptor callbacks are scripted at
explicit boundaries. The retail constructor, polar/angle routines and CRT
math execute in both runs. No instructions are patched. Passing cases do not
prove all possible inputs or establish retail's EAX convention for the rooted
Update body.

The sealed evidence includes 16 complete graph measurements, four additional
effect-owner controls (two rejected for missing complete helper symbols),
fresh retained input snapshots, native PE/MAP/object files, complete diagnostic
bodies, cases and observations. Three read-only compiler traces preserve every
complete native body and emitted code byte in their respective 23- and 27-function graphs. See the
[recovery note](../../recovery_notes/scheduled_effect_native_00427e90_2026_10_06.md)
for the remaining differences and trace findings.
