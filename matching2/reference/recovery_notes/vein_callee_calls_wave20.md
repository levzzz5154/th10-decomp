# The vein's call-only regions (wave 20) - 7 landings, 291 bytes

2026-09-19, agent `VeinCalls`.  Target: vein regions (`kind: asm`, `owner` absent
or different) whose bodies contain calls to callees that are already recovered or
are leaves, i.e. regions that should need no anchor authoring.  Work was done in
`/tmp/VeinCalls/msvc` (`cp -a matching2/msvc`) and promoted with
`promote_scratch.py --apply`, one address at a time.

**7 landed EXACT (291 bytes).**  Every one was re-probed against the *maintained*
tree after promotion and reports `EXACT`; `build_msvc.validate_project` accepts the
result (545 clusters, partition contiguous, no duplicate symbol).

| address | size | path | symbol | probe |
| --- | ---: | --- | --- | --- |
| `0x0040C780` | 47 | plain | `?Release@Object0040c780@@QAEXXZ` | EXACT |
| `0x00449FE0` | 32 | cluster | `?Deletable_00449fe0_Delete@@YGPAXPAUDeletable_00449fe0@@H@Z` | EXACT |
| `0x0044CBB0` | 50 | cluster | `?Deletable_0044cbb0_Delete@@YGPAXPAUDeletable_0044cbb0@@H@Z` | EXACT |
| `0x00448CC0` | 50 | cluster | `?Deletable_00448cc0_Delete@@YGPAXPAUDeletable_00448cc0@@H@Z` | EXACT |
| `0x0043C910` | 18 | cluster | `?Destroyable_0043c910_Release@@YGXPAUDestroyable_0043c910@@@Z` | EXACT |
| `0x0044C260` | 58 | cluster | `?PolarMotion_0044c260_Update@@YGXPAUPolarMotion_0044c260@@@Z` | EXACT |
| `0x00429B30` | 36 | cluster | `?Reseed_00429b30@@YGHPAUTimerRecord_00429b30@@H@Z` | EXACT |

## Population and method

The vein is the 426 current `kind: asm` regions the pre-wave-17 owner filter hid.
For each, the naked body was parsed for `call` instructions and every direct callee
resolved through `include/asm_symbols.hpp` and the manifest `symbols` map, then
each callee's entry register set was read from the *retail disassembly* (not from
its source, which is stale for landed units).  A callee counts as declarable when
its entry reads only ECX, EDX and the stack.  That left 33 regions (1,845 bytes),
of which the ones in the static CRT block are out of scope here and the rest were
worked in size order.

Two things about the population are worth recording, because they contradict the
premise in the ticket:

1. Most "landed callee" calls in this vein are *not* cheaper than an anchor lead.
   A recovered function whose recovered body is compiled inside a cluster
   (`asm_FUN_004451c0_004451c0`, `Archive_LoadFile`, `AnimationManager::SetFlag`,
   the `Scheduler_Register*` pair, `FUN_00450470`, `FUN_00447810`) has an ABI the
   /GL pass chose, not one a declaration names; reaching it from a *new* unit still
   needs the callee's body in the same link.  The genuinely cheap subset is calls
   to CRT leaves and to recovered functions whose entry registers a declaration
   already owns.
2. The cheapest shape by far is the ESI-receiver deleting destructor / release
   pair calling the CRT `free` entries (0x004524A1, 0x00452422).  Three of the
   seven landings are that family and they copy the wave-19
   `dtor_delete_*` / `dtor_release_*` templates unchanged.

## Landings - source text

### 0x0040C780 - 47 bytes - `?Release@Object0040c780@@QAEXXZ` (plain)

`src/unidentified/unassigned_0040c780.cpp`

```cpp
// 0x0040C780..0x0040C7AE: release the node list owned by the object at +0x1034.
void __cdecl operator delete(void* memory);

struct ListNode0040c780 {
    void* payload;                 // +0x00
    ListNode0040c780* next_node;   // +0x04
};

struct Object0040c780 {
    void* vtable;                       // +0x0000
    unsigned char pad_004[0x1034 - 4];
    ListNode0040c780* first_node;       // +0x1034

    void Release();
};

void Object0040c780::Release() {
    vtable = (void*)0x0046D0D8;
    ListNode0040c780* node = first_node;
    while (node) {
        ListNode0040c780* next_node = node->next_node;
        operator delete(node->payload);
        operator delete(node);
        node = next_node;
    }
}
```

