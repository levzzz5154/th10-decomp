# 0x00401DE0 entity initializer: 183-byte exact prefix, three misplaced `pop`s

2026-09-19. The region is **not landed**. No manifest entry was touched: the
model below is 32 bytes off, so registering it would break the image. The whole
of `0x00401DE0..0x00401E96` (183 bytes: prologue, position/render-bucket save,
`rep stos` clear, restore, colour/scale, the complete identity matrix) is
byte-exact, and the only residual is where MSVC places three one-byte
callee-save restores.

## Measured delta

| | value |
| --- | --- |
| declared size | 273 |
| emitted size | **273** (`probe` compares extents first: equal) |
| instructions | 67 emitted, 67 retail |
| differing bytes | **32 of 273** |
| differing instruction slots | 9 of 67 (the `pop` chain displacing its neighbours) |
| first difference | `0x00401E97` |
| `pop %edi` | retail `0x00401EAD`, model `0x00401E97` (4 instructions early) |
| `pop %esi` | retail `0x00401ED8`, model `0x00401ED8` (exact) |
| `pop %ebp` | retail `0x00401EE2`, model `0x00401ED9` (3 instructions early) |
| `pop %ebx` | retail `0x00401EEC`, model `0x00401EEC` (exact) |

Every other instruction, including all 16 identity-matrix stores, both
`mov 0x10(%esp),%ecx` / `mov 0x1c(%esp),%eax` spill reloads, the
`mov %eax,0x8(%esi)` z store, and the `for`-loop-unrolled pair of self-owning
list nodes, matches retail byte for byte. Retail places one pop after each of
the last four statement groups (timer group, counter group, first loop
iteration, function end); the model places `pop edi` after the matrix block and
leaves `pop ebp` immediately behind `pop esi`.

## ABI: the receiver is EDX and the model keeps it

Retail's ten call sites are `mov <reg>,%edx; call 0x401DE0` with no
materialisation of the first fastcall argument (disassembly check: the only
ECX writes in the neighbourhood of each call belong to other calls or are
stores/compares; the two sites inside `0x401110` are `mov %esi,%edx; call`).
The model is a two-argument `__fastcall` whose first parameter is dead, which is
exactly that convention:

```cpp
void __fastcall Entity_Init(void* unused, Entity* entity);
```

MSVC emits the body with the entity in **EDX** and never touches ECX before
`mov $0xeb,%ecx` for the clear, and it never writes EDX, so the callee preserves
the receiver register across the call (the property the pool allocator needs).
The `__declspec(noinline)` cluster shape below reproduces the same EDX entry
and the same bytes, so **no cluster is required for this region** — the native
LTCG path and the plain `/O2 /Gz /MT /Gy /G6 /GF /GS /Zl` compile of this
function are byte-identical, including the pop positions.

## Model that produces the delta

Probe (run from the repository root, against a throwaway copy of the project;
`src/game/entity_initialize_00401de0.cpp` is the carved single-region unit, see
below):

```text
python3 matching2/tools/matching/probe.py --source src/game/entity_initialize_00401de0.cpp \
    --project /tmp/InitEntity/msvc --output /tmp/InitEntity/out --proposal /tmp/InitEntity/proposal.json --show 12
0x00401de0     273 bytes  ?Entity_Init_Model@@YIXPAXPAUEntity@@@Z  DIFFERENT
  first difference at 0x00401e97
  expected: 66 c7 82 5c 03 00 00 07 00 89 42 60   0x00401e97: 66 c7 82 5c 03 00 00 07 00  mov WORD PTR [edx+0x35c],0x7
  actual:   5f 66 c7 82 5c 03 00 00 07 00 89 42   0x00401e97: 5f  pop edi
```

