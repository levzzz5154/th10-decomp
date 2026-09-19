# Record-shaped adjacent-store and copy regions (wave 19) - 11 landed in 7 layouts

2026-09-19, agent `VeinRecords`. Scope: the remaining vein regions whose body is a
run of adjacent field initialisation or copying - two or more stores to one base
register, or a `rep movs`/`rep stos` pair - grouped per record into one
multi-function layout with even-numbered gap sections and odd-numbered function
sections so the linker places them in address order. Work was done in
`/tmp/VeinRecords/msvc2`, a fresh copy of the maintained tree taken after
`RepsInitialisers` confirmed it keeps only the ten `0x0040xxxx` `rep stosd`
initialisers.

**Landing total: 11 regions / 487 bytes across 7 layouts.** Both manifest gates
pass on the result: `build_msvc.validate_project` reports 4425 regions / 2354
units and `ltcg_cluster.load_clusters` accepts every cluster. Every landing was
re-probed `EXACT` against the maintained tree after promotion. No manifest field
was hand-edited; all 11 went through
`promote_scratch.py --scratch /tmp/VeinRecords/msvc2 --address <addr> --apply`,
one call per region (the first call for a layout is refused until every region it
owns shares its source, which is expected and the last call registers it). `make`
was not run - the owner gates the build once per wave.

## Landings per layout

| layout | regions | bytes |
|---|---:|---:|
| `layout/ltcg/timer_arm_record_00404ca0.json` | 2 | 113 |
| `layout/ltcg/record_write_runs_b_0040.json` | 2 | 77 |
| `layout/ltcg/record_links_0042.json` | 3 | 132 |
| `layout/ltcg/holder_copy_00442180_d.json` | 1 | 20 |
| `layout/ltcg/publish_index_0040ada0.json` | 1 | 25 |
| `layout/ltcg/timer_arm_float_00405450.json` | 1 | 57 |
| `layout/ltcg/flag_broadcast_0041fd90.json` | 1 | 63 |

### Probe lines

```
0x00404ca0      56 bytes  ?Arm@TimerArmRecord_00404ca0@@QAEXXZ        EXACT
0x0043c930      57 bytes  ?Arm@TimerArmRecord_0043c930@@QAEXXZ        EXACT
0x004020b0      56 bytes  ?Clear@WriteRunB_004020b0@@QAEXXZ           EXACT
0x0044c0e0      21 bytes  ?Init@WriteRunB_0044c0e0@@QAEXXZ            EXACT
0x0042aae0      54 bytes  @Init_0042aae0@8                            EXACT
0x0042abd0      55 bytes  ?Clear@ListHolder_0042abd0@@QAEXXZ          EXACT
0x0043bc20      23 bytes  @Init_0043bc20@8                            EXACT
0x00442180      20 bytes  ?CopyTo@Triple_00442180@@QAEXPAUHolder_00442180@@@Z  EXACT
0x0040ada0      25 bytes  _Publish_0040ada0@8                         EXACT
0x00405450      57 bytes  ?Arm@TimerArm_00405450@@QAEXH@Z             EXACT
0x0041fd90      63 bytes  @Update_0041fd90@8                         EXACT
```

## Source text

#### `0x00404CA0` + `0x0043C930` (113 bytes, one layout) - `src/unidentified/timer_arm_record_00404ca0.cpp`

Two timer arms of one record family.  `0x00404CA0` uses the fields at
`+0x70..+0x80`, `0x0043C930` the identical layout at `+0x30..+0x40`, so they share
one source and one EAX-receiver driver.  The second arm's leading store needed the
pointer spelling: a direct `field_02c = 1;` sinks into the `test cl,1` slot below
the flag load (14 differing bytes), `volatile int* p = &field_02c; *p = 1;` keeps
it first.

