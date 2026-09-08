#!/bin/bash
# Current source reports and reference integrity; does not run the game.
set -euo pipefail
ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
python3 "$ROOT/tests/progress_evidence_test.py"
python3 "$ROOT/tools/coverage_report.py" --check
python3 "$ROOT/tools/function_registry.py" --check
python3 "$ROOT/tools/standalone_readiness.py" --check
python3 "$ROOT/../tools/audit_reference_corpus.py" --check
