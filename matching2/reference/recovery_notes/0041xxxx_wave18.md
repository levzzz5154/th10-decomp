# 0x0041xxxx block - wave 18 sweep: 93 of 124 small regions landed

2026-09-19, agent `VeinBlock41`. Block `0x00412300..0x0041FF50`, 124 asm regions
of at most 64 bytes whose manifest `owner` is null or differs from their address,
2,183 bytes in total. **93 landed EXACT (1,224 bytes, 56%)**, 31 dropped (959 bytes).

All 93 were promoted with
`matching2/tools/waves/promote_scratch.py --scratch /tmp/VeinBlock41/msvc --address 0x... --apply`
(93 promotions, 0 failures), so the maintained manifest carries each record and, for the
cluster landings, its layout and driver. Re-probed afterwards against the maintained tree:

```text
python3 matching2/tools/matching/probe.py <93 sources> --project matching2/msvc
93 region lines, every one EXACT; final line "EXACT"
```

No layout that was not EXACT was left registered: the four non-exact clusters
(`cl_00412e60`, `cl_004187f0`, `cl_0041f780`, `cl_0041fd90`) were unregistered from the
scratch copy and their sources restored to the retail assembly, as were the five
non-exact plain regions (`0x00413050`, `0x00417660`, `0x00418A50`, `0x004177c0`,
`0x004177e0`) and `0x00413B50`.

## What the block turned out to be

Two families dominate, and both need the native-LTCG cluster path because the
first parameter arrives in EAX / the receiver register is chosen by the
whole-program pass:

* **Field accessors and flag helpers** on a handful of large game objects - load a
  float/int at a fixed offset, test or set one bit, mask a word with an argument.
  The proven `layout/ltcg/accessor_*.json` template (member with
  `__declspec(noinline)`, `#pragma code_seg`, an array-walking synthetic caller)
  landed 60 of these unchanged, with the driver only varied for float-returning,
  store-shaped and argument-taking members.
* **Scalar deleting destructors / release wrappers** - `push esi`, call the
  object-specific destroy entry, free on the low bit of the stack flag. The
  existing `destroy_owned_*` layouts were the template; the new ones are
  `layout/ltcg/cl_004148c0.json`, `cl_00418170.json`, `cl_004190e0.json`,
  `cl_0041af90.json`, `cl_0041c2f0.json`, `cl_0041fd50.json` (deleting) and
  `cl_00419100.json`, `cl_0041c310.json`, `cl_0041fd70.json` (release).
* The rest are one-off leaves: pointer offsets, doubly-linked list unlink,
  vector add / dot / scale, an atan2 pair, a `rep stosd` block clear, a
  branchless single-bit assignment, a do-while virtual dispatch.

A plain translation unit was enough whenever the entry registers were empty or
just ECX, which is 21 of the landings (the empty `ret` leaves, `fabs`, the RNG
scale, the thiscall list walk, the `rep stosd` block wrapper).

## Landings (93)

| address | bytes | symbol | probe |
| --- | ---: | --- | --- |
| `0x00412790` | 12 | `?SetRecord_00412790@@YGXIHPAX@Z` | EXACT |
| `0x00412EA0` | 8 | `?LoadValue@ObjectAccessor_00412ea0@@QBEHXZ` | EXACT |
| `0x00412EB0` | 9 | `?LoadValue@ObjectAccessor_00412eb0@@QBEMXZ` | EXACT |
| `0x00412EC0` | 8 | `?LoadValue@ObjectAccessor_00412ec0@@QBEMXZ` | EXACT |
| `0x00412EF0` | 25 | `?DistanceSquared@Vector2_00412ef0@@QBEMPBU1@@Z` | EXACT |
| `0x00412F30` | 4 | `?LoadValue@ObjectAccessor_00412f30@@QBEMXZ` | EXACT |
| `0x00412F40` | 4 | `?LoadValue@ObjectAccessor_00412f40@@QBEMXZ` | EXACT |
| `0x00412F50` | 5 | `?SetFlag@ObjectAccessor_00412f50@@QAEXXZ` | EXACT |
| `0x00412F60` | 7 | `?LoadFlag@ObjectAccessor_00412f60@@QBEIXZ` | EXACT |
| `0x00412F80` | 4 | `?LoadValue@ObjectAccessor_00412f80@@QBEMXZ` | EXACT |
| `0x00412F90` | 4 | `?LoadValue@ObjectAccessor_00412f90@@QBEMXZ` | EXACT |
| `0x00412FA0` | 5 | `?ClearFlag@ObjectAccessor_00412fa0@@QAEXXZ` | EXACT |
| `0x00412FB0` | 7 | `?LoadValue@ObjectAccessor_00412fb0@@QBEMXZ` | EXACT |
| `0x00412FC0` | 7 | `?LoadValue@ObjectAccessor_00412fc0@@QBEMXZ` | EXACT |
| `0x00412FD0` | 4 | `?LoadValue@ObjectAccessor_00412fd0@@QBEMXZ` | EXACT |
| `0x00412FE0` | 1 | `_asm_unassigned_00412fe0` | EXACT |
| `0x004130B0` | 7 | `_asm_unassigned_004130b0` | EXACT |
| `0x004130C0` | 4 | `?Offset_004130c0@@YGPADPAUObjectAccessor_004130c0@@@Z` | EXACT |
| `0x004130F0` | 4 | `?LoadValue@ObjectAccessor_004130f0@@QBEMXZ` | EXACT |
| `0x00413110` | 3 | `?LoadValue@ObjectAccessor_00413110@@QBEMXZ` | EXACT |
| `0x00413120` | 20 | `?Assign@ObjectAccessor_00413120@@QAEXABUTriple_00413120@@@Z` | EXACT |
| `0x00413190` | 14 | `?ClearBlock_00413190@@YGXPAX@Z` | EXACT |
| `0x004131A0` | 10 | `?LoadFlag@ObjectAccessor_004131a0@@QBEIXZ` | EXACT |
| `0x004131B0` | 1 | `_asm_unassigned_004131b0` | EXACT |
| `0x004131C0` | 37 | `?Remove@Node_004131c0@@QAEXXZ` | EXACT |
| `0x00413250` | 31 | `?Scale@ObjectAccessor_00413250@@QAEXM@Z` | EXACT |
| `0x00413290` | 12 | `?LoadValue@ObjectAccessor_00413290@@QBEMXZ` | EXACT |
| `0x004132A0` | 25 | `?InitBlock_004132a0@@YGPAUBlock_004132a0@@PAU1@@Z` | EXACT |
| `0x004136B0` | 1 | `_asm_unassigned_004136b0` | EXACT |
| `0x00413740` | 18 | `?SetFlagAndClear@ObjectAccessor_00413740@@QAEXXZ` | EXACT |
| `0x00413760` | 13 | `?LoadFlag@ObjectAccessor_00413760@@QBEIXZ` | EXACT |
| `0x00413770` | 8 | `?SetFlag@ObjectAccessor_00413770@@QAEXXZ` | EXACT |
| `0x00413780` | 13 | `?LoadFlag@ObjectAccessor_00413780@@QBEIXZ` | EXACT |
| `0x004137F0` | 15 | `?LoadFlag@ObjectAccessor_004137f0@@QBEIXZ` | EXACT |
| `0x00413800` | 12 | `?LoadFlag@ObjectAccessor_00413800@@QBEIXZ` | EXACT |
| `0x004148C0` | 27 | `?ReleaseComposite_DeletingDestructor_004148c0@@YGPAXPAUOwnedObject_004148c0@@I@Z` | EXACT |
| `0x004175B0` | 10 | `?LoadFlag@ObjectAccessor_004175b0@@QBEIXZ` | EXACT |
| `0x004175C0` | 5 | `?SetFlag@ObjectAccessor_004175c0@@QAEXXZ` | EXACT |
| `0x00417600` | 10 | `?LoadFlag@ObjectAccessor_00417600@@QBEIXZ` | EXACT |
| `0x00417610` | 7 | `?Mask@ObjectAccessor_00417610@@QBEII@Z` | EXACT |
| `0x00417620` | 7 | `?Mask@ObjectAccessor_00417620@@QBEII@Z` | EXACT |
| `0x00417630` | 6 | `?Offset_00417630@@YGPADPAUObjectAccessor_00417630@@@Z` | EXACT |
| `0x00417650` | 6 | `?Offset_00417650@@YGPADPAUObjectAccessor_00417650@@@Z` | EXACT |
| `0x00417690` | 10 | `?LoadFlag@ObjectAccessor_00417690@@QBEIXZ` | EXACT |
| `0x004176B0` | 1 | `_asm_unassigned_004176b0` | EXACT |
| `0x004176F0` | 8 | `?ClearFlag@ObjectAccessor_004176f0@@QAEXXZ` | EXACT |
| `0x00417700` | 8 | `?SetFlag@ObjectAccessor_00417700@@QAEXXZ` | EXACT |
| `0x00417710` | 13 | `?LoadFlag@ObjectAccessor_00417710@@QBEIXZ` | EXACT |
| `0x00417730` | 10 | `?StoreValue@ObjectAccessor_00417730@@QAENN@Z` | EXACT |
| `0x00417740` | 10 | `?StoreValue@ObjectAccessor_00417740@@QAENN@Z` | EXACT |
| `0x00417750` | 23 | `?Unlink@ObjectAccessor_00417750@@QAEXXZ` | EXACT |
| `0x00418170` | 27 | `?DestroyOwned_DeletingDestructor_00418170@@YGPAXPAUOwnedObject_00418170@@I@Z` | EXACT |
| `0x004187A0` | 31 | `?Reset_004187a0@@YGHPAUObjectAccessor_004187a0@@@Z` | EXACT |
| `0x004189E0` | 15 | `?ClearState@ObjectAccessor_004189e0@@QAEXXZ` | EXACT |
| `0x004189F0` | 7 | `?IncrementCounters@ObjectAccessor_004189f0@@QAEXXZ` | EXACT |
| `0x00418A70` | 31 | `?ClearFlags_00418a70@@YGXPAUObjectAccessor_00418a70@@@Z` | EXACT |
| `0x00418AD0` | 21 | `?SetBit3@ObjectAccessor_00418ad0@@QAEXI@Z` | EXACT |
| `0x00418AF0` | 17 | `?SetBit1@ObjectAccessor_00418af0@@QAEXI@Z` | EXACT |
| `0x00418B10` | 17 | `?SetBit0@ObjectAccessor_00418b10@@QAEXI@Z` | EXACT |
| `0x00418B30` | 9 | `?LoadFlag@ObjectAccessor_00418b30@@QBEIXZ` | EXACT |
| `0x00418B50` | 5 | `?ClearFlag@ObjectAccessor_00418b50@@QAEXXZ` | EXACT |
| `0x00418C10` | 9 | `?ClearCounters@ObjectAccessor_00418c10@@QAEXXZ` | EXACT |
| `0x00418C20` | 1 | `_asm_unassigned_00418c20` | EXACT |
| `0x00418CC0` | 63 | `?Reset_00418cc0@@YGXPAUObjectAccessor_00418cc0@@@Z` | EXACT |
| `0x00418EC0` | 28 | `?SetFlags_00418ec0@@YGXPAUObjectAccessor_00418ec0@@@Z` | EXACT |
| `0x004190E0` | 27 | `?DestroyOwned_DeletingDestructor_004190e0@@YGPAXPAUOwnedObject_004190e0@@I@Z` | EXACT |
| `0x00419100` | 18 | `?ReleaseOwned_00419100@@YGXPAUOwnedObject_00419100@@@Z` | EXACT |
| `0x0041AAD0` | 39 | `?RetireCounts@ObjectAccessor_0041aad0@@QAEXXZ` | EXACT |
| `0x0041AB00` | 15 | `?LoadValue@ObjectAccessor_0041ab00@@QBEHXZ` | EXACT |
| `0x0041AC40` | 50 | `?Reset_0041ac40@@YGXPAUObjectAccessor_0041ac40@@@Z` | EXACT |
| `0x0041AC90` | 1 | `_asm_unassigned_0041ac90` | EXACT |
| `0x0041AF90` | 27 | `?DestroyOwned_DeletingDestructor_0041af90@@YGPAXPAUOwnedObject_0041af90@@I@Z` | EXACT |
| `0x0041BE70` | 8 | `?LoadValue@ObjectAccessor_0041be70@@QBEHXZ` | EXACT |
| `0x0041BED0` | 1 | `_asm_unassigned_0041bed0` | EXACT |
| `0x0041BEF0` | 1 | `_asm_unassigned_0041bef0` | EXACT |
| `0x0041BF90` | 1 | `_asm_unassigned_0041bf90` | EXACT |
| `0x0041BFA0` | 1 | `_asm_unassigned_0041bfa0` | EXACT |
| `0x0041BFB0` | 1 | `_asm_unassigned_0041bfb0` | EXACT |
| `0x0041BFC0` | 1 | `_asm_unassigned_0041bfc0` | EXACT |
| `0x0041BFD0` | 1 | `_asm_unassigned_0041bfd0` | EXACT |
| `0x0041BFE0` | 1 | `_asm_unassigned_0041bfe0` | EXACT |
| `0x0041C020` | 1 | `_asm_unassigned_0041c020` | EXACT |
| `0x0041C2F0` | 27 | `?ScoreExtendedObject_Destroy_DeletingDestructor_0041c2f0@@YGPAXPAUOwnedObject_0041c2f0@@I@Z` | EXACT |
| `0x0041C310` | 18 | `?ReleaseOwned_0041c310@@YGXPAUOwnedObject_0041c310@@@Z` | EXACT |
| `0x0041C450` | 43 | `?Process_0041c450@@YGHPAUObjectAccessor_0041c450@@@Z` | EXACT |
| `0x0041F760` | 25 | `?DistanceSquared@Vector2_0041f760@@QBEMPBU1@@Z` | EXACT |
| `0x0041F820` | 19 | `?UpdateFlag@ObjectAccessor_0041f820@@QAEXXZ` | EXACT |
| `0x0041F840` | 1 | `_asm_unassigned_0041f840` | EXACT |
| `0x0041FD50` | 27 | `?DestroyOwned_DeletingDestructor_0041fd50@@YGPAXPAUOwnedObject_0041fd50@@I@Z` | EXACT |
| `0x0041FD70` | 18 | `?ReleaseOwned_0041fd70@@YGXPAUOwnedObject_0041fd70@@@Z` | EXACT |
| `0x0041FF00` | 34 | `?Mark_0041ff00@@YGXPAUObjectAccessor_0041ff00@@@Z` | EXACT |
| `0x0041FF40` | 13 | `?LoadFlag@ObjectAccessor_0041ff40@@QBEIXZ` | EXACT |
| `0x0041FF50` | 1 | `_asm_unassigned_0041ff50` | EXACT |

