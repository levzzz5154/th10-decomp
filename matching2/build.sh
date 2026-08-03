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
    src/game/progress.cpp
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
