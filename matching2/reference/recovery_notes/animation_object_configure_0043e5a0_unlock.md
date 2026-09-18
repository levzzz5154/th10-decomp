# 0x0043E5A0 `AnimationObject_ConfigureFromResource` — EXACT and landed

2026-09-19. Region `0x0043E5A0` (356 bytes, previously
`asm_AnimationObject_ConfigureFromResource_0043e5a0`) is recovered as ordinary C++
(`AnimationObject_0043e5a0::ConfigureFromResource`) and probes **EXACT (356/356, 0 differing
bytes)**. It is registered in the maintained manifest as
`semantic_AnimationObject_0043e5a0_ConfigureFromResource_0043e5a0`, `kind: semantic`, with the
payload held by the new native-LTCG cluster
`layout/ltcg/anm_object_configure_0043e5a0.json`. This unblocks the `0x00401440`
`CreateGameThread` chain, whose measured dependency was that `0x00401110`
`LoadGameThreadResources` calls this body with the object in **EAX**, the resource in **ECX** and
the index in **EDX** — the emitted body now uses exactly that convention (see §2).

## 1. What the region is

One archive/resource record is applied to an animation object: two guard reads, four scalar
stores, two 4x4 identity matrices written in place, two of their diagonal entries rescaled, a
third matrix read out of the record, and the first matrix mirrored 0x40 bytes into a second one.
The region has **no calls** and never touches the frame pointer, so nothing but statement order
and the whole-program register choice was ever at stake.

```
0043E5A0  56              push  esi
0043E5A1  8b f1           mov   esi,ecx                 ; resource (ECX) -> ESI
0043E5A3  57              push  edi
0043E5A4  8b be 08 01 00 00  mov edi,[esi+0x108]
0043E5AA  33 c9           xor   ecx,ecx                 ; zero register for both guards and the clears
0043E5AC  3b f9           cmp   edi,ecx
0043E5AE  0f 84 4a 01 00 00  je 0043E6FE                ; +0x108 == 0  -> -1
0043E5B4  39 8e 24 01 00 00  cmp   [esi+0x124],ecx
0043E5BA  0f 85 3e 01 00 00  jne 0043E6FE                ; +0x124 != 0 -> -1
0043E5C0  66 89 90 84 03 00 00  mov [eax+0x384],dx      ; record_index = (short)index
0043E5C7  6b d2 44        imul  edx,edx,0x44
0043E5CA  89 b0 08 03 00 00  mov [eax+0x308],esi      ; resource
0043E5D0  8b b6 18 01 00 00  mov esi,[esi+0x118]
0043E5D6  03 d6           add   edx,esi
0043E5D8  89 90 94 03 00 00  mov [eax+0x394],edx      ; record = records + index*0x44
0043E5DE  8b 52 34        mov   edx,[edx+0x34]
0043E5E1  89 50 4c        mov   [eax+0x4C],edx       ; width  = record[+0x34]
0043E5E4  8b 90 94 03 00 00  mov edx,[eax+0x394]      ; reloaded through the member
0043E5EA  8b 52 30        mov   edx,[edx+0x30]
0043E5ED  89 50 50        mov   [eax+0x50],edx       ; height = record[+0x30]
0043E5F0  89 88 74 02 00 00  mov [eax+0x274],ecx      ; 12 off-diagonal zeroes of matrix A,
..        ..              ..    descending                    +0x240..+0x274
0043E638  8d b0 3c 02 00 00  lea esi,[eax+0x23C]
0043E63E  ba 00 00 80 3f  mov edx,0x3F800000
0043E643  89 56 3c        mov   [esi+0x3C],edx       ; A[3][3] = 1.0
0043E646  89 56 28        mov   [esi+0x28],edx       ; A[2][2]
0043E649  89 56 14        mov   [esi+0x14],edx       ; A[1][1]
0043E64C  89 16           mov   [esi],edx            ; A[0][0]
0043E64E  ..              ..    matrix B identity, 12 zeroes + 4 diagonal, +0x2BC..+0x2F8
0043E6AE  8b 88 94 03 00 00  mov ecx,[eax+0x394]      ; record pointer, ECX is free again
0043E6B4  d9 40 4c        fld   [eax+0x4C]
0043E6B7  8d b8 7c 02 00 00  lea edi,[eax+0x27C]      ; mirror destination
0043E6BD  d8 0d 7c 0b 47 00  fmul  ds:0x00470B7C      ; 1/256
0043E6C3  d9 1e           fstp  [esi]                ; A[0][0] = width  * (1/256)
0043E6C5  d9 40 50        fld   [eax+0x50]
0043E6C8  d8 0d 7c 0b 47 00  fmul  ds:0x00470B7C
0043E6CE  d9 98 50 02 00 00  fstp [eax+0x250]         ; A[1][1] = height * (1/256)
0043E6D4  d9 41 38        fld   [ecx+0x38]
0043E6D7  d8 71 1c        fdiv  [ecx+0x1C]
0043E6DA  d8 48 4c        fmul  [eax+0x4C]
0043E6DD  d9 98 bc 02 00 00  fstp [eax+0x2BC]         ; B[0][0] = (r38/r1C)*width
0043E6E3  d9 41 3c        fld   [ecx+0x3C]
0043E6E6  d8 71 18        fdiv  [ecx+0x18]
0043E6E9  b9 10 00 00 00  mov   ecx,0x10
0043E6EE  f3 a5           rep movsd                  ; mirror = matrix A (0x40 bytes)
0043E6F0  5f              pop   edi
0043E6F1  5e              pop   esi
0043E6F2  d8 48 50        fmul  [eax+0x50]
0043E6F5  d9 98 d0 02 00 00  fstp [eax+0x2D0]         ; B[1][1] = (r3C/r18)*height
0043E6FB  33 c0           xor   eax,eax
0043E6FD  c3              ret
0043E6FE  5f              pop   edi
0043E6FF  83 c8 ff        or    eax,0FFFFFFFFh         ; -1
0043E702  5e              pop   esi
0043E703  c3              ret
```