### Source text

#### 0x00412790 - 12 bytes - `?SetRecord_00412790@@YGXIHPAX@Z`

`src/unidentified/unassigned_00412790.cpp`

```cpp
// 0x00412790: store a value into the indexed sixteen-byte record
// The register convention below is only reachable from a native LTCG link,
// so this region is compiled as a cluster.

__declspec(noinline) void SetRecord_00412790(unsigned int value, int index, void* base);
#pragma code_seg(".text$01accessor")
void SetRecord_00412790(unsigned int value, int index, void* base) {
    *(unsigned int*)((char*)base + (index + 0x24A) * 16) = value;
}
#pragma code_seg()
```

#### 0x00412EA0 - 8 bytes - `?LoadValue@ObjectAccessor_00412ea0@@QBEHXZ`

`src/unidentified/unassigned_00412ea0.cpp`

```cpp
// 0x00412EA0: load the sign-extended object field at +0x38A.
// The object pointer arrives in EAX, which only a native LTCG link chooses, so
// this region is compiled as a cluster.

struct ObjectAccessor_00412ea0 {
    unsigned char pad_000[0x38A];
    short field_38A;
    __declspec(noinline) int LoadValue() const;
};

#pragma code_seg(".text$01accessor")
int ObjectAccessor_00412ea0::LoadValue() const {
    return field_38A;
}
#pragma code_seg()
```

#### 0x00412EB0 - 9 bytes - `?LoadValue@ObjectAccessor_00412eb0@@QBEMXZ`

`src/unidentified/unassigned_00412eb0.cpp`

```cpp
// 0x00412EB0: angle of the pair at +0x0C/+0x10
// The object pointer arrives in EAX, which only a native LTCG link chooses, so
// this region is compiled as a cluster.

#pragma pack(push, 1)
struct ObjectAccessor_00412eb0 {
    unsigned char pad_000[0xC];
    float field_00C;
    float field_010;
    __declspec(noinline) float LoadValue() const;
};
#pragma pack(pop)
#include <math.h>

#pragma code_seg(".text$01accessor")
float ObjectAccessor_00412eb0::LoadValue() const {
    return atan2f(field_010, field_00C);
}
#pragma code_seg()
```

#### 0x00412EC0 - 8 bytes - `?LoadValue@ObjectAccessor_00412ec0@@QBEMXZ`

`src/unidentified/unassigned_00412ec0.cpp`

```cpp
// 0x00412EC0: angle of the pair at +0x00/+0x04
// The object pointer arrives in EAX, which only a native LTCG link chooses, so
// this region is compiled as a cluster.

#pragma pack(push, 1)
struct ObjectAccessor_00412ec0 {
    float field_000;
    float field_004;
    __declspec(noinline) float LoadValue() const;
};
#pragma pack(pop)
#include <math.h>

#pragma code_seg(".text$01accessor")
float ObjectAccessor_00412ec0::LoadValue() const {
    return atan2f(field_004, field_000);
}
#pragma code_seg()
```

#### 0x00412EF0 - 25 bytes - `?DistanceSquared@Vector2_00412ef0@@QBEMPBU1@@Z`

`src/unidentified/unassigned_00412ef0.cpp`

```cpp
// 0x00412EF0: squared distance to the other vector
// The register convention below is only reachable from a native LTCG link,
// so this region is compiled as a cluster.

struct Vector2_00412ef0 {
    float x;
    float y;
    __declspec(noinline) float DistanceSquared(const Vector2_00412ef0* other) const;
};
#pragma code_seg(".text$01accessor")
float Vector2_00412ef0::DistanceSquared(const Vector2_00412ef0* other) const {
    float dy = y - other->y;
    float dx = x - other->x;
    return dx * dx + dy * dy;
}
#pragma code_seg()
```

#### 0x00412F30 - 4 bytes - `?LoadValue@ObjectAccessor_00412f30@@QBEMXZ`

`src/unidentified/unassigned_00412f30.cpp`

```cpp
// 0x00412F30: load the float field at +0x20
// The object pointer arrives in EAX, which only a native LTCG link chooses, so
// this region is compiled as a cluster.

struct ObjectAccessor_00412f30 {
    unsigned char pad_000[0x20];
    float field_020;
    __declspec(noinline) float LoadValue() const;
};

#pragma code_seg(".text$01accessor")
float ObjectAccessor_00412f30::LoadValue() const {
    return field_020;
}
#pragma code_seg()
```

#### 0x00412F40 - 4 bytes - `?LoadValue@ObjectAccessor_00412f40@@QBEMXZ`

`src/unidentified/unassigned_00412f40.cpp`

```cpp
// 0x00412F40: load the float field at +0x24
// The object pointer arrives in EAX, which only a native LTCG link chooses, so
// this region is compiled as a cluster.

struct ObjectAccessor_00412f40 {
    unsigned char pad_000[0x24];
    float field_024;
    __declspec(noinline) float LoadValue() const;
};

#pragma code_seg(".text$01accessor")
float ObjectAccessor_00412f40::LoadValue() const {
    return field_024;
}
#pragma code_seg()
```

#### 0x00412F50 - 5 bytes - `?SetFlag@ObjectAccessor_00412f50@@QAEXXZ`

`src/unidentified/unassigned_00412f50.cpp`

```cpp
// 0x00412F50: set bit 0 of the word at +0x28
// The object pointer arrives in EAX, which only a native LTCG link chooses, so
// this region is compiled as a cluster.

struct ObjectAccessor_00412f50 {
    unsigned char pad_000[0x28];
    unsigned int field_028;
    __declspec(noinline) void SetFlag();
};

#pragma code_seg(".text$01accessor")
void ObjectAccessor_00412f50::SetFlag() {
    field_028 |= 1u;
}
#pragma code_seg()
```

#### 0x00412F60 - 7 bytes - `?LoadFlag@ObjectAccessor_00412f60@@QBEIXZ`

`src/unidentified/unassigned_00412f60.cpp`

```cpp
// 0x00412F60: load bit 0 of the word at +0x28
// The object pointer arrives in EAX, which only a native LTCG link chooses, so
// this region is compiled as a cluster.

struct ObjectAccessor_00412f60 {
    unsigned char pad_000[0x28];
    unsigned int field_028;
    __declspec(noinline) unsigned int LoadFlag() const;
};

#pragma code_seg(".text$01accessor")
unsigned int ObjectAccessor_00412f60::LoadFlag() const {
    return field_028 & 1u;
}
#pragma code_seg()
```

#### 0x00412F80 - 4 bytes - `?LoadValue@ObjectAccessor_00412f80@@QBEMXZ`

`src/unidentified/unassigned_00412f80.cpp`

```cpp
// 0x00412F80: load the float field at +0x18
// The object pointer arrives in EAX, which only a native LTCG link chooses, so
// this region is compiled as a cluster.

struct ObjectAccessor_00412f80 {
    unsigned char pad_000[0x18];
    float field_018;
    __declspec(noinline) float LoadValue() const;
};

#pragma code_seg(".text$01accessor")
float ObjectAccessor_00412f80::LoadValue() const {
    return field_018;
}
#pragma code_seg()
```

#### 0x00412F90 - 4 bytes - `?LoadValue@ObjectAccessor_00412f90@@QBEMXZ`

`src/unidentified/unassigned_00412f90.cpp`

```cpp
// 0x00412F90: load the float field at +0x1C
// The object pointer arrives in EAX, which only a native LTCG link chooses, so
// this region is compiled as a cluster.

struct ObjectAccessor_00412f90 {
    unsigned char pad_000[0x1C];
    float field_01C;
    __declspec(noinline) float LoadValue() const;
};

#pragma code_seg(".text$01accessor")
float ObjectAccessor_00412f90::LoadValue() const {
    return field_01C;
}
#pragma code_seg()
```

