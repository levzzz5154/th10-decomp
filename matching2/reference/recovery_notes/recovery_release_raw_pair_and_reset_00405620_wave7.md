# 0x00405620 `ReleaseRawPairAndReset` — **NOT EXACT**: the copy order does *not* flip in the merged cluster

2026-09-19, wave 7. Region `0x00405620..0x004056A9` (137 bytes,
`asm_Recovery_ReleaseRawPairAndReset_00405620`) was re-tested in the
configuration `entity_player_helpers_00401de0_00405d00_00405620_004059f0.md`
left open: **merged into `layout/ltcg/bullet_manager_load_scripts_0040ae70.json`**,
where `Scheduler_Remove` (0x00449F60), its registration pair and
`src/game/scheduler_tasks.cpp` are already `additional_sources`, i.e. with the
real callee bodies selected and the landed extents (`131/131/52/114`).

**Verdict: the ordering does not flip.** The merged configuration reproduces the
documented near-miss byte for byte — emitted **137 bytes = retail 137**, exactly
**4 differing bytes**, first difference at **+0x2F**:

```text
candidate +0x2E: 8B D7 8B CE   mov edx,edi; mov ecx,esi
retail    +0x2E: 8B CE 8B D7   mov ecx,esi; mov edx,edi
same pair again at +0x62 (0x00405682): candidate mov edx,edi; mov ecx,esi, retail mov ecx,esi; mov edx,edi
```

Everything else in the 137 bytes — including the whole prologue
(`push ebx / mov ebx,ds:0x4660B0 / push ebp / mov ebp,ds:0x4660B4 / push esi /
mov esi,[eax+8] / test esi,esi / push edi / mov edi,ds:0x491BE4 / je`), the
second block's stack reload `mov ecx,[esp+0x14]`, the two `call ebx` / `call ebp`
indirect import calls, the `inc/dec byte ds:0x49231C` pair, the store to
`0x004776EC` and `ret 4` — is byte-identical. No maintained file was modified;
`regions.json` and the layout were touched only inside the scratch copy
`/tmp/ReleasePairRepair/msvc`.

## Measured deltas, all three configurations

| configuration | emitted | differing bytes | first diff | first differing instruction |
| --- | ---: | ---: | ---: | --- |
| **A. merged** (requested): callee `Scheduler_Remove` selected in this cluster, extents 131/131/52/114 | **137** | **4** | **+0x2F** | `+0x2E` got `8b d7` `mov edx,edi`, want `8b ce` `mov ecx,esi` |
| B. same shape, removal call bound opaquely to 0x00449F60 (`@Scheduler_RemoveOpaque_00449f60@8` → 0x00449F60, `relative_code`) | **137** | **4** | **+0x2F** | identical |
| C. A with `@Scheduler_Remove@8` added to the layout `roots` (public ABI pinned) | **137** | **4** | **+0x2F** | identical |

Callee selection therefore makes **no** difference: the two argument moves are
still materialised caller-side, in the wrong order, in all three.

Probe (configuration A, `--project /tmp/ReleasePairRepair/msvc --show 30`); the
other 14 cluster regions keep their landed extents and stay exact:

