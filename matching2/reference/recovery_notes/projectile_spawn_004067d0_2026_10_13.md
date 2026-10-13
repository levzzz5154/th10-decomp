# Projectile cell spawner `0x004067D0` — semantic cluster in progress

Status: not yet EXACT. Closest result: the whole-program schema-2 cluster
`layout/ltcg/projectile_spawn_runtime.json` builds and places the compiled body
at `0x004067D0` with the EXACT 1472-byte retail extent (the section-size gate
passes; the loop-head alignment pad `jmp +9; lea esp,[esp]` appears at the same
address as retail). 1159 of 1472 bytes differ - the remaining divergence is
register assignment (manager in EDI loaded after the pushes vs retail EAX at
entry; zero/attempts in ESI/EDX vs retail EDI/ESI) and per-block ordering.
The `continue`-based loop bottom (attempts < 2000 → continue; return 1) was
what fixed the frame and produced the pad. See also
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
4. RESOLVED: Spawn's section now compiles to the EXACT 1472-byte extent (the
   `continue`-based loop bottom - `attempts < 2000` → continue, then
   `return 1` - produced the retail frame, loop-head alignment pad and
   short-loop-back shape). The remaining 1472-byte content diff is register
   assignment only: manager in EDI (loaded after the pushes) vs retail EAX
   (hoisted at entry); zero/attempts in ESI/EDX vs retail EDI/ESI. Ten source
   spellings of the manager lifetime (long local, disjoint fresh reads,
   exit-only re-reads) did not move the allocator.
5. Main's priority-law coverage reduction was also probed: caching the records
   base in a local (so the manager pointer's remaining reads are the entry
   pair plus the exit store) grew the body to 1476 and left the manager in
   ESI with an immediate-compare zero - the allocator still did not hand the
   manager EAX at entry. The scan's zero constant also became an immediate
   (`cmpw $0x0`) in that variant, removing the zero register entirely.
6. The ScanCells drift (210 vs 194) is the coupled pair allocation: the /GL
   pass promoted Spawn's pattern→EBX but did NOT promote ScanCells'
   pattern→EAX (my compiled ScanCells re-loads the pattern from its stack
   slot and RETs 8). A synthetic hot-loop caller anchor (the old context
   trick) did not trigger the promotion. The entry function choice (Tick
   instead of ScanCells) also did not.

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

## 2026-10-13 addendum 2: THE VOLATILE-PARAMETER BREAKTHROUGH

The manager-EAX hoist is SOLVED: declare the manager parameter
`volatile` (`ProjectileManager_004073e0* volatile manager`) and split its
reads into three disjoint clusters:

1. one non-volatile copy at entry (`spawn_manager = (…)manager`) covering the
   record load and the five scan wraps - one candidate, no calls in range,
   hoisted to EAX at entry (the compiler now emits retail's exact
   `mov eax,[esp+4]; mov ecx,[esp+8]` two-hoisted-loads prologue, `push ebp;
   mov ebp,[eax+10h]; push esi; push edi; xor edi,edi; xor esi,esi` - byte
   identical through the alignment pad);
2. a fresh volatile read for the StartScript animations argument;
3. a fresh volatile read for the exit cursor store.

Volatile reads cannot be CSE-merged, so the exit read is a separate short
candidate (retail's `[esp+24h]` reload) instead of stretching the entry
candidate across four calls. With this spelling the prologue is byte-identical
to retail and the diff fell to 272/~770 lines (from 355). The residual is
branch-form tie-breaks in the scan tail: the model emits `jge return-block`
(6 bytes) where retail has `jl body(2) + jmp return(2)` at the two
attempts-check sites, plus the loop rotation direction (the model rotated the
scan loop; retail's back-edge is `jl 0x4067F0` to the state check).

## 2026-10-13 addendum: the manager reference census

Reference counts through the manager pointer inside the scan (the candidate's
covered blocks are identical in both):

| use | retail (EAX) | model (EDI) |
| --- | ---: | ---: |
| record load at entry | 1 (`mov ebp,[eax+10h]`) | 1 |
| scan wraps (`lea ebp,[eax+60h]`) | 5 | 5 |
| exit cursor store | 0 in-range (re-reads `[esp+24h]` - a fresh candidate) | 2-3 (CSE'd into the entry candidate's range) |
| StartScript animations | 0 in-range (fresh read after the call) | 1 |

The in-scan counts MATCH (6 = 6). The difference is that the model's exit and
StartScript reads were CSE-merged into the entry candidate, stretching its
live range across three calls (Angle_NormalizeSum, Entity_StartScript, Tick,
RunAnimationVm) - which is exactly why it earned a callee-saved register.
Retail's compiler kept the exit read as a separate short candidate. Four
spellings of the exit read (fresh parameter reads, disjoint ranges, the
records_base cache) all got CSE-merged anyway; the CSE across the calls is
legal (the stack argument cannot be modified by callees) and the compiler
exercises it. The remaining unknown is what made retail's compiler split the
candidate - possibly that the retail source's exit went through a different
expression shape than the entry (e.g. the manager re-derived from the record
pointer rather than re-read from the argument).
