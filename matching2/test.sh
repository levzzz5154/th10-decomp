#!/bin/bash
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
TEST_BUILD="$ROOT/build/tests"
mkdir -p "$TEST_BUILD"

g++ -std=c++17 -Wall -Wextra -Werror \
    -D__stdcall= -D__fastcall= -D__cdecl= \
    -I"$ROOT/include" \
    "$ROOT/src/archive/lzss.cpp" \
    "$ROOT/tests/lzss_test.cpp" \
    -o "$TEST_BUILD/lzss_test"

"$TEST_BUILD/lzss_test"
