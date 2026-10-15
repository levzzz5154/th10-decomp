# Source layout

The folders under `game/`, `pack/`, `core/` and `script/` mirror ZUN's own
source files: one folder per retail `.cpp`. The retail `.rdata` keeps the
debug strings of compiled-out allocation logs (for example
`.\src\game\card.cpp:272 CardInf`). They name the files, and the linker
placed each file's code in `.text` in the same order:

| Folder | Retail file | `.text` range |
|---|---|---|
| `game/ascii` … `game/title` | `src/game/<name>.cpp` | 0x401000–0x434C10 (pause from 0x4220E0) |
| `pack/arcmngr` | `src/pack/_ArcMngr.cpp` | 0x434C10–0x435320 |
| `pack/file` | `src/pack/File.cpp` | 0x435320–0x4359B0 |
| `pack/lzssutil` | `src/pack/LzssUtil.cpp` | 0x4359B0–0x436370 |
| `pack/resfile` | `src/pack/ResFile.cpp` | 0x436370–0x436570 |
| `core/main` | `src/core/main.cpp` | 0x436570–0x43A490 |
| `core/midilib` | `src/core/midilib.cpp` | 0x43A490–0x43B8D0 |
| `core/input` | *(no retail string)* | 0x43B8D0–0x43BC40 |
| `core/screen` | `src/core/screen.cpp` | 0x43BC40–0x43CC40 |
| `core/sound` | `src/core/sound.cpp` | 0x43CC40–0x43E460 |
| `core/sprtanim` | `src/core/sprtanim.cpp` | 0x43E460–0x4423C0 |
| `core/sprtfunc` | `src/core/sprtfunc.cpp` | 0x4423C0–0x445900 |
| `core/sprtlib` | `src/core/sprtlib.cpp` | 0x445900–0x449A50 |
| `core/zunlib` | `src/core/zunlib.cpp` | 0x449A50–0x44C8F0 |
| `core/zwave` | `src/core/zwave.cpp` | 0x44C8F0–0x44DF70 |
| `script/sptcmd` | `src/script/sptcmd.cpp` | 0x44DF70–0x450220 |
| `script/sptlib` | `src/script/sptlib.cpp` | 0x450220–0x450710 |

The `game/` boundaries follow the task installers and the info classes of
each file (`AsciiInf`, `BackGroundInf`, `EclViewInf`, `EnemyCtrlInf` …). The
boundaries past 0x436570 are less certain:
- The `core/` files leave fewer strings. `core/input` holds the DirectInput
  set-up, and no retail string names its file.
- The splits between `sprtanim`, `sprtfunc` and `sprtlib`, and between
  `sptcmd` and `sptlib`, come from the order of each file's constants in
  `.rdata`.

A folder can hold several files because native-LTCG clusters compile
functions in distinct scopes. Compatible fragments in a shared compiler unit
are merged; independent scopes retain separate files so their private ABIs and
machine code stay unchanged. The old mixed `app/`, `platform/`, `render/`,
`math/`, `archive/` and top-level `game/` sources have been split into these
retail owners.

Default-build C++ recoveries are here too. Their exact-only counterparts,
compiler contexts, placement tables, import thunks and embedded `.text` data
live under [`../build_support/`](../build_support/README.md). Some maintained
files are compiled through private wrappers which preserve retail function
order; use the top-level `make` rather than compiling folders independently.
Runtime layout declarations remain under `include/th10/`.

`crt/` contains maintained C-runtime functions, `static_init/` contains the
compiler-generated global initializers and destructors, and `unreferenced/`
contains recovered code nothing in the game calls.

The game-file boundaries, including the info/query leaves before constructors:

| Folder | `.text` range |
|---|---|
| `game/ascii` | 0x401000–0x402160 |
| `game/background` | 0x402160–0x4055A0 |
| `game/bomb` | 0x4055A0–0x405D00 |
| `game/bullet` | 0x405D00–0x408910 |
| `game/card` | 0x408910–0x409EB0 |
| `game/eclview` | 0x409EB0–0x40AE70 |
| `game/effect` | 0x40AE70–0x40B560 |
| `game/ending` | 0x40B560–0x40C5E0 |
| `game/enemy` | 0x40C5E0–0x413350 |
| `game/fps` | 0x413350–0x413810 |
| `game/front` | 0x413810–0x417870 |
| `game/game` | 0x417870–0x418D00 |
| `game/hint` | 0x418D00–0x41AB10 |
| `game/item` | 0x41AB10–0x41BEF0 |
| `game/laser` | 0x41BEF0–0x41F850 |
| `game/loading` | 0x41F850–0x41FF80 |
| `game/mother` | 0x41FF80–0x4220E0 |
| `game/pause` | 0x4220E0–0x4246C0 |
| `game/player` | 0x4246C0–0x428F60 |
| `game/replay` | 0x428F60–0x42ACB0 |
| `game/score` | 0x42ACB0–0x42B430 |
| `game/smollscore` | 0x42B430–0x42BAD0 |
| `game/spttest` | 0x42BAD0–0x42C5B0 |
| `game/title` | 0x42C5B0–0x434C10 |

Compiler-generated unwind bodies at the end of `.text` follow their parent
function's owner rather than the numerical ranges above.
