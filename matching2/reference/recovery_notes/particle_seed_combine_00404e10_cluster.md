# 0x00404E10 landed as a native-LTCG cluster: `ParticleSeed::Combine`

Status: **EXACT**. The 92-byte region between the recovery-scaler tail
(`0x00404DA0` + its padding) and the `0x00404E6C` padding is now ordinary C++
plus one cluster layout. The focused probe reports

```
0x00404e10      92 bytes  ?Combine@ParticleSeed@@QBEPAU1@PBU1@PAU1@@Z  EXACT
EXACT
```

and the unit that owns the region's six assembly call sites is unchanged:

```
0x004049a0     688 bytes  _asm_FUN_004049a0_004049a0  EXACT
EXACT
```

## What the region computes

Retail, in order:

```text
D9 40 14 / D8 41 14   fld dword ptr [eax+0x14]; fadd dword ptr [ecx+0x14]
...                   six sums, pushed back to front (0x14 down to 0)
D9 1E / D9 5E 04      fstp dword ptr [esi]; fstp dword ptr [esi+4]
D9 56 08              fst  dword ptr [esi+8]          (keeps the value)
D9 C1 / D9 5E 0C      fld st(1); fstp dword ptr [esi+0xC]
D9 C2 / D9 5E 10      fld st(2); fstp dword ptr [esi+0x10]
D9 C3 / D9 5E 14      fld st(3); fstp dword ptr [esi+0x14]
E8 .. / 88 46 18      call 0x00463B2C (__ftol2); mov byte ptr [esi+0x18],al   (x4)
8B C6                 mov eax,esi
C3                    ret
```

So the entry convention is `EAX` = one operand, `ECX` = the other operand,
`ESI` = the destination, and the function returns `ESI` in `EAX`. The three
pointers address the same 28-byte record: six floats at `+0x00..+0x17` and four
bytes at `+0x18..+0x1B`. The body writes the six component sums and then fills
the four bytes with the *truncated sums of components 2..5* — the six sums are
still live on the x87 stack at that point, so each `__ftol2` consumes one of
them and only `AL` is stored.

`0x00463B2C` is the compiler's float→int helper `__ftol2`, **not** an RNG. The
legacy reconstruction in `reference/legacy_semantic/src/game/particle_seed.cpp`
models it as a `ParticleRandomHook next_random` parameter and calls it four
times; that reading is wrong — the callee is a compiler helper that reads
`ST(0)`, so the source must be four `(unsigned char)` casts of the live sums.

The region is the `fadd`/register-mirror twin of the landed `Vec_Subtract`
(`0x00404D40`, 92 bytes, same skeleton with `fsub` and the operand roles
swapped), which is why both are clusters.

## Files

* `src/game/particle_seed.cpp` — the model; this source owns only this region,
  so the cutover is complete (the `__declspec(naked)` body is gone).
* `layout/ltcg/particle_seed_combine_00404e10.json` — the layout.
* `layout/ltcg/particle_seed_combine_00404e10_context.cpp` — synthetic
  array-walking caller; establishes the convention, contributes no game code.

No header edit and no additional source file is needed. The six
`call asm_ParticleSeed_Combine_00404e10` sites in `src/math/math_utils.cpp`
keep resolving because the manifest still binds
`_asm_ParticleSeed_Combine_00404e10` to `0x00404E10` (the region record keeps it
as `previous_record`), exactly as the landed `Vec_Subtract` cluster does for its
own asm call sites.

```cpp
// 0x00404E10: the component-wise sum of two six-float particle-seed records,
// with the destination's four random bytes refreshed from its last four
// components.
//
// Retail: D9 40 14 / D8 41 14   fld [eax+0x14]; fadd [ecx+0x14]
//         ... six sums, pushed back to front
//         D9 1E / D9 5E 04      fstp [esi]; fstp [esi+4]
//         D9 56 08              fst  [esi+8]
//         D9 C1 / D9 5E 0C      fld st(1); fstp [esi+0xC]
//         D9 C2 / D9 5E 10      fld st(2); fstp [esi+0x10]
//         D9 C3 / D9 5E 14      fld st(3); fstp [esi+0x14]
//         E8 .. / 88 46 18      call __ftol2; mov [esi+0x18],al   (x4, random)
//         8B C6                 mov eax,esi
//         C3                    ret
// The other operand arrives in EAX, the receiver in ECX and the destination in
// ESI, so the sum is compiled as a native-LTCG cluster.
// Carved out of this file (asm_ParticleSeed_Combine_00404e10).

struct ParticleSeed {
    float values[6];
    unsigned char random[4];

    __declspec(noinline) ParticleSeed* Combine(const ParticleSeed* other,
                                               ParticleSeed* destination) const;
};

#pragma code_seg(".text$01seedcombine")
ParticleSeed* ParticleSeed::Combine(const ParticleSeed* other,
                                    ParticleSeed* destination) const {
    // The six sums are computed last-to-first: retail's x87 pushes run back to
    // front, and only that order keeps all six in registers.
    float value5 = values[5] + other->values[5];
    float value4 = values[4] + other->values[4];
    float value3 = values[3] + other->values[3];
    float value2 = values[2] + other->values[2];
    float value1 = values[1] + other->values[1];
    float value0 = values[0] + other->values[0];
    destination->values[0] = value0;
    destination->values[1] = value1;
    destination->values[2] = value2;
    destination->values[3] = value3;
    destination->values[4] = value4;
    destination->values[5] = value5;
    // The random bytes are the truncated sums of the last four components;
    // retail reaches them through __ftol2, of whose result only AL is kept.
    destination->random[0] = (unsigned char)value2;
    destination->random[1] = (unsigned char)value3;
    destination->random[2] = (unsigned char)value4;
    destination->random[3] = (unsigned char)value5;
    return destination;
}
#pragma code_seg()
```

