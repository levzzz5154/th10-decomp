# `0x00401DE0` recovered EXACT — wave 9

2026-09-19. `Entity_Init` (273 bytes) is **recovered as C++** and **landed** in
the maintained tree; probing the maintained project reports
`0x00401de0 273 bytes ?Entity_Init@@YIXPAXPAUEntity@@@Z EXACT` with all 67
instruction slots and all four callee-save restores in retail's positions, and
the emitted body is byte-identical to retail (identical sha256, 0 differing
bytes). Every consumer of the address and every sibling region of
`src/game/entity.cpp` was re-probed as well. The landing package is retained at
`matching2/build/waves/results10/InitEntity/` for re-application.

```
0x00401de0     273 bytes  ?Entity_Init@@YIXPAXPAUEntity@@@Z  EXACT     (+ 7 sibling regions of entity.cpp, and 7 caller units)
```

## What the residual was

Wave 8 left the model at 273/273 bytes, 67/67 instructions and 32 differing
bytes: only the callee-save pop chain differed.

| | retail | model (wave 8) |
| --- | --- | --- |
| `pop %edi` | `0x401EAD` (after the frame-state group) | `0x401E97` (after the identity matrix, 4 statements early) |
| `pop %esi` | `0x401ED8` | `0x401ED8` (exact) |
| `pop %ebp` | `0x401EE2` (after the first list node) | `0x401ED9` (stacked on `pop %esi`) |
| `pop %ebx` | `0x401EEC` | `0x401EEC` (exact) |

Retail places the four restores at the ends of the last four statement groups
(frame state, seven slot words, first list node, function); the model placed
`pop edi` at the end of the identity matrix and stacked `pop ebp` on `pop esi`.

## The lever: a sub-object reference for each group

The pop anchors are *not* statement counts or code shapes; they follow the
group structure the pass sees, and a reference local is what draws the group
boundary. Measured on the pre-fix model (same 273 bytes, same 67 instructions,
only the anchors move):

| shape | `pop` slots (`edi`,`esi`,`ebp`,`ebx`) | differing slots |
| --- | --- | --- |
| reference model (plain member stores everywhere) | 44, 56, 57, 64 | 9 |
| identity matrix written as `entity->local_transform.values[i][j]` (no `Matrix4x4& m`) | **25**, 56, 57, 64 | 34 |
| identity matrix through a `float* v` pointer | 44, 56, 57, 64 | 9 |
| slot words through `*(uint32_t*)((char*)entity + 0x…)` | 44, 56, 57, 64 | 9 |
| list nodes as two `EntityLink&` references (one per node) | 44, 56, **60**, 64 | 5 |
| frame state through `float& frame_elapsed` | **48**, 56, 60, 64 | **0** |
| frame state through `FrameState&` (`previous/current/elapsed` at `+0x5C`) | **48**, 56, 60, 64 | **0** |

The `Matrix4x4& m` reference is what holds `pop edi` at the matrix end (removing
it sinks the pop to the memset, slot 25); the two `EntityLink&` references move
`pop ebp` from the `pop esi` stack to the end of the first node, and the
`FrameState&`/`float&` reference moves `pop edi` from the matrix end to the end
of the frame state. With those three references the pass emits every store in
retail's order *and* the four restores at retail's four group ends; the machine
code of every store is unchanged, so no store order had to be traded away.

The frame state is a real sub-object: `previous_frame` `+0x5C`, `current_frame`
`+0x60`, `frame_elapsed` `+0x64` are contiguous in the maintained header, and
the emitted order is `end_marker`, `current_frame`, `previous_frame`,
`frame_elapsed` — so the reference is also the plausibly-original access form.
`__declspec(noinline)` is byte-neutral here (measured) and keeps an /LTCG link
from inlining the body into `0x401110`'s caller.

## Other shapes measured in this wave (all 273 bytes / 67 slots)

A 160-shape sweep over {frame-state form} × {slot-word form} × {node form} ×
{`entity->` vs a `self` reference} — plain statements, one inlined setter for
the group, one inlined setter per store, braced groups, `for`/`while`/`do`
loops, index and pointer walks, an explicit two-node unroll — produced only
four anchor signatures: 9 differing slots (`44,56,57,64`), 12 (`55,57,61,64`,
the `current = link + i` temporary), 43 (the `do`/`while` forms; 278 bytes) and
50 (the `p != link + 2` walk; 280 bytes). None of them moved `pop edi`, and no
inlining shape (the wave-8 recipe: a per-store inlined body) moved any anchor at
all. The `entity->` vs `self` distinction and braces are inert; the reference
locals are the whole lever.

