# `0x00401110` LoadGameThreadResources — modelled, one allocator decision short

2026-09-19. Third-wave agent `LoadGameThreadRes`. The region was **not landed**:
every byte of the extent and every internal call site is accounted for, and the
residual is a single whole-program register-assignment decision (the entry
register), not a source shape. Two configurations are measured end to end:

| configuration | `0x00401110` | `0x00401000` | `0x00401440` |
| --- | ---: | --- | --- |
| plain translation unit | 332 bytes (+2) | not in the unit | not in the unit |
| native LTCG `{ctor, loader, factory}` | **332 bytes (+2)**, `this` in ESI | 251 EXACT | **69 EXACT, 0 differing** |
| native LTCG `{ctor, loader, factory, scheduler_tasks, text_log}` | **326 bytes (-4)**, `this` in EBX | 251 EXACT | 69 bytes, 22 differing |

The middle row is the new result: with the loader's *real* body in the link the
factory `0x00401440` is **byte-identical**, which the previous note's placeholder
bodies could not reach (they produced `mov ecx,esi`). The bottom row is the
configuration the scheduler call sites need, and there the allocator re-picks the
entry register, which costs the factory its exactness again.

## 1. Where the thread pointer goes

Retail's value flow through the three regions:

```asm
00401452  mov  esi,eax        ; factory: object (ctor return) kept in ESI
0040145f  mov  eax,esi        ; ---- argument handed over in EAX ----
00401461  call 0x00401110
00401116  push ebx            ; callee: saves EBX, because it is about to be written
00401121  mov  eax,ebx        ; ---- EBX becomes the body's object pointer ----
00401123  call 0x00447280     ; EAX/ECX/EDX then serve every callee as scratch
00401182  pop  ebx            ; failure epilogue, before the ret
00401258  pop  ebx            ; success epilogue, after the pops of EDI and ESI
```

So: **the caller puts the thread in EAX and the body keeps it in EBX** (a
callee-saved register, saved and restored by the callee) with ESI for the task
pointer and EDI for the priority/resource — a three-register interior.

Measured against that:

* plain translation unit — `this` arrives in ECX (the declared
  `__thiscall`/`__fastcall` slot) and the body keeps it in ESI. Neither
  register matches; both the caller and the callee sides are wrong.
* `{ctor, loader, factory}` link — the body's **entry register is EAX**, exactly
  retail's (`push esi` / `mov eax,esi`; the factory's `mov eax,esi` is emitted
  verbatim, which is why `0x00401440` probes EXACT) — but the body keeps it in
  **ESI**, not EBX, because in this link the body needs only one scratch
  register (EDI).
* `{ctor, loader, factory, scheduler_tasks, text_log}` link — the body keeps it
  in **EBX**, exactly retail's (the scheduler calls make ESI and EDI scratch),
  and the three `Scheduler_Register*` call sites and the `TextLog::Append` call
  site become byte-identical — but the entry register becomes **EBX**, so the
  factory's `mov eax,esi` disappears and `0x00401440` loses 22 bytes of match.

Both halves of retail's convention are therefore reproduced by this source; no
configuration measured produces both at once. The pass prefers the strictly
cheaper pairing in each case (a transparent ESI, or a transparent EBX) over
retail's EAX-in + EBX-interior + save/restore triple.

## 2. The instruction-level delta in the full link

Emitted **326** bytes against retail's **330**. The body is retail's instruction
sequence from `0x401110` to the success epilogue; the differences are these
seven, in order of appearance (byte counts are from the two disassemblies):

| # | retail | emitted | bytes |
| --- | --- | --- | ---: |
| 1 | `push ebx` + `mov eax,ebx` at entry | absent (`this` arrives in EBX) | -3 |
| 2 | `pop ebx` in both epilogues (`0x401182` before the failure `ret`, `0x401258` in the success tail) | absent | -2 |
| 3 | second registration: `mov %ebx,0x20(%esi)` then `mov %eax,0x4(%esi)` | the same two stores transposed | 0 |
| 4 | third registration: `mov 0x4(%esi),%ecx` / `and $0xfffffffd,%ecx` / `mov %ecx,0x4(%esi)` | `andl $0xfffffffd,0x4(%esi)` (memory form) | -5 |
| 5 | `mov %esi,%edx` / `call 0x401de0` (twice) | plus `xor %ecx,%ecx` before each call | +4 |
| 6 | `xor %edx,%edx` / `mov %esi,%eax` / `mov %edi,%ecx` / `mov %edi,0x308(%esi)` / `call 0x43e5a0` | `push %esi` / `push $0x0` / `xor %edx,%edx` / `mov %edi,%ecx` / `mov %edi,0x308(%esi)` / `call` | +2 |
| 7 | second block loads the resource into EBX (`mov 0x8994(%ebx),%ebx`) | into EDI (`mov 0x8994(%ebx),%edi`) | 0 |

