# 0x0040AE70 `BulletManager_LoadScripts` — recovered, and `0x0040AF90` lands with it

2026-09-19. Third-wave agent `LoadScriptsGen`. Region `0x0040AE70` (134 bytes,
`src/game/bullet_manager_load_scripts_0040ae70.cpp`) is modelled as ordinary C++
and is **byte-identical to retail in a native-LTCG cluster**; the dependent
region `0x0040AF90` (`BulletManager_Create`) is **byte-identical in the same
cluster**, which is the landing the `0x40AF90` note was waiting for. The
configuration, the receiver register and the one pitfall that cost the earlier
attempts are recorded below; all artifacts are also in the copy at
`/tmp/LoadScriptsGen/msvc`.

## What the region is

```
0040ae70  mov    edx,[0x491c10]      ; resource cache table
0040ae76  push   0x46cd88            ; resource name
0040ae7b  mov    ecx,7               ; resource id
0040ae80  call   0x447280            ; LoadCachedResource(id, table, name)
0040ae85  test   eax,eax
0040ae87  mov    [ebx+10h],eax       ; state->bullet_resource
0040ae8a  jne    0x40aea2
0040ae8c  push   0x46cf74            ; failure text
0040ae91  mov    ecx,0x474f70        ; text log object
0040ae96  call   0x44b810            ; TextLog::Append
0040ae9b  add    esp,4
0040ae9e  or     eax,-1
0040aea1  ret
0040aea2  push   esi
0040aea3  push   edi
0040aea4  push   0x40b050            ; primary callback body
0040aea9  call   0x449ed0            ; SchedulerCallback_Create
0040aeae  mov    esi,eax
0040aeb0  and    dword [esi+4],0fffffffdh
0040aeb4  mov    eax,[0x491be4]      ; the scheduler
0040aeb9  push   eax
0040aeba  mov    edi,0x17            ; primary priority
0040aebf  mov    [esi+20h],ebx       ; task->context = state
0040aec2  call   0x449ae0            ; Scheduler_RegisterPrimary
0040aec7  push   0x40b060            ; secondary callback body
0040aecc  mov    [ebx+8],esi         ; state->primary_callback
0040aecf  call   0x449ed0
0040aed4  mov    esi,eax
0040aed6  and    dword [esi+4],0fffffffdh
0040aeda  mov    ecx,[0x491be4]
0040aee0  push   ecx
0040aee1  mov    edi,0x20            ; secondary priority
0040aee6  mov    [esi+20h],ebx
0040aee9  call   0x449b70            ; Scheduler_RegisterSecondary
0040aeee  pop    edi
0040aeef  mov    [ebx+0Ch],esi       ; state->secondary_callback
0040aef2  xor    eax,eax
0040aef4  pop    esi
0040aef5  ret
```

The manager arrives in **EBX** (`mov [ebx+10h],eax`, `mov [esi+20h],ebx`,
`mov [ebx+8],esi`), the callback under construction in ESI and the
registration priority in EDI. Only `0x417B8B` calls this region — with the
manager in EBX and no argument set up, result in EAX — which is exactly what
the `0x40AF90` model does.

## Receiver register (the question the caller side asked)

Retail's caller `0x40AF90` puts the manager in **EBX** and the callee keeps it
there; my emitted body keeps it in **EBX** too, and `0x40AF90` is byte-exact
against the same link (86 bytes, 0 differing). The three registers are
whole-program agreements inside one `/LTCG` link: the manager in EBX, the
callback in ESI and the priority in EDI, with the two registration callees
consuming ESI/EDI themselves — so this region cannot be modelled against
opaque declarations of those callees.

## The model

