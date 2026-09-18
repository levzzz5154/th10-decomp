# Region `0x0041AD90` (84 bytes) - wave 5

Date: 2026-09-19. Status: **EXACT**. Recovered as `?Recovery_InstallPairClearFlags@@`
and landed inside the existing cluster `layout/ltcg/bullet_manager_load_scripts_0040ae70.json`
(merge pattern, lesson 5): the region's source is a new file, but the register it is
entered with is only derivable in the link that already co-compiles the scheduler
registration pair.

```
$ python3 matching2/tools/matching/probe.py \
      --source src/game/recovery_install_pair_clear_flags_0041ad90.cpp \
      --project matching2/msvc --output /tmp/InstallPairClearFlags/maintained-out --show 30
0x004055c0      84 bytes  _asm_Recovery_InstallPairSetFlags_004055c0@4  EXACT
0x004056b0      85 bytes  _asm_Recovery_CreateFixedState_004056b0  EXACT
0x0040ae70     134 bytes  _BulletManager_LoadScripts_0040ae70@4  EXACT
0x0040af90      86 bytes  ?BulletManager_Create_0040af90@@YGPAUBulletManagerState_0040af90@@XZ  EXACT
0x0041ad90      84 bytes  _asm_Recovery_InstallPairClearFlags_0041ad90@4  EXACT
0x00449ae0     131 bytes  _Scheduler_RegisterPrimary@12  EXACT
0x00449b70     131 bytes  _Scheduler_RegisterSecondary@12  EXACT
0x00449f20      52 bytes  _Scheduler_RemoveLocked@8  EXACT
0x00449f60     114 bytes  @Scheduler_Remove@8  EXACT
0x0044a0c0     105 bytes  ?Joystick_Probe_0044a0c0@@YGFXZ  EXACT
0x0044b810     201 bytes  ?Append@TextLog_0044b810@@QAAPADPADZZ  EXACT
EXACT
```

The new region's complete 84-byte body differs from retail in **zero** bytes
(checked byte-for-byte out of the cluster's `bodies.obj`, including the rel32
displacements), and the ten regions the cluster already carried are still EXACT -
adding it disturbed none of them.

## What the region is

Retail `0x0041AD90..0x0041ADE3` is byte-for-byte the *clear* twin of the landed
set-flags installer `0x004055C0`: same 84-byte shape, same section order, only
four operands differ (the two callback works addresses `0x41BA00`/`0x41BA30`,
the two priorities `0x15`/`0x19`, and `and [esi+4],0xFFFFFFFD` where the set twin
has `or [esi+4],2`).

* callback cursor in **ESI** (`push esi` at +0), registration priority in **EDI**
  (`push edi` at +1, `mov edi,0x15` / `mov edi,0x19`),
* the pair live in **EBX**, which the body only reads (`mov [esi+20h],ebx`,
  `mov [ebx+8],esi`, `mov [ebx+0Ch],esi`) and never writes, so it is not saved,
* the freshly created callback's `reserved_flags` bit (`SchedulerTask.heap_owned`
  is bit 0 of the dword at +4, `reserved_flags` the upper 31, so clearing the
  first reserved bit is the in-place `and dword [esi+4],0xFFFFFFFD`),
* `Scheduler_RegisterPrimary` at priority `0x15`, `Scheduler_RegisterSecondary`
  at `0x19`, second callback published after the second registration call,
* result `0` in **EAX**, plain `RET` with no stack argument cleanup.

## Source `src/game/recovery_install_pair_clear_flags_0041ad90.cpp`

