#!/bin/bash
# Host-compiler test suite: builds and runs every reconstruction test with
# g++. The recovered headers keep retail calling conventions; defining them
# away lets the same sources parse on a host compiler.
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
CXX="${CXX:-g++}"
CXXFLAGS=(-std=c++17 -Wall -Wextra -Werror "-I$ROOT/include" \
    -D__fastcall= -D__stdcall= -D__cdecl= -D__thiscall= '-D__declspec(x)=')
TEST_BUILD="$ROOT/build/tests"
mkdir -p "$TEST_BUILD"

python3 "$ROOT/tests/progress_evidence_test.py"
python3 "$ROOT/tools/coverage_report.py" --check
python3 "$ROOT/tools/function_registry.py" --check
python3 "$ROOT/tools/standalone_readiness.py" --check

# Partition arguments into FLAGS (before `--`) and SOURCES (after). When no
# separator is present, every argument is a source file.
split_args() {
    FLAGS=(); SOURCES=(); local sep=0 arg
    for arg in "$@"; do
        if (( sep == 0 )) && [[ "$arg" == "--" ]]; then sep=1; continue; fi
        if (( sep == 0 )); then FLAGS+=("$arg"); else SOURCES+=("$arg"); fi
    done
    if (( sep == 0 )); then SOURCES=("${FLAGS[@]}"); FLAGS=(); fi
}

# Build and run one host test binary.
run_test() {
    local name="$1"; shift
    split_args "$@"
    "$CXX" "${CXXFLAGS[@]}" "${FLAGS[@]}" "${SOURCES[@]}" \
        -o "$TEST_BUILD/$name"
    "$TEST_BUILD/$name"
}

# The 32-bit suites need real i386 calling conventions (no -D__thiscall=),
# so they bypass the shared flags with their own g++ invocation.
run_test_m32() {
    local name="$1"; shift
    split_args "$@"
    g++ -m32 -std=c++17 -Wall -Wextra -Werror \
        -D__stdcall= -D__fastcall= -D__cdecl= '-D__declspec(x)=' \
        -I"$ROOT/include" "${FLAGS[@]}" "${SOURCES[@]}" \
        -o "$TEST_BUILD/$name"
    "$TEST_BUILD/$name"
}


run_test title_main_menu_test \
    "$ROOT/src/game/title_main_menu.cpp" \
    "$ROOT/src/runtime/missing_edge.cpp" \
    "$ROOT/tests/title_main_menu_test.cpp"

run_test title_options_menu_test \
    "$ROOT/src/game/title_options_menu.cpp" \
    "$ROOT/tests/title_options_menu_test.cpp"

run_test anm_file_test \
    "$ROOT/src/render/anm_file.cpp" \
    "$ROOT/src/runtime/missing_edge.cpp" \
    "$ROOT/tests/anm_file_test.cpp"

run_test anm_sprite_quad_test \
    "$ROOT/src/render/anm_sprite_quad.cpp" \
    "$ROOT/tests/anm_sprite_quad_test.cpp"

run_test anm_vm_interrupt_test \
    "$ROOT/src/math/interpolators.cpp" \
    "$ROOT/src/script/anm_vm_tick.cpp" \
    "$ROOT/tests/anm_vm_interrupt_test.cpp"

run_test archive_test \
    "$ROOT/src/archive/crypt.cpp" \
    "$ROOT/src/archive/dat.cpp" \
    "$ROOT/src/archive/lzss.cpp" \
    "$ROOT/src/platform/memory_file.cpp" \
    "$ROOT/src/platform/path.cpp" \
    "$ROOT/src/render/d3d_resource_manager.cpp" \
    "$ROOT/src/render/device_reset.cpp" \
    "$ROOT/src/render/game_render_targets.cpp" \
    "$ROOT/src/util/heap.cpp" \
    "$ROOT/src/util/runtime_pool.cpp" \
    "$ROOT/src/runtime/missing_edge.cpp" \
    "$ROOT/tests/archive_test.cpp"

run_test scheduler_test \
    "$ROOT/src/game/scheduler.cpp" \
    "$ROOT/src/runtime/missing_edge.cpp" \
    "$ROOT/tests/scheduler_test.cpp"

run_test game_runtime_test -Wno-unused-parameter -- \
    "$ROOT/src/math/timer.cpp" \
    "$ROOT/src/math/vector.cpp" \
    "$ROOT/src/math/rng.cpp" \
    "$ROOT/src/math/angle.cpp" \
    "$ROOT/src/math/easing.cpp" \
    "$ROOT/src/math/random_vector.cpp" \
    "$ROOT/src/game/menu.cpp" \
    "$ROOT/src/game/progress.cpp" \
    "$ROOT/src/game/score.cpp" \
    "$ROOT/src/game/score_runtime_ui_update.cpp" \
    "$ROOT/src/runtime/missing_edge.cpp" \
    "$ROOT/src/game/scheduler.cpp" \
    "$ROOT/src/game/stage_text.cpp" \
    "$ROOT/src/render/animation_manager.cpp" \
    "$ROOT/src/render/anm_entry_load.cpp" \
    "$ROOT/tests/game_runtime_test.cpp"

run_test score_runtime_test \
    "$ROOT/src/game/score.cpp" \
    "$ROOT/src/game/score_runtime_ui_update.cpp" \
    "$ROOT/src/runtime/missing_edge.cpp" \
    "$ROOT/tests/score_runtime_test.cpp"

run_test d3d_resource_manager_test \
    "$ROOT/src/render/d3d_resource_manager.cpp" \
    "$ROOT/src/runtime/missing_edge.cpp" \
    "$ROOT/tests/d3d_resource_manager_test.cpp"

run_test file_resource_test \
    "$ROOT/src/platform/file.cpp" \
    "$ROOT/src/platform/memory_file.cpp" \
    "$ROOT/src/platform/resource_file.cpp" \
    "$ROOT/src/archive/resource_manager.cpp" \
    "$ROOT/src/platform/path.cpp" \
    "$ROOT/src/runtime/missing_edge.cpp" \
    "$ROOT/tests/file_resource_test.cpp"

