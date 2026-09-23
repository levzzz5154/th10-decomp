# `Recovery_CreateLargeResourceState` (`0x00425020`) ABI audit

**Disposition:** retain the exact assembly body. Live Ghidra confirms that the
outer entry has a conventional zero-argument, pointer-returning call shape, but
the helper edges needed to model its behavior depend on private register
receivers that Ghidra does not expose as C++ parameters. A semantic C++ rewrite
would have to preserve those register conventions explicitly.

## Extent and aliases

- The function occupies `0x00425020` through the `RET` at `0x00425064`, a
  69-byte region (`regions.json`: size `69`).
- Current names at this entry are Ghidra's `FUN_00425020`, the source function
  `asm_Recovery_CreateLargeResourceState_00425020`, and the region symbol
  `_asm_Recovery_CreateLargeResourceState_00425020`. The source comment labels
  its body `Recovery_CreateLargeResourceState`.
- Ghidra reports no labels inside the function body.

## ABI and direct references

Ghidra reports `void * __stdcall FUN_00425020(void)`. There are two direct
callers:

- `FUN_00417870`, call at `0x00417ab8`, passes no stack arguments and tests
  `EAX` immediately for null.
- `FUN_0040a350`, call at `0x0040a351`, passes no stack arguments and ignores
  the result.

Those callsites support the outer zero-argument return shape. They do not
support the internal helper ABIs as standard C++ calls:

- After allocation, `0x00425033` copies the allocation pointer into `ESI` and
  calls `FUN_004246c0` without pushing an argument or setting `ECX`. That
  helper's Ghidra decompilation identifies `unaff_ESI`, and its instructions
  read and write fields through `ESI` before returning that pointer in `EAX`.
- The returned pointer is kept in `EBX` and passed implicitly to
  `FUN_004247f0`; its Ghidra signature also has no parameters, while its
  instructions dereference `[EBX + 0x10]`. The outer entry is therefore using
  `EBX` as a private state receiver across this call.
- On its failure path the entry pushes the state pointer for
  `FUN_00424ed0`. Ghidra's outer decompilation renders this as
  `FUN_00424ed0(this, (int)pvVar1)` with an undefined `this`; the machine-level
  call is stack-based and the callee returns with `RET 4`.

The pseudocode consequently loses the receiver flow: Ghidra shows no parameter
for the `ESI` initializer, no parameter for the `EBX` state routine, and an
undefined value for cleanup's `this`. The exact register/stack sequence in the
naked body remains the supported representation for this entry.
