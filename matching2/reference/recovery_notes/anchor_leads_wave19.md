# The anchor lead - wave 19: 24 regions landed, and what a compiled anchor decides

The ten regions the 0x41 block note left as "needs an anchor" all share one shape:
the region calls a callee whose parameter register no C++ declaration names, so the
callee has to be *compiled into the same native-LTCG link* for the pass to pick it.
This wave built those callees as layout `anchors` (a body placed at the retail
address, selected into the link, never exported as recovered code) and landed
**24 regions** - 8 of the nine 0x41 leads listed in that note (all but
`0x0041BE40`) and 16 of the 0x40 block's equivalents, including the tenth lead
`0x0040C440` whose callee is the same `0x409E50` handle anchor.
Every landing below was probed `EXACT` against the maintained tree, with the
maintained layout set loaded.

## What the anchor decides (measured this wave)

1. **A post-parameter call frees the parameter's register.** `0x00418C30` is
   `mov edx,esi; call 0x418C40; mov eax,esi; ret`: the record has to arrive in ESI
   and move to EDX for the call. An anchor whose body merely writes through its
   pointer lets the pass keep the *caller's* value in EDX (it can see the callee
   does not clobber it), which emits `call; mov eax,edx; ret` in 8 bytes. Making
   the anchor call *after* it has consumed the pointer - `entry_free_004524a1(config)`
   as the last statement - makes EDX non-preserved, so the caller's live value must
   go to a callee-saved register, and the pass picks ESI: retail's exact 10 bytes.
   **This is the lever for every "record in ESI" wrapper in this wave.**
2. **A by-value struct parameter cannot be promoted, so it stays on the stack.**
   `0x41BE40` needs its anchor to take (EAX body, ESI owner, stack argument).
   With `void*` the pass kept the argument in ECX; with a one-dword
   `AnchorArgument_00404f30 argument` parameter it stays on the stack and ESI/EAX
   fall to the other two.
3. **Dead register parameters soak registers.** Declaring two extra unused `int`
   parameters moves the pass's second register assignment off the live parameter
   (used to place the argument before the struct-parameter lever was found).
4. **A declaration is enough when the register is one MSVC names.** `0x00412A80`
   and `0x0040C670` need the *EclFrame pointer* in EDX with the pass-through value in
   ECX: `int __fastcall ECL_ResolveIntValue_0044ff00(int unused, EclFrame* frame,
   int selector, int value);` plus an `absolute_symbols` binding of the mangled
   name (kind `relative_code`) reproduces the call site with no compiled callee.
   `0x0040C5F0` likewise declares `__fastcall resolve_operand_0044fdb0(int unused,
   EclFrame*, int)`, and passes its own `this` as the dead first argument so no
   ECX setup is emitted.
5. **A member body with a single argument gets this in ECX and the argument in
   EAX.** That is what the 0x40 block's EAX-entry wrappers need (`0x4051E0`,
   `0x4051D0`, `0x402040`, `0x40DC70`, `0x4088A0`, `0x40CE50`, `0x409E10`,
   `0x40ADA0`): plain free functions or members, no anchor at all.
6. **The anchors are shape, not semantics.** None of them is byte-compared; only
   the register each parameter earns matters. `0x44C350` (a 16-case x87 switch),
   `0x409E50` (a lookup plus a child walk), `0x447810` (a record release),
   `0x4136C0` (five opaque releases), `0x40E770`, `0x418C40` and `0x404F30` were
   all written fresh in the drivers, several of them under 20 statements.

## Landings (24)

| address | bytes | symbol | layout | entry registers earned |
| --- | ---: | --- | --- | --- |
| `0x00418C30` | 10 | `?Reset@GameConfig_00418c30@@QAEPAU1@XZ` | `layout/ltcg/cl_00418c30.json` | record in ESI, the callee's EDX argument |
| `0x00417840` | 33 | `?Reset@Object_00417840@@QAEPAU1@XZ` | `layout/ltcg/cl_00417840.json` | record in ESI, the callee's EDX argument |
| `0x00412A80` | 17 | `?Resolve@EclOperandSource_00412a80@@QAEHHH@Z` | `layout/ltcg/cl_00412a80.json` | source in EAX, selector in ECX, value in EDX (no anchor needed) |
| `0x00413B90` | 47 | `?ReleaseCachedResource_00413b90@@YGHXZ` | `layout/ltcg/cl_00413b90.json` | record in EDI, result in EAX |
| `0x00414550` | 30 | `?DestroySlot_00414550@@YGPAUAnimationSlot_00414550@@PAU1@I@Z` | `layout/ltcg/cl_00414550.json` | slot in EAX, flags on the stack, RET 4 |
| `0x00417720` | 10 | `?StopHandle@Entity_00417720@@QAEXXZ` | `layout/ltcg/cl_00417720.json` | entity in EAX, plain RET, tail jump |
| `0x00412E10` | 20 | `?Evaluate@CurveObject_00412e10@@QAEMXZ` | `layout/ltcg/cl_00412e10.json` | object in EAX, result in ST(0) |
| `0x00419930` | 35 | `?FindKey_00419930@@YGHPAUSearchRecord_00419930@@HH@Z` | `layout/ltcg/cl_00419930.json` | table in EDI, count in EDX, key in ESI |
| `0x004051E0` | 10 | `?AllocateBlock_004051e0@@YGPAXI@Z` | `layout/ltcg/cl_004051e0.json` | size in EAX, plain RET |
| `0x004051D0` | 7 | `?RetireBlock_004051d0@@YGHPAX@Z` | `layout/ltcg/cl_004051d0.json` | object in EAX, plain RET |
| `0x00402040` | 8 | `?FreeBlock_00402040@@YGXPAX@Z` | `layout/ltcg/cl_00402040.json` | block in EAX, plain RET |
| `0x0040CE50` | 17 | `?SetMax@Options_0040ce50@@QAEXH@Z` | `layout/ltcg/cl_0040ce50.json` | this in ECX, value in EAX, plain RET |
| `0x0040C440` | 24 | `?StopHandleAndClear@Entity_0040c440@@QAEXXZ` | `layout/ltcg/cl_0040c440.json` | entity in EAX, plain RET |
| `0x00402020` | 30 | `?ReleaseOwned@Holder_00402020@@QAEXXZ` | `layout/ltcg/cl_00402020.json` | holder in ESI, plain RET |
| `0x0040DC70` | 12 | `?Run@Outer_0040dc70@@QAEHXZ` | `layout/ltcg/cl_0040dc70.json` | outer in EAX, plain RET |
| `0x004088A0` | 11 | `?SlotIndex_004088a0@@YGHHH@Z` | `layout/ltcg/cl_004088a0.json` | index in EAX, base in ECX, plain RET |
| `0x0040C670` | 11 | `?Resolve_0040c670@@YGHHPAUEclSource_0040c670@@H@Z` | `layout/ltcg/cl_0040c670.json` | selector in ECX, source in EDX, value in EAX |
| `0x0040C5F0` | 10 | `?Resolve@OperandSource_0040c5f0@@QAEHH@Z` | `layout/ltcg/cl_0040c5f0.json` | source in ECX, selector in EAX |
| `0x0040E760` | 11 | `?Run@Outer_0040e760@@QAEXXZ` | `layout/ltcg/cl_0040e760.json` | outer in ECX, plain RET, tail jump |
| `0x00409E10` | 12 | `?Evaluate@Vector_00409e10@@QAEHXZ` | `layout/ltcg/cl_00409e10.json` | this in ECX, plain RET |
| `0x0040C860` | 36 | `?ReleaseBlock@ResourceOwner_0040c860@@QAEXXZ` | `layout/ltcg/cl_0040c860.json` | owner in ESI, plain RET |
| `0x00404CF0` | 20 | `?Evaluate@CurveObject_00404cf0@@QAEMXZ` | `layout/ltcg/cl_00404cf0.json` | object in EAX, result in ST(0) |
| `0x00404D10` | 26 | `?Evaluate@CurveObject_00404d10@@QAEMXZ` | `layout/ltcg/cl_00404d10.json` | object in EAX, result in ST(0) |
| `0x00405F40` | 47 | `?ReleaseCachedResource_00405f40@@YGHXZ` | `layout/ltcg/cl_00405f40.json` | record in EDI, result in EAX |

