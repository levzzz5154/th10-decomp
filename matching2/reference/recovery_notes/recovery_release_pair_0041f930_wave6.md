# 0x0041F930 — `Recovery_ReleasePair`: **EXACT 91/91**, merged into the resource-release cluster

2026-09-19, wave 6. Region `0x0041F930..0x0041F98A` (91 bytes,
`asm_Recovery_ReleasePair_0041f930`) is recovered as readable C++ and is
**byte-identical to retail, 0 differing bytes** (emitted sha256
`f33521e5aaca3bf80049179d9ccfbf34be8a80119780cac027a8ddb915b03b25` = retail's).
It is the **fifth function of the already-registered native-LTCG cluster**
`layout/ltcg/animation_manager_mark_resource_for_removal_004493e0.json` — the
merge pattern of `ltcg_cluster_lessons.md` rule 5 — and it lands with the
cluster's four existing regions unchanged.

```
$ python3 matching2/tools/matching/probe.py --source src/game/recovery_release_pair_0041f930.cpp \
      --project matching2/msvc --output /tmp/ReleasePair/out_maint --show 30
0x00405ed0      45 bytes  ?Reset@BulletPool@@QAEXXZ  EXACT
0x0041f930      91 bytes  _ReleasePair_0041f930  EXACT
0x004477d0      55 bytes  ?ClearResourceSlot@AnimationManager_004477d0@@QAEXH@Z  EXACT
0x00447810     242 bytes  ?Release@AnimationResource_00447810@@QAEXXZ  EXACT
0x004493e0      92 bytes  ?MarkResourceForRemoval@AnimationManager@@QAEXPAX@Z  EXACT
EXACT
```

The same five-region result is measured in the scratch copy
(`--project /tmp/ReleasePair/msvc`); `0x00405ED0`, `0x004477D0`, `0x00447810` and
`0x004493E0` all measure 0 differing bytes before and after the merge.

## Retail

```
41f930  56              push  esi
41f931  8b 35 10 1c 49 00  mov  esi,ds:0x491C10        ; animation-manager singleton
41f937  81 c6 84 d0 3a 00  add  esi,0x3AD084           ; &slots_3ad06c[6]
41f93d  57              push  edi
41f93e  8b 3e           mov  edi,[esi]                ; *slot
41f940  85 ff           test edi,edi
41f942  74 16           je   41f95a
41f944  e8 c7 7e 02 00  call 0x00447810              ; AnimationResource::Release(EDI)
41f949  8b 06           mov  eax,[esi]
41f94b  50              push eax
41f94c  e8 50 2b 03 00  call 0x004524A1              ; free(*slot)
41f951  83 c4 04        add  esp,4
41f954  c7 06 00 00 00 00  mov [esi],0              ; *slot = 0
41f95a  8b 35 10 1c 49 00  mov  esi,ds:0x491C10     ; singleton re-read
41f960  8b be 88 d0 3a 00  mov  edi,[esi+0x3AD088]  ; slots_3ad06c[7]
41f966  81 c6 88 d0 3a 00  add  esi,0x3AD088
41f96c  85 ff           test edi,edi
41f96e  74 16           je   41f986
41f970  e8 9b 7e 02 00  call 0x00447810
41f975  8b 0e           mov  ecx,[esi]
41f977  51              push ecx
41f978  e8 24 2b 03 00  call 0x004524A1
41f97d  83 c4 04        add  esp,4
41f980  c7 06 00 00 00 00  mov [esi],0
41f986  5f              pop  edi
41f987  33 c0           xor  eax,eax
41f989  5e              pop  esi
41f98a  c3              ret
```

Emitted bytes (identical to retail):

```
568b35101c490081c684d03a00578b3e85ff7416e8c77e02008b0650e8502b03
0083c404c706000000008b35101c49008bbe88d03a0081c688d03a0085ff7416
e89b7e02008b0e51e8242b030083c404c706000000005f33c05ec3
```

Two slot releases, each guarded, each releasing the record through the release
routine at `0x00447810` and then freeing the allocation through the CRT entry at
`0x004524A1`, clearing the slot. The region returns **0** (`xor eax,eax`). The
two fixed displacements are **indices 6 and 7 of the manager's 0x21-entry
resource-slot array at `+0x3AD06C`** — the same array
`AnimationManager_ClearResourceSlot` (`0x004477D0`) indexes with a variable,
bounds-checked index, and the same array the *inlined single-slot* copies of this
very statement address at constant offsets all over the image:

| inlined copy | slot displacement | index |
| --- | --- | --- |
| `0x00401369` | `+0x3AD06C` | 0 |
| `0x00401395` | `+0x3AD078` | 3 |
| `0x0042C800` | `+0x3AD070` | 1 |
| `0x00405F40` (unassigned fragment) | `+0x3AD088` | 7 |
| `0x00413B90` (unassigned fragment) | `+0x3AD084` | 6 |
| `0x00424F90` | `+0x3AD08C` | 8 |
| `0x0040B858`, `0x0040B87F`, … | `+0x3AD0E0`, `+0x3AD0E4` | 0x1D, 0x1E |
| `0x00414389` | `+0x3AD0DC` | 0x1C |
| `0x0042BD40`, `0x0042BD72` | `+0x3AD088`, `+0x3AD084` | 7 then 6 |

`0x0041F930` is the out-of-line two-slot version of that statement, and
`0x00405F40` / `0x00413B90` are its exactly-one-slot siblings. Every one of them
reaches `0x00447810` with the record in EDI and frees through `0x004524A1`.

## Recovered source (`src/game/recovery_release_pair_0041f930.cpp`, replaces the naked body)

```cpp
// 0x0041F930..0x0041F98A: release two slots of the animation manager's
// resource array, freeing each allocation and clearing the slot.
//
// Retail calls the release routine at 0x00447810 with the record in EDI - a
// native /LTCG register choice, not a declared convention - and frees through
// the CRT entry at 0x004524A1.  The region therefore joins the whole-program
// link that already carries the recovered release body,
// layout/ltcg/animation_manager_mark_resource_for_removal_004493e0.json.
//
// The two slots are indices 6 and 7 of the 0x21-entry resource-slot array at
// +0x3AD06C that AnimationManager_ClearResourceSlot indexes.  Retail holds the
// addressed slot in ESI across each block's calls and re-loads the singleton
// between the two blocks; holding only the record would cost a third
// callee-saved register and re-read the global after every call.

struct AnimationResource_00447810 {
    __declspec(noinline) void Release();
};

struct AnimationManager_0041f930 {
    unsigned char pad_000[0x3AD06C];
    AnimationResource_00447810* slots_3ad06c[0x21];
};

extern "C" AnimationManager_0041f930* data_00491c10;
extern "C" void __cdecl entry_free_004524a1(void* memory);

#pragma code_seg(".text$03pair")
extern "C" __declspec(noinline) int __cdecl ReleasePair_0041f930() {
    AnimationResource_00447810** slot = &data_00491c10->slots_3ad06c[6];
    if (*slot != 0) {
        (*slot)->Release();
        entry_free_004524a1(*slot);
        *slot = 0;
    }
    slot = &data_00491c10->slots_3ad06c[7];
    if (*slot != 0) {
        (*slot)->Release();
        entry_free_004524a1(*slot);
        *slot = 0;
    }
    return 0;
}
#pragma code_seg()
```

`AnimationResource_00447810` is deliberately the **same class name** the
cluster's release body is defined on (`src/render/fun_00447810_00447810.cpp`):
the linker resolves `?Release@AnimationResource_00447810@@QAEXXZ`, so a
differently named local type is `LNK2001: unresolved external symbol`.

## Driver (`layout/ltcg/animation_manager_mark_resource_for_removal_004493e0_context.cpp`)

Unchanged apart from the declaration and the one call (`+3` lines); the
context's emitted extent grows **101 → 106 bytes**, which the layout carries:

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

extern "C" __declspec(noinline) int __cdecl ReleasePair_0041f930();

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
    index += ReleasePair_0041f930();
    return index;
}
#pragma code_seg()
```

The calling shape the context adds is the only thing this region needed: the
caller takes `ReleasePair`'s **0** back into a live local, so the body must
return in EAX as retail does. `ReleasePair` is itself `__declspec(noinline)` —
without it the whole-program pass folds the region into the context, no symbol
appears, and the layout reports an unresolved function.

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
    { "name": "BulletPool_Reset_00405ed0", "symbol": "?Reset@BulletPool@@QAEXXZ",
      "section": ".text$01reset", "address": "0x00405ED0", "size": 45,
      "actual_abi": "pool in ESI; plain RET",
      "source": "src/game/bullet_pool_reset_retail_00405ed0.cpp" },
    { "name": "Recovery_ReleasePair_0041f930", "symbol": "_ReleasePair_0041f930",
      "section": ".text$03pair", "address": "0x0041F930", "size": 91,
      "actual_abi": "no entry register; plain RET with EAX = 0",
      "source": "src/game/recovery_release_pair_0041f930.cpp" },
    { "name": "AnimationManager_ClearResourceSlot", "symbol": "?ClearResourceSlot@AnimationManager_004477d0@@QAEXH@Z",
      "section": ".text$08clear", "address": "0x004477D0", "size": 55,
      "actual_abi": "manager in EBX; index in ESI; record in EDI; plain RET",
      "source": "src/render/animation_manager_clear_resource_slot_004477d0.cpp" },
    { "name": "AnimationResource_Release", "symbol": "?Release@AnimationResource_00447810@@QAEXXZ",
      "section": ".text$10release", "address": "0x00447810", "size": 242,
      "actual_abi": "record in EDI; plain RET",
      "source": "src/render/fun_00447810_00447810.cpp" },
    { "name": "AnimationManager_MarkResourceForRemoval", "symbol": "?MarkResourceForRemoval@AnimationManager@@QAEXPAX@Z",
      "section": ".text$20helper", "address": "0x004493E0", "size": 92,
      "actual_abi": "animation manager in EAX; retired resource in EDX; plain RET" }
  ],
  "context": {
    "symbol": "?AnimationManagerHelperCompilerContext@@YGHPAPAUBulletPool@@PAPAUAnimationResource_00447810@@PAUAnimationManager_004477d0@@HH@Z",
    "section": ".text$30context",
    "address": "0x00449480",
    "size": 106,
    "description": "Synthetic array-walking caller; not recovered game code."
  },
  "gaps": [
    { "section": ".text$00layout", "address": "0x00401000", "size": 20176 },
    { "section": ".text$02layout", "address": "0x00405EFD", "size": 105011 },
    { "section": ".text$04layout", "address": "0x0041F98B", "size": 163397 },
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
    "src/render/animation_manager_clear_resource_slot_004477d0.cpp",
    "src/game/recovery_release_pair_0041f930.cpp"
  ]
}
```

