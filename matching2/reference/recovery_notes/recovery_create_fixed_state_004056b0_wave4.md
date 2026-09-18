# 0x004056B0 - Recovery_CreateFixedState: EXACT (85 bytes)

2026-09-19, wave 4. Region `0x004056B0..0x00405704` (85 bytes) is recovered as
readable C++ and is byte-exact under native LTCG. It lands inside the existing
`bullet_manager_load_scripts_0040ae70` cluster, which already carries the four
scheduler registration/removal functions the region's callee chain needs; the
region's callee `0x004055C0` is recovered with it (84 bytes, also exact) because
the pair's register agreement is established by that callee's body.

Probe line (throwaway copy, `--project /tmp/CreateFixedState/msvc`):

```text
0x004055c0      84 bytes  _asm_Recovery_InstallPairSetFlags_004055c0@4  EXACT
0x004056b0      85 bytes  _asm_Recovery_CreateFixedState_004056b0  EXACT
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

```
python3 matching2/tools/matching/probe.py \
    --source src/game/recovery_create_fixed_state_004056b0.cpp \
    --project /tmp/CreateFixedState/msvc --output /tmp/CreateFixedState/out --show 30
```

Measured directly from the cluster image as well: all ten declared functions are
0-differing bytes against retail, including the eight regions that cluster
already carried - adding the two functions did not disturb any of them.

## The model, verbatim (`src/game/recovery_create_fixed_state_004056b0.cpp`)

```cpp
// 0x004056B0..0x00405704 (85 bytes): Recovery_CreateFixedState
//
// Allocates the 0x48-byte fixed-state pair, zeroes it, clears bit 0 of its
// flag word at +0x24, raises bit 1 of its published flags and publishes it
// through data_004776EC.  The scheduler callbacks are then installed; when the
// installation fails the freshly built pair is released and freed again, and
// the factory reports NULL so callers can tell "not created" from "created".
//
// Retail keeps the pair in EBX across the installation, the release and the
// free. That is a whole-program register agreement: the installer at 0x004055C0
// holds the pair across the two scheduler registrations it reaches, which
// themselves keep the callback in ESI and the priority in EDI, so the pair is
// left in EBX. This source is therefore compiled in the same native-LTCG link
// as that callee chain (see layout/ltcg/bullet_manager_load_scripts_0040ae70.json).
#include <string.h>

void *__cdecl operator new(unsigned int size);

struct RawPair_004056b0 {
    unsigned int flags_000;             // +0x00, bit 1 = published
    unsigned char pad_004[4];
    void *callback_008;                 // +0x08
    void *callback_00C;                 // +0x0C
    unsigned char pad_010[0x14];
    unsigned int flags_024;             // +0x24
    unsigned char pad_028[0x20];
};

extern "C" void *data_004776ec;
extern "C" void __cdecl entry_free_004524a1(void *block);
extern "C" int __stdcall asm_Recovery_InstallPairSetFlags_004055c0(
        RawPair_004056b0 *pair);
extern "C" void __stdcall asm_Recovery_ReleaseRawPairAndReset_00405620(
        RawPair_004056b0 *pair);

#pragma code_seg(".text$00_xfixed")
extern "C" __declspec(noinline) void *__cdecl asm_Recovery_CreateFixedState_004056b0(void) {
    RawPair_004056b0 *fresh = new RawPair_004056b0;
    RawPair_004056b0 *state;
    if (fresh) {
        // The pair's low header flag is cleared before the block is zeroed.
        unsigned int *owned = (unsigned int *)((char *)fresh + 0x24);
        *owned &= ~1u;
        memset(fresh, 0, sizeof(RawPair_004056b0));
        fresh->flags_000 |= 2u;
        data_004776ec = fresh;
        state = fresh;
    } else {
        state = 0;
    }
    if (asm_Recovery_InstallPairSetFlags_004055c0(state) != 0) {
        if (state) {
            asm_Recovery_ReleaseRawPairAndReset_00405620(state);
            entry_free_004524a1(state);
        }
        return 0;
    }
    return state;
}
#pragma code_seg()
```

Retail's emitted order is `and [edx+24h],~1` (in place), `push edi`, the
`rep stosd` zeroing of all 0x48 bytes, `or [edx],2`, `mov [4776ec],edx`,
`mov ebx,edx`, `pop edi`, `jmp` over the out-of-line `xor ebx,ebx` - all of that
falls out of the model above: `new RawPair` produces the EDX temp / EBX result
pair, the conditional expression produces the two result arms.

## Second region recovered with it (`src/game/recovery_install_pair_set_flags_004055c0.cpp`)

0x004055C0 is the region's callee and the reason the pair lives in EBX. It was a
naked assembly body and is now the semantic model below; it measures 84/84
bytes exact.

```cpp
// 0x004055C0..0x00405613 (84 bytes): ?Recovery_InstallPairSetFlags@@
//
// Builds the two scheduler callbacks that drive a fixed-state pair, publishes
// each one on the pair, and registers them with the scheduler's primary and
// secondary lists.
//
// Retail receives the pair in EBX - not a parameter register of any MSVC
// convention. The register is a whole-program agreement the LTCG pass derives
// from the pair being live across both registration calls while the freshly
// created callback occupies ESI: this source is therefore compiled in the same
// native-LTCG link as the registration pair it calls (see
// layout/ltcg/bullet_manager_load_scripts_0040ae70.json).
#include "th10/game/scheduler.hpp"

