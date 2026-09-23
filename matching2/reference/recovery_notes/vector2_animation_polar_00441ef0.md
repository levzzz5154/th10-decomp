# Animation polar setter at `0x00441EF0`

`0x00441EF0` is a 30-byte 2D polar-vector setter. Ghidra identifies the
function as `void __thiscall SetAnimationPolarVector(void *this, float,
float)` and decompiles the stores as `x = cos(angle) * length` and
`y = sin(angle) * length`. The readable, inline-assembly-free candidate is
`AnimationPolarVector2_00441EF0::SetAnimationPolar` in
`matching2/msvc/src/game/recovery_leaves.cpp`.

The ABI is confirmed by the instructions: `ECX` is copied as the receiver,
the two stack floats are loaded at `[ESP+8]` and `[ESP+0xC]`, and `ret 8`
cleans them. Retail computes both trigonometric values with one `FSINCOS`,
multiplies each by the length, and stores the cosine result at offset `0` and
the sine result at offset `4`.

Ghidra reports exactly two call xrefs, both from `FUN_0043EE30`:

| Call site | Caller |
| --- | --- |
| `0x00441210` | `FUN_0043EE30` |
| `0x00441298` | `FUN_0043EE30` |

The C++ calls to `cosf` and `sinf` express the component behavior and ordinary
member ABI, but do not reproduce retail's single `FSINCOS` instruction or
guarantee identical x87 rounding. The existing
[`vector_polar_setters_family.md`](vector_polar_setters_family.md) documents
the VC7.1 instruction-selection limitation for this family. No build, probe,
or byte comparison was run for this candidate; the manifest entry and shared
assembly aliases remain unchanged.
