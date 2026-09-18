# 0x004477D0 `AnimationManager_ClearResourceSlot` — model exact, one loader allowance short

2026-09-19. Region 55 bytes, `src/render/animation_manager_clear_resource_slot_004477d0.cpp`.
Status: **not registered**, because the native-LTCG cluster that reproduces it needs a
scaffolding function the cluster loader refuses. The emitted region is nonetheless
**byte-identical to retail (55/55, 0 differing bytes)**; with a two-line loader allowance the
maintained probe reports `EXACT` (evidence below).

## What the region is

```
004477d0  85 f6                 test  esi,esi
004477d2  7c 32                 jl    00447806
004477d4  83 fe 21              cmp   esi,0x21
004477d7  73 2d                 jae   00447806
004477d9  57                    push  edi
004477da  8b bc b3 6c d0 3a 00  mov   edi,[ebx+esi*4+0x3ad06c]
004477e1  85 ff                 test  edi,edi
004477e3  74 20                 je    00447805
004477e5  e8 26 00 00 00        call  00447810
004477ea  8b 84 b3 6c d0 3a 00  mov   eax,[ebx+esi*4+0x3ad06c]
004477f1  50                    push  eax
004477f2  e8 aa ac 00 00        call  004524a1            ; free
004477f7  83 c4 04              add   esp,4
004477fa  c7 84 b3 6c d0 3a 00 00 00 00 00  mov [ebx+esi*4+0x3ad06c],0
00447805  5f                    pop   edi
00447806  c3                    ret
```

Retail's entry convention is manager in **EBX**, slot index in **ESI**, and the release routine
`0x00447810` receives the record pointer in **EDI** (its body reads `[edi+0x108]` before writing
anything; all 24 call sites of `0x00447810` set EDI). None of the three is expressible as a
declaration, so the region is a native-LTCG cluster.

## Recovered source (`src/render/animation_manager_clear_resource_slot_004477d0.cpp`)

```cpp
// 0x004477D0..0x00447806: release and null one animation-manager resource slot.
//
// Retail enters with the manager in EBX and the slot index in ESI, and hands the
// record pointer to the manager's release routine at 0x00447810 in EDI:
// conventions only a native /LTCG link of this source chooses.  They come from
// layout/ltcg/clear_resource_slot_004477d0.json - its synthetic context keeps
// the manager and the index in those registers, and its scaffolding body for
// 0x00447810 fixes the EDI argument.  No scaffolding byte is recovered code.

struct AnimationResource_004477d0;

extern "C" void __cdecl entry_free_004524a1(void* memory);

// 0x00447810.  Its register convention is not expressible as a declaration, so
// the call resolves through the layout's scaffolding body for it.
extern "C" void __cdecl asm_FUN_00447810_00447810(AnimationResource_004477d0* resource);

struct AnimationManager_004477d0 {
    unsigned char pad_000[0x3AD06C];
    AnimationResource_004477d0* slots_3ad06c[0x21];   // +0x3AD06C

    __declspec(noinline) void ClearResourceSlot(int index);
};

#pragma code_seg(".text$01clear")
void AnimationManager_004477d0::ClearResourceSlot(int index) {
    if (index < 0)
        return;
    if ((unsigned)index >= 0x21u)
        return;
    if (slots_3ad06c[index] == 0)
        return;
    asm_FUN_00447810_00447810(slots_3ad06c[index]);
    entry_free_004524a1(slots_3ad06c[index]);
    slots_3ad06c[index] = 0;
}
#pragma code_seg()
```

`if (index < 0)` then `if ((unsigned)index >= 0x21u)` are two separate tests because retail has
both (`jl` *and* `jae`); a merged `(unsigned)index >= 0x21u` produces a single `jae` and one byte
fewer. `slots_3ad06c[index]` is written out again for the free and the store: retail reloads
`[ebx+esi*4+0x3ad06c]` after the release call instead of keeping the pointer live.

## Driver (`layout/ltcg/clear_resource_slot_004477d0_context.cpp`)

