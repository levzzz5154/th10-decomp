# 0x0040D6B0 `EnemyManager_CreateRetail` — wave 5: model complete, NOT landed

2026-09-19. Region `0x0040D6B0..0x0040D70E` (95 bytes). The C++ model below
reproduces the complete retail body *extent* (95 bytes, every branch
displacement, both `ret 4`) and differs from retail in **9 bytes, all of them
register identities**: retail keeps the freshly allocated manager in **EBX**
and hands it to `0x0040D530` in **EAX**; the compiled model keeps it in **ESI**
and hands it over in **ECX**. Nothing was registered; `regions.json`, the
region's source and the maintained tree are untouched.

## Disposition

| | |
|---|---|
| emitted extent | **95 bytes** (declared 95 — the cluster validates on extent) |
| emitted body | sha256 `163dc0079f3c1a5c4a27e2d09d533ec2834f438b9c08ea6f115b853c6e46598e` (retail `17c08edb9514ca78f1da0aa8c2fd0565f0db2f0a631738f35bc9e0d93c645103`) |
| differing bytes | **9** |
| probe | `DIFFERENT`, first difference `0x0040D6B0` expected `53 push ebx`, actual `56 push esi` |
| blocker | retail's private calling convention of the two **opaque** callees `0x0040D280` (object in EBX) and `0x0040D530` (object in EAX) |
| path needed to land | model `0x0040D280` and `0x0040D530` in the same `/LTCG` scope (see *Next dependency*) |

## What the region does

`EnemyManager_CreateRetail(int script_name)`: allocate `0x68` bytes through
`operator new` (`0x00452493`), clear bit 0 of the header word at `+0x50` before
the block is zeroed, zero all `0x1A` dwords, raise bit 1 of `+0x00`, publish the
manager through the global at `0x00477704`, then run the script initialiser
`0x0040D280` with the script name. When that fails, tear the half-built manager
down through `0x0040D530` and `free` (`0x004524A1`) and report NULL; otherwise
report the manager. The legacy reconstruction
(`reference/legacy_semantic/src/game/manager_factories.cpp:140`,
`EnemyManager_Create`) gives the same behaviour; it omits the `+0x50` clear and
parameterises the hooks.

## Retail body (oracle)

```asm
0040d6b0  push ebx
0040d6b1  push 68h
0040d6b3  call 0x452493            ; operator new(0x68)
0040d6b8  mov  edx,eax
0040d6ba  add  esp,4
0040d6bd  test edx,edx
0040d6bf  je   0x40d6df
0040d6c1  and  dword ptr [edx+50h],0FFFFFFFEh
0040d6c5  push edi
0040d6c6  xor  eax,eax
0040d6c8  mov  ecx,1Ah
0040d6cd  mov  edi,edx
0040d6cf  rep stos dword ptr es:[edi]
0040d6d1  or   dword ptr [edx],2
0040d6d4  mov  dword ptr ds:477704h,edx
0040d6da  mov  ebx,edx
0040d6dc  pop  edi
0040d6dd  jmp  0x40d6e1
0040d6df  xor  ebx,ebx
0040d6e1  mov  eax,dword ptr [esp+8]     ; script_name
0040d6e5  push eax
0040d6e6  call 0x40d280                  ; object in EBX, script name on the stack
0040d6eb  test eax,eax
0040d6ed  je   0x40d709
0040d6ef  test ebx,ebx
0040d6f1  je   0x40d703
0040d6f3  mov  eax,ebx                   ; object in EAX for 0x40D530
0040d6f5  call 0x40d530
0040d6fa  push ebx
0040d6fb  call 0x4524A1                  ; free(manager)
0040d700  add  esp,4
0040d703  xor  eax,eax
0040d705  pop  ebx
0040d706  ret  4
0040d709  mov  eax,ebx
0040d70b  pop  ebx
0040d70c  ret  4
```

Entry ABI: one stack argument, `RET 4`, result in EAX, no live-ins. Only two
callers exist in the image, both `push <arg>` / `call` / use EAX:
`0x0040A377` (region `0x0040A1A0`, holds its stage context in **ESI** and uses
**EDI** after the call) and `0x00417B33` (region `0x00417C80`, holds its state
in **EBP**). Neither needs a register input, and both are preserved by any of
the shapes below.

