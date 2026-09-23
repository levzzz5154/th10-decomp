# `_setSBCS` semantic model at `0x0045CD85`

The 41-byte manifest row is now ordinary C++ and marked `semantic`. The prior
ASM row remains in `previous_record`; its external symbol is unchanged. The
shared symbol header exposes the table and multibyte-state aliases used by the
model.

## Ghidra evidence

Ghidra identifies a no-argument `void __cdecl` routine with a plain `RET` and
one direct caller at `0x0045D12C` in `FUN_0045CFB8`. Its listing preserves EDI,
clears 64 dwords and one trailing byte at `0x00497FA0`, clears dwords at
`0x004980A4`, `0x00497F98`, and `0x00497F90`, then clears three dwords starting
at `0x004980B0`.

## Recovered behavior

The C++ model keeps those write widths and order with volatile accesses. The
first operation zeros 257 bytes; the remaining stores reset the associated
locale and multibyte state words. It has no private register inputs or helper
calls.

## Limits

This is a behavioral model; emitted bytes have not been compared with retail.
No build, probe, or test was run.