The offsets the model writes: `+0x108` is the resource's loaded-entry pointer, `+0x124` a second
guard word, `+0x118` the record array (0x44-byte stride), record `+0x34`/`+0x30` the two
dimensions, record `+0x38`/`+0x1C` and `+0x3C`/`+0x18` the two aspect ratios. Object side:
`+0x4C`/`+0x50` the dumped dimensions, `+0x23C` matrix A, `+0x27C` its mirror, `+0x2BC` matrix B,
`+0x308` the resource, `+0x384` the record index, `+0x394` the record pointer.

## 2. Receiver registers (the wave's question)

Retail's two call sites inside `0x00401110` set **ECX = resource, EDX = index, EAX = object**
(`xor edx,edx / mov eax,esi / mov ecx,edi / call 0x0043E5A0`, and
`mov edx,0x62 / mov eax,esi / mov ecx,ebx / call 0x0043E5A0`), and the region's other asm call
sites (`src/game/score.cpp`, `src/game/player_front_runtime.cpp`,
`src/game/result_overlay.cpp`, `src/game/score_hud_update.cpp`) do the same.

The emitted body **keeps all three**: byte 0 is `56 8b f1` — `push esi; mov esi,ecx` — so ECX is
the resource at entry and stays in ESI for the whole body; the object is used as the store base
in EAX; the index reaches `imul edx,edx,0x44` and the `mov [eax+0x384],dx` store in EDX. The
result (0 / -1) lands in EAX and the function ends in a plain `ret`. The declared model is a
member of the *object*, but the whole-program pass put the object in EAX and the resource in ECX
on its own, which is exactly the convention the dependent callers use.

What could **not** be pinned and did not need to be: the same 356 bytes were *not* reachable by
declaration shape. Seven different declarations (`this` = object or = resource, parameter orders
swapped, free `__stdcall` with all three arguments) all emitted the identical body — the pass
re-decides the convention from the callee's own IR, and four very different synthetic callers
(including a register-pressure-heavy one and one that calls the function four times per
iteration) also emitted identical bytes.

