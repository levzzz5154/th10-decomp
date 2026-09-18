# `0x00418D40` recovered EXACT — wave 8

Date: 2026-09-19. `StageTipManager_Construct` (237 bytes) is **recovered as C++**:
in the co-compiled native-LTCG cluster it emits **237 bytes with 0 differing
bytes**, and in the same link **`0x00418E30` is 131/131 and `0x00419090` is
67/67** — the factory keeps its single-instruction home register, so the
wave-7 "waits on the construct" condition is satisfied and all three regions
land together.

Measured on the cluster's own image (the same bytes `probe.py` compares):

```
0x00418D40  237 bytes  differing=0 EXACT
0x00418E30  131 bytes  differing=0 EXACT
0x00419090   67 bytes  differing=0 EXACT
```

## What the residual was

Wave 7 left the region at 237/237 bytes with 69 differing bytes in the store
schedule: retail stores, per record, `owner, +04, +08`, and hoists the owner
pairs of records 0/1 and 8/9, while the model emitted every record as
`+08, +04, owner`. Two scheduler facts describe the whole residual:

1. **A record's owner store is deferred to the end of its inlined body.** A
   three-store helper (`owner, +08, +04`) emits `+08, +04, owner` per record —
   the owner store is scheduled after its record's two zero stores. Nine source
   orderings and a byte-pointer helper do not change it: the group boundary, not
   the statement order, decides.
2. **Owner stores written as plain statements are grouped in front of all the
   zero stores** (143 bytes off), because the pass reorders the whole block by
   stored value.

The fix is to give every owner its own inlined body so the pass keeps emitting
them in source order, and to let the two hoisted pairs share one body:

```cpp
static void SetOwnerPair_00418d40(...) { record[0].owner = owner; record[1].owner = owner; }
```

With `SetOwnerPair` for records 0/1 and 8/9 (each pair emitted owners first) and
`SetOwner`/`ClearRecord` for the rest, the emitted stream *is* the source order
and retail's schedule is reproduced exactly, including the `orl $0x2,(%edx)`
fold of the flag update and the position of the zero materialisation between the
two owner stores and the first zero store — no `volatile`, no asm barrier, no
pragma. The earlier 237-byte barrier variants (asm labels after the flag update)
folded the flag update but always emitted `push edi; xor eax,eax` instead of
retail's `xor eax,eax; push edi`, a 3-byte prologue difference; that device is
**not** needed and is not used.

## Source: `src/game/stage_tip_manager.cpp`

```cpp
// 0x00418D40..0x00418E2C (237 bytes): StageTipManager_Construct
//
// Zeroes the 0x1A8-byte stage-tip manager, raises its +0x00 flag, points each
// of its sixteen 12-byte records back at the manager, and publishes the
// finished manager through data_00477814.
//
// Retail receives the manager in EDX - a register no MSVC convention assigns -
// and the dead leading slot the fastcall declaration introduces is dropped by
// the whole-program pass, so this source is compiled inside the same native-LTCG
// link as the two functions that consume its result (see
// layout/ltcg/bullet_manager_load_scripts_0040ae70.json).
//
// The record stores are the part that took several waves.  A record's three
// stores must be split so that the owner store lands in its own inlined body:
// with a single three-store helper the pass schedules a record's owner store
// *after* that record's two zero stores (69 bytes from retail's schedule), and
// with the owners written as plain statements the pass groups all thirty-two
// zero stores in front of all sixteen owners (143 bytes).  Kept apart this way
// the pass emits the stores in exactly the source order, so the sixteen owners
// and zero pairs below are written in retail's order - including the two owner
// pairs retail hoists (records 0/1 and 8/9), which share one inlined body so the
// pair is emitted owner,owner before the pair's four zero stores.
#include <string.h>

struct StageTipRecord_00418d40 {
    void* owner;
    unsigned int unknown_04;
    unsigned int unknown_08;
};

struct StageTipManager_00418d40 {
    unsigned int flags;
    unsigned char pad_004[0x18 - 0x04];
    StageTipRecord_00418d40 records[16];
    unsigned char pad_0D8[0x1A8 - 0xD8];
};

extern "C" StageTipManager_00418d40* data_00477814;

static void SetOwner_00418d40(StageTipRecord_00418d40* record,
                             StageTipManager_00418d40* owner) {
    record->owner = owner;
}

static void SetOwnerPair_00418d40(StageTipRecord_00418d40* record,
                                 StageTipManager_00418d40* owner) {
    record[0].owner = owner;
    record[1].owner = owner;
}

static void ClearRecord_00418d40(StageTipRecord_00418d40* record) {
    record->unknown_04 = 0;
    record->unknown_08 = 0;
}

extern "C" __declspec(noinline) StageTipManager_00418d40* __fastcall
Construct_00418d40(int unused, StageTipManager_00418d40* manager);
#pragma code_seg(".text$00d_cxctor")
extern "C" __declspec(noinline) StageTipManager_00418d40* __fastcall
Construct_00418d40(int unused, StageTipManager_00418d40* manager) {
    memset(manager, 0, sizeof(StageTipManager_00418d40));
    manager->flags |= 2;
    SetOwnerPair_00418d40(&manager->records[0], manager);
    ClearRecord_00418d40(&manager->records[0]);
    ClearRecord_00418d40(&manager->records[1]);
    SetOwner_00418d40(&manager->records[2], manager);
    ClearRecord_00418d40(&manager->records[2]);
    SetOwner_00418d40(&manager->records[3], manager);
    ClearRecord_00418d40(&manager->records[3]);
    SetOwner_00418d40(&manager->records[4], manager);
    ClearRecord_00418d40(&manager->records[4]);
    SetOwner_00418d40(&manager->records[5], manager);
    ClearRecord_00418d40(&manager->records[5]);
    SetOwner_00418d40(&manager->records[6], manager);
    ClearRecord_00418d40(&manager->records[6]);
    SetOwner_00418d40(&manager->records[7], manager);
    ClearRecord_00418d40(&manager->records[7]);
    SetOwnerPair_00418d40(&manager->records[8], manager);
    ClearRecord_00418d40(&manager->records[8]);
    ClearRecord_00418d40(&manager->records[9]);
    SetOwner_00418d40(&manager->records[10], manager);
    ClearRecord_00418d40(&manager->records[10]);
    SetOwner_00418d40(&manager->records[11], manager);
    ClearRecord_00418d40(&manager->records[11]);
    SetOwner_00418d40(&manager->records[12], manager);
    ClearRecord_00418d40(&manager->records[12]);
    SetOwner_00418d40(&manager->records[13], manager);
    ClearRecord_00418d40(&manager->records[13]);
    SetOwner_00418d40(&manager->records[14], manager);
    ClearRecord_00418d40(&manager->records[14]);
    SetOwner_00418d40(&manager->records[15], manager);
    ClearRecord_00418d40(&manager->records[15]);
    data_00477814 = manager;
    return manager;
}
#pragma code_seg()
```

