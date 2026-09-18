# 0x00441E50 rounded-vector scaler: landed through the native-LTCG cluster path

2026-09-19. Region `0x00441E50`, 56 bytes, owner `src/math/random_vector.cpp`.
Recovered as ordinary C++ and **EXACT** through the cluster path. Nothing in the
maintained tree was changed except this note; the source, driver and layout below
still have to be applied by the integration owner.

## What the region is

`asm_RandomVector_StoreRoundedScalar_00441e50` scales a three-integer vector by a
float rate and truncates each product toward zero, componentwise:

```
fild [edi+4] / push ebx / push ebp / fmul [esp+0xC] / call __ftol2 (0x463B2C)
fild [edi+8] / mov ebx,eax / fmul [esp+0xC] / call __ftol2
fild [edi]   / mov ebp,eax / fmul [esp+0xC] / call __ftol2
mov [esi+8],ebp / pop ebp / mov [esi],eax / mov [esi+4],ebx / mov eax,esi / pop ebx / ret 4
```

Observed ABI: **source pointer in EDI, destination pointer in ESI, rate on the
stack, destination returned in EAX, `RET 4`**. That is not expressible with a
plain declaration — a three-argument `__stdcall` pops 12 — so the region is a
native-LTCG cluster. The verified callers are at `0x004417C8`, `0x004417FB`,
`0x0044183F` and `0x0044187F` inside the `0x00441600` interpolator, where EDI is
`&object->vector[i]` (stride 12) and ESI is a stack temporary that the caller
reads back through EAX.

## Model (src/math/random_vector.cpp)

```cpp
// 0x00441E50: scale a three-component integer vector by a float rate and
// truncate every product toward zero.
//
// The source vector arrives in EDI, the destination in ESI, the rate on the
// stack, and the destination is returned in EAX, so the scaler is compiled as
// a native LTCG cluster (layout/ltcg/random_vector_store_rounded_scalar.json).
//
// The three products are computed in the order y, z, x and stored in the order
// +8, +0, +4. MSVC rotates the statement sequence left by one, so writing the
// components in declaration order reproduces retail's schedule; writing them
// in retail's emitted order (y, z, x) rotates it once more and misses.

struct RandomVectorSource { int x, y, z; };
struct RandomVectorResult { int x, y, z; };

#pragma code_seg(".text$01store")
__declspec(noinline) RandomVectorResult* __stdcall RandomVector_StoreRoundedScalar(
        RandomVectorSource* source, RandomVectorResult* result, float scale) {
    int x = int(source->x * scale);
    int y = int(source->y * scale);
    int z = int(source->z * scale);
    result->x = x;
    result->y = y;
    result->z = z;
    return result;
}
#pragma code_seg()
```

Decorated symbol (read back from a probe compile, not guessed):
`?RandomVector_StoreRoundedScalar@@YGPAURandomVectorResult@@PAURandomVectorSource@@PAU1@M@Z`

## Compiler context (layout/ltcg/random_vector_store_rounded_scalar_context.cpp)

```cpp
// Compiler context only; never selected as recovered game code.
#include "../../src/math/random_vector.cpp"

#pragma code_seg(".text$03context")
int __stdcall RandomVectorCompilerContext(
        RandomVectorSource* sources, RandomVectorResult* results, int count, float scale) {
    for (int index = 0; index < count; ++index)
        RandomVector_StoreRoundedScalar(&sources[index], &results[index], scale);
    return 0;
}
#pragma code_seg()
```

The array walk is what puts the two pointer arguments in ESI and EDI and leaves
the float on the stack; the emitted body is identical under the four other
contexts tried (see below), so the convention is stable once the caller walks a
source array into a destination array.

Context symbol: `?RandomVectorCompilerContext@@YGHPAURandomVectorSource@@PAURandomVectorResult@@HM@Z`

## Layout (layout/ltcg/random_vector_store_rounded_scalar.json)