## 3. Recovered source (`src/game/animation_object_configure_from_resource_0043e5a0.cpp`)

Replaces the naked body. The cluster compiles this whole file, so it holds no other function.

```cpp
// 0x0043E5A0 (356 bytes): configure one animation object from an archive
// resource record.

struct Resource_0043e5a0 {
    unsigned char reserved[0x200];
};

struct Matrix4x4_0043e5a0 {
    float values[4][4];

    __forceinline void SetIdentity();
};

struct AnimationObject_0043e5a0 {
    unsigned char reserved_0000[0x04C];
    float width;                                       // +0x04C
    float height;                                      // +0x050
    unsigned char reserved_054[0x23C - 0x054];
    Matrix4x4_0043e5a0 block_a;                        // +0x23C
    Matrix4x4_0043e5a0 block_copy;                     // +0x27C
    Matrix4x4_0043e5a0 block_b;                        // +0x2BC
    unsigned char reserved_2fc[0x308 - 0x2FC];
    Resource_0043e5a0* resource;                       // +0x308
    unsigned char reserved_30c[0x384 - 0x30C];
    unsigned short record_index;                       // +0x384
    unsigned char reserved_386[0x394 - 0x386];
    unsigned char* record;                             // +0x394

    __declspec(noinline) int ConfigureFromResource(Resource_0043e5a0* resource,
                                                   int index);
};

__forceinline void Matrix4x4_0043e5a0::SetIdentity() {
    values[3][2] = 0.0f;
    values[3][1] = 0.0f;
    values[3][0] = 0.0f;
    values[2][3] = 0.0f;
    values[2][1] = 0.0f;
    values[2][0] = 0.0f;
    values[1][3] = 0.0f;
    values[1][2] = 0.0f;
    values[1][0] = 0.0f;
    values[0][3] = 0.0f;
    values[0][2] = 0.0f;
    values[0][1] = 0.0f;
    values[3][3] = 1.0f;
    values[2][2] = 1.0f;
    values[1][1] = 1.0f;
    values[0][0] = 1.0f;
}

#pragma code_seg(".text$01configure")
__declspec(noinline) int AnimationObject_0043e5a0::ConfigureFromResource(
    Resource_0043e5a0* resource, int index) {
    unsigned char* res = reinterpret_cast<unsigned char*>(resource);
    if (*reinterpret_cast<void**>(res + 0x108) == 0 ||
        *reinterpret_cast<unsigned int*>(res + 0x124) != 0)
        return -1;

    this->record_index = static_cast<unsigned short>(index);
    this->resource = resource;
    this->record = *reinterpret_cast<unsigned char**>(res + 0x118) + index * 0x44;
    this->width = *reinterpret_cast<float*>(this->record + 0x34);
    this->height = *reinterpret_cast<float*>(this->record + 0x30);
    this->block_a.SetIdentity();
    this->block_b.SetIdentity();
    unsigned char* rec = this->record;
    this->block_a.values[0][0] = this->width * 0.00390625f;
    this->block_a.values[1][1] = this->height * 0.00390625f;
    this->block_b.values[0][0] =
        (*reinterpret_cast<float*>(rec + 0x38) /
         *reinterpret_cast<float*>(rec + 0x1C)) * this->width;
    this->block_b.values[1][1] =
        (*reinterpret_cast<float*>(rec + 0x3C) /
         *reinterpret_cast<float*>(rec + 0x18)) * this->height;
    this->block_copy = this->block_a;
    return 0;
}
#pragma code_seg()
```

Three shape facts carry the whole region; each was found by byte comparison, not by taste:

