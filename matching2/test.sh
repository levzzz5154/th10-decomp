#!/bin/bash
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
TEST_BUILD="$ROOT/build/tests"
mkdir -p "$TEST_BUILD"

python3 "$ROOT/tools/function_registry.py" --check
python3 "$ROOT/tools/standalone_readiness.py" --check

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
    "$ROOT/src/game/scheduler.cpp" \
    "$ROOT/src/game/stage_text.cpp" \
    "$ROOT/src/render/animation_manager.cpp" \
    "$ROOT/tests/game_runtime_test.cpp" \
    -o "$TEST_BUILD/game_runtime_test"

"$TEST_BUILD/game_runtime_test"

g++ -std=c++17 -Wall -Wextra -Werror \
    -D__stdcall= -D__fastcall= -D__cdecl= '-D__declspec(x)=' \
    -I"$ROOT/include" \
    "$ROOT/src/game/score.cpp" \
    "$ROOT/tests/score_runtime_test.cpp" \
    -o "$TEST_BUILD/score_runtime_test"

"$TEST_BUILD/score_runtime_test"

g++ -std=c++17 -Wall -Wextra -Werror \
    -D__stdcall= -D__fastcall= -D__cdecl= '-D__declspec(x)=' \
    -I"$ROOT/include" \
    "$ROOT/src/render/d3d_resource_manager.cpp" \
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
    "$ROOT/tests/file_resource_test.cpp" \
    -o "$TEST_BUILD/file_resource_test"

"$TEST_BUILD/file_resource_test"

g++ -std=c++17 -Wall -Wextra -Werror \
    -D__stdcall= -D__fastcall= -D__cdecl= '-D__declspec(x)=' \
    -I"$ROOT/include" \
    "$ROOT/src/platform/process.cpp" \
    "$ROOT/src/platform/text_log.cpp" \
    "$ROOT/src/platform/win32_timer.cpp" \
    "$ROOT/tests/process_test.cpp" \
    -o "$TEST_BUILD/process_test"

"$TEST_BUILD/process_test"

g++ -std=c++17 -Wall -Wextra -Werror \
    -D__stdcall= -D__fastcall= -D__cdecl= '-D__declspec(x)=' \
    -I"$ROOT/include" \
    "$ROOT/src/game/recovery_leaves.cpp" \
    "$ROOT/tests/recovery_leaves_test.cpp" \
    -o "$TEST_BUILD/recovery_leaves_test"

"$TEST_BUILD/recovery_leaves_test"

g++ -std=c++17 -Wall -Wextra -Werror \
    -D__stdcall= -D__fastcall= -D__cdecl= '-D__declspec(x)=' \
    -I"$ROOT/include" \
    "$ROOT/src/script/ecl_vm.cpp" \
    "$ROOT/src/script/ecl_helpers.cpp" \
    "$ROOT/src/game/recovery_leaves.cpp" \
    "$ROOT/tests/ecl_vm_test.cpp" \
    -o "$TEST_BUILD/ecl_vm_test"

"$TEST_BUILD/ecl_vm_test"

g++ -std=c++17 -Wall -Wextra -Werror \
    -I"$ROOT/include" \
    "$ROOT/src/script/entity_vm.cpp" \
    "$ROOT/tests/entity_vm_test.cpp" \
    -o "$TEST_BUILD/entity_vm_test"

"$TEST_BUILD/entity_vm_test"

g++ -std=c++17 -Wall -Wextra -Werror \
    -D__stdcall= -D__fastcall= -D__cdecl= '-D__declspec(x)=' \
    -I"$ROOT/include" \
    "$ROOT/src/script/ecl_helpers.cpp" \
    "$ROOT/tests/ecl_helpers_test.cpp" \
    -o "$TEST_BUILD/ecl_helpers_test"

"$TEST_BUILD/ecl_helpers_test"

g++ -std=c++17 -Wall -Wextra -Werror \
    -I"$ROOT/include" \
    "$ROOT/src/script/prng.cpp" \
    "$ROOT/tests/prng_test.cpp" \
    -o "$TEST_BUILD/prng_test"

"$TEST_BUILD/prng_test"

# GameState stores 32-bit retail pointers in its ABI fields, so exercise its
# device-failure state transitions in a 32-bit host binary.
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
    "$ROOT/tests/bullet_manager_test.cpp" \
    -o "$TEST_BUILD/bullet_manager_test"

"$TEST_BUILD/bullet_manager_test"

g++ -std=c++17 -Wall -Wextra -Werror \
    -D__stdcall= -D__fastcall= -D__cdecl= '-D__declspec(x)=' \
    -I"$ROOT/include" \
    "$ROOT/src/game/game_thread_queue.cpp" \
    "$ROOT/tests/game_thread_queue_test.cpp" \
    -o "$TEST_BUILD/game_thread_queue_test"

"$TEST_BUILD/game_thread_queue_test"

g++ -std=c++17 -Wall -Wextra -Werror \
    -D__stdcall= -D__fastcall= -D__cdecl= '-D__declspec(x)=' \
    -I"$ROOT/include" \
    "$ROOT/src/game/player_scheduler.cpp" \
    "$ROOT/tests/player_scheduler_test.cpp" \
    -o "$TEST_BUILD/player_scheduler_test"

"$TEST_BUILD/player_scheduler_test"