Plain path: the receiver is ECX and the body has no unusual entry register, so no
cluster is needed.  It is the non-deleting half of the pair whose deleting form at
0x0040C7B0 is already landed; the retail loader reloads `first_node` *before* the
vtable store and MSVC schedules the same way from the vtable-first source (measured
on the landed sibling).  `??3@YAXPAX@Z` is bound to 0x004524A1 in the manifest.

Probe (maintained tree): `0x0040c780      47 bytes  ?Release@Object0040c780@@QAEXXZ  EXACT`

### 0x00449FE0 - 32 bytes - `?Deletable_00449fe0_Delete@@YGPAXPAU...@@H@Z` (cluster)

`src/unidentified/unassigned_00449fe0.cpp`

```cpp
extern "C" void __cdecl entry_free_004524a1(void* block);

struct Deletable_00449fe0 {
    unsigned char unknown_0000[0x08];
    int field_08;   // +0x08
    int field_0C;   // +0x0C
    int field_10;   // +0x10
};

__declspec(noinline) void* Deletable_00449fe0_Delete(Deletable_00449fe0* object, int flags);

#pragma code_seg(".text$01del")
void* Deletable_00449fe0_Delete(Deletable_00449fe0* object, int flags) {
    object->field_08 = 0;
    object->field_0C = 0;
    object->field_10 = 0;
    if ((flags & 1) != 0) {
        entry_free_004524a1(object);
    }
    return object;
}
#pragma code_seg()
```

Object in ESI (array-walk context, `layout/ltcg/dtor_delete_00449fe0.json`).  One
extra lever beyond the wave-19 template: the three stores must be written as three
separate `= 0` assignments so the pass shares the single `xor eax,eax` retail keeps
(the three-field clear is one register reused, not three immediates).

Probe: `0x00449fe0      32 bytes  ?Deletable_00449fe0_Delete@@YGPAXPAUDeletable_00449fe0@@H@Z  EXACT`

### 0x0044CBB0 - 50 bytes - `?Deletable_0044cbb0_Delete@@YGPAXPAU...@@H@Z` (cluster)

`src/unidentified/unassigned_0044cbb0.cpp`

```cpp
extern "C" void __cdecl entry_free_004524a1(void* block);
extern "C" void (__stdcall* data_004660cc)(void* handle);

struct Deletable_0044cbb0 {
    unsigned char unknown_0000[0x78];
    int field_78;                       // +0x78
    unsigned char unknown_07c[0x8C - 0x7C];
    int field_8C;                       // +0x8C
};

__declspec(noinline) void* Deletable_0044cbb0_Delete(Deletable_0044cbb0* object, int flags);

#pragma code_seg(".text$01del")
void* Deletable_0044cbb0_Delete(Deletable_0044cbb0* object, int flags) {
    if (object->field_78 == 1) {
        data_004660cc((void*)object->field_8C);
        object->field_8C = -1;
    }
    if ((flags & 1) != 0) {
        entry_free_004524a1(object);
    }
    return object;
}
#pragma code_seg()
```

Same ESI array-walk context; the handle close goes through the import slot
0x004660CC bound as `_data_004660cc` (`kind: data`) — the only addition to
`absolute_symbols` over the template.

Probe: `0x0044cbb0      50 bytes  ?Deletable_0044cbb0_Delete@@YGPAXPAUDeletable_0044cbb0@@H@Z  EXACT`

### 0x00448CC0 - 50 bytes - `?Deletable_00448cc0_Delete@@YGPAXPAU...@@H@Z` (cluster)

`src/unidentified/unassigned_00448cc0.cpp`

```cpp
extern "C" void __cdecl entry_free_00452422(void* block);
extern "C" void __cdecl entry_free_004524a1(void* block);

struct Deletable_00448cc0 {
    unsigned char unknown_0000[0x358];
    void* field_358;                    // +0x358
};

__declspec(noinline) void* Deletable_00448cc0_Delete(Deletable_00448cc0* object, int flags);

#pragma code_seg(".text$01del")
void* Deletable_00448cc0_Delete(Deletable_00448cc0* object, int flags) {
    if (object->field_358 != 0) {
        entry_free_00452422(object->field_358);
    }
    object->field_358 = 0;
    if ((flags & 1) != 0) {
        entry_free_004524a1(object);
    }
    return object;
}
#pragma code_seg()
```

