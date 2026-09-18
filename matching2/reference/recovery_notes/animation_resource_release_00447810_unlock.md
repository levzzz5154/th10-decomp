# 0x00447810 + 0x004477D0 — both EXACT in one merged native-LTCG cluster, no scaffolding

2026-09-19. Region `0x00447810` (242 bytes, `asm_FUN_00447810_00447810`) is recovered as
`AnimationResource_00447810::Release` and probes **EXACT (242/242, 0 differing bytes)**. Because
its receiver register is EDI, it had to join the `/LTCG` link that already carries
`AnimationManager::MarkResourceForRemoval` and `BulletPool::Reset`; the merged cluster
`layout/ltcg/animation_manager_mark_resource_for_removal_004493e0.json` grew a third function, and
the dependent caller `0x004477D0` (`AnimationManager_ClearResourceSlot`) grew in with it as a
fourth. **`0x004477D0` now probes EXACT as well, with no scaffolding function anywhere** — its
whole-program call to `0x00447810` resolves against the real recovered body, which is what puts
the record in EDI. Both previously landed regions sharing the cluster
(`0x00405ED0`, `0x004493E0`) still probe EXACT after the merge (measured).

## The region

```
00447810  51                    push  ecx
00447811  8b 87 08 01 00 00     mov   eax,[edi+0x108]
00447817  55                    push  ebp
00447818  33 ed                 xor   ebp,ebp
0044781a  3b c5                 cmp   eax,ebp
0044781c  0f 84 dd 00 00 00     je    004478ff
00447822  a1 10 1c 49 00        mov   eax,ds:0x491C10          ; animation-manager singleton
00447827  8b d7                 mov   edx,edi                 ; retired record
00447829  e8 b2 1b 00 00        call  004493E0                 ; MarkResourceForRemoval(EAX, EDX)
0044782e  39 af 0c 01 00 00     cmp   [edi+0x10C],ebp
00447834  89 6c 24 04           mov   [esp+4],ebp
00447838  7e 48                 jle   00447882                 ; entry_count <= 0
0044783a  53 56 33 db 8b ff     push ebx / push esi / xor ebx,ebx / mov edi,edi   (16-byte loop align)
00447840  8b b7 20 01 00 00     mov   esi,[edi+0x120]          ; loop head, 16-aligned
00447846  8b 04 1e              mov   eax,[esi+ebx]
00447849  03 f3                 add   esi,ebx                  ; esi = &entries[i]
0044784b  3b c5                 cmp   eax,ebp
0044784d  74 08                 je    00447857
0044784f  8b 08                 mov   ecx,[eax]
00447851  50                    push  eax
00447852  ff 51 08              call  [ecx+8]                  ; handle->slot2(), this pushed
00447855  89 2e                 mov   [esi],ebp                ; entry->handle = 0
00447857  8b 46 04              mov   eax,[esi+4]
0044785a  3b c5                 cmp   eax,ebp
0044785c  74 0c                 je    0044786a
0044785e  50                    push  eax
0044785f  e8 be ab 00 00        call  00452422                 ; free(entry->allocation)
00447864  83 c4 04              add   esp,4
00447867  89 6e 04              mov   [esi+4],ebp              ; entry->allocation = 0
0044786a  8b 44 24 0c           mov   eax,[esp+0xC]            ; index (in memory)
0044786e  8b 8f 0c 01 00 00     mov   ecx,[edi+0x10C]          ; entry_count re-read
00447874  40 83 c3 10           inc eax / add ebx,0x10
00447878  3b c1                 cmp   eax,ecx
0044787a  89 44 24 0c           mov   [esp+0xC],eax
0044787e  7c c0                 jl    00447840
00447880  5e 5b                 pop esi / pop ebx
00447882  .. tail frees ..      [edi+0x120], [edi+0x118], [edi+0x11C], [edi+0x12C], [edi+0x108]
004478ff  5d 59 c3              pop ebp / pop ecx / ret
```

`+0x108` guards the call (`== 0` returns) and is freed last; `+0x10C` is a signed entry count;
`+0x118`, `+0x11C`, `+0x120`, `+0x12C` are allocations freed and zeroed in that order after the
loop. Each 0x10-byte entry is `{handle, allocation}` — the handle's third virtual slot is called
with the handle pushed (`__stdcall` member), the allocation goes through the CRT free at
`0x00452422`. The record itself is the argument to `MarkResourceForRemoval`: retail loads
`0x491C10` and moves **EDI** to EDX, i.e. the record, not `[+0x108]`.