`roots` stays empty (rooting would lock a public convention and pull the record
out of EDI); `absolute_symbols` is unchanged; the release body keeps freeing
through `0x00452422` while this region frees through the five-byte jump at
`0x004524A1`, so both bindings are needed.

## Landing

The layout is **already registered**, so `register_cluster.py` does not apply
(it refuses a merged layout: "region 0x405ed0 is owned by …"). The merge was
promoted with the documented tool:

```
python3 matching2/tools/waves/promote_scratch.py --scratch /tmp/ReleasePair/msvc \
        --address 0x41F930 --apply
region   0x0041f930  asm_Recovery_ReleasePair_0041f930 (asm)
scratch  semantic_Recovery_ReleasePair_0041f930 (semantic) size 91 symbol _ReleasePair_0041f930
layout   layout/ltcg/animation_manager_mark_resource_for_removal_004493e0.json (already registered - will be overwritten, merge)
copy     src/game/recovery_release_pair_0041f930.cpp
copy     layout/ltcg/animation_manager_mark_resource_for_removal_004493e0.json
copy     layout/ltcg/animation_manager_mark_resource_for_removal_004493e0_context.cpp
promoted 0x0041f930
```

Manifest diff: **exactly one region record** (13 insertions, 4 deletions), the
`asm` → `semantic` flip with `previous_record`:

```json
{
  "name": "semantic_Recovery_ReleasePair_0041f930",
  "source": "src/game/recovery_release_pair_0041f930.cpp",
  "symbol": "_ReleasePair_0041f930",
  "address": "0x0041F930",
  "size": 91,
  "kind": "semantic",
  "owner": "0x0041F930",
  "previous_record": {
    "name": "asm_Recovery_ReleasePair_0041f930",
    "source": "src/game/recovery_release_pair_0041f930.cpp",
    "symbol": "_asm_Recovery_ReleasePair_0041f930",
    "address": "0x0041F930",
    "size": 91,
    "kind": "asm",
    "owner": "0x0041F930"
  }
}
```

`translation_units` is untouched: `src/game/recovery_release_pair_0041f930.cpp`
was already a unit and is now also a cluster `additional_source`, which
`build_msvc` subtracts — the same arrangement the two sources landed yesterday
have. `symbols` still maps `_asm_Recovery_ReleasePair_0041f930` to `0x0041F930`,
so the naked caller in `src/game/fun_0041fb50_0041fb50.cpp:100` keeps
resolving; that unit still probes EXACT (417/417) after the merge.

The probe path was driven from a scratch copy and its manifest was edited there
by hand (region record only); the maintained manifest was touched **only** by
`promote_scratch.py --apply`, not by `register_cluster.py`. A sibling's
`git add -A` commit swept the four files into `3a479be1`; the region record and
the three files were re-verified after that commit against the maintained tree.

