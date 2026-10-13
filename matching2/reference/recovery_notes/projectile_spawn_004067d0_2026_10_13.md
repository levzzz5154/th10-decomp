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

## 2026-10-13 addendum: the schema-1 composition effect

The 276-line state was achieved in the schema-2 composition (Spawn and Tick
co-compiled with the scan as a separate selected function). After switching to
schema 1 (the driver TU textually including the verbatim scan + Spawn, Tick as
an additional source), the whole-program allocator state changed and the
Spawn prologue's two-hoisted-loads shape (mov eax,[esp+4]; mov ecx,[esp+8])
is no longer produced — the allocator instead spills both arguments to the
frame (sub 0x18; mov eax,[esp+1c]; mov ecx,[esp+20]). The volatile-parameter
and three-cluster spellings that fixed the prologue in the schema-2
composition do not reproduce in schema 1 because the /GL allocator's
candidate set depends on the whole-program IL shape (the scan as a selected
function vs a context body changes the callee-reachable set).

The 421-line schema-1 state is the current best: the extent is 1500 bytes
(28 over the 1472 retail) with the prologue/scan structure matching but the
entry shape and the volatile-parameter mechanics differing. The path forward:
either (a) return to schema 2 with Tick included (the 276-line state was
green on the size gate there) and find the ScanCells promotion fix in that
composition, or (b) stay in schema 1 and find a source spelling that
reproduces the two-hoisted-loads entry under the changed allocator state.

## 2026-10-13 final addendum: the composition dependence

The two-hoisted-loads prologue (mov eax,[esp+4]; mov ecx,[esp+8]) is COMPOSITION-
DEPENDENT: it appears in the schema-2 link with 3 selected functions when the
volatile parameter forces the eager load, but NOT in the schema-1 link with the
scan as a context body, and NOT in the schema-2 link without the volatile
parameter. The /GL allocator's block walk and candidate priority depend on the
entire link's IL shape, making single-function source spelling insufficient to
control the entry shape deterministically. The volatile-parameter spelling is
the only source-level mechanism that produces the eager load — but it also
causes per-wrap re-reads (+16 bytes) because the compiler re-reads the volatile
parameter at each use instead of caching the dereferenced result.

The continuation requires either:
1. a source spelling that combines the volatile-forced eager load with
   non-volatile cached wraps (the const_cast intermediate was tried but the
   compiler tracks through it);
2. the tracer-based deterministic approach (winedbg+gdb on link.exe's c2.dll
   during the /LTCG phase) to identify the exact coverage-set difference;
3. accepting the 1464-1488 byte compiled size and finding the remaining -8/+16
   bytes of legitimate body content to compensate.

## 2026-10-14 addendum: the entry-copy lever and the tie-break law

### The priority tie-break (read from c2.dll disassembly, NOT traced)
The candidate insertion at c2 RVA 0x000A9E2B-0x000A9E42 (image base 0x10700000,
file offsets map 1:1 through the .text section):
```
a9e2b: mov 0xc(%edi),%ecx     ; current node's priority
a9e2f: mov 0xc(%eax),%esi     ; new candidate's priority
a9e32: cmp %ecx,%esi
a9e34: jg  insert             ; higher priority inserts EARLIER (list is
                              ; descending by priority; the head pops first)
a9e36: je  tie
a9e38: (walk) mov %edi,%ecx
tie:
a9e3c: mov 0x44(%eax),%ecx
a9e3f: cmp 0x44(%edi),%ecx
a9e42: jb  walk               ; walk while current->0x44 < new->0x44 → the list
                              ; is descending by +0x44 too: the LARGER +0x44 pops
                              ; first. +0x44 is set at candidate creation
                              ; (sequence/index-like) → on ties the LATER-created
                              ; candidate wins the allocation.
```
Implication for the Tick receiver keystone: the receiver's candidate must have
strictly HIGHER priority (+0xc) than the sign constant to keep EBP — ties favor
the later-created candidate, and the receiver is created first. The priority is
live-range/loop-depth driven; the receiver's whole-function range should already
beat a block-local constant, so the EBP loss in the model points at a SPLIT
receiver live range (per-use re-derivation through the record reference), not at
the tie law.

### The entry-copy lever (new)
`sub $0x14` (the retail frame) was recovered with an entry-local volatile-style
copy of the manager parameter:
```cpp
ProjectileSpawnManager* const entry_manager =
    *reinterpret_cast<ProjectileSpawnManager* const*>(&manager);
```
This forces the manager load BEFORE the frame push (hoisted to ECX) and yields
frame 0x14 + one hoisted load — 1476 bytes (vs 1496 with the volatile parameter,
vs 1464 with the eager animations local). The pattern's matching entry copy did
not hoist (the compiler keeps the pattern read behind the pushes in ESI).
Retail's two-hoisted shape needs BOTH args hoisted; the second hoist (mov
eax,[esp+4]) did not appear in this composition — the whole-program allocator
still couples Spawn's prologue to Tick's IL (the 19:23 composition with the
older Tick IL produced the one-hoist shape at 1472 with 296 diff lines; the
current Tick IL gives 1476 at 394).

### Best current pair state (both sizes green or near)
- Spawn: 1476/1472 (+4), frame 0x14 ✓, one hoist, 394 diff lines
- Tick: 1604/1604 ✓ (the approved extent), receiver-in-EBX (retail: EBP)

## 2026-10-14 addendum: the record field types corrected by retail's encoding

Retail's Tick encoding proves these ProjectileSpawnRecord fields are INT
(plain `mov` stores from the command values), not float as first modeled:
- +0x6D8, +0x6DC (the case-0x40 timer-companion stores: mov ecx→6d8,
  mov edx,[esi+0xC]→6dc)
- +0x7DC (the case-0x2000 store)
- +0x6A4, +0x420 (turn_420), +0x6F8, +0x710 (the motion-flag case stores)
The float typing had forced fildl/fstps conversion pairs at every site —
8 conversion ops total. After the retype the model reproduces retail's int
moves; the remaining float sites (0x660, 0x6C8 — the AngleFromPoint results)
match retail's fstps.

The header matching2/msvc/include/th10/game/projectile_spawn_runtime_004067d0.hpp
is updated (field_6d8/6dc/7dc/6a4/6f8/710/turn_420 → int). Size consequence:
the Tick allocation GREW +24 (1608→1628) — the whole-program allocator
reshuffled; the case-order convergence (the shared timer-reset jump target)
is the next lever to recover the bytes.
