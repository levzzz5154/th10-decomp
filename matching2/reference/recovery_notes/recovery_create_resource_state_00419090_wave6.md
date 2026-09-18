# Region `0x00419090` (67 bytes) — wave 6

Date: 2026-09-19. Status: **NOT EXACT — blocked on two whole-program register
agreements with callees that are still assembly.** Nothing was registered in the
maintained manifest and no maintained source was touched; every attempt below ran
in `cp -a matching2/msvc /tmp/CreateResourceState/msvc`, driven through
`matching2/tools/waves/cluster_attempt.py`. The closest shape leaves the region
either **two bytes long** (69 vs 67) or, at exactly 67 bytes, with the block in
the wrong register and the manager in ESI instead of EBX.

## What the region is

`0x00419090..0x004190D2` creates the stage-tip manager that
`0x00418D40` publishes to `data_00477814`:

```
419090  push %ebx
419091  push $0x1a8
419096  call 0x452493              ; cdecl allocator wrapper
41909b  add  $0x4,%esp
41909e  test %eax,%eax
4190a0  je   4190ad
4190a2  mov  %eax,%edx             ; the fresh block arrives in EDX
4190a4  call 0x418d40              ; construct; also returns the block in EAX
4190a9  mov  %eax,%ebx             ; the manager lives in EBX from here on
4190ab  jmp  4190af
4190ad  xor  %ebx,%ebx
4190af  call 0x418e30              ; bring up the scheduler callbacks; reads EBX
4190b4  test %eax,%eax
4190b6  je   4190cf                ; success -> return the manager
4190b8  test %ebx,%ebx
4190ba  je   4190cb
4190bc  push %ebx
4190bd  call 0x418ee0              ; __stdcall teardown, callee pops
4190c2  push %ebx
4190c3  call 0x4524a1              ; cdecl CRT free
4190c8  add  $0x4,%esp
4190cb  xor  %eax,%eax
4190cd  pop  %ebx
4190ce  ret
4190cf  mov  %eax,%ebx
4190d1  pop  %ebx
4190d2  ret
```

Retail's only caller is `0x417AE5` inside `asm_FUN_00417870_00417870`
(`src/game/stage_entry.cpp`), one link of a chain of create-and-test calls:
`call 0x422360; test %eax,%eax; je ...; call 0x419090; test %eax,%eax; je 0x417b3c`.
That function pushes EBX, EBP, ESI and EDI at `0x417870` and pops them at
`0x417C5B`, and all four are live across `0x00419090` (`%esp`-relative EBP frame,
EBX/ESI/EDI used throughout the body), while **no** argument register is set for
the call and ECX/EDX are dead behind it, so the region's own ABI is plain: no
arguments, result in EAX, EBX/EBP/ESI/EDI preserved.

The emitted bodies keep that contract. Both the 69-byte and the 67-byte shape
push and pop exactly one callee-saved register (EBX in retail, ESI in ours),
never touch EBX (in the ESI shape), EBP or EDI, and clobber only EAX, ECX and
EDX, all dead at `0x417AE5`. So the region is call-site compatible and the
residual is *inside* the region: the block's register for `0x00418D40`, and
which callee-saved register carries the manager to `0x00418E30`.

The callees' conventions, read off their bodies:

| callee | convention |
| --- | --- |
| `0x00418D40` | **block in EDX**, `ECX` untouched and dead (`mov %edx,%edi; rep stosd`), block returned in EAX, plain `ret` |
| `0x00418E30` | **manager in EBX** (`mov %esi,0x8(%ebx)`, `mov %esi,0xc(%ebx)`, `movl $0,0x10(%ebx)`, `push %ebx` twice, EBX never saved), status in EAX, no arguments |
| `0x00418EE0` | `__stdcall` (`ret $0x4`), manager at `[esp+8]` after its dummy `push %ecx` |
| `0x00452493` | `__cdecl`, one stack argument (`push $1; push 0x8(%esp); call 0x4526da; pop ecx; pop ecx; ret`) |
| `0x004524A1` | five-byte `jmp 0x452422`, `__cdecl` (caller cleans) |

`0x00418D40` and `0x00418E30` have exactly **one** caller each — this region — and
neither is reached from anywhere else in the image.

## Closest shape (exactly 67 bytes, 10 differing bytes)

Model `src/game/recovery_create_resource_state_00419090.cpp` (sha256
`9b8e8a2906dbb123b2db06a068ead33237eb9dd1aa1b818960cd0436da121246`):

