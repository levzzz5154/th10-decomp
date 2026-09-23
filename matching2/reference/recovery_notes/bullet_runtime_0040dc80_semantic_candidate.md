# 0x0040DC80 semantic replacement candidate

**Disposition: keep the retail naked body in `matching2/msvc/src/game/bullet.cpp`.**
The only pre-existing C++ candidate is a partial legacy transcription and cannot
replace the current body faithfully. No uncompiled replacement source was added.

## Live Ghidra evidence

Program: `th10.exe`.

- Entry/body: `0x0040DC80..0x0040E5EB` (2,412 bytes).
- Entry signature: `undefined4 __stdcall FUN_0040dc80(undefined4 *param_1)`;
  Ghidra places the single pointer in `Stack[0x4]`. The body ends with
  `ret 4`. The return value is in EAX: the decompilation returns `0` for the
  already-updating and normal paths, `0xFFFFFFFF` on the discard paths, and
  `1` when the lifetime helper reports expiration. A typed C++ entry would
  therefore need an `int`-sized result and `__stdcall` cleanup.
- Direct callers reported by Ghidra: `FUN_0040cfb0` and `FUN_0040d750`.
  Both pass a state pointer on the stack; the latter checks EAX after the call.
  The complete analysis also lists a call xref at `0x0040DC76` in addition to
  the two caller functions.
- Direct callees reported by Ghidra (22):
  `FUN_00404610`, `FUN_00409d90`, `FUN_0040c6e0`, `FUN_0040c730`,
  `FUN_0040e5f0`, `FUN_004127a0`, `FUN_00412ac0`, `FUN_004266b0`,
  `FUN_00428630`, `FUN_0043dd10`, `FUN_004491c0`, `FUN_004492f0`,
  `FUN_00449350`, `FUN_004496d0`, `FUN_0044bf40`, `FUN_0044c2a0`,
  `FUN_0044c5d0`, `FUN_0044fd10`, `FUN_00450470`, `FUN_00450700`,
  `FUN_00463b2c`, and `NormalizeAngle`.

The decompilation shows the update flag check and previous-position copy first,
then four conditional trajectory evaluations, two position paths, three motion
advances, playfield clamping/culling, and the remaining lifetime, animation,
resource, and render-state updates. The early geometry section is only one part
of this routine.

## Integration blockers

1. The declaration in `matching2/msvc/include/asm_symbols.hpp` is the stale
   `extern "C" void __cdecl asm_FUN_0040dc80_0040dc80();`, while the live entry
   is a one-pointer `__stdcall` function with an EAX result. A semantic C++
   definition needs a corrected visible declaration or a translation-unit
   declaration workaround; neither is part of this function-body-only edit.
2. `matching2/reference/legacy_semantic/src/game/bullet.cpp` contains an
   incomplete `BulletEntity_UpdateTransform` model. It adds a null-pointer
   return absent from retail and stops after transform/culling, omitting the
   rest of the Ghidra body, including its lifetime and animation/resource
   updates. It also calls `Trajectory_*` names that are not the target's
   declared direct callees.
3. The current `asm_symbols.hpp` declarations expose the callees as untyped
   no-argument C symbols, while the retail body passes values in registers,
   stack slots, and x87 results. The current naked body spells out that
   marshalling. A faithful C++ integration needs resolved call signatures and
   state types for the paths it calls; the partial legacy model does not supply
   them.

Until those declarations and the full runtime behavior are recovered together,
the retail body remains the only integrated definition. No build, probe, or
test was run for this inspection.