## Receiver register (the question the wave asked)

Every one of the 24 call sites sets **EDI** to the record before the call (e.g. the naked caller
at `0x00402593`: `mov edi,[ecx+eax*4+0x3AD06C]; test edi,edi; call 0x00447810`), and the body
never writes EDI, so EDI is a callee-saved receiver argument and not a declared convention. The
emitted body **keeps EDI** — it is instruction-for-instruction and operand-for-operand identical
to retail, so `mov edx,edi`, `[edi+0x108]`, `call [ecx+8]` all agree. The co-compiled caller
therefore emits `mov edi,[ebx+esi*4+0x3AD06C]` … `call 0x00447810` with no register moves at all.

## Recovered source (`src/render/fun_00447810_00447810.cpp`, replaces the naked body)

```cpp
// 0x00447810..0x004478F6: retire one cached animation-resource record.
//
// Retail enters with the record in EDI - every one of its 24 call sites loads
// it there - and hands the record to AnimationManager::MarkResourceForRemoval
// with the manager singleton in EAX and the record in EDX.  Neither convention
// is expressible as a declaration: an external callee keeps the convention its
// prototype names, and no MSVC convention puts an argument in EAX.  Both are
// choices of the native /LTCG pass, so this model lives in the same
// whole-program link as that helper: the merged
// layout/ltcg/animation_manager_mark_resource_for_removal_004493e0.json
// cluster, whose driver carries the synthetic caller that establishes the
// record in EDI.
//
// The loop holds a pointer to the current entry instead of re-indexing the
// array.  Retail keeps that pointer live in ESI across the interface release
// and the free; that is the pressure which moves the receiver out of ESI and
// into EDI.

class AnimationManager {
public:
    void MarkResourceForRemoval(void* resource);
};

extern "C" AnimationManager* data_00491c10;

// CRT free, the entry at 0x00452422 (0x004524A1 is the five-byte jump to it).
extern "C" void __cdecl entry_free_00452422(void* memory);

// One entry's animation interface.  Retail calls its third virtual slot (+0x8)
// with the interface itself pushed, i.e. a __stdcall member.
struct AnimationHandle_00447810 {
    virtual void slot0();
    virtual void slot1();
    virtual void __stdcall slot2();
};

struct AnimationResourceEntry_00447810 {
    AnimationHandle_00447810* handle;   // +0x00
    void* allocation;                   // +0x04
    unsigned char pad_008[8];
};

struct AnimationResource_00447810 {
    unsigned char pad_000[0x108];
    void* resource_108;                            // +0x108: the record's own interface
    int entry_count_10c;                           // +0x10C
    unsigned char pad_110[0x118 - 0x110];
    void* auxiliary_118;                           // +0x118
    void* auxiliary_11c;                           // +0x11C
    AnimationResourceEntry_00447810* entries_120;  // +0x120
    unsigned char pad_124[0x12C - 0x124];
    void* auxiliary_12c;                           // +0x12C

    __declspec(noinline) void Release();
};

#pragma code_seg(".text$10release")
void AnimationResource_00447810::Release() {
    if (resource_108 == 0)
        return;
    data_00491c10->MarkResourceForRemoval(this);
    for (int index = 0; index < entry_count_10c; ++index) {
        AnimationResourceEntry_00447810* entry = &entries_120[index];
        if (entry->handle != 0) {
            entry->handle->slot2();
            entry->handle = 0;
        }
        if (entry->allocation != 0) {
            entry_free_00452422(entry->allocation);
            entry->allocation = 0;
        }
    }
    if (entries_120 != 0) {
        entry_free_00452422(entries_120);
        entries_120 = 0;
    }
    if (auxiliary_118 != 0) {
        entry_free_00452422(auxiliary_118);
        auxiliary_118 = 0;
    }
    if (auxiliary_11c != 0) {
        entry_free_00452422(auxiliary_11c);
        auxiliary_11c = 0;
    }
    if (auxiliary_12c != 0) {
        entry_free_00452422(auxiliary_12c);
        auxiliary_12c = 0;
    }
    if (resource_108 != 0) {
        entry_free_00452422(resource_108);
        resource_108 = 0;
    }
}
#pragma code_seg()
```