run_test process_test \
    "$ROOT/src/platform/process.cpp" \
    "$ROOT/src/platform/text_log.cpp" \
    "$ROOT/src/platform/win32_timer.cpp" \
    "$ROOT/src/runtime/missing_edge.cpp" \
    "$ROOT/tests/process_test.cpp"

run_test recovery_leaves_test \
    "$ROOT/src/game/recovery_leaves.cpp" \
    "$ROOT/src/runtime/missing_edge.cpp" \
    "$ROOT/tests/recovery_leaves_test.cpp"

run_test ecl_vm_test \
    "$ROOT/src/script/ecl_vm.cpp" \
    "$ROOT/src/script/ecl_helpers.cpp" \
    "$ROOT/src/game/recovery_leaves.cpp" \
    "$ROOT/src/runtime/missing_edge.cpp" \
    "$ROOT/tests/ecl_vm_test.cpp"
python3 "$ROOT/tests/ecl_unsupported_test.py" "$TEST_BUILD/ecl_vm_test"

# The four ECL core edges (0x0044DF70 / 0x004500D0 / 0x00450160 / 0x00450070),
# bound into EclVm_TickCore: call/ret cycle, async spawn, find-by-id, float
# destination resolution.
run_test ecl_core_edges_test \
    "$ROOT/src/script/ecl_core_interpreter.cpp" \
    "$ROOT/src/script/ecl_vm.cpp" \
    "$ROOT/src/script/ecl_helpers.cpp" \
    "$ROOT/src/game/recovery_leaves.cpp" \
    "$ROOT/src/math/angle.cpp" \
    "$ROOT/src/runtime/missing_edge.cpp" \
    "$ROOT/tests/ecl_core_edges_test.cpp"

run_test entity_vm_test \
    "$ROOT/src/script/entity_vm.cpp" \
    "$ROOT/src/runtime/missing_edge.cpp" \
    "$ROOT/tests/entity_vm_test.cpp"

run_test ecl_helpers_test \
    "$ROOT/src/script/ecl_helpers.cpp" \
    "$ROOT/src/runtime/missing_edge.cpp" \
    "$ROOT/tests/ecl_helpers_test.cpp"

run_test prng_test \
    "$ROOT/src/script/prng.cpp" \
    "$ROOT/src/runtime/missing_edge.cpp" \
    "$ROOT/tests/prng_test.cpp"

run_test animation_slot_test \
    "$ROOT/src/render/animation_slot.cpp" \
    "$ROOT/src/runtime/missing_edge.cpp" \
    "$ROOT/tests/animation_slot_test.cpp"

# ANM archive-entry loader (0x00447470) and shared sprite arithmetic.
run_test anm_entry_load_test \
    "$ROOT/src/render/anm_entry_load.cpp" \
    "$ROOT/src/runtime/missing_edge.cpp" \
    "$ROOT/tests/anm_entry_load_test.cpp"

run_test anm_distance_color_test \
    "$ROOT/src/render/anm_distance_color.cpp" \
    "$ROOT/tests/anm_distance_color_test.cpp"

# Per-slot game-state snapshot capture/restore (0x0042A450).
run_test slot_snapshot_test \
    "$ROOT/src/game/slot_snapshot.cpp" \
    "$ROOT/src/runtime/missing_edge.cpp" \
    "$ROOT/tests/slot_snapshot_test.cpp"

# Four-block parameter interpolator (0x004049A0).
run_test param_block_interp_test \
    "$ROOT/src/math/param_block_interp.cpp" \
    "$ROOT/src/math/math_utils.cpp" \
    "$ROOT/src/math/easing.cpp" \
    "$ROOT/src/runtime/missing_edge.cpp" \
    "$ROOT/tests/param_block_interp_test.cpp"

# Rectangular entity-pool region sweep (0x00408210).
run_test entity_region_sweep_test \
    "$ROOT/src/game/entity_region_sweep.cpp" \
    "$ROOT/src/runtime/missing_edge.cpp" \
    "$ROOT/tests/entity_region_sweep_test.cpp"

# Gameplay render/transition pass (0x00402850).
run_test gameplay_render_pass_test \
    "$ROOT/src/game/gameplay_render_pass.cpp" \
    "$ROOT/src/runtime/missing_edge.cpp" \
    "$ROOT/tests/gameplay_render_pass_test.cpp"

# Message host construction (0x0040D280).
run_test message_host_init_test \
    "$ROOT/src/game/message_host_init.cpp" \
    "$ROOT/src/math/math_utils.cpp" \
    "$ROOT/src/runtime/missing_edge.cpp" \
    "$ROOT/tests/message_host_init_test.cpp"

# Per-stage slot construction (0x00415B00).
run_test stage_slot_state_test \
    "$ROOT/src/game/stage_slot_state.cpp" \
    "$ROOT/src/game/entity_region_sweep.cpp" \
    "$ROOT/src/math/math_utils.cpp" \
    "$ROOT/src/runtime/missing_edge.cpp" \
    "$ROOT/tests/stage_slot_state_test.cpp"

run_test entity_movement_slot_test \
    "$ROOT/src/game/entity_movement_slot.cpp" \
    "$ROOT/src/runtime/missing_edge.cpp" \
    "$ROOT/tests/entity_movement_slot_test.cpp"

run_test entity_color_slot_test \
    "$ROOT/src/game/entity_color_slot.cpp" \
    "$ROOT/src/runtime/missing_edge.cpp" \
    "$ROOT/tests/entity_color_slot_test.cpp"

run_test linked_pool_release_test \
    "$ROOT/src/game/linked_pool_release.cpp" \
    "$ROOT/src/runtime/missing_edge.cpp" \
    "$ROOT/tests/linked_pool_release_test.cpp"

