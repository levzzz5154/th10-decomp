# Decimal digit formatter at `0x00460D10`

The 119-byte `__fptostr` routine is represented as C++ that copies the
requested digits from a decimal-conversion record, rounds using the next digit,
updates the exponent on a carry past the leading digit, and removes its
temporary leading zero when no exponent carry occurs.

## Ghidra evidence and effective ABI

Live Ghidra bounds the body at `0x00460D10..0x00460D86`. It uses a standard
EBP frame and ends in a plain `RET`. The instructions read the output buffer
from `[EBP+8]`, the signed digit count from `[EBP+0xC]`, and the conversion
record pointer from `[EBP+0x10]`. The record's digit-string pointer is at
`+0x0C`; a carry increments the integer at `+4`.

Ghidra's inferred signature includes a fourth `STRFLT` argument, but the body
never reads `[EBP+0x14]`. Current disassembly confirms that each call site
pushes exactly three fresh arguments at `0x0045DDCF`, `0x0045DED4`, and
`0x0045DF3C`. In push order these are the conversion-record pointer, output
buffer length, and output pointer, so the callee observes `(output, length,
record)` at `[EBP+8]`, `[EBP+0xC]`, and `[EBP+0x10]`. The apparent fourth stack
word is the first argument left by each caller's preceding four-argument
conversion call. The body has three effective arguments: output pointer,
signed digit count, and conversion-record pointer.

The callers are `FUN_0045dd85`, `FUN_0045de91`, and `FUN_0045def8`. None reads
the return register after this call; each later performs caller-side cleanup
for the accumulated cdecl arguments. The model therefore returns `void`;
Ghidra's inferred `errno_t` is not supported by any caller use. The raw body
does leave the output pointer in EAX on its normal paths (the non-carry path
gets it from `_memmove`, and an all-nines carry reaches the leading byte), so
the `void` model does not preserve that otherwise-unused return register
value. If that result becomes part of a typed interface, the shared prototype
should be revisited. The direct callees are `asm_strlen_00456720` and
`asm_memmove_00453280`, both already represented by semantic C++ sources.

## Record and rounding behavior

The record fields used here match `DecimalConversionRecord_00460E41`'s four
output words: sign at `+0`, exponent at `+4`, status at `+8`, and digit-string
pointer at `+0x0C`. The formatter writes a temporary `'0'` before the digits,
copies `digitCount` characters, and writes `'0'` for each missing character
after the source terminator. Negative counts skip copying and rounding; a zero
count still rounds based on the first source character. A next digit of `'5'`
or greater propagates through trailing nines. If that changes the temporary
leading byte to `'1'`, the exponent is incremented; otherwise the temporary
byte is removed with `strlen` and `memmove`.

The canonical C-linkage symbol is `_Fptostr_00460D10`. The existing raw
assembly symbol `_asm_fptostr_00460d10` remains in the manifest symbol map at
the same address for the three assembly callers.

The C++ behavior and symbol routing have not been build-verified or compared
byte-for-byte with retail. No build, probe, or test was run.