### Source text

#### 0x00418C30 - 10 bytes - `?Reset@GameConfig_00418c30@@QAEPAU1@XZ`

`src/unidentified/unassigned_00418c30.cpp`

```cpp
#pragma pack(push, 1)
struct GameConfig_00418c30 {
    unsigned char bytes[0x34];
    __declspec(noinline) GameConfig_00418c30* Reset();
};
#pragma pack(pop)
char __fastcall InitConfigAnchor_00418c40(int reserved, GameConfig_00418c30* config);
#pragma code_seg(".text$01reset")
GameConfig_00418c30* GameConfig_00418c30::Reset() {
    InitConfigAnchor_00418c40(0, this);
    return this;
}
#pragma code_seg()
```

Probe: `0x00418c30      10 bytes  ?Reset@GameConfig_00418c30@@QAEPAU1@XZ  EXACT`

Anchors compiled into this cluster (`layout/ltcg/cl_00418c30_context.cpp`):

```cpp
// Compiler context only; never selected as recovered game code.
#include <string.h>
#include "../../src/unidentified/unassigned_00418c30.cpp"

extern "C" void __cdecl entry_free_004524a1(void* block);

#pragma code_seg(".text$03anchor")
__declspec(noinline) char __fastcall InitConfigAnchor_00418c40(int reserved, GameConfig_00418c30* config) {
    memset(config, 0, 0x34);
    *(int*)(config->bytes + 0x00) = 0x100003;
    *(unsigned short*)(config->bytes + 0x16) = 0x258;
    *(unsigned short*)(config->bytes + 0x18) = 0x258;
    *(int*)(config->bytes + 0x30) |= 0x100;
    config->bytes[0x10] = 2;
    config->bytes[0x21] = 0x50;
    entry_free_004524a1(config);
    return 0;
}
#pragma code_seg()

#pragma code_seg(".text$05context")
int __stdcall ResetContext_00418c30(GameConfig_00418c30** items, int count) {
    int total = 0;
    for (int i = 0; i < count; ++i) {
        GameConfig_00418c30* one = items[i];
        one->bytes[0] = (unsigned char)i;
        total += (int)one->Reset();
        total += one->bytes[2];
    }
    return total;
}
#pragma code_seg()
```

#### 0x00417840 - 33 bytes - `?Reset@Object_00417840@@QAEPAU1@XZ`

`src/unidentified/unassigned_00417840.cpp`

```cpp
#include <string.h>
extern "C" void __cdecl entry_free_004524a1(void* block);

#pragma pack(push, 1)
struct GameConfig_00417840 { unsigned char bytes[0x34]; };
#pragma pack(pop)
char __fastcall GameConfig_00417840_InitDefaults(int reserved, GameConfig_00417840* config);

struct Object_00417840 {
    unsigned char pad_000[0x20];
    unsigned int flags_20;
    GameConfig_00417840 config_24;
    unsigned char pad_058[8];
    __declspec(noinline) Object_00417840* Reset();
};

#pragma code_seg(".text$01reset")
Object_00417840* Object_00417840::Reset() {
    flags_20 &= ~1u;
    GameConfig_00417840_InitDefaults(0, &config_24);
    memset(this, 0, 0x60);
    return this;
}
#pragma code_seg()
```

Probe: `0x00417840      33 bytes  ?Reset@Object_00417840@@QAEPAU1@XZ  EXACT`

Anchors compiled into this cluster (`layout/ltcg/cl_00417840_context.cpp`):

