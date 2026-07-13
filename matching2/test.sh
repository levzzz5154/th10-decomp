#!/bin/bash
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
TEST_BUILD="$ROOT/build/tests"
mkdir -p "$TEST_BUILD"

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
    "$ROOT/tests/archive_test.cpp" \
    -o "$TEST_BUILD/archive_test"

"$TEST_BUILD/archive_test"

g++ -std=c++17 -Wall -Wextra -Werror \
    -D__stdcall= -D__fastcall= -D__cdecl= '-D__declspec(x)=' \
    -I"$ROOT/include" \
    "$ROOT/src/game/scheduler.cpp" \
    "$ROOT/tests/scheduler_test.cpp" \
    -o "$TEST_BUILD/scheduler_test"

"$TEST_BUILD/scheduler_test"

g++ -std=c++17 -Wall -Wextra -Werror \
    -D__stdcall= -D__fastcall= -D__cdecl= '-D__declspec(x)=' \
    -I"$ROOT/include" \
    "$ROOT/src/math/timer.cpp" \
    "$ROOT/src/render/animation_manager.cpp" \
    "$ROOT/tests/game_runtime_test.cpp" \
    -o "$TEST_BUILD/game_runtime_test"

"$TEST_BUILD/game_runtime_test"
