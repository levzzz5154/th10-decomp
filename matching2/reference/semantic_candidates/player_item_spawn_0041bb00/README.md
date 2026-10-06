# Genuine player-state, collision and item-spawn graph

The complete item-spawn callee and script-start function extend the previous
33-function graph to 36 complete ordinary C++ functions. Its six real roots
are the five previous player/animation roots and the actual public item-polar
method. No synthetic caller, register annotation or compiler modification is
used. The item manager contains the actual 150-slot normal pool, 2,048-slot
special ring and timer/animation/position fields with checked offsets.

The genuine item-spawn body makes collision check raw-exact for all 260 bytes,
including its private EAX manager / EBX point / three-stack-word / RET12 ABI.
Activation remains raw-exact for all 199 bytes with its ESI receiver. Both
bodies are now selected through this genuine graph in production. They were
already selected C++ in an older compiler context, so this changes their context
and source ownership but adds zero recovered bytes. Their original complete
bodies remain unselected anchors in the six-function legacy player/drop/enemy
cluster; those remaining selected bodies still pass.

The new graph has 27 diagnostic-exact functions / 3,281 bytes and 24 raw-exact
complete functions / 2,889 bytes in its fixed-address image. The full owner
remains 3,060/3,112 bytes, including the 20-byte table. Item spawn measures
823/819 bytes, including its full 23-byte switch material. Script startup is
200/202; script loading 197/203; positioned creation 116/118. These whole
bodies remain unselected. The source now states the loader's actual pointer/null
return contract; all current genuine callers ignore its return, so this source
correction leaves its native bytes unchanged.

All 7,084 bounded comparisons pass, including 1,574 new item cases. The former
947 owner and 1,557 collision cases now execute genuine item spawning too.
The item suite covers normal-pool exhaustion, first/last slots, signed power
thresholds, kind remapping, retiring a prior kind-3 animation, loaded/empty
scripts, special-ring occupancy and count/cursor thresholds, signed remainders,
three x87 precision controls, the real seven-item death fan and repeated calls.
Complete state and relevant memory, external calls, helper invocation counts,
results, register preservation, stack cleanup and x87 balance/control word are
compared. Direct private-entry tests are emulator fixtures, with no compiler
caller or extra root. VM effects, successful allocation and bottom player
collaborators remain explicitly bounded boundaries. The ordinary native polar
method uses separate FCOS/FSIN instructions and is tested over finite gameplay
angles; it is unselected and does not recover the existing FSINCOS leaf.

The full normal and exact production builds pass. The exact executable equals
retail byte for byte. Normal-mode differences stay entirely inside the eight
existing equivalent-recovery regions; all other bytes, including both collision
bodies, equal retail. The current audit verifies 964 layouts, 1,484 selected
functions and 4,030 unique compiler inputs. The remaining actual assembly is
still 59 regions / 89,043 bytes; the full goal remains incomplete.

Reproduce from the repository root:

```sh
python matching2/reference/semantic_candidates/player_item_spawn_0041bb00/audit_receipt.py
python matching2/reference/semantic_candidates/player_item_spawn_0041bb00/measure.py genuine_graph --fresh
python matching2/reference/semantic_candidates/player_item_spawn_0041bb00/item_differential.py genuine_graph
python matching2/reference/semantic_candidates/player_item_spawn_0041bb00/collision_differential.py genuine_graph
python matching2/reference/semantic_candidates/player_item_spawn_0041bb00/player_differential.py genuine_graph
python matching2/reference/semantic_candidates/player_item_spawn_0041bb00/differential.py genuine_graph
python matching2/reference/semantic_candidates/player_item_spawn_0041bb00/effect_differential.py --candidate matching2/build/experiments/player_item_spawn_2026_10_06/genuine_graph/model.exe --output matching2/build/experiments/player_item_spawn_2026_10_06/genuine_graph/effect_differential.json
python matching2/reference/semantic_candidates/player_item_spawn_0041bb00/sequence_differential.py genuine_graph
python matching2/reference/semantic_candidates/player_item_spawn_0041bb00/spawn_differential.py genuine_graph
python matching2/reference/semantic_candidates/player_item_spawn_0041bb00/schedule_differential.py genuine_graph
python -m matching2.tools.matching.probe --project matching2/msvc --source src/game/player_collision_00408030_00408100.cpp --output matching2/build/experiments/player_item_spawn_2026_10_06/production_probe --oracle matching2/build/oracle/th10.exe --json
python -m matching2.tools.matching.build_msvc --verify matching2/build/oracle/th10.exe --jobs 8
python -m matching2.tools.matching.build_msvc --exact --verify matching2/build/oracle/th10.exe --jobs 8
```

The sealed native graph was measured before the production context migration.
Its recorded production-manifest hash is checked against the archived before
snapshot. Current production inputs are checked separately against the fresh
production reports. Historical receipts that require the former live manifest
will correctly reject that changed prerequisite; their source and artifact
hashes remain unchanged.

See the [recovery note](../../recovery_notes/player_item_spawn_genuine_2026_10_06.md)
for residuals, production ownership and evidence details.
