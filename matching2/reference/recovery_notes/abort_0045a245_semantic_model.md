# `_abort` semantic model at `0x0045A245`

The 23-byte row now uses ordinary C++ and is marked `semantic`; its prior ASM
record and external symbol remain in the manifest. The shared declaration
marks the entry as `__cdecl` and nonreturning. The `_raise` declaration and
naked definition now share Ghidra's `int __cdecl(int)` signature.

## Ghidra evidence

Ghidra identifies `_abort` as a no-argument CRT function. Its disassembly makes
three cdecl calls in order: `FUN_00458EFD(10)`, `_raise(0x16)`, and
`__exit(3)`. The sole direct caller is `terminate` at `0x004556C3`. The first
helper takes one stack argument; `_raise` returns an integer that `_abort`
ignores; `__exit` already has a semantic C++ wrapper with the matching
one-integer cdecl interface.

## Recovered behavior

The C++ body preserves the runtime-error report, signal raise, and exit-status
call order. `_abort` is nonreturning, so the source retains a no-return sink
after the exit call.

## Limits

This is a behavioral model, not a claim of byte identity. No build, probe, or
test was run.
