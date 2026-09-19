# ESI deleting destructors (wave 19) - all sixteen landed EXACT

2026-09-19, agent `DeletingDtors`.  Scope: the sixteen ESI-receiver deleting
destructors that the `0x40` block agent listed as "not attempted" in
`0040xxxx_wave18.md` (its section 2).  Work was done in `/tmp/DeletingDtors/msvc`
(`cp -a matching2/msvc`); the final registration went through
`register_cluster.py --apply` on the maintained tree, one single-source layout per
region.

**16 of 16 landed EXACT (246 bytes), 0 dropped.**  Every landing was probed
against the maintained tree after registration and reports `EXACT`; the whole
cluster set (494 layouts, up from 478) loads, and the manifest reads 4425 regions.
Because all sixteen landed there is no drop list - the family's second shape,
which the wave-18 note suspected was unlandable, is modelled below.

| address | size | shape | cleanup callee | layout |
| --- | ---: | --- | --- | --- |
| `0x00401490` | 27 | deleting destructor | `0x401260` | `dtor_delete_00401490` |
| `0x004014B0` | 18 | null-checked release | `0x401260` | `dtor_release_004014b0` |
| `0x004026E0` | 27 | deleting destructor | `0x402440` | `dtor_delete_004026e0` |
| `0x00402700` | 18 | null-checked release | `0x402440` | `dtor_release_00402700` |
| `0x00405710` | 27 | deleting destructor | `0x405620` | `dtor_delete_00405710` |
| `0x00406120` | 27 | deleting destructor | `0x405F70` | `dtor_delete_00406120` |
| `0x00408D20` | 27 | deleting destructor | `0x408AF0` | `dtor_delete_00408d20` |
| `0x00408D40` | 18 | null-checked release | `0x408AF0` | `dtor_release_00408d40` |
| `0x0040A410` | 27 | deleting destructor | `0x40A1A0` | `dtor_delete_0040a410` |
| `0x0040A430` | 18 | null-checked release | `0x40A1A0` | `dtor_release_0040a430` |
| `0x0040AFF0` | 27 | deleting destructor | `0x40AF00` | `dtor_delete_0040aff0` |
| `0x0040B010` | 18 | null-checked release | `0x40AF00` | `dtor_release_0040b010` |
| `0x0040B920` | 28 | deleting destructor, EAX-convention cleanup | `0x40B3A0` | `dtor_delete_0040b920` |
| `0x0040B9B0` | 27 | deleting destructor | `0x40B7B0` | `dtor_delete_0040b9b0` |
| `0x0040D660` | 30 | deleting destructor, EAX receiver, ESI preserved | `0x40D680` | `dtor_delete_0040d660` |
| `0x0040D710` | 28 | deleting destructor, EAX-convention cleanup | `0x40D530` | `dtor_delete_0040d710` |

### Probe lines (maintained tree, after registration)

```text
0x00401490      27 bytes  ?Deletable_00401490_Delete@@YGPAXPAUDeletable_00401490@@H@Z  EXACT   src/unidentified/unassigned_00401490.cpp
0x004014b0      18 bytes  ?Destroyable_004014b0_Release@@YGXPAUDestroyable_004014b0@@@Z  EXACT   src/unidentified/unassigned_004014b0.cpp
0x004026e0      27 bytes  ?Deletable_004026e0_Delete@@YGPAXPAUDeletable_004026e0@@H@Z  EXACT   src/unidentified/unassigned_004026e0.cpp
0x00402700      18 bytes  ?Destroyable_00402700_Release@@YGXPAUDestroyable_00402700@@@Z  EXACT   src/unidentified/unassigned_00402700.cpp
0x00405710      27 bytes  ?Deletable_00405710_Delete@@YGXPAUDeletable_00405710@@H@Z  EXACT   src/unidentified/unassigned_00405710.cpp
0x00406120      27 bytes  ?Deletable_00406120_Delete@@YGXPAUDeletable_00406120@@H@Z  EXACT   src/unidentified/unassigned_00406120.cpp
0x00408d20      27 bytes  ?Deletable_00408d20_Delete@@YGXPAUDeletable_00408d20@@H@Z  EXACT   src/unidentified/unassigned_00408d20.cpp
0x00408d40      18 bytes  ?Destroyable_00408d40_Release@@YGXPAUDestroyable_00408d40@@@Z  EXACT   src/unidentified/unassigned_00408d40.cpp
0x0040a410      27 bytes  ?Deletable_0040a410_Delete@@YGPAXPAUDeletable_0040a410@@H@Z  EXACT   src/unidentified/unassigned_0040a410.cpp
0x0040a430      18 bytes  ?Destroyable_0040a430_Release@@YGXPAUDestroyable_0040a430@@@Z  EXACT   src/unidentified/unassigned_0040a430.cpp
0x0040aff0      27 bytes  ?Deletable_0040aff0_Delete@@YGPAXPAUDeletable_0040aff0@@H@Z  EXACT   src/unidentified/unassigned_0040aff0.cpp
0x0040b010      18 bytes  ?Destroyable_0040b010_Release@@YGXPAUDestroyable_0040b010@@@Z  EXACT   src/unidentified/unassigned_0040b010.cpp
0x0040b920      28 bytes  ?Deletable_0040b920_Delete@@YGPAXPAUDeletable_0040b920@@H@Z  EXACT   src/unidentified/unassigned_0040b920.cpp
0x0040b9b0      27 bytes  ?Deletable_0040b9b0_Delete@@YGPAXPAUDeletable_0040b9b0@@H@Z  EXACT   src/unidentified/unassigned_0040b9b0.cpp
0x0040d660      30 bytes  ?Delete@Releaseable_0040d660@@QAEPAXH@Z  EXACT   src/unidentified/unassigned_0040d660.cpp
0x0040d710      28 bytes  ?Deletable_0040d710_Delete@@YGPAXPAUDeletable_0040d710@@H@Z  EXACT   src/unidentified/unassigned_0040d710.cpp
```