```cpp
// 0x00419090..0x004190D2 (67 bytes): create the stage-tip manager.
//
// Retail allocates the manager's 0x1A8 bytes, hands the fresh block to the
// construct at 0x00418D40, brings the manager's scheduler callbacks up, and
// returns the manager; when that bring-up reports failure it tears the manager
// down again and returns null instead.
//
// 0x00418D40 reads the fresh block in EDX with nothing in ECX and 0x00418E30
// reads the manager in EBX.  Neither is a convention a declaration can name, so
// the two call sites below are what this attempt measures.

struct StageTipBucket_00419090 {
    void* head;                              // +0x00
    unsigned char reserved_004[8];
};

struct StageTipManager_00419090 {
    unsigned flags;                          // +0x000
    unsigned char reserved_004[0x18 - 0x04];
    StageTipBucket_00419090 buckets[16];     // +0x018: the two eight-way arrays
    unsigned char reserved_0D8[0x1A8 - 0xD8];
};

extern "C" void* __cdecl alloc_00452493(unsigned size);                       // 0x00452493
extern "C" void* __fastcall construct_00418d40(void* block);                 // 0x00418D40
extern "C" int __cdecl initialize_00418e30();                                 // 0x00418E30
extern "C" int __stdcall teardown_00418ee0(void* manager);                    // 0x00418EE0
extern "C" void __cdecl release_004524a1(void* block);                        // 0x004524A1

#pragma code_seg(".text$01accessor")
extern "C" __declspec(noinline) StageTipManager_00419090* __cdecl
CreateStageTipManager_00419090() {
    void* block = alloc_00452493(sizeof(StageTipManager_00419090));
    StageTipManager_00419090* manager;
    if (block)
        manager = (StageTipManager_00419090*)construct_00418d40(block);
    else
        manager = 0;
    if (initialize_00418e30()) {
        if (manager) {
            teardown_00418ee0(manager);
            release_004524a1(manager);
        }
        return 0;
    }
    return manager;
}
#pragma code_seg()
```

It emits, at the full retail extent:

```
419090  push %esi                          ; retail: push %ebx
419091  push $0x1a8                        ; ---------------------------------
419096  call 0x452493                      ; identical from here to 0x4190a2
41909b  add  $0x4,%esp
41909e  test %eax,%eax
4190a0  je   4190ad
4190a2  mov  %eax,%ecx                     ; retail: mov %eax,%edx
4190a4  call 0x418d40
4190a9  mov  %eax,%esi                     ; retail: mov %eax,%ebx
4190ab  jmp  4190af
4190ad  xor  %esi,%esi
4190af  call 0x418e30
4190b4  test %eax,%eax                     ; the whole tail is retail with ESI
4190b6  je   4190cf                        ; where retail has EBX
4190b8  test %esi,%esi
4190ba  je   4190cb
4190bc  push %esi
4190bd  call 0x418ee0
4190c2  push %esi
4190c3  call 0x4524a1
4190c8  add  $0x4,%esp
4190cb  xor  %eax,%eax
4190cd  pop  %esi
4190ce  ret
4190cf  mov  %esi,%eax
4190d1  pop  %esi
4190d2  ret
```

