#!/bin/bash
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
HEADLESS="${GHIDRA_HEADLESS:-/opt/ghidra/support/analyzeHeadless}"
PROJECT_DIR="${GHIDRA_PROJECT_DIR:-$ROOT/ghidra/project}"
PROJECT_NAME="${GHIDRA_PROJECT_NAME:-th10}"
PROGRAM_NAME="${GHIDRA_PROGRAM_NAME:-th10.exe}"
OUTPUT="${GHIDRA_DECOMPILED_OUTPUT:-$ROOT/decompiled/ghidra_raw}"

mkdir -p "$OUTPUT"
find "$OUTPUT" -maxdepth 1 -type f \( -name '*.c' -o -name 'index.tsv' \) -delete

"$HEADLESS" "$PROJECT_DIR" "$PROJECT_NAME" \
    -process "$PROGRAM_NAME" \
    -noanalysis \
    -readOnly \
    -scriptPath "$ROOT/ghidra" \
    -postScript ExportGameFunctions.java "$ROOT/matching/tracking.csv" "$OUTPUT"
