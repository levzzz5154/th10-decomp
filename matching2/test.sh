#!/bin/bash
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
CXX="${CXX:-g++}"
# The recovered headers keep retail calling conventions; defining them away
# lets the same sources parse on a host compiler.
CXXFLAGS=(-std=c++17 -Wall -Wextra -Werror "-I$ROOT/include" \
    -D__fastcall= -D__stdcall= -D__cdecl= -D__thiscall= '-D__declspec(x)=')
TEST_BUILD="$ROOT/build/tests"
mkdir -p "$TEST_BUILD"

python3 "$ROOT/tools/function_registry.py" --check
python3 "$ROOT/tools/standalone_readiness.py" --check

g++ -std=c++17 -Wall -Wextra -Werror \
    -I"$ROOT/include" \
    "$ROOT/src/game/title_main_menu.cpp" \
    "$ROOT/src/runtime/missing_edge.cpp" \
    "$ROOT/tests/title_main_menu_test.cpp" \
    -o "$TEST_BUILD/title_main_menu_test"

"$TEST_BUILD/title_main_menu_test"

"$CXX" "${CXXFLAGS[@]}" \
    "$ROOT/src/game/title_options_menu.cpp" \
    "$ROOT/tests/title_options_menu_test.cpp" \
    -o "$TEST_BUILD/title_options_menu_test"

"$TEST_BUILD/title_options_menu_test"

g++ -std=c++17 -Wall -Wextra -Werror \
    -I"$ROOT/include" \
    "$ROOT/src/render/anm_file.cpp" \
    "$ROOT/src/runtime/missing_edge.cpp" \
    "$ROOT/tests/anm_file_test.cpp" \
    -o "$TEST_BUILD/anm_file_test"

"$TEST_BUILD/anm_file_test"

"$CXX" "${CXXFLAGS[@]}" \
    "$ROOT/src/math/interpolators.cpp" \
    "$ROOT/src/script/anm_vm_tick.cpp" \
    "$ROOT/tests/anm_vm_interrupt_test.cpp" \
    -o "$TEST_BUILD/anm_vm_interrupt_test"

"$TEST_BUILD/anm_vm_interrupt_test"

g++ -std=c++17 -Wall -Wextra -Werror \
    -D__stdcall= -D__fastcall= -D__cdecl= '-D__declspec(x)=' \
    -I"$ROOT/include" \
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
    "$ROOT/tests/archive_test.cpp" \
    -o "$TEST_BUILD/archive_test"

"$TEST_BUILD/archive_test"

g++ -std=c++17 -Wall -Wextra -Werror \
    -D__stdcall= -D__fastcall= -D__cdecl= '-D__declspec(x)=' \
    -I"$ROOT/include" \
    "$ROOT/src/game/scheduler.cpp" \
    "$ROOT/src/runtime/missing_edge.cpp" \
    "$ROOT/tests/scheduler_test.cpp" \
    -o "$TEST_BUILD/scheduler_test"

"$TEST_BUILD/scheduler_test"

g++ -std=c++17 -Wall -Wextra -Werror -Wno-unused-parameter \
    -D__stdcall= -D__fastcall= -D__cdecl= '-D__declspec(x)=' \
    -I"$ROOT/include" \
    "$ROOT/src/math/timer.cpp" \
    "$ROOT/src/math/vector.cpp" \
    "$ROOT/src/math/rng.cpp" \
    "$ROOT/src/math/angle.cpp" \
    "$ROOT/src/math/easing.cpp" \
    "$ROOT/src/math/random_vector.cpp" \
    "$ROOT/src/game/menu.cpp" \
    "$ROOT/src/game/progress.cpp" \
    "$ROOT/src/game/score.cpp" \
    "$ROOT/src/runtime/missing_edge.cpp" \
    "$ROOT/src/game/scheduler.cpp" \
    "$ROOT/src/game/stage_text.cpp" \
    "$ROOT/src/render/animation_manager.cpp" \
    "$ROOT/src/render/anm_entry_load.cpp" \
    "$ROOT/tests/game_runtime_test.cpp" \
    -o "$TEST_BUILD/game_runtime_test"

"$TEST_BUILD/game_runtime_test"

g++ -std=c++17 -Wall -Wextra -Werror \
    -D__stdcall= -D__fastcall= -D__cdecl= '-D__declspec(x)=' \
    -I"$ROOT/include" \
    "$ROOT/src/game/score.cpp" \
    "$ROOT/src/runtime/missing_edge.cpp" \
    "$ROOT/tests/score_runtime_test.cpp" \
    -o "$TEST_BUILD/score_runtime_test"

"$TEST_BUILD/score_runtime_test"

g++ -std=c++17 -Wall -Wextra -Werror \
    -D__stdcall= -D__fastcall= -D__cdecl= '-D__declspec(x)=' \
    -I"$ROOT/include" \
    "$ROOT/src/render/d3d_resource_manager.cpp" \
    "$ROOT/src/runtime/missing_edge.cpp" \
    "$ROOT/tests/d3d_resource_manager_test.cpp" \
    -o "$TEST_BUILD/d3d_resource_manager_test"

"$TEST_BUILD/d3d_resource_manager_test"

g++ -std=c++17 -Wall -Wextra -Werror \
    -D__stdcall= -D__fastcall= -D__cdecl= '-D__declspec(x)=' \
    -I"$ROOT/include" \
    "$ROOT/src/platform/file.cpp" \
    "$ROOT/src/platform/memory_file.cpp" \
    "$ROOT/src/platform/resource_file.cpp" \
    "$ROOT/src/archive/resource_manager.cpp" \
    "$ROOT/src/platform/path.cpp" \
    "$ROOT/src/runtime/missing_edge.cpp" \
    "$ROOT/tests/file_resource_test.cpp" \
    -o "$TEST_BUILD/file_resource_test"

"$TEST_BUILD/file_resource_test"

g++ -std=c++17 -Wall -Wextra -Werror \
    -D__stdcall= -D__fastcall= -D__cdecl= '-D__declspec(x)=' \
    -I"$ROOT/include" \
    "$ROOT/src/platform/process.cpp" \
    "$ROOT/src/platform/text_log.cpp" \
    "$ROOT/src/platform/win32_timer.cpp" \
    "$ROOT/src/runtime/missing_edge.cpp" \
    "$ROOT/tests/process_test.cpp" \
    -o "$TEST_BUILD/process_test"

"$TEST_BUILD/process_test"

g++ -std=c++17 -Wall -Wextra -Werror \
    -D__stdcall= -D__fastcall= -D__cdecl= '-D__declspec(x)=' \
    -I"$ROOT/include" \
    "$ROOT/src/game/recovery_leaves.cpp" \
    "$ROOT/src/runtime/missing_edge.cpp" \
    "$ROOT/tests/recovery_leaves_test.cpp" \
    -o "$TEST_BUILD/recovery_leaves_test"

"$TEST_BUILD/recovery_leaves_test"