#### 0x00412FA0 - 5 bytes - `?ClearFlag@ObjectAccessor_00412fa0@@QAEXXZ`

`src/unidentified/unassigned_00412fa0.cpp`

```cpp
// 0x00412FA0: clear 0x1 in the word at +0x28
// The object pointer arrives in EAX, which only a native LTCG link chooses, so
// this region is compiled as a cluster.

struct ObjectAccessor_00412fa0 {
    unsigned char pad_000[0x28];
    unsigned int field_028;
    __declspec(noinline) void ClearFlag();
};

#pragma code_seg(".text$01accessor")
void ObjectAccessor_00412fa0::ClearFlag() {
    field_028 &= ~0x1u;
}
#pragma code_seg()
```

#### 0x00412FB0 - 7 bytes - `?LoadValue@ObjectAccessor_00412fb0@@QBEMXZ`

`src/unidentified/unassigned_00412fb0.cpp`

```cpp
// 0x00412FB0: product of the floats at +0x4C and +0x3C
// The object pointer arrives in EAX, which only a native LTCG link chooses, so
// this region is compiled as a cluster.

struct ObjectAccessor_00412fb0 {
    unsigned char pad_000[0x3C];
    float field_03C;
    unsigned char pad_040[0xC];
    float field_04C;
    __declspec(noinline) float LoadValue() const;
};

#pragma code_seg(".text$01accessor")
float ObjectAccessor_00412fb0::LoadValue() const {
    return field_04C * field_03C;
}
#pragma code_seg()
```

#### 0x00412FC0 - 7 bytes - `?LoadValue@ObjectAccessor_00412fc0@@QBEMXZ`

`src/unidentified/unassigned_00412fc0.cpp`

```cpp
// 0x00412FC0: product of the floats at +0x50 and +0x40
// The object pointer arrives in EAX, which only a native LTCG link chooses, so
// this region is compiled as a cluster.

struct ObjectAccessor_00412fc0 {
    unsigned char pad_000[0x40];
    float field_040;
    unsigned char pad_044[0xC];
    float field_050;
    __declspec(noinline) float LoadValue() const;
};

#pragma code_seg(".text$01accessor")
float ObjectAccessor_00412fc0::LoadValue() const {
    return field_050 * field_040;
}
#pragma code_seg()
```

#### 0x00412FD0 - 4 bytes - `?LoadValue@ObjectAccessor_00412fd0@@QBEMXZ`

`src/unidentified/unassigned_00412fd0.cpp`

```cpp
// 0x00412FD0: load the float field at +0x08
// The object pointer arrives in EAX, which only a native LTCG link chooses, so
// this region is compiled as a cluster.

struct ObjectAccessor_00412fd0 {
    unsigned char pad_000[0x8];
    float field_008;
    __declspec(noinline) float LoadValue() const;
};

#pragma code_seg(".text$01accessor")
float ObjectAccessor_00412fd0::LoadValue() const {
    return field_008;
}
#pragma code_seg()
```

#### 0x00412FE0 - 1 bytes - `_asm_unassigned_00412fe0`

`src/unidentified/unassigned_00412fe0.cpp`

```cpp
// 0x00412FE0: empty function. Retail's complete body is a single RET -- the
// tail an override whose work the whole-program pass removed leaves.
extern "C" void __cdecl asm_unassigned_00412fe0(void) {
}
```

#### 0x004130B0 - 7 bytes - `_asm_unassigned_004130b0`

`src/unidentified/unassigned_004130b0.cpp`

```cpp
// 0x004130B0: absolute value of the float argument.
#include <math.h>

extern "C" float __cdecl asm_unassigned_004130b0(float value) {
    return fabsf(value);
}
```

#### 0x004130C0 - 4 bytes - `?Offset_004130c0@@YGPADPAUObjectAccessor_004130c0@@@Z`

`src/unidentified/unassigned_004130c0.cpp`

```cpp
// 0x004130C0: return the address of the field block at +0xC
// The leading parameter arrives in EAX, a convention only a native LTCG link
// chooses, so this region is compiled as a cluster.

struct ObjectAccessor_004130c0 {
    unsigned char pad_000[0xC];
};

__declspec(noinline) char* Offset_004130c0(ObjectAccessor_004130c0* object);
#pragma code_seg(".text$01accessor")
char* Offset_004130c0(ObjectAccessor_004130c0* object) {
    return (char*)object + 0xC;
}
#pragma code_seg()
```

#### 0x004130F0 - 4 bytes - `?LoadValue@ObjectAccessor_004130f0@@QBEMXZ`

`src/unidentified/unassigned_004130f0.cpp`

```cpp
// 0x004130F0: load the float field at +0x04
// The object pointer arrives in EAX, which only a native LTCG link chooses, so
// this region is compiled as a cluster.

struct ObjectAccessor_004130f0 {
    unsigned char pad_000[0x4];
    float field_004;
    __declspec(noinline) float LoadValue() const;
};

#pragma code_seg(".text$01accessor")
float ObjectAccessor_004130f0::LoadValue() const {
    return field_004;
}
#pragma code_seg()
```

#### 0x00413110 - 3 bytes - `?LoadValue@ObjectAccessor_00413110@@QBEMXZ`

`src/unidentified/unassigned_00413110.cpp`

```cpp
// 0x00413110: load the float field at +0x00
// The object pointer arrives in EAX, which only a native LTCG link chooses, so
// this region is compiled as a cluster.

struct ObjectAccessor_00413110 {
    float field_000;
    __declspec(noinline) float LoadValue() const;
};

#pragma code_seg(".text$01accessor")
float ObjectAccessor_00413110::LoadValue() const {
    return field_000;
}
#pragma code_seg()
```

#### 0x00413120 - 20 bytes - `?Assign@ObjectAccessor_00413120@@QAEXABUTriple_00413120@@@Z`

`src/unidentified/unassigned_00413120.cpp`

```cpp
// 0x00413120: copy three words into the block at +0x0C
// The register convention below is only reachable from a native LTCG link,
// so this region is compiled as a cluster.

struct Triple_00413120 {
    unsigned int a;
    unsigned int b;
    unsigned int c;
};

struct ObjectAccessor_00413120 {
    unsigned char pad_000[0x0C];
    Triple_00413120 block;   // +0x0C
    __declspec(noinline) void Assign(const Triple_00413120& value);
};
#pragma code_seg(".text$01accessor")
void ObjectAccessor_00413120::Assign(const Triple_00413120& value) {
    block = value;
}
#pragma code_seg()
```

#### 0x00413190 - 14 bytes - `?ClearBlock_00413190@@YGXPAX@Z`

`src/unidentified/unassigned_00413190.cpp`

```cpp
// 0x00413190: clear the eleven-word block
// The register convention below is only reachable from a native LTCG link,
// so this region is compiled as a cluster.

#include <string.h>

__declspec(noinline) void ClearBlock_00413190(void* block);
#pragma code_seg(".text$01accessor")
void ClearBlock_00413190(void* block) {
    memset(block, 0, 44);
}
#pragma code_seg()
```

#### 0x004131A0 - 10 bytes - `?LoadFlag@ObjectAccessor_004131a0@@QBEIXZ`

`src/unidentified/unassigned_004131a0.cpp`

```cpp
// 0x004131A0: test bit 3 of the word at +0x60
// The object pointer arrives in EAX, which only a native LTCG link chooses, so
// this region is compiled as a cluster.

struct ObjectAccessor_004131a0 {
    unsigned char pad_000[0x60];
    unsigned int field_060;
    __declspec(noinline) unsigned int LoadFlag() const;
};

#pragma code_seg(".text$01accessor")
unsigned int ObjectAccessor_004131a0::LoadFlag() const {
    return (field_060 >> 3) & 1u;
}
#pragma code_seg()
```

#### 0x004131B0 - 1 bytes - `_asm_unassigned_004131b0`

`src/unidentified/unassigned_004131b0.cpp`

```cpp
// 0x004131B0: empty function. Retail's complete body is a single RET -- the
// tail an override whose work the whole-program pass removed leaves.
extern "C" void __cdecl asm_unassigned_004131b0(void) {
}
```

#### 0x004131C0 - 37 bytes - `?Remove@Node_004131c0@@QAEXXZ`

`src/unidentified/unassigned_004131c0.cpp`

```cpp
// 0x004131C0: unlink the node and clear its two links
// The register convention below is only reachable from a native LTCG link,
// so this region is compiled as a cluster.

struct Node_004131c0 {
    unsigned char pad_000[0x04];
    Node_004131c0* prev;   // +0x04
    Node_004131c0* next;   // +0x08
    __declspec(noinline) void Remove();
};
#pragma code_seg(".text$01accessor")
void Node_004131c0::Remove() {
    if (prev) {
        prev->next = next;
    }
    if (next) {
        next->prev = prev;
    }
    prev = 0;
    next = 0;
}
#pragma code_seg()
```

#### 0x00413250 - 31 bytes - `?Scale@ObjectAccessor_00413250@@QAEXM@Z`

`src/unidentified/unassigned_00413250.cpp`

```cpp
// 0x00413250: scale the three floats at +0x00..+0x08 by the argument
// The object pointer arrives in EAX, which only a native LTCG link chooses, so
// this region is compiled as a cluster.

#pragma pack(push, 1)
struct ObjectAccessor_00413250 {
    float x;
    float y;
    float z;
    __declspec(noinline) void Scale(float factor);
};
#pragma pack(pop)

#pragma code_seg(".text$01accessor")
void ObjectAccessor_00413250::Scale(float factor) {
    x *= factor;
    y *= factor;
    z *= factor;
}
#pragma code_seg()
```

#### 0x00413290 - 12 bytes - `?LoadValue@ObjectAccessor_00413290@@QBEMXZ`

`src/unidentified/unassigned_00413290.cpp`

```cpp
// 0x00413290: one signed random value scaled by the retail constant at 0x470B18.
// The receiver in ECX is handed straight to the generator at 0x44BB90.

struct RngState;

struct ObjectAccessor_00413290 {
    __declspec(noinline) float LoadValue() const;
};

float __fastcall Rng_NextFloatSigned(RngState* state);
extern "C" float data_00470b18;

float ObjectAccessor_00413290::LoadValue() const {
    return Rng_NextFloatSigned((RngState*)this) * data_00470b18;
}
```

#### 0x004132A0 - 25 bytes - `?InitBlock_004132a0@@YGPAUBlock_004132a0@@PAU1@@Z`

`src/unidentified/unassigned_004132a0.cpp`

```cpp
// 0x004132A0: clear the thirty-five-word block, latch bit 1 and publish it as the
// current global block. The block arrives in EDX, which only a native LTCG link
// chooses, so this region is compiled as a cluster.

#include <string.h>

struct Block_004132a0 {
    unsigned int flags;                    // +0x00
    unsigned int words[0x23 - 1];          // +0x04
};

extern "C" Block_004132a0* data_00477708;

__declspec(noinline) Block_004132a0* InitBlock_004132a0(Block_004132a0* block);
#pragma code_seg(".text$01accessor")
Block_004132a0* InitBlock_004132a0(Block_004132a0* block) {
    memset(block, 0, 0x8C);
    block->flags |= 2u;
    data_00477708 = block;
    return block;
}
#pragma code_seg()
```