```cpp
// 0x00401DE0..0x00401EF0: Entity initializer.
#include <string.h>
#include "th10/game/entity.hpp"

void __fastcall Entity_Init_Model(void* unused, Entity* entity) {
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
    entity->end_marker = 7;
    entity->current_frame = 0;
    entity->previous_frame = 0xFFF0BDC1;
    entity->frame_elapsed = 0.0f;
    entity->pad_0B4[0] = 0;
    entity->pad_100[0] = 0;
    entity->pad_12C[0] = 0;
    entity->pad_178[0] = 0;
    entity->pad_1B4[0] = 0;
    entity->pad_200[0] = 0;
    entity->pad_22C[0] = 0;
    struct EntityLink { Entity* self; void* next; void* prev; };
    EntityLink* link = (EntityLink*)&entity->manager_node_animation;
    for (int i = 0; i < 2; ++i, ++link) {
        link->self = entity;
        link->next = 0;
        link->prev = 0;
    }
}
```

The matrix order above is retail's emitted order (twelve off-diagonal zeros in
descending offset order, then the four diagonal ones descending) and is written
statement by statement for the same reason as the landed `0x00401F00` region:
MSVC preserves the statement order of a run of constant stores to one base
register.

## Shapes measured on the way (differing instruction slots, same 273-byte extent)

| shape | diffs | note |
| --- | ---: | --- |
| `memset` + `position = position` then `bucket` (aggregate copy) | 21 | reloads hoisted but z store uses `[edx+0x348]` |
| same, bucket statement first | 20 | reload registers land right (`ecx`←bucket, `eax`←z) |
| per-field `destination->x/y`, `bucket`, `destination->z` | 53-54 | store order right, frame collapses to `sub esp,0xc` |
| `memcpy` 8 + bucket + `memcpy` 4 through `&entity->position.z` | 18 | z store still `[edx+0x348]` |
| bucket statement + 12-byte copy (model above), plain list nodes | 20 | pops bunch after the matrix |
| model above + **node loop** | **9** | the loop form is what spreads the pop chain |
| node loop written with a `current = link + i` temporary | 12 | pops move one group later (after the counter group) |
| identity matrix as an inlined helper / member function | 9 | identical bytes, no pop movement |
| manual `rep stos` loop instead of `memset` | 9 | identical |
| `#pragma`-free braces, 1-iteration `for`, folded `if` around a group | 9 | front end removes the region |
| A/B/C groups as front-end-inlined helpers | 9 | identical |
| helper placed in another source and inlined by the native-LTCG pass | 9 | identical, so LTCG inlining is not the mechanism |
| `/O1`, `/Os`, `/Ot`, `/Ob1`, `/Oy-`, `/Oi`, `/Ow`, `/Og`, `/G5`, `/GB` | 12-138 | wrong flags for this TU; `/O2 /G6` is the profile |
| 24 permutations of the matrix/timer/counter/node blocks | 9 best | source reordering moves the pop anchor but transposes stores |

Two sources of noise were ruled out: the head is not the problem (183 bytes
exact, and the same head with a plain-node tail still gives 20 diffs), and the
tail is not *semantically* mis-transcribed (every store is right; only the pop
chain moves). The pop chain is a schedule artefact: MSVC places the four pops at
the ends of the last four "groups" it sees, and the group it chooses for
`pop edi`/`pop ebp` shifts with the loop form, the statement order and the
matrix access form, but the pair `(after timer group, after first loop
iteration)` was not reachable from any shape tried.

## Landing path if the pop chain is solved

`src/game/entity.cpp` owns eight regions (0x401DE0, 0x401FF0, 0x402050,
0x405D00, 0x405DE0, 0x406160, 0x4061D0, 0x41AD60), so the region has to be
carved into its own translation unit first. `carve_region.py --source
src/game/entity.cpp --address 0x401DE0` does exactly that and both units still
probe EXACT with the naked body in the new file (verified in a throwaway copy;
the parent keeps its seven other regions). The carved file must then receive the
semantic model, the region symbol must be renamed through
`probe.py --write-proposal` (or `register_cluster.py` if a cluster is ever
wanted), and the integration owner merges it; nothing non-exact is ever
registered.

## Effect on the dependents

Because the model is 32 bytes off it cannot be registered, so this region does
**not** unlock the `0x401440` (CreateGameThread) chain and does not change
`0x401110` (LoadGameThreadResources). The sibling on 0x401110 was told the
declared signature and that the entity arrives in EDX with ECX unused, which is
what its two call sites need, and was told not to bind the symbol until it
lands.
