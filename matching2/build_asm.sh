#!/usr/bin/env bash
# Assemble the full text section and package the supported byte-exact PE.
set -euo pipefail
ROOT="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)"
if (( $# != 0 )) && { (( $# != 2 )) || [[ "$1" != "--verify" ]]; }; then
    echo "Usage: $0 [--verify /path/to/retail/th10.exe]" >&2
    exit 2
fi
rm -f -- "$ROOT/build/asm-baseline/full/th10.exe"
python3 "$ROOT/tools/matching/build_asm_text.py" "$@"
python3 "$ROOT/tools/matching/pack_asm_pe.py" \
    --text "$ROOT/build/asm-baseline/full/text.bin" \
    --output "$ROOT/build/asm-baseline/full/th10.exe" "$@"
