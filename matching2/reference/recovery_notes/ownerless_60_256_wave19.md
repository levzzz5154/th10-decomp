# The owner-less vein, 60-256 bytes (wave 19) - 9 landings, 690 bytes

2026-09-19, agent `VeinRest`. Population: every manifest region with `kind: asm`,
`owner: null`, in the game range, with a size between 60 and 256 bytes - the band
the eight wave-18 block sweeps did not cover, since those took 64 bytes and under.
35 regions, 3,009 bytes. Work was done in `/tmp/VeinRest/msvc` (`cp -a
matching2/msvc`) and promoted with `promote_scratch.py --apply`.

**9 landed EXACT (690 bytes).** Of the 26 the wave did not land, four were handed
to a sibling agent (below), 7 were modelled and carry a measured delta, 10 have
the blocking reason recorded and no model, and 5 were already closed with
evidence by earlier waves. Every landing was re-probed against the maintained
tree after promotion and reports `EXACT`; the whole set is in the maintained
manifest as `semantic`, and `load_clusters` accepts the result (515 clusters,
4,425 regions).

Four regions of the band (`0x421C00`, `0x424530`, `0x449A50`, `0x44C6E0`) were
handed to the sibling agent `VeinRecords`, which owns the record-shaped regions,
and are **not** counted among the drops here. `0x41FD90`, dropped in wave 18, was
landed by another sibling during this wave as
`semantic_Update_0041fd90_0041fd90`, so it is no longer in the remainder either.

## The levers that mattered

1. **The EAX-receiver driver is still the workhorse.** Six of the nine landings
   are single-function clusters whose synthetic caller walks an array of objects:
   0x449530 and 0x40B2A0 get EAX, 0x42AFE0, 0x42AB80, 0x43B840 and 0x436970 get
   ESI (the record survives the body's calls, which is the 0x43 note's rule).
2. **An `extern "C"` `__fastcall` declaration is what fixes `(ECX, EDX)` entry.**
   0x40D200 takes its manager in ECX and its node in EDX, which no member
   declaration can express; a free `__fastcall` function compiles to it directly
   and needs no cluster.
3. **The node-field spelling beats a `link` local for a doubly-linked unlink.**
   0x40D200 only matched once the head-pointer reloads used the *node's* own
   `+0x1170`/`+0x1174` fields (`mov 0x1170(%edx),%esi`) instead of a `Link*`
   local folded through the `lea` base. The local spelling was 78 bytes against
   retail's 82: the compiler reused EDX and never materialised the integer zero
   register retail keeps in ESI for both the compares and the two null stores.
4. **Move a store inside its own branch or the scheduler hoists it past the
   join.** 0x436970's `field_000 = 0;` has to sit inside `if (field_000 != 0)`
   for retail's `je`-over-the-store layout; written as a statement after the `if`
   the compiler sank it to the join and the region came out 73 bytes against 75.
5. **The ternary and the if/else are not interchangeable either.** The same
   region's string-storage pick (`capacity < 0x10 ? inline : heap`) only produced
   retail's `mov / jmp / lea` pair as an explicit `if`/`else` assigning the
   destination; the `?:` spelling gave the 2-byte-shorter `lea`-then-`jb` form.
6. **A duplicated tail call does not stop the /GL pass from tail-calling it
   anyway** - see 0x40B320 and 0x415E30 below.
7. **`constant_aliases` needs the float *value*, not its bits.** The loader
   rejects `"value": 1065353216` for `__real@3f800000` with "constant alias value
   does not match its compiler literal name"; `"value": 1.0` is accepted.
8. **A float-bearing cluster must bind `__fltused` (`kind: metadata`)** or the
   link dies with `unresolved external symbol __fltused`; a float-to-int
   conversion inside a cluster emits a call to `__ftol2`, which the cluster link
   resolves only when the layout binds it (`relative_code` at 0x00463B2C).
9. **A 14-argument call through a global function pointer is modelable**: the
   pointer's type fixes the push order and the `std::string`-style storage pick
   is just a capacity test (0x436970).

## The `cluster_attempt` map-size bug, hit again

`tools/waves/cluster_attempt.py` read the link map's *offset* column into both
`_map_offset` and `_map_section` (the two functions were textually identical),
then corrected `context.size` and the function size from it. A context whose
emitted size differs from the declared guess therefore sends both sizes wild: the
first attempt at 0x449530 reported `size=296240 ctx=296352` and `function ...
extent is outside a MAP CODE contribution`, and every retry after that was
nonsense. This wave worked around it in its scratch harness by parsing both map
columns (offset *and* length) and correcting only the context size/address, which
is what converged all six cluster landings here.