g++ -std=c++17 -Wall -Wextra -Werror \
    -D__stdcall= -D__fastcall= -D__cdecl= '-D__declspec(x)=' \
    -I"$ROOT/include" \
    "$ROOT/src/script/ecl_vm.cpp" \
    "$ROOT/src/script/ecl_helpers.cpp" \
    "$ROOT/src/game/recovery_leaves.cpp" \
    "$ROOT/src/runtime/missing_edge.cpp" \
    "$ROOT/tests/ecl_vm_test.cpp" \
    -o "$TEST_BUILD/ecl_vm_test"

"$TEST_BUILD/ecl_vm_test"

g++ -std=c++17 -Wall -Wextra -Werror \
    -I"$ROOT/include" \
    "$ROOT/src/script/entity_vm.cpp" \
    "$ROOT/src/runtime/missing_edge.cpp" \
    "$ROOT/tests/entity_vm_test.cpp" \
    -o "$TEST_BUILD/entity_vm_test"

"$TEST_BUILD/entity_vm_test"

g++ -std=c++17 -Wall -Wextra -Werror \
    -D__stdcall= -D__fastcall= -D__cdecl= '-D__declspec(x)=' \
    -I"$ROOT/include" \
    "$ROOT/src/script/ecl_helpers.cpp" \
    "$ROOT/src/runtime/missing_edge.cpp" \
    "$ROOT/tests/ecl_helpers_test.cpp" \
    -o "$TEST_BUILD/ecl_helpers_test"

"$TEST_BUILD/ecl_helpers_test"

g++ -std=c++17 -Wall -Wextra -Werror \
    -I"$ROOT/include" \
    "$ROOT/src/script/prng.cpp" \
    "$ROOT/src/runtime/missing_edge.cpp" \
    "$ROOT/tests/prng_test.cpp" \
    -o "$TEST_BUILD/prng_test"

"$TEST_BUILD/prng_test"

g++ -std=c++17 -Wall -Wextra -Werror \
    -D__stdcall= -D__fastcall= -D__cdecl= '-D__declspec(x)=' \
    -I"$ROOT/include" \
    "$ROOT/src/render/animation_slot.cpp" \
    "$ROOT/src/runtime/missing_edge.cpp" \
    "$ROOT/tests/animation_slot_test.cpp" \
    -o "$TEST_BUILD/animation_slot_test"

"$TEST_BUILD/animation_slot_test"

# ANM archive-entry loader (0x00447470) and shared sprite arithmetic.
g++ -std=c++17 -Wall -Wextra -Werror \
    -D__stdcall= -D__fastcall= -D__cdecl= '-D__declspec(x)=' \
    -I"$ROOT/include" \
    "$ROOT/src/render/anm_entry_load.cpp" \
    "$ROOT/src/runtime/missing_edge.cpp" \
    "$ROOT/tests/anm_entry_load_test.cpp" \
    -o "$TEST_BUILD/anm_entry_load_test"
"$TEST_BUILD/anm_entry_load_test"

# Per-slot game-state snapshot capture/restore (0x0042A450).
g++ -std=c++17 -Wall -Wextra -Werror \
    -D__stdcall= -D__fastcall= -D__cdecl= '-D__declspec(x)=' \
    -I"$ROOT/include" \
    "$ROOT/src/game/slot_snapshot.cpp" \
    "$ROOT/src/runtime/missing_edge.cpp" \
    "$ROOT/tests/slot_snapshot_test.cpp" \
    -o "$TEST_BUILD/slot_snapshot_test"
"$TEST_BUILD/slot_snapshot_test"

# Four-block parameter interpolator (0x004049A0).
g++ -std=c++17 -Wall -Wextra -Werror \
    -D__stdcall= -D__fastcall= -D__cdecl= '-D__declspec(x)=' \
    -I"$ROOT/include" \
    "$ROOT/src/math/param_block_interp.cpp" \
    "$ROOT/src/math/math_utils.cpp" \
    "$ROOT/src/math/easing.cpp" \
    "$ROOT/src/runtime/missing_edge.cpp" \
    "$ROOT/tests/param_block_interp_test.cpp" \
    -o "$TEST_BUILD/param_block_interp_test"
"$TEST_BUILD/param_block_interp_test"

# Rectangular entity-pool region sweep (0x00408210).
g++ -std=c++17 -Wall -Wextra -Werror \
    -D__stdcall= -D__fastcall= -D__cdecl= '-D__declspec(x)=' \
    -I"$ROOT/include" \
    "$ROOT/src/game/entity_region_sweep.cpp" \
    "$ROOT/src/runtime/missing_edge.cpp" \
    "$ROOT/tests/entity_region_sweep_test.cpp" \
    -o "$TEST_BUILD/entity_region_sweep_test"
"$TEST_BUILD/entity_region_sweep_test"

# Gameplay render/transition pass (0x00402850).
g++ -std=c++17 -Wall -Wextra -Werror \
    -D__stdcall= -D__fastcall= -D__cdecl= '-D__declspec(x)=' \
    -I"$ROOT/include" \
    "$ROOT/src/game/gameplay_render_pass.cpp" \
    "$ROOT/src/runtime/missing_edge.cpp" \
    "$ROOT/tests/gameplay_render_pass_test.cpp" \
    -o "$TEST_BUILD/gameplay_render_pass_test"
"$TEST_BUILD/gameplay_render_pass_test"

# Message host construction (0x0040D280).
g++ -std=c++17 -Wall -Wextra -Werror \
    -D__stdcall= -D__fastcall= -D__cdecl= '-D__declspec(x)=' \
    -I"$ROOT/include" \
    "$ROOT/src/game/message_host_init.cpp" \
    "$ROOT/src/math/math_utils.cpp" \
    "$ROOT/src/runtime/missing_edge.cpp" \
    "$ROOT/tests/message_host_init_test.cpp" \
    -o "$TEST_BUILD/message_host_init_test"
"$TEST_BUILD/message_host_init_test"

# Per-stage slot construction (0x00415B00).
g++ -std=c++17 -Wall -Wextra -Werror \
    -D__stdcall= -D__fastcall= -D__cdecl= '-D__declspec(x)=' \
    -I"$ROOT/include" \
    "$ROOT/src/game/stage_slot_state.cpp" \
    "$ROOT/src/game/entity_region_sweep.cpp" \
    "$ROOT/src/math/math_utils.cpp" \
    "$ROOT/src/runtime/missing_edge.cpp" \
    "$ROOT/tests/stage_slot_state_test.cpp" \
    -o "$TEST_BUILD/stage_slot_state_test"
"$TEST_BUILD/stage_slot_state_test"

g++ -std=c++17 -Wall -Wextra -Werror \
    -I"$ROOT/include" \
    "$ROOT/src/game/entity_movement_slot.cpp" \
    "$ROOT/src/runtime/missing_edge.cpp" \
    "$ROOT/tests/entity_movement_slot_test.cpp" \
    -o "$TEST_BUILD/entity_movement_slot_test"