#### 0x004136B0 - 1 bytes - `_asm_unassigned_004136b0`

`src/unidentified/unassigned_004136b0.cpp`

```cpp
// 0x004136B0: empty function. Retail's complete body is a single RET -- the
// tail an override whose work the whole-program pass removed leaves.
extern "C" void __cdecl asm_unassigned_004136b0(void) {
}
```

#### 0x00413740 - 18 bytes - `?SetFlagAndClear@ObjectAccessor_00413740@@QAEXXZ`

`src/unidentified/unassigned_00413740.cpp`

```cpp
// 0x00413740: set 0x10 at +0x9EB4 and clear +0x9ECC
// The object pointer arrives in EAX, which only a native LTCG link chooses, so
// this region is compiled as a cluster.

struct ObjectAccessor_00413740 {
    unsigned char pad_000[0x9EB4];
    unsigned int field_9EB4;
    unsigned char pad_9EB8[0x14];
    unsigned int field_9ECC;
    __declspec(noinline) void SetFlagAndClear();
};

#pragma code_seg(".text$01accessor")
void ObjectAccessor_00413740::SetFlagAndClear() {
    field_9EB4 |= 0x10u;
    field_9ECC = 0;
}
#pragma code_seg()
```

#### 0x00413760 - 13 bytes - `?LoadFlag@ObjectAccessor_00413760@@QBEIXZ`

`src/unidentified/unassigned_00413760.cpp`

```cpp
// 0x00413760: test bit 4 of the word at +0x9EB4
// The object pointer arrives in EAX, which only a native LTCG link chooses, so
// this region is compiled as a cluster.

struct ObjectAccessor_00413760 {
    unsigned char pad_000[0x9EB4];
    unsigned int field_9EB4;
    __declspec(noinline) unsigned int LoadFlag() const;
};

#pragma code_seg(".text$01accessor")
unsigned int ObjectAccessor_00413760::LoadFlag() const {
    return (field_9EB4 >> 4) & 1u;
}
#pragma code_seg()
```

#### 0x00413770 - 8 bytes - `?SetFlag@ObjectAccessor_00413770@@QAEXXZ`

`src/unidentified/unassigned_00413770.cpp`

```cpp
// 0x00413770: set 0x20 in the word at +0x9EB4
// The object pointer arrives in EAX, which only a native LTCG link chooses, so
// this region is compiled as a cluster.

struct ObjectAccessor_00413770 {
    unsigned char pad_000[0x9EB4];
    unsigned int field_9EB4;
    __declspec(noinline) void SetFlag();
};

#pragma code_seg(".text$01accessor")
void ObjectAccessor_00413770::SetFlag() {
    field_9EB4 |= 0x20u;
}
#pragma code_seg()
```

#### 0x00413780 - 13 bytes - `?LoadFlag@ObjectAccessor_00413780@@QBEIXZ`

`src/unidentified/unassigned_00413780.cpp`

```cpp
// 0x00413780: test bit 5 of the word at +0x9EB4
// The object pointer arrives in EAX, which only a native LTCG link chooses, so
// this region is compiled as a cluster.

struct ObjectAccessor_00413780 {
    unsigned char pad_000[0x9EB4];
    unsigned int field_9EB4;
    __declspec(noinline) unsigned int LoadFlag() const;
};

#pragma code_seg(".text$01accessor")
unsigned int ObjectAccessor_00413780::LoadFlag() const {
    return (field_9EB4 >> 5) & 1u;
}
#pragma code_seg()
```

#### 0x004137F0 - 15 bytes - `?LoadFlag@ObjectAccessor_004137f0@@QBEIXZ`

`src/unidentified/unassigned_004137f0.cpp`

```cpp
// 0x004137F0: complement bit 4 of the word at +0x2480
// The object pointer arrives in EAX, which only a native LTCG link chooses, so
// this region is compiled as a cluster.

struct ObjectAccessor_004137f0 {
    unsigned char pad_000[0x2480];
    unsigned int field_2480;
    __declspec(noinline) unsigned int LoadFlag() const;
};

#pragma code_seg(".text$01accessor")
unsigned int ObjectAccessor_004137f0::LoadFlag() const {
    return ~(field_2480 >> 4) & 1u;
}
#pragma code_seg()
```

#### 0x00413800 - 12 bytes - `?LoadFlag@ObjectAccessor_00413800@@QBEIXZ`

`src/unidentified/unassigned_00413800.cpp`

```cpp
// 0x00413800: complement bit 0 of the word at +0x2480
// The object pointer arrives in EAX, which only a native LTCG link chooses, so
// this region is compiled as a cluster.

struct ObjectAccessor_00413800 {
    unsigned char pad_000[0x2480];
    unsigned int field_2480;
    __declspec(noinline) unsigned int LoadFlag() const;
};

#pragma code_seg(".text$01accessor")
unsigned int ObjectAccessor_00413800::LoadFlag() const {
    return ~field_2480 & 1u;
}
#pragma code_seg()
```

#### 0x004148C0 - 27 bytes - `?ReleaseComposite_DeletingDestructor_004148c0@@YGPAXPAUOwnedObject_004148c0@@I@Z`

`src/unidentified/unassigned_004148c0.cpp`

```cpp
// 0x004148c0: scalar deleting destructor. Retail keeps the object in ESI and the
// delete flag in the first stack argument, so this body is a cluster whose
// synthetic caller walks an array of the objects.

struct OwnedObject_004148c0;
extern "C" void asm_FUN_004145f0_004145f0(void* object);
extern "C" void __cdecl entry_free_004524a1(void* memory);
__declspec(noinline) void* ReleaseComposite_DeletingDestructor_004148c0(OwnedObject_004148c0* object, unsigned int flags);
#pragma code_seg(".text$01delete004148c0")
void* ReleaseComposite_DeletingDestructor_004148c0(OwnedObject_004148c0* object, unsigned int flags) {
    asm_FUN_004145f0_004145f0(object);
    if (flags & 1) entry_free_004524a1(object);
    return object;
}
#pragma code_seg()
```

#### 0x004175B0 - 10 bytes - `?LoadFlag@ObjectAccessor_004175b0@@QBEIXZ`

`src/unidentified/unassigned_004175b0.cpp`

```cpp
// 0x004175B0: test bit 2 of the word at +0x60
// The object pointer arrives in EAX, which only a native LTCG link chooses, so
// this region is compiled as a cluster.

struct ObjectAccessor_004175b0 {
    unsigned char pad_000[0x60];
    unsigned int field_060;
    __declspec(noinline) unsigned int LoadFlag() const;
};

#pragma code_seg(".text$01accessor")
unsigned int ObjectAccessor_004175b0::LoadFlag() const {
    return (field_060 >> 2) & 1u;
}
#pragma code_seg()
```

#### 0x004175C0 - 5 bytes - `?SetFlag@ObjectAccessor_004175c0@@QAEXXZ`

`src/unidentified/unassigned_004175c0.cpp`

```cpp
// 0x004175C0: set 0x4 in the word at +0x60
// The object pointer arrives in EAX, which only a native LTCG link chooses, so
// this region is compiled as a cluster.

struct ObjectAccessor_004175c0 {
    unsigned char pad_000[0x60];
    unsigned int field_060;
    __declspec(noinline) void SetFlag();
};

#pragma code_seg(".text$01accessor")
void ObjectAccessor_004175c0::SetFlag() {
    field_060 |= 0x4u;
}
#pragma code_seg()
```

#### 0x00417600 - 10 bytes - `?LoadFlag@ObjectAccessor_00417600@@QBEIXZ`

`src/unidentified/unassigned_00417600.cpp`

```cpp
// 0x00417600: test bit 4 of the word at +0x60
// The object pointer arrives in EAX, which only a native LTCG link chooses, so
// this region is compiled as a cluster.

struct ObjectAccessor_00417600 {
    unsigned char pad_000[0x60];
    unsigned int field_060;
    __declspec(noinline) unsigned int LoadFlag() const;
};

#pragma code_seg(".text$01accessor")
unsigned int ObjectAccessor_00417600::LoadFlag() const {
    return (field_060 >> 4) & 1u;
}
#pragma code_seg()
```

#### 0x00417610 - 7 bytes - `?Mask@ObjectAccessor_00417610@@QBEII@Z`

`src/unidentified/unassigned_00417610.cpp`

```cpp
// 0x00417610: mask the word field at +0x32
// The object pointer arrives in EAX, which only a native LTCG link chooses, so
// this region is compiled as a cluster.

struct ObjectAccessor_00417610 {
    unsigned char pad_000[0x32];
    unsigned short field_032;
    __declspec(noinline) unsigned int Mask(unsigned int mask) const;
};

#pragma code_seg(".text$01accessor")
unsigned int ObjectAccessor_00417610::Mask(unsigned int mask) const {
    return field_032 & mask;
}
#pragma code_seg()
```

#### 0x00417620 - 7 bytes - `?Mask@ObjectAccessor_00417620@@QBEII@Z`

`src/unidentified/unassigned_00417620.cpp`

```cpp
// 0x00417620: mask the word field at +0x2C
// The object pointer arrives in EAX, which only a native LTCG link chooses, so
// this region is compiled as a cluster.

struct ObjectAccessor_00417620 {
    unsigned char pad_000[0x2C];
    unsigned short field_02C;
    __declspec(noinline) unsigned int Mask(unsigned int mask) const;
};

#pragma code_seg(".text$01accessor")
unsigned int ObjectAccessor_00417620::Mask(unsigned int mask) const {
    return field_02C & mask;
}
#pragma code_seg()
```

#### 0x00417630 - 6 bytes - `?Offset_00417630@@YGPADPAUObjectAccessor_00417630@@@Z`

`src/unidentified/unassigned_00417630.cpp`

```cpp
// 0x00417630: return the address of the field block at +0x2FC
// The leading parameter arrives in EAX, a convention only a native LTCG link
// chooses, so this region is compiled as a cluster.

struct ObjectAccessor_00417630 {
    unsigned char pad_000[0x2FC];
};

__declspec(noinline) char* Offset_00417630(ObjectAccessor_00417630* object);
#pragma code_seg(".text$01accessor")
char* Offset_00417630(ObjectAccessor_00417630* object) {
    return (char*)object + 0x2FC;
}
#pragma code_seg()
```

#### 0x00417650 - 6 bytes - `?Offset_00417650@@YGPADPAUObjectAccessor_00417650@@@Z`

`src/unidentified/unassigned_00417650.cpp`

```cpp
// 0x00417650: return the address of the field block at +0x340
// The leading parameter arrives in EAX, a convention only a native LTCG link
// chooses, so this region is compiled as a cluster.

struct ObjectAccessor_00417650 {
    unsigned char pad_000[0x340];
};

__declspec(noinline) char* Offset_00417650(ObjectAccessor_00417650* object);
#pragma code_seg(".text$01accessor")
char* Offset_00417650(ObjectAccessor_00417650* object) {
    return (char*)object + 0x340;
}
#pragma code_seg()
```

#### 0x00417690 - 10 bytes - `?LoadFlag@ObjectAccessor_00417690@@QBEIXZ`