Everything else — the three-load chain and its `test`/member-store/`je`
scheduling, the merged failure block inline before the success path with the
third test emitted as `jne`, the `push 0x4014f0/0x401510/0x401520` +
`mov %eax,%esi` + `mov $0x4/%edi`, `mov $0x30,%edi`, `mov $0x26,%edi` +
`mov %ebx,0x20(%esi)` registration bodies, the `lea 0x14(%ebx),%esi` /
`lea 0x3c0(%ebx),%esi` blocks, `mov 0x8994(%ebx),%edi` before the first
`InitializeEntity`, and the `pop edi / xor eax,eax / pop esi / ret` tail — is
byte-identical.

Item 5 is a call-site materialisation: with the entity body visible (whose first
`__fastcall` slot its own model leaves unused) the `xor %ecx,%ecx` has no
consumer and the pass drops it, leaving retail's `mov %esi,%edx; call`. Item 6
is the same kind of site for a callee whose three register arguments
(ECX/EDX/EAX) no declaration can supply, so it follows the sibling's emitted
convention rather than mine. Item 4 is a register-pressure cascade of item 1:
retail has a spare ECX for the read-modify-write because its `this` is one
register lower in the allocator's order.

## 3. Why the discrepancy is the third load, not anything else

The load chain is worth recording because two shapes get it wrong. Retail's
branch shape is `je fail`, `je fail`, `jne success` with the failure block
emitted *inline before* the success block. That is only produced by writing the
three failures as **separate early-return blocks**:

```cpp
    a = load(...); if (a == 0) { log(); return -1; }
    b = load(...); if (b == 0) { log(); return -1; }
    c = load(...); if (c == 0) { log(); return -1; }
```

The identical `log(); return -1;` blocks are tail-merged into one block placed
immediately after the third test, which is why that test is emitted inverted
(`jne`). Written as nested `if`/`else` or as a short-circuit
`if ((a = load()) == 0 || (b = load()) == 0 || (c = load()) == 0) { ... }`, MSVC
emits three `je`s to a block placed *after* the success path — same instruction
count, wrong layout, first difference at `0x401168`.

## 4. Dependencies (measured, not inferred)

Co-compiling these bodies in the same native LTCG link is required for the
listed effect; each was observed, and each co-compiled region stayed EXACT while
it was in the link:

| source | regions it also owns | what it fixes in `0x00401110` |
| --- | --- | --- |
| `src/game/scheduler_tasks.cpp` | `0x00449AE0`, `0x00449B70`, `0x00449F20`, `0x00449F60` (all four must be selected) | the interior register choice (EBX as `this`, ESI for the task, EDI for the priority) and all three registration call sites: `push %eax; mov $4,%edi; mov %ebx,0x20(%esi); call 0x449ae0` |
| `src/platform/text_log.cpp` | `0x0044B810` | the failure call site: `push $0x46cb68; mov $0x474f70,%ecx; call; add $0x4,%esp` (a variadic member called from a link without its body pushes `this`, emitting `push $0x474f70` + `add $0x8,%esp`) |
| `src/game/entity.cpp` → `0x00401DE0` (sibling `InitEntity`) | own source | removes the `xor %ecx,%ecx` in front of both calls; retail is `mov %esi,%edx; call` with ECX dead, which needs the callee's unused first `__fastcall` slot visible |
| `src/game/animation_object_configure_from_resource_0043e5a0.cpp` (sibling `AnmObjectConfig`) | own source | the two call sites: retail is `xor %edx,%edx` / `mov %esi,%eax` / `mov %edi,%ecx` / `mov %edi,0x308(%esi)` / `call` — resource in ECX, index in EDX, object in EAX, none of which a declaration can supply |