struct RawPair_004055c0 {
    unsigned char pad_000[8];
    void *callback_008;                 // +0x08, primary scheduler callback
    void *callback_00C;                 // +0x0C, secondary scheduler callback
};

extern "C" SchedulerTask *__stdcall SchedulerCallback_Create_00449ed0(void *callback);
extern "C" void *data_00491be4;

#pragma code_seg(".text$00_vinstall")
extern "C" __declspec(noinline) int __stdcall
asm_Recovery_InstallPairSetFlags_004055c0(RawPair_004055c0 *pair) {
    SchedulerTask *primary = SchedulerCallback_Create_00449ed0((void *)0x405840);
    primary->reserved_flags |= 1u;
    primary->context = pair;
    Scheduler_RegisterPrimary((Scheduler *)data_00491be4, primary, 0x11);
    pair->callback_008 = primary;

    SchedulerTask *secondary = SchedulerCallback_Create_00449ed0((void *)0x405850);
    secondary->reserved_flags |= 1u;
    secondary->context = pair;
    Scheduler_RegisterSecondary((Scheduler *)data_00491be4, secondary, 0x22);
    pair->callback_00C = secondary;
    return 0;
}
#pragma code_seg()
```

## Why the cluster (and which one)

0x004056B0 has no live-in register at all, so a plain translation unit gets the
instruction sequence right but not the register: measured standalone it emits
**85 bytes with 9 differing bytes**, and every one of those nine is the
callee-saved register choice - `push %esi` / `mov %edx,%esi` / `test %esi,%esi` /
`xor %esi,%esi` / `push %esi` x2 / `pop %esi` x2 / `mov %esi,%eax` where retail
has EBX (`push %ebx`, `0x4056DB`, `0x4056E0`, `0x4056EB`, `0x4056EE`,
`0x4056F4`, `0x4056FF`, `0x405702`, `0x405703`). Everything else, including the
in-place `andl $0xfffffffe,0x24(%edx)`, the `rep stosd`, the out-of-line null
arm and both call sequences, already matched.

That register is a whole-program agreement, and the pass only derives it when the
callee chain is in the same link:

* With the installer left opaque (an absolute binding), the value is free and the
  pass takes ESI.
* Co-compiling only the installer with a visible `pair` parameter promotes the
  argument to a register, but with the scheduler calls still opaque the priority
  is a pushed immediate, EDI stays free, and the pass takes **EDI** - 83 bytes,
  wrong.
* Co-compiling the installer *and* the registration pair
  (`src/game/scheduler_tasks.cpp`, whose bodies keep the callback in ESI and the
  priority in EDI) forces the installer's pair parameter into EBX, and the
  caller follows: **85/85 exact**.

`scheduler_tasks.cpp` is already claimed by
`layout/ltcg/bullet_manager_load_scripts_0040ae70.json`, so per the wave
constraints the new regions merge into that layout as additional sources rather
than forming a second claimant.

## Layout (`layout/ltcg/bullet_manager_load_scripts_0040ae70.json`, complete)

Only additions; the eight existing functions, the context address and the
seven gaps below `.text$00a_loadscripts` are untouched. `context.size` grows
123 -> 133 because the driver now also calls the factory.

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
    "src/game/recovery_install_pair_set_flags_004055c0.cpp"
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
  "description": "BulletManager_LoadScripts and BulletManager_Create compiled with the scheduler registration/removal pair, the constant-log formatter and the joystick probe under native LTCG, so the pass keeps the manager in EBX, the callback in ESI and the registration priority in EDI. It also carries the fixed-state factory and the callback installer it calls, so the pass keeps the fixed-state pair in EBX across the installation, the release and the free.",
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
    }
  ],
  "context": {
    "symbol": "?BulletManagerLoadScriptsCompilerContext@@YGHPAUScheduler@@PAPAUSchedulerTask@@HHPAPAUBulletManagerState_0040af90@@@Z",
    "section": ".text$90context",
    "address": "0x0044B900",
    "size": 133,
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
      "size": 256762
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

The old `.text$00_layout` gap (40560 bytes) splits into three, because the two
new sections sit inside the range it covered and sections are placed in name
order: `.text$00_vinstall` and `.text$00_xfixed` sort after `.text$00_layout`
and before `.text$00a_loadscripts` (lesson 6 - a tag must sort after anything it
must follow). The bytes between the two functions
(0x00405614..0x004056B0, which contains the still-asm release helper at
0x00405620) are a zero-filled layout gap, not recovered code.

## Driver (`layout/ltcg/bullet_manager_load_scripts_0040ae70_context.cpp`, complete)

```cpp
// Compiler context only: this caller is not recovered application code.
#include "../../src/game/bullet_manager_load_scripts_0040ae70.cpp"