```cpp
// 0x0040AE70..0x0040AEF5 (134 bytes) - BulletManager_LoadScripts
//
// Loads the bullet animation resource, then creates and registers the two
// scheduler callbacks that drive it.  Retail keeps the manager in EBX, the
// callback under construction in ESI and the registration priority in EDI;
// those are whole-program register agreements, so this source is compiled in
// the same native-LTCG link as the scheduler registration functions it calls
// and as the constant-log formatter it reports a failure through.
#include "th10/game/scheduler.hpp"

struct BulletManagerState_0040af90 {
    unsigned flags;                 // +0x00
    unsigned reserved_004;          // +0x04
    void *primary_callback;         // +0x08
    void *secondary_callback;       // +0x0C
    void *bullet_resource;          // +0x10
    unsigned reserved_014;          // +0x14
};

struct BulletResourceCache_0040ae70;

// Declared here exactly as the co-compiled TextLog translation unit defines it,
// so the whole-program pass can pick the register agreement retail used.
struct TextLog_0044b810 {
    char text[0x2000];
    char *cursor;
    unsigned char dirty;
    char *Append(char *format, ...);
};

extern "C" void * __fastcall Recovery_LoadCachedResource_00447280(
        int id, BulletResourceCache_0040ae70 *cache, const char *name);
extern "C" SchedulerTask * __stdcall SchedulerCallback_Create_00449ed0(void *callback);
extern "C" BulletResourceCache_0040ae70 *data_00491c10;
extern "C" Scheduler *data_00491be4;

#pragma code_seg(".text$00a_loadscripts")
extern "C" __declspec(noinline) int __stdcall BulletManager_LoadScripts_0040ae70(
        BulletManagerState_0040af90 *state) {
    void *resource = Recovery_LoadCachedResource_00447280(
            7, data_00491c10, (const char *)0x46CD88);
    state->bullet_resource = resource;
    if (!resource) {
        ((TextLog_0044b810 *)0x474F70)->Append((char *)0x46CF74);
        return -1;
    }

    SchedulerTask *primary = SchedulerCallback_Create_00449ed0((void *)0x40B050);
    primary->reserved_flags &= ~1u;
    primary->context = state;
    Scheduler_RegisterPrimary(data_00491be4, primary, 0x17);
    state->primary_callback = primary;

    SchedulerTask *secondary = SchedulerCallback_Create_00449ed0((void *)0x40B060);
    secondary->reserved_flags &= ~1u;
    secondary->context = state;
    Scheduler_RegisterSecondary(data_00491be4, secondary, 0x20);
    state->secondary_callback = secondary;
    return 0;
}
#pragma code_seg()
```

Load-bearing details, each arrived at by measurement:

* **`Recovery_LoadCachedResource_00447280` is an opaque `__fastcall` with the
  argument order `(id, table, name)`.** That declaration is what makes the pass
  emit retail's prologue verbatim: `mov edx,[0x491c10]` (the *value* of a data
  pointer, not its address), `push <name>`, `mov ecx,7`, `call`. The callee's
  `ret 4` then removes the stack argument, which is why the caller needs no
  `add esp,4` here.
* **`SchedulerCallback_Create_00449ed0` is an opaque `__stdcall(void *)`** —
  `push <body>; call`, callee-cleaned, exactly retail.
* **`primary->reserved_flags &= ~1u`** is the header's 31-bit bitfield starting
  at bit 1, so MSVC emits retail's `and dword ptr [esi+4],0FFFFFFFDh` in the
  memory-operand form (the result is dead). Writing the state's `+4` as a plain
  `unsigned flags` and clearing bit 1 emits the same instruction.
* **The `TextLog::Append` call must be a real in-link call.** No declaration
  suffices. A varargs member call pushes `this` (`push <format>; push
  <object>; call; add esp,8`: the same 18 bytes as retail's call sequence but 4
  differing bytes, and wrong at run time because retail's `Append` reads `this`
  from ECX); a two-register `__fastcall(self,fmt)` emits `mov edx,<format>; mov
  ecx,<object>` and is 8 bytes shorter; a byte-valued second fastcall slot adds
  `xor dl,dl` (136 bytes); `__fastcall` with a varargs tail makes MSVC push
  every argument. Declared opaquely the whole body also collapses to **131
  bytes** in-cluster, because the opaque call changes the surrounding
  allocation. Only `this`-in-ECX + format-on-stack + caller cleanup matches,
  and that convention exists only while `TextLog::Append` is compiled in the
  same link.

## Layout and driver

`layout/ltcg/bullet_manager_load_scripts_0040ae70.json`:

```json
{
  "schema_version": 1,
  "name": "bullet_manager_load_scripts_0040ae70",
  "source": "src/game/bullet_manager_load_scripts_0040ae70.cpp",
  "additional_sources": [
    "src/game/scheduler_tasks.cpp",
    "src/platform/text_log.cpp",
    "src/platform/joystick_probe.cpp",
    "src/game/bullet_manager_create_0040af90.cpp"
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
  "description": "BulletManager_LoadScripts and BulletManager_Create compiled with the scheduler registration/removal pair, the constant-log formatter and the joystick probe under native LTCG, so the pass keeps the manager in EBX, the callback in ESI and the registration priority in EDI.",
  "functions": [
    {"name": "BulletManager_LoadScripts_0040ae70", "symbol": "_BulletManager_LoadScripts_0040ae70@4",
     "section": ".text$00a_loadscripts", "address": "0x0040AE70", "size": 134,
     "actual_abi": "manager in EBX; no stack argument; result in EAX; plain RET"},
    {"name": "BulletManager_Create_0040af90",
     "symbol": "?BulletManager_Create_0040af90@@YGPAUBulletManagerState_0040af90@@XZ",
     "section": ".text$00c_create", "address": "0x0040AF90", "size": 86,
     "source": "src/game/bullet_manager_create_0040af90.cpp",
     "actual_abi": "manager in EBX across the script-load and release calls; result in EAX"},
    {"name": "Scheduler_RegisterPrimary", "source": "src/game/scheduler_tasks.cpp",
     "symbol": "_Scheduler_RegisterPrimary@12", "section": ".text$10primary",
     "address": "0x00449AE0", "size": 131,
     "actual_abi": "task in ESI, priority in EDI, scheduler on stack; RET 4"},
    {"name": "Scheduler_RegisterSecondary", "source": "src/game/scheduler_tasks.cpp",
     "symbol": "_Scheduler_RegisterSecondary@12", "section": ".text$30secondary",
     "address": "0x00449B70", "size": 131,
     "actual_abi": "task in ESI, priority in EDI, scheduler on stack; RET 4"},
    {"name": "Scheduler_RemoveLocked", "source": "src/game/scheduler_tasks.cpp",
     "symbol": "_Scheduler_RemoveLocked@8", "section": ".text$50locked",
     "address": "0x00449F20", "size": 52,
     "actual_abi": "task in ESI, scheduler on stack; RET 4"},
    {"name": "Scheduler_Remove", "source": "src/game/scheduler_tasks.cpp",
     "symbol": "@Scheduler_Remove@8", "section": ".text$70remove",
     "address": "0x00449F60", "size": 114,
     "actual_abi": "task in ECX, scheduler in EDX; plain RET"},
    {"name": "Joystick_Probe", "source": "src/platform/joystick_probe.cpp",
     "symbol": "?Joystick_Probe_0044a0c0@@YGFXZ", "section": ".text$80joystick",
     "address": "0x0044A0C0", "size": 105,
     "actual_abi": "zero-argument stdcall probe; WinMM imports in fixed slots; short status in AX"},
    {"name": "TextLog_Append", "source": "src/platform/text_log.cpp",
     "symbol": "?Append@TextLog_0044b810@@QAAPADPADZZ", "section": ".text$85textlog",
     "address": "0x0044B810", "size": 201,
     "actual_abi": "log object in ECX; format and varargs on stack; caller cleanup; plain RET"}
  ],
  "context": {
    "symbol": "?BulletManagerLoadScriptsCompilerContext@@YGHPAUScheduler@@PAPAUSchedulerTask@@HHPAPAUBulletManagerState_0040af90@@@Z",
    "section": ".text$90context", "address": "0x0044B900", "size": 123,
    "description": "Synthetic array-walking caller that establishes the loader's register convention; not recovered game code."
  },
  "gaps": [
    {"section": ".text$00_layout", "address": "0x00401000", "size": 40560},
    {"section": ".text$00b_layout", "address": "0x0040AEF6", "size": 154},
    {"section": ".text$00d_layout", "address": "0x0040AFE6", "size": 256762},
    {"section": ".text$20_layout", "address": "0x00449B63", "size": 13},
    {"section": ".text$40_layout", "address": "0x00449BF3", "size": 813},
    {"section": ".text$60_layout", "address": "0x00449F54", "size": 12},
    {"section": ".text$75_layout", "address": "0x00449FD2", "size": 238},
    {"section": ".text$82_layout", "address": "0x0044A129", "size": 5863},
    {"section": ".text$87_layout", "address": "0x0044B8D9", "size": 39}
  ],
  "constants": [],
  "absolute_symbols": [
    {"symbol": "?g_thread_synchronization@@3UThreadSynchronization@@A", "address": "0x00492274", "kind": "data"},
    {"symbol": "__imp__EnterCriticalSection@4", "address": "0x004660B0", "kind": "data"},
    {"symbol": "__imp__LeaveCriticalSection@4", "address": "0x004660B4", "kind": "data"},
    {"symbol": "??3@YAXPAX@Z", "address": "0x004524A1", "kind": "relative_code"},
    {"symbol": "_data_004922bc", "address": "0x004922BC", "kind": "data"},
    {"symbol": "_data_0049231f", "address": "0x0049231F", "kind": "data"},
    {"symbol": "_data_00466280", "address": "0x00466280", "kind": "data"},
    {"symbol": "_data_0046627c", "address": "0x0046627C", "kind": "data"},
    {"symbol": "_asm_vsprintf_004524a6", "address": "0x004524A6", "kind": "relative_code"},
    {"symbol": "__chkstk", "address": "0x00458EC0", "kind": "relative_code"},
    {"symbol": "___security_cookie", "address": "0x00473660", "kind": "data"},
    {"symbol": "@__security_check_cookie@4", "address": "0x00458EA5", "kind": "relative_code"},
    {"symbol": "@Recovery_LoadCachedResource_00447280@12", "address": "0x00447280", "kind": "relative_code"},
    {"symbol": "_SchedulerCallback_Create_00449ed0@4", "address": "0x00449ED0", "kind": "relative_code"},
    {"symbol": "_data_00491c10", "address": "0x00491C10", "kind": "data"},
    {"symbol": "_data_00491be4", "address": "0x00491BE4", "kind": "data"},
    {"symbol": "_asm_BulletManager_Release_0040af00@4", "address": "0x0040AF00", "kind": "relative_code"},
    {"symbol": "_entry_free_004524a1", "address": "0x004524A1", "kind": "relative_code"},
    {"symbol": "??2@YAPAXI@Z", "address": "0x00452493", "kind": "relative_code"},
    {"symbol": "_memset", "address": "0x0045BED0", "kind": "relative_code"},
    {"symbol": "_data_004776fc", "address": "0x004776FC", "kind": "data"}
  ]
}
```