## The caller (`src/render/animation_manager_clear_resource_slot_004477d0.cpp`)

Landed with it; this text is the model from
`animation_manager_clear_resource_slot_004477d0_cluster.md` with its `extern "C"` callee
declaration replaced by the real `Release` member (the scaffolding body is gone).

```cpp
// 0x004477D0..0x00447806: release and null one animation-manager resource slot.
//
// Retail enters with the manager singleton in EBX and the slot index in ESI,
// and hands the slot's record to the release routine at 0x00447810 in EDI:
// conventions only a native /LTCG link of this source chooses.  They come from
// this region's place in layout/ltcg/animation_manager_mark_resource_for_removal_004493e0.json,
// whose synthetic caller keeps the manager and the index in those registers and
// whose co-compiled release body is the real recovered 0x00447810 model.
//
// The two range tests stay separate because retail has both (jl and jae); a
// merged (unsigned)index >= 0x21u produces a single jae.
struct AnimationResource_00447810 {
    __declspec(noinline) void Release();
};

extern "C" void __cdecl entry_free_004524a1(void* memory);

struct AnimationManager_004477d0 {
    unsigned char pad_000[0x3AD06C];
    AnimationResource_00447810* slots_3ad06c[0x21];   // +0x3AD06C

    __declspec(noinline) void ClearResourceSlot(int index);
};

#pragma code_seg(".text$08clear")
void AnimationManager_004477d0::ClearResourceSlot(int index) {
    if (index < 0)
        return;
    if ((unsigned)index >= 0x21u)
        return;
    if (slots_3ad06c[index] == 0)
        return;
    slots_3ad06c[index]->Release();
    entry_free_004524a1(slots_3ad06c[index]);
    slots_3ad06c[index] = 0;
}
#pragma code_seg()
```

## Driver (`layout/ltcg/animation_manager_mark_resource_for_removal_004493e0_context.cpp`)

```cpp
// Compiler context only; never selected as recovered game code.
#include "../../src/render/animation_manager_mark_resource_for_removal_004493e0.cpp"

struct BulletPool {
    unsigned char reserved_0000[0x3E0B54];
    __declspec(noinline) void Reset();
};

struct AnimationResource_00447810 {
    unsigned char pad_000[0x108];
    void* resource_108;
    int entry_count_10c;
    unsigned char pad_110[0x118 - 0x110];
    void* auxiliary_118;
    void* auxiliary_11c;
    void* entries_120;
    unsigned char pad_124[0x12C - 0x124];
    void* auxiliary_12c;
    __declspec(noinline) void Release();
};

struct AnimationManager_004477d0 {
    unsigned char pad_000[0x3AD06C];
    AnimationResource_00447810* slots_3ad06c[0x21];
    __declspec(noinline) void ClearResourceSlot(int index);
};

#pragma code_seg(".text$30context")
int __stdcall AnimationManagerHelperCompilerContext(BulletPool** pools,
                                                    AnimationResource_00447810** records,
                                                    AnimationManager_004477d0* manager,
                                                    int first, int count) {
    while (count--) {
        BulletPool* pool = *pools++;
        pool->Reset();
        pool->Reset();
        AnimationResource_00447810* record = *records++;
        record->Release();
    }
    int index = first;
    while (count--) {
        manager->ClearResourceSlot(index);
        index++;
    }
    return index;
}
#pragma code_seg()
```

The context is one function with the two shapes the cluster needs. The first loop keeps the pool
pointer live across both `Reset` calls (pool in **ESI**, and therefore the retired-resource call
in **EAX/EDX**); the record-array walk gives `Release` its receiver, and with the entry pointer
live in the loop body the receiver comes out **EDI**, which in turn forces the caller's manager
into **EBX** and its index into **ESI** — exactly retail. The second loop's `manager`/`index`
shape is the one `animation_manager_clear_resource_slot_004477d0_cluster.md` measured; it now
needs no scaffolding body because the callee is real recovered code.

## Layout (`layout/ltcg/animation_manager_mark_resource_for_removal_004493e0.json`, merged)

