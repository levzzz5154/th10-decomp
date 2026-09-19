# Region 0x0040C540 (75 bytes) - recovered EXACT

2026-09-19, agent `LazyFetchTail`. Region `0x0040C540..0x0040C58A`, source
`src/game/animation_resource_lazy_fetch.cpp`, 75 bytes. Work was done in
`/tmp/LazyFetchTail/msvc` plus two throwaway copies: `/tmp/LazyFetchTail/combined`
(the wave-10 measurement link, 448D50 a selected function and 0x40C540 an anchor)
and `/tmp/LazyFetchTail/land` (the landing shape, 0x40C540 the selected function
and 448D50 an anchor).

## Disposition

**EXACT 75/75 bytes**, landed as a single-function native-LTCG cluster with four
compiled ABI anchors, registered through the normal path:

```sh
python3 matching2/tools/waves/register_cluster.py \
    --project matching2/msvc \
    --layout layout/ltcg/lazy_animation_resource_0040c540_wave11.json --apply
# registered semantic_GameThread_EnsureAnimationResource_0040c540_0040c540
#   as ?EnsureAnimationResource@GameThread_0040c540@@QAEPAXMM@Z
# ltcg_clusters: 260 entries
```

Probe against the maintained tree:

```sh
python3 matching2/tools/matching/probe.py \
    --source src/game/animation_resource_lazy_fetch.cpp \
    --project matching2/msvc --output /tmp/LazyFetchTail/outfinal --show 30
0x0040c540      75 bytes  ?EnsureAnimationResource@GameThread_0040c540@@QAEPAXMM@Z  EXACT
EXACT
```

Manifest gates (this registration only; `make` was not run here):

```text
build_msvc.validate_project: 4425 regions / 2395 units
ltcg_cluster.load_clusters:  260 clusters loaded, none rejected
```

The exported body is byte-identical to retail with nothing masked:

```text
emitted   75 bytes  sha256 db211c56b1a3d43bd7ec6205df37dee126b4ff410ed4ef813ba7dbaabd1978f3
retail    75 bytes  sha256 db211c56b1a3d43bd7ec6205df37dee126b4ff410ed4ef813ba7dbaabd1978f3

83 ec 0c 8b 44 24 10 8b 4c 24 14 89 04 24 8b 86 a4 89 00 00 85 c0 89 4c 24
04 c7 44 24 08 00 00 00 00 75 21 8b 86 94 89 00 00 57 6a 06 8d 54 24 18 52
50 8d 7c 24 10 e8 d4 c7 03 00 8b 00 89 86 a4 89 00 00 5f 83 c4 0c c2 08 00
```

which is retail's own listing, instruction for instruction: `sub esp,0Ch` / the
three position stores (`mov eax,[esp+10h]`, `mov [esp],eax`, `mov ecx,[esp+14h]`
scheduled after the handle load and test) / `mov eax,[esi+89A4h]` / `test eax,eax`
/ `jne 0x40C585` / `mov eax,[esi+8994h]` / `push edi` / `push 6` / `lea edx,[esp+18h]`
/ `push edx` / `push eax` / `lea edi,[esp+10h]` / `call 0x448D50` /
`mov eax,[eax]` / `mov [esi+89A4h],eax` / `pop edi` / `add esp,0Ch` / `ret 8`.

## What the last two bytes were

Wave 10 landed `0x00448D50` and measured this region at 75 bytes with **2**
differing:

```text
40c57c: emitted  8b 08              mov (%eax),%ecx      retail  8b 00  mov (%eax),%eax
40c57e: emitted  89 8e a4 89 00 00  mov %ecx,0x89a4(%esi) retail  89 86 a4 89 00 00  mov %eax,...
```

Both are `+0x3d 08/00` and `+0x3f 8e/86`: the scratch register for the handle
loaded through the callee's returned out slot. Wave 10 measured three tail
shapes (`*call(...)`, a `void* value = *call(...)` local, and a two-step
`void** slot = call(...)`) and all three produced ECX, so the tie-break was not
in the shape of the *load*.

