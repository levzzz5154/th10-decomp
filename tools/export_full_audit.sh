#!/bin/bash
# Write a new corpus without replacing the historical 703-function export.
set -euo pipefail
ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
MODE="${1:-saved}"
case "$MODE" in
    saved) OUTPUT="${2:-$ROOT/decompiled/ghidra_full}" ;;
    augmented) OUTPUT="${2:-$ROOT/decompiled/ghidra_augmented}" ;;
    *) printf '%s\n' 'Usage: export_full_audit.sh [saved|augmented] [empty-output-directory]' >&2; exit 2 ;;
esac
if [[ -d "$OUTPUT" && -n "$(ls -A "$OUTPUT")" ]]; then
    printf '%s\n' "Output must be empty: $OUTPUT" >&2
    exit 1
fi
mkdir -p "$OUTPUT"
OUTPUT="$(cd "$OUTPUT" && pwd)"
PREPARE=()
if [[ "$MODE" == augmented ]]; then
    python3 "$ROOT/tools/audit_reference_corpus.py" --seeds "$OUTPUT/ida_starts.txt"
    python3 "$ROOT/tools/audit_reference_corpus.py" --reconstruction-seeds "$OUTPUT/reconstruction_starts.txt"
    PREPARE=(-postScript PrepareFullAudit.java "$OUTPUT/ida_starts.txt" "$OUTPUT/ida_seeds.tsv"
        -postScript PrepareFullAudit.java "$OUTPUT/reconstruction_starts.txt" "$OUTPUT/reconstruction_seeds.tsv")
fi
"${GHIDRA_HEADLESS:-/opt/ghidra/support/analyzeHeadless}" \
    "${GHIDRA_PROJECT_DIR:-$ROOT/ghidra/project}" "${GHIDRA_PROJECT_NAME:-th10}" \
    -process "${GHIDRA_PROGRAM_NAME:-th10.exe}" -noanalysis -readOnly \
    -scriptPath "$ROOT/ghidra" "${PREPARE[@]}" -postScript ExportFullAudit.java "$OUTPUT"
