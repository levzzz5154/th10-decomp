#!/bin/bash
# Current source reports and reference integrity; does not run the game.
set -euo pipefail
ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
python3 "$ROOT/tests/progress_evidence_test.py"
python3 "$ROOT/tools/runtime/coverage_report.py" --check
python3 "$ROOT/tools/runtime/function_registry.py" --check
python3 "$ROOT/tools/runtime/standalone_readiness.py" --check
python3 "$ROOT/../tools/audit_reference_corpus.py" --check