"$TEST_BUILD/entity_movement_slot_test"

g++ -std=c++17 -Wall -Wextra -Werror \
    -I"$ROOT/include" \
    "$ROOT/src/game/entity_color_slot.cpp" \
    "$ROOT/src/runtime/missing_edge.cpp" \
    "$ROOT/tests/entity_color_slot_test.cpp" \
    -o "$TEST_BUILD/entity_color_slot_test"

"$TEST_BUILD/entity_color_slot_test"

g++ -std=c++17 -Wall -Wextra -Werror \
    -I"$ROOT/include" \
    "$ROOT/src/game/linked_pool_release.cpp" \
    "$ROOT/src/runtime/missing_edge.cpp" \
    "$ROOT/tests/linked_pool_release_test.cpp" \
    -o "$TEST_BUILD/linked_pool_release_test"

"$TEST_BUILD/linked_pool_release_test"

g++ -std=c++17 -Wall -Wextra -Werror \
    -I"$ROOT/include" \
    "$ROOT/src/game/animation_resource_lazy_fetch.cpp" \
    "$ROOT/src/runtime/missing_edge.cpp" \
    "$ROOT/tests/animation_resource_lazy_fetch_test.cpp" \
    -o "$TEST_BUILD/animation_resource_lazy_fetch_test"

"$TEST_BUILD/animation_resource_lazy_fetch_test"

g++ -std=c++17 -Wall -Wextra -Werror \
    -I"$ROOT/include" \
    "$ROOT/src/math/vector3_cross.cpp" \
    "$ROOT/src/runtime/missing_edge.cpp" \
    "$ROOT/tests/vector3_cross_test.cpp" \
    -o "$TEST_BUILD/vector3_cross_test"

"$TEST_BUILD/vector3_cross_test"

g++ -std=c++17 -Wall -Wextra -Werror \
    -D__stdcall= -D__fastcall= -D__cdecl= '-D__declspec(x)=' \
    -I"$ROOT/include" \
    "$ROOT/src/game/archive_cursor.cpp" \
    "$ROOT/src/runtime/missing_edge.cpp" \
    "$ROOT/tests/archive_cursor_test.cpp" \
    -o "$TEST_BUILD/archive_cursor_test"

"$TEST_BUILD/archive_cursor_test"

g++ -std=c++17 -Wall -Wextra -Werror \
    -D__stdcall= -D__fastcall= -D__cdecl= '-D__declspec(x)=' \
    -I"$ROOT/include" \
    "$ROOT/src/game/archive_cursor_read.cpp" \
    "$ROOT/src/runtime/missing_edge.cpp" \
    "$ROOT/tests/archive_cursor_read_test.cpp" \
    -o "$TEST_BUILD/archive_cursor_read_test"

"$TEST_BUILD/archive_cursor_read_test"

g++ -std=c++17 -Wall -Wextra -Werror \
    -I"$ROOT/include" \
    "$ROOT/src/game/asset_buffer.cpp" \
    "$ROOT/src/render/transparent_pixel_fill.cpp" \
    "$ROOT/src/runtime/missing_edge.cpp" \
    "$ROOT/tests/recovery_batch3_test.cpp" \
    -o "$TEST_BUILD/recovery_batch3_test"

"$TEST_BUILD/recovery_batch3_test"


g++ -std=c++17 -Wall -Wextra -Werror \
    -D__stdcall= -D__fastcall= -D__cdecl= '-D__declspec(x)=' \
    -I"$ROOT/include" \
    "$ROOT/src/game/particle_seed.cpp" \
    "$ROOT/src/game/stage_tip_manager.cpp" \
    "$ROOT/src/runtime/missing_edge.cpp" \
    "$ROOT/tests/recovery_batch4_test.cpp" \
    -o "$TEST_BUILD/recovery_batch4_test"

"$TEST_BUILD/recovery_batch4_test"


g++ -std=c++17 -Wall -Wextra -Werror \
    -I"$ROOT/include" \
    "$ROOT/src/game/score_popup.cpp" \
    "$ROOT/src/runtime/missing_edge.cpp" \
    "$ROOT/tests/score_popup_test.cpp" \
    -o "$TEST_BUILD/score_popup_test"

"$TEST_BUILD/score_popup_test"


g++ -std=c++17 -Wall -Wextra -Werror \
    -I"$ROOT/include" \
    "$ROOT/src/game/score_cleanup.cpp" \
    "$ROOT/src/render/image_alpha_transform.cpp" \
    "$ROOT/src/render/transparent_pixel_fill.cpp" \
    "$ROOT/src/render/transparent_pixel_fill_locked.cpp" \
    "$ROOT/src/runtime/missing_edge.cpp" \
    "$ROOT/tests/large_easy_functions_test.cpp" \
    -o "$TEST_BUILD/large_easy_functions_test"

"$TEST_BUILD/large_easy_functions_test"

# The 32-bit suites need the i686 glibc headers; skip them (with a notice)
# on hosts without gnu/stubs-32.h instead of failing the whole run.
if [[ -f /usr/include/gnu/stubs-32.h ]]; then
    # GameState stores 32-bit retail pointers in its ABI fields, so exercise
    # its device-failure state transitions in a 32-bit host binary.
    g++ -m32 -std=c++17 -Wall -Wextra -Werror \
        -D__stdcall= -D__fastcall= -D__cdecl= '-D__declspec(x)=' \
        -I"$ROOT/include" \
        "$ROOT/src/game/game_state.cpp" \
        "$ROOT/src/game/scheduler.cpp" \
        "$ROOT/tests/game_state_test.cpp" \
        -o "$TEST_BUILD/game_state_test"

    "$TEST_BUILD/game_state_test"

    # The bullet manager is laid out with 32-bit retail pointers, so exercise
    # the create / load-scripts / release lifecycle on a 32-bit host binary.
    g++ -m32 -std=c++17 -Wall -Wextra -Werror -Wno-unused-parameter \
        -D__stdcall= -D__fastcall= -D__cdecl= '-D__declspec(x)=' \
        -I"$ROOT/include" \
        "$ROOT/src/game/bullet.cpp" \
        "$ROOT/src/game/scheduler.cpp" \
        "$ROOT/src/render/animation_manager.cpp" \
        "$ROOT/src/render/anm_entry_load.cpp" \
        "$ROOT/tests/bullet_manager_test.cpp" \
        -o "$TEST_BUILD/bullet_manager_test"

    "$TEST_BUILD/bullet_manager_test"
else
    echo "NOTE: skipping 32-bit suites (gnu/stubs-32.h not installed)"
fi

g++ -std=c++17 -Wall -Wextra -Werror \
    -D__stdcall= -D__fastcall= -D__cdecl= '-D__declspec(x)=' \
    -I"$ROOT/include" \
    "$ROOT/src/game/game_thread_queue.cpp" \
    "$ROOT/src/runtime/missing_edge.cpp" \
    "$ROOT/tests/game_thread_queue_test.cpp" \
    -o "$TEST_BUILD/game_thread_queue_test"

