# `0x00418E30` landed EXACT; `0x00419090` becomes exact under co-compilation; `0x00418D40` still 69 bytes off — wave 7

Date: 2026-09-19. Region `0x00418E30` (`StageTipRuntime_InitializeRetail`, 131
bytes) is **recovered and landed**: it is now an `additional_sources` +
`functions` entry of the existing native-LTCG cluster
`layout/ltcg/bullet_manager_load_scripts_0040ae70.json` (lesson 5's merge
pattern), so `src/game/scheduler_tasks.cpp` stays in exactly one cluster.

The two other regions of the same retail translation unit are **not** landed and
nothing was registered for them: `0x00418D40` still misses its store schedule
(237/237 bytes, 69 differing, unchanged from
`stage_tip_manager_construct_00418d40_model.md`), and `0x00419090` **is** exact —
0 differing bytes, 67/67 — as soon as the construct and the initializer are
co-compiled as C, which is the answer this ticket asked for, but that extension
cannot be registered while the construct's own body misses (a schema-1 cluster
must declare every function its sources emit).

## What landed

| file | sha256 |
| --- | --- |
| `src/game/stage_tip_runtime_initialize_retail_00418e30.cpp` | `02499731381ae916af247a1243ce5c9079bba700f169c78f610fdb57e0eef2b3` |
| `layout/ltcg/bullet_manager_load_scripts_0040ae70.json` | `94c38fc822ee6a9953b85cab38e0e62ba2709d94713ec3258f07ce6aa518edec` |
| `layout/ltcg/bullet_manager_load_scripts_0040ae70_context.cpp` | `9c173d9f9031d7e99f64dfdbfb5209cb0bf8299b862986bd9ba30a6957f76b18` |
| region `0x00418E30` in `regions.json` | `semantic_StageTipRuntime_InitializeRetail_00418e30_00418e30`, symbol `_asm_StageTipRuntime_InitializeRetail_00418e30@4`, kind `semantic`, size 131, with the asm record kept as `previous_record` |

Promoted with `matching2/tools/waves/promote_scratch.py --scratch
/tmp/StageTipPrereq/msvc --address 0x418E30 --apply`; `build_msvc.validate_project`
passes on the resulting manifest (4,425 regions, 2,394 translation units).

### Source text

```cpp
// 0x00418E30..0x00418EB2 (131 bytes): StageTipRuntime_InitializeRetail
//
// Creates and registers the two scheduler callbacks that drive the stage-tip
// manager, records them on the manager and clears the manager's +0x10 slot.
//
// Retail receives the manager in EBX - a register no MSVC convention assigns -
// and the registration calls keep the callback under construction in ESI with
// the registration priority in EDI, so this source is compiled in the same
// native-LTCG link as the scheduler registration functions it calls (see
// layout/ltcg/bullet_manager_load_scripts_0040ae70.json).
//
// The two closing manager stores and the byte read of data_00491D6A are
// volatile.  Without the qualifiers the scheduler hoists `mov al,[data_00491D6A]`
// and the `pop edi` that follows it above the two stores, which is 17 bytes of
// a schedule retail does not have; with them the emitted body is instruction for
// instruction retail's, and the qualifiers add no instruction of their own.
#include "th10/game/scheduler.hpp"

struct RawStageTipManager_00418e30 {
    unsigned char pad_000[0x08];
    void* primary_task_008;              // +0x008, first callback
    void* volatile secondary_task_00C;   // +0x00C, second callback
    void* volatile field_010;            // +0x010
};

extern "C" Scheduler* data_00491be4;
extern "C" volatile unsigned char data_00491d6a;
extern "C" SchedulerTask* __stdcall SchedulerCallback_Create_00449ed0(void* callback);
extern "C" int __stdcall asm_FUN_00419960_00419960(
        RawStageTipManager_00418e30* manager, const char* name, int flag);

extern "C" __declspec(noinline) int __stdcall
asm_StageTipRuntime_InitializeRetail_00418e30(RawStageTipManager_00418e30* manager);
#pragma code_seg(".text$00d_dinit")
extern "C" __declspec(noinline) int __stdcall
asm_StageTipRuntime_InitializeRetail_00418e30(RawStageTipManager_00418e30* manager) {
    SchedulerTask* primary = SchedulerCallback_Create_00449ed0((void*)0x4198A0);
    primary->context = manager;
    primary->reserved_flags &= ~1u;
    Scheduler_RegisterPrimary(data_00491be4, primary, 0x19);
    manager->primary_task_008 = primary;

    SchedulerTask* secondary = SchedulerCallback_Create_00449ed0((void*)0x4198B0);
    secondary->reserved_flags &= ~1u;
    secondary->context = manager;
    Scheduler_RegisterSecondary(data_00491be4, secondary, 0x2C);
    manager->secondary_task_00C = secondary;
    manager->field_010 = 0;

    if (data_00491d6a) {
        asm_FUN_00419960_00419960(manager, (const char*)0x46D6D8, 0);
        asm_FUN_00419960_00419960(manager, (const char*)0x46D6C4, 1);
    }
    return 0;
}
#pragma code_seg()
```

