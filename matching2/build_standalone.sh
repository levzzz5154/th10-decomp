#!/bin/bash
# Build the retail-free standalone startup-to-title runner.
# Delegates to standalone/build.sh, which links ONLY reconstructed
# matching2 sources plus the host platform layer in standalone/host_main.cpp.
set -euo pipefail
ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
"$ROOT/standalone/build.sh"
