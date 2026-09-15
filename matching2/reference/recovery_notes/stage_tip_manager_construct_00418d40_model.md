# 0x00418D40 — stage-tip manager construct: model at the retail extent, 69 bytes off

2026-09-16. `StageTipManager_Construct` (237 bytes) was reconstructed from its
retail listing. The model reaches **237 bytes, exactly the retail extent**, and
matches the prologue, the tail and 47 of its `mov` stores byte-for-byte; the
residual is where the scheduler places the sixteen owner stores relative to the
zero stores. The region stays assembly and
`matching2/msvc/src/game/stage_tip_manager.cpp` is unchanged.

## Verified shape

`__fastcall` free function: `int` parameter in ECX (unused), the manager in EDX,
the manager returned in EAX, plain `ret`. Body:

```cpp
static void InitRecord(StageTipRecord* record, StageTipManager_00418d40* owner) {
    record->owner = owner;                 // +0x00
    record->unknown_08 = 0;                // +0x08
    record->unknown_04 = 0;                // +0x04
}

__declspec(noinline) StageTipManager_00418d40* __fastcall
StageTipManager_Construct_00418d40(int unused, StageTipManager_00418d40* manager) {
    memset(manager, 0, 0x1A8);             // rep stosd, ecx = 0x6A
    manager->flags |= 2;                   // or dword [edx], 2
    InitRecord(&manager->records[0], manager);
    ... sixteen inlined calls ...
    data_00477814 = manager;               // mov [0x477814], edx
    return manager;                        // mov eax, edx
}
```

Manager layout: `flags` at `+0x00`, sixteen 12-byte records from `+0x18`
(`{owner, unknown_04, unknown_08}`), size `0x1A8`.

## Measured variants (maintained compile path)

| variant | extent | differing |
| --- | ---: | ---: |
| `void` return, per-record stores written owner-first | 235 | 23 |
| `void` return, owners then all zeros | 235 | 118 |
| pointer return, per-record stores inline | 237 | 143 |
| **pointer return, sixteen inlined `InitRecord` calls, owner→08→04** | **237** | **69** |
| same with owner→04→08, 08→04→owner, 08→owner→04 | 237 | 80/80/69 |

Two facts make this region interesting rather than merely blocked:

1. The **`void` form is the one that interleaves** owner and zero stores the way
   retail does (23 differing bytes) but it is two bytes short because it never
   emits retail's trailing `mov eax, edx`.
2. Every **pointer-returning** form emits the retail tail (`mov eax, edx; pop
   edi; ret`) and the retail extent, but the scheduler then groups the owner
   stores and places them one record later than retail.

The sixteen inlined `InitRecord` calls are the middle ground: extent and tail
exact, store placement unique to retail unreachable (`tools/waves/shape.py`
reports 0.94 register-normalised similarity for the `void` form).

## Next experiments

1. A construct that keeps the manager live to the end *without* the return
   value being the manager — the return is what flips the scheduler into
   grouping; e.g. a `volatile` global hand-off or a second use of `manager`
   after the global store.
2. Try `#pragma optimize("t", off)` on this function only (not tested here).
3. The record loop is *not* a loop in retail (237 bytes against 61 for the loop
   form), so the source was unrolled — keep that invariant in any retry.