```text
0x004055c0      84 bytes  _asm_Recovery_InstallPairSetFlags_004055c0@4  EXACT
0x00405620     137 bytes  _ReleaseRawPairAndReset_00405620@4  DIFFERENT
  first difference at 0x0040564f
  expected: ce 8b d7 e8 09 49 04 00 68 74 22 49 00 ff d5 fe 0d 1c 23 49 00 8b 4c 24 14 8b 71 0c 85 f6   0x0040564e: 8b ce  mov    ecx,esi
  actual:   d7 8b ce e8 09 49 04 00 68 74 22 49 00 ff d5 fe 0d 1c 23 49 00 8b 4c 24 14 8b 71 0c 85 f6   0x0040564e: 8b d7  mov    edx,edi
0x004056b0      85 bytes  _asm_Recovery_CreateFixedState_004056b0  EXACT
0x0040ae70     134 bytes  _BulletManager_LoadScripts_0040ae70@4  EXACT
0x0040af90      86 bytes  ?BulletManager_Create_0040af90@@YGPAUBulletManagerState_0040af90@@XZ  EXACT
0x0041ad90      84 bytes  _asm_Recovery_InstallPairClearFlags_0041ad90@4  EXACT
0x0041c030      98 bytes  ?ScoreObject_Initialize@@YIPAUScoreObject@@PAXPAU1@@Z  EXACT
0x0041c120     146 bytes  _asm_ScoreDisplay_RegisterTasksRetail_0041c120@4  EXACT
0x0041c290      91 bytes  _asm_ScoreManager_CreateAndInitRetail_0041c290  EXACT
0x00449ae0     131 bytes  _Scheduler_RegisterPrimary@12  EXACT
0x00449b70     131 bytes  _Scheduler_RegisterSecondary@12  EXACT
0x00449f20      52 bytes  _Scheduler_RemoveLocked@8  EXACT
0x00449f60     114 bytes  @Scheduler_Remove@8  EXACT
0x0044a0c0     105 bytes  ?Joystick_Probe_0044a0c0@@YGFXZ  EXACT
0x0044b810     201 bytes  ?Append@TextLog_0044b810@@QAAPADPADZZ  EXACT
NOT EXACT
```

`probe --json` for the region: `size 137`, `different_bytes 4`,
`first_difference 0x0040564F`, `expected_instruction "0x0040564e: 8b ce  mov ecx,esi"`,
`actual_instruction "0x0040564e: 8b d7  mov edx,edi"`, zero relocations pending
(the cluster exports already-linked bodies; the `call 0x449F60`, the two import
loads and all four globals are resolved absolutely). The scratch manifest +
merged layout also pass `build_msvc.validate_project` (4425 regions / 2395
translation units), so nothing but these four bytes stands in the way.

## What the shape needed, and why it is now right