Instruction-for-instruction this is retail with **exactly one** difference — the
instruction at `0x4190A2` is `mov %eax,%ecx` where retail has `mov %eax,%edx` —
plus the manager's home register ESI standing in for EBX. Register-normalised
(`%esi`→`%ebx`) the compiled sequence has 27 instructions and retail has 27, and
the only mismatching row is `mov %eax,%ecx` vs `mov %eax,%edx`. The 10 differing
bytes are the nine ESI encodings at `+0x00` (`push %esi`), `+0x1a`, `+0x1e`,
`+0x29`, `+0x2c`, `+0x32`, `+0x3d`, `+0x40`, `+0x41`, plus the receiver byte at
`+0x13` (`c8` for ECX, retail's `d0` for EDX).

Probe, through the cluster path (layout below is registered in the throwaway
copy, so the probe builds the cluster and compares its `bodies.obj`):

```
$ python3 matching2/tools/matching/probe.py \
      --source src/game/recovery_create_resource_state_00419090.cpp \
      --project /tmp/CreateResourceState/msvc --output /tmp/CreateResourceState/probe --show 24
0x00419090      67 bytes  _CreateStageTipManager_00419090  DIFFERENT
  first difference at 0x00419090
  expected: 53 68 a8 01 00 00 e8 f8 93 03 00 83 c4 04 85 c0 74 0b 8b d0 e8 97 fc ff
  actual:   56 68 a8 01 00 00 e8 f8 93 03 00 83 c4 04 85 c0 74 0b 8b c8 e8 97 fc ff
NOT EXACT
```

`--json` reports `"size": 67, "different_bytes": 10, "first_difference": 0x00419090`
with `expected_instruction 0x00419090: 53 push ebx` /
`actual_instruction 0x00419090: 56 push esi`.

### The semantically explicit variant instead costs two bytes

Writing the construct's unused leading `__fastcall` slot explicitly —
`extern "C" void* __fastcall construct_00418d40(unsigned zero, void* block);`
(sha256 `f0a0a9288edb8a4dd0124b7db96e491ed35712cab80a0e14c6fa83827baae327`), so
that the block really is in EDX — emits **69 bytes**:

```
4190a2  mov  %eax,%edx      ; retail's instruction, in retail's place
4190a4  xor  %ecx,%ecx      ; 2 bytes retail does not have
4190a6  call 0x418d40
```

Everything after `0x4190A6` is retail shifted by two; 48 byte positions differ
only because of that shift. Removing the `xor %ecx,%ecx` and renaming ESI→EBX
makes the sequence **instruction-identical to retail** (27 rows, no mismatch) —
so the whole residual is that one insertion plus the home register. The layout
would have to declare `size: 69`, which `register_cluster.py` refuses (the
manifest region is 67), i.e. this shape is also not landable.

## Why both registers are unreachable

All three experiments below used the project's toolkit with the project's flags
plus `/GL` and a `/LTCG` link, in isolation, outside the cluster machinery.

1. **A callee with an analysable body gets the retail shape and no `ECX` setup.**
   `static void* __fastcall Construct(int unused, void* mem)` with a C body under
   the same `/GL`+`/LTCG` link produces the callee as
   `push %edi; xor %eax,%eax; mov $0x6a,%ecx; mov %edx,%edi; rep stosd` — the
   receiver in **EDX**, exactly retail's prologue — and the caller emits
   `mov %eax,%edx; jmp 0x401010` with **no `xor %ecx,%ecx`**: the LTCG pass
   eliminated the unused first argument.
2. **A callee whose body is naked assembly keeps its declared convention.**
   The same declaration and the same caller, but with the callee's body written
   as `__declspec(naked)` inline assembly using EDX, emit
   `mov %eax,%edx; xor %ecx,%ecx; jmp 0x401010`. The unused argument is *not*
   eliminated, because the LTCG pass cannot see the body's register usage. The
   maintained `0x00418D40` and `0x00418E30` are exactly this case: naked assembly
   regions with declared signatures (`void __cdecl ...()`) bound absolutely.
3. **The caller's home register follows the callee's receiver register.** With
   `initialize` co-compiled as an analysable `static int initialize(M*)`, the
   caller keeps the manager in **ESI** and copies it into whatever register the
   pass chose for the receiver (`mov %esi,%ecx; call 0x401030` in one build,
   `mov %esi,%edx; call 0x401050` in another with a heavier callee). Retail has
   no such copy because its callee's receiver is **EBX** and the value is also
   live after the call, so one register serves both. The EBX home is therefore
   not a free choice of the source shape — it is the cross-function allocation
   that only exists when the callee's body is in the same `/LTCG` link.

This is lesson 12 with a second half: `0x00418E30`'s EBX receiver is a register
no MSVC convention assigns, and `0x00418D40`'s EDX receiver is only reachable by
occupying the `ECX` slot, which retail did not have to do because the pass knew
the slot was dead. Binding either callee opaquely keeps its declared convention,
so every shape misses.

## Shapes tried (all through `cluster_attempt`, throwaway copy)

| shape | construct declaration | bring-up declaration | extent | differing bytes vs 67 |
| --- | --- | --- | ---: | ---: |
| v1 | `__fastcall(unsigned, void*)`, `manager = 0; if (block) …` | niladic | 67 | 24 |
| v2 | `__fastcall(unsigned, void*)`, `if/else` | niladic | **69** | 48 (2-byte insertion) |
| v5 | `__fastcall(void*)` | niladic | **67** | **10** |
| v6 | `__fastcall(unsigned, void*)` | member `manager->Initialize_00418e30()` | 71 | 46 |
| v7 | `__fastcall(unsigned, void*)` | `__cdecl(void* manager)` on the stack | 73 | 48 |

The `if/else` source shape of v2 is the one retail compiled: it reproduces
retail's `test %eax,%eax; je; mov %eax,%edx; call; mov %ebx,%eax; jmp; xor %ebx,%ebx`
branch layout exactly, while the `manager = 0; if (block)` form (v1) folds the
zero into a hoisted `xor` and drops the `jmp` (net zero bytes, 24 differing
bytes). v6 and v7 show that handing the manager over explicitly costs
`mov %ecx,%ebx` (+2) or `push`/`add $4,%esp` (+4) and still keeps the home in
ESI. No source shape changed the home register away from ESI.

The `__stdcall` teardown and the two `__cdecl` calls (`0x00418EE0`, `0x004524A1`,
`0x00452493`) are exact in every variant above, including the missing `add $0x4,%esp`
after `0x00418EE0` that its `ret $0x4` accounts for.

## Layout, driver and registration state

Layout `layout/ltcg/recovery_create_resource_state_00419090.json` (sha256
`c65c2a1025dee1585aafbcb4169a00f4fcd981cc0107e909ae41d21624ee5f51`) — the one the
probe above consumed, with the 67-byte shape and the emitted context size 45:

```json
{
  "schema_version": 1,
  "name": "recovery_create_resource_state_00419090",
  "source": "src/game/recovery_create_resource_state_00419090.cpp",
  "driver": "layout/ltcg/recovery_create_resource_state_00419090_context.cpp",
  "headers": [],
  "image_base": "0x00400000",
  "description": "Stage-tip manager creation compiled with native LTCG.",
  "functions": [
    {
      "name": "CreateStageTipManager",
      "symbol": "_CreateStageTipManager_00419090",
      "section": ".text$01accessor",
      "address": "0x00419090",
      "size": 67,
      "actual_abi": "no arguments; manager returned in EAX"
    }
  ],
  "context": {
    "symbol": "?RecoveryCreateResourceStateCompilerContext@@YGHPAPAUStageTipManager_00419090@@H@Z",
    "section": ".text$03context",
    "address": "0x004190F0",
    "size": 45,
    "description": "Synthetic array-walking caller; not recovered game code."
  },
  "gaps": [
    {"section": ".text$00layout", "address": "0x00401000", "size": 98448},
    {"section": ".text$02layout", "address": "0x004190D3", "size": 29}
  ],
  "constants": [],
  "roots": [],
  "absolute_symbols": [
    {"symbol": "_alloc_00452493", "address": "0x00452493", "kind": "relative_code"},
    {"symbol": "_initialize_00418e30", "address": "0x00418E30", "kind": "relative_code"},
    {"symbol": "_teardown_00418ee0@4", "address": "0x00418EE0", "kind": "relative_code"},
    {"symbol": "_release_004524a1", "address": "0x004524A1", "kind": "relative_code"},
    {"symbol": "@construct_00418d40@4", "address": "0x00418D40", "kind": "relative_code"}
  ]
}
```

Driver `layout/ltcg/recovery_create_resource_state_00419090_context.cpp`
(sha256 `15c68943ea041cc53a6b1f123161b846ccc8691cb804d94e11070ed57e8d8487`); the
decorated context symbol was verified from an actual object, and the emitted
context is 45 bytes at `0x004190F0`:

```cpp
// Compiler context only; never selected as recovered game code.
#include "../../src/game/recovery_create_resource_state_00419090.cpp"

#pragma code_seg(".text$03context")
int __stdcall RecoveryCreateResourceStateCompilerContext(
        StageTipManager_00419090** slots, int count) {
    int created = 0;
    while (count--)
        if ((*slots++ = CreateStageTipManager_00419090()) != 0)
            ++created;
    return created;
}
#pragma code_seg()
```

The manifest state summarised here is the **throwaway copy's**; the maintained
`regions.json` keeps the region as `asm_Recovery_CreateResourceState_00419090`
with `_asm_Recovery_CreateResourceState_00419090`, unchanged. No maintained
source, layout or cluster list was modified by this attempt.

## Next attempt

This region should be retried **after** `0x00418D40` and `0x00418E30` are
recovered, following the merge pattern of lesson 5: the three sources
(`stage_tip_manager.cpp`, `stage_tip_runtime_initialize_retail_00418e30.cpp`
and this one) are one translation unit in retail, so one cluster should compile
their models together and this region's source becomes an `additional_sources`
entry of that cluster whose driver calls this entry point. With both callees'
bodies analysable in the same `/GL` link, the pass should put the block in EDX
with no `ECX` setup and keep the manager in EBX across the bare bring-up call —
experiment 1 shows the argument elimination happens on its own, experiment 3
shows the home register then follows.

Two routes are *not* available and were checked:

* a declaration that puts an argument in EBX does not exist, so binding either
  callee opaquely cannot be made to work;
* an "anchor" body for a callee that is not a recovered region is what lesson 10
  forbids, and it is also insufficient here: a schema-1 cluster has a single
  context slot, so at most one of the two agreements could be taught, and the
  remaining one still misses.

`0x00418D40`'s own model note (`stage_tip_manager_construct_00418d40_model.md`,
2026-09-16) records 237 bytes with 69 differing bytes; `0x00418E30` has no model
note yet.
