# Recovered-code audit inventory

Capture baseline: `895c4202387d1c6099cf0cec2e8798bdae6a1754`, dated 2026-09-06. File hashes describe the current generated inputs, not an assertion that they still match the baseline.

Scope: **722 coverage addresses**, **551 production/header/standalone files**, and **539 IDA boundary-review candidates** outside coverage. All require review or revalidation. Full occurrence text, reference ranges, hashes, and historical findings are in [inventory.json](inventory.json).

Source annotations and prior review verdicts are separate. Candidate markers are heuristic: several files may be wrappers, references, alternate implementations, or actual competing bodies. The inventory does not choose one owner. File scope includes uncredited helpers and does not infer which files a build uses.

Earlier bounded review: **57 reviewed** within a **708-address** partition scope, with five separate sparse checks. Historical `grounded` means a reported result at that report's stated boundary; it is neither revalidated nor whole-program proof. The bounded report does not specify its original source commit. Report hashes, written dates, scope, and count validation are preserved in JSON.

Generate: `python3 matching2/tools/audit_inventory.py --write`. Verify: `python3 matching2/tools/audit_inventory.py --check`. Test: `python3 matching2/tests/audit_inventory_test.py`. Commands run from the repository root; the script itself also works from other directories. `--check` fails on missing/stale outputs or inconsistent address/report inventories.

## Counts

| Measure | Count |
| --- | ---: |
| coverage_addresses | 722 |
| ghidra_index_addresses | 703 |
| historical_overlay_addresses | 397 |
| file_scope | 551 |
| files_without_candidate_claims | 150 |
| multiple_candidate_claim_addresses | 280 |
| ida_boundary_review_candidates | 539 |
| annotation_counts: partial | 4 |
| annotation_counts: researched | 3 |
| annotation_counts: semantic | 710 |
| annotation_counts: unrecovered | 5 |
| prior_review_counts: outside_prior_bounded_and_sparse_scopes | 9 |
| prior_review_counts: pending_bounded_review | 634 |
| prior_review_counts: reference_unresolved | 17 |
| prior_review_counts: reported_grounded | 28 |
| prior_review_counts: reported_partial | 29 |
| prior_review_counts: separate_sparse_review | 5 |

## Every coverage address

Reference availability does not imply usable or correct decompilation. Source locations below are candidate claims; JSON also retains every incidental address reference. All current audit statuses are pending revalidation.

| Address | Annotation | Prior review | IDA C / ASM / Ghidra | Candidate claim locations |
| --- | --- | --- | --- | --- |
| `0x00401000` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/game_thread.cpp:3](../../../matching2/src/game/game_thread.cpp#L3); [matching2/src/game/game_thread.cpp:146](../../../matching2/src/game/game_thread.cpp#L146); [matching2/src/game/game_thread_overlay.cpp:2](../../../matching2/src/game/game_thread_overlay.cpp#L2) |
| `0x00401110` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/game_thread.cpp:3](../../../matching2/src/game/game_thread.cpp#L3); [matching2/src/game/game_thread.cpp:227](../../../matching2/src/game/game_thread.cpp#L227) |
| `0x00401260` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/game_thread.cpp:3](../../../matching2/src/game/game_thread.cpp#L3); [matching2/src/game/game_thread.cpp:297](../../../matching2/src/game/game_thread.cpp#L297) |
| `0x00401440` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/game_thread.cpp:4](../../../matching2/src/game/game_thread.cpp#L4); [matching2/src/game/game_thread.cpp:367](../../../matching2/src/game/game_thread.cpp#L367) |
| `0x00401520` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/recovery_leaves.cpp:39](../../../matching2/src/game/recovery_leaves.cpp#L39) |
| `0x00401530` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/game_thread_queue.cpp:4](../../../matching2/src/game/game_thread_queue.cpp#L4) |
| `0x00401630` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/game_thread_queue.cpp:49](../../../matching2/src/game/game_thread_queue.cpp#L49) |
| `0x00401690` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/game_thread_queue.cpp:59](../../../matching2/src/game/game_thread_queue.cpp#L59) |
| `0x00401760` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/game_thread.cpp:118](../../../matching2/src/game/game_thread.cpp#L118); [matching2/src/game/game_thread_queue.cpp:71](../../../matching2/src/game/game_thread_queue.cpp#L71); [matching2/include/th10/game/game_thread_queue.hpp:46](../../../matching2/include/th10/game/game_thread_queue.hpp#L46) |
| `0x00401A50` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/game_thread.cpp:124](../../../matching2/src/game/game_thread.cpp#L124); [matching2/src/game/game_thread_text_draw.cpp:6](../../../matching2/src/game/game_thread_text_draw.cpp#L6) |
| `0x00401D20` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/render/render_stage_select.cpp:4](../../../matching2/src/render/render_stage_select.cpp#L4) |
| `0x00401DE0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/entity.cpp:3](../../../matching2/src/game/entity.cpp#L3); [matching2/src/game/entity.cpp:120](../../../matching2/src/game/entity.cpp#L120); [matching2/src/game/manager_factories.cpp:299](../../../matching2/src/game/manager_factories.cpp#L299) |
| `0x00401FF0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/entity.cpp:3](../../../matching2/src/game/entity.cpp#L3); [matching2/src/game/entity.cpp:62](../../../matching2/src/game/entity.cpp#L62) |
| `0x00402050` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/entity.cpp:3](../../../matching2/src/game/entity.cpp#L3); [matching2/src/game/entity.cpp:97](../../../matching2/src/game/entity.cpp#L97) |
| `0x00402160` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/game_state.cpp:3](../../../matching2/src/game/game_state.cpp#L3); [matching2/src/game/game_state.cpp:339](../../../matching2/src/game/game_state.cpp#L339) |
| `0x00402230` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/game_state.cpp:3](../../../matching2/src/game/game_state.cpp#L3); [matching2/src/game/game_state.cpp:392](../../../matching2/src/game/game_state.cpp#L392) |
| `0x00402440` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/game_state.cpp:3](../../../matching2/src/game/game_state.cpp#L3); [matching2/src/game/game_state.cpp:495](../../../matching2/src/game/game_state.cpp#L495) |
| `0x00402640` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/game_state.cpp:4](../../../matching2/src/game/game_state.cpp#L4); [matching2/src/game/game_state.cpp:582](../../../matching2/src/game/game_state.cpp#L582) |
| `0x00402720` | semantic | reported_partial | yes / yes / yes | [matching2/src/game/bullet_manager.cpp:399](../../../matching2/src/game/bullet_manager.cpp#L399); [matching2/src/game/game_state.cpp:81](../../../matching2/src/game/game_state.cpp#L81) |
| `0x00402850` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/game_state.cpp:130](../../../matching2/src/game/game_state.cpp#L130); [matching2/src/game/gameplay_render_pass.cpp:11](../../../matching2/src/game/gameplay_render_pass.cpp#L11); [matching2/include/th10/game/gameplay_render_pass.hpp:55](../../../matching2/include/th10/game/gameplay_render_pass.hpp#L55) |
| `0x00402CA0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/game_state.cpp:212](../../../matching2/src/game/game_state.cpp#L212); [matching2/src/render/composite_passes.cpp:20](../../../matching2/src/render/composite_passes.cpp#L20); [matching2/include/th10/render/composite_passes.hpp:4](../../../matching2/include/th10/render/composite_passes.hpp#L4) |
| `0x00403090` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/render/projection_quads.cpp:97](../../../matching2/src/render/projection_quads.cpp#L97) |
| `0x00403850` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/script/stage_ecl_load.cpp:14](../../../matching2/src/script/stage_ecl_load.cpp#L14) |
| `0x00403990` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/render/anm_script_table_sweep.cpp:12](../../../matching2/src/render/anm_script_table_sweep.cpp#L12) |
| `0x00403A30` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/render/anm_record_walk.cpp:8](../../../matching2/src/render/anm_record_walk.cpp#L8) |
| `0x00403C80` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/event_script_runtime.cpp:105](../../../matching2/src/game/event_script_runtime.cpp#L105) |
| `0x00404450` | semantic | reported_grounded | yes / yes / yes | [matching2/src/game/bullet_manager.cpp:285](../../../matching2/src/game/bullet_manager.cpp#L285) |
| `0x00404530` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/player.cpp:418](../../../matching2/src/game/player.cpp#L418); [matching2/src/game/recovery_leaves.cpp:731](../../../matching2/src/game/recovery_leaves.cpp#L731) |
| `0x004045B0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/player.cpp:37](../../../matching2/src/game/player.cpp#L37); [matching2/src/game/player.cpp:429](../../../matching2/src/game/player.cpp#L429) |
| `0x00404610` | semantic | reported_partial | yes / yes / yes | [matching2/src/game/trajectory_evaluate.cpp:160](../../../matching2/src/game/trajectory_evaluate.cpp#L160); [matching2/src/math/interpolators.cpp:3](../../../matching2/src/math/interpolators.cpp#L3); [matching2/src/math/interpolators.cpp:38](../../../matching2/src/math/interpolators.cpp#L38); [matching2/include/th10/game/trajectory_evaluate.hpp:26](../../../matching2/include/th10/game/trajectory_evaluate.hpp#L26); [matching2/include/th10/math/interpolators.hpp:3](../../../matching2/include/th10/math/interpolators.hpp#L3) |
| `0x004049A0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/math/math_utils.cpp:50](../../../matching2/src/math/math_utils.cpp#L50); [matching2/src/math/param_block_interp.cpp:3](../../../matching2/src/math/param_block_interp.cpp#L3); [matching2/src/math/param_block_interp.cpp:21](../../../matching2/src/math/param_block_interp.cpp#L21) |
| `0x00404D40` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/math/math_utils.cpp:62](../../../matching2/src/math/math_utils.cpp#L62); [matching2/include/th10/math/quantized_vector.hpp:24](../../../matching2/include/th10/math/quantized_vector.hpp#L24) |
| `0x00404DA0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/recovery_leaves.cpp:502](../../../matching2/src/game/recovery_leaves.cpp#L502) |
| `0x00404E10` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/particle_seed.cpp:4](../../../matching2/src/game/particle_seed.cpp#L4); [matching2/include/th10/math/quantized_vector.hpp:33](../../../matching2/include/th10/math/quantized_vector.hpp#L33) |
| `0x00404ED0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/math/timer.cpp:2](../../../matching2/src/math/timer.cpp#L2) |
| `0x00404F30` | semantic | reported_grounded | yes / yes / yes | [matching2/src/game/bullet_manager.cpp:335](../../../matching2/src/game/bullet_manager.cpp#L335) |
| `0x00405040` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/recovery_leaves.cpp:781](../../../matching2/src/game/recovery_leaves.cpp#L781) |
| `0x004050D0` | semantic | reported_partial | yes / yes / yes | [matching2/src/game/effect_indicator_slots.cpp:19](../../../matching2/src/game/effect_indicator_slots.cpp#L19); [matching2/src/game/score_timer_leaves.cpp:8](../../../matching2/src/game/score_timer_leaves.cpp#L8); [matching2/src/math/timer.cpp:81](../../../matching2/src/math/timer.cpp#L81) |
| `0x00405300` | semantic | reported_partial | yes / yes / yes | [matching2/src/game/bullet_manager.cpp:349](../../../matching2/src/game/bullet_manager.cpp#L349) |
| `0x00405410` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/player.cpp:107](../../../matching2/src/game/player.cpp#L107); [matching2/src/script/ecl_vm.cpp:628](../../../matching2/src/script/ecl_vm.cpp#L628) |
| `0x004054B0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/platform/all_source_runtime.cpp:205](../../../matching2/src/platform/all_source_runtime.cpp#L205); [matching2/src/render/animation_manager.cpp:1411](../../../matching2/src/render/animation_manager.cpp#L1411) |
| `0x00405500` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/player.cpp:124](../../../matching2/src/game/player.cpp#L124) |
| `0x004055C0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/player.cpp:447](../../../matching2/src/game/player.cpp#L447); [matching2/src/game/recovery_leaves.cpp:529](../../../matching2/src/game/recovery_leaves.cpp#L529) |
| `0x00405620` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/player.cpp:477](../../../matching2/src/game/player.cpp#L477); [matching2/src/game/recovery_leaves.cpp:802](../../../matching2/src/game/recovery_leaves.cpp#L802) |
| `0x004056B0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/recovery_leaves.cpp:934](../../../matching2/src/game/recovery_leaves.cpp#L934) |
| `0x00405750` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/player.cpp:3](../../../matching2/src/game/player.cpp#L3); [matching2/src/game/player.cpp:299](../../../matching2/src/game/player.cpp#L299) |
| `0x00405860` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/player.cpp:3](../../../matching2/src/game/player.cpp#L3); [matching2/src/game/player.cpp:155](../../../matching2/src/game/player.cpp#L155) |
| `0x004059F0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/player.cpp:4](../../../matching2/src/game/player.cpp#L4); [matching2/src/game/player.cpp:243](../../../matching2/src/game/player.cpp#L243) |
| `0x00405AC0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/player.cpp:4](../../../matching2/src/game/player.cpp#L4); [matching2/src/game/player.cpp:358](../../../matching2/src/game/player.cpp#L358) |
| `0x00405B60` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/player.cpp:5](../../../matching2/src/game/player.cpp#L5) |
| `0x00405BE0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/player_scheduler.cpp:25](../../../matching2/src/game/player_scheduler.cpp#L25) |
| `0x00405D00` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/entity.cpp:27](../../../matching2/src/game/entity.cpp#L27) |
| `0x00405DE0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/entity.cpp:86](../../../matching2/src/game/entity.cpp#L86) |
| `0x00405E20` | semantic | reported_partial | yes / yes / yes | [matching2/src/game/bullet_manager.cpp:193](../../../matching2/src/game/bullet_manager.cpp#L193); [matching2/src/game/bullet_manager.cpp:228](../../../matching2/src/game/bullet_manager.cpp#L228) |
| `0x00405ED0` | semantic | reported_grounded | yes / yes / yes | [matching2/src/game/bullet_manager.cpp:265](../../../matching2/src/game/bullet_manager.cpp#L265); [matching2/src/game/bullet_manager_overlay.cpp:2](../../../matching2/src/game/bullet_manager_overlay.cpp#L2) |
| `0x00405F70` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/manager_teardown.cpp:135](../../../matching2/src/game/manager_teardown.cpp#L135); [matching2/include/th10/game/manager_teardown.hpp:5](../../../matching2/include/th10/game/manager_teardown.hpp#L5) |
| `0x00406060` | semantic | reported_grounded | yes / yes / yes | [matching2/src/game/bullet_manager.cpp:309](../../../matching2/src/game/bullet_manager.cpp#L309); [matching2/include/th10/game/stage_entry.hpp:16](../../../matching2/include/th10/game/stage_entry.hpp#L16) |
| `0x00406160` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/entity.cpp:47](../../../matching2/src/game/entity.cpp#L47) |
| `0x004061D0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/entity.cpp:54](../../../matching2/src/game/entity.cpp#L54) |
| `0x00406240` | semantic | reported_grounded | yes / yes / yes | [matching2/src/game/bullet_runtime_update.cpp:17](../../../matching2/src/game/bullet_runtime_update.cpp#L17); [matching2/include/th10/game/bullet_runtime_update.hpp:37](../../../matching2/include/th10/game/bullet_runtime_update.hpp#L37) |
| `0x004065C0` | semantic | reported_partial | yes / yes / yes | [matching2/src/game/bullet_manager.cpp:55](../../../matching2/src/game/bullet_manager.cpp#L55); [matching2/src/game/bullet_manager.cpp:366](../../../matching2/src/game/bullet_manager.cpp#L366) |
| `0x004066E0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/enemy_lifecycle.cpp:54](../../../matching2/src/game/enemy_lifecycle.cpp#L54) |
| `0x0040678E` | semantic | reference_unresolved | missing / missing / yes | [matching2/src/game/player_motion.cpp:30](../../../matching2/src/game/player_motion.cpp#L30) |
| `0x004067D0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/enemy_projectile_spawn.cpp:6](../../../matching2/src/game/enemy_projectile_spawn.cpp#L6) |
| `0x00406D90` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/projectile_command_runtime.cpp:3](../../../matching2/src/game/projectile_command_runtime.cpp#L3) |
| `0x004073E0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/enemy_grid_scan.cpp:13](../../../matching2/src/game/enemy_grid_scan.cpp#L13); [matching2/include/th10/script/ecl.hpp:173](../../../matching2/include/th10/script/ecl.hpp#L173) |
| `0x004074B0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/player_motion.cpp:92](../../../matching2/src/game/player_motion.cpp#L92) |
| `0x00407560` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/enemy_motion_steps.cpp:61](../../../matching2/src/game/enemy_motion_steps.cpp#L61) |
| `0x004076A0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/player_motion.cpp:122](../../../matching2/src/game/player_motion.cpp#L122) |
| `0x00407780` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/enemy_motion_steps.cpp:150](../../../matching2/src/game/enemy_motion_steps.cpp#L150) |
| `0x004078E0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/enemy_motion_steps.cpp:145](../../../matching2/src/game/enemy_motion_steps.cpp#L145) |
| `0x00407A30` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/enemy_motion_steps.cpp:203](../../../matching2/src/game/enemy_motion_steps.cpp#L203) |
| `0x00407BE0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/enemy_motion_steps.cpp:155](../../../matching2/src/game/enemy_motion_steps.cpp#L155) |
| `0x00407DA0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/player_motion.cpp:62](../../../matching2/src/game/player_motion.cpp#L62) |
| `0x00407E40` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/player_motion.cpp:76](../../../matching2/src/game/player_motion.cpp#L76) |
| `0x00407EF0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/enemy_motion_steps.cpp:81](../../../matching2/src/game/enemy_motion_steps.cpp#L81) |
| `0x00408030` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/score.cpp:506](../../../matching2/src/game/score.cpp#L506) |
| `0x00408100` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/enemy_lifecycle.cpp:152](../../../matching2/src/game/enemy_lifecycle.cpp#L152) |
| `0x00408210` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/entity_region_sweep.cpp:3](../../../matching2/src/game/entity_region_sweep.cpp#L3); [matching2/src/game/entity_region_sweep.cpp:21](../../../matching2/src/game/entity_region_sweep.cpp#L21); [matching2/include/th10/game/entity_region_sweep.hpp:3](../../../matching2/include/th10/game/entity_region_sweep.hpp#L3) |
| `0x00408660` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/score.cpp:141](../../../matching2/src/game/score.cpp#L141) |
| `0x004086B0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/score.cpp:265](../../../matching2/src/game/score.cpp#L265) |
| `0x00408750` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/score.cpp:415](../../../matching2/src/game/score.cpp#L415) |
| `0x004088C0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/score.cpp:354](../../../matching2/src/game/score.cpp#L354) |
| `0x00408910` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/manager_factories.cpp:361](../../../matching2/src/game/manager_factories.cpp#L361); [matching2/src/game/score.cpp:170](../../../matching2/src/game/score.cpp#L170) |
| `0x004089C0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/score.cpp:182](../../../matching2/src/game/score.cpp#L182); [matching2/src/game/score.cpp:209](../../../matching2/src/game/score.cpp#L209) |
| `0x00408AF0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/manager_teardown.cpp:251](../../../matching2/src/game/manager_teardown.cpp#L251); [matching2/include/th10/game/manager_teardown.hpp:3](../../../matching2/include/th10/game/manager_teardown.hpp#L3) |
| `0x00408C90` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/manager_factories.cpp:358](../../../matching2/src/game/manager_factories.cpp#L358) |
| `0x00408D60` | semantic | reported_partial | yes / yes / yes | [matching2/src/game/score.cpp:33](../../../matching2/src/game/score.cpp#L33); [matching2/src/game/score_runtime_ui_update.cpp:22](../../../matching2/src/game/score_runtime_ui_update.cpp#L22); [matching2/include/th10/game/score_runtime_ui_update.hpp:37](../../../matching2/include/th10/game/score_runtime_ui_update.hpp#L37) |
| `0x004091C0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/score.cpp:644](../../../matching2/src/game/score.cpp#L644) |
| `0x00409230` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/score.cpp:117](../../../matching2/src/game/score.cpp#L117); [matching2/src/game/score.cpp:634](../../../matching2/src/game/score.cpp#L634) |
| `0x00409270` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/score.cpp:123](../../../matching2/src/game/score.cpp#L123); [matching2/src/game/score.cpp:660](../../../matching2/src/game/score.cpp#L660) |
| `0x00409280` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/ui_final_runtime.cpp:81](../../../matching2/src/game/ui_final_runtime.cpp#L81) |
| `0x00409C00` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/spell_card_end.cpp:17](../../../matching2/src/game/spell_card_end.cpp#L17) |
| `0x00409D90` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/score.cpp:569](../../../matching2/src/game/score.cpp#L569) |
| `0x00409E20` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/score.cpp:621](../../../matching2/src/game/score.cpp#L621) |
| `0x00409E50` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/render/anm_propagate.cpp:19](../../../matching2/src/render/anm_propagate.cpp#L19); [matching2/include/th10/render/anm_propagate.hpp:24](../../../matching2/include/th10/render/anm_propagate.hpp#L24) |
| `0x00409F90` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/manager_teardown.cpp:25](../../../matching2/src/game/manager_teardown.cpp#L25); [matching2/include/th10/game/manager_teardown.hpp:5](../../../matching2/include/th10/game/manager_teardown.hpp#L5) |
| `0x0040A940` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/sprite_test_overlay.cpp:45](../../../matching2/src/game/sprite_test_overlay.cpp#L45); [matching2/include/th10/game/sprite_test_overlay.hpp:19](../../../matching2/include/th10/game/sprite_test_overlay.hpp#L19) |
| `0x0040AC20` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/score.cpp:368](../../../matching2/src/game/score.cpp#L368) |
| `0x0040AC90` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/score.cpp:406](../../../matching2/src/game/score.cpp#L406) |
| `0x0040ACE0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/score.cpp:275](../../../matching2/src/game/score.cpp#L275) |
| `0x0040AD20` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/score.cpp:389](../../../matching2/src/game/score.cpp#L389) |
| `0x0040AE70` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/bullet.cpp:6](../../../matching2/src/game/bullet.cpp#L6); [matching2/src/game/bullet.cpp:717](../../../matching2/src/game/bullet.cpp#L717); [matching2/include/th10/game/entity.hpp:266](../../../matching2/include/th10/game/entity.hpp#L266) |
| `0x0040AF00` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/bullet.cpp:5](../../../matching2/src/game/bullet.cpp#L5); [matching2/src/game/bullet.cpp:670](../../../matching2/src/game/bullet.cpp#L670); [matching2/include/th10/game/entity.hpp:259](../../../matching2/include/th10/game/entity.hpp#L259) |
| `0x0040AF90` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/bullet.cpp:5](../../../matching2/src/game/bullet.cpp#L5); [matching2/src/game/bullet.cpp:749](../../../matching2/src/game/bullet.cpp#L749); [matching2/include/th10/game/entity.hpp:262](../../../matching2/include/th10/game/entity.hpp#L262) |
| `0x0040B110` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/enemy_lifecycle.cpp:128](../../../matching2/src/game/enemy_lifecycle.cpp#L128) |
| `0x0040B250` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/bullet.cpp:151](../../../matching2/src/game/bullet.cpp#L151) |
| `0x0040B3A0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/bullet_anim_release.cpp:17](../../../matching2/src/game/bullet_anim_release.cpp#L17); [matching2/include/th10/game/bullet_anim_release.hpp:39](../../../matching2/include/th10/game/bullet_anim_release.hpp#L39) |
| `0x0040B480` | semantic | reported_partial | yes / yes / yes | [matching2/src/game/asset_buffer.cpp:5](../../../matching2/src/game/asset_buffer.cpp#L5) |
| `0x0040B560` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/message_manager_init.cpp:3](../../../matching2/src/game/message_manager_init.cpp#L3); [matching2/include/th10/game/ending_text.hpp:7](../../../matching2/include/th10/game/ending_text.hpp#L7); [matching2/include/th10/game/message_manager_init.hpp:31](../../../matching2/include/th10/game/message_manager_init.hpp#L31) |
| `0x0040B7B0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/manager_teardown.cpp:180](../../../matching2/src/game/manager_teardown.cpp#L180); [matching2/include/th10/game/manager_teardown.hpp:4](../../../matching2/include/th10/game/manager_teardown.hpp#L4) |
| `0x0040B940` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/recovery_leaves.cpp:810](../../../matching2/src/game/recovery_leaves.cpp#L810) |
| `0x0040B9D0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/score.cpp:132](../../../matching2/src/game/score.cpp#L132) |
| `0x0040B9F0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/recovery_leaves.cpp:952](../../../matching2/src/game/recovery_leaves.cpp#L952) |
| `0x0040BA90` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/ending_text.cpp:27](../../../matching2/src/game/ending_text.cpp#L27); [matching2/include/th10/game/ending_text.hpp:7](../../../matching2/include/th10/game/ending_text.hpp#L7) |
| `0x0040BD20` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/recovery_leaves.cpp:464](../../../matching2/src/game/recovery_leaves.cpp#L464) |
| `0x0040BD80` | partial | separate_sparse_review | yes / yes / yes | [matching2/src/game/event_script_runtime.cpp:5](../../../matching2/src/game/event_script_runtime.cpp#L5) |
| `0x0040C3C0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/stage_background.cpp:17](../../../matching2/src/game/stage_background.cpp#L17); [matching2/src/game/stage_background_overlay.cpp:2](../../../matching2/src/game/stage_background_overlay.cpp#L2) |
| `0x0040C480` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/render/animation_manager.cpp:650](../../../matching2/src/render/animation_manager.cpp#L650) |
| `0x0040C4D0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/render/animation_manager.cpp:658](../../../matching2/src/render/animation_manager.cpp#L658) |
| `0x0040C540` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/animation_resource_lazy_fetch.cpp:1](../../../matching2/src/game/animation_resource_lazy_fetch.cpp#L1); [matching2/src/game/animation_resource_lazy_fetch.cpp:2](../../../matching2/src/game/animation_resource_lazy_fetch.cpp#L2); [matching2/include/th10/game/animation_resource_lazy_fetch.hpp:1](../../../matching2/include/th10/game/animation_resource_lazy_fetch.hpp#L1); [matching2/include/th10/game/animation_resource_lazy_fetch.hpp:2](../../../matching2/include/th10/game/animation_resource_lazy_fetch.hpp#L2) |
| `0x0040C6E0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/bullet.cpp:175](../../../matching2/src/game/bullet.cpp#L175) |
| `0x0040C730` | semantic | reported_grounded | yes / yes / yes | [matching2/src/game/bullet_manager.cpp:427](../../../matching2/src/game/bullet_manager.cpp#L427) |
| `0x0040C9A0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/recovery_leaves.cpp:718](../../../matching2/src/game/recovery_leaves.cpp#L718) |
| `0x0040C9D0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/item_scatter.cpp:27](../../../matching2/src/game/item_scatter.cpp#L27); [matching2/include/th10/game/item_scatter.hpp:4](../../../matching2/include/th10/game/item_scatter.hpp#L4) |
| `0x0040CC50` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/recovery_leaves.cpp:44](../../../matching2/src/game/recovery_leaves.cpp#L44) |
| `0x0040CC70` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/bullet.cpp:4](../../../matching2/src/game/bullet.cpp#L4); [matching2/src/game/bullet.cpp:191](../../../matching2/src/game/bullet.cpp#L191) |
| `0x0040CD20` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/script/ecl_name_table.cpp:73](../../../matching2/src/script/ecl_name_table.cpp#L73) |
| `0x0040CEA0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/bullet.cpp:140](../../../matching2/src/game/bullet.cpp#L140) |
| `0x0040CF40` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/bullet.cpp:108](../../../matching2/src/game/bullet.cpp#L108); [matching2/include/th10/game/entity.hpp:208](../../../matching2/include/th10/game/entity.hpp#L208) |
| `0x0040CF60` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/bullet.cpp:119](../../../matching2/src/game/bullet.cpp#L119) |
| `0x0040CF90` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/bullet.cpp:128](../../../matching2/src/game/bullet.cpp#L128) |
| `0x0040CFB0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/bullet.cpp:3](../../../matching2/src/game/bullet.cpp#L3); [matching2/src/game/bullet.cpp:544](../../../matching2/src/game/bullet.cpp#L544) |
| `0x0040D280` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/message_host_init.cpp:3](../../../matching2/src/game/message_host_init.cpp#L3); [matching2/src/game/message_host_init.cpp:44](../../../matching2/src/game/message_host_init.cpp#L44); [matching2/include/th10/game/message_host_init.hpp:3](../../../matching2/include/th10/game/message_host_init.hpp#L3) |
| `0x0040D530` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/manager_teardown.cpp:48](../../../matching2/src/game/manager_teardown.cpp#L48); [matching2/include/th10/game/manager_teardown.hpp:4](../../../matching2/include/th10/game/manager_teardown.hpp#L4) |
| `0x0040D680` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/bullet.cpp:164](../../../matching2/src/game/bullet.cpp#L164) |
| `0x0040D6B0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/manager_factories.cpp:135](../../../matching2/src/game/manager_factories.cpp#L135) |
| `0x0040D750` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/enemy_lifecycle.cpp:101](../../../matching2/src/game/enemy_lifecycle.cpp#L101) |
| `0x0040D830` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/bullet.cpp:3](../../../matching2/src/game/bullet.cpp#L3); [matching2/src/game/bullet.cpp:399](../../../matching2/src/game/bullet.cpp#L399) |
| `0x0040DAE0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/enemy_lifecycle.cpp:179](../../../matching2/src/game/enemy_lifecycle.cpp#L179) |
| `0x0040DC80` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/bullet.cpp:4](../../../matching2/src/game/bullet.cpp#L4); [matching2/src/game/bullet.cpp:224](../../../matching2/src/game/bullet.cpp#L224) |
| `0x0040E5F0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/boss_overlays.cpp:35](../../../matching2/src/game/boss_overlays.cpp#L35) |
| `0x0040E6A0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/enemy_lifecycle.cpp:77](../../../matching2/src/game/enemy_lifecycle.cpp#L77); [matching2/src/game/enemy_lifecycle_overlay.cpp:2](../../../matching2/src/game/enemy_lifecycle_overlay.cpp#L2) |
| `0x0040E770` | partial | outside_prior_bounded_and_sparse_scopes | missing / missing / yes | [matching2/src/script/ecl_core_interpreter.cpp:1108](../../../matching2/src/script/ecl_core_interpreter.cpp#L1108); [matching2/src/script/ecl_vm.cpp:1](../../../matching2/src/script/ecl_vm.cpp#L1); [matching2/src/script/ecl_vm.cpp:397](../../../matching2/src/script/ecl_vm.cpp#L397); [matching2/src/script/ecl_vm.cpp:648](../../../matching2/src/script/ecl_vm.cpp#L648) |
| `0x00412720` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/recovery_leaves.cpp:78](../../../matching2/src/game/recovery_leaves.cpp#L78) |
| `0x004127A0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/spell_timer.cpp:34](../../../matching2/src/game/spell_timer.cpp#L34) |
| `0x00412A00` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/script/ecl_vm.cpp:215](../../../matching2/src/script/ecl_vm.cpp#L215) |
| `0x00412A10` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/script/ecl_vm.cpp:246](../../../matching2/src/script/ecl_vm.cpp#L246) |
| `0x00412AA0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/recovery_leaves.cpp:62](../../../matching2/src/game/recovery_leaves.cpp#L62) |
| `0x00412AC0` | semantic | separate_sparse_review | yes / yes / yes | [matching2/src/game/trajectory_evaluate.cpp:34](../../../matching2/src/game/trajectory_evaluate.cpp#L34); [matching2/include/th10/game/trajectory_evaluate.hpp:11](../../../matching2/include/th10/game/trajectory_evaluate.hpp#L11) |
| `0x00412DB0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/recovery_leaves.cpp:103](../../../matching2/src/game/recovery_leaves.cpp#L103) |
| `0x00412E70` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/score.cpp:577](../../../matching2/src/game/score.cpp#L577) |
| `0x00412ED0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/recovery_leaves.cpp:180](../../../matching2/src/game/recovery_leaves.cpp#L180); [matching2/include/th10/script/ecl.hpp:101](../../../matching2/include/th10/script/ecl.hpp#L101) |
| `0x00412FF0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/replay_progress.cpp:58](../../../matching2/src/game/replay_progress.cpp#L58) |
| `0x00413170` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/recovery_leaves.cpp:188](../../../matching2/src/game/recovery_leaves.cpp#L188) |
| `0x00413200` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/recovery_leaves.cpp:68](../../../matching2/src/game/recovery_leaves.cpp#L68) |
| `0x00413270` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/recovery_leaves.cpp:120](../../../matching2/src/game/recovery_leaves.cpp#L120) |
| `0x00413350` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/stats_task.cpp:11](../../../matching2/src/game/stats_task.cpp#L11); [matching2/include/th10/game/stats_task.hpp:19](../../../matching2/include/th10/game/stats_task.hpp#L19) |
| `0x00413450` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/recovery_leaves.cpp:457](../../../matching2/src/game/recovery_leaves.cpp#L457) |
| `0x004134B0` | semantic | reported_partial | yes / yes / yes | [matching2/src/app/fps_counter.cpp:52](../../../matching2/src/app/fps_counter.cpp#L52) |
| `0x004135D0` | semantic | reported_partial | yes / yes / yes | [matching2/src/app/fps_counter.cpp:24](../../../matching2/src/app/fps_counter.cpp#L24) |
| `0x004136C0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/render/animation_slot.cpp:1](../../../matching2/src/render/animation_slot.cpp#L1); [matching2/src/render/animation_slot.cpp:2](../../../matching2/src/render/animation_slot.cpp#L2); [matching2/include/th10/render/animation_slot.hpp:1](../../../matching2/include/th10/render/animation_slot.hpp#L1); [matching2/include/th10/render/animation_slot.hpp:2](../../../matching2/include/th10/render/animation_slot.hpp#L2) |
| `0x00413790` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/recovery_leaves.cpp:91](../../../matching2/src/game/recovery_leaves.cpp#L91) |
| `0x00413810` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/manager_factories.cpp:392](../../../matching2/src/game/manager_factories.cpp#L392); [matching2/src/game/pool_constructors.cpp:279](../../../matching2/src/game/pool_constructors.cpp#L279); [matching2/include/th10/game/pool_constructors.hpp:24](../../../matching2/include/th10/game/pool_constructors.hpp#L24) |
| `0x00413980` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/task_registration.cpp:159](../../../matching2/src/game/task_registration.cpp#L159); [matching2/src/game/task_registration.cpp:194](../../../matching2/src/game/task_registration.cpp#L194); [matching2/include/th10/game/task_registration.hpp:71](../../../matching2/include/th10/game/task_registration.hpp#L71) |
| `0x00413A20` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/score_tasks.cpp:53](../../../matching2/src/game/score_tasks.cpp#L53) |
| `0x00413BC0` | semantic | reported_partial | yes / yes / yes | [matching2/src/game/player_front_runtime.cpp:164](../../../matching2/src/game/player_front_runtime.cpp#L164) |
| `0x00414370` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/manager_teardown.cpp:165](../../../matching2/src/game/manager_teardown.cpp#L165); [matching2/include/th10/game/manager_teardown.hpp:4](../../../matching2/include/th10/game/manager_teardown.hpp#L4) |
| `0x00414570` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/recovery_leaves.cpp:1022](../../../matching2/src/game/recovery_leaves.cpp#L1022) |
| `0x004145F0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/manager_teardown.cpp:156](../../../matching2/src/game/manager_teardown.cpp#L156); [matching2/include/th10/game/manager_teardown.hpp:3](../../../matching2/include/th10/game/manager_teardown.hpp#L3) |
| `0x00414830` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/manager_factories.cpp:389](../../../matching2/src/game/manager_factories.cpp#L389) |
| `0x00414900` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/ui_final_runtime.cpp:278](../../../matching2/src/game/ui_final_runtime.cpp#L278); [matching2/src/game/ui_final_runtime.cpp:646](../../../matching2/src/game/ui_final_runtime.cpp#L646); [matching2/include/th10/game/ui_final_runtime.hpp:89](../../../matching2/include/th10/game/ui_final_runtime.hpp#L89) |
| `0x00415800` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/game_state_overlay_draw.cpp:3](../../../matching2/src/game/game_state_overlay_draw.cpp#L3); [matching2/src/game/task_registration.cpp:69](../../../matching2/src/game/task_registration.cpp#L69) |
| `0x00415B00` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/stage_slot_state.cpp:3](../../../matching2/src/game/stage_slot_state.cpp#L3); [matching2/src/game/stage_slot_state.cpp:45](../../../matching2/src/game/stage_slot_state.cpp#L45); [matching2/include/th10/game/stage_slot_state.hpp:3](../../../matching2/include/th10/game/stage_slot_state.hpp#L3) |
| `0x00415DB0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/replay_progress.cpp:35](../../../matching2/src/game/replay_progress.cpp#L35) |
| `0x00415E90` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/ui_final_runtime.cpp:653](../../../matching2/src/game/ui_final_runtime.cpp#L653); [matching2/include/th10/game/ui_final_runtime.hpp:9](../../../matching2/include/th10/game/ui_final_runtime.hpp#L9) |
| `0x00417010` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/platform/path.cpp:6](../../../matching2/src/platform/path.cpp#L6) |
| `0x00417040` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/score_hud_update.cpp:12](../../../matching2/src/game/score_hud_update.cpp#L12) |
| `0x004172E0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/result_overlay.cpp:12](../../../matching2/src/game/result_overlay.cpp#L12); [matching2/include/th10/game/result_overlay.hpp:4](../../../matching2/include/th10/game/result_overlay.hpp#L4); [matching2/include/th10/game/result_overlay.hpp:30](../../../matching2/include/th10/game/result_overlay.hpp#L30) |
| `0x004175E0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/rank_level.cpp:10](../../../matching2/src/game/rank_level.cpp#L10); [matching2/include/th10/game/rank_level.hpp:5](../../../matching2/include/th10/game/rank_level.hpp#L5) |
| `0x00417770` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/recovery_leaves.cpp:228](../../../matching2/src/game/recovery_leaves.cpp#L228) |
| `0x00417800` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/recovery_leaves.cpp:133](../../../matching2/src/game/recovery_leaves.cpp#L133) |
| `0x00417870` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/stage_entry.cpp:28](../../../matching2/src/game/stage_entry.cpp#L28); [matching2/include/th10/game/stage_entry.hpp:6](../../../matching2/include/th10/game/stage_entry.hpp#L6); [matching2/include/th10/game/stage_entry.hpp:76](../../../matching2/include/th10/game/stage_entry.hpp#L76); [matching2/include/th10/game/stage_entry.hpp:158](../../../matching2/include/th10/game/stage_entry.hpp#L158) |
| `0x00417C80` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/manager_teardown.cpp:201](../../../matching2/src/game/manager_teardown.cpp#L201); [matching2/include/th10/game/manager_teardown.hpp:3](../../../matching2/include/th10/game/manager_teardown.hpp#L3) |
| `0x004180E0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/game_ui_create.cpp:11](../../../matching2/src/game/game_ui_create.cpp#L11); [matching2/include/th10/game/game_ui_create.hpp:5](../../../matching2/include/th10/game/game_ui_create.hpp#L5) |
| `0x00418150` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/util/heap.cpp:44](../../../matching2/src/util/heap.cpp#L44) |
| `0x00418190` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/stage_entry.cpp:175](../../../matching2/src/game/stage_entry.cpp#L175); [matching2/src/game/stage_update.cpp:64](../../../matching2/src/game/stage_update.cpp#L64); [matching2/include/th10/game/stage_entry.hpp:33](../../../matching2/include/th10/game/stage_entry.hpp#L33) |
| `0x00418810` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/recovery_leaves.cpp:856](../../../matching2/src/game/recovery_leaves.cpp#L856) |
| `0x004188A0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/recovery_leaves.cpp:965](../../../matching2/src/game/recovery_leaves.cpp#L965); [matching2/standalone/host_stage.cpp:3313](../../../matching2/standalone/host_stage.cpp#L3313) |
| `0x00418930` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/faith_gauge.cpp:22](../../../matching2/src/game/faith_gauge.cpp#L22); [matching2/include/th10/game/faith_gauge.hpp:5](../../../matching2/include/th10/game/faith_gauge.hpp#L5) |
| `0x00418A00` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/recovery_leaves.cpp:864](../../../matching2/src/game/recovery_leaves.cpp#L864) |
| `0x00418A90` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/score_timer_leaves.cpp:28](../../../matching2/src/game/score_timer_leaves.cpp#L28); [matching2/include/th10/game/score_timer_leaves.hpp:23](../../../matching2/include/th10/game/score_timer_leaves.hpp#L23) |
| `0x00418B80` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/score_timer_leaves.cpp:5](../../../matching2/src/game/score_timer_leaves.cpp#L5); [matching2/include/th10/game/score_timer_leaves.hpp:18](../../../matching2/include/th10/game/score_timer_leaves.hpp#L18); [matching2/include/th10/game/stage_entry.hpp:124](../../../matching2/include/th10/game/stage_entry.hpp#L124) |
| `0x00418C40` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/game_config_defaults.cpp:17](../../../matching2/src/game/game_config_defaults.cpp#L17); [matching2/include/th10/app/main_tasks.hpp:98](../../../matching2/include/th10/app/main_tasks.hpp#L98); [matching2/include/th10/game/game_config_defaults.hpp:28](../../../matching2/include/th10/game/game_config_defaults.hpp#L28); [matching2/standalone/host_main.cpp:5173](../../../matching2/standalone/host_main.cpp#L5173) |
| `0x00418D00` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/stage_tips.cpp:5](../../../matching2/src/game/stage_tips.cpp#L5) |
| `0x00418D40` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/stage_tip_manager.cpp:144](../../../matching2/src/game/stage_tip_manager.cpp#L144); [matching2/include/th10/game/stage_tips.hpp:53](../../../matching2/include/th10/game/stage_tips.hpp#L53) |
| `0x00418E30` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/stage_tip_manager.cpp:168](../../../matching2/src/game/stage_tip_manager.cpp#L168); [matching2/src/game/task_registration.cpp:88](../../../matching2/src/game/task_registration.cpp#L88); [matching2/include/th10/game/task_registration.hpp:25](../../../matching2/include/th10/game/task_registration.hpp#L25) |
| `0x00418EE0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/manager_teardown.cpp:110](../../../matching2/src/game/manager_teardown.cpp#L110); [matching2/include/th10/game/manager_teardown.hpp:4](../../../matching2/include/th10/game/manager_teardown.hpp#L4) |
| `0x00419040` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/recovery_leaves.cpp:443](../../../matching2/src/game/recovery_leaves.cpp#L443) |
| `0x00419090` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/recovery_leaves.cpp:996](../../../matching2/src/game/recovery_leaves.cpp#L996); [matching2/include/th10/game/stage_entry.hpp:16](../../../matching2/include/th10/game/stage_entry.hpp#L16) |
| `0x00419120` | semantic | reported_grounded | yes / yes / yes | [matching2/src/game/effect_indicator_queue.cpp:2](../../../matching2/src/game/effect_indicator_queue.cpp#L2); [matching2/include/th10/game/effect_indicator_queue.hpp:6](../../../matching2/include/th10/game/effect_indicator_queue.hpp#L6) |
| `0x00419650` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/stage_focus_fade.cpp:4](../../../matching2/src/game/stage_focus_fade.cpp#L4); [matching2/src/game/stage_tip_manager.cpp:31](../../../matching2/src/game/stage_tip_manager.cpp#L31) |
| `0x004198A0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/recovery_leaves.cpp:323](../../../matching2/src/game/recovery_leaves.cpp#L323) |
| `0x004198C0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/recovery_leaves.cpp:18](../../../matching2/src/game/recovery_leaves.cpp#L18) |
| `0x00419960` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/stage_tip_parser.cpp:1](../../../matching2/src/game/stage_tip_parser.cpp#L1); [matching2/src/game/stage_tip_parser.cpp:185](../../../matching2/src/game/stage_tip_parser.cpp#L185) |
| `0x00419F40` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/script/script_text_reader.cpp:12](../../../matching2/src/script/script_text_reader.cpp#L12) |
| `0x0041A050` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/recovery_leaves.cpp:667](../../../matching2/src/game/recovery_leaves.cpp#L667) |
| `0x0041A0A0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/recovery_leaves.cpp:743](../../../matching2/src/game/recovery_leaves.cpp#L743) |
| `0x0041A120` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/stage_tip_manager.cpp:207](../../../matching2/src/game/stage_tip_manager.cpp#L207); [matching2/include/th10/game/stage_tips.hpp:66](../../../matching2/include/th10/game/stage_tips.hpp#L66) |
| `0x0041A200` | semantic | reported_partial | yes / yes / yes | [matching2/src/archive/score_save.cpp:256](../../../matching2/src/archive/score_save.cpp#L256); [matching2/include/th10/archive/score_save.hpp:3](../../../matching2/include/th10/archive/score_save.hpp#L3) |
| `0x0041AB10` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/recovery_leaves.cpp:334](../../../matching2/src/game/recovery_leaves.cpp#L334) |
| `0x0041AB70` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/entity_movement_slot.cpp:1](../../../matching2/src/game/entity_movement_slot.cpp#L1); [matching2/include/th10/game/entity_movement_slot.hpp:1](../../../matching2/include/th10/game/entity_movement_slot.hpp#L1) |
| `0x0041AD60` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/entity.cpp:74](../../../matching2/src/game/entity.cpp#L74) |
| `0x0041AD90` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/recovery_leaves.cpp:537](../../../matching2/src/game/recovery_leaves.cpp#L537) |
| `0x0041ADF0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/manager_teardown.cpp:121](../../../matching2/src/game/manager_teardown.cpp#L121); [matching2/include/th10/game/manager_teardown.hpp:5](../../../matching2/include/th10/game/manager_teardown.hpp#L5) |
| `0x0041AED0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/manager_factories.cpp:444](../../../matching2/src/game/manager_factories.cpp#L444); [matching2/include/th10/game/stage_entry.hpp:16](../../../matching2/include/th10/game/stage_entry.hpp#L16); [matching2/standalone/host_stage.hpp:20](../../../matching2/standalone/host_stage.hpp#L20) |
| `0x0041AFD0` | semantic | reported_partial | yes / yes / yes | [matching2/src/game/manager_factories.cpp:29](../../../matching2/src/game/manager_factories.cpp#L29) |
| `0x0041BA50` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/enemy_drop_sweep.cpp:20](../../../matching2/src/game/enemy_drop_sweep.cpp#L20); [matching2/include/th10/game/enemy_drop_sweep.hpp:5](../../../matching2/include/th10/game/enemy_drop_sweep.hpp#L5) |
| `0x0041BB00` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/item_spawn.cpp:27](../../../matching2/src/game/item_spawn.cpp#L27); [matching2/include/th10/game/entity_region_sweep.hpp:48](../../../matching2/include/th10/game/entity_region_sweep.hpp#L48); [matching2/include/th10/game/item_spawn.hpp:4](../../../matching2/include/th10/game/item_spawn.hpp#L4); [matching2/include/th10/game/item_spawn.hpp:38](../../../matching2/include/th10/game/item_spawn.hpp#L38); [matching2/include/th10/game/laser_line.hpp:164](../../../matching2/include/th10/game/laser_line.hpp#L164) |
| `0x0041BE80` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/score.cpp:1](../../../matching2/src/game/score.cpp#L1) |
| `0x0041BEB0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/score.cpp:421](../../../matching2/src/game/score.cpp#L421) |
| `0x0041C030` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/score.cpp:428](../../../matching2/src/game/score.cpp#L428) |
| `0x0041C120` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/task_registration.cpp:132](../../../matching2/src/game/task_registration.cpp#L132); [matching2/include/th10/game/task_registration.hpp:56](../../../matching2/include/th10/game/task_registration.hpp#L56) |
| `0x0041C1C0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/score.cpp:484](../../../matching2/src/game/score.cpp#L484) |
| `0x0041C290` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/object_factories.cpp:11](../../../matching2/src/game/object_factories.cpp#L11); [matching2/include/th10/game/object_factories.hpp:5](../../../matching2/include/th10/game/object_factories.hpp#L5); [matching2/include/th10/game/stage_entry.hpp:16](../../../matching2/include/th10/game/stage_entry.hpp#L16); [matching2/standalone/host_stage.hpp:20](../../../matching2/standalone/host_stage.hpp#L20) |
| `0x0041C330` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/score_tasks.cpp:82](../../../matching2/src/game/score_tasks.cpp#L82) |
| `0x0041C510` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/score_queue.cpp:3](../../../matching2/src/game/score_queue.cpp#L3); [matching2/include/th10/game/score_queue.hpp:21](../../../matching2/include/th10/game/score_queue.hpp#L21) |
| `0x0041C5B0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/score.cpp:456](../../../matching2/src/game/score.cpp#L456) |
| `0x0041C680` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/score_view_ctor.cpp:5](../../../matching2/src/game/score_view_ctor.cpp#L5); [matching2/include/th10/game/score_view_ctor.hpp:9](../../../matching2/include/th10/game/score_view_ctor.hpp#L9) |
| `0x0041C7D0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/score.cpp:538](../../../matching2/src/game/score.cpp#L538) |
| `0x0041C800` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/score.cpp:547](../../../matching2/src/game/score.cpp#L547) |
| `0x0041C850` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/score_cleanup.cpp:3](../../../matching2/src/game/score_cleanup.cpp#L3) |
| `0x0041CFD0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/projectile_bounce.cpp:7](../../../matching2/src/game/projectile_bounce.cpp#L7) |
| `0x0041D2C0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/effect_accel.cpp:28](../../../matching2/src/game/effect_accel.cpp#L28) |
| `0x0041D3D0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/laser_line.cpp:3](../../../matching2/src/game/laser_line.cpp#L3); [matching2/include/th10/game/laser_line.hpp:4](../../../matching2/include/th10/game/laser_line.hpp#L4); [matching2/include/th10/game/laser_line.hpp:36](../../../matching2/include/th10/game/laser_line.hpp#L36) |
| `0x0041D7C0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/boss_overlays.cpp:4](../../../matching2/src/game/boss_overlays.cpp#L4) |
| `0x0041D880` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/laser_segment_cut.cpp:227](../../../matching2/src/game/laser_segment_cut.cpp#L227) |
| `0x0041DD80` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/laser_segment_cut.cpp:213](../../../matching2/src/game/laser_segment_cut.cpp#L213) |
| `0x0041E260` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/line_effect_sweep.cpp:26](../../../matching2/src/game/line_effect_sweep.cpp#L26); [matching2/include/th10/game/line_effect_sweep.hpp:4](../../../matching2/include/th10/game/line_effect_sweep.hpp#L4) |
| `0x0041E4D0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/math/oriented_rect.cpp:5](../../../matching2/src/math/oriented_rect.cpp#L5) |
| `0x0041E700` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/laser_grow_update.cpp:49](../../../matching2/src/game/laser_grow_update.cpp#L49); [matching2/include/th10/game/laser_grow_update.hpp:4](../../../matching2/include/th10/game/laser_grow_update.hpp#L4) |
| `0x0041EB00` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/laser_segment_cut.cpp:200](../../../matching2/src/game/laser_segment_cut.cpp#L200); [matching2/include/th10/game/laser_segment_cut.hpp:41](../../../matching2/include/th10/game/laser_segment_cut.hpp#L41) |
| `0x0041EFA0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/laser_segment_cut.cpp:187](../../../matching2/src/game/laser_segment_cut.cpp#L187); [matching2/include/th10/game/laser_segment_cut.hpp:6](../../../matching2/include/th10/game/laser_segment_cut.hpp#L6); [matching2/include/th10/game/laser_segment_cut.hpp:37](../../../matching2/include/th10/game/laser_segment_cut.hpp#L37) |
| `0x0041F400` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/laser_line.cpp:124](../../../matching2/src/game/laser_line.cpp#L124); [matching2/include/th10/game/laser_line.hpp:139](../../../matching2/include/th10/game/laser_line.hpp#L139) |
| `0x0041F7A0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/score.cpp:589](../../../matching2/src/game/score.cpp#L589); [matching2/include/th10/game/laser_line.hpp:114](../../../matching2/include/th10/game/laser_line.hpp#L114) |
| `0x0041F800` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/math/vector.cpp:6](../../../matching2/src/math/vector.cpp#L6); [matching2/include/th10/game/laser_line.hpp:112](../../../matching2/include/th10/game/laser_line.hpp#L112) |
| `0x0041F850` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/recovery_leaves.cpp:759](../../../matching2/src/game/recovery_leaves.cpp#L759) |
| `0x0041F8D0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/recovery_leaves.cpp:586](../../../matching2/src/game/recovery_leaves.cpp#L586) |
| `0x0041F930` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/recovery_leaves.cpp:545](../../../matching2/src/game/recovery_leaves.cpp#L545) |
| `0x0041F990` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/title_assets.cpp:13](../../../matching2/src/game/title_assets.cpp#L13) |
| `0x0041FAC0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/recovery_leaves.cpp:1012](../../../matching2/src/game/recovery_leaves.cpp#L1012) |
| `0x0041FB50` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/manager_teardown.cpp:187](../../../matching2/src/game/manager_teardown.cpp#L187); [matching2/include/th10/game/manager_teardown.hpp:3](../../../matching2/include/th10/game/manager_teardown.hpp#L3) |
| `0x0041FD00` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/object_factories.cpp:43](../../../matching2/src/game/object_factories.cpp#L43); [matching2/include/th10/game/object_factories.hpp:19](../../../matching2/include/th10/game/object_factories.hpp#L19) |
| `0x0041FDD0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/result_screen_effects.cpp:16](../../../matching2/src/game/result_screen_effects.cpp#L16) |
| `0x0041FF80` | semantic | reported_grounded | yes / yes / yes | [matching2/src/app/main_tasks.cpp:6](../../../matching2/src/app/main_tasks.cpp#L6); [matching2/include/th10/app/main_tasks.hpp:37](../../../matching2/include/th10/app/main_tasks.hpp#L37) |
| `0x00420100` | semantic | reported_partial | yes / yes / yes | [matching2/src/app/version_marker.cpp:5](../../../matching2/src/app/version_marker.cpp#L5) |
| `0x00420270` | semantic | reported_grounded | yes / yes / yes | [matching2/src/app/main_tasks.cpp:48](../../../matching2/src/app/main_tasks.cpp#L48); [matching2/include/th10/app/main_tasks.hpp:3](../../../matching2/include/th10/app/main_tasks.hpp#L3) |
| `0x004203C0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/platform/win32_timer.cpp:7](../../../matching2/src/platform/win32_timer.cpp#L7) |
| `0x004203F0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/recovery_leaves.cpp:1038](../../../matching2/src/game/recovery_leaves.cpp#L1038) |
| `0x00420470` | semantic | reported_partial | yes / yes / yes | [matching2/src/app/main_tasks.cpp:20](../../../matching2/src/app/main_tasks.cpp#L20); [matching2/include/th10/app/main_tasks.hpp:3](../../../matching2/include/th10/app/main_tasks.hpp#L3); [matching2/include/th10/app/main_tasks.hpp:12](../../../matching2/include/th10/app/main_tasks.hpp#L12) |
| `0x00420670` | semantic | reported_partial | yes / yes / yes | [matching2/src/app/main_tasks.cpp:126](../../../matching2/src/app/main_tasks.cpp#L126); [matching2/include/th10/app/main_tasks.hpp:3](../../../matching2/include/th10/app/main_tasks.hpp#L3) |
| `0x00420870` | semantic | reported_grounded | yes / yes / yes | [matching2/src/app/main_tasks.cpp:81](../../../matching2/src/app/main_tasks.cpp#L81); [matching2/include/th10/app/main_tasks.hpp:3](../../../matching2/include/th10/app/main_tasks.hpp#L3); [matching2/standalone/host_main.cpp:156](../../../matching2/standalone/host_main.cpp#L156); [matching2/standalone/host_main.cpp:174](../../../matching2/standalone/host_main.cpp#L174); [matching2/standalone/host_main.cpp:5286](../../../matching2/standalone/host_main.cpp#L5286); [matching2/standalone/host_main.cpp:5299](../../../matching2/standalone/host_main.cpp#L5299); [matching2/standalone/host_main.cpp:5340](../../../matching2/standalone/host_main.cpp#L5340) |
| `0x00420A90` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/recovery_leaves.cpp:767](../../../matching2/src/game/recovery_leaves.cpp#L767) |
| `0x00420B10` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/platform/sound_dummy.cpp:7](../../../matching2/src/platform/sound_dummy.cpp#L7); [matching2/include/th10/platform/sound_dummy.hpp:5](../../../matching2/include/th10/platform/sound_dummy.hpp#L5) |
| `0x00420C00` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/scheduler.cpp:16](../../../matching2/src/game/scheduler.cpp#L16) |
| `0x00420C30` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/platform/sound_leaves.cpp:4](../../../matching2/src/platform/sound_leaves.cpp#L4); [matching2/include/th10/platform/sound_leaves.hpp:5](../../../matching2/include/th10/platform/sound_leaves.hpp#L5) |
| `0x00420CD0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/render/fog_disable.cpp:3](../../../matching2/src/render/fog_disable.cpp#L3); [matching2/include/th10/render/fog_disable.hpp:11](../../../matching2/include/th10/render/fog_disable.hpp#L11); [matching2/standalone/host_main.cpp:4272](../../../matching2/standalone/host_main.cpp#L4272) |
| `0x00420DD0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/version_list.cpp:7](../../../matching2/src/game/version_list.cpp#L7); [matching2/include/th10/game/version_list.hpp:12](../../../matching2/include/th10/game/version_list.hpp#L12) |
| `0x00420EA0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/thread_spawn.cpp:3](../../../matching2/src/game/thread_spawn.cpp#L3); [matching2/include/th10/game/game_ui_create.hpp:12](../../../matching2/include/th10/game/game_ui_create.hpp#L12); [matching2/include/th10/game/thread_spawn.hpp:16](../../../matching2/include/th10/game/thread_spawn.hpp#L16) |
| `0x00421070` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/render/queued_anm_cleanup.cpp:18](../../../matching2/src/render/queued_anm_cleanup.cpp#L18) |
| `0x00421300` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/render/anm_handle_release.cpp:29](../../../matching2/src/render/anm_handle_release.cpp#L29); [matching2/include/th10/render/anm_handle_release.hpp:7](../../../matching2/include/th10/render/anm_handle_release.hpp#L7) |
| `0x00421480` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/render/camera_setup.cpp:7](../../../matching2/src/render/camera_setup.cpp#L7) |
| `0x004215A0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/render/camera_apply.cpp:21](../../../matching2/src/render/camera_apply.cpp#L21); [matching2/include/th10/render/camera_apply.hpp:43](../../../matching2/include/th10/render/camera_apply.hpp#L43) |
| `0x004216F0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/render/camera_defaults.cpp:65](../../../matching2/src/render/camera_defaults.cpp#L65); [matching2/include/th10/render/camera_defaults.hpp:3](../../../matching2/include/th10/render/camera_defaults.hpp#L3) |
| `0x004218D0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/game_mode_switch.cpp:5](../../../matching2/src/game/game_mode_switch.cpp#L5) |
| `0x00421B90` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/math/vector3_cross.cpp:1](../../../matching2/src/math/vector3_cross.cpp#L1); [matching2/src/math/vector3_cross.cpp:2](../../../matching2/src/math/vector3_cross.cpp#L2); [matching2/include/th10/math/vector3_cross.hpp:1](../../../matching2/include/th10/math/vector3_cross.hpp#L1); [matching2/include/th10/math/vector3_cross.hpp:2](../../../matching2/include/th10/math/vector3_cross.hpp#L2) |
| `0x00421C50` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/slot_lock_leaves.cpp:4](../../../matching2/src/game/slot_lock_leaves.cpp#L4); [matching2/include/th10/game/slot_lock_leaves.hpp:16](../../../matching2/include/th10/game/slot_lock_leaves.hpp#L16) |
| `0x00421D20` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/slot_lock_leaves.cpp:19](../../../matching2/src/game/slot_lock_leaves.cpp#L19); [matching2/include/th10/game/slot_lock_leaves.hpp:22](../../../matching2/include/th10/game/slot_lock_leaves.hpp#L22) |
| `0x00421E00` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/platform/sound_fade.cpp:21](../../../matching2/src/platform/sound_fade.cpp#L21); [matching2/include/th10/platform/sound_fade.hpp:12](../../../matching2/include/th10/platform/sound_fade.hpp#L12) |
| `0x00421F00` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/recovery_leaves.cpp:559](../../../matching2/src/game/recovery_leaves.cpp#L559) |
| `0x00421F60` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/scheduler.cpp:26](../../../matching2/src/game/scheduler.cpp#L26) |
| `0x00421FA0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/score_file.cpp:166](../../../matching2/src/game/score_file.cpp#L166); [matching2/include/th10/game/score_file.hpp:49](../../../matching2/include/th10/game/score_file.hpp#L49) |
| `0x004220E0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/recovery_leaves.cpp:245](../../../matching2/src/game/recovery_leaves.cpp#L245) |
| `0x00422150` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/main_menu_dispatch.cpp:630](../../../matching2/src/game/main_menu_dispatch.cpp#L630); [matching2/src/game/main_menu_dispatch_overlay.cpp:2](../../../matching2/src/game/main_menu_dispatch_overlay.cpp#L2); [matching2/src/game/task_registration.cpp:108](../../../matching2/src/game/task_registration.cpp#L108); [matching2/include/th10/game/task_registration.hpp:45](../../../matching2/include/th10/game/task_registration.hpp#L45) |
| `0x00422220` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/manager_teardown.cpp:91](../../../matching2/src/game/manager_teardown.cpp#L91); [matching2/include/th10/game/manager_teardown.hpp:5](../../../matching2/include/th10/game/manager_teardown.hpp#L5) |
| `0x00422360` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/recovery_leaves.cpp:907](../../../matching2/src/game/recovery_leaves.cpp#L907); [matching2/include/th10/game/stage_entry.hpp:16](../../../matching2/include/th10/game/stage_entry.hpp#L16) |
| `0x004223F0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/main_menu_dispatch.cpp:166](../../../matching2/src/game/main_menu_dispatch.cpp#L166); [matching2/standalone/host_main.cpp:4550](../../../matching2/standalone/host_main.cpp#L4550); [matching2/standalone/host_main.cpp:5508](../../../matching2/standalone/host_main.cpp#L5508) |
| `0x004224C0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/name_entry.cpp:18](../../../matching2/src/game/name_entry.cpp#L18) |
| `0x00422660` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/main_menu_dispatch.cpp:105](../../../matching2/src/game/main_menu_dispatch.cpp#L105); [matching2/src/game/result_menu_draw.cpp:113](../../../matching2/src/game/result_menu_draw.cpp#L113); [matching2/include/th10/game/result_menu_draw.hpp:5](../../../matching2/include/th10/game/result_menu_draw.hpp#L5); [matching2/include/th10/game/result_menu_draw.hpp:77](../../../matching2/include/th10/game/result_menu_draw.hpp#L77) |
| `0x00422A90` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/recovery_leaves.cpp:328](../../../matching2/src/game/recovery_leaves.cpp#L328) |
| `0x00422AB0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/main_menu_dispatch.cpp:186](../../../matching2/src/game/main_menu_dispatch.cpp#L186); [matching2/src/game/pause_result_open.cpp:57](../../../matching2/src/game/pause_result_open.cpp#L57); [matching2/standalone/host_main.cpp:4590](../../../matching2/standalone/host_main.cpp#L4590) |
| `0x00422C30` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/scheduler.cpp:34](../../../matching2/src/game/scheduler.cpp#L34) |
| `0x00422C80` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/main_menu_dispatch.cpp:216](../../../matching2/src/game/main_menu_dispatch.cpp#L216); [matching2/src/game/result_choice_menu.cpp:3](../../../matching2/src/game/result_choice_menu.cpp#L3); [matching2/include/th10/game/result_choice_menu.hpp:7](../../../matching2/include/th10/game/result_choice_menu.hpp#L7); [matching2/standalone/host_main.cpp:5767](../../../matching2/standalone/host_main.cpp#L5767) |
| `0x004231D0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/pause_result_open.cpp:76](../../../matching2/src/game/pause_result_open.cpp#L76) |
| `0x00423370` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/result_menu_open.cpp:18](../../../matching2/src/game/result_menu_open.cpp#L18) |
| `0x00423510` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/recovery_leaves.cpp:571](../../../matching2/src/game/recovery_leaves.cpp#L571) |
| `0x00423570` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/name_entry.cpp:44](../../../matching2/src/game/name_entry.cpp#L44) |
| `0x004236F0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/main_menu_dispatch.cpp:179](../../../matching2/src/game/main_menu_dispatch.cpp#L179); [matching2/src/game/main_menu_dispatch.cpp:231](../../../matching2/src/game/main_menu_dispatch.cpp#L231); [matching2/include/th10/game/main_menu_dispatch.hpp:28](../../../matching2/include/th10/game/main_menu_dispatch.hpp#L28); [matching2/include/th10/game/ui_final_runtime.hpp:9](../../../matching2/include/th10/game/ui_final_runtime.hpp#L9); [matching2/standalone/host_main.cpp:4796](../../../matching2/standalone/host_main.cpp#L4796) |
| `0x004243F0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/recovery_leaves.cpp:924](../../../matching2/src/game/recovery_leaves.cpp#L924) |
| `0x00424480` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/sprite_descriptor.cpp:11](../../../matching2/src/game/sprite_descriptor.cpp#L11) |
| `0x00424650` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/stage_tip_manager.cpp:261](../../../matching2/src/game/stage_tip_manager.cpp#L261) |
| `0x004246C0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/player_reset.cpp:8](../../../matching2/src/game/player_reset.cpp#L8); [matching2/src/game/player_runtime_init.cpp:284](../../../matching2/src/game/player_runtime_init.cpp#L284); [matching2/include/th10/game/player_reset.hpp:7](../../../matching2/include/th10/game/player_reset.hpp#L7) |
| `0x004247F0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/player_runtime_init.cpp:202](../../../matching2/src/game/player_runtime_init.cpp#L202); [matching2/src/game/player_runtime_init.cpp:294](../../../matching2/src/game/player_runtime_init.cpp#L294); [matching2/include/th10/game/player_runtime_init.hpp:65](../../../matching2/include/th10/game/player_runtime_init.hpp#L65) |
| `0x00424D90` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/pause_menu_reset.cpp:24](../../../matching2/src/game/pause_menu_reset.cpp#L24) |
| `0x00424ED0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/manager_teardown.cpp:72](../../../matching2/src/game/manager_teardown.cpp#L72); [matching2/include/th10/game/manager_teardown.hpp:5](../../../matching2/include/th10/game/manager_teardown.hpp#L5) |
| `0x00425020` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/recovery_leaves.cpp:1064](../../../matching2/src/game/recovery_leaves.cpp#L1064); [matching2/include/th10/game/stage_entry.hpp:16](../../../matching2/include/th10/game/stage_entry.hpp#L16); [matching2/standalone/host_stage.cpp:2025](../../../matching2/standalone/host_stage.cpp#L2025) |
| `0x004250B0` | partial | separate_sparse_review | yes / yes / yes | [matching2/src/game/player_front_runtime.cpp:13](../../../matching2/src/game/player_front_runtime.cpp#L13) |
| `0x00425730` | researched | outside_prior_bounded_and_sparse_scopes | yes / yes / yes | [matching2/src/game/gameplay_final_runtime.cpp:810](../../../matching2/src/game/gameplay_final_runtime.cpp#L810); [matching2/include/th10/game/gameplay_final_runtime.hpp:72](../../../matching2/include/th10/game/gameplay_final_runtime.hpp#L72); [matching2/include/th10/game/gameplay_final_runtime.hpp:238](../../../matching2/include/th10/game/gameplay_final_runtime.hpp#L238) |
| `0x00426360` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/player_runtime_init.cpp:167](../../../matching2/src/game/player_runtime_init.cpp#L167); [matching2/src/game/stage_controller_tick.cpp:5](../../../matching2/src/game/stage_controller_tick.cpp#L5) |
| `0x00426520` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/music_room.cpp:13](../../../matching2/src/game/music_room.cpp#L13); [matching2/src/game/music_room_overlay.cpp:2](../../../matching2/src/game/music_room_overlay.cpp#L2) |
| `0x00426610` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/score.cpp:152](../../../matching2/src/game/score.cpp#L152) |
| `0x00426660` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/score.cpp:161](../../../matching2/src/game/score.cpp#L161) |
| `0x004266B0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/item_field_contact.cpp:13](../../../matching2/src/game/item_field_contact.cpp#L13) |
| `0x004267F0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/trigger_region.cpp:6](../../../matching2/src/game/trigger_region.cpp#L6); [matching2/include/th10/game/laser_line.hpp:117](../../../matching2/include/th10/game/laser_line.hpp#L117) |
| `0x004269D0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/spell_timeout.cpp:5](../../../matching2/src/game/spell_timeout.cpp#L5) |
| `0x00426CF0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/trigger_activation.cpp:18](../../../matching2/src/game/trigger_activation.cpp#L18) |
| `0x00426F70` | researched | outside_prior_bounded_and_sparse_scopes | yes / yes / yes | [matching2/include/th10/game/player_runtime_init.hpp:65](../../../matching2/include/th10/game/player_runtime_init.hpp#L65) |
| `0x00427950` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/recovery_leaves.cpp:317](../../../matching2/src/game/recovery_leaves.cpp#L317) |
| `0x00427960` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/stage_background.cpp:46](../../../matching2/src/game/stage_background.cpp#L46) |
| `0x00427AE0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/recovery_leaves.cpp:483](../../../matching2/src/game/recovery_leaves.cpp#L483) |
| `0x00427B50` | semantic | reported_grounded | yes / yes / yes | [matching2/src/game/effect_indicator_slots.cpp:35](../../../matching2/src/game/effect_indicator_slots.cpp#L35); [matching2/include/th10/game/effect_indicator_slots.hpp:31](../../../matching2/include/th10/game/effect_indicator_slots.hpp#L31); [matching2/include/th10/game/gameplay_final_runtime.hpp:72](../../../matching2/include/th10/game/gameplay_final_runtime.hpp#L72) |
| `0x00427C50` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/platform/sound_float_forward.cpp:4](../../../matching2/src/platform/sound_float_forward.cpp#L4) |
| `0x00427C70` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/frame_counter.cpp:3](../../../matching2/src/game/frame_counter.cpp#L3); [matching2/include/th10/game/frame_counter.hpp:5](../../../matching2/include/th10/game/frame_counter.hpp#L5) |
| `0x00427D80` | semantic | reported_grounded | missing / missing / yes | [matching2/src/game/effect_indicator_slots.cpp:73](../../../matching2/src/game/effect_indicator_slots.cpp#L73); [matching2/include/th10/game/effect_indicator_slots.hpp:51](../../../matching2/include/th10/game/effect_indicator_slots.hpp#L51) |
| `0x00427E90` | semantic | reported_grounded | yes / yes / yes | [matching2/src/game/effect_indicator_slots.cpp:82](../../../matching2/src/game/effect_indicator_slots.cpp#L82); [matching2/include/th10/game/effect_indicator_slots.hpp:121](../../../matching2/include/th10/game/effect_indicator_slots.hpp#L121) |
| `0x00428160` | semantic | reported_partial | yes / yes / yes | [matching2/src/game/effect_indicator_slots.cpp:82](../../../matching2/src/game/effect_indicator_slots.cpp#L82); [matching2/src/game/recovery_leaves.cpp:691](../../../matching2/src/game/recovery_leaves.cpp#L691) |
| `0x004281D0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/recovery_leaves.cpp:1092](../../../matching2/src/game/recovery_leaves.cpp#L1092) |
| `0x00428280` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/effect_pool_update.cpp:3](../../../matching2/src/game/effect_pool_update.cpp#L3); [matching2/include/th10/game/effect_pool_update.hpp:7](../../../matching2/include/th10/game/effect_pool_update.hpp#L7) |
| `0x00428630` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/player_pickup_sweep.cpp:58](../../../matching2/src/game/player_pickup_sweep.cpp#L58); [matching2/include/th10/game/player_pickup_sweep.hpp:4](../../../matching2/include/th10/game/player_pickup_sweep.hpp#L4); [matching2/include/th10/game/player_pickup_sweep.hpp:65](../../../matching2/include/th10/game/player_pickup_sweep.hpp#L65) |
| `0x00428C20` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/boss_gauge.cpp:26](../../../matching2/src/game/boss_gauge.cpp#L26); [matching2/include/th10/game/boss_gauge.hpp:29](../../../matching2/include/th10/game/boss_gauge.hpp#L29) |
| `0x00428D70` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/score.cpp:589](../../../matching2/src/game/score.cpp#L589); [matching2/src/game/score.cpp:614](../../../matching2/src/game/score.cpp#L614) |
| `0x00428DD0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/math/timer.cpp:26](../../../matching2/src/math/timer.cpp#L26); [matching2/src/math/timer.cpp:38](../../../matching2/src/math/timer.cpp#L38) |
| `0x00428E10` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/boss_gauge.cpp:45](../../../matching2/src/game/boss_gauge.cpp#L45); [matching2/include/th10/game/boss_gauge.hpp:37](../../../matching2/include/th10/game/boss_gauge.hpp#L37) |
| `0x00428F60` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/replay_runtime_bootstrap.cpp:4](../../../matching2/src/game/replay_runtime_bootstrap.cpp#L4); [matching2/include/th10/game/replay_runtime_bootstrap.hpp:7](../../../matching2/include/th10/game/replay_runtime_bootstrap.hpp#L7) |
| `0x004294A0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/manager_teardown.cpp:146](../../../matching2/src/game/manager_teardown.cpp#L146); [matching2/include/th10/game/manager_teardown.hpp:4](../../../matching2/include/th10/game/manager_teardown.hpp#L4) |
| `0x00429610` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/manager_factories.cpp:420](../../../matching2/src/game/manager_factories.cpp#L420) |
| `0x004296F0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/manager_factories.cpp:220](../../../matching2/src/game/manager_factories.cpp#L220) |
| `0x004297B0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/recovery_leaves.cpp:388](../../../matching2/src/game/recovery_leaves.cpp#L388) |
| `0x004297D0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/input_recorder.cpp:15](../../../matching2/src/game/input_recorder.cpp#L15) |
| `0x00429B60` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/replay_large_runtime.cpp:6](../../../matching2/src/game/replay_large_runtime.cpp#L6) |
| `0x0042A200` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/replay_file_load.cpp:6](../../../matching2/src/game/replay_file_load.cpp#L6) |
| `0x0042A450` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/slot_snapshot.cpp:1](../../../matching2/src/game/slot_snapshot.cpp#L1); [matching2/include/th10/game/slot_snapshot.hpp:3](../../../matching2/include/th10/game/slot_snapshot.hpp#L3); [matching2/include/th10/game/slot_snapshot.hpp:69](../../../matching2/include/th10/game/slot_snapshot.hpp#L69) |
| `0x0042A6A0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/spell_card_dispatch.cpp:11](../../../matching2/src/game/spell_card_dispatch.cpp#L11) |
| `0x0042A8A0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/recovery_leaves.cpp:878](../../../matching2/src/game/recovery_leaves.cpp#L878) |
| `0x0042A930` | semantic | reported_grounded | yes / yes / yes | [matching2/src/game/effect_indicator_slots.cpp:17](../../../matching2/src/game/effect_indicator_slots.cpp#L17); [matching2/include/th10/game/effect_indicator_slots.hpp:44](../../../matching2/include/th10/game/effect_indicator_slots.hpp#L44) |
| `0x0042AA50` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/linked_pool_append.cpp:6](../../../matching2/src/game/linked_pool_append.cpp#L6); [matching2/include/th10/game/linked_pool_append.hpp:35](../../../matching2/include/th10/game/linked_pool_append.hpp#L35) |
| `0x0042AB20` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/linked_pool_release.cpp:1](../../../matching2/src/game/linked_pool_release.cpp#L1); [matching2/src/game/linked_pool_release.cpp:2](../../../matching2/src/game/linked_pool_release.cpp#L2); [matching2/include/th10/game/linked_pool_release.hpp:1](../../../matching2/include/th10/game/linked_pool_release.hpp#L1); [matching2/include/th10/game/linked_pool_release.hpp:2](../../../matching2/include/th10/game/linked_pool_release.hpp#L2) |
| `0x0042ACB0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/score_file.cpp:130](../../../matching2/src/game/score_file.cpp#L130); [matching2/include/th10/game/score_file.hpp:43](../../../matching2/include/th10/game/score_file.hpp#L43) |
| `0x0042ADD0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/recovery_leaves.cpp:892](../../../matching2/src/game/recovery_leaves.cpp#L892) |
| `0x0042AE60` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/manager_factories.cpp:247](../../../matching2/src/game/manager_factories.cpp#L247) |
| `0x0042AF20` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/score_tasks.cpp:42](../../../matching2/src/game/score_tasks.cpp#L42) |
| `0x0042B030` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/score_file.cpp:72](../../../matching2/src/game/score_file.cpp#L72); [matching2/include/th10/game/score_file.hpp:36](../../../matching2/include/th10/game/score_file.hpp#L36) |
| `0x0042B1E0` | semantic | reported_partial | yes / yes / yes | [matching2/src/archive/score_save.cpp:211](../../../matching2/src/archive/score_save.cpp#L211); [matching2/include/th10/archive/score_save.hpp:3](../../../matching2/include/th10/archive/score_save.hpp#L3) |
| `0x0042B430` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/pool_constructors.cpp:194](../../../matching2/src/game/pool_constructors.cpp#L194); [matching2/include/th10/game/pool_constructors.hpp:11](../../../matching2/include/th10/game/pool_constructors.hpp#L11) |
| `0x0042B4D0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/manager_factories.cpp:295](../../../matching2/src/game/manager_factories.cpp#L295); [matching2/src/game/pool_constructors.cpp:207](../../../matching2/src/game/pool_constructors.cpp#L207) |
| `0x0042B570` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/effect_manager_destroy.cpp:31](../../../matching2/src/game/effect_manager_destroy.cpp#L31); [matching2/include/th10/game/effect_manager_destroy.hpp:12](../../../matching2/include/th10/game/effect_manager_destroy.hpp#L12) |
| `0x0042B660` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/recovery_leaves.cpp:1072](../../../matching2/src/game/recovery_leaves.cpp#L1072) |
| `0x0042B6F0` | semantic | pending_bounded_review | missing / missing / yes | [matching2/src/game/weather_pool.cpp:4](../../../matching2/src/game/weather_pool.cpp#L4) |
| `0x0042B780` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/floating_text_draw.cpp:34](../../../matching2/src/game/floating_text_draw.cpp#L34); [matching2/include/th10/game/floating_text_draw.hpp:4](../../../matching2/include/th10/game/floating_text_draw.hpp#L4) |
| `0x0042B9C0` | semantic | separate_sparse_review | yes / yes / yes | [matching2/src/game/score_popup.cpp:3](../../../matching2/src/game/score_popup.cpp#L3) |
| `0x0042C360` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/sprite_test_overlay.cpp:19](../../../matching2/src/game/sprite_test_overlay.cpp#L19) |
| `0x0042C5C0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/score_timer_leaves.cpp:8](../../../matching2/src/game/score_timer_leaves.cpp#L8); [matching2/src/math/timer.cpp:61](../../../matching2/src/math/timer.cpp#L61) |
| `0x0042C620` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/math/timer.cpp:44](../../../matching2/src/math/timer.cpp#L44) |
| `0x0042C670` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/recovery_leaves.cpp:601](../../../matching2/src/game/recovery_leaves.cpp#L601) |
| `0x0042C6D0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/recovery_leaves.cpp:617](../../../matching2/src/game/recovery_leaves.cpp#L617) |
| `0x0042C730` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/scheduler.cpp:50](../../../matching2/src/game/scheduler.cpp#L50) |
| `0x0042C750` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/scheduler.cpp:59](../../../matching2/src/game/scheduler.cpp#L59) |
| `0x0042C770` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/render/anm_propagate.cpp:30](../../../matching2/src/render/anm_propagate.cpp#L30); [matching2/include/th10/render/anm_propagate.hpp:30](../../../matching2/include/th10/render/anm_propagate.hpp#L30) |
| `0x0042C850` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/progress.cpp:12](../../../matching2/src/game/progress.cpp#L12) |
| `0x0042C8C0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/progress.cpp:22](../../../matching2/src/game/progress.cpp#L22) |
| `0x0042C920` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/pool_constructors.cpp:267](../../../matching2/src/game/pool_constructors.cpp#L267); [matching2/include/th10/game/pool_constructors.hpp:19](../../../matching2/include/th10/game/pool_constructors.hpp#L19) |
| `0x0042CAA0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/task_registration.cpp:233](../../../matching2/src/game/task_registration.cpp#L233); [matching2/include/th10/game/task_registration.hpp:102](../../../matching2/include/th10/game/task_registration.hpp#L102) |
| `0x0042CB60` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/manager_teardown.cpp:172](../../../matching2/src/game/manager_teardown.cpp#L172); [matching2/include/th10/game/manager_teardown.hpp:4](../../../matching2/include/th10/game/manager_teardown.hpp#L4) |
| `0x0042CD50` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/progress_worker.cpp:6](../../../matching2/src/game/progress_worker.cpp#L6); [matching2/include/th10/game/progress_worker.hpp:5](../../../matching2/include/th10/game/progress_worker.hpp#L5) |
| `0x0042CDB0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/util/heap.cpp:55](../../../matching2/src/util/heap.cpp#L55) |
| `0x0042CDF0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/title_menu_runtime.cpp:3](../../../matching2/src/game/title_menu_runtime.cpp#L3); [matching2/include/th10/game/title_menu_runtime.hpp:8](../../../matching2/include/th10/game/title_menu_runtime.hpp#L8) |
| `0x0042D300` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/ending_screen.cpp:13](../../../matching2/src/game/ending_screen.cpp#L13) |
| `0x0042D420` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/title_main_menu.cpp:81](../../../matching2/src/game/title_main_menu.cpp#L81); [matching2/src/game/title_options_menu.cpp:89](../../../matching2/src/game/title_options_menu.cpp#L89) |
| `0x0042D920` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/title_options_menu.cpp:8](../../../matching2/src/game/title_options_menu.cpp#L8) |
| `0x0042E5A0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/ui_final_runtime.cpp:1055](../../../matching2/src/game/ui_final_runtime.cpp#L1055); [matching2/include/th10/game/ui_final_runtime.hpp:9](../../../matching2/include/th10/game/ui_final_runtime.hpp#L9) |
| `0x0042F540` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/menu_flow_updates.cpp:29](../../../matching2/src/game/menu_flow_updates.cpp#L29); [matching2/include/th10/game/menu_flow_updates.hpp:40](../../../matching2/include/th10/game/menu_flow_updates.hpp#L40) |
| `0x0042F8B0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/ui_final_runtime.cpp:1141](../../../matching2/src/game/ui_final_runtime.cpp#L1141); [matching2/include/th10/game/ui_final_runtime.hpp:9](../../../matching2/include/th10/game/ui_final_runtime.hpp#L9) |
| `0x00430250` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/key_config.cpp:12](../../../matching2/src/game/key_config.cpp#L12); [matching2/src/game/key_config_overlay.cpp:2](../../../matching2/src/game/key_config_overlay.cpp#L2) |
| `0x00430320` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/menu_flow_updates.cpp:99](../../../matching2/src/game/menu_flow_updates.cpp#L99); [matching2/include/th10/game/menu_flow_updates.hpp:51](../../../matching2/include/th10/game/menu_flow_updates.hpp#L51) |
| `0x004306A0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/menu_flow_updates.cpp:154](../../../matching2/src/game/menu_flow_updates.cpp#L154); [matching2/include/th10/game/menu_flow_updates.hpp:62](../../../matching2/include/th10/game/menu_flow_updates.hpp#L62) |
| `0x00430A60` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/shot_practice_menu.cpp:3](../../../matching2/src/game/shot_practice_menu.cpp#L3); [matching2/include/th10/game/shot_practice_menu.hpp:6](../../../matching2/include/th10/game/shot_practice_menu.hpp#L6) |
| `0x00430FF0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/practice_stage_menu.cpp:20](../../../matching2/src/game/practice_stage_menu.cpp#L20); [matching2/include/th10/game/practice_stage_menu.hpp:46](../../../matching2/include/th10/game/practice_stage_menu.hpp#L46) |
| `0x00431410` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/score_menu_rows.cpp:30](../../../matching2/src/game/score_menu_rows.cpp#L30); [matching2/include/th10/game/score_menu_rows.hpp:4](../../../matching2/include/th10/game/score_menu_rows.hpp#L4) |
| `0x004315C0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/replay_menu_runtime.cpp:10](../../../matching2/src/game/replay_menu_runtime.cpp#L10) |
| `0x00431BA0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/replay_browser_draw.cpp:5](../../../matching2/src/game/replay_browser_draw.cpp#L5) |
| `0x00431EE0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/replay_large_runtime.cpp:10](../../../matching2/src/game/replay_large_runtime.cpp#L10) |
| `0x00432690` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/replay_spell_list.cpp:16](../../../matching2/src/game/replay_spell_list.cpp#L16); [matching2/include/th10/game/replay_spell_list.hpp:26](../../../matching2/include/th10/game/replay_spell_list.hpp#L26) |
| `0x004329F0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/replay_score_draw.cpp:7](../../../matching2/src/game/replay_score_draw.cpp#L7) |
| `0x00432CB0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/name_entry.cpp:97](../../../matching2/src/game/name_entry.cpp#L97); [matching2/include/th10/game/name_entry.hpp:61](../../../matching2/include/th10/game/name_entry.hpp#L61) |
| `0x00433230` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/replay_stage_name_draw.cpp:6](../../../matching2/src/game/replay_stage_name_draw.cpp#L6) |
| `0x00433570` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/replay_menu_runtime.cpp:25](../../../matching2/src/game/replay_menu_runtime.cpp#L25) |
| `0x00433B30` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/replay_menu_draw.cpp:80](../../../matching2/src/game/replay_menu_draw.cpp#L80); [matching2/include/th10/game/replay_menu_draw.hpp:4](../../../matching2/include/th10/game/replay_menu_draw.hpp#L4); [matching2/include/th10/game/replay_menu_draw.hpp:45](../../../matching2/include/th10/game/replay_menu_draw.hpp#L45) |
| `0x00433EF0` | researched | outside_prior_bounded_and_sparse_scopes | yes / yes / yes | [matching2/include/th10/game/ui_final_runtime.hpp:9](../../../matching2/include/th10/game/ui_final_runtime.hpp#L9) |
| `0x004349E0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/stage_text.cpp:4](../../../matching2/src/game/stage_text.cpp#L4) |
| `0x00434A20` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/stage_text.cpp:18](../../../matching2/src/game/stage_text.cpp#L18) |
| `0x00434A80` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/stage_text.cpp:36](../../../matching2/src/game/stage_text.cpp#L36); [matching2/src/render/animation_manager.cpp:972](../../../matching2/src/render/animation_manager.cpp#L972) |
| `0x00434C20` | semantic | reported_grounded | yes / yes / yes | [matching2/src/archive/dat.cpp:123](../../../matching2/src/archive/dat.cpp#L123) |
| `0x00434C30` | semantic | reported_partial | yes / yes / yes | [matching2/src/archive/dat.cpp:145](../../../matching2/src/archive/dat.cpp#L145); [matching2/src/archive/dat_file.cpp:6](../../../matching2/src/archive/dat_file.cpp#L6) |
| `0x00434CA0` | semantic | reported_partial | missing / missing / yes | [matching2/src/archive/dat_file.cpp:15](../../../matching2/src/archive/dat_file.cpp#L15) |
| `0x00434D10` | semantic | reported_grounded | yes / yes / yes | [matching2/src/archive/dat.cpp:128](../../../matching2/src/archive/dat.cpp#L128) |
| `0x00434DD0` | semantic | reported_grounded | yes / yes / yes | [matching2/src/archive/dat.cpp:166](../../../matching2/src/archive/dat.cpp#L166) |
| `0x00434EF0` | semantic | reported_grounded | yes / yes / yes | [matching2/src/archive/dat.cpp:219](../../../matching2/src/archive/dat.cpp#L219) |
| `0x00434F30` | semantic | reported_grounded | yes / yes / yes | [matching2/src/archive/dat.cpp:201](../../../matching2/src/archive/dat.cpp#L201) |
| `0x00434F70` | semantic | reported_partial | yes / yes / yes | [matching2/src/archive/dat.cpp:45](../../../matching2/src/archive/dat.cpp#L45) |
| `0x004350D0` | semantic | reported_partial | yes / yes / yes | [matching2/src/archive/dat.cpp:280](../../../matching2/src/archive/dat.cpp#L280) |
| `0x00435220` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/util/heap.cpp:76](../../../matching2/src/util/heap.cpp#L76) |
| `0x00435250` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/util/heap.cpp:35](../../../matching2/src/util/heap.cpp#L35) |
| `0x004352C0` | semantic | reference_unresolved | missing / missing / missing | [matching2/src/util/heap.cpp:15](../../../matching2/src/util/heap.cpp#L15) |
| `0x00435320` | unrecovered | outside_prior_bounded_and_sparse_scopes | yes / yes / yes | none; inspect references |
| `0x00435340` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/platform/file.cpp:39](../../../matching2/src/platform/file.cpp#L39) |
| `0x00435370` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/platform/file.cpp:234](../../../matching2/src/platform/file.cpp#L234) |
| `0x00435460` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/platform/file.cpp:284](../../../matching2/src/platform/file.cpp#L284) |
| `0x00435490` | semantic | pending_bounded_review | yes / yes / missing | [matching2/src/platform/file.cpp:293](../../../matching2/src/platform/file.cpp#L293) |
| `0x004354D0` | semantic | pending_bounded_review | yes / yes / missing | [matching2/src/platform/file.cpp:303](../../../matching2/src/platform/file.cpp#L303) |
| `0x00435510` | semantic | pending_bounded_review | yes / yes / missing | [matching2/src/platform/file.cpp:313](../../../matching2/src/platform/file.cpp#L313) |
| `0x00435530` | semantic | pending_bounded_review | yes / yes / missing | [matching2/src/platform/file.cpp:321](../../../matching2/src/platform/file.cpp#L321) |
| `0x00435550` | semantic | pending_bounded_review | yes / yes / missing | [matching2/src/platform/file.cpp:329](../../../matching2/src/platform/file.cpp#L329) |
| `0x00435580` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/platform/file.cpp:338](../../../matching2/src/platform/file.cpp#L338) |
| `0x00435610` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/platform/file.cpp:44](../../../matching2/src/platform/file.cpp#L44) |
| `0x00435690` | unrecovered | outside_prior_bounded_and_sparse_scopes | yes / yes / missing | none; inspect references |
| `0x004356A0` | unrecovered | outside_prior_bounded_and_sparse_scopes | yes / yes / missing | none; inspect references |
| `0x004356F0` | semantic | reported_partial | yes / yes / yes | [matching2/src/archive/resource_manager.cpp:22](../../../matching2/src/archive/resource_manager.cpp#L22) |
| `0x00435800` | semantic | reported_partial | yes / yes / yes | [matching2/src/archive/resource_manager.cpp:56](../../../matching2/src/archive/resource_manager.cpp#L56) |
| `0x004358E0` | semantic | reported_partial | yes / yes / yes | [matching2/src/archive/resource_manager.cpp:72](../../../matching2/src/archive/resource_manager.cpp#L72) |
| `0x004359B0` | semantic | reported_grounded | yes / yes / yes | [matching2/src/archive/score_save.cpp:113](../../../matching2/src/archive/score_save.cpp#L113); [matching2/include/th10/archive/score_save.hpp:3](../../../matching2/include/th10/archive/score_save.hpp#L3); [matching2/include/th10/archive/score_save.hpp:32](../../../matching2/include/th10/archive/score_save.hpp#L32) |
| `0x00435DC0` | semantic | reported_grounded | yes / yes / yes | [matching2/src/archive/lzss.cpp:150](../../../matching2/src/archive/lzss.cpp#L150) |
| `0x00436000` | semantic | reported_grounded | yes / yes / yes | [matching2/src/archive/score_save.cpp:24](../../../matching2/src/archive/score_save.cpp#L24); [matching2/include/th10/archive/score_save.hpp:3](../../../matching2/include/th10/archive/score_save.hpp#L3); [matching2/include/th10/archive/score_save.hpp:28](../../../matching2/include/th10/archive/score_save.hpp#L28) |
| `0x00436210` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/platform/memory_file.cpp:79](../../../matching2/src/platform/memory_file.cpp#L79) |
| `0x00436260` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/platform/memory_file.cpp:41](../../../matching2/src/platform/memory_file.cpp#L41) |
| `0x004362B0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/platform/memory_file.cpp:53](../../../matching2/src/platform/memory_file.cpp#L53) |
| `0x00436330` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/platform/memory_file.cpp:67](../../../matching2/src/platform/memory_file.cpp#L67) |
| `0x00436370` | semantic | reference_unresolved | yes / yes / missing | [matching2/src/platform/memory_file.cpp:162](../../../matching2/src/platform/memory_file.cpp#L162) |
| `0x004363A0` | unrecovered | outside_prior_bounded_and_sparse_scopes | yes / yes / yes | none; inspect references |
| `0x004363C0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/platform/memory_file.cpp:121](../../../matching2/src/platform/memory_file.cpp#L121) |
| `0x00436430` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/platform/memory_file.cpp:135](../../../matching2/src/platform/memory_file.cpp#L135) |
| `0x00436460` | semantic | reference_unresolved | yes / yes / missing | [matching2/src/platform/memory_file.cpp:146](../../../matching2/src/platform/memory_file.cpp#L146) |
| `0x004364D0` | semantic | reference_unresolved | yes / yes / missing | [matching2/src/platform/memory_file.cpp:167](../../../matching2/src/platform/memory_file.cpp#L167) |
| `0x004364E0` | semantic | reference_unresolved | yes / yes / missing | [matching2/src/platform/memory_file.cpp:172](../../../matching2/src/platform/memory_file.cpp#L172) |
| `0x00436570` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/platform/process.cpp:4](../../../matching2/src/platform/process.cpp#L4) |
| `0x00436660` | unrecovered | outside_prior_bounded_and_sparse_scopes | yes / yes / yes | none; inspect references |
| `0x00436680` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/platform/resource_file.cpp:27](../../../matching2/src/platform/resource_file.cpp#L27) |
| `0x004366C0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/platform/resource_file.cpp:33](../../../matching2/src/platform/resource_file.cpp#L33) |
| `0x00436A30` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/platform/gdi_font_cache.cpp:7](../../../matching2/src/platform/gdi_font_cache.cpp#L7); [matching2/src/platform/memory_file.cpp:103](../../../matching2/src/platform/memory_file.cpp#L103) |
| `0x00436AF0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/platform/gdi_surface.cpp:18](../../../matching2/src/platform/gdi_surface.cpp#L18) |
| `0x00436CA0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/platform/resource_file.cpp:18](../../../matching2/src/platform/resource_file.cpp#L18) |
| `0x00436DA0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/render/transparent_pixel_fill.cpp:15](../../../matching2/src/render/transparent_pixel_fill.cpp#L15) |
| `0x00437160` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/render/image_alpha_transform.cpp:5](../../../matching2/src/render/image_alpha_transform.cpp#L5) |
| `0x00437750` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/platform/font_surface_blend.cpp:12](../../../matching2/src/platform/font_surface_blend.cpp#L12) |
| `0x00437A00` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/platform/font_cache_init.cpp:4](../../../matching2/src/platform/font_cache_init.cpp#L4) |
| `0x00437D10` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/platform/gdi_font_cache.cpp:11](../../../matching2/src/platform/gdi_font_cache.cpp#L11); [matching2/include/th10/platform/gdi_font_cache.hpp:3](../../../matching2/include/th10/platform/gdi_font_cache.hpp#L3) |
| `0x00437DB0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/platform/font_texture_draw.cpp:42](../../../matching2/src/platform/font_texture_draw.cpp#L42); [matching2/include/th10/platform/font_texture_draw.hpp:24](../../../matching2/include/th10/platform/font_texture_draw.hpp#L24) |
| `0x00437FE0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/platform/font_texture_draw.cpp:50](../../../matching2/src/platform/font_texture_draw.cpp#L50); [matching2/include/th10/platform/font_texture_draw.hpp:29](../../../matching2/include/th10/platform/font_texture_draw.hpp#L29) |
| `0x004381F0` | semantic | reference_unresolved | missing / missing / yes | [matching2/src/util/heap.cpp:66](../../../matching2/src/util/heap.cpp#L66) |
| `0x00438250` | semantic | reference_unresolved | yes / yes / missing | [matching2/src/util/heap.cpp:226](../../../matching2/src/util/heap.cpp#L226) |
| `0x00438260` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/util/heap.cpp:151](../../../matching2/src/util/heap.cpp#L151) |
| `0x00438350` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/util/heap.cpp:90](../../../matching2/src/util/heap.cpp#L90); [matching2/src/util/heap.cpp:91](../../../matching2/src/util/heap.cpp#L91) |
| `0x00438380` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/util/heap.cpp:232](../../../matching2/src/util/heap.cpp#L232) |
| `0x00438420` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/util/heap.cpp:102](../../../matching2/src/util/heap.cpp#L102); [matching2/src/util/heap.cpp:104](../../../matching2/src/util/heap.cpp#L104) |
| `0x00438510` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/util/heap.cpp:197](../../../matching2/src/util/heap.cpp#L197); [matching2/src/util/heap.cpp:198](../../../matching2/src/util/heap.cpp#L198) |
| `0x00438590` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/util/heap.cpp:215](../../../matching2/src/util/heap.cpp#L215); [matching2/src/util/heap.cpp:216](../../../matching2/src/util/heap.cpp#L216) |
| `0x00438680` | semantic | reference_unresolved | missing / missing / missing | [matching2/src/util/heap.cpp:269](../../../matching2/src/util/heap.cpp#L269) |
| `0x00438690` | semantic | reference_unresolved | missing / missing / missing | [matching2/src/util/heap.cpp:24](../../../matching2/src/util/heap.cpp#L24) |
| `0x004386A0` | semantic | reference_unresolved | yes / yes / missing | [matching2/src/util/heap.cpp:30](../../../matching2/src/util/heap.cpp#L30) |
| `0x004386B0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/util/heap.cpp:285](../../../matching2/src/util/heap.cpp#L285) |
| `0x00438723` | semantic | pending_bounded_review | missing / missing / yes | [matching2/src/util/legacy_string_funclets.cpp:3](../../../matching2/src/util/legacy_string_funclets.cpp#L3) |
| `0x0043874C` | semantic | reference_unresolved | missing / missing / yes | [matching2/src/util/heap.cpp:287](../../../matching2/src/util/heap.cpp#L287) |
| `0x004387C2` | semantic | pending_bounded_review | missing / missing / yes | [matching2/src/util/legacy_string_funclets.cpp:13](../../../matching2/src/util/legacy_string_funclets.cpp#L13) |
| `0x00438800` | semantic | reference_unresolved | missing / missing / missing | [matching2/src/util/heap.cpp:261](../../../matching2/src/util/heap.cpp#L261) |
| `0x00438840` | semantic | reference_unresolved | missing / missing / missing | [matching2/src/util/heap.cpp:19](../../../matching2/src/util/heap.cpp#L19) |
| `0x00438880` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/render/d3d_resource_manager.cpp:53](../../../matching2/src/render/d3d_resource_manager.cpp#L53) |
| `0x004388F0` | semantic | pending_bounded_review | missing / missing / missing | [matching2/src/util/runtime_pool.cpp:5](../../../matching2/src/util/runtime_pool.cpp#L5) |
| `0x00438A30` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/entity.cpp:3](../../../matching2/src/game/entity.cpp#L3); [matching2/src/game/entity.cpp:222](../../../matching2/src/game/entity.cpp#L222) |
| `0x00438A60` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/render/game_render_targets.cpp:126](../../../matching2/src/render/game_render_targets.cpp#L126) |
| `0x00438AD0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/app/game_main.cpp:23](../../../matching2/src/app/game_main.cpp#L23); [matching2/src/platform/window.cpp:187](../../../matching2/src/platform/window.cpp#L187); [matching2/src/platform/window.cpp:351](../../../matching2/src/platform/window.cpp#L351); [matching2/src/platform/window.cpp:360](../../../matching2/src/platform/window.cpp#L360); [matching2/src/platform/window.cpp:387](../../../matching2/src/platform/window.cpp#L387); [matching2/include/th10/app/game_main.hpp:3](../../../matching2/include/th10/app/game_main.hpp#L3); [matching2/include/th10/app/game_main.hpp:59](../../../matching2/include/th10/app/game_main.hpp#L59); [matching2/standalone/host_main.cpp:168](../../../matching2/standalone/host_main.cpp#L168); [matching2/standalone/host_main.cpp:5815](../../../matching2/standalone/host_main.cpp#L5815); [matching2/standalone/host_main.cpp:5836](../../../matching2/standalone/host_main.cpp#L5836); [matching2/standalone/host_main.cpp:5853](../../../matching2/standalone/host_main.cpp#L5853); [matching2/standalone/host_stage.cpp:145](../../../matching2/standalone/host_stage.cpp#L145) |
| `0x004390E0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/platform/window.cpp:3](../../../matching2/src/platform/window.cpp#L3); [matching2/src/platform/window.cpp:210](../../../matching2/src/platform/window.cpp#L210) |
| `0x004391F0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/render/device_reset.cpp:32](../../../matching2/src/render/device_reset.cpp#L32) |
| `0x004392E0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/platform/window.cpp:4](../../../matching2/src/platform/window.cpp#L4); [matching2/src/platform/window.cpp:159](../../../matching2/src/platform/window.cpp#L159) |
| `0x00439390` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/app/frame_clock.cpp:36](../../../matching2/src/app/frame_clock.cpp#L36); [matching2/src/platform/window.cpp:76](../../../matching2/src/platform/window.cpp#L76); [matching2/src/platform/window.cpp:315](../../../matching2/src/platform/window.cpp#L315); [matching2/include/th10/app/frame_clock.hpp:3](../../../matching2/include/th10/app/frame_clock.hpp#L3); [matching2/include/th10/app/game_main.hpp:4](../../../matching2/include/th10/app/game_main.hpp#L4); [matching2/standalone/host_main.cpp:5779](../../../matching2/standalone/host_main.cpp#L5779); [matching2/standalone/host_main.cpp:6468](../../../matching2/standalone/host_main.cpp#L6468); [matching2/standalone/host_main.cpp:6616](../../../matching2/standalone/host_main.cpp#L6616); [matching2/standalone/host_main.cpp:6639](../../../matching2/standalone/host_main.cpp#L6639) |
| `0x00439540` | semantic | reported_grounded | yes / yes / yes | [matching2/src/app/frame_clock.cpp:6](../../../matching2/src/app/frame_clock.cpp#L6); [matching2/src/app/frame_clock.cpp:19](../../../matching2/src/app/frame_clock.cpp#L19); [matching2/include/th10/app/frame_clock.hpp:3](../../../matching2/include/th10/app/frame_clock.hpp#L3); [matching2/include/th10/app/game_main.hpp:3](../../../matching2/include/th10/app/game_main.hpp#L3); [matching2/standalone/host_main.cpp:5377](../../../matching2/standalone/host_main.cpp#L5377); [matching2/standalone/host_main.cpp:5396](../../../matching2/standalone/host_main.cpp#L5396) |
| `0x00439730` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/platform/window.cpp:3](../../../matching2/src/platform/window.cpp#L3); [matching2/src/platform/window.cpp:259](../../../matching2/src/platform/window.cpp#L259) |
| `0x00439890` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/render/d3d_init.cpp:3](../../../matching2/src/render/d3d_init.cpp#L3); [matching2/src/render/d3d_init.cpp:67](../../../matching2/src/render/d3d_init.cpp#L67) |
| `0x00439D20` | semantic | reported_grounded | yes / yes / yes | [matching2/src/app/frame_clock.cpp:87](../../../matching2/src/app/frame_clock.cpp#L87); [matching2/include/th10/app/frame_clock.hpp:3](../../../matching2/include/th10/app/frame_clock.hpp#L3); [matching2/include/th10/app/game_main.hpp:4](../../../matching2/include/th10/app/game_main.hpp#L4); [matching2/standalone/host_main.cpp:1950](../../../matching2/standalone/host_main.cpp#L1950); [matching2/standalone/host_main.cpp:4261](../../../matching2/standalone/host_main.cpp#L4261) |
| `0x00439FF0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/platform/window.cpp:4](../../../matching2/src/platform/window.cpp#L4); [matching2/src/platform/window.cpp:559](../../../matching2/src/platform/window.cpp#L559) |
| `0x0043A1C0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/platform/pack_file_loader.cpp:82](../../../matching2/src/platform/pack_file_loader.cpp#L82) |
| `0x0043A290` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/platform/window.cpp:509](../../../matching2/src/platform/window.cpp#L509) |
| `0x0043A730` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/platform/midi_sequencer.cpp:32](../../../matching2/src/platform/midi_sequencer.cpp#L32); [matching2/src/platform/midi_sequencer.cpp:52](../../../matching2/src/platform/midi_sequencer.cpp#L52); [matching2/include/th10/platform/midi_sequencer.hpp:31](../../../matching2/include/th10/platform/midi_sequencer.hpp#L31) |
| `0x0043A910` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/platform/sound_commands.cpp:111](../../../matching2/src/platform/sound_commands.cpp#L111); [matching2/include/th10/platform/sound_commands.hpp:4](../../../matching2/include/th10/platform/sound_commands.hpp#L4) |
| `0x0043AA60` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/platform/window.cpp:426](../../../matching2/src/platform/window.cpp#L426) |
| `0x0043AAD0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/platform/midi_sequencer.cpp:70](../../../matching2/src/platform/midi_sequencer.cpp#L70); [matching2/include/th10/platform/midi_sequencer.hpp:65](../../../matching2/include/th10/platform/midi_sequencer.hpp#L65) |
| `0x0043ACE0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/platform/midi_sequencer.cpp:46](../../../matching2/src/platform/midi_sequencer.cpp#L46); [matching2/include/th10/platform/midi_sequencer.hpp:35](../../../matching2/include/th10/platform/midi_sequencer.hpp#L35) |
| `0x0043AE20` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/platform/window.cpp:477](../../../matching2/src/platform/window.cpp#L477) |
| `0x0043AEB0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/platform/window.cpp:450](../../../matching2/src/platform/window.cpp#L450) |
| `0x0043AF30` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/platform/midi_sequencer.cpp:125](../../../matching2/src/platform/midi_sequencer.cpp#L125); [matching2/include/th10/platform/midi_sequencer.hpp:99](../../../matching2/include/th10/platform/midi_sequencer.hpp#L99) |
| `0x0043B110` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/platform/midi_event_runtime.cpp:4](../../../matching2/src/platform/midi_event_runtime.cpp#L4) |
| `0x0043B7A0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/platform/midi_worker.cpp:45](../../../matching2/src/platform/midi_worker.cpp#L45) |
| `0x0043B8D0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/platform/dinput_device_setup.cpp:19](../../../matching2/src/platform/dinput_device_setup.cpp#L19); [matching2/include/th10/platform/dinput_device_setup.hpp:4](../../../matching2/include/th10/platform/dinput_device_setup.hpp#L4) |
| `0x0043BC40` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/recovery_leaves.cpp:1082](../../../matching2/src/game/recovery_leaves.cpp#L1082) |
| `0x0043BCD0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/render/camera_setup.cpp:23](../../../matching2/src/render/camera_setup.cpp#L23); [matching2/src/render/camera_setup.cpp:27](../../../matching2/src/render/camera_setup.cpp#L27); [matching2/include/th10/render/camera_setup.hpp:3](../../../matching2/include/th10/render/camera_setup.hpp#L3) |
| `0x0043BDA0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/render/special_quad.cpp:11](../../../matching2/src/render/special_quad.cpp#L11) |
| `0x0043BFA0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/render/texture_stage_reset.cpp:17](../../../matching2/src/render/texture_stage_reset.cpp#L17) |
| `0x0043C1A0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/render/default_viewport.cpp:13](../../../matching2/src/render/default_viewport.cpp#L13) |
| `0x0043C2C0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/ascii_overlay_callbacks.cpp:52](../../../matching2/src/game/ascii_overlay_callbacks.cpp#L52) |
| `0x0043C410` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/ascii_overlay_callbacks.cpp:45](../../../matching2/src/game/ascii_overlay_callbacks.cpp#L45); [matching2/src/game/ascii_overlay_callbacks_overlay.cpp:2](../../../matching2/src/game/ascii_overlay_callbacks_overlay.cpp#L2) |
| `0x0043C500` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/render/special_quad.cpp:38](../../../matching2/src/render/special_quad.cpp#L38) |
| `0x0043C870` | semantic | pending_bounded_review | missing / yes / yes | [matching2/src/game/recovery_leaves.cpp:710](../../../matching2/src/game/recovery_leaves.cpp#L710) |
| `0x0043C8B0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/manager_factories.cpp:161](../../../matching2/src/game/manager_factories.cpp#L161) |
| `0x0043C970` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/manager_factories.cpp:176](../../../matching2/src/game/manager_factories.cpp#L176); [matching2/include/th10/game/manager_factories.hpp:56](../../../matching2/include/th10/game/manager_factories.hpp#L56) |
| `0x0043CB00` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/recovery_leaves.cpp:793](../../../matching2/src/game/recovery_leaves.cpp#L793) |
| `0x0043CB80` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/script/prng.cpp:1](../../../matching2/src/script/prng.cpp#L1); [matching2/src/script/prng.cpp:2](../../../matching2/src/script/prng.cpp#L2); [matching2/include/th10/script/prng.hpp:1](../../../matching2/include/th10/script/prng.hpp#L1) |
| `0x0043CC40` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/platform/sound_worker.cpp:4](../../../matching2/src/platform/sound_worker.cpp#L4); [matching2/include/th10/platform/sound_worker.hpp:14](../../../matching2/include/th10/platform/sound_worker.hpp#L14) |
| `0x0043CD30` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/platform/sound_device_init.cpp:38](../../../matching2/src/platform/sound_device_init.cpp#L38); [matching2/include/th10/platform/sound_device_init.hpp:5](../../../matching2/include/th10/platform/sound_device_init.hpp#L5); [matching2/include/th10/platform/sound_device_init.hpp:129](../../../matching2/include/th10/platform/sound_device_init.hpp#L129) |
| `0x0043D120` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/platform/sound_commands.cpp:93](../../../matching2/src/platform/sound_commands.cpp#L93); [matching2/include/th10/platform/sound_commands.hpp:3](../../../matching2/include/th10/platform/sound_commands.hpp#L3) |
| `0x0043D250` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/platform/memory_file.cpp:4](../../../matching2/src/platform/memory_file.cpp#L4) |
| `0x0043D2A0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/platform/path.cpp:22](../../../matching2/src/platform/path.cpp#L22) |
| `0x0043D390` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/platform/memory_file.cpp:209](../../../matching2/src/platform/memory_file.cpp#L209); [matching2/include/th10/platform/memory_file.hpp:84](../../../matching2/include/th10/platform/memory_file.hpp#L84); [matching2/include/th10/platform/sound_device_init.hpp:32](../../../matching2/include/th10/platform/sound_device_init.hpp#L32); [matching2/include/th10/platform/sound_device_init.hpp:116](../../../matching2/include/th10/platform/sound_device_init.hpp#L116) |
| `0x0043D690` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/platform/sound_stream_thread.cpp:12](../../../matching2/src/platform/sound_stream_thread.cpp#L12) |
| `0x0043D790` | semantic | pending_bounded_review | missing / missing / yes | [matching2/src/game/recovery_leaves.cpp:656](../../../matching2/src/game/recovery_leaves.cpp#L656) |
| `0x0043D7D0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/platform/sound_commands.cpp:238](../../../matching2/src/platform/sound_commands.cpp#L238); [matching2/include/th10/platform/sound_commands.hpp:3](../../../matching2/include/th10/platform/sound_commands.hpp#L3) |
| `0x0043D950` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/platform/sound_commands.cpp:215](../../../matching2/src/platform/sound_commands.cpp#L215); [matching2/include/th10/platform/sound_commands.hpp:3](../../../matching2/include/th10/platform/sound_commands.hpp#L3) |
| `0x0043DAB0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/platform/midi_worker_stop.cpp:4](../../../matching2/src/platform/midi_worker_stop.cpp#L4); [matching2/include/th10/platform/midi_worker_stop.hpp:24](../../../matching2/include/th10/platform/midi_worker_stop.hpp#L24) |
| `0x0043DB60` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/platform/sound_effect_buffers.cpp:15](../../../matching2/src/platform/sound_effect_buffers.cpp#L15) |
| `0x0043DC90` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/render/animation_manager.cpp:1389](../../../matching2/src/render/animation_manager.cpp#L1389) |
| `0x0043DD10` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/platform/sound_event_queue.cpp:12](../../../matching2/src/platform/sound_event_queue.cpp#L12) |
| `0x0043DDF0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/platform/sound_commands.cpp:17](../../../matching2/src/platform/sound_commands.cpp#L17); [matching2/include/th10/platform/sound_commands.hpp:3](../../../matching2/include/th10/platform/sound_commands.hpp#L3) |
| `0x0043E3A0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/platform/midi_worker.cpp:14](../../../matching2/src/platform/midi_worker.cpp#L14); [matching2/src/platform/midi_worker_overlay.cpp:2](../../../matching2/src/platform/midi_worker_overlay.cpp#L2); [matching2/include/th10/platform/bgm_streamer_refill.hpp:5](../../../matching2/include/th10/platform/bgm_streamer_refill.hpp#L5) |
| `0x0043E460` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/render/animation_manager.cpp:1371](../../../matching2/src/render/animation_manager.cpp#L1371) |
| `0x0043E5A0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/pool_constructors.cpp:122](../../../matching2/src/game/pool_constructors.cpp#L122); [matching2/src/render/animation_manager.cpp:895](../../../matching2/src/render/animation_manager.cpp#L895); [matching2/include/th10/game/pool_constructors.hpp:33](../../../matching2/include/th10/game/pool_constructors.hpp#L33) |
| `0x0043E710` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/render/animation_manager.cpp:5](../../../matching2/src/render/animation_manager.cpp#L5) |
| `0x0043E7E0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/render/animation_manager.cpp:5](../../../matching2/src/render/animation_manager.cpp#L5) |
| `0x0043E8B0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/render/animation_manager.cpp:807](../../../matching2/src/render/animation_manager.cpp#L807) |
| `0x0043EAC0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/script/anm_vm_tick.cpp:87](../../../matching2/src/script/anm_vm_tick.cpp#L87); [matching2/include/th10/script/anm_vm_tick.hpp:3](../../../matching2/include/th10/script/anm_vm_tick.hpp#L3) |
| `0x0043EC70` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/render/animation_manager.cpp:117](../../../matching2/src/render/animation_manager.cpp#L117) |
| `0x0043ED00` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/render/animation_manager.cpp:154](../../../matching2/src/render/animation_manager.cpp#L154) |
| `0x0043EDA0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/render/animation_manager.cpp:135](../../../matching2/src/render/animation_manager.cpp#L135) |
| `0x0043EE30` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/script/anm_vm_tick.cpp:113](../../../matching2/src/script/anm_vm_tick.cpp#L113); [matching2/src/script/entity_vm.cpp:5](../../../matching2/src/script/entity_vm.cpp#L5); [matching2/include/th10/script/anm_vm_tick.hpp:3](../../../matching2/include/th10/script/anm_vm_tick.hpp#L3) |
| `0x00441600` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/math/interpolators.cpp:3](../../../matching2/src/math/interpolators.cpp#L3); [matching2/src/math/interpolators.cpp:107](../../../matching2/src/math/interpolators.cpp#L107); [matching2/include/th10/math/interpolators.hpp:3](../../../matching2/include/th10/math/interpolators.hpp#L3) |
| `0x00441950` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/math/interpolators.cpp:3](../../../matching2/src/math/interpolators.cpp#L3); [matching2/src/math/interpolators.cpp:134](../../../matching2/src/math/interpolators.cpp#L134); [matching2/include/th10/math/interpolators.hpp:3](../../../matching2/include/th10/math/interpolators.hpp#L3) |
| `0x00441AD0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/math/interpolators.cpp:3](../../../matching2/src/math/interpolators.cpp#L3); [matching2/src/math/interpolators.cpp:86](../../../matching2/src/math/interpolators.cpp#L86); [matching2/include/th10/math/interpolators.hpp:3](../../../matching2/include/th10/math/interpolators.hpp#L3) |
| `0x00441E50` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/math/random_vector.cpp:4](../../../matching2/src/math/random_vector.cpp#L4) |
| `0x00441EF0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/recovery_leaves.cpp:127](../../../matching2/src/game/recovery_leaves.cpp#L127) |
| `0x00441F50` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/recovery_leaves.cpp:305](../../../matching2/src/game/recovery_leaves.cpp#L305) |
| `0x00442050` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/entity_color_slot.cpp:1](../../../matching2/src/game/entity_color_slot.cpp#L1); [matching2/src/game/entity_color_slot.cpp:2](../../../matching2/src/game/entity_color_slot.cpp#L2); [matching2/include/th10/game/entity_color_slot.hpp:1](../../../matching2/include/th10/game/entity_color_slot.hpp#L1); [matching2/include/th10/game/entity_color_slot.hpp:2](../../../matching2/include/th10/game/entity_color_slot.hpp#L2) |
| `0x00442220` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/recovery_leaves.cpp:289](../../../matching2/src/game/recovery_leaves.cpp#L289) |
| `0x00442300` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/recovery_leaves.cpp:274](../../../matching2/src/game/recovery_leaves.cpp#L274) |
| `0x004423C0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/render/animation_manager.cpp:97](../../../matching2/src/render/animation_manager.cpp#L97) |
| `0x004423E0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/render/anm_blend_state.cpp:18](../../../matching2/src/render/anm_blend_state.cpp#L18) |
| `0x004425A0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/render/render_state_sync.cpp:4](../../../matching2/src/render/render_state_sync.cpp#L4); [matching2/include/th10/render/render_state_sync.hpp:13](../../../matching2/include/th10/render/render_state_sync.hpp#L13); [matching2/standalone/host_main.cpp:2019](../../../matching2/standalone/host_main.cpp#L2019) |
| `0x00442670` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/render/final_quad_pipeline.cpp:6](../../../matching2/src/render/final_quad_pipeline.cpp#L6); [matching2/include/th10/render/final_quad_pipeline.hpp:6](../../../matching2/include/th10/render/final_quad_pipeline.hpp#L6); [matching2/standalone/host_main.cpp:2019](../../../matching2/standalone/host_main.cpp#L2019) |
| `0x00442F50` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/render/anm_batch_flush.cpp:4](../../../matching2/src/render/anm_batch_flush.cpp#L4); [matching2/src/render/camera_setup.cpp:27](../../../matching2/src/render/camera_setup.cpp#L27); [matching2/src/render/final_quad_pipeline.cpp:124](../../../matching2/src/render/final_quad_pipeline.cpp#L124); [matching2/include/th10/render/camera_apply.hpp:8](../../../matching2/include/th10/render/camera_apply.hpp#L8); [matching2/standalone/host_main.cpp:4247](../../../matching2/standalone/host_main.cpp#L4247); [matching2/standalone/host_main.cpp:4377](../../../matching2/standalone/host_main.cpp#L4377) |
| `0x00442FE0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/render/quad_vertex_append.cpp:3](../../../matching2/src/render/quad_vertex_append.cpp#L3) |
| `0x00443080` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/render/quad_build_anchored.cpp:3](../../../matching2/src/render/quad_build_anchored.cpp#L3) |
| `0x00443290` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/render/anchored_quad_draw.cpp:3](../../../matching2/src/render/anchored_quad_draw.cpp#L3) |
| `0x00443B60` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/render/projection_quads.cpp:63](../../../matching2/src/render/projection_quads.cpp#L63) |
| `0x00443F80` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/render/game_render_targets.cpp:12](../../../matching2/src/render/game_render_targets.cpp#L12) |
| `0x00443FB0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/render/anm_distance_color.cpp:61](../../../matching2/src/render/anm_distance_color.cpp#L61); [matching2/include/th10/render/anm_distance_color.hpp:20](../../../matching2/include/th10/render/anm_distance_color.hpp#L20) |
| `0x00444240` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/render/projection_quads.cpp:19](../../../matching2/src/render/projection_quads.cpp#L19) |
| `0x00444580` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/render/game_render_targets.cpp:21](../../../matching2/src/render/game_render_targets.cpp#L21) |
| `0x004445C0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/render/faded_quad_draw.cpp:22](../../../matching2/src/render/faded_quad_draw.cpp#L22) |
| `0x00444760` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/render/quad_transform_draw.cpp:32](../../../matching2/src/render/quad_transform_draw.cpp#L32); [matching2/include/th10/render/quad_transform_draw.hpp:4](../../../matching2/include/th10/render/quad_transform_draw.hpp#L4) |
| `0x00444B10` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/render/edge_strips.cpp:9](../../../matching2/src/render/edge_strips.cpp#L9); [matching2/include/th10/render/edge_strips.hpp:40](../../../matching2/include/th10/render/edge_strips.hpp#L40) |
| `0x00444BE0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/render/edge_strips.cpp:50](../../../matching2/src/render/edge_strips.cpp#L50); [matching2/include/th10/render/edge_strips.hpp:48](../../../matching2/include/th10/render/edge_strips.hpp#L48) |
| `0x00444CE0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/render/edge_strip_draw.cpp:13](../../../matching2/src/render/edge_strip_draw.cpp#L13); [matching2/include/th10/render/edge_strip_draw.hpp:4](../../../matching2/include/th10/render/edge_strip_draw.hpp#L4) |
| `0x004450E0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/render/rect_fan_draw.cpp:13](../../../matching2/src/render/rect_fan_draw.cpp#L13) |
| `0x004451C0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/render/anm_vm_draw_dispatch.cpp:50](../../../matching2/src/render/anm_vm_draw_dispatch.cpp#L50) |
| `0x004452F0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/render/effect_ring.cpp:6](../../../matching2/src/render/effect_ring.cpp#L6) |
| `0x00445620` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/render/effect_ring_update.cpp:25](../../../matching2/src/render/effect_ring_update.cpp#L25); [matching2/include/th10/render/effect_ring_update.hpp:5](../../../matching2/include/th10/render/effect_ring_update.hpp#L5) |
| `0x004458B0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/math/vector.cpp:14](../../../matching2/src/math/vector.cpp#L14) |
| `0x00445900` | semantic | reported_partial | yes / yes / yes | [matching2/src/app/game_state_init.cpp:22](../../../matching2/src/app/game_state_init.cpp#L22) |
| `0x00446220` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/render/animation_manager.cpp:204](../../../matching2/src/render/animation_manager.cpp#L204) |
| `0x004462F0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/render/anm_clip_quad.cpp:17](../../../matching2/src/render/anm_clip_quad.cpp#L17) |
| `0x004465B0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/render/transparent_pixel_fill_locked.cpp:13](../../../matching2/src/render/transparent_pixel_fill_locked.cpp#L13) |
| `0x00446C70` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/render/anm_texture_upload.cpp:94](../../../matching2/src/render/anm_texture_upload.cpp#L94) |
| `0x00446D70` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/render/anm_surface_restore.cpp:14](../../../matching2/src/render/anm_surface_restore.cpp#L14) |
| `0x00446EB0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/recovery_leaves.cpp:979](../../../matching2/src/game/recovery_leaves.cpp#L979); [matching2/include/th10/render/anm_entry_load.hpp:66](../../../matching2/include/th10/render/anm_entry_load.hpp#L66) |
| `0x00446F40` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/render/anm_texture_upload.cpp:48](../../../matching2/src/render/anm_texture_upload.cpp#L48); [matching2/include/th10/render/anm_entry_load.hpp:62](../../../matching2/include/th10/render/anm_entry_load.hpp#L62); [matching2/standalone/host_main.cpp:1721](../../../matching2/standalone/host_main.cpp#L1721) |
| `0x00447050` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/render/animation_manager.cpp:50](../../../matching2/src/render/animation_manager.cpp#L50); [matching2/include/th10/render/anm_entry_load.hpp:70](../../../matching2/include/th10/render/anm_entry_load.hpp#L70) |
| `0x004470C0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/render/anm_archive.cpp:6](../../../matching2/src/render/anm_archive.cpp#L6); [matching2/include/th10/render/anm_archive.hpp:3](../../../matching2/include/th10/render/anm_archive.hpp#L3) |
| `0x00447280` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/recovery_leaves.cpp:635](../../../matching2/src/game/recovery_leaves.cpp#L635); [matching2/standalone/host_stage.cpp:432](../../../matching2/standalone/host_stage.cpp#L432) |
| `0x004472E0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/render/anm_archive.cpp:40](../../../matching2/src/render/anm_archive.cpp#L40); [matching2/include/th10/render/anm_archive.hpp:3](../../../matching2/include/th10/render/anm_archive.hpp#L3); [matching2/include/th10/render/anm_archive.hpp:34](../../../matching2/include/th10/render/anm_archive.hpp#L34) |
| `0x004473C0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/render/anm_texture_upload.cpp:5](../../../matching2/src/render/anm_texture_upload.cpp#L5) |
| `0x00447470` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/render/anm_entry_load.cpp:1](../../../matching2/src/render/anm_entry_load.cpp#L1); [matching2/include/th10/render/anm_entry_load.hpp:3](../../../matching2/include/th10/render/anm_entry_load.hpp#L3); [matching2/include/th10/render/anm_entry_load.hpp:97](../../../matching2/include/th10/render/anm_entry_load.hpp#L97) |
| `0x00447700` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/render/anm_pending_service.cpp:12](../../../matching2/src/render/anm_pending_service.cpp#L12); [matching2/src/render/anm_pending_service_overlay.cpp:2](../../../matching2/src/render/anm_pending_service_overlay.cpp#L2) |
| `0x004477D0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/render/animation_manager.cpp:1354](../../../matching2/src/render/animation_manager.cpp#L1354) |
| `0x00447810` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/render/animation_manager.cpp:63](../../../matching2/src/render/animation_manager.cpp#L63) |
| `0x00447940` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/render/animation_manager.cpp:104](../../../matching2/src/render/animation_manager.cpp#L104); [matching2/src/render/anm_entry_load.cpp:158](../../../matching2/src/render/anm_entry_load.cpp#L158) |
| `0x004479D0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/recovery_leaves.cpp:1050](../../../matching2/src/game/recovery_leaves.cpp#L1050) |
| `0x00447A50` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/recovery_leaves.cpp:989](../../../matching2/src/game/recovery_leaves.cpp#L989); [matching2/standalone/host_main.cpp:2609](../../../matching2/standalone/host_main.cpp#L2609) |
| `0x00447AE0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/ascii_overlay_callbacks.cpp:23](../../../matching2/src/game/ascii_overlay_callbacks.cpp#L23) |
| `0x00447BB0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/game_thread_text_draw.cpp:59](../../../matching2/src/game/game_thread_text_draw.cpp#L59) |
| `0x00447F70` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/render/animation_manager.cpp:1342](../../../matching2/src/render/animation_manager.cpp#L1342) |
| `0x00447FD0` | semantic | pending_bounded_review | missing / missing / yes | [matching2/src/render/anm_surface_restore.cpp:82](../../../matching2/src/render/anm_surface_restore.cpp#L82) |
| `0x00448120` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/render/anm_surface_restore.cpp:54](../../../matching2/src/render/anm_surface_restore.cpp#L54); [matching2/src/render/anm_surface_restore.cpp:89](../../../matching2/src/render/anm_surface_restore.cpp#L89) |
| `0x00448270` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/render/camera_setup.cpp:44](../../../matching2/src/render/camera_setup.cpp#L44); [matching2/include/th10/render/camera_setup.hpp:3](../../../matching2/include/th10/render/camera_setup.hpp#L3) |
| `0x00448450` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/render/camera_setup.cpp:61](../../../matching2/src/render/camera_setup.cpp#L61); [matching2/include/th10/render/camera_setup.hpp:4](../../../matching2/include/th10/render/camera_setup.hpp#L4) |
| `0x00448860` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/render/animation_manager.cpp:4](../../../matching2/src/render/animation_manager.cpp#L4) |
| `0x00448900` | semantic | pending_bounded_review | missing / missing / yes | [matching2/src/render/animation_manager.cpp:4](../../../matching2/src/render/animation_manager.cpp#L4) |
| `0x00448980` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/render/animation_manager.cpp:4](../../../matching2/src/render/animation_manager.cpp#L4) |
| `0x004489D0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/render/animation_manager.cpp:3](../../../matching2/src/render/animation_manager.cpp#L3) |
| `0x00448A50` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/render/animation_manager.cpp:3](../../../matching2/src/render/animation_manager.cpp#L3) |
| `0x00448AC0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/render/animation_manager.cpp:3](../../../matching2/src/render/animation_manager.cpp#L3) |
| `0x00448B40` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/render/animation_manager.cpp:3](../../../matching2/src/render/animation_manager.cpp#L3) |
| `0x00448BB0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/render/animation_manager.cpp:527](../../../matching2/src/render/animation_manager.cpp#L527) |
| `0x00448D00` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/render/animation_manager.cpp:284](../../../matching2/src/render/animation_manager.cpp#L284) |
| `0x00448D50` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/render/animation_manager.cpp:316](../../../matching2/src/render/animation_manager.cpp#L316) |
| `0x00448DB0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/render/animation_manager.cpp:5](../../../matching2/src/render/animation_manager.cpp#L5); [matching2/include/th10/game/enemy_drop_sweep.hpp:10](../../../matching2/include/th10/game/enemy_drop_sweep.hpp#L10); [matching2/include/th10/game/entity_region_sweep.hpp:50](../../../matching2/include/th10/game/entity_region_sweep.hpp#L50); [matching2/include/th10/game/laser_line.hpp:121](../../../matching2/include/th10/game/laser_line.hpp#L121) |
| `0x00448E30` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/render/animation_manager.cpp:292](../../../matching2/src/render/animation_manager.cpp#L292) |
| `0x00448F60` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/render/animation_manager.cpp:300](../../../matching2/src/render/animation_manager.cpp#L300) |
| `0x00449090` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/render/animation_manager.cpp:308](../../../matching2/src/render/animation_manager.cpp#L308) |
| `0x004491C0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/render/animation_manager.cpp:348](../../../matching2/src/render/animation_manager.cpp#L348) |
| `0x00449210` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/render/animation_manager.cpp:632](../../../matching2/src/render/animation_manager.cpp#L632) |
| `0x00449250` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/render/animation_manager.cpp:664](../../../matching2/src/render/animation_manager.cpp#L664) |
| `0x004492A0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/render/animation_manager.cpp:703](../../../matching2/src/render/animation_manager.cpp#L703) |
| `0x004492F0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/render/animation_manager.cpp:7](../../../matching2/src/render/animation_manager.cpp#L7) |
| `0x00449350` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/render/animation_manager.cpp:1026](../../../matching2/src/render/animation_manager.cpp#L1026) |
| `0x004493E0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/render/animation_manager.cpp:733](../../../matching2/src/render/animation_manager.cpp#L733) |
| `0x00449450` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/render/animation_manager.cpp:1037](../../../matching2/src/render/animation_manager.cpp#L1037) |
| `0x00449470` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/render/animation_manager.cpp:643](../../../matching2/src/render/animation_manager.cpp#L643) |
| `0x00449590` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/render/animation_manager.cpp:704](../../../matching2/src/render/animation_manager.cpp#L704); [matching2/src/render/animation_manager.cpp:728](../../../matching2/src/render/animation_manager.cpp#L728) |
| `0x004495E0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/render/animation_manager.cpp:716](../../../matching2/src/render/animation_manager.cpp#L716) |
| `0x00449630` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/render/animation_manager.cpp:1047](../../../matching2/src/render/animation_manager.cpp#L1047) |
| `0x00449670` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/render/animation_manager.cpp:1056](../../../matching2/src/render/animation_manager.cpp#L1056) |
| `0x004496A0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/render/animation_manager.cpp:1069](../../../matching2/src/render/animation_manager.cpp#L1069) |
| `0x004496D0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/render/animation_manager.cpp:861](../../../matching2/src/render/animation_manager.cpp#L861) |
| `0x004497D0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/render/animation_manager.cpp:1193](../../../matching2/src/render/animation_manager.cpp#L1193) |
| `0x00449870` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/render/animation_manager.cpp:873](../../../matching2/src/render/animation_manager.cpp#L873) |
| `0x00449950` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/render/animation_manager.cpp:7](../../../matching2/src/render/animation_manager.cpp#L7); [matching2/src/render/animation_manager.cpp:239](../../../matching2/src/render/animation_manager.cpp#L239) |
| `0x00449A90` | semantic | pending_bounded_review | missing / missing / yes | [matching2/src/render/d3d_resource_manager.cpp:13](../../../matching2/src/render/d3d_resource_manager.cpp#L13) |
| `0x00449AA0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/render/d3d_resource_manager.cpp:47](../../../matching2/src/render/d3d_resource_manager.cpp#L47) |
| `0x00449AE0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/scheduler.cpp:3](../../../matching2/src/game/scheduler.cpp#L3); [matching2/include/th10/app/main_tasks.hpp:22](../../../matching2/include/th10/app/main_tasks.hpp#L22); [matching2/include/th10/game/stage_entry.hpp:11](../../../matching2/include/th10/game/stage_entry.hpp#L11) |
| `0x00449B70` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/scheduler.cpp:4](../../../matching2/src/game/scheduler.cpp#L4); [matching2/include/th10/app/game_state_init.hpp:39](../../../matching2/include/th10/app/game_state_init.hpp#L39); [matching2/include/th10/app/main_tasks.hpp:22](../../../matching2/include/th10/app/main_tasks.hpp#L22); [matching2/include/th10/game/stage_entry.hpp:12](../../../matching2/include/th10/game/stage_entry.hpp#L12) |
| `0x00449C00` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/scheduler.cpp:245](../../../matching2/src/game/scheduler.cpp#L245); [matching2/standalone/host_main.cpp:5779](../../../matching2/standalone/host_main.cpp#L5779) |
| `0x00449D40` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/scheduler.cpp:245](../../../matching2/src/game/scheduler.cpp#L245) |
| `0x00449E50` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/render/d3d_resource_manager.cpp:30](../../../matching2/src/render/d3d_resource_manager.cpp#L30) |
| `0x00449ED0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/scheduler.cpp:3](../../../matching2/src/game/scheduler.cpp#L3); [matching2/include/th10/game/stage_entry.hpp:126](../../../matching2/include/th10/game/stage_entry.hpp#L126) |
| `0x00449F60` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/scheduler.cpp:126](../../../matching2/src/game/scheduler.cpp#L126) |
| `0x0044A000` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/scheduler.cpp:156](../../../matching2/src/game/scheduler.cpp#L156) |
| `0x0044A030` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/scheduler.cpp:169](../../../matching2/src/game/scheduler.cpp#L169) |
| `0x0044A0C0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/platform/joystick_probe.cpp:5](../../../matching2/src/platform/joystick_probe.cpp#L5); [matching2/include/th10/platform/joystick_probe.hpp:17](../../../matching2/include/th10/platform/joystick_probe.hpp#L17) |
| `0x0044A190` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/platform/joystick_poll.cpp:35](../../../matching2/src/platform/joystick_poll.cpp#L35) |
| `0x0044A4E0` | semantic | reported_partial | yes / yes / yes | [matching2/src/game/score.cpp:282](../../../matching2/src/game/score.cpp#L282); [matching2/src/game/score.cpp:292](../../../matching2/src/game/score.cpp#L292); [matching2/src/platform/joystick_poll.cpp:127](../../../matching2/src/platform/joystick_poll.cpp#L127); [matching2/src/platform/joystick_poll.cpp:143](../../../matching2/src/platform/joystick_poll.cpp#L143) |
| `0x0044A5F0` | partial | separate_sparse_review | yes / yes / yes | [matching2/src/platform/final_input_runtime.cpp:85](../../../matching2/src/platform/final_input_runtime.cpp#L85) |
| `0x0044B010` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/score.cpp:297](../../../matching2/src/game/score.cpp#L297) |
| `0x0044B080` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/score.cpp:314](../../../matching2/src/game/score.cpp#L314) |
| `0x0044B0D0` | semantic | reported_grounded | yes / yes / yes | [matching2/src/archive/crypt.cpp:57](../../../matching2/src/archive/crypt.cpp#L57); [matching2/include/th10/archive/crypt.hpp:17](../../../matching2/include/th10/archive/crypt.hpp#L17) |
| `0x0044B220` | semantic | reported_grounded | yes / yes / yes | [matching2/src/archive/crypt.cpp:108](../../../matching2/src/archive/crypt.cpp#L108); [matching2/include/th10/archive/crypt.hpp:27](../../../matching2/include/th10/archive/crypt.hpp#L27) |
| `0x0044B360` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/platform/pack_file_loader.cpp:28](../../../matching2/src/platform/pack_file_loader.cpp#L28); [matching2/include/th10/app/main_tasks.hpp:108](../../../matching2/include/th10/app/main_tasks.hpp#L108); [matching2/standalone/host_main.cpp:5257](../../../matching2/standalone/host_main.cpp#L5257); [matching2/standalone/host_main.cpp:5817](../../../matching2/standalone/host_main.cpp#L5817) |
| `0x0044B4D0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/platform/file.cpp:81](../../../matching2/src/platform/file.cpp#L81) |
| `0x0044B540` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/platform/file.cpp:154](../../../matching2/src/platform/file.cpp#L154); [matching2/standalone/host_main.cpp:161](../../../matching2/standalone/host_main.cpp#L161); [matching2/standalone/host_main.cpp:5247](../../../matching2/standalone/host_main.cpp#L5247); [matching2/standalone/host_main.cpp:5329](../../../matching2/standalone/host_main.cpp#L5329); [matching2/standalone/host_main.cpp:5817](../../../matching2/standalone/host_main.cpp#L5817) |
| `0x0044B620` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/platform/file.cpp:135](../../../matching2/src/platform/file.cpp#L135) |
| `0x0044B6B0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/platform/file.cpp:144](../../../matching2/src/platform/file.cpp#L144) |
| `0x0044B740` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/platform/file.cpp:197](../../../matching2/src/platform/file.cpp#L197) |
| `0x0044B790` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/platform/file.cpp:215](../../../matching2/src/platform/file.cpp#L215) |
| `0x0044B7E0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/platform/file.cpp:97](../../../matching2/src/platform/file.cpp#L97) |
| `0x0044B810` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/platform/text_log.cpp:31](../../../matching2/src/platform/text_log.cpp#L31); [matching2/include/th10/app/game_main.hpp:55](../../../matching2/include/th10/app/game_main.hpp#L55); [matching2/include/th10/app/main_tasks.hpp:112](../../../matching2/include/th10/app/main_tasks.hpp#L112); [matching2/include/th10/app/main_tasks.hpp:114](../../../matching2/include/th10/app/main_tasks.hpp#L114); [matching2/include/th10/platform/sound_device_init.hpp:18](../../../matching2/include/th10/platform/sound_device_init.hpp#L18); [matching2/include/th10/platform/sound_device_init.hpp:113](../../../matching2/include/th10/platform/sound_device_init.hpp#L113); [matching2/standalone/host_main.cpp:161](../../../matching2/standalone/host_main.cpp#L161); [matching2/standalone/host_main.cpp:5169](../../../matching2/standalone/host_main.cpp#L5169); [matching2/standalone/host_main.cpp:5817](../../../matching2/standalone/host_main.cpp#L5817); [matching2/standalone/host_main.cpp:5836](../../../matching2/standalone/host_main.cpp#L5836) |
| `0x0044B8E0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/platform/text_log.cpp:49](../../../matching2/src/platform/text_log.cpp#L49); [matching2/include/th10/app/main_tasks.hpp:124](../../../matching2/include/th10/app/main_tasks.hpp#L124); [matching2/standalone/host_main.cpp:5340](../../../matching2/standalone/host_main.cpp#L5340); [matching2/standalone/host_main.cpp:5855](../../../matching2/standalone/host_main.cpp#L5855) |
| `0x0044B9E0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/math/rng.cpp:35](../../../matching2/src/math/rng.cpp#L35); [matching2/include/th10/math/rng.hpp:9](../../../matching2/include/th10/math/rng.hpp#L9) |
| `0x0044BA80` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/math/rng.cpp:45](../../../matching2/src/math/rng.cpp#L45) |
| `0x0044BB20` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/math/rng.cpp:59](../../../matching2/src/math/rng.cpp#L59) |
| `0x0044BB90` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/math/rng.cpp:64](../../../matching2/src/math/rng.cpp#L64) |
| `0x0044BC10` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/math/angle.cpp:27](../../../matching2/src/math/angle.cpp#L27); [matching2/include/th10/math/rng.hpp:9](../../../matching2/include/th10/math/rng.hpp#L9) |
| `0x0044BC70` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/bullet.cpp:49](../../../matching2/src/game/bullet.cpp#L49); [matching2/src/math/angle.cpp:10](../../../matching2/src/math/angle.cpp#L10); [matching2/src/script/ecl_core_interpreter.cpp:28](../../../matching2/src/script/ecl_core_interpreter.cpp#L28) |
| `0x0044BD10` | semantic | reference_unresolved | missing / missing / yes | [matching2/src/platform/process.cpp:87](../../../matching2/src/platform/process.cpp#L87) |
| `0x0044BE20` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/score.cpp:341](../../../matching2/src/game/score.cpp#L341) |
| `0x0044BE70` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/score.cpp:327](../../../matching2/src/game/score.cpp#L327) |
| `0x0044BEA0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/menu.cpp:1](../../../matching2/src/game/menu.cpp#L1); [matching2/src/game/title_main_menu.cpp:35](../../../matching2/src/game/title_main_menu.cpp#L35); [matching2/include/th10/game/title_main_menu.hpp:33](../../../matching2/include/th10/game/title_main_menu.hpp#L33) |
| `0x0044BF40` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/math/timer.cpp:26](../../../matching2/src/math/timer.cpp#L26) |
| `0x0044C100` | semantic | reference_unresolved | missing / missing / yes | [matching2/src/platform/process.cpp:56](../../../matching2/src/platform/process.cpp#L56) |
| `0x0044C130` | semantic | reference_unresolved | missing / missing / yes | [matching2/src/platform/process.cpp:33](../../../matching2/src/platform/process.cpp#L33); [matching2/src/platform/process.cpp:68](../../../matching2/src/platform/process.cpp#L68) |
| `0x0044C150` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/platform/all_source_runtime.cpp:184](../../../matching2/src/platform/all_source_runtime.cpp#L184); [matching2/src/platform/process.cpp:33](../../../matching2/src/platform/process.cpp#L33); [matching2/include/th10/app/frame_clock.hpp:54](../../../matching2/include/th10/app/frame_clock.hpp#L54) |
| `0x0044C1C0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/platform/worker_start.cpp:3](../../../matching2/src/platform/worker_start.cpp#L3); [matching2/include/th10/platform/worker_start.hpp:17](../../../matching2/include/th10/platform/worker_start.hpp#L17) |
| `0x0044C2A0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/bullet.cpp:72](../../../matching2/src/game/bullet.cpp#L72); [matching2/src/game/recovery_leaves.cpp:1128](../../../matching2/src/game/recovery_leaves.cpp#L1128) |
| `0x0044C350` | semantic | reported_partial | yes / yes / yes | [matching2/src/game/trajectory_evaluate.cpp:94](../../../matching2/src/game/trajectory_evaluate.cpp#L94); [matching2/src/math/easing.cpp:3](../../../matching2/src/math/easing.cpp#L3); [matching2/include/th10/game/trajectory_evaluate.hpp:46](../../../matching2/include/th10/game/trajectory_evaluate.hpp#L46) |
| `0x0044C5D0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/math/vector2_polar.cpp:5](../../../matching2/src/math/vector2_polar.cpp#L5); [matching2/include/th10/math/vector2_polar.hpp:3](../../../matching2/include/th10/math/vector2_polar.hpp#L3) |
| `0x0044C7E0` | semantic | reported_partial | yes / yes / yes | [matching2/src/platform/joystick_property.cpp:18](../../../matching2/src/platform/joystick_property.cpp#L18); [matching2/src/platform/joystick_property_overlay.cpp:2](../../../matching2/src/platform/joystick_property_overlay.cpp#L2); [matching2/src/platform/sound_device_init.cpp:70](../../../matching2/src/platform/sound_device_init.cpp#L70); [matching2/include/th10/platform/sound_device_init.hpp:92](../../../matching2/include/th10/platform/sound_device_init.hpp#L92) |
| `0x0044C8F0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/platform/sound_stream_create.cpp:15](../../../matching2/src/platform/sound_stream_create.cpp#L15); [matching2/include/th10/platform/sound_stream_create.hpp:4](../../../matching2/include/th10/platform/sound_stream_create.hpp#L4) |
| `0x0044CBF0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/platform/sound_commands.cpp:123](../../../matching2/src/platform/sound_commands.cpp#L123); [matching2/include/th10/platform/sound_commands.hpp:4](../../../matching2/include/th10/platform/sound_commands.hpp#L4) |
| `0x0044CE80` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/recovery_leaves.cpp:830](../../../matching2/src/game/recovery_leaves.cpp#L830) |
| `0x0044CF00` | semantic | pending_bounded_review | missing / missing / yes | [matching2/src/game/recovery_leaves.cpp:53](../../../matching2/src/game/recovery_leaves.cpp#L53) |
| `0x0044CF20` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/platform/sound_commands.cpp:146](../../../matching2/src/platform/sound_commands.cpp#L146); [matching2/include/th10/platform/sound_commands.hpp:4](../../../matching2/include/th10/platform/sound_commands.hpp#L4) |
| `0x0044D080` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/recovery_leaves.cpp:345](../../../matching2/src/game/recovery_leaves.cpp#L345) |
| `0x0044D110` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/platform/sound_commands.cpp:170](../../../matching2/src/platform/sound_commands.cpp#L170); [matching2/include/th10/platform/sound_commands.hpp:4](../../../matching2/include/th10/platform/sound_commands.hpp#L4) |
| `0x0044D300` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/recovery_leaves.cpp:366](../../../matching2/src/game/recovery_leaves.cpp#L366) |
| `0x0044D370` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/recovery_leaves.cpp:206](../../../matching2/src/game/recovery_leaves.cpp#L206) |
| `0x0044D440` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/platform/sound_stream_start.cpp:4](../../../matching2/src/platform/sound_stream_start.cpp#L4); [matching2/include/th10/platform/sound_stream_start.hpp:18](../../../matching2/include/th10/platform/sound_stream_start.hpp#L18) |
| `0x0044D4E0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/recovery_leaves.cpp:422](../../../matching2/src/game/recovery_leaves.cpp#L422) |
| `0x0044D550` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/recovery_leaves.cpp:166](../../../matching2/src/game/recovery_leaves.cpp#L166); [matching2/include/th10/platform/midi_worker_stop.hpp:25](../../../matching2/include/th10/platform/midi_worker_stop.hpp#L25) |
| `0x0044D5B0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/platform/process.cpp:73](../../../matching2/src/platform/process.cpp#L73) |
| `0x0044D5D0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/recovery_leaves.cpp:153](../../../matching2/src/game/recovery_leaves.cpp#L153) |
| `0x0044D600` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/recovery_leaves.cpp:193](../../../matching2/src/game/recovery_leaves.cpp#L193) |
| `0x0044D6A0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/recovery_leaves.cpp:844](../../../matching2/src/game/recovery_leaves.cpp#L844) |
| `0x0044D710` | semantic | pending_bounded_review | missing / missing / yes | [matching2/src/game/recovery_leaves.cpp:413](../../../matching2/src/game/recovery_leaves.cpp#L413) |
| `0x0044D730` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/platform/sound_leaves.cpp:18](../../../matching2/src/platform/sound_leaves.cpp#L18); [matching2/include/th10/platform/sound_leaves.hpp:16](../../../matching2/include/th10/platform/sound_leaves.hpp#L16) |
| `0x0044D850` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/platform/bgm_streamer_refill.cpp:12](../../../matching2/src/platform/bgm_streamer_refill.cpp#L12); [matching2/include/th10/platform/bgm_streamer_refill.hpp:5](../../../matching2/include/th10/platform/bgm_streamer_refill.hpp#L5) |
| `0x0044DAD0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/platform/sound_commands.cpp:200](../../../matching2/src/platform/sound_commands.cpp#L200); [matching2/include/th10/platform/sound_commands.hpp:4](../../../matching2/include/th10/platform/sound_commands.hpp#L4) |
| `0x0044DBF0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/archive_cursor_open.cpp:1](../../../matching2/src/game/archive_cursor_open.cpp#L1); [matching2/src/game/archive_cursor_open.cpp:2](../../../matching2/src/game/archive_cursor_open.cpp#L2); [matching2/include/th10/game/archive_cursor_open.hpp:1](../../../matching2/include/th10/game/archive_cursor_open.hpp#L1); [matching2/include/th10/game/archive_cursor_open.hpp:2](../../../matching2/include/th10/game/archive_cursor_open.hpp#L2) |
| `0x0044DCA0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/game/recovery_leaves.cpp:398](../../../matching2/src/game/recovery_leaves.cpp#L398) |
| `0x0044DD40` | semantic | reported_grounded | yes / yes / yes | [matching2/src/game/archive_cursor.cpp:1](../../../matching2/src/game/archive_cursor.cpp#L1); [matching2/src/game/archive_cursor.cpp:2](../../../matching2/src/game/archive_cursor.cpp#L2); [matching2/include/th10/game/archive_cursor.hpp:1](../../../matching2/include/th10/game/archive_cursor.hpp#L1); [matching2/include/th10/game/archive_cursor.hpp:2](../../../matching2/include/th10/game/archive_cursor.hpp#L2) |
| `0x0044DE10` | semantic | reported_grounded | yes / yes / yes | [matching2/src/game/archive_cursor_read.cpp:1](../../../matching2/src/game/archive_cursor_read.cpp#L1); [matching2/src/game/archive_cursor_read.cpp:2](../../../matching2/src/game/archive_cursor_read.cpp#L2); [matching2/include/th10/game/archive_cursor_read.hpp:1](../../../matching2/include/th10/game/archive_cursor_read.hpp#L1); [matching2/include/th10/game/archive_cursor_read.hpp:2](../../../matching2/include/th10/game/archive_cursor_read.hpp#L2) |
| `0x0044DF70` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/script/ecl_core_interpreter.cpp:15](../../../matching2/src/script/ecl_core_interpreter.cpp#L15); [matching2/src/script/ecl_core_interpreter.cpp:283](../../../matching2/src/script/ecl_core_interpreter.cpp#L283); [matching2/src/script/ecl_core_interpreter.cpp:315](../../../matching2/src/script/ecl_core_interpreter.cpp#L315); [matching2/src/script/ecl_core_interpreter.cpp:1172](../../../matching2/src/script/ecl_core_interpreter.cpp#L1172); [matching2/src/script/ecl_vm_children.cpp:26](../../../matching2/src/script/ecl_vm_children.cpp#L26); [matching2/include/th10/script/ecl_core_interpreter.hpp:93](../../../matching2/include/th10/script/ecl_core_interpreter.hpp#L93); [matching2/include/th10/script/ecl_core_interpreter.hpp:99](../../../matching2/include/th10/script/ecl_core_interpreter.hpp#L99); [matching2/include/th10/script/ecl_core_interpreter.hpp:154](../../../matching2/include/th10/script/ecl_core_interpreter.hpp#L154); [matching2/include/th10/script/ecl_vm_children.hpp:79](../../../matching2/include/th10/script/ecl_vm_children.hpp#L79) |
| `0x0044E1A0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/script/ecl_core_interpreter.cpp:1](../../../matching2/src/script/ecl_core_interpreter.cpp#L1); [matching2/include/th10/script/ecl_core_interpreter.hpp:117](../../../matching2/include/th10/script/ecl_core_interpreter.hpp#L117); [matching2/include/th10/script/ecl_core_interpreter.hpp:127](../../../matching2/include/th10/script/ecl_core_interpreter.hpp#L127) |
| `0x0044FD10` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/script/ecl_vm_children.cpp:130](../../../matching2/src/script/ecl_vm_children.cpp#L130) |
| `0x0044FDB0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/script/ecl_core_interpreter.cpp:32](../../../matching2/src/script/ecl_core_interpreter.cpp#L32); [matching2/src/script/ecl_core_interpreter.cpp:94](../../../matching2/src/script/ecl_core_interpreter.cpp#L94); [matching2/src/script/ecl_vm.cpp:205](../../../matching2/src/script/ecl_vm.cpp#L205) |
| `0x0044FE40` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/script/ecl_core_interpreter.cpp:32](../../../matching2/src/script/ecl_core_interpreter.cpp#L32); [matching2/src/script/ecl_core_interpreter.cpp:94](../../../matching2/src/script/ecl_core_interpreter.cpp#L94); [matching2/src/script/ecl_core_interpreter.cpp:551](../../../matching2/src/script/ecl_core_interpreter.cpp#L551); [matching2/src/script/ecl_vm.cpp:155](../../../matching2/src/script/ecl_vm.cpp#L155); [matching2/include/th10/script/ecl_core_interpreter.hpp:31](../../../matching2/include/th10/script/ecl_core_interpreter.hpp#L31) |
| `0x0044FF00` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/script/ecl_core_interpreter.cpp:20](../../../matching2/src/script/ecl_core_interpreter.cpp#L20); [matching2/src/script/ecl_core_interpreter.cpp:94](../../../matching2/src/script/ecl_core_interpreter.cpp#L94); [matching2/src/script/ecl_core_interpreter.cpp:336](../../../matching2/src/script/ecl_core_interpreter.cpp#L336); [matching2/src/script/ecl_core_interpreter.cpp:481](../../../matching2/src/script/ecl_core_interpreter.cpp#L481); [matching2/src/script/ecl_vm.cpp:164](../../../matching2/src/script/ecl_vm.cpp#L164) |
| `0x0044FF80` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/script/ecl_core_interpreter.cpp:21](../../../matching2/src/script/ecl_core_interpreter.cpp#L21); [matching2/src/script/ecl_core_interpreter.cpp:94](../../../matching2/src/script/ecl_core_interpreter.cpp#L94); [matching2/src/script/ecl_core_interpreter.cpp:477](../../../matching2/src/script/ecl_core_interpreter.cpp#L477); [matching2/src/script/ecl_vm.cpp:107](../../../matching2/src/script/ecl_vm.cpp#L107); [matching2/include/th10/script/ecl_core_interpreter.hpp:23](../../../matching2/include/th10/script/ecl_core_interpreter.hpp#L23) |
| `0x00450030` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/script/ecl_core_interpreter.cpp:22](../../../matching2/src/script/ecl_core_interpreter.cpp#L22); [matching2/src/script/ecl_vm.cpp:268](../../../matching2/src/script/ecl_vm.cpp#L268); [matching2/include/th10/script/ecl_core_interpreter.hpp:23](../../../matching2/include/th10/script/ecl_core_interpreter.hpp#L23); [matching2/include/th10/script/ecl_core_interpreter.hpp:31](../../../matching2/include/th10/script/ecl_core_interpreter.hpp#L31) |
| `0x00450070` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/script/ecl_core_interpreter.cpp:18](../../../matching2/src/script/ecl_core_interpreter.cpp#L18); [matching2/src/script/ecl_core_interpreter.cpp:1361](../../../matching2/src/script/ecl_core_interpreter.cpp#L1361); [matching2/src/script/ecl_vm.cpp:224](../../../matching2/src/script/ecl_vm.cpp#L224); [matching2/include/th10/script/ecl_core_interpreter.hpp:23](../../../matching2/include/th10/script/ecl_core_interpreter.hpp#L23); [matching2/include/th10/script/ecl_core_interpreter.hpp:31](../../../matching2/include/th10/script/ecl_core_interpreter.hpp#L31); [matching2/include/th10/script/ecl_core_interpreter.hpp:181](../../../matching2/include/th10/script/ecl_core_interpreter.hpp#L181) |
| `0x004500D0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/script/ecl_core_interpreter.cpp:16](../../../matching2/src/script/ecl_core_interpreter.cpp#L16); [matching2/src/script/ecl_core_interpreter.cpp:386](../../../matching2/src/script/ecl_core_interpreter.cpp#L386); [matching2/src/script/ecl_core_interpreter.cpp:1309](../../../matching2/src/script/ecl_core_interpreter.cpp#L1309); [matching2/src/script/ecl_vm_children.cpp:92](../../../matching2/src/script/ecl_vm_children.cpp#L92); [matching2/include/th10/script/ecl_core_interpreter.hpp:95](../../../matching2/include/th10/script/ecl_core_interpreter.hpp#L95); [matching2/include/th10/script/ecl_core_interpreter.hpp:162](../../../matching2/include/th10/script/ecl_core_interpreter.hpp#L162) |
| `0x00450160` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/script/ecl_core_interpreter.cpp:17](../../../matching2/src/script/ecl_core_interpreter.cpp#L17); [matching2/src/script/ecl_core_interpreter.cpp:1346](../../../matching2/src/script/ecl_core_interpreter.cpp#L1346); [matching2/src/script/ecl_vm.cpp:286](../../../matching2/src/script/ecl_vm.cpp#L286); [matching2/include/th10/script/ecl_core_interpreter.hpp:123](../../../matching2/include/th10/script/ecl_core_interpreter.hpp#L123); [matching2/include/th10/script/ecl_core_interpreter.hpp:171](../../../matching2/include/th10/script/ecl_core_interpreter.hpp#L171) |
| `0x00450190` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/script/ecl_core_interpreter.cpp:23](../../../matching2/src/script/ecl_core_interpreter.cpp#L23); [matching2/src/script/ecl_vm.cpp:300](../../../matching2/src/script/ecl_vm.cpp#L300); [matching2/include/th10/script/ecl.hpp:107](../../../matching2/include/th10/script/ecl.hpp#L107) |
| `0x004501B0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/script/ecl_core_interpreter.cpp:27](../../../matching2/src/script/ecl_core_interpreter.cpp#L27); [matching2/src/script/ecl_vm.cpp:342](../../../matching2/src/script/ecl_vm.cpp#L342) |
| `0x00450220` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/script/ecl_name_table.cpp:18](../../../matching2/src/script/ecl_name_table.cpp#L18) |
| `0x00450470` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/script/final_script_runtime.cpp:23](../../../matching2/src/script/final_script_runtime.cpp#L23) |
| `0x004505B0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/script/ecl_core_interpreter.cpp:26](../../../matching2/src/script/ecl_core_interpreter.cpp#L26); [matching2/src/script/ecl_core_interpreter.cpp:180](../../../matching2/src/script/ecl_core_interpreter.cpp#L180); [matching2/src/script/ecl_vm.cpp:348](../../../matching2/src/script/ecl_vm.cpp#L348); [matching2/include/th10/script/ecl_core_interpreter.hpp:114](../../../matching2/include/th10/script/ecl_core_interpreter.hpp#L114) |
| `0x00450690` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/script/ecl_core_interpreter.cpp:24](../../../matching2/src/script/ecl_core_interpreter.cpp#L24); [matching2/src/script/ecl_vm.cpp:311](../../../matching2/src/script/ecl_vm.cpp#L311); [matching2/include/th10/script/ecl.hpp:107](../../../matching2/include/th10/script/ecl.hpp#L107); [matching2/include/th10/script/ecl_core_interpreter.hpp:113](../../../matching2/include/th10/script/ecl_core_interpreter.hpp#L113); [matching2/include/th10/script/ecl_core_interpreter.hpp:120](../../../matching2/include/th10/script/ecl_core_interpreter.hpp#L120) |
| `0x004506D0` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/script/ecl_core_interpreter.cpp:25](../../../matching2/src/script/ecl_core_interpreter.cpp#L25); [matching2/src/script/ecl_core_interpreter.cpp:234](../../../matching2/src/script/ecl_core_interpreter.cpp#L234); [matching2/src/script/ecl_vm.cpp:328](../../../matching2/src/script/ecl_vm.cpp#L328); [matching2/include/th10/script/ecl.hpp:107](../../../matching2/include/th10/script/ecl.hpp#L107); [matching2/include/th10/script/ecl_core_interpreter.hpp:113](../../../matching2/include/th10/script/ecl_core_interpreter.hpp#L113); [matching2/include/th10/script/ecl_core_interpreter.hpp:120](../../../matching2/include/th10/script/ecl_core_interpreter.hpp#L120) |
| `0x00450700` | semantic | pending_bounded_review | yes / yes / yes | [matching2/src/script/final_script_runtime.cpp:1](../../../matching2/src/script/final_script_runtime.cpp#L1); [matching2/src/script/final_script_runtime.cpp:37](../../../matching2/src/script/final_script_runtime.cpp#L37); [matching2/include/th10/script/final_script_runtime.hpp:40](../../../matching2/include/th10/script/final_script_runtime.hpp#L40) |

## Separate file audit scope

Every file below remains pending file review, including files whose addresses have historical reviews. SHA-256 hashes are in JSON. Zero marker candidates does not remove a file from scope.

| File | Lines | Candidate addresses |
| --- | ---: | ---: |
| [matching2/src/app/fps_counter.cpp](../../../matching2/src/app/fps_counter.cpp) | 96 | 2 |
| [matching2/src/app/frame_clock.cpp](../../../matching2/src/app/frame_clock.cpp) | 127 | 3 |
| [matching2/src/app/game_main.cpp](../../../matching2/src/app/game_main.cpp) | 157 | 1 |
| [matching2/src/app/game_state_init.cpp](../../../matching2/src/app/game_state_init.cpp) | 130 | 1 |
| [matching2/src/app/main_tasks.cpp](../../../matching2/src/app/main_tasks.cpp) | 185 | 5 |
| [matching2/src/app/version_marker.cpp](../../../matching2/src/app/version_marker.cpp) | 30 | 1 |
| [matching2/src/archive/crypt.cpp](../../../matching2/src/archive/crypt.cpp) | 155 | 2 |
| [matching2/src/archive/dat.cpp](../../../matching2/src/archive/dat.cpp) | 321 | 8 |
| [matching2/src/archive/dat_file.cpp](../../../matching2/src/archive/dat_file.cpp) | 23 | 2 |
| [matching2/src/archive/lzss.cpp](../../../matching2/src/archive/lzss.cpp) | 194 | 1 |
| [matching2/src/archive/resource_manager.cpp](../../../matching2/src/archive/resource_manager.cpp) | 85 | 4 |
| [matching2/src/archive/score_save.cpp](../../../matching2/src/archive/score_save.cpp) | 318 | 4 |
| [matching2/src/game/animation_resource_lazy_fetch.cpp](../../../matching2/src/game/animation_resource_lazy_fetch.cpp) | 24 | 1 |
| [matching2/src/game/archive_cursor.cpp](../../../matching2/src/game/archive_cursor.cpp) | 102 | 1 |
| [matching2/src/game/archive_cursor_open.cpp](../../../matching2/src/game/archive_cursor_open.cpp) | 109 | 1 |
| [matching2/src/game/archive_cursor_read.cpp](../../../matching2/src/game/archive_cursor_read.cpp) | 106 | 1 |
| [matching2/src/game/ascii_overlay_callbacks.cpp](../../../matching2/src/game/ascii_overlay_callbacks.cpp) | 56 | 3 |
| [matching2/src/game/ascii_overlay_callbacks_overlay.cpp](../../../matching2/src/game/ascii_overlay_callbacks_overlay.cpp) | 4 | 1 |
| [matching2/src/game/asset_buffer.cpp](../../../matching2/src/game/asset_buffer.cpp) | 19 | 1 |
| [matching2/src/game/boss_gauge.cpp](../../../matching2/src/game/boss_gauge.cpp) | 58 | 2 |
| [matching2/src/game/boss_overlays.cpp](../../../matching2/src/game/boss_overlays.cpp) | 60 | 2 |
| [matching2/src/game/bullet.cpp](../../../matching2/src/game/bullet.cpp) | 778 | 18 |
| [matching2/src/game/bullet_anim_release.cpp](../../../matching2/src/game/bullet_anim_release.cpp) | 52 | 1 |
| [matching2/src/game/bullet_manager.cpp](../../../matching2/src/game/bullet_manager.cpp) | 439 | 9 |
| [matching2/src/game/bullet_manager_overlay.cpp](../../../matching2/src/game/bullet_manager_overlay.cpp) | 4 | 1 |
| [matching2/src/game/bullet_runtime_update.cpp](../../../matching2/src/game/bullet_runtime_update.cpp) | 84 | 1 |
| [matching2/src/game/effect_accel.cpp](../../../matching2/src/game/effect_accel.cpp) | 49 | 1 |
| [matching2/src/game/effect_indicator_queue.cpp](../../../matching2/src/game/effect_indicator_queue.cpp) | 3 | 1 |
| [matching2/src/game/effect_indicator_slots.cpp](../../../matching2/src/game/effect_indicator_slots.cpp) | 179 | 6 |
| [matching2/src/game/effect_manager_destroy.cpp](../../../matching2/src/game/effect_manager_destroy.cpp) | 45 | 1 |
| [matching2/src/game/effect_pool_update.cpp](../../../matching2/src/game/effect_pool_update.cpp) | 122 | 1 |
| [matching2/src/game/ending_screen.cpp](../../../matching2/src/game/ending_screen.cpp) | 58 | 1 |
| [matching2/src/game/ending_text.cpp](../../../matching2/src/game/ending_text.cpp) | 83 | 1 |
| [matching2/src/game/enemy_drop_sweep.cpp](../../../matching2/src/game/enemy_drop_sweep.cpp) | 48 | 1 |
| [matching2/src/game/enemy_grid_scan.cpp](../../../matching2/src/game/enemy_grid_scan.cpp) | 44 | 1 |
| [matching2/src/game/enemy_grid_scan_overlay.cpp](../../../matching2/src/game/enemy_grid_scan_overlay.cpp) | 4 | 0 |
| [matching2/src/game/enemy_lifecycle.cpp](../../../matching2/src/game/enemy_lifecycle.cpp) | 261 | 6 |
| [matching2/src/game/enemy_lifecycle_overlay.cpp](../../../matching2/src/game/enemy_lifecycle_overlay.cpp) | 4 | 1 |
| [matching2/src/game/enemy_motion_steps.cpp](../../../matching2/src/game/enemy_motion_steps.cpp) | 251 | 6 |
| [matching2/src/game/enemy_projectile_spawn.cpp](../../../matching2/src/game/enemy_projectile_spawn.cpp) | 32 | 1 |
| [matching2/src/game/entity.cpp](../../../matching2/src/game/entity.cpp) | 248 | 9 |
| [matching2/src/game/entity_color_slot.cpp](../../../matching2/src/game/entity_color_slot.cpp) | 64 | 1 |
| [matching2/src/game/entity_movement_slot.cpp](../../../matching2/src/game/entity_movement_slot.cpp) | 54 | 1 |
| [matching2/src/game/entity_region_sweep.cpp](../../../matching2/src/game/entity_region_sweep.cpp) | 117 | 1 |
| [matching2/src/game/event_script_runtime.cpp](../../../matching2/src/game/event_script_runtime.cpp) | 220 | 2 |
| [matching2/src/game/faith_gauge.cpp](../../../matching2/src/game/faith_gauge.cpp) | 54 | 1 |
| [matching2/src/game/floating_text_draw.cpp](../../../matching2/src/game/floating_text_draw.cpp) | 77 | 1 |
| [matching2/src/game/frame_counter.cpp](../../../matching2/src/game/frame_counter.cpp) | 11 | 1 |
| [matching2/src/game/game_config_defaults.cpp](../../../matching2/src/game/game_config_defaults.cpp) | 43 | 1 |
| [matching2/src/game/game_mode_switch.cpp](../../../matching2/src/game/game_mode_switch.cpp) | 125 | 1 |
| [matching2/src/game/game_state.cpp](../../../matching2/src/game/game_state.cpp) | 612 | 8 |
| [matching2/src/game/game_state_overlay_draw.cpp](../../../matching2/src/game/game_state_overlay_draw.cpp) | 13 | 1 |
| [matching2/src/game/game_thread.cpp](../../../matching2/src/game/game_thread.cpp) | 396 | 6 |
| [matching2/src/game/game_thread_overlay.cpp](../../../matching2/src/game/game_thread_overlay.cpp) | 4 | 1 |
| [matching2/src/game/game_thread_queue.cpp](../../../matching2/src/game/game_thread_queue.cpp) | 123 | 4 |
| [matching2/src/game/game_thread_text_draw.cpp](../../../matching2/src/game/game_thread_text_draw.cpp) | 84 | 2 |
| [matching2/src/game/game_ui_create.cpp](../../../matching2/src/game/game_ui_create.cpp) | 45 | 1 |
| [matching2/src/game/gameplay_final_runtime.cpp](../../../matching2/src/game/gameplay_final_runtime.cpp) | 1257 | 2 |
| [matching2/src/game/gameplay_render_pass.cpp](../../../matching2/src/game/gameplay_render_pass.cpp) | 104 | 1 |
| [matching2/src/game/input_recorder.cpp](../../../matching2/src/game/input_recorder.cpp) | 78 | 1 |
| [matching2/src/game/item_field_contact.cpp](../../../matching2/src/game/item_field_contact.cpp) | 38 | 1 |
| [matching2/src/game/item_scatter.cpp](../../../matching2/src/game/item_scatter.cpp) | 55 | 1 |
| [matching2/src/game/item_spawn.cpp](../../../matching2/src/game/item_spawn.cpp) | 95 | 1 |
| [matching2/src/game/key_config.cpp](../../../matching2/src/game/key_config.cpp) | 30 | 1 |
| [matching2/src/game/key_config_overlay.cpp](../../../matching2/src/game/key_config_overlay.cpp) | 4 | 1 |
| [matching2/src/game/laser_grow_update.cpp](../../../matching2/src/game/laser_grow_update.cpp) | 118 | 1 |
| [matching2/src/game/laser_line.cpp](../../../matching2/src/game/laser_line.cpp) | 173 | 2 |
| [matching2/src/game/laser_segment_cut.cpp](../../../matching2/src/game/laser_segment_cut.cpp) | 236 | 4 |
| [matching2/src/game/line_effect_sweep.cpp](../../../matching2/src/game/line_effect_sweep.cpp) | 68 | 1 |
| [matching2/src/game/linked_pool_append.cpp](../../../matching2/src/game/linked_pool_append.cpp) | 38 | 1 |
| [matching2/src/game/linked_pool_release.cpp](../../../matching2/src/game/linked_pool_release.cpp) | 59 | 1 |
| [matching2/src/game/main_menu_dispatch.cpp](../../../matching2/src/game/main_menu_dispatch.cpp) | 670 | 6 |
| [matching2/src/game/main_menu_dispatch_overlay.cpp](../../../matching2/src/game/main_menu_dispatch_overlay.cpp) | 4 | 1 |
| [matching2/src/game/manager_factories.cpp](../../../matching2/src/game/manager_factories.cpp) | 469 | 15 |
| [matching2/src/game/manager_teardown.cpp](../../../matching2/src/game/manager_teardown.cpp) | 263 | 15 |
| [matching2/src/game/menu.cpp](../../../matching2/src/game/menu.cpp) | 35 | 1 |
| [matching2/src/game/menu_flow_updates.cpp](../../../matching2/src/game/menu_flow_updates.cpp) | 217 | 3 |
| [matching2/src/game/message_host_init.cpp](../../../matching2/src/game/message_host_init.cpp) | 93 | 1 |
| [matching2/src/game/message_manager_init.cpp](../../../matching2/src/game/message_manager_init.cpp) | 32 | 1 |
| [matching2/src/game/music_room.cpp](../../../matching2/src/game/music_room.cpp) | 53 | 1 |
| [matching2/src/game/music_room_overlay.cpp](../../../matching2/src/game/music_room_overlay.cpp) | 4 | 1 |
| [matching2/src/game/name_entry.cpp](../../../matching2/src/game/name_entry.cpp) | 153 | 3 |
| [matching2/src/game/object_factories.cpp](../../../matching2/src/game/object_factories.cpp) | 67 | 3 |
| [matching2/src/game/particle_seed.cpp](../../../matching2/src/game/particle_seed.cpp) | 19 | 1 |
| [matching2/src/game/pause_menu_reset.cpp](../../../matching2/src/game/pause_menu_reset.cpp) | 46 | 1 |
| [matching2/src/game/pause_result_open.cpp](../../../matching2/src/game/pause_result_open.cpp) | 98 | 2 |
| [matching2/src/game/player.cpp](../../../matching2/src/game/player.cpp) | 495 | 11 |
| [matching2/src/game/player_front_runtime.cpp](../../../matching2/src/game/player_front_runtime.cpp) | 243 | 2 |
| [matching2/src/game/player_motion.cpp](../../../matching2/src/game/player_motion.cpp) | 142 | 5 |
| [matching2/src/game/player_pickup_sweep.cpp](../../../matching2/src/game/player_pickup_sweep.cpp) | 127 | 1 |
| [matching2/src/game/player_reset.cpp](../../../matching2/src/game/player_reset.cpp) | 17 | 1 |
| [matching2/src/game/player_runtime_init.cpp](../../../matching2/src/game/player_runtime_init.cpp) | 391 | 4 |
| [matching2/src/game/player_scheduler.cpp](../../../matching2/src/game/player_scheduler.cpp) | 32 | 1 |
| [matching2/src/game/pool_constructors.cpp](../../../matching2/src/game/pool_constructors.cpp) | 310 | 10 |
| [matching2/src/game/practice_stage_menu.cpp](../../../matching2/src/game/practice_stage_menu.cpp) | 99 | 1 |
| [matching2/src/game/progress.cpp](../../../matching2/src/game/progress.cpp) | 36 | 2 |
| [matching2/src/game/progress_worker.cpp](../../../matching2/src/game/progress_worker.cpp) | 41 | 1 |
| [matching2/src/game/projectile_bounce.cpp](../../../matching2/src/game/projectile_bounce.cpp) | 51 | 1 |
| [matching2/src/game/projectile_command_runtime.cpp](../../../matching2/src/game/projectile_command_runtime.cpp) | 5 | 1 |
| [matching2/src/game/rank_level.cpp](../../../matching2/src/game/rank_level.cpp) | 21 | 1 |
| [matching2/src/game/recovery_leaves.cpp](../../../matching2/src/game/recovery_leaves.cpp) | 1151 | 83 |
| [matching2/src/game/replay_browser_draw.cpp](../../../matching2/src/game/replay_browser_draw.cpp) | 8 | 1 |
| [matching2/src/game/replay_file_load.cpp](../../../matching2/src/game/replay_file_load.cpp) | 38 | 1 |
| [matching2/src/game/replay_large_runtime.cpp](../../../matching2/src/game/replay_large_runtime.cpp) | 12 | 2 |
| [matching2/src/game/replay_menu_draw.cpp](../../../matching2/src/game/replay_menu_draw.cpp) | 88 | 1 |
| [matching2/src/game/replay_menu_runtime.cpp](../../../matching2/src/game/replay_menu_runtime.cpp) | 40 | 2 |
| [matching2/src/game/replay_progress.cpp](../../../matching2/src/game/replay_progress.cpp) | 72 | 2 |
| [matching2/src/game/replay_runtime_bootstrap.cpp](../../../matching2/src/game/replay_runtime_bootstrap.cpp) | 5 | 1 |
| [matching2/src/game/replay_score_draw.cpp](../../../matching2/src/game/replay_score_draw.cpp) | 27 | 1 |
| [matching2/src/game/replay_spell_list.cpp](../../../matching2/src/game/replay_spell_list.cpp) | 64 | 1 |
| [matching2/src/game/replay_stage_name_draw.cpp](../../../matching2/src/game/replay_stage_name_draw.cpp) | 8 | 1 |
| [matching2/src/game/result_choice_menu.cpp](../../../matching2/src/game/result_choice_menu.cpp) | 4 | 1 |
| [matching2/src/game/result_menu_draw.cpp](../../../matching2/src/game/result_menu_draw.cpp) | 135 | 1 |
| [matching2/src/game/result_menu_open.cpp](../../../matching2/src/game/result_menu_open.cpp) | 42 | 1 |
| [matching2/src/game/result_overlay.cpp](../../../matching2/src/game/result_overlay.cpp) | 55 | 1 |
| [matching2/src/game/result_screen_effects.cpp](../../../matching2/src/game/result_screen_effects.cpp) | 37 | 1 |
| [matching2/src/game/scheduler.cpp](../../../matching2/src/game/scheduler.cpp) | 263 | 13 |
| [matching2/src/game/score.cpp](../../../matching2/src/game/score.cpp) | 665 | 35 |
| [matching2/src/game/score_cleanup.cpp](../../../matching2/src/game/score_cleanup.cpp) | 16 | 1 |
| [matching2/src/game/score_file.cpp](../../../matching2/src/game/score_file.cpp) | 198 | 3 |
| [matching2/src/game/score_hud_update.cpp](../../../matching2/src/game/score_hud_update.cpp) | 67 | 1 |
| [matching2/src/game/score_menu_rows.cpp](../../../matching2/src/game/score_menu_rows.cpp) | 58 | 1 |
| [matching2/src/game/score_popup.cpp](../../../matching2/src/game/score_popup.cpp) | 52 | 1 |
| [matching2/src/game/score_queue.cpp](../../../matching2/src/game/score_queue.cpp) | 45 | 1 |
| [matching2/src/game/score_runtime_ui_update.cpp](../../../matching2/src/game/score_runtime_ui_update.cpp) | 104 | 1 |
| [matching2/src/game/score_tasks.cpp](../../../matching2/src/game/score_tasks.cpp) | 134 | 3 |
| [matching2/src/game/score_timer_leaves.cpp](../../../matching2/src/game/score_timer_leaves.cpp) | 36 | 4 |
| [matching2/src/game/score_view_ctor.cpp](../../../matching2/src/game/score_view_ctor.cpp) | 32 | 1 |
| [matching2/src/game/shot_practice_menu.cpp](../../../matching2/src/game/shot_practice_menu.cpp) | 4 | 1 |
| [matching2/src/game/slot_lock_leaves.cpp](../../../matching2/src/game/slot_lock_leaves.cpp) | 29 | 2 |
| [matching2/src/game/slot_snapshot.cpp](../../../matching2/src/game/slot_snapshot.cpp) | 156 | 1 |
| [matching2/src/game/spell_card_dispatch.cpp](../../../matching2/src/game/spell_card_dispatch.cpp) | 58 | 1 |
| [matching2/src/game/spell_card_end.cpp](../../../matching2/src/game/spell_card_end.cpp) | 58 | 1 |
| [matching2/src/game/spell_timeout.cpp](../../../matching2/src/game/spell_timeout.cpp) | 71 | 1 |
| [matching2/src/game/spell_timer.cpp](../../../matching2/src/game/spell_timer.cpp) | 94 | 1 |
| [matching2/src/game/sprite_descriptor.cpp](../../../matching2/src/game/sprite_descriptor.cpp) | 34 | 1 |
| [matching2/src/game/sprite_test_overlay.cpp](../../../matching2/src/game/sprite_test_overlay.cpp) | 112 | 2 |
| [matching2/src/game/stage_background.cpp](../../../matching2/src/game/stage_background.cpp) | 73 | 2 |
| [matching2/src/game/stage_background_overlay.cpp](../../../matching2/src/game/stage_background_overlay.cpp) | 4 | 1 |
| [matching2/src/game/stage_controller_tick.cpp](../../../matching2/src/game/stage_controller_tick.cpp) | 32 | 1 |
| [matching2/src/game/stage_entry.cpp](../../../matching2/src/game/stage_entry.cpp) | 191 | 4 |
| [matching2/src/game/stage_focus_fade.cpp](../../../matching2/src/game/stage_focus_fade.cpp) | 18 | 1 |
| [matching2/src/game/stage_slot_state.cpp](../../../matching2/src/game/stage_slot_state.cpp) | 121 | 1 |
| [matching2/src/game/stage_std.cpp](../../../matching2/src/game/stage_std.cpp) | 147 | 0 |
| [matching2/src/game/stage_text.cpp](../../../matching2/src/game/stage_text.cpp) | 51 | 3 |
| [matching2/src/game/stage_timeline.cpp](../../../matching2/src/game/stage_timeline.cpp) | 138 | 0 |
| [matching2/src/game/stage_tip_manager.cpp](../../../matching2/src/game/stage_tip_manager.cpp) | 287 | 5 |
| [matching2/src/game/stage_tip_parser.cpp](../../../matching2/src/game/stage_tip_parser.cpp) | 343 | 1 |
| [matching2/src/game/stage_tips.cpp](../../../matching2/src/game/stage_tips.cpp) | 19 | 1 |
| [matching2/src/game/stage_update.cpp](../../../matching2/src/game/stage_update.cpp) | 140 | 1 |
| [matching2/src/game/stats_task.cpp](../../../matching2/src/game/stats_task.cpp) | 51 | 2 |
| [matching2/src/game/task_registration.cpp](../../../matching2/src/game/task_registration.cpp) | 260 | 8 |
| [matching2/src/game/thread_spawn.cpp](../../../matching2/src/game/thread_spawn.cpp) | 38 | 1 |
| [matching2/src/game/title_assets.cpp](../../../matching2/src/game/title_assets.cpp) | 52 | 1 |
| [matching2/src/game/title_main_menu.cpp](../../../matching2/src/game/title_main_menu.cpp) | 207 | 2 |
| [matching2/src/game/title_menu_runtime.cpp](../../../matching2/src/game/title_menu_runtime.cpp) | 7 | 1 |
| [matching2/src/game/title_options_menu.cpp](../../../matching2/src/game/title_options_menu.cpp) | 124 | 2 |
| [matching2/src/game/trajectory_evaluate.cpp](../../../matching2/src/game/trajectory_evaluate.cpp) | 237 | 3 |
| [matching2/src/game/trigger_activation.cpp](../../../matching2/src/game/trigger_activation.cpp) | 56 | 1 |
| [matching2/src/game/trigger_region.cpp](../../../matching2/src/game/trigger_region.cpp) | 43 | 1 |
| [matching2/src/game/ui_final_runtime.cpp](../../../matching2/src/game/ui_final_runtime.cpp) | 1720 | 6 |
| [matching2/src/game/version_list.cpp](../../../matching2/src/game/version_list.cpp) | 41 | 1 |
| [matching2/src/game/weather_pool.cpp](../../../matching2/src/game/weather_pool.cpp) | 31 | 1 |
| [matching2/src/math/angle.cpp](../../../matching2/src/math/angle.cpp) | 43 | 2 |
| [matching2/src/math/easing.cpp](../../../matching2/src/math/easing.cpp) | 51 | 1 |
| [matching2/src/math/interpolators.cpp](../../../matching2/src/math/interpolators.cpp) | 153 | 4 |
| [matching2/src/math/math_utils.cpp](../../../matching2/src/math/math_utils.cpp) | 73 | 2 |
| [matching2/src/math/oriented_rect.cpp](../../../matching2/src/math/oriented_rect.cpp) | 24 | 1 |
| [matching2/src/math/param_block_interp.cpp](../../../matching2/src/math/param_block_interp.cpp) | 147 | 2 |
| [matching2/src/math/random_vector.cpp](../../../matching2/src/math/random_vector.cpp) | 15 | 1 |
| [matching2/src/math/rng.cpp](../../../matching2/src/math/rng.cpp) | 68 | 4 |
| [matching2/src/math/timer.cpp](../../../matching2/src/math/timer.cpp) | 94 | 6 |
| [matching2/src/math/vector.cpp](../../../matching2/src/math/vector.cpp) | 17 | 2 |
| [matching2/src/math/vector2_polar.cpp](../../../matching2/src/math/vector2_polar.cpp) | 11 | 1 |
| [matching2/src/math/vector3_cross.cpp](../../../matching2/src/math/vector3_cross.cpp) | 20 | 1 |
| [matching2/src/platform/all_source_runtime.cpp](../../../matching2/src/platform/all_source_runtime.cpp) | 405 | 4 |
| [matching2/src/platform/bgm_streamer_refill.cpp](../../../matching2/src/platform/bgm_streamer_refill.cpp) | 90 | 1 |
| [matching2/src/platform/dinput_device_setup.cpp](../../../matching2/src/platform/dinput_device_setup.cpp) | 67 | 1 |
| [matching2/src/platform/file.cpp](../../../matching2/src/platform/file.cpp) | 366 | 18 |
| [matching2/src/platform/final_input_runtime.cpp](../../../matching2/src/platform/final_input_runtime.cpp) | 133 | 1 |
| [matching2/src/platform/font_cache_init.cpp](../../../matching2/src/platform/font_cache_init.cpp) | 24 | 1 |
| [matching2/src/platform/font_surface_blend.cpp](../../../matching2/src/platform/font_surface_blend.cpp) | 111 | 1 |
| [matching2/src/platform/font_texture_draw.cpp](../../../matching2/src/platform/font_texture_draw.cpp) | 56 | 2 |
| [matching2/src/platform/gdi_font_cache.cpp](../../../matching2/src/platform/gdi_font_cache.cpp) | 27 | 2 |
| [matching2/src/platform/gdi_surface.cpp](../../../matching2/src/platform/gdi_surface.cpp) | 69 | 1 |
| [matching2/src/platform/joystick_poll.cpp](../../../matching2/src/platform/joystick_poll.cpp) | 165 | 2 |
| [matching2/src/platform/joystick_probe.cpp](../../../matching2/src/platform/joystick_probe.cpp) | 24 | 1 |
| [matching2/src/platform/joystick_property.cpp](../../../matching2/src/platform/joystick_property.cpp) | 40 | 1 |
| [matching2/src/platform/joystick_property_overlay.cpp](../../../matching2/src/platform/joystick_property_overlay.cpp) | 4 | 1 |
| [matching2/src/platform/memory_file.cpp](../../../matching2/src/platform/memory_file.cpp) | 279 | 15 |
| [matching2/src/platform/midi_event_runtime.cpp](../../../matching2/src/platform/midi_event_runtime.cpp) | 5 | 1 |
| [matching2/src/platform/midi_sequencer.cpp](../../../matching2/src/platform/midi_sequencer.cpp) | 173 | 4 |
| [matching2/src/platform/midi_worker.cpp](../../../matching2/src/platform/midi_worker.cpp) | 64 | 2 |
| [matching2/src/platform/midi_worker_overlay.cpp](../../../matching2/src/platform/midi_worker_overlay.cpp) | 4 | 1 |
| [matching2/src/platform/midi_worker_stop.cpp](../../../matching2/src/platform/midi_worker_stop.cpp) | 45 | 1 |
| [matching2/src/platform/pack_file_loader.cpp](../../../matching2/src/platform/pack_file_loader.cpp) | 106 | 2 |
| [matching2/src/platform/path.cpp](../../../matching2/src/platform/path.cpp) | 79 | 3 |
| [matching2/src/platform/process.cpp](../../../matching2/src/platform/process.cpp) | 110 | 6 |
| [matching2/src/platform/resource_file.cpp](../../../matching2/src/platform/resource_file.cpp) | 59 | 3 |
| [matching2/src/platform/sound_commands.cpp](../../../matching2/src/platform/sound_commands.cpp) | 258 | 9 |
| [matching2/src/platform/sound_device_init.cpp](../../../matching2/src/platform/sound_device_init.cpp) | 137 | 4 |
| [matching2/src/platform/sound_dummy.cpp](../../../matching2/src/platform/sound_dummy.cpp) | 22 | 1 |
| [matching2/src/platform/sound_effect_buffers.cpp](../../../matching2/src/platform/sound_effect_buffers.cpp) | 46 | 1 |
| [matching2/src/platform/sound_event_queue.cpp](../../../matching2/src/platform/sound_event_queue.cpp) | 35 | 1 |
| [matching2/src/platform/sound_fade.cpp](../../../matching2/src/platform/sound_fade.cpp) | 44 | 1 |
| [matching2/src/platform/sound_float_forward.cpp](../../../matching2/src/platform/sound_float_forward.cpp) | 9 | 1 |
| [matching2/src/platform/sound_leaves.cpp](../../../matching2/src/platform/sound_leaves.cpp) | 27 | 2 |
| [matching2/src/platform/sound_stream_create.cpp](../../../matching2/src/platform/sound_stream_create.cpp) | 77 | 1 |
| [matching2/src/platform/sound_stream_start.cpp](../../../matching2/src/platform/sound_stream_start.cpp) | 46 | 1 |
| [matching2/src/platform/sound_stream_thread.cpp](../../../matching2/src/platform/sound_stream_thread.cpp) | 34 | 1 |
| [matching2/src/platform/sound_worker.cpp](../../../matching2/src/platform/sound_worker.cpp) | 39 | 1 |
| [matching2/src/platform/text_log.cpp](../../../matching2/src/platform/text_log.cpp) | 66 | 2 |
| [matching2/src/platform/win32_timer.cpp](../../../matching2/src/platform/win32_timer.cpp) | 19 | 1 |
| [matching2/src/platform/window.cpp](../../../matching2/src/platform/window.cpp) | 625 | 14 |
| [matching2/src/platform/worker_start.cpp](../../../matching2/src/platform/worker_start.cpp) | 26 | 1 |
| [matching2/src/render/all_source_anm_runtime.cpp](../../../matching2/src/render/all_source_anm_runtime.cpp) | 796 | 0 |
| [matching2/src/render/anchored_quad_draw.cpp](../../../matching2/src/render/anchored_quad_draw.cpp) | 5 | 1 |
| [matching2/src/render/animation_manager.cpp](../../../matching2/src/render/animation_manager.cpp) | 1421 | 52 |
| [matching2/src/render/animation_slot.cpp](../../../matching2/src/render/animation_slot.cpp) | 43 | 1 |
| [matching2/src/render/anm_archive.cpp](../../../matching2/src/render/anm_archive.cpp) | 61 | 2 |
| [matching2/src/render/anm_batch_flush.cpp](../../../matching2/src/render/anm_batch_flush.cpp) | 36 | 1 |
| [matching2/src/render/anm_blend_state.cpp](../../../matching2/src/render/anm_blend_state.cpp) | 72 | 1 |
| [matching2/src/render/anm_clip_quad.cpp](../../../matching2/src/render/anm_clip_quad.cpp) | 39 | 1 |
| [matching2/src/render/anm_distance_color.cpp](../../../matching2/src/render/anm_distance_color.cpp) | 84 | 1 |
| [matching2/src/render/anm_entry_load.cpp](../../../matching2/src/render/anm_entry_load.cpp) | 171 | 6 |
| [matching2/src/render/anm_file.cpp](../../../matching2/src/render/anm_file.cpp) | 164 | 0 |
| [matching2/src/render/anm_handle_release.cpp](../../../matching2/src/render/anm_handle_release.cpp) | 46 | 1 |
| [matching2/src/render/anm_pending_service.cpp](../../../matching2/src/render/anm_pending_service.cpp) | 36 | 1 |
| [matching2/src/render/anm_pending_service_overlay.cpp](../../../matching2/src/render/anm_pending_service_overlay.cpp) | 4 | 1 |
| [matching2/src/render/anm_propagate.cpp](../../../matching2/src/render/anm_propagate.cpp) | 39 | 2 |
| [matching2/src/render/anm_record_walk.cpp](../../../matching2/src/render/anm_record_walk.cpp) | 40 | 1 |
| [matching2/src/render/anm_script_table_sweep.cpp](../../../matching2/src/render/anm_script_table_sweep.cpp) | 39 | 1 |
| [matching2/src/render/anm_sprite_quad.cpp](../../../matching2/src/render/anm_sprite_quad.cpp) | 353 | 0 |
| [matching2/src/render/anm_surface_restore.cpp](../../../matching2/src/render/anm_surface_restore.cpp) | 93 | 3 |
| [matching2/src/render/anm_texture_upload.cpp](../../../matching2/src/render/anm_texture_upload.cpp) | 137 | 3 |
| [matching2/src/render/anm_vm_draw_dispatch.cpp](../../../matching2/src/render/anm_vm_draw_dispatch.cpp) | 83 | 1 |
| [matching2/src/render/camera_apply.cpp](../../../matching2/src/render/camera_apply.cpp) | 66 | 1 |
| [matching2/src/render/camera_defaults.cpp](../../../matching2/src/render/camera_defaults.cpp) | 119 | 1 |
| [matching2/src/render/camera_setup.cpp](../../../matching2/src/render/camera_setup.cpp) | 84 | 5 |
| [matching2/src/render/composite_passes.cpp](../../../matching2/src/render/composite_passes.cpp) | 97 | 1 |
| [matching2/src/render/d3d_init.cpp](../../../matching2/src/render/d3d_init.cpp) | 277 | 1 |
| [matching2/src/render/d3d_resource_manager.cpp](../../../matching2/src/render/d3d_resource_manager.cpp) | 60 | 4 |
| [matching2/src/render/default_viewport.cpp](../../../matching2/src/render/default_viewport.cpp) | 24 | 1 |
| [matching2/src/render/device_reset.cpp](../../../matching2/src/render/device_reset.cpp) | 56 | 1 |
| [matching2/src/render/edge_strip_draw.cpp](../../../matching2/src/render/edge_strip_draw.cpp) | 44 | 1 |
| [matching2/src/render/edge_strips.cpp](../../../matching2/src/render/edge_strips.cpp) | 90 | 2 |
| [matching2/src/render/effect_ring.cpp](../../../matching2/src/render/effect_ring.cpp) | 48 | 1 |
| [matching2/src/render/effect_ring_update.cpp](../../../matching2/src/render/effect_ring_update.cpp) | 95 | 1 |
| [matching2/src/render/faded_quad_draw.cpp](../../../matching2/src/render/faded_quad_draw.cpp) | 49 | 1 |
| [matching2/src/render/final_quad_pipeline.cpp](../../../matching2/src/render/final_quad_pipeline.cpp) | 134 | 2 |
| [matching2/src/render/fog_disable.cpp](../../../matching2/src/render/fog_disable.cpp) | 21 | 1 |
| [matching2/src/render/game_render_targets.cpp](../../../matching2/src/render/game_render_targets.cpp) | 138 | 3 |
| [matching2/src/render/image_alpha_transform.cpp](../../../matching2/src/render/image_alpha_transform.cpp) | 40 | 1 |
| [matching2/src/render/projection_quads.cpp](../../../matching2/src/render/projection_quads.cpp) | 135 | 3 |
| [matching2/src/render/quad_build_anchored.cpp](../../../matching2/src/render/quad_build_anchored.cpp) | 41 | 1 |
| [matching2/src/render/quad_transform_draw.cpp](../../../matching2/src/render/quad_transform_draw.cpp) | 110 | 1 |
| [matching2/src/render/quad_vertex_append.cpp](../../../matching2/src/render/quad_vertex_append.cpp) | 27 | 1 |
| [matching2/src/render/queued_anm_cleanup.cpp](../../../matching2/src/render/queued_anm_cleanup.cpp) | 31 | 1 |
| [matching2/src/render/recovered_render_leaves.cpp](../../../matching2/src/render/recovered_render_leaves.cpp) | 222 | 0 |
| [matching2/src/render/rect_fan_draw.cpp](../../../matching2/src/render/rect_fan_draw.cpp) | 47 | 1 |
| [matching2/src/render/render_stage_select.cpp](../../../matching2/src/render/render_stage_select.cpp) | 20 | 1 |
| [matching2/src/render/render_state_sync.cpp](../../../matching2/src/render/render_state_sync.cpp) | 40 | 1 |
| [matching2/src/render/special_quad.cpp](../../../matching2/src/render/special_quad.cpp) | 42 | 2 |
| [matching2/src/render/texture_stage_reset.cpp](../../../matching2/src/render/texture_stage_reset.cpp) | 47 | 1 |
| [matching2/src/render/transparent_pixel_fill.cpp](../../../matching2/src/render/transparent_pixel_fill.cpp) | 120 | 1 |
| [matching2/src/render/transparent_pixel_fill_locked.cpp](../../../matching2/src/render/transparent_pixel_fill_locked.cpp) | 77 | 1 |
| [matching2/src/runtime/missing_edge.cpp](../../../matching2/src/runtime/missing_edge.cpp) | 15 | 0 |
| [matching2/src/script/anm_vm_tick.cpp](../../../matching2/src/script/anm_vm_tick.cpp) | 632 | 2 |
| [matching2/src/script/ecl_core_interpreter.cpp](../../../matching2/src/script/ecl_core_interpreter.cpp) | 1378 | 18 |
| [matching2/src/script/ecl_helpers.cpp](../../../matching2/src/script/ecl_helpers.cpp) | 431 | 0 |
| [matching2/src/script/ecl_name_table.cpp](../../../matching2/src/script/ecl_name_table.cpp) | 81 | 2 |
| [matching2/src/script/ecl_vm.cpp](../../../matching2/src/script/ecl_vm.cpp) | 1666 | 19 |
| [matching2/src/script/ecl_vm_children.cpp](../../../matching2/src/script/ecl_vm_children.cpp) | 162 | 3 |
| [matching2/src/script/entity_vm.cpp](../../../matching2/src/script/entity_vm.cpp) | 565 | 1 |
| [matching2/src/script/final_script_runtime.cpp](../../../matching2/src/script/final_script_runtime.cpp) | 49 | 2 |
| [matching2/src/script/prng.cpp](../../../matching2/src/script/prng.cpp) | 48 | 1 |
| [matching2/src/script/script_text_reader.cpp](../../../matching2/src/script/script_text_reader.cpp) | 54 | 1 |
| [matching2/src/script/stage_ecl_load.cpp](../../../matching2/src/script/stage_ecl_load.cpp) | 55 | 1 |
| [matching2/src/util/heap.cpp](../../../matching2/src/util/heap.cpp) | 313 | 21 |
| [matching2/src/util/legacy_string_funclets.cpp](../../../matching2/src/util/legacy_string_funclets.cpp) | 32 | 2 |
| [matching2/src/util/runtime_pool.cpp](../../../matching2/src/util/runtime_pool.cpp) | 27 | 2 |
| [matching2/include/cstdint](../../../matching2/include/cstdint) | 4 | 0 |
| [matching2/include/th10/app/fps_counter.hpp](../../../matching2/include/th10/app/fps_counter.hpp) | 35 | 0 |
| [matching2/include/th10/app/frame_clock.hpp](../../../matching2/include/th10/app/frame_clock.hpp) | 91 | 5 |
| [matching2/include/th10/app/game_main.hpp](../../../matching2/include/th10/app/game_main.hpp) | 102 | 6 |
| [matching2/include/th10/app/game_state_init.hpp](../../../matching2/include/th10/app/game_state_init.hpp) | 51 | 1 |
| [matching2/include/th10/app/main_tasks.hpp](../../../matching2/include/th10/app/main_tasks.hpp) | 147 | 12 |
| [matching2/include/th10/app/version_marker.hpp](../../../matching2/include/th10/app/version_marker.hpp) | 19 | 0 |
| [matching2/include/th10/archive/crypt.hpp](../../../matching2/include/th10/archive/crypt.hpp) | 35 | 2 |
| [matching2/include/th10/archive/dat.hpp](../../../matching2/include/th10/archive/dat.hpp) | 76 | 0 |
| [matching2/include/th10/archive/lzss.hpp](../../../matching2/include/th10/archive/lzss.hpp) | 18 | 0 |
| [matching2/include/th10/archive/resource_manager.hpp](../../../matching2/include/th10/archive/resource_manager.hpp) | 17 | 0 |
| [matching2/include/th10/archive/score_save.hpp](../../../matching2/include/th10/archive/score_save.hpp) | 75 | 4 |
| [matching2/include/th10/game/animation_resource_lazy_fetch.hpp](../../../matching2/include/th10/game/animation_resource_lazy_fetch.hpp) | 32 | 1 |
| [matching2/include/th10/game/archive_cursor.hpp](../../../matching2/include/th10/game/archive_cursor.hpp) | 44 | 1 |
| [matching2/include/th10/game/archive_cursor_open.hpp](../../../matching2/include/th10/game/archive_cursor_open.hpp) | 44 | 1 |
| [matching2/include/th10/game/archive_cursor_read.hpp](../../../matching2/include/th10/game/archive_cursor_read.hpp) | 36 | 1 |
| [matching2/include/th10/game/ascii_overlay_callbacks.hpp](../../../matching2/include/th10/game/ascii_overlay_callbacks.hpp) | 18 | 0 |
| [matching2/include/th10/game/asset_buffer.hpp](../../../matching2/include/th10/game/asset_buffer.hpp) | 14 | 0 |
| [matching2/include/th10/game/boss_gauge.hpp](../../../matching2/include/th10/game/boss_gauge.hpp) | 40 | 2 |
| [matching2/include/th10/game/boss_overlays.hpp](../../../matching2/include/th10/game/boss_overlays.hpp) | 27 | 0 |
| [matching2/include/th10/game/bullet_anim_release.hpp](../../../matching2/include/th10/game/bullet_anim_release.hpp) | 48 | 1 |
| [matching2/include/th10/game/bullet_manager.hpp](../../../matching2/include/th10/game/bullet_manager.hpp) | 177 | 0 |
| [matching2/include/th10/game/bullet_runtime_update.hpp](../../../matching2/include/th10/game/bullet_runtime_update.hpp) | 39 | 1 |
| [matching2/include/th10/game/effect_accel.hpp](../../../matching2/include/th10/game/effect_accel.hpp) | 19 | 0 |
| [matching2/include/th10/game/effect_indicator_queue.hpp](../../../matching2/include/th10/game/effect_indicator_queue.hpp) | 7 | 1 |
| [matching2/include/th10/game/effect_indicator_slots.hpp](../../../matching2/include/th10/game/effect_indicator_slots.hpp) | 128 | 4 |
| [matching2/include/th10/game/effect_manager_destroy.hpp](../../../matching2/include/th10/game/effect_manager_destroy.hpp) | 21 | 3 |
| [matching2/include/th10/game/effect_pool_update.hpp](../../../matching2/include/th10/game/effect_pool_update.hpp) | 89 | 1 |
| [matching2/include/th10/game/ending_screen.hpp](../../../matching2/include/th10/game/ending_screen.hpp) | 30 | 0 |
| [matching2/include/th10/game/ending_text.hpp](../../../matching2/include/th10/game/ending_text.hpp) | 60 | 2 |
| [matching2/include/th10/game/enemy_drop_sweep.hpp](../../../matching2/include/th10/game/enemy_drop_sweep.hpp) | 17 | 2 |
| [matching2/include/th10/game/enemy_grid_scan.hpp](../../../matching2/include/th10/game/enemy_grid_scan.hpp) | 15 | 0 |
| [matching2/include/th10/game/enemy_lifecycle.hpp](../../../matching2/include/th10/game/enemy_lifecycle.hpp) | 174 | 0 |
| [matching2/include/th10/game/enemy_motion_steps.hpp](../../../matching2/include/th10/game/enemy_motion_steps.hpp) | 133 | 0 |
| [matching2/include/th10/game/enemy_projectile_spawn.hpp](../../../matching2/include/th10/game/enemy_projectile_spawn.hpp) | 12 | 0 |
| [matching2/include/th10/game/entity.hpp](../../../matching2/include/th10/game/entity.hpp) | 307 | 4 |
| [matching2/include/th10/game/entity_color_slot.hpp](../../../matching2/include/th10/game/entity_color_slot.hpp) | 41 | 1 |
| [matching2/include/th10/game/entity_movement_slot.hpp](../../../matching2/include/th10/game/entity_movement_slot.hpp) | 45 | 1 |
| [matching2/include/th10/game/entity_region_sweep.hpp](../../../matching2/include/th10/game/entity_region_sweep.hpp) | 62 | 3 |
| [matching2/include/th10/game/event_script_runtime.hpp](../../../matching2/include/th10/game/event_script_runtime.hpp) | 37 | 0 |
| [matching2/include/th10/game/faith_gauge.hpp](../../../matching2/include/th10/game/faith_gauge.hpp) | 19 | 1 |
| [matching2/include/th10/game/floating_text_draw.hpp](../../../matching2/include/th10/game/floating_text_draw.hpp) | 5 | 1 |
| [matching2/include/th10/game/frame_counter.hpp](../../../matching2/include/th10/game/frame_counter.hpp) | 15 | 1 |
| [matching2/include/th10/game/game_config_defaults.hpp](../../../matching2/include/th10/game/game_config_defaults.hpp) | 29 | 1 |
| [matching2/include/th10/game/game_mode_switch.hpp](../../../matching2/include/th10/game/game_mode_switch.hpp) | 51 | 0 |
| [matching2/include/th10/game/game_state.hpp](../../../matching2/include/th10/game/game_state.hpp) | 94 | 0 |
| [matching2/include/th10/game/game_state_overlay_draw.hpp](../../../matching2/include/th10/game/game_state_overlay_draw.hpp) | 19 | 0 |
| [matching2/include/th10/game/game_thread_queue.hpp](../../../matching2/include/th10/game/game_thread_queue.hpp) | 53 | 1 |
| [matching2/include/th10/game/game_thread_text_draw.hpp](../../../matching2/include/th10/game/game_thread_text_draw.hpp) | 71 | 0 |
| [matching2/include/th10/game/game_ui_create.hpp](../../../matching2/include/th10/game/game_ui_create.hpp) | 21 | 2 |
| [matching2/include/th10/game/gameplay_final_runtime.hpp](../../../matching2/include/th10/game/gameplay_final_runtime.hpp) | 270 | 3 |
| [matching2/include/th10/game/gameplay_render_pass.hpp](../../../matching2/include/th10/game/gameplay_render_pass.hpp) | 58 | 1 |
| [matching2/include/th10/game/input_recorder.hpp](../../../matching2/include/th10/game/input_recorder.hpp) | 35 | 0 |
| [matching2/include/th10/game/item_field_contact.hpp](../../../matching2/include/th10/game/item_field_contact.hpp) | 22 | 0 |
| [matching2/include/th10/game/item_scatter.hpp](../../../matching2/include/th10/game/item_scatter.hpp) | 8 | 1 |
| [matching2/include/th10/game/item_spawn.hpp](../../../matching2/include/th10/game/item_spawn.hpp) | 44 | 1 |
| [matching2/include/th10/game/key_config.hpp](../../../matching2/include/th10/game/key_config.hpp) | 9 | 0 |
| [matching2/include/th10/game/laser_grow_update.hpp](../../../matching2/include/th10/game/laser_grow_update.hpp) | 5 | 1 |
| [matching2/include/th10/game/laser_line.hpp](../../../matching2/include/th10/game/laser_line.hpp) | 175 | 7 |
| [matching2/include/th10/game/laser_segment_cut.hpp](../../../matching2/include/th10/game/laser_segment_cut.hpp) | 49 | 2 |
| [matching2/include/th10/game/line_effect_sweep.hpp](../../../matching2/include/th10/game/line_effect_sweep.hpp) | 5 | 1 |
| [matching2/include/th10/game/linked_pool_append.hpp](../../../matching2/include/th10/game/linked_pool_append.hpp) | 45 | 1 |
| [matching2/include/th10/game/linked_pool_release.hpp](../../../matching2/include/th10/game/linked_pool_release.hpp) | 28 | 1 |
| [matching2/include/th10/game/main_menu_dispatch.hpp](../../../matching2/include/th10/game/main_menu_dispatch.hpp) | 70 | 1 |
| [matching2/include/th10/game/manager_factories.hpp](../../../matching2/include/th10/game/manager_factories.hpp) | 150 | 1 |
| [matching2/include/th10/game/manager_teardown.hpp](../../../matching2/include/th10/game/manager_teardown.hpp) | 89 | 15 |
| [matching2/include/th10/game/menu.hpp](../../../matching2/include/th10/game/menu.hpp) | 19 | 0 |
| [matching2/include/th10/game/menu_flow_updates.hpp](../../../matching2/include/th10/game/menu_flow_updates.hpp) | 64 | 3 |
| [matching2/include/th10/game/message_host_init.hpp](../../../matching2/include/th10/game/message_host_init.hpp) | 74 | 1 |
| [matching2/include/th10/game/message_manager_init.hpp](../../../matching2/include/th10/game/message_manager_init.hpp) | 34 | 1 |
| [matching2/include/th10/game/music_room.hpp](../../../matching2/include/th10/game/music_room.hpp) | 25 | 0 |
| [matching2/include/th10/game/name_entry.hpp](../../../matching2/include/th10/game/name_entry.hpp) | 64 | 1 |
| [matching2/include/th10/game/object_factories.hpp](../../../matching2/include/th10/game/object_factories.hpp) | 28 | 2 |
| [matching2/include/th10/game/particle_seed.hpp](../../../matching2/include/th10/game/particle_seed.hpp) | 19 | 0 |
| [matching2/include/th10/game/pause_menu_reset.hpp](../../../matching2/include/th10/game/pause_menu_reset.hpp) | 22 | 0 |
| [matching2/include/th10/game/pause_result_open.hpp](../../../matching2/include/th10/game/pause_result_open.hpp) | 53 | 0 |
| [matching2/include/th10/game/player.hpp](../../../matching2/include/th10/game/player.hpp) | 30 | 0 |
| [matching2/include/th10/game/player_front_runtime.hpp](../../../matching2/include/th10/game/player_front_runtime.hpp) | 66 | 0 |
| [matching2/include/th10/game/player_motion.hpp](../../../matching2/include/th10/game/player_motion.hpp) | 60 | 0 |
| [matching2/include/th10/game/player_pickup_sweep.hpp](../../../matching2/include/th10/game/player_pickup_sweep.hpp) | 71 | 1 |
| [matching2/include/th10/game/player_reset.hpp](../../../matching2/include/th10/game/player_reset.hpp) | 15 | 1 |
| [matching2/include/th10/game/player_runtime_init.hpp](../../../matching2/include/th10/game/player_runtime_init.hpp) | 85 | 2 |
| [matching2/include/th10/game/pool_constructors.hpp](../../../matching2/include/th10/game/pool_constructors.hpp) | 44 | 5 |
| [matching2/include/th10/game/practice_stage_menu.hpp](../../../matching2/include/th10/game/practice_stage_menu.hpp) | 49 | 1 |
| [matching2/include/th10/game/progress.hpp](../../../matching2/include/th10/game/progress.hpp) | 9 | 0 |
| [matching2/include/th10/game/progress_worker.hpp](../../../matching2/include/th10/game/progress_worker.hpp) | 22 | 1 |
| [matching2/include/th10/game/projectile_bounce.hpp](../../../matching2/include/th10/game/projectile_bounce.hpp) | 33 | 0 |
| [matching2/include/th10/game/projectile_command_runtime.hpp](../../../matching2/include/th10/game/projectile_command_runtime.hpp) | 5 | 0 |
| [matching2/include/th10/game/rank_level.hpp](../../../matching2/include/th10/game/rank_level.hpp) | 9 | 2 |
| [matching2/include/th10/game/recovery_leaves.hpp](../../../matching2/include/th10/game/recovery_leaves.hpp) | 291 | 0 |
| [matching2/include/th10/game/registered_clock.hpp](../../../matching2/include/th10/game/registered_clock.hpp) | 25 | 0 |
| [matching2/include/th10/game/replay_browser_draw.hpp](../../../matching2/include/th10/game/replay_browser_draw.hpp) | 9 | 0 |
| [matching2/include/th10/game/replay_file_load.hpp](../../../matching2/include/th10/game/replay_file_load.hpp) | 44 | 0 |
| [matching2/include/th10/game/replay_large_runtime.hpp](../../../matching2/include/th10/game/replay_large_runtime.hpp) | 7 | 0 |
| [matching2/include/th10/game/replay_menu_draw.hpp](../../../matching2/include/th10/game/replay_menu_draw.hpp) | 46 | 1 |
| [matching2/include/th10/game/replay_menu_runtime.hpp](../../../matching2/include/th10/game/replay_menu_runtime.hpp) | 16 | 0 |
| [matching2/include/th10/game/replay_progress.hpp](../../../matching2/include/th10/game/replay_progress.hpp) | 14 | 0 |
| [matching2/include/th10/game/replay_runtime_bootstrap.hpp](../../../matching2/include/th10/game/replay_runtime_bootstrap.hpp) | 8 | 1 |
| [matching2/include/th10/game/replay_score_draw.hpp](../../../matching2/include/th10/game/replay_score_draw.hpp) | 33 | 0 |
| [matching2/include/th10/game/replay_spell_list.hpp](../../../matching2/include/th10/game/replay_spell_list.hpp) | 30 | 1 |
| [matching2/include/th10/game/replay_stage_name_draw.hpp](../../../matching2/include/th10/game/replay_stage_name_draw.hpp) | 5 | 0 |
| [matching2/include/th10/game/result_choice_menu.hpp](../../../matching2/include/th10/game/result_choice_menu.hpp) | 9 | 1 |
| [matching2/include/th10/game/result_menu_draw.hpp](../../../matching2/include/th10/game/result_menu_draw.hpp) | 80 | 1 |
| [matching2/include/th10/game/result_menu_open.hpp](../../../matching2/include/th10/game/result_menu_open.hpp) | 56 | 0 |
| [matching2/include/th10/game/result_overlay.hpp](../../../matching2/include/th10/game/result_overlay.hpp) | 35 | 1 |
| [matching2/include/th10/game/result_screen_effects.hpp](../../../matching2/include/th10/game/result_screen_effects.hpp) | 28 | 0 |
| [matching2/include/th10/game/scheduler.hpp](../../../matching2/include/th10/game/scheduler.hpp) | 52 | 0 |
| [matching2/include/th10/game/score.hpp](../../../matching2/include/th10/game/score.hpp) | 131 | 0 |
| [matching2/include/th10/game/score_cleanup.hpp](../../../matching2/include/th10/game/score_cleanup.hpp) | 18 | 0 |
| [matching2/include/th10/game/score_file.hpp](../../../matching2/include/th10/game/score_file.hpp) | 55 | 4 |
| [matching2/include/th10/game/score_hud_update.hpp](../../../matching2/include/th10/game/score_hud_update.hpp) | 32 | 0 |
| [matching2/include/th10/game/score_menu_rows.hpp](../../../matching2/include/th10/game/score_menu_rows.hpp) | 5 | 1 |
| [matching2/include/th10/game/score_popup.hpp](../../../matching2/include/th10/game/score_popup.hpp) | 29 | 0 |
| [matching2/include/th10/game/score_queue.hpp](../../../matching2/include/th10/game/score_queue.hpp) | 35 | 1 |
| [matching2/include/th10/game/score_runtime_ui_update.hpp](../../../matching2/include/th10/game/score_runtime_ui_update.hpp) | 40 | 1 |
| [matching2/include/th10/game/score_tasks.hpp](../../../matching2/include/th10/game/score_tasks.hpp) | 63 | 0 |
| [matching2/include/th10/game/score_timer_leaves.hpp](../../../matching2/include/th10/game/score_timer_leaves.hpp) | 25 | 2 |
| [matching2/include/th10/game/score_view_ctor.hpp](../../../matching2/include/th10/game/score_view_ctor.hpp) | 18 | 1 |
| [matching2/include/th10/game/shot_practice_menu.hpp](../../../matching2/include/th10/game/shot_practice_menu.hpp) | 7 | 1 |
| [matching2/include/th10/game/slot_lock_leaves.hpp](../../../matching2/include/th10/game/slot_lock_leaves.hpp) | 24 | 2 |
| [matching2/include/th10/game/slot_snapshot.hpp](../../../matching2/include/th10/game/slot_snapshot.hpp) | 73 | 1 |
| [matching2/include/th10/game/spell_card_dispatch.hpp](../../../matching2/include/th10/game/spell_card_dispatch.hpp) | 72 | 0 |
| [matching2/include/th10/game/spell_card_end.hpp](../../../matching2/include/th10/game/spell_card_end.hpp) | 31 | 0 |
| [matching2/include/th10/game/spell_timeout.hpp](../../../matching2/include/th10/game/spell_timeout.hpp) | 52 | 0 |
| [matching2/include/th10/game/spell_timer.hpp](../../../matching2/include/th10/game/spell_timer.hpp) | 37 | 0 |
| [matching2/include/th10/game/sprite_descriptor.hpp](../../../matching2/include/th10/game/sprite_descriptor.hpp) | 11 | 0 |
| [matching2/include/th10/game/sprite_test_overlay.hpp](../../../matching2/include/th10/game/sprite_test_overlay.hpp) | 20 | 1 |
| [matching2/include/th10/game/stage_background.hpp](../../../matching2/include/th10/game/stage_background.hpp) | 42 | 0 |
| [matching2/include/th10/game/stage_controller_tick.hpp](../../../matching2/include/th10/game/stage_controller_tick.hpp) | 31 | 0 |
| [matching2/include/th10/game/stage_entry.hpp](../../../matching2/include/th10/game/stage_entry.hpp) | 172 | 14 |
| [matching2/include/th10/game/stage_focus_fade.hpp](../../../matching2/include/th10/game/stage_focus_fade.hpp) | 8 | 0 |
| [matching2/include/th10/game/stage_slot_state.hpp](../../../matching2/include/th10/game/stage_slot_state.hpp) | 84 | 1 |
| [matching2/include/th10/game/stage_std.hpp](../../../matching2/include/th10/game/stage_std.hpp) | 58 | 0 |
| [matching2/include/th10/game/stage_text.hpp](../../../matching2/include/th10/game/stage_text.hpp) | 20 | 0 |
| [matching2/include/th10/game/stage_timeline.hpp](../../../matching2/include/th10/game/stage_timeline.hpp) | 52 | 0 |
| [matching2/include/th10/game/stage_tip_parser.hpp](../../../matching2/include/th10/game/stage_tip_parser.hpp) | 21 | 0 |
| [matching2/include/th10/game/stage_tips.hpp](../../../matching2/include/th10/game/stage_tips.hpp) | 76 | 2 |
| [matching2/include/th10/game/stage_update.hpp](../../../matching2/include/th10/game/stage_update.hpp) | 63 | 0 |
| [matching2/include/th10/game/stats_task.hpp](../../../matching2/include/th10/game/stats_task.hpp) | 30 | 1 |
| [matching2/include/th10/game/task_registration.hpp](../../../matching2/include/th10/game/task_registration.hpp) | 113 | 6 |
| [matching2/include/th10/game/thread_spawn.hpp](../../../matching2/include/th10/game/thread_spawn.hpp) | 29 | 1 |
| [matching2/include/th10/game/title_assets.hpp](../../../matching2/include/th10/game/title_assets.hpp) | 35 | 0 |
| [matching2/include/th10/game/title_main_menu.hpp](../../../matching2/include/th10/game/title_main_menu.hpp) | 68 | 1 |
| [matching2/include/th10/game/title_menu_runtime.hpp](../../../matching2/include/th10/game/title_menu_runtime.hpp) | 9 | 1 |
| [matching2/include/th10/game/title_options_menu.hpp](../../../matching2/include/th10/game/title_options_menu.hpp) | 39 | 0 |
| [matching2/include/th10/game/trajectory_evaluate.hpp](../../../matching2/include/th10/game/trajectory_evaluate.hpp) | 47 | 3 |
| [matching2/include/th10/game/trigger_activation.hpp](../../../matching2/include/th10/game/trigger_activation.hpp) | 32 | 0 |
| [matching2/include/th10/game/trigger_region.hpp](../../../matching2/include/th10/game/trigger_region.hpp) | 29 | 0 |
| [matching2/include/th10/game/ui_final_runtime.hpp](../../../matching2/include/th10/game/ui_final_runtime.hpp) | 271 | 7 |
| [matching2/include/th10/game/version_list.hpp](../../../matching2/include/th10/game/version_list.hpp) | 19 | 1 |
| [matching2/include/th10/game/weather_pool.hpp](../../../matching2/include/th10/game/weather_pool.hpp) | 24 | 0 |
| [matching2/include/th10/math/angle.hpp](../../../matching2/include/th10/math/angle.hpp) | 4 | 0 |
| [matching2/include/th10/math/easing.hpp](../../../matching2/include/th10/math/easing.hpp) | 5 | 0 |
| [matching2/include/th10/math/interpolators.hpp](../../../matching2/include/th10/math/interpolators.hpp) | 56 | 4 |
| [matching2/include/th10/math/oriented_rect.hpp](../../../matching2/include/th10/math/oriented_rect.hpp) | 16 | 0 |
| [matching2/include/th10/math/param_block_interp.hpp](../../../matching2/include/th10/math/param_block_interp.hpp) | 38 | 0 |
| [matching2/include/th10/math/quantized_vector.hpp](../../../matching2/include/th10/math/quantized_vector.hpp) | 47 | 2 |
| [matching2/include/th10/math/random_vector.hpp](../../../matching2/include/th10/math/random_vector.hpp) | 6 | 0 |
| [matching2/include/th10/math/rng.hpp](../../../matching2/include/th10/math/rng.hpp) | 22 | 3 |
| [matching2/include/th10/math/timer.hpp](../../../matching2/include/th10/math/timer.hpp) | 33 | 0 |
| [matching2/include/th10/math/vector.hpp](../../../matching2/include/th10/math/vector.hpp) | 10 | 0 |
| [matching2/include/th10/math/vector2_polar.hpp](../../../matching2/include/th10/math/vector2_polar.hpp) | 5 | 1 |
| [matching2/include/th10/math/vector3_cross.hpp](../../../matching2/include/th10/math/vector3_cross.hpp) | 30 | 1 |
| [matching2/include/th10/platform/bgm_streamer_refill.hpp](../../../matching2/include/th10/platform/bgm_streamer_refill.hpp) | 49 | 2 |
| [matching2/include/th10/platform/dinput_device_setup.hpp](../../../matching2/include/th10/platform/dinput_device_setup.hpp) | 7 | 1 |
| [matching2/include/th10/platform/file.hpp](../../../matching2/include/th10/platform/file.hpp) | 70 | 0 |
| [matching2/include/th10/platform/final_input_runtime.hpp](../../../matching2/include/th10/platform/final_input_runtime.hpp) | 53 | 0 |
| [matching2/include/th10/platform/font_cache_init.hpp](../../../matching2/include/th10/platform/font_cache_init.hpp) | 16 | 0 |
| [matching2/include/th10/platform/font_surface_blend.hpp](../../../matching2/include/th10/platform/font_surface_blend.hpp) | 38 | 0 |
| [matching2/include/th10/platform/font_texture_draw.hpp](../../../matching2/include/th10/platform/font_texture_draw.hpp) | 32 | 2 |
| [matching2/include/th10/platform/gdi_font_cache.hpp](../../../matching2/include/th10/platform/gdi_font_cache.hpp) | 10 | 1 |
| [matching2/include/th10/platform/gdi_surface.hpp](../../../matching2/include/th10/platform/gdi_surface.hpp) | 43 | 0 |
| [matching2/include/th10/platform/joystick_poll.hpp](../../../matching2/include/th10/platform/joystick_poll.hpp) | 86 | 0 |
| [matching2/include/th10/platform/joystick_probe.hpp](../../../matching2/include/th10/platform/joystick_probe.hpp) | 28 | 2 |
| [matching2/include/th10/platform/joystick_property.hpp](../../../matching2/include/th10/platform/joystick_property.hpp) | 21 | 0 |
| [matching2/include/th10/platform/memory_file.hpp](../../../matching2/include/th10/platform/memory_file.hpp) | 89 | 1 |
| [matching2/include/th10/platform/midi.hpp](../../../matching2/include/th10/platform/midi.hpp) | 39 | 0 |
| [matching2/include/th10/platform/midi_event_runtime.hpp](../../../matching2/include/th10/platform/midi_event_runtime.hpp) | 5 | 0 |
| [matching2/include/th10/platform/midi_sequencer.hpp](../../../matching2/include/th10/platform/midi_sequencer.hpp) | 103 | 4 |
| [matching2/include/th10/platform/midi_worker.hpp](../../../matching2/include/th10/platform/midi_worker.hpp) | 28 | 0 |
| [matching2/include/th10/platform/midi_worker_stop.hpp](../../../matching2/include/th10/platform/midi_worker_stop.hpp) | 37 | 2 |
| [matching2/include/th10/platform/pack_file_loader.hpp](../../../matching2/include/th10/platform/pack_file_loader.hpp) | 53 | 0 |
| [matching2/include/th10/platform/path.hpp](../../../matching2/include/th10/platform/path.hpp) | 6 | 0 |
| [matching2/include/th10/platform/process.hpp](../../../matching2/include/th10/platform/process.hpp) | 14 | 0 |
| [matching2/include/th10/platform/sound_commands.hpp](../../../matching2/include/th10/platform/sound_commands.hpp) | 149 | 9 |
| [matching2/include/th10/platform/sound_device_init.hpp](../../../matching2/include/th10/platform/sound_device_init.hpp) | 133 | 4 |
| [matching2/include/th10/platform/sound_dummy.hpp](../../../matching2/include/th10/platform/sound_dummy.hpp) | 13 | 1 |
| [matching2/include/th10/platform/sound_effect_buffers.hpp](../../../matching2/include/th10/platform/sound_effect_buffers.hpp) | 35 | 0 |
| [matching2/include/th10/platform/sound_event_queue.hpp](../../../matching2/include/th10/platform/sound_event_queue.hpp) | 8 | 0 |
| [matching2/include/th10/platform/sound_fade.hpp](../../../matching2/include/th10/platform/sound_fade.hpp) | 20 | 1 |
| [matching2/include/th10/platform/sound_float_forward.hpp](../../../matching2/include/th10/platform/sound_float_forward.hpp) | 5 | 0 |
| [matching2/include/th10/platform/sound_leaves.hpp](../../../matching2/include/th10/platform/sound_leaves.hpp) | 18 | 2 |
| [matching2/include/th10/platform/sound_stream_create.hpp](../../../matching2/include/th10/platform/sound_stream_create.hpp) | 8 | 1 |
| [matching2/include/th10/platform/sound_stream_start.hpp](../../../matching2/include/th10/platform/sound_stream_start.hpp) | 33 | 1 |
| [matching2/include/th10/platform/sound_stream_thread.hpp](../../../matching2/include/th10/platform/sound_stream_thread.hpp) | 12 | 0 |
| [matching2/include/th10/platform/sound_worker.hpp](../../../matching2/include/th10/platform/sound_worker.hpp) | 22 | 1 |
| [matching2/include/th10/platform/text_log.hpp](../../../matching2/include/th10/platform/text_log.hpp) | 16 | 0 |
| [matching2/include/th10/platform/timer.hpp](../../../matching2/include/th10/platform/timer.hpp) | 13 | 0 |
| [matching2/include/th10/platform/window.hpp](../../../matching2/include/th10/platform/window.hpp) | 18 | 0 |
| [matching2/include/th10/platform/windows_types.hpp](../../../matching2/include/th10/platform/windows_types.hpp) | 127 | 0 |
| [matching2/include/th10/platform/worker_start.hpp](../../../matching2/include/th10/platform/worker_start.hpp) | 27 | 1 |
| [matching2/include/th10/render/anchored_quad_draw.hpp](../../../matching2/include/th10/render/anchored_quad_draw.hpp) | 4 | 0 |
| [matching2/include/th10/render/animation_manager.hpp](../../../matching2/include/th10/render/animation_manager.hpp) | 278 | 0 |
| [matching2/include/th10/render/animation_slot.hpp](../../../matching2/include/th10/render/animation_slot.hpp) | 28 | 1 |
| [matching2/include/th10/render/anm_archive.hpp](../../../matching2/include/th10/render/anm_archive.hpp) | 57 | 2 |
| [matching2/include/th10/render/anm_batch_flush.hpp](../../../matching2/include/th10/render/anm_batch_flush.hpp) | 24 | 0 |
| [matching2/include/th10/render/anm_blend_state.hpp](../../../matching2/include/th10/render/anm_blend_state.hpp) | 34 | 0 |
| [matching2/include/th10/render/anm_clip_quad.hpp](../../../matching2/include/th10/render/anm_clip_quad.hpp) | 22 | 0 |
| [matching2/include/th10/render/anm_distance_color.hpp](../../../matching2/include/th10/render/anm_distance_color.hpp) | 30 | 1 |
| [matching2/include/th10/render/anm_entry_load.hpp](../../../matching2/include/th10/render/anm_entry_load.hpp) | 102 | 5 |
| [matching2/include/th10/render/anm_file.hpp](../../../matching2/include/th10/render/anm_file.hpp) | 55 | 0 |
| [matching2/include/th10/render/anm_handle_release.hpp](../../../matching2/include/th10/render/anm_handle_release.hpp) | 14 | 1 |
| [matching2/include/th10/render/anm_pending_service.hpp](../../../matching2/include/th10/render/anm_pending_service.hpp) | 16 | 0 |
| [matching2/include/th10/render/anm_propagate.hpp](../../../matching2/include/th10/render/anm_propagate.hpp) | 35 | 2 |
| [matching2/include/th10/render/anm_record_walk.hpp](../../../matching2/include/th10/render/anm_record_walk.hpp) | 42 | 0 |
| [matching2/include/th10/render/anm_script_table_sweep.hpp](../../../matching2/include/th10/render/anm_script_table_sweep.hpp) | 31 | 0 |
| [matching2/include/th10/render/anm_sprite_quad.hpp](../../../matching2/include/th10/render/anm_sprite_quad.hpp) | 84 | 0 |
| [matching2/include/th10/render/anm_surface_restore.hpp](../../../matching2/include/th10/render/anm_surface_restore.hpp) | 47 | 0 |
| [matching2/include/th10/render/anm_texture_upload.hpp](../../../matching2/include/th10/render/anm_texture_upload.hpp) | 66 | 0 |
| [matching2/include/th10/render/anm_vm_draw_dispatch.hpp](../../../matching2/include/th10/render/anm_vm_draw_dispatch.hpp) | 38 | 0 |
| [matching2/include/th10/render/camera_apply.hpp](../../../matching2/include/th10/render/camera_apply.hpp) | 51 | 2 |
| [matching2/include/th10/render/camera_defaults.hpp](../../../matching2/include/th10/render/camera_defaults.hpp) | 7 | 1 |
| [matching2/include/th10/render/camera_setup.hpp](../../../matching2/include/th10/render/camera_setup.hpp) | 75 | 3 |
| [matching2/include/th10/render/composite_passes.hpp](../../../matching2/include/th10/render/composite_passes.hpp) | 5 | 1 |
| [matching2/include/th10/render/default_viewport.hpp](../../../matching2/include/th10/render/default_viewport.hpp) | 13 | 0 |
| [matching2/include/th10/render/device_reset.hpp](../../../matching2/include/th10/render/device_reset.hpp) | 5 | 0 |
| [matching2/include/th10/render/edge_strip_draw.hpp](../../../matching2/include/th10/render/edge_strip_draw.hpp) | 8 | 1 |
| [matching2/include/th10/render/edge_strips.hpp](../../../matching2/include/th10/render/edge_strips.hpp) | 54 | 2 |
| [matching2/include/th10/render/effect_ring.hpp](../../../matching2/include/th10/render/effect_ring.hpp) | 36 | 0 |
| [matching2/include/th10/render/effect_ring_update.hpp](../../../matching2/include/th10/render/effect_ring_update.hpp) | 46 | 1 |
| [matching2/include/th10/render/faded_quad_draw.hpp](../../../matching2/include/th10/render/faded_quad_draw.hpp) | 24 | 0 |
| [matching2/include/th10/render/final_quad_pipeline.hpp](../../../matching2/include/th10/render/final_quad_pipeline.hpp) | 73 | 2 |
| [matching2/include/th10/render/fog_disable.hpp](../../../matching2/include/th10/render/fog_disable.hpp) | 17 | 1 |
| [matching2/include/th10/render/game_render_targets.hpp](../../../matching2/include/th10/render/game_render_targets.hpp) | 20 | 0 |
| [matching2/include/th10/render/image_alpha_transform.hpp](../../../matching2/include/th10/render/image_alpha_transform.hpp) | 10 | 0 |
| [matching2/include/th10/render/projection_quads.hpp](../../../matching2/include/th10/render/projection_quads.hpp) | 67 | 0 |
| [matching2/include/th10/render/quad_build_anchored.hpp](../../../matching2/include/th10/render/quad_build_anchored.hpp) | 21 | 0 |
| [matching2/include/th10/render/quad_transform_draw.hpp](../../../matching2/include/th10/render/quad_transform_draw.hpp) | 9 | 1 |
| [matching2/include/th10/render/quad_vertex_append.hpp](../../../matching2/include/th10/render/quad_vertex_append.hpp) | 28 | 0 |
| [matching2/include/th10/render/queued_anm_cleanup.hpp](../../../matching2/include/th10/render/queued_anm_cleanup.hpp) | 21 | 0 |
| [matching2/include/th10/render/recovered_render_leaves.hpp](../../../matching2/include/th10/render/recovered_render_leaves.hpp) | 64 | 0 |
| [matching2/include/th10/render/rect_fan_draw.hpp](../../../matching2/include/th10/render/rect_fan_draw.hpp) | 19 | 0 |
| [matching2/include/th10/render/render_stage_select.hpp](../../../matching2/include/th10/render/render_stage_select.hpp) | 16 | 0 |
| [matching2/include/th10/render/render_state_sync.hpp](../../../matching2/include/th10/render/render_state_sync.hpp) | 27 | 1 |
| [matching2/include/th10/render/resource_manager.hpp](../../../matching2/include/th10/render/resource_manager.hpp) | 34 | 0 |
| [matching2/include/th10/render/special_quad.hpp](../../../matching2/include/th10/render/special_quad.hpp) | 30 | 0 |
| [matching2/include/th10/render/texture_stage_reset.hpp](../../../matching2/include/th10/render/texture_stage_reset.hpp) | 25 | 0 |
| [matching2/include/th10/render/transparent_pixel_fill.hpp](../../../matching2/include/th10/render/transparent_pixel_fill.hpp) | 22 | 0 |
| [matching2/include/th10/runtime/missing_edge.hpp](../../../matching2/include/th10/runtime/missing_edge.hpp) | 8 | 0 |
| [matching2/include/th10/script/anm_vm_tick.hpp](../../../matching2/include/th10/script/anm_vm_tick.hpp) | 125 | 2 |
| [matching2/include/th10/script/ecl.hpp](../../../matching2/include/th10/script/ecl.hpp) | 190 | 5 |
| [matching2/include/th10/script/ecl_core_interpreter.hpp](../../../matching2/include/th10/script/ecl_core_interpreter.hpp) | 230 | 11 |
| [matching2/include/th10/script/ecl_name_table.hpp](../../../matching2/include/th10/script/ecl_name_table.hpp) | 33 | 0 |
| [matching2/include/th10/script/ecl_vm_children.hpp](../../../matching2/include/th10/script/ecl_vm_children.hpp) | 85 | 1 |
| [matching2/include/th10/script/entity_vm.hpp](../../../matching2/include/th10/script/entity_vm.hpp) | 121 | 0 |
| [matching2/include/th10/script/final_script_runtime.hpp](../../../matching2/include/th10/script/final_script_runtime.hpp) | 44 | 1 |
| [matching2/include/th10/script/prng.hpp](../../../matching2/include/th10/script/prng.hpp) | 27 | 1 |
| [matching2/include/th10/script/script_label_search.hpp](../../../matching2/include/th10/script/script_label_search.hpp) | 45 | 0 |
| [matching2/include/th10/script/script_text_reader.hpp](../../../matching2/include/th10/script/script_text_reader.hpp) | 9 | 0 |
| [matching2/include/th10/script/stage_ecl_load.hpp](../../../matching2/include/th10/script/stage_ecl_load.hpp) | 30 | 0 |
| [matching2/include/th10/util/heap.hpp](../../../matching2/include/th10/util/heap.hpp) | 50 | 0 |
| [matching2/include/th10/util/legacy_string_funclets.hpp](../../../matching2/include/th10/util/legacy_string_funclets.hpp) | 22 | 0 |
| [matching2/include/th10/util/runtime_pool.hpp](../../../matching2/include/th10/util/runtime_pool.hpp) | 15 | 0 |
| [matching2/include/th10/util/scalars.hpp](../../../matching2/include/th10/util/scalars.hpp) | 7 | 0 |
| [matching2/standalone/globals.cpp](../../../matching2/standalone/globals.cpp) | 20 | 0 |
| [matching2/standalone/host_main.cpp](../../../matching2/standalone/host_main.cpp) | 7444 | 33 |
| [matching2/standalone/host_stage.cpp](../../../matching2/standalone/host_stage.cpp) | 3909 | 5 |
| [matching2/standalone/host_stage.hpp](../../../matching2/standalone/host_stage.hpp) | 171 | 2 |
| [matching2/standalone/th10_standalone.rc](../../../matching2/standalone/th10_standalone.rc) | 25 | 0 |
| [matching2/standalone/win32_compat.cpp](../../../matching2/standalone/win32_compat.cpp) | 12 | 0 |

## IDA-only boundary review

These are outside the coverage union. They may be runtime/library functions or reflect different function boundaries; listing them makes no new recovery or equivalence claim.

| Address | IDA C | IDA ASM |
| --- | --- | --- |
| `0x00401100` | [ida/th10.exe.c:11823](../../../ida/th10.exe.c#L11823) | [ida/th10.exe.asm:103](../../../ida/th10.exe.asm#L103) |
| `0x004014F0` | [ida/th10.exe.c:12000](../../../ida/th10.exe.c#L12000) | [ida/th10.exe.asm:447](../../../ida/th10.exe.asm#L447) |
| `0x00401510` | [ida/th10.exe.c:12009](../../../ida/th10.exe.c#L12009) | [ida/th10.exe.asm:461](../../../ida/th10.exe.asm#L461) |
| `0x004015C0` | [ida/th10.exe.c:12056](../../../ida/th10.exe.c#L12056) | [ida/th10.exe.asm:537](../../../ida/th10.exe.asm#L537) |
| `0x00401700` | [ida/th10.exe.c:12114](../../../ida/th10.exe.c#L12114) | [ida/th10.exe.asm:655](../../../ida/th10.exe.asm#L655) |
| `0x00401C90` | [ida/th10.exe.c:12365](../../../ida/th10.exe.c#L12365) | [ida/th10.exe.asm:1109](../../../ida/th10.exe.asm#L1109) |
| `0x00401CB0` | [ida/th10.exe.c:12371](../../../ida/th10.exe.c#L12371) | [ida/th10.exe.asm:1122](../../../ida/th10.exe.asm#L1122) |
| `0x00401CC0` | [ida/th10.exe.c:12378](../../../ida/th10.exe.c#L12378) | [ida/th10.exe.asm:1132](../../../ida/th10.exe.asm#L1132) |
| `0x00401CD0` | [ida/th10.exe.c:12385](../../../ida/th10.exe.c#L12385) | [ida/th10.exe.asm:1142](../../../ida/th10.exe.asm#L1142) |
| `0x00401D10` | [ida/th10.exe.c:12391](../../../ida/th10.exe.c#L12391) | [ida/th10.exe.asm:1165](../../../ida/th10.exe.asm#L1165) |
| `0x00401F50` | [ida/th10.exe.c:12472](../../../ida/th10.exe.c#L12472) | [ida/th10.exe.asm:1332](../../../ida/th10.exe.asm#L1332) |
| `0x00401F60` | [ida/th10.exe.c:12479](../../../ida/th10.exe.c#L12479) | [ida/th10.exe.asm:1342](../../../ida/th10.exe.asm#L1342) |
| `0x00401F70` | [ida/th10.exe.c:12486](../../../ida/th10.exe.c#L12486) | [ida/th10.exe.asm:1352](../../../ida/th10.exe.asm#L1352) |
| `0x00401F80` | [ida/th10.exe.c:12493](../../../ida/th10.exe.c#L12493) | [ida/th10.exe.asm:1362](../../../ida/th10.exe.asm#L1362) |
| `0x00401FA0` | [ida/th10.exe.c:12500](../../../ida/th10.exe.c#L12500) | [ida/th10.exe.asm:1378](../../../ida/th10.exe.asm#L1378) |
| `0x00401FB0` | [ida/th10.exe.c:12506](../../../ida/th10.exe.c#L12506) | [ida/th10.exe.asm:1388](../../../ida/th10.exe.asm#L1388) |
| `0x00401FD0` | [ida/th10.exe.c:12513](../../../ida/th10.exe.c#L12513) | [ida/th10.exe.asm:1400](../../../ida/th10.exe.asm#L1400) |
| `0x00403050` | [ida/th10.exe.c:13156](../../../ida/th10.exe.c#L13156) | [ida/th10.exe.asm:2720](../../../ida/th10.exe.asm#L2720) |
| `0x00403060` | [ida/th10.exe.c:13162](../../../ida/th10.exe.c#L13162) | [ida/th10.exe.asm:2730](../../../ida/th10.exe.asm#L2730) |
| `0x00403070` | [ida/th10.exe.c:13168](../../../ida/th10.exe.c#L13168) | [ida/th10.exe.asm:2741](../../../ida/th10.exe.asm#L2741) |
| `0x00404410` | [ida/th10.exe.c:14142](../../../ida/th10.exe.c#L14142) | [ida/th10.exe.asm:4440](../../../ida/th10.exe.asm#L4440) |
| `0x00404990` | [ida/th10.exe.c:14448](../../../ida/th10.exe.c#L14448) | [ida/th10.exe.asm:4950](../../../ida/th10.exe.asm#L4950) |
| `0x00404C50` | [ida/th10.exe.c:14599](../../../ida/th10.exe.c#L14599) | [ida/th10.exe.asm:5212](../../../ida/th10.exe.asm#L5212) |
| `0x00404C90` | [ida/th10.exe.c:14606](../../../ida/th10.exe.c#L14606) | [ida/th10.exe.asm:5242](../../../ida/th10.exe.asm#L5242) |
| `0x00404CE0` | [ida/th10.exe.c:14613](../../../ida/th10.exe.c#L14613) | [ida/th10.exe.asm:5269](../../../ida/th10.exe.asm#L5269) |
| `0x00404D30` | [ida/th10.exe.c:14619](../../../ida/th10.exe.c#L14619) | [ida/th10.exe.asm:5297](../../../ida/th10.exe.asm#L5297) |
| `0x00405130` | [ida/th10.exe.c:14789](../../../ida/th10.exe.c#L14789) | [ida/th10.exe.asm:5656](../../../ida/th10.exe.asm#L5656) |
| `0x00405150` | [ida/th10.exe.c:14801](../../../ida/th10.exe.c#L14801) | [ida/th10.exe.asm:5671](../../../ida/th10.exe.asm#L5671) |
| `0x00405160` | [ida/th10.exe.c:14808](../../../ida/th10.exe.c#L14808) | [ida/th10.exe.asm:5681](../../../ida/th10.exe.asm#L5681) |
| `0x004051B0` | [ida/th10.exe.c:14815](../../../ida/th10.exe.c#L14815) | [ida/th10.exe.asm:5701](../../../ida/th10.exe.asm#L5701) |
| `0x004052E0` | [ida/th10.exe.c:14822](../../../ida/th10.exe.c#L14822) | [ida/th10.exe.asm:5803](../../../ida/th10.exe.asm#L5803) |
| `0x00405340` | [ida/th10.exe.c:14846](../../../ida/th10.exe.c#L14846) | [ida/th10.exe.asm:5838](../../../ida/th10.exe.asm#L5838) |
| `0x00405360` | [ida/th10.exe.c:14854](../../../ida/th10.exe.c#L14854) | [ida/th10.exe.asm:5849](../../../ida/th10.exe.asm#L5849) |
| `0x00405370` | [ida/th10.exe.c:14860](../../../ida/th10.exe.c#L14860) | [ida/th10.exe.asm:5859](../../../ida/th10.exe.asm#L5859) |
| `0x00405390` | [ida/th10.exe.c:14870](../../../ida/th10.exe.c#L14870) | [ida/th10.exe.asm:5876](../../../ida/th10.exe.asm#L5876) |
| `0x004053B0` | [ida/th10.exe.c:14876](../../../ida/th10.exe.c#L14876) | [ida/th10.exe.asm:5890](../../../ida/th10.exe.asm#L5890) |
| `0x004053D0` | [ida/th10.exe.c:14885](../../../ida/th10.exe.c#L14885) | [ida/th10.exe.asm:5910](../../../ida/th10.exe.asm#L5910) |
| `0x00405400` | [ida/th10.exe.c:14891](../../../ida/th10.exe.c#L14891) | [ida/th10.exe.asm:5924](../../../ida/th10.exe.asm#L5924) |
| `0x00405580` | [ida/th10.exe.c:14947](../../../ida/th10.exe.c#L14947) | [ida/th10.exe.asm:6060](../../../ida/th10.exe.asm#L6060) |
| `0x00405590` | [ida/th10.exe.c:14953](../../../ida/th10.exe.c#L14953) | [ida/th10.exe.asm:6070](../../../ida/th10.exe.asm#L6070) |
| `0x00405730` | [ida/th10.exe.c:15043](../../../ida/th10.exe.c#L15043) | [ida/th10.exe.asm:6244](../../../ida/th10.exe.asm#L6244) |
| `0x00405830` | [ida/th10.exe.c:15108](../../../ida/th10.exe.c#L15108) | [ida/th10.exe.asm:6363](../../../ida/th10.exe.asm#L6363) |
| `0x00405840` | [ida/th10.exe.c:15114](../../../ida/th10.exe.c#L15114) | [ida/th10.exe.asm:6373](../../../ida/th10.exe.asm#L6373) |
| `0x00405850` | [ida/th10.exe.c:15120](../../../ida/th10.exe.c#L15120) | [ida/th10.exe.asm:6386](../../../ida/th10.exe.asm#L6386) |
| `0x00405B90` | [ida/th10.exe.c:15307](../../../ida/th10.exe.c#L15307) | [ida/th10.exe.asm:6734](../../../ida/th10.exe.asm#L6734) |
| `0x00405BB0` | [ida/th10.exe.c:15313](../../../ida/th10.exe.c#L15313) | [ida/th10.exe.asm:6747](../../../ida/th10.exe.asm#L6747) |
| `0x00405BD0` | missing | [ida/th10.exe.asm:6759](../../../ida/th10.exe.asm#L6759) |
| `0x00405CA0` | [ida/th10.exe.c:15354](../../../ida/th10.exe.c#L15354) | [ida/th10.exe.asm:6818](../../../ida/th10.exe.asm#L6818) |
| `0x00405CB0` | [ida/th10.exe.c:15360](../../../ida/th10.exe.c#L15360) | [ida/th10.exe.asm:6828](../../../ida/th10.exe.asm#L6828) |
| `0x00406140` | [ida/th10.exe.c:15520](../../../ida/th10.exe.c#L15520) | [ida/th10.exe.asm:7243](../../../ida/th10.exe.asm#L7243) |
| `0x00406770` | [ida/th10.exe.c:15792](../../../ida/th10.exe.c#L15792) | [ida/th10.exe.asm:7816](../../../ida/th10.exe.asm#L7816) |
| `0x004067A0` | [ida/th10.exe.c:15801](../../../ida/th10.exe.c#L15801) | [ida/th10.exe.asm:7842](../../../ida/th10.exe.asm#L7842) |
| `0x004084A0` | [ida/th10.exe.c:17105](../../../ida/th10.exe.c#L17105) | [ida/th10.exe.asm:10233](../../../ida/th10.exe.asm#L10233) |
| `0x004087D0` | [ida/th10.exe.c:17224](../../../ida/th10.exe.c#L17224) | [ida/th10.exe.asm:10562](../../../ida/th10.exe.asm#L10562) |
| `0x00408830` | [ida/th10.exe.c:17231](../../../ida/th10.exe.c#L17231) | [ida/th10.exe.asm:10590](../../../ida/th10.exe.asm#L10590) |
| `0x004088B0` | [ida/th10.exe.c:17237](../../../ida/th10.exe.c#L17237) | [ida/th10.exe.asm:10628](../../../ida/th10.exe.asm#L10628) |
| `0x00409220` | missing | [ida/th10.exe.asm:11431](../../../ida/th10.exe.asm#L11431) |
| `0x00409DC0` | [ida/th10.exe.c:18353](../../../ida/th10.exe.c#L18353) | [ida/th10.exe.asm:12440](../../../ida/th10.exe.asm#L12440) |
| `0x00409DD0` | [ida/th10.exe.c:18359](../../../ida/th10.exe.c#L18359) | [ida/th10.exe.asm:12450](../../../ida/th10.exe.asm#L12450) |
| `0x00409DE0` | [ida/th10.exe.c:18365](../../../ida/th10.exe.c#L18365) | [ida/th10.exe.asm:12460](../../../ida/th10.exe.asm#L12460) |
| `0x00409DF0` | [ida/th10.exe.c:18371](../../../ida/th10.exe.c#L18371) | [ida/th10.exe.asm:12470](../../../ida/th10.exe.asm#L12470) |
| `0x00409EB0` | [ida/th10.exe.c:18415](../../../ida/th10.exe.c#L18415) | [ida/th10.exe.asm:12552](../../../ida/th10.exe.asm#L12552) |
| `0x00409F30` | [ida/th10.exe.c:18439](../../../ida/th10.exe.c#L18439) | [ida/th10.exe.asm:12610](../../../ida/th10.exe.asm#L12610) |
| `0x00409F40` | [ida/th10.exe.c:18445](../../../ida/th10.exe.c#L18445) | [ida/th10.exe.asm:12620](../../../ida/th10.exe.asm#L12620) |
| `0x00409F60` | [ida/th10.exe.c:18451](../../../ida/th10.exe.c#L18451) | [ida/th10.exe.asm:12639](../../../ida/th10.exe.asm#L12639) |
| `0x00409F70` | [ida/th10.exe.c:18457](../../../ida/th10.exe.c#L18457) | [ida/th10.exe.asm:12649](../../../ida/th10.exe.asm#L12649) |
| `0x00409F80` | [ida/th10.exe.c:18463](../../../ida/th10.exe.c#L18463) | [ida/th10.exe.asm:12660](../../../ida/th10.exe.asm#L12660) |
| `0x0040A010` | [ida/th10.exe.c:18514](../../../ida/th10.exe.c#L18514) | [ida/th10.exe.asm:12739](../../../ida/th10.exe.asm#L12739) |
| `0x0040A040` | [ida/th10.exe.c:18522](../../../ida/th10.exe.c#L18522) | [ida/th10.exe.asm:12761](../../../ida/th10.exe.asm#L12761) |
| `0x0040A130` | [ida/th10.exe.c:18564](../../../ida/th10.exe.c#L18564) | [ida/th10.exe.asm:12823](../../../ida/th10.exe.asm#L12823) |
| `0x0040A1A0` | [ida/th10.exe.c:18593](../../../ida/th10.exe.c#L18593) | [ida/th10.exe.asm:12861](../../../ida/th10.exe.asm#L12861) |
| `0x0040A340` | missing | [ida/th10.exe.asm:13016](../../../ida/th10.exe.asm#L13016) |
| `0x0040A350` | [ida/th10.exe.c:18686](../../../ida/th10.exe.c#L18686) | [ida/th10.exe.asm:13029](../../../ida/th10.exe.asm#L13029) |
| `0x0040A3C0` | [ida/th10.exe.c:18703](../../../ida/th10.exe.c#L18703) | [ida/th10.exe.asm:13064](../../../ida/th10.exe.asm#L13064) |
| `0x0040A450` | [ida/th10.exe.c:18726](../../../ida/th10.exe.c#L18726) | [ida/th10.exe.asm:13130](../../../ida/th10.exe.asm#L13130) |
| `0x0040ABE0` | [ida/th10.exe.c:19060](../../../ida/th10.exe.c#L19060) | [ida/th10.exe.asm:13746](../../../ida/th10.exe.asm#L13746) |
| `0x0040ABF0` | [ida/th10.exe.c:19066](../../../ida/th10.exe.c#L19066) | [ida/th10.exe.asm:13757](../../../ida/th10.exe.asm#L13757) |
| `0x0040AC00` | [ida/th10.exe.c:19072](../../../ida/th10.exe.c#L19072) | [ida/th10.exe.asm:13770](../../../ida/th10.exe.asm#L13770) |
| `0x0040AC10` | [ida/th10.exe.c:19078](../../../ida/th10.exe.c#L19078) | [ida/th10.exe.asm:13780](../../../ida/th10.exe.asm#L13780) |
| `0x0040AD10` | [ida/th10.exe.c:19144](../../../ida/th10.exe.c#L19144) | [ida/th10.exe.asm:13897](../../../ida/th10.exe.asm#L13897) |
| `0x0040AD50` | [ida/th10.exe.c:19174](../../../ida/th10.exe.c#L19174) | [ida/th10.exe.asm:13938](../../../ida/th10.exe.asm#L13938) |
| `0x0040AD80` | [ida/th10.exe.c:19181](../../../ida/th10.exe.c#L19181) | [ida/th10.exe.asm:13956](../../../ida/th10.exe.asm#L13956) |
| `0x0040AD90` | [ida/th10.exe.c:19188](../../../ida/th10.exe.c#L19188) | [ida/th10.exe.asm:13966](../../../ida/th10.exe.asm#L13966) |
| `0x0040AE20` | [ida/th10.exe.c:19194](../../../ida/th10.exe.c#L19194) | [ida/th10.exe.asm:14010](../../../ida/th10.exe.asm#L14010) |
| `0x0040AE30` | [ida/th10.exe.c:19200](../../../ida/th10.exe.c#L19200) | [ida/th10.exe.asm:14020](../../../ida/th10.exe.asm#L14020) |
| `0x0040AE40` | [ida/th10.exe.c:19206](../../../ida/th10.exe.c#L19206) | [ida/th10.exe.asm:14030](../../../ida/th10.exe.asm#L14030) |
| `0x0040B030` | [ida/th10.exe.c:19311](../../../ida/th10.exe.c#L19311) | [ida/th10.exe.asm:14230](../../../ida/th10.exe.asm#L14230) |
| `0x0040B040` | [ida/th10.exe.c:19317](../../../ida/th10.exe.c#L19317) | [ida/th10.exe.asm:14240](../../../ida/th10.exe.asm#L14240) |
| `0x0040B050` | [ida/th10.exe.c:19323](../../../ida/th10.exe.c#L19323) | [ida/th10.exe.asm:14250](../../../ida/th10.exe.asm#L14250) |
| `0x0040B060` | [ida/th10.exe.c:19329](../../../ida/th10.exe.c#L19329) | [ida/th10.exe.asm:14260](../../../ida/th10.exe.asm#L14260) |
| `0x0040B070` | [ida/th10.exe.c:19335](../../../ida/th10.exe.c#L19335) | [ida/th10.exe.asm:14270](../../../ida/th10.exe.asm#L14270) |
| `0x0040B1B0` | [ida/th10.exe.c:19420](../../../ida/th10.exe.c#L19420) | [ida/th10.exe.asm:14403](../../../ida/th10.exe.asm#L14403) |
| `0x0040B4F0` | [ida/th10.exe.c:19553](../../../ida/th10.exe.c#L19553) | [ida/th10.exe.asm:14749](../../../ida/th10.exe.asm#L14749) |
| `0x0040BA60` | [ida/th10.exe.c:19853](../../../ida/th10.exe.c#L19853) | [ida/th10.exe.asm:15304](../../../ida/th10.exe.asm#L15304) |
| `0x0040BA70` | [ida/th10.exe.c:19859](../../../ida/th10.exe.c#L19859) | [ida/th10.exe.asm:15314](../../../ida/th10.exe.asm#L15314) |
| `0x0040BA80` | [ida/th10.exe.c:19865](../../../ida/th10.exe.c#L19865) | [ida/th10.exe.asm:15327](../../../ida/th10.exe.asm#L15327) |
| `0x0040C3A0` | missing | [ida/th10.exe.asm:16219](../../../ida/th10.exe.asm#L16219) |
| `0x0040C460` | [ida/th10.exe.c:20421](../../../ida/th10.exe.c#L20421) | [ida/th10.exe.asm:16298](../../../ida/th10.exe.asm#L16298) |
| `0x0040C520` | [ida/th10.exe.c:20468](../../../ida/th10.exe.c#L20468) | [ida/th10.exe.asm:16380](../../../ida/th10.exe.asm#L16380) |
| `0x0040C5B0` | [ida/th10.exe.c:20492](../../../ida/th10.exe.c#L20492) | [ida/th10.exe.asm:16441](../../../ida/th10.exe.asm#L16441) |
| `0x0040C5C0` | [ida/th10.exe.c:20498](../../../ida/th10.exe.c#L20498) | [ida/th10.exe.asm:16451](../../../ida/th10.exe.asm#L16451) |
| `0x0040C5E0` | [ida/th10.exe.c:20504](../../../ida/th10.exe.c#L20504) | [ida/th10.exe.asm:16466](../../../ida/th10.exe.asm#L16466) |
| `0x0040C650` | [ida/th10.exe.c:20510](../../../ida/th10.exe.c#L20510) | [ida/th10.exe.asm:16517](../../../ida/th10.exe.asm#L16517) |
| `0x0040C660` | [ida/th10.exe.c:20516](../../../ida/th10.exe.c#L20516) | [ida/th10.exe.asm:16527](../../../ida/th10.exe.asm#L16527) |
| `0x0040C680` | [ida/th10.exe.c:20522](../../../ida/th10.exe.c#L20522) | [ida/th10.exe.asm:16543](../../../ida/th10.exe.asm#L16543) |
| `0x0040C690` | [ida/th10.exe.c:20528](../../../ida/th10.exe.c#L20528) | [ida/th10.exe.asm:16553](../../../ida/th10.exe.asm#L16553) |
| `0x0040C6A0` | [ida/th10.exe.c:20534](../../../ida/th10.exe.c#L20534) | [ida/th10.exe.asm:16563](../../../ida/th10.exe.asm#L16563) |
| `0x0040C6B0` | [ida/th10.exe.c:20540](../../../ida/th10.exe.c#L20540) | [ida/th10.exe.asm:16573](../../../ida/th10.exe.asm#L16573) |
| `0x0040C6C0` | [ida/th10.exe.c:20546](../../../ida/th10.exe.c#L20546) | [ida/th10.exe.asm:16583](../../../ida/th10.exe.asm#L16583) |
| `0x0040C7B0` | [ida/th10.exe.c:20588](../../../ida/th10.exe.c#L20588) | [ida/th10.exe.asm:16685](../../../ida/th10.exe.asm#L16685) |
| `0x0040C810` | [ida/th10.exe.c:20613](../../../ida/th10.exe.c#L20613) | [ida/th10.exe.asm:16735](../../../ida/th10.exe.asm#L16735) |
| `0x0040C820` | [ida/th10.exe.c:20619](../../../ida/th10.exe.c#L20619) | [ida/th10.exe.asm:16745](../../../ida/th10.exe.asm#L16745) |
| `0x0040C890` | [ida/th10.exe.c:20625](../../../ida/th10.exe.c#L20625) | [ida/th10.exe.asm:16779](../../../ida/th10.exe.asm#L16779) |
| `0x0040C8A0` | [ida/th10.exe.c:20631](../../../ida/th10.exe.c#L20631) | [ida/th10.exe.asm:16789](../../../ida/th10.exe.asm#L16789) |
| `0x0040C8B0` | [ida/th10.exe.c:20638](../../../ida/th10.exe.c#L20638) | [ida/th10.exe.asm:16799](../../../ida/th10.exe.asm#L16799) |
| `0x0040C8C0` | [ida/th10.exe.c:20644](../../../ida/th10.exe.c#L20644) | [ida/th10.exe.asm:16809](../../../ida/th10.exe.asm#L16809) |
| `0x0040C8D0` | [ida/th10.exe.c:20651](../../../ida/th10.exe.c#L20651) | [ida/th10.exe.asm:16819](../../../ida/th10.exe.asm#L16819) |
| `0x0040C8E0` | [ida/th10.exe.c:20657](../../../ida/th10.exe.c#L20657) | [ida/th10.exe.asm:16829](../../../ida/th10.exe.asm#L16829) |
| `0x0040C8F0` | [ida/th10.exe.c:20664](../../../ida/th10.exe.c#L20664) | [ida/th10.exe.asm:16839](../../../ida/th10.exe.asm#L16839) |
| `0x0040C900` | [ida/th10.exe.c:20670](../../../ida/th10.exe.c#L20670) | [ida/th10.exe.asm:16849](../../../ida/th10.exe.asm#L16849) |
| `0x0040C910` | [ida/th10.exe.c:20677](../../../ida/th10.exe.c#L20677) | [ida/th10.exe.asm:16859](../../../ida/th10.exe.asm#L16859) |
| `0x0040C950` | [ida/th10.exe.c:20684](../../../ida/th10.exe.c#L20684) | [ida/th10.exe.asm:16887](../../../ida/th10.exe.asm#L16887) |
| `0x0040C960` | [ida/th10.exe.c:20691](../../../ida/th10.exe.c#L20691) | [ida/th10.exe.asm:16897](../../../ida/th10.exe.asm#L16897) |
| `0x0040C980` | [ida/th10.exe.c:20699](../../../ida/th10.exe.c#L20699) | [ida/th10.exe.asm:16914](../../../ida/th10.exe.asm#L16914) |
| `0x0040C990` | [ida/th10.exe.c:20706](../../../ida/th10.exe.c#L20706) | [ida/th10.exe.asm:16924](../../../ida/th10.exe.asm#L16924) |
| `0x0040CC40` | [ida/th10.exe.c:20777](../../../ida/th10.exe.c#L20777) | [ida/th10.exe.asm:17157](../../../ida/th10.exe.asm#L17157) |
| `0x0040CD80` | [ida/th10.exe.c:20831](../../../ida/th10.exe.c#L20831) | [ida/th10.exe.asm:17301](../../../ida/th10.exe.asm#L17301) |
| `0x0040CD90` | [ida/th10.exe.c:20838](../../../ida/th10.exe.c#L20838) | [ida/th10.exe.asm:17311](../../../ida/th10.exe.asm#L17311) |
| `0x0040CDA0` | [ida/th10.exe.c:20845](../../../ida/th10.exe.c#L20845) | [ida/th10.exe.asm:17321](../../../ida/th10.exe.asm#L17321) |
| `0x0040CDB0` | [ida/th10.exe.c:20851](../../../ida/th10.exe.c#L20851) | [ida/th10.exe.asm:17331](../../../ida/th10.exe.asm#L17331) |
| `0x0040CDE0` | [ida/th10.exe.c:20857](../../../ida/th10.exe.c#L20857) | [ida/th10.exe.asm:17350](../../../ida/th10.exe.asm#L17350) |
| `0x0040CDF0` | [ida/th10.exe.c:20864](../../../ida/th10.exe.c#L20864) | [ida/th10.exe.asm:17360](../../../ida/th10.exe.asm#L17360) |
| `0x0040CE00` | [ida/th10.exe.c:20870](../../../ida/th10.exe.c#L20870) | [ida/th10.exe.asm:17370](../../../ida/th10.exe.asm#L17370) |
| `0x0040CE40` | [ida/th10.exe.c:20877](../../../ida/th10.exe.c#L20877) | [ida/th10.exe.asm:17391](../../../ida/th10.exe.asm#L17391) |
| `0x0040CF00` | [ida/th10.exe.c:20894](../../../ida/th10.exe.c#L20894) | [ida/th10.exe.asm:17451](../../../ida/th10.exe.asm#L17451) |
| `0x0040CF10` | [ida/th10.exe.c:20904](../../../ida/th10.exe.c#L20904) | [ida/th10.exe.asm:17465](../../../ida/th10.exe.asm#L17465) |
| `0x0040CF20` | [ida/th10.exe.c:20914](../../../ida/th10.exe.c#L20914) | [ida/th10.exe.asm:17479](../../../ida/th10.exe.asm#L17479) |
| `0x0040CF80` | [ida/th10.exe.c:20946](../../../ida/th10.exe.c#L20946) | [ida/th10.exe.asm:17534](../../../ida/th10.exe.asm#L17534) |
| `0x0040D400` | [ida/th10.exe.c:21193](../../../ida/th10.exe.c#L21193) | [ida/th10.exe.asm:17962](../../../ida/th10.exe.asm#L17962) |
| `0x0040D510` | [ida/th10.exe.c:21261](../../../ida/th10.exe.c#L21261) | [ida/th10.exe.asm:18099](../../../ida/th10.exe.asm#L18099) |
| `0x0040D730` | [ida/th10.exe.c:21407](../../../ida/th10.exe.c#L21407) | [ida/th10.exe.asm:18345](../../../ida/th10.exe.asm#L18345) |
| `0x0040D800` | [ida/th10.exe.c:21467](../../../ida/th10.exe.c#L21467) | [ida/th10.exe.asm:18437](../../../ida/th10.exe.asm#L18437) |
| `0x0040D810` | [ida/th10.exe.c:21473](../../../ida/th10.exe.c#L21473) | [ida/th10.exe.asm:18447](../../../ida/th10.exe.asm#L18447) |
| `0x0040D820` | [ida/th10.exe.c:21479](../../../ida/th10.exe.c#L21479) | [ida/th10.exe.asm:18460](../../../ida/th10.exe.asm#L18460) |
| `0x00412A60` | [ida/th10.exe.c:22389](../../../ida/th10.exe.c#L22389) | [ida/th10.exe.asm:25254](../../../ida/th10.exe.asm#L25254) |
| `0x00412A70` | [ida/th10.exe.c:22395](../../../ida/th10.exe.c#L22395) | [ida/th10.exe.asm:25265](../../../ida/th10.exe.asm#L25265) |
| `0x00412D50` | [ida/th10.exe.c:22575](../../../ida/th10.exe.c#L22575) | [ida/th10.exe.asm:25548](../../../ida/th10.exe.asm#L25548) |
| `0x00412D60` | [ida/th10.exe.c:22582](../../../ida/th10.exe.c#L22582) | [ida/th10.exe.asm:25558](../../../ida/th10.exe.asm#L25558) |
| `0x00412D70` | [ida/th10.exe.c:22593](../../../ida/th10.exe.c#L22593) | [ida/th10.exe.asm:25571](../../../ida/th10.exe.asm#L25571) |
| `0x00412D80` | [ida/th10.exe.c:22604](../../../ida/th10.exe.c#L22604) | [ida/th10.exe.asm:25584](../../../ida/th10.exe.asm#L25584) |
| `0x00412D90` | [ida/th10.exe.c:22615](../../../ida/th10.exe.c#L22615) | [ida/th10.exe.asm:25597](../../../ida/th10.exe.asm#L25597) |
| `0x00412DA0` | [ida/th10.exe.c:22626](../../../ida/th10.exe.c#L22626) | [ida/th10.exe.asm:25610](../../../ida/th10.exe.asm#L25610) |
| `0x00412DF0` | [ida/th10.exe.c:22655](../../../ida/th10.exe.c#L22655) | [ida/th10.exe.asm:25644](../../../ida/th10.exe.asm#L25644) |
| `0x00412E00` | [ida/th10.exe.c:22661](../../../ida/th10.exe.c#L22661) | [ida/th10.exe.asm:25654](../../../ida/th10.exe.asm#L25654) |
| `0x00412EE0` | [ida/th10.exe.c:22692](../../../ida/th10.exe.c#L22692) | [ida/th10.exe.asm:25749](../../../ida/th10.exe.asm#L25749) |
| `0x00412F10` | [ida/th10.exe.c:22698](../../../ida/th10.exe.c#L22698) | [ida/th10.exe.asm:25772](../../../ida/th10.exe.asm#L25772) |
| `0x00412F20` | [ida/th10.exe.c:22708](../../../ida/th10.exe.c#L22708) | [ida/th10.exe.asm:25786](../../../ida/th10.exe.asm#L25786) |
| `0x00412F70` | [ida/th10.exe.c:22718](../../../ida/th10.exe.c#L22718) | [ida/th10.exe.asm:25813](../../../ida/th10.exe.asm#L25813) |
| `0x004130A0` | [ida/th10.exe.c:22757](../../../ida/th10.exe.c#L22757) | [ida/th10.exe.asm:25913](../../../ida/th10.exe.asm#L25913) |
| `0x004130D0` | [ida/th10.exe.c:22764](../../../ida/th10.exe.c#L22764) | [ida/th10.exe.asm:25930](../../../ida/th10.exe.asm#L25930) |
| `0x004130E0` | [ida/th10.exe.c:22771](../../../ida/th10.exe.c#L22771) | [ida/th10.exe.asm:25940](../../../ida/th10.exe.asm#L25940) |
| `0x00413100` | [ida/th10.exe.c:22781](../../../ida/th10.exe.c#L22781) | [ida/th10.exe.asm:25957](../../../ida/th10.exe.asm#L25957) |
| `0x00413140` | [ida/th10.exe.c:22791](../../../ida/th10.exe.c#L22791) | [ida/th10.exe.asm:25983](../../../ida/th10.exe.asm#L25983) |
| `0x00413150` | [ida/th10.exe.c:22801](../../../ida/th10.exe.c#L22801) | [ida/th10.exe.asm:25997](../../../ida/th10.exe.asm#L25997) |
| `0x00413160` | [ida/th10.exe.c:22811](../../../ida/th10.exe.c#L22811) | [ida/th10.exe.asm:26011](../../../ida/th10.exe.asm#L26011) |
| `0x004131F0` | [ida/th10.exe.c:22827](../../../ida/th10.exe.c#L22827) | [ida/th10.exe.asm:26079](../../../ida/th10.exe.asm#L26079) |
| `0x00413220` | [ida/th10.exe.c:22849](../../../ida/th10.exe.c#L22849) | [ida/th10.exe.asm:26108](../../../ida/th10.exe.asm#L26108) |
| `0x00413240` | [ida/th10.exe.c:22861](../../../ida/th10.exe.c#L22861) | [ida/th10.exe.asm:26123](../../../ida/th10.exe.asm#L26123) |
| `0x00413690` | [ida/th10.exe.c:23066](../../../ida/th10.exe.c#L23066) | [ida/th10.exe.asm:26549](../../../ida/th10.exe.asm#L26549) |
| `0x004136A0` | [ida/th10.exe.c:23072](../../../ida/th10.exe.c#L23072) | [ida/th10.exe.asm:26562](../../../ida/th10.exe.asm#L26562) |
| `0x00413730` | [ida/th10.exe.c:23106](../../../ida/th10.exe.c#L23106) | [ida/th10.exe.asm:26619](../../../ida/th10.exe.asm#L26619) |
| `0x004137E0` | [ida/th10.exe.c:23149](../../../ida/th10.exe.c#L23149) | [ida/th10.exe.asm:26691](../../../ida/th10.exe.asm#L26691) |
| `0x004148E0` | [ida/th10.exe.c:24103](../../../ida/th10.exe.c#L24103) | [ida/th10.exe.asm:28200](../../../ida/th10.exe.asm#L28200) |
| `0x00415AE0` | [ida/th10.exe.c:25324](../../../ida/th10.exe.c#L25324) | [ida/th10.exe.asm:29826](../../../ida/th10.exe.asm#L29826) |
| `0x00415AF0` | [ida/th10.exe.c:25330](../../../ida/th10.exe.c#L25330) | [ida/th10.exe.asm:29837](../../../ida/th10.exe.asm#L29837) |
| `0x00417580` | [ida/th10.exe.c:26626](../../../ida/th10.exe.c#L26626) | [ida/th10.exe.asm:32229](../../../ida/th10.exe.asm#L32229) |
| `0x00417590` | [ida/th10.exe.c:26633](../../../ida/th10.exe.c#L26633) | [ida/th10.exe.asm:32239](../../../ida/th10.exe.asm#L32239) |
| `0x004175A0` | [ida/th10.exe.c:26639](../../../ida/th10.exe.c#L26639) | [ida/th10.exe.asm:32249](../../../ida/th10.exe.asm#L32249) |
| `0x004175D0` | [ida/th10.exe.c:26645](../../../ida/th10.exe.c#L26645) | [ida/th10.exe.asm:32267](../../../ida/th10.exe.asm#L32267) |
| `0x00417640` | [ida/th10.exe.c:26667](../../../ida/th10.exe.c#L26667) | [ida/th10.exe.asm:32313](../../../ida/th10.exe.asm#L32313) |
| `0x00417670` | [ida/th10.exe.c:26673](../../../ida/th10.exe.c#L26673) | [ida/th10.exe.asm:32332](../../../ida/th10.exe.asm#L32332) |
| `0x00417680` | [ida/th10.exe.c:26680](../../../ida/th10.exe.c#L26680) | [ida/th10.exe.asm:32342](../../../ida/th10.exe.asm#L32342) |
| `0x004176A0` | [ida/th10.exe.c:26686](../../../ida/th10.exe.c#L26686) | [ida/th10.exe.asm:32357](../../../ida/th10.exe.asm#L32357) |
| `0x004176C0` | [ida/th10.exe.c:26692](../../../ida/th10.exe.c#L26692) | [ida/th10.exe.asm:32369](../../../ida/th10.exe.asm#L32369) |
| `0x004176D0` | [ida/th10.exe.c:26699](../../../ida/th10.exe.c#L26699) | [ida/th10.exe.asm:32379](../../../ida/th10.exe.asm#L32379) |
| `0x004176E0` | [ida/th10.exe.c:26705](../../../ida/th10.exe.c#L26705) | [ida/th10.exe.asm:32389](../../../ida/th10.exe.asm#L32389) |
| `0x00417C70` | [ida/th10.exe.c:26962](../../../ida/th10.exe.c#L26962) | [ida/th10.exe.asm:32866](../../../ida/th10.exe.asm#L32866) |
| `0x004187C0` | missing | [ida/th10.exe.asm:33945](../../../ida/th10.exe.asm#L33945) |
| `0x004187D0` | [ida/th10.exe.c:27637](../../../ida/th10.exe.c#L27637) | [ida/th10.exe.asm:33956](../../../ida/th10.exe.asm#L33956) |
| `0x00418AB0` | [ida/th10.exe.c:27764](../../../ida/th10.exe.c#L27764) | [ida/th10.exe.asm:34259](../../../ida/th10.exe.asm#L34259) |
| `0x00418AC0` | [ida/th10.exe.c:27770](../../../ida/th10.exe.c#L27770) | [ida/th10.exe.asm:34269](../../../ida/th10.exe.asm#L34269) |
| `0x00418B40` | [ida/th10.exe.c:27778](../../../ida/th10.exe.c#L27778) | [ida/th10.exe.asm:34309](../../../ida/th10.exe.asm#L34309) |
| `0x00418B60` | [ida/th10.exe.c:27785](../../../ida/th10.exe.c#L27785) | [ida/th10.exe.asm:34322](../../../ida/th10.exe.asm#L34322) |
| `0x00418B70` | [ida/th10.exe.c:27792](../../../ida/th10.exe.c#L27792) | [ida/th10.exe.asm:34332](../../../ida/th10.exe.asm#L34332) |
| `0x00418BD0` | [ida/th10.exe.c:27822](../../../ida/th10.exe.c#L27822) | [ida/th10.exe.asm:34376](../../../ida/th10.exe.asm#L34376) |
| `0x00418BE0` | [ida/th10.exe.c:27829](../../../ida/th10.exe.c#L27829) | [ida/th10.exe.asm:34386](../../../ida/th10.exe.asm#L34386) |
| `0x00418BF0` | [ida/th10.exe.c:27836](../../../ida/th10.exe.c#L27836) | [ida/th10.exe.asm:34396](../../../ida/th10.exe.asm#L34396) |
| `0x00418C00` | [ida/th10.exe.c:27843](../../../ida/th10.exe.c#L27843) | [ida/th10.exe.asm:34406](../../../ida/th10.exe.asm#L34406) |
| `0x00419890` | [ida/th10.exe.c:28529](../../../ida/th10.exe.c#L28529) | [ida/th10.exe.asm:35555](../../../ida/th10.exe.asm#L35555) |
| `0x004198B0` | [ida/th10.exe.c:28541](../../../ida/th10.exe.c#L28541) | [ida/th10.exe.asm:35578](../../../ida/th10.exe.asm#L35578) |
| `0x0041AB50` | [ida/th10.exe.c:29469](../../../ida/th10.exe.c#L29469) | [ida/th10.exe.asm:37551](../../../ida/th10.exe.asm#L37551) |
| `0x0041AB60` | [ida/th10.exe.c:29475](../../../ida/th10.exe.c#L29475) | [ida/th10.exe.asm:37561](../../../ida/th10.exe.asm#L37561) |
| `0x0041AC00` | [ida/th10.exe.c:29508](../../../ida/th10.exe.c#L29508) | [ida/th10.exe.asm:37613](../../../ida/th10.exe.asm#L37613) |
| `0x0041AC10` | [ida/th10.exe.c:29515](../../../ida/th10.exe.c#L29515) | [ida/th10.exe.asm:37623](../../../ida/th10.exe.asm#L37623) |
| `0x0041AC20` | [ida/th10.exe.c:29522](../../../ida/th10.exe.c#L29522) | [ida/th10.exe.asm:37633](../../../ida/th10.exe.asm#L37633) |
| `0x0041AC30` | [ida/th10.exe.c:29533](../../../ida/th10.exe.c#L29533) | [ida/th10.exe.asm:37646](../../../ida/th10.exe.asm#L37646) |
| `0x0041AC80` | [ida/th10.exe.c:29544](../../../ida/th10.exe.c#L29544) | [ida/th10.exe.asm:37676](../../../ida/th10.exe.asm#L37676) |
| `0x0041ACA0` | [ida/th10.exe.c:29552](../../../ida/th10.exe.c#L29552) | [ida/th10.exe.asm:37694](../../../ida/th10.exe.asm#L37694) |
| `0x0041ACF0` | [ida/th10.exe.c:29558](../../../ida/th10.exe.c#L29558) | [ida/th10.exe.asm:37722](../../../ida/th10.exe.asm#L37722) |
| `0x0041AFB0` | [ida/th10.exe.c:29671](../../../ida/th10.exe.c#L29671) | [ida/th10.exe.asm:37985](../../../ida/th10.exe.asm#L37985) |
| `0x0041B8E0` | [ida/th10.exe.c:30027](../../../ida/th10.exe.c#L30027) | [ida/th10.exe.asm:38740](../../../ida/th10.exe.asm#L38740) |
| `0x0041BA00` | [ida/th10.exe.c:30080](../../../ida/th10.exe.c#L30080) | [ida/th10.exe.asm:38836](../../../ida/th10.exe.asm#L38836) |
| `0x0041BA30` | [ida/th10.exe.c:30091](../../../ida/th10.exe.c#L30091) | [ida/th10.exe.asm:38867](../../../ida/th10.exe.asm#L38867) |
| `0x0041BEE0` | [ida/th10.exe.c:30316](../../../ida/th10.exe.c#L30316) | [ida/th10.exe.asm:39310](../../../ida/th10.exe.asm#L39310) |
| `0x0041BF00` | [ida/th10.exe.c:30324](../../../ida/th10.exe.c#L30324) | [ida/th10.exe.asm:39323](../../../ida/th10.exe.asm#L39323) |
| `0x0041BF10` | [ida/th10.exe.c:30330](../../../ida/th10.exe.c#L30330) | [ida/th10.exe.asm:39333](../../../ida/th10.exe.asm#L39333) |
| `0x0041BF20` | [ida/th10.exe.c:30336](../../../ida/th10.exe.c#L30336) | [ida/th10.exe.asm:39343](../../../ida/th10.exe.asm#L39343) |
| `0x0041BF30` | [ida/th10.exe.c:30342](../../../ida/th10.exe.c#L30342) | [ida/th10.exe.asm:39353](../../../ida/th10.exe.asm#L39353) |
| `0x0041BF50` | [ida/th10.exe.c:30354](../../../ida/th10.exe.c#L30354) | [ida/th10.exe.asm:39373](../../../ida/th10.exe.asm#L39373) |
| `0x0041BF60` | [ida/th10.exe.c:30360](../../../ida/th10.exe.c#L30360) | [ida/th10.exe.asm:39383](../../../ida/th10.exe.asm#L39383) |
| `0x0041BF70` | [ida/th10.exe.c:30366](../../../ida/th10.exe.c#L30366) | [ida/th10.exe.asm:39393](../../../ida/th10.exe.asm#L39393) |
| `0x0041BF80` | [ida/th10.exe.c:30372](../../../ida/th10.exe.c#L30372) | [ida/th10.exe.asm:39403](../../../ida/th10.exe.asm#L39403) |
| `0x0041C480` | [ida/th10.exe.c:30615](../../../ida/th10.exe.c#L30615) | [ida/th10.exe.asm:39882](../../../ida/th10.exe.asm#L39882) |
| `0x0041C4E0` | [ida/th10.exe.c:30635](../../../ida/th10.exe.c#L30635) | [ida/th10.exe.asm:39931](../../../ida/th10.exe.asm#L39931) |
| `0x0041C760` | [ida/th10.exe.c:30773](../../../ida/th10.exe.c#L30773) | [ida/th10.exe.asm:40142](../../../ida/th10.exe.asm#L40142) |
| `0x0041C880` | [ida/th10.exe.c:30874](../../../ida/th10.exe.c#L30874) | [ida/th10.exe.asm:40319](../../../ida/th10.exe.asm#L40319) |
| `0x0041C8C0` | [ida/th10.exe.c:30897](../../../ida/th10.exe.c#L30897) | [ida/th10.exe.asm:40364](../../../ida/th10.exe.asm#L40364) |
| `0x0041D170` | [ida/th10.exe.c:31042](../../../ida/th10.exe.c#L31042) | [ida/th10.exe.asm:41022](../../../ida/th10.exe.asm#L41022) |
| `0x0041D870` | [ida/th10.exe.c:31328](../../../ida/th10.exe.c#L31328) | [ida/th10.exe.asm:41627](../../../ida/th10.exe.asm#L41627) |
| `0x0041E5C0` | [ida/th10.exe.c:31950](../../../ida/th10.exe.c#L31950) | [ida/th10.exe.asm:42792](../../../ida/th10.exe.asm#L42792) |
| `0x0041EA40` | [ida/th10.exe.c:32146](../../../ida/th10.exe.c#L32146) | [ida/th10.exe.asm:43157](../../../ida/th10.exe.asm#L43157) |
| `0x0041EAF0` | [ida/th10.exe.c:32172](../../../ida/th10.exe.c#L32172) | [ida/th10.exe.asm:43211](../../../ida/th10.exe.asm#L43211) |
| `0x0041F670` | [ida/th10.exe.c:32669](../../../ida/th10.exe.c#L32669) | [ida/th10.exe.asm:44184](../../../ida/th10.exe.asm#L44184) |
| `0x0041FEB0` | missing | [ida/th10.exe.asm:44953](../../../ida/th10.exe.asm#L44953) |
| `0x0041FEF0` | missing | [ida/th10.exe.asm:44976](../../../ida/th10.exe.asm#L44976) |
| `0x0041FF30` | [ida/th10.exe.c:33026](../../../ida/th10.exe.c#L33026) | [ida/th10.exe.asm:45000](../../../ida/th10.exe.asm#L45000) |
| `0x00420000` | [ida/th10.exe.c:33055](../../../ida/th10.exe.c#L33055) | [ida/th10.exe.asm:45082](../../../ida/th10.exe.asm#L45082) |
| `0x004200C0` | [ida/th10.exe.c:33092](../../../ida/th10.exe.c#L33092) | [ida/th10.exe.asm:45136](../../../ida/th10.exe.asm#L45136) |
| `0x004200D0` | [ida/th10.exe.c:33098](../../../ida/th10.exe.c#L33098) | [ida/th10.exe.asm:45146](../../../ida/th10.exe.asm#L45146) |
| `0x004201B0` | missing | [ida/th10.exe.asm:45227](../../../ida/th10.exe.asm#L45227) |
| `0x00420B80` | [ida/th10.exe.c:33532](../../../ida/th10.exe.c#L33532) | [ida/th10.exe.asm:46131](../../../ida/th10.exe.asm#L46131) |
| `0x00421180` | [ida/th10.exe.c:33728](../../../ida/th10.exe.c#L33728) | [ida/th10.exe.asm:46690](../../../ida/th10.exe.asm#L46690) |
| `0x00421420` | [ida/th10.exe.c:33880](../../../ida/th10.exe.c#L33880) | [ida/th10.exe.asm:46913](../../../ida/th10.exe.asm#L46913) |
| `0x00421450` | [ida/th10.exe.c:33896](../../../ida/th10.exe.c#L33896) | [ida/th10.exe.asm:46939](../../../ida/th10.exe.asm#L46939) |
| `0x00421D00` | [ida/th10.exe.c:34258](../../../ida/th10.exe.c#L34258) | [ida/th10.exe.asm:47653](../../../ida/th10.exe.asm#L47653) |
| `0x00421D70` | [ida/th10.exe.c:34280](../../../ida/th10.exe.c#L34280) | [ida/th10.exe.asm:47695](../../../ida/th10.exe.asm#L47695) |
| `0x00421D80` | [ida/th10.exe.c:34287](../../../ida/th10.exe.c#L34287) | [ida/th10.exe.asm:47705](../../../ida/th10.exe.asm#L47705) |
| `0x00421D90` | [ida/th10.exe.c:34294](../../../ida/th10.exe.c#L34294) | [ida/th10.exe.asm:47715](../../../ida/th10.exe.asm#L47715) |
| `0x00421DA0` | [ida/th10.exe.c:34301](../../../ida/th10.exe.c#L34301) | [ida/th10.exe.asm:47725](../../../ida/th10.exe.asm#L47725) |
| `0x00421DB0` | [ida/th10.exe.c:34308](../../../ida/th10.exe.c#L34308) | [ida/th10.exe.asm:47735](../../../ida/th10.exe.asm#L47735) |
| `0x00421DC0` | [ida/th10.exe.c:34315](../../../ida/th10.exe.c#L34315) | [ida/th10.exe.asm:47745](../../../ida/th10.exe.asm#L47745) |
| `0x00421DD0` | [ida/th10.exe.c:34322](../../../ida/th10.exe.c#L34322) | [ida/th10.exe.asm:47755](../../../ida/th10.exe.asm#L47755) |
| `0x00421DE0` | [ida/th10.exe.c:34329](../../../ida/th10.exe.c#L34329) | [ida/th10.exe.asm:47765](../../../ida/th10.exe.asm#L47765) |
| `0x00421DF0` | [ida/th10.exe.c:34336](../../../ida/th10.exe.c#L34336) | [ida/th10.exe.asm:47775](../../../ida/th10.exe.asm#L47775) |
| `0x00421EF0` | [ida/th10.exe.c:34409](../../../ida/th10.exe.c#L34409) | [ida/th10.exe.asm:47892](../../../ida/th10.exe.asm#L47892) |
| `0x00421F50` | [ida/th10.exe.c:34430](../../../ida/th10.exe.c#L34430) | [ida/th10.exe.asm:47926](../../../ida/th10.exe.asm#L47926) |
| `0x00422AA0` | [ida/th10.exe.c:35003](../../../ida/th10.exe.c#L35003) | [ida/th10.exe.asm:48969](../../../ida/th10.exe.asm#L48969) |
| `0x00424590` | [ida/th10.exe.c:36404](../../../ida/th10.exe.c#L36404) | [ida/th10.exe.asm:51317](../../../ida/th10.exe.asm#L51317) |
| `0x004245A0` | [ida/th10.exe.c:36410](../../../ida/th10.exe.c#L36410) | [ida/th10.exe.asm:51327](../../../ida/th10.exe.asm#L51327) |
| `0x004245C0` | [ida/th10.exe.c:36417](../../../ida/th10.exe.c#L36417) | [ida/th10.exe.asm:51343](../../../ida/th10.exe.asm#L51343) |
| `0x00424600` | [ida/th10.exe.c:36423](../../../ida/th10.exe.c#L36423) | [ida/th10.exe.asm:51367](../../../ida/th10.exe.asm#L51367) |
| `0x00424620` | [ida/th10.exe.c:36429](../../../ida/th10.exe.c#L36429) | [ida/th10.exe.asm:51380](../../../ida/th10.exe.asm#L51380) |
| `0x00424640` | [ida/th10.exe.c:36439](../../../ida/th10.exe.c#L36439) | [ida/th10.exe.asm:51393](../../../ida/th10.exe.asm#L51393) |
| `0x00425090` | [ida/th10.exe.c:36907](../../../ida/th10.exe.c#L36907) | [ida/th10.exe.asm:52122](../../../ida/th10.exe.asm#L52122) |
| `0x00426500` | [ida/th10.exe.c:37905](../../../ida/th10.exe.c#L37905) | [ida/th10.exe.asm:53734](../../../ida/th10.exe.asm#L53734) |
| `0x00426510` | [ida/th10.exe.c:37911](../../../ida/th10.exe.c#L37911) | [ida/th10.exe.asm:53745](../../../ida/th10.exe.asm#L53745) |
| `0x00427AD0` | [ida/th10.exe.c:39019](../../../ida/th10.exe.c#L39019) | [ida/th10.exe.asm:55532](../../../ida/th10.exe.asm#L55532) |
| `0x00427D70` | [ida/th10.exe.c:39113](../../../ida/th10.exe.c#L39113) | [ida/th10.exe.asm:55803](../../../ida/th10.exe.asm#L55803) |
| `0x00427DF0` | [ida/th10.exe.c:39121](../../../ida/th10.exe.c#L39121) | [ida/th10.exe.asm:55861](../../../ida/th10.exe.asm#L55861) |
| `0x00427E10` | [ida/th10.exe.c:39127](../../../ida/th10.exe.c#L39127) | [ida/th10.exe.asm:55873](../../../ida/th10.exe.asm#L55873) |
| `0x00427E20` | [ida/th10.exe.c:39133](../../../ida/th10.exe.c#L39133) | [ida/th10.exe.asm:55883](../../../ida/th10.exe.asm#L55883) |
| `0x00428AD0` | [ida/th10.exe.c:39854](../../../ida/th10.exe.c#L39854) | [ida/th10.exe.asm:57131](../../../ida/th10.exe.asm#L57131) |
| `0x00428B10` | [ida/th10.exe.c:39870](../../../ida/th10.exe.c#L39870) | [ida/th10.exe.asm:57155](../../../ida/th10.exe.asm#L57155) |
| `0x00428CE0` | [ida/th10.exe.c:39959](../../../ida/th10.exe.c#L39959) | [ida/th10.exe.asm:57339](../../../ida/th10.exe.asm#L57339) |
| `0x00429A70` | [ida/th10.exe.c:40541](../../../ida/th10.exe.c#L40541) | [ida/th10.exe.asm:58528](../../../ida/th10.exe.asm#L58528) |
| `0x0042A3D0` | [ida/th10.exe.c:40959](../../../ida/th10.exe.c#L40959) | [ida/th10.exe.asm:59402](../../../ida/th10.exe.asm#L59402) |
| `0x0042A3E0` | [ida/th10.exe.c:40965](../../../ida/th10.exe.c#L40965) | [ida/th10.exe.asm:59415](../../../ida/th10.exe.asm#L59415) |
| `0x0042A430` | [ida/th10.exe.c:40988](../../../ida/th10.exe.c#L40988) | [ida/th10.exe.asm:59451](../../../ida/th10.exe.asm#L59451) |
| `0x0042A810` | [ida/th10.exe.c:41212](../../../ida/th10.exe.c#L41212) | [ida/th10.exe.asm:59759](../../../ida/th10.exe.asm#L59759) |
| `0x0042A970` | [ida/th10.exe.c:41253](../../../ida/th10.exe.c#L41253) | [ida/th10.exe.asm:59885](../../../ida/th10.exe.asm#L59885) |
| `0x0042A980` | [ida/th10.exe.c:41260](../../../ida/th10.exe.c#L41260) | [ida/th10.exe.asm:59895](../../../ida/th10.exe.asm#L59895) |
| `0x0042A990` | [ida/th10.exe.c:41267](../../../ida/th10.exe.c#L41267) | [ida/th10.exe.asm:59905](../../../ida/th10.exe.asm#L59905) |
| `0x0042A9B0` | [ida/th10.exe.c:41279](../../../ida/th10.exe.c#L41279) | [ida/th10.exe.asm:59919](../../../ida/th10.exe.asm#L59919) |
| `0x0042A9C0` | [ida/th10.exe.c:41286](../../../ida/th10.exe.c#L41286) | [ida/th10.exe.asm:59929](../../../ida/th10.exe.asm#L59929) |
| `0x0042A9D0` | [ida/th10.exe.c:41293](../../../ida/th10.exe.c#L41293) | [ida/th10.exe.asm:59939](../../../ida/th10.exe.asm#L59939) |
| `0x0042AC20` | [ida/th10.exe.c:41370](../../../ida/th10.exe.c#L41370) | [ida/th10.exe.asm:60162](../../../ida/th10.exe.asm#L60162) |
| `0x0042AC60` | [ida/th10.exe.c:41392](../../../ida/th10.exe.c#L41392) | [ida/th10.exe.asm:60191](../../../ida/th10.exe.asm#L60191) |
| `0x0042B6D0` | [ida/th10.exe.c:41921](../../../ida/th10.exe.c#L41921) | [ida/th10.exe.asm:61214](../../../ida/th10.exe.asm#L61214) |
| `0x0042B9A0` | missing | [ida/th10.exe.asm:61476](../../../ida/th10.exe.asm#L61476) |
| `0x0042B9B0` | [ida/th10.exe.c:42023](../../../ida/th10.exe.c#L42023) | [ida/th10.exe.asm:61489](../../../ida/th10.exe.asm#L61489) |
| `0x0042BA90` | [ida/th10.exe.c:42090](../../../ida/th10.exe.c#L42090) | [ida/th10.exe.asm:61589](../../../ida/th10.exe.asm#L61589) |
| `0x0042BAA0` | [ida/th10.exe.c:42100](../../../ida/th10.exe.c#L42100) | [ida/th10.exe.asm:61603](../../../ida/th10.exe.asm#L61603) |
| `0x0042BAD0` | [ida/th10.exe.c:42110](../../../ida/th10.exe.c#L42110) | [ida/th10.exe.asm:61626](../../../ida/th10.exe.asm#L61626) |
| `0x0042BB30` | [ida/th10.exe.c:42134](../../../ida/th10.exe.c#L42134) | [ida/th10.exe.asm:61675](../../../ida/th10.exe.asm#L61675) |
| `0x0042BBD0` | [ida/th10.exe.c:42165](../../../ida/th10.exe.c#L42165) | [ida/th10.exe.asm:61714](../../../ida/th10.exe.asm#L61714) |
| `0x0042BC30` | [ida/th10.exe.c:42189](../../../ida/th10.exe.c#L42189) | [ida/th10.exe.asm:61748](../../../ida/th10.exe.asm#L61748) |
| `0x0042BE10` | [ida/th10.exe.c:42274](../../../ida/th10.exe.c#L42274) | [ida/th10.exe.asm:61904](../../../ida/th10.exe.asm#L61904) |
| `0x0042BE20` | [ida/th10.exe.c:42282](../../../ida/th10.exe.c#L42282) | [ida/th10.exe.asm:61917](../../../ida/th10.exe.asm#L61917) |
| `0x0042BF30` | [ida/th10.exe.c:42336](../../../ida/th10.exe.c#L42336) | [ida/th10.exe.asm:62014](../../../ida/th10.exe.asm#L62014) |
| `0x0042BFC0` | [ida/th10.exe.c:42359](../../../ida/th10.exe.c#L42359) | [ida/th10.exe.asm:62080](../../../ida/th10.exe.asm#L62080) |
| `0x0042C580` | missing | [ida/th10.exe.asm:62566](../../../ida/th10.exe.asm#L62566) |
| `0x0042C590` | [ida/th10.exe.c:42602](../../../ida/th10.exe.c#L42602) | [ida/th10.exe.asm:62575](../../../ida/th10.exe.asm#L62575) |
| `0x0042C5B0` | [ida/th10.exe.c:42608](../../../ida/th10.exe.c#L42608) | [ida/th10.exe.asm:62590](../../../ida/th10.exe.asm#L62590) |
| `0x0042C7C0` | [ida/th10.exe.c:42741](../../../ida/th10.exe.c#L42741) | [ida/th10.exe.asm:62790](../../../ida/th10.exe.asm#L62790) |
| `0x0042C830` | [ida/th10.exe.c:42748](../../../ida/th10.exe.c#L42748) | [ida/th10.exe.asm:62838](../../../ida/th10.exe.asm#L62838) |
| `0x0042C9F0` | [ida/th10.exe.c:42837](../../../ida/th10.exe.c#L42837) | [ida/th10.exe.asm:62981](../../../ida/th10.exe.asm#L62981) |
| `0x0042D2E0` | [ida/th10.exe.c:43351](../../../ida/th10.exe.c#L43351) | [ida/th10.exe.asm:63826](../../../ida/th10.exe.asm#L63826) |
| `0x0042D2F0` | [ida/th10.exe.c:43358](../../../ida/th10.exe.c#L43358) | [ida/th10.exe.asm:63836](../../../ida/th10.exe.asm#L63836) |
| `0x00434B60` | [ida/th10.exe.c:49974](../../../ida/th10.exe.c#L49974) | [ida/th10.exe.asm:74877](../../../ida/th10.exe.asm#L74877) |
| `0x00434B70` | [ida/th10.exe.c:49980](../../../ida/th10.exe.c#L49980) | [ida/th10.exe.asm:74887](../../../ida/th10.exe.asm#L74887) |
| `0x00434BE0` | [ida/th10.exe.c:49987](../../../ida/th10.exe.c#L49987) | [ida/th10.exe.asm:74920](../../../ida/th10.exe.asm#L74920) |
| `0x00434BF0` | [ida/th10.exe.c:49993](../../../ida/th10.exe.c#L49993) | [ida/th10.exe.asm:74930](../../../ida/th10.exe.asm#L74930) |
| `0x00434C10` | [ida/th10.exe.c:49999](../../../ida/th10.exe.c#L49999) | [ida/th10.exe.asm:74943](../../../ida/th10.exe.asm#L74943) |
| `0x00434D70` | [ida/th10.exe.c:50085](../../../ida/th10.exe.c#L50085) | [ida/th10.exe.asm:75122](../../../ida/th10.exe.asm#L75122) |
| `0x00435300` | [ida/th10.exe.c:50374](../../../ida/th10.exe.c#L50374) | [ida/th10.exe.asm:75842](../../../ida/th10.exe.asm#L75842) |
| `0x004356C0` | [ida/th10.exe.c:50631](../../../ida/th10.exe.c#L50631) | [ida/th10.exe.asm:76374](../../../ida/th10.exe.asm#L76374) |
| `0x004359A0` | [ida/th10.exe.c:50766](../../../ida/th10.exe.c#L50766) | [ida/th10.exe.asm:76719](../../../ida/th10.exe.asm#L76719) |
| `0x00436400` | [ida/th10.exe.c:51458](../../../ida/th10.exe.c#L51458) | [ida/th10.exe.asm:77813](../../../ida/th10.exe.asm#L77813) |
| `0x004364F0` | [ida/th10.exe.c:51524](../../../ida/th10.exe.c#L51524) | [ida/th10.exe.asm:77956](../../../ida/th10.exe.asm#L77956) |
| `0x00436770` | [ida/th10.exe.c:51670](../../../ida/th10.exe.c#L51670) | [ida/th10.exe.asm:78264](../../../ida/th10.exe.asm#L78264) |
| `0x004367A0` | [ida/th10.exe.c:51680](../../../ida/th10.exe.c#L51680) | [ida/th10.exe.asm:78292](../../../ida/th10.exe.asm#L78292) |
| `0x004367E0` | [ida/th10.exe.c:51687](../../../ida/th10.exe.c#L51687) | [ida/th10.exe.asm:78323](../../../ida/th10.exe.asm#L78323) |
| `0x004367F0` | [ida/th10.exe.c:51695](../../../ida/th10.exe.c#L51695) | [ida/th10.exe.asm:78334](../../../ida/th10.exe.asm#L78334) |
| `0x00436800` | [ida/th10.exe.c:51701](../../../ida/th10.exe.c#L51701) | [ida/th10.exe.asm:78344](../../../ida/th10.exe.asm#L78344) |
| `0x00436810` | [ida/th10.exe.c:51707](../../../ida/th10.exe.c#L51707) | [ida/th10.exe.asm:78354](../../../ida/th10.exe.asm#L78354) |
| `0x00436820` | [ida/th10.exe.c:51713](../../../ida/th10.exe.c#L51713) | [ida/th10.exe.asm:78364](../../../ida/th10.exe.asm#L78364) |
| `0x00436830` | [ida/th10.exe.c:51719](../../../ida/th10.exe.c#L51719) | [ida/th10.exe.asm:78374](../../../ida/th10.exe.asm#L78374) |
| `0x00436840` | [ida/th10.exe.c:51725](../../../ida/th10.exe.c#L51725) | [ida/th10.exe.asm:78384](../../../ida/th10.exe.asm#L78384) |
| `0x00436850` | [ida/th10.exe.c:51731](../../../ida/th10.exe.c#L51731) | [ida/th10.exe.asm:78394](../../../ida/th10.exe.asm#L78394) |
| `0x00436890` | [ida/th10.exe.c:51737](../../../ida/th10.exe.c#L51737) | [ida/th10.exe.asm:78423](../../../ida/th10.exe.asm#L78423) |
| `0x00436A20` | missing | [ida/th10.exe.asm:78564](../../../ida/th10.exe.asm#L78564) |
| `0x00436D30` | [ida/th10.exe.c:51873](../../../ida/th10.exe.c#L51873) | [ida/th10.exe.asm:78879](../../../ida/th10.exe.asm#L78879) |
| `0x004372A0` | [ida/th10.exe.c:52148](../../../ida/th10.exe.c#L52148) | [ida/th10.exe.asm:79473](../../../ida/th10.exe.asm#L79473) |
| `0x00437380` | [ida/th10.exe.c:52191](../../../ida/th10.exe.c#L52191) | [ida/th10.exe.asm:79577](../../../ida/th10.exe.asm#L79577) |
| `0x004383F0` | [ida/th10.exe.c:52884](../../../ida/th10.exe.c#L52884) | [ida/th10.exe.asm:81300](../../../ida/th10.exe.asm#L81300) |
| `0x00438400` | [ida/th10.exe.c:52890](../../../ida/th10.exe.c#L52890) | [ida/th10.exe.asm:81310](../../../ida/th10.exe.asm#L81310) |
| `0x00438410` | [ida/th10.exe.c:52896](../../../ida/th10.exe.c#L52896) | [ida/th10.exe.asm:81320](../../../ida/th10.exe.asm#L81320) |
| `0x004385B0` | [ida/th10.exe.c:53027](../../../ida/th10.exe.c#L53027) | [ida/th10.exe.asm:81577](../../../ida/th10.exe.asm#L81577) |
| `0x00438974` | [ida/th10.exe.c:53168](../../../ida/th10.exe.c#L53168) | [ida/th10.exe.asm:82012](../../../ida/th10.exe.asm#L82012) |
| `0x004389B0` | [ida/th10.exe.c:53182](../../../ida/th10.exe.c#L53182) | [ida/th10.exe.asm:82048](../../../ida/th10.exe.asm#L82048) |
| `0x004389C0` | [ida/th10.exe.c:53189](../../../ida/th10.exe.c#L53189) | [ida/th10.exe.asm:82058](../../../ida/th10.exe.asm#L82058) |
| `0x004389D0` | [ida/th10.exe.c:53196](../../../ida/th10.exe.c#L53196) | [ida/th10.exe.asm:82068](../../../ida/th10.exe.asm#L82068) |
| `0x00439660` | [ida/th10.exe.c:53771](../../../ida/th10.exe.c#L53771) | [ida/th10.exe.asm:83286](../../../ida/th10.exe.asm#L83286) |
| `0x0043A3A0` | [ida/th10.exe.c:54249](../../../ida/th10.exe.c#L54249) | [ida/th10.exe.asm:84482](../../../ida/th10.exe.asm#L84482) |
| `0x0043A490` | [ida/th10.exe.c:54285](../../../ida/th10.exe.c#L54285) | [ida/th10.exe.asm:84573](../../../ida/th10.exe.asm#L84573) |
| `0x0043A5C0` | [ida/th10.exe.c:54293](../../../ida/th10.exe.c#L54293) | [ida/th10.exe.asm:84705](../../../ida/th10.exe.asm#L84705) |
| `0x0043A6E0` | [ida/th10.exe.c:54304](../../../ida/th10.exe.c#L54304) | [ida/th10.exe.asm:84821](../../../ida/th10.exe.asm#L84821) |
| `0x0043A6F0` | [ida/th10.exe.c:54310](../../../ida/th10.exe.c#L54310) | [ida/th10.exe.asm:84836](../../../ida/th10.exe.asm#L84836) |
| `0x0043A9B0` | [ida/th10.exe.c:54378](../../../ida/th10.exe.c#L54378) | [ida/th10.exe.asm:85047](../../../ida/th10.exe.asm#L85047) |
| `0x0043AC90` | [ida/th10.exe.c:54499](../../../ida/th10.exe.c#L54499) | [ida/th10.exe.asm:85317](../../../ida/th10.exe.asm#L85317) |
| `0x0043BA90` | [ida/th10.exe.c:55097](../../../ida/th10.exe.c#L55097) | [ida/th10.exe.asm:86660](../../../ida/th10.exe.asm#L86660) |
| `0x0043BAF0` | [ida/th10.exe.c:55115](../../../ida/th10.exe.c#L55115) | [ida/th10.exe.asm:86690](../../../ida/th10.exe.asm#L86690) |
| `0x0043BB30` | [ida/th10.exe.c:55128](../../../ida/th10.exe.c#L55128) | [ida/th10.exe.asm:86721](../../../ida/th10.exe.asm#L86721) |
| `0x0043BBF0` | [ida/th10.exe.c:55150](../../../ida/th10.exe.c#L55150) | [ida/th10.exe.asm:86784](../../../ida/th10.exe.asm#L86784) |
| `0x0043BC00` | [ida/th10.exe.c:55156](../../../ida/th10.exe.c#L55156) | [ida/th10.exe.asm:86794](../../../ida/th10.exe.asm#L86794) |
| `0x0043BD40` | missing | [ida/th10.exe.asm:86913](../../../ida/th10.exe.asm#L86913) |
| `0x0043BF90` | [ida/th10.exe.c:55302](../../../ida/th10.exe.c#L55302) | [ida/th10.exe.asm:87138](../../../ida/th10.exe.asm#L87138) |
| `0x0043C230` | [ida/th10.exe.c:55409](../../../ida/th10.exe.c#L55409) | [ida/th10.exe.asm:87378](../../../ida/th10.exe.asm#L87378) |
| `0x0043C310` | [ida/th10.exe.c:55448](../../../ida/th10.exe.c#L55448) | [ida/th10.exe.asm:87483](../../../ida/th10.exe.asm#L87483) |
| `0x0043C3C0` | [ida/th10.exe.c:55490](../../../ida/th10.exe.c#L55490) | [ida/th10.exe.asm:87563](../../../ida/th10.exe.asm#L87563) |
| `0x0043C460` | [ida/th10.exe.c:55520](../../../ida/th10.exe.c#L55520) | [ida/th10.exe.asm:87627](../../../ida/th10.exe.asm#L87627) |
| `0x0043C550` | [ida/th10.exe.c:55571](../../../ida/th10.exe.c#L55571) | [ida/th10.exe.asm:87736](../../../ida/th10.exe.asm#L87736) |
| `0x0043C710` | [ida/th10.exe.c:55661](../../../ida/th10.exe.c#L55661) | [ida/th10.exe.asm:87903](../../../ida/th10.exe.asm#L87903) |
| `0x0043CCF0` | [ida/th10.exe.c:55925](../../../ida/th10.exe.c#L55925) | [ida/th10.exe.asm:88521](../../../ida/th10.exe.asm#L88521) |
| `0x0043D080` | [ida/th10.exe.c:56086](../../../ida/th10.exe.c#L56086) | [ida/th10.exe.asm:88849](../../../ida/th10.exe.asm#L88849) |
| `0x0043E520` | [ida/th10.exe.c:57141](../../../ida/th10.exe.c#L57141) | [ida/th10.exe.asm:90965](../../../ida/th10.exe.asm#L90965) |
| `0x0043E530` | [ida/th10.exe.c:57147](../../../ida/th10.exe.c#L57147) | [ida/th10.exe.asm:90975](../../../ida/th10.exe.asm#L90975) |
| `0x0043E560` | [ida/th10.exe.c:57153](../../../ida/th10.exe.c#L57153) | [ida/th10.exe.asm:90995](../../../ida/th10.exe.asm#L90995) |
| `0x0043E9D0` | [ida/th10.exe.c:57368](../../../ida/th10.exe.c#L57368) | [ida/th10.exe.asm:91326](../../../ida/th10.exe.asm#L91326) |
| `0x004415C0` | [ida/th10.exe.c:59311](../../../ida/th10.exe.c#L59311) | [ida/th10.exe.asm:95414](../../../ida/th10.exe.asm#L95414) |
| `0x00441940` | [ida/th10.exe.c:59532](../../../ida/th10.exe.c#L59532) | [ida/th10.exe.asm:95778](../../../ida/th10.exe.asm#L95778) |
| `0x00441D60` | [ida/th10.exe.c:59812](../../../ida/th10.exe.c#L59812) | [ida/th10.exe.asm:96190](../../../ida/th10.exe.asm#L96190) |
| `0x00441E40` | [ida/th10.exe.c:59818](../../../ida/th10.exe.c#L59818) | [ida/th10.exe.asm:96267](../../../ida/th10.exe.asm#L96267) |
| `0x00441FD0` | [ida/th10.exe.c:59882](../../../ida/th10.exe.c#L59882) | [ida/th10.exe.asm:96430](../../../ida/th10.exe.asm#L96430) |
| `0x00441FE0` | [ida/th10.exe.c:59889](../../../ida/th10.exe.c#L59889) | [ida/th10.exe.asm:96440](../../../ida/th10.exe.asm#L96440) |
| `0x00441FF0` | [ida/th10.exe.c:59896](../../../ida/th10.exe.c#L59896) | [ida/th10.exe.asm:96450](../../../ida/th10.exe.asm#L96450) |
| `0x00442000` | [ida/th10.exe.c:59903](../../../ida/th10.exe.c#L59903) | [ida/th10.exe.asm:96461](../../../ida/th10.exe.asm#L96461) |
| `0x00442120` | [ida/th10.exe.c:59960](../../../ida/th10.exe.c#L59960) | [ida/th10.exe.asm:96558](../../../ida/th10.exe.asm#L96558) |
| `0x00442170` | [ida/th10.exe.c:59967](../../../ida/th10.exe.c#L59967) | [ida/th10.exe.asm:96586](../../../ida/th10.exe.asm#L96586) |
| `0x004421A0` | [ida/th10.exe.c:59974](../../../ida/th10.exe.c#L59974) | [ida/th10.exe.asm:96604](../../../ida/th10.exe.asm#L96604) |
| `0x004422F0` | [ida/th10.exe.c:60036](../../../ida/th10.exe.c#L60036) | [ida/th10.exe.asm:96714](../../../ida/th10.exe.asm#L96714) |
| `0x00442390` | [ida/th10.exe.c:60077](../../../ida/th10.exe.c#L60077) | [ida/th10.exe.asm:96768](../../../ida/th10.exe.asm#L96768) |
| `0x004423A0` | [ida/th10.exe.c:60084](../../../ida/th10.exe.c#L60084) | [ida/th10.exe.asm:96779](../../../ida/th10.exe.asm#L96779) |
| `0x00442AD0` | [ida/th10.exe.c:60373](../../../ida/th10.exe.c#L60373) | [ida/th10.exe.asm:97411](../../../ida/th10.exe.asm#L97411) |
| `0x00442F30` | [ida/th10.exe.c:60521](../../../ida/th10.exe.c#L60521) | [ida/th10.exe.asm:97752](../../../ida/th10.exe.asm#L97752) |
| `0x004436C0` | [ida/th10.exe.c:60757](../../../ida/th10.exe.c#L60757) | [ida/th10.exe.asm:98303](../../../ida/th10.exe.asm#L98303) |
| `0x00443910` | [ida/th10.exe.c:60890](../../../ida/th10.exe.c#L60890) | [ida/th10.exe.asm:98503](../../../ida/th10.exe.asm#L98503) |
| `0x00445880` | [ida/th10.exe.c:62157](../../../ida/th10.exe.c#L62157) | [ida/th10.exe.asm:101240](../../../ida/th10.exe.asm#L101240) |
| `0x004458A0` | [ida/th10.exe.c:62164](../../../ida/th10.exe.c#L62164) | [ida/th10.exe.asm:101256](../../../ida/th10.exe.asm#L101256) |
| `0x004458D0` | [ida/th10.exe.c:62181](../../../ida/th10.exe.c#L62181) | [ida/th10.exe.asm:101290](../../../ida/th10.exe.asm#L101290) |
| `0x004458E0` | [ida/th10.exe.c:62187](../../../ida/th10.exe.c#L62187) | [ida/th10.exe.asm:101300](../../../ida/th10.exe.asm#L101300) |
| `0x004458F0` | [ida/th10.exe.c:62193](../../../ida/th10.exe.c#L62193) | [ida/th10.exe.asm:101310](../../../ida/th10.exe.asm#L101310) |
| `0x00446210` | [ida/th10.exe.c:62868](../../../ida/th10.exe.c#L62868) | [ida/th10.exe.asm:102090](../../../ida/th10.exe.asm#L102090) |
| `0x00446500` | [ida/th10.exe.c:63000](../../../ida/th10.exe.c#L63000) | [ida/th10.exe.asm:102322](../../../ida/th10.exe.asm#L102322) |
| `0x00446B70` | [ida/th10.exe.c:63346](../../../ida/th10.exe.c#L63346) | [ida/th10.exe.asm:102999](../../../ida/th10.exe.asm#L102999) |
| `0x00447C80` | [ida/th10.exe.c:64234](../../../ida/th10.exe.c#L64234) | [ida/th10.exe.asm:104833](../../../ida/th10.exe.asm#L104833) |
| `0x00447EC0` | [ida/th10.exe.c:64337](../../../ida/th10.exe.c#L64337) | [ida/th10.exe.asm:105065](../../../ida/th10.exe.asm#L105065) |
| `0x00448360` | [ida/th10.exe.c:64521](../../../ida/th10.exe.c#L64521) | [ida/th10.exe.asm:105552](../../../ida/th10.exe.asm#L105552) |
| `0x004485D0` | [ida/th10.exe.c:64666](../../../ida/th10.exe.c#L64666) | [ida/th10.exe.asm:105826](../../../ida/th10.exe.asm#L105826) |
| `0x004485E0` | [ida/th10.exe.c:64672](../../../ida/th10.exe.c#L64672) | [ida/th10.exe.asm:105836](../../../ida/th10.exe.asm#L105836) |
| `0x004485F0` | [ida/th10.exe.c:64715](../../../ida/th10.exe.c#L64715) | [ida/th10.exe.asm:105849](../../../ida/th10.exe.asm#L105849) |
| `0x00448600` | [ida/th10.exe.c:64721](../../../ida/th10.exe.c#L64721) | [ida/th10.exe.asm:105863](../../../ida/th10.exe.asm#L105863) |
| `0x00448610` | [ida/th10.exe.c:64727](../../../ida/th10.exe.c#L64727) | [ida/th10.exe.asm:105877](../../../ida/th10.exe.asm#L105877) |
| `0x00448620` | [ida/th10.exe.c:64733](../../../ida/th10.exe.c#L64733) | [ida/th10.exe.asm:105891](../../../ida/th10.exe.asm#L105891) |
| `0x004486A0` | [ida/th10.exe.c:64754](../../../ida/th10.exe.c#L64754) | [ida/th10.exe.asm:105936](../../../ida/th10.exe.asm#L105936) |
| `0x004486B0` | [ida/th10.exe.c:64760](../../../ida/th10.exe.c#L64760) | [ida/th10.exe.asm:105950](../../../ida/th10.exe.asm#L105950) |
| `0x004486C0` | [ida/th10.exe.c:64766](../../../ida/th10.exe.c#L64766) | [ida/th10.exe.asm:105964](../../../ida/th10.exe.asm#L105964) |
| `0x004486D0` | [ida/th10.exe.c:64772](../../../ida/th10.exe.c#L64772) | [ida/th10.exe.asm:105978](../../../ida/th10.exe.asm#L105978) |
| `0x004486E0` | [ida/th10.exe.c:64778](../../../ida/th10.exe.c#L64778) | [ida/th10.exe.asm:105992](../../../ida/th10.exe.asm#L105992) |
| `0x004486F0` | [ida/th10.exe.c:64784](../../../ida/th10.exe.c#L64784) | [ida/th10.exe.asm:106006](../../../ida/th10.exe.asm#L106006) |
| `0x00448700` | [ida/th10.exe.c:64790](../../../ida/th10.exe.c#L64790) | [ida/th10.exe.asm:106020](../../../ida/th10.exe.asm#L106020) |
| `0x00448710` | [ida/th10.exe.c:64796](../../../ida/th10.exe.c#L64796) | [ida/th10.exe.asm:106034](../../../ida/th10.exe.asm#L106034) |
| `0x00448720` | [ida/th10.exe.c:64802](../../../ida/th10.exe.c#L64802) | [ida/th10.exe.asm:106048](../../../ida/th10.exe.asm#L106048) |
| `0x00448730` | [ida/th10.exe.c:64808](../../../ida/th10.exe.c#L64808) | [ida/th10.exe.asm:106062](../../../ida/th10.exe.asm#L106062) |
| `0x00448740` | [ida/th10.exe.c:64814](../../../ida/th10.exe.c#L64814) | [ida/th10.exe.asm:106076](../../../ida/th10.exe.asm#L106076) |
| `0x00448770` | [ida/th10.exe.c:64829](../../../ida/th10.exe.c#L64829) | [ida/th10.exe.asm:106095](../../../ida/th10.exe.asm#L106095) |
| `0x004487C0` | [ida/th10.exe.c:64843](../../../ida/th10.exe.c#L64843) | [ida/th10.exe.asm:106123](../../../ida/th10.exe.asm#L106123) |
| `0x00448810` | [ida/th10.exe.c:64857](../../../ida/th10.exe.c#L64857) | [ida/th10.exe.asm:106151](../../../ida/th10.exe.asm#L106151) |
| `0x00448E80` | [ida/th10.exe.c:65213](../../../ida/th10.exe.c#L65213) | [ida/th10.exe.asm:106852](../../../ida/th10.exe.asm#L106852) |
| `0x00448EE0` | [ida/th10.exe.c:65228](../../../ida/th10.exe.c#L65228) | [ida/th10.exe.asm:106893](../../../ida/th10.exe.asm#L106893) |
| `0x00448FB0` | [ida/th10.exe.c:65259](../../../ida/th10.exe.c#L65259) | [ida/th10.exe.asm:106971](../../../ida/th10.exe.asm#L106971) |
| `0x00449010` | [ida/th10.exe.c:65274](../../../ida/th10.exe.c#L65274) | [ida/th10.exe.asm:107012](../../../ida/th10.exe.asm#L107012) |
| `0x004490E0` | [ida/th10.exe.c:65305](../../../ida/th10.exe.c#L65305) | [ida/th10.exe.asm:107090](../../../ida/th10.exe.asm#L107090) |
| `0x00449140` | [ida/th10.exe.c:65320](../../../ida/th10.exe.c#L65320) | [ida/th10.exe.asm:107131](../../../ida/th10.exe.asm#L107131) |
| `0x00449440` | [ida/th10.exe.c:65525](../../../ida/th10.exe.c#L65525) | [ida/th10.exe.asm:107503](../../../ida/th10.exe.asm#L107503) |
| `0x00449700` | [ida/th10.exe.c:65641](../../../ida/th10.exe.c#L65641) | [ida/th10.exe.asm:107797](../../../ida/th10.exe.asm#L107797) |
| `0x00449A20` | [ida/th10.exe.c:65751](../../../ida/th10.exe.c#L65751) | [ida/th10.exe.asm:108127](../../../ida/th10.exe.asm#L108127) |
| `0x0044A950` | [ida/th10.exe.c:66523](../../../ida/th10.exe.c#L66523) | [ida/th10.exe.asm:109743](../../../ida/th10.exe.asm#L109743) |
| `0x0044A9D0` | [ida/th10.exe.c:66570](../../../ida/th10.exe.c#L66570) | [ida/th10.exe.asm:109803](../../../ida/th10.exe.asm#L109803) |
| `0x0044AD30` | [ida/th10.exe.c:66736](../../../ida/th10.exe.c#L66736) | [ida/th10.exe.asm:110150](../../../ida/th10.exe.asm#L110150) |
| `0x0044C000` | [ida/th10.exe.c:67641](../../../ida/th10.exe.c#L67641) | [ida/th10.exe.asm:112193](../../../ida/th10.exe.asm#L112193) |
| `0x0044C140` | [ida/th10.exe.c:67681](../../../ida/th10.exe.c#L67681) | [ida/th10.exe.asm:112373](../../../ida/th10.exe.asm#L112373) |
| `0x0044C590` | [ida/th10.exe.c:67876](../../../ida/th10.exe.c#L67876) | [ida/th10.exe.asm:112825](../../../ida/th10.exe.asm#L112825) |
| `0x0044C620` | [ida/th10.exe.c:67894](../../../ida/th10.exe.c#L67894) | [ida/th10.exe.asm:112884](../../../ida/th10.exe.asm#L112884) |
| `0x0044DD30` | [ida/th10.exe.c:68995](../../../ida/th10.exe.c#L68995) | [ida/th10.exe.asm:115323](../../../ida/th10.exe.asm#L115323) |
| `0x0044DF40` | [ida/th10.exe.c:69105](../../../ida/th10.exe.c#L69105) | [ida/th10.exe.asm:115547](../../../ida/th10.exe.asm#L115547) |
| `0x0044DF50` | [ida/th10.exe.c:69111](../../../ida/th10.exe.c#L69111) | [ida/th10.exe.asm:115557](../../../ida/th10.exe.asm#L115557) |
| `0x0044DF60` | [ida/th10.exe.c:69118](../../../ida/th10.exe.c#L69118) | [ida/th10.exe.asm:115567](../../../ida/th10.exe.asm#L115567) |
| `0x004501E0` | [ida/th10.exe.c:71114](../../../ida/th10.exe.c#L71114) | [ida/th10.exe.asm:118598](../../../ida/th10.exe.asm#L118598) |
| `0x004501F0` | [ida/th10.exe.c:71121](../../../ida/th10.exe.c#L71121) | [ida/th10.exe.asm:118608](../../../ida/th10.exe.asm#L118608) |
| `0x00450200` | [ida/th10.exe.c:71128](../../../ida/th10.exe.c#L71128) | [ida/th10.exe.asm:118619](../../../ida/th10.exe.asm#L118619) |
| `0x00450210` | [ida/th10.exe.c:71134](../../../ida/th10.exe.c#L71134) | [ida/th10.exe.asm:118630](../../../ida/th10.exe.asm#L118630) |
| `0x00450500` | [ida/th10.exe.c:71302](../../../ida/th10.exe.c#L71302) | [ida/th10.exe.asm:118994](../../../ida/th10.exe.asm#L118994) |
| `0x00453111` | [ida/th10.exe.c:71396](../../../ida/th10.exe.c#L71396) | [ida/th10.exe.asm:120119](../../../ida/th10.exe.asm#L120119) |
| `0x0045326D` | [ida/th10.exe.c:71450](../../../ida/th10.exe.c#L71450) | [ida/th10.exe.asm:120264](../../../ida/th10.exe.asm#L120264) |
| `0x00453A9B` | [ida/th10.exe.c:71461](../../../ida/th10.exe.c#L71461) | [ida/th10.exe.asm:120380](../../../ida/th10.exe.asm#L120380) |
| `0x00453B60` | [ida/th10.exe.c:71467](../../../ida/th10.exe.c#L71467) | [ida/th10.exe.asm:120397](../../../ida/th10.exe.asm#L120397) |
| `0x00454ED7` | [ida/th10.exe.c:71474](../../../ida/th10.exe.c#L71474) | [ida/th10.exe.asm:120516](../../../ida/th10.exe.asm#L120516) |
| `0x004556E0` | [ida/th10.exe.c:71930](../../../ida/th10.exe.c#L71930) | [ida/th10.exe.asm:121369](../../../ida/th10.exe.asm#L121369) |
| `0x00455731` | [ida/th10.exe.c:71940](../../../ida/th10.exe.c#L71940) | [ida/th10.exe.asm:121409](../../../ida/th10.exe.asm#L121409) |
| `0x004557F0` | [ida/th10.exe.c:71947](../../../ida/th10.exe.c#L71947) | [ida/th10.exe.asm:121433](../../../ida/th10.exe.asm#L121433) |
| `0x004557F6` | [ida/th10.exe.c:71954](../../../ida/th10.exe.c#L71954) | [ida/th10.exe.asm:121442](../../../ida/th10.exe.asm#L121442) |
| `0x0045598D` | [ida/th10.exe.c:71960](../../../ida/th10.exe.c#L71960) | [ida/th10.exe.asm:121453](../../../ida/th10.exe.asm#L121453) |
| `0x00455B19` | [ida/th10.exe.c:71966](../../../ida/th10.exe.c#L71966) | [ida/th10.exe.asm:121466](../../../ida/th10.exe.asm#L121466) |
| `0x00455BF3` | [ida/th10.exe.c:72011](../../../ida/th10.exe.c#L72011) | [ida/th10.exe.asm:121554](../../../ida/th10.exe.asm#L121554) |
| `0x00455D53` | [ida/th10.exe.c:72061](../../../ida/th10.exe.c#L72061) | [ida/th10.exe.asm:121725](../../../ida/th10.exe.asm#L121725) |
| `0x00455FE7` | [ida/th10.exe.c:72192](../../../ida/th10.exe.c#L72192) | [ida/th10.exe.asm:121958](../../../ida/th10.exe.asm#L121958) |
| `0x00456674` | [ida/th10.exe.c:72305](../../../ida/th10.exe.c#L72305) | [ida/th10.exe.asm:122195](../../../ida/th10.exe.asm#L122195) |
| `0x00456AC4` | [ida/th10.exe.c:72341](../../../ida/th10.exe.c#L72341) | [ida/th10.exe.asm:122332](../../../ida/th10.exe.asm#L122332) |
| `0x00457395` | [ida/th10.exe.c:72352](../../../ida/th10.exe.c#L72352) | [ida/th10.exe.asm:122360](../../../ida/th10.exe.asm#L122360) |
| `0x0045794D` | [ida/th10.exe.c:72461](../../../ida/th10.exe.c#L72461) | [ida/th10.exe.asm:122641](../../../ida/th10.exe.asm#L122641) |
| `0x00457A7C` | [ida/th10.exe.c:72515](../../../ida/th10.exe.c#L72515) | [ida/th10.exe.asm:122800](../../../ida/th10.exe.asm#L122800) |
| `0x004588A7` | [ida/th10.exe.c:73398](../../../ida/th10.exe.c#L73398) | [ida/th10.exe.asm:124055](../../../ida/th10.exe.asm#L124055) |
| `0x00458EFD` | [ida/th10.exe.c:73501](../../../ida/th10.exe.c#L73501) | [ida/th10.exe.asm:124411](../../../ida/th10.exe.asm#L124411) |
| `0x00459776` | [ida/th10.exe.c:73566](../../../ida/th10.exe.c#L73566) | [ida/th10.exe.asm:124626](../../../ida/th10.exe.asm#L124626) |
| `0x004597BA` | [ida/th10.exe.c:73579](../../../ida/th10.exe.c#L73579) | [ida/th10.exe.asm:124676](../../../ida/th10.exe.asm#L124676) |
| `0x00459CD2` | [ida/th10.exe.c:73592](../../../ida/th10.exe.c#L73592) | [ida/th10.exe.asm:124738](../../../ida/th10.exe.asm#L124738) |
| `0x00459E8E` | [ida/th10.exe.c:73697](../../../ida/th10.exe.c#L73697) | [ida/th10.exe.asm:124942](../../../ida/th10.exe.asm#L124942) |
| `0x00459FA7` | [ida/th10.exe.c:73730](../../../ida/th10.exe.c#L73730) | [ida/th10.exe.asm:125028](../../../ida/th10.exe.asm#L125028) |
| `0x0045A195` | [ida/th10.exe.c:73737](../../../ida/th10.exe.c#L73737) | [ida/th10.exe.asm:125135](../../../ida/th10.exe.asm#L125135) |
| `0x0045A19B` | [ida/th10.exe.c:73744](../../../ida/th10.exe.c#L73744) | [ida/th10.exe.asm:125144](../../../ida/th10.exe.asm#L125144) |
| `0x0045AF1D` | [ida/th10.exe.c:73751](../../../ida/th10.exe.c#L73751) | [ida/th10.exe.asm:125205](../../../ida/th10.exe.asm#L125205) |
| `0x0045B02D` | [ida/th10.exe.c:73817](../../../ida/th10.exe.c#L73817) | [ida/th10.exe.asm:125333](../../../ida/th10.exe.asm#L125333) |
| `0x0045BB33` | [ida/th10.exe.c:73824](../../../ida/th10.exe.c#L73824) | [ida/th10.exe.asm:125434](../../../ida/th10.exe.asm#L125434) |
| `0x0045BD21` | [ida/th10.exe.c:73950](../../../ida/th10.exe.c#L73950) | [ida/th10.exe.asm:125638](../../../ida/th10.exe.asm#L125638) |
| `0x0045BD72` | [ida/th10.exe.c:73956](../../../ida/th10.exe.c#L73956) | [ida/th10.exe.asm:125660](../../../ida/th10.exe.asm#L125660) |
| `0x0045C377` | [ida/th10.exe.c:73962](../../../ida/th10.exe.c#L73962) | [ida/th10.exe.asm:125683](../../../ida/th10.exe.asm#L125683) |
| `0x0045C544` | [ida/th10.exe.c:73988](../../../ida/th10.exe.c#L73988) | [ida/th10.exe.asm:125756](../../../ida/th10.exe.asm#L125756) |
| `0x0045C5DC` | [ida/th10.exe.c:74021](../../../ida/th10.exe.c#L74021) | [ida/th10.exe.asm:125827](../../../ida/th10.exe.asm#L125827) |
| `0x0045C651` | [ida/th10.exe.c:74047](../../../ida/th10.exe.c#L74047) | [ida/th10.exe.asm:125889](../../../ida/th10.exe.asm#L125889) |
| `0x0045C86F` | [ida/th10.exe.c:74127](../../../ida/th10.exe.c#L74127) | [ida/th10.exe.asm:126100](../../../ida/th10.exe.asm#L126100) |
| `0x0045CDAE` | [ida/th10.exe.c:74168](../../../ida/th10.exe.c#L74168) | [ida/th10.exe.asm:126228](../../../ida/th10.exe.asm#L126228) |
| `0x0045CFB8` | [ida/th10.exe.c:74255](../../../ida/th10.exe.c#L74255) | [ida/th10.exe.asm:126404](../../../ida/th10.exe.asm#L126404) |
| `0x0045D5CE` | [ida/th10.exe.c:74384](../../../ida/th10.exe.c#L74384) | [ida/th10.exe.asm:126612](../../../ida/th10.exe.asm#L126612) |
| `0x0045D5E4` | [ida/th10.exe.c:74391](../../../ida/th10.exe.c#L74391) | [ida/th10.exe.asm:126629](../../../ida/th10.exe.asm#L126629) |
| `0x0045D676` | [ida/th10.exe.c:74398](../../../ida/th10.exe.c#L74398) | [ida/th10.exe.asm:126648](../../../ida/th10.exe.asm#L126648) |
| `0x0045D701` | [ida/th10.exe.c:74408](../../../ida/th10.exe.c#L74408) | [ida/th10.exe.asm:126725](../../../ida/th10.exe.asm#L126725) |
| `0x0045D746` | [ida/th10.exe.c:74418](../../../ida/th10.exe.c#L74418) | [ida/th10.exe.asm:126771](../../../ida/th10.exe.asm#L126771) |
| `0x0045DD85` | [ida/th10.exe.c:74753](../../../ida/th10.exe.c#L74753) | [ida/th10.exe.asm:127442](../../../ida/th10.exe.asm#L127442) |
| `0x0045DE91` | [ida/th10.exe.c:74767](../../../ida/th10.exe.c#L74767) | [ida/th10.exe.asm:127506](../../../ida/th10.exe.asm#L127506) |
| `0x0045DEF8` | [ida/th10.exe.c:74780](../../../ida/th10.exe.c#L74780) | [ida/th10.exe.asm:127566](../../../ida/th10.exe.asm#L127566) |
| `0x0045E0E4` | [ida/th10.exe.c:74802](../../../ida/th10.exe.c#L74802) | [ida/th10.exe.asm:127663](../../../ida/th10.exe.asm#L127663) |
| `0x0045E3A0` | [ida/th10.exe.c:74815](../../../ida/th10.exe.c#L74815) | [ida/th10.exe.asm:127709](../../../ida/th10.exe.asm#L127709) |
| `0x0045EA31` | [ida/th10.exe.c:74821](../../../ida/th10.exe.c#L74821) | [ida/th10.exe.asm:127743](../../../ida/th10.exe.asm#L127743) |
| `0x0045EE1D` | [ida/th10.exe.c:74861](../../../ida/th10.exe.c#L74861) | [ida/th10.exe.asm:127960](../../../ida/th10.exe.asm#L127960) |
| `0x0045F259` | [ida/th10.exe.c:75072](../../../ida/th10.exe.c#L75072) | [ida/th10.exe.asm:128419](../../../ida/th10.exe.asm#L128419) |
| `0x0045F3A4` | [ida/th10.exe.c:75132](../../../ida/th10.exe.c#L75132) | [ida/th10.exe.asm:128563](../../../ida/th10.exe.asm#L128563) |
| `0x0045F3C0` | [ida/th10.exe.c:75143](../../../ida/th10.exe.c#L75143) | [ida/th10.exe.asm:128581](../../../ida/th10.exe.asm#L128581) |
| `0x0045FDA6` | [ida/th10.exe.c:75154](../../../ida/th10.exe.c#L75154) | [ida/th10.exe.asm:128629](../../../ida/th10.exe.asm#L128629) |
| `0x0045FE7E` | [ida/th10.exe.c:75160](../../../ida/th10.exe.c#L75160) | [ida/th10.exe.asm:128648](../../../ida/th10.exe.asm#L128648) |
| `0x004601A1` | [ida/th10.exe.c:75167](../../../ida/th10.exe.c#L75167) | [ida/th10.exe.asm:128661](../../../ida/th10.exe.asm#L128661) |
| `0x004601E8` | [ida/th10.exe.c:75179](../../../ida/th10.exe.c#L75179) | [ida/th10.exe.asm:128705](../../../ida/th10.exe.asm#L128705) |
| `0x0046041E` | [ida/th10.exe.c:75282](../../../ida/th10.exe.c#L75282) | [ida/th10.exe.asm:128965](../../../ida/th10.exe.asm#L128965) |
| `0x00460872` | [ida/th10.exe.c:75351](../../../ida/th10.exe.c#L75351) | [ida/th10.exe.asm:129134](../../../ida/th10.exe.asm#L129134) |
| `0x0046095A` | [ida/th10.exe.c:75412](../../../ida/th10.exe.c#L75412) | [ida/th10.exe.asm:129253](../../../ida/th10.exe.asm#L129253) |
| `0x00460B90` | [ida/th10.exe.c:75574](../../../ida/th10.exe.c#L75574) | [ida/th10.exe.asm:129507](../../../ida/th10.exe.asm#L129507) |
| `0x00461184` | [ida/th10.exe.c:75624](../../../ida/th10.exe.c#L75624) | [ida/th10.exe.asm:129626](../../../ida/th10.exe.asm#L129626) |
| `0x00461361` | [ida/th10.exe.c:75774](../../../ida/th10.exe.c#L75774) | [ida/th10.exe.asm:129854](../../../ida/th10.exe.asm#L129854) |
| `0x00461841` | [ida/th10.exe.c:75808](../../../ida/th10.exe.c#L75808) | [ida/th10.exe.asm:129946](../../../ida/th10.exe.asm#L129946) |
| `0x00461AF9` | [ida/th10.exe.c:75972](../../../ida/th10.exe.c#L75972) | [ida/th10.exe.asm:130279](../../../ida/th10.exe.asm#L130279) |
| `0x00461F31` | [ida/th10.exe.c:76181](../../../ida/th10.exe.c#L76181) | [ida/th10.exe.asm:130717](../../../ida/th10.exe.asm#L130717) |
| `0x00462327` | [ida/th10.exe.c:76319](../../../ida/th10.exe.c#L76319) | [ida/th10.exe.asm:130963](../../../ida/th10.exe.asm#L130963) |
| `0x00462371` | [ida/th10.exe.c:76330](../../../ida/th10.exe.c#L76330) | [ida/th10.exe.asm:131001](../../../ida/th10.exe.asm#L131001) |
| `0x0046238E` | [ida/th10.exe.c:76339](../../../ida/th10.exe.c#L76339) | [ida/th10.exe.asm:131018](../../../ida/th10.exe.asm#L131018) |
| `0x004623C2` | [ida/th10.exe.c:76348](../../../ida/th10.exe.c#L76348) | [ida/th10.exe.asm:131049](../../../ida/th10.exe.asm#L131049) |
| `0x004623DE` | [ida/th10.exe.c:76357](../../../ida/th10.exe.c#L76357) | [ida/th10.exe.asm:131072](../../../ida/th10.exe.asm#L131072) |
| `0x00462401` | [ida/th10.exe.c:76365](../../../ida/th10.exe.c#L76365) | [ida/th10.exe.asm:131089](../../../ida/th10.exe.asm#L131089) |
| `0x0046241D` | [ida/th10.exe.c:76374](../../../ida/th10.exe.c#L76374) | [ida/th10.exe.asm:131112](../../../ida/th10.exe.asm#L131112) |
| `0x00462468` | [ida/th10.exe.c:76382](../../../ida/th10.exe.c#L76382) | [ida/th10.exe.asm:131123](../../../ida/th10.exe.asm#L131123) |
| `0x004624AB` | [ida/th10.exe.c:76393](../../../ida/th10.exe.c#L76393) | [ida/th10.exe.asm:131165](../../../ida/th10.exe.asm#L131165) |
| `0x00462525` | [ida/th10.exe.c:76402](../../../ida/th10.exe.c#L76402) | [ida/th10.exe.asm:131185](../../../ida/th10.exe.asm#L131185) |
| `0x00462BED` | [ida/th10.exe.c:76411](../../../ida/th10.exe.c#L76411) | [ida/th10.exe.asm:131324](../../../ida/th10.exe.asm#L131324) |
| `0x00462BF1` | [ida/th10.exe.c:76417](../../../ida/th10.exe.c#L76417) | [ida/th10.exe.asm:131333](../../../ida/th10.exe.asm#L131333) |
| `0x00462BFC` | [ida/th10.exe.c:76428](../../../ida/th10.exe.c#L76428) | [ida/th10.exe.asm:131343](../../../ida/th10.exe.asm#L131343) |
| `0x00462C01` | [ida/th10.exe.c:76434](../../../ida/th10.exe.c#L76434) | [ida/th10.exe.asm:131352](../../../ida/th10.exe.asm#L131352) |
| `0x00462C12` | [ida/th10.exe.c:76447](../../../ida/th10.exe.c#L76447) | [ida/th10.exe.asm:131364](../../../ida/th10.exe.asm#L131364) |
| `0x00462C5A` | [ida/th10.exe.c:76471](../../../ida/th10.exe.c#L76471) | [ida/th10.exe.asm:131408](../../../ida/th10.exe.asm#L131408) |
| `0x00462CAC` | [ida/th10.exe.c:76505](../../../ida/th10.exe.c#L76505) | [ida/th10.exe.asm:131459](../../../ida/th10.exe.asm#L131459) |
| `0x00462D00` | [ida/th10.exe.c:76517](../../../ida/th10.exe.c#L76517) | [ida/th10.exe.asm:131493](../../../ida/th10.exe.asm#L131493) |
| `0x00462D0B` | [ida/th10.exe.c:76525](../../../ida/th10.exe.c#L76525) | [ida/th10.exe.asm:131502](../../../ida/th10.exe.asm#L131502) |
| `0x00462D24` | [ida/th10.exe.c:76534](../../../ida/th10.exe.c#L76534) | [ida/th10.exe.asm:131521](../../../ida/th10.exe.asm#L131521) |
| `0x00462D3C` | [ida/th10.exe.c:76543](../../../ida/th10.exe.c#L76543) | [ida/th10.exe.asm:131539](../../../ida/th10.exe.asm#L131539) |
| `0x00462D77` | [ida/th10.exe.c:76551](../../../ida/th10.exe.c#L76551) | [ida/th10.exe.asm:131564](../../../ida/th10.exe.asm#L131564) |
| `0x00462D82` | [ida/th10.exe.c:76559](../../../ida/th10.exe.c#L76559) | [ida/th10.exe.asm:131573](../../../ida/th10.exe.asm#L131573) |
| `0x00462DBD` | [ida/th10.exe.c:76568](../../../ida/th10.exe.c#L76568) | [ida/th10.exe.asm:131597](../../../ida/th10.exe.asm#L131597) |
| `0x00462DD9` | [ida/th10.exe.c:76577](../../../ida/th10.exe.c#L76577) | [ida/th10.exe.asm:131620](../../../ida/th10.exe.asm#L131620) |
| `0x00462DF5` | [ida/th10.exe.c:76586](../../../ida/th10.exe.c#L76586) | [ida/th10.exe.asm:131643](../../../ida/th10.exe.asm#L131643) |
| `0x0046316C` | [ida/th10.exe.c:76595](../../../ida/th10.exe.c#L76595) | [ida/th10.exe.asm:131676](../../../ida/th10.exe.asm#L131676) |
| `0x0046508C` | [ida/th10.exe.c:76601](../../../ida/th10.exe.c#L76601) | [ida/th10.exe.asm:132100](../../../ida/th10.exe.asm#L132100) |