```json
{
  "schema_version": 1,
  "name": "random_vector_store_rounded_scalar",
  "source": "src/math/random_vector.cpp",
  "driver": "layout/ltcg/random_vector_store_rounded_scalar_context.cpp",
  "headers": [],
  "image_base": "0x00400000",
  "description": "Rounded vector scaling compiled with native LTCG.",
  "functions": [
    {
      "name": "RandomVector_StoreRoundedScalar",
      "symbol": "?RandomVector_StoreRoundedScalar@@YGPAURandomVectorResult@@PAURandomVectorSource@@PAU1@M@Z",
      "section": ".text$01store",
      "address": "0x00441E50",
      "size": 56,
      "actual_abi": "source in EDI; result in ESI; scale on the stack; RET 4"
    }
  ],
  "context": {
    "symbol": "?RandomVectorCompilerContext@@YGHPAURandomVectorSource@@PAURandomVectorResult@@HM@Z",
    "section": ".text$03context",
    "address": "0x00441EA0",
    "size": 50,
    "description": "Synthetic caller that establishes the observed register convention; not recovered game code."
  },
  "gaps": [
    { "section": ".text$00layout", "address": "0x00401000", "size": 265808 },
    { "section": ".text$02layout", "address": "0x00441E88", "size": 24 }
  ],
  "constants": [],
  "absolute_symbols": [
    { "symbol": "__ftol2", "address": "0x00463B2C", "kind": "relative_code" },
    { "symbol": "__fltused", "address": "0x00000000", "kind": "metadata" }
  ]
}
```

`__ftol2` at `0x00463B2C` is the shared float-to-int helper the three products
are truncated through, and `__fltused` has to be bound because the unit uses
floats at all.

## Verification

```
python3 matching2/tools/matching/probe.py --source src/math/random_vector.cpp \
    --project /tmp/StoreRoundedScalar/msvc --output /tmp/StoreRoundedScalar/out --show 30
0x00441e50      56 bytes  ?RandomVector_StoreRoundedScalar@@YGPAURandomVectorResult@@PAURandomVectorSource@@PAU1@M@Z  EXACT
```

The JSON report shows `different_bytes: 0` for a 56-byte region whose object came
from `clusters/random_vector_store_rounded_scalar/bodies.obj` (`compiler_kind:
native-ltcg`, two compiler inputs: the context driver and the padding layout).
Whole-image `make` was **not** run here: it belongs to the integration owner.

## Shapes tried

Six source shapes and five contexts were attempted, all in a throwaway copy.
Four shapes and three contexts compiled.

| Source shape | Context | Result |
| --- | --- | --- |
| `x,y,z` locals then stores (landed) | A: array walk | **EXACT, 56 bytes, 0 differing** |
| `y,z,x` locals then stores | A | 56 bytes, 21 differing (emitted compute order `z,x,y`) |
| `x,y,z` direct assignment | A | 48 bytes, 54 differing (stores not deferred) |
| `y,z,x` direct assignment | A | 48 bytes, 43 differing |
| `y,z,x` locals | D: array walk plus accumulated result | 56 bytes, 21 differing, same body as A |
| `y,z,x` locals | E: pointer walk with a scale array | 56 bytes, 21 differing, same body as A |
| `y,z,x` locals | B: destination carried across the loop | rejected — context is not a single MAP CODE contribution |
| `y,z,x` locals | C: three fixed destinations | rejected — context is not its entire declared contribution |
| swapped `source`/`result` parameter order | A | did not compile: context disagreed with the declaration |
| `z,y,x` statement order | A | did not compile: the generated probe text was malformed |

## Mechanism worth remembering

- The **statement order matters and is not the emitted order.** With the three
  products written `x, y, z`, MSVC emits the chain `y, z, x` and the stores
  `+8, +0, +4`; writing them `y, z, x` emits `z, x, y` with stores `+0, +4, +8`.
  The scheduler rotates the sequence left by one, and the stores follow the
  rotated sequence. Modelling retail's *emitted* order as the source order
  misses by 21 bytes even though the extent is right.
- Deferring the stores behind three explicit locals is what makes the extent 56;
  assigning straight into `result` members lets the scheduler interleave the
  stores and collapses the body to 48 bytes.
- The context only has to establish the register convention; all three contexts
  that built gave the byte-identical body.
