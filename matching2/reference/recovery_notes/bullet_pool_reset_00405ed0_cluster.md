# 0x00405ED0 (`BulletPool::Reset`) — EXACT through a merged native-LTCG cluster

2026-09-19. Region `0x00405ED0` (45 bytes, `asm_BulletPool_ResetRetail_00405ed0`)
is recovered as `BulletPool::Reset` and probes **EXACT** (0 differing bytes).
It is the first semantic caller of the already landed helper `0x004493E0`
(`AnimationManager::MarkResourceForRemoval`), so the two regions now share one
cluster: `layout/ltcg/animation_manager_mark_resource_for_removal_004493e0.json`.
That cluster's 92-byte callee still probes **EXACT** after the merge (measured,
see below).

## The region

```asm
405ed0: mov    0x3e0b50(%esi),%edx      ; the pool's animation resource handle
405ed6: mov    0x491c10,%eax            ; the animation manager singleton
405edb: push   %edi
405edc: call   0x4493e0                 ; MarkResourceForRemoval(manager=EAX, resource=EDX)
405ee1: lea    0x60(%esi),%edx          ; pool base
405ee4: mov    $0xf82bc,%ecx            ; 0xF82BC dwords
405ee9: xor    %eax,%eax
405eeb: mov    %edx,%edi
405eed: rep stos %eax,%es:(%edi)        ; zero the whole slot array
405eef: mov    %edx,0x10(%esi)          ; free-slot cursor := pool base
405ef2: movw   $0x5,0x3e07a6(%esi)      ; state word := 5
405efb: pop    %edi
405efc: ret
```

Semantics, all corroborated by the surrounding bullet code rather than inferred
from the bytes: `+0x60` is the 0xF82BC-dword slot array and `+0x10` its cursor,
`+0x3E07A6` the state word and `+0x3E0B50` the `bullet.anm` resource handle —
`FUN_00405e20` (`0x00405E20`) stores the handle at `+0x3E0B50` and then writes
the very same `*(+0x10) = base` / `*(+0x3E07A6) = 5` pair, and
`legacy_semantic/src/game/bullet_manager.cpp` records the same three fields plus
the 0xF82BC-dword pool for `0x00405ED0`. `esi` is the pool, i.e. the retail
`/LTCG` scope chose a private ABI with the receiver in ESI; all four callers
(`0x0040A505`, `0x0040A65A`, `0x0041822E`, `0x0041842E`) load `[0x004776F0]`
into ESI before the call.

## Why the plain path cannot produce it

The plain `/O2` translation unit is 51 bytes:

```asm
push %esi / mov %esi,%ecx      ; receiver would arrive in ECX, so it is moved
mov 0x3e0b50(%esi),%eax        ; instead of retail's %edx
mov 0x491c10,%ecx              ; manager in ECX (6-byte load; retail uses the 5-byte A1 form)
push %edi / push %eax / call   ; resource passed on the stack
... identical memset/cursor/state tail ...
pop %edi / mov %edx,0x10(%esi) / movw $0x5,... / pop %esi / ret
```

