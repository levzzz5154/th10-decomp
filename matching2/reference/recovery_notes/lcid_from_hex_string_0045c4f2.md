# `_LcidFromHexString` at `0x0045C4F2`

Ghidra identifies a 53-byte Visual Studio 2003 Release helper with signature
`int __fastcall _LcidFromHexString(undefined4, char *)`. The first argument
occupies ECX but is ignored; the input pointer is in EDX and the result is
returned in EAX. Xrefs show calls at `0x0045C558`, `0x0045C60F`,
`0x0045C665`, and `0x0045C883`.

The function scans bytes through the first NUL. It adjusts lowercase ASCII
`a` through `f` by `-0x27` and uppercase `A` through `F` by `-7`, then folds
each sign-extended byte into a 32-bit accumulator using
`(accumulator - 3) * 16 + value`. The accumulator therefore wraps at 32 bits.
The comparison instructions are signed. A non-hex byte is not rejected or
skipped: it remains unchanged, is sign-extended, and participates in the same
accumulator recurrence. This preserves the retail behavior instead of using
a validating standard-library parser.

The source candidate is
`matching2/msvc/src/unidentified/LcidFromHexString_0045c4f2.cpp`. It models
the ignored ECX slot and EDX string pointer with an ordinary `__fastcall`
definition, and uses unsigned accumulator arithmetic to retain EAX
wraparound.

## Status and integration

The C++ fastcall definition now owns the semantic region using decorated
symbol `@asm_LcidFromHexString_0045c4f2@8`. The shared declaration in
`asm_symbols.hpp` now describes ECX and EDX correctly, so the existing four
inline-assembly callers resolve the fastcall symbol while retaining their
existing instructions. The old cdecl symbol remains in the manifest symbol
table and in `previous_record` as a historical alias.

No build, probe, or test was run; byte exactness is unverified.
