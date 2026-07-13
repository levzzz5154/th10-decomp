#!/bin/bash
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
BUILD="$ROOT/build"
ORIGINAL="${TH10_ORIGINAL_EXE:-$HOME/Games/TH10 - Mountain of Faith/th10.exe}"
CL="$HOME/.wine/drive_c/Program Files (x86)/Microsoft Visual C++ Toolkit 2003/bin/cl.exe"

mkdir -p "$BUILD"
export WINEDEBUG=-all

wine "$CL" /nologo /c /O2 /Gz /MT /Gy /G6 /GF \
    "/I$(winepath -w "$ROOT/include")" \
    "/Fo$(winepath -w "$BUILD/entity.obj")" \
    "$(winepath -w "$ROOT/src/game/entity.cpp")"

wine "$CL" /nologo /c /O2 /Gz /MT /Gy /G6 /GF \
    "/I$(winepath -w "$ROOT/include")" \
    "/Fo$(winepath -w "$BUILD/score.obj")" \
    "$(winepath -w "$ROOT/src/game/score.cpp")"

python3 "$ROOT/tools/build_hybrid.py" \
    --original "$ORIGINAL" \
    --objects "$BUILD" \
    --output "$BUILD/th10_reimpl.exe"
