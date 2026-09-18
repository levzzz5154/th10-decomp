# 0x004285F0 landed as a native-LTCG cluster: `Vector2::GetBounds`

Status: **EXACT**. The 55-byte region between `EffectPool_Update` (`0x00428280`)
and the pickup sweep (`0x00428630`) is now ordinary C++ plus one cluster layout;
the focused probe reports

```
0x004285f0      55 bytes  ?GetBounds@Vector2@@QBEXPBU1@PAU1@1@Z  EXACT
```

## What the region computes

Retail, in order:

```text
D9 00        fld  dword ptr [eax]        ; size->x
D8 0D 0C0B4700  fmul dword ptr [0x470B0C] ; * 0.5f   (the shared pool copy)
D8 29        fsubr dword ptr [ecx]       ; centre.x - half
D9 1E        fstp dword ptr [esi]        ; min->x
D9 40 04     fld  dword ptr [eax+4]
D8 0D 0C0B4700  fmul dword ptr [0x470B0C]
D8 69 04     fsubr dword ptr [ecx+4]
D9 5E 04     fstp dword ptr [esi+4]      ; min->y
D9 00 / D8 0D .. / D8 01 / D9 1A         ; max->x into [edx]
D9 40 04 / D8 0D .. / D8 41 04 / D9 5A 04 ; max->y into [edx+4]
C3           ret
```

So the entry convention is `EAX` = size, `ECX` = the centred receiver,
`ESI` = minimum corner, `EDX` = maximum corner, with no frame and no other
clobber: `min = centre - size * 0.5f`, `max = centre + size * 0.5f`. The body
re-loads and re-multiplies rather than reusing the products, and only a plain
source expression reproduces that: a single `half` local or a fused
`centre ± size * 0.5f` per component gives exactly this sequence, while any
attempt to keep the product live adds or removes an `fld`.

The routine is **not referenced anywhere in the image** — no `E8/E9` rel32 and
no absolute pointer in `.text`, `.rdata` or `.data` targets `0x004285F0`, and
neither IDA nor Ghidra ever treated the address as a function entry. It is
retail code the linker kept (no dead-code elimination), which is why no caller
pins the register convention and the native-LTCG cluster is the only route that
can reproduce it [INFERENCE from the reference scans].

## Files

* `src/unidentified/unassigned_004285f0.cpp` — the model (no other region is
  owned by this source, so the cutover is complete).
* `layout/ltcg/bounds_from_center_004285f0.json` — the layout below.
* `layout/ltcg/bounds_from_center_004285f0_context.cpp` — synthetic
  array-walking caller; establishes the convention, contributes no game code.

```cpp
// 0x004285F0 - the two corners of an axis-aligned box centred on this vector,
// given the box size.  Retail's x87 body is, in order,
//
//     D9 00        fld  dword ptr [eax]        ; size->x
//     D8 0D ..     fmul dword ptr [0x470B0C]   ; * 0.5f
//     D8 29        fsubr dword ptr [ecx]       ; centre.x - half
//     D9 1E        fstp dword ptr [esi]        ; min->x
//     ...          (same for y, then the two adds into edx)
//     C3           ret
//
// The shared 0.5f pool slot at 0x470B0C is the literal every other function
// in the image uses.  The size arrives in EAX, the centred receiver in ECX,
// the minimum in ESI and the maximum in EDX, so the model is compiled as a
// native-LTCG cluster.
#pragma code_seg(".text$01bounds")
struct Vector2 {
    float x;
    float y;

    __declspec(noinline) void GetBounds(const Vector2* size, Vector2* min, Vector2* max) const;
};

void Vector2::GetBounds(const Vector2* size, Vector2* min, Vector2* max) const {
    min->x = x - size->x * 0.5f;
    min->y = y - size->y * 0.5f;
    max->x = x + size->x * 0.5f;
    max->y = y + size->y * 0.5f;
}
#pragma code_seg()
```

```cpp
// layout/ltcg/bounds_from_center_004285f0_context.cpp
// Compiler context only; never selected as recovered game code.
// The array-walking caller is what makes the whole-program pass pick the
// observed retail convention: size in EAX, the centred receiver in ECX, the
// minimum in ESI and the maximum in EDX.
#include "../../src/unidentified/unassigned_004285f0.cpp"

#pragma code_seg(".text$03context")
extern "C" __declspec(noinline) int __stdcall BoundsFromCenterCompilerContext(
        Vector2** centers, Vector2** sizes, Vector2* min, Vector2* max, int count) {
    while (count--) {
        (*centers++)->GetBounds(*sizes++, min, max);
    }
    return 0;
}
#pragma code_seg()
```

Layout (`layout/ltcg/bounds_from_center_004285f0.json`), abbreviated to the
load-bearing fields:

```json
{
  "schema_version": 1,
  "name": "bounds_from_center_004285f0",
  "source": "src/unidentified/unassigned_004285f0.cpp",
  "driver": "layout/ltcg/bounds_from_center_004285f0_context.cpp",
  "headers": [],
  "image_base": "0x00400000",
  "functions": [{"name": "Vector2_GetBounds",
                 "symbol": "?GetBounds@Vector2@@QBEXPBU1@PAU1@1@Z",
                 "section": ".text$01bounds", "address": "0x004285F0", "size": 55,
                 "actual_abi": "centred receiver in ECX; size in EAX; minimum in ESI; maximum in EDX; plain RET"}],
  "context": {"symbol": "BoundsFromCenterCompilerContext@20", "section": ".text$03context",
              "address": "0x00428640", "size": 70},
  "gaps": [{"section": ".text$00layout", "address": "0x00401000", "size": 161264},
           {"section": ".text$02layout", "address": "0x00428627", "size": 25}],
  "constants": [],
  "constant_aliases": [{"symbol": "__real@3f000000", "address": "0x00470B0C", "value": 0.5}],
  "absolute_symbols": [{"symbol": "__fltused", "address": "0x00000000", "kind": "metadata"}]
}
```

`constant_aliases` is required: the literal has to be read at retail's shared
pool slot `0x470B0C`, which an isolated one-function cluster cannot reach — the
compiler's own pooled copy lands at `0x429000` and the alias rebinds
`__real@3f000000` to `0x470B0C` (the same mechanism `frame_timer.json` uses).
Without it the body is byte-identical except for those four operand words.

## Integration

Copy the source, layout and driver into the tree and register through the
sanctioned tool, which rewrites the region record and appends the layout:

```
python3 matching2/tools/waves/register_cluster.py \
    --layout layout/ltcg/bounds_from_center_004285f0.json --apply
```

then run the focused probe and the whole build; semantic bytes rise by 55.

## Shapes tried

| # | shape | result |
| --- | --- | --- |
| 1 | plain `__cdecl` free function with an `extern "C" float data_00470b0c` operand | 73 bytes; body correct but the constant loads first (`fld const; fmul [eax]`), arguments on the stack |
| 2 | plain free function with the `0.5f` literal | 73 bytes; **instruction-for-instruction retail** except the four stack-argument `mov`s and `ret 16` |
| 3 | cluster: `Box2::GetBoundsFrom` (centre in a member) + array-walking context | 55 bytes, exact except the pooled-constant address |
| 4 | cluster: `Vector2::GetBounds` + the same context, `constant_aliases` for `0.5f` | **EXACT** |
