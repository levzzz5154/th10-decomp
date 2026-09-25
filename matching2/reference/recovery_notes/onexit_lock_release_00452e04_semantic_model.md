# `0x00452E04` on-exit lock release semantic model

The ordinary C++ model is in
[`FUN_00452e04_00452e04.cpp`](../semantic_candidates/FUN_00452e04_00452e04.cpp).
It keeps the existing C-linkage symbol and zero-argument calling convention.

## Behavior and call path

The six-byte retail body consists of a relative call to `FUN_00457580` followed
by `RET`. That helper calls `FUN_00453B3F(8)`, which passes the critical-section
record at `0x004730C0` to `LeaveCriticalSection` through IAT slot `0x004660B4`.
Ghidra identifies `__onexit` at `0x00452DD2` as the direct caller. It saves the
result of the preceding on-exit registration call before calling this wrapper,
then restores that saved result, so the wrapper's return register is unused.

## ABI and exactness

Ghidra identifies no parameters, stack cleanup, or private register inputs for
the wrapper. Its body is a plain call and plain `RET`. The C++ definition uses
`__cdecl`; with no arguments this has the same stack effect. The semantic model
preserves the observed forwarding behavior, but no build or byte comparison was
run, so exact machine-code identity is unverified.

The manifest records the row as semantic under the unchanged
`_asm_FUN_00452e04_00452e04` symbol and retains the prior assembly row in
`previous_record`.

**Build status (2026-09-25):** the full byte-verified build showed that this model does not reproduce the retail bytes. The maintained source keeps the exact assembly, and the model is preserved in `reference/semantic_candidates/`.
