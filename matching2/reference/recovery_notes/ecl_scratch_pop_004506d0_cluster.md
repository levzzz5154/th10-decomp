# ECL scratch push/pop recovery status

Updated 2026-09-30. The active project currently has a semantic Push region at
`0x00450690..0x004506CF` and an assembly Pop region at
`0x004506D0..0x004506F8`. The earlier pair-layout and Pop-promotion claims in
this note were stale and do not describe the current manifest.

## Recovered behavior

The checked-in Ghidra listing at
[`004506D0.asm`](../../../decompiled/ghidra_augmented/functions/004506D0.asm)
shows Pop receiving the frame address in EAX. It loads `sp` from `+0x1000`,
adds `-4`, and branches when the result is negative. For a nonnegative result,
it stores the result to `sp` and loads `frame_base` from `frame + result`. It
then restores the old frame-base value to `sp` and returns zero. The two code
xrefs are `0x0044E211` and `0x0044E453`, both in `FUN_0044E1A0`; neither pushes
stack arguments. Retail's final instructions are `xor eax,eax; ret`.

The scratch-frame layout is a 0x1000-byte buffer followed by `sp` at `+0x1000`
and `frame_base` at `+0x1004`. The current shared view for the reference
candidates is
[`ecl_scratch_frame_00450690.hpp`](../semantic_candidates/ecl_scratch_frame_00450690.hpp).

## Active project state

`regions.json` still owns Pop as a 41-byte `asm` region at `0x004506D0`, using
`src/script/ecl_pop_scratch_value_004506d0.cpp`. That production source is
still a naked inline-assembly wrapper. Push is a separate 64-byte semantic
region. The registered
[`ecl_push_scratch_value_00450690.json`](../../msvc/layout/ltcg/ecl_push_scratch_value_00450690.json)
is Push-only: its synthetic caller begins at `0x004506E0`, and its layout gap
occupies `0x004506D0..0x004506DF`. It is not a verified Push/Pop pair layout.

The reference-only C++ model in
[`ecl_pop_scratch_value_004506d0.cpp`](../semantic_candidates/ecl_pop_scratch_value_004506d0.cpp)
uses a `regparm(1)` entry so the frame arrives in EAX. It models the decrement
as unsigned 32-bit wraparound, then tests the sign bit; this avoids signed
overflow in the source while preserving the machine condition. It contains no
inline assembly and is not part of the active project build.

## Byte-match status

With the configured Clang 22 i386 GNU target flags, the candidate emits the
correct 41-byte extent but differs from retail in 16 bytes. Clang keeps the
same `add ..., -4` and branch shape, but allocates the offset and saved frame
base to different registers, reverses the SIB base/index order, and encodes
the final self-XOR as `31 C0` instead of retail's `33 C0`. Therefore Pop has
not passed the exact-byte gate and remains assembly in the active manifest.

A future paired attempt must start from the current Push-only layout, build a
new shared caller context, and compare both functions with native LTCG. That
route is useful only if its function signatures can express Pop's EAX entry
without adding assembly. Do not register this reference candidate as semantic
until the configured exact gate passes.