The allocation was the first half of the problem, and it is *solved*: the
construct that reproduces retail's registers is an explicit **`Scheduler*
scheduler` local read from `ds:0x491BE4` immediately before each `if`** (plus a
`SchedulerTask* task` local dead at the call):

| source shape (merged cluster, callee selected) | emitted | result |
| --- | ---: | --- |
| `scheduler` local before each `if`, `task` local, `Scheduler_Remove(task, scheduler)` (**candidate**) | **137** | retail's prologue *and* epilogue exactly: EBX = `EnterCriticalSection` (0x4660B0), EBP = `LeaveCriticalSection` (0x4660B4), ESI = task, EDI = scheduler; pair re-read from the stack in block 2; 4 bytes off (the two copies) |
| same, but the scheduler passed as the global expression `data_00491be4` | 129 | pair cached in ESI, task reloaded from `[esi+8]`, scheduler in volatile EDX |
| pair members passed directly (`pair->callback_008`, `scheduler`) | 135 | scheduler load sunk below the `Enter` call |
| no locals at all (`pair->callback_008`, `data_00491be4`) | 129 | pair cached, scheduler in EDX |
| `Scheduler *const` locals + second-block reload (no re-assignment) | 140 | pair cached in ESI, `push esi` prologue |
| import-pointer locals (`EnterCriticalSectionFn enter = *(EnterCriticalSectionFn*)&data_004660b0;` … `call` through the local), lab style | **137** | right extent, **16** differing bytes: the allocator swaps EBX/EBP (`mov ebx,ds:0x4660B4`), i.e. the import registers come out the other way |
| `(void*)`/`(SchedulerTask*)` casts, redeclared `noinline` callee, reordered locals, temp-then-call `(t = task), (s = scheduler)` | 137 each | all identical to the candidate — 4 bytes off, same two instructions |
| **member call** `((TaskOps *)task)->Remove(scheduler)` with the member symbol `?Remove@TaskOps@@QAIXPAUScheduler@@@Z` bound to 0x00449F60 | 137 | identical to the free call — 4 bytes off, and the `this` copy is still emitted **second** |

So the *only* shape that reproduces retail's register ownership is the candidate,
and its residual is confined to the order of two independent 2-byte copies.

## Why no source shape can fix the order (toolkit-level, not modelling)

The two copies move into **ECX** (task) and **EDX** (scheduler) — the physical
registers are fixed by the callee, whose 114-byte body is landed and exact. Only
their *emission order* is ours to influence, and this toolkit's c2 emits them
**param2-first**, while retail's emits **param1-first**:

1. **Image census (retail).** Scanning the `.text` bytes: 52 occurrences of
   `8b <ecx>,r32; 8b <edx>,r32` and **4** of the reverse; 40 of the 52 are
   immediately followed by a `call`, and the only reverse-order site followed by
   a call is an **indirect** call (`0x00428780 call *%eax`). The release idiom
   itself — `mov ecx,esi; mov edx,edi; call 0x00449F60` — appears **27 times
   and never in the reverse order**. Source pairs vary (`ecx<-r7, edx<-r3`,
   `ecx<-r5, edx<-r1`, …), so retail is ordering by **argument/register
   ascending**, not by source register.
2. **This toolkit.** Every configuration above (and the whole-cluster builds)
   emits `mov edx,edi; mov ecx,esi`. Two throwaway TUs isolate it, both compiled
   with the cluster's own profile (`/O2 /Gz /MT /Gy /G6 /GF /GS /Zl`):
   * a free `__fastcall f(void*, void*)` called with two values held in
     callee-saved registers → `mov %ebp,%edx; mov %edi,%ecx; call`;
   * the same call written as a `__fastcall` **member** call `t->RemoveA(s)`
     (`?RemoveA@TaskA@@QAIXPAUSched@@@Z`) → byte-identical caller, still
     `mov %ebp,%edx; mov %edi,%ecx` — so `this` is *not* ordered first, and the
     member/`this` hypothesis for retail's 27 sites is ruled out;
   * a three-argument fastcall → `push <arg3>; mov %ebx,%edx; mov %edi,%ecx;
     call`, i.e. the traversal is uniformly **argument-list-reverse**.
3. **Flag insensitivity.** The minimal TU emits the same reverse order under
   `/G5`, `/G6`, `/G7`, with and without `/GS`, with `/Ot` and even `/O1`, so
   this is not a profile knob.
4. **Where the two compilers agree.** When one operand is a *memory* load the
   load is scheduled first in both: `0x00449F20` (`Scheduler_RemoveLocked`, 52
   bytes, exact in this same cluster) emits `mov 0x4(%esp),%edx; mov %esi,%ecx`
   in retail and in our build. Only the register-register pair diverges.

Consequence: because the copy *targets* are pinned by the exact callee
convention, the residual is structural. It is not reachable by any declaration,
expression form, local, anchor, caller, or callee-visibility change — which is
what the earlier note's "investigate an original class/member declaration or
front-end expression shape" item was still hoping for; that item is now closed
(member call proved equivalent, and the reverse traversal is uniform).

## Registers retail's callers use, and whether the emitted body keeps them

All five direct call sites pass the pair on the **stack** and rely on `ret 4`:
`0x004056EF` (`push ebx`, from `Recovery_CreateFixedState_004056b0`),
`0x00405711` (`push esi`), `0x00405735` (`push esi`, `FUN_00405730`),
`0x0040A2AA` (`push esi`, `FUN_0040A1A0`), `0x00417FD5` (`push esi`, inside
`FUN_00417C80`). No caller keeps a live argument register at the call. The
candidate keeps that ABI exactly (rooted `__stdcall`, pair read from `[esp+4]`,
`ret 4`), and keeps retail's internal registers: EBX = `EnterCriticalSection`,
EBP = `LeaveCriticalSection`, ESI = the task, EDI = the scheduler object
`ds:0x491BE4`, with the same `push ebx/ebp/esi/edi` … `pop edi/esi/ebp/ebx`
order. The rest of each block (the `call ebp` leave, the depth decrement, the
second block's `mov ecx,[esp+0x14]` stack reload and its `mov esi,[ecx+0xC]`)
matches byte for byte.

## The 21 sibling regions that will hit the same wall

The same inlined two-callback release idiom — hence the same reverse copy order —
occurs in these still-`asm` regions; none of them should be modelled as semantic
C++ until the copy-order residual is understood or the toolkit is replaced:
`0x00405F70`, `0x00408AF0` (`0x00408B7A`), `0x0040A1A0`, `0x0040AF00`,
`0x0040B7B0`, `0x0040D530`, `0x00413300`, `0x004133F0`, `0x00413450`,
`0x004145F0`, `0x00417C80`, `0x00418EE0`, `0x0041ADF0`, `0x0041C1C0`,
`0x0041FB50`, `0x00422220`, `0x00424ED0`, `0x0042B570`, `0x0042BC30`,
`0x0042CB60`, `0x0043CB00`.

## Candidate artifacts (scratch only; nothing landed)

`/tmp/ReleasePairRepair/msvc` holds the exact state that produces the table
above: `src/game/recovery_release_raw_pair_and_reset_00405620.cpp`,
`layout/ltcg/bullet_manager_load_scripts_0040ae70.json` (patched) and the
scratch `regions.json`. The driver
`layout/ltcg/bullet_manager_load_scripts_0040ae70_context.cpp` is **unchanged**
(`roots` already force `ReleaseRawPairAndReset`'s public ABI; the function is
referenced through `roots`, so no call has to be added to the synthetic
context). The layout patch is three insertions:

```json
// additional_sources +=
"src/game/recovery_release_raw_pair_and_reset_00405620.cpp"