```cpp
// Compiler context only; never selected as recovered game code.
#include <string.h>
#include "../../src/unidentified/unassigned_00417840.cpp"
extern "C" void __cdecl entry_free_004524a1(void* block);

#pragma code_seg(".text$03anchor")
__declspec(noinline) char __fastcall GameConfig_00417840_InitDefaults(
        int reserved, GameConfig_00417840* config) {
    memset(config, 0, 0x34);
    *(int*)(config->bytes + 0x00) = 0x100003;
    *(unsigned short*)(config->bytes + 0x16) = 0x258;
    *(unsigned short*)(config->bytes + 0x18) = 0x258;
    *(int*)(config->bytes + 0x30) |= 0x100;
    config->bytes[0x10] = 2;
    config->bytes[0x1f] = 2;
    config->bytes[0x21] = 0x50;
    entry_free_004524a1(config);
    return 0;
}
#pragma code_seg()

#pragma code_seg(".text$05context")
int __stdcall ResetContext_00417840(Object_00417840** items, int count) {
    int total = 0;
    for (int i = 0; i < count; ++i) {
        Object_00417840* one = items[i];
        one->pad_000[0] = (unsigned char)i;
        total += (int)one->Reset();
        total += one->flags_20;
    }
    return total;
}
#pragma code_seg()
```

#### 0x00412A80 - 17 bytes - `?Resolve@EclOperandSource_00412a80@@QAEHHH@Z`

`src/unidentified/unassigned_00412a80.cpp`

```cpp

struct EclFrame;
int __fastcall ECL_ResolveIntValue_0044ff00(int unused, EclFrame* frame,
                                            int selector, int value);

struct EclOperandSource_00412a80 {
    unsigned char pad_000[0x14D8];
    int* field_14D8;
    __declspec(noinline) int Resolve(int selector, int value);
};

#pragma code_seg(".text$01resolve")
int EclOperandSource_00412a80::Resolve(int selector, int value) {
    int* source = field_14D8;
    return ECL_ResolveIntValue_0044ff00(selector, (EclFrame*)source[1], value, selector);
}
#pragma code_seg()
```

Probe: `0x00412a80      17 bytes  ?Resolve@EclOperandSource_00412a80@@QAEHHH@Z  EXACT`

#### 0x00413B90 - 47 bytes - `?ReleaseCachedResource_00413b90@@YGHXZ`

`src/unidentified/unassigned_00413b90.cpp`

```cpp

extern "C" void __cdecl entry_free_004524a1(void* block);
extern "C" char* data_00491c10;

struct AnimationResource_00413b90 {
    unsigned char pad_000[0x108];
    void* resource_108;
    int entry_count_10c;
    unsigned char pad_114[0x118 - 0x110];
    void* auxiliary_118;
    void* auxiliary_11c;
    void* entries_120;
    __declspec(noinline) void Release();
};

__declspec(noinline) int ReleaseCachedResource_00413b90();

#pragma code_seg(".text$01release")
__declspec(noinline) int ReleaseCachedResource_00413b90() {
    AnimationResource_00413b90** slot =
        (AnimationResource_00413b90**)(data_00491c10 + 0x3AD084);
    AnimationResource_00413b90* record = *slot;
    if (record != 0) {
        record->Release();
        entry_free_004524a1(*slot);
        *slot = 0;
    }
    return 0;
}
#pragma code_seg()
```

Probe: `0x00413b90      47 bytes  ?ReleaseCachedResource_00413b90@@YGHXZ  EXACT`

Anchors compiled into this cluster (`layout/ltcg/cl_00413b90_context.cpp`):

```cpp
// Compiler context only; never selected as recovered game code.
#include "../../src/unidentified/unassigned_00413b90.cpp"

extern "C" void __cdecl opaque_release_004492a0(void* item);

#pragma code_seg(".text$03anchor")
__declspec(noinline) void AnimationResource_00413b90::Release() {
    if (resource_108 == 0) {
        entry_free_004524a1(this);
        return;
    }
    for (int index = 0; index < entry_count_10c; ++index) {
        char* entry = (char*)entries_120 + index * 8;
        if (*(void**)entry != 0) {
            opaque_release_004492a0(*(void**)entry);
            *(void**)entry = 0;
        }
        if (*(void**)(entry + 4) != 0) {
            opaque_release_004492a0(*(void**)(entry + 4));
            *(void**)(entry + 4) = 0;
        }
    }
    if (auxiliary_118 != 0) {
        entry_free_004524a1(auxiliary_118);
        auxiliary_118 = 0;
    }
    if (entries_120 != 0) {
        entry_free_004524a1(entries_120);
        entries_120 = 0;
    }
    entry_free_004524a1(this);
}
#pragma code_seg()

#pragma code_seg(".text$05context")
int __stdcall ReleaseContext_00413b90(int count) {
    int total = 0;
    for (int i = 0; i < count; ++i) {
        total += ReleaseCachedResource_00413b90();
    }
    return total;
}
#pragma code_seg()
```

#### 0x00414550 - 30 bytes - `?DestroySlot_00414550@@YGPAUAnimationSlot_00414550@@PAU1@I@Z`

`src/unidentified/unassigned_00414550.cpp`

```cpp

extern "C" void __cdecl entry_free_004524a1(void* block);

struct AnimationSlot_00414550 {
    unsigned char pad_000[0x40];
    void* field_40;
    void* field_44;
    void* field_48;
    void* field_4c;
    void* field_50;
    __declspec(noinline) void ReleaseRetail();
};

__declspec(noinline) AnimationSlot_00414550* DestroySlot_00414550(
        AnimationSlot_00414550* slot, unsigned int flags);

#pragma code_seg(".text$03destroy")
__declspec(noinline) AnimationSlot_00414550* DestroySlot_00414550(
        AnimationSlot_00414550* slot, unsigned int flags) {
    slot->ReleaseRetail();
    if (flags & 1) entry_free_004524a1(slot);
    return slot;
}
#pragma code_seg()
```

Probe: `0x00414550      30 bytes  ?DestroySlot_00414550@@YGPAUAnimationSlot_00414550@@PAU1@I@Z  EXACT`

Anchors compiled into this cluster (`layout/ltcg/cl_00414550_context.cpp`):

