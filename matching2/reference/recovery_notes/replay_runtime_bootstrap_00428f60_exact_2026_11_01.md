# Replay runtime bootstrap 0x00428F60: byte-exact, 2026-11-01

`ReplayManager::Start` (1,344 bytes), the replay runtime's bootstrap that the
factory at 0x00429610 calls, is now byte-exact C++. The source is
`src/game/replay/replay_runtime_bootstrap.cpp`, and it is built in the new
cluster `build_support/layout/ltcg/replay_runtime_bootstrap.json`. Three files
are gone: the old equivalent layout (3 instruction hunks, 507 differing bytes,
parked since 2026-10-18 as an "addressing-mode decision no spelling steers"),
the asm owner `build_support/exact/game/replay/replay_runtime_bootstrap.cpp`,
and the rig context `build_support/layout/ltcg/replay_runtime_bootstrap_00428f60_context.cpp`.

## What closed it

1. **Mode 1 (playback), all 507 bytes.** In the stage-input rewind, two
   stores were re-folded into `[ebx+edx*4+disp]` encodings, which shifted the
   whole tail by 507 bytes. The 2026-10-18 note blamed c2's disp-less-base
   address CSE. That diagnosis was wrong. The real cause was the two
   `_ReadWriteBarrier()`s an old session had put around
   `g_rng.generation = 0` in the seed restore. They cut the store dependency
   chains, which lowered the stores' list-scheduler priority. Removing them
   and making the generator state's address escape (as it does in retail,
   where the RNG helpers take `&g_rng` as their receiver) gave the retail
   schedule: 0 differing bytes in the rig.
2. **Mode 0 (recording) record fill: four more barriers and a raw-address
   read removed.** The configuration word `g_stage_flags` (0x00491FC4, field
   +0x39C of the application object at 0x00491C28) now escapes too. With
   that, the fill reads naturally:
   `stage_record->flag = g_stage_flags; if (g_stage_flags != 0) { ... }`.
   `flag` is the record's 1-bit field. This replaces four barriers, a
   hand-written `flag ^ ((flag ^ word) & 1)` and an
   `*(int *)0x00491FC4` "fresh read". It measured 0 bytes in the rig and in
   the cluster. Moving the `flag` store above `g_rng.generation = 0` costs
   1,043 bytes, so the source keeps retail's statement order.
3. **One barrier stays,** in the inline callback-node constructor
   (`SchedulerCallbackTask2`), between `priority = 0` and the heap-owned
   clear. Retail loads the flag word first, then does the four stores, then
   `and ecx,~1`. Without the barrier c2 puts the `and` right after the load.
   That happens six times (one per node) and costs 54 bytes. These spellings
   all measured 54:
   - plain `flags &= ~1u` (rig and cluster);
   - a load/mask/store without the barrier (rig);
   - a th06-style 1-bit field clear (`heap_owned = 0` / `= false`, cluster; the
     `ChainElem::isHeapAllocated` shape).

   `_ReadWriteBarrier` is an accepted lever (see
   `th10-readwritebarrier-is-accepted-lever`).

No asm, padding or flag changes. The shipped body has 1 barrier, down from 7,
and no raw-address reads.

## Cluster

Schema 1. It reproduces the equivalence rig's link: unit 1 is the body
(through the driver `build_support/layout/ltcg/replay_runtime_bootstrap/driver.cpp`,
which only includes it), and unit 2 is the rig context, now
`build_support/layout/ltcg/replay_runtime_bootstrap/context.cpp`. The link
entry `ReplayManagerStartCompilerContext` is the unselected cluster
`context`. Only `?Start@ReplayManager@@QAEHHPBD@Z` is selected.

- **No /EHsc (`"exceptions": false`).** The rig compiled its context with
  /EHsc, but the bootstrap's bytes are the same without it (rig variant
  `ctx_noeh`: 0 bytes). The factory's unwind group (funclets 0x00465660 and
  0x0046566B, plus the .xdata) belongs to the factory's own cluster
  `replay_manager_create_00429610.json`, and an EH body cannot be compiled
  in a second cluster (`th10-eh-functions-one-per-ltcg-cluster`). Without EH
  the factory calls the node constructor and destructor directly, so those
  two are `relative_code` absolute symbols, and the EH-only symbols
  (`___CxxFrameHandler`, `__except_list`, `??_L`, `??_M`) are dropped.
- **Factory supplies the private convention.** The factory source
  `src/game/replay/replay_manager_create_00429610.cpp` is included in the
  context (it is in `included_sources`). It still sets up the bootstrap's
  private convention: receiver in EBX, mode in EAX, path in ECX. Its code is
  parked at 0x00401040 through an overridable `code_seg` macro wrapper.
- **Seven called stand-ins at their retail addresses.** These are the bodies
  the bootstrap calls, so their call displacements are baked in:
  - `GameConfig_InitializeDefaults` 0x00418C40
  - `ReplayManager_LoadFile2` 0x0042A200
  - `EmbeddedTimerState::SetCountdown` 0x0042A930
  - `PoolOwner::AppendPage` 0x0042AA50
  - `ReplayPool_Clear` 0x0042AB20
  - `FuncCtrl_RegisterPrimary` 0x00449AE0
  - `FuncCtrl_RegisterSecondary` 0x00449B70

  Each has its own `code_seg`. The anchor sizes are the map contribution
  lengths (`sizes.json`).
- **Parked at 0x00401000..** (the bootstrap does not call these): the
  entry, the escape `ReplayBootstrapRngEscape(void**)`, the factory and the
  stand-in destructor. The rig's escape was a context-defined global
  pointer, which the cluster cannot emit as data. It became a rooted public
  function that stores `&g_rng` and `&g_stage_flags`, the
  `TitleDispatcherEscape` / `AnmVmTickEscape` pattern. `anchor_roots` =
  factory + escape.
- **22 absolute symbols** come from the old equivalent layout: game globals
  as data, retail CRT/helpers as code.

Generator: `matching2/build/experiments/goal_2026_11_01/promote_replay_runtime_bootstrap/gen.py`.
Its inputs are snapshotted under `inputs/` (the search agent's winning body
and rig context, and the old equivalent layout), with the header list and
`sizes.json` baked in. The cutover runs from that directory:

    MSVC_TREE=$PWD/tree/msvc python3 gen.py
    python3 ../promote_regions.py tree/msvc 0x00428F60 semantic_ReplayManager_Start_00428f60 \
        src/game/replay/replay_runtime_bootstrap.cpp '?Start@ReplayManager@@QAEHHPBD@Z' \
        build_support/layout/equivalent/replay_runtime_bootstrap.json \
        build_support/layout/ltcg/replay_runtime_bootstrap.json
    rm tree/msvc/build_support/exact/game/replay/replay_runtime_bootstrap.cpp \
       tree/msvc/build_support/layout/equivalent/replay_runtime_bootstrap.json
    python3 ../cbuild.py tree/msvc build_support/layout/ltcg/replay_runtime_bootstrap.json out

    FUNC ?Start@ReplayManager@@QAEHHPBD@Z 0x428f60 1344 DIFFBYTES 0

`load_clusters` accepts all 987 clusters of the resulting tree.
