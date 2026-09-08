#!/bin/bash
# Compile every matching2 production translation unit into one PE32 image.
#
# This is an integration-audit target. Every project function edge must have a
# real definition; the build fails instead of manufacturing callable storage.
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
BUILD="$ROOT/build/all-pe32"
TOOLCHAIN_ROOT="${LLVM_MINGW_ROOT:-/opt/llvm-mingw}"

# Prefer an explicit override, then a native prefixed MinGW installation, and
# finally the historical LLVM-MinGW directory layout.
resolve_tool() {
    local override="$1"
    local system_name="$2"
    local legacy_path="$3"
    local resolved

    if [[ -n "$override" ]]; then
        if [[ "$override" == */* ]]; then
            printf '%s\n' "$override"
        elif resolved="$(command -v "$override")"; then
            printf '%s\n' "$resolved"
        else
            return 1
        fi
        return 0
    fi
    if resolved="$(command -v "$system_name")"; then
        printf '%s\n' "$resolved"
    elif [[ -x "$legacy_path" ]]; then
        printf '%s\n' "$legacy_path"
    else
        return 1
    fi
}

CXX="$(resolve_tool "${TH10_PE32_CXX:-}" i686-w64-mingw32-g++ \
    "$TOOLCHAIN_ROOT/bin/i686-w64-mingw32-g++")" || {
    echo "required PE32 C++ compiler not found; set TH10_PE32_CXX or LLVM_MINGW_ROOT" >&2
    exit 1
}
CC="$(resolve_tool "${TH10_PE32_CC:-}" i686-w64-mingw32-gcc \
    "$TOOLCHAIN_ROOT/bin/i686-w64-mingw32-gcc")" || {
    echo "required PE32 C compiler not found; set TH10_PE32_CC or LLVM_MINGW_ROOT" >&2
    exit 1
}
NM="$(resolve_tool "${TH10_PE32_NM:-}" i686-w64-mingw32-nm \
    "$TOOLCHAIN_ROOT/bin/llvm-nm")" || {
    echo "required PE32 symbol tool not found; set TH10_PE32_NM or LLVM_MINGW_ROOT" >&2
    exit 1
}
WINDRES="$(resolve_tool "${TH10_PE32_WINDRES:-}" i686-w64-mingw32-windres \
    "$TOOLCHAIN_ROOT/bin/i686-w64-mingw32-windres")" || {
    echo "required PE32 resource compiler not found; set TH10_PE32_WINDRES or LLVM_MINGW_ROOT" >&2
    exit 1
}
GAME_DIR="${TH10_GAME_DIR:-$HOME/Games/TH10 - Mountain of Faith}"
RETAIL_EXE="${TH10_RETAIL_EXE:-$GAME_DIR/th10.exe}"

for tool in "$CXX" "$CC" "$NM" "$WINDRES"; do
    if [[ ! -x "$tool" ]]; then
        echo "required PE32 tool is not executable: $tool" >&2
        exit 1
    fi
done

mkdir -p "$BUILD/objects"
# The unresolved inventory is computed from production/host objects only.
find "$BUILD/objects" -type f -delete
find "$ROOT/src" -type f -name '*.cpp' -print | sort > "$BUILD/sources.txt"

while IFS= read -r source; do
    relative="${source#"$ROOT/"}"
    object="$BUILD/objects/${relative//\//__}.o"
    "$CXX" -std=c++17 -Wall -Wextra -Werror -O2 -I"$ROOT/include" \
        -c "$source" -o "$object"
done < "$BUILD/sources.txt"

for relative in standalone/host_main.cpp standalone/host_stage.cpp standalone/host_trace.cpp \
                standalone/win32_compat.cpp standalone/globals.cpp; do
    object="$BUILD/objects/${relative//\//__}.o"
    "$CXX" -std=c++17 -Wall -Wextra -Werror -O2 -I"$ROOT/include" \
        -c "$ROOT/$relative" -o "$object"
done

"$WINDRES" "$ROOT/standalone/th10_standalone.rc" "$BUILD/objects/resources.o"

"$NM" -u "$BUILD/objects/"*.o |
    awk 'NF == 2 && $1 == "U" {print $2}' |
    sort -u > "$BUILD/undefined-all.txt"
"$NM" -j --defined-only "$BUILD/objects/"*.o |
    sort -u > "$BUILD/defined-all.txt"
comm -23 "$BUILD/undefined-all.txt" "$BUILD/defined-all.txt" \
    > "$BUILD/unresolved-all.txt"

python3 - "$BUILD" "$RETAIL_EXE" <<'PY'
from pathlib import Path
import hashlib
import re
import sys

build = Path(sys.argv[1])
retail_exe = Path(sys.argv[2])
symbols = (build / "unresolved-all.txt").read_text().splitlines()
expected_hash = (
    "2f14760b6fbbf57549541583283badb9a19a4222b90f0a146d5aa17f01dc9040"
)
if not retail_exe.is_file():
    raise SystemExit(f"retail executable not found: {retail_exe}")
image = retail_exe.read_bytes()
actual_hash = hashlib.sha256(image).hexdigest()
if actual_hash != expected_hash:
    raise SystemExit(
        f"unexpected retail executable SHA-256: {actual_hash}"
    )

# Original PE section layout.  Only data is imported; no retail instructions
# enter the all-source executable.
rdata = image[0x65000:0x65000 + 0xCA46]
data_raw = image[0x71C00:0x71C00 + 0x4200]
(build / "retail-rdata.bin").write_bytes(rdata)
(build / "retail-data.bin").write_bytes(data_raw)

address_pattern = re.compile(
    r"(?:DAT|FUN|LAB|caseD)_([0-9A-Fa-f]{8})"
)
global_aliases = {}
for symbol in symbols:
    match = address_pattern.search(symbol)
    if match:
        address = int(match.group(1), 16)
        if 0x00466000 <= address < 0x00472A46:
            global_aliases[symbol] = ("rdata", address - 0x00466000)
        elif 0x00473000 <= address < 0x0049934C:
            global_aliases[symbol] = ("data", address - 0x00473000)

# Ghidra's named pointer globals, corroborated against direct PE32 stores.
named_globals = {
    "_g_pD3D9": 0x00491C2C,
    "_g_pD3DDevice": 0x00491C30,
    "_g_pGameStateManager": 0x00491C10,
    "_g_pGameThread": 0x004776E0,
    "_g_pWnd": 0x00491C70,
}
for symbol, address in named_globals.items():
    if symbol in symbols:
        global_aliases[symbol] = ("data", address - 0x00473000)

global_assembly = [
    '.section .rdata,"dr"',
    "retail_rdata_base:",
    f'.incbin "{build / "retail-rdata.bin"}"',
    '.section .data,"dw"',
    "retail_data_base:",
    f'.incbin "{build / "retail-data.bin"}"',
    f"  .space {0x2634C - 0x4200}",
]
for symbol, (section, offset) in sorted(global_aliases.items()):
    base = "retail_rdata_base" if section == "rdata" else "retail_data_base"
    global_assembly.extend((
        f'.globl "{symbol}"',
        f'.set "{symbol}", {base} + {offset}',
    ))
(build / "retail_global_state.s").write_text(
    "\n".join(global_assembly) + "\n"
)
(build / "retail-global-symbols.txt").write_text(
    "\n".join(sorted(global_aliases)) + "\n"
)

def project_edge(symbol):
    return (
        symbol.startswith((
            "_DAT", "__DAT", "_PTR", "_g_p", "_ECL",
            "_AnimationManager", "_LegacyString",
        ))
        or symbol.startswith("@_Z")
        or (symbol.startswith("__Z") and len(symbol) > 3 and symbol[3].isdigit())
        or symbol in {
            "__eh_vector_constructor_iterator_",
            "__eh_vector_destructor_iterator_",
            "__memmove", "__strrchr", "__vsprintf",
            "___stricmp", "_D3DXMatrixLookAtLH",
            "_D3DXMatrixPerspectiveFovLH",
        }
    )

edges = sorted({
    symbol for symbol in symbols
    if project_edge(symbol) and symbol not in global_aliases
})
(build / "unresolved-symbols.txt").write_text(
    "\n".join(edges) + ("\n" if edges else "")
)
if edges:
    raise SystemExit(
        "unresolved project edges:\n  " + "\n  ".join(edges)
    )
PY

"$CC" -c "$BUILD/retail_global_state.s" \
    -o "$BUILD/objects/retail_global_state.o"

mapfile -d '' OBJECTS < <(find "$BUILD/objects" -type f -name '*.o' \
                          -print0 | sort -z)
# -mwindows: retail th10.exe is a GUI-subsystem image entered at WinMain.
"$CXX" -static -mwindows "${OBJECTS[@]}" \
    -Wl,-Map,"$BUILD/th10_all_sources.map" \
    -ld3d9 -ldinput8 -ldxguid -ldsound -ld3dx9 -lole32 -lwinmm -lgdi32 \
    -o "$BUILD/th10_all_sources.exe"

echo "built $BUILD/th10_all_sources.exe"
echo "linked $(wc -l < "$BUILD/sources.txt") production translation units"
echo "retail data globals: $(wc -l < "$BUILD/retail-global-symbols.txt") symbols"
echo "unresolved project edges: 0"
# The audit is a build gate, not a report: any host adapter, empty-lambda
# hook, or optional runtime binding that survives fails the build.
python3 "$ROOT/tools/runtime_placeholder_audit.py" --check \
    > "$BUILD/runtime-placeholder-audit.txt"
grep '^RUNTIME_PLACEHOLDER_COUNT=0$' \
    "$BUILD/runtime-placeholder-audit.txt"
grep '^SOFTWARE_RENDERER_COUNT=0$' \
    "$BUILD/runtime-placeholder-audit.txt"
grep '^EMPTY_FUNCTION_COUNT=' \
    "$BUILD/runtime-placeholder-audit.txt"

# Reconstruction fidelity: a promoted source must plausibly implement the
# retail functions it is credited with, measured against the IDA pseudocode.
# Ratchets against tools/reconstruction_fidelity_baseline.json - known
# violations are tolerated, new or worsened ones fail.
python3 "$ROOT/tools/reconstruction_fidelity_audit.py" --check \
    > "$BUILD/reconstruction-fidelity-audit.txt"
grep -E '^FIDELITY_(NEW|WORSENED)=0$' \
    "$BUILD/reconstruction-fidelity-audit.txt"