The scheduler functions must be **called** by the cluster's context, not merely
rooted: with `roots` naming them, LINK keeps their public `__stdcall` shape and
their extents change (`Scheduler_RegisterPrimary` grew past its 131 bytes and
pushed `0x449B70` to `0x449B80`). Under the array-walking context of their own
cluster they come out EXACT inside the merged link, so the merged context must
reproduce that shape (the driver in §6 does).

## 5. Recovered source (worked model)

`src/game/load_game_thread_resources_00401110.cpp`:

```cpp
// 0x00401110: bind the game thread's resources, scheduler tasks and blocks.
//
// The thread object arrives in EAX in retail and is kept in EBX inside the
// body, so the region is modelled as a member function and compiled through a
// native LTCG cluster (see layout/ltcg/loader_chain.json).

#include "th10/game/game_thread.hpp"
#include "th10/game/scheduler.hpp"

typedef void (__cdecl *ScheduleCallback)(void);

// The shared resource table pointer, the global scheduler and the resource
// names all live in absolute slots the image fixes.
extern "C" void* data_00491c10;
extern "C" Scheduler* data_00491be4;
extern "C" char data_0046cb80[];
extern "C" char data_0046cb5c[];
extern "C" char data_0046cb50[];
extern "C" char data_0046cb68[];
// The constant log object and the three task callbacks.
extern "C" char data_00474f70[];
extern "C" void __cdecl callback_004014f0();
extern "C" void __cdecl callback_00401510();
extern "C" void __cdecl callback_00401520();

CachedResource* __fastcall Recovery_LoadCachedResource(int index, void* owner, const char* name);
extern "C" int* __stdcall SchedulerCallback_Create_00449ed0(ScheduleCallback callback);
extern "C" int __stdcall Scheduler_RegisterPrimary(Scheduler*, SchedulerTask*, int priority);
extern "C" int __stdcall Scheduler_RegisterSecondary(Scheduler*, SchedulerTask*, int priority);
extern "C" void __fastcall InitializeEntity_00401de0(void* unused, GameThreadBlock* block);
extern "C" void __fastcall AnimationObject_ConfigureFromResource_0043e5a0(
    CachedResource* resource, int index, void* unused_esi, GameThreadBlock* block);

struct TextLog_0044b810 {
    char* Append(char* format, ...);
};

// The two loads that must all succeed; a failure logs the constant message and
// reports -1, which the factory turns into a destroyed thread.
#pragma code_seg(".text$02load")
int GameThread::LoadGameThreadResources_00401110() {
    resource_8994 = Recovery_LoadCachedResource(2, data_00491c10, data_0046cb80);
    if (resource_8994 == 0) {
        ((TextLog_0044b810*)data_00474f70)->Append(data_0046cb68);
        return -1;
    }
    resource_899C = Recovery_LoadCachedResource(0, data_00491c10, data_0046cb5c);
    if (resource_899C == 0) {
        ((TextLog_0044b810*)data_00474f70)->Append(data_0046cb68);
        return -1;
    }
    resource_8998 = Recovery_LoadCachedResource(3, data_00491c10, data_0046cb50);
    if (resource_8998 == 0) {
        ((TextLog_0044b810*)data_00474f70)->Append(data_0046cb68);
        return -1;
    }

    // The primary task ticks at the base priority, the two secondary ones at
    // 0x30 and 0x26.
    SchedulerTask* primary =
        (SchedulerTask*)SchedulerCallback_Create_00449ed0(callback_004014f0);
    primary->reserved_flags &= ~1u;
    primary->context = this;
    Scheduler_RegisterPrimary(data_00491be4, primary, 4);
    this->primary_task = primary;

    SchedulerTask* secondary =
        (SchedulerTask*)SchedulerCallback_Create_00449ed0(callback_00401510);
    secondary->reserved_flags &= ~1u;
    secondary->context = this;
    Scheduler_RegisterSecondary(data_00491be4, secondary, 0x30);
    this->secondary_task = secondary;

    SchedulerTask* tertiary =
        (SchedulerTask*)SchedulerCallback_Create_00449ed0(callback_00401520);
    tertiary->reserved_flags &= ~1u;
    tertiary->context = this;
    Scheduler_RegisterSecondary(data_00491be4, tertiary, 0x26);
    this->third_task = tertiary;

    // Each block binds the first resource as its animation owner, at frame 0
    // for the first player and frame 0x62 for the second.
    CachedResource* resource = this->resource_8994;
    GameThreadBlock* block = &this->blocks[0];
    InitializeEntity_00401de0(0, block);
    block->animation = resource;
    AnimationObject_ConfigureFromResource_0043e5a0(resource, 0, 0, block);

    resource = this->resource_8994;
    block = &this->blocks[1];
    InitializeEntity_00401de0(0, block);
    block->animation = resource;
    AnimationObject_ConfigureFromResource_0043e5a0(resource, 0x62, 0, block);
    return 0;
}
#pragma code_seg()
```

