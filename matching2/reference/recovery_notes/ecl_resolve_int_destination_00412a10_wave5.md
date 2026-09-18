# 0x00412A10 — ECL integer destination resolution: landed EXACT as a native-LTCG cluster

2026-09-19 (wave 5). `?ECL_ResolveIntDestination` (75 bytes) is now readable C++
compiled through the cluster path. Probe:

```
0x00412a10      75 bytes  ?ResolveIntDestination@EclInterpreter_00412a10@@QAEPAHH@Z  EXACT
```

Emitted 75 bytes against the declared 75, zero differing bytes, no relocations,
no pooled constants, no absolute bindings, no dropped sections — the body is the
region verbatim:

```
8b 90 d8 14 00 00   mov edx,[eax+14D8h]
8b 42 04            mov eax,[edx+4]
8b 50 04            mov edx,[eax+4]
56                  push esi
0f b7 72 08         movzx esi,word ptr [edx+8]
57                  push edi
bf 01 00 00 00      mov edi,1
d3 e7               shl edi,cl
85 f7               test esi,edi
74 29               je  412a56
8b 54 8a 10         mov edx,[edx+ecx*4+10h]
85 d2               test edx,edx
7c 10               jl  412a45
8d 48 08            lea ecx,[eax+8]
8b 81 04 10 00 00   mov eax,[ecx+1004h]
03 c2               add eax,edx
5f                  pop edi
03 c1               add eax,ecx
5e                  pop esi
c3                  ret
8b 80 14 10 00 00   mov eax,[eax+1014h]
8b 30               mov esi,[eax]
52                  push edx
8b c8               mov ecx,eax
ff 56 08            call dword ptr [esi+8]
5f                  pop edi
5e                  pop esi
c3                  ret
5f                  pop edi
33 c0               xor eax,eax
5e                  pop esi
c3                  ret
```

## Registers retail's callers use, and whether the body keeps them

Retail's nine call sites (all in the assembly of `src/script/ecl_vm.cpp`, e.g.
0x411157, 0x411a15) set up `mov eax,ebx` (EBX = the script interpreter that owns
the `+0x14D8` handle) and `mov ecx,<index>` (sometimes a constant, sometimes a
loaded slot) and then `call`. The model keeps that ABI exactly: the interpreter
arrives in **EAX** and is only read (`[eax+14D8h]`); the **index** arrives in
**ECX** and is consumed by the shift and the table index, after which ECX is
reused for the frame address. The result comes back in EAX and the body ends in a
plain `ret` (no callee cleanup). ESI/EDI are saved and restored around the body
exactly as retail does.

## The one decision that fixes the bytes

The address is `frame + frame->frame_base + displacement`, and c2 emits the two
`add`s in the **source operand order it is given**, so the sum must reach c2 as
*(base, displacement, frame)*. c2 canonicalises pointer arithmetic, so every
spelling that gives it the frame as a pointer-valued summand puts the frame add
first:

```
8d 48 08   lea ecx,[eax+8]
8b 81 ..   mov eax,[ecx+1004h]
03 c1      add eax,ecx        <- frame first: WRONG, 2 differing bytes
5f         pop edi
03 c2      add eax,edx
```

The shape that works is to name the slot **as an lvalue reference into the
table** (`const int& displacement = table->offsets[index];`). c2 then sees a
*load* operand, not a value it already holds, and orders the adds
`add eax,edx` / `add eax,ecx` — retail's order — while still emitting exactly one
table load (the reference is CSE'd with the load the sign test needs). Writing
`table->offsets[index]` directly in the sum has the same effect; a plain
`int offset` local has the wrong one. The two spellings differ by two bytes and
nothing else.

Three retail siblings in the same family prove the order is the intended one, not
a coincidence: `ECL_ResolveVariableValue` (0x450030), `ECL_ResolveFloatDestination`
(0x450070) and the 11-byte unassigned helper at 0x44DF20
(`mov eax,[ecx+1004h]; add eax,edx; add eax,ecx; ret`) all add the displacement
before the frame address.

Two more structural facts the body pins:

- `if (mask & (1 << index)) { … } return 0;` (not the inverted
  `if (!(…)) return 0;`) is what puts the returning `xor eax,eax` block at the
  end of the function, so the test compiles to retail's `je 412a56`.
- `if (displacement >= 0) { … } return owner->Resolve(displacement);` is what
  puts the virtual-call block out of line after the positive block, so the slot
  test compiles to retail's `jl 412a45`.
- The base must be loaded **through the frame** (`frame->frame_base`), not flat
  from the VM. That is what makes c2 materialise `lea ecx,[eax+8]` before the
  load and reuse ECX as the load's base register (`[ecx+1004h]`, retail's
  encoding). A flat `vm->field_100C` access compiles to the same value but a
  74-byte body (`mov ecx,[eax+100Ch]; add ecx,edx; lea eax,[ecx+eax+8]`).