## Source — `src/game/entity_initialize_00401de0.cpp`

Carved out of `src/game/entity.cpp` (which owns eight regions) so the one /GL
scope that consumes the call can co-compile the body; the unit's own compile is
byte-identical to the native-LTCG one (receiver in EDX, dead ECX slot), so no
cluster layout and no driver are involved.

```cpp
// 0x00401DE0..0x00401EF0 (273 bytes): Entity_Init, the retail entity
// initializer.  It preserves the entity's position and render bucket across
// the 0x3AC-byte clear, re-establishes them, sets the identity transform and
// the frame state, clears the seven slot payload words and links the entity
// into its two intrinsic list nodes.
//
// The region is carved out of src/game/entity.cpp, which owns eight regions, so
// that the one /GL scope that consumes the call can co-compile this body:
// 0x00401110 reaches it twice and retail materialises nothing for the dead
// first argument.  On its own the unit's compile has the same bytes as the
// native-LTCG one, so no cluster is required for this region.
//
// Retail receives the entity in EDX and never reads ECX, so the declaration
// keeps the header's dead leading slot: MSVC assigns the second parameter to
// EDX and the body writes neither incoming register.
//
// The frame state and the two list nodes are written through references to
// their sub-objects rather than through the entity pointer.  Retail's four
// callee-save restores sit at the ends of the frame-state group, the slot
// group, the first node and the function (pop edi/pop esi/pop ebp/pop ebx).
// With plain member stores the pass sinks `pop edi` to the end of the identity
// matrix and stacks `pop ebp` on `pop esi` - a 32-byte delta with the same 67
// instructions.  Going through the sub-object references makes the pass emit
// the restores at retail's four group ends; the machine code of every store is
// unchanged.
#include <string.h>
#include "th10/game/entity.hpp"

__declspec(noinline) void __fastcall Entity_Init(void* unused, Entity* entity) {
    (void)unused;
    Vector3 position = entity->position;
    int32_t bucket = entity->render_bucket;
    memset(entity, 0, sizeof(Entity));
    entity->render_bucket = bucket;
    memcpy(&entity->position, &position, 12);
    entity->primary_color = 0xFFFFFFFF;
    entity->scale_x = 1.0f;
    entity->scale_y = 1.0f;
    Matrix4x4& m = entity->local_transform;
    m.values[3][2] = 0.0f;
    m.values[3][1] = 0.0f;
    m.values[3][0] = 0.0f;
    m.values[2][3] = 0.0f;
    m.values[2][1] = 0.0f;
    m.values[2][0] = 0.0f;
    m.values[1][3] = 0.0f;
    m.values[1][2] = 0.0f;
    m.values[1][0] = 0.0f;
    m.values[0][3] = 0.0f;
    m.values[0][2] = 0.0f;
    m.values[0][1] = 0.0f;
    m.values[3][3] = 1.0f;
    m.values[2][2] = 1.0f;
    m.values[1][1] = 1.0f;
    m.values[0][0] = 1.0f;
    struct FrameState { int32_t previous_frame; int32_t current_frame; float frame_elapsed; };
    entity->end_marker = 7;
    FrameState& frame = *(FrameState*)((char*)entity + 0x5C);
    frame.current_frame = 0;
    frame.previous_frame = 0xFFF0BDC1;
    frame.frame_elapsed = 0.0f;
    entity->pad_0B4[0] = 0;
    entity->pad_100[0] = 0;
    entity->pad_12C[0] = 0;
    entity->pad_178[0] = 0;
    entity->pad_1B4[0] = 0;
    entity->pad_200[0] = 0;
    entity->pad_22C[0] = 0;
    struct EntityLink { Entity* self; void* next; void* prev; };
    EntityLink& animation_node = *(EntityLink*)&entity->manager_node_animation;
    animation_node.self = entity;
    animation_node.next = 0;
    animation_node.prev = 0;
    EntityLink& child_node = *(EntityLink*)&entity->child_node_animation;
    child_node.self = entity;
    child_node.next = 0;
    child_node.prev = 0;
}
```