run_test animation_resource_lazy_fetch_test \
    "$ROOT/src/game/animation_resource_lazy_fetch.cpp" \
    "$ROOT/src/runtime/missing_edge.cpp" \
    "$ROOT/tests/animation_resource_lazy_fetch_test.cpp"

run_test vector3_cross_test \
    "$ROOT/src/math/vector3_cross.cpp" \
    "$ROOT/src/runtime/missing_edge.cpp" \
    "$ROOT/tests/vector3_cross_test.cpp"

run_test archive_cursor_test \
    "$ROOT/src/game/archive_cursor.cpp" \
    "$ROOT/src/runtime/missing_edge.cpp" \
    "$ROOT/tests/archive_cursor_test.cpp"

run_test archive_cursor_read_test \
    "$ROOT/src/game/archive_cursor_read.cpp" \
    "$ROOT/src/runtime/missing_edge.cpp" \
    "$ROOT/tests/archive_cursor_read_test.cpp"

run_test recovery_batch3_test \
    "$ROOT/src/game/asset_buffer.cpp" \
    "$ROOT/src/render/transparent_pixel_fill.cpp" \
    "$ROOT/src/runtime/missing_edge.cpp" \
    "$ROOT/tests/recovery_batch3_test.cpp"


run_test recovery_batch4_test \
    "$ROOT/src/game/particle_seed.cpp" \
    "$ROOT/src/game/stage_focus_fade.cpp" \
    "$ROOT/src/game/stage_tip_manager.cpp" \
    "$ROOT/src/runtime/missing_edge.cpp" \
    "$ROOT/tests/recovery_batch4_test.cpp"


run_test score_popup_test \
    "$ROOT/src/game/score_popup.cpp" \
    "$ROOT/src/runtime/missing_edge.cpp" \
    "$ROOT/tests/score_popup_test.cpp"


run_test large_easy_functions_test \
    "$ROOT/src/game/score_cleanup.cpp" \
    "$ROOT/src/render/image_alpha_transform.cpp" \
    "$ROOT/src/render/transparent_pixel_fill.cpp" \
    "$ROOT/src/render/transparent_pixel_fill_locked.cpp" \
    "$ROOT/src/runtime/missing_edge.cpp" \
    "$ROOT/tests/large_easy_functions_test.cpp"

# The 32-bit suites need the i686 glibc headers; skip them (with a notice)
# on hosts without gnu/stubs-32.h instead of failing the whole run.
if [[ -f /usr/include/gnu/stubs-32.h ]]; then
    # GameState stores 32-bit retail pointers in its ABI fields, so exercise
    # its device-failure state transitions in a 32-bit host binary.
run_test_m32 game_state_test \
    "$ROOT/src/game/game_state.cpp" \
    "$ROOT/src/game/scheduler.cpp" \
    "$ROOT/tests/game_state_test.cpp"

    # The bullet manager is laid out with 32-bit retail pointers, so exercise
    # the create / load-scripts / release lifecycle on a 32-bit host binary.
run_test_m32 bullet_manager_test -Wno-unused-parameter -- \
    "$ROOT/src/game/bullet.cpp" \
    "$ROOT/src/game/trajectory_evaluate.cpp" \
    "$ROOT/src/game/scheduler.cpp" \
    "$ROOT/src/render/animation_manager.cpp" \
    "$ROOT/src/render/anm_entry_load.cpp" \
    "$ROOT/tests/bullet_manager_test.cpp"

    # Player_AdjustPower lives in the retail-layout player translation unit.
    run_test_m32 player_adjust_power_test -ffunction-sections -fdata-sections \
        -Wl,--gc-sections -- \
        "$ROOT/src/game/player.cpp" \
        "$ROOT/tests/player_adjust_power_test.cpp"
else
    echo "NOTE: skipping 32-bit suites (gnu/stubs-32.h not installed)"
fi

run_test game_thread_queue_test \
    "$ROOT/src/game/game_thread_queue.cpp" \
    "$ROOT/src/runtime/missing_edge.cpp" \
    "$ROOT/tests/game_thread_queue_test.cpp"

run_test player_scheduler_test \
    "$ROOT/src/game/player_scheduler.cpp" \
    "$ROOT/src/runtime/missing_edge.cpp" \
    "$ROOT/tests/player_scheduler_test.cpp"

run_test recovery_batch_test \
    "$ROOT/src/render/quad_vertex_append.cpp" \
    "$ROOT/src/game/archive_cursor_open.cpp" \
    "$ROOT/src/game/score_timer_leaves.cpp" \
    "$ROOT/src/game/game_config_defaults.cpp" \
    "$ROOT/src/game/stage_focus_fade.cpp" \
    "$ROOT/src/game/stage_tip_manager.cpp" \
    "$ROOT/src/platform/sound_worker.cpp" \
    "$ROOT/src/runtime/missing_edge.cpp" \
    "$ROOT/tests/recovery_batch_test.cpp"

