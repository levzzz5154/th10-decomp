#!/bin/bash
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
ENGINE_ROOT="$ROOT/../engine"
BUILD_DIR="${TH10_STANDALONE_BUILD:-$ENGINE_ROOT/build}"
OUTPUT="$ROOT/build/th10_standalone"

cmake -S "$ENGINE_ROOT" -B "$BUILD_DIR" -DCMAKE_BUILD_TYPE=Release
cmake --build "$BUILD_DIR" --parallel

mkdir -p "$ROOT/build"
cp "$BUILD_DIR/th10" "$OUTPUT"
chmod 755 "$OUTPUT"
echo "built: $OUTPUT"