```json
{
  "schema_version": 1,
  "name": "animation_manager_mark_resource_for_removal_004493e0",
  "source": "src/render/animation_manager_mark_resource_for_removal_004493e0.cpp",
  "driver": "layout/ltcg/animation_manager_mark_resource_for_removal_004493e0_context.cpp",
  "headers": [],
  "image_base": "0x00400000",
  "description": "AnimationManagerMarkResourceForRemoval, BulletPool::Reset, the resource release and its slot caller in one native /LTCG scope.",
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
      "name": "AnimationManager_ClearResourceSlot",
      "symbol": "?ClearResourceSlot@AnimationManager_004477d0@@QAEXH@Z",
      "section": ".text$08clear",
      "address": "0x004477D0",
      "size": 55,
      "actual_abi": "manager in EBX; index in ESI; record in EDI; plain RET",
      "source": "src/render/animation_manager_clear_resource_slot_004477d0.cpp"
    },
    {
      "name": "AnimationResource_Release",
      "symbol": "?Release@AnimationResource_00447810@@QAEXXZ",
      "section": ".text$10release",
      "address": "0x00447810",
      "size": 242,
      "actual_abi": "record in EDI; plain RET",
      "source": "src/render/fun_00447810_00447810.cpp"
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
    "symbol": "?AnimationManagerHelperCompilerContext@@YGHPAPAUBulletPool@@PAPAUAnimationResource_00447810@@PAUAnimationManager_004477d0@@HH@Z",
    "section": ".text$30context",
    "address": "0x00449480",
    "size": 101,
    "description": "Synthetic array-walking caller; not recovered game code."
  },
  "gaps": [
    { "section": ".text$00layout", "address": "0x00401000", "size": 20176 },
    { "section": ".text$02layout", "address": "0x00405EFD", "size": 268499 },
    { "section": ".text$09layout", "address": "0x00447807", "size": 9 },
    { "section": ".text$15layout", "address": "0x00447902", "size": 6878 },
    { "section": ".text$25layout", "address": "0x0044943C", "size": 68 }
  ],
  "constants": [],
  "roots": [],
  "absolute_symbols": [
    { "symbol": "_data_00491c10", "address": "0x00491C10", "kind": "data" },
    { "symbol": "_entry_free_00452422", "address": "0x00452422", "kind": "relative_code" },
    { "symbol": "_entry_free_004524a1", "address": "0x004524A1", "kind": "relative_code" }
  ],
  "additional_sources": [
    "src/game/bullet_pool_reset_retail_00405ed0.cpp",
    "src/render/fun_00447810_00447810.cpp",
    "src/render/animation_manager_clear_resource_slot_004477d0.cpp"
  ]
}
```

`roots` stays empty: rooting any of the four would lock its public convention
(`whole_program_ltcg.md`, negative control) — `0x00447810` would come back with ECX, the pool
with ECX, and the caller with ECX.

## Measured result

Emitted bytes at `0x00447810` (identical to retail, sha256
`4b5c726a5ccfd93707e41e0a826a6bfb4d01b63251123ac884bfd3681dc7b3bb`):

```
518b87080100005533ed3bc50f84dd000000a1101c49008bd7e8b21b000039af0c010000896c24047e485356
33db8bff8bb7200100008b041e03f33bc574088b0850ff5108892e8b46043bc5740c50e8beab000083c404
896e048b44240c8b8f0c0100004083c3103bc18944240c7cc05e5b8b87200100003bc5740f50e890ab0000
83c40489af200100008b87180100003bc5740f50e877ab000083c40489af180100008b871c0100003bc574
0f50e85eab000083c40489af1c0100008b872c0100003bc5740f50e845ab000083c40489af2c0100008b87
080100003bc5740f50e82cab000083c40489af080100005d59c3
```

Emitted bytes at `0x004477D0` — byte-identical to retail, no scaffolding in the link:

```
85f67c3283fe21732d578bbcb36cd03a0085ff7420e8260000008b84b36cd03a0050e8aaac000083c404
c784b36cd03a00000000005fc3
```

Probe (maintained tools, scratch project `/tmp/ReleaseDispatch/msvc`; the same four regions are
reported from either entry source because they share one cluster):