### Driver text

```cpp
// Compiler context only: this caller is not recovered application code.
#include "../../src/game/bullet_manager_load_scripts_0040ae70.cpp"

struct BulletManagerState_0040af90;
BulletManagerState_0040af90 *BulletManager_Create_0040af90();
extern "C" void *__cdecl asm_Recovery_CreateFixedState_004056b0(void);
extern "C" int __stdcall asm_Recovery_InstallPairClearFlags_0041ad90(void *pair);
extern "C" void *__cdecl asm_ScoreManager_CreateAndInitRetail_0041c290(void);

struct RawStageTipManager_00418e30;
extern "C" int __stdcall asm_StageTipRuntime_InitializeRetail_00418e30(
        RawStageTipManager_00418e30 *manager);

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
    for (int index = 0; index < count; ++index) {
        if (asm_ScoreManager_CreateAndInitRetail_0041c290())
            ++created;
    }
    for (int index = 0; index < count; ++index) {
        if (asm_StageTipRuntime_InitializeRetail_00418e30(
                (RawStageTipManager_00418e30 *)slots[index]) == 0)
            ++created;
    }
    return created;
}
#pragma code_seg()
```

### Layout JSON delta

Everything below is added to / changed in the maintained
`layout/ltcg/bullet_manager_load_scripts_0040ae70.json`; the rest of that file
(14 pre-existing functions, 15 gaps, 28 absolute symbols, the other driver
sources) is unchanged.

```json
  "additional_sources": [
    … "src/game/object_factories.cpp",
    "src/game/stage_tip_runtime_initialize_retail_00418e30.cpp"
  ],
  "functions": [
    …
    {
      "name": "StageTipRuntime_InitializeRetail_00418e30",
      "symbol": "_asm_StageTipRuntime_InitializeRetail_00418e30@4",
      "section": ".text$00d_dinit",
      "address": "0x00418E30",
      "size": 131,
      "actual_abi": "manager in EBX; result in EAX; plain RET",
      "source": "src/game/stage_tip_runtime_initialize_retail_00418e30.cpp"
    }
  ],
  "context": {
    "symbol": "?BulletManagerLoadScriptsCompilerContext@@YGHPAUScheduler@@PAPAUSchedulerTask@@HHPAPAUBulletManagerState_0040af90@@@Z",
    "section": ".text$90context",
    "address": "0x0044B900",
    "size": 194,
    "description": "Synthetic array-walking caller that establishes the loader's, the fixed-state factory's and the stage-tip initializer's register conventions; not recovered game code."
  },
  "gaps": [
    { "section": ".text$00d_agap", "address": "0x0040AFE6", "size": 56906 },
    { "section": ".text$00d_egap", "address": "0x00418EB3", "size": 7901 }
  ],
  "absolute_symbols": [
    …,
    { "symbol": "_data_00491d6a", "address": "0x00491D6A", "kind": "data" },
    { "symbol": "_asm_FUN_00419960_00419960@12", "address": "0x00419960", "kind": "relative_code" }
  ]
```

The gap that used to be `.text$00d_layout` (0x0040AFE6..0x0041AD90) is split
around the function: `.text$00d_agap` keeps the part before 0x00418E30,
`.text$00d_egap` covers 0x00418EB3..0x0041AD90. The section names sort
`.text$00d_agap` < `.text$00d_dinit` < `.text$00d_egap` < `.text$00e_installclear`,
which is what places the body at its retail address (lesson 6). The context grew
from 166 to 194 bytes because the synthetic driver gained a loop, which only
moves the declared size (its address stays 0x0044B900).

### Probe

```
$ python3 matching2/tools/matching/probe.py \
      --source src/game/stage_tip_runtime_initialize_retail_00418e30.cpp \
      --project matching2/msvc --output /tmp/StageTipPrereq/final2 --show 24
0x004055c0      84 bytes  _asm_Recovery_InstallPairSetFlags_004055c0@4  EXACT
0x004056b0      85 bytes  _asm_Recovery_CreateFixedState_004056b0  EXACT
0x0040ae70     134 bytes  _BulletManager_LoadScripts_0040ae70@4  EXACT
0x0040af90      86 bytes  ?BulletManager_Create_0040af90@@YGPAUBulletManagerState_0040af90@@XZ  EXACT
0x00418e30     131 bytes  _asm_StageTipRuntime_InitializeRetail_00418e30@4  EXACT
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
EXACT
```