// functions +=
{ "name": "ReleaseRawPairAndReset_00405620",
  "symbol": "_ReleaseRawPairAndReset_00405620@4",
  "section": ".text$00_wrelease",
  "address": "0x00405620", "size": 137,
  "actual_abi": "pair on the stack; RET 4",
  "source": "src/game/recovery_release_raw_pair_and_reset_00405620.cpp" }

// gaps: .text$00_wlayout shrinks 156 -> 12 (0x00405614..0x00405620) and a new
// trailing gap is inserted after the function
{ "section": ".text$00_wlayout",  "address": "0x00405614", "size": 12 },
{ "section": ".text$00_wxlayout", "address": "0x004056A9", "size": 7 },

// roots += "_ReleaseRawPairAndReset_00405620@4"
// (the pre-existing absolute binding _asm_Recovery_ReleaseRawPairAndReset_00405620@4
//  -> 0x00405620 stays, so Recovery_CreateFixedState keeps its opaque call and
//  stays exact; the region record's symbol becomes _ReleaseRawPairAndReset_00405620@4
//  and player.cpp drops the naked body)
```

The section names sort between `.text$00_vinstall`/`.text$00_wlayout` and
`.text$00_xfixed`, which is what keeps `0x004056B0` (`CreateFixedState`) on its
address while the region is spliced in — verified by the 14 EXACT lines above.

The candidate source (`src/game/recovery_release_raw_pair_and_reset_00405620.cpp`):

```cpp
// 0x00405620..0x004056A8 (137 bytes): ReleaseRawPairAndReset
//
// Conditional callback removal for the fixed-state pair: each of the two
// scheduler callbacks at +8 and +0xC is unlinked under the scheduler critical
// section with the depth byte bracketing it, and the published-pair global is
// cleared.  Retail reaches Scheduler_Remove (0x00449F60) through the
// whole-program register agreement, so this body is compiled in the same
// native-LTCG link as that callee and the two installers it belongs to.
#include "th10/game/scheduler.hpp"
#include "th10/platform/thread_sync.hpp"

struct RawPair_00405620 {
    unsigned char pad_000[8];
    SchedulerTask *callback_008;
    SchedulerTask *callback_00C;
};

extern "C" Scheduler *data_00491be4;
extern "C" void *data_004776ec;