`src/unidentified/unassigned_00417690.cpp`

```cpp
// 0x00417690: test bit 5 of the word at +0x60
// The object pointer arrives in EAX, which only a native LTCG link chooses, so
// this region is compiled as a cluster.

struct ObjectAccessor_00417690 {
    unsigned char pad_000[0x60];
    unsigned int field_060;
    __declspec(noinline) unsigned int LoadFlag() const;
};

#pragma code_seg(".text$01accessor")
unsigned int ObjectAccessor_00417690::LoadFlag() const {
    return (field_060 >> 5) & 1u;
}
#pragma code_seg()
```

#### 0x004176B0 - 1 bytes - `_asm_unassigned_004176b0`

`src/unidentified/unassigned_004176b0.cpp`

```cpp
// 0x004176B0: empty function. Retail's complete body is a single RET -- the
// tail an override whose work the whole-program pass removed leaves.
extern "C" void __cdecl asm_unassigned_004176b0(void) {
}
```

#### 0x004176F0 - 8 bytes - `?ClearFlag@ObjectAccessor_004176f0@@QAEXXZ`

`src/unidentified/unassigned_004176f0.cpp`

```cpp
// 0x004176F0: clear 0x2 in the word at +0x35C
// The object pointer arrives in EAX, which only a native LTCG link chooses, so
// this region is compiled as a cluster.

struct ObjectAccessor_004176f0 {
    unsigned char pad_000[0x35C];
    unsigned int field_35C;
    __declspec(noinline) void ClearFlag();
};

#pragma code_seg(".text$01accessor")
void ObjectAccessor_004176f0::ClearFlag() {
    field_35C &= ~0x2u;
}
#pragma code_seg()
```

#### 0x00417700 - 8 bytes - `?SetFlag@ObjectAccessor_00417700@@QAEXXZ`

`src/unidentified/unassigned_00417700.cpp`

```cpp
// 0x00417700: set 0x2 in the word at +0x35C
// The object pointer arrives in EAX, which only a native LTCG link chooses, so
// this region is compiled as a cluster.

struct ObjectAccessor_00417700 {
    unsigned char pad_000[0x35C];
    unsigned int field_35C;
    __declspec(noinline) void SetFlag();
};

#pragma code_seg(".text$01accessor")
void ObjectAccessor_00417700::SetFlag() {
    field_35C |= 0x2u;
}
#pragma code_seg()
```

#### 0x00417710 - 13 bytes - `?LoadFlag@ObjectAccessor_00417710@@QBEIXZ`

`src/unidentified/unassigned_00417710.cpp`

```cpp
// 0x00417710: test bit 3 of the word at +0x2A18
// The object pointer arrives in EAX, which only a native LTCG link chooses, so
// this region is compiled as a cluster.

struct ObjectAccessor_00417710 {
    unsigned char pad_000[0x2A18];
    unsigned int field_2A18;
    __declspec(noinline) unsigned int LoadFlag() const;
};

#pragma code_seg(".text$01accessor")
unsigned int ObjectAccessor_00417710::LoadFlag() const {
    return (field_2A18 >> 3) & 1u;
}
#pragma code_seg()
```

#### 0x00417730 - 10 bytes - `?StoreValue@ObjectAccessor_00417730@@QAENN@Z`

`src/unidentified/unassigned_00417730.cpp`

```cpp
// 0x00417730: store the double argument at +0x24 and return it
// The object pointer arrives in EAX, which only a native LTCG link chooses, so
// this region is compiled as a cluster.

#pragma pack(push, 1)
struct ObjectAccessor_00417730 {
    unsigned char pad_000[0x24];
    double field_024;
    __declspec(noinline) double StoreValue(double value);
};
#pragma pack(pop)

#pragma code_seg(".text$01accessor")
double ObjectAccessor_00417730::StoreValue(double value) {
    field_024 = value;
    return value;
}
#pragma code_seg()
```

#### 0x00417740 - 10 bytes - `?StoreValue@ObjectAccessor_00417740@@QAENN@Z`

`src/unidentified/unassigned_00417740.cpp`

```cpp
// 0x00417740: store the double argument at +0x2C and return it
// The object pointer arrives in EAX, which only a native LTCG link chooses, so
// this region is compiled as a cluster.

#pragma pack(push, 1)
struct ObjectAccessor_00417740 {
    unsigned char pad_000[0x2C];
    double field_02C;
    __declspec(noinline) double StoreValue(double value);
};
#pragma pack(pop)

#pragma code_seg(".text$01accessor")
double ObjectAccessor_00417740::StoreValue(double value) {
    field_02C = value;
    return value;
}
#pragma code_seg()
```

#### 0x00417750 - 23 bytes - `?Unlink@ObjectAccessor_00417750@@QAEXXZ`

`src/unidentified/unassigned_00417750.cpp`

```cpp
// 0x00417750: unlink the node from its doubly-linked neighbours.
// The object pointer arrives in EAX, which only a native LTCG link chooses, so
// this region is compiled as a cluster.

struct ObjectAccessor_00417750 {
    unsigned char pad_000[0x04];
    ObjectAccessor_00417750* prev;
    ObjectAccessor_00417750* next;
    __declspec(noinline) void Unlink();
};

#pragma code_seg(".text$01accessor")
void ObjectAccessor_00417750::Unlink() {
    prev->next = next;
    if (next) {
        next->prev = prev;
    }
}
#pragma code_seg()
```

#### 0x00418170 - 27 bytes - `?DestroyOwned_DeletingDestructor_00418170@@YGPAXPAUOwnedObject_00418170@@I@Z`

`src/unidentified/unassigned_00418170.cpp`

```cpp
// 0x00418170: scalar deleting destructor. Retail keeps the object in ESI and the
// delete flag in the first stack argument, so this body is a cluster whose
// synthetic caller walks an array of the objects.

struct OwnedObject_00418170;
extern "C" void asm_FUN_00417c80_00417c80(void* object);
extern "C" void __cdecl entry_free_004524a1(void* memory);
__declspec(noinline) void* DestroyOwned_DeletingDestructor_00418170(OwnedObject_00418170* object, unsigned int flags);
#pragma code_seg(".text$01delete00418170")
void* DestroyOwned_DeletingDestructor_00418170(OwnedObject_00418170* object, unsigned int flags) {
    asm_FUN_00417c80_00417c80(object);
    if (flags & 1) entry_free_004524a1(object);
    return object;
}
#pragma code_seg()
```

#### 0x004187A0 - 31 bytes - `?Reset_004187a0@@YGHPAUObjectAccessor_004187a0@@@Z`

`src/unidentified/unassigned_004187a0.cpp`

```cpp
// 0x004187A0: clear the shared state unless the object keeps it
// The leading parameter arrives in EAX, a convention only a native LTCG link
// chooses, so this region is compiled as a cluster.

struct GlobalState_00491c10 {
    unsigned char pad_04C[0x4C];
    int field_04C;
    int field_050;
    int field_054;
    int field_058;
};

struct ObjectAccessor_004187a0 {
    unsigned char pad_000[0x58];
    unsigned int flags;   // +0x58
};

extern "C" GlobalState_00491c10* data_00491c10;

int __declspec(noinline) Reset_004187a0(ObjectAccessor_004187a0* object);
#pragma code_seg(".text$01accessor")
int Reset_004187a0(ObjectAccessor_004187a0* object) {
    if ((object->flags & 4u) == 0) {
        GlobalState_00491c10* state = data_00491c10;
        state->field_050 = 0;
        state->field_054 = 0;
        state->field_04C = 0;
        state->field_058 = 0;
    }
    return 1;
}
#pragma code_seg()
```

#### 0x004189E0 - 15 bytes - `?ClearState@ObjectAccessor_004189e0@@QAEXXZ`

`src/unidentified/unassigned_004189e0.cpp`

```cpp
// 0x004189E0: clear the four state words at +0x4C..+0x58
// The object pointer arrives in EAX, which only a native LTCG link chooses, so
// this region is compiled as a cluster.

struct ObjectAccessor_004189e0 {
    unsigned char pad_000[0x4C];
    int field_04C;
    int field_050;
    int field_054;
    int field_058;
    __declspec(noinline) void ClearState();
};

#pragma code_seg(".text$01accessor")
void ObjectAccessor_004189e0::ClearState() {
    field_050 = 0;
    field_054 = 0;
    field_04C = 0;
    field_058 = 0;
}
#pragma code_seg()
```

#### 0x004189F0 - 7 bytes - `?IncrementCounters@ObjectAccessor_004189f0@@QAEXXZ`

`src/unidentified/unassigned_004189f0.cpp`

```cpp
// 0x004189F0: increment the counters at +0x48 and +0x4C
// The object pointer arrives in EAX, which only a native LTCG link chooses, so
// this region is compiled as a cluster.

struct ObjectAccessor_004189f0 {
    unsigned char pad_000[0x48];
    int field_048;
    int field_04C;
    __declspec(noinline) void IncrementCounters();
};

#pragma code_seg(".text$01accessor")
void ObjectAccessor_004189f0::IncrementCounters() {
    ++field_048;
    ++field_04C;
}
#pragma code_seg()
```

#### 0x00418A70 - 31 bytes - `?ClearFlags_00418a70@@YGXPAUObjectAccessor_00418a70@@@Z`

`src/unidentified/unassigned_00418a70.cpp`

```cpp
// 0x00418A70: clear bit 1 of the two owned flag words
// The leading parameter arrives in EAX, a convention only a native LTCG link
// chooses, so this region is compiled as a cluster.

struct Flagged_00418a70 {
    unsigned char pad_000[0x04];
    unsigned int flags;
};

struct ObjectAccessor_00418a70 {
    unsigned char pad_000[0x0C];
    Flagged_00418a70* low;
    unsigned char pad_010[0x1CC - 0x10];
    Flagged_00418a70* high;
};

void __declspec(noinline) ClearFlags_00418a70(ObjectAccessor_00418a70* object);
#pragma code_seg(".text$01accessor")
void ClearFlags_00418a70(ObjectAccessor_00418a70* object) {
    if (object->high) {
        object->high->flags &= ~2u;
    }
    if (object->low) {
        object->low->flags &= ~2u;
    }
}
#pragma code_seg()
```

#### 0x00418AD0 - 21 bytes - `?SetBit3@ObjectAccessor_00418ad0@@QAEXI@Z`

`src/unidentified/unassigned_00418ad0.cpp`

```cpp
// 0x00418AD0: assign bit 3 of the word at +0x60 from the argument
// The object pointer arrives in EAX, which only a native LTCG link chooses, so
// this region is compiled as a cluster.

struct ObjectAccessor_00418ad0 {
    unsigned char pad_000[0x60];
    unsigned int field_060;
    __declspec(noinline) void SetBit3(unsigned int mask);
};

#pragma code_seg(".text$01accessor")
void ObjectAccessor_00418ad0::SetBit3(unsigned int mask) {
    field_060 = (field_060 & ~8u) | ((mask & 1u) << 3);
}
#pragma code_seg()
```

#### 0x00418AF0 - 17 bytes - `?SetBit1@ObjectAccessor_00418af0@@QAEXI@Z`

`src/unidentified/unassigned_00418af0.cpp`