run_test recovery_batch2_test \
    "$ROOT/src/game/boss_gauge.cpp" \
    "$ROOT/src/game/bullet_anim_release.cpp" \
    "$ROOT/src/game/effect_indicator_slots.cpp" \
    "$ROOT/src/game/effect_manager_destroy.cpp" \
    "$ROOT/src/game/enemy_drop_sweep.cpp" \
    "$ROOT/src/game/faith_gauge.cpp" \
    "$ROOT/src/game/frame_counter.cpp" \
    "$ROOT/src/game/game_ui_create.cpp" \
    "$ROOT/src/game/linked_pool_append.cpp" \
    "$ROOT/src/game/object_factories.cpp" \
    "$ROOT/src/game/player_reset.cpp" \
    "$ROOT/src/game/pool_constructors.cpp" \
    "$ROOT/src/game/progress_worker.cpp" \
    "$ROOT/src/game/rank_level.cpp" \
    "$ROOT/src/game/score_file.cpp" \
    "$ROOT/src/game/score_queue.cpp" \
    "$ROOT/src/game/score_view_ctor.cpp" \
    "$ROOT/src/game/slot_lock_leaves.cpp" \
    "$ROOT/src/game/stats_task.cpp" \
    "$ROOT/src/game/task_registration.cpp" \
    "$ROOT/src/game/ui_final_runtime.cpp" \
    "$ROOT/src/render/animation_manager.cpp" \
    "$ROOT/src/render/anm_entry_load.cpp" \
    "$ROOT/src/game/game_state_overlay_draw.cpp" \
    "$ROOT/src/game/floating_text_draw.cpp" \
    "$ROOT/src/render/recovered_render_leaves.cpp" \
    "$ROOT/src/render/anm_vm_draw_dispatch.cpp" \
    "$ROOT/src/render/quad_build_anchored.cpp" \
    "$ROOT/src/render/quad_vertex_append.cpp" \
    "$ROOT/src/render/anm_batch_flush.cpp" \
    "$ROOT/src/game/thread_spawn.cpp" \
    "$ROOT/src/game/version_list.cpp" \
    "$ROOT/src/math/vector2_polar.cpp" \
    "$ROOT/src/platform/gdi_font_cache.cpp" \
    "$ROOT/src/platform/joystick_probe.cpp" \
    "$ROOT/src/platform/midi_sequencer.cpp" \
    "$ROOT/src/platform/midi_worker_stop.cpp" \
    "$ROOT/src/platform/sound_dummy.cpp" \
    "$ROOT/src/platform/sound_fade.cpp" \
    "$ROOT/src/platform/sound_leaves.cpp" \
    "$ROOT/src/platform/sound_stream_start.cpp" \
    "$ROOT/src/platform/worker_start.cpp" \
    "$ROOT/src/render/anm_handle_release.cpp" \
    "$ROOT/src/render/anm_propagate.cpp" \
    "$ROOT/src/render/camera_apply.cpp" \
    "$ROOT/src/render/camera_defaults.cpp" \
    "$ROOT/src/render/edge_strips.cpp" \
    "$ROOT/src/render/fog_disable.cpp" \
    "$ROOT/src/render/render_state_sync.cpp" \
    "$ROOT/src/game/game_config_defaults.cpp" \
    "$ROOT/src/game/scheduler.cpp" \
    "$ROOT/src/game/entity.cpp" \
    "$ROOT/src/runtime/missing_edge.cpp" \
    "$ROOT/tests/recovery_batch2_test.cpp"

run_test manager_factories_test -Wno-unused-parameter -- \
    "$ROOT/src/util/legacy_string_funclets.cpp" \
    "$ROOT/src/platform/sound_float_forward.cpp" \
    "$ROOT/src/game/player_motion.cpp" \
    "$ROOT/src/game/weather_pool.cpp" \
    "$ROOT/src/script/ecl_vm_children.cpp" \
    "$ROOT/src/game/manager_factories.cpp" \
        "$ROOT/src/game/gameplay_final_runtime.cpp" \
"$ROOT/src/game/pool_constructors.cpp" \
    "$ROOT/src/game/floating_text_draw.cpp" \
    "$ROOT/src/render/recovered_render_leaves.cpp" \
    "$ROOT/src/render/anm_vm_draw_dispatch.cpp" \
    "$ROOT/src/render/quad_build_anchored.cpp" \
    "$ROOT/src/render/quad_vertex_append.cpp" \
    "$ROOT/src/render/anm_batch_flush.cpp" \
    "$ROOT/src/game/message_manager_init.cpp" \
    "$ROOT/src/game/bullet_manager.cpp" \
    "$ROOT/src/math/angle.cpp" \
    "$ROOT/src/game/enemy_lifecycle.cpp" \
    "$ROOT/src/game/boss_overlays.cpp" \
    "$ROOT/src/render/render_stage_select.cpp" \
    "$ROOT/src/game/stage_background.cpp" \
    "$ROOT/src/render/anm_texture_upload.cpp" \
    "$ROOT/src/platform/midi_worker.cpp" \
    "$ROOT/src/game/scheduler.cpp" \
    "$ROOT/src/game/entity.cpp" \
    "$ROOT/src/runtime/missing_edge.cpp" \
    "$ROOT/tests/manager_factories_test.cpp"

run_test bullet_systems_test -Wno-unused-parameter -- \
    "$ROOT/src/game/enemy_grid_scan.cpp" \
    "$ROOT/src/game/manager_factories.cpp" \
    "$ROOT/src/game/pool_constructors.cpp" \
    "$ROOT/src/game/floating_text_draw.cpp" \
    "$ROOT/src/render/recovered_render_leaves.cpp" \
    "$ROOT/src/render/anm_vm_draw_dispatch.cpp" \
    "$ROOT/src/render/quad_build_anchored.cpp" \
    "$ROOT/src/render/quad_vertex_append.cpp" \
    "$ROOT/src/render/anm_batch_flush.cpp" \
    "$ROOT/src/game/enemy_lifecycle.cpp" \
    "$ROOT/src/game/main_menu_dispatch.cpp" \
    "$ROOT/src/game/result_menu_draw.cpp" \
    "$ROOT/src/game/pause_result_open.cpp" \
    "$ROOT/src/game/game_thread_queue.cpp" \
    "$ROOT/src/game/key_config.cpp" \
    "$ROOT/src/render/anm_pending_service.cpp" \
    "$ROOT/src/game/ascii_overlay_callbacks.cpp" \
    "$ROOT/src/game/bullet_manager.cpp" \
    "$ROOT/src/math/angle.cpp" \
    "$ROOT/src/game/player_motion.cpp" \
    "$ROOT/src/game/result_choice_menu.cpp" \
    "$ROOT/src/game/gameplay_final_runtime.cpp" \
    "$ROOT/src/game/replay_progress.cpp" \
    "$ROOT/src/platform/sound_event_queue.cpp" \
    "$ROOT/src/render/rect_fan_draw.cpp" \
    "$ROOT/src/app/fps_counter.cpp" \
    "$ROOT/src/game/music_room.cpp" \
    "$ROOT/src/platform/sound_stream_thread.cpp" \
    "$ROOT/src/script/script_text_reader.cpp" \
    "$ROOT/src/game/scheduler.cpp" \
    "$ROOT/src/game/entity.cpp" \
    "$ROOT/src/runtime/missing_edge.cpp" \
    "$ROOT/tests/bullet_systems_test.cpp"