`Entity_Init` keeps the declaration the entity header already carries
(`include/th10/game/entity.hpp`, `void __fastcall Entity_Init(void* unused, Entity* entity);`),
so a semantic caller in another unit binds `?Entity_Init@@YIXPAXPAUEntity@@@Z`
to the definition; that declaration mangles to exactly that symbol (checked by
compiling a caller against the header).

## Manifest delta — no layout, no driver

The region needs no cluster and no `layout/ltcg` entry: the plain unit's compile
of this function is retail's, so the landing is the region record alone.

```json
  { "name": "semantic_Entity_Init_00401de0",
    "source": "src/game/entity_initialize_00401de0.cpp",
    "symbol": "?Entity_Init@@YIXPAXPAUEntity@@@Z",
    "address": "0x00401DE0", "size": 273, "kind": "semantic",
    "owner": "0x00401DE0",
    "previous_record": { "name": "asm_InitializeEntity_00401de0",
                         "source": "src/game/entity.cpp",
                         "symbol": "_asm_InitializeEntity_00401de0",
                         "address": "0x00401DE0", "size": 273, "kind": "asm",
                         "owner": "0x00401DE0" } }
```

`src/game/entity.cpp` loses the 273-byte naked block and keeps its seven other
regions; `translation_units` keeps `src/game/entity.cpp` and gains
`src/game/entity_initialize_00401de0.cpp`. `manifest["symbols"]` keeps
`_asm_InitializeEntity_00401de0 = 0x00401DE0`, so the naked callers below keep
resolving to the same address.

The landing is staged as `matching2/build/waves/results10/InitEntity/`
(`apply_package.py` + `payload/`, `probe.txt`). It splices the naked body out of
the *maintained* `entity.cpp` instead of shipping that file, because the file
owns eight regions and siblings convert its other regions in the same wave.

## Verification

Applied to a fresh copy of the project, then probed with the project's own
probe (`--source` for the new unit, for `entity.cpp` and for every unit that
calls 0x401DE0):

```
0x00401de0     273 bytes  ?Entity_Init@@YIXPAXPAUEntity@@@Z  EXACT
0x00401ff0      34 bytes  ?Entity_Destructor@@YIXPAUEntity@@@Z  EXACT
0x00402050      88 bytes  ?Entity_Constructor@@YIPAUEntity@@PAU1@@Z  EXACT
0x00405d00     215 bytes  _asm_FUN_00405d00_00405d00  EXACT
0x00405de0      34 bytes  ?EntitySecondaryResource_Release@@YIXPAUEntity@@@Z  EXACT
0x00406160     109 bytes  ?OutsidePlayfield@PlayfieldPoint@@QBEHMM@Z  EXACT
0x004061d0     109 bytes  ?OutsidePlayfieldInclusive@PlayfieldPoint@@QBEHMM@Z  EXACT
0x0041ad60      34 bytes  ?EntityAnimation_Release@@YIXPAUEntity@@@Z  EXACT
0x00401110     330 bytes  _asm_LoadGameThreadResources_00401110  EXACT
0x00445900    2315 bytes  _asm_GameStateInit_00445900  EXACT
0x00404f30     202 bytes  _asm_FUN_00404f30_00404f30  EXACT
0x0042b4d0     145 bytes  _asm_EffectManagerRuntime_InitializeRetail_0042b4d0  EXACT
0x00449950     161 bytes  _asm_FUN_00449950_00449950  EXACT
0x0043e710     203 bytes  _asm_AnimationObject_LoadScript_0043e710  EXACT
0x00448bb0     268 bytes  _asm_FUN_00448bb0_00448bb0  EXACT
EXACT
```

`build_msvc.validate_project` accepts the resulting manifest (4425 regions,
2394 translation units, `.text` covered to `0x465C00`; 2395 units once the
carved file is registered).

The same probe run against the **maintained** project after the integration
owner applied the package gives `0x00401de0 273 bytes
?Entity_Init@@YIXPAXPAUEntity@@@Z EXACT` together with the unit's seven other
regions, `0x00401110 330 bytes EXACT`, `0x00445900 2315 bytes EXACT` and
`0x00449950 161 bytes EXACT`.