## The model (closest variant, 95 bytes / 9 differing)

```cpp
// 0x0040D6B0..0x0040D70E: EnemyManager_CreateRetail
#include <string.h>

void *__cdecl operator new(unsigned int size);

struct EnemyManager_0040d6b0 {
    unsigned int flags_000;             // +0x00, bit 1 = published
    unsigned char pad_004[0x4C];
    unsigned int flags_050;             // +0x50
    unsigned char pad_054[0x14];
};

extern "C" void *data_00477704;
extern "C" int __stdcall FUN_0040d280_0040d280(int script_name);
extern "C" void __fastcall FUN_0040d530_0040d530(EnemyManager_0040d6b0 *manager);
extern "C" void __cdecl entry_free_004524a1(void *memory);

#pragma code_seg(".text$01create")
extern "C" __declspec(noinline) EnemyManager_0040d6b0 *__stdcall
EnemyManager_CreateRetail_0040d6b0(int script_name) {
    EnemyManager_0040d6b0 *fresh = new EnemyManager_0040d6b0;
    EnemyManager_0040d6b0 *manager;
    if (fresh) {
        unsigned int *owned = (unsigned int *)((char *)fresh + 0x50);
        *owned &= ~1u;
        memset(fresh, 0, sizeof(EnemyManager_0040d6b0));
        fresh->flags_000 |= 2u;
        data_00477704 = fresh;
        manager = fresh;
    } else {
        manager = 0;
    }
    if (FUN_0040d280_0040d280(script_name) != 0) {
        if (manager) {
            FUN_0040d530_0040d530(manager);
            entry_free_004524a1(manager);
        }
        return 0;
    }
    return manager;
}
#pragma code_seg()
```

Layout (`layout/ltcg/enemy_manager_create_0040d6b0.json`, **not registered**;
context address/size are the emitted ones):

```json
{
  "schema_version": 1,
  "name": "enemy_manager_create_0040d6b0",
  "source": "src/game/enemy_manager_create_retail_0040d6b0.cpp",
  "driver": "layout/ltcg/enemy_manager_create_0040d6b0_context.cpp",
  "headers": [],
  "image_base": "0x00400000",
  "description": "EnemyManager factory compiled with native LTCG.",
  "functions": [
    {
      "name": "EnemyManager_CreateRetail_0040d6b0",
      "symbol": "_EnemyManager_CreateRetail_0040d6b0@4",
      "section": ".text$01create",
      "address": "0x0040D6B0",
      "size": 95,
      "actual_abi": "script name on the stack; RET 4; result in EAX"
    }
  ],
  "context": {
    "symbol": "?EnemyManagerCreateCompilerContext@@YGHPAPAUEnemyManager_0040d6b0@@HH@Z",
    "section": ".text$03context",
    "address": "0x0040D720",
    "size": 46,
    "description": "synthetic caller; not recovered game code"
  },
  "gaps": [
    {"section": ".text$00layout", "address": "0x00401000", "size": 50864},
    {"section": ".text$02layout", "address": "0x0040D70F", "size": 17}
  ],
  "constants": [],
  "roots": [],
  "absolute_symbols": [
    {"symbol": "??2@YAPAXI@Z", "address": "0x00452493", "kind": "relative_code"},
    {"symbol": "_entry_free_004524a1", "address": "0x004524A1", "kind": "relative_code"},
    {"symbol": "_data_00477704", "address": "0x00477704", "kind": "data"},
    {"symbol": "_FUN_0040d280_0040d280@4", "address": "0x0040D280", "kind": "relative_code"},
    {"symbol": "@FUN_0040d530_0040d530@4", "address": "0x0040D530", "kind": "relative_code"}
  ]
}
```

Driver (`layout/ltcg/enemy_manager_create_0040d6b0_context.cpp`):

```cpp
// Compiler context only; never selected as recovered game code.
#include "../../src/game/enemy_manager_create_retail_0040d6b0.cpp"

#pragma code_seg(".text$03context")
int __stdcall EnemyManagerCreateCompilerContext(EnemyManager_0040d6b0 **slots, int count,
                                                int script_name) {
    for (int index = 0; index < count; ++index) {
        slots[index] = EnemyManager_CreateRetail_0040d6b0(script_name);
    }
    return 0;
}
#pragma code_seg()
```

