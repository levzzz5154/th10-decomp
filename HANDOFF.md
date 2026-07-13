# TH10 Matching Decompilation — Handoff Document

## Project Goal

Produce C++ source that compiles with MSVC 7.1 (Visual C++ Toolkit 2003) into a PE32 binary that is byte-identical to the original `th10.exe` (Touhou 10: Mountain of Faith). The original binary is a 32-bit Windows game compiled with MSVC 7.1, using Direct3D 9, DirectSound, DirectInput8, and WinMM.

## Original Binary

- **Path**: `/home/levzzz/Games/TH10 - Mountain of Faith/th10.exe`
- **Size**: 487,936 bytes
- **Format**: PE32, x86 (Machine 0x14C)
- **Image base**: `0x00400000`
- **Entry point**: `0x00537DC` (CRT startup → `WinMainCRTStartup`)
- **Subsystem**: 2 (Windows GUI)
- **Sections**:

| Section | VA | VSize | Raw Offset | Raw Size |
|---------|------|-------|------------|----------|
| `.text` | `0x1000` | `0x64A81` | `0x400` | `0x64C00` |
| `.rdata` | `0x66000` | `0xCA46` | `0x65000` | `0xCC00` |
| `.data` | `0x73000` | `0x2634C` | `0x71C00` | `0x4200` |
| `.rsrc` | `0x9A000` | `0x12E0` | `0x75E00` | `0x1400` |

- **Imports**: 9 DLLs (kernel32, user32, gdi32, d3d9, d3dx9_31, dsound, winmm, dinput8, ole32)
- **Functions**: 1196 total (703 game, 470 CRT, 23 import thunks)

## Toolchain

All tools are on the system at:

| Tool | Path | Notes |
|------|------|-------|
| `cl.exe` | `~/.wine/drive_c/Program Files (x86)/Microsoft Visual C++ Toolkit 2003/bin/cl.exe` | MSVC 7.1 compiler (v13.10.3052) |
| `link.exe` | `~/.wine/drive_c/Program Files (x86)/Microsoft Visual C++ Toolkit 2003/bin/link.exe` | MSVC 7.1 linker |
| `libcmt.lib` | `~/.wine/drive_c/Program Files (x86)/Microsoft Visual C++ Toolkit 2003/lib/libcmt.lib` | Static CRT (multi-threaded) |
| `libcpmt.lib` | same lib dir | C++ runtime |
| `oldnames.lib` | same lib dir | Old CRT name aliases |
| `nasm` | `/usr/bin/nasm` | NASM 3.01 (for raw byte assembly) |
| `llvm-lib` | `/usr/bin/llvm-lib` | Import library generator |
| `wine` | system | Wine 11.11 (runs MSVC tools on Linux) |

**Compile flags**: `/nologo /c /O2 /Gd /MT`
- `/O2` = maximize speed (matches original)
- `/Gd` = `__cdecl` default calling convention
- `/MT` = link with `libcmt.lib` (static CRT)

**Link flags**: `/nologo /SUBSYSTEM:WINDOWS /BASE:0x400000`

**Important**: Always run with `WINEDEBUG=-all` to suppress Wine debug spam. Filter output with `grep -v "libEGL\|pci id\|libGL"`.

## Project Structure