```cpp
// 0x00418AF0: assign bit 1 of the word at +0x60 from the argument
// The object pointer arrives in EAX, which only a native LTCG link chooses, so
// this region is compiled as a cluster.

struct ObjectAccessor_00418af0 {
    unsigned char pad_000[0x60];
    unsigned int field_060;
    __declspec(noinline) void SetBit1(unsigned int mask);
};

#pragma code_seg(".text$01accessor")
void ObjectAccessor_00418af0::SetBit1(unsigned int mask) {
    field_060 = (field_060 & ~2u) | ((mask & 1u) << 1);
}
#pragma code_seg()
```

#### 0x00418B10 - 17 bytes - `?SetBit0@ObjectAccessor_00418b10@@QAEXI@Z`

`src/unidentified/unassigned_00418b10.cpp`

```cpp
// 0x00418B10: assign bit 0 of the word at +0x60 from the argument
// The object pointer arrives in EAX, which only a native LTCG link chooses, so
// this region is compiled as a cluster.

struct ObjectAccessor_00418b10 {
    unsigned char pad_000[0x60];
    unsigned int field_060;
    __declspec(noinline) void SetBit0(unsigned int mask);
};

#pragma code_seg(".text$01accessor")
void ObjectAccessor_00418b10::SetBit0(unsigned int mask) {
    field_060 = (field_060 & ~1u) | (mask & 1u);
}
#pragma code_seg()
```

#### 0x00418B30 - 9 bytes - `?LoadFlag@ObjectAccessor_00418b30@@QBEIXZ`

`src/unidentified/unassigned_00418b30.cpp`

```cpp
// 0x00418B30: test bit 1 of the word at +0x60
// The object pointer arrives in EAX, which only a native LTCG link chooses, so
// this region is compiled as a cluster.

struct ObjectAccessor_00418b30 {
    unsigned char pad_000[0x60];
    unsigned int field_060;
    __declspec(noinline) unsigned int LoadFlag() const;
};

#pragma code_seg(".text$01accessor")
unsigned int ObjectAccessor_00418b30::LoadFlag() const {
    return (field_060 >> 1) & 1u;
}
#pragma code_seg()
```

#### 0x00418B50 - 5 bytes - `?ClearFlag@ObjectAccessor_00418b50@@QAEXXZ`

`src/unidentified/unassigned_00418b50.cpp`

```cpp
// 0x00418B50: clear 0x4 in the word at +0x60
// The object pointer arrives in EAX, which only a native LTCG link chooses, so
// this region is compiled as a cluster.

struct ObjectAccessor_00418b50 {
    unsigned char pad_000[0x60];
    unsigned int field_060;
    __declspec(noinline) void ClearFlag();
};

#pragma code_seg(".text$01accessor")
void ObjectAccessor_00418b50::ClearFlag() {
    field_060 &= ~0x4u;
}
#pragma code_seg()
```

#### 0x00418C10 - 9 bytes - `?ClearCounters@ObjectAccessor_00418c10@@QAEXXZ`

`src/unidentified/unassigned_00418c10.cpp`

```cpp
// 0x00418C10: clear the counters at +0x48 and +0x4C
// The object pointer arrives in EAX, which only a native LTCG link chooses, so
// this region is compiled as a cluster.

struct ObjectAccessor_00418c10 {
    unsigned char pad_000[0x48];
    int field_048;
    int field_04C;
    __declspec(noinline) void ClearCounters();
};

#pragma code_seg(".text$01accessor")
void ObjectAccessor_00418c10::ClearCounters() {
    field_048 = 0;
    field_04C = 0;
}
#pragma code_seg()
```

#### 0x00418C20 - 1 bytes - `_asm_unassigned_00418c20`

`src/unidentified/unassigned_00418c20.cpp`

```cpp
// 0x00418C20: empty function. Retail's complete body is a single RET -- the
// tail an override whose work the whole-program pass removed leaves.
extern "C" void __cdecl asm_unassigned_00418c20(void) {
}
```

#### 0x00418CC0 - 63 bytes - `?Reset_00418cc0@@YGXPAUObjectAccessor_00418cc0@@@Z`

`src/unidentified/unassigned_00418cc0.cpp`

```cpp
// 0x00418CC0: clear bit 0, latch it and reload the retail defaults
// The object pointer arrives in EAX, a convention only a native LTCG link
// chooses, so this region is compiled as a cluster.

struct ObjectAccessor_00418cc0 {
    unsigned char pad_000[0x14];
    int field_014;   // +0x14
    int field_018;   // +0x18
    int field_01C;   // +0x1C
    int field_020;   // +0x20
    unsigned int field_024;  // +0x24
    unsigned char pad_028[0x34 - 0x28];
    int field_034;   // +0x34
};

__declspec(noinline) void Reset_00418cc0(ObjectAccessor_00418cc0* object);
#pragma code_seg(".text$01accessor")
void Reset_00418cc0(ObjectAccessor_00418cc0* object) {
    unsigned int value = object->field_024 & ~1u;
    object->field_024 = value;
    if ((value & 1u) == 0) {
        value |= 1u;
        object->field_018 = 0;
        object->field_014 = 0xFFF0BDC1;
        object->field_01C = 0;
        object->field_020 = 0x476F78;
        object->field_024 = value;
    }
    object->field_018 = 0;
    object->field_01C = 0;
    object->field_014 = 0xFFFFFFFF;
    object->field_034 = 1;
}
#pragma code_seg()
```

#### 0x00418EC0 - 28 bytes - `?SetFlags_00418ec0@@YGXPAUObjectAccessor_00418ec0@@@Z`

`src/unidentified/unassigned_00418ec0.cpp`

```cpp
// 0x00418EC0: set bit 1 of the two owned flag words
// The leading parameter arrives in EAX, a convention only a native LTCG link
// chooses, so this region is compiled as a cluster.

struct Flagged_00418ec0 {
    unsigned char pad_000[0x04];
    unsigned int flags;
};

struct ObjectAccessor_00418ec0 {
    unsigned char pad_000[0x08];
    Flagged_00418ec0* first;
    Flagged_00418ec0* second;
};

void __declspec(noinline) SetFlags_00418ec0(ObjectAccessor_00418ec0* object);
#pragma code_seg(".text$01accessor")
void SetFlags_00418ec0(ObjectAccessor_00418ec0* object) {
    if (object->first) {
        object->first->flags |= 2u;
    }
    if (object->second) {
        object->second->flags |= 2u;
    }
}
#pragma code_seg()
```

#### 0x004190E0 - 27 bytes - `?DestroyOwned_DeletingDestructor_004190e0@@YGPAXPAUOwnedObject_004190e0@@I@Z`

`src/unidentified/unassigned_004190e0.cpp`

```cpp
// 0x004190e0: scalar deleting destructor. Retail keeps the object in ESI and the
// delete flag in the first stack argument, so this body is a cluster whose
// synthetic caller walks an array of the objects.

struct OwnedObject_004190e0;
extern "C" void asm_FUN_00418ee0_00418ee0(void* object);
extern "C" void __cdecl entry_free_004524a1(void* memory);
__declspec(noinline) void* DestroyOwned_DeletingDestructor_004190e0(OwnedObject_004190e0* object, unsigned int flags);
#pragma code_seg(".text$01delete004190e0")
void* DestroyOwned_DeletingDestructor_004190e0(OwnedObject_004190e0* object, unsigned int flags) {
    asm_FUN_00418ee0_00418ee0(object);
    if (flags & 1) entry_free_004524a1(object);
    return object;
}
#pragma code_seg()
```

#### 0x00419100 - 18 bytes - `?ReleaseOwned_00419100@@YGXPAUOwnedObject_00419100@@@Z`

`src/unidentified/unassigned_00419100.cpp`

```cpp
// 0x00419100: release an owned object and free it. Retail keeps the object in ESI.

struct OwnedObject_00419100;
extern "C" void asm_FUN_00418ee0_00418ee0(void* object);
extern "C" void __cdecl entry_free_004524a1(void* memory);
__declspec(noinline) void ReleaseOwned_00419100(OwnedObject_00419100* object);
#pragma code_seg(".text$01release00419100")
void ReleaseOwned_00419100(OwnedObject_00419100* object) {
    if (object) {
        asm_FUN_00418ee0_00418ee0(object);
        entry_free_004524a1(object);
    }
}
#pragma code_seg()
```

#### 0x0041AAD0 - 39 bytes - `?RetireCounts@ObjectAccessor_0041aad0@@QAEXXZ`

`src/unidentified/unassigned_0041aad0.cpp`

```cpp
// 0x0041AAD0: walk the bucket selected by the global index at 0x474C7C and
// retire one count from each element's counter at +0x70.

struct Chain_0041aad0 {
    Chain_0041aad0* inner;               // +0x00
    Chain_0041aad0* next;                // +0x04
    unsigned char pad_008[0x70 - 0x08];
    int count;                           // +0x70
};

struct Entry_0041aad0 {
    Chain_0041aad0* head;                // +0x00
    unsigned int reserved[2];
};

struct ObjectAccessor_0041aad0 {
    unsigned char pad_000[0x7C];
    Entry_0041aad0 entries[];            // +0x7C, stride 12
    __declspec(noinline) void RetireCounts();
};

extern "C" int data_00474c7c;

void ObjectAccessor_0041aad0::RetireCounts() {
    Chain_0041aad0* node = entries[data_00474c7c].head;
    while (node) {
        Chain_0041aad0* next = node->next;
        Chain_0041aad0* inner = node->inner;
        if (inner->count > 0) {
            --inner->count;
        }
        node = next;
    }
}
```

#### 0x0041AB00 - 15 bytes - `?LoadValue@ObjectAccessor_0041ab00@@QBEHXZ`

`src/unidentified/unassigned_0041ab00.cpp`

```cpp
// 0x0041AB00: return +0x4C when +0x44 is set, otherwise +0x48
// The object pointer arrives in EAX, which only a native LTCG link chooses, so
// this region is compiled as a cluster.

struct ObjectAccessor_0041ab00 {
    unsigned char pad_000[0x44];
    unsigned int field_044;
    int field_048;
    int field_04C;
    __declspec(noinline) int LoadValue() const;
};

#pragma code_seg(".text$01accessor")
int ObjectAccessor_0041ab00::LoadValue() const {
    return field_044 ? field_04C : field_048;
}
#pragma code_seg()
```

#### 0x0041AC40 - 50 bytes - `?Reset_0041ac40@@YGXPAUObjectAccessor_0041ac40@@@Z`

`src/unidentified/unassigned_0041ac40.cpp`

```cpp
// 0x0041AC40: latch bit 0 and reload the retail defaults
// The object pointer arrives in EAX, a convention only a native LTCG link
// chooses, so this region is compiled as a cluster.

struct ObjectAccessor_0041ac40 {
    unsigned char pad_000[0x20];
    int field_020;   // +0x20
    int field_024;   // +0x24
    int field_028;   // +0x28
    int field_02C;   // +0x2C
    unsigned int field_030;  // +0x30
};

__declspec(noinline) void Reset_0041ac40(ObjectAccessor_0041ac40* object);
#pragma code_seg(".text$01accessor")
void Reset_0041ac40(ObjectAccessor_0041ac40* object) {
    if ((object->field_030 & 1u) == 0) {
        object->field_024 = 0;
        object->field_020 = 0xFFF0BDC1;
        object->field_028 = 0;
        object->field_02C = 0x476F78;
        object->field_030 |= 1u;
    }
    object->field_024 = 0;
    object->field_028 = 0;
    object->field_020 = 0xFFFFFFFF;
}
#pragma code_seg()
```

