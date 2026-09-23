# `__close` at `0x0046218A`

## Ghidra body and ABI

The live `th10.exe` analysis identifies `FUN_0046218a` as `int __cdecl
FUN_0046218a(uint file)`. The entry reads its sole descriptor from `[EBP+8]`
and returns through a plain `RET`, so the caller owns stack cleanup. Its
semantic source model now has the same one-argument cdecl boundary and returns
the `__close_lk` result in EAX.

Ghidra lists one caller, `FUN_0046140c`. At `0x00461429` it pushes the
descriptor from `[ESI+0x10]`, calls `0x0046218A` at `0x0046142C`, and later
adjusts ESP. The caller batches cleanup for this and its preceding cdecl calls;
the descriptor push and plain callee `RET` agree with the cdecl signature.

## Behavior recovered

`__close` first rejects a descriptor at or above `data_004991e4`, or whose
record flag byte at offset `+4` lacks bit 0. That path sets `errno` to 9,
clears `_doserrno`, and returns -1. Otherwise it locks the descriptor with
`_lock_fhandle`, re-reads the open flag, and either sets `errno` to 9 and
returns -1 if the flag cleared while locking, or calls `__close_lk(file)`.
The lock is released on either locked path. The table is grouped into 32-entry
blocks with records of stride `0x24` bytes; the recheck resolves the block
pointer again after locking, as the retail body does.

The source models release with a small C++ scope guard. It calls the existing
ordinary cdecl unlock helper `_FUN_0045F7B5(file)` directly. The retail body
calls the 8-byte wrapper at `0x00462201`, which obtains `file` from EBX and
forwards it as a cdecl stack argument to that helper; calling the helper
directly preserves the operation while avoiding that private register ABI.

## Dependencies and limits

Ghidra shows these relevant callees and contracts:

- `_lock_fhandle` at `0x0045F715`: one cdecl descriptor argument.
- `__close_lk` at `0x00462107`: one cdecl descriptor argument and an `int`
  result; its semantic source is already available.
- `_errno` at `0x00456AF2`: returns `int*`.
- `_doserrno` at `0x00456AFB`: returns `unsigned int*`.
- `_FUN_0045F7B5` at `0x0045F7B5`: one cdecl descriptor argument, unlocks the
  associated critical section.

The original function installs an SEH frame and uses its state word to release
the descriptor lock during exception unwinding. The C++ scope guard expresses
the cleanup behavior, but this is a semantic model: exception metadata and
retail byte identity have not been established. No build, probe, or test was
run.

The shared header and manifest now register `Close_0046218A` as the semantic
entry and preserve `_asm_close_0046218a` as the legacy alias. The separate
source region `0x00462209..0x00462224` remains as a raw assembly fragment in
the same translation unit. It contains the retail error/SEH tail that the
semantic entry now expresses directly; Ghidra shows no separate caller for
that fragment. Exception metadata and exact retail byte identity remain
unverified.