```
th10Decomp/
├── matching/                      # Main matching decomp project
│   ├── tools/                     # Python tools
│   │   ├── gen_naked.py           # Naked asm generator (extracts bytes, disassembles, generates __asm)
│   │   ├── categorize.py          # Categorizes functions (GAME/CRT/THUNK)
│   │   ├── compile_all.py         # Batch compiler
│   │   ├── compare.py             # Byte comparison tool
│   │   ├── extract_funcs.py       # Function extractor from PE
│   │   ├── tracker.py             # Tracking CSV manager
│   │   └── build.py               # Full build pipeline
│   ├── src/
│   │   ├── th10/                  # 703 naked asm .cpp files (FUN_xxxx.cpp, Catch_xxxx.cpp, GameMain.cpp, GameStateInit.cpp)
│   │   ├── nasm/                  # 41 NASM .asm files (for 30 functions that MSVC inline asm couldn't handle + 11 CRT stubs)
│   │   ├── emit/                  # 30 _emit-based .cpp files (unused — MSVC 7.1 doesn't support _emit in __asm blocks)
│   │   ├── core/                  # (empty, reserved)
│   │   ├── crt/                   # (empty, reserved)
│   │   ├── game/                  # (empty, reserved)
│   │   ├── render/                # (empty, reserved)
│   │   ├── ui/                    # (empty, reserved)
│   │   ├── util/                  # (empty, reserved)
│   │   └── data/                  # (empty, reserved for data section .obj files)
│   ├── include/
│   │   ├── common.h               # Common includes for all naked asm files
│   │   ├── windows_types.h        # Windows type stubs
│   │   ├── d3d_stubs.h            # D3D9/D3DX type stubs
│   │   ├── dinput_stubs.h         # DirectInput8 type stubs
│   │   ├── dsound_stubs.h         # DirectSound type stubs
│   │   ├── structs.h              # Game struct definitions (Entity, etc.)
│   │   └── th10/                  # (reserved)
│   ├── libs/                      # Import library .def and .lib files
│   │   ├── kernel32.def / .lib
│   │   ├── user32.def / .lib
│   │   ├── gdi32.def / .lib
│   │   ├── d3d9.def / .lib
│   │   ├── d3dx9_31.def / .lib
│   │   ├── dsound.def / .lib
│   │   ├── winmm.def / .lib
│   │   ├── dinput8.def / .lib
│   │   └── ole32.def / .lib
│   ├── stubs/                     # (empty, reserved for stub implementations)
│   ├── build/                     # Build output directory
│   └── tracking.csv               # Function tracking: address, name, size, category, status
│
├── matching2/                     # Documented C++ source project (proper decompilation)
│   ├── include/th10/
│   │   ├── entity.hpp             # Entity (0x3AC), BulletEntity (0x2518), SchedulerTask types
│   │   ├── game_state.hpp         # GameState (0x2B64), GameThread (0x89AC) types
│   │   ├── ecl.hpp                # ECL opcode enum (122 opcodes), VM state types
│   │   └── th10_types.hpp         # Windows type stubs for matching2
│   └── src/
│       ├── game/                  # Entity, bullet, player, game-state/thread, score
│       ├── math/                  # Timer, vector, and numeric utilities
│       ├── platform/              # Win32 window and process integration
│       ├── render/                # Direct3D initialization and render state
│       └── script/                # ECL VM implementation
│
├── ghidra/                        # Ghidra project (MCP-connected)
│   └── project/th10/             # Ghidra project with th10.exe loaded
│
├── engine/                        # Old SDL2/OpenGL port project (NOT matching decomp — separate effort)
└── docs/
    └── architecture.md            # Architecture notes
```

## Current State

### 2026-07-13 C++ matching continuation

- Added `matching2/tools/compare_obj.py`, which selects an individual COFF
  COMDAT function and ignores link-time relocation operands during comparison.
- Fixed `_free` and `operator_new` declarations in `matching2/src/game/entity.cpp`
  to remain cdecl when the translation unit is compiled with `/Gz`.
- `Entity_Destructor` now verifies at 100% (30/30 non-relocation bytes).
- `Entity_Constructor` verifies at 100% (88/88 bytes).
- `DestroyEntityList` verifies at 100% (43/43 bytes).
- Reshaped `Entity_Init`'s preserved fields as the original three-dword
  aggregate and ordered its initialization stores like the executable. Its
  first 45 bytes now match exactly; later code still differs because MSVC
  schedules register restores/pops differently.
- Added reproducible compile and compare commands to `matching2/README.md`.
- Initialized a Git repository on `main`; the initial checkpoint is `17f7817`.
- Added `matching2/build.sh` and `matching2/tools/build_hybrid.py`. The hybrid
  builder verifies the retail executable hash, overlays only byte-matched COFF
  functions at their original virtual addresses, and preserves the original PE
  data, imports, and resources for a continuously playable baseline.
- Added `matching2/run.sh`. It links the original `th10.dat` and `thbgm.dat`
  archives beside the rebuilt executable because TH10 resolves archives from
  the module directory rather than the shell working directory.
- Verified under Wine that `th10_reimpl.exe` opens both original archives and
  remains in the game loop for a 20-second bounded smoke test.
- Added the pure-C++ `EntityAnimation_Release` implementation at `0x0041AD60`;
  it matches 30/30 non-relocation bytes. The hybrid now verifies four overlays
  totaling 191 comparable bytes.
- Added a readable `ScoreCounter::AddScaled` reconstruction for `0x0041BE80`.
  It is not yet overlaid because MSVC 7.1 selects a register-form multiply while
  the retail function uses a stack-memory operand.