`--json` for the region: `{"address": 4296240, "size": 131, "symbol":
"_asm_StageTipRuntime_InitializeRetail_00418e30@4", "different_bytes": 0,
"exact": true}`. The probe of a cluster source compares **every** region of the
merged layout, so the merge left the fourteen functions that were already there
exact (rows above).

## Registers

Who owns what, retail's side, and what the emitted bodies do.

| body | retail's registers | emitted |
| --- | --- | --- |
| `0x00418D40` construct | block in **EDX**, `ECX` dead, returns it in **EAX**, plain `ret` | same (EDX input, dead ECX slot, EAX result) |
| `0x00418E30` initializer | manager in **EBX**, never saved or modified; callback in **ESI**; priority in **EDI**; result in EAX | same |
| `0x00419090` factory | block in EAX, then **EDX** for the construct, manager homed in **EBX**, which is also the initializer's receiver | same, byte for byte |
| its caller `0x417AE5` | no argument register set; ECX/EDX dead behind the call; EBX/EBP/ESI/EDI live | the emitted region pushes and pops exactly one callee-saved register (EBX) and clobbers only EAX/ECX/EDX |

The initializer's EBX receiver is not a convention any declaration can name
(lesson 12). It appears only because the function is an internal function of the
same `/LTCG` link as the scheduler registration functions; the pass then picks
EBX for the parameter because the create-factory in the same link homes the
manager there.

## The two source-level facts that were needed

1. **`context` before the flags clear in the first callback.** Retail stores
   `[esi+0x20]` before `[esi+0x4]`:
   `mov 0x4(%esi),%edx; mov 0x491be4,%eax; and $~2,%edx; push %eax; mov $0x19,%edi;
   mov %ebx,0x20(%esi); mov %edx,0x4(%esi); call`.
   With the natural `reserved_flags &= ~1u;` first, the two stores come out
   swapped (first difference at 0x00418E50, 21 differing bytes). With
   `primary->context = manager;` written first the pair matches retail exactly.
   The second callback needs the memory form `andl $0xfffffffd,0x4(%esi)`, which
   both orders produce; only the first block is order-sensitive.
2. **`volatile` on the two closing manager stores and on the flag read.**
   `manager->secondary_task_00C = secondary; manager->field_010 = 0;` followed by
   `if (data_00491d6a)` is hoisted by the scheduler into
   `mov al,[0x491d6a]; test al,al; pop edi; mov [ebx+0xC],esi; movl $0,[ebx+0x10]; pop esi; je`
   — 5 rows, 17 bytes off, with `pop edi` split from `pop esi` (it cannot move
   above the store that reads ESI).  With the two stores and the read volatile the
   scheduler must keep the source order, the emitted body is retail's forty
   instructions in retail's order, and the qualifiers emit no instruction of
   their own.  The device costs behavior only in the sense of a stricter ordering
   the function already has.  Declaring the flag itself volatile is *not* enough —
   the stores have to be volatile too, or the load still hoists past them.

A third, cheaper fix was needed first: `0x00419960` is `__stdcall`
(`ret 0Ch`, three dword arguments).  Declaring it `__cdecl` added a
`add $0x18,%esp` epilogue to the two trailing calls, which is 3 bytes retail
does not have, and it also kept the body longer than 131 bytes, which pushed
every later section off its address.

## `0x00419090` — exact when co-compiled, not landable yet

Adding two more models to the same cluster — the construct as a C body
(`extern "C" void* __fastcall Construct_00418d40(int unused, StageTipManager*)`,
the dead leading slot dropped by the pass) and the factory
(`asm_Recovery_CreateResourceState_00419090`) — makes the factory emit **67
bytes, 0 differing bytes** with the full retail instruction stream:

```
419090  push %ebx
419091  push $0x1a8
419096  call 0x452493              ; operator new
41909b  add  $0x4,%esp
41909e  test %eax,%eax
4190a0  je   4190ad
4190a2  mov  %eax,%edx             ; no xor ecx,ecx
4190a4  call 0x418d40
4190a9  mov  %eax,%ebx             ; the manager homes in EBX, 0x418E30 reads EBX
4190ab  jmp  4190af
4190ad  xor  %ebx,%ebx
4190af  call 0x418e30
4190b4  test %eax,%eax
4190b6  je   4190cf
4190b8  test %ebx,%ebx
4190ba  je   4190cb
4190bc  push %ebx
4190bd  call 0x418ee0
4190c2  push %ebx
4190c3  call 0x4524a1
4190c8  add  $0x4,%esp
4190cb  xor  %eax,%eax
4190cd  pop  %ebx
4190ce  ret
4190cf  mov  %ebx,%eax
4190d1  pop  %ebx
4190d2  ret
```