The maintained tool has since been fixed properly in commit `2ba6f0c1` ("... fix
the map size helper"), whose message notes this was the third agent to hit it.
The symptom above is kept only so a later wave recognises the failure mode if it
reappears.

## Landings

| address | size | kind | symbol | probe |
| --- | ---: | --- | --- | --- |
| `0x00449530` | 92 | cluster | `?Begin@AnimationNode_00449530@@QAEXXZ` | EXACT |
| `0x0042AFE0` | 65 | cluster | `?DestroyOwned_DeletingDestructor_0042afe0@@YGPAXPAUOwnedObject_0042afe0@@I@Z` | EXACT |
| `0x0042AF90` | 76 | plain | `_FlushHolder_0042af90@0` | EXACT |
| `0x00447790` | 62 | plain | `?AllEmpty@Table_00447790@@QBEHXZ` | EXACT |
| `0x0040D200` | 82 | plain | `@RemoveNode_0040d200@8` | EXACT |
| `0x0042AB80` | 73 | cluster | `?DestroyOwned_DeletingDestructor_0042ab80@@YGPAXPAUOwnedObject_0042ab80@@I@Z` | EXACT |
| `0x0040B2A0` | 100 | cluster | `?Update@Worker_0040b2a0@@QAEHXZ` | EXACT |
| `0x0043B840` | 65 | cluster | `?Renew@Record_0043b840@@QAEXXZ` | EXACT |
| `0x00436970` | 75 | cluster | `?Reopen@Record_00436970@@QAEXXZ` | EXACT |

### Probe lines (maintained tree)

```text
0x00449530      92 bytes  ?Begin@AnimationNode_00449530@@QAEXXZ  EXACT
0x0042afe0      65 bytes  ?DestroyOwned_DeletingDestructor_0042afe0@@YGPAXPAUOwnedObject_0042afe0@@I@Z  EXACT
0x0042af90      76 bytes  _FlushHolder_0042af90@0  EXACT
0x00447790      62 bytes  ?AllEmpty@Table_00447790@@QBEHXZ  EXACT
0x0040d200      82 bytes  @RemoveNode_0040d200@8  EXACT
0x0042ab80      73 bytes  ?DestroyOwned_DeletingDestructor_0042ab80@@YGPAXPAUOwnedObject_0042ab80@@I@Z  EXACT
0x0040b2a0     100 bytes  ?Update@Worker_0040b2a0@@QAEHXZ  EXACT
0x0043b840      65 bytes  ?Renew@Record_0043b840@@QAEXXZ  EXACT
0x00436970      75 bytes  ?Reopen@Record_00436970@@QAEXXZ  EXACT
```

Each cluster's layout and driver are registered in `regions.json`'s
`ltcg_clusters`; the plain records carry no layout.

## Source text


### `0x00449530` (92 bytes, cluster) - `matching2/msvc/src/unidentified/unassigned_00449530.cpp`

layout `layout/ltcg/anim_begin_00449530.json`, driver `layout/ltcg/anim_begin_00449530_context.cpp`

```cpp
// 0x00449530: find the node named by this object's first field, set flag bit 1
// and clear flag bit 17 on it, and do the same to every node in its child chain
// when it has no children of its own.
extern "C" void* data_00491c10;

struct AnimationNode_00449530 {
    AnimationNode_00449530* field_000;   // +0x000
    AnimationNode_00449530* field_004;   // +0x004
    unsigned char pad_008[0x0C];
    AnimationNode_00449530* field_014;   // +0x014
    AnimationNode_00449530* field_018;   // +0x018
    unsigned char pad_01c[0x340];
    unsigned int flags_35c;              // +0x35C
    __declspec(noinline) void Begin();
};

extern "C" AnimationNode_00449530* __fastcall AnimationManager_Find_004491c0(
    void* value, void* manager, int unused);

#pragma code_seg(".text$01accessor")
void AnimationNode_00449530::Begin() {
    AnimationNode_00449530* node =
        AnimationManager_Find_004491c0(field_000, data_00491c10, (int)field_000);
    if (node == 0) {
        return;
    }
    node->flags_35c = (node->flags_35c & ~0x20000u) | 2u;
    if (node->field_018 != 0) {
        return;
    }
    for (AnimationNode_00449530* child = node->field_014; child != 0; child = child->field_004) {
        child->field_000->flags_35c |= 2u;
        child->field_000->flags_35c &= ~0x20000u;
    }
}
#pragma code_seg()
```


### `0x0042AFE0` (65 bytes, cluster) - `matching2/msvc/src/unidentified/unassigned_0042afe0.cpp`

layout `layout/ltcg/del_0042afe0.json`, driver `layout/ltcg/del_0042afe0_context.cpp`

```cpp
// 0x0042AFE0: scalar deleting destructor. Retail keeps the object in ESI and
// the delete flag in the first stack argument, so this body is a cluster whose
// synthetic caller walks an array of the objects.
struct OwnedObject_0042afe0;
extern "C" void __cdecl entry_free_00452422(void* memory);
extern "C" void __cdecl entry_free_004524a1(void* memory);
__declspec(noinline) void* DestroyOwned_DeletingDestructor_0042afe0(OwnedObject_0042afe0* object, unsigned int flags);
#pragma code_seg(".text$01delete0042afe0")
void* DestroyOwned_DeletingDestructor_0042afe0(OwnedObject_0042afe0* object, unsigned int flags) {
    void** fields = (void**)object;
    if (fields[0]) { entry_free_00452422(fields[0]); fields[0] = 0; }
    if (fields[1]) { entry_free_00452422(fields[1]); fields[1] = 0; }
    if (flags & 1) entry_free_004524a1(object);
    return object;
}
#pragma code_seg()
```


### `0x0042AF90` (76 bytes, plain) - `matching2/msvc/src/unidentified/unassigned_0042af90.cpp`

```cpp
// 0x0042AF90: free the pair held by the global at 0x47783C, then the record
// itself, then clear the global.
extern "C" void* data_0047783c;
extern "C" void __cdecl entry_free_00452422(void* memory);
extern "C" void __cdecl entry_free_004524a1(void* memory);
extern "C" void FlushHolder_0042af90(void) {
    void** record = (void**)data_0047783c;
    if (record) {
        if (record[0]) { entry_free_00452422(record[0]); record[0] = 0; }
        if (record[1]) { entry_free_00452422(record[1]); record[1] = 0; }
        entry_free_004524a1(record);
    }
    data_0047783c = 0;
}
```


### `0x00447790` (62 bytes, plain) - `matching2/msvc/src/unidentified/unassigned_00447790.cpp`

```cpp
// 0x00447790: answer 1 when every slot of the table at this+0x3AD06C is either
// null or holds a node whose +0x124 and +0x128 fields are both zero.
struct Node_00447790 {
    unsigned char pad_000[0x124];
    void* field_124;
    void* field_128;
};
struct Table_00447790 {
    unsigned char pad_000[0x3AD06C];
    Node_00447790* slots[0x21];
    __declspec(noinline) int AllEmpty() const;
};
int Table_00447790::AllEmpty() const {
    for (unsigned index = 0; index < 0x21; ++index) {
        Node_00447790* node = slots[index];
        if (node != 0 && (node->field_128 != 0 || node->field_124 != 0)) {
            return 0;
        }
    }
    return 1;
}
```


### `0x0040D200` (82 bytes, plain) - `matching2/msvc/src/unidentified/unassigned_0040d200.cpp`

```cpp
// 0x0040D200: unlink the list node at this+0x116C from the manager's pair of
// head pointers and decrement its count.
struct Link_0040d200 {
    void* field_000;
    Link_0040d200* field_004;
    Link_0040d200* field_008;
};
struct Node_0040d200 {
    unsigned char pad_000[0x116C];
    unsigned char link_116c[4];
    Link_0040d200* field_1170;
    Link_0040d200* field_1174;
};
struct Manager_0040d200 {
    unsigned char pad_000[0x58];
    Link_0040d200* head_058;
    Link_0040d200* head_05c;
    int count_060;
};
extern "C" int __fastcall RemoveNode_0040d200(Manager_0040d200* manager, Node_0040d200* node);
int __fastcall RemoveNode_0040d200(Manager_0040d200* manager, Node_0040d200* node) {
    Link_0040d200* link = (Link_0040d200*)node->link_116c;
    if (manager->head_058 == link) manager->head_058 = node->field_1170;
    if (manager->head_05c == link) manager->head_05c = node->field_1174;
    if (link->field_004 != 0) link->field_004->field_008 = link->field_008;
    if (link->field_008 != 0) link->field_008->field_004 = link->field_004;
    link->field_004 = 0;
    link->field_008 = 0;
    return --manager->count_060;
}
```


### `0x0042AB80` (73 bytes, cluster) - `matching2/msvc/src/unidentified/unassigned_0042ab80.cpp`

layout `layout/ltcg/del_0042ab80.json`, driver `layout/ltcg/del_0042ab80_context.cpp`

```cpp
// 0x0042AB80: scalar deleting destructor for a list node. Retail keeps the
// object in ESI, unlinks it from the pair of neighbours at +0x627C/+0x6280 and
// takes the delete flag from the first stack argument.
struct ListNode_0042ab80 {
    void* field_000;
    ListNode_0042ab80* field_004;
    ListNode_0042ab80* field_008;
};
struct OwnedObject_0042ab80 {
    unsigned char pad_000[0x627C];
    ListNode_0042ab80* field_627c;
    ListNode_0042ab80* field_6280;
};
extern "C" void __cdecl entry_free_004524a1(void* memory);
__declspec(noinline) void* DestroyOwned_DeletingDestructor_0042ab80(OwnedObject_0042ab80* object, unsigned int flags);
#pragma code_seg(".text$01delete0042ab80")
void* DestroyOwned_DeletingDestructor_0042ab80(OwnedObject_0042ab80* object, unsigned int flags) {
    if (object->field_627c) object->field_627c->field_008 = object->field_6280;
    if (object->field_6280) object->field_6280->field_004 = object->field_627c;
    object->field_627c = 0;
    object->field_6280 = 0;
    if (flags & 1) entry_free_004524a1(object);
    return object;
}
#pragma code_seg()
```


### `0x0040B2A0` (100 bytes, cluster) - `matching2/msvc/src/unidentified/unassigned_0040b2a0.cpp`

layout `layout/ltcg/polar_0040b2a0.json`, driver `layout/ltcg/polar_0040b2a0_context.cpp`

```cpp
// 0x0040B2A0: advance the worker's embedded polar record, then publish the
// resulting vector into the worker's own +0x340 triple. The worker arrives in
// EAX, which only the native LTCG link chooses, so this is a cluster.
extern "C" void __fastcall asm_Recovery_PolarToVectorRetail_0044c5d0(void* target, float value, float other);
extern "C" void __cdecl asm_Recovery_AdvancePolarMotion_0044c2a0();
extern "C" float __stdcall Angle_Normalize_0044bc70(float value);
struct Vec3_0040b2a0 {
    float x; float y; float z;
};
struct PolarState_0040b2a0 {
    Vec3_0040b2a0 vector_000;
    float field_00c;
    float field_010;
    float field_014;
    float field_018;
    float field_01c;
    float field_020;
    float field_024;
    unsigned int flags_028;
};
struct Worker_0040b2a0 {
    unsigned char pad_000[0x340];
    Vec3_0040b2a0 output_340;
    unsigned char pad_34c[0x0C];
    PolarState_0040b2a0* state_358;
    __declspec(noinline) int Update();
};
#pragma code_seg(".text$01accessor")
int Worker_0040b2a0::Update() {
    PolarState_0040b2a0* state = state_358;
    if ((state->flags_028 & 1) == 0) {
        asm_Recovery_PolarToVectorRetail_0044c5d0(&state->field_00c, state->field_01c, state->field_018);
        state->field_014 = 0.0f;
    } else {
        state->field_020 += state->field_024;
        state->field_01c = Angle_Normalize_0044bc70(state->field_01c + state->field_018);
    }
    asm_Recovery_AdvancePolarMotion_0044c2a0();
    *(Vec3_0040b2a0*)((unsigned char*)this + 0x340) = state->vector_000;
    return 0;
}
#pragma code_seg()
```


### `0x0043B840` (65 bytes, cluster) - `matching2/msvc/src/unidentified/unassigned_0043b840.cpp`

layout `layout/ltcg/renew_0043b840.json`, driver `layout/ltcg/renew_0043b840_context.cpp`

```cpp
// 0x0043B840: release the record's two owned handles and recreate the first one
// through the platform callbacks held in the global slots.
extern "C" void (*data_00466288)(void* handle);
extern "C" void (*data_00466274)(void* memory);
extern "C" void (*data_00466278)(void* memory);
extern "C" int (*data_0046628c)(int size, void* memory, void* entry, void* owner, int flag);
struct Record_0043b840 {
    unsigned char pad_000[4];
    int handle_004;
    void* memory_008;
    __declspec(noinline) void Renew();
};
#pragma code_seg(".text$01accessor")
void Record_0043b840::Renew() {
    if (handle_004 != 0) data_00466288((void*)handle_004);
    data_00466274(memory_008);
    handle_004 = 0;
    data_00466278(memory_008);
    handle_004 = data_0046628c(0x10, memory_008, (void*)0x43A6E0, this, 1);
}
#pragma code_seg()
```


### `0x00436970` (75 bytes, cluster) - `matching2/msvc/src/unidentified/unassigned_00436970.cpp`

layout `layout/ltcg/reopen_00436970.json`, driver `layout/ltcg/reopen_00436970_context.cpp`

```cpp
// 0x00436970: close the record's handle and reopen it through the import slot,
// passing the record's string storage (inline when the capacity is under 0x10).
extern "C" void (*data_00466030)(void* handle);
extern "C" int (*data_00466034)(int a1, int a2, int a3, int a4, int a5, int a6, int a7,
                                int a8, int a9, int a10, int a11, int a12, int a13, const char* a14);
struct Record_00436970 {
    void* field_000;
    int field_004;
    int field_008;
    unsigned char pad_00c[4];
    void* storage_010;
    unsigned char pad_014[0x10];
    unsigned int capacity_024;
    int field_028;
    __declspec(noinline) void Reopen();
};
#pragma code_seg(".text$01accessor")
void Record_00436970::Reopen() {
    if (field_000 != 0) {
        data_00466030(field_000);
        field_000 = 0;
    }
    const char* text;
    if (capacity_024 >= 0x10) {
        text = (const char*)storage_010;
    } else {
        text = (const char*)((unsigned char*)this + 0x10);
    }
    field_000 = (void*)data_00466034(field_008, field_004, 0, 0, field_028, 0, 0, 0,
                                     1, 0, 0, 0, 0x30, text);
}
#pragma code_seg()
```

## Attempted, with the measured delta

| region | size | closest model | delta |
| --- | ---: | --- | --- |
| `0x0040B320` | 73 | cluster member `Update()` in an array-walking driver, three spellings (one shared tail call; a duplicated tail call; duplicated plus an unused `int` parameter) | emitted **66 vs 73**. The pass takes the receiver in **ESI at entry** where retail has it in EAX and moves it (`push esi; mov esi,eax`), and it tail-jumps `AdvancePolarMotion` in both branches (`jmp`) where retail calls and then restores (`call; pop esi; ret`). Nothing else differs. |
| `0x00413300` | 71 | cluster member `Release()` with `@Scheduler_Remove@8` bound, two spellings (early return on the null entry; declaration order flipped) | emitted **71 vs 71, 2 differing bytes at +0x20**: retail `8b ce / 8b d7` (`mov esi,ecx; mov edi,edx`), mine `89 fa / 89 f1` (the same two moves, reversed). A pure argument-setup-order tie-break; both spellings produce the reversed pair. |
| `0x00415E30` | 93 | cluster member `Tick()` with the 1.0f literal aliased to 0x470AFC and `__ftol2` bound | emitted **92 vs 93**: the pass again takes the receiver in ESI at entry, so retail's `push esi` is missing. Same blocker as 0x40B320. |
| `0x0044BFA0` | 74 | cluster member `Advance()` with `__ftol2` bound to 0x463B2C and 1.0f aliased to 0x470AFC | emitted **74 vs 74, 12 differing**, first at +0x1: retail `mov edx,[esi+4] / mov ecx,[esi+0Ch]`, mine `mov ecx,[esi+4] / mov edx,[esi+0Ch]` - the two loads swap registers, and the first branch's x87 pair is `fld 1.0f; fadd [esi+8]` against retail's `fld [esi+8]; fadd 1.0f`. The alias fixed the operand order of the *comparisons* but not of this add. |
| `0x00418850` | 65 | cluster with a `strcpy`-shaped body (`start` pointer walk, `memcpy` of `text - start`); also the plain `strcat(g, text)` spelling | `strcat`: emitted **65 vs 65, 30 differing** (the compiler's inline dest scan is a forward walk, retail's is `dec edi` / `[edi+1]`). Hand-written: emitted **64 vs 65** - retail keeps `text` in EAX with the start in ECX and pushes ESI/EDI *after* the length loop; mine keeps `text` in ESI and pushes at entry. |
| `0x00437200` | 159 | plain `__fastcall` free function on a record in ECX with the value in DL | emitted **176 vs 159** (17 over). The three-way `mode - 0x15 / -4 / -1` dispatch and both strided stores are modelled; the excess is in the 0x19 branch's `(value == 0) ? 0 : 0x80` flag and the loop bounds. |
| `0x0043BBA0` | 77 | cluster free function calling `PlatformWorker::Stop()` (bound `?Stop@PlatformWorker@@QAEXXZ` = 0x44C150) and then `_asm_beginthreadex_00453683` | emitted **75 vs 77**: mine sets the worker with `mov ecx,0x474DD4` (5 bytes) where retail has `mov esi,474DD4h` plus `push esi`/`pop esi` (7). The pass cannot see the callee's body (it is an absolute binding), so it defaults to the thiscall register of the declaration instead of retail's ESI. |

## Not attempted, and why

None of these has a byte delta: the reason column is what blocks it.

| region | size | entry reads | why |
| --- | ---: | --- | --- |
| `0x00408460` | 62 | `eax,ebx` | A 0x7D0-iteration slot walk that tests **EBX** without ever writing it, so the value is a live-in its caller supplies; that caller is not modelled. |
| `0x0040C600` | 69 | `eax,ecx` | EAX receiver plus **CL** as a bit index, an inner table indexed by CL, and one virtual `[esi+8]` call whose receiver is read from `[inner+0x1014]`. |
| `0x004133F0` | 91 | `ebx` | EBX receiver with the delete flag on the stack and a `ret 4`; every array-walking driver shape this family has tried yields ESI or EAX. |
| `0x00441520` | 97 | `eax,ecx` | EAX+ECX entry (count in EAX, base in ECX) *plus* a stack word argument; two live-in registers need a purpose-built context. |
| `0x00436AA0` | 76 | `ebx,esi,edi` | EBX receiver, EBP frame and a callee entered with EAX plus three stack arguments; three live-ins. |
| `0x00438950` | 79 | `esi` | The log callee 0x44B810 is variadic: the landed model passes `this` on the stack while retail passes it in ECX, so a declaration cannot reproduce the call. |
| `0x0043A4C0` | 68 | `esi,edi` | ESI object with EDI as a second live-in pointer across two indirect `[data_004662*]` calls. |
| `0x00437590` | 214 | `ebx` | EBX receiver, a 0x44-byte local frame, three virtual `[eax+30h]`/`[ecx+34h]`/`[eax+38h]` dispatches and two `rep movs` row copies. |
| `0x00437670` | 214 | `ebx` | The twin of 0x437590 (same shape with one extra `test eax,eax` early-out). |
| `0x0044C790` | 69 | `esi,esp` | ESI object, a virtual `[ecx+8]` call, `_asm_Ordinal_11_00452170` and a `ret 0Ch` whose three stack arguments are read at three different `[esp+8]`/`[esp+0Ch]` depths. |

## Closed before this wave (not re-attempted)

`0x41FD90` (63) was modelled exactly in wave 18 but emitted 75 bytes against the
region's 63; it has since been recovered by another agent, so it is listed here
only for completeness.

| region | size | status |
| --- | ---: | --- |
| `0x00412300` | 64 | four-way jump-table leaf; the table at 0x412340 is a sibling region, so a C++ `switch` emits its own table at the wrong address. Dropped by the 0x41 block agent in wave 18. |
| `0x004126D0` | 64 | the same, table at 0x412710. |
| `0x0041C0D0` | 78 | spans two complete functions (0x41C0D0 and 0x41C100); needs a manifest partition, not a model. |
| `0x004494D0` | 63 | fragment: ends in `jmp 0x449510`, whose loop tail is the sibling region 0x449510. |

## Bindings added to `matching2/msvc/regions.json`

- `@asm_Recovery_PolarToVectorRetail_0044c5d0@12` = `0x0044C5D0` - the
  `__fastcall` spelling a one-pointer-plus-two-float declaration produces (the
  pre-existing `@8` spelling is a different signature). Needed by 0x40B2A0.
- `_Angle_Normalize_0044bc70@4` = `0x0044BC70` - the `__stdcall` spelling of
  `float Angle_Normalize(float)`. Needed by 0x40B2A0.

Both were added with the manifest lock held by hand; `register_cluster.py
--apply` was not needed for them (they are plain linker bindings, not
registrations). No other manifest field was hand-edited: every region record went
through `promote_scratch.py --scratch /tmp/VeinRest/msvc --address <addr>
--apply`. `make` was not run.