struct BulletManagerState_0040af90;
BulletManagerState_0040af90 *BulletManager_Create_0040af90();
extern "C" void *__cdecl asm_Recovery_CreateFixedState_004056b0(void);

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
    return created;
}
#pragma code_seg()
```

Measured: calling the factory inside the existing `slots[]` loop instead keeps
all ten regions exact as well, so the wiring is not fragile.

## Caller registers

The two retail callers of 0x004056B0 are `0x0040A350` (`call` with no argument
setup, result ignored in a global startup sequence) and `0x00417B93` (result
tested with `test eax,eax; je`). `0x0040A350` runs with **ESI live** - its caller
sets `ESI = [0x004776F8]` at `0x0040A341` and `0x0040A350` uses it again at
`0x0040A36A` - and with its own **EDI** pushed at `0x0040A350`; EBX is free
across the call. The emitted body matches that: EBX owns the pair across the
installation, release and free, ESI is never touched, and EDI is saved only
inside the zeroing block (`push edi` at +0x15, `pop edi` at +0x2C) exactly as
retail does.

## Integration (owner)

Two regions change record, both from this cluster:

```json
{ "name": "semantic_Recovery_CreateFixedState_004056b0_004056b0",
  "source": "src/game/recovery_create_fixed_state_004056b0.cpp",
  "symbol": "_asm_Recovery_CreateFixedState_004056b0",
  "address": "0x004056B0", "size": 85, "kind": "semantic", "owner": "0x004056B0" }
{ "name": "semantic_Recovery_InstallPairSetFlags_004055c0_004055c0",
  "source": "src/game/recovery_install_pair_set_flags_004055c0.cpp",
  "symbol": "_asm_Recovery_InstallPairSetFlags_004055c0@4",
  "address": "0x004055C0", "size": 84, "kind": "semantic", "owner": "0x004055C0" }
```

`register_cluster.py` cannot register a multi-source cluster (it requires every
function's region to be owned by the layout's primary source), so the merge is
the overwrite path the tooling already documents: `promote_scratch.py --scratch
/tmp/CreateFixedState/msvc --address 0x4056B0 --apply` and then the same for
`--address 0x4055C0`. Each run copies the layout, the driver and that region's
source and rewrites that region's record; the layout is already registered, so
the second run only overwrites it with the identical merged copy. The manifest's
`symbols` map keeps `_asm_Recovery_InstallPairSetFlags_004055c0` as a binding for
the assembly callers; the region now defines the `@4` spelling, and
`make_link_script` now assigns the old name instead of skipping it - GNU ld
accepts a script assignment over an object definition (checked with a two-line
object+script probe: `SECTIONS { .text 0x401000 : { *(.text) *(.text$*) }
foo = 0x401000; }` over an object that defines `foo` links clean). The only other
object that spells the old name is `player.cpp`'s stale copy of the installer
body, which no region selects.

## Shapes tried before the chain (all standalone LTCG, 85-byte target)

| model | emitted | first difference |
|---|---:|---|
| `fresh->flags_024 &= ~1u;` + memset + or + install as a no-argument call | 84/85, 67 differing | structure: `and` load/and/store, no conditional value |
| `new RawPair` + one variable | 90/85 | `and` 9 bytes instead of 4 |
| two variables + `if/else` (bullet-manager shape) | 90/85 | same |
| type-punned flag-pointer local `*(unsigned*)((char*)fresh+0x24) &= ~1u` | 85/85, **9 differing** | only the callee-saved register |
| same + `__stdcall` / C++-mangled / `__fastcall` / extra-argument declaration | 85/85, 9 differing | no change |
| same + synthetic caller keeping ESI and EDI live across the call | 85/85, 9 differing | no change |
| same + extra co-compiled helper functions in the module | 85/85, 9 differing | no change |
| installer co-compiled with a parameter, schedulers opaque | 83/85 | pass picks EDI |
| installer + registration pair co-compiled (landed) | **85/85, 0 differing** | - |

The in-place `andl $0xfffffffe,0x24(%edx)` is itself a source-shape finding: a
plain `fresh->flags_024 &= ~1u;` before a `memset` of the whole object is
lowered to `mov/and/mov` (+5 bytes) because the load is hoisted above the
`push edi`; only an access through a pointer the optimizer cannot coalesce with
`fresh` (the type-punned `unsigned int *owned`) keeps the memory form. Bisected
in isolation: `p->f &= ~1u; memset(p,0,sizeof); p->f |= 2u;` stays in place,
`p->f &= ~1u; memset(p,0,sizeof); p->g |= 2u;` does not.

No test file was added: the cluster's own byte comparison and the probe are the
gate, and the whole-image build is the owner's.