```cpp
// Compiler context only; never selected as recovered game code.
#include "../../src/render/animation_manager_clear_resource_slot_004477d0.cpp"

extern "C" void* data_00491c10;

// Scaffolding body for 0x00447810.  The record pointer stays live across the
// entry frees, which is what makes the whole-program pass hand it a callee-saved
// argument register (EDI in retail); these bytes are never selected.
#pragma code_seg(".text$02callee")
extern "C" __declspec(noinline) void __cdecl asm_FUN_00447810_00447810(AnimationResource_004477d0* resource) {
    unsigned char* bytes = (unsigned char*)resource;
    int count = *(int*)(bytes + 0x10c);
    unsigned char* cursor = *(unsigned char**)(bytes + 0x120);
    for (int i = 0; i < count; ++i) {
        entry_free_004524a1(*(void**)(cursor + 4));
        *(void**)(cursor + 4) = 0;
        cursor += 0x10;
    }
    entry_free_004524a1(cursor);
    *(void**)(bytes + 0x120) = 0;
    entry_free_004524a1(*(void**)(bytes + 0x108));
    *(void**)(bytes + 0x108) = 0;
}
#pragma code_seg()

// Synthetic caller: it keeps the manager in EBX and the slot index in ESI across
// the call, which is this region's retail entry convention.
#pragma code_seg(".text$03context")
int __stdcall ClearResourceSlotCompilerContext(int first, int count) {
    AnimationManager_004477d0* manager =
        (AnimationManager_004477d0*)data_00491c10;
    int index = first;
    while (count--) {
        manager->ClearResourceSlot(index);
        index++;
    }
    return index;
}
#pragma code_seg()
```

## Layout (`layout/ltcg/clear_resource_slot_004477d0.json`)

```json
{
  "schema_version": 1,
  "name": "clear_resource_slot_004477d0",
  "source": "src/render/animation_manager_clear_resource_slot_004477d0.cpp",
  "driver": "layout/ltcg/clear_resource_slot_004477d0_context.cpp",
  "headers": [],
  "image_base": "0x00400000",
  "description": "AnimationManager_ClearResourceSlot compiled with native LTCG so the manager arrives in EBX, the index in ESI and the release call in EDI.",
  "functions": [
    {
      "name": "AnimationManager_ClearResourceSlot",
      "symbol": "?ClearResourceSlot@AnimationManager_004477d0@@QAEXH@Z",
      "section": ".text$01clear",
      "address": "0x004477D0",
      "size": 55,
      "actual_abi": "manager in EBX; index in ESI; plain RET"
    }
  ],
  "context": {
    "symbol": "?ClearResourceSlotCompilerContext@@YGHHH@Z",
    "section": ".text$03context",
    "address": "0x00447870",
    "size": 38,
    "description": "Synthetic caller that keeps the manager in EBX and the index in ESI; not recovered game code."
  },
  "gaps": [
    {
      "section": ".text$00layout",
      "address": "0x00401000",
      "size": 288720
    },
    {
      "section": ".text$01zlayout",
      "address": "0x00447807",
      "size": 9
    }
  ],
  "constants": [],
  "roots": [],
  "absolute_symbols": [
    {
      "symbol": "_data_00491c10",
      "address": "0x00491C10",
      "kind": "data"
    },
    {
      "symbol": "_entry_free_004524a1",
      "address": "0x004524A1",
      "kind": "relative_code"
    }
  ],
  "scaffolding": [
    "_asm_FUN_00447810_00447810"
  ]
}
```

The nine-byte `.text$01zlayout` gap is what puts `.text$02callee` at exactly `0x00447810`, so the
selected body's `call` bakes the retail displacement `0x26`. The scaffolding body is emitted but
never selected: `export_bodies` writes only the functions in `functions`, so the only bytes this
cluster contributes to the image are the region's 55.

## Measured result

Build (native /LTCG, wine MSVC 13.10.6030), region bytes read out of the link's PE:

```
got    85f67c3283fe21732d578bbcb36cd03a0085ff7420e8260000008b84b36cd03a0050e8aaac000083c404
       c784b36cd03a00000000005fc3
retail 85f67c3283fe21732d578bbcb36cd03a0085ff7420e8260000008b84b36cd03a0050e8aaac000083c404
       c784b36cd03a00000000005fc3
region bytes equal: True (55 bytes)
```