"$TEST_BUILD/game_thread_queue_test"

g++ -std=c++17 -Wall -Wextra -Werror \
    -D__stdcall= -D__fastcall= -D__cdecl= '-D__declspec(x)=' \
    -I"$ROOT/include" \
    "$ROOT/src/game/player_scheduler.cpp" \
    "$ROOT/src/runtime/missing_edge.cpp" \
    "$ROOT/tests/player_scheduler_test.cpp" \
    -o "$TEST_BUILD/player_scheduler_test"

"$TEST_BUILD/player_scheduler_test"

g++ -std=c++17 -Wall -Wextra -Werror \
    -D__stdcall= -D__fastcall= -D__cdecl= '-D__declspec(x)=' \
    -I"$ROOT/include" \
    "$ROOT/src/render/quad_vertex_append.cpp" \
    "$ROOT/src/game/archive_cursor_open.cpp" \
    "$ROOT/src/game/score_timer_leaves.cpp" \
    "$ROOT/src/game/game_config_defaults.cpp" \
    "$ROOT/src/game/stage_tip_manager.cpp" \
    "$ROOT/src/platform/sound_worker.cpp" \
    "$ROOT/src/runtime/missing_edge.cpp" \
    "$ROOT/tests/recovery_batch_test.cpp" \
    -o "$TEST_BUILD/recovery_batch_test"

"$TEST_BUILD/recovery_batch_test"

g++ -std=c++17 -Wall -Wextra -Werror \
    -D__stdcall= -D__fastcall= -D__cdecl= '-D__declspec(x)=' \
    -I"$ROOT/include" \
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
    "$ROOT/tests/recovery_batch2_test.cpp" \
    -o "$TEST_BUILD/recovery_batch2_test"

"$TEST_BUILD/recovery_batch2_test"

g++ -std=c++17 -Wall -Wextra -Werror -Wno-unused-parameter \
    -D__stdcall= -D__fastcall= -D__cdecl= '-D__declspec(x)=' \
    -I"$ROOT/include" \
    "$ROOT/src/util/legacy_string_funclets.cpp" \
    "$ROOT/src/platform/sound_float_forward.cpp" \
    "$ROOT/src/game/player_motion.cpp" \
    "$ROOT/src/game/weather_pool.cpp" \
    "$ROOT/src/script/ecl_vm_children.cpp" \
    "$ROOT/src/game/manager_factories.cpp" \
    "$ROOT/src/game/message_manager_init.cpp" \
    "$ROOT/src/game/bullet_manager.cpp" \
    "$ROOT/src/game/enemy_lifecycle.cpp" \
    "$ROOT/src/game/boss_overlays.cpp" \
    "$ROOT/src/render/render_stage_select.cpp" \
    "$ROOT/src/game/stage_background.cpp" \
    "$ROOT/src/render/anm_texture_upload.cpp" \
    "$ROOT/src/platform/midi_worker.cpp" \
    "$ROOT/src/game/scheduler.cpp" \
    "$ROOT/src/game/entity.cpp" \
    "$ROOT/src/runtime/missing_edge.cpp" \
    "$ROOT/tests/manager_factories_test.cpp" \
    -o "$TEST_BUILD/manager_factories_test"

"$TEST_BUILD/manager_factories_test"

g++ -std=c++17 -Wall -Wextra -Werror -Wno-unused-parameter \
    -D__stdcall= -D__fastcall= -D__cdecl= '-D__declspec(x)=' \
    -I"$ROOT/include" \
    "$ROOT/src/game/enemy_grid_scan.cpp" \
    "$ROOT/src/game/manager_factories.cpp" \
    "$ROOT/src/game/enemy_lifecycle.cpp" \
    "$ROOT/src/game/main_menu_dispatch.cpp" \
    "$ROOT/src/game/key_config.cpp" \
    "$ROOT/src/render/anm_pending_service.cpp" \
    "$ROOT/src/game/ascii_overlay_callbacks.cpp" \
    "$ROOT/src/game/bullet_manager.cpp" \
    "$ROOT/src/game/player_motion.cpp" \
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
    "$ROOT/tests/bullet_systems_test.cpp" \
    -o "$TEST_BUILD/bullet_systems_test"

"$TEST_BUILD/bullet_systems_test"

g++ -std=c++17 -Wall -Wextra -Werror -Wno-unused-parameter \
    -D__stdcall= -D__fastcall= -D__cdecl= '-D__declspec(x)=' \
    -I"$ROOT/include" \
    "$ROOT/src/app/fps_counter.cpp" \
    "$ROOT/src/game/ending_screen.cpp" \
    "$ROOT/src/render/default_viewport.cpp" \
    "$ROOT/src/game/ascii_overlay_callbacks.cpp" \
    "$ROOT/src/game/bullet_manager.cpp" \
    "$ROOT/src/game/manager_factories.cpp" \
    "$ROOT/src/game/title_assets.cpp" \
    "$ROOT/src/platform/midi_worker.cpp" \
    "$ROOT/src/platform/sound_effect_buffers.cpp" \
    "$ROOT/src/render/anm_vm_draw_dispatch.cpp" \
    "$ROOT/src/script/stage_ecl_load.cpp" \
    "$ROOT/src/game/enemy_motion_steps.cpp" \
    "$ROOT/src/game/enemy_lifecycle.cpp" \
    "$ROOT/src/game/pause_menu_reset.cpp" \
    "$ROOT/src/game/item_field_contact.cpp" \
    "$ROOT/src/render/anm_surface_restore.cpp" \
    "$ROOT/src/game/scheduler.cpp" \
    "$ROOT/src/game/entity.cpp" \
    "$ROOT/src/runtime/missing_edge.cpp" \
    "$ROOT/tests/enemy_motion_steps_test.cpp" \
    -o "$TEST_BUILD/enemy_motion_steps_test"

"$TEST_BUILD/enemy_motion_steps_test"

g++ -std=c++17 -Wall -Wextra -Werror -Wno-unused-parameter \
    -D__stdcall= -D__fastcall= -D__cdecl= '-D__declspec(x)=' \
    -I"$ROOT/include" \
    "$ROOT/src/platform/joystick_property.cpp" \
    "$ROOT/src/game/enemy_lifecycle.cpp" \
    "$ROOT/src/script/ecl_name_table.cpp" \
    "$ROOT/src/game/spell_timer.cpp" \
    "$ROOT/src/game/bullet_manager.cpp" \
    "$ROOT/src/game/manager_factories.cpp" \
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
    "$ROOT/tests/game_systems_test.cpp" \
    -o "$TEST_BUILD/game_systems_test"

"$TEST_BUILD/game_systems_test"