The 28/30-byte entries are the 27-byte shape with one extra instruction: `0x40B920`
and `0x40D710` add a `mov eax,esi` because their cleanup reads EAX, and `0x40D660`
adds `push esi`/`pop esi` because its cleanup reads ESI.

## The reading of the family

Two shapes, both entered with the object in ESI:

```text
push esi / call <cleanup> / test byte [esp+4],1 / je L / push esi / call free /
    add esp,4 / L: mov eax,esi / ret 4                       (27 bytes)
test esi,esi / je L / push esi / call <cleanup> / push esi / call free /
    pop ecx / L: ret                                          (18 bytes)
```

**The 27-byte form tests the delete-flag argument, not the return address.**  The
wave-18 note read `test byte [esp+4],1` as testing the low byte of the pushed
return address and concluded the shape was only self-consistent for a function
that is never called.  That reading assumed the `push esi` before the cleanup is
still on the stack when the test runs.  It is not: every cleanup callee is a
`__stdcall` function that pops its own argument, which is why the source declares
it as an ordinary one-argument `extern "C"` function and the compiler emits no
`add esp,4` after the call.  Measured on all eight callees, each ends in `ret 4`:

```text
0x401260 ret 4   0x402440 ret 4   0x405620 ret 4   0x405F70 ret 4
0x408AF0 ret 4   0x40A1A0 ret 4   0x40AF00 ret 4   0x40B7B0 ret 4
```

so after `push esi; call cleanup` the stack is back to its entry state and
`[esp+4]` is the first stack argument - the flags dword that `ret 4` pops at the
end.  The 27-byte shape is therefore `T* Destroy(unsigned flags)` with the object
in ESI, `__thiscall`-like in its stack behaviour (one dword, callee-pops) and a
private receiver register.  It is a completely ordinary scalar deleting
destructor and lands as one.

The `push esi` is the cleanup call's argument setup, not a register save, which is
also why ESI is never popped: the object arrives in ESI and belongs to the caller.

The 18-byte form is `void Release(T* object)` with the same ESI receiver: a null
test, then cleanup and free.  Both forms balance the `__cdecl` free - `add esp,4`
in the 27-byte body, the 1-byte `pop ecx` in the 18-byte body - with the same
`entry_free_004524a1` declaration.

## The two driver templates

Thirteen of the sixteen are the two templates below, unchanged from the
already-registered `dtor_delete_004223b0` / `dtor_release_004223d0` pair: a
`__stdcall` free function whose object parameter the whole-program pass puts in
ESI, plus the array-walk caller.  Only the class name, the cleanup symbol and the
addresses change per landing.

`layout/ltcg/dtor_delete_<addr>_context.cpp` (27/28-byte shape):

```cpp
// Compiler context only; never selected as recovered game code.
#include "../../src/unidentified/unassigned_00401490.cpp"

#pragma code_seg(".text$03context")
extern "C" int __stdcall DtorDeleteContext_00401490(Deletable_00401490** items, int count) {
    int freed = 0;
    while (count--) {
        freed += Deletable_00401490_Delete(*items++, 1) != 0;
    }
    return freed;
}
#pragma code_seg()```

`layout/ltcg/dtor_release_<addr>_context.cpp` (18-byte shape):

```cpp
// Compiler context only; never selected as recovered game code.
#include "../../src/unidentified/unassigned_004014b0.cpp"

#pragma code_seg(".text$03context")
extern "C" int __stdcall DtorReleaseContext_004014b0(Destroyable_004014b0** items, int count) {
    while (count--) {
        Destroyable_004014b0_Release(*items++);
    }
    return 0;
}
#pragma code_seg()```

