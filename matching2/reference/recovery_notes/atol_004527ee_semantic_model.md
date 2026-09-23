# `_atol` semantic model at `0x004527EE`

The 136-byte manifest row is now represented by ordinary C++ in
`src/unidentified/atol_004527ee.cpp`. Its manifest kind is `semantic`; the
previous ASM record and linker symbol are preserved in `previous_record`.
The shared declaration now records `long __cdecl(const char*)`.

## Ghidra evidence

Ghidra identifies the entry as the VS 2003 CRT `_atol` implementation and
decompiles it as `long __cdecl _atol(char*)`. The body spans
`0x004527EE..0x00452875` and ends in a plain `RET`. The only stack input is the
string pointer at `[ESP+0x0c]` after the two saved registers and the `getptd`
call. Its other dependencies are the per-thread-data accessor at `0x00456357`,
locale refresh at `0x00455ADE`, and ctype helper at `0x00455752`.

Ghidra's references are three direct calls from `__tzset_lk` (`0x00456CC5`,
`0x00456E13`, `0x00456E36`), one call from `FUN_004601A1` (`0x004601D6`), one
from `FUN_0045C377` (`0x0045C3DE`), and the five-byte `_atol` alias at
`0x00452876`.

## Recovered behavior

The routine obtains the thread's locale, refreshes it when it differs from the
global default locale, and skips leading whitespace using the locale ctype
table or the multithreaded ctype helper. It then accepts one optional `+` or
`-`, accumulates consecutive ASCII decimal digits, and stops at the first
non-digit. No digits produce zero. The retail arithmetic wraps at 32 bits on
overflow; the model uses unsigned accumulation and applies the sign modulo
2^32 before returning the signed result. It does not report range errors.

## Limits

This is a behavioral model with the ordinary cdecl entry ABI. Its emitted bytes
have not been compared with the retail body. No build, probe, or test was run.