1. **The identity is a `float values[4][4]` written by a `__forceinline` member.** Written as
   flat statements inside `ConfigureFromResource` the same 16 stores and the scale expressions
   interleave under the x87 scheduler and the body comes out **357** bytes (one over) with the
   1.0-constant stores hoisted ahead of the zero stores and two of the four dead 1.0 stores
   deleted. The landed `0x00401F00` `Matrix4x4::SetIdentity` region is the same idiom already in
   the tree; giving the clear its own inline function reproduces retail's store schedule exactly.
2. **`rec = this->record` is read *before* the two `block_a` scale statements.** Retail loads the
   record pointer into ECX at `0043E6AE` — after the clears, before the first `fld`. With the
   local deferred until after the two scale statements the pointer comes out in EDX and the
   `fdiv`/`rep movsd`/`fmul` interleave differently (46 bytes still differ, same 356 extent).
3. **The mirror assignment is the last statement**, after `block_b.values[1][1]`. It is
   independent of matrix B, and this is the order that leaves `rep movsd` where retail has it.

The 1/256 factor is written as the **literal** `0.00390625f`; MSVC pools it as `__real@3b800000`
and the layout's `constant_aliases` binds that pooled symbol absolutely at the retail address
`0x00470B7C`, so the two `fmul` operands are `ds:0x470B7C` as in retail (`fmul ds:…`, not a
register). `__fltused` is bound as `metadata`, as float models require.

## 4. Driver (`layout/ltcg/anm_object_configure_0043e5a0_context.cpp`)

```cpp
// Compiler context only; never selected as recovered game code.
#include "../../src/game/animation_object_configure_from_resource_0043e5a0.cpp"

#pragma code_seg(".text$03context")
int __stdcall AnimationObjectConfigureCompilerContext(
    AnimationObject_0043e5a0** objects, int count,
    Resource_0043e5a0* resource) {
    int result = 0;
    for (int slot = 0; slot < count; ++slot)
        result += objects[slot]->ConfigureFromResource(resource, slot);
    return result;
}
#pragma code_seg()
```

The synthetic caller walks the object array, keeps the resource live across the loop and passes a
varying index; it is *not* what establishes the convention (see §2), but it keeps the function
reachable and non-inlinable in the way the other clusters do.

## 5. Layout (`layout/ltcg/anm_object_configure_0043e5a0.json`)

```json
{
  "schema_version": 1,
  "name": "anm_object_configure_0043e5a0",
  "source": "src/game/animation_object_configure_from_resource_0043e5a0.cpp",
  "driver": "layout/ltcg/anm_object_configure_0043e5a0_context.cpp",
  "headers": [],
  "image_base": "0x00400000",
  "description": "Animation-object resource configuration compiled with native LTCG so the object arrives in EAX, the resource in ECX and the index in EDX.",
  "functions": [
    {
      "name": "AnimationObject_0043e5a0_ConfigureFromResource",
      "symbol": "?ConfigureFromResource@AnimationObject_0043e5a0@@QAEHPAUResource_0043e5a0@@H@Z",
      "section": ".text$01configure",
      "address": "0x0043E5A0",
      "size": 356,
      "actual_abi": "resource in ECX (copied to ESI at entry), object in EAX, index in EDX; result in EAX; plain RET"
    }
  ],
  "context": {
    "symbol": "?AnimationObjectConfigureCompilerContext@@YGHPAPAUAnimationObject_0043e5a0@@HPAUResource_0043e5a0@@@Z",
    "section": ".text$03context",
    "address": "0x0043E720",
    "size": 52,
    "description": "Synthetic array-walking caller that establishes the observed register convention; not recovered game code."
  },
  "gaps": [
    { "section": ".text$00layout", "address": "0x00401000", "size": 251296 },
    { "section": ".text$02layout", "address": "0x0043E704", "size": 16 }
  ],
  "constants": [],
  "roots": [],
  "absolute_symbols": [
    { "symbol": "__fltused", "address": "0x00000000", "kind": "metadata" }
  ],
  "constant_aliases": [
    { "symbol": "__real@3b800000", "address": "0x00470B7C", "value": 0.00390625 }
  ]
}
```

