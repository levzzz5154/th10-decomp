# Title ANM Vertical-Slice Bridge

Status: bounded all-source bridge implemented; curated source split resolved.
Both `build_all_pe32.sh` and the published `build_pe32.sh` runner now use the
280-TU all-source PE32 image. It mounts real ANM descriptors, synchronizes live
`HostAnmVm` state into pooled `AnimationObject` records, and lets
`AnimationObject_Render` own valid title draws. Unsupported title bindings keep
the object paused with no host draw callback; real mode records an error and
terminates.

## Current Path

The title path is split across two incompatible representations:

1. `matching2/standalone/host_main.cpp:224-239` defines `HostAnmVm`. Its
   `AnmVmState` contains the current sprite, transform, colour and flags, while
   the VM stores only `resource_index`, raw `resource_bytes` and
   `resource_size`.
2. `matching2/standalone/host_main.cpp:5263-5320` loads `title.anm`,
   `title_v.anm` and `sig.anm` into `title_resource_bytes[]`. The title script
   and sprite lookups at `:656-899` and `:2655-2752` use those raw bytes through
   `AnmFile_FindGlobalScript`/`AnmFile_FindGlobalSprite`.
3. `matching2/standalone/host_main.cpp` retains `g_anim_object_vm[]` only as
   stable VM metadata for tracing and object publication; manager-owned title
   objects do not install a host draw callback.
4. `matching2/standalone/host_main.cpp` allocates a pooled `AnimationObject`
   and registers it in the primary list. In the all-source target the bridge now
   publishes a descriptor at `+0x308`, sprite metadata at `+0x394`, and the VM's
   current state into the retail object fields while pausing the manager script
   executor. If the descriptor/texture is unavailable, it leaves the object
   paused without a callback and reports the unsupported edge.
5. Stage/front/player VMs now mount descriptor resources in manager slots
   `0x1c`/`0x1d`/`0x1e` and publish placement/player/HUD copies through the
   same manager bucket path. The raw `HostDrawAnmVm` route has been removed from
   the standalone source.

The requested manager renderer is `AnimationObject_Render`:

- The PE32 implementation is `matching2/src/render/all_source_anm_runtime.cpp:303-392`.
- It consumes `AnimationObject` fields at `+0x35c` (flags), `+0x394` (the
  descriptor sprite record), `+0x334..+0x354` (position terms), `+0x4c/+0x50`
  (sprite extents), `+0x2c` (rotation), and `+0x2fc` (colour).
- The descriptor layout it expects is `RuntimeAnmResource` at
  `matching2/src/render/all_source_anm_runtime.cpp:20-35`: raw image at
  `+0x108`, sprite records at `+0x118`, scripts at `+0x11c`, texture records at
  `+0x120`, and loading state at `+0x124`.
- `AnimationObject_ConfigureFromResource` in
  `matching2/src/render/animation_manager.cpp:2279-2318` is the existing
  operation that binds a descriptor and sprite record to an object.

## Concrete Blockers

### 1. Curated source-set split is resolved

`matching2/build_pe32.sh` now delegates to `build_all_pe32.sh` and publishes its
all-source executable as `build/pe32/th10_standalone.exe`. The descriptor
runtime and manager implementation therefore enter both normal PE32 runners,
with one global ownership model. The unified build reports 280 production
translation units, zero unresolved project edges, and the resource runtime smoke
passes against real `ascii.anm` and `stage01.std` data.

A historical 36-TU direct-link audit is retained below as evidence for why the
curated source list was removed; it is no longer the active runner.

### 2. Descriptor failure is explicit

Both PE32 runners use the descriptor runtime. If a visible title VM cannot bind
a descriptor or texture, the host records `title_resource_error`, logs the
unsupported edge, leaves the manager object paused without a draw callback, and
terminates the run instead of silently treating host rendering as retail
ownership. Headless smoke mode has no D3D device by design and does not assert a
rendered title draw.

### 3. Portable VM state is synchronized explicitly

