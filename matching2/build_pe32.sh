#!/bin/bash
# Build the retail-free startup-to-title harness as a self-contained PE32.
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
BUILD="$ROOT/build/pe32"
TOOLCHAIN_ROOT="${LLVM_MINGW_ROOT:-/opt/llvm-mingw}"
COMPILER="${TH10_PE32_CXX:-$TOOLCHAIN_ROOT/bin/i686-w64-mingw32-g++}"

if [[ ! -x "$COMPILER" ]]; then
    echo "LLVM-MinGW i686 compiler not found: $COMPILER" >&2
    echo "Install llvm-mingw or set LLVM_MINGW_ROOT/TH10_PE32_CXX." >&2
    exit 1
fi

mkdir -p "$BUILD"
"$COMPILER" -std=c++17 -Wall -Wextra -Werror -O2 -static \
    -I"$ROOT/include" \
    "$ROOT/standalone/host_main.cpp" \
    "$ROOT/src/app/game_main.cpp" \
    "$ROOT/src/app/game_state_init.cpp" \
    "$ROOT/src/app/frame_clock.cpp" \
    "$ROOT/src/app/main_tasks.cpp" \
    "$ROOT/src/game/task_registration.cpp" \
    "$ROOT/src/platform/sound_commands.cpp" \
    "$ROOT/src/render/camera_setup.cpp" \
    -o "$BUILD/th10_standalone.exe"

echo "built $BUILD/th10_standalone.exe"