```cpp
// 0x0041AD90..0x0041ADE3 (84 bytes): ?Recovery_InstallPairClearFlags@@
//
// The clear-flags counterpart of ?Recovery_InstallPairSetFlags@@ (0x004055C0):
// it builds the two scheduler callbacks that drive a freshly created pair,
// clears the reserved flag the set-flags installer raises, publishes each
// callback on the pair and registers the pair with the scheduler's primary and
// secondary lists.
//
// Retail receives the pair in EBX - not a parameter register of any MSVC
// convention - and returns the status in EAX. As in the set-flags installer,
// the pair stays live across both registration calls while the freshly created
// callback occupies ESI and the priority EDI, so the register is a whole-program
// agreement: this source is compiled in the same native-LTCG link as the
// registration pair it calls (see
// layout/ltcg/bullet_manager_load_scripts_0040ae70.json).
#include "th10/game/scheduler.hpp"

struct RawPair_0041ad90 {
    unsigned char pad_000[8];
    void *callback_008;                 // +0x08, primary scheduler callback
    void *callback_00C;                 // +0x0C, secondary scheduler callback
};

extern "C" SchedulerTask *__stdcall SchedulerCallback_Create_00449ed0(void *callback);
extern "C" void *data_00491be4;

#pragma code_seg(".text$00e_installclear")
extern "C" __declspec(noinline) int __stdcall
asm_Recovery_InstallPairClearFlags_0041ad90(RawPair_0041ad90 *pair) {
    SchedulerTask *primary = SchedulerCallback_Create_00449ed0((void *)0x41BA00);
    primary->reserved_flags &= ~1u;
    primary->context = pair;
    Scheduler_RegisterPrimary((Scheduler *)data_00491be4, primary, 0x15);
    pair->callback_008 = primary;

    SchedulerTask *secondary = SchedulerCallback_Create_00449ed0((void *)0x41BA30);
    secondary->reserved_flags &= ~1u;
    secondary->context = pair;
    Scheduler_RegisterSecondary((Scheduler *)data_00491be4, secondary, 0x19);
    pair->callback_00C = secondary;
    return 0;
}
#pragma code_seg()
```

sha256 `3479060f55a237b51090f629dd349585503a96179ed5596abef33373c338a4c9`.

## Driver `layout/ltcg/bullet_manager_load_scripts_0040ae70_context.cpp`

```cpp
// Compiler context only: this caller is not recovered application code.
#include "../../src/game/bullet_manager_load_scripts_0040ae70.cpp"

struct BulletManagerState_0040af90;
BulletManagerState_0040af90 *BulletManager_Create_0040af90();
extern "C" void *__cdecl asm_Recovery_CreateFixedState_004056b0(void);
extern "C" int __stdcall asm_Recovery_InstallPairClearFlags_0041ad90(void *pair);

#pragma code_seg(".text$90context")
int __stdcall BulletManagerLoadScriptsCompilerContext(
        Scheduler *scheduler, SchedulerTask **tasks, int count, int priority,
        BulletManagerState_0040af90 **slots) {
    for (int index = 0; index < count; ++index) {
        SchedulerTask *task = tasks[index];
        Scheduler_RegisterPrimary(scheduler, task, priority);
        Scheduler_RegisterSecondary(scheduler, task, priority);
        Scheduler_RemoveLocked(scheduler, task);
    }
    void (__fastcall * volatile remove)(SchedulerTask *, Scheduler *) = &Scheduler_Remove;
    remove(tasks[0], scheduler);
    int created = 0;
    for (int index = 0; index < count; ++index) {
        slots[index] = BulletManager_Create_0040af90();
        if (slots[index])
            ++created;
    }
    if (asm_Recovery_CreateFixedState_004056b0())
        ++created;
    if (asm_Recovery_InstallPairClearFlags_0041ad90(tasks[0]))
        ++created;
    return created;
}
#pragma code_seg()
```

sha256 `94871cf55ef0d72f540f0cd94427e01169a2661111edbe9328bda1d43855317d`. Only the declaration and the `if (...) ++created;` call are new;
the context's own size grew 133 -> 149 bytes. The context is synthetic and is
never selected by the outer link (`build_msvc` selects only the declared
functions out of `bodies.obj`), so its growth moved nothing else.

## Layout `layout/ltcg/bullet_manager_load_scripts_0040ae70.json`

