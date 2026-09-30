# ECL operand/value resolver family: live Ghidra ABI audit

Update 2026-09-30: `0x0040C650`, `0x0040C680` and `0x00412A00` are now MSVC C++ in the `ecl_operand_thunks` LTCG layout; `0x00412A60` remains Clang. See [the MSVC port note](foreign_compiler_regions_to_msvc_2026-09-30.md).

Audited against the connected Ghidra program `th10.exe` on 2026-09-23. No
build, probe, or test was run. The integer operand is now classified as a
semantic C++ region in the manifest; its emitted bytes remain unverified. The
other three resolver entries remain assembly.

## Results

| Entry | Retail extent | Ghidra live inputs and return | Call evidence | Disposition |
|---|---:|---|---|---|
| `0x0044FDB0` `ResolveEclIntOperand` | 144 bytes, ends with `RET 4` at `0x44FE3D` | Ignored ECX, VM/frame in EDX, selector at `[ESP+4]`; integer value in EAX | Nine references from `0x44E1A0`; many from `0x40E770`; helper callers at `0x412A00` and `0x40C5F0`. `0x44E438` loads EDX from ESI after pushing EBP as selector. `0x40ED2D` loads the VM into EDX and `0x40ED30` pushes zero as selector. | Replaced the naked body with a C++ candidate whose three-argument `__fastcall` signature preserves this mapping: unused ECX, frame EDX, selector on stack, `RET 4`. Semantics follow the mask, positive frame displacement, `-1` scratch pop/type tag, and external-variable virtual call. Exact bytes remain unverified. |
| `0x0044FE40` `ResolveEclFloatOperand` | 183 bytes, ends at `0x44FEF6` | VM in EAX, selector in ECX, float result in x87; no stack arguments | Ten references from `0x44E1A0`, many from `0x40E770`; `0x40C650` is a tail thunk that loads `[EAX+4]` into EAX then jumps here. `0x40EFAA` sets VM in EAX and index 2 in ECX. | Keep the exact assembly body for now. Prior candidate variants reached 169–185 bytes but did not reproduce the x87/control-flow bytes. Needs the actual interpreter call schedule and shared VM/frame declarations in a native-LTCG context. |
| `0x0044FF80` `ResolveEclFloatValue` | 171 bytes, ends with `RET 4` at `0x450028` | VM in EAX, selector in CL, float operand at `[ESP+4]`; float result in x87 | Calls from `0x44E1A0`, `0x44DF70`, `ForwardEclFloat`, and tail thunk `0x40C680`. At `0x44FB2F` the interpreter pushes the float operand, then sets EAX from ESI and ECX from EBX before calling. | Keep the exact assembly body for now. Historical candidate reached the 171-byte extent but differed in 140 bytes, including branch polarity. Needs the real caller schedule/shared class context to recover both argument placement and x87 code shape. |
| `0x00450030` `ResolveEclVariableValue` | 58 bytes, ends at `0x450069` | VM in ESI, selector in ECX; address or zero in EAX | Only two direct calls, both in `0x44E1A0`: `0x44E481` and `0x44F87A`. At the latter, ESI remains the VM and ECX is cleared before the call. | Keep the exact assembly body for now. The VM is an implicit ESI live-in, which a normal member signature cannot name; previous native-LTCG contexts did not reproduce that private register assignment. |

Ghidra's current decompiler infers a `ulonglong` result for `0x0044FDB0`, while
the C++ model returns the 32-bit EAX value. The reviewed call sites consume
EAX and either discard or overwrite EDX; no sampled caller relies on a high
return half. That register-level limit is recorded separately from the
semantic row classification.

The operand table shape is independently consistent with the exact native-LTCG
float destination at `0x00450070`: table pointer at VM `+4`, indirect mask at
table `+8`, and slot values at table `+0x10`. The embedded frame starts at VM
`+8`; its stack pointer is VM `+0x1008`, frame base is `+0x100C`, variable
slots pointer is `+0x1010`, and external-value context is `+0x1014`. The
`0x0044FDB0` source uses those same frame fields and the existing
`EclVariableContext::ResolveSlot` declaration.

## ABI correction and next cut

The old blocker comment in `ecl_core_interpreter.cpp` said retail entered
`0x0044FDB0` with the selector in EAX. Ghidra's disassembly and call sites show
that EAX is loaded from `[ESP+4]` inside the function; callers pass the selector
on the stack. The matching C++ shape is the same three-argument fastcall
pattern already used by the semantic `0x0044FF00` function in this translation
unit: an ignored ECX placeholder, the frame in EDX, and remaining arguments on
the stack. That evidence motivated the `0x0044FDB0` source candidate.

The remaining coherent conversion cut is the float pair plus the ESI-based
variable lookup, scheduled from a real interpreter caller. `0x0044E1A0` is
their shared direct caller and contains both x87 float call shapes and the
implicit ESI live-in. A synthetic one-call array context has not reproduced
those assignments. The integer operand retains its raw assembly alias for
existing assembly call sites while the manifest points at the semantic C++
symbol; byte identity is a separate, unverified claim.

## Tail-thunk update

`0x0040C650`, `0x0040C680`, and `0x00412A60` now have exact ordinary C++
bodies compiled with the pinned Clang i386 COFF profile. The first two load
their resolver receiver with `MOV EAX, [register+4]`: the first receives its
frame in EAX, and the second in EDX with its original EAX input unused. The
third loads `[EAX+0x14D8]` and then `[EAX+4]`, chasing the VM's operand frame.
Each tail-jumps to its existing assembly resolver, retaining the live ECX
selector, the second resolver's stack float argument, and the x87 result.
The focused probe matched all three complete regions, including target
relocations. This does not change the assembly status of the resolver bodies
at `0x0044FE40` and `0x0044FF80`.