```cpp
// Compiler context only; never selected as recovered game code.
#include "../../src/unidentified/unassigned_00414550.cpp"

extern "C" void __cdecl opaque_release_004492a0(void* item);

#pragma code_seg(".text$01anchor")
__declspec(noinline) void AnimationSlot_00414550::ReleaseRetail() {
    opaque_release_004492a0(field_40);
    field_40 = 0;
    opaque_release_004492a0(field_44);
    field_44 = 0;
    opaque_release_004492a0(field_48);
    field_48 = 0;
    opaque_release_004492a0(field_4c);
    field_4c = 0;
    opaque_release_004492a0(field_50);
    field_50 = 0;
}
#pragma code_seg()

#pragma code_seg(".text$05context")
int __stdcall DestroyContext_00414550(AnimationSlot_00414550** items, int count) {
    int total = 0;
    for (int i = 0; i < count; ++i) {
        AnimationSlot_00414550* one = items[i];
        total += (int)DestroySlot_00414550(one, (unsigned int)i);
    }
    return total;
}
#pragma code_seg()
```

#### 0x00417720 - 10 bytes - `?StopHandle@Entity_00417720@@QAEXXZ`

`src/unidentified/unassigned_00417720.cpp`

```cpp

extern "C" void* __stdcall find_opaque_004491c0(unsigned int id);
extern "C" char* data_00491c10;

struct AnimationNode_00417720 {
    AnimationNode_00417720* object;
    AnimationNode_00417720* next;
    unsigned char pad_008[0x14 - 0x08];
    AnimationNode_00417720* children;
    int children_flagged;
    unsigned char pad_01c[0x304 - 0x1C];
    unsigned short stop_frame;
};

struct AnimationHandle_00417720 {
    unsigned short id;
};

__declspec(noinline) void StopHandleAnchor_00409e50(AnimationHandle_00417720* handle);

struct Entity_00417720 {
    unsigned char pad_000[0x9E14];
    AnimationHandle_00417720 handle;
    __declspec(noinline) void StopHandle();
};

#pragma code_seg(".text$03stop")
void Entity_00417720::StopHandle() {
    StopHandleAnchor_00409e50(&this->handle);
}
#pragma code_seg()
```

Probe: `0x00417720      10 bytes  ?StopHandle@Entity_00417720@@QAEXXZ  EXACT`

Anchors compiled into this cluster (`layout/ltcg/cl_00417720_context.cpp`):

```cpp
// Compiler context only; never selected as recovered game code.
#include "../../src/unidentified/unassigned_00417720.cpp"

#pragma code_seg(".text$01anchor")
__declspec(noinline) void StopHandleAnchor_00409e50(AnimationHandle_00417720* handle) {
    unsigned int id = handle->id;
    AnimationNode_00417720* node = (AnimationNode_00417720*)find_opaque_004491c0(id);
    if (node != 0) {
        node->stop_frame = 1;
        if (!node->children_flagged) {
            for (AnimationNode_00417720* child = node->children; child != 0; child = child->next)
                child->object->stop_frame = 1;
        }
    }
}
#pragma code_seg()

#pragma code_seg(".text$05context")
int __stdcall StopContext_00417720(Entity_00417720** items, int count) {
    for (int i = 0; i < count; ++i) {
        (*items++)->StopHandle();
    }
    return 0;
}
#pragma code_seg()
```

#### 0x00412E10 - 20 bytes - `?Evaluate@CurveObject_00412e10@@QAEMXZ`

`src/unidentified/unassigned_00412e10.cpp`

```cpp

struct CurveObject_00412e10 {
    unsigned char pad_000[0x28];
    float field_28;
    unsigned char pad_2C[0x34 - 0x2C];
    int field_34;
    int field_38;
    __declspec(noinline) float Evaluate();
};

float __stdcall EvaluateCurveAnchor_0044c350(unsigned int op, float first, float second);

#pragma code_seg(".text$01evaluate")
float CurveObject_00412e10::Evaluate() {
    return EvaluateCurveAnchor_0044c350(field_38, field_28, (float)field_34);
}
#pragma code_seg()
```

Probe: `0x00412e10      20 bytes  ?Evaluate@CurveObject_00412e10@@QAEMXZ  EXACT`

Anchors compiled into this cluster (`layout/ltcg/cl_00412e10_context.cpp`):

```cpp
// Compiler context only; never selected as recovered game code.
#include "../../src/unidentified/unassigned_00412e10.cpp"

#pragma code_seg(".text$03anchor")
__declspec(noinline) float __stdcall EvaluateCurveAnchor_0044c350(unsigned int op, float first,
                                                                 float second) {
    switch (op) {
    case 1: return first + second;
    case 2: return first - second;
    case 3: return first * second;
    case 4: return first / second;
    case 5: return second - first;
    case 6: return second / first;
    case 7: return (first + second) * 0.5f;
    case 8: return (first - second) * 0.5f;
    case 9: return first > second ? first : second;
    case 10: return first < second ? first : second;
    case 11: return -first;
    case 12: return -second;
    case 13: return first * first + second * second;
    case 14: return first * second - 1.0f;
    case 15: return 1.0f - first * second;
    case 16: return first + second * 2.0f;
    default: return 0.0f;
    }
}
#pragma code_seg()

#pragma code_seg(".text$05context")
float __stdcall EvaluateContext_00412e10(CurveObject_00412e10** items, int count) {
    float total = 0.0f;
    while (count--) {
        total += (*items++)->Evaluate();
    }
    return total;
}
#pragma code_seg()
```

#### 0x00419930 - 35 bytes - `?FindKey_00419930@@YGHPAUSearchRecord_00419930@@HH@Z`

`src/unidentified/unassigned_00419930.cpp`

```cpp

struct SearchRecord_00419930 {
    int value;
    int key;
};
int __declspec(noinline) FindKey_00419930(SearchRecord_00419930* table, int count, int key);

#pragma code_seg(".text$01find")
__declspec(noinline) int FindKey_00419930(SearchRecord_00419930* table, int count, int key) {
    for (int i = 0; i < count; ++i) {
        if (table[i].key == key) return table[i].value;
    }
    return 0;
}
#pragma code_seg()
```

