# `_strncnt` at `0x00461ADD`

## Live Ghidra evidence

The active Ghidra program is `/th10.exe` (32-bit x86 PE). At `0x00461ADD`,
Ghidra reports a 28-byte leaf through `0x00461AF8`, named `_strncnt`, with no
callees. The only incoming references are two calls in `FUN_00461af9`, at
`0x00461B67` and `0x00461B7A`.

The Ghidra library signature is `size_t __cdecl _strncnt(char*, size_t)`,
but its parameter storage is inconsistent with both the instructions and the
call sites. The function reads its sole stack argument from `[ESP+4]` into
`ECX`; the scan pointer arrives in `EAX`. Each call site pushes only a count,
moves a string pointer into `EAX`, calls this entry, then pops the count. The
result is returned in `EAX`; `RET` leaves caller cleanup in place. The second
Ghidra stack parameter is therefore not passed at these callers. Ghidra's
decompilation exposes the actual pointer as the phantom register variable
`in_EAX`.

The caller's source is
`matching2/msvc/src/unidentified/FUN_00461af9_00461af9.cpp`. At each of the
two call sites it has the same push / move-to-`EAX` / call / pop sequence as
the live listing. No other xrefs to `0x00461ADD` were reported.

## Behavior

For a valid readable string and a 32-bit bound `n`, the return value is the
number of non-NUL bytes before the first NUL, capped at `n`:

```text
min(strlen(text), n)
```

This follows from the instruction sequence: decrement `ECX`, compare the byte
at `[EAX]` with zero, advance `EAX` only for nonzero bytes, and stop on NUL or
when the bound reaches zero. The final arithmetic returns the consumed count.
When `n == 0`, the routine returns zero without reading through `EAX`. With a
positive bound, it reads at least the first byte; a null or unreadable pointer
therefore faults. It does not add a null check. If no NUL occurs within the
bound, it returns the bound.

## Recovery decision and symbols

The observed entry ABI combines an `EAX` input with a cdecl stack argument.
An ordinary typed MSVC x86 C++ function cannot declare that register-plus-stack
parameter placement. The source therefore retains the naked assembly body for
now. A semantic C++ helper is straightforward, but using it requires adapting
both call sites in the naked caller to pass the pointer and bound as ordinary
cdecl arguments; changing a symbol alias alone would break the observed ABI.

The current raw C-linkage symbol is `_asm_strncnt_00461add` (from
`asm_strncnt_00461add` in the source and `asm_symbols.hpp`). Ghidra's label
`_strncnt` is the recovered target name, not the current linker symbol. If the
callers are later adapted, a suitable address-qualified semantic symbol is
`_strncnt_00461add`; it must replace the raw calls rather than receive a direct
alias while they keep the register-based convention.

The assembly source lists the retail instructions directly. No rebuild or
byte comparison was run in this recovery, so linked placement/codegen is not
verified. A normal C++ implementation and the required caller edits also
remain unbuilt and unverified.
