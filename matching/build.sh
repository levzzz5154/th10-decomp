#!/bin/bash
# ================================================================
# th10.exe Matching Decompilation Build Script
# Uses MSVC 7.1 (Visual C++ Toolkit 2003) via Wine
#
# Usage:
#   ./build.sh --compile    Compile all .cpp files in src/
#   ./build.sh --link       Link into th10_rebuilt.exe
#   ./build.sh --compare    Compare disassembly against original
#   ./build.sh --source X   Compile a single file
#   ./build.sh              Compile + link + compare
# ================================================================

set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="${SCRIPT_DIR}"
SRC_DIR="${PROJECT_ROOT}/src"
INCLUDE_DIR="${PROJECT_ROOT}/include"
STUBS_DIR="${PROJECT_ROOT}/stubs"
BUILD_DIR="${PROJECT_ROOT}/build"

# MSVC 7.1 Toolkit paths (under Wine)
MSVC_BASE="${HOME}/.wine/drive_c/Program Files (x86)/Microsoft Visual C++ Toolkit 2003"
CL_EXE="${MSVC_BASE}/bin/cl.exe"
LINK_EXE="${MSVC_BASE}/bin/link.exe"
LIBCMT="${MSVC_BASE}/lib/libcmt.lib"
MSVC_INCLUDE="${MSVC_BASE}/include"

# Wine settings
WINE="wine"
export WINEDEBUG="-all"

# Compiler flags: match original th10.exe build
# cl.exe 13.10.3077, /O2 /Gz /MT /Gy /G6
# /Gz = stdcall default (used by th10)
CL_FLAGS="/nologo /c /O2 /Gz /MT /Gy /G6 /GF"

# Original EXE for comparison
ORIG_EXE="${ORIG_EXE:-${HOME}/Games/TH10 - Mountain of Faith/th10.exe}"

# ---------------------------------------------------------------
# Helpers
# ---------------------------------------------------------------
info()  { echo "[INFO]  $*" >&2; }
err()   { echo "[ERROR] $*" >&2; }

wpath() {
    # Convert Unix path to Windows path for Wine
    winepath -w "$1" 2>/dev/null || echo "Z:${1//\//\\}"
}

check_msvc() {
    if [ ! -f "${CL_EXE}" ]; then
        err "MSVC cl.exe not found at: ${CL_EXE}"
        err "Install Visual C++ Toolkit 2003 and try again."
        exit 1
    fi
    if [ ! -f "${LIBCMT}" ]; then
        err "libcmt.lib not found at: ${LIBCMT}"
        exit 1
    fi
    info "cl.exe:  $(wpath "${CL_EXE}")"
    info "libcmt:   $(wpath "${LIBCMT}")"
}

find_sources() {
    find "${SRC_DIR}" -name "*.cpp" -type f | sort
}

find_stubs() {
    if [ -d "${STUBS_DIR}" ]; then
        find "${STUBS_DIR}" -name "*.cpp" -o -name "*.c" -type f | sort
    fi
}

# ---------------------------------------------------------------
# Compile
# ---------------------------------------------------------------
compile_one() {
    local cpp_file="$1"
    local base_name
    base_name="$(basename "${cpp_file}" .cpp)"
    local obj_file="${BUILD_DIR}/${base_name}.obj"
    local asm_file="${BUILD_DIR}/${base_name}.asm"

    info "Compiling ${base_name}.cpp"

    "${WINE}" "$(wpath "${CL_EXE}")" \
        ${CL_FLAGS} \
        "/I$(wpath "${INCLUDE_DIR}")" \
        "/I$(wpath "${MSVC_INCLUDE}")" \
        "/Fo$(wpath "${obj_file}")" \
        "/FAsc" \
        "/Fa$(wpath "${asm_file}")" \
        "$(wpath "${cpp_file}")" >&2

    local ret=$?
    if [ ${ret} -ne 0 ]; then
        err "Compilation failed for ${cpp_file}"
        return 1
    fi
    echo "${obj_file}"
}

