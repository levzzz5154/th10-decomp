# Non-semantic ledger handoff

Historical snapshot: the ledger counts and manifest hashes below predate the
current worktree. Use `make progress` and `msvc/regions.json` for current
accounting; [the eighth 2026-09-28 recovery checkpoint](recovery_notes/native_recoveries_2026-09-28_eighth.md)
records the latest verified conversions.

Refreshed 2026-09-17 from the current manifest. The 2026-09-15 continuation
task is complete: both ledger snapshots were re-derived and the four regions
the 2026-09-15 measurement flagged as semantic-with-naked-assembly
(`0x00407560`, `0x004127A0`, `0x00418D40`, `0x0042ACB0`) are back to their
`previous_record` asm classification. No C++ definition exists for them; the
recovery notes record the measured residuals
(`spell_timer_advance_slots_004127a0_model.md`,
`stage_tip_manager_construct_00418d40_model.md`). They remain semantic
*candidates*, not irreducible assembly.

## Authoritative checkpoint

- Manifest: `matching2/msvc/regions.json`
- Manifest SHA-256: `24b7a0ab98c689ed0be2b569ed2367a538b40a2b421c35ae1bb44a980d45b215`
- Whole executable: exact across 487,936 bytes
- Semantic C++: 475 regions / 33,257 bytes
- Assembly: 2,110 regions / 355,771 bytes
- Embedded `.text` data: 24 regions / 8,114 bytes
- Padding: 1816 regions / 15,530 bytes
- Total non-semantic: 3,950 regions / 379,415 bytes

`non_semantic_regions.json` and `non_semantic_regions.md` describe this
manifest unless a later promotion says otherwise.

## 2026-09-17 progress

Eight small EAX-entry regions joined the semantic C++ pool as native-LTCG
clusters, each verified EXACT by the per-unit probe and by the whole-image
build:

| region | bytes | cluster |
|---|---:|---|
| `0x0040CDC0` | 23 | `enemy_slot_conditional_set_0040cdc0` (object in EAX, value on stack, `RET 4`) |
| `0x00418AC0` | 15 | `state_reset_pair_00418ac0` |
| `0x00421D00` | 21 | `replay_marker_clear_00421d00` |
| `0x0043A490` | 14 | `sound_pair_clear_0043a490` |
| `0x0044C620` | 14 | `camera_pair_reset_0044c620` |
| `0x00421DE0` | 11 | `replay_slot_clear_a_00421de0` |
| `0x00421DF0` | 11 | `replay_slot_clear_b_00421df0` |
| `0x004367E0` | 11 | `resource_slot_init_004367e0` (value in ECX) |

The earlier in-progress clusters at `0x0040CDE0`, `0x00412E00`, `0x0042A810`
and `0x004356C0` were probed EXACT and stand. See
`recovery_notes/enemy_state_cluster_followup_0040cdc0_0044c620.md` for the
cluster-recipe notes (context decoration, `noinline`, gap arithmetic).

`oriented_rect_hit_test_0041e4d0_model.md` was extended with a six-variant
sweep; the retained model (207/226) still wins and the region stays assembly.