```json
{
  "schema_version": 1,
  "name": "bullet_manager_load_scripts_0040ae70",
  "source": "src/game/bullet_manager_load_scripts_0040ae70.cpp",
  "additional_sources": [
    "src/game/scheduler_tasks.cpp",
    "src/platform/text_log.cpp",
    "src/platform/joystick_probe.cpp",
    "src/game/bullet_manager_create_0040af90.cpp",
    "src/game/recovery_create_fixed_state_004056b0.cpp",
    "src/game/recovery_install_pair_set_flags_004055c0.cpp",
    "src/game/recovery_install_pair_clear_flags_0041ad90.cpp"
  ],
  "driver": "layout/ltcg/bullet_manager_load_scripts_0040ae70_context.cpp",
  "roots": [
    "?Joystick_Probe_0044a0c0@@YGFXZ"
  ],
  "headers": [
    "include/th10/game/scheduler.hpp",
    "include/th10/platform/thread_sync.hpp"
  ],
  "image_base": "0x00400000",
  "description": "BulletManager_LoadScripts and BulletManager_Create compiled with the scheduler registration/removal pair, the constant-log formatter and the joystick probe under native LTCG, so the pass keeps the manager in EBX, the callback in ESI and the registration priority in EDI. It also carries the fixed-state factory and the callback installer it calls, so the pass keeps the fixed-state pair in EBX across the installation, the release and the free. It also carries the clear-flags counterpart of the callback installer, so the pass keeps that installer's pair in EBX as well.",
  "functions": [
    {
      "name": "BulletManager_LoadScripts_0040ae70",
      "symbol": "_BulletManager_LoadScripts_0040ae70@4",
      "section": ".text$00a_loadscripts",
      "address": "0x0040AE70",
      "size": 134,
      "actual_abi": "manager in EBX; no stack argument; result in EAX; plain RET"
    },
    {
      "name": "BulletManager_Create_0040af90",
      "symbol": "?BulletManager_Create_0040af90@@YGPAUBulletManagerState_0040af90@@XZ",
      "section": ".text$00c_create",
      "address": "0x0040AF90",
      "size": 86,
      "source": "src/game/bullet_manager_create_0040af90.cpp",
      "actual_abi": "manager in EBX across the script-load and release calls; result in EAX"
    },
    {
      "name": "Scheduler_RegisterPrimary",
      "source": "src/game/scheduler_tasks.cpp",
      "symbol": "_Scheduler_RegisterPrimary@12",
      "section": ".text$10primary",
      "address": "0x00449AE0",
      "size": 131,
      "actual_abi": "task in ESI, priority in EDI, scheduler on stack; RET 4"
    },
    {
      "name": "Scheduler_RegisterSecondary",
      "source": "src/game/scheduler_tasks.cpp",
      "symbol": "_Scheduler_RegisterSecondary@12",
      "section": ".text$30secondary",
      "address": "0x00449B70",
      "size": 131,
      "actual_abi": "task in ESI, priority in EDI, scheduler on stack; RET 4"
    },
    {
      "name": "Scheduler_RemoveLocked",
      "source": "src/game/scheduler_tasks.cpp",
      "symbol": "_Scheduler_RemoveLocked@8",
      "section": ".text$50locked",
      "address": "0x00449F20",
      "size": 52,
      "actual_abi": "task in ESI, scheduler on stack; RET 4"
    },
    {
      "name": "Scheduler_Remove",
      "source": "src/game/scheduler_tasks.cpp",
      "symbol": "@Scheduler_Remove@8",
      "section": ".text$70remove",
      "address": "0x00449F60",
      "size": 114,
      "actual_abi": "task in ECX, scheduler in EDX; plain RET"
    },
    {
      "name": "Joystick_Probe",
      "source": "src/platform/joystick_probe.cpp",
      "symbol": "?Joystick_Probe_0044a0c0@@YGFXZ",
      "section": ".text$80joystick",
      "address": "0x0044A0C0",
      "size": 105,
      "actual_abi": "zero-argument stdcall probe; WinMM imports in fixed slots; short status in AX"
    },
    {
      "name": "TextLog_Append",
      "source": "src/platform/text_log.cpp",
      "symbol": "?Append@TextLog_0044b810@@QAAPADPADZZ",
      "section": ".text$85textlog",
      "address": "0x0044B810",
      "size": 201,
      "actual_abi": "log object in ECX; format and varargs on stack; caller cleanup; plain RET"
    },
    {
      "name": "Recovery_InstallPairSetFlags_004055c0",
      "source": "src/game/recovery_install_pair_set_flags_004055c0.cpp",
      "symbol": "_asm_Recovery_InstallPairSetFlags_004055c0@4",
      "section": ".text$00_vinstall",
      "address": "0x004055C0",
      "size": 84,
      "actual_abi": "pair in EBX across both registration calls; result in EAX; plain RET"
    },
    {
      "name": "Recovery_CreateFixedState_004056b0",
      "source": "src/game/recovery_create_fixed_state_004056b0.cpp",
      "symbol": "_asm_Recovery_CreateFixedState_004056b0",
      "section": ".text$00_xfixed",
      "address": "0x004056B0",
      "size": 85,
      "actual_abi": "no live-in registers; result in EAX; plain RET"
    },
    {
      "name": "Recovery_InstallPairClearFlags_0041ad90",
      "source": "src/game/recovery_install_pair_clear_flags_0041ad90.cpp",
      "symbol": "_asm_Recovery_InstallPairClearFlags_0041ad90@4",
      "section": ".text$00e_installclear",
      "address": "0x0041AD90",
      "size": 84,
      "actual_abi": "pair in EBX across both registration calls; result in EAX; plain RET"
    }
  ],
  "context": {
    "symbol": "?BulletManagerLoadScriptsCompilerContext@@YGHPAUScheduler@@PAPAUSchedulerTask@@HHPAPAUBulletManagerState_0040af90@@@Z",
    "section": ".text$90context",
    "address": "0x0044B900",
    "size": 149,
    "description": "Synthetic array-walking caller that establishes the loader's and the fixed-state factory's register conventions; not recovered game code."
  },
  "gaps": [
    {
      "section": ".text$00_layout",
      "address": "0x00401000",
      "size": 17856
    },
    {
      "section": ".text$00_wlayout",
      "address": "0x00405614",
      "size": 156
    },
    {
      "section": ".text$00_ylayout",
      "address": "0x00405705",
      "size": 22379
    },
    {
      "section": ".text$00b_layout",
      "address": "0x0040AEF6",
      "size": 154
    },
    {
      "section": ".text$00d_layout",
      "address": "0x0040AFE6",
      "size": 64938
    },
    {
      "section": ".text$00f_layout",
      "address": "0x0041ADE4",
      "size": 191740
    },
    {
      "section": ".text$20_layout",
      "address": "0x00449B63",
      "size": 13
    },
    {
      "section": ".text$40_layout",
      "address": "0x00449BF3",
      "size": 813
    },
    {
      "section": ".text$60_layout",
      "address": "0x00449F54",
      "size": 12
    },
    {
      "section": ".text$75_layout",
      "address": "0x00449FD2",
      "size": 238
    },
    {
      "section": ".text$82_layout",
      "address": "0x0044A129",
      "size": 5863
    },
    {
      "section": ".text$87_layout",
      "address": "0x0044B8D9",
      "size": 39
    }
  ],
  "constants": [],
  "absolute_symbols": [
    {
      "symbol": "?g_thread_synchronization@@3UThreadSynchronization@@A",
      "address": "0x00492274",
      "kind": "data"
    },
    {
      "symbol": "__imp__EnterCriticalSection@4",
      "address": "0x004660B0",
      "kind": "data"
    },
    {
      "symbol": "__imp__LeaveCriticalSection@4",
      "address": "0x004660B4",
      "kind": "data"
    },
    {
      "symbol": "??3@YAXPAX@Z",
      "address": "0x004524A1",
      "kind": "relative_code"
    },
    {
      "symbol": "_data_004922bc",
      "address": "0x004922BC",
      "kind": "data"
    },
    {
      "symbol": "_data_0049231f",
      "address": "0x0049231F",
      "kind": "data"
    },
    {
      "symbol": "_data_00466280",
      "address": "0x00466280",
      "kind": "data"
    },
    {
      "symbol": "_data_0046627c",
      "address": "0x0046627C",
      "kind": "data"
    },
    {
      "symbol": "_asm_vsprintf_004524a6",
      "address": "0x004524A6",
      "kind": "relative_code"
    },
    {
      "symbol": "__chkstk",
      "address": "0x00458EC0",
      "kind": "relative_code"
    },
    {
      "symbol": "___security_cookie",
      "address": "0x00473660",
      "kind": "data"
    },
    {
      "symbol": "@__security_check_cookie@4",
      "address": "0x00458EA5",
      "kind": "relative_code"
    },
    {
      "symbol": "@Recovery_LoadCachedResource_00447280@12",
      "address": "0x00447280",
      "kind": "relative_code"
    },
    {
      "symbol": "_SchedulerCallback_Create_00449ed0@4",
      "address": "0x00449ED0",
      "kind": "relative_code"
    },
    {
      "symbol": "_data_00491c10",
      "address": "0x00491C10",
      "kind": "data"
    },
    {
      "symbol": "_data_00491be4",
      "address": "0x00491BE4",
      "kind": "data"
    },
    {
      "symbol": "_asm_BulletManager_Release_0040af00@4",
      "address": "0x0040AF00",
      "kind": "relative_code"
    },
    {
      "symbol": "_entry_free_004524a1",
      "address": "0x004524A1",
      "kind": "relative_code"
    },
    {
      "symbol": "??2@YAPAXI@Z",
      "address": "0x00452493",
      "kind": "relative_code"
    },
    {
      "symbol": "_memset",
      "address": "0x0045BED0",
      "kind": "relative_code"
    },
    {
      "symbol": "_data_004776fc",
      "address": "0x004776FC",
      "kind": "data"
    },
    {
      "symbol": "_asm_Recovery_ReleaseRawPairAndReset_00405620@4",
      "address": "0x00405620",
      "kind": "relative_code"
    },
    {
      "symbol": "_data_004776ec",
      "address": "0x004776EC",
      "kind": "data"
    }
  ]
}
```

