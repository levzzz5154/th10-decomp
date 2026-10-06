# Genuine player-state collision graph at 0x00425730

The complete player-state owner now calls readable, complete C++ collision
check, record activation, playfield bounds, offset animation creation and script
loading functions. These five functions extend the previous genuine graph from
28 to 33 functions; its five actual roots are unchanged. The real owner and
collision loop derive activation's retail ESI receiver without a synthetic
caller, register annotations, compiler modification or instruction patches.

The complete 199-byte activation body passes the unchanged normal fixed-address
probe. Its raw SHA-256 is
`104d9d3111629b8e843a524b4be11b5d826e0b6c5e10cd08b773d07e30f9f89f`.
The fixed graph has 23 raw-exact complete functions / 2,629 bytes. Address-only
diagnostic rebinding finds 26 exact functions / 3,021 bytes. These are different
checks: three diagnostic matches still use different pooled-literal addresses
in the fixed graph.

The full player-state owner measures 3,060/3,112 bytes, including a complete
20-byte switch table. It has 2,852 differing overlapping bytes in 124 instruction
groups. Its previous extent was 3,024 with 136 groups; the other 27 prior
complete diagnostic bodies are unchanged. The owner remains unselected.

All 5,510 bounded comparisons pass: 1,965 pickup/helper, 215 effect, 328 shared
sequences, 186 scheduled creation, 312 sequence update, 947 full owner and 1,557
new collision cases. The collision suite executes all five added functions,
including first/last records and all 2,000 records, state and countdown gates,
circle and playfield boundaries, unordered coordinates, timer initialization,
loaded/empty/loading scripts, pool/heap allocation, three x87 precision controls
and repeated real-owner updates. Complete collision and activation bodies also
run directly under their observed private entry conventions in the emulator;
these tests add no compiler caller or root.

Item spawning, animation VM effects, successful operator new and bottom player
collaborators remain explicit scripted boundaries. Retail constructor and CRT
math execute in both runs. This evidence establishes bounded behavior under
those collaborators, not full game integration or raw equivalence of the
unmatched functions. A read-only compiler trace preserves all 33 bodies and
the complete 9,728-byte code section.

Production is unchanged. Activation was already selected C++ in a separate
compiler context, so this new genuine-context proof earns zero recovered bytes.
The verified production executable still equals retail; 59 assembly regions /
89,043 bytes remain.

Reproduce from the repository root:

```sh
python matching2/reference/semantic_candidates/player_collision_state_00425730/audit_receipt.py
python matching2/reference/semantic_candidates/player_collision_state_00425730/measure.py genuine_graph --fresh
python matching2/reference/semantic_candidates/player_collision_state_00425730/collision_differential.py genuine_graph
python matching2/reference/semantic_candidates/player_collision_state_00425730/player_differential.py genuine_graph
python matching2/reference/semantic_candidates/player_collision_state_00425730/differential.py genuine_graph
python matching2/reference/semantic_candidates/player_collision_state_00425730/effect_differential.py --candidate matching2/build/experiments/player_collision_state_2026_10_06/genuine_graph/model.exe --output matching2/build/experiments/player_collision_state_2026_10_06/genuine_graph/effect_differential.json
python matching2/reference/semantic_candidates/player_collision_state_00425730/sequence_differential.py genuine_graph
python matching2/reference/semantic_candidates/player_collision_state_00425730/spawn_differential.py genuine_graph
python matching2/reference/semantic_candidates/player_collision_state_00425730/schedule_differential.py genuine_graph
python matching2/reference/semantic_candidates/player_collision_state_00425730/prepare_fixed_probe.py genuine_graph
python -m matching2.tools.matching.probe --project matching2/build/experiments/player_collision_state_2026_10_06/activation_fixed_gate/project --source graph/collision_activate.cpp --output matching2/build/experiments/player_collision_state_2026_10_06/activation_fixed_gate/probe --oracle matching2/build/oracle/th10.exe --json
```

See the [recovery note](../../recovery_notes/player_collision_state_00425730_2026_10_06.md)
for whole-function controls and the remaining ABI differences.
