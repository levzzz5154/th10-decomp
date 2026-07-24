#!/bin/bash
# Run the retail-free PE32 startup-to-title harness under Wine.
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
EXE="$ROOT/build/pe32/th10_standalone.exe"
GAME_DIR="${TH10_GAME_DIR:-$HOME/Games/TH10 - Mountain of Faith}"

if [[ ! -f "$EXE" ]]; then
    "$ROOT/build_pe32.sh"
fi
if [[ ! -f "$GAME_DIR/th10.dat" ]]; then
    echo "Original TH10 archive was not found in: $GAME_DIR" >&2
    exit 1
fi
if [[ ! -f "$GAME_DIR/thbgm.dat" ]]; then
    echo "Original TH10 BGM archive was not found in: $GAME_DIR" >&2
    exit 1
fi

cd "$ROOT/build/pe32"
ln -sfn "$GAME_DIR/th10.dat" th10.dat
ln -sfn "$GAME_DIR/thbgm.dat" thbgm.dat
exec env WINEDEBUG="${WINEDEBUG:--all}" wine "$EXE" "$@"
