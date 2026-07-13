#!/bin/bash
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
GAME_DIR="${TH10_GAME_DIR:-$HOME/Games/TH10 - Mountain of Faith}"

if [[ ! -f "$ROOT/build/th10_reimpl.exe" ]]; then
    "$ROOT/build.sh"
fi
if [[ ! -f "$GAME_DIR/th10.dat" || ! -f "$GAME_DIR/thbgm.dat" ]]; then
    echo "Original TH10 assets were not found in: $GAME_DIR" >&2
    exit 1
fi

# The retail game derives its archive paths from the executable's directory,
# not from the process working directory. Keep the 430 MB of original archives
# in place and expose them beside the rebuilt image through symlinks.
ln -sfn "$GAME_DIR/th10.dat" "$ROOT/build/th10.dat"
ln -sfn "$GAME_DIR/thbgm.dat" "$ROOT/build/thbgm.dat"
if [[ -f "$GAME_DIR/th10.cfg" ]]; then
    ln -sfn "$GAME_DIR/th10.cfg" "$ROOT/build/th10.cfg"
fi
mkdir -p "$ROOT/build/replay" "$ROOT/build/snapshot"

cd "$ROOT/build"
exec env WINEDEBUG="${WINEDEBUG:--all}" wine "$ROOT/build/th10_reimpl.exe"