sha256 `77d6964c0a453aec2e9be7b7c38208902e6b5cb4fed9f41eabdabe505829c3a6`. Additions only: the new `additional_sources` entry, the new
`functions` entry and a `.text$00e_installclear` section for it, the context
size, and the split of the old `.text$00d_layout` gap (`0x40AFE6`, 256762 bytes)
into `.text$00d_layout` (64938, up to the new function), the function, and
`.text$00f_layout` (`0x41ADE4`, 191740, up to `Scheduler_RegisterPrimary`).
Name order keeps the placement legal: `.text$00d_layout` <
`.text$00e_installclear` < `.text$00f_layout` < `.text$10primary`.

## Shapes tried - why the cluster is required

Retail's pair-in-EBX is a whole-program agreement; the pass only derives it when
the registration pair is in the same link. Measured with a throwaway standalone
layout (`clearflags_standalone`, in `/tmp/InstallPairClearFlags/sa/msvc`, every
callee bound opaquely, the same model and the same `#pragma code_seg` section):

| model | emitted | differing bytes | first difference |
|---|---:|---:|---|
| this source alone, callees opaque (`SchedulerCallback_Create`, `Scheduler_RegisterPrimary/Secondary`, `data_00491be4` as `absolute_symbols`) | 88/84 | 86 | `0x0041AD91`: retail `57` `push edi`, emitted `68 00 ba 41 00` `push 0x41ba00` |
| this source merged with the registration pair co-compiled (landed) | **84/84** | **0** | - |