```cpp
// Two timer-arm leaves of one record family, each entered with its record in
// EAX (a convention no C++ declaration names).  0x00404CA0 arms the record at
// +0x70 and 0x0043C930 the identical layout at +0x30: while the flag word is
// not yet running, the four fields take the stopped sentinels, then the three
// live fields are forced to the -1/0/0 stopped state.  The leading store of the
// second arm is spelled through a pointer so the scheduler keeps it ahead of the
// flag load, which retail does and a direct member store does not.
struct TimerArmRecord_00404ca0 {
    unsigned char pad_000[0x70];
    int field_070;
    int field_074;
    int field_078;
    int field_07c;
    unsigned int flags_080;
    __declspec(noinline) void Arm();
};

struct TimerArmRecord_0043c930 {
    unsigned char pad_000[0x2C];
    int field_02c;
    int field_030;
    int field_034;
    int field_038;
    int field_03c;
    unsigned int flags_040;
    __declspec(noinline) void Arm();
};

#pragma code_seg(".text$01arm")
void TimerArmRecord_00404ca0::Arm() {
    if (!(flags_080 & 1u)) {
        field_074 = 0;
        field_070 = 0xFFF0BDC1;
        field_078 = 0;
        field_07c = 0x00476F78;
        flags_080 |= 1u;
    }
    field_074 = 0;
    field_078 = 0;
    field_070 = -1;
}
#pragma code_seg()

#pragma code_seg(".text$03arm2")
void TimerArmRecord_0043c930::Arm() {
    volatile int* p = &field_02c; *p = 1;
    if (!(flags_040 & 1u)) {
        field_034 = 0;
        field_030 = 0xFFF0BDC1;
        field_038 = 0;
        field_03c = 0x00476F78;
        flags_040 |= 1u;
    }
    field_034 = 0;
    field_038 = 0;
    field_030 = -1;
}
#pragma code_seg()
```

#### `0x004020B0` + `0x0044C0E0` (77 bytes, one layout) - `src/unidentified/record_write_runs_b_0040.cpp`

A mask clear across eight flag words and a vtable stamp with four cleared fields.
Both are single-load EAX-receiver leaves; the mask is a local so the compiler
emits `and [eax+off],ecx` for the seven tail words exactly as retail does.

```cpp
// Record write runs whose receiver arrives in EAX: a mask clear across eight
// flag words (0x004020B0) and a vtable stamp with four cleared fields
// (0x0044C0E0).
struct WriteRunB_004020b0 {
    unsigned char pad_000[0x6C];
    unsigned int flags_06c;              // +0x06C
    unsigned char pad_070[0x40];
    unsigned int flags_0b0;              // +0x0B0
    unsigned char pad_0b4[0x48];
    unsigned int flags_0fc;              // +0x0FC
    unsigned char pad_100[0x28];
    unsigned int flags_128;              // +0x128
    unsigned char pad_12c[0x48];
    unsigned int flags_174;              // +0x174
    unsigned char pad_178[0x38];
    unsigned int flags_1b0;              // +0x1B0
    unsigned char pad_1b4[0x48];
    unsigned int flags_1fc;              // +0x1FC
    unsigned char pad_200[0x28];
    unsigned int flags_228;              // +0x228
    __declspec(noinline) void Clear();
};

struct WriteRunB_0044c0e0 {
    void* stamp_000;                     // +0x000
    int field_004;                       // +0x004
    int field_008;                       // +0x008
    int field_00c;                       // +0x00C
    int field_010;                       // +0x010
    __declspec(noinline) void Init();
};

#pragma code_seg(".text$01b")
void WriteRunB_004020b0::Clear() {
    unsigned int mask = ~1u;
    flags_06c &= mask;
    flags_0b0 &= mask;
    flags_0fc &= mask;
    flags_128 &= mask;
    flags_174 &= mask;
    flags_1b0 &= mask;
    flags_1fc &= mask;
    flags_228 &= mask;
}
#pragma code_seg()

#pragma code_seg(".text$03c")
void WriteRunB_0044c0e0::Init() {
    stamp_000 = (void*)0x004703E4;
    field_004 = 0;
    field_008 = 0;
    field_00c = 0;
    field_010 = 0;
}
#pragma code_seg()
```

#### `0x0042AAE0` + `0x0042ABD0` + `0x0043BC20` (132 bytes, one layout) - `src/unidentified/record_links_0042.cpp`