g++ -std=c++17 -Wall -Wextra -Werror -Wno-unused-parameter \
    -D__stdcall= -D__fastcall= -D__cdecl= '-D__declspec(x)=' \
    -I"$ROOT/include" \
    "$ROOT/src/render/anm_script_table_sweep.cpp" \
    "$ROOT/src/game/enemy_motion_steps.cpp" \
    "$ROOT/src/game/score_tasks.cpp" \
    "$ROOT/src/game/spell_card_dispatch.cpp" \
    "$ROOT/src/platform/font_surface_blend.cpp" \
    "$ROOT/src/platform/joystick_poll.cpp" \
    "$ROOT/src/runtime/missing_edge.cpp" \
    "$ROOT/tests/spell_and_input_test.cpp" \
    -o "$TEST_BUILD/spell_and_input_test"

"$TEST_BUILD/spell_and_input_test"

g++ -std=c++17 -Wall -Wextra -Werror -Wno-unused-parameter \
    -D__stdcall= -D__fastcall= -D__cdecl= '-D__declspec(x)=' \
    -I"$ROOT/include" \
    "$ROOT/src/app/version_marker.cpp" \
    "$ROOT/src/game/game_mode_switch.cpp" \
    "$ROOT/src/game/stage_controller_tick.cpp" \
    "$ROOT/src/runtime/missing_edge.cpp" \
    "$ROOT/tests/game_mode_transitions_test.cpp" \
    -o "$TEST_BUILD/game_mode_transitions_test"

"$TEST_BUILD/game_mode_transitions_test"

g++ -std=c++17 -Wall -Wextra -Werror -Wno-unused-parameter \
    -D__stdcall= -D__fastcall= -D__cdecl= '-D__declspec(x)=' \
    -I"$ROOT/include" \
    "$ROOT/src/math/oriented_rect.cpp" \
    "$ROOT/src/game/trigger_region.cpp" \
    "$ROOT/src/render/special_quad.cpp" \
    "$ROOT/src/game/spell_timeout.cpp" \
    "$ROOT/src/runtime/missing_edge.cpp" \
    "$ROOT/tests/spell_timeout_test.cpp" \
    -o "$TEST_BUILD/spell_timeout_test"

"$TEST_BUILD/spell_timeout_test"

g++ -std=c++17 -Wall -Wextra -Werror -Wno-unused-parameter \
    -D__stdcall= -D__fastcall= -D__cdecl= '-D__declspec(x)=' \
    -I"$ROOT/include" \
    "$ROOT/src/game/trigger_activation.cpp" \
    "$ROOT/src/game/projectile_bounce.cpp" \
    "$ROOT/src/runtime/missing_edge.cpp" \
    "$ROOT/tests/trigger_activation_test.cpp" \
    -o "$TEST_BUILD/trigger_activation_test"

"$TEST_BUILD/trigger_activation_test"

g++ -std=c++17 -Wall -Wextra -Werror -Wno-unused-parameter \
    -D__stdcall= -D__fastcall= -D__cdecl= '-D__declspec(x)=' \
    -I"$ROOT/include" \
    "$ROOT/src/platform/font_texture_draw.cpp" \
    "$ROOT/src/render/special_quad.cpp" \
    "$ROOT/src/runtime/missing_edge.cpp" \
    "$ROOT/tests/font_texture_draw_test.cpp" \
    -o "$TEST_BUILD/font_texture_draw_test"

"$TEST_BUILD/font_texture_draw_test"

g++ -std=c++17 -Wall -Wextra -Werror -Wno-unused-parameter \
    -D__stdcall= -D__fastcall= -D__cdecl= '-D__declspec(x)=' \
    -I"$ROOT/include" \
    "$ROOT/src/platform/font_cache_init.cpp" \
    "$ROOT/src/render/queued_anm_cleanup.cpp" \
    "$ROOT/src/runtime/missing_edge.cpp" \
    "$ROOT/tests/font_cache_init_test.cpp" \
    -o "$TEST_BUILD/font_cache_init_test"

"$TEST_BUILD/font_cache_init_test"

g++ -std=c++17 -Wall -Wextra -Werror -Wno-unused-parameter \
    -D__stdcall= -D__fastcall= -D__cdecl= '-D__declspec(x)=' \
    -I"$ROOT/include" \
    "$ROOT/src/game/sprite_test_overlay.cpp" \
    "$ROOT/src/render/quad_build_anchored.cpp" \
    "$ROOT/src/runtime/missing_edge.cpp" \
    "$ROOT/tests/sprite_test_overlay_test.cpp" \
    -o "$TEST_BUILD/sprite_test_overlay_test"

"$TEST_BUILD/sprite_test_overlay_test"

g++ -std=c++17 -Wall -Wextra -Werror -Wno-unused-parameter \
    -D__stdcall= -D__fastcall= -D__cdecl= '-D__declspec(x)=' \
    -I"$ROOT/include" \
    "$ROOT/src/game/score_hud_update.cpp" \
    "$ROOT/src/runtime/missing_edge.cpp" \
    "$ROOT/tests/score_hud_update_test.cpp" \
    -o "$TEST_BUILD/score_hud_update_test"

"$TEST_BUILD/score_hud_update_test"

g++ -std=c++17 -Wall -Wextra -Werror -Wno-unused-parameter \
    -D__stdcall= -D__fastcall= -D__cdecl= '-D__declspec(x)=' \
    -I"$ROOT/include" \
    "$ROOT/src/render/projection_quads.cpp" \
    "$ROOT/src/game/sprite_descriptor.cpp" \
    "$ROOT/src/game/result_menu_open.cpp" \
    "$ROOT/src/runtime/missing_edge.cpp" \
    "$ROOT/tests/projection_quads_test.cpp" \
    -o "$TEST_BUILD/projection_quads_test"

"$TEST_BUILD/projection_quads_test"

g++ -std=c++17 -Wall -Wextra -Werror -Wno-unused-parameter \
    -D__stdcall= -D__fastcall= -D__cdecl= '-D__declspec(x)=' \
    -I"$ROOT/include" \
    "$ROOT/src/render/projection_quads.cpp" \
    "$ROOT/src/game/sprite_descriptor.cpp" \
    "$ROOT/src/game/result_menu_open.cpp" \
    "$ROOT/src/render/faded_quad_draw.cpp" \
    "$ROOT/src/render/anm_record_walk.cpp" \
    "$ROOT/src/runtime/missing_edge.cpp" \
    "$ROOT/tests/faded_quad_draw_test.cpp" \
    -o "$TEST_BUILD/faded_quad_draw_test"

"$TEST_BUILD/faded_quad_draw_test"

g++ -std=c++17 -Wall -Wextra -Werror -Wno-unused-parameter \
    -D__stdcall= -D__fastcall= -D__cdecl= '-D__declspec(x)=' \
    -I"$ROOT/include" \
    "$ROOT/src/game/replay_file_load.cpp" \
    "$ROOT/src/runtime/missing_edge.cpp" \
    "$ROOT/tests/replay_file_load_test.cpp" \
    -o "$TEST_BUILD/replay_file_load_test"

"$TEST_BUILD/replay_file_load_test"