Source-shape notes that cost time here:

* the resource must be read into a block-local **before** each
  `InitializeEntity` and used twice — reading `this->resource_8994` at each use
  emits four loads instead of retail's two and costs the body a register;
* `task->reserved_flags &= ~1u` (bit 1 of the flags word) is the clear retail
  performs three times; `heap_owned`'s bit 0 is what `0x449ED0` clears;
* the callback arguments are `extern "C" void __cdecl` placeholders whose
  mangled names the layout binds absolutely (`_callback_004014f0` …, kind
  `data`). The integration should reference each callback through the
  declaration its own region's landed source uses — `0x4014F0` is landed as the
  member `?ClearPending_004014f0@WidgetHost@@QAEHXZ` and `0x401510` as the
  free `?FUN_00401510@@YIXPAX@Z`, so a member-pointer spelling has to be
  checked before the push is byte-equal.

`include/th10/game/game_thread.hpp` (new, shared by all three sources — one
declaration instead of the three hand-kept padding structs the previous note
complained about):

```cpp
#pragma once

// The game thread object shared by the constructor (0x401000), the resource
// loader (0x401110) and the factory (0x401440).  One declaration so the three
// recovered bodies agree on the object instead of keeping private padding
// structs.

struct SchedulerTask;
struct CachedResource;

// One of the thread's two per-player blocks; the entity's animation owner sits
// at +0x308 and its 16-bit flag word at +0x384.
struct GameThreadBlock {
    char pad_000[0x6C];
    unsigned field_06C;
    char pad_070[0x40];
    unsigned field_0B0;
    char pad_0B4[0x48];
    unsigned field_0FC;
    char pad_100[0x28];
    unsigned field_128;
    char pad_12C[0x48];
    unsigned field_174;
    char pad_178[0x38];
    unsigned field_1B0;
    char pad_1B4[0x48];
    unsigned field_1FC;
    char pad_200[0x28];
    unsigned field_228;
    char pad_22C[0x308 - 0x22C];
    CachedResource* animation;
    char pad_30C[0x378 - 0x30C];
    unsigned field_378;
    char pad_37C[8];
    unsigned short field_384;
    char pad_386[0x26];
};

struct GameThread {
    const void* type;
    unsigned flags;
    char pad_008[4];
    SchedulerTask* primary_task;
    SchedulerTask* secondary_task;
    GameThreadBlock blocks[2];
    char pad_76C[0x8974 - 0x76C];
    int field_8974;
    float field_8978;
    float field_897C;
    char pad_8980[4];
    int field_8984;
    char pad_8988[4];
    int field_898C;
    char pad_8990[4];
    CachedResource* resource_8994;
    CachedResource* resource_8998;
    CachedResource* resource_899C;
    char pad_89A0[8];
    SchedulerTask* third_task;

    __declspec(noinline) GameThread();
    __declspec(noinline) int LoadGameThreadResources_00401110();
};
```

`0x00401000`'s body is unchanged by the header (its `GameThreadSlot` becomes
`GameThreadBlock` with the animation pointer split out of `pad_22C`, same
offsets, same extent) and it probed EXACT inside both merged links.
`0x00401440`'s model (unchanged from the previous note except that it now calls
the member):

```cpp
#pragma code_seg(".text$04create")
__declspec(noinline) GameThread* CreateGameThread_00401440() {
    GameThread* thread = new GameThread;
    if (thread->LoadGameThreadResources_00401110() != 0) {
        if (thread) {
            DestroyGameThread_00401260(thread);
            Free_004524a1(thread);
        }
        return 0;
    }
    return thread;
}
#pragma code_seg()
```

