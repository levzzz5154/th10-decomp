#!/bin/bash
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
BUILD="$ROOT/build"
ORIGINAL="${TH10_ORIGINAL_EXE:-$HOME/Games/TH10 - Mountain of Faith/th10.exe}"
CL="$HOME/.wine/drive_c/Program Files (x86)/Microsoft Visual C++ Toolkit 2003/bin/cl.exe"

mkdir -p "$BUILD"
export WINEDEBUG=-all

declare -A object_names
while IFS= read -r source; do
    base="$(basename "$source" .cpp)"
    if [[ -n "${object_names[$base]:-}" ]]; then
        echo "Duplicate source basename '$base':" >&2
        echo "  ${object_names[$base]}" >&2
        echo "  $source" >&2
        exit 1
    fi
    object_names[$base]="$source"
    wine "$CL" /nologo /c /O2 /Gz /MT /Gy /G6 /GF \
        "/I$(winepath -w "$ROOT/include")" \
        "/Fo$(winepath -w "$BUILD/$base.obj")" \
        "$(winepath -w "$source")"
done < <(find "$ROOT/src" -name '*.cpp' -type f | sort)

python3 "$ROOT/tools/build_hybrid.py" \
    --original "$ORIGINAL" \
    --objects "$BUILD" \
    --output "$BUILD/th10_reimpl.exe"