The only failure of that build is `validate_native_output`'s
`native compiler emitted an undeclared function`, because the scaffolding body's symbol
(`_asm_FUN_00447810_00447810`) is not one of the symbols the loader expects.

With a scratch copy of the tools whose loader admits the layout's declared `scaffolding` symbols
(`allowed |= {'scaffolding'}`; `declared |= set(spec.get('scaffolding', []))`), the maintained
probe command reports

```
$ python3 <scratch-tools>/matching2/tools/matching/probe.py \
      --source src/render/animation_manager_clear_resource_slot_004477d0.cpp \
      --project /tmp/ClearResourceSlot/msvc --output /tmp/ClearResourceSlot/out --show 30
0x004477d0      55 bytes  ?ClearResourceSlot@AnimationManager_004477d0@@QAEXH@Z  EXACT

EXACT
```

## Why the loader has to change

A region whose callee takes an argument in a register no declaration names (`EDI` here) can only
get that convention from a callee whose IL is in the same /LTCG link. Every function in that link
is fenced by `validate_native_output`:

```python
declared = {item['symbol'] for item in spec['functions']}
if spec['context']:
    context_symbol = spec['context']['symbol']
    declared |= {context_symbol, '_' + context_symbol}
```

so a cluster may contain exactly one scaffolding function beyond the region: the compiler context.
A second one is needed here, because the context must be the link entry, and LINK's `/ENTRY:C`
prefixes `_` unless `C` is already decorated (`?`-mangled), while the loader's own context lookup
prefers a symbol named exactly `C`:

* context symbol mangled (`?…@@…`, what the landed clusters use): `/ENTRY` and the lookup both
  resolve the context, but the only other admitted name is `_?…@@…`, which no declaration emits;
* context symbol a C name: the anchor would have to be named with the bare undecorated spelling
  (the `_`-form is the context itself), which no declaration emits either.

Both spellings were built and measured (see *shapes tried*); with the merged variant, where the
scaffolding body *is* the entry and therefore needs no second name, the entry's convention is
pinned to its declaration — measured `__cdecl` → argument pushed, `__stdcall` → argument pushed,
`__fastcall` → argument in ECX — so EDI is unreachable that way.

Recommended allowance (schema 1, validating rather than name-fenced):

```json
"anchors": [
  {"name": "asm_FUN_00447810_00447810",
   "symbol": "_asm_FUN_00447810_00447810",
   "section": ".text$02callee",
   "address": "0x00447810",
   "size": 81}
]
```

`load_cluster` admits the field, requires each anchor's section to be distinct from the selected
functions and the context, and `validate_native_output` requires the symbol to appear exactly once
at the declared address with the declared contribution length, then adds it to `declared`. That
keeps the check's purpose (no *undeclared* code) while allowing a declared ABI anchor whose bytes
are never exported.

## Shapes tried

| shape | emitted | first delta |
| --- | --- | --- |
| plain semantic TU (no cluster) | — | no prototype puts `this` in EBX |
| external callee, default (`__stdcall`) | 54 | `mov eax,[ebx+esi*4+0x3ad06c]`, `push eax; call` instead of EDI |
| external callee, `__cdecl` | 54 | as above plus `add esp,8` |
| external callee, `__fastcall` | 53 | `mov ecx,[…]` — the declared convention is never re-assigned for an external symbol |
| scaffolding callee + pointer-walking context (`*indices++`) | 55 | index in EDI, release argument in ESI (roles swapped, 17 bytes differ) |
| scaffolding callee + counter context (`index = first; …; index++`) | **55** | none — byte-identical |
| scaffolding callee bodies: two frees / four frees | 55 | argument still ESI; the parameter must stay live across a *loop* to earn EDI |
| scaffolding callee merged with the context (one symbol) | 55 | argument pushed / in ECX; the entry's convention is pinned |
| context with a third live value across the call | 55 | manager no longer in EBX |

## Reproduction

`/tmp/ClearResourceSlot/{verify.py,final/}` holds the source, driver, layout and the driver script
(`python3 verify.py` builds and prints the byte comparison; `python3 verify.py --patched` copies the
tools to `/tmp/ClearResourceSlot/tools`, adds the two-line allowance, registers the cluster in the
scratch manifest and runs the probe). The maintained tree was not modified.