run_test bullet_pool_update_test -Wno-unused-parameter -- \
    "$ROOT/src/game/bullet_manager.cpp" \
    "$ROOT/tests/bullet_pool_update_test.cpp"

run_test enemy_motion_steps_test -Wno-unused-parameter -- \
    "$ROOT/src/app/fps_counter.cpp" \
    "$ROOT/src/game/ending_screen.cpp" \
    "$ROOT/src/render/default_viewport.cpp" \
    "$ROOT/src/game/ascii_overlay_callbacks.cpp" \
    "$ROOT/src/game/bullet_manager.cpp" \
    "$ROOT/src/math/angle.cpp" \
    "$ROOT/src/game/manager_factories.cpp" \
    "$ROOT/src/game/gameplay_final_runtime.cpp" \
    "$ROOT/src/game/pool_constructors.cpp" \
    "$ROOT/src/game/floating_text_draw.cpp" \
    "$ROOT/src/render/recovered_render_leaves.cpp" \
    "$ROOT/src/render/anm_vm_draw_dispatch.cpp" \
    "$ROOT/src/render/quad_build_anchored.cpp" \
    "$ROOT/src/render/quad_vertex_append.cpp" \
    "$ROOT/src/render/anm_batch_flush.cpp" \
    "$ROOT/src/game/title_assets.cpp" \
    "$ROOT/src/platform/midi_worker.cpp" \
    "$ROOT/src/platform/sound_effect_buffers.cpp" \
    "$ROOT/src/script/stage_ecl_load.cpp" \
    "$ROOT/src/game/enemy_motion_steps.cpp" \
    "$ROOT/src/game/enemy_lifecycle.cpp" \
    "$ROOT/src/game/pause_menu_reset.cpp" \
    "$ROOT/src/game/item_field_contact.cpp" \
    "$ROOT/src/render/anm_surface_restore.cpp" \
    "$ROOT/src/game/scheduler.cpp" \
    "$ROOT/src/game/entity.cpp" \
    "$ROOT/src/runtime/missing_edge.cpp" \
    "$ROOT/tests/enemy_motion_steps_test.cpp"

run_test game_systems_test -Wno-unused-parameter -- \
    "$ROOT/src/platform/joystick_property.cpp" \
    "$ROOT/src/game/enemy_lifecycle.cpp" \
    "$ROOT/src/script/ecl_name_table.cpp" \
    "$ROOT/src/game/spell_timer.cpp" \
    "$ROOT/src/game/bullet_manager.cpp" \
    "$ROOT/src/math/angle.cpp" \
    "$ROOT/src/game/manager_factories.cpp" \
    "$ROOT/src/game/gameplay_final_runtime.cpp" \
    "$ROOT/src/game/pool_constructors.cpp" \
    "$ROOT/src/game/floating_text_draw.cpp" \
    "$ROOT/src/render/recovered_render_leaves.cpp" \
    "$ROOT/src/render/anm_vm_draw_dispatch.cpp" \
    "$ROOT/src/render/quad_build_anchored.cpp" \
    "$ROOT/src/render/quad_vertex_append.cpp" \
    "$ROOT/src/render/anm_batch_flush.cpp" \
    "$ROOT/src/render/anm_clip_quad.cpp" \
    "$ROOT/src/game/score_tasks.cpp" \
    "$ROOT/src/game/replay_progress.cpp" \
    "$ROOT/src/game/name_entry.cpp" \
    "$ROOT/src/game/result_screen_effects.cpp" \
    "$ROOT/src/platform/gdi_surface.cpp" \
    "$ROOT/src/game/enemy_motion_steps.cpp" \
    "$ROOT/src/render/anm_blend_state.cpp" \
    "$ROOT/src/render/texture_stage_reset.cpp" \
    "$ROOT/src/game/effect_accel.cpp" \
    "$ROOT/src/game/pause_result_open.cpp" \
    "$ROOT/src/game/stage_background.cpp" \
    "$ROOT/src/game/spell_card_end.cpp" \
    "$ROOT/src/game/scheduler.cpp" \
    "$ROOT/src/game/entity.cpp" \
    "$ROOT/src/runtime/missing_edge.cpp" \
    "$ROOT/tests/game_systems_test.cpp"

run_test spell_and_input_test -Wno-unused-parameter -- \
    "$ROOT/src/render/anm_script_table_sweep.cpp" \
    "$ROOT/src/game/enemy_motion_steps.cpp" \
    "$ROOT/src/game/score_tasks.cpp" \
    "$ROOT/src/game/spell_card_dispatch.cpp" \
    "$ROOT/src/platform/font_surface_blend.cpp" \
    "$ROOT/src/platform/joystick_poll.cpp" \
    "$ROOT/src/runtime/missing_edge.cpp" \
    "$ROOT/tests/spell_and_input_test.cpp"

run_test game_mode_transitions_test -Wno-unused-parameter -- \
    "$ROOT/src/app/version_marker.cpp" \
    "$ROOT/src/game/game_mode_switch.cpp" \
    "$ROOT/src/game/stage_controller_tick.cpp" \
    "$ROOT/src/runtime/missing_edge.cpp" \
    "$ROOT/tests/game_mode_transitions_test.cpp"