Probe: `0x00419930      35 bytes  ?FindKey_00419930@@YGHPAUSearchRecord_00419930@@HH@Z  EXACT`

#### 0x004051E0 - 10 bytes - `?AllocateBlock_004051e0@@YGPAXI@Z`

`src/unidentified/unassigned_004051e0.cpp`

```cpp

extern "C" void* __cdecl entry_malloc_00452706(unsigned int size);

__declspec(noinline) void* AllocateBlock_004051e0(unsigned int size);

#pragma code_seg(".text$01alloc")
__declspec(noinline) void* AllocateBlock_004051e0(unsigned int size) {
    return entry_malloc_00452706(size);
}
#pragma code_seg()
```

Probe: `0x004051e0      10 bytes  ?AllocateBlock_004051e0@@YGPAXI@Z  EXACT`

#### 0x004051D0 - 7 bytes - `?RetireBlock_004051d0@@YGHPAX@Z`

`src/unidentified/unassigned_004051d0.cpp`

```cpp

extern "C" int __stdcall target_0043ee30(void* object);

__declspec(noinline) int RetireBlock_004051d0(void* object);

#pragma code_seg(".text$01retire")
__declspec(noinline) int RetireBlock_004051d0(void* object) {
    return target_0043ee30(object);
}
#pragma code_seg()
```

Probe: `0x004051d0      7 bytes  ?RetireBlock_004051d0@@YGHPAX@Z  EXACT`

#### 0x00402040 - 8 bytes - `?FreeBlock_00402040@@YGXPAX@Z`

`src/unidentified/unassigned_00402040.cpp`

```cpp
extern "C" void __cdecl entry_free_00452422(void* block);

__declspec(noinline) void FreeBlock_00402040(void* block);

#pragma code_seg(".text$01free")
__declspec(noinline) void FreeBlock_00402040(void* block) {
    entry_free_00452422(block);
}
#pragma code_seg()
```

Probe: `0x00402040      8 bytes  ?FreeBlock_00402040@@YGXPAX@Z  EXACT`

#### 0x0040CE50 - 17 bytes - `?SetMax@Options_0040ce50@@QAEXH@Z`

`src/unidentified/unassigned_0040ce50.cpp`

```cpp

struct Options_0040ce50 {
    unsigned char pad_000[0x9EC0];
    int max_value;
    __declspec(noinline) void SetMax(int value);
};

#pragma code_seg(".text$01setmax")
void Options_0040ce50::SetMax(int value) {
    if (value > 99) value = 99;
    max_value = value;
}
#pragma code_seg()
```

Probe: `0x0040ce50      17 bytes  ?SetMax@Options_0040ce50@@QAEXH@Z  EXACT`

#### 0x0040C440 - 24 bytes - `?StopHandleAndClear@Entity_0040c440@@QAEXXZ`

`src/unidentified/unassigned_0040c440.cpp`

```cpp

extern "C" void* __stdcall find_opaque_004491c0(unsigned int id);
extern "C" char* data_00491c10;

struct AnimationNode_0040c440 {
    AnimationNode_0040c440* object;
    AnimationNode_0040c440* next;
    unsigned char pad_008[0x14 - 0x08];
    AnimationNode_0040c440* children;
    int children_flagged;
    unsigned char pad_01c[0x304 - 0x1C];
    unsigned short stop_frame;
};

struct AnimationHandle_0040c440 { unsigned short id; };

__declspec(noinline) void StopHandleAnchor_00409e50(AnimationHandle_0040c440* handle);

struct Entity_0040c440 {
    unsigned char pad_000[0x89A4];
    unsigned int handle;
    __declspec(noinline) void StopHandleAndClear();
};

#pragma code_seg(".text$03stop")
void Entity_0040c440::StopHandleAndClear() {
    AnimationHandle_0040c440* handle = (AnimationHandle_0040c440*)&this->handle;
    StopHandleAnchor_00409e50(handle);
    this->handle = 0;
}
#pragma code_seg()
```

Probe: `0x0040c440      24 bytes  ?StopHandleAndClear@Entity_0040c440@@QAEXXZ  EXACT`

Anchors compiled into this cluster (`layout/ltcg/cl_0040c440_context.cpp`):

```cpp
// Compiler context only; never selected as recovered game code.
#include "../../src/unidentified/unassigned_0040c440.cpp"

#pragma code_seg(".text$01anchor")
__declspec(noinline) void StopHandleAnchor_00409e50(AnimationHandle_0040c440* handle) {
    unsigned int id = handle->id;
    AnimationNode_0040c440* node = (AnimationNode_0040c440*)find_opaque_004491c0(id);
    if (node != 0) {
        node->stop_frame = 1;
        if (!node->children_flagged) {
            for (AnimationNode_0040c440* child = node->children; child != 0; child = child->next)
                child->object->stop_frame = 1;
        }
    }
}
#pragma code_seg()

#pragma code_seg(".text$05context")
int __stdcall StopContext_0040c440(Entity_0040c440** items, int count) {
    for (int i = 0; i < count; ++i) {
        (*items++)->StopHandleAndClear();
    }
    return 0;
}
#pragma code_seg()
```

#### 0x00402020 - 30 bytes - `?ReleaseOwned@Holder_00402020@@QAEXXZ`

`src/unidentified/unassigned_00402020.cpp`

```cpp
extern "C" void __cdecl entry_free_00452422(void* block);

struct Holder_00402020 {
    unsigned char pad_000[0x358];
    void* field_358;
    __declspec(noinline) void ReleaseOwned();
};

#pragma code_seg(".text$01release")
void Holder_00402020::ReleaseOwned() {
    if (field_358) entry_free_00452422(field_358);
    field_358 = 0;
}
#pragma code_seg()
```

Probe: `0x00402020      30 bytes  ?ReleaseOwned@Holder_00402020@@QAEXXZ  EXACT`

#### 0x0040DC70 - 12 bytes - `?Run@Outer_0040dc70@@QAEHXZ`

`src/unidentified/unassigned_0040dc70.cpp`