```
$ python3 matching2/tools/matching/probe.py --source src/render/fun_00447810_00447810.cpp \
      --project /tmp/ReleaseDispatch/msvc --output /tmp/ReleaseDispatch/out --show 30
0x00405ed0      45 bytes  ?Reset@BulletPool@@QAEXXZ  EXACT
0x004477d0      55 bytes  ?ClearResourceSlot@AnimationManager_004477d0@@QAEXH@Z  EXACT
0x00447810     242 bytes  ?Release@AnimationResource_00447810@@QAEXXZ  EXACT
0x004493e0      92 bytes  ?MarkResourceForRemoval@AnimationManager@@QAEXPAX@Z  EXACT
EXACT

$ python3 matching2/tools/matching/probe.py --source src/render/animation_manager_clear_resource_slot_004477d0.cpp \
      --project /tmp/ReleaseDispatch/msvc --output /tmp/ReleaseDispatch/out --show 30
0x00405ed0  45  EXACT
0x004477d0  55  EXACT
0x00447810 242  EXACT
0x004493e0  92  EXACT
EXACT
```

So the dependent region lands: **`0x004477D0` probes EXACT with no scaffolding**, and the two
regions already in the cluster are unchanged.

## Shapes tried (242-byte target)

| shape | emitted | first delta | receiver |
| --- | --- | --- | --- |
| `entries_120[index].handle` / `.allocation` written out at each use (natural re-indexing) | 256 | `+0x0`: got `8b` (`mov eax,[esi+0x108]`) want `51` (`push ecx`); 201 bytes differ | ESI, and `esi`/`edi`/`ebp` carry zero/index/counter while the entry pointer is not live across the calls |
| pointer local `AnimationResourceEntry* entry = &entries_120[index]`, one base load per iteration | **242** | none | **EDI**; zero in EBP, byte index in EBX, entry pointer live in ESI — retail's allocation |

The re-indexing shape fails on the loop, not on the prologue: it reloads `[this+0x120]` for every
`handle`/`allocation` use and never keeps the entry address across the interface call, so the pass
can serve the whole loop from EBX/EDI/EBP and hands `this` the ESI the caller was about to use.
Holding the entry pointer across both calls costs the loop the fourth callee-saved register; the
counter then spills to `[esp+0xC]` exactly as retail's does, and the pass moves the receiver to
EDI and spills nothing else.

## Why it cannot be a standalone cluster, and why it must be a merged layout

The model calls `AnimationManager::MarkResourceForRemoval` with the manager in **EAX** and the
record in **EDX**. No MSVC convention puts an argument in EAX, and — as
`bullet_pool_reset_00405ed0_cluster.md` measured — an external binding keeps whatever convention
its declaration names (`__thiscall` → ECX + pushed argument, `__fastcall` → ECX/EDX). The only way
to reach EAX/EDX is to have the callee's IL in the same `/LTCG` invocation, and that source is
already claimed by the registered `animation_manager_mark_resource_for_removal_004493e0` cluster
(`clusters must have distinct maintained sources`), so the cluster grew rather than a second one
being created — the pattern of commit `6271088e`.

`register_cluster.py --apply` cannot register a merged layout: it compares every function's
region against the layout's single `source` and refuses before touching the manifest:

```
$ python3 matching2/tools/waves/register_cluster.py --project /tmp/ReleaseDispatch/msvc \
      --layout layout/ltcg/animation_manager_mark_resource_for_removal_004493e0.json
refused: region 0x405ed0 is owned by src/game/bullet_pool_reset_retail_00405ed0.cpp, not src/render/animation_manager_mark_resource_for_removal_004493e0.cpp
```

`ltcg_clusters` therefore needs **no change** (the layout path is already registered); only the
region records move.

## Integration

`promote_scratch.py` performs the whole merge, once per address. The layout is already in the
maintained `ltcg_clusters`, so it is copied as an "already registered - overwritten, merge"
layout and `register_cluster.py` is not invoked for it:

```
python3 matching2/tools/waves/promote_scratch.py --scratch /tmp/ReleaseDispatch/msvc --address 0x447810 --apply
python3 matching2/tools/waves/promote_scratch.py --scratch /tmp/ReleaseDispatch/msvc --address 0x4477D0 --apply
```

That copies `src/render/fun_00447810_00447810.cpp`,
`src/render/animation_manager_clear_resource_slot_004477d0.cpp`, the merged layout and its driver,
and rewrites exactly the two region records below (keeping `previous_record`, as
`promote_clusters.py` does).

