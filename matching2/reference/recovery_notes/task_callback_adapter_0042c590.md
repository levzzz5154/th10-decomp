# 0x0042C590 — queued callback ABI adapter; keep as assembly

2026-09-23. The manifest assigns `0x0042C590..0x0042C599` (10 bytes) to
`asm_FUN_0042c590_0042c590`; `0x0042C59A..0x0042C59F` is the following
6-byte padding region. Read-only Ghidra MCP inspection of `th10.exe` confirms
the exact boundary and instructions:

```text
0042c590  57             push edi
0042c591  8bf9           mov  edi,ecx
0042c593  e8c8fdffff     call 0042c360
0042c598  5f             pop  edi
0042c599  c3             ret
```

Ghidra has no function object at `0x0042C590`, so its function-level caller
query cannot resolve this address. The sole address xref is the data reference
at `0x0042BBF5` in `FUN_0042bbd0`: that routine pushes `0x0042C590` into
`FUN_00449ed0`, stores its `EBX` context at the returned descriptor's `+0x20`,
then registers the descriptor through `FUN_00449b70`. `FUN_00449ed0` stores the
callback pointer at descriptor `+0x08`. The queue runner `FUN_00449c00`
executes it with `ECX = [descriptor + 0x20]` followed by `call [descriptor +
0x08]`; it reads the callback result from `EAX`. Thus the public entry takes
the context in `ECX` and returns the callee's `EAX` unchanged.

The direct callee, `FUN_0042c360`, is reported by Ghidra as
`undefined4 __stdcall FUN_0042c360(void)`, but its decompilation uses
`unaff_EDI` as the context and reads fields at `+0x30`, `+0x38`, and `+0x2D8`.
It returns `1`; its status-dependent work appends the `Spt Test`, file/ECL,
loading, quit, and position text records, changes the game-thread text color,
and calls `FUN_00463b2c` twice for status 3. The wrapper's `mov edi,ecx` is
therefore an ABI bridge: it converts the scheduler's ECX context to the
callee's otherwise implicit EDI input. The balanced EDI save/restore also
preserves the x86 nonvolatile register. The scheduler consumes the resulting
EAX status.

Do not promote this body to ordinary C++. The observed callback convention
requires a hidden EDI argument to the existing callee, while the scheduler
supplies its context in ECX; the target also forwards the callee's EAX result.
An ordinary MSVC function declaration cannot express the callee's EDI input.
The callback also needs an integer return for the scheduler's EAX status.
Implementing the register transfer with inline assembly would still be an
assembly bridge. The current naked body preserves the hidden input and return
value exactly, so the source remains unchanged.