## The model (verbatim, as measured)

```cpp
// 0x00412A10..0x00412A5A: hand back where the integer variable selected by
// the index in CL lives. The variable table marks the live slots with a
// 16-bit mask; a slot's displacement is either a non-negative offset into the
// interpreter's pooled frame or a negative one the value owner resolves. The
// interpreter arrives in EAX and the index in ECX, a convention only a native
// LTCG link chooses, so this region is compiled as a cluster.

struct EclVarTable_00412a10 {
    unsigned char pad_000[8];
    unsigned short valid_mask;  // +0x0008
    unsigned char pad_00a[6];
    int offsets[1];             // +0x0010
};

struct EclValueOwner_00412a10 {
    virtual void Reserved0();
    virtual void Reserved1();
    virtual int* Resolve(int displacement);
};

struct EclFrame_00412a10 {
    unsigned char pad_000[0x1004];
    int frame_base;                 // +0x1004
    unsigned char pad_1008[4];
    EclValueOwner_00412a10* owner;  // +0x100C
};

struct EclVm_00412a10 {
    void* field_000;
    EclVarTable_00412a10* table;  // +0x0004
    EclFrame_00412a10 frame;      // +0x0008
};

struct EclHandle_00412a10 {
    void* field_000;
    EclVm_00412a10* vm;  // +0x0004
};

struct EclInterpreter_00412a10 {
    unsigned char pad_000[0x14D8];
    EclHandle_00412a10* handle;  // +0x14D8
    __declspec(noinline) int* ResolveIntDestination(int index);
};

#pragma code_seg(".text$01resolve")
int* EclInterpreter_00412a10::ResolveIntDestination(int index) {
    EclVm_00412a10* vm = handle->vm;
    EclVarTable_00412a10* table = vm->table;
    if (table->valid_mask & (1 << index)) {
        const int& displacement = table->offsets[index];
        if (displacement >= 0) {
            EclFrame_00412a10* frame = &vm->frame;
            return (int*)((char*)frame + frame->frame_base + displacement);
        }
        return vm->frame.owner->Resolve(displacement);
    }
    return 0;
}
#pragma code_seg()
```

The owner handle (`handle->vm`) is a two-word object whose second word is the
VM; the VM's `+4` is the variable table and its frame is a by-value member at
`+8` (so `frame+0x1004` = `vm+0x100C` and `frame+0x100C` = `vm+0x1014`). The
owner call is the frame's third virtual slot (`call [esi+8]`), which is why the
region needs no external binding at all and its relocation list is empty.

## Layout, driver, registration

`layout/ltcg/ecl_resolve_int_destination_00412a10.json`:

```json
{
  "schema_version": 1,
  "name": "ecl_resolve_int_destination_00412a10",
  "source": "src/script/ecl_resolve_int_destination_00412a10.cpp",
  "driver": "layout/ltcg/ecl_resolve_int_destination_00412a10_context.cpp",
  "headers": [],
  "image_base": "0x00400000",
  "description": "Integer destination resolution compiled with native LTCG so the interpreter arrives in EAX and the variable index in ECX, as retail's call sites do.",
  "functions": [
    {
      "name": "EclInterpreter_ResolveIntDestination",
      "symbol": "?ResolveIntDestination@EclInterpreter_00412a10@@QAEPAHH@Z",
      "section": ".text$01resolve",
      "address": "0x00412A10",
      "size": 75,
      "actual_abi": "interpreter in EAX; index in ECX; plain RET"
    }
  ],
  "context": {
    "symbol": "EclResolveIntDestinationContext@12",
    "section": ".text$03context",
    "address": "0x412a60",
    "size": 42,
    "description": "Synthetic array-walking caller that establishes the observed register convention; not recovered game code."
  },
  "gaps": [
    {
      "section": ".text$00layout",
      "address": "0x00401000",
      "size": 72208
    },
    {
      "section": ".text$02layout",
      "address": "0x412a5b",
      "size": 5
    }
  ],
  "constants": [],
  "absolute_symbols": []
}
```

`layout/ltcg/ecl_resolve_int_destination_00412a10_context.cpp`:

```cpp
// Compiler context only; never selected as recovered game code.
#include "../../src/script/ecl_resolve_int_destination_00412a10.cpp"

#pragma code_seg(".text$03context")
extern "C" __declspec(noinline) int* __stdcall EclResolveIntDestinationContext(
        EclInterpreter_00412a10** items, int index, int count) {
    int* last = 0;
    while (count--) {
        last = (*items++)->ResolveIntDestination(index);
    }
    return last;
}
#pragma code_seg()
```

The gap after the function is exactly the five padding bytes the manifest already
records at `0x00412A5B`, so the synthetic context lands on the 16-byte boundary at
`0x412A60` and is 42 bytes. The context shape (an array walk whose element pointer
changes per call while the index stays live in a register) is what makes the whole
program pass hand the callee the interpreter in EAX and the index in ECX; three
other context shapes (loop counter as the index, a dereferenced result, and a
constant index) produced the identical 75-byte body, so the convention is not
sensitive to the exact walk.

Landed with a single `register_cluster.py --layout
layout/ltcg/ecl_resolve_int_destination_00412a10.json --apply` run from
`matching2/msvc` (the layout is the only claimant of its source), so the manifest's
`translation_units` list was updated by the tool and not by hand. The region keeps
its `_asm_ECL_ResolveIntDestination_00412a10` binding in `symbols` and its
declaration in `asm_symbols.hpp`, which is how the nine assembly call sites in
`ecl_vm.cpp` still reach it (same pattern as the landed
`BulletEntity_ClearResourceList_0040c6e0`).

## Shapes tried before the landing (all measured, 2-byte residual unless noted)

- Six permutations and both groupings (left/right) of `base`, `displacement`,
  `frame`, in three field spellings (`int`, `char*`, `unsigned`) and five setup
  patterns (inline, `int base`, `char* pool`, `int frame_address`, `int fa`) —
  216 enumerated shapes, all landing on `add eax,ecx; add eax,edx`.
- Int-cast spellings of the frame (`(int)frame`, `(unsigned)frame`, a union
  member, `int fa = (int)(char*)ff`, `int frame_address = (int)vm + 8`) and
  int-address loads (`*(int*)(frame_address + 0x1004)`) — same order.
- A flat VM layout (base at `vm+0x100C`, frame term `(char*)vm + 8`,
  `&vm->frame`, `+8` last): 74 bytes, `mov ecx,[eax+100Ch]; add ecx,edx;
  lea eax,[ecx+eax+8]`.
- An inlined `__forceinline int* Value(int)` member of the frame (the shape the
  11-byte 0x44DF20 helper presumably has): same 2-byte residual. A standalone
  `__fastcall` model of that helper also fails to reproduce 0x44DF20's bytes, so
  the operand order really is decided by how the summands reach c2, not by the
  receiver's register.
- Pointer-field variants (`char* frame_base` with `pool + offset + (int)frame`),
  pointer-cast sums (`(char*)(base + offset) + (int)frame`), `int*`-scaled sums
  (which scale the offset by four and are semantically wrong), and one doubled
  load of the slot: the doubled load is the shape that flips the order.