The layouts are the same as `dtor_delete_004223b0.json` / `dtor_release_004223d0.json`
in structure: the first gap runs from `0x00401000` to the function, the second
from the function's end to the context, and the two bound callees are
`_<cleanup>@4` and `_entry_free_004524a1`, both `relative_code`.

## The three that need an ABI anchor

`0x40B920`, `0x40D710` and `0x40D660` call cleanups whose object register no
declaration names - EAX for the first two, ESI for the third - so the callee
cannot be bound absolutely: an undefined symbol keeps whatever convention its
declaration gives it (never EAX).  Each of the three compiles the cleanup's body
into the same link as an **ABI anchor** (`anchors`, the mechanism the wave-10/11/12
layouts use): the section is placed at the callee's retail address by the gaps, the
pass assigns the register, the caller's `call rel32` bakes retail's own
displacement, and none of the anchor's bytes are exported as recovered code.

`0x40B920` / `0x40D710` - the object stays in ESI across the call (its live range
reaches the `free` and the return) and the cleanup wants it in EAX, so the pass
emits retail's `mov eax,esi; call`.  The caller is modelled exactly like the
27-byte template; only the cleanup declaration (`__cdecl`, one pointer, so the
anchor's body decides the register rather than the declaration) and the anchor
differ:

```cpp
// Compiler context and ABI anchor only; none of these bytes enter the image.
#include "../../src/unidentified/unassigned_0040b920.cpp"

// As 0x0040B3A0 reads it: a slot word at +0x40.
struct AnchorEntity_0040b920 {
    unsigned char reserved_000[0x40];
    unsigned int slot;
};

// 0x0040B3A0's body.  It is compiled only so the whole-program pass can hand it
// the object in EAX: its only caller is the modelled deleting destructor and no
// declaration names that register.  The layout's gaps place this section at the
// retail address, so the destructor's call bakes retail's own displacement.
// None of these bytes are selected as recovered code.
#pragma code_seg(".text$01anchor")
extern "C" __declspec(noinline) void __cdecl asm_FUN_0040b3a0_0040b3a0(void* object) {
    AnchorEntity_0040b920* entity = (AnchorEntity_0040b920*)object;
    entity->slot = 0;
}
#pragma code_seg()

#pragma code_seg(".text$05context")
extern "C" int __stdcall DtorDeleteContext_0040b920(Deletable_0040b920** items, int count) {
    int freed = 0;
    while (count--) {
        freed += Deletable_0040b920_Delete(*items++, 1) != 0;
    }
    return freed;
}
#pragma code_seg()```

For `0x40D710` the same driver with `0x40D530` / `asm_FUN_0040d530_0040d530` and
slot offset `+0x08` produces `mov eax,esi; call 0x40D530` in the same way.

`0x40D660` - the cleanup (`0x40D680` `BulletEntity::ReleaseResource`, already
landed semantic with `this` in ESI) needs ESI, the object arrives in a
caller-saved register, and ESI is saved and restored around the call.  Modelling
the body as a **member function** (`__thiscall`: one stack argument, callee pops,
so retail's `ret 4`) puts the receiver in EAX and lets the pass spill it into
callee-saved ESI for the call, exactly as retail:

```cpp
// Compiler context and ABI anchor only; none of these bytes enter the image.
#include "../../src/unidentified/unassigned_0040d660.cpp"

extern "C" void __cdecl entry_free_00452422(void* memory);

// 0x0040D680's body, compiled only so the whole-program pass can carry its
// object in ESI: no declaration names that register, and the pointer has to
// outlive the free.  The layout's gaps place this section at the retail
// address, so the destructor's call bakes retail's own displacement.  None of
// these bytes are selected as recovered code.
#pragma code_seg(".text$03anchor")
void BulletEntity_0040d680::ReleaseResource() {
    void* const resource = owned_resource;
    vtable = 0x0046D0F0;
    if (resource != 0) {
        entry_free_00452422(resource);
        owned_resource = 0;
    }
}
#pragma code_seg()

#pragma code_seg(".text$05context")
extern "C" int __stdcall DtorDeleteContext_0040d660(Releaseable_0040d660** items, int count) {
    int freed = 0;
    while (count--) {
        freed += (*items++)->Delete(1) != 0;
    }
    return freed;
}
#pragma code_seg()```

Its anchor is the landed `?ReleaseResource@BulletEntity_0040d680@@QAEXXZ`, 36
bytes - the modelled body compiles to retail's own size - and the function's
region ends 2 bytes before the anchor, so the middle gap is 2 bytes.

## Source text per landing

#### `0x00401490` (27 bytes, cluster) - `src/unidentified/unassigned_00401490.cpp`

layout `layout/ltcg/dtor_delete_00401490.json`, symbol `?Deletable_00401490_Delete@@YGPAXPAUDeletable_00401490@@H@Z`

```cpp
// 0x00401490..0x004014AB (27 bytes): scalar deleting destructor.
//
// Retail runs the object cleanup at 0x00401260 -- the callee takes the object
// as a stack argument and cleans it (RET 4) -- then, when bit 0 of the incoming
// flags is set, hands the object to the CRT free entry at 0x004524A1, and
// finally returns the object in EAX.  The object lives in ESI across both calls,
// a receiver no C++ declaration names, so the body is compiled in the
// native-LTCG cluster layout/ltcg/dtor_delete_00401490.json whose array-walking synthetic
// caller establishes that convention.

extern "C" void asm_DestroyGameThread_00401260(void* object);
extern "C" void __cdecl entry_free_004524a1(void* block);

struct Deletable_00401490 {
    unsigned char unknown_0000[0x04];
};

__declspec(noinline) void* Deletable_00401490_Delete(Deletable_00401490* object, int flags);

#pragma code_seg(".text$01del")
void* Deletable_00401490_Delete(Deletable_00401490* object, int flags) {
    asm_DestroyGameThread_00401260(object);
    if ((flags & 1) != 0) {
        entry_free_004524a1(object);
    }
    return object;
}
#pragma code_seg()
```

#### `0x004014B0` (18 bytes, cluster) - `src/unidentified/unassigned_004014b0.cpp`

layout `layout/ltcg/dtor_release_004014b0.json`, symbol `?Destroyable_004014b0_Release@@YGXPAUDestroyable_004014b0@@@Z`

```cpp
// 0x004014B0..0x004014C2 (18 bytes): release a possibly-absent object.
//
// Retail answers a null object immediately; otherwise it runs the cleanup at
// 0x00401260 (the callee takes the object as a stack argument and cleans it,
// RET 4), hands the object to the CRT free entry at 0x004524A1 and returns.
// The object lives in ESI, so the body is compiled in the native-LTCG cluster
// layout/ltcg/dtor_release_004014b0.json whose array-walking synthetic caller establishes that
// convention.

extern "C" void asm_DestroyGameThread_00401260(void* object);
extern "C" void __cdecl entry_free_004524a1(void* block);

struct Destroyable_004014b0 {
    unsigned char unknown_0000[0x04];
};

__declspec(noinline) void Destroyable_004014b0_Release(Destroyable_004014b0* object);

#pragma code_seg(".text$01rel")
void Destroyable_004014b0_Release(Destroyable_004014b0* object) {
    if (object != 0) {
        asm_DestroyGameThread_00401260(object);
        entry_free_004524a1(object);
    }
}
#pragma code_seg()
```

#### `0x004026E0` (27 bytes, cluster) - `src/unidentified/unassigned_004026e0.cpp`

layout `layout/ltcg/dtor_delete_004026e0.json`, symbol `?Deletable_004026e0_Delete@@YGPAXPAUDeletable_004026e0@@H@Z`

```cpp
// 0x004026E0..0x004026FB (27 bytes): scalar deleting destructor.
//
// Retail runs the object cleanup at 0x00402440 -- the callee takes the object
// as a stack argument and cleans it (RET 4) -- then, when bit 0 of the incoming
// flags is set, hands the object to the CRT free entry at 0x004524A1, and
// finally returns the object in EAX.  The object lives in ESI across both calls,
// a receiver no C++ declaration names, so the body is compiled in the
// native-LTCG cluster layout/ltcg/dtor_delete_004026e0.json whose array-walking synthetic
// caller establishes that convention.

extern "C" void asm_DestroyGameState_00402440(void* object);
extern "C" void __cdecl entry_free_004524a1(void* block);

struct Deletable_004026e0 {
    unsigned char unknown_0000[0x04];
};

__declspec(noinline) void* Deletable_004026e0_Delete(Deletable_004026e0* object, int flags);

#pragma code_seg(".text$01del")
void* Deletable_004026e0_Delete(Deletable_004026e0* object, int flags) {
    asm_DestroyGameState_00402440(object);
    if ((flags & 1) != 0) {
        entry_free_004524a1(object);
    }
    return object;
}
#pragma code_seg()
```

#### `0x00402700` (18 bytes, cluster) - `src/unidentified/unassigned_00402700.cpp`

layout `layout/ltcg/dtor_release_00402700.json`, symbol `?Destroyable_00402700_Release@@YGXPAUDestroyable_00402700@@@Z`

```cpp
// 0x00402700..0x00402712 (18 bytes): release a possibly-absent object.
//
// Retail answers a null object immediately; otherwise it runs the cleanup at
// 0x00402440 (the callee takes the object as a stack argument and cleans it,
// RET 4), hands the object to the CRT free entry at 0x004524A1 and returns.
// The object lives in ESI, so the body is compiled in the native-LTCG cluster
// layout/ltcg/dtor_release_00402700.json whose array-walking synthetic caller establishes that
// convention.

extern "C" void asm_DestroyGameState_00402440(void* object);
extern "C" void __cdecl entry_free_004524a1(void* block);

struct Destroyable_00402700 {
    unsigned char unknown_0000[0x04];
};

__declspec(noinline) void Destroyable_00402700_Release(Destroyable_00402700* object);

#pragma code_seg(".text$01rel")
void Destroyable_00402700_Release(Destroyable_00402700* object) {
    if (object != 0) {
        asm_DestroyGameState_00402440(object);
        entry_free_004524a1(object);
    }
}
#pragma code_seg()
```

#### `0x00405710` (27 bytes, cluster) - `src/unidentified/unassigned_00405710.cpp`

layout `layout/ltcg/dtor_delete_00405710.json`, symbol `?Deletable_00405710_Delete@@YGPAXPAUDeletable_00405710@@H@Z`

```cpp
// 0x00405710..0x0040572B (27 bytes): scalar deleting destructor.
//
// Retail runs the object cleanup at 0x00405620 -- the callee takes the object
// as a stack argument and cleans it (RET 4) -- then, when bit 0 of the incoming
// flags is set, hands the object to the CRT free entry at 0x004524A1, and
// finally returns the object in EAX.  The object lives in ESI across both calls,
// a receiver no C++ declaration names, so the body is compiled in the
// native-LTCG cluster layout/ltcg/dtor_delete_00405710.json whose array-walking synthetic
// caller establishes that convention.

extern "C" void asm_Recovery_ReleaseRawPairAndReset_00405620(void* object);
extern "C" void __cdecl entry_free_004524a1(void* block);

struct Deletable_00405710 {
    unsigned char unknown_0000[0x04];
};

__declspec(noinline) void* Deletable_00405710_Delete(Deletable_00405710* object, int flags);

#pragma code_seg(".text$01del")
void* Deletable_00405710_Delete(Deletable_00405710* object, int flags) {
    asm_Recovery_ReleaseRawPairAndReset_00405620(object);
    if ((flags & 1) != 0) {
        entry_free_004524a1(object);
    }
    return object;
}
#pragma code_seg()
```

#### `0x00406120` (27 bytes, cluster) - `src/unidentified/unassigned_00406120.cpp`

layout `layout/ltcg/dtor_delete_00406120.json`, symbol `?Deletable_00406120_Delete@@YGPAXPAUDeletable_00406120@@H@Z`

```cpp
// 0x00406120..0x0040613B (27 bytes): scalar deleting destructor.
//
// Retail runs the object cleanup at 0x00405F70 -- the callee takes the object
// as a stack argument and cleans it (RET 4) -- then, when bit 0 of the incoming
// flags is set, hands the object to the CRT free entry at 0x004524A1, and
// finally returns the object in EAX.  The object lives in ESI across both calls,
// a receiver no C++ declaration names, so the body is compiled in the
// native-LTCG cluster layout/ltcg/dtor_delete_00406120.json whose array-walking synthetic
// caller establishes that convention.

extern "C" void asm_ItemManager_DestroyRetail_00405f70(void* object);
extern "C" void __cdecl entry_free_004524a1(void* block);

struct Deletable_00406120 {
    unsigned char unknown_0000[0x04];
};

__declspec(noinline) void* Deletable_00406120_Delete(Deletable_00406120* object, int flags);

#pragma code_seg(".text$01del")
void* Deletable_00406120_Delete(Deletable_00406120* object, int flags) {
    asm_ItemManager_DestroyRetail_00405f70(object);
    if ((flags & 1) != 0) {
        entry_free_004524a1(object);
    }
    return object;
}
#pragma code_seg()
```

#### `0x00408D20` (27 bytes, cluster) - `src/unidentified/unassigned_00408d20.cpp`

layout `layout/ltcg/dtor_delete_00408d20.json`, symbol `?Deletable_00408d20_Delete@@YGPAXPAUDeletable_00408d20@@H@Z`

```cpp
// 0x00408D20..0x00408D3B (27 bytes): scalar deleting destructor.
//
// Retail runs the object cleanup at 0x00408AF0 -- the callee takes the object
// as a stack argument and cleans it (RET 4) -- then, when bit 0 of the incoming
// flags is set, hands the object to the CRT free entry at 0x004524A1, and
// finally returns the object in EAX.  The object lives in ESI across both calls,
// a receiver no C++ declaration names, so the body is compiled in the
// native-LTCG cluster layout/ltcg/dtor_delete_00408d20.json whose array-walking synthetic
// caller establishes that convention.

extern "C" void asm_FUN_00408af0_00408af0(void* object);
extern "C" void __cdecl entry_free_004524a1(void* block);

struct Deletable_00408d20 {
    unsigned char unknown_0000[0x04];
};

__declspec(noinline) void* Deletable_00408d20_Delete(Deletable_00408d20* object, int flags);

#pragma code_seg(".text$01del")
void* Deletable_00408d20_Delete(Deletable_00408d20* object, int flags) {
    asm_FUN_00408af0_00408af0(object);
    if ((flags & 1) != 0) {
        entry_free_004524a1(object);
    }
    return object;
}
#pragma code_seg()
```

#### `0x00408D40` (18 bytes, cluster) - `src/unidentified/unassigned_00408d40.cpp`

layout `layout/ltcg/dtor_release_00408d40.json`, symbol `?Destroyable_00408d40_Release@@YGXPAUDestroyable_00408d40@@@Z`

```cpp
// 0x00408D40..0x00408D52 (18 bytes): release a possibly-absent object.
//
// Retail answers a null object immediately; otherwise it runs the cleanup at
// 0x00408AF0 (the callee takes the object as a stack argument and cleans it,
// RET 4), hands the object to the CRT free entry at 0x004524A1 and returns.
// The object lives in ESI, so the body is compiled in the native-LTCG cluster
// layout/ltcg/dtor_release_00408d40.json whose array-walking synthetic caller establishes that
// convention.

extern "C" void asm_FUN_00408af0_00408af0(void* object);
extern "C" void __cdecl entry_free_004524a1(void* block);

struct Destroyable_00408d40 {
    unsigned char unknown_0000[0x04];
};

__declspec(noinline) void Destroyable_00408d40_Release(Destroyable_00408d40* object);

#pragma code_seg(".text$01rel")
void Destroyable_00408d40_Release(Destroyable_00408d40* object) {
    if (object != 0) {
        asm_FUN_00408af0_00408af0(object);
        entry_free_004524a1(object);
    }
}
#pragma code_seg()
```

#### `0x0040A410` (27 bytes, cluster) - `src/unidentified/unassigned_0040a410.cpp`

layout `layout/ltcg/dtor_delete_0040a410.json`, symbol `?Deletable_0040a410_Delete@@YGPAXPAUDeletable_0040a410@@H@Z`

```cpp
// 0x0040A410..0x0040A42B (27 bytes): scalar deleting destructor.
//
// Retail runs the object cleanup at 0x0040A1A0 -- the callee takes the object
// as a stack argument and cleans it (RET 4) -- then, when bit 0 of the incoming
// flags is set, hands the object to the CRT free entry at 0x004524A1, and
// finally returns the object in EAX.  The object lives in ESI across both calls,
// a receiver no C++ declaration names, so the body is compiled in the
// native-LTCG cluster layout/ltcg/dtor_delete_0040a410.json whose array-walking synthetic
// caller establishes that convention.

extern "C" void asm_FUN_0040a1a0_0040a1a0(void* object);
extern "C" void __cdecl entry_free_004524a1(void* block);

struct Deletable_0040a410 {
    unsigned char unknown_0000[0x04];
};

__declspec(noinline) void* Deletable_0040a410_Delete(Deletable_0040a410* object, int flags);

#pragma code_seg(".text$01del")
void* Deletable_0040a410_Delete(Deletable_0040a410* object, int flags) {
    asm_FUN_0040a1a0_0040a1a0(object);
    if ((flags & 1) != 0) {
        entry_free_004524a1(object);
    }
    return object;
}
#pragma code_seg()
```

#### `0x0040A430` (18 bytes, cluster) - `src/unidentified/unassigned_0040a430.cpp`

layout `layout/ltcg/dtor_release_0040a430.json`, symbol `?Destroyable_0040a430_Release@@YGXPAUDestroyable_0040a430@@@Z`

```cpp
// 0x0040A430..0x0040A442 (18 bytes): release a possibly-absent object.
//
// Retail answers a null object immediately; otherwise it runs the cleanup at
// 0x0040A1A0 (the callee takes the object as a stack argument and cleans it,
// RET 4), hands the object to the CRT free entry at 0x004524A1 and returns.
// The object lives in ESI, so the body is compiled in the native-LTCG cluster
// layout/ltcg/dtor_release_0040a430.json whose array-walking synthetic caller establishes that
// convention.

extern "C" void asm_FUN_0040a1a0_0040a1a0(void* object);
extern "C" void __cdecl entry_free_004524a1(void* block);

struct Destroyable_0040a430 {
    unsigned char unknown_0000[0x04];
};

__declspec(noinline) void Destroyable_0040a430_Release(Destroyable_0040a430* object);

#pragma code_seg(".text$01rel")
void Destroyable_0040a430_Release(Destroyable_0040a430* object) {
    if (object != 0) {
        asm_FUN_0040a1a0_0040a1a0(object);
        entry_free_004524a1(object);
    }
}
#pragma code_seg()
```

#### `0x0040AFF0` (27 bytes, cluster) - `src/unidentified/unassigned_0040aff0.cpp`

layout `layout/ltcg/dtor_delete_0040aff0.json`, symbol `?Deletable_0040aff0_Delete@@YGPAXPAUDeletable_0040aff0@@H@Z`

```cpp
// 0x0040AFF0..0x0040B00B (27 bytes): scalar deleting destructor.
//
// Retail runs the object cleanup at 0x0040AF00 -- the callee takes the object
// as a stack argument and cleans it (RET 4) -- then, when bit 0 of the incoming
// flags is set, hands the object to the CRT free entry at 0x004524A1, and
// finally returns the object in EAX.  The object lives in ESI across both calls,
// a receiver no C++ declaration names, so the body is compiled in the
// native-LTCG cluster layout/ltcg/dtor_delete_0040aff0.json whose array-walking synthetic
// caller establishes that convention.

extern "C" void asm_BulletManager_Release_0040af00(void* object);
extern "C" void __cdecl entry_free_004524a1(void* block);

struct Deletable_0040aff0 {
    unsigned char unknown_0000[0x04];
};

__declspec(noinline) void* Deletable_0040aff0_Delete(Deletable_0040aff0* object, int flags);

#pragma code_seg(".text$01del")
void* Deletable_0040aff0_Delete(Deletable_0040aff0* object, int flags) {
    asm_BulletManager_Release_0040af00(object);
    if ((flags & 1) != 0) {
        entry_free_004524a1(object);
    }
    return object;
}
#pragma code_seg()
```

#### `0x0040B010` (18 bytes, cluster) - `src/unidentified/unassigned_0040b010.cpp`

layout `layout/ltcg/dtor_release_0040b010.json`, symbol `?Destroyable_0040b010_Release@@YGXPAUDestroyable_0040b010@@@Z`

```cpp
// 0x0040B010..0x0040B022 (18 bytes): release a possibly-absent object.
//
// Retail answers a null object immediately; otherwise it runs the cleanup at
// 0x0040AF00 (the callee takes the object as a stack argument and cleans it,
// RET 4), hands the object to the CRT free entry at 0x004524A1 and returns.
// The object lives in ESI, so the body is compiled in the native-LTCG cluster
// layout/ltcg/dtor_release_0040b010.json whose array-walking synthetic caller establishes that
// convention.

extern "C" void asm_BulletManager_Release_0040af00(void* object);
extern "C" void __cdecl entry_free_004524a1(void* block);

struct Destroyable_0040b010 {
    unsigned char unknown_0000[0x04];
};

__declspec(noinline) void Destroyable_0040b010_Release(Destroyable_0040b010* object);

#pragma code_seg(".text$01rel")
void Destroyable_0040b010_Release(Destroyable_0040b010* object) {
    if (object != 0) {
        asm_BulletManager_Release_0040af00(object);
        entry_free_004524a1(object);
    }
}
#pragma code_seg()
```

#### `0x0040B920` (28 bytes, cluster) - `src/unidentified/unassigned_0040b920.cpp`

layout `layout/ltcg/dtor_delete_0040b920.json`, symbol `?Deletable_0040b920_Delete@@YGPAXPAUDeletable_0040b920@@H@Z`

```cpp
// 0x0040B920..0x0040B93C (28 bytes): scalar deleting destructor.
//
// Retail copies the object from ESI to EAX before the cleanup at 0x0040B3A0 --
// that callee reads its object from EAX -- then, when bit 0 of the incoming
// flags is set, hands the object to the CRT free entry at 0x004524A1 and
// returns it in EAX.  The object stays in ESI across the call, a receiver no
// C++ declaration names, so the body is compiled in the native-LTCG cluster
// layout/ltcg/dtor_delete_0040b920.json; the callee is compiled into the same link as an
// ABI anchor so the pass hands it the object in EAX.

extern "C" void __cdecl asm_FUN_0040b3a0_0040b3a0(void* object);
extern "C" void __cdecl entry_free_004524a1(void* block);

struct Deletable_0040b920 {
    unsigned char unknown_0000[0x04];
};

__declspec(noinline) void* Deletable_0040b920_Delete(Deletable_0040b920* object, int flags);

#pragma code_seg(".text$03del")
void* Deletable_0040b920_Delete(Deletable_0040b920* object, int flags) {
    asm_FUN_0040b3a0_0040b3a0(object);
    if ((flags & 1) != 0) {
        entry_free_004524a1(object);
    }
    return object;
}
#pragma code_seg()
```

#### `0x0040B9B0` (27 bytes, cluster) - `src/unidentified/unassigned_0040b9b0.cpp`

layout `layout/ltcg/dtor_delete_0040b9b0.json`, symbol `?Deletable_0040b9b0_Delete@@YGPAXPAUDeletable_0040b9b0@@H@Z`

```cpp
// 0x0040B9B0..0x0040B9CB (27 bytes): scalar deleting destructor.
//
// Retail runs the object cleanup at 0x0040B7B0 -- the callee takes the object
// as a stack argument and cleans it (RET 4) -- then, when bit 0 of the incoming
// flags is set, hands the object to the CRT free entry at 0x004524A1, and
// finally returns the object in EAX.  The object lives in ESI across both calls,
// a receiver no C++ declaration names, so the body is compiled in the
// native-LTCG cluster layout/ltcg/dtor_delete_0040b9b0.json whose array-walking synthetic
// caller establishes that convention.

extern "C" void asm_FUN_0040b7b0_0040b7b0(void* object);
extern "C" void __cdecl entry_free_004524a1(void* block);

struct Deletable_0040b9b0 {
    unsigned char unknown_0000[0x04];
};

__declspec(noinline) void* Deletable_0040b9b0_Delete(Deletable_0040b9b0* object, int flags);

#pragma code_seg(".text$01del")
void* Deletable_0040b9b0_Delete(Deletable_0040b9b0* object, int flags) {
    asm_FUN_0040b7b0_0040b7b0(object);
    if ((flags & 1) != 0) {
        entry_free_004524a1(object);
    }
    return object;
}
#pragma code_seg()
```

#### `0x0040D660` (30 bytes, cluster) - `src/unidentified/unassigned_0040d660.cpp`

layout `layout/ltcg/dtor_delete_0040d660.json`, symbol `?Delete@Releaseable_0040d660@@QAEPAXH@Z`

```cpp
// 0x0040D660..0x0040D67D (30 bytes): scalar deleting destructor.
//
// Retail hands the object to the resource release at 0x0040D680 -- that callee
// carries its object in ESI -- then, when bit 0 of the incoming flags is set,
// hands the object to the CRT free entry at 0x004524A1 and returns it in EAX.
// ESI is saved and restored around the call, so the receiver arrives in a
// caller-saved register while ESI stays a callee-saved one; no C++ declaration
// names that arrangement, so the body is compiled in the native-LTCG cluster
// layout/ltcg/dtor_delete_0040d660.json, whose callee is compiled into the same link as an
// ABI anchor.

extern "C" void __cdecl entry_free_004524a1(void* block);

struct BulletEntity_0040d680 {
    unsigned int vtable;
    unsigned char reserved_004[0x88];
    void* owned_resource;

    __declspec(noinline) void ReleaseResource();
};

struct Releaseable_0040d660 {
    unsigned char unknown_0000[0x04];

    __declspec(noinline) void* Delete(int flags);
};

#pragma code_seg(".text$01del")
void* Releaseable_0040d660::Delete(int flags) {
    ((BulletEntity_0040d680*)this)->ReleaseResource();
    if ((flags & 1) != 0) {
        entry_free_004524a1(this);
    }
    return this;
}
#pragma code_seg()
```

#### `0x0040D710` (28 bytes, cluster) - `src/unidentified/unassigned_0040d710.cpp`

layout `layout/ltcg/dtor_delete_0040d710.json`, symbol `?Deletable_0040d710_Delete@@YGPAXPAUDeletable_0040d710@@H@Z`

```cpp
// 0x0040D710..0x0040D72C (28 bytes): scalar deleting destructor.
//
// Retail copies the object from ESI to EAX before the cleanup at 0x0040D530 --
// that callee reads its object from EAX -- then, when bit 0 of the incoming
// flags is set, hands the object to the CRT free entry at 0x004524A1 and
// returns it in EAX.  The object stays in ESI across the call, a receiver no
// C++ declaration names, so the body is compiled in the native-LTCG cluster
// layout/ltcg/dtor_delete_0040d710.json; the callee is compiled into the same link as an
// ABI anchor so the pass hands it the object in EAX.

extern "C" void __cdecl asm_FUN_0040d530_0040d530(void* object);
extern "C" void __cdecl entry_free_004524a1(void* block);

struct Deletable_0040d710 {
    unsigned char unknown_0000[0x04];
};

__declspec(noinline) void* Deletable_0040d710_Delete(Deletable_0040d710* object, int flags);

#pragma code_seg(".text$03del")
void* Deletable_0040d710_Delete(Deletable_0040d710* object, int flags) {
    asm_FUN_0040d530_0040d530(object);
    if ((flags & 1) != 0) {
        entry_free_004524a1(object);
    }
    return object;
}
#pragma code_seg()
```


## Drops

None.  All sixteen landed, so there is no byte delta to report.  The two regions
the wave-18 note singled out as possibly unlandable (`0x40B9B0`, `0x40D710`, both
listed "27/28 bytes") landed with the plain 27-byte template; `0x40B920` and
`0x40D660` needed the anchor described above.  Nothing in this family was
"forced": every model either reproduces the retail bytes with `different=0` or it
does not, and the ones that did not are not registered.
