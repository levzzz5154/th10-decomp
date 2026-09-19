# The ten EDX-receiver `rep stosd` initialisers (wave 19) — 10 of 10 landed EXACT

2026-09-19, agent `RepsInitialisers`. The ten regions the 0x40 block agent
enumerated in `0040xxxx_wave18.md` §3 as "a zeroed or vtable-stamped record whose
pointer arrives in EDX and which is returned in EAX": `0x409F10` (17),
`0x409F50` (16), `0x4055A0` (29), `0x405C80` (28), `0x40C830` (34),
`0x40CBD0` (25), `0x40CBF0` (17), `0x40CF30` (16), `0x40D260` (29),
`0x40D3D0` (34). **245 bytes, 10 landings, 0 drops.** Work was done in
`/tmp/RepsInitialisers/msvc` (`cp -a matching2/msvc`) and promoted with
`promote_scratch.py --apply`, one address at a time.

Every landing below was re-probed against the maintained tree after promotion and
reports `EXACT`.

## The driver shape (this is the whole family)

The EAX-accessor shape from wave 18 has an EDX twin, and it is **one dead leading
`__fastcall` slot**:

```cpp
extern "C" __declspec(noinline) T* __fastcall Init(void* unused, T* obj) {
    (void)unused;
    memset(obj, 0, sizeof(T));
    ...
    return obj;
}
```

Declared that way MSVC homes `obj` in **EDX** and never reads ECX, so the
constant-size `memset` inlines to exactly retail's

```text
push edi / xor eax,eax / mov ecx,<count> / mov edi,edx / rep stosd
```

and `return obj;` gives the trailing `mov edx,eax`. No synthetic context shaping
was needed for any of these nine: the plain array-walking caller

```cpp
int __stdcall RepsContext(T** items, int count) {
    while (count--) { Init(0, *items++); }
    return 0;
}
```

leaves the declared EDX home alone. (The wave-18 accessor driver needed the
opposite — a member declaration whose `this` the pass *moves* to EAX; here the
declaration already names the home, so nothing has to be earned.)

Two more rules the ten confirm:

1. **`return (int)this + N` interior fills come from the pointer expression, not
   from a member.** `memset((char*)obj + 0x14, 0, 0x21CEA0)` emits
   `mov edi,edx / add edi,14h / mov ecx,873A8h / xor eax,eax` — note the
   *count-before-xor* order, which the whole-struct spellings never produce.
2. **A `rep stosd` `&= ~1u` before the fill is split by the scheduler** — see the
   negatives below. Routing the read-modify-write through a local pointer
   (`unsigned int* flag = (unsigned int*)((char*)obj + 0x24); *flag &= ~1u;`)
   stops the split and lands the fused `and dword ptr [edx+24h],0FEh`.

## Landings

| address | size | symbol | sha256(retail)[:16] |
| --- | ---: | --- | --- |
| `0x00409F10` | 17 | `@Init_00409f10@8` | `a4ae53c55559fe90` |
| `0x00409F50` | 16 | `@Init_00409f50@8` | `f4da04683fb90ca3` |
| `0x004055A0` | 29 | `@Init_004055a0@8` | `d6b2234107a85496` |
| `0x00405C80` | 28 | `@Init_00405c80@4` | `523b44faddf410e4` |
| `0x0040C830` | 34 | `@Init_0040c830@8` | `cf93319a3399b158` |
| `0x0040CBD0` | 25 | `@Init_0040cbd0@8` | `5a6eaa7b230d04c1` |
| `0x0040CBF0` | 17 | `@Init_0040cbf0@8` | `07da22e212a8bb01` |
| `0x0040CF30` | 16 | `@Init_0040cf30@8` | `331341303e9272a2` |
| `0x0040D260` | 29 | `@Init_0040d260@8` | `4b8f05d49feebdf9` |
| `0x0040D3D0` | 34 | `@Init_0040d3d0@8` | `b8270dd30b3103b2` |

### Probe lines (maintained tree)

