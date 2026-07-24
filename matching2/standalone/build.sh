#!/bin/sh
# Build the retail-free standalone startup-to-title runner.
# Links ONLY reconstructed matching2 sources + the host platform layer.
set -e
cd "$(dirname "$0")/.."
mkdir -p build/standalone
g++ -std=c++17 -Wall -Wextra -Werror -O2 \
    -D__fastcall= \
    -Iinclude \
    standalone/host_main.cpp \
    src/app/game_main.cpp \
    src/app/game_state_init.cpp \
    src/app/frame_clock.cpp \
    src/app/main_tasks.cpp \
    src/game/task_registration.cpp \
    src/game/title_main_menu.cpp \
    src/platform/sound_commands.cpp \
    src/render/camera_setup.cpp \
    -o build/standalone/th10_standalone
echo "built build/standalone/th10_standalone"