#pragma code_seg(".text$00_wrelease")
extern "C" __declspec(noinline) void __stdcall
ReleaseRawPairAndReset_00405620(RawPair_00405620 *pair) {
    Scheduler *scheduler = data_00491be4;
    SchedulerTask *task = pair->callback_008;
    if (task) {
        EnterCriticalSection(&g_thread_synchronization.critical_sections[0]);
        ++g_thread_synchronization.scheduler_lock_depth;
        Scheduler_Remove(task, scheduler);
        LeaveCriticalSection(&g_thread_synchronization.critical_sections[0]);
        --g_thread_synchronization.scheduler_lock_depth;
    }
    scheduler = data_00491be4;
    task = pair->callback_00C;
    if (task) {
        EnterCriticalSection(&g_thread_synchronization.critical_sections[0]);
        ++g_thread_synchronization.scheduler_lock_depth;
        Scheduler_Remove(task, scheduler);
        LeaveCriticalSection(&g_thread_synchronization.critical_sections[0]);
        --g_thread_synchronization.scheduler_lock_depth;
    }
    data_004776ec = 0;
}
#pragma code_seg()
```

Emitted bytes (candidate) against retail; the only differing offsets are
`0x2f`, `0x31`, `0x63`, `0x65`:

```text
candidate:
  8b 44 24 04 53 8b 1d b0 60 46 00 55 8b 2d b4 60
  46 00 56 8b 70 08 85 f6 57 8b 3d e4 1b 49 00 74
  23 68 74 22 49 00 ff d3 fe 05 1c 23 49 00 8b d7
  8b ce e8 09 49 04 00 68 74 22 49 00 ff d5 fe 0d
  1c 23 49 00 8b 4c 24 14 8b 71 0c 85 f6 8b 3d e4
  1b 49 00 74 23 68 74 22 49 00 ff d3 fe 05 1c 23
  49 00 8b d7 8b ce e8 d5 48 04 00 68 74 22 49 00
  ff d5 fe 0d 1c 23 49 00 5f 5e 5d c7 05 ec 76 47
  00 00 00 00 00 5b c2 04 00
retail:
  8b 44 24 04 53 8b 1d b0 60 46 00 55 8b 2d b4 60
  46 00 56 8b 70 08 85 f6 57 8b 3d e4 1b 49 00 74
  23 68 74 22 49 00 ff d3 fe 05 1c 23 49 00 8b ce
  8b d7 e8 09 49 04 00 68 74 22 49 00 ff d5 fe 0d
  1c 23 49 00 8b 4c 24 14 8b 71 0c 85 f6 8b 3d e4
  1b 49 00 74 23 68 74 22 49 00 ff d3 fe 05 1c 23
  49 00 8b ce 8b d7 e8 d5 48 04 00 68 74 22 49 00
  ff d5 fe 0d 1c 23 49 00 5f 5e 5d c7 05 ec 76 47
  00 00 00 00 00 5b c2 04 00
```

(The two `e8` operands are the two `call 0x00449F60` rel32s: `09 49 04 00` =
`0x00449F60 - (0x00405652 + 5)`, `d5 48 04 00` = `0x00449F60 - (0x00405686 + 5)`,
both already resolved because the cluster exports linked bodies.)

One further probe, `__fastcall Scheduler_Remove(SchedulerTask*, Scheduler*&)`,
did not produce a valid cluster image (the layout could not be tiled and the
native link's entry/base differed), and it is not a candidate for the same
reason as the rest: a reference parameter still materialises the scheduler in
EDX.

## Next-step options (in order of cost)

1. **Leave the region as assembly** (recommended): 137 bytes of naked body is
   already exact, and the residual is a toolkit-wide copy-order property that no
   source construct reaches.
2. If the project ever wants it: the only lever left is the copy insertion order
   in c2 — e.g. comparing this toolkit build against another MSVC 13.10 build
   (retail's own `cl.exe` build number) on the two-instruction minimal TU above
   would settle whether a different c2 revision emits param1-first. Everything
   else (caller, callee, declaration, expression, flags, extents, roots) has now
   been measured and ruled out.
