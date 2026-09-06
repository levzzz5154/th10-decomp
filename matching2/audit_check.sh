#!/bin/bash
# Audit infrastructure and evidence freshness, not retail equivalence.
set -euo pipefail
ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
python3 "$ROOT/tests/audit_inventory_test.py"
python3 "$ROOT/tests/audit_packet_test.py"
python3 "$ROOT/tests/retail_vs_recon_stage_test.py"
python3 "$ROOT/tools/semantic_audit_manifest.py" --check
python3 "$ROOT/tools/audit_inventory.py" --check
python3 "$ROOT/tools/audit_host_contracts.py" --check
python3 "$ROOT/tools/audit_packets.py" --check
python3 "$ROOT/tools/audit_evidence.py"
python3 "$ROOT/../tools/audit_reference_corpus.py" --check
printf '%s\n' 'AUDIT_INFRASTRUCTURE_PASS (game equivalence remains unestablished)'
