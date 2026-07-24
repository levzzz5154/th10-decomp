#!/bin/bash
# Run the retail-free standalone runner (startup-to-title smoke milestone).
# No retail executable, hybrid image, or game data is required: the host
# layer provides stub device/sound services and the reconstructed code
# drives the boot flow through title task registration.
set -euo pipefail
ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
if [[ ! -x "$ROOT/build/standalone/th10_standalone" ]]; then
    "$ROOT/standalone/build.sh"
fi
exec "$ROOT/build/standalone/th10_standalone" "$@"
