# Wave 15: two near-misses, measured (0x004364F0, 0x00405620)

2026-09-19, PoolRegionG. **Nothing landed.** No manifest entry, layout or source in the
maintained tree was touched; both models exist only in `/tmp/PoolRegionG/msvc`. Both are
recorded because each is a *size-exact* model stopped by a compiler-side codegen
tie-break, not by a semantic gap, and both deltas are measured rather than estimated.

| region | declared | emitted | different bytes | first difference |
|---|---:|---:|---:|---|
| `0x004364F0` `BufferFile::Seek` | 107 | 107 | **7** | `0x436539` |
| `0x00405620` `Recovery_ReleaseRawPairAndReset` | 137 | 137 | **4** | `0x40564E` |

Everything here was probed with
`python3 matching2/tools/matching/probe.py --source <src> --project /tmp/PoolRegionG/msvc --output /tmp/PoolRegionG/out --show 8`
against a `cp -a` copy. `build_msvc.validate_project` was not run (nothing was promoted).

## 0x00405620 — the closer of the two (4 bytes)

The function is the raw-pair release the pair factory (`0x004056B0`) and the deleting
destructor (`0x00405710`) both call; `RawPair_004056b0` in
`src/game/recovery_create_fixed_state_004056b0.cpp` already names the object, and
`Scheduler_RemoveLocked` in `src/game/scheduler_tasks.cpp` is the same lock/unlock block.