The tail is byte-identical, so the *model* is right; the plain path fails only on
the ABI: the receiver register (ECX against retail's ESI) and the callee's private
argument registers. EAX/EDX cannot be requested by any declaration — EAX is not an
argument register in any MSVC convention — because the registers retail uses are
the ones the `/LTCG` pass picked for the pair, not a declared convention.

## The cluster, and why it is merged

`whole_program_ltcg.md` states the rule this region meets: **both sides of the
private call must be visible to the same `/LTCG` invocation**. With
`0x004493E0` bound only as an absolute symbol the caller emits `mov ecx,...`;
only with the callee's body in the same link does the pass give the receiver EAX
and the argument EDX, exactly as retail. A second cluster claiming
`src/render/animation_manager_mark_resource_for_removal_004493e0.cpp` is rejected
(`clusters must have distinct maintained sources`), so the existing cluster grew
instead: same layout path, same `name`, the new source added as
`additional_sources`, and a second entry in `functions` (each function carries
its own `source`). `ltcg_clusters` therefore needs **no** change — the path is
already registered.

`roots` stays empty on purpose: rooting either function would lock its public
convention (`whole_program_ltcg.md`'s negative control) — the pool function
would come back with ECX and the callee with ECX. Both functions are reachable
from the `/ENTRY` context, so `/OPT:REF` keeps them.

### Measured result

```
0x00405ed0      45 bytes  ?Reset@BulletPool@@QAEXXZ  EXACT
0x004493e0      92 bytes  ?MarkResourceForRemoval@AnimationManager@@QAEXPAX@Z  EXACT
EXACT
```

(`python3 matching2/tools/matching/probe.py --source
src/game/bullet_pool_reset_retail_00405ed0.cpp --project /tmp/BulletPoolReset/msvc
--output /tmp/BulletPoolReset/final --show 30`; re-run for reproducibility, both
regions `different_bytes: 0`.) The link map shows
`?Reset@BulletPool@@QAEXXZ 00405ed0 f source_000.obj` (the model, compiled `/GL`)
and `?MarkResourceForRemoval@AnimationManager@@QAEXPAX@Z 004493e0 f cluster.obj`,
and the emitted bytes at `0x00405ED0` are instruction-for-instruction and
operand-for-operand identical to the retail listing above — including the REL32
to `0x004493E0` and the absolute `0x00491C10` load.

## Artifacts

### `src/game/bullet_pool_reset_retail_00405ed0.cpp` (replaces the naked body)

```cpp
// 0x00405ED0 - Re-arm the bullet pool: retire the pool's animation resource,
// zero the whole slot array, rewind the free-slot cursor, and set the state
// word back to 5.
#include <string.h>

class AnimationManager {
public:
    void MarkResourceForRemoval(void* resource);
};

extern "C" AnimationManager* data_00491c10;

struct BulletPool {
    unsigned char reserved_000[0x10];
    unsigned int* cursor;
    unsigned char reserved_014[0x60 - 0x14];
    unsigned int slots[0xF82BC];
    void* animation;

    __declspec(noinline) void Reset();
};

#pragma code_seg(".text$01reset")
void BulletPool::Reset() {
    AnimationManager* manager = data_00491c10;
    manager->MarkResourceForRemoval(animation);
    memset(slots, 0, sizeof(slots));
    cursor = slots;
    *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(this) + 0x3E07A6) = 5;
}
#pragma code_seg()
```

The state word lives *inside* the slot array (`0x3E07A6 < 0x60 + 0xF82BC*4`), so
the source cannot declare it as a field after `slots`; it is addressed by offset,
as in `bullet_entity_mark_animation_for_removal_0040cea0.cpp`.

### `layout/ltcg/animation_manager_mark_resource_for_removal_004493e0.json` (merged; replaces the one-function layout)

```json
{
  "schema_version": 1,
  "name": "animation_manager_mark_resource_for_removal_004493e0",
  "source": "src/render/animation_manager_mark_resource_for_removal_004493e0.cpp",
  "driver": "layout/ltcg/animation_manager_mark_resource_for_removal_004493e0_context.cpp",
  "headers": [],
  "image_base": "0x00400000",
  "description": "The bullet pool reset and the animation-manager retirement helper compiled as one native /LTCG scope so the private call keeps retail's EAX/EDX argument registers and the pool arrives in ESI.",
  "functions": [
    {
      "name": "BulletPool_Reset_00405ed0",
      "symbol": "?Reset@BulletPool@@QAEXXZ",
      "section": ".text$01reset",
      "address": "0x00405ED0",
      "size": 45,
      "actual_abi": "pool in ESI; plain RET",
      "source": "src/game/bullet_pool_reset_retail_00405ed0.cpp"
    },
    {
      "name": "AnimationManager_MarkResourceForRemoval",
      "symbol": "?MarkResourceForRemoval@AnimationManager@@QAEXPAX@Z",
      "section": ".text$20helper",
      "address": "0x004493E0",
      "size": 92,
      "actual_abi": "animation manager in EAX; retired resource in EDX; plain RET"
    }
  ],
  "context": {
    "symbol": "?AnimationManagerHelperCompilerContext@@YGHPAPAUBulletPool@@H@Z",
    "section": ".text$30context",
    "address": "0x00449480",
    "size": 42,
    "description": "Synthetic array-walking caller that establishes the observed register conventions; not recovered game code."
  },
  "gaps": [
    { "section": ".text$00layout", "address": "0x00401000", "size": 20176 },
    { "section": ".text$02layout", "address": "0x00405EFD", "size": 275683 },
    { "section": ".text$25layout", "address": "0x0044943C", "size": 68 }
  ],
  "constants": [],
  "roots": [],
  "absolute_symbols": [
    { "symbol": "_data_00491c10", "address": "0x00491C10", "kind": "data" }
  ],
  "additional_sources": [
    "src/game/bullet_pool_reset_retail_00405ed0.cpp"
  ]
}
```

### `layout/ltcg/animation_manager_mark_resource_for_removal_004493e0_context.cpp` (replaces the array-of-managers context)

```cpp
// Compiler context only; never selected as recovered game code.
#include "../../src/render/animation_manager_mark_resource_for_removal_004493e0.cpp"

struct BulletPool {
    unsigned char reserved_0000[0x3E0B54];
    __declspec(noinline) void Reset();
};

#pragma code_seg(".text$30context")
int __stdcall AnimationManagerHelperCompilerContext(BulletPool** pools, int count) {
    while (count--) {
        BulletPool* pool = *pools++;
        pool->Reset();
        pool->Reset();
    }
    return 0;
}
#pragma code_seg()
```

The context keeps the pool live across the first call (hence the ESI receiver,
the shape `owned_pointer_array_00409eb0_context.cpp` uses) and reaches
`0x004493E0` only through `Reset`, so the callee has exactly one co-compiled call
site — the one retail has. The local `struct BulletPool` declaration decorates
`?Reset@BulletPool@@QAEXXZ` identically to the model, so the driver does not need
to include the model (`additional_sources` are compiled separately; including it
would define it twice).

## Integration

1. Replace the naked body in `src/game/bullet_pool_reset_retail_00405ed0.cpp`.
2. Write the merged layout over `layout/ltcg/animation_manager_mark_resource_for_removal_004493e0.json`
   (same path and `name`, so `ltcg_clusters` is untouched) and the driver over
   `…_004493e0_context.cpp`.
3. Rewrite just the `0x00405ED0` region record, keeping `previous_record`, exactly
   as `matching2/tools/waves/promote_clusters.py` does:

```json
{
  "name": "semantic_BulletPool_Reset_00405ed0",
  "source": "src/game/bullet_pool_reset_retail_00405ed0.cpp",
  "symbol": "?Reset@BulletPool@@QAEXXZ",
  "address": "0x00405ED0",
  "size": 45,
  "kind": "semantic",
  "owner": "0x00405ED0",
  "previous_record": {
    "name": "asm_BulletPool_ResetRetail_00405ed0",
    "source": "src/game/bullet_pool_reset_retail_00405ed0.cpp",
    "symbol": "_asm_BulletPool_ResetRetail_00405ed0",
    "address": "0x00405ED0",
    "size": 45,
    "kind": "asm",
    "owner": "0x00405ED0"
  }
}
```

`register_cluster.py --apply` **cannot** do step 3 for a merged layout: it
compares every function's region against the layout's single `source`, and the
two functions live in two sources, so it refuses before touching the manifest.
No other manifest field changes.

**No header edit and no additional source file are needed.** The model sits in
the region's existing source file; the driver declares its `BulletPool` locally;
the only new file is this note.

## Pitfalls this cost a build each

* The model needs `#pragma code_seg(".text$01reset")` — an `additional_source`
  TU is no exception: without it the function lands in the default `.text` at
  `0x00401000` and the layout fails with
  `native function address or compiler origin differs`.
* The context's declared extent must equal the emitted one (42 bytes here); a
  stale 53 (the old context's size) fails with
  `function compiler context extent is outside a MAP CODE contribution`.
* Rooting either function is not an option (`roots` stays `[]`); the callee is
  reached transitively through `Reset`, which is also what keeps its own
  EAX/EDX ABI instead of the public ECX one.
