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
Runtime layout declarations live under `include/th10/`. For stage selection,
[`stage_route.hpp`](../include/th10/game/stage_route.hpp) describes the eight
resource records shared by stage startup, title, replay and score code. The
score screens use the address *after* those records as a marker; it is not a
ninth stage to load.

The title's 195 animation slots hold [`AnimationScriptId`](../include/th10/render/animation_script_id.hpp)
values. A slot contains an ID to look up in the sprite manager, not a pointer
to an animation object.
[`title_input.hpp`](../include/th10/game/title_input.hpp) defines the name
keyboard shared by score entry and replay saving, and the same 50 replay
slots used by replay selection. [`title_score_file.hpp`](../include/th10/game/title_score_file.hpp)
places the score tables, practice unlocks and last entered name in one layout.
Difficulty, replay, spell-record and score-name selection use the same
[`EnsureTitleMenuBackdrop`](../include/th10/game/difficulty_select_update.hpp)
to install slot 94 and retain the back-layer animation handle.

[`SoundQueue::Queue`](core/sound/sound_queue.cpp) owns sound-request batching.
The item, title, HUD and projectile compiler contexts include this body rather
than separate copies; a context selects only its native code section.

[`LoadScript2`](core/sprtanim/animation_object_load_script.cpp) installs an
animation script and runs its first tick. Its private LTCG caller views do not
all have the same signature. The laser and item-line contexts share the
[loader that returns the sprite manager](../build_support/layout/ltcg/laser_grow/loader.cpp);
the player contexts share a
[void loader](../build_support/layout/ltcg/update_player_dependencies/item_spawn_0041bb00_loader.cpp).
The [front loader](../build_support/layout/ltcg/front_initialize/load_script_body.cpp)
uses the front HUD's own type declarations in both initialization and stage update.

`crt/` contains maintained C-runtime functions, `static_init/` contains the
compiler-generated global initializers and destructors, and `unreferenced/`
contains recovered code nothing in the game calls.

For script execution, start at the dispatcher for the bytecode you are reading:

- [`EclVm::Run`](script/sptcmd/ecl_core_interpreter.cpp) checks instruction
  time and rank, runs stack and control-flow operations, and delegates
  game-specific instructions to the owner.
- [`Enemy::Execute2`](game/enemy/enemy_execute.cpp) implements enemy ECL
  operations, including spawning, movement, animation and shooting. Cases
  stay in compiler order; the group comments identify related operations.
- [`AnmVm::Tick`](core/sprtanim/anm_vm_tick.cpp) runs animation instructions
  due this frame. A jump installs a new PC; a wait can keep the current PC
  while motion and interpolation still advance.

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

## File naming

Source, header and build-support files drop the `_00XXXXXX` address suffix
wherever the plain name is unambiguous. The suffix stays where it is the
unit's identity: the two replay-manager creation clusters
(`replay_manager_create_00429610`, `replay_manager_create_004296f0`), the
second recovery-script caller view (`recovery_script_executor_caller_00433ef0`)
against the first (`recovery_script_executor_caller.cpp`), and the
unrecovered scratch functions in `unreferenced/` (`fun_*`, `unassigned_*`,
`thunk_*`) whose only name is their address.