Model (this text stood in the copy's `src/game/player.cpp`, replacing the naked body):

```cpp
// 0x00405620: release the two scheduler callbacks the raw pair owns, each under
// the scheduler lock, then clear the published pointer.
#include "th10/game/scheduler.hpp"
#include "th10/platform/thread_sync.hpp"

struct RawPair_00405620 {
    unsigned int flags_000;             // +0x00
    unsigned char pad_004[4];
    SchedulerTask *callback_008;        // +0x08
    SchedulerTask *callback_00C;        // +0x0C
};

#define g_scheduler (*(Scheduler **)&data_00491be4)

extern "C" __declspec(noinline) void __stdcall
Recovery_ReleaseRawPairAndReset_00405620(RawPair_00405620 *pair) {
    SchedulerTask *task;
    Scheduler *scheduler;
    task = pair->callback_008;
    scheduler = g_scheduler;
    if (task) {
        EnterCriticalSection(&g_thread_synchronization.critical_sections[0]);
        ++g_thread_synchronization.scheduler_lock_depth;
        Scheduler_Remove(task, scheduler);
        LeaveCriticalSection(&g_thread_synchronization.critical_sections[0]);
        --g_thread_synchronization.scheduler_lock_depth;
    }
    task = pair->callback_00C;
    scheduler = g_scheduler;
    if (task) {
        EnterCriticalSection(&g_thread_synchronization.critical_sections[0]);
        ++g_thread_synchronization.scheduler_lock_depth;
        Scheduler_Remove(task, scheduler);
        LeaveCriticalSection(&g_thread_synchronization.critical_sections[0]);
        --g_thread_synchronization.scheduler_lock_depth;
    }
    *(unsigned int *)&data_004776ec = 0;
}
```

Probe: emitted extent **137 = declared 137**, `different_bytes` **4**, first difference
`0x0040564E`. Retail and the model agree byte-for-byte on the prologue (both IAT slots
loaded into EBX/EBP), the hoisted scheduler load before the `je`, the whole locked block,
the second block's ESI/EDI allocation, and the `data_004776EC` store. The only difference
is the order of the two argument moves in front of each `Scheduler_Remove` call:

```text
retail  0x40564E: 8b ce   mov ecx,esi     ; task
        0x405650: 8b d7   mov edx,edi     ; scheduler
model   0x40564E: 8b d7   mov edx,edi
        0x405650: 8b ce   mov ecx,esi
```

`0x00449F60` really is `Scheduler_Remove(SchedulerTask*, Scheduler*)` — its retail entry is
`push edi; xor edi,edi; cmp edi,ecx; je` then `lea 0x14(%edx),%eax`, so ECX is the
null-checked task and EDX the scheduler, exactly the project's landed model. The swap is
therefore a codegen order, not an argument-order error.

Shapes tried for the *load placement* (this is what got the delta from 14 to 4):

| shape | emitted | different bytes |
|---|---:|---:|
| `Scheduler_Remove(pair->cb8, g_scheduler)` read at the call site | 129 | — (scheduler reload after the lock) |
| `scheduler` read inside `if (task)` | 137 | 14 (load not hoisted past the `je`; block 2 swaps ESI/EDI) |
| `scheduler` read before `if (task)`, task in a local | 137 | **4** |
| `__forceinline` helper `(scheduler, task)` or `(task, scheduler)` called twice | 137 | 4 |
| declaration spelled `void*`, `SchedulerTask*, void*`, `void*, Scheduler*`, const-qualified | 137 | 4 |
| casts at the call, `copy_locals`, `task_only`, explicit `scheduler = 0` first | 137 | 4 or worse |
| pre- vs post-increment of `scheduler_lock_depth` | 137 | 4 |

Two structural facts worth keeping: the scheduler local has to be read **before** the
`if (task)` for its load to be scheduled ahead of the branch, and the task must be a
**local** so it stays in ESI across the lock (reading `pair->callback_00C` directly makes
MSVC reload it from the pair and lands on 129). The move order did not move for any of
~25 shapes. A two-object `/GL` + `/LTCG` control was started to test whether LINK 7.10's
whole-program codegen picks the forward order; the link discarded the function before the
control could be read (`/INCLUDE:` does not retain an unreferenced `/GL` body), so this is
unresolved and is the first thing to redo.

## 0x004364F0 — BufferFile::Seek (7 bytes)

`BufferFile`'s seventh vtable slot (`0x0046F320` = `0x004364F0`, vtable at `0x0046F300`);
the class, its vtable neighbours and `Read`/`Tell`/`GetSize` are already landed. Model
(all three cases assign `base`, one shared store after the switch):

```cpp
BYTE BufferFile::Seek(LONG distance, DWORD origin) {
    BYTE* base;
    switch (origin) {
    case 0:
        if (distance >= 0 && (DWORD)distance < size_)
            base = data_;
        else
            return 0;
        break;
    case 1: {
        LONG remaining = (LONG)((data_ + size_) - position_);
        if (remaining <= distance)
            return 0;
        base = position_;
        break;
    }
    case 2: {
        if (distance > 0)
            return 0;
        if ((DWORD)(distance < 0 ? -distance : distance) >= size_)
            return 0;
        base = data_ + size_;
        break;
    }
    default:
        return 0;
    }
    position_ = base + distance;
    return 1;
}
```

Probe: emitted extent **107 = declared 107**, `different_bytes` **7**, first difference
`0x00436539` (case 1's `jg`). Retail merges the shared tail into case 2's block and lets
case 0 keep a specialized copy (`mov edx,[ecx+0xc]; add edx,eax; mov [ecx+8],edx`, distance
in EAX); the model mirrors that — the tail merges into case 0's block and case 2 keeps the
copy, which also forces distance into EDX in case 0. Same instruction multiset, same
extent, different pairing.

Shapes tried (all 107 bytes and all with the mirrored pairing): per-case stores instead of
a shared `base` (118), `base` shared after the switch (122), `LONG base`/`void* base`/
`char* base`, `goto apply` from each case with the tail as a label in case 2 / after the
switch / before case 0, all six source orders of the case bodies (byte-identical output —
MSVC normalises case order), `default` first/middle/last, base assigned before vs after the
checks in each case, `(DWORD)-distance` vs the ternary magnitude, `if/else if` chains in
both orders, `position_ = &base[distance]` and integer-cast spellings, and 48 further
combinations of case check spellings. A `/GL` + `/LTCG` build of the same body produced the
identical mirrored body, so this is not an LTCG-visibility effect.

## What would unblock them

Both deltas are single-pass decisions with no semantic content: the fastcall argument-move
order (0x405620, 4 bytes) and which of two identical merged tails a conditional edge
targets (0x4364F0, 7 bytes). Neither moved for any source shape, so the next attempt should
not re-search the source: 0x405620 needs the two-object `/GL` control finished (a live
caller so `/INCLUDE:` retains the body) to see whether LINK's whole-program codegen emits
`mov ecx,esi; mov edx,edi`; 0x4364F0 likely needs a real anchor/context from the cluster
path that changes the block-merge order, not a different spelling of the same statement.