## 6. Cluster layout and driver

`layout/ltcg/loader_chain.json` (schema 1; the `functions`/`sources` shown are
the full configuration of §1, the 3-source configuration is the same file with
the five last functions, their sources and the last two gaps removed):

```json
{"schema_version": 1, "name": "loader_chain", "source": "src/game/load_game_thread_resources_00401110.cpp",
 "additional_sources": ["src/game/create_game_thread_00401440.cpp", "src/game/game_thread.cpp",
                        "src/game/scheduler_tasks.cpp", "src/platform/text_log.cpp"],
 "driver": "layout/ltcg/loader_chain_context.cpp",
 "headers": ["include/th10/game/game_thread.hpp", "include/th10/game/scheduler.hpp",
             "include/th10/platform/thread_sync.hpp"],
 "image_base": "0x00400000",
 "description": "GameThread construction, resource binding and the factory in one native-LTCG link.",
 "functions": [
  {"name": "GameThread_Construct", "symbol": "??0GameThread@@QAE@XZ", "section": ".text$01thread", "address": "0x00401000", "size": 251, "source": "src/game/game_thread.cpp", "actual_abi": "this in ESI; returns this in EAX; plain RET"},
  {"name": "LoadGameThreadResources_00401110", "symbol": "?LoadGameThreadResources_00401110@GameThread@@QAEHXZ", "section": ".text$02load", "address": "0x00401110", "size": 326, "source": "src/game/load_game_thread_resources_00401110.cpp", "actual_abi": "thread in EAX; result in EAX; plain RET"},
  {"name": "CreateGameThread_00401440", "symbol": "?CreateGameThread_00401440@@YGPAUGameThread@@XZ", "section": ".text$04create", "address": "0x00401440", "size": 69, "source": "src/game/create_game_thread_00401440.cpp", "actual_abi": "no arguments; object in EAX; plain RET"},
  {"name": "Scheduler_RegisterPrimary", "symbol": "_Scheduler_RegisterPrimary@12", "section": ".text$10primary", "address": "0x00449AE0", "size": 131, "source": "src/game/scheduler_tasks.cpp", "actual_abi": "task in ESI, priority in EDI, scheduler on stack; RET 4"},
  {"name": "Scheduler_RegisterSecondary", "symbol": "_Scheduler_RegisterSecondary@12", "section": ".text$30secondary", "address": "0x00449B70", "size": 131, "source": "src/game/scheduler_tasks.cpp", "actual_abi": "task in ESI, priority in EDI, scheduler on stack; RET 4"},
  {"name": "Scheduler_RemoveLocked", "symbol": "_Scheduler_RemoveLocked@8", "section": ".text$50locked", "address": "0x00449F20", "size": 52, "source": "src/game/scheduler_tasks.cpp", "actual_abi": "task in ESI, scheduler on stack; RET 4"},
  {"name": "Scheduler_Remove", "symbol": "@Scheduler_Remove@8", "section": ".text$70remove", "address": "0x00449F60", "size": 114, "source": "src/game/scheduler_tasks.cpp", "actual_abi": "task in ECX, scheduler in EDX; plain RET"},
  {"name": "TextLog_Append", "symbol": "?Append@TextLog_0044b810@@QAAPADPADZZ", "section": ".text$85textlog", "address": "0x0044B810", "size": 201, "source": "src/platform/text_log.cpp", "actual_abi": "log object in ECX; format and varargs on stack; caller cleanup; plain RET"}
 ],
 "context": {"symbol": "?CreateGameThreadCompilerContext@@YGHPAUGameThread@@HPAUScheduler@@PAPAUSchedulerTask@@H@Z", "section": ".text$03context", "address": "0x00401270", "size": 124, "description": "Synthetic caller that establishes the observed register conventions; not recovered game code."},
 "gaps": [
  {"section": ".text$01zgap", "address": "0x004010FB", "size": 21},
  {"section": ".text$02zgap", "address": "0x00401256", "size": 26},
  {"section": ".text$03zgap", "address": "0x004012EC", "size": 340},
  {"section": ".text$04zgap", "address": "0x00401485", "size": 296539},
  {"section": ".text$40zgap", "address": "0x00449BF3", "size": 813},
  {"section": ".text$80zgap", "address": "0x00449FD2", "size": 6206}
 ],
 "constants": [], "roots": [],
 "absolute_symbols": [
  {"symbol": "_data_00491c10", "address": "0x00491C10", "kind": "data"},
  {"symbol": "_data_00491be4", "address": "0x00491BE4", "kind": "data"},
  {"symbol": "_data_0046cb80", "address": "0x0046CB80", "kind": "data"},
  {"symbol": "_data_0046cb5c", "address": "0x0046CB5C", "kind": "data"},
  {"symbol": "_data_0046cb50", "address": "0x0046CB50", "kind": "data"},
  {"symbol": "_data_0046cb68", "address": "0x0046CB68", "kind": "data"},
  {"symbol": "_data_00474f70", "address": "0x00474F70", "kind": "data"},
  {"symbol": "_callback_004014f0", "address": "0x004014F0", "kind": "data"},
  {"symbol": "_callback_00401510", "address": "0x00401510", "kind": "data"},
  {"symbol": "_callback_00401520", "address": "0x00401520", "kind": "data"},
  {"symbol": "_data_0046cb14", "address": "0x0046CB14", "kind": "data"},
  {"symbol": "_data_004776e0", "address": "0x004776E0", "kind": "data"},
  {"symbol": "__fltused", "address": "0x0", "kind": "metadata"},
  {"symbol": "?Recovery_LoadCachedResource@@YIPAUCachedResource@@HPAXPBD@Z", "address": "0x00447280", "kind": "relative_code"},
  {"symbol": "_SchedulerCallback_Create_00449ed0@4", "address": "0x00449ED0", "kind": "relative_code"},
  {"symbol": "@InitializeEntity_00401de0@8", "address": "0x00401DE0", "kind": "relative_code"},
  {"symbol": "@AnimationObject_ConfigureFromResource_0043e5a0@16", "address": "0x0043E5A0", "kind": "relative_code"},
  {"symbol": "??2@YAPAXI@Z", "address": "0x00452493", "kind": "relative_code"},
  {"symbol": "_DestroyGameThread_00401260@4", "address": "0x00401260", "kind": "relative_code"},
  {"symbol": "_Free_004524a1", "address": "0x004524A1", "kind": "relative_code"},
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
  {"symbol": "@__security_check_cookie@4", "address": "0x00458EA5", "kind": "relative_code"}
 ]}
```