```cpp

extern "C" int __stdcall target_0040dc80(void* object);

struct Sub_0040dc70 { unsigned char bytes[0x100]; };

struct Outer_0040dc70 {
    unsigned char pad_000[0x103C];
    Sub_0040dc70 sub;
    __declspec(noinline) int Run();
};

#pragma code_seg(".text$01run")
int Outer_0040dc70::Run() {
    return target_0040dc80(&this->sub);
}
#pragma code_seg()
```

Probe: `0x0040dc70      12 bytes  ?Run@Outer_0040dc70@@QAEHXZ  EXACT`

#### 0x004088A0 - 11 bytes - `?SlotIndex_004088a0@@YGHHH@Z`

`src/unidentified/unassigned_004088a0.cpp`

```cpp

struct Slot_004088a0 { unsigned char bytes[8]; };

__declspec(noinline) int SlotIndex_004088a0(int index, int base);

#pragma code_seg(".text$01index")
__declspec(noinline) int SlotIndex_004088a0(int index, int base) {
    return index * 0x437C + base + 8;
}
#pragma code_seg()
```

Probe: `0x004088a0      11 bytes  ?SlotIndex_004088a0@@YGHHH@Z  EXACT`

#### 0x0040C670 - 11 bytes - `?Resolve_0040c670@@YGHHPAUEclSource_0040c670@@H@Z`

`src/unidentified/unassigned_0040c670.cpp`

```cpp

struct EclFrame;

int __fastcall ECL_ResolveIntValue_0044ff00(int unused, EclFrame* frame, int selector, int value);

struct EclSource_0040c670 { unsigned char pad_000[4]; void* field_004; };

__declspec(noinline) int Resolve_0040c670(int selector, EclSource_0040c670* source, int value);

#pragma code_seg(".text$01resolve")
__declspec(noinline) int Resolve_0040c670(int selector, EclSource_0040c670* source, int value) {
    return ECL_ResolveIntValue_0044ff00(selector, (EclFrame*)source->field_004, selector, value);
}
#pragma code_seg()
```

Probe: `0x0040c670      11 bytes  ?Resolve_0040c670@@YGHHPAUEclSource_0040c670@@H@Z  EXACT`

#### 0x0040C5F0 - 10 bytes - `?Resolve@OperandSource_0040c5f0@@QAEHH@Z`

`src/unidentified/unassigned_0040c5f0.cpp`

```cpp

struct EclFrame;

int __fastcall resolve_operand_0044fdb0(int unused, EclFrame* frame, int selector);

struct OperandSource_0040c5f0 {
    unsigned char pad_000[4];
    void* field_004;
    __declspec(noinline) int Resolve(int value);
};

#pragma code_seg(".text$01resolve")
int OperandSource_0040c5f0::Resolve(int value) {
    return resolve_operand_0044fdb0((int)this, (EclFrame*)field_004, value);
}
#pragma code_seg()
```

Probe: `0x0040c5f0      10 bytes  ?Resolve@OperandSource_0040c5f0@@QAEHH@Z  EXACT`

#### 0x0040E760 - 11 bytes - `?Run@Outer_0040e760@@QAEXXZ`

`src/unidentified/unassigned_0040e760.cpp`

```cpp

struct Inner_0040e760 {
    unsigned char bytes[0x100];
    __declspec(noinline) void Run();
};

struct Outer_0040e760 {
    unsigned char pad_000[0x103C];
    Inner_0040e760 inner;
    __declspec(noinline) void Run();
};

#pragma code_seg(".text$01run")
void Outer_0040e760::Run() {
    inner.Run();
}
#pragma code_seg()
```

Probe: `0x0040e760      11 bytes  ?Run@Outer_0040e760@@QAEXXZ  EXACT`

Anchors compiled into this cluster (`layout/ltcg/cl_0040e760_context.cpp`):

```cpp
// Compiler context only; never selected as recovered game code.
#include "../../src/unidentified/unassigned_0040e760.cpp"

#pragma code_seg(".text$03anchor")
__declspec(noinline) void Inner_0040e760::Run() {
    unsigned char* bytes = this->bytes;
    for (int i = 0; i < 0x100; ++i) {
        bytes[i] = (unsigned char)i;
    }
    int sum = 0;
    sum += bytes[0x14];
    sum += bytes[0x15];
    bytes[0x20] = (unsigned char)sum;
}
#pragma code_seg()

#pragma code_seg(".text$05context")
int __stdcall RunContext_0040e760(Outer_0040e760** items, int count) {
    for (int i = 0; i < count; ++i) {
        (*items++)->Run();
    }
    return 0;
}
#pragma code_seg()
```

#### 0x00409E10 - 12 bytes - `?Evaluate@Vector_00409e10@@QAEHXZ`

`src/unidentified/unassigned_00409e10.cpp`

```cpp

struct Vector_00409e10 {
    unsigned char pad_000[0x28];
    int field_28;
    int field_2C;
    __declspec(noinline) int Evaluate();
};

#pragma code_seg(".text$01evaluate")
int Vector_00409e10::Evaluate() {
    return field_28 * 3 + field_2C;
}
#pragma code_seg()
```

Probe: `0x00409e10      12 bytes  ?Evaluate@Vector_00409e10@@QAEHXZ  EXACT`

#### 0x0040C860 - 36 bytes - `?ReleaseBlock@ResourceOwner_0040c860@@QAEXXZ`

`src/unidentified/unassigned_0040c860.cpp`

```cpp
extern "C" void __cdecl entry_free_00452422(void* block);

struct ResourceOwner_0040c860 {
    void* vtable;
    unsigned char pad_004[0x8C - 0x04];
    void* block_8C;
    __declspec(noinline) void ReleaseBlock();
};

#pragma code_seg(".text$01release")
void ResourceOwner_0040c860::ReleaseBlock() {
    vtable = (void*)0x46D0F0;
    if (block_8C != 0) {
        entry_free_00452422(block_8C);
        block_8C = 0;
    }
}
#pragma code_seg()
```

