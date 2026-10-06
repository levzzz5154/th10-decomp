# Genuine animation initializer caller graph

The already selected 217-byte object initializer at `0x00449870` now compiles
under its complete genuine effect/pickup graph. The former 60-byte synthetic
array loop and its private loader copy have been removed from the production
layout. The original files are preserved as historical evidence. No new region
or byte is credited by this context replacement.

The graph maintains 20 complete real functions across two translation units,
including the collision sweep, effect update, creator, registrar, allocator,
object/entity initialization and preserving script loader. Its three real
entries are the effect callback, pickup sweep and public object initializer.
The initializer's public contract is resource ECX, object/index on the stack,
RET 8. Existing recovered callers and its prior complete proof establish this
contract. Rooting that real entry prevents LTCG from specializing it into the
private object-EDX, RET 4 form. No synthetic caller, register annotation,
artificial work, instruction patch or comparison mask supplies the contract.

That change also restores the complete 73-byte creator's normal argument push,
flags scratch and store ordering. The diagnostic native graph now matches all
17 supporting functions, 1884 bytes, after address rebinding. Hit-test remains
203/202 bytes, sweep 1171/1170 and effect update 874/876; those three owners
remain assembly. Diagnostic address rebinding is only a comparison operation;
execution uses the untouched native images.

The production manifest uses the actual effect callback as its context and the
actual sweep as an independently retained anchor. Every contribution is placed
at its genuine retail address with its complete compiler-produced extent.
The selected initializer matches all 217 raw bytes, including its relative
loader call, SHA-256
`c4be92e1096f74b7be92e5fe32adee65afee5fa061b3775559c574a83ecc5267`.
Only that initializer is exported to the production object. Other recovered
functions retain their existing owners. The context and anchors receive no
selection credit. Sixteen complete bodies match raw bytes in this proof image;
the unselected Motion body uses native pooled float addresses. The diagnostic
17-body result must not be confused with production selection of this graph.

Native proof is at
`matching2/build/experiments/initialize_object_genuine_2026_10_06/production_probe/clusters/animation_resource_initialize_object_00449870/report.json`.
The fixed-address comparison records all 20 complete contributions, including
the three unresolved owners and Motion's native pool references. The cluster
uses the unchanged normal compiler/linker profile and matching gate.

The shared candidate passes 2460 bounded retail/native comparisons: 1917
pickup/helper checks, 215 effect checks and 328 sequences. The 48 new checks
call the public initializer directly with flags 0, 500, 40000000 and FFFFFFFF;
script indices 1, 17 and 63; loaded/unloaded scripts; and loading states 0/1.
Both caller suites also execute their complete real creation chains. Sequence
observations remain unchanged, with 410 invocations of each owner. Successful
allocation, descriptor callbacks and VM effects remain scripted boundaries;
these checks do not establish arbitrary VM or full-game behavior.

The source/header copies under
`msvc/layout/ltcg/animation_initialize_runtime/` adapt only include paths and
section names from the genuine candidate. They retain the complete function
bodies. The selected initializer is included from its maintained source file,
with the same real public declaration shared by its actual creator. The old
synthetic driver is archived in the candidate evidence rather than compiled.

Replay the normal selection proof:

```sh
python3 matching2/tools/matching/probe.py --source src/render/animation_resource_initialize_object_00449870.cpp --output matching2/build/experiments/animation_initialize_genuine_replay
```

The [shared reference follow-up](player_effect_pickup_reference_2026_10_06.md) removes the duplicate lookup ID type, preserves all 20 complete native bodies and passes 2508 bounded comparisons, including 48 direct zero/high-bit ID checks. It also refreshes the normal initializer proof under the updated shared interface. The prior checkpoint above remains archived.