The 88-byte standalone body puts the pair in **EDI** (it emits `push esi` only,
`mov [esi+20h],edi`, `mov [edi+8],esi`) and passes the two registration calls
entirely on the stack (`push 0x15`/`push 0x19`, `push esi`, `push eax` after
`mov eax,[0x491be4]`), and it loses the in-place flag update to
`mov edx,[esi+4]` / `and edx,-3` / `mov [esi+4],edx`. With
`src/game/scheduler_tasks.cpp` co-compiled (its bodies keep the task in ESI and
the priority in EDI) EBX is the only free callee-saved register left for the
pair, and the in-place `and` and the `mov edi,0x15`/`mov edi,0x19` forms fall
out - the same mechanism recorded for the set-flags twin in
`recovery_create_fixed_state_004056b0_wave4.md`.

No float pool, no `constant_aliases`, no `roots`, nothing else was needed. The
model is the set-flags source with the four operand deltas applied; the first
build of it was already exact.

## Caller registers

`0x0041AD90` has exactly one caller in the image: the `call` at `0x0041AF48`
inside `asm_FUN_0041aed0_0041aed0` (region `0x0041AED0`, still assembly, 185 bytes).
Immediately before the call it runs

```
0x0041AF3D  push ebx
0x0041AF3E  mov ebx,esi          ; EBX = the pair just allocated
0x0041AF40  mov dword [esp+14h],-1
0x0041AF48  call 0x0041AD90
0x0041AF4D  test eax,eax
0x0041AF4F  pop ebx
0x0041AF50  je  0x0041AF77
```

