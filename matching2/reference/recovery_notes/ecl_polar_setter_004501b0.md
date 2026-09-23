# ECL polar vector setter at `0x004501B0`

`ecl_core_interpreter.cpp` now expresses the setter as the ordinary C++ member
`EclPolarVector2_004501B0::SetPolar(float angle, float scale)`. It writes
`cosf(angle) * scale` to the first float and `sinf(angle) * scale` to the
second. The former assembly label remains a linker address alias for the
interpreter's inline-assembly call.

## Ghidra evidence

Ghidra identifies a complete 30-byte leaf at `0x004501B0..0x004501CD` with
signature `__thiscall(void *this, float angle, float scale)`. ECX supplies the
receiver; the two floats are on the stack; the function returns with `RET 8`.
It computes cosine and sine from the angle, multiplies both by the same scale,
and stores the results at receiver offsets `0` and `4`. There is one direct
caller, `FUN_0044e1a0`, at `0x0044F97B`, and the function calls no helpers.

The return register is not consumed by the observed caller; the source model
therefore uses `void`. The source preserves the component behavior and entry
convention, but ordinary `cosf`/`sinf` do not reproduce retail's fused
`FSINCOS` instruction or establish identical x87 rounding. Byte-exactness is
unverified. The manifest now selects the decorated C++ member symbol and keeps
the prior assembly record; no build, probe, or test was run.
