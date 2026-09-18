# 0x004451C0 entity draw dispatch - 188 of 216 bytes; the ten case routines are the region's ABI

2026-09-19. Worker `AnmVmDispatch`. **No promotion**: nothing in the maintained
tree changed except this note; every measurement was taken in
`/tmp/AnmVmDispatch/msvc` (`cp -a matching2/msvc`).

## The answer in one paragraph

0x004451C0 is a ten-way type dispatch whose ten case bodies are register
shuffles into ten different drawing routines, and **those ten routines must be
compiled from C++ in the same `/LTCG` link before this region can be exact**.
The model below reproduces retail's shared head byte for byte - the guard, the
`push esi / push edi` sink, the type nibble, the comparisons and *the entry
register pair retail's callers use* - and it reproduces retail's call sequence
exactly for the cases whose callee convention a prototype can name (case 7, and
case 9 as soon as the already-recovered 0x00444CE0 `DrawStrip` is a definition in
the same link), but the other eight cases need the callee's *body*: seven of the
ten routines take their entity in a register an MSVC declaration cannot name
(ESI, EDI, EAX) or take the manager on the stack next to it, so an opaque
declaration always falls back to a push-and-call that retail does not have.

Probe line of the best measured shape (nine callees bound opaquely, declarations
chosen so the pass reproduces retail's entry pair):

```
$ python3 matching2/tools/matching/probe.py --source src/render/anm_vm_draw_dispatch.cpp \
      --project /tmp/AnmVmDispatch/msvc --output /tmp/AnmVmDispatch/out --show 8
0x004451c0     188 bytes  _asm_FUN_004451c0_004451c0@8  DIFFERENT
  first difference at 0x004451e9
  expected: 56 57 77 7b ff 24 95 70   0x004451e9: 56  push   esi
  actual:   77 66 ff 24 95 54 52 44   0x004451e9: 77 66  ja     0x445251
NOT EXACT
```

* emitted **188** bytes against the declared **216**;
* **163 differing bytes** of 216, **41 identical bytes at the head**
  (0x004451C0..0x004451E8, i.e. `8b905c030000 f6c201 7411 f6c202 740c 538a98ff020000 84db 5b 7504 83c8ff c3 c1ea16 83e20f 83fa09`);
* the first difference is retail's saved-register prologue `push esi; push edi`,
  which retail needs because its case bodies pass the entity in ESI/EDI and the
  model's opaque declarations do not.

**0x00409230 and its sibling still do not land**: their 50/95 bytes are still
proven only against a stand-in callee (see
`release_flagged_entities_00409230_cluster.md`), because the prerequisite there
was always "0x004451C0 as C++ inside the link", and that is still gated on the
ten routines below.

## The region

`0x004451C0..0x00445298`, 216 bytes = 173 bytes of code + 3 bytes of jump-table
alignment pad (`8d 49 00`) + the 40-byte table at `0x00445270`. The guard reads
the entity's `+0x35C` flag word once (retail keeps it in EDX), rejects it if
`flags & 1` or `flags & 2` is clear or if the alpha byte at `+0x2FF` is zero
(retail loads it through BL and saves EBX around the test), and then switches on
`(flags >> 22) & 0xF` with a default that returns 0.

Table index -> case body -> routine, with the routine's own entry registers
(read off the retail image; the sizes are the manifest's):

| idx | case body | routine | size | entry registers | stack cleanup |
| --- | --- | --- | --- | --- | --- |
| 0 | 0x004451F4 | 0x00443080 | 515 | entity in **ESI**, manager on stack | `ret 4` |
| 1 | 0x004451FF | 0x004436C0 | 591 | manager in **ECX**, entity in **EDX** | plain `ret` |
| 2 | 0x00445256 | 0x00443290 | 486 | entity in **EAX**, manager on stack | `ret 4` |
| 3 | 0x0044525F | 0x00443910 | 591 | manager in **ECX**, entity in **EDX** | plain `ret` |
| 4 | 0x00445208 | 0x00443F80 | 33 | entity in **ESI**, manager on stack | `ret 4` |
| 5 | 0x00445213 | 0x00444580 | 60 | entity in **ESI**, manager in **EDI** | plain `ret` |
| 6 | 0x0044521F | 0x00443FB0 | 643 | entity in **EDI**, manager in **ESI** | plain `ret` |
| 7 | 0x0044522B | 0x004445C0 | 402 | manager then entity **on the stack** | `ret 8` |
| 8 | 0x00445235 | 0x00444760 | 929 | entity in **EAX**, manager on stack | `ret 4` |
| 9 | 0x0044523E | 0x00444CE0 | 224 | manager in **ECX**, entity in **EAX**, vertices/count on stack | `ret 8` |

The nine unrecovered routines are `kind: asm` in the manifest today (sources
`src/render/quad_build_anchored.cpp`, `anchored_quad_draw.cpp`,
`fun_00443f80_00443f80.cpp`, `fun_00444580_00444580.cpp`,
`anm_distance_color.cpp`, `faded_quad_draw.cpp`, `quad_transform_draw.cpp` and
`src/unidentified/FUN_004436c0_004436c0.cpp` / `FUN_00443910_00443910.cpp`);
only 0x00444CE0 is semantic (`src/render/edge_strip_draw.cpp`, landed in the
render-batch cluster).

Two facts that help whoever recovers them:

* **0x004436C0 and 0x00443910 are instruction-identical twins**: a byte diff of
  their two 591-byte bodies shows differences *only* in branch displacements
  (same constants, same field offsets, same calls). One model, two regions.
* 0x00443F80 (33 bytes) and 0x00444580 (60 bytes) are thin wrappers: they call
  0x00443B60 / 0x00444240 and then `SubmitSpriteQuad` (0x00442670, already
  semantic) with mode 0, and 0x00444580 additionally stores `1.0f` into
  0x00497920 / 0x00497904 / 0x004978E8 / 0x004978CC.

The conventions are global, not local to this dispatcher: all 23 `call
0x004451C0` sites in the image load the manager into ECX from `ds:0x00491C10`
(19 of them) or have it live there already (0x0041D863, 0x0041EAE3,
0x004263AE, 0x004489B0) and compute the entity into EAX right before the call;
`0x00409190` is the plainest:

```
409199  mov ecx,dword ptr [data_00491c10]
40919f  lea eax,[esi+10h]
4091a2  call 004451C0h
4091a7  mov ecx,dword ptr [data_00491c10]   ; reloaded: the callee clobbers ECX
4091ad  lea eax,[esi+3BCh]
4091b3  call 004451C0h
```

and 0x00443080's convention is confirmed at four independent asm call sites
(e.g. 0x0042B929 `mov ecx,[data_00491c10] / push ecx / call 0x00443080` with the
entity in ESI).

## The model

Modelled as a free function with C linkage so the maintained symbol
`_asm_FUN_004451c0_004451c0` (and therefore the caller's cluster binding) is
unchanged; `/Gz` decorates it `_asm_FUN_004451c0_004451c0@8`, the name the
release note's verification already used for the callee.

```cpp
// 0x004451C0: dispatch one animation entity's quad to the routine its type selects.
#include "th10/render/quad_batch.hpp"

extern "C" __declspec(noinline) int EntityDraw_00443080(RenderEntity* entity, AnimationManager_00442F50* manager);
extern "C" __declspec(noinline) int QuadDrawChecked_004436c0(AnimationManager_00442F50*, RenderEntity*);
extern "C" __declspec(noinline) int EntityDraw_00443290(RenderEntity* entity, AnimationManager_00442F50* manager);
extern "C" __declspec(noinline) int QuadDrawCheckedAlt_00443910(AnimationManager_00442F50*, RenderEntity*);
extern "C" __declspec(noinline) int EntityDraw_00443f80(RenderEntity* entity, AnimationManager_00442F50* manager);
extern "C" __declspec(noinline) int EntityDraw_00444580(RenderEntity* entity, AnimationManager_00442F50* manager);
extern "C" __declspec(noinline) int EntityDraw_00443fb0(RenderEntity* entity, AnimationManager_00442F50* manager);
extern "C" __declspec(noinline) int FadedQuadDraw_004445c0(AnimationManager_00442F50*, RenderEntity*);
extern "C" __declspec(noinline) int EntityDraw_00444760(RenderEntity* entity, AnimationManager_00442F50* manager);

#pragma code_seg(".text$01dispatch")
extern "C" __declspec(noinline) int asm_FUN_004451c0_004451c0(AnimationManager_00442F50* manager, RenderEntity* entity) {
    unsigned int flags = entity->flags;
    if (!(flags & 1)) return -1;
    if (!(flags & 2)) return -1;
    if (((const unsigned char*)&entity->color)[3] == 0) return -1;
    switch ((flags >> 22) & 0xF) {
    case 0: return EntityDraw_00443080(entity, manager);
    case 1: return QuadDrawChecked_004436c0(manager, entity);
    case 2: return EntityDraw_00443290(entity, manager);
    case 3: return QuadDrawCheckedAlt_00443910(manager, entity);
    case 4: return EntityDraw_00443f80(entity, manager);
    case 5: return EntityDraw_00444580(entity, manager);
    case 6: return EntityDraw_00443fb0(entity, manager);
    case 7: return FadedQuadDraw_004445c0(manager, entity);
    case 8: return EntityDraw_00444760(entity, manager);
    case 9: return manager->DrawStrip(entity, entity->strip_vertices, entity->strip_count * 2);
    }
    return 0;
}
#pragma code_seg()
```

Three notes on the source:

* the nine `EntityDraw_*` / `QuadDrawChecked_*` / `FadedQuadDraw_*` prototypes are
  **placeholders for definitions that do not exist yet**; they are written as
  free functions whose arguments go on the stack so that the pass keeps retail's
  entry pair (see the shapes table). Their argument *order* only has to make the
  semantics readable; once the routines are modelled as members of the entity or
  manager record (the family idiom - `?DrawStrip@AnimationManager_00442F50@@...`
  is a manager member taking the entity, `?SyncRenderState@...` the same) the
  pass re-chooses the registers from their bodies.
* the guard was written against `entity->flags` (`unsigned int` at +0x35C) held in
  a local, and against the alpha byte of `entity->color` at +0x2FF - the same
  idiom the landed `DrawStrip` uses (`((const unsigned char*)&entity->color)[3]`).
  Both come out byte-identical to retail (see the 41-byte head), including the
  `push ebx / mov bl,... / test bl,bl / pop ebx` sequence.
* the shared header needed two views of the entity that it did not have yet
  (attempting the region without them is impossible, since case 9 hands
  `[entity+0x358]` and `[entity+0x30C]*2` to `DrawStrip`):

```cpp
    unsigned char reserved_304[0x30C - 0x304];
    unsigned int strip_count;                       // +0x30C, doubled at the call site
    unsigned char reserved_310[0x358 - 0x310];
    const void* strip_vertices;                     // +0x358
    unsigned int flags;                             // +0x35C
```

  The offsets and the object size are unchanged, and the merge experiment below
  measured that the change does not perturb the landed render-batch cluster
  (`DrawStrip` was still 0 differing bytes in that link).

`layout/ltcg/anm_vm_draw_dispatch_004451c0.json` as measured (declared size is the
*emitted* 188; the region's declared 216 cannot be declared here until the body
is exact, which is why nothing is registered):

```json
{
  "schema_version": 1,
  "name": "anm_vm_draw_dispatch_004451c0",
  "source": "src/render/anm_vm_draw_dispatch.cpp",
  "driver": "layout/ltcg/anm_vm_draw_dispatch_004451c0_context.cpp",
  "headers": ["include/th10/render/quad_batch.hpp"],
  "image_base": "0x00400000",
  "description": "Type dispatch for the animation entity quad draws, compiled with native LTCG ...",
  "functions": [
    {
      "name": "AnmVmDrawDispatch",
      "symbol": "_asm_FUN_004451c0_004451c0@8",
      "section": ".text$01dispatch",
      "address": "0x004451C0",
      "size": 188,
      "actual_abi": "manager in ECX; entity in EAX; no stack arguments; plain RET"
    }
  ],
  "context": {
    "symbol": "?AnmVmDrawDispatchCompilerContext@@YGHPAPAURenderEntity@@H@Z",
    "section": ".text$03context",
    "address": "0x00445290",
    "size": 63,
    "description": "Synthetic array-walking caller that establishes the observed register convention; not recovered game code."
  },
  "gaps": [
    { "section": ".text$00layout", "address": "0x00401000", "size": 278976 },
    { "section": ".text$02layout", "address": "0x0044527C", "size": 20 }
  ],
  "constants": [],
  "absolute_symbols": [
    { "symbol": "_EntityDraw_00443080@8", "address": "0x00443080", "kind": "relative_code" },
    { "symbol": "_EntityDraw_00443290@8", "address": "0x00443290", "kind": "relative_code" },
    { "symbol": "_EntityDraw_00443f80@8", "address": "0x00443F80", "kind": "relative_code" },
    { "symbol": "_EntityDraw_00443fb0@8", "address": "0x00443FB0", "kind": "relative_code" },
    { "symbol": "_EntityDraw_00444580@8", "address": "0x00444580", "kind": "relative_code" },
    { "symbol": "_EntityDraw_00444760@8", "address": "0x00444760", "kind": "relative_code" },
    { "symbol": "?DrawStrip@AnimationManager_00442F50@@QAEHPBURenderEntity@@PBXI@Z", "address": "0x00444CE0", "kind": "relative_code" },
    { "symbol": "_QuadDrawChecked_004436c0@8", "address": "0x004436C0", "kind": "relative_code" },
    { "symbol": "_QuadDrawCheckedAlt_00443910@8", "address": "0x00443910", "kind": "relative_code" },
    { "symbol": "_FadedQuadDraw_004445c0@8", "address": "0x004445C0", "kind": "relative_code" },
    { "symbol": "_data_00491c10", "address": "0x00491C10", "kind": "data" }
  ]
}
```

(the context's declared address is the *emitted* one: the linker aligns the
context section itself, so the tail gap is whatever makes
`align16(0x4451C0 + emitted function size + gap)` land on the declared address.)

`layout/ltcg/anm_vm_draw_dispatch_004451c0_context.cpp`:

```cpp
#include "../../src/render/anm_vm_draw_dispatch.cpp"

#pragma code_seg(".text$03context")
int __stdcall AnmVmDrawDispatchCompilerContext(RenderEntity** entities, int count) {
    int drawn = 0;
    for (int i = 0; i < count; ++i) {
        drawn += asm_FUN_004451c0_004451c0(data_00491c10, entities[i]);
    }
    return drawn;
}
```

## Shapes tried (standalone cluster, measured)

| declarations for the nine routines | emitted | differing | identical head | entry pair (manager/entity) |
| --- | --- | --- | --- | --- |
| `entity->X(manager)` members (six) + `__fastcall`-style free ones | 184 | 166 | 1 byte | **ECX / EAX** - mirrored: the six member calls want the entity in ECX, so the pass swaps the pair |
| six `__stdcall(entity, manager)` + `__fastcall` for cases 1/3 + cdecl for 7 (**best head**) | 188 | **163** | **41 bytes** | ECX / EAX - retail's pair |
| as above but `__fastcall` for cases 1/3 | 180 | 203 | 1 byte | pair moves off retail |
| as above but 1/3 `__fastcall` and the six as entity members ("best") | 180 | 203 | 1 byte | pair moves off retail |
| **merged into the landed render-batch cluster** (DrawStrip defined in the link) with the best-head declarations | 188 | 163 | 41 bytes | ECX / EAX; **case 9 byte-exact**, DrawStrip still 0 differing |
| the same merge with the "best" declarations | 184 | 201 | 1 byte | pair moves off retail |

The lesson in that table is that the dispatcher's *own* entry registers are the
pass's joint optimum over its callees, so a declaration change anywhere moves
them: only the shape whose nine prototypes impose no register demand reproduces
retail's `(manager ECX, entity EAX)` pair at all.

### The instruction-level delta of the 188-byte body

The 41-byte head, then per case (retail -> emitted, the merged-link build):

| idx | retail | emitted | comment |
| --- | --- | --- | --- |
| 0 | `push ecx; mov esi,eax; call` | `push ecx; push eax; call` | entity on the stack instead of ESI |
| 1 | `pop edi; mov edx,eax; pop esi; jmp` | `push eax; push ecx; call; ret` | no tail call: ECX/EDX needs the callee's body |
| 2 | `push ecx; mov esi,eax; call` | `push ecx; push eax; call` | entity in EAX retail, on the stack here |
| 3 | `pop edi; mov edx,eax; pop esi; jmp` | `push eax; push ecx; call; ret` | as case 1 |
| 4 | `push ecx; mov esi,eax; call` | `push ecx; push eax; call` | as case 0 |
| 5 | `mov esi,eax; mov edi,ecx; call` | `push ecx; push eax; call` | ESI/EDI needs the callee's body |
| 6 | `mov edi,eax; mov esi,ecx; call` | `push ecx; push eax; call` | EDI/ESI needs the callee's body |
| 7 | `push eax; push ecx; call` | `push eax; push ecx; call` | **instruction-identical** (`5051e8...`); retail's `5f 5e c3` epilogue belongs to the shared ESI/EDI save |
| 8 | `push ecx; call` | `push ecx; push eax; call` | entity in EAX retail |
| 9 | `mov edx,[eax+30C]; shl edx,1; push edx; mov edx,[eax+358]; push edx; call` | identical (`8b900c030000d1e2528b905803000052e8...`) | **byte-exact in the merged link**, plus retail's `5f 5e c3` |
| default | `xor eax,eax; ret` | `xor eax,eax; ret` | identical modulo the shared epilogue |

The jump table is the second structural difference: retail's sits at 0x00445270
after 3 bytes of `8d 49 00` padding, the emitted one at 0x004451F2/0x00445254
because the eight short case bodies shrink the function, so every table entry and
every relative displacement differs even where the instructions agree, and the
`ja` default displacement differs too.

## The merge that will land it

The one callee that already exists as a definition is `0x00444CE0 DrawStrip`
(manager member, `RET 8`, entity in EAX - exactly what retail's case 9 assumes),
and it lives in the landed render-batch cluster
(`layout/ltcg/anm_batch_flush_00442f50.json`). Adding this region to that cluster
was measured in the scratch tree:

* add `src/render/anm_vm_draw_dispatch.cpp` to its `additional_sources`,
* add the function entry with section `.text$06hdispatch` (the section name has
  to sort after `.text$06glayout` and before the trailing gap, because the
  linker places sections in name order),
* split its `.text$06glayout` gap (0x004451B3, 77) into a 13-byte gap, this
  function, and a `.text$06ilayout` gap, and move the declared context address to
  `align16(0x4451C0 + emitted + 16)`,
* bind the nine still-opaque routines absolutely as above,
* declare `asm_FUN_004451c0_004451c0` in `layout/ltcg/render_batch_context.cpp`
  and call it from the synthetic loop so the function is reachable (it is not
  rooted).

Result of that build: the dispatcher is still 188 bytes / 163 differing with the
same 41-byte head - **but case 9 now emits retail's exact six-instruction body**
(`mov edx,[eax+30C]; shl edx,1; push edx; mov edx,[eax+358]; push edx; call`,
no entity push, the definition in the link is what makes DrawStrip take the
entity in EAX), and the cluster's own `DrawStrip` region is **still 0 differing
bytes**, so the added source and the header fields do not perturb it.

A two-source cluster that put the dispatcher and `DrawStrip` alone in one link
(without the rest of the batch cluster) showed why the whole call graph is
needed: `DrawStrip`'s callees `SyncRenderState` / `Flush` were then opaque, the
joint optimum moved, and `DrawStrip`'s own body lost its `push esi; push edi`
prologue (208 of 215 bytes differing) - i.e. a partial cluster re-chooses the ABI
of the functions in it. That is also why the *scheduler* cluster is not the merge
target here: `0x00409230`/`0x004091C0` are their own sources, and the cluster that
already owns the callee is the render-batch one.

## What has to exist for an exact 216 bytes (and for 0x00409230)

1. Recover the nine routines above as C++ (one region each, same native-LTCG
   idiom as the family: entity/manager member functions whose bodies the pass
   re-conventions). 0x004436C0 and 0x00443910 are the same code twice; 0x00443F80
   and 0x00444580 are thin wrappers around `SubmitSpriteQuad`.
2. Put this dispatcher, those nine regions **and** `DrawStrip`'s source in one
   cluster, with a context that walks entities the way the retail callers do
   (`mov ecx,[data_00491c10]; lea eax,[entity+0x10]; call`), so the pass sees
   retail's joint optimum - the manager in ECX at every call site and each entity
   in the register that callee reads.
3. `0x00409230` (and its sibling `0x004091C0`, whose receiver EBX is supplied by
   `0x00409270`) then join the same cluster, since their exact 50/95 bytes only
   exist when the dispatcher's *definition* is in the link.

## Reproduction

```
cp -a matching2/msvc /tmp/AnmVmDispatch/msvc
# write the three artifacts above into the copy, then
python3 /home/levzzz/Games/th10Decomp/matching2/tools/waves/register_cluster.py \
    --project /tmp/AnmVmDispatch/msvc \
    --layout layout/ltcg/anm_vm_draw_dispatch_004451c0.json --apply
python3 matching2/tools/matching/probe.py --source src/render/anm_vm_draw_dispatch.cpp \
    --project /tmp/AnmVmDispatch/msvc --output /tmp/AnmVmDispatch/out --show 8
```

(The scratch copy carries a manifest region size of 188 for 0x004451C0 only so
the loader accepts the emitted extent, exactly the exploration path the cluster
lessons describe; the maintained manifest still declares 216 and `kind: asm`.)
