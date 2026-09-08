#!/bin/bash
# Host-compiler test suite: builds and runs every reconstruction test with
# g++. The recovered headers keep retail calling conventions; defining them
# away lets the same sources parse on a host compiler.
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
CXX="${CXX:-g++}"
CXXFLAGS=(-std=c++17 -Wall -Wextra -Werror "-I$ROOT/include" \
    -D__fastcall= -D__stdcall= -D__cdecl= -D__thiscall= '-D__declspec(x)=')
TEST_BUILD="$ROOT/build/tests"
mkdir -p "$TEST_BUILD"

"$ROOT/check.sh"

# Partition arguments into FLAGS (before `--`) and SOURCES (after). When no
# separator is present, every argument is a source file.
split_args() {
    FLAGS=(); SOURCES=(); local sep=0 arg
    for arg in "$@"; do
        if (( sep == 0 )) && [[ "$arg" == "--" ]]; then sep=1; continue; fi
        if (( sep == 0 )); then FLAGS+=("$arg"); else SOURCES+=("$arg"); fi
    done
    if (( sep == 0 )); then SOURCES=("${FLAGS[@]}"); FLAGS=(); fi
}

# Build and run one host test binary.
run_test() {
    local name="$1"; shift
    split_args "$@"
    "$CXX" "${CXXFLAGS[@]}" "${FLAGS[@]}" "${SOURCES[@]}" \
        -o "$TEST_BUILD/$name"
    "$TEST_BUILD/$name"
}

# The 32-bit suites need real i386 calling conventions (no -D__thiscall=),
# so they bypass the shared flags with their own g++ invocation.
run_test_m32() {
    local name="$1"; shift
    split_args "$@"
    "$CXX" -m32 -std=c++17 -Wall -Wextra -Werror \
        -D__stdcall= -D__fastcall= -D__cdecl= '-D__declspec(x)=' \
        -I"$ROOT/include" "${FLAGS[@]}" "${SOURCES[@]}" \
        -o "$TEST_BUILD/$name"
    "$TEST_BUILD/$name"
}

# Explicit source dependencies for the focused host harnesses.
source "$ROOT/tests/host_suites.sh"