`layout/ltcg/loader_chain_context.cpp`:

```cpp
// Compiler context only; never selected as recovered game code.
#include "../../src/game/load_game_thread_resources_00401110.cpp"
#include "th10/game/scheduler.hpp"

#pragma code_seg(".text$03context")
inline void* __cdecl operator new(unsigned int, void* memory) {
    return memory;
}

inline void __cdecl operator delete(void*, void*) {
}

GameThread* CreateGameThread_00401440();

// Roots the constructor through a placement-construction loop, the factory
// through its real call, and the scheduler registration pair through the
// array-walking shape their own cluster uses.
int __stdcall CreateGameThreadCompilerContext(GameThread* threads, int count,
                                              Scheduler* scheduler, SchedulerTask** tasks,
                                              int priority) {
    for (int index = 0; index < count; ++index)
        new (&threads[index]) GameThread;
    for (int index = 0; index < count; ++index) {
        SchedulerTask* task = tasks[index];
        Scheduler_RegisterPrimary(scheduler, task, priority);
        Scheduler_RegisterSecondary(scheduler, task, priority);
        Scheduler_RemoveLocked(scheduler, task);
    }
    void (__fastcall *volatile remove)(SchedulerTask*, Scheduler*) = &Scheduler_Remove;
    remove(tasks[0], scheduler);
    return CreateGameThread_00401440() != 0;
}
#pragma code_seg()
```

The 3-source configuration uses the same driver without the scheduler loop and
the 5-argument context (`?CreateGameThreadCompilerContext@@YGHPAUGameThread@@H@Z`,
emitted 50 bytes at `0x401270`; loader 332 bytes ends `0x40125C` so the gap
`0x0040125C` is 20 bytes and the trailing gap is 414 bytes).

## 7. Integration constraints found while building this

