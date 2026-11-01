# Replay save 0x00429B60 — byte-exact, 2026-11-01

The 1,681-byte replay save routine `ReplaySaveManager::Save` is byte-exact
C++ (`src/game/replay/replay_save.cpp`), built in the cluster
`build_support/layout/ltcg/replay_save.json` (registered now; it existed
before only as the equivalent layout's unregistered context cluster). The
equivalent layout (29 recorded differences plus a 31-instruction -8/-4/+4
frame shift) is gone. So are the context-only stub
`src/game/replay/replay_save_stub.cpp`, the legacy model file
`build_support/contexts/legacy/game/replay_save.cpp` and the naked-asm owner
`build_support/exact/game/replay/replay_large_runtime.cpp` (no other region
used it). Byte-exact C++ 89.3% -> 89.8%; equivalent regions 13 -> 12.

## What closed it

The search agent's rig (`equivalence.py`, model + the replay_save cluster
context) reached 0 differing bytes with these changes to the model:

- The sprintf arguments were wrong (a semantic bug). The version line is
  `sprintf(out, "Version %s\r\n" @0x0046E5C8, "1.00a" @0x0046E5D8)`. The
  model had the two symbol names swapped, so it passed "1.00a" as the
  format and pushed the two pointers in the wrong order.
- The pool-size expressions read through inline helpers
  (`ReplayPool_Size`, `ReplayPool_InputCount`), and each figure is computed
  again at each use. The stage loop is a plain
  `for (stage = 0; stage < 8; ...)`.
- The summary stores follow retail order: stage count, then score, then slow
  rate. The slow rate is the inlined `Fps_SlowRate` (the 0x00421F80 body).
- The shared-file writer 0x0044B740 is a `__forceinline WriteShared`
  helper. Each call site has its own `written` local, and the helper returns
  early when the handle is -1.
- The compressor's out-parameter is a block-scoped local around
  `Lzss_Compress` + `free`. This fixed the frame (the -8/-4/+4 stack-slot
  shifts).
- `WriteFile`/`CloseHandle` are `__declspec(dllimport)` declarations, so
  calls on one path share one loaded import pointer. The cluster binds
  `__imp__WriteFile@20` = 0x004660D4, `__imp__CloseHandle@4` = 0x004660CC and
  `__imp__LeaveCriticalSection@4` = 0x004660B4 as absolute data symbols.
- The score is read through `ReplayGameCounters g_globals_score`
  (0x00474C44). Its address escapes in the link: the driver passes
  `&g_globals_score` to a function that never runs. So a store through any
  pointer may change the score, and that gives retail's load/store order
  around the summary.
- Chunk padding is the direct expression
  `if (len % 4 != 0) out += 4 - len % 4;` with no `remainder` local.

## Cluster

The cluster compiles the rig's translation unit (the rig's other source
was the empty stub). The driver `replay_save_00429b60_context.cpp` includes
the save routine's source, then the byte cipher `replay_save/encrypt.cpp`.
The cipher is an anchor at 0x0044B220 (size 307), so both calls pass the key
in AL and bake the retail displacement. Next come two compiler-context
functions:

- the escape function `ReplaySaveScoreEscape`, the rig's padding function
  renamed, parked as an anchor at 0x0044B3A0 (size 26);
- the synthetic stdcall caller `ReplaySaveCompilerContext_00429b60`, the
  link entry (context, 0x0044B360, 61 bytes). It reaches the save routine and
  the escape through volatile function pointers.

Only the save routine is selected (DIFFBYTES 0). The old unregistered
manifest had a 23-byte context, and it left the rig's padding function inside
a gap section. The generator
`matching2/build/experiments/goal_2026_11_01/promote_replay_save/gen.py`
rebuilds the manifest and the driver from the old manifest: it adds the
`__imp__*` slots and the player/entity/types headers, and derives the gaps
from the sorted items.