## Instruction-level delta (emitted vs retail, same 95 bytes)

```
+0x00 0040D6B0  56           push esi          | 53            push ebx
+0x2B 0040D6DB  f2           mov esi,edx       | da            mov ebx,edx
+0x30 0040D6E0  f6           xor esi,esi       | db            xor ebx,ebx
+0x40 0040D6F0  f6           test esi,esi      | db            test ebx,ebx
+0x44 0040D6F4  ce           mov ecx,esi       | c3            mov eax,ebx
+0x4A 0040D6FA  56           push esi          | 53            push ebx
+0x55 0040D705  5e           pop esi           | 5b            pop ebx
+0x5A 0040D70A  c6           mov eax,esi       | c3            mov eax,ebx
+0x5B 0040D70B  5e           pop esi           | 5b            pop ebx
```

Everything else is byte-identical: the `push 68h` / `call operator new` /
`add esp,4` sequence, the `and dword [edx+50h]`, the `rep stosd` zeroing
(`mov ecx,1Ah`), `or [edx],2`, the `mov ds:477704h,edx` absolute store, the
stack reload of the script name, the `call 0x40D530` and `call 0x4524A1`
displacements, every conditional branch displacement, and both `ret 4`.

## Why it is 9 bytes rather than 0

Retail's two callees receive their subject in a register that no C++
declaration can name:

* `0x0040D280` (334 bytes, source `src/game/message_host_init.cpp`) reads its
  manager from **EBX** (`mov [ebx+30h],ecx`, `mov [ebx+54h],ecx`) and takes the
  script name on the stack. That is why my function's local lives in EBX in
  retail: the whole-program pass propagated the callee's receiver register into
  its only caller.
* `0x0040D530` (300 bytes, source `src/game/fun_0040d530_0040d530.cpp`) reads its
  object from **EAX** (`mov edi,eax` in its prologue). All five callers
  (`0x0040A291`, `0x0040D6F5`, `0x0040D712`, `0x0040D736`, `0x00417F95`) reach it
  with `mov eax,<reg>` first; four of the five move it out of ESI and the call
  from this factory (`0x0040D6F5`) moves it out of EBX. The callers at
  `0x0040D710` and `0x0040D730` are themselves still unrecovered assembly
  regions.

In this cluster both callees are *opaque absolute bindings*, so the link must
use the declared convention at the call site and the pass has no register
demand to propagate:

* `mov eax,[esp+8] / push eax / call 0x40D280` **is** expressible — a one-stack
  argument `__stdcall` declaration, and the object is then only "incidentally"
  live across the call. That half already matches.