## Registers retail's callers use

`0x0041F930` has exactly **one** direct caller in the image, at `0x0041FBF2`
inside the game-thread worker `FUN_0041FB50` (`0x0041FB50`, 417 bytes):

```
41fbec  fe 0d 1c 23 49 00  dec  byte ptr ds:0x49231C     ; LeaveCriticalSection depth
41fbf2  e8 39 fd ff ff     call 0x0041F930
41fbf7  8b 1d 10 1c 49 00  mov  ebx,ds:0x491C10          ; caller reloads its cached singleton
```

At the call the worker has **EBX** (scheduler object, `0x00491BE4`), **EBP**
(LeaveCriticalSection), **ESI** (EnterCriticalSection) and **EDI** (the freeing
routine) all live; there are no arguments and no return value is consumed. The
emitted body keeps exactly the registers retail's does — it pushes ESI and EDI
and pops both, uses no other callee-saved register, takes no stack argument, and
returns `EAX = 0` (clobbering the volatile EAX the caller does not read). That is
byte equality, not similarity: 0 of 91 bytes differ.

## Shapes tried

| shape | emitted | first delta |
| --- | ---: | --- |
| **`slot = &g->slots_3ad06c[6]` / `[7]`, slot pointer held across each block's calls** | **91** | none — **EXACT** |
| named members `slot_3ad084` / `slot_3ad088` addressed the same way | 91 | none — also byte-exact |
| repeated member access `g->slot->Release(); free(g->slot); g->slot = 0;` (no pointer local) | 114 | `+0x00`: got `a1 10 1c 49 00` (`mov eax,ds:0x491C10`), want `56` (`push esi`) |
| member function `AnimationManager::ReleasePair` (same body) | not built — the free-function form was already exact |

The 114-byte shape is the informative failure: with no pointer local the
compiler must re-read the *global* after every opaque call, so each block emits
three `mov reg,ds:0x491C10` loads (one for the guard, one for the free argument,
one for the store) and the slot address is never materialised. Retail materialises
it once per block (`mov esi,ds:0x491C10` / `add esi,imm32`) and re-reads only the
slot; that is what holding `AnimationResource** slot` in the source reproduces.
The allocator then gives the second block `mov ecx,[esi]` where the first uses
`mov eax,[esi]`, and the epilogue interleaves `pop edi / xor eax,eax / pop esi`
— all three fall out of the same source with no shaping.