g++ -std=c++17 -Wall -Wextra -Werror -Wno-unused-parameter \
    -D__stdcall= -D__fastcall= -D__cdecl= '-D__declspec(x)=' \
    -I"$ROOT/include" \
    "$ROOT/src/game/ending_text.cpp" \
    "$ROOT/src/platform/bgm_streamer_refill.cpp" \
    "$ROOT/src/render/effect_ring_update.cpp" \
    "$ROOT/src/runtime/missing_edge.cpp" \
    "$ROOT/tests/ending_streamer_ring_test.cpp" \
    -o "$TEST_BUILD/ending_streamer_ring_test"

"$TEST_BUILD/ending_streamer_ring_test"

g++ -std=c++17 -Wall -Wextra -Werror -Wno-unused-parameter \
    -D__stdcall= -D__fastcall= -D__cdecl= '-D__declspec(x)=' \
    -I"$ROOT/include" \
    "$ROOT/src/game/laser_line.cpp" \
    "$ROOT/src/game/effect_pool_update.cpp" \
    "$ROOT/src/runtime/missing_edge.cpp" \
    "$ROOT/tests/laser_line_test.cpp" \
    -o "$TEST_BUILD/laser_line_test"

"$TEST_BUILD/laser_line_test"

g++ -std=c++17 -Wall -Wextra -Werror -Wno-unused-parameter \
    -D__stdcall= -D__fastcall= -D__cdecl= '-D__declspec(x)=' \
    -I"$ROOT/include" \
    "$ROOT/src/platform/sound_device_init.cpp" \
    "$ROOT/src/runtime/missing_edge.cpp" \
    "$ROOT/tests/sound_device_init_test.cpp" \
    -o "$TEST_BUILD/sound_device_init_test"

"$TEST_BUILD/sound_device_init_test"
g++ -std=c++17 -Wall -Wextra -Werror -Wno-unused-parameter -D__stdcall= -D__fastcall= -D__cdecl= '-D__declspec(x)=' \
  -I"$ROOT/include" \
  "$ROOT/src/game/stage_entry.cpp" \
  "$ROOT/tests/stage_entry_test.cpp" \
  -o "$TEST_BUILD/stage_entry_test"
"$TEST_BUILD/stage_entry_test"

g++ -std=c++17 -Wall -Wextra -Werror -Wno-unused-parameter \
  -D__stdcall= -D__fastcall= -D__cdecl= '-D__declspec(x)=' \
  -I"$ROOT/include" \
  "$ROOT/src/game/result_menu_draw.cpp" \
  "$ROOT/tests/result_menu_draw_test.cpp" \
  -o "$TEST_BUILD/result_menu_draw_test"
"$TEST_BUILD/result_menu_draw_test"

g++ -std=c++17 -Wall -Wextra -Werror -Wno-unused-parameter \
  -D__stdcall= -D__fastcall= -D__cdecl= '-D__declspec(x)=' \
  -I"$ROOT/include" \
  "$ROOT/src/game/replay_menu_draw.cpp" \
  "$ROOT/tests/replay_menu_draw_test.cpp" \
  -o "$TEST_BUILD/replay_menu_draw_test"
"$TEST_BUILD/replay_menu_draw_test"

g++ -std=c++17 -Wall -Wextra -Werror -Wno-unused-parameter \
  -D__stdcall= -D__fastcall= -D__cdecl= '-D__declspec(x)=' \
  -I"$ROOT/include" \
  "$ROOT/src/game/player_pickup_sweep.cpp" \
  "$ROOT/tests/player_pickup_sweep_test.cpp" \
  -o "$TEST_BUILD/player_pickup_sweep_test"
"$TEST_BUILD/player_pickup_sweep_test"

g++ -std=c++17 -Wall -Wextra -Werror -Wno-unused-parameter \
  -D__stdcall= -D__fastcall= -D__cdecl= '-D__declspec(x)=' \
  -I"$ROOT/include" \
  "$ROOT/src/game/result_overlay.cpp" \
  "$ROOT/tests/result_overlay_test.cpp" \
  -o "$TEST_BUILD/result_overlay_test"
"$TEST_BUILD/result_overlay_test"

g++ -std=c++17 -Wall -Wextra -Werror -Wno-unused-parameter \
  -D__stdcall= -D__fastcall= -D__cdecl= '-D__declspec(x)=' \
  -I"$ROOT/include" \
  "$ROOT/src/game/item_spawn.cpp" \
  "$ROOT/tests/item_spawn_test.cpp" \
  -o "$TEST_BUILD/item_spawn_test"
"$TEST_BUILD/item_spawn_test"

g++ -std=c++17 -Wall -Wextra -Werror -Wno-unused-parameter \
  -D__stdcall= -D__fastcall= -D__cdecl= '-D__declspec(x)=' \
  -I"$ROOT/include" \
  "$ROOT/src/game/item_scatter.cpp" \
  "$ROOT/tests/item_scatter_test.cpp" \
  -o "$TEST_BUILD/item_scatter_test"
"$TEST_BUILD/item_scatter_test"

g++ -std=c++17 -Wall -Wextra -Werror -Wno-unused-parameter \
  -D__stdcall= -D__fastcall= -D__cdecl= '-D__declspec(x)=' \
  -I"$ROOT/include" \
  "$ROOT/src/render/edge_strip_draw.cpp" \
  "$ROOT/tests/edge_strip_draw_test.cpp" \
  -o "$TEST_BUILD/edge_strip_draw_test"
"$TEST_BUILD/edge_strip_draw_test"

g++ -std=c++17 -Wall -Wextra -Werror -Wno-unused-parameter \
  -D__stdcall= -D__fastcall= -D__cdecl= '-D__declspec(x)=' \
  -I"$ROOT/include" \
  "$ROOT/src/platform/dinput_device_setup.cpp" \
  "$ROOT/tests/dinput_device_setup_test.cpp" \
  -o "$TEST_BUILD/dinput_device_setup_test"
"$TEST_BUILD/dinput_device_setup_test"

g++ -std=c++17 -Wall -Wextra -Werror -Wno-unused-parameter \
  -D__stdcall= -D__fastcall= -D__cdecl= '-D__declspec(x)=' \
  -I"$ROOT/include" \
  "$ROOT/src/platform/sound_stream_create.cpp" \
  "$ROOT/tests/sound_stream_create_test.cpp" \
  -o "$TEST_BUILD/sound_stream_create_test"
"$TEST_BUILD/sound_stream_create_test"

g++ -std=c++17 -Wall -Wextra -Werror -Wno-unused-parameter \
  -D__stdcall= -D__fastcall= -D__cdecl= '-D__declspec(x)=' \
  -I"$ROOT/include" \
  "$ROOT/src/render/quad_transform_draw.cpp" \
  "$ROOT/tests/quad_transform_draw_test.cpp" \
  -o "$TEST_BUILD/quad_transform_draw_test"
"$TEST_BUILD/quad_transform_draw_test"