It is in the **signature**. With a `void` return, nothing is live in EAX when the
body ends, so the backend is free to use the address register's dying value for
the load and picks ECX. Declaring the model to *return the handle* leaves EAX
holding the function's result, and the pass then coalesces the load into it -
retail's `mov (%eax),%eax; mov %eax,0x89a4(%esi)` - and both return paths agree:
the early path already has EAX = the loaded handle for its `test`, and the tail's
value is the returned one. This is the wave-10 "consumed temporary" lever seen
from the other side: what matters is which value is live in a register at the end
of the body, not how many source temporaries there are.

Measured in the landing-shaped link (`/tmp/LazyFetchTail/land`; only the return
type and the tail statements vary; the head, the call and the 448D50 anchor are
constant):

| tail shape | return | emitted | differing |
|---|---|---:|---:|
| `void** slot = call(...); void* value = *slot; animation_handle = value; return;` | `void` | 75 | **2** (`+0x3d 08/00`, `+0x3f 8e/86`) |
| `animation_handle = *slot;` (wave 10's three shapes, all identical) | `void` | 75 | 2 (same two) |
| `void* value = *slot; animation_handle = value; return value;` | `void*` | 75 | **0** |
| `return animation_handle = *slot;` | `void*` | 75 | **0** |
| **`animation_handle = *slot; return animation_handle;`** | **`void*`** | **75** | **0** |

The landed source uses the last shape; the `void*` return is not a convenience:
retail's EAX at every exit is the handle, so a caller reading the return would see
the handle, and the allocator only reproduces EAX when the model says so. The six
retail call sites all ignore EAX (`mov 0x4776e0,%esi; push ...; call 0x40c540`),
so nothing in the image depends on the choice; three of them are inlined copies
of this very body.

## The cluster

`0x00448D50` is landed and registered, so this layout **anchors** it rather than
selecting it (two clusters cannot select the same maintained source, and a region
can be exported once): the driver carries the recovered 95-byte body verbatim -
only the position type's name and the section change - placed at the retail
address, declared in `anchors` and never exported. In this link that anchor comes
out byte-identical to retail as a by-product (0 differing of 95), which is a
useful check that the scaffold is the landed recovery and not a fiction.

The three bodies `0x00448D50` calls are carried as anchors too, exactly as the
wave-10 landing carried them (`0x0043E710` 207 bytes, `0x004489D0` 103 bytes,
`0x00449950` 171 bytes). Those three are *models* of their regions - their bytes
differ from retail (192, 66 and 155 of 207/103/171) - and they exist only so the
whole-program pass assigns the entry registers retail's `0x00448D50` body needs
(position in EDI on this side; EDX/EBX/EAX and ECX/EAX/EBX on the other), which
is what makes this region's own call site retail's. The cluster exports exactly
one function (the report's `functions` list has a single entry, `.text$01lazy`,
75 bytes); no anchor byte enters the image.

Sections are name-ordered, gaps even-numbered, code odd-numbered, so the linker's
alphabetical `.text$NN` packing reproduces the retail addresses:

```text
.text$00alayout   0x401000  46400      .text$06layout   0x448A37   793
.text$01lazy      0x40C540     75      .text$07accessor 0x448D50    95
.text$02alayout   0x40C58B 126976      .text$08layout   0x448DAF  2977
.text$02blayout   0x42B58B  78213      .text$09alloc    0x449950   171
.text$03loadscript 0x43E710   207      .text$0alayout   0x4499FB     5
.text$04alayout   0x43E7DF  41457      .text$0bcontext  0x449A00    47
.text$05regprimary 0x4489D0   103
```

## Does it unblock anything? No

The region is a leaf called from assembly regions only (`manager_teardown.cpp`,
`event_script_runtime.cpp`, `practice_stage_menu.cpp`, `replay_menu_runtime.cpp`,
`shot_practice_menu.cpp`); those call sites address the symbol and were already
exact, and they read nothing back, so no caller's model changes. The three
regions that contain an *inlined* copy of this body (wave 7 located them at
`0x417CC6`, `0x40B63F` and one more) still have to inline the model themselves;
a selected body at 0x40C540 does not compile their copies. Nothing else was
two bytes from exact on account of this region.

## Files

sha256:

```text
80ea919ee6eebd8bf660090e0ad97828d8cb406f5d891fd21726412440c9bd91  src/game/animation_resource_lazy_fetch.cpp
f68daffc68e3983f658dafcd06275cb8c31757b49ed286ae255cc90922049f72  layout/ltcg/lazy_animation_resource_0040c540_wave11.json
e8c6654ff7d2ce585b293532c9f43efbf5bc7a803923e3dd3b60aa5428178d36  layout/ltcg/lazy_animation_resource_0040c540_wave11_context.cpp
```

The only manifest change is region `0x0040C540` (`asm` -> `semantic`) and one
appended entry in `ltcg_clusters`; every other region record is byte-identical.

### `src/game/animation_resource_lazy_fetch.cpp`

```cpp
// 0x0040C540..0x0040C58A (75 bytes): arm the game thread's animation handle.
//
// The body builds the twelve-byte position record from its two float
// arguments, returns early when the cached handle at +0x89A4 is already armed,
// and otherwise asks the animation manager's positioned-primary creation
// (0x00448D50) for a new object, storing the handle it returns through the
// caller-supplied out slot at +0x89A4.  The function returns that handle, which
// is what the whole-program pass keeps in EAX across the tail.
//
// Retail enters this body with the game thread in ESI (a register no MSVC
// declaration names for a member function), so the region is compiled in the
// cluster layout/ltcg/lazy_animation_resource_0040c540_wave11.json.  Its driver
// carries the compiled body of 0x00448D50 as an ABI anchor - retail hands that
// callee the position record in **EDI**, which only a native /LTCG link that
// can see the callee's body assigns - together with the three callees
// 0x00448D50 itself needs (0x00449950 manager in ESI, 0x0043E710 resource in
// ECX / object in EAX / index in EBX, 0x004489D0 manager in EDX / entity in EBX
// / handle record in EAX).  The anchors are placed at their retail addresses
// and are never exported as recovered code.
//
// The tail pins the register too: with the handle declared as a consumed
// temporary that is then assigned to the live member, no value is live in EAX
// at the end of the body and the backend picks ECX for the load
// (`mov (%eax),%ecx; mov %ecx,0x89a4(%esi)`), two bytes away from retail.  With
// the handle returned instead, the pass has to leave it in EAX and emits
// retail's own `mov (%eax),%eax; mov %eax,0x89a4(%esi)`.
#pragma code_seg(".text$01lazy")

// The twelve-byte position record handed to the animation manager (the same
// record 0x00448D50 fills into the object at +0x340).
struct AnimationPosition_00448d50 {
    float x;
    float y;
    float z;
};

struct GameThread_0040c540 {
    unsigned char reserved_0000[0x8994];
    void* animation_resource;                       // +0x8994
    unsigned char reserved_8998[0x89A4 - 0x8998];
    void* animation_handle;                         // +0x89A4
    __declspec(noinline) void* EnsureAnimationResource(float x, float y);
};

// The animation manager's positioned-primary creation, recovered at
// 0x00448D50; the cluster driver carries its compiled body as an ABI anchor.
void** __stdcall AnimationManager_CreatePositionedPrimary_00448d50(
    void* resource, void** out, int index,
    const AnimationPosition_00448d50* position);

__declspec(noinline)
void* GameThread_0040c540::EnsureAnimationResource(float x, float y) {
    AnimationPosition_00448d50 position;
    position.x = x;
    position.y = y;
    position.z = 0.0f;
    if (animation_handle != 0) {
        return animation_handle;
    }
    void* handle;
    void** slot = AnimationManager_CreatePositionedPrimary_00448d50(
        animation_resource, &handle, 6, &position);
    animation_handle = *slot;
    return animation_handle;
}
#pragma code_seg()
```

### `layout/ltcg/lazy_animation_resource_0040c540_wave11.json`

```json
{
  "schema_version": 1,
  "name": "lazy_animation_resource_0040c540_wave11",
  "source": "src/game/animation_resource_lazy_fetch.cpp",
  "driver": "layout/ltcg/lazy_animation_resource_0040c540_wave11_context.cpp",
  "headers": [],
  "image_base": "0x00400000",
  "description": "0x0040C540 compiled with native LTCG so the game thread stays in ESI, the two floats stay on the stack and the returned handle stays in EAX. The .text$03loadscript, .text$05regprimary, .text$07accessor and .text$09alloc sections are compiled ABI anchors for the assembly regions at 0x0043E710, 0x004489D0, 0x00448D50 and 0x00449950: 0x00448D50 takes the position record in EDI and the other three arguments on the stack, and its own three callees keep their retail entry registers. The anchors are placed at the retail addresses so the calls carry retail's displacements, and they are never exported as recovered code.",
  "functions": [
    {
      "name": "GameThread_EnsureAnimationResource_0040c540",
      "symbol": "?EnsureAnimationResource@GameThread_0040c540@@QAEPAXMM@Z",
      "section": ".text$01lazy",
      "address": "0x0040C540",
      "size": 75,
      "actual_abi": "game thread in ESI; the two floats on the stack; the handle in EAX; ret 8"
    }
  ],
  "anchors": [
    {
      "name": "AnimationObject_LoadScript_0043e710_abi_anchor",
      "symbol": "_asm_AnimationObject_LoadScript_0043e710",
      "section": ".text$03loadscript",
      "address": "0x0043E710",
      "size": 207
    },
    {
      "name": "AnimationManager_RegisterPrimaryBack_004489d0_abi_anchor",
      "symbol": "_asm_AnimationManager_RegisterPrimaryBack_004489d0",
      "section": ".text$05regprimary",
      "address": "0x004489D0",
      "size": 103
    },
    {
      "name": "AnimationManager_CreatePositionedPrimary_00448d50_abi_anchor",
      "symbol": "?AnimationManager_CreatePositionedPrimary_00448d50@@YGPAPAXPAXPAPAXHPBUAnimationPosition_00448d50@@@Z",
      "section": ".text$07accessor",
      "address": "0x00448D50",
      "size": 95
    },
    {
      "name": "FUN_00449950_00449950_abi_anchor",
      "symbol": "_asm_FUN_00449950_00449950",
      "section": ".text$09alloc",
      "address": "0x00449950",
      "size": 171
    }
  ],
  "context": {
    "symbol": "?LazyResourceCompilerContext@@YGHPAPAUGameThread_0040c540@@H@Z",
    "section": ".text$0bcontext",
    "address": "0x449a00",
    "size": 47,
    "description": "Synthetic array-walking caller that establishes the region's register convention; not recovered game code."
  },
  "gaps": [
    {
      "section": ".text$00alayout",
      "address": "0x401000",
      "size": 46400
    },
    {
      "section": ".text$02alayout",
      "address": "0x40c58b",
      "size": 126976
    },
    {
      "section": ".text$02blayout",
      "address": "0x42b58b",
      "size": 78213
    },
    {
      "section": ".text$04alayout",
      "address": "0x43e7df",
      "size": 41457
    },
    {
      "section": ".text$06layout",
      "address": "0x448a37",
      "size": 793
    },
    {
      "section": ".text$08layout",
      "address": "0x448daf",
      "size": 2977
    },
    {
      "section": ".text$0alayout",
      "address": "0x4499fb",
      "size": 5
    }
  ],
  "constants": [],
  "roots": [],
  "absolute_symbols": [
    {
      "symbol": "_data_00491c10",
      "address": "0x00491C10",
      "kind": "data"
    },
    {
      "symbol": "_operator_new_00452493",
      "address": "0x00452493",
      "kind": "relative_code"
    },
    {
      "symbol": "_Entity_Constructor_00402050",
      "address": "0x00402050",
      "kind": "relative_code"
    },
    {
      "symbol": "_Entity_Init_00401de0",
      "address": "0x00401DE0",
      "kind": "relative_code"
    },
    {
      "symbol": "_asm_AnimationObject_LoadScriptTail_0043ee30",
      "address": "0x0043EE30",
      "kind": "relative_code"
    },
    {
      "symbol": "__fltused",
      "address": "0x00000000",
      "kind": "metadata"
    }
  ]
}
```

### `layout/ltcg/lazy_animation_resource_0040c540_wave11_context.cpp`

```cpp
// Compiler context and ABI anchors only; none of these bytes enter the image.
#include "../../src/game/animation_resource_lazy_fetch.cpp"

// Bindings for everything the anchors below call.
extern "C" void* data_00491c10;
extern "C" void* __cdecl operator_new_00452493(unsigned int size);
extern "C" void* __cdecl Entity_Constructor_00402050(void* entity);
extern "C" void __cdecl Entity_Init_00401de0(void* unused, void* entity);
extern "C" void __cdecl asm_AnimationObject_LoadScriptTail_0043ee30(void* object);

static unsigned int NextPoolIndex_00449950(unsigned int index) {
    unsigned int next = (index + 1) & 0x80000FFFu;
    if ((int)next < 0) {
        next = ((next - 1) | 0xFFFFF000u) + 1;
    }
    return next;
}

// The animation-manager pool allocator modelled only for its argument shape.
// These bytes are never selected as recovered code.
#pragma code_seg(".text$09alloc")
extern "C" __declspec(noinline) void* __cdecl asm_FUN_00449950_00449950(void* manager) {
    unsigned char* bytes = (unsigned char*)manager;
    unsigned int index = *(unsigned int*)(bytes + 0x3AD068);
    if (bytes[0x3AC068 + index] != 0) {
        index = NextPoolIndex_00449950(index);
        *(unsigned int*)(bytes + 0x3AD068) = index;
        if (bytes[0x3AC068 + index] != 0) {
            unsigned char* allocated = (unsigned char*)operator_new_00452493(0x3AC);
            if (allocated == 0) {
                return 0;
            }
            Entity_Constructor_00402050(allocated);
            Entity_Init_00401de0(0, allocated);
            *(unsigned int*)(bytes + 0x3AD068) =
                NextPoolIndex_00449950(*(unsigned int*)(bytes + 0x3AD068));
            return allocated;
        }
    }
    unsigned char* slot = bytes + 0x68 + index * 0x3AC;
    bytes[0x3AC068 + index] = 1;
    *(unsigned int*)(bytes + 0x3AD068) =
        NextPoolIndex_00449950(*(unsigned int*)(bytes + 0x3AD068));
    return slot;
}
#pragma code_seg()


// The script loader modelled only for its argument shape.  These bytes are
// never selected as recovered code.
#pragma code_seg(".text$03loadscript")
extern "C" __declspec(noinline) void __cdecl asm_AnimationObject_LoadScript_0043e710(
        void* resource, void* object, int index) {
    unsigned char* res = (unsigned char*)resource;
    unsigned char* obj = (unsigned char*)object;
    unsigned char* entries = *(unsigned char**)(res + 0x11C);
    if (*(int*)(entries + index * 4) == 0 || *(int*)(res + 0x124) != 0) {
        for (unsigned int byte = 0; byte < 0x3AC; ++byte) { obj[byte] = 0; }
        return;
    }
    Entity_Init_00401de0(0, obj);
    int flags = *(int*)(obj + 0x35C);
    *(short*)(obj + 0x38A) = (short)index;
    *(short*)(obj + 0x386) = *(short*)res;
    *(void**)(obj + 0x308) = res;
    *(int*)(obj + 0x35C) = flags & ~0x600;
    int value = *(int*)(entries + index * 4);
    *(int*)(obj + 0x38C) = value;
    *(int*)(obj + 0x390) = value;
    int state = *(int*)(obj + 0x6C);
    if ((state & 1) == 0) {
        *(int*)(obj + 0x6C) = state | 1;
        *(int*)(obj + 0x60) = 0;
        *(int*)(obj + 0x5C) = (int)0xFFF0BDC1u;
        *(int*)(obj + 0x64) = 0;
        *(int*)(obj + 0x68) = (int)0x00476F78u;
    }
    *(int*)(obj + 0x60) = 0;
    *(int*)(obj + 0x64) = 0;
    *(int*)(obj + 0x5C) = -1;
    *(int*)(obj + 0x35C) = *(int*)(obj + 0x35C) & ~1;
    asm_AnimationObject_LoadScriptTail_0043ee30(obj);
    unsigned char* manager = (unsigned char*)data_00491c10;
    *(int*)(manager + 0x4C) = *(int*)(manager + 0x4C) + 1;
}
#pragma code_seg()


// The primary-list registration leaf modelled only for its argument shape.
// These bytes are never selected as recovered code.
struct AnmListNode_00448d50 {
    void* owner;
    AnmListNode_00448d50* next;
    AnmListNode_00448d50* previous;
};

struct AnmListObject_00448d50 {
    int id;
    AnmListNode_00448d50 primary_back;
};

struct AnmListManager_00448d50 {
    unsigned char reserved_00000000[0x72DAD4];
    AnmListNode_00448d50* primary_back_head;
    AnmListNode_00448d50* primary_back_tail;
    unsigned char reserved_0072DADC[0x732454 - 0x72DADC];
    int next_id;
};

#pragma code_seg(".text$05regprimary")
extern "C" __declspec(noinline) void** __cdecl asm_AnimationManager_RegisterPrimaryBack_004489d0(
        void* manager, void** out, void* entity) {
    unsigned char* m = (unsigned char*)manager;
    unsigned char* e = (unsigned char*)entity;
    void** node = (void**)(e + 0x04);
    node[0] = e; node[1] = 0; node[2] = 0;
    void* head = *(void**)(m + 0x72DAD4);
    if (head == 0) { *(void**)(m + 0x72DAD4) = node; }
    else {
        unsigned char* tail = *(unsigned char**)(m + 0x72DAD8);
        unsigned char* next = *(unsigned char**)(tail + 0x04);
        if (next != 0) { node[1] = next; *(unsigned char**)(next + 0x08) = (unsigned char*)node; }
        *(unsigned char**)(tail + 0x04) = (unsigned char*)node;
        node[2] = tail;
    }
    *(void**)(m + 0x72DAD8) = node;
    int id = ++*(int*)(m + 0x732454);
    if (id == 0) { id = ++*(int*)(m + 0x732454); }
    *(int*)(e + 0x00) = id;
    *(int*)out = id;
    return out;
}
#pragma code_seg()

// 0x00448D50 as a compiled ABI anchor: the animation manager's positioned
// primary creation.  Its body is the recovered one; it is placed at the retail
// address so the call above bakes retail's displacement, and it is never
// exported as recovered code.  Retail hands this body the position record in
// EDI - a convention only a whole-program pass over this body can assign - and
// receives the resource, out slot and index on the stack.
struct AnimationObject_00448d50 {
    unsigned char reserved_000[0x20];
    int render_bucket_020;                          // +0x20
    unsigned char reserved_024[0x340 - 0x24];
    AnimationPosition_00448d50 position_340;        // +0x340
    unsigned char reserved_34c[0x35C - 0x34C];
    unsigned int flags_035c;                        // +0x35C
};

#pragma code_seg(".text$07accessor")
__declspec(noinline)
void** __stdcall AnimationManager_CreatePositionedPrimary_00448d50(
    void* resource, void** out, int index,
    const AnimationPosition_00448d50* position) {
    AnimationObject_00448d50* object =
        (AnimationObject_00448d50*)asm_FUN_00449950_00449950(data_00491c10);
    object->flags_035c |= 0x40000000u;
    object->render_bucket_020 = 0;
    object->position_340 = *position;
    asm_AnimationObject_LoadScript_0043e710(resource, object, index);
    asm_AnimationManager_RegisterPrimaryBack_004489d0(data_00491c10, out, object);
    return out;
}
#pragma code_seg()


// 0x0040C540's own caller, shaped like the game's animation users.  Not
// recovered game code.
#pragma code_seg(".text$0bcontext")
int __stdcall LazyResourceCompilerContext(GameThread_0040c540** items, int count) {
    while (count--) {
        GameThread_0040c540* thread = *items++;
        thread->EnsureAnimationResource(480.0f, 392.0f);
    }
    return 0;
}
#pragma code_seg()
```
