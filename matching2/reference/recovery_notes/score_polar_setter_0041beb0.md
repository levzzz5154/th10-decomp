# Polar setter at `0x0041BEB0`

`0x0041BEB0` is a 30-byte vector setter. Ghidra identifies the function as
`void __thiscall FUN_0041beb0(void *this, float angle, float scale)` and
decompiles it as a cosine-scaled first component followed by a sine-scaled
second component. The corresponding source candidate is
`PolarVector2_0041BEB0::SetPolar` in `matching2/msvc/src/game/score.cpp`:

```cpp
x = cosf(angle) * scale;
y = sinf(angle) * scale;
```

The retail body confirms the member ABI directly: `ECX` supplies `this`, the
angle is at `[ESP+8]`, scale is at `[ESP+0xC]`, and `ret 8` cleans both stack
arguments. Ghidra reports four call sites: `0x0041BB9D` and `0x0041BD99` in
`FUN_0041BB00`, plus `0x0041B23F` and `0x0041B2C9` in `FUN_0041AFD0`.

Retail loads the angle once, executes `FSINCOS`, multiplies cosine by scale and
stores `x`, then multiplies sine by scale and stores `y`. The semantic source
uses ordinary C++ math calls and contains no inline assembly. Its mathematical
component behavior and `__thiscall` signature are clear; it does not establish
the same x87 instruction sequence or bit-for-bit floating-point results.

The existing [`vector_polar_setters_family.md`](vector_polar_setters_family.md)
documents the family-wide exact-byte limitation: the VC7.1 toolchain emits
separate `FCOS` and `FSIN` operations for these source forms rather than
retail's single `FSINCOS`. No build, probe, or byte comparison was run for this
candidate. The manifest entry for `0x0041BEB0` remains `kind: asm`; this source
edit supplies a readable semantic candidate and does not claim an exact
replacement.
