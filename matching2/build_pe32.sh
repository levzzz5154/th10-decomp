#!/bin/bash
# Build the retail-layout standalone runner from the authoritative all-source
# PE32 image. Keeping one source set prevents the old curated runner from
# silently dropping AnimationObject_Render and descriptor ownership.
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
BUILD="$ROOT/build/pe32"

"$ROOT/build_all_pe32.sh"
mkdir -p "$BUILD"
cp -f "$ROOT/build/all-pe32/th10_all_sources.exe" \
    "$BUILD/th10_standalone.exe"
echo "built $BUILD/th10_standalone.exe from all-source PE32 runtime"
