# Decimal conversion record adapter at `0x00460E41`

## Recovered behavior

`FUN_00460e41` accepts the low and high dwords of a binary64 value, an `int[4]`
result record, and a caller-owned digit buffer. It converts the input to the
retail ten-byte x87 extended representation with `___dtold`, passes a
precision/count argument of 17 to `FUN_00461841`, copies the resulting
NUL-terminated text into the caller's buffer with `FUN_0045bd80`, and returns
the result-record pointer.

The four result dwords are written in this order: ASCII sign (`' '` or `'-'`),
sign-extended decimal exponent, the integer status returned by
`FUN_00461841`, and the caller's digit-buffer pointer. The formatter's local
record has a 16-bit exponent at offset 0, sign at offset 2, digit count at
offset 3, and digit text starting at offset 4. The twenty-byte digit field
matches the retail 24-byte scratch area; the call uses precision 17, leaving
room for the formatter's rounding digit and terminator.

The extended intermediate is represented as two 32-bit significand words and
one 16-bit sign/exponent word. This passes the actual ten-byte representation
through the existing helpers without treating MSVC `long double` as an
80-bit type or asking the compiler to pass a ten-byte aggregate by value.
`FUN_00461841` receives those three words as separate cdecl parameters, then
the precision, flags, and output pointer, matching its six stack arguments.

## Ghidra evidence and ABI

Live Ghidra analysis of `0x00460E41` reports a 120-byte function,
`int * __cdecl` return, and four stack arguments. Its callers are
`0x0045DDAA`, `0x0045DEB6`, and `0x0045DF1E`; each pushes the result pointer,
the high input dword, then the low input dword, with the digit-buffer pointer
already on the stack. The callee ends in plain `RET`, so caller cleanup matches
cdecl.

The retail body calls `___dtold` with pointers to the two contiguous binary64
words and to a ten-byte local; Ghidra confirms the helper is cdecl with two
pointer parameters. It writes the low significand word, high significand
word, and sign/exponent at offsets 0, 4, and 8. The `0x00461841` call copies
those ten bytes into its first three stack slots, then receives precision
`0x11`, flags `0`, and the formatted-record pointer. Ghidra confirms its
six-argument cdecl ABI (`uint`, `uint`, `ushort`, `int`, `byte`, `short *`);
its EAX return is one for finite values (including zero) and zero for its
infinity/NaN spellings. Its output fields
are exponent, sign, digit count, and digits as described above. The
`FUN_0045bd80` helper is a two-pointer cdecl string copy and returns the
destination pointer.

The wrapper and these two conversion helpers pass and manipulate the extended
value as integer words; the adapter does not evaluate it as a C++ floating
value. This keeps the retail 80-bit representation intact and avoids relying
on MSVC's 64-bit `long double`. The C++ source declares the two helper
prototypes directly from the observed stack ABI. The retail epilogue decodes
its saved cookie and calls the fastcall `__security_check_cookie` helper; the
C++ body retains an explicit saved-word check through that helper, using the
saved local's address as its XOR anchor instead of depending on an
EBP-relative slot.

## Verification status

The source body is now ordinary C++ with no inline assembly. The manifest row
is promoted to semantic, its canonical cdecl symbol is recorded, and the old
assembly label is retained as a linker fallback. The shared raw-label
declaration now carries the four-argument cdecl type. No build, probe, or test
was run, so code generation and emitted bytes remain unverified.