```cpp
// layout/ltcg/particle_seed_combine_00404e10_context.cpp
// Compiler context only; never selected as recovered game code.
// The array-walking caller is what makes the whole-program pass pick the
// observed retail convention: the other operand in EAX, the receiver in ECX
// and the destination in ESI.
#include "../../src/game/particle_seed.cpp"

#pragma code_seg(".text$03context")
int __stdcall ParticleSeedCombineCompilerContext(ParticleSeed** left, ParticleSeed** right,
                                                 ParticleSeed* destination, int count) {
    while (count--) {
        destination = (*left++)->Combine(*right++, destination);
    }
    return 0;
}
#pragma code_seg()
```

Layout (`layout/ltcg/particle_seed_combine_00404e10.json`), full:

```json
{
  "schema_version": 1,
  "name": "particle_seed_combine_00404e10",
  "source": "src/game/particle_seed.cpp",
  "driver": "layout/ltcg/particle_seed_combine_00404e10_context.cpp",
  "headers": [],
  "image_base": "0x00400000",
  "description": "Six-float component-wise sum with refreshed random bytes, compiled with native LTCG so the other operand arrives in EAX, the receiver in ECX and the destination in ESI.",
  "functions": [
    {
      "name": "ParticleSeed_Combine",
      "symbol": "?Combine@ParticleSeed@@QBEPAU1@PBU1@PAU1@@Z",
      "section": ".text$01seedcombine",
      "address": "0x00404E10",
      "size": 92,
      "actual_abi": "other operand in EAX; receiver in ECX; destination in ESI; plain RET"
    }
  ],
  "context": {
    "symbol": "?ParticleSeedCombineCompilerContext@@YGHPAPAUParticleSeed@@0PAU1@H@Z",
    "section": ".text$03context",
    "address": "0x00404E80",
    "size": 53,
    "description": "Synthetic array-processing caller that establishes the observed register convention; not recovered game code."
  },
  "gaps": [
    {"section": ".text$00layout", "address": "0x00401000", "size": 15888},
    {"section": ".text$02layout", "address": "0x00404E6C", "size": 20}
  ],
  "constants": [],
  "absolute_symbols": [
    {"symbol": "__ftol2", "address": "0x00463B2C", "kind": "relative_code"},
    {"symbol": "__fltused", "address": "0x00000000", "kind": "metadata"}
  ]
}
```

`__ftol2` is bound as `relative_code` at retail's helper address and
`__fltused` as metadata, as every float-touching layout needs.

## Integration

The files are already in the tree and the registration is applied:

```
python3 matching2/tools/waves/register_cluster.py \
    --layout layout/ltcg/particle_seed_combine_00404e10.json --apply
python3 matching2/tools/matching/probe.py --source src/game/particle_seed.cpp
```

Semantic bytes rise by 92; the whole-image build is the integration owner's.

## Register assignment: what the flag sweep showed

The interesting part of this region is that it is the *mirror* of its
`Vec_Subtract` twin: retail's accumulator operand is in `EAX` and its memory
operand in `ECX`, where the twin's is the other way round.

| # | shape | result |
| --- | --- | --- |
| 1 | free `__stdcall` `ParticleSeed* ParticleSeed_Combine(const ParticleSeed*, const ParticleSeed*, ParticleSeed*)`, reverse temporaries, array-walking context | 92 bytes, **12 differing** — emitted `fld [ecx]; fadd [eax]` |
| 2 | same, expression operands swapped (`right->values[i] + left->values[i]`) | 92 bytes, 12 differing, byte-identical to #1 |
| 3 | same, context calls `Combine(*right++, *left++, result)` | 92 bytes, 12 differing, byte-identical to #1 |
| 4 | same, parameters declared in the opposite order (`right` first) | 92 bytes, 12 differing, byte-identical to #1 |
| 5 | free function with the destination first (`Combine(result, *left++, *right++)`) | 92 bytes, 12 differing — again `fld [ecx]; fadd [eax]` |
| 6 | member `ParticleSeed* ParticleSeed::Combine(const ParticleSeed* other, ParticleSeed* destination) const`, reverse temporaries, same array-walking context | 92 bytes, **0 differing** — `fld [eax]; fadd [ecx]`, destination in `ESI` |
| 7 | #6 with the expression written `other->values[i] + values[i]` | 92 bytes, 0 differing, byte-identical to #6 |

The 12 differing bytes in #1-#5 are exactly the ModRM register fields of the 12
x87 memory operands; the opcodes, the `__ftol2` sequence and the tail are
already retail. The lesson: for a *free* three-pointer function under this
context the whole-program pass puts the accumulator-side operand in `ECX` and
the memory-operand side in `EAX`, and the source order cannot change that
(`fadd`/`fmul` are commutative, so MSVC canonicalises the operand pair and the
emitted bytes stay identical whichever way the expression, the declaration or
the call argument list is written). Modelling the record as a *member* — the
receiver in `ECX`, the other operand in `EAX`, the destination in `ESI` —
reproduces retail directly and is what landed.

Both `#6` and `#7` are byte-identical, so the model above uses the reading order
`values[i] + other->values[i]`; the temporary order (5 → 0) is load-bearing, as
in the twin.

## One size pitfall

The synthetic context of this layout is **53** bytes, not the 60/61 the
neighbouring clusters emit (a member call needs one fewer setup instruction than
a three-pointer `__stdcall` call). A layout that declares the wrong context size
fails *before* any byte comparison with

```
function compiler context extent is outside a MAP CODE contribution
```

(the context's declared extent is not inside its map contribution) — the
emitted value is in the build's `cluster.map` line for `.text$03context`.