Two different CRT free entries (0x00452422 for the field, 0x004524A1 for the
object).  Retail's `movl $0,0x358(%esi)` sits between the delete-flag test and its
branch; the statement order above schedules exactly there.

Probe: `0x00448cc0      50 bytes  ?Deletable_00448cc0_Delete@@YGPAXPAUDeletable_00448cc0@@H@Z  EXACT`

### 0x0043C910 - 18 bytes - `?Destroyable_0043c910_Release@@YGXPAU...@@@Z` (cluster)

`src/unidentified/unassigned_0043c910.cpp`

```cpp
extern "C" void asm_Recovery_ReleaseRawPair_0043cb00(void* object);
extern "C" void __cdecl entry_free_004524a1(void* block);

struct Destroyable_0043c910 {
    unsigned char unknown_0000[0x04];
};

__declspec(noinline) void Destroyable_0043c910_Release(Destroyable_0043c910* object);

#pragma code_seg(".text$01rel")
void Destroyable_0043c910_Release(Destroyable_0043c910* object) {
    if (object != 0) {
        asm_Recovery_ReleaseRawPair_0043cb00(object);
        entry_free_004524a1(object);
    }
}
#pragma code_seg()
```

The wave-19 18-byte release form.  The cleanup callee is a still-assembly *leaf*
at 0x0043CB00 whose argument is on the stack and which pops it (`ret 4`), so an
`extern "C"` declaration under the project's /Gz default emits the right call and
the layout binds the decorated `_asm_Recovery_ReleaseRawPair_0043cb00@4`; the
`pop ecx` is the caller's cdecl free cleanup.

Probe: `0x0043c910      18 bytes  ?Destroyable_0043c910_Release@@YGXPAUDestroyable_0043c910@@@Z  EXACT`

### 0x0044C260 - 58 bytes - `?PolarMotion_0044c260_Update@@YGXPAU...@@@Z` (cluster)

`src/unidentified/unassigned_0044c260.cpp`

```cpp
struct Vec2_0044c260 { float x; float y; };

struct PolarMotion_0044c260 {
    unsigned char unknown_0000[0x0C];
    Vec2_0044c260 direction;        // +0x0C
    int state;                      // +0x14
    float field_18;                 // +0x18
    float angle;                    // +0x1C
    float field_20;                 // +0x20
    float delta;                    // +0x24
    unsigned char flags;            // +0x28
};

extern "C" void __fastcall asm_Recovery_PolarToVectorRetail_0044c5d0(
        Vec2_0044c260* destination, float angle, float radius);
float __stdcall Angle_Normalize(float angle);

__declspec(noinline) void PolarMotion_0044c260_Update(PolarMotion_0044c260* motion);

#pragma code_seg(".text$01polar")
void PolarMotion_0044c260_Update(PolarMotion_0044c260* motion) {
    if ((motion->flags & 1) == 0) {
        asm_Recovery_PolarToVectorRetail_0044c5d0(
                &motion->direction, motion->angle, motion->field_18);
        motion->state = 0;
    } else {
        motion->field_20 += motion->delta;
        motion->angle = Angle_Normalize(motion->field_18 + motion->angle);
    }
}
#pragma code_seg()
```

Two levers here, both measured:

* The still-assembly polar routine at 0x0044C5D0 is a `__usercall` with its
  destination pointer in ECX and two floats on the stack (`ret 8`), which a
  `__fastcall` free declaration reproduces exactly — the value already in ECX
  needs no move.  Bound as `@asm_Recovery_PolarToVectorRetail_0044c5d0@12`
  (`relative_code`).