run_test spell_timeout_test -Wno-unused-parameter -- \
    "$ROOT/src/math/oriented_rect.cpp" \
    "$ROOT/src/game/trigger_region.cpp" \
    "$ROOT/src/render/special_quad.cpp" \
    "$ROOT/src/game/spell_timeout.cpp" \
    "$ROOT/src/runtime/missing_edge.cpp" \
    "$ROOT/tests/spell_timeout_test.cpp"

run_test trigger_activation_test -Wno-unused-parameter -- \
    "$ROOT/src/game/trigger_activation.cpp" \
    "$ROOT/src/game/projectile_bounce.cpp" \
    "$ROOT/src/runtime/missing_edge.cpp" \
    "$ROOT/tests/trigger_activation_test.cpp"

run_test font_texture_draw_test -Wno-unused-parameter -- \
    "$ROOT/src/platform/font_texture_draw.cpp" \
    "$ROOT/src/render/special_quad.cpp" \
    "$ROOT/src/runtime/missing_edge.cpp" \
    "$ROOT/tests/font_texture_draw_test.cpp"

run_test font_cache_init_test -Wno-unused-parameter -- \
    "$ROOT/src/platform/font_cache_init.cpp" \
    "$ROOT/src/render/queued_anm_cleanup.cpp" \
    "$ROOT/src/runtime/missing_edge.cpp" \
    "$ROOT/tests/font_cache_init_test.cpp"

run_test sprite_test_overlay_test -Wno-unused-parameter -- \
    "$ROOT/src/game/sprite_test_overlay.cpp" \
    "$ROOT/src/render/quad_build_anchored.cpp" \
    "$ROOT/src/runtime/missing_edge.cpp" \
    "$ROOT/tests/sprite_test_overlay_test.cpp"

run_test score_hud_update_test -Wno-unused-parameter -- \
    "$ROOT/src/game/score_hud_update.cpp" \
    "$ROOT/src/runtime/missing_edge.cpp" \
    "$ROOT/tests/score_hud_update_test.cpp"

run_test projection_quads_test -Wno-unused-parameter -- \
    "$ROOT/src/render/projection_quads.cpp" \
    "$ROOT/src/game/sprite_descriptor.cpp" \
    "$ROOT/src/game/result_menu_open.cpp" \
    "$ROOT/src/runtime/missing_edge.cpp" \
    "$ROOT/tests/projection_quads_test.cpp"

run_test faded_quad_draw_test -Wno-unused-parameter -- \
    "$ROOT/src/render/projection_quads.cpp" \
    "$ROOT/src/game/sprite_descriptor.cpp" \
    "$ROOT/src/game/result_menu_open.cpp" \
    "$ROOT/src/render/faded_quad_draw.cpp" \
    "$ROOT/src/render/anm_record_walk.cpp" \
    "$ROOT/src/runtime/missing_edge.cpp" \
    "$ROOT/tests/faded_quad_draw_test.cpp"

run_test replay_file_load_test -Wno-unused-parameter -- \
    "$ROOT/src/game/replay_file_load.cpp" \
    "$ROOT/src/runtime/missing_edge.cpp" \
    "$ROOT/tests/replay_file_load_test.cpp"

run_test ending_streamer_ring_test -Wno-unused-parameter -- \
    "$ROOT/src/game/ending_text.cpp" \
    "$ROOT/src/platform/bgm_streamer_refill.cpp" \
    "$ROOT/src/render/effect_ring_update.cpp" \
    "$ROOT/src/runtime/missing_edge.cpp" \
    "$ROOT/tests/ending_streamer_ring_test.cpp"

run_test laser_line_test -Wno-unused-parameter -- \
    "$ROOT/src/game/laser_line.cpp" \
    "$ROOT/src/game/effect_pool_update.cpp" \
    "$ROOT/src/runtime/missing_edge.cpp" \
    "$ROOT/tests/laser_line_test.cpp"

run_test sound_device_init_test -Wno-unused-parameter -- \
    "$ROOT/src/platform/sound_device_init.cpp" \
    "$ROOT/src/runtime/missing_edge.cpp" \
    "$ROOT/tests/sound_device_init_test.cpp"
run_test stage_entry_test -Wno-unused-parameter -- \
    "$ROOT/src/game/stage_entry.cpp" \
    "$ROOT/tests/stage_entry_test.cpp"

run_test result_menu_draw_test -Wno-unused-parameter -- \
    "$ROOT/src/game/result_menu_draw.cpp" \
    "$ROOT/tests/result_menu_draw_test.cpp"

run_test replay_menu_draw_test -Wno-unused-parameter -- \
    "$ROOT/src/game/replay_menu_draw.cpp" \
    "$ROOT/tests/replay_menu_draw_test.cpp"

run_test player_pickup_sweep_test -Wno-unused-parameter -- \
    "$ROOT/src/game/player_pickup_sweep.cpp" \
    "$ROOT/tests/player_pickup_sweep_test.cpp"

run_test result_overlay_test -Wno-unused-parameter -- \
    "$ROOT/src/game/result_overlay.cpp" \
    "$ROOT/tests/result_overlay_test.cpp"

run_test item_spawn_test -Wno-unused-parameter -- \
    "$ROOT/src/game/item_spawn.cpp" \
    "$ROOT/tests/item_spawn_test.cpp"

run_test item_scatter_test -Wno-unused-parameter -- \
    "$ROOT/src/game/item_scatter.cpp" \
    "$ROOT/tests/item_scatter_test.cpp"

run_test edge_strip_draw_test -Wno-unused-parameter -- \
    "$ROOT/src/render/edge_strip_draw.cpp" \
    "$ROOT/tests/edge_strip_draw_test.cpp"

run_test dinput_device_setup_test -Wno-unused-parameter -- \
    "$ROOT/src/platform/dinput_device_setup.cpp" \
    "$ROOT/tests/dinput_device_setup_test.cpp"

run_test sound_stream_create_test -Wno-unused-parameter -- \
    "$ROOT/src/platform/sound_stream_create.cpp" \
    "$ROOT/tests/sound_stream_create_test.cpp"