`src/game/recovery_create_resource_state_00419090.cpp` becomes the C factory
(the wave-7 package, unchanged in shape):

```cpp
struct StageTipManager_00419090 { unsigned char bytes[0x1A8]; };
void* __cdecl operator new(unsigned int size);
extern "C" void __cdecl entry_free_004524a1(void* block);
extern "C" void* __fastcall Construct_00418d40(int unused, StageTipManager_00419090* manager);
extern "C" int __stdcall asm_StageTipRuntime_InitializeRetail_00418e30(StageTipManager_00419090* manager);
extern "C" int __stdcall asm_FUN_00418ee0_00418ee0(void* manager);

extern "C" __declspec(noinline) StageTipManager_00419090* __cdecl
asm_Recovery_CreateResourceState_00419090();
#pragma code_seg(".text$00d_fcreate")
extern "C" __declspec(noinline) StageTipManager_00419090* __cdecl
asm_Recovery_CreateResourceState_00419090() {
    StageTipManager_00419090* block = new StageTipManager_00419090;
    StageTipManager_00419090* manager;
    if (block)
        manager = (StageTipManager_00419090*)Construct_00418d40(0, block);
    else
        manager = 0;
    if (asm_StageTipRuntime_InitializeRetail_00418e30(manager)) {
        if (manager) {
            asm_FUN_00418ee0_00418ee0(manager);
            entry_free_004524a1(manager);
        }
        return 0;
    }
    return manager;
}
#pragma code_seg()
```

## Layout delta — `layout/ltcg/bullet_manager_load_scripts_0040ae70.json`

```json
  "additional_sources": [ … , "src/game/stage_tip_manager.cpp",
                              "src/game/recovery_create_resource_state_00419090.cpp" ],
  "functions": [ … ,
    { "name": "Construct_00418d40", "symbol": "@Construct_00418d40@8",
      "section": ".text$00d_cxctor", "address": "0x00418D40", "size": 237,
      "actual_abi": "block in EDX; dead ECX slot; result in EAX; plain RET",
      "source": "src/game/stage_tip_manager.cpp" },
    { "name": "Recovery_CreateResourceState_00419090",
      "symbol": "_asm_Recovery_CreateResourceState_00419090",
      "section": ".text$00d_fcreate", "address": "0x00419090", "size": 67,
      "actual_abi": "no arguments; manager in EAX; plain RET",
      "source": "src/game/recovery_create_resource_state_00419090.cpp" } ],
  "gaps": [ …,
    { "section": ".text$00d_agap",  "address": "0x0040AFE6", "size": … },   // to the construct
    { "section": ".text$00d_cgap",  "address": "0x0040D3CE", "size": … },
    { "section": ".text$00d_cygap", "address": "0x00418E2D", "size": 3 },
    { "section": ".text$00d_egap",  "address": "0x00418EB3", "size": 477 },
    { "section": ".text$00d_ggap",  "address": "0x004190D3", "size": 7357 } ],
  "absolute_symbols": [ …,
    { "symbol": "_data_00491d6a", "address": "0x00491D6A", "kind": "data" },
    { "symbol": "_asm_FUN_00419960_00419960@12", "address": "0x00419960", "kind": "relative_code" },
    { "symbol": "_asm_FUN_00418ee0_00418ee0@4", "address": "0x00418EE0", "kind": "relative_code" },
    { "symbol": "_data_00477814", "address": "0x00477814", "kind": "data" } ]
```

