# Source layout

The folders under `game/`, `pack/`, `core/` and `script/` mirror ZUN's own
source files: one folder per retail `.cpp`. The retail `.rdata` keeps the
debug strings of compiled-out allocation logs (for example
`.\src\game\card.cpp:272 CardInf`). They name the files, and the linker
placed each file's code in `.text` in the same order:

| Folder | Retail file | `.text` range |
|---|---|---|
| `game/ascii` … `game/title` | `src/game/<name>.cpp` | 0x401000–0x434C10 |
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
functions separately. Files whose functions span two retail files still sit
in the older topical folders (`app/`, `platform/`, `render/` …) until they
are split. `crt/` is the C runtime, `data/` holds embedded `.text` data and
`unreferenced/` holds code nothing in the game calls.