```text
0x00409f10      17 bytes  @Init_00409f10@8  EXACT   src/unidentified/unassigned_00409f10.cpp
0x00409f50      16 bytes  @Init_00409f50@8  EXACT   src/unidentified/unassigned_00409f50.cpp
0x004055a0      29 bytes  @Init_004055a0@8  EXACT   src/unidentified/unassigned_004055a0.cpp
0x00405c80      28 bytes  @Init_00405c80@4  EXACT   src/unidentified/unassigned_00405c80.cpp
0x0040c830      34 bytes  @Init_0040c830@8  EXACT   src/unidentified/unassigned_0040c830.cpp
0x0040cbd0      25 bytes  @Init_0040cbd0@8  EXACT   src/unidentified/unassigned_0040cbd0.cpp
0x0040cbf0      17 bytes  @Init_0040cbf0@8  EXACT   src/unidentified/unassigned_0040cbf0.cpp
0x0040cf30      16 bytes  @Init_0040cf30@8  EXACT   src/unidentified/unassigned_0040cf30.cpp
0x0040d260      29 bytes  @Init_0040d260@8  EXACT   src/unidentified/unassigned_0040d260.cpp
0x0040d3d0      34 bytes  @Init_0040d3d0@8  EXACT   src/unidentified/unassigned_0040d3d0.cpp
```

### `0x00409F10` — `src/unidentified/unassigned_00409f10.cpp`, `layout/ltcg/reps_00409f10.json`

```cpp
#include <stddef.h>
extern "C" void *__cdecl memset(void *destination, int value, unsigned int size);

struct Rec_00409f10 { unsigned char pad_000[0x14]; };
#pragma code_seg(".text$01accessor")
extern "C" __declspec(noinline) void __fastcall
Init_00409f10(void* unused, Rec_00409f10* obj) {
    (void)unused;
    memset((char*)obj + 0x14, 0, 0x21CEA0);
}
#pragma code_seg()
```

### `0x00409F50` — `src/unidentified/unassigned_00409f50.cpp`, `layout/ltcg/reps_00409f50.json`

```cpp
#include <stddef.h>
extern "C" void *__cdecl memset(void *destination, int value, unsigned int size);

struct Rec_00409f50 { int words[0x10]; };
#pragma code_seg(".text$01accessor")
extern "C" __declspec(noinline) Rec_00409f50* __fastcall
Init_00409f50(void* unused, Rec_00409f50* obj) {
    (void)unused;
    memset(obj, 0, sizeof(Rec_00409f50));
    return obj;
}
#pragma code_seg()
```

### `0x004055A0` — `src/unidentified/unassigned_004055a0.cpp`, `layout/ltcg/reps_004055a0.json`

Binds `_data_004776ec` (0x004776EC, `data`).

```cpp
#include <stddef.h>
extern "C" void *__cdecl memset(void *destination, int value, unsigned int size);

struct Rec_004055a0 {
    unsigned int flags_000;
    unsigned char pad_004[0x24 - 0x04];
    unsigned int field_024;
    unsigned char pad_028[0x48 - 0x28];
};
extern "C" Rec_004055a0* data_004776ec;
#pragma code_seg(".text$01accessor")
extern "C" __declspec(noinline) Rec_004055a0* __fastcall
Init_004055a0(void* unused, Rec_004055a0* obj) {
    (void)unused;
    unsigned int* flag = (unsigned int*)((char*)obj + 0x24);
    *flag &= ~1u;
    memset(obj, 0, sizeof(Rec_004055a0));
    obj->flags_000 |= 2u;
    data_004776ec = obj;
    return obj;
}
#pragma code_seg()
```

### `0x00405C80` — `src/unidentified/unassigned_00405c80.cpp`, `layout/ltcg/reps_00405c80.json`

The one member of the family whose pointer arrives in **ECX**: retail is
`mov edx,ecx` then the fill out of EDX. Declaring `obj` as the *first* fastcall
slot is right, but the LTCG pass then re-homes it to EDX and drops the copy (26
bytes, first difference at `+0`). The fix is to make the address taken in the
driver, so the declared convention cannot be changed:

```cpp
// layout/ltcg/reps_00405c80_context.cpp
typedef Rec_00405c80* (__fastcall *InitFn_00405c80)(Rec_00405c80*);
int __stdcall RepsContext_00405c80(Rec_00405c80** items, int count) {
    InitFn_00405c80 fn = Init_00405c80;
    while (count--) { fn(*items++); }
    return 0;
}
```

```cpp
#include <stddef.h>
extern "C" void *__cdecl memset(void *destination, int value, unsigned int size);

struct Rec_00405c80 {
    unsigned char pad_000[0x204];
    int field_204;
    unsigned char pad_208[0x210 - 0x208];
};
#pragma code_seg(".text$01accessor")
extern "C" __declspec(noinline) Rec_00405c80* __fastcall
Init_00405c80(Rec_00405c80* obj) {
    memset(obj, 0, sizeof(Rec_00405c80));
    obj->field_204 = -1;
    return obj;
}
#pragma code_seg()
```

### `0x0040C830` — `src/unidentified/unassigned_0040c830.cpp`, `layout/ltcg/reps_0040c830.json`