g++ -std=c++17 -Wall -Wextra -Werror -Wno-unused-parameter \
  -D__stdcall= -D__fastcall= -D__cdecl= '-D__declspec(x)=' \
  -I"$ROOT/include" \
  "$ROOT/src/render/composite_passes.cpp" \
  "$ROOT/tests/composite_passes_test.cpp" \
  -o "$TEST_BUILD/composite_passes_test"
"$TEST_BUILD/composite_passes_test"

g++ -std=c++17 -Wall -Wextra -Werror -Wno-unused-parameter \
  -D__stdcall= -D__fastcall= -D__cdecl= '-D__declspec(x)=' \
  -I"$ROOT/include" \
  "$ROOT/src/game/line_effect_sweep.cpp" \
  "$ROOT/tests/line_effect_sweep_test.cpp" \
  -o "$TEST_BUILD/line_effect_sweep_test"
"$TEST_BUILD/line_effect_sweep_test"

g++ -std=c++17 -Wall -Wextra -Werror -Wno-unused-parameter \
  -D__stdcall= -D__fastcall= -D__cdecl= '-D__declspec(x)=' \
  -I"$ROOT/include" \
  "$ROOT/src/game/trajectory_evaluate.cpp" \
  "$ROOT/tests/trajectory_evaluate_test.cpp" \
  -o "$TEST_BUILD/trajectory_evaluate_test"
"$TEST_BUILD/trajectory_evaluate_test"

g++ -std=c++17 -Wall -Wextra -Werror -Wno-unused-parameter \
  -D__stdcall= -D__fastcall= -D__cdecl= '-D__declspec(x)=' \
  -I"$ROOT/include" \
  "$ROOT/src/game/sprite_test_overlay.cpp" \
  "$ROOT/tests/sprite_view_draw_test.cpp" \
  -o "$TEST_BUILD/sprite_view_draw_test"
"$TEST_BUILD/sprite_view_draw_test"

g++ -std=c++17 -Wall -Wextra -Werror -Wno-unused-parameter \
  -D__stdcall= -D__fastcall= -D__cdecl= '-D__declspec(x)=' \
  -I"$ROOT/include" \
  "$ROOT/src/game/floating_text_draw.cpp" \
  "$ROOT/tests/floating_text_draw_test.cpp" \
  -o "$TEST_BUILD/floating_text_draw_test"
"$TEST_BUILD/floating_text_draw_test"

g++ -std=c++17 -Wall -Wextra -Werror -Wno-unused-parameter \
  -D__stdcall= -D__fastcall= -D__cdecl= '-D__declspec(x)=' \
  -I"$ROOT/include" \
  "$ROOT/src/game/score_menu_rows.cpp" \
  "$ROOT/tests/score_menu_rows_test.cpp" \
  -o "$TEST_BUILD/score_menu_rows_test"
"$TEST_BUILD/score_menu_rows_test"

g++ -std=c++17 -Wall -Wextra -Werror -Wno-unused-parameter \
  -D__stdcall= -D__fastcall= -D__cdecl= '-D__declspec(x)=' \
  -I"$ROOT/include" \
  "$ROOT/src/game/laser_grow_update.cpp" \
  "$ROOT/tests/laser_grow_update_test.cpp" \
  -o "$TEST_BUILD/laser_grow_update_test"
"$TEST_BUILD/laser_grow_update_test"

g++ -std=c++17 -Wall -Wextra -Werror -Wno-unused-parameter \
  -D__stdcall= -D__fastcall= -D__cdecl= '-D__declspec(x)=' \
  -I"$ROOT/include" \
  "$ROOT/src/game/game_thread_text_draw.cpp" \
  "$ROOT/tests/game_thread_text_draw_test.cpp" \
  -o "$TEST_BUILD/game_thread_text_draw_test"
"$TEST_BUILD/game_thread_text_draw_test"

g++ -std=c++17 -Wall -Wextra -Werror -Wno-unused-parameter \
  -D__stdcall= -D__fastcall= -D__cdecl= '-D__declspec(x)=' \
  -I"$ROOT/include" \
  "$ROOT/src/game/input_recorder.cpp" \
  "$ROOT/tests/input_recorder_test.cpp" \
  -o "$TEST_BUILD/input_recorder_test"
"$TEST_BUILD/input_recorder_test"

g++ -std=c++17 -Wall -Wextra -Werror \
  -I"$ROOT/include" \
  "$ROOT/src/app/game_state_init.cpp" \
  "$ROOT/tests/game_state_init_test.cpp" \
  -o "$TEST_BUILD/game_state_init_test"
"$TEST_BUILD/game_state_init_test"

g++ -std=c++17 -Wall -Wextra -Werror \
  -I"$ROOT/include" \
  "$ROOT/src/game/stage_update.cpp" \
  "$ROOT/tests/stage_update_test.cpp" \
  -o "$TEST_BUILD/stage_update_test"
"$TEST_BUILD/stage_update_test"

"$CXX" "${CXXFLAGS[@]}" \
    "$ROOT/src/game/stage_std.cpp" \
    "$ROOT/src/runtime/missing_edge.cpp" \
    "$ROOT/tests/stage_std_test.cpp" \
    -o "$TEST_BUILD/stage_std_test"
"$TEST_BUILD/stage_std_test"

"$CXX" "${CXXFLAGS[@]}" \
    "$ROOT/src/game/stage_std.cpp" \
    "$ROOT/src/game/stage_timeline.cpp" \
    "$ROOT/tests/stage_timeline_test.cpp" \
    -o "$TEST_BUILD/stage_timeline_test"
"$TEST_BUILD/stage_timeline_test"

"$CXX" "${CXXFLAGS[@]}" \
    -D__stdcall= -D__fastcall= -D__cdecl= '-D__declspec(x)=' \
    "$ROOT/src/app/main_tasks.cpp" \
    "$ROOT/src/game/manager_factories.cpp" \
    "$ROOT/src/game/message_manager_init.cpp" \
    "$ROOT/src/game/stage_tips.cpp" \
    "$ROOT/src/game/scheduler.cpp" \
    "$ROOT/src/game/entity.cpp" \
    "$ROOT/src/platform/midi_sequencer.cpp" \
    "$ROOT/src/render/anm_distance_color.cpp" \
    "$ROOT/src/runtime/missing_edge.cpp" \
    "$ROOT/tests/coverage_completion_test.cpp" \
    -o "$TEST_BUILD/coverage_completion_test"
"$TEST_BUILD/coverage_completion_test"

# Replay-score detail page (0x004329F0).
"$CXX" "${CXXFLAGS[@]}" \
    "$ROOT/src/game/replay_score_draw.cpp" \
    "$ROOT/tests/replay_score_draw_test.cpp" \
    -o "$TEST_BUILD/replay_score_draw_test"
"$TEST_BUILD/replay_score_draw_test"

# Game-state animation/overlay pass (0x00415800).
"$CXX" "${CXXFLAGS[@]}" \
    "$ROOT/src/game/game_state_overlay_draw.cpp" \
    "$ROOT/tests/game_state_overlay_draw_test.cpp" \
    -o "$TEST_BUILD/game_state_overlay_draw_test"
