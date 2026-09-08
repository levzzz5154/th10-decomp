#!/bin/bash
# Run the all-production-source PE32 integration-audit image under Wine.
# `--menu-smoke` is a deterministic host-driven title-menu flow; it does not
# require --input or physical keyboard input.
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
EXE="$ROOT/build/all-pe32/th10_all_sources.exe"
GAME_DIR="${TH10_GAME_DIR:-$HOME/Games/TH10 - Mountain of Faith}"

if [[ ! -f "$EXE" ]]; then
    "$ROOT/build.sh"
fi
for archive in th10.dat thbgm.dat; do
    if [[ ! -f "$GAME_DIR/$archive" ]]; then
        echo "Original TH10 archive was not found: $GAME_DIR/$archive" >&2
        exit 1
    fi
    ln -sfn "$GAME_DIR/$archive" "$ROOT/build/all-pe32/$archive"
done

cd "$ROOT/build/all-pe32"
exec env WINEDEBUG="${WINEDEBUG:--all}" wine "$EXE" "$@"