- Added three more byte-exact ordinary-C++ implementations:
  `EntitySecondaryResource_Release` (`0x00405DE0`, 30/30),
  `HeapBuffer_Release` (`0x00435250`, 22/22), and
  `LegacyString_Clear` (`0x004381F0`, 34/34).
- Added the Win32-backed `FileHandle_Close` implementation (`0x00435460`,
  30/30), using a proper `dllimport` declaration so MSVC emits the original
  indirect IAT call.
- The hybrid now verifies eight overlays totaling 307 comparable bytes.
- `matching2/build.sh` now compiles all 12 subsystem translation units rather
  than maintaining a partial source list. Duplicate source basenames fail the
  build to keep COFF object selection deterministic.

### What Works

1. **703 game function .obj files compile** (673 via MSVC naked asm, 30 via NASM raw bytes)
2. **9 import .lib files generated** from .def files using `llvm-lib`
3. **PE32 binary successfully linked** — 715 .obj files + libcmt.lib + import libs → `/tmp/th10_built.exe` (147 KB)
4. **0 unresolved external symbols** after adding CRT alias stubs
5. **6 functions verified as 100% byte match**: Entity_Constructor, Timer_Set, Timer_Reset, ClampValue (and 2 more at ~96% with only call relocations differing)
6. **Ghidra MCP connection active** — can decompile any function on demand

### What Doesn't Work Yet

1. **Binary is 147 KB, not 488 KB** — missing `.data` (152 KB), `.rdata` (52 KB), `.rsrc` (5 KB) sections
2. **Binary won't run** — code references absolute addresses in `.data`/`.rdata` that aren't present
3. **C++ functions don't byte-match** — `Entity_Init`, `game_state.cpp`, `game_thread.cpp`, `player.cpp`, `d3d_init.cpp` compile but produce different register allocation than original. Only naked asm functions match.
4. **`matching2/` source files don't link** — they're documentation-quality C++, not linked into the final binary

### Function Tracking Summary

| Category | Status | Count | Notes |
|----------|--------|-------|-------|
| GAME | compiled | 671 | MSVC naked asm, produces .obj |
| GAME | pending | 32 | Fixed via NASM raw bytes (not reflected in CSV) |
| CRT | auto | 470 | Provided by `libcmt.lib` |
| THUNK | auto | 23 | Import thunks, provided by import .lib files |
| **Total** | | **1196** | |

## How to Build

### Compile all .obj files

```bash
export WINEDEBUG=-all
CL="$HOME/.wine/drive_c/Program Files (x86)/Microsoft Visual C++ Toolkit 2003/bin/cl.exe"

# Compile naked asm files in batches of 100
cd /home/levzzz/Games/th10Decomp/matching
mkdir -p /tmp/obj

# MSVC naked asm files (673 compile successfully)
count=0; srcs=""
for f in src/th10/*.cpp; do
    srcs="$srcs Z:\\home\\levzzz\\Games\\th10Decomp\\matching\\$f"
    count=$((count + 1))
    if [ $count -ge 100 ]; then
        wine "$CL" /nologo /c /O2 /Gd /MT /Fo"Z:\\tmp\\obj\\" $srcs 2>&1 | grep -v "libEGL\|pci id\|libGL"
        srcs=""; count=0
    fi
done
if [ -n "$srcs" ]; then
    wine "$CL" /nologo /c /O2 /Gd /MT /Fo"Z:\\tmp\\obj\\" $srcs 2>&1 | grep -v "libEGL\|pci id\|libGL"
fi

# NASM raw byte files (30 functions + 11 CRT stubs)
for f in src/nasm/*.asm; do
    nasm -f win32 "$f" -o "/tmp/obj/$(basename $f .asm).obj"
done
```

### Generate import libraries

```bash
cd /home/levzzz/Games/th10Decomp/matching/libs
for def in *.def; do
    name=$(basename "$def" .def)
    llvm-lib /machine:x86 /def:"$def" /out:"/tmp/${name}.lib"
done

# Also copy CRT libs to /tmp (avoid spaces in path)
cp ~/.wine/drive_c/Program\ Files\ \(x86\)/Microsoft\ Visual\ C++\ Toolkit\ 2003/lib/*.lib /tmp/
```

### Create CRT alias stubs

The naked asm files reference CRT functions with non-standard names (`_operator_new`, `__free`, `___allmul`, etc.) that don't match `libcmt.lib` symbol names. A NASM file provides aliases:

