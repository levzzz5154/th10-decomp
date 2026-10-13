# Projectile cell spawner `0x004067D0` — semantic cluster in progress

Status: not yet EXACT. Closest result: the whole-program schema-2 cluster
`layout/ltcg/projectile_spawn_runtime.json` builds and places the compiled body
at `0x004067D0` with the retail `sub esp,0x14` frame; the compiled contribution
is 1484 bytes against the fixed 1472-byte retail extent, with 355 of ~770
disassembly diff lines remaining (both sides counted). See also
projectile_runtime_004067d0_00406d90.md for the earlier failed attempts this
session supersedes (the EBX demotion now works).

## What exists

- Readable C++ model (private working copy, to become
  `src/game/enemy_projectile_spawn.cpp` once it probes EXACT): defines
  `?SpawnPatternCell_004067d0@@YGHPAUProjectilePattern_004073e0@@PAUProjectileManager_004073e0@@HHM@Z`
  with the 5-argument stdcall spelling the header
  `include/th10/game/enemy_grid_scan_004073e0.hpp` already declares; the /GL
  pass demotes the blueprint to EBX exactly as retail does (verified: the
  compiled body reads the rows through `[ebx+0x1F6]`).
- Record/glossary types in
  `include/th10/game/projectile_spawn_runtime_004067d0.hpp`
  (`ProjectileSpawnRecord` 0x7F0 with static offset checks, `ProjectileSpawnManager`,
  `ProjectileBlueprint_004067d0`, `SpawnCommandRecord`, `PlayerSchedulerRecord`,
  `ScoreGameplayPolarVector`).
- Schema-2 cluster `layout/ltcg/projectile_spawn_runtime.json`: entry
  `?EnemyGrid_ScanCells_004073e0@@...` (src/game/enemy_grid_scan.cpp, needs a
  one-line `#include` of the queue_pan anchor), source
  `src/game/enemy_projectile_spawn.cpp`, ABI anchors at the retail addresses for
  `?Entity_StartScript_00404f30@@...` (195 bytes compiled),
  `?SetScorePolar@ScoreGameplayPolarVector@@QAEPAU1@MM@Z` (24),
  `?QueuePan@SoundQueue@@QAEXHM@Z` (138), gap tiling verified to place every
  function at its retail address (LINK 16-aligns each contribution; gaps
  absorb the slack).
- Verified mechanics: /OPT:REF drops anchors nothing calls (they must either be
  called from a selected body or be dropped from the manifest); zero-length
  contributions of stripped anchors duplicate map entries and fail
  `parse_map`; a `/GS` cookie appears when a local whose address escapes is
  spelled with a char-array or `memset(&struct, ...)` shape — an
  `unsigned int[]` local with a decayed `memset` avoids it, matching retail's
  cookie-free frame.

## Verified retail ABI

`EBX` = spawn blueprint (live-in from the caller), stack `(manager, column,
row, aim)` `RET 0x10`; `ECX`/`EDX` dead on entry. The callee never saves EBX;
the caller needs it after the call. Two compiler jump tables sit at `0x00406D58`
(9 entries, layout switch) and `0x00406D7C` (5 entries, death-table switch)
inside the region, so a compiled body must keep them in its own section — the
extant approach works for this region, unlike `0x00406D90`.

## Residual class

Whole-program register allocation and frame shape. The compiled body already
matches retail's x87 idioms (the `fsubr st(1)` interpolation form after naming
the blueprint's `y_head` read, `fimul`/`fidiv` integer forms, the three-product
velocity shift kept on the x87 stack through `Vec3 shift = velocity * scale`),
but differs in: manager kept in EDI across the scan instead of EAX with a
stack-arg reload at exit; the zero/5 constants in ESI/EAX instead of EDI/EDX;
frame `sub esp,0x8`/`0x20` instead of `0x14`; no loop-head alignment pad; the
command-copy `rep movsd` interleavings. 80 diff hunks across the whole body —
the divergence is pervasive, not localized.

## Next lever

Continue the byte-golf loop in `scratch/projectile/msvc` (working copy
`scratch/projectile/spawn_golf.cpp`; sync with `/tmp/sync.sh` equivalent):

1. Force the `sub esp,0x14` frame (five slots: x, y, the stored third product
   plus two the allocator reserves) — most `[esp+...]` operand diffs collapse
   once the frame matches.
2. Make the manager arg die at the scan: re-read the parameter for the final
   cursor stores (retail reloads `[esp+0x24]` at exit) so the allocator picks
   EAX instead of a callee-saved register (tried; no effect yet).
3. Re-check the scan register assignment (retail: `esi`=attempts, `edi`=zero,
   `edx`=5, manager in `EAX` loaded at entry; model: `edx`/`esi`/`eax`, manager
   in `EDI` loaded after the pushes) and the loop-head alignment pad
   (`jmp +9; lea esp,[esp]; mov edi,edi`).
4. Spawn's death switch lowered to a 3-entry jump table (12 bytes at the
   section tail, targets inside the body) where retail has the cmp/ja +
   5-entry form at 0x00406D7C - the 5 dense cases must lower as retail's
   single table; check the switch spelling against the retail shape.
5. The compiled caller `0x004073E0` co-evolves: its contribution drifted to 209
   bytes (retail 194) because the pair's joint demotion picked different
   registers (model caller holds manager in `EBP`, aim in `EAX`; retail the
   reverse). The pair must reach the fixed point together.
5. Working state (all preserved in-tree):
   `scratch/projectile/spawn_golf.cpp` (Spawn model),
   `scratch/projectile/tick_golf.cpp` (Tick model),
   `scratch/projectile/sync.sh` (copies both into the reflink scratch project
   `scratch/projectile/msvc` whose regions.json already carries the semantic
   conversions, the 1604-byte Tick extent and the dropped table data regions),
   cluster manifest + seven anchors in `matching2/msvc/layout/ltcg/`. Probe:
   `PYTHONPATH=. python3 matching2/tools/matching/probe.py --project
   scratch/projectile/msvc --source src/game/enemy_projectile_spawn.cpp
   --output matching2/build/probe-<name>`. The real tree keeps the assembly
   regions until the gate passes.