"$TEST_BUILD/game_state_overlay_draw_test"

# Stage focus fade updater (0x00419650).
"$CXX" "${CXXFLAGS[@]}" \
    "$ROOT/src/game/stage_focus_fade.cpp" \
    "$ROOT/tests/stage_focus_fade_test.cpp" \
    -o "$TEST_BUILD/stage_focus_fade_test"
"$TEST_BUILD/stage_focus_fade_test"

# Replay browser list/detail renderer (0x00431BA0).
"$CXX" "${CXXFLAGS[@]}" \
    "$ROOT/src/game/replay_browser_draw.cpp" \
    "$ROOT/tests/replay_browser_draw_test.cpp" \
    -o "$TEST_BUILD/replay_browser_draw_test"
"$TEST_BUILD/replay_browser_draw_test"

# Replay stage/name-entry renderer (0x00433230).
"$CXX" "${CXXFLAGS[@]}" \
    "$ROOT/src/game/replay_stage_name_draw.cpp" \
    "$ROOT/tests/replay_stage_name_draw_test.cpp" \
    -o "$TEST_BUILD/replay_stage_name_draw_test"
"$TEST_BUILD/replay_stage_name_draw_test"

# Final medium-band recovery set.
"$CXX" "${CXXFLAGS[@]}" \
    "$ROOT/src/game/bullet_runtime_update.cpp" \
    "$ROOT/src/game/menu_flow_updates.cpp" \
    "$ROOT/src/game/replay_spell_list.cpp" \
    "$ROOT/tests/medium_completion_test.cpp" \
    -o "$TEST_BUILD/medium_completion_test"
"$TEST_BUILD/medium_completion_test"

# Practice-stage selection state machine (0x00430FF0).
"$CXX" "${CXXFLAGS[@]}" \
    "$ROOT/src/game/practice_stage_menu.cpp" \
    "$ROOT/tests/practice_stage_menu_test.cpp" \
    -o "$TEST_BUILD/practice_stage_menu_test"
"$TEST_BUILD/practice_stage_menu_test"

# Runtime score-panel updater (0x00408D60).
"$CXX" "${CXXFLAGS[@]}" \
    "$ROOT/src/game/score_runtime_ui_update.cpp" \
    "$ROOT/tests/score_runtime_ui_update_test.cpp" \
    -o "$TEST_BUILD/score_runtime_ui_update_test"
"$TEST_BUILD/score_runtime_ui_update_test"

# Laser segment circle/rectangle cutters (0x0041EFA0, 0x0041EB00).
"$CXX" "${CXXFLAGS[@]}" \
    "$ROOT/src/game/laser_segment_cut.cpp" \
    "$ROOT/tests/laser_segment_cut_test.cpp" \
    -o "$TEST_BUILD/laser_segment_cut_test"
"$TEST_BUILD/laser_segment_cut_test"

# Title runtime and effect-indicator queue updates.
"$CXX" "${CXXFLAGS[@]}" \
    "$ROOT/src/game/effect_indicator_queue.cpp" \
    "$ROOT/src/game/title_menu_runtime.cpp" \
    "$ROOT/tests/large_runtime_updates_test.cpp" \
    -o "$TEST_BUILD/large_runtime_updates_test"
"$TEST_BUILD/large_runtime_updates_test"

# Replay bootstrap and result-choice state machines.
"$CXX" "${CXXFLAGS[@]}" \
    "$ROOT/src/game/replay_runtime_bootstrap.cpp" \
    "$ROOT/src/game/result_choice_menu.cpp" \
    "$ROOT/tests/replay_result_runtime_test.cpp" \
    -o "$TEST_BUILD/replay_result_runtime_test"
"$TEST_BUILD/replay_result_runtime_test"

# Name-entry and shot-practice menu completion.
"$CXX" "${CXXFLAGS[@]}" \
    "$ROOT/src/game/name_entry.cpp" \
    "$ROOT/src/game/shot_practice_menu.cpp" \
    "$ROOT/tests/menu_completion_test.cpp" \
    -o "$TEST_BUILD/menu_completion_test"
"$TEST_BUILD/menu_completion_test"

# Player runtime initializer (0x004247F0).
"$CXX" "${CXXFLAGS[@]}" \
    "$ROOT/src/game/player_runtime_init.cpp" \
    "$ROOT/src/game/scheduler.cpp" \
    "$ROOT/src/runtime/missing_edge.cpp" \
    "$ROOT/tests/player_runtime_init_test.cpp" \
    -o "$TEST_BUILD/player_runtime_init_test"
"$TEST_BUILD/player_runtime_init_test"

# Enemy-projectile spawn and replay load/save menu runtimes
# (0x004067D0, 0x004315C0, 0x00433570).
"$CXX" "${CXXFLAGS[@]}" \
    "$ROOT/src/game/enemy_projectile_spawn.cpp" \
    "$ROOT/src/game/replay_menu_runtime.cpp" \
    "$ROOT/tests/large_recovery_pass_test.cpp" \
    -o "$TEST_BUILD/large_recovery_pass_test"
"$TEST_BUILD/large_recovery_pass_test"

# Ten-function large recovery continuation.
"$CXX" "${CXXFLAGS[@]}" \
    "$ROOT/src/game/stage_tip_parser.cpp" \
    "$ROOT/src/game/event_script_runtime.cpp" \
    "$ROOT/src/game/projectile_command_runtime.cpp" \
    "$ROOT/src/game/player_front_runtime.cpp" \
    "$ROOT/src/platform/midi_event_runtime.cpp" \
    "$ROOT/src/game/replay_large_runtime.cpp" \
    "$ROOT/src/render/anchored_quad_draw.cpp" \
    "$ROOT/tests/next10_large_recovery_test.cpp" \
    -o "$TEST_BUILD/next10_large_recovery_test"
"$TEST_BUILD/next10_large_recovery_test"

# Final 15-function pass, including completion of ExecuteEcl.
# final_quad_pipeline.cpp (0x00442670) calls the recovered 0x004423C0 that
# lives in animation_manager.cpp, whose other functions reach device and
# entity edges this target does not link; --gc-sections drops them.
"$CXX" "${CXXFLAGS[@]}" -ffunction-sections -fdata-sections -Wl,--gc-sections \
    "$ROOT/src/game/ui_final_runtime.cpp" \
    "$ROOT/src/game/gameplay_final_runtime.cpp" \
    "$ROOT/src/render/final_quad_pipeline.cpp" \
    "$ROOT/src/render/animation_manager.cpp" \
    "$ROOT/src/platform/final_input_runtime.cpp" \
    "$ROOT/src/script/final_script_runtime.cpp" \
    "$ROOT/tests/final_722_recovery_test.cpp" \
    -o "$TEST_BUILD/final_722_recovery_test"
"$TEST_BUILD/final_722_recovery_test"