so the caller passes the pair in **EBX**, saves EBX itself (it knows the callee
may clobber it), keeps **ESI** live across the call (the same pair, read again at
`0x0041AF52` and `0x0041AF65`), has already popped **EDI** at `0x0041AF38`, and
reads the status out of **EAX**. The emitted body keeps every one of those: it
pushes and pops ESI and EDI exactly as retail does, never writes EBX, returns `0`
in EAX and returns with a plain `RET` - so the pass replaced the declared
`__stdcall` stack argument with the internal EBX convention, which is why the
call site has no argument push and no `RET 4`.

## Integration

Both the source and the layout are already in the maintained tree (verified by
the probe line above, run against `--project matching2/msvc` after the change).
The merge went through the documented overwrite path, not through hand edits:

```
python3 matching2/tools/waves/promote_scratch.py \
    --scratch /tmp/InstallPairClearFlags/msvc --address 0x41AD90 --apply
```

which copied exactly three files (`src/game/recovery_install_pair_clear_flags_0041ad90.cpp`,
`layout/ltcg/bullet_manager_load_scripts_0040ae70.json`,
`layout/ltcg/bullet_manager_load_scripts_0040ae70_context.cpp`) and rewrote the
one region record:

```json
{ "name": "semantic_Recovery_InstallPairClearFlags_0041ad90_0041ad90",
  "source": "src/game/recovery_install_pair_clear_flags_0041ad90.cpp",
  "symbol": "_asm_Recovery_InstallPairClearFlags_0041ad90@4",
  "address": "0x0041AD90", "size": 84, "kind": "semantic", "owner": "0x0041AD90" }
```

* `register_cluster.py --apply` was **not** used: the layout is an existing
  multi-source cluster, which that tool refuses. Per lesson 11 this is the
  manifest path I took and it is the one the tooling documents for the merge
  pattern; the diff footprint is 17 lines in `regions.json`.
* `translation_units` was **not** rewritten and is unchanged - the source already
  appeared there (the old asm region owned it). `ltcg_clusters` already listed
  the layout.
* The manifest `symbols` map still binds the old spelling
  `_asm_Recovery_InstallPairClearFlags_0041ad90` = `0x0041AD90`, so the naked
  caller `src/game/fun_0041aed0_0041aed0.cpp:82` (`call asm_Recovery_InstallPairClearFlags_0041ad90`)
  resolves to the recovered body through the linker-script assignment, exactly as
  the set-flags twin does.
* `src/game/recovery_leaves.cpp:1530` still holds a stale naked copy of the body
  under the old cdecl spelling (the set twin has the same situation in
  `player.cpp`); no region selects it and the spelling differs from the region's
  `@4` symbol.
* No test file was added - the cluster probe above is the gate - and no build
  (`make`, `build_msvc.sh`, `build_msvc.py`) was run; the whole-image build is the
  integration owner's.