Binds `_data_0046d0f0` (0x0046D0F0, `data`). The vtable store precedes the fill
in retail (`mov [edx],46D0F0h` before `rep stosd`), so it is dead code the
optimizer keeps — source it first.

```cpp
#include <stddef.h>
extern "C" void *__cdecl memset(void *destination, int value, unsigned int size);

struct Rec_0040c830 {
    void* vtable_000;
    unsigned char pad_004[0x1090 - 0x04];
    unsigned int tail_1090;
    unsigned int tail_1094;
};
extern "C" unsigned char data_0046d0f0;
#pragma code_seg(".text$01accessor")
extern "C" __declspec(noinline) Rec_0040c830* __fastcall
Init_0040c830(void* unused, Rec_0040c830* obj) {
    (void)unused;
    obj->vtable_000 = &data_0046d0f0;
    unsigned int* tail = (unsigned int*)((char*)obj + 0x1090);
    tail[0] = 0;
    tail[1] = 0;
    memset(obj, 0, sizeof(Rec_0040c830));
    return obj;
}
#pragma code_seg()
```

### `0x0040CBD0` — `src/unidentified/unassigned_0040cbd0.cpp`, `layout/ltcg/reps_0040cbd0.json`

Binds `__fltused` as `metadata` (the two `32.0f` stores). The two dead `+0x34`
and `+0x38` words are cleared by the fill and then stamped, so the stores come
after the `memset`; retail writes them descending, so source them descending.

```cpp
#include <stddef.h>
extern "C" void *__cdecl memset(void *destination, int value, unsigned int size);

struct Rec_0040cbd0 {
    unsigned char pad_000[0x34];
    float field_034;
    float field_038;
};
#pragma code_seg(".text$01accessor")
extern "C" __declspec(noinline) void __fastcall
Init_0040cbd0(void* unused, Rec_0040cbd0* obj) {
    (void)unused;
    memset(obj, 0, sizeof(Rec_0040cbd0));
    obj->field_038 = 32.0f;
    obj->field_034 = 32.0f;
}
#pragma code_seg()
```

### `0x0040CBF0` — `src/unidentified/unassigned_0040cbf0.cpp`, `layout/ltcg/reps_0040cbf0.json`

```cpp
#include <stddef.h>
extern "C" void *__cdecl memset(void *destination, int value, unsigned int size);

struct Rec_0040cbf0 { unsigned char pad_000[0x4]; };
#pragma code_seg(".text$01accessor")
extern "C" __declspec(noinline) void __fastcall
Init_0040cbf0(void* unused, Rec_0040cbf0* obj) {
    (void)unused;
    memset((char*)obj + 0x4, 0, 0x30);
}
#pragma code_seg()
```

### `0x0040CF30` — `src/unidentified/unassigned_0040cf30.cpp`, `layout/ltcg/reps_0040cf30.json`

```cpp
#include <stddef.h>
extern "C" void *__cdecl memset(void *destination, int value, unsigned int size);

struct Rec_0040cf30 { int words[0x77]; };
#pragma code_seg(".text$01accessor")
extern "C" __declspec(noinline) Rec_0040cf30* __fastcall
Init_0040cf30(void* unused, Rec_0040cf30* obj) {
    (void)unused;
    memset(obj, 0, sizeof(Rec_0040cf30));
    return obj;
}
#pragma code_seg()
```

