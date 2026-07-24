#!/bin/sh
# Build the retail-free standalone startup-to-title runner.
# Links ONLY reconstructed matching2 sources + the host platform layer.
set -e
cd "$(dirname "$0")/.."
mkdir -p build/standalone
g++ -std=c++17 -Wall -Wextra -Werror -O2 \
    -D__fastcall= -D__stdcall= -D__cdecl= '-D__declspec(x)=' \
    -Iinclude \
    standalone/host_main.cpp \
    standalone/host_stage.cpp \
    src/app/game_main.cpp \
    src/app/game_state_init.cpp \
    src/app/frame_clock.cpp \
    src/app/main_tasks.cpp \
    src/game/task_registration.cpp \
    src/game/title_main_menu.cpp \
    src/game/title_options_menu.cpp \
    src/game/stage_entry.cpp \
    src/game/stage_std.cpp \
    src/game/stage_update.cpp \
    src/game/game_mode_switch.cpp \
    src/game/scheduler.cpp \
    src/game/manager_factories.cpp \
    src/game/object_factories.cpp \
    src/game/recovery_leaves.cpp \
    src/game/bullet_manager.cpp \
    src/script/stage_ecl_load.cpp \
    src/archive/dat.cpp \
    src/archive/dat_file.cpp \
    src/archive/crypt.cpp \
    src/archive/lzss.cpp \
    src/archive/resource_manager.cpp \
    src/platform/path.cpp \
    src/platform/pack_file_loader.cpp \
    src/platform/memory_file.cpp \
    src/platform/resource_file.cpp \
    src/platform/sound_commands.cpp \
    src/render/anm_file.cpp \
    src/render/camera_setup.cpp \
    -o build/standalone/th10_standalone
echo "built build/standalone/th10_standalone"