The gaps are rebuilt as the **complement of the span's functions**, not from a
fixed list, so a function another agent added in the same span (the message-host
region at `0x0040D280` today) keeps its place and its own gap; section names are
ordered so the linker's name order equals the address order. The construct's
section is `.text$00d_cxctor`, not `.text$00d_bctor`: `.text$00d_bmsghost` now
sorts between the first gap and the construct, and a `.text$00d_bctor` section
would be placed before it.

## Driver delta — `layout/ltcg/bullet_manager_load_scripts_0040ae70_context.cpp`

The shared driver gains one declaration and one loop, which is what roots the
factory (and, through it, the construct) in the `LTCG` link:

```cpp
extern "C" void *__cdecl asm_Recovery_CreateResourceState_00419090();
…
    for (int index = 0; index < count; ++index) {
        if (asm_Recovery_CreateResourceState_00419090())
            ++created;
    }
```

The context grows to the size the linker reports (214 bytes with the span as it
stands) and its address is unchanged; the layout's `context.size` must be the
emitted one.

## Verification

Built with the project's own cluster path (`build_cluster` on
`layout/ltcg/bullet_manager_load_scripts_0040ae70.json`, MSVC 13.10.6030,
`/O2 /Gz /MT /Gy /G6 /GF /GS /Zl`), then every declared region compared against
the retail image:

```
0x00418D40  237 declared / 237 retail  differing_bytes=0  EXACT
0x00418E30  131 declared / 131 retail  differing_bytes=0  EXACT
0x00419090   67 declared /  67 retail  differing_bytes=0  EXACT
```

The construct's emitted stream is retail's, byte for byte: `xor eax,eax`,
`push edi`, `mov $0x6a,%ecx`, `mov %edx,%edi`, `rep stosd`, `orl $0x2,(%edx)`,
then `owner,owner` pairs and `+04,+08` pairs in retail's order, the zero
materialisation in front of the first zero store, `mov %edx,0x477814`,
`mov %edx,%eax`, `pop edi`, `ret`.

## Landing state — not applied

The landing is **staged but not promoted**, because the shared cluster cannot
link as the tree stands: `src/game/message_host_init.cpp` (a sibling's in-flight
region `0x0040D280`) defines `asm_FUN_0040d280_0040d280` with a `ret 4` body,
while the maintained layout, the maintained driver and the maintained
`regions.json` record all name `_asm_MessageHost_InitRetail_0040d280@8`
(`LNK2001: unresolved external symbol _asm_MessageHost_InitRetail_0040d280@8`),
and the source also needs `include/asm_encoding.hpp` and
`include/asm_symbols.hpp` declared in the layout's `headers`. The verification
above therefore ran with that source and its function removed from the layout
(the span's gap rebuild absorbs the space; the measured sizes are unaffected).
`0x00418D40` and `0x00419090` become exact on the maintained tree as soon as
that sibling landing is consistent.

Landing steps for whoever applies it (multi-source merge into a registered
cluster, so `promote_scratch.py`, or an `apply_package.py` payload):

1. Copy `src/game/stage_tip_manager.cpp` and
   `src/game/recovery_create_resource_state_00419090.cpp` from
   `/tmp/StageTipConstruct/msvc`.
2. Apply the layout delta above to the *current* maintained layout (rebuild the
   span gaps as the complement of its functions) and the driver delta; update
   `context.size` to the emitted size.
3. Rewrite the `0x00418D40` record to
   `{name: semantic_Construct_00418d40_00418d40, symbol: @Construct_00418d40@8,
   size: 237, kind: semantic}` with its asm record kept as `previous_record`, and
   the `0x00419090` record to
   `{name: semantic_Recovery_CreateResourceState_00419090_00419090,
   symbol: _asm_Recovery_CreateResourceState_00419090, size: 67, kind: semantic}`
   likewise; recompute `translation_units`.
4. `probe.py --source src/game/stage_tip_manager.cpp --project matching2/msvc`
   must report `EXACT` for `0x00418D40`, `0x00418E30` and `0x00419090`.