1. **Three clusters have to be dissolved into this one.** `scheduler_tasks.cpp`,
   `text_log.cpp` and `game_thread.cpp` are each claimed by their own layout and
   `load_clusters` rejects a source declared twice, so the wave has to replace
   `layout/ltcg/scheduler_tasks.json`, `layout/ltcg/d3d_text_log_append_0044b810.json`
   and `layout/ltcg/game_thread.json` with the merged layout
   (`joystick_probe.cpp` stays where it is; it is not needed here).
2. **`register_cluster.py` cannot register this layout.**
   `its update()` requires every selected function's region to be owned by the
   layout's own `source`, which is false for the five co-compiled regions. Use
   the `promote_clusters.py` path: set the region records (kind `semantic`,
   symbol, source) and append the layout to `ltcg_clusters`, then let
   `load_cluster` validate.
3. **`text_log.cpp`'s section name must move.** Its `#pragma code_seg` currently
   says `.text$03textlog`, which sorts before `.text$04create` and would place
   `0x44B810` in the low 0x4012xx block. All a cluster's section names are
   laid out in name order, so the text-log section has to sort after
   `.text$70remove`; the measured build uses `.text$85textlog` (one line in
   `text_log.cpp`, no byte change), which also means the d3d layout that
   declares `.text$03textlog` cannot survive beside it.
4. The callback pushes: `0x4014F0` and `0x401510` are landed as a member
   function and a free function respectively, so binding the push to those
   symbols needs the declaration their own sources use, not an invented
   `extern "C"` name (measured byte-identical with the placeholders; the symbol
   names themselves are not observable in the region's bytes, only at final
   link).
5. `0x00401000` and every co-compiled region stayed EXACT in both merged links,
   so the header swap and the merges do not disturb their bytes.

## 8. Shapes tried

| shape | result |
| --- | --- |
| plain TU, member function, nested `if` chain | 336 bytes, fail block out of line, 3 `je` |
| plain TU, short-circuit `if (a == 0 \|\| b == 0 \|\| c == 0)` | 332 bytes, fail block still out of line, 3 `je` |
| plain TU, three separate early-return blocks | 332 bytes, retail's `je/je/jne` layout reproduced |
| resource read at each use vs per-block local | 336 → 332 bytes; local matches retail's two loads |
| native link `{ctor, loader, factory}` | 332 bytes, entry EAX ✓, interior ESI ✗, **factory EXACT** |
| native link + `scheduler_tasks.cpp` with the four functions **rooted** | rejected: LINK keeps the public `__stdcall` shape, `0x449B70` moved to `0x449B80` |
| native link + `scheduler_tasks.cpp` + `text_log.cpp`, bodies called by the context | 326 bytes, interior EBX ✓, entry EBX ✗, three scheduler call sites and the `Append` call site byte-identical, all five co-compiled regions EXACT |

## 9. Reproduce

```bash
cp -a matching2/msvc /tmp/<id>/msvc
# scratch only: replace layout/ltcg/{scheduler_tasks,d3d_text_log_append_0044b810,game_thread}.json,
# set the five merged regions to kind semantic + symbol + source (§7.2), append the merged layout to
# ltcg_clusters, and rename text_log.cpp's code section to something sorting after .text$70remove (§7.3)
python3 matching2/tools/matching/probe.py --source src/game/load_game_thread_resources_00401110.cpp \
  --project /tmp/<id>/msvc --proposal /tmp/<id>/proposal.json --show 30
i686-w64-mingw32-objdump -d --no-show-raw-insn --start-address=0x401110 --stop-address=0x40125C \
  /tmp/<id>/ltcg/<build>/native-*/cluster.exe
```

`--proposal` needs one entry, because the region's inline-assembly symbol does
not name the compiled function:

```json
{"regions": [{"address": "0x00401110", "source": "src/game/load_game_thread_resources_00401110.cpp",
              "symbol": "?LoadGameThreadResources_00401110@GameThread@@QAEHXZ"}]}
```

Nothing from this run is in the maintained tree: no manifest edit, no layout, no
source. The scratch copy is `/tmp/LoadGameThreadRes/{msvc,plain/msvc,ltcg}` with
`run_cluster.py` as the build/compare driver (it re-derives every declared size
from the link map, which is what makes the gap addresses converge).