## Why this lands where the blocked sibling 0x00405620 does not

`0x00405620` (`ReleaseRawPairAndReset`) is the same *statement* shape with the
opposite wall, and the comparison is worth recording because the difference is
exactly the item the earlier note left open.

- **0x00405620** calls the scheduler removal at `0x00449F60` **opaquely**: the
  callee is an absolute `relative_code` binding with a declared convention, so
  the caller has to materialise the argument registers itself, and the two
  independent `mov ecx,esi` / `mov edx,edi` pairs came out in the opposite order
  from retail at both call sites despite caller visibility, source-level Win32
  imports, the exact callee body and the exact extents all being ruled out.
- **0x0041F930** calls `0x00447810`, whose **real recovered body is in the same
  /LTCG invocation**. The record receiver is then not a caller-side
  materialisation at all: the whole-program pass assigns the receiver EDI once,
  every caller just leaves the record there, and `call 0x00447810` is emitted with
  *no* preceding register move. Both of the sibling's unmatched moves simply do
  not exist in this region, and the region's only remaining shape question is the
  slot-address live range, which the pointer local settles.

So the actionable generalisation from that note is confirmed here: a receiver the
pass assigns (EDI, EAX) cannot be reached by any declaration, but it *can* be
reached by co-compiling the callee — and doing so removes the caller-side
materialisation that a bound external forces. The earlier note's conclusion ("a
next attempt should investigate an original class/member declaration or
front-end expression shape for the removal call") is where `0x00405620` still
stands: its callee `0x00449F60` (`Scheduler_Remove`, 114 bytes) is recovered and
exact, but `src/game/scheduler_tasks.cpp` is already an `additional_source` of
the registered `layout/ltcg/bullet_manager_load_scripts_0040ae70.json` cluster,
so `0x00405620` can only absorb it by joining *that* cluster — a merge that would
have to grow that layout rather than this one.

## Pitfalls this cost

- **The local class name is load-bearing.** `AnimationResource_0041f930` (my
  first draft) is `LNK2001: unresolved external symbol
  "public: void __thiscall AnimationResource_0041f930::Release(void)"`, because
  the co-compiled body defines `AnimationResource_00447810::Release`. The merge
  is at the symbol level, so the type must be spelled as the cluster defines it.
- **The function's section suffix must sort between the sections it is spliced
  into.** `.text$02layout` had to be split, and the new function needs a name
  after `.text$02layout` and before the split remainder: `.text$03pair`, then
  `.text$04layout` for the rest.
- **The gap after the function must leave the next *function* section on its
  16-byte alignment.** Gap arrays are alignment-1 contributions while
  `#pragma code_seg` bodies are 16-aligned; the tiling only works because
  `0x0041F930 + 91 + 163397 == 0x004477D0`. When the emitted size is wrong the
  linker pads 32 bytes before `.text$08clear` and every later address shifts —
  the failure then shows up as `ClearResourceSlot` two functions away, at
  `0x004477F0`, not at this region.
- **The map prints lowercase hex.** Reading section sizes back from
  `cluster.map` with `[0-9A-F]{8}` silently returns `None` for any length
  containing `a`-`f`, which is what makes the adaptive size retry loop forever on
  a bogus "address or origin differs" complaint. (A sibling fixed
  `cluster_attempt.py`'s parsers for this in `3a479be1`; the scratch harness here
  carried the same fix.)
- **A context change moves the context's declared size.** Adding one call grew
  the synthetic context from its declared 101 to 106 bytes; the layout must carry
  the emitted extent or `validate_native_output` rejects the contribution before
  any byte comparison.

## Reproduction

`/tmp/ReleasePair/{sweep.py,variants.py,verify.py,final_source.cpp}` hold the
harness: `variants.py <name>` writes the source, patches the scratch region
record, rebuilds the canonical layout with the emitted sizes read back from the
map and prints the per-region differing-byte count; `verify.py` prints all five
cluster regions against retail and the emitted/retail sha256.