`HostAnmVm::state` remains a portable `AnmVmState`, not a retail entity layout.
The all-source bridge now copies flags, colours, position, parent-chain
position, rotation, and scale into the pooled object after configuring its
descriptor sprite record. The object carries `ANM_FLAG_PAUSED`, so the host VM
remains the only script executor and `AnimationObject_Render` is the only valid
manager draw owner.

### 4. Texture ownership is descriptor-backed across ANM families

Mounted title, stage, player, and front descriptors own their texture records
and are destroyed with `ResourceManager_DestroyResource` before the D3D device
is released. Raw bytes remain alongside each VM for script/sprite parsing, but
no live render path uses the raw-entry texture cache.

### 5. Focused bridge coverage is implemented

`matching2/tests/title_anm_manager_bridge_test.cpp` is a D3D-free i386
regression. It checks descriptor sprite binding, retail object fields, texture
record selection, and reuse of the same pooled object on a second publish.

## Exact Follow-up Patch

The descriptor promotion is complete for the current stage/front/player slice.
`--stage-live N` validates the real D3D9 manager draw list for a bounded stage
run; the current 120-frame run emits 16,173 `stage_draw` events and 179
pre-Present checksums. The next ANM work is to extend the same
descriptor-owned path to any newly discovered replay/result resources.

## Focused Regression

`matching2/tests/title_anm_manager_bridge_test.cpp` builds a synthetic descriptor
with one sprite and one texture record, configures a pooled object through
`AnimationObject_ConfigureFromResource`, checks the retail object fields and
texture record, and repeats the publish to assert object reuse. It is compiled
with the i386 ABI and does not include ECL sources. The existing `anm_file_test`
and `game_runtime_test` remain the precondition tests for raw archive parsing and
animation-manager pool/list behavior.

## Verification From This Checkout

- `matching2/test.sh` is the relevant host regression entry point; run at least
  `anm_file_test`, `anm_entry_load_test`, `game_runtime_test`, and the new bridge
  test once the descriptor helper exists.
- The bundled PE32 default path is absent in this environment, but the system
  i686 MinGW tools are available. The following source/link check was run from
  `matching2` with `TH10_PE32_CXX=$(command -v i686-w64-mingw32-g++)` and
  `TH10_PE32_WINDRES=$(command -v i686-w64-mingw32-windres)`:

  - `./build_pe32.sh` compiled its 36 listed C++ translation units and failed
    at the final link with 173 unique undefined references.
  - `i686-w64-mingw32-g++ -std=c++17 -Wall -Wextra -Werror -O2 -Iinclude
    -c src/render/all_source_anm_runtime.cpp` passed.
  - A temporary repeat of the same link command with only
    `src/render/all_source_anm_runtime.cpp` added compiled that TU but failed
    with 176 unique undefined references. It removed exactly:
    `AnimationObject_ExecuteScript(AnimationObject*)`,
    `ResourceManager_FindResource(int, void*, char const*)`, and
    `ResourceManager_DestroyResource(void*, void*)`.
  - That addition introduced exactly these six new unresolved edges:
    `AnimationManager_CreatePrimaryFront(void*, void*, int, int)`,
    `AnimationManager_CreateSecondaryBack(void*, void*, int, int)`,
    `AnimationManager_CreateSecondaryFront(void*, void*, int, int)`,
    `AnimationObject_ReadIntegerVariable(AnimationObject*, int)`,
    `AnimationObject_ResolveFloatVariable(AnimationObject*, int, float*, bool)`,
    and `AnimationObject_ResolveIntegerVariable(AnimationObject*, int, int*, bool)`.

  The descriptor addition also leaves the existing manager boundary unresolved:
  `AnimationObject_ConfigureFromResource(void*, void*, int)`,
  `AnimationManager_AllocateObject(void*)`,
  `AnimationManager_RegisterObjectAt(void*, AnimationObject*, AnimationManagerList, AnimationListInsertion)`,
  `AnimationManager_UpdatePrimary(void*)`,
  `AnimationManager_RenderBucket(void*, int)`, and
  `AnimationManager_MarkResourceForRemoval(void*, void*)`. Therefore adding
  the descriptor TU alone cannot converge `build_pe32.sh`; widening the curated
  source set would be a separate manager/runtime integration change.