* `mov eax,ebx / call 0x40D530` is **not** expressible. MSVC 13.10 x86 has no
  convention that puts an argument in EAX or EBX; the toolkit accepts only
  `__cdecl`/`__stdcall`/`__fastcall`/`__thiscall` (`__regcall`, `__vectorcall`,
  `__clrcall`, `__pascal` are all rejected: `error C2182`). A lab compile of
  every candidate shape — cdecl, stdcall, fastcall with the object first and
  second, `__int64`/`double` first arguments, 4-byte and 64-byte struct by
  value, member functions returning a struct — emits `push`, `mov ecx` or
  `mov edx` for the object and never EAX or EBX. The private register only
  exists for functions the same `/LTCG` link can regenerate, which is exactly
  what `reference/whole_program_ltcg.md` records ("both sides of the private
  call must be visible to the same `/LTCG` invocation, and the callee must
  remain eligible for ABI changes").

The same applies to the home register: without a callee demanding EBX the pass
homes the cross-call pointer in ESI (8 of the 9 bytes). Letting the register
demand come from a *selected* callee is the mechanism the project already used
for `0x004055C0`/`0x004056B0` and `0x0040AE70`/`0x0040AF90`, where a modelled
callee's EBX receiver is what puts the caller's pointer in EBX.

## Shapes tried

All through the real cluster path (`build_cluster`, `/GL` objects + one `/LTCG`
link, driver compiled with `/GL`), against the oracle:

| variant | change | emitted | differing |
|---|---|---:|---:|
| **model above** | `0x40D280` `__stdcall(int)`, `0x40D530` `__fastcall(ptr)` | **95** | **9** |
| plain unit | same source probed without the cluster (`kind: semantic` region in the throwaway copy) | 95 | 9 (first `56` vs `53`) |
| `roots` | `roots: ["_EnemyManager_CreateRetail_0040d6b0@4"]` (`/INCLUDE`, keeps the declared ABI) | 95 | 9 |
| `onevar` | single local with an explicit `else manager = 0` | 95 | 9 |
| `voidarg` | `script_name` declared `void *` (and the callee likewise) | 95 | 9 |
| `early` | `manager = fresh;` before the `+0x50` clear (compiler sank it back) | 95 | 9 |
| `andfield` | `fresh->flags_050 &= ~1u;` instead of the pointer-cast local | 100 | 5 extra bytes: `mov ecx,[edx+50h] / and ecx,~1 / mov [edx+50h],ecx` instead of retail's single `and dword [edx+50h],~1` (the analogue `0x004056B0` needs the same pointer-cast idiom) |
| `s530std` | `0x40D530` `__stdcall(ptr)` | 94 | 32 (`push esi / call` instead of `mov eax,ebx / call`, rest shifted) |
| `s530none` | `0x40D530` declared with no parameter and called with none | 93 | 32 (`call 0x40D530` with no argument load) |
| `single` | one local with no `else` (no `xor` on the failure path) | 89 | 51 |
| context shapes | array-of-pointer loop (above), `__cdecl` context, struct-array loop with the script name loaded from a record, and a context that returns the created pointer — all four emit the **identical** 95-byte body (`163dc007…`): the entry convention (`RET 4`, stack argument, result in EAX) is preserved and the interior home register stays ESI |

The context is not the lever here: the modelled function's *entry* already
matches retail (`push`+`ret 4`, result in EAX, no live-ins), and the differing
registers are chosen by the pass for the function's interior, on demand from its
callees.

## Next dependency

Landing this region needs a `/LTCG` scope in which the *callees* are selected
C++ models:

1. `0x0040D280` in the same layout would both be exact itself and supply the EBX
   receiver that homes the caller's pointer in EBX.
2. `0x0040D530` must be modelled as well, and — because its EAX receiver is a
   whole-program agreement with **five** callers — the modelled body has to keep
   retail's `mov edi,eax` prologue while the callers supply EAX. That is the
   same "next dependency" the manager-teardown note recorded
   (`manager_teardown_cluster_00405f70_0040b7b0_0040d530_00424ed0_004294a0_0042cb60.md`):
   it is one cluster spanning this factory plus `0x0040A1A0`-region,
   `0x0040D710`, `0x0040D730`, `0x00417C80`-region and the two teardown bodies.

Until that exists, absorbing the two *assembly* sources as `additional_sources`
would not help. [INFERENCE — not measured in this cluster] An inline-`__asm`
body is not eligible for an ABI change, so the call sites would still be
emitted per the declared convention; that is the "callee must remain eligible"
half of the rule quoted above, and the measured contrast is the analogue
clusters, where the EBX receiver only appears once the callee is a selected
C++ model.

## Provenance

* `matching2/tools/matching/probe.py --source src/game/enemy_manager_create_retail_0040d6b0.cpp`
  on the throwaway copy → `0x0040d6b0 95 bytes DIFFERENT`, first difference
  `expected 53 6a 68 e8 db 4d 04 00…` / `actual 56 6a 68 e8 db 4d 04 00…`.
* Cluster builds: `matching2/tools/matching/ltcg_cluster.build_cluster` on
  `/tmp/EnemyManagerCreate/msvc`, contrast against
  `matching2/build/oracle/th10.exe`.
* Evidence for the missing conventions: `reference/whole_program_ltcg.md` (the
  five negative controls) plus a lab compile with the project toolkit
  (`~/.local/share/th10-toolchains/msvc-13.10.6030`), which emits only
  `push`/`mov ecx`/`mov edx` for a register argument.
* **Manifest note (lesson 11).** The maintained `regions.json` was never
  touched: the layout above was built against a throwaway copy at
  `/tmp/EnemyManagerCreate/msvc`, in which the single `0x0040D6B0` region record
  was hand-edited to `kind: semantic` with the decorated symbol
  `_EnemyManager_CreateRetail_0040d6b0@4` for the plain-unit probe. That copy's
  `translation_units` list therefore does not describe a valid project; nothing
  of it was copied back, and no layout is registered in the maintained tree.