run_test quad_transform_draw_test -Wno-unused-parameter -- \
    "$ROOT/src/render/quad_transform_draw.cpp" \
    "$ROOT/tests/quad_transform_draw_test.cpp"

run_test composite_passes_test -Wno-unused-parameter -- \
    "$ROOT/src/render/composite_passes.cpp" \
    "$ROOT/tests/composite_passes_test.cpp"

run_test line_effect_sweep_test -Wno-unused-parameter -- \
    "$ROOT/src/game/line_effect_sweep.cpp" \
    "$ROOT/tests/line_effect_sweep_test.cpp"

run_test trajectory_evaluate_test -Wno-unused-parameter -- \
    "$ROOT/src/game/trajectory_evaluate.cpp" \
    "$ROOT/tests/trajectory_evaluate_test.cpp"

run_test sprite_view_draw_test -Wno-unused-parameter -- \
    "$ROOT/src/game/sprite_test_overlay.cpp" \
    "$ROOT/tests/sprite_view_draw_test.cpp"

run_test floating_text_draw_test -Wno-unused-parameter -- \
    "$ROOT/src/game/floating_text_draw.cpp" \
    "$ROOT/tests/floating_text_draw_test.cpp"

run_test score_menu_rows_test -Wno-unused-parameter -- \
    "$ROOT/src/game/score_menu_rows.cpp" \
    "$ROOT/tests/score_menu_rows_test.cpp"

run_test laser_grow_update_test -Wno-unused-parameter -- \
    "$ROOT/src/game/laser_grow_update.cpp" \
    "$ROOT/tests/laser_grow_update_test.cpp"

run_test game_thread_text_draw_test -Wno-unused-parameter -- \
    "$ROOT/src/game/game_thread_text_draw.cpp" \
    "$ROOT/tests/game_thread_text_draw_test.cpp"

run_test input_recorder_test -Wno-unused-parameter -- \
    "$ROOT/src/game/input_recorder.cpp" \
    "$ROOT/tests/input_recorder_test.cpp"

run_test game_state_init_test \
    "$ROOT/src/app/game_state_init.cpp" \
    "$ROOT/tests/game_state_init_test.cpp"

run_test stage_update_test \
    "$ROOT/src/game/stage_update.cpp" \
    "$ROOT/tests/stage_update_test.cpp"

run_test stage_std_test \
    "$ROOT/src/game/stage_std.cpp" \
    "$ROOT/src/runtime/missing_edge.cpp" \
    "$ROOT/tests/stage_std_test.cpp"

run_test stage_timeline_test \
    "$ROOT/src/game/stage_std.cpp" \
    "$ROOT/src/game/stage_timeline.cpp" \
    "$ROOT/tests/stage_timeline_test.cpp"

run_test coverage_completion_test \
    "$ROOT/src/app/main_tasks.cpp" \
    "$ROOT/src/game/manager_factories.cpp" \
    "$ROOT/src/game/gameplay_final_runtime.cpp" \
    "$ROOT/src/game/pool_constructors.cpp" \
    "$ROOT/src/game/floating_text_draw.cpp" \
    "$ROOT/src/render/recovered_render_leaves.cpp" \
    "$ROOT/src/render/anm_vm_draw_dispatch.cpp" \
    "$ROOT/src/render/quad_build_anchored.cpp" \
    "$ROOT/src/render/quad_vertex_append.cpp" \
    "$ROOT/src/render/anm_batch_flush.cpp" \
    "$ROOT/src/game/message_manager_init.cpp" \
    "$ROOT/src/game/stage_tips.cpp" \
    "$ROOT/src/game/scheduler.cpp" \
    "$ROOT/src/game/entity.cpp" \
    "$ROOT/src/platform/midi_sequencer.cpp" \
    "$ROOT/src/render/anm_distance_color.cpp" \
    "$ROOT/src/runtime/missing_edge.cpp" \
    "$ROOT/tests/coverage_completion_test.cpp"

# Replay-score detail page (0x004329F0).
run_test replay_score_draw_test \
    "$ROOT/src/game/replay_score_draw.cpp" \
    "$ROOT/tests/replay_score_draw_test.cpp"

# Game-state animation/overlay pass (0x00415800).
run_test game_state_overlay_draw_test \
    "$ROOT/src/game/game_state_overlay_draw.cpp" \
    "$ROOT/tests/game_state_overlay_draw_test.cpp"

# Stage focus fade updater (0x00419650).
run_test stage_focus_fade_test \
    "$ROOT/src/game/stage_focus_fade.cpp" \
    "$ROOT/tests/stage_focus_fade_test.cpp"

# Replay browser list/detail renderer (0x00431BA0).
run_test replay_browser_draw_test \
    "$ROOT/src/game/replay_browser_draw.cpp" \
    "$ROOT/tests/replay_browser_draw_test.cpp"

# Replay stage/name-entry renderer (0x00433230).
run_test replay_stage_name_draw_test \
    "$ROOT/src/game/replay_stage_name_draw.cpp" \
    "$ROOT/tests/replay_stage_name_draw_test.cpp"

# Final medium-band recovery set.
run_test medium_completion_test \
    "$ROOT/src/game/bullet_runtime_update.cpp" \
    "$ROOT/src/game/menu_flow_updates.cpp" \
    "$ROOT/src/game/replay_spell_list.cpp" \
    "$ROOT/tests/medium_completion_test.cpp"

# Practice-stage selection state machine (0x00430FF0).
run_test practice_stage_menu_test \
    "$ROOT/src/game/practice_stage_menu.cpp" \
    "$ROOT/tests/practice_stage_menu_test.cpp"

# Runtime score-panel updater (0x00408D60).
run_test score_runtime_ui_update_test \
    "$ROOT/src/game/score_runtime_ui_update.cpp" \
    "$ROOT/tests/score_runtime_ui_update_test.cpp"

