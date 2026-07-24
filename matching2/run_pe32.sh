#!/bin/bash
# Run the retail-free PE32 startup-to-title harness under Wine.
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
EXE="$ROOT/build/pe32/th10_standalone.exe"

if [[ ! -f "$EXE" ]]; then
    "$ROOT/build_pe32.sh"
fi

exec env WINEDEBUG="${WINEDEBUG:--all}" wine "$EXE" "$@"