(Also builds the sibling at `0x40CF40`: `memset` of `0x7E` dwords, then
`mov dword ptr [edx+2Ch],41000000h`, `mov eax,edx` — same shape, a different
record. Not in this ticket's ten.)

### `0x0040D260` — `src/unidentified/unassigned_0040d260.cpp`, `layout/ltcg/reps_0040d260.json`

Binds `_data_00477704` (0x00477704, `data`). Identical to `0x4055A0` with `+0x50`
for the dead clear, `0x68` for the fill and `data_00477704` for the publish.

```cpp
#include <stddef.h>
extern "C" void *__cdecl memset(void *destination, int value, unsigned int size);

struct Rec_0040d260 {
    unsigned int flags_000;
    unsigned char pad_004[0x50 - 0x04];
    unsigned int field_050;
    unsigned char pad_054[0x68 - 0x54];
};
extern "C" Rec_0040d260* data_00477704;
#pragma code_seg(".text$01accessor")
extern "C" __declspec(noinline) Rec_0040d260* __fastcall
Init_0040d260(void* unused, Rec_0040d260* obj) {
    (void)unused;
    unsigned int* flag = (unsigned int*)((char*)obj + 0x50);
    *flag &= ~1u;
    memset(obj, 0, sizeof(Rec_0040d260));
    obj->flags_000 |= 2u;
    data_00477704 = obj;
    return obj;
}
#pragma code_seg()
```

### `0x0040D3D0` — `src/unidentified/unassigned_0040d3d0.cpp`, `layout/ltcg/reps_0040d3d0.json`

Binds `_data_0046d0b4` (0x0046D0B4, `data`) — the **out-of-line copy of the
0x0040D280 `MessageParser` constructor** (same `0x1098`-byte body, same vtable,
same tail words). It is the same source shape as the inlined constructor inside
`src/game/message_host_init.cpp`, with the vtable store after the fill.

```cpp
#include <stddef.h>
extern "C" void *__cdecl memset(void *destination, int value, unsigned int size);

struct Rec_0040d3d0 {
    void* vtable_000;
    unsigned char pad_004[0x1090 - 0x04];
    unsigned int tail_1090;
    unsigned int tail_1094;
};
extern "C" unsigned char data_0046d0b4;
#pragma code_seg(".text$01accessor")
extern "C" __declspec(noinline) Rec_0040d3d0* __fastcall
Init_0040d3d0(void* unused, Rec_0040d3d0* obj) {
    (void)unused;
    unsigned int* tail = (unsigned int*)((char*)obj + 0x1090);
    tail[0] = 0;
    tail[1] = 0;
    memset(obj, 0, sizeof(Rec_0040d3d0));
    obj->vtable_000 = &data_0046d0b4;
    return obj;
}
#pragma code_seg()
```

## Negatives (no drops left; these are the spellings that *miss*, with deltas)

All three were measured in the throwaway copy with the same driver above.

| region | spelling that misses | emitted | retail | delta |
| --- | --- | ---: | ---: | --- |
| `0x4055A0` | `obj->field_024 &= ~1u;` (member form, no local pointer) | 34 | 29 | **+5, first diff `+0`** (`8b 4a 24 83 e1 fe` load/and vs `83 62 24 fe` RMW) |
| `0x40D260` | same, on `field_050` | 34 | 29 | **+5, first diff `+0`** |
| `0x405C80` | first-fastcall-slot declaration with the plain array-walking driver (no function pointer) | 26 | 28 | **-2, first diff `+0`** (pass re-homes `obj` to EDX, drops `mov edx,ecx`) |
| `0x405C80` | `__thiscall` member `Rec* Init()` , no arguments | 26 | 28 | **-2, first diff `+0`** (same re-home; `this` lands in EDX) |

The `+5` split is *the same source text*, only moved: `memset` first and the
`&= ~1u` second emits the fused `andl $0xfffffffe,0x24(%edx)` — but then it sits
*after* the `rep stosd`, and with the `or`/publish present the pass instead folds
the two into one register-carried `mov (%edx),%eax / or / mov %eax,(%edx)`
pattern, so the extent is wrong in a different way. There is no source position
that gets the fused form into retail's slot except the local pointer. Every other `and` spelling tried
(`& 0xFFFFFFFEu`, `& -2`, `(x>>1)<<1`, `& ~(1u<<0)`, `volatile`, cast through
`char*`, bitfield-cast, and `(x & ~1u) | 0`) also emits the split form — the
register it picks varies, the shape does not, so the field type and the constant
spelling are irrelevant. Only the routing through a local `unsigned int*` matters.

`m5_guard` (`if (field & 1u) field &= ~1u;`) is not a candidate either: it
emits `mov/test/je/and reg/mov/ret`, 15 bytes against 29.

## Tooling note

`matching2/tools/waves/cluster_attempt.py::_map_section` captures the map's
**section-relative offset** (`[0-9A-F]{4}:([0-9A-F]{8})`), not the size, which is
what its own callers use it for. With it, the adaptive size correction feeds the
*offset* back as a size and every attempt after the first dies as
`function ... extent is outside a MAP CODE contribution`, silently (after four
retries the loop exits without printing a line). The fixed reader is the second
hex field:

```python
re.search(r'[0-9A-Fa-f]{4}:[0-9A-Fa-f]{8}\s+([0-9A-Fa-f]{8})H\s+'
          + re.escape(section) + r'\b', maps[-1].read_text())
```

`_map_offset` next to it is correct; only the size reader is wrong.

## Related regions handed back

The same EDX/ESI-receiver rep-stos initialiser shape also covers `0x42AAE0`
(54, EDX, `rep stos` + field inits + publish to `+0x5460`/`+0x6274`),
`0x43BC20` (23, EDX), and the ESI trio `0x417840`, `0x428F30`, `0x41ACB0`.
They are outside this ticket; the driver recipe above is what they need, and
`VeinRecords` has them.
