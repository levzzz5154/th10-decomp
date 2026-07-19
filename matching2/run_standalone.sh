#!/bin/bash
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
GAME_DIR="${TH10_GAME_DIR:-$HOME/Games/TH10 - Mountain of Faith}"

if [[ ! -x "$ROOT/build/th10_standalone" ]]; then
    "$ROOT/build_standalone.sh"
fi
if [[ ! -f "$GAME_DIR/th10.dat" ]]; then
    echo "TH10 data archive was not found: $GAME_DIR/th10.dat" >&2
    echo "Set TH10_GAME_DIR to the directory containing th10.dat." >&2
    exit 1
fi

cd "$ROOT/build"
exec "$ROOT/build/th10_standalone" --game-dir "$GAME_DIR" "$@"
