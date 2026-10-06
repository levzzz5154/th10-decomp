# Complete item-update candidate

`update.cpp` reconstructs the complete 2,198-slot update at `0x0041AFD0` in
ordinary C++, with all collection cases and the genuine helper/caller graph.
Its 2,232-byte native contribution is **unselected**: retail is 2,320 bytes.
The complete update passes 473 bounded retail/native execution comparisons,
including 120 cases that distinguish intermediate float rounding and 12
screen-limit cases that distinguish stored floats from retained x87 results.

The 32-function graph also supplies production's complete, raw-exact
`ConvertItems` (165 bytes), `AddPower` (166 bytes) and `AddLives` (141 bytes).
Those regions were already recovered; their proof now uses the genuine full
update, animation and sound graph. The former synthetic life-counter caller
is no longer selected. No recovered-byte credit is added. With the real entity
initializer visible, item spawn is 823 native / 819 retail bytes and remains
unselected. The preceding graph's two-byte spawn residue is archived.

From the repository root:

```sh
python3 matching2/reference/semantic_candidates/item_update_0041afd0/measure.py saved_collection_graph
python3 matching2/reference/semantic_candidates/item_update_0041afd0/differential.py saved_collection_graph
python3 matching2/reference/semantic_candidates/item_update_0041afd0/fixed_collection_gate.py
python3 matching2/reference/semantic_candidates/item_update_0041afd0/fixed_collection_gate.py --allocator
make
make EXACT=1
python3 matching2/reference/semantic_candidates/item_update_0041afd0/audit_production.py
```

The diagnostic runner links two bases and normalizes addresses for comparison.
The separate collection gate uses the unchanged production fixed-address
validator and checks all three complete selected bodies against retail.
Neither runner builds using reference instruction bytes. The execution fixture
executes actual banner creation/initialization, list lookup/removal, life icons,
sound queuing and the complete entity initializer. It covers ring wraparound,
heap fallback and valid item scripts. Successful operator new, VM callbacks,
power-change and terminal conversion remain scripted. The constructor executes
retail's already-recovered body in both runs; this is bounded evidence.
The optional allocator gate proves all 161 bytes independently; production
retains the genuine player-initialization owner.

See [the recovery note](../../recovery_notes/item_update_genuine_graph_0041afd0_2026_10_06.md)
for field corrections, the preserved rounding failure, scope and production
ownership, and the [precision follow-up](../../recovery_notes/item_update_precision_0041afd0_2026_10_06.md)
for the subsequent Y correction and rejected native controls. `receipt.json`
hashes the maintained sources, evidence and compiler context; `evidence/`
retains the full diagnostic reports and production proof. `evidence/initial_graph/`
is the historical 2,448-byte checkpoint, whose 238-case fixture did not expose
the falling Y error. Its source, reports and production compiler inputs are
preserved independently.

The [initializer follow-up](../../recovery_notes/item_update_initializer_0041afd0_2026_10_06.md)
records the preceding initializer checkpoint. The [motion follow-up](../../recovery_notes/item_update_motion_0041afd0_2026_10_06.md) records the current typed motion graph and proofs. `evidence/collaborator_graph/` preserves
the preceding 2,428-byte / 405-case graph and its actual production inputs.
The [collaborator follow-up](../../recovery_notes/item_update_collaborators_0041afd0_2026_10_06.md)
records that historical checkpoint. `evidence/precision_graph/`
preserves the preceding 2,452-byte / 370-case checkpoint and the retired
production graphs, including the historical synthetic counter caller.

`evidence/initializer_graph/` preserves the preceding 2,436-byte graph,
receipt and production inputs. Thirteen complete motion/rectangle/stage-caller
controls, each passing all 473 item comparisons, are under
`evidence/motion_precision_controls/`; their ledger separates source/code
measurements from execution evidence. The complete update remains unselected.