**The two promotions are one change.** The merged layout declares four functions from four
sources, and `load_cluster` requires every region of those sources to be a declared function, so
after only one of the two calls the manifest no longer matches the layout and *every* unit fails
to load. Apply both before the next build; with both applied the tree equals the verified state
(the scratch manifest differs from the maintained one in exactly those two records and nothing
else).

No other manifest field changes — in particular `symbols` still maps
`_asm_FUN_00447810_00447810` and `_asm_AnimationManager_ClearResourceSlot_004477d0` to the same
addresses, which is what keeps the 24 naked callers of `0x00447810` (e.g.
`src/game/destroy_game_state_00402440.cpp:194`, which already sets EDI) and the callers of
`0x004477D0` resolving.

```json
{
  "name": "semantic_AnimationResource_Release_00447810",
  "source": "src/render/fun_00447810_00447810.cpp",
  "symbol": "?Release@AnimationResource_00447810@@QAEXXZ",
  "address": "0x00447810",
  "size": 242,
  "kind": "semantic",
  "owner": "0x00447810",
  "previous_record": {
    "name": "asm_FUN_00447810_00447810",
    "source": "src/render/fun_00447810_00447810.cpp",
    "symbol": "_asm_FUN_00447810_00447810",
    "address": "0x00447810",
    "size": 242,
    "kind": "asm",
    "owner": "0x00447810"
  }
}
```

```json
{
  "name": "semantic_AnimationManager_ClearResourceSlot_004477d0",
  "source": "src/render/animation_manager_clear_resource_slot_004477d0.cpp",
  "symbol": "?ClearResourceSlot@AnimationManager_004477d0@@QAEXH@Z",
  "address": "0x004477D0",
  "size": 55,
  "kind": "semantic",
  "owner": "0x004477D0",
  "previous_record": {
    "name": "asm_AnimationManager_ClearResourceSlot_004477d0",
    "source": "src/render/animation_manager_clear_resource_slot_004477d0.cpp",
    "symbol": "_asm_AnimationManager_ClearResourceSlot_004477d0",
    "address": "0x004477D0",
    "size": 55,
    "kind": "asm",
    "owner": "0x004477D0"
  }
}
```

Both source files keep their manifest `source` strings, so `translation_units` is untouched; both
are listed in the layout's `additional_sources`, so neither is compiled as its own unit
(`build_msvc.py` subtracts cluster additional sources).

## Pitfalls this cost a build each

* `0x00447810` frees through **0x00452422**, not through the five-byte jump at 0x004524A1 the
  caller uses. Binding `_entry_free_00452422` for the model and `_entry_free_004524a1` for the
  caller is required; using one for both shifts every `free` displacement by `0x7F`.
* The `/ENTRY` symbol must be the decorated name the driver actually emits; adding a parameter
  changes the mangling (`…PAPAUAnimationResource_00447810@@PAUAnimationManager_004477d0@@HH@Z`),
  and a stale spelling surfaces as `native cluster image base or entry address differs` (the
  entry collapses to 0), not as a missing symbol.
* Sections are laid out in `$`-suffix order, so the caller at the *lower* address needs a section
  name that sorts before `.text$10release` (`.text$08clear`), with a `.text$09layout` gap for the
  9 bytes between `0x00447807` and `0x00447810`.
* Every gap must be recomputed from the emitted extents: with the 256-byte first shape the
  following gap was short and the mark helper landed at `0x004493F0`, i.e. the layout failure
  appears at a region two functions away.
* The caller's TU needs `Release` declared on the record type (`struct X { void Release(); };` or
  the full type); a bare `struct AnimationResource_00447810;` forward declaration is
  `error C2027: use of undefined type` at the call.
* Adding the caller did **not** disturb the three existing functions: `0x00405ED0` (45),
  `0x00447810` (242) and `0x004493E0` (92) all measure 0 differing bytes in the four-function link.

## Reproduction

`/tmp/ReleaseDispatch/{sweep.py,sweep_caller.py,final/,final_source.cpp,caller_final.cpp,driver_caller.cpp}`
hold the harnesses, the artifacts and the driver scripts; `sweep_caller.py`'s `run()` builds the
four-function cluster adaptively and prints the per-region differing-byte counts. The maintained
tree was not modified by this note.
