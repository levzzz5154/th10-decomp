# `__fpmath` at `0x00456AD4`

## Recovered behavior

Ghidra identifies the entry as `void __cdecl __fpmath(int param_1)` with a body from `0x00456AD4` through the `ret` at `0x00456AF1`. The only caller xref is `__cinit` at `0x004575BF`; it loads the function pointer stored at `0x004733A8`, passes its own stack parameter, calls it, then removes that argument. The source names the argument `set_default_precision` because that is its only direct use.

The function runs these steps in order:

1. Call `FUN_00456A8C`, which installs six CRT floating-point conversion hooks in the pointer table at `0x004739C0` through `0x004739D4`.
2. Call `__ms_p5_mp_test_fdiv` and save its result to the 32-bit global at `0x00477388`.
3. If `param_1` is nonzero, call `__setdefaultprecision`, which calls `__controlfp(0x10000, 0x30000)`.
4. Clear pending x87 exceptions with `FNCLEX`.

The feature-test helper has no arguments. Its Ghidra decompilation checks for `KERNEL32!IsProcessorFeaturePresent` and calls the resolved function with feature number zero when available; otherwise it falls back to `__ms_p5_test_fdiv`. The latter returns an integer boolean from its floating-point division check. Although Ghidra left the feature-test return type undefined and the shared source declaration is `void`, the caller consumes EAX as the stored result. The C++ source uses a local `int (__cdecl*)()` view of the same no-argument entry to preserve that observed return value. The cdecl/stdcall distinction does not alter cleanup for this zero-argument call.

Ghidra classifies `0x00477388` as a four-byte `undefined4`; `__fpmath` writes EAX as a dword, and code at `0x00463BC6` reads the dword and compares it with one when choosing its floating-point remainder path. The implementation therefore writes an `unsigned int` through the existing data symbol even though its shared declaration currently says `unsigned char`.

## C++ mapping and limits

`fpmath_00456ad4.cpp` is now ordinary C++ with the observed cdecl parameter and the helper-call ordering intact. Its last operation calls the existing `asm_clrfp_0045ed7b` entry: Ghidra shows that helper reads the current status word, executes `FNCLEX`, and returns the saved word. `__fpmath` ignores that return value, so this models its exception-clear side effect while keeping the inline instruction out of this function's source. The helper itself remains an assembly-backed function pending its own recovery.

The semantic names and final meaning of the six conversion hooks remain only partly known. The exact runtime result also depends on whether the target OS exports `IsProcessorFeaturePresent` and on the behavior of the fallback FDIV probe. This pass did not build, probe, or run tests, so generated code equivalence is unverified.