# Laser segment circle/rectangle cutters (0x0041EFA0, 0x0041EB00).
run_test laser_segment_cut_test \
    "$ROOT/src/game/laser_segment_cut.cpp" \
    "$ROOT/tests/laser_segment_cut_test.cpp"

# Title runtime and effect-indicator queue updates.
run_test large_runtime_updates_test \
    "$ROOT/src/game/effect_indicator_queue.cpp" \
    "$ROOT/src/game/title_menu_runtime.cpp" \
    "$ROOT/tests/large_runtime_updates_test.cpp"

# Replay bootstrap and result-choice state machines.
run_test replay_result_runtime_test \
    "$ROOT/src/game/replay_runtime_bootstrap.cpp" \
    "$ROOT/src/game/result_choice_menu.cpp" \
    "$ROOT/tests/replay_result_runtime_test.cpp"

# Name-entry and shot-practice menu completion.
run_test menu_completion_test \
    "$ROOT/src/game/name_entry.cpp" \
    "$ROOT/src/game/shot_practice_menu.cpp" \
    "$ROOT/tests/menu_completion_test.cpp"

# Player runtime initializer (0x004247F0).
run_test player_runtime_init_test \
    "$ROOT/src/game/player_runtime_init.cpp" \
    "$ROOT/src/game/scheduler.cpp" \
    "$ROOT/src/game/stage_controller_tick.cpp" \
    "$ROOT/src/render/recovered_render_leaves.cpp" \
    "$ROOT/src/render/anm_vm_draw_dispatch.cpp" \
    "$ROOT/src/render/quad_build_anchored.cpp" \
    "$ROOT/src/render/quad_vertex_append.cpp" \
    "$ROOT/src/render/anm_batch_flush.cpp" \
    "$ROOT/src/runtime/missing_edge.cpp" \
    "$ROOT/src/game/gameplay_final_runtime.cpp" \
    "$ROOT/tests/player_runtime_init_test.cpp"

# PE32-only raw player-object formation table bridge (+0x45C/+0x20/+0x98).
run_test_m32 formation_table_bridge_test \
    "$ROOT/src/game/gameplay_final_runtime.cpp" \
    "$ROOT/tests/formation_table_bridge_test.cpp"

# D3D-free retail-layout ANM descriptor/object binding and pooled-object reuse.
run_test_m32 title_anm_manager_bridge_test \
    -ffunction-sections -fdata-sections -Wl,--gc-sections -- \
    "$ROOT/src/render/animation_manager.cpp" \
    "$ROOT/src/runtime/missing_edge.cpp" \
    "$ROOT/tests/title_anm_manager_bridge_test.cpp"

# Enemy-projectile spawn and replay load/save menu runtimes
# (0x004067D0, 0x004315C0, 0x00433570).
run_test large_recovery_pass_test \
    "$ROOT/src/game/enemy_projectile_spawn.cpp" \
    "$ROOT/src/game/replay_menu_runtime.cpp" \
    "$ROOT/tests/large_recovery_pass_test.cpp"

# Ten-function large recovery continuation.
run_test next10_large_recovery_test -- \
    "$ROOT/src/game/event_script_runtime.cpp" \
    "$ROOT/src/game/projectile_command_runtime.cpp" \
    "$ROOT/src/game/player_front_runtime.cpp" \
    "$ROOT/src/platform/midi_event_runtime.cpp" \
    "$ROOT/src/game/replay_large_runtime.cpp" \
    "$ROOT/src/render/anchored_quad_draw.cpp" \
    "$ROOT/tests/next10_large_recovery_test.cpp"

run_test ending_script_runtime_test \
    "$ROOT/src/game/event_script_runtime.cpp" \
    "$ROOT/tests/ending_script_runtime_test.cpp"

run_test player_front_runtime_test \
    "$ROOT/src/game/player_front_runtime.cpp" \
    "$ROOT/tests/player_front_runtime_test.cpp"

# Stage-tips file parser (0x00419960) against the reconstructed pack-loader
# and stage-tip record types.
run_test stage_tip_parser_test -- \
    "$ROOT/src/game/stage_tip_parser.cpp" \
    "$ROOT/src/game/stage_tips.cpp" \
    "$ROOT/src/platform/pack_file_loader.cpp" \
    "$ROOT/tests/stage_tip_parser_test.cpp"

# Final 15-function pass, including completion of ExecuteEcl.
# final_quad_pipeline.cpp (0x00442670) calls the recovered 0x004423C0 that
# lives in animation_manager.cpp, whose other functions reach device and
# entity edges this target does not link; --gc-sections drops them.
run_test final_722_recovery_test -ffunction-sections -fdata-sections -Wl,--gc-sections -- \
    "$ROOT/src/game/ui_final_runtime.cpp" \
    "$ROOT/src/game/gameplay_final_runtime.cpp" \
    "$ROOT/src/render/final_quad_pipeline.cpp" \
    "$ROOT/src/render/animation_manager.cpp" \
    "$ROOT/src/platform/final_input_runtime.cpp" \
    "$ROOT/src/script/final_script_runtime.cpp" \
    "$ROOT/tests/final_722_recovery_test.cpp"

run_test final_input_runtime_test \
    "$ROOT/src/platform/final_input_runtime.cpp" \
    "$ROOT/tests/final_input_runtime_test.cpp"

# Callback-backed retail Music Room model (0x00433EF0).
run_test music_room_env_test -ffunction-sections -fdata-sections -Wl,--gc-sections -- \
    "$ROOT/src/game/ui_final_runtime.cpp" \
    "$ROOT/src/render/animation_manager.cpp" \
    "$ROOT/tests/music_room_env_test.cpp"

# Deterministic JSONL trace schema and semantic comparison helper.
python3 "$ROOT/tests/runtime_trace_compare_test.py"
python3 "$ROOT/tests/retail_probe_script_test.py"
bash "$ROOT/audit_check.sh"