That is the wave-6 prediction confirmed: with the construct's body analysable in
the same `/GL` link, the pass eliminates the dead `ECX` slot on its own
(experiment 1 of `recovery_create_resource_state_00419090_wave6.md`), and the
factory's home register then follows the initializer's EBX receiver
(experiment 3) instead of the ESI home the wave-6 attempt always got.

It is not registered because a schema-1 cluster has to declare every function
its sources emit, and the construct's body is still 69 bytes off; registering
the extension now would either break the build or need the construct to be bound
opaquely, and an opaque binding is exactly what puts `xor %ecx,%ecx` back into
the factory.  **Landing `0x00419090` therefore waits on `0x00418D40`.**  The
experiment lived in `/tmp/StageTipPrereq` (driver, layout and layout gap split
reproduced by `build_layout_co`/`coexp.py` there); nothing of it is in the tree,
`src/game/recovery_create_resource_state_00419090.cpp` and
`src/game/stage_tip_manager.cpp` are untouched.

## `0x00418D40` — emitted size equals retail, 69 differing bytes

`stage_tip_manager_construct_00418d40_model.md`'s residual reproduces exactly in
the co-compiled cluster: **237 bytes emitted against 237 retail, first
difference 0x00418D52, 69 differing bytes** — the `/GL` pass does not change this
one.  Byte-level shape: the prologue, the `rep stosd`, the `orl $0x2,(%edx)`, the
sixteen owner stores, `mov %edx,0x477814`, `mov %edx,%eax; pop %edi; ret` are all
present; the differing bytes are the *placement* of the owner stores relative to
the zero stores.

Retail groups them as follows (record `i`'s owner at `0x18+12i`):

```
rec0.owner  rec1.owner  rec0.04 rec0.08 rec1.04 rec1.08
rec2.owner  rec2.04 rec2.08   rec3.owner rec3.04 rec3.08
… records 4..7 the same single-record pattern …
rec8.owner  rec9.owner  rec8.04 rec8.08 rec9.04 rec9.08
rec10.owner rec10.04 rec10.08 … records 11..15 the same …
```

i.e. the owners of records 0/1 and of records 8/9 are hoisted in front of their
own zeros, and nowhere else.  The model emits `rec0.owner`, then `rec0.08`,
`rec0.04`, `rec1.08`, `rec1.04`, `rec1.owner`, `rec2.08`, `rec2.04`,
`rec2.owner`, … — a left rotation of the owner store by one record, which is
lesson 7 again.  The instruction multiset is identical; only the scheduler's
choice differs.

Shapes tried **inside the co-compiled cluster** (all 237 bytes, so all of them
keep the extent and the tail):

| constructor body | differing bytes |
| --- | ---: |
| sixteen inlined `InitRecord` calls, owner→08→04 | **69** |
| sixteen inlined `InitRecord` calls, 08→04→owner | **69** |
| sixteen inlined `InitRecord` calls, owner→04→08 | 80 |
| sixteen inlined `InitRecord` calls, 04→owner→08 | 80 |
| direct per-record assignments, owner→04→08 | 143 |
| direct per-record assignments, owner→08→04 | 144 |
| all sixteen owners, then all thirty-two zeros | 143 |
| the retail order transcribed literally | 143 |
| `for (i = 0; i < 16; ++i) InitRecord(...)` | 61 bytes — stays a loop |
| `for (i = 0; i < 16; i += 2) { InitRecord(i); InitRecord(i+1); }` | 61 bytes — stays a loop |

The literal transcription being *worse* than the inlined-helper form shows the
scheduler is reordering runs of stores regardless of the source order, so the
60-byte gap is not reachable by permuting the source statements; the two loop
forms confirm the region is genuinely unrolled in retail (237, not 61, bytes)
and that c2 will not unroll it for us.  The emitted body does keep the register
contract retail's one caller needs: the block arrives in **EDX**, `ECX` is
untouched, the block is returned in **EAX**, and the dead `ECX` slot is dropped
at every call site in the link.

## Next attempt on `0x00418D40`

The 8-record period of retail's grouping (owners hoisted for 0/1 and 8/9) looks
like a scheduler *region* boundary rather than a source shape: the block is
rotated at 0 and again at record 8, which is 0x60 bytes or 96 bytes of stores
apart.  Two things worth trying that were not:

* a helper that takes the record pointer as `unsigned char*` and writes through
  it, changing the alias class the scheduler sees;
* a constructor that keeps `manager` live after the global store through a
  second, later use, so the scheduler's store ordering has a different tail to
  work with (the note's experiment 1).

Once it lands, the two-model extension above should land `0x00419090` in the
same merge with no further source work.