```bash
cat > /tmp/crt_aliases.asm << 'EOF'
EXTERN _malloc, _free, _rand, _GameMain
SECTION .text

global _operator_new
_operator_new: jmp _malloc

global __free
__free: jmp _free

global __rand
__rand: jmp _rand

global __malloc
__malloc: jmp _malloc

global ___allmul, ___aulldiv, ___chkstk, ___beginthread, ___beginthreadex
global ___security_check_cookie, __eh_vector_constructor_iterator_
global __eh_vector_destructor_iterator_, ___CxxThrowException_8
___allmul: ret
___aulldiv: ret
___chkstk: ret
___beginthread: ret
___beginthreadex: ret
___security_check_cookie: ret
__eh_vector_constructor_iterator_: ret
__eh_vector_destructor_iterator_: ret
___CxxThrowException_8: ret

global __atof, __atol, __localtime, __memmove, __sprintf, __sscanf
global ___stricmp, __strncmp, __strncpy, __strrchr, __vsprintf
__atof: ret
__atol: ret
__localtime: ret
__memmove: ret
__sprintf: ret
__sscanf: ret
___stricmp: ret
__strncmp: ret
__strncpy: ret
__strrchr: ret
__vsprintf: ret

global _WinMain@16
_WinMain@16:
    call _GameMain
    xor eax, eax
    ret 16
EOF

nasm -f win32 /tmp/crt_aliases.asm -o /tmp/obj/crt_aliases.obj
```

### Link

```bash
LINK="$HOME/.wine/drive_c/Program Files (x86)/Microsoft Visual C++ Toolkit 2003/bin/link.exe"

OBJ_LIST=""
for f in /tmp/obj/*.obj; do
    OBJ_LIST="$OBJ_LIST Z:\\tmp\\obj\\$(basename $f)"
done

LIBS="Z:\\tmp\\libcmt.lib Z:\\tmp\\libcpmt.lib Z:\\tmp\\oldnames.lib \
      Z:\\tmp\\kernel32.lib Z:\\tmp\\user32.lib Z:\\tmp\\gdi32.lib \
      Z:\\tmp\\d3d9.lib Z:\\tmp\\d3dx9_31.lib Z:\\tmp\\dsound.lib \
      Z:\\tmp\\winmm.lib Z:\\tmp\\dinput8.lib Z:\\tmp\\ole32.lib"

wine "$LINK" /nologo /SUBSYSTEM:WINDOWS /BASE:0x400000 \
    /OUT:Z:\\tmp\\th10_built.exe /LIBPATH:Z:\\tmp $OBJ_LIST $LIBS
```

## Known Issues & Solutions

### 1. DSOUND ordinal import

The original imports DirectSound by ordinal #11. The .def file must use:
```
LIBRARY DSOUND.dll
EXPORTS
  DirectSoundCreate @11 NONAME
  Ordinal_11 @11
```

### 2. `fnstsw ax` in inline asm

MSVC 7.1 inline assembler does NOT support `fnstsw`. Use `_emit 0xDF; _emit 0xE0` instead, or better, use NASM for functions that need FPU status word.

### 3. `ds:` prefix in inline asm

MSVC 7.1 generates an unnecessary `DS:` segment override prefix (0x3E) when using `ds:[0xADDRESS]` syntax. Use `_emit` for the raw FPU instruction bytes, or use NASM.

### 4. `extern "C"` requirement

All naked asm function definitions MUST have `extern "C"` prefix, otherwise MSVC mangles the name to `?FUN_xxx@@YAXXZ` and the linker can't resolve cross-references between .obj files. Already patched in all 703 files.

### 5. `__declspec(dllimport)` for Win32 APIs

The original binary was compiled with Windows SDK headers that use `__declspec(dllimport)` on all Win32 API declarations. This causes the compiler to generate `call [__imp__Function]` (indirect through IAT) instead of `call Function` (direct to thunk). Our naked asm files use raw `call` to absolute addresses, so this doesn't matter for them. But for pure C++ functions that call Win32 APIs, the import call pattern won't match without `__declspec(dllimport)`.

### 6. MSVC 7.1 pre-C++11 limitations

- No `nullptr` (use `0` or `NULL`)
- No `static_assert` (use a typedef trick or comment)
- No `using` type aliases (use `typedef`)
- No `<cstdint>` (use manual typedefs)
- No `enum class` (use plain `enum`)
- `__thiscall` only works on actual member functions, not free functions

## Next Steps to Playable Binary

### Option A: Extract data sections from original (fastest)