The clearest record group: `0x0042AAE0` and `0x0042ABD0` are two leaves of the
same linked-record layout (head/tail at `+0x627C/+0x6280`, node links at
`+4/+8`); `0x0043BC20` is the same initialiser shape on a small record.  The two
initialisers take the record in **EDX** via a dead leading `__fastcall` slot
(`RepsInitialisers`' recipe, credited below); the unlinker is a plain EAX
member.  The four contiguous links are written through one shared pointer, which
is what keeps retail's `+0x5460` store between the two zero stores rather than
below them (7 differing bytes otherwise).

```cpp
// Two leaves of one linked-record layout: 0x0042AAE0 initialises the record
// (clearing it and wiring the four tail links at +0x6274..+0x6280 to itself),
// 0x0042ABD0 unlinks its head/tail pair.  The initialiser receives its record in
// EDX (dead leading __fastcall slot) and the unlinker in EAX (member receiver).
struct RecordInit_0042aae0 {
    unsigned char data_000[0x5460];
    void* self_5460;                     // +0x5460
    unsigned char pad_5464[0xE10];
    void* link_6274;                     // +0x6274
    void* link_6278;                     // +0x6278
    void* link_627c;                     // +0x627C
    void* link_6280;                     // +0x6280
};
extern "C" __declspec(noinline) RecordInit_0042aae0* __fastcall
Init_0042aae0(void* unused, RecordInit_0042aae0* record);
#pragma code_seg(".text$01init")
RecordInit_0042aae0* __fastcall Init_0042aae0(void* unused, RecordInit_0042aae0* record) {
    (void)unused;
    memset(record, 0, sizeof(RecordInit_0042aae0));
    void** tail = &record->link_6274;
    tail[0] = (void*)((unsigned char*)record + 0x5464);
    record->self_5460 = record;
    tail[2] = 0;
    tail[3] = 0;
    tail[1] = record;
    return record;
}
#pragma code_seg()

struct RecordInit_0043bc20 {
    unsigned int flags_000;              // +0x000
    unsigned char pad_004[0x3C];
    unsigned int flags_040;              // +0x040
};
extern "C" __declspec(noinline) RecordInit_0043bc20* __fastcall
Init_0043bc20(void* unused, RecordInit_0043bc20* record);
#pragma code_seg(".text$05init2")
RecordInit_0043bc20* __fastcall Init_0043bc20(void* unused, RecordInit_0043bc20* record) {
    (void)unused;
    unsigned int* p = &record->flags_040;
    *p &= ~1u;
    memset(record, 0, sizeof(RecordInit_0043bc20));
    record->flags_000 |= 2u;
    return record;
}
#pragma code_seg()

struct ListNode_0042abd0 {
    unsigned char pad_000[4];
    ListNode_0042abd0* prev_004;         // +0x004
    ListNode_0042abd0* next_008;         // +0x008
};
struct ListHolder_0042abd0 {
    unsigned char pad_000[0x627c];
    ListNode_0042abd0* head_627c;        // +0x627C
    ListNode_0042abd0* tail_6280;        // +0x6280
    __declspec(noinline) void Clear();
};
#pragma code_seg(".text$03unlink")
void ListHolder_0042abd0::Clear() {
    if (head_627c)
        head_627c->next_008 = tail_6280;
    if (tail_6280)
        tail_6280->prev_004 = head_627c;
    head_627c = 0;
    tail_6280 = 0;
}
#pragma code_seg()
```

#### `0x00442180` (20 bytes) - `src/unidentified/holder_copy_00442180.cpp`

Three bytes copied into the `+0/+4/+8` fields of a destination record.  The
destination is in EAX and the source in ECX; modelling it as a method of the
**source** type is what produces that pair - as a method of the destination type
the compiler kept the destination in ECX and promoted the argument to EAX (6
differing bytes, both spellings).

```cpp
// 0x00442180: copy the three bytes of a source triple into the +0/+4/+8 fields
// of a destination record.  Modelled as a method of the SOURCE type, so the
// natural __thiscall receiver keeps the source in ECX and the whole-program pass
// promotes the destination argument to EAX, which is retail's register pair.
struct Holder_00442180 { unsigned int field_000, field_004, field_008; };
struct Triple_00442180 {
    unsigned char b0, b1, b2;
    __declspec(noinline) void CopyTo(Holder_00442180* dest);
};
#pragma code_seg(".text$01copy")
void Triple_00442180::CopyTo(Holder_00442180* dest) {
    dest->field_008 = b2;
    dest->field_004 = b1;
    dest->field_000 = b0;
}
#pragma code_seg()
```

#### `0x0040ADA0` (25 bytes) - `src/unidentified/publish_index_0040ada0.cpp`

Index in EAX, record in ECX (the pointer-argument pair).  A free `__stdcall`
whose first parameter is the index and second the record earns exactly that; the
global it publishes is bound in the layout's `absolute_symbols`.

```cpp
// 0x0040ADA0: publish the strided record selected by an index and stamp that
// index into the record's +0x3C/+0x40 fields.  The index arrives in EAX and the
// record in ECX, the pointer-argument pair convention the EAX driver earns.
struct Indexed_0040ada0 {
    unsigned char pad_000[0x3c];
    unsigned int field_03c;              // +0x03C
    unsigned int field_040;              // +0x040
};
extern "C" unsigned int* data_00477848;
extern "C" __declspec(noinline) void __stdcall Publish_0040ada0(unsigned int index, Indexed_0040ada0* record);
#pragma code_seg(".text$01pub")
void __stdcall Publish_0040ada0(unsigned int index, Indexed_0040ada0* record) {
    data_00477848 = (unsigned int*)(index * 0x30 + 0x00474788);
    record->field_03c = index;
    record->field_040 = index;
}
#pragma code_seg()
```

#### `0x00405450` (57 bytes) - `src/unidentified/timer_arm_float_00405450.cpp`

The record arrives in EAX and the count on the stack; the count is stored as an
int pair and as a float.  The float store needs `__fltused` bound as metadata in
the layout's `absolute_symbols`; nothing converts float to int, so no `__ftol2`.

```cpp
// 0x00405450: arm a timer leaf whose record arrives in EAX and whose count comes
// on the stack; the count is stored as an int pair and as a float.
struct TimerArm_00405450 {
    int field_000;                       // +0x000
    int field_004;                       // +0x004
    float field_008;                     // +0x008
    int field_00c;                       // +0x00C
    unsigned int flags_010;              // +0x010
    __declspec(noinline) void Arm(int value);
};
#pragma code_seg(".text$01arm")
void TimerArm_00405450::Arm(int value) {
    if (!(flags_010 & 1u)) {
        field_004 = 0;
        field_000 = 0xFFF0BDC1;
        field_008 = 0.0f;
        field_00c = 0x00476F78;
        flags_010 |= 1u;
    }
    field_004 = value;
    field_000 = value - 1;
    field_008 = (float)value;
}
#pragma code_seg()
```

#### `0x0041FD90` (63 bytes) - `src/unidentified/flag_broadcast_0041fd90.cpp`

Three quarter-paths of one flag.  Two levers were needed: the early exit and the
tail both `return 1`, which MSVC merges into a single trailing `mov eax,1; ret`
(the `if (!(...)) return 0;` spelling gave the return-first layout, 15 bytes);
and the global bit and the record flag are cleared through pointers to their
fields so MSVC emits `and [mem],imm` instead of a load/and/store (12 differing
bytes otherwise).  The record arrives in EDX via the dead `__fastcall` slot.

```cpp
// 0x0041FD90: if a record is flagged, raise the running bit of three
// sub-records, clear a global bit, publish a global mode and clear the flag.
// Both the early exit and the tail return 1, so MSVC merges them into one.
// The record arrives in EDX (dead leading __fastcall slot).  The global and the
// record flag are cleared through pointers to their fields so MSVC emits the
// read-modify-write `and [mem],imm` retail has instead of a load/and/store.
struct Sub_0041fd90 { unsigned char pad_000[4]; unsigned int flags_004; };
struct Owner_0041fd90 {
    unsigned char pad_000[0x0C];
    Sub_0041fd90* a_00c;                 // +0x00C
    Sub_0041fd90* b_010;                 // +0x010
    unsigned char pad_014[0x89a8 - 0x14];
    Sub_0041fd90* c_89a8;                // +0x89A8
};
struct Flagged_0041fd90 { unsigned int flags_000; };
extern "C" Owner_0041fd90* data_004776e0;
extern "C" unsigned int data_00491ff4;
extern "C" unsigned int data_00491fb8;
extern "C" __declspec(noinline) int __fastcall Update_0041fd90(void* unused, Flagged_0041fd90* record);
#pragma code_seg(".text$01flag")
int __fastcall Update_0041fd90(void* unused, Flagged_0041fd90* record) {
    (void)unused;
    if (!(record->flags_000 & 2u))
        return 1;
    Owner_0041fd90* owner = data_004776e0;
    owner->a_00c->flags_004 |= 2u;
    owner->b_010->flags_004 |= 2u;
    owner->c_89a8->flags_004 |= 2u;
    unsigned int* global = &data_00491ff4;
    *global &= 0xFFFFEFFFu;
    unsigned int* mode = &data_00491fb8;
    *mode = 4u;
    unsigned int* flags = &record->flags_000;
    *flags &= ~2u;
    return 1;
}
#pragma code_seg()
```

## Drops

### Probed, with a measured delta

| address | size | model | emitted | first diff | what is left |
|---|---:|---|---:|---|---|
| `0x0044C6E0` | 114 | member `Set(unsigned a0..a15)`, 16 stores | 106 | `+0` `89 08` vs `8b 4c 24 04` | The pass promotes `a0` to ECX and `a1` to EDX and pops only `ret 38`; retail has all sixteen on the stack and `ret 40`. Also tried a free `__stdcall` 17-arg model and three driver shapes (registers kept live, arguments loaded from a local array, plain constants); all emit the same two promotions, so this is an ABI tie-break that needs a caller with ECX/EDX occupied - a synthetic driver cannot express it. |
| `0x004014D0` | 32 | `field_896c=0; field_8970=0; ++count_8990; return 1;` | 26 | - | The model is byte-identical over all 26 function bytes; the region's last six bytes are the `CC CC CC CC CC CC` alignment run. Like the block's other INT3-suffixed regions it wants a `padding` reclassification, not a cluster function. |
| `0x00417840` | 33 | ESI-receiver `Init` calling `0x00418C40` with `this+0x24` in EDX | 35 | `+7` extra `33 c9` | The callee takes its only argument in EDX, which needs the dead leading `__fastcall` slot in the *caller*, and materialising that slot's `0` costs the extra `xor ecx,ecx` (`lea 0x24(%esi),%edx` is otherwise exact, and the receiver does land in ESI). Only a convention that reads EDX without an ECX argument would remove it. |

### Structural: one manifest region holding two functions

The loader requires each declared function to be exactly one complete compiler
contribution, and `register_cluster` requires the declared size to equal the
region size, so a region that contains two adjacent functions cannot be owned by
one cluster.  Each of these needs the region split into two records first; none
was probed because the split is the blocker, not the body.  The sub-extents are
from the retail disassembly.

| address | region | sub-extents |
|---|---:|---|
| `0x00421C00` | 74 | predicate `0x421C00..0x421C0B` (11) then an eight-word arg-store ladder `0x421C0B..0x421C4A` (63) |
| `0x00424530` | 84 | predicate `0x424530..0x42453D` (13) then a ten-word arg-store ladder (71) |
| `0x00449A50` | 64 | two identical 32-byte record-copy bodies (`0x449A50`, `0x449A70`), differing only in where `xor ecx,ecx` sits |
| `0x0041C0A0` | 41 | 16-byte `rep movsd` record copy then a 25-byte list insert |
| `0x00449A30` | 17 | 16-byte `rep stosd` clear then a stray `ret` |
| `0x0042A9E0` | 40 | two 20-byte `rep stosd` clears, the second preceded by a call to `0x00418C40` |
| `0x00441E00` | 51 | 20-byte two-component vector add then a 31-byte three-component subtract |

### Handed on, not attempted

`RepsInitialisers` keeps the ten `0x0040xxxx` EDX-receiver `rep stosd`
initialisers and handed the rest of that family here; two remain because they are
ESI-receiver with an EH vector-constructor call that needs a five-argument
anchor: `0x00428F30` (42, calls `0x0045252D` on `this+0xA0`) and `0x0041ACB0`
(54, calls `0x0045252D` on `this+0x14`, then publishes `this` to `0x00477818`).
The remaining three-register field accumulators `0x00436D60`, `0x00446530` and
`0x00446570` (55 bytes each, accumulator in EAX, packed word in EDX, counter
pointer in ESI) need a three-register convention and were not attempted.

## New levers this wave added to the family

1. **The dead leading `__fastcall` slot generalises to EDX-receiver record
   inits** (credit `RepsInitialisers`): `extern "C" T* __fastcall Init(void*, T*)`
   with `(void)unused;` puts the record in EDX, `memset(obj,0,sizeof(T))` expands
   to the exact `push edi / xor eax,eax / mov ecx,N / mov edi,edx / rep stosd`,
   and `return obj` produces the trailing `mov edx,eax`.
2. **`x &= ~1u` through a direct member emits load/and/store; through a pointer to
   the field it emits `and [mem],0FFFFFFFEh`.**  This is the fix for the spelling
   `RepsInitialisers` was still working; it is required in `0x0043BC20`.
3. **Model a record-to-record copy as a method of the SOURCE type**, not the
   destination, to get destination in EAX and source in ECX (`0x00442180`).
4. **Two merged `return`s** (`if (!(f & bit)) return 1; ... return 1;`) reproduce
   retail's `je` to a single trailing `mov eax,1; ret` where `return 0` on the
   early exit does not (`0x0041FD90`).
5. **A shared pointer over contiguous fields pins store order** that the scheduler
   otherwise sinks (`0x0042AAE0`'s four links, `0x0043C930`'s leading store).
