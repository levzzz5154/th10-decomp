# 0x0042BF30 allocation and callback setup ABI audit

Audited read-only against the connected Ghidra program `th10.exe` on
2026-09-23. The live manifest has one 67-byte assembly region at
`0x0042BF30..0x0042BF72`, owned by
`src/unidentified/FUN_0042bf30_0042bf30.cpp`.

## Boundary and references

Ghidra's address-level disassembly of 67 bytes yields 27 instructions. The
entry begins with `push ebx`; both return paths terminate at `0x0042BF6E` or
`0x0042BF72`. The adjacent source overlay records 11 bytes of `CC` padding at
`0x0042BF25..0x0042BF2F` and 13 bytes of `CC` padding at
`0x0042BF73..0x0042BF7F`, matching the entry and end boundaries.

The current Ghidra database does not define a function at `0x0042BF30`
(`get_function_by_address` reports no function), so its function-caller query
cannot enumerate callers. Address-level xrefs report no references to the
entry, and a program-wide scan of 124,200 decoded instructions found no `CALL`
whose operand is `0x0042BF30`. No caller is known from the current listing.

## Behavior and ABI

The function allocates `0x2E4` bytes with the cdecl entry at `0x00452493`,
cleans the pushed size from the stack, and tests the returned pointer. For a
non-null pointer it copies EAX into EDX and calls `0x0042BB30`. Ghidra reports
that callee as `__fastcall` with the state pointer in its second parameter
(EDX); the current semantic source model also marks its first parameter as
unused. Its body initializes the 0x2E4-byte state, records it in
`data_00477844`, and returns the state pointer, which this function keeps in
EBX.

The function then calls `0x0042BBD0` without stack arguments while retaining
the state in EBX. That callee's Ghidra prototype is `__stdcall(void)`, but its
body reads the hidden state from EBX, creates/registers callbacks `0x0042C580`
and `0x0042C590`, and stores their handles in the state. It returns zero in
EAX in the inspected body. If EAX is zero, `0x0042BF30` returns the state in
EAX. If EAX is nonzero, it calls `0x0042BC30` with the state pushed on the
stack; that callee uses `ret 4` to pop the argument. The caller then frees the
state via the cdecl entry at `0x004524A1` and returns zero. EBX is restored on
both exits.

Direct callees and current source aliases:

| Address | Role | Source/link symbol |
| --- | --- | --- |
| `0x00452493` | allocate `0x2E4` bytes | `asm_operator_new_00452493` |
| `0x0042BB30` | initialize state; state pointer in EDX | `asm_FUN_0042bb30_0042bb30` |
| `0x0042BBD0` | register callbacks; hidden state input in EBX | `asm_FUN_0042bbd0_0042bbd0` |
| `0x0042BC30` | release state; one stack argument, callee pops 4 bytes | `asm_FUN_0042bc30_0042bc30` |
| `0x004524A1` | free state | `asm_free_004524a1` |

The region symbol is `asm_FUN_0042bf30_0042bf30` (COFF symbol
`_asm_FUN_0042bf30_0042bf30`). The helper aliases and their `VA_...` macros are
declared in `matching2/msvc/include/asm_symbols.hpp`.

## Standard-C++ blocker

The decisive ABI input is EBX at the call to `0x0042BBD0`: the caller places
the state there, and the callee consumes it there despite declaring no
parameter. Standard C++ has no way to declare or guarantee this hidden
register argument on MSVC x86. A normal C++ call would preserve EBX as a
callee-saved register, but cannot require the state pointer to be in it. The
`0x0042BB30` call also uses EDX for its state parameter. Reproducing the
observed call sequence therefore requires explicit assembly or a separately
engineered register-binding wrapper, so this entry remains naked assembly.