Probe: `0x0040c860      36 bytes  ?ReleaseBlock@ResourceOwner_0040c860@@QAEXXZ  EXACT`

#### 0x00404CF0 - 20 bytes - `?Evaluate@CurveObject_00404cf0@@QAEMXZ`

`src/unidentified/unassigned_00404cf0.cpp`

```cpp

struct CurveObject_00404cf0 {
    unsigned char pad_000[0x38];
    float field_38;
    unsigned char pad_3C[0x44 - 0x3C];
    int field_44;
    int field_48;
    __declspec(noinline) float Evaluate();
};
float __stdcall EvaluateCurveAnchor_0044c350(unsigned int op, float first, float second);

#pragma code_seg(".text$01evaluate")
float CurveObject_00404cf0::Evaluate() {
    return EvaluateCurveAnchor_0044c350(field_48, field_38, (float)field_44);
}
#pragma code_seg()
```

Probe: `0x00404cf0      20 bytes  ?Evaluate@CurveObject_00404cf0@@QAEMXZ  EXACT`

Anchors compiled into this cluster (`layout/ltcg/cl_00404cf0_context.cpp`):

```cpp
// Compiler context only; never selected as recovered game code.
#include "../../src/unidentified/unassigned_00404cf0.cpp"

#pragma code_seg(".text$03anchor")
__declspec(noinline) float __stdcall EvaluateCurveAnchor_0044c350(unsigned int op, float first,
                                                                 float second) {
    switch (op) {
    case 1: return first + second;
    case 2: return first - second;
    case 3: return first * second;
    case 4: return first / second;
    case 5: return second - first;
    case 6: return second / first;
    case 7: return (first + second) * 0.5f;
    case 8: return (first - second) * 0.5f;
    case 9: return first > second ? first : second;
    case 10: return first < second ? first : second;
    case 11: return -first;
    case 12: return -second;
    case 13: return first * first + second * second;
    case 14: return first * second - 1.0f;
    case 15: return 1.0f - first * second;
    case 16: return first + second * 2.0f;
    default: return 0.0f;
    }
}
#pragma code_seg()

#pragma code_seg(".text$05context")
float __stdcall EvaluateContext_00404cf0(CurveObject_00404cf0** items, int count) {
    float total = 0.0f;
    while (count--) {
        total += (*items++)->Evaluate();
    }
    return total;
}
#pragma code_seg()
```

#### 0x00404D10 - 26 bytes - `?Evaluate@CurveObject_00404d10@@QAEMXZ`

`src/unidentified/unassigned_00404d10.cpp`

```cpp

struct CurveObject_00404d10 {
    unsigned char pad_000[0x78];
    float field_78;
    unsigned char pad_f[0x84 - 0x7C];
    int field_84;
    int field_88;
    __declspec(noinline) float Evaluate();
};
float __stdcall EvaluateCurveAnchor_0044c350(unsigned int op, float first, float second);

#pragma code_seg(".text$01evaluate")
float CurveObject_00404d10::Evaluate() {
    return EvaluateCurveAnchor_0044c350(field_88, field_78, (float)field_84);
}
#pragma code_seg()
```

Probe: `0x00404d10      26 bytes  ?Evaluate@CurveObject_00404d10@@QAEMXZ  EXACT`

Anchors compiled into this cluster (`layout/ltcg/cl_00404d10_context.cpp`):

```cpp
// Compiler context only; never selected as recovered game code.
#include "../../src/unidentified/unassigned_00404d10.cpp"

#pragma code_seg(".text$03anchor")
__declspec(noinline) float __stdcall EvaluateCurveAnchor_0044c350(unsigned int op, float first,
                                                                 float second) {
    switch (op) {
    case 1: return first + second;
    case 2: return first - second;
    case 3: return first * second;
    case 4: return first / second;
    case 5: return second - first;
    case 6: return second / first;
    case 7: return (first + second) * 0.5f;
    case 8: return (first - second) * 0.5f;
    case 9: return first > second ? first : second;
    case 10: return first < second ? first : second;
    case 11: return -first;
    case 12: return -second;
    case 13: return first * first + second * second;
    case 14: return first * second - 1.0f;
    case 15: return 1.0f - first * second;
    case 16: return first + second * 2.0f;
    default: return 0.0f;
    }
}
#pragma code_seg()

#pragma code_seg(".text$05context")
float __stdcall EvaluateContext_00404d10(CurveObject_00404d10** items, int count) {
    float total = 0.0f;
    while (count--) {
        total += (*items++)->Evaluate();
    }
    return total;
}
#pragma code_seg()
```

#### 0x00405F40 - 47 bytes - `?ReleaseCachedResource_00405f40@@YGHXZ`

`src/unidentified/unassigned_00405f40.cpp`

```cpp

extern "C" void __cdecl entry_free_004524a1(void* block);
extern "C" char* data_00491c10;

struct AnimationResource_00405f40 {
    unsigned char pad_000[0x108];
    void* resource_108;
    int entry_count_10c;
    unsigned char pad_114[0x118 - 0x110];
    void* auxiliary_118;
    void* auxiliary_11c;
    void* entries_120;
    __declspec(noinline) void Release();
};

__declspec(noinline) int ReleaseCachedResource_00405f40();

#pragma code_seg(".text$01release")
__declspec(noinline) int ReleaseCachedResource_00405f40() {
    AnimationResource_00405f40** slot =
        (AnimationResource_00405f40**)(data_00491c10 + 0x3AD088);
    AnimationResource_00405f40* record = *slot;
    if (record != 0) {
        record->Release();
        entry_free_004524a1(*slot);
        *slot = 0;
    }
    return 0;
}
#pragma code_seg()
```

Probe: `0x00405f40      47 bytes  ?ReleaseCachedResource_00405f40@@YGHXZ  EXACT`

Anchors compiled into this cluster (`layout/ltcg/cl_00405f40_context.cpp`):