`layout/ltcg/bullet_manager_load_scripts_0040ae70_context.cpp`:

```cpp
// Compiler context only: this caller is not recovered application code.
#include "../../src/game/bullet_manager_load_scripts_0040ae70.cpp"

struct BulletManagerState_0040af90;
BulletManagerState_0040af90 *BulletManager_Create_0040af90();

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
    return created;
}
#pragma code_seg()
```

The synthetic context's own shape is not load-bearing: it only has to make the
registration pair reachable, and adding another loop that calls
`BulletManager_LoadScripts_0040ae70` directly leaves all eight regions exact
(measured). The manager's EBX agreement comes from the real caller,
`BulletManager_Create_0040af90`, which is in the same link.

## The pitfall that blocked the earlier attempts

The `0x40AF90` note concluded that "the only configuration that reproduces
retail is one where `0x40AE70` itself is a selected function in the same
`/LTCG` link" and therefore proposed an extended `scheduler_tasks` cluster with
the removal pair in `roots`. That layout does **not** work, and the reason is
not the loader and not the constant-log call:

* `/INCLUDE:`-rooted symbols keep their **declared** ABI. With
  `_Scheduler_RemoveLocked@8` in `roots`, the pass refuses the register
  agreement for it: the emitted `.text$50locked` contribution is **58 bytes
  against the 52-byte region** (`push %esi; mov 0xc(%esp),%esi; ... ret 8`
  instead of `test %esi,%esi; ... ret 4`), every later section shifts by 0x10,
  and `0x40AE70` then calls `0x44b820` instead of `0x44b810` — 134 bytes, 1
  differing byte, and validation fails with *"function is not its entire
  declared compiler contribution: _Scheduler_RemoveLocked@8"*.
* Rooting only `@Scheduler_Remove@8` (which really is external-facing and has a
  declared `__fastcall` ABI) is harmless; rooting nothing but the joystick probe
  is what the layout above does, with the removal pair *called* by the context
  instead.
* The same rule applies to this region: it must not be in `roots` either — its
  receiver agreement is a promoted parameter. It is reachable from the real
  `BulletManager_Create` in the link, so it needs no root.

Measured, in the same link, with `_Scheduler_RemoveLocked@8` rooted and with the
`TextLog::Append` call in-link: `0x40AE70` 134/1 differing, `0x40AF90` 86/0
exact, `0x449AE0`/`0x449B70` 131/0 exact, `0x449F20` 58 emitted against 52,
`0x449F60` 114 exact, `0x44A0C0` 105 exact, `0x44B810` 201 exact.

## Evidence

`/tmp/LoadScriptsGen/msvc`, copy of the maintained project, one cluster
registered (`layout/ltcg/bullet_manager_load_scripts_0040ae70.json`), all eight
regions flipped to that layout's symbols. The probe compares every region the
cluster owns, so the contract's own single-source line is the whole proof:

```
python3 matching2/tools/matching/probe.py \
  --source src/game/bullet_manager_load_scripts_0040ae70.cpp \
  --project /tmp/LoadScriptsGen/msvc --output /tmp/LoadScriptsGen/out --show 30
0x0040ae70     134 bytes  _BulletManager_LoadScripts_0040ae70@4  EXACT
0x0040af90      86 bytes  ?BulletManager_Create_0040af90@@YGPAUBulletManagerState_0040af90@@XZ  EXACT
0x00449ae0     131 bytes  _Scheduler_RegisterPrimary@12  EXACT
0x00449b70     131 bytes  _Scheduler_RegisterSecondary@12  EXACT
0x00449f20      52 bytes  _Scheduler_RemoveLocked@8  EXACT
0x00449f60     114 bytes  @Scheduler_Remove@8  EXACT
0x0044a0c0     105 bytes  ?Joystick_Probe_0044a0c0@@YGFXZ  EXACT
0x0044b810     201 bytes  ?Append@TextLog_0044b810@@QAAPADPADZZ  EXACT
EXACT
```

The same result with each unit named explicitly (so every claimed source is
known to be a cluster source of this link):

```
python3 matching2/tools/matching/probe.py \
  --source src/game/bullet_manager_load_scripts_0040ae70.cpp \
  --source src/game/bullet_manager_create_0040af90.cpp \
  --source src/game/scheduler_tasks.cpp \
  --source src/platform/joystick_probe.cpp \
  --source src/platform/text_log.cpp \
  --project /tmp/LoadScriptsGen/msvc --output /tmp/LoadScriptsGen/out --show 12
… eight EXACT lines …
EXACT
```

The emitted `0x40AE70` body is the listing at the top of this note, byte for
byte, including `call 0x44b810` — `matching2/build/oracle/th10.exe`
`0x40AE70..0x40AEF6` compared with zero differing bytes.

The carve alternative was also verified: with the registration pair and the
removal pair moved into `src/game/scheduler_registration_0040ae70.cpp` and
`src/game/scheduler_remove_0040ae70.cpp` (their body text verbatim, sections
renamed so the name order follows the address order) and a two-function
`scheduler_tasks` cluster dropped to `{RemoveLocked, Remove}`, my region and
`0x40AF90` are exact as well; that variant keeps the scheduler cluster
independent but requires re-sourcing four regions and leaves the maintained
`scheduler_tasks.cpp` unused.

## Integration

Both regions are new to the tree, so this is a `promote_scratch.py`-style
landing plus a cluster merge, not a `register_cluster.py` one (the layout claims
five sources; `register_cluster.py` refuses those by design).

1. **Copy** from the scratch copy:
   * `src/game/bullet_manager_load_scripts_0040ae70.cpp` (model above; replaces
     the naked body),
   * `src/game/bullet_manager_create_0040af90.cpp` (the `0x40AF90` note's model
     with `#pragma code_seg(".text$00c_create")`; replaces the naked body),
   * `layout/ltcg/bullet_manager_load_scripts_0040ae70.json` and its driver.
2. **Section names.** The cluster's section order is fixed by the section names
   (`scheduler_tasks.cpp` keeps `.text$10primary` … `.text$70remove`), so the two
   d3d-cluster sources must be renumbered to sort after the removal pair:
   `src/platform/joystick_probe.cpp` `.text$01joystick` → `.text$80joystick`,
   `src/platform/text_log.cpp` `.text$03textlog` → `.text$85textlog`. No other
   maintained source changes.
3. **Manifest.** Flip regions `0x0040AE70` and `0x0040AF90` to semantic with
   `_BulletManager_LoadScripts_0040ae70@4` and
   `?BulletManager_Create_0040af90@@YGPAUBulletManagerState_0040af90@@XZ`
   (`promote_scratch.py --scratch /tmp/LoadScriptsGen/msvc --address … --apply`
   for each; its `register_cluster.py` step prints the multi-source refusal,
   which is expected and does not stop the two records from being flipped). The
   other six regions keep the source, symbol and size they have today, so
   `translation_units` is unchanged.
4. **Clusters.** Replace `layout/ltcg/scheduler_tasks.json` and
   `layout/ltcg/d3d_text_log_append_0044b810.json` in `ltcg_clusters` with
   `layout/ltcg/bullet_manager_load_scripts_0040ae70.json`
   (`register_cluster.py --unregister` must **not** be used on them: it returns
   those regions to assembly. Drop the entries and delete the two stale layout
   files and `layout/ltcg/scheduler_tasks_context.cpp`.)
5. **Gate.** `make` must print `Whole EXE exact: 487,936 bytes.`; semantic C++
   rises by 134 + 86 = 220 bytes.