1. **Extract `.rdata` section** from original binary as a .obj file at RVA `0x66000`
2. **Extract `.data` section** from original binary as a .obj file at RVA `0x73000`
3. **Extract `.rsrc` section** from original binary as a .obj file at RVA `0x9A000`
4. Link these data .obj files with the code .obj files
5. Use `/FIXED` and `/SECTION:.data,WR` linker flags to place sections at correct addresses

This can be done with NASM:
```nasm
; data_section.asm
BITS 32
GLOBAL _data_start
SECTION .data DATA
_data_start:
    incbin "data_section.bin"
```

Or with `objcopy` to convert raw binary to COFF .obj with proper section attributes.

### Option B: Reverse-engineer globals (proper matching decomp)

1. Use Ghidra to enumerate all global variables in `.data` and `.rdata`
2. Declare each global in C++ with correct type and initial value
3. Compile data as C++ source → produces `.data` and `.rdata` sections
4. Extract `.rsrc` from original (resources aren't expressible in C++)

### Option C: Hybrid approach (recommended)

1. Extract `.rsrc` from original as a .obj (resources can't be reverse-engineered to C++)
2. Extract `.rdata` from original as a .obj (string literals, const tables — low value to reverse-engineer)
3. Reverse-engineer `.data` section globals in C++ (vtables, game state, mutable globals)
4. This gives a playable binary quickly while allowing gradual replacement of `.data` with proper C++

## Ghidra MCP

A Ghidra instance is running with the `th10.exe` binary loaded. Use MCP tools to:

- `ghidra_decompile_function` — Get C decompilation of any function by address
- `ghidra_batch_decompile` — Decompile multiple functions at once
- `ghidra_disassemble_function` — Get raw disassembly
- `ghidra_search_functions_enhanced` — Search/list functions
- `ghidra_list_instances` / `ghidra_connect_instance` — Manage Ghidra connection

The Ghidra project is at `/home/levzzz/Games/th10Decomp/ghidra/project/th10`.

## Key Function Addresses

| Address | Name | Description |
|---------|------|-------------|
| `0x00401000` | GameThread_Construct | Initialize 0x89AC-byte game thread |
| `0x00401110` | GameThread_Init | Load animations, create callbacks |
| `0x00401260` | GameThread_Destroy | Release resources, free memory |
| `0x00401440` | GameThread_Create | Allocate + construct + init game thread |
| `0x00402050` | Entity_Constructor | Zero entity, clear flags (100% byte match) |
| `0x00401DE0` | Entity_Init | Full entity reset with defaults |
| `0x00401FF0` | Entity_Destructor | Free resource at +0x358 (100% byte match) |
| `0x00404ED0` | Timer_Tick | Advance timer by one frame (96% byte match) |
| `0x00405410` | Timer_Set | Initialize timer (100% byte match) |
| `0x00405B60` | ClampValue | Clamp to [-0x400, 0x400] (100% byte match) |
| `0x0040CFB0` | Entity_Spawn | Allocate 0x2518-byte bullet/enemy |
| `0x0040D830` | Entity_InitHelper | Initialize bullet entity fields |
| `0x0040E770` | ECL_VM_Dispatch | 122-opcode ECL interpreter (1826 lines decompiled) |
| `0x00438AD0` | GameMain | Main game loop entry |
| `0x00438A30` | DestroyEntityList | Destroy 32 entity slots |
| `0x004390E0` | WndProc | Window procedure |
| `0x004392E0` | SaveSystemSettings | Save SPI settings + init perf counters |
| `0x00439730` | CreateGameWindow | Register class + create window |
| `0x00439890` | D3D_Init | Create D3D device + camera setup |
| `0x00439FF0` | InstanceCheck | Mutex + .lnk shortcut resolution |
| `0x00452422` | _free | CRT free (from libcmt.lib) |
| `0x00452493` | operator_new | CRT operator new (from libcmt.lib) |
| `0x00463B2C` | rand | CRT rand function |

## File Count Summary

| Location | Count | Description |
|----------|-------|-------------|
| `matching/src/th10/*.cpp` | 703 | Naked asm game functions |
| `matching/src/nasm/*.asm` | 41 | NASM raw byte files (30 broken + 11 CRT stubs) |
| `matching/libs/*.def` | 9 | Import library definition files |
| `matching/tools/*.py` | 7 | Build/analysis Python scripts |
| `matching/include/*.h` | 6 | Type stubs and structs |
| `matching2/src/{game,math,platform,render,script}/*.cpp` | 10 | Documented C++ source files |
| `matching2/include/th10/*.hpp` | 4 | C++ type headers |
| `matching/tracking.csv` | 1196 rows | Function tracking database |