```cpp
// Compiler context only; never selected as recovered game code.
#include "../../src/unidentified/unassigned_00405f40.cpp"

extern "C" void __cdecl opaque_release_004492a0(void* item);
extern "C" char* data_00491c10;

#pragma code_seg(".text$03anchor")
__declspec(noinline) void AnimationResource_00405f40::Release() {
    if (resource_108 == 0) {
        entry_free_004524a1(this);
        return;
    }
    for (int index = 0; index < entry_count_10c; ++index) {
        char* entry = (char*)entries_120 + index * 8;
        if (*(void**)entry != 0) {
            opaque_release_004492a0(*(void**)entry);
            *(void**)entry = 0;
        }
        if (*(void**)(entry + 4) != 0) {
            opaque_release_004492a0(*(void**)(entry + 4));
            *(void**)(entry + 4) = 0;
        }
    }
    if (auxiliary_118 != 0) {
        entry_free_004524a1(auxiliary_118);
        auxiliary_118 = 0;
    }
    if (entries_120 != 0) {
        entry_free_004524a1(entries_120);
        entries_120 = 0;
    }
    entry_free_004524a1(this);
}
#pragma code_seg()

#pragma code_seg(".text$05context")
int __stdcall ReleaseContext_00405f40(int count) {
    int total = 0;
    for (int i = 0; i < count; ++i) {
        total += ReleaseCachedResource_00405f40();
    }
    return total;
}
#pragma code_seg()
```

## Dropped (attempted)

| address | bytes | status |
| --- | ---: | --- |
| `0x0041BE40` | 46 | the anchor earns retail's `(EAX body, ESI owner, stack argument)`, but the region's own scheduling does not come back: the pass keeps the pool and the argument in EAX and pushes EAX, then loads the body into EAX after the push, where retail keeps the pool in ECX, loads the body into EAX first and pushes EDX. Emitted 45 bytes against 46, 36 bytes differ, first at `+0`. |
| `0x0040C780` | 47 | **2 bytes.** The receiver arrives in EAX where retail has ECX: `8b b1 34 10 00 00` (retail, `mov esi,[ecx+0x1034]`) against `8b b0 34 10 00 00`, and the vtable stamp `c7 01` against `c7 00`. Six context shapes (member caller, member loop, table walker, nested loop, single-argument caller) all chose EAX; this is the allocator tie-break class. |
| `0x004014D0` | 32 | the region holds a **26-byte function plus six `INT3` alignment bytes** (`0x4014EA`..`0x4014EF`), so no C++ body can fill it. The function itself (`zero +0x896C/+0x8970, inc [eax+0x8990], return 1`) is an EAX-receiver leaf that the driver family would land if the region were reclassified or its extent reduced. |
| `0x00401DC0` | 29 | not modelled: `mov esi,edx; call 0x401DE0; mov edx,[esp+4]; mov eax,esi; mov ecx,edi; mov [esi+0x308],edi; call 0x43E5A0; ret 4` needs three callee conventions at once (0x401DE0's EDX, 0x43E5A0's ECX/EAX) plus one stack argument; two compiled anchors in one layout is a later wave's job. |
| `0x00409190` | 46 | the dispatch anchor for `0x4451C0` cannot be made to enter on retail's pair: every body shape and both declaration orders earned `(EAX entity-as-param1, EDX manager)` where retail has `(ECX manager, EAX entity)`. Emitted `f6 80 8c 37 00 00 01 74 13 8d 50 10 e8 ... 8d 90 bc 03 00 00 e8 ... b8 01 00 00 00 c3` against retail `f6 86 ... 74 1f 8b 0d 10 1c 49 00 8d 46 10 e8 ... 8b 0d 10 1c 49 00 8d 86 bc 03 00 00 e8 ... b8 01 00 00 00 c3` - 13 bytes differ, first at `+1` (the receiver stays in EAX instead of ESI, and the entity address lands in EDX instead of EAX). The `0x4451C0` register pair (ECX manager, EAX entity) is set by the dispatcher's own ten case bodies in `anm_batch_flush_00442f50`; an anchor called from one site does not reproduce it. |
| `0x0040ADA0` | 25 | **already landed by a sibling during this wave** as `_Publish_0040ada0@8` in `src/unidentified/publish_index_0040ada0.cpp`; the model here also probes EXACT but was not registered (no duplicate cluster for one region). |

## Transferable findings

1. **An anchor's register set is decided by usage, not by the declaration order.**
   Permuting the declaration order of a three-parameter anchor reproduced the same
   register-to-role mapping in every case; what changes the mapping is (a) which
   parameter is live across a call, (b) whether a parameter dies before the first
   call, and (c) whether a parameter is a by-value aggregate.
2. **A one-dword struct parameter is the way to pin an argument to the stack**
   when a register parameter would otherwise be promoted.
3. **`__fastcall` declarations plus a `relative_code` binding land every callee
   whose convention is ECX/EDX/stack**, so most of the "needs an anchor" leads are
   really "needs the right declaration".
4. **The same anchor is reusable across clusters**: the `0x409E50` handle anchor
   serves `0x417720` and `0x40C440`; the `0x418C40` config anchor serves
   `0x418C30` and `0x417840`; the `0x44C350` curve anchor serves `0x412E10`,
   `0x404CF0` and `0x404D10`; the `0x447810` release anchor serves `0x413B90`
   and `0x405F40`. Each cluster carries its own copy in its driver; nothing is
   shared through the maintained manifest beyond the region records.
5. **A `jle`/`jbe` mismatch means a signed/unsigned model error**, not an
   allocator residual: `0x40CE50` was one byte off until `unsigned int value`
   became `int value`.
6. **Regions that end in `INT3` inside their declared extent cannot be landed** by
   any C++ body (`0x4014D0`); check the extent before modelling.

## Files

* 24 model sources under `src/unidentified/`, one per region.
* 24 layouts `layout/ltcg/cl_<addr>.json` with their `cl_<addr>_context.cpp`
  drivers; the drivers hold the ABI anchors and the synthetic callers.
* `matching2/msvc/regions.json` gained 24 `semantic` records and 24
  `ltcg_clusters` entries (539 entries when this note was written).
* No file outside these was touched; no manifest field was hand-edited.