* Branch polarity had to be inverted: `if ((flags & 1) == 0) { polar } else
  { floats }` compiles to retail's `jne`-forward-past-the-polar-block layout,
  while `if (flags & 1) { floats } else { polar }` gives the mirrored `je` and
  18 differing bytes.  (Same class as the wave-19 note's "two forward gotos onto
  a labelled trailing return".)

`__fltused` (`kind: metadata`) is required because the body does float arithmetic;
the cluster died with `unresolved external symbol __fltused` without it.

Probe: `0x0044c260      58 bytes  ?PolarMotion_0044c260_Update@@YGXPAUPolarMotion_0044c260@@@Z  EXACT`

### 0x00429B30 - 36 bytes - `?Reseed_00429b30@@YGHPAUTimerRecord...@@H@Z` (cluster)

`src/unidentified/unassigned_00429b30.cpp`

```cpp
struct TimerBlock_00429b30 {
    unsigned char unknown_0000[0x5C];
    int field_5C;                       // +0x5C
};

struct TimerRecord_00429b30 {
    unsigned char unknown_0000[0x18];
    TimerBlock_00429b30* block;         // +0x18
};

extern "C" int __cdecl asm_FID_conflict___time32_00452b71(int* timer);
extern "C" int data_00474c7c;

__declspec(noinline) int Reseed_00429b30(TimerRecord_00429b30* record, int value);

#pragma code_seg(".text$01reseed")
int Reseed_00429b30(TimerRecord_00429b30* record, int value) {
    asm_FID_conflict___time32_00452b71((int*)((char*)record->block + 0x0C));
    record->block->field_5C = (value != 0) ? value + 7 : data_00474c7c;
    return 0;
}
#pragma code_seg()
```

Record in EDI, value in ESI (record/values context in
`layout/ltcg/reseed_00429b30.json`).  `_time32` is an ordinary `__cdecl` CRT leaf
the declaration names; the context size had to be corrected from the link map
(declared 45, emitted 79).

Probe: `0x00429b30      36 bytes  ?Reseed_00429b30@@YGHPAUTimerRecord_00429b30@@H@Z  EXACT`

## Drops

| address | size | delta | measured blocking reason |
| --- | ---: | --- | --- |
| `0x00427C10` | 33 | 18 of 33 bytes differ | Scale-and-truncate pair (`fld src; fmul K; call __ftol2`) reached in the mirror order: MSVC hoists `fld [0x470B44]` to the top of the body and re-loads it after the first `__ftol2` instead of using it as the `fmul` memory operand. Register homes are correct (source ESI, destination EDI) and the extent is exactly 33; only the x87 spelling differs. Tried `src*K`, `K*src`, a source local and a scale local; the local-scale spelling changes the extent. Unregistered again after measuring (18 differing bytes, `--json`). |
| `0x00405CC0` | 51 | 2 of 51 bytes differ | The only difference is the *image-base* byte of the two `push`ed code addresses: retail `push 0x405DE0`/`push 0x405D00` against the compiled `push 0x5DE0`/`push 0x5D00`, i.e. MSVC emitted the code addresses image-base-relative (not a masked DIR32/REL32 field) even though both symbols are declared and bound (`_asm_FUN_00405d00_00405d00`, `?EntitySecondaryResource_Release@@YIXPAUEntity@@@Z`). The `rep stosd` zeroing is reproduced by `memset(object, 0, 0x3E0B54)` byte-for-byte, and the EH vector-constructor call marshalling is exact. Unregistered again. |

### Modelled and reverted, or blocked with no model

| address | size | reason |
| --- | ---: | --- |
| `0x00441F40` | 16 | `fld [esp+4]; fld [esp+8]; call 0x00463BBA; ret 8` forwards two floats to the CRT power helper, which takes its inputs on the x87 stack and is not a declaration MSVC emits from source; no spelling attempted beyond reading its entry. |
| `0x00447910` | 42 | Releases a field through a vtable slot with the object *pushed* (`mov ecx,[eax]; push eax; call [ecx+8]`), not the `mov ecx,obj; call [vtbl+N]` shape the wave-18 virtual-dispatch device produces. |
| `0x00404420` | 47 | Calls the landed `AnimationManager::SetFlag` twice with ECX left *dead* at both call sites. Every declaration that names the ECX parameter forces a `mov ecx,X` that retail does not have (`SetFlag` forwards ECX through to `Find`, which ignores it); reaching this needs both bodies in one link. |
| `0x00450610` | 122 | Calls `FUN_00450470`, whose entry reads EAX (an object) and whose own body is a compiler-generated binary-search/copy routine; the caller also reads BL live-in. |
| `0x00424460`, `0x00424470`, `0x00434B80` | 15 each | `push 0; push N; mov edx,imm; call 0x0043E460` thunks with the manager live in EAX at entry and `ret` (no cleanup). 0x0043E460 is a still-assembly leaf entered with the manager in EAX and the name pointer in EDX, so the thunk needs that leaf compiled in the same link. `0x00434B80` is `NamedCalleeDrops`'. |
| `0x00405F00`, `0x00413B50` | 50 each | Both call `Recovery_LoadCachedResource` (declarable, exact call site) and then `TextLog_0044b810::Append`. The log entry is variadic, so a plain unit emits `push this; push format; call; add esp,8` where retail has `mov ecx,log; push format; call; add esp,4`. The plain compile of 0x00405F00 came out 49 bytes against 50 with that one call shape wrong; reaching it needs the `TextLog` body in the link (the `load_archive_file` layout does exactly that with a 201-byte ABI anchor, which is anchor work, not a declaration). |
| `0x004576E6`, `0x00457A1C`, `0x004622F6`, `0x0045F3B4`, `0x00461551`, `0x0045247E`, `0x00457A24`, `0x0045B012`, `0x0045FD32`, `0x00459CB6`, `0x00459F1D`, `0x004613F0`, `0x00462209`, `0x00463BC4`, `0x00457A52`, `0x00460EB9`, `0x0045A0BC`, `0x00460170`, `0x0045EBF5`, `0x00457506`, `0x0045972A`, `0x00454863`, `0x0045F4FC`, `0x0045F5A1`, `0x00420547` | 6-295 | All at or above the static CRT block (>= 0x00452493) or inside it; out of the game-code recovery target per `remaining_work_split_2026_09_19.md`. |

## Manifest and source edits, and the validation run

* Sources rewritten (7): `src/unidentified/unassigned_0040c780.cpp`,
  `unassigned_00449fe0.cpp`, `unassigned_0044cbb0.cpp`, `unassigned_00448cc0.cpp`,
  `unassigned_0043c910.cpp`, `unassigned_0044c260.cpp`, `unassigned_00429b30.cpp`.
  Each was a single-region file, so no sibling's region was touched.
* Layouts and drivers added (6):
  `layout/ltcg/dtor_delete_00449fe0.{json,_context.cpp}`,
  `dtor_delete_0044cbb0.{json,_context.cpp}`,
  `dtor_delete_00448cc0.{json,_context.cpp}`,
  `dtor_release_0043c910.{json,_context.cpp}`,
  `polar_update_0044c260.{json,_context.cpp}`,
  `reseed_00429b30.{json,_context.cpp}`.
* Region records went into the maintained manifest only through
  `promote_scratch.py --apply` (one `--address` per landing), which takes
  `regions.json.lock` and re-reads the manifest inside it; no hand edit of the
  maintained manifest.  The two failed clusters were unregistered in the scratch
  copy before promoting, so nothing unverified travelled in the scratch's
  `ltcg_clusters` list.
* Validation: `build_msvc.validate_project(config, reference)` over the maintained
  manifest completes without raising (schema 2, contiguous 0x401000..0x465C00
  partition, distinct symbols), and all seven sources re-probe `EXACT` against
  `matching2/msvc` after promotion (the seven probe lines quoted above are from
  that run).  No `make`, no whole-image build was run.

## Coordination

`RegionSplits` owns 0x00413070 and 0x0042A9E0 (I yielded both) and confirmed no
overlap with the rest of my set.  `NamedCalleeDrops`' declared set was
0x0040B320, 0x00413300, 0x00415E30, 0x00418850, 0x0041ACB0, 0x0041BE40,
0x00428F30, 0x00437200, 0x00439080, 0x00439700, 0x0043BBA0, 0x0043C910,
0x0043DA80, 0x004434B0, 0x004357D0, 0x0044BFA0, 0x0044C6E0,
0x0044D740, 0x004658F0.  We agreed they keep all of it except
0x0043D640/0x0043D670, which they handed to me and which I did **not** attempt:
both call `Archive_LoadFile`, which is a *selected function* of the
`load_archive_file` cluster, so the two callers would have to join that existing
span rather than get a layout of their own.  **One cross-over did happen**:
0x0043C910 was on their list and is landed by this wave before that reply arrived;
it is now `semantic` in the maintained manifest, and they were told mid-run.
They also landed 0x00441D70, which removes it from my candidate list.