The unit was also built the way a co-compiling cluster will build it: both
`entity_initialize_00401de0.cpp` and a caller TU compiled with `/GL` and linked
with `/LTCG` (`link /DLL /NOENTRY /LTCG`). The linked image emits the region
byte-identically to retail — `xor %eax,%eax` / `push %edi` / `mov $0xeb,%ecx` /
`rep stosd` / `or`-free frame state with `pop %edi` after `mov %eax,0x64(%edx)`,
`pop %esi` after the slot words, `pop %ebp` after the first node, `pop %ebx`
before `ret` — so the native-LTCG path and the plain unit agree, and a cluster
that lists this source in `additional_sources` keeps the region exact.

## Effect on the dependents

`0x00401110` (LoadGameThreadResources, 330 bytes) is **unchanged and still
EXACT**: it is still the registered `asm` region, and its two call sites
(`0x401217`, `0x40123B`, both `mov %esi,%edx; call 0x401de0`) keep binding
through `_asm_InitializeEntity_00401de0 = 0x401DE0`. The other six consumers of
the address (`game_state_init.cpp`,
`fun_00404f30_00404f30.cpp`,
`effect_manager_runtime_initialize_retail_0042b4d0.cpp`,
`fun_00449950_00449950.cpp`, `animation_object_load_script_0043e710.cpp`,
`fun_00448bb0_00448bb0.cpp`) were re-probed EXACT as well.

`0x00401110` does **not** land from this change alone. The remaining gap is on
the caller's side and the two agents who measured it disagree, so both readings
are recorded here.

Locally, an ordinary C++ call to the declared two-slot signature always
materialises the dead first slot. Four shapes, all with the maintained flags and
`Entity_Init(0, entity)`: (1) separate TU, `/GL` both, `link /LTCG`, callee
`__declspec(noinline)` → `xor %ecx,%ecx` in front of *each* call; (2) the same
without `noinline`, both symbols `/INCLUDE`-rooted → `xor %ecx,%ecx`; (3) callee
and caller in one TU as two distinct emitted functions → `xor %ecx,%ecx`; (4)
callee bound opaquely → `xor %ecx,%ecx`. Retail's two sites at `0x401217` and
`0x40123B` set *neither* register: `ECX` holds a stale value from unrelated code
(the flags word from `0x4011EF` at the first site, `%edi` from `0x401220` at the
second), which is what an argument the whole-program pass knows the callee
ignores looks like when the value already occupies that register.

`ThreadChain` reports the opposite for the shape it actually builds: with a
*compiled ABI anchor* for `0x401DE0` whose body is visible in its `/LTCG` link,
its loader's two sites come out `lea 0x14(%ebx),%esi` / `mov %esi,%edx` /
`call 0x401de0` with no `xor %ecx,%ecx` and no materialisation; it explained the
difference as "caller and callee IL in one /GL input". That explanation does not
reproduce either: a callee and caller compiled as one `/GL` input (callee a
distinct emitted body, `__declspec(noinline)`, the `call` surviving, literal `0`
in the first slot) linked with `/LTCG` still emits `xor %ecx,%ecx` before each
call. The remaining candidate is what `ECX` already holds at the two sites:
retail's own body has one early `xor %ecx,%ecx` (`0x40113D`) whose zero is still
in `ECX` at `0x40121C`, so a model whose surrounding code leaves `ECX`
known-zero would have the per-site setup CSE'd away. Whichever reading is
right for a given link, the shape that is *guaranteed* to work is a call that
leaves `ECX` alone — inline asm over the existing absolute binding (what the
naked region does today, EXACT), or a first-slot expression already resident in
`ECX`.

`ThreadChain` has decided to keep its own anchor text rather than select this
unit, precisely because selecting it is the configuration where the
materialisation was measured; the address, the `_asm_InitializeEntity_00401de0`
binding and the header declaration are unchanged by that choice.

What this landing supplies for the `0x401110` work is the real definition plus
the header declaration (`?Entity_Init@@YIXPAXPAUEntity@@@Z`, verified to be the
mangling the header produces) and the carved single-region unit such a `/GL`
scope can co-compile: in the `/GL` + `/LTCG` link built to check this, the
region comes out byte-identical to retail (273 bytes, same four `pop`
positions), so co-compiling it is safe. The definition stays
`__declspec(noinline)` (byte-neutral, measured) so that no `/GL` link can inline
the 273-byte body into a caller that retail calls; a cluster that selects this
unit can drop it in its own copy of the body if it needs the linker to analyse
the call instead.