#### 0x0041AC90 - 1 bytes - `_asm_unassigned_0041ac90`

`src/unidentified/unassigned_0041ac90.cpp`

```cpp
// 0x0041AC90: empty function. Retail's complete body is a single RET -- the
// tail an override whose work the whole-program pass removed leaves.
extern "C" void __cdecl asm_unassigned_0041ac90(void) {
}
```

#### 0x0041AF90 - 27 bytes - `?DestroyOwned_DeletingDestructor_0041af90@@YGPAXPAUOwnedObject_0041af90@@I@Z`

`src/unidentified/unassigned_0041af90.cpp`

```cpp
// 0x0041AF90: scalar deleting destructor. Retail keeps the object in ESI and the
// delete flag in the first stack argument, so this body is a cluster.

struct OwnedObject_0041af90;
extern "C" void asm_FUN_0041adf0_0041adf0(void* object);
extern "C" void __cdecl entry_free_004524a1(void* memory);
__declspec(noinline) void* DestroyOwned_DeletingDestructor_0041af90(OwnedObject_0041af90* object, unsigned int flags);
#pragma code_seg(".text$01delete0041af90")
void* DestroyOwned_DeletingDestructor_0041af90(OwnedObject_0041af90* object, unsigned int flags) {
    asm_FUN_0041adf0_0041adf0(object);
    if (flags & 1) entry_free_004524a1(object);
    return object;
}
#pragma code_seg()
```

#### 0x0041BE70 - 8 bytes - `?LoadValue@ObjectAccessor_0041be70@@QBEHXZ`

`src/unidentified/unassigned_0041be70.cpp`

```cpp
// 0x0041BE70: load the sign-extended word field at +0x384
// The object pointer arrives in EAX, which only a native LTCG link chooses, so
// this region is compiled as a cluster.

struct ObjectAccessor_0041be70 {
    unsigned char pad_000[0x384];
    short field_384;
    __declspec(noinline) int LoadValue() const;
};

#pragma code_seg(".text$01accessor")
int ObjectAccessor_0041be70::LoadValue() const {
    return field_384;
}
#pragma code_seg()
```

#### 0x0041BED0 - 1 bytes - `_asm_unassigned_0041bed0`

`src/unidentified/unassigned_0041bed0.cpp`

```cpp
// 0x0041BED0: empty function. Retail's complete body is a single RET -- the
// tail an override whose work the whole-program pass removed leaves.
extern "C" void __cdecl asm_unassigned_0041bed0(void) {
}
```

#### 0x0041BEF0 - 1 bytes - `_asm_unassigned_0041bef0`

`src/unidentified/unassigned_0041bef0.cpp`

```cpp
// 0x0041BEF0: empty function. Retail's complete body is a single RET -- the
// tail an override whose work the whole-program pass removed leaves.
extern "C" void __cdecl asm_unassigned_0041bef0(void) {
}
```

#### 0x0041BF90 - 1 bytes - `_asm_unassigned_0041bf90`

`src/unidentified/unassigned_0041bf90.cpp`

```cpp
// 0x0041BF90: empty function. Retail's complete body is a single RET -- the
// tail an override whose work the whole-program pass removed leaves.
extern "C" void __cdecl asm_unassigned_0041bf90(void) {
}
```

#### 0x0041BFA0 - 1 bytes - `_asm_unassigned_0041bfa0`

`src/unidentified/unassigned_0041bfa0.cpp`

```cpp
// 0x0041BFA0: empty function. Retail's complete body is a single RET -- the
// tail an override whose work the whole-program pass removed leaves.
extern "C" void __cdecl asm_unassigned_0041bfa0(void) {
}
```

#### 0x0041BFB0 - 1 bytes - `_asm_unassigned_0041bfb0`

`src/unidentified/unassigned_0041bfb0.cpp`

```cpp
// 0x0041BFB0: empty function. Retail's complete body is a single RET -- the
// tail an override whose work the whole-program pass removed leaves.
extern "C" void __cdecl asm_unassigned_0041bfb0(void) {
}
```

#### 0x0041BFC0 - 1 bytes - `_asm_unassigned_0041bfc0`

`src/unidentified/unassigned_0041bfc0.cpp`

```cpp
// 0x0041BFC0: empty function. Retail's complete body is a single RET -- the
// tail an override whose work the whole-program pass removed leaves.
extern "C" void __cdecl asm_unassigned_0041bfc0(void) {
}
```

#### 0x0041BFD0 - 1 bytes - `_asm_unassigned_0041bfd0`

`src/unidentified/unassigned_0041bfd0.cpp`

```cpp
// 0x0041BFD0: empty function. Retail's complete body is a single RET -- the
// tail an override whose work the whole-program pass removed leaves.
extern "C" void __cdecl asm_unassigned_0041bfd0(void) {
}
```

#### 0x0041BFE0 - 1 bytes - `_asm_unassigned_0041bfe0`

`src/unidentified/unassigned_0041bfe0.cpp`

```cpp
// 0x0041BFE0: empty function. Retail's complete body is a single RET -- the
// tail an override whose work the whole-program pass removed leaves.
extern "C" void __cdecl asm_unassigned_0041bfe0(void) {
}
```

#### 0x0041C020 - 1 bytes - `_asm_unassigned_0041c020`

`src/unidentified/unassigned_0041c020.cpp`

```cpp
// 0x0041C020: empty function. Retail's complete body is a single RET -- the
// tail an override whose work the whole-program pass removed leaves.
extern "C" void __cdecl asm_unassigned_0041c020(void) {
}
```

#### 0x0041C2F0 - 27 bytes - `?ScoreExtendedObject_Destroy_DeletingDestructor_0041c2f0@@YGPAXPAUOwnedObject_0041c2f0@@I@Z`

`src/unidentified/unassigned_0041c2f0.cpp`

```cpp
// 0x0041c2f0: scalar deleting destructor. Retail keeps the object in ESI and the
// delete flag in the first stack argument, so this body is a cluster whose
// synthetic caller walks an array of the objects.

struct OwnedObject_0041c2f0;
extern "C" void asm_ScoreExtendedObject_DestroyRetail_0041c1c0(void* object);
extern "C" void __cdecl entry_free_004524a1(void* memory);
__declspec(noinline) void* ScoreExtendedObject_Destroy_DeletingDestructor_0041c2f0(OwnedObject_0041c2f0* object, unsigned int flags);
#pragma code_seg(".text$01delete0041c2f0")
void* ScoreExtendedObject_Destroy_DeletingDestructor_0041c2f0(OwnedObject_0041c2f0* object, unsigned int flags) {
    asm_ScoreExtendedObject_DestroyRetail_0041c1c0(object);
    if (flags & 1) entry_free_004524a1(object);
    return object;
}
#pragma code_seg()
```

#### 0x0041C310 - 18 bytes - `?ReleaseOwned_0041c310@@YGXPAUOwnedObject_0041c310@@@Z`

`src/unidentified/unassigned_0041c310.cpp`

```cpp
// 0x0041c310: release an owned object and free it. Retail keeps the object in ESI.

struct OwnedObject_0041c310;
extern "C" void asm_ScoreExtendedObject_DestroyRetail_0041c1c0(void* object);
extern "C" void __cdecl entry_free_004524a1(void* memory);
__declspec(noinline) void ReleaseOwned_0041c310(OwnedObject_0041c310* object);
#pragma code_seg(".text$01release0041c310")
void ReleaseOwned_0041c310(OwnedObject_0041c310* object) {
    if (object) {
        asm_ScoreExtendedObject_DestroyRetail_0041c1c0(object);
        entry_free_004524a1(object);
    }
}
#pragma code_seg()
```

#### 0x0041C450 - 43 bytes - `?Process_0041c450@@YGHPAUObjectAccessor_0041c450@@@Z`

`src/unidentified/unassigned_0041c450.cpp`

```cpp
// 0x0041C450: dispatch every list entry that is not the primary kind
// The register convention below is only reachable from a native LTCG link,
// so this region is compiled as a cluster.

struct Item_0041c450 {
    virtual void Slot00();
    virtual void Slot01();
    virtual void Slot02();
    virtual void Slot03();
    unsigned char pad_004[0x08 - 0x04];
    Item_0041c450* next;   // +0x08
    int kind;                                               // +0x0C
};

struct ObjectAccessor_0041c450 {
    unsigned char pad_000[0x18];
    Item_0041c450* head;    // +0x18
};

__declspec(noinline) void Slot03() {}

__declspec(noinline) int Process_0041c450(ObjectAccessor_0041c450* object);
#pragma code_seg(".text$01accessor")
int Process_0041c450(ObjectAccessor_0041c450* object) {
    Item_0041c450* item = object->head;
    if (item != 0) {
        do {
            Item_0041c450* next = item->next;
            if (item->kind != 1) {
                item->Slot03();
            }
            item = next;
        } while (item != 0);
    }
    return 1;
}
#pragma code_seg()
```

#### 0x0041F760 - 25 bytes - `?DistanceSquared@Vector2_0041f760@@QBEMPBU1@@Z`

`src/unidentified/unassigned_0041f760.cpp`

```cpp
// 0x0041F760: squared distance to the other vector
// The register convention below is only reachable from a native LTCG link,
// so this region is compiled as a cluster.

struct Vector2_0041f760 {
    float x;
    float y;
    __declspec(noinline) float DistanceSquared(const Vector2_0041f760* other) const;
};
#pragma code_seg(".text$01accessor")
float Vector2_0041f760::DistanceSquared(const Vector2_0041f760* other) const {
    float dy = y - other->y;
    float dx = x - other->x;
    return dx * dx + dy * dy;
}
#pragma code_seg()
```

#### 0x0041F820 - 19 bytes - `?UpdateFlag@ObjectAccessor_0041f820@@QAEXXZ`

`src/unidentified/unassigned_0041f820.cpp`

```cpp
// 0x0041F820: clear 0x20 and set 0x10 at +0x35C
// The object pointer arrives in EAX, which only a native LTCG link chooses, so
// this region is compiled as a cluster.

struct ObjectAccessor_0041f820 {
    unsigned char pad_000[0x35C];
    unsigned int field_35C;
    __declspec(noinline) void UpdateFlag();
};

#pragma code_seg(".text$01accessor")
void ObjectAccessor_0041f820::UpdateFlag() {
    field_35C = (field_35C & ~0x20u) | 0x10u;
}
#pragma code_seg()
```

#### 0x0041F840 - 1 bytes - `_asm_unassigned_0041f840`

`src/unidentified/unassigned_0041f840.cpp`

```cpp
// 0x0041F840: empty function. Retail's complete body is a single RET -- the
// tail an override whose work the whole-program pass removed leaves.
extern "C" void __cdecl asm_unassigned_0041f840(void) {
}
```

#### 0x0041FD50 - 27 bytes - `?DestroyOwned_DeletingDestructor_0041fd50@@YGPAXPAUOwnedObject_0041fd50@@I@Z`

