#!/bin/bash
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
BUILD="$ROOT/build"
ORIGINAL="${TH10_ORIGINAL_EXE:-$HOME/Games/TH10 - Mountain of Faith/th10.exe}"
CL="$HOME/.wine/drive_c/Program Files (x86)/Microsoft Visual C++ Toolkit 2003/bin/cl.exe"
TOOLKIT="$HOME/.wine/drive_c/Program Files (x86)/Microsoft Visual C++ Toolkit 2003"

mkdir -p "$BUILD"
export WINEDEBUG=-all
export INCLUDE="$(winepath -w "$TOOLKIT/include")"
export LIB="$(winepath -w "$TOOLKIT/lib")"

# The hybrid builder only needs the translation units that provide the
# currently verified overlays. The rest of the tree uses C++11 features and is
# built by the PE32 standalone target with LLVM-MinGW (build_all_pe32.sh).
OVERLAY_SOURCES=(
    src/game/entity.cpp
    src/game/bullet.cpp
    src/util/heap.cpp
    src/platform/file.cpp
    src/platform/memory_file.cpp
    src/platform/resource_file.cpp
    src/util/runtime_pool.cpp
    src/math/angle.cpp
    src/math/rng.cpp
    src/math/vector.cpp
    src/math/timer.cpp
    src/math/math_utils.cpp
    src/game/scheduler.cpp
    src/game/player.cpp
    src/game/player_motion.cpp
    src/game/stage_text.cpp
    src/game/game_thread_queue.cpp
    src/game/game_thread_overlay.cpp
    src/game/progress.cpp
    src/game/progress_worker.cpp
    src/archive/dat.cpp
    src/render/animation_manager.cpp
    src/render/d3d_resource_manager.cpp
    src/game/score.cpp
    src/script/ecl_vm.cpp
    src/platform/sound_float_forward.cpp
    src/platform/path.cpp
    src/platform/process.cpp
    src/platform/win32_timer.cpp
    src/game/recovery_leaves.cpp
    src/game/stage_tips.cpp
    src/platform/sound_stream_start.cpp
    src/platform/sound_commands.cpp
    src/platform/text_log.cpp
    src/platform/joystick_property_overlay.cpp
    src/game/archive_cursor_open.cpp
    src/game/archive_cursor.cpp
    src/game/archive_cursor_read.cpp
    src/game/menu.cpp
    src/script/ecl_vm_children.cpp
    src/game/weather_pool.cpp
    src/math/random_vector.cpp
    src/render/quad_vertex_append.cpp
    src/render/anm_batch_flush.cpp
    src/render/edge_strips.cpp
    src/render/anm_texture_upload.cpp
    src/app/fps_counter.cpp
    src/game/faith_gauge.cpp
    src/render/animation_slot.cpp
    src/game/boss_overlays.cpp
    src/platform/gdi_font_cache.cpp
    src/game/game_ui_create.cpp
    src/game/stage_tip_manager.cpp
    src/game/frame_counter.cpp
    src/game/effect_indicator_slots.cpp
    src/game/slot_lock_leaves.cpp
    src/game/player_scheduler.cpp
    src/game/score_file.cpp
    src/game/manager_factories.cpp
    src/game/task_registration.cpp
    src/game/manager_teardown.cpp
    src/game/ascii_overlay_callbacks_overlay.cpp
    src/game/bullet_manager_overlay.cpp
    src/game/music_room_overlay.cpp
    src/render/camera_setup.cpp
    src/platform/window.cpp
    src/render/render_stage_select.cpp
    src/game/stage_background_overlay.cpp
    src/game/enemy_drop_sweep.cpp
    src/game/enemy_grid_scan_overlay.cpp
    src/platform/midi_worker_overlay.cpp
    src/game/main_menu_dispatch_overlay.cpp
    src/platform/sound_leaves.cpp
    src/platform/sound_dummy.cpp
    src/platform/midi_worker_stop.cpp
    src/archive/dat_file.cpp
    src/game/game_config_defaults.cpp
    src/script/prng.cpp
    src/math/vector3_cross.cpp
    src/game/particle_seed.cpp
    src/game/score_timer_leaves.cpp
)

for source in "${OVERLAY_SOURCES[@]}"; do
    base="$(basename "$source" .cpp)"
    wine "$CL" /nologo /c /O2 /Gz /MT /Gy /G6 /GF \
        "/I$(winepath -w "$ROOT/include")" \
        "/Fo$(winepath -w "$BUILD/$base.obj")" \
        "$(winepath -w "$ROOT/$source")"
done

python3 "$ROOT/tools/build_hybrid.py" \
    --original "$ORIGINAL" \
    --objects "$BUILD" \
    --output "$BUILD/th10_reimpl.exe"