The `context.size` is the *section contribution* the linker reports (52), not the extracted
symbol extent (48): the validator compares the contribution, and declaring 48 fails with
`function is not its entire declared compiler contribution`. Gap 1 is the minimum 16 bytes
between the function (ends `0x0043E704`) and the 16-aligned context.

## 6. Probe line and result

```
$ python3 matching2/tools/matching/probe.py \
    --source src/game/animation_object_configure_from_resource_0043e5a0.cpp \
    --output /tmp/AnmObjectConfig/final_probe --show 30
0x0043e5a0     356 bytes  ?ConfigureFromResource@AnimationObject_0043e5a0@@QAEHPAUResource_0043e5a0@@H@Z  EXACT
EXACT
```

The 356 bytes read out of the cluster's linked image at `0x0043E5A0` compare equal to the retail
bytes byte for byte. A control probe of an unrelated landed cluster
(`src/game/player_adjustpower_00405b60.cpp`) still reports `EXACT` after the registration, and the
manifest still binds `_asm_AnimationObject_ConfigureFromResource_0043e5a0 -> 0x0043E5A0`, so the
existing naked call sites in `load_game_thread_resources_00401110.cpp`, `score.cpp`,
`player_front_runtime.cpp`, `result_overlay.cpp` and `score_hud_update.cpp` keep resolving to the
same address and need no edit.

## 7. Landing state and what is still unmeasured

Landed in the maintained tree:

* `src/game/animation_object_configure_from_resource_0043e5a0.cpp` — the naked body replaced by
  the model above.
* `layout/ltcg/anm_object_configure_0043e5a0_context.cpp` — new driver.
* `layout/ltcg/anm_object_configure_0043e5a0.json` — new layout.
* `regions.json` — `0x0043E5A0` is now `kind: semantic` with the `?ConfigureFromResource@…`
  symbol; the old asm record is kept in `previous_record`. Registered through
  `register_cluster.py --apply`, not by hand (248 clusters).

**Measured:** the region probes EXACT; the emitted body keeps retail's EAX/ECX/EDX argument
registers; the pre-existing manifest binding for the old asm symbol is intact so no caller breaks.

**Not measured (needs the wave's integration build):** whether `0x00401440` `CreateGameThread`
now lands. Its chain still needs `0x00401110`'s body and `0x00401DE0`'s body co-compiled — this
region was one of the three, and always the least risky (no calls, no callee dependency). The
one thing this region contributes to that chain is now certain: the convention the callers use
(§2) is the convention the emitted body has.

Nothing from the scratch copy `/tmp/AnmObjectConfig` was promoted beyond the four files above;
no other region, tool or source in the maintained tree was touched.

## 8. Why the merged-link variant of this cluster is not used

`LoadGameThreadRes` measured (`load_game_thread_resources_00401110_unlock.md`) that adding this
source to its merged `0x00401110` link, with the code section renamed to `.text$06configure`,
takes `0x00401110` from 326 to 329 bytes of retail's 330 — still one byte short — and that the
two call sites then snap to retail's `xor %edx,%edx / mov %esi,%eax / mov %edi,%ecx / call`.
That variant cannot be registered while this standalone cluster exists, for three independent
reasons, so it must not be landed by simply adding a layout:

* `load_clusters` requires **distinct maintained sources** across clusters
  (`ltcg_cluster.py:349`), and this cluster now owns
  `src/game/animation_object_configure_from_resource_0043e5a0.cpp`;
* `register_cluster.py --apply` refuses a layout whose function's **region source differs** from
  the layout's own `source`, so `0x0043E5A0` cannot be re-registered from another layout at all —
  it needs `promote_clusters.py`'s path;
* this layout declares the function's section as `.text$01configure`, so renaming the pragma in
  the maintained source would also fail this cluster's contribution check.

Main's decision (2026-09-19): **keep this cluster standalone**. The merge would buy 3 bytes on a
region that is still not exact, at the cost of a pragma rename, a record re-homing and a layout
replacement on an already-sound cluster, so `0x00401110` waits on `0x00401DE0` instead.