`src/unidentified/unassigned_0041fd50.cpp`

```cpp
// 0x0041fd50: scalar deleting destructor. Retail keeps the object in ESI and the
// delete flag in the first stack argument, so this body is a cluster whose
// synthetic caller walks an array of the objects.

struct OwnedObject_0041fd50;
extern "C" void asm_FUN_0041fb50_0041fb50(void* object);
extern "C" void __cdecl entry_free_004524a1(void* memory);
__declspec(noinline) void* DestroyOwned_DeletingDestructor_0041fd50(OwnedObject_0041fd50* object, unsigned int flags);
#pragma code_seg(".text$01delete0041fd50")
void* DestroyOwned_DeletingDestructor_0041fd50(OwnedObject_0041fd50* object, unsigned int flags) {
    asm_FUN_0041fb50_0041fb50(object);
    if (flags & 1) entry_free_004524a1(object);
    return object;
}
#pragma code_seg()
```

#### 0x0041FD70 - 18 bytes - `?ReleaseOwned_0041fd70@@YGXPAUOwnedObject_0041fd70@@@Z`

`src/unidentified/unassigned_0041fd70.cpp`

```cpp
// 0x0041fd70: release an owned object and free it. Retail keeps the object in ESI.

struct OwnedObject_0041fd70;
extern "C" void asm_FUN_0041fb50_0041fb50(void* object);
extern "C" void __cdecl entry_free_004524a1(void* memory);
__declspec(noinline) void ReleaseOwned_0041fd70(OwnedObject_0041fd70* object);
#pragma code_seg(".text$01release0041fd70")
void ReleaseOwned_0041fd70(OwnedObject_0041fd70* object) {
    if (object) {
        asm_FUN_0041fb50_0041fb50(object);
        entry_free_004524a1(object);
    }
}
#pragma code_seg()
```

#### 0x0041FF00 - 34 bytes - `?Mark_0041ff00@@YGXPAUObjectAccessor_0041ff00@@@Z`

`src/unidentified/unassigned_0041ff00.cpp`

```cpp
// 0x0041FF00: mark the three owned slots with bit 1
// The leading parameter arrives in EAX, a convention only a native LTCG link
// chooses, so this region is compiled as a cluster.

struct Flagged_0041ff00 {
    unsigned char pad_000[0x04];
    unsigned int flags;
};

struct ObjectAccessor_0041ff00 {
    unsigned char pad_000[0x0C];
    Flagged_0041ff00* first;
    Flagged_0041ff00* second;
    unsigned char pad_014[0x89A8 - 0x14];
    Flagged_0041ff00* third;
};

void __declspec(noinline) Mark_0041ff00(ObjectAccessor_0041ff00* object);
#pragma code_seg(".text$01accessor")
void Mark_0041ff00(ObjectAccessor_0041ff00* object) {
    object->first->flags |= 2u;
    object->second->flags |= 2u;
    object->third->flags |= 2u;
}
#pragma code_seg()
```

#### 0x0041FF40 - 13 bytes - `?LoadFlag@ObjectAccessor_0041ff40@@QBEIXZ`

`src/unidentified/unassigned_0041ff40.cpp`

```cpp
// 0x0041FF40: test bit 4 of the word at +0x150
// The object pointer arrives in EAX, which only a native LTCG link chooses, so
// this region is compiled as a cluster.

struct ObjectAccessor_0041ff40 {
    unsigned char pad_000[0x150];
    unsigned int field_150;
    __declspec(noinline) unsigned int LoadFlag() const;
};

#pragma code_seg(".text$01accessor")
unsigned int ObjectAccessor_0041ff40::LoadFlag() const {
    return (field_150 >> 4) & 1u;
}
#pragma code_seg()
```

#### 0x0041FF50 - 1 bytes - `_asm_unassigned_0041ff50`

`src/unidentified/unassigned_0041ff50.cpp`

```cpp
// 0x0041FF50: empty function. Retail's complete body is a single RET -- the
// tail an override whose work the whole-program pass removed leaves.
extern "C" void __cdecl asm_unassigned_0041ff50(void) {
}
```

## Dropped (31)

| address | bytes | status |
| --- | ---: | --- |
| `0x00412300` | 64 | four-way jump-table leaf; the table at 0x412340 is a sibling region |
| `0x004126D0` | 64 | four-way jump-table leaf; the table at 0x412710 is a sibling region |
| `0x00412750` | 56 | EDX + ESI + ECX plus three stack arguments; no driver shape reached it |
| `0x00412A80` | 17 | needs an anchor: callee 0x44FF00 takes its record in EDX with two register arguments passed through |
| `0x00412E10` | 20 | needs an anchor: callee 0x44C350 takes an argument in EAX plus a float on the stack |
| `0x00412E30` | 37 | region spans two complete functions (0x412E30 and 0x412E40) |
| `0x00412E60` | 16 | 4 shapes; native pass puts destination in EDX, addends in ECX/EAX - retail wants destination in EAX |
| `0x00413050` | 17 | 5 spellings of the comparison; the allocator loads the field into ECX - retail loads it into EDX |
| `0x00413070` | 33 | region spans two complete functions (0x413070 and 0x413080) |
| `0x004132C0` | 50 | EBX/EDI/ESI frame around 0x449ED0 and 0x449B70 |
| `0x00413B50` | 50 | the log call 0x44B810 is variadic; MSVC 13.10 compiles a variadic member as __cdecl (this on the stack) while retail passes this in ECX |
| `0x00413B90` | 47 | needs an anchor: callee 0x447810 takes its pointer in EDI |
| `0x00414550` | 30 | needs an anchor: callee 0x4136C0 is reached with the object in ESI and EAX as the entry argument |
| `0x00417660` | 16 | 5 spellings of the comparison; the allocator loads the field into ECX - retail loads it into EDX |
| `0x00417720` | 10 | needs an anchor: tail `add eax,9E14h; jmp 0x409E50` - 0x409E50's receiver is in EAX |
| `0x004177C0` | 25 | 7 spellings; second store base lands in ECX (this) instead of EAX |
| `0x004177E0` | 25 | 7 spellings; second store base lands in ECX (this) instead of EAX |
| `0x00417840` | 33 | needs an anchor: callee 0x418C40 takes its argument in EDX |
| `0x004187F0` | 29 | 4 shapes (incl. pooled literals); native pass puts source in EAX and destination in ECX - retail wants destination in EAX |
| `0x00418A50` | 17 | 5 spellings of the comparison; the allocator loads the field into ECX - retail loads it into EDX |
| `0x00418C30` | 10 | needs an anchor: callee 0x418C40 takes its argument in EDX |
| `0x004198AA` | 6 | six `int 3` alignment-padding bytes |
| `0x004198B6` | 10 | ten `int 3` alignment-padding bytes |
| `0x00419930` | 35 | four-register search (table EDI, count EDX, key ESI); no driver shape reached that assignment |
| `0x0041ACB0` | 54 | EH vector constructor 0x45252D plus a `rep stosd` frame |
| `0x0041BA4D` | 3 | three `int 3` alignment-padding bytes |
| `0x0041BE40` | 46 | needs an anchor: callee 0x404F30 is reached with EAX = object+0x176 |
| `0x0041C0A0` | 41 | region spans two complete functions (0x41C0A0 and 0x41C0B0) |
| `0x0041C84C` | 4 | four `int 3` alignment-padding bytes |
| `0x0041F780` | 31 | 3 shapes; native pass puts destination in ECX and source in EAX - retail wants destination in EAX |
| `0x0041FD90` | 63 | modelled exactly; emitted 75 bytes against the region 63, never converged |

### Byte-level deltas of the attempted drops

* **0x00412E60** (16 bytes) - first difference at 0x00412E64; expected `42 04` (`fadd [edx+0x4]`), emitted `40 04` (`fadd [eax+0x4]`).
* **0x0041F780** (31 bytes) - first difference at 0x0041F785; expected `49 08` (`fmul [ecx+0x8]`), emitted `48 08` (`fmul [eax+0x8]`).
* **0x004187F0** (29 bytes) - first difference at 0x004187F1; expected `01` (`fld [ecx]`), emitted `00` (`fld [eax]`).
* **0x00413050** (17 bytes) - first difference at 0x00413051; expected `51 04` (`mov edx,[ecx+0x4]`), emitted `49 04` (`mov ecx,[ecx+0x4]`).
* **0x00417660** (16 bytes) - first difference at 0x00417661; expected `11` (`mov edx,[ecx]`), emitted `09` (`mov ecx,[ecx]`).
* **0x00418A50** (17 bytes) - first difference at 0x00418A51; expected `51 04` (`mov edx,[ecx+0x4]`), emitted `49 04` (`mov ecx,[ecx+0x4]`).
* **0x004177C0** (25 bytes) - first difference at 0x004177D2; expected `41 0c` (`mov eax,[ecx+0xc]`), emitted `49 0c` (`mov ecx,[ecx+0xc]`).
* **0x004177E0** (25 bytes) - first difference at 0x004177F2; expected `41 0c` (`mov eax,[ecx+0xc]`), emitted `49 0c` (`mov ecx,[ecx+0xc]`).
* **0x0041FD90** (63 bytes) - never EXACT; expected -, emitted emitted body 75 bytes (12 over the region).

Every other drop was never modelled, so it has no byte delta: the reason column
above is what blocks it.

## Transferable findings

1. **The native pass assigns the *first* parameter of a small function to EAX,
   but only when it is the sole interesting operand.** With a second pointer or a
   mask argument the assignment is usage-driven: `this`/destination in EAX for a
   1-argument member or 2-argument free function, but it flips to ECX when the
   *other* operand is read more often than the receiver is written (0x4187F0,
   0x41F780) and to EDX for a 3-argument free function (0x412E60, 0x412790).
   `0x00412790` landed only after the parameter order was rotated to
   `(value, index, base)` so the pass put the index in EAX, the base in ECX and
   the value in EDX, which is retail's triplet. **Reordering the modelled
   parameters is a real lever** and it is much cheaper than adding a driver.
2. **A `memset` of the exact block size reproduces `rep stosd` byte-for-byte**,
   including the `push edi / mov ecx,N / xor eax,eax / mov edi,reg / pop edi`
   frame (0x413190, 0x4132A0). A hand-written `for` loop does not.
3. **A float literal plus `constant_aliases` is what fixes the x87 operand
   order** for a store-through-pair like 0x4187F0: with `extern "C" float
   data_00470b4c` the constant loads first, with the literal `224.0f` aliased to
   0x470B4C the source loads first, exactly as retail does. The register pair was
   the only thing left over.
4. **A do-while reproduces retail's rotated loop with its 6-byte `jmp`/NOP
   padding** where a `for` loop does not (0x41C450).
5. **Two adjacent stores through freshly loaded pointers keep `this`'s register
   for the second base** under /O2 for every spelling tried (0x4177C0/0x4177E0);
   that pair is a pure allocator tie-break and needs the whole-program pass, not
   another source shape.

## Files

* 93 sources under `src/unidentified/` and `src/game/`, one per region.
* Cluster layouts and drivers promoted with the sources, named `layout/ltcg/cl_<addr>.json`
  and `layout/ltcg/cl_<addr>_context.cpp` (plus `acc_*` for the accessor family).
* No file outside this block was touched.