compile_all() {
    echo "=== Compile ==="
    mkdir -p "${BUILD_DIR}"

    local sources
    mapfile -t sources < <(find_sources)
    if [ ${#sources[@]} -eq 0 ]; then
        err "No .cpp files found in ${SRC_DIR}"
        return 1
    fi
    info "Found ${#sources[@]} source(s)"

    local objs=()
    for src in "${sources[@]}"; do
        objs+=("$(compile_one "${src}")") || return 1
    done

    local stubs
    mapfile -t stubs < <(find_stubs)
    for stub in "${stubs[@]}"; do
        objs+=("$(compile_one "${stub}")") || return 1
    done

    printf "%s\n" "${objs[@]}" > "${BUILD_DIR}/objects.txt"
    info "Compiled ${#objs[@]} objects"
}

# ---------------------------------------------------------------
# Link
# ---------------------------------------------------------------
link_all() {
    echo "=== Link ==="

    # The link step requires Platform SDK libraries (user32.lib, gdi32.lib, etc.)
    # These are NOT included with the VC++ Toolkit 2003.
    # Install the Windows Server 2003 Platform SDK or .NET Framework 1.1 SDK.

    err "Linking requires Platform SDK (user32.lib, gdi32.lib, advapi32.lib)"
    err "The MSVC Toolkit 2003 only includes kernel32.lib and CRT libs."
    err ""
    err "For matching decompilation, compare .obj sections against the"
    err "original binary using: ./build.sh --compare"
    return 1
}

# ---------------------------------------------------------------
# Compare
# ---------------------------------------------------------------
compare_bytes() {
    echo "=== Compare ==="

    local out_exe="${BUILD_DIR}/th10_rebuilt.exe"
    if [ ! -f "${out_exe}" ]; then
        err "No rebuilt EXE. Compile and link first."
        return 1
    fi
    if [ ! -f "${ORIG_EXE}" ]; then
        err "Original EXE not found at: ${ORIG_EXE}"
        info "Set ORIG_EXE env var or place th10.exe in the expected location"
        return 1
    fi

    python3 -c "
import struct

def read_text_section(path):
    with open(path, 'rb') as f:
        f.seek(0x3C)
        pe_off = struct.unpack('<I', f.read(4))[0]
        f.seek(pe_off)
        if f.read(4) != b'PE\x00\x00':
            return None
        fh = f.read(20)
        ns = struct.unpack('<H', fh[2:4])[0]
        ohs = struct.unpack('<H', fh[16:18])[0]
        f.read(ohs)
        for _ in range(ns):
            name = f.read(8).rstrip(b'\x00')
            vs = struct.unpack('<I', f.read(4))[0]
            va = struct.unpack('<I', f.read(4))[0]
            rs = struct.unpack('<I', f.read(4))[0]
            ro = struct.unpack('<I', f.read(4))[0]
            f.read(16)
            if name == b'.text':
                f.seek(ro)
                return f.read(rs)
    return None

orig = read_text_section('${ORIG_EXE}')
rebuilt = read_text_section('${out_exe}')

if orig is None:
    print('Failed to read original .text')
    exit(1)

entry_rva = 0x4537DC - 0x00400000
entry_size = 0x1D4

if rebuilt is None:
    print('Failed to read rebuilt .text')
else:
    print(f'Original  .text: {len(orig)} bytes')
    print(f'Rebuilt   .text: {len(rebuilt)} bytes')

if rebuilt is not None and len(rebuilt) > entry_rva:
    r = rebuilt[entry_rva:entry_rva+entry_size]
    o = orig[entry_rva:entry_rva+entry_size]
    m = sum(1 for a,b in zip(o,r) if a==b)
    t = max(len(o),len(r))
    print(f'Entry match: {m}/{t} bytes ({m/t*100:.1f}%)')
else:
    # Show a few instruction bytes from original for reference
    chunk = orig[entry_rva:entry_rva+32]
    hx = chunk.hex() if hasattr(chunk, 'hex') else ''.join(f'{b:02x}' for b in chunk)
    print(f'Original entry bytes: {hx}')
"
    local ret=$?
    return ${ret}
}

show_asm() {
    local asm_file="${BUILD_DIR}/entry.asm"
    if [ -f "${asm_file}" ]; then
        echo "=== Disassembly ==="
        head -120 "${asm_file}"
    fi
}

# ---------------------------------------------------------------
# Main
# ---------------------------------------------------------------
usage() {
    cat << 'EOF'
Usage: build.sh [options]

Options:
  --compile     Compile all .cpp files in src/ to .obj + .asm
  --link        Link objects into th10_rebuilt.exe
  --compare     Binary comparison against original th10.exe
  --source SRC  Compile a single source file
  --asm         Show generated assembly for entry.obj
  -h, --help    Show this help

Environment:
  ORIG_EXE      Path to original th10.exe
EOF
}

main() {
    local mode="all"

    while [[ $# -gt 0 ]]; do
        case "$1" in
            --compile) mode="compile"; shift ;;
            --link)    mode="link"; shift ;;
            --compare) mode="compare"; shift ;;
            --asm)     mode="asm"; shift ;;
            --source)  mode="single"; single_src="$2"; shift 2 ;;
            -h|--help) usage; exit 0 ;;
            *)         err "Unknown option: $1"; usage; exit 1 ;;
        esac
    done

    check_msvc

    case "${mode}" in
        compile)  compile_all ;;
        link)     link_all ;;
        compare)  compare_bytes ;;
        asm)      show_asm ;;
        all)      compile_all && link_all && compare_bytes ;;
        single)   compile_one "${single_src}" ;;
    esac
}

main "$@"
