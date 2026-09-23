# Decimal text parser at `0x0045D746`

## Recovered behavior

`FUN_0045d746` parses a decimal byte string and writes the CRT's 12-byte
`_LDBL12` intermediate. The maintained source body is now ordinary C++ and
keeps the existing `asm_FUN_0045d746_0045d746` C-linkage symbol for its current
callers. It implements the observed state machine, including its accepted
`D`/`E` exponent markers, locale decimal separator, optional-sign mode,
end-pointer rollbacks, 25-byte digit staging, exponent saturation, and
rounding/trailing-zero handling.

The seven cdecl stack arguments are:

1. output pointer to the 12-byte intermediate;
2. an `int *` where the parser stores the address of the first unconsumed byte;
3. input byte string;
4. flag forwarded to the scaling helper to retain the low rounding word;
5. power adjustment added when no exponent value was parsed;
6. power adjustment subtracted when no decimal separator was seen;
7. flag enabling the parser's optional-sign state after a mantissa.

The second argument is an end pointer despite its recovered `int *` type. It
normally receives the first unconsumed byte. The parser deliberately rolls
back to the original input pointer after a sign or leading decimal separator
that is not followed by a number, while an invalid first character after
whitespace leaves the pointer at that first nonspace byte. The wrappers at
`0x0045D676`, `0x0045D6BB`, and `0x0045D701` pass local integers and discard
their contents; `0x0045DB86` forwards its caller's `int *`. The `0x00456674`
caller uses the returned status bits directly.

The output fields, in byte order, are:

| Offset | Size | Meaning |
| --- | ---: | --- |
| `0x00` | 2 | low guard/rounding word |
| `0x02` | 4 | low dword of the 64-bit significand |
| `0x06` | 4 | high dword of the 64-bit significand |
| `0x0A` | 2 | sign bit `0x8000` and 15-bit exponent |

The routine returns a 32-bit status in EAX: `0` for a finite in-range result,
`1` for underflow, `2` for overflow, and `4` when no number was converted.
Underflow and no-conversion results have zero significand and exponent bits,
with the sign bit retained; overflow writes the maximum exponent and the
normalized integer bit. The leading minus sign is ORed into the final
sign/exponent word for every status.

## Ghidra evidence and dependency ABIs

Live Ghidra analysis at `0x0045D746` reports a 1088-byte manifest region, a
`__cdecl` function with seven stack parameters, and five callers:
`0x00456674`, `0x0045D676`, `0x0045D6BB`, `0x0045D701`, and `0x0045DB86`. The
epilogue returns the word held at `[ebp-0x48]` in EAX. The parsed-input pointer
is stored through argument 2 at the common parse exit. The three wrappers
using `_ld12tod` or `_ld12told` confirm that argument 1 is a 12-byte floating
intermediate rather than a textual digit buffer.

The adjacent CRT converter `__ld12told` at `0x0045D5FA` reads the low guard
word at offset 0, the significand dwords at offsets 2 and 6, and the
sign/exponent word at offset 10. It passes the guard and significand to
`__RoundMan`, then writes the rounded 64-bit significand and sign/exponent to
the ten-byte x87 destination. This establishes the `_LDBL12` field layout
above.

The parser's helpers have standard cdecl stack ABIs:

- `0x0045685E`, `_isdigit(int) -> int`, receives each byte zero-extended;
- `0x00460872(char *digits, int count, uint32_t *words) -> void` turns the
  retained decimal digit bytes into the normalized 96-bit intermediate;
- `0x00460B90(uint32_t *words, uint32_t power, int retain_tail) -> void`
  scales that intermediate. Its third argument clears the low word at offset
  0 when zero and leaves it available when nonzero.

The source also preserves the observed stack-cookie check through the
fastcall helper at `0x00458EA5`. No build, probe, or test was run.

## Region integration

The semantic function occupies `0x0045D746..0x0045DB54` (1039 bytes). The
following byte is a retail NOP at `0x0045DB55`; the next 48 bytes are the
12-entry absolute jump table formerly used by the parser's indirect state
dispatch. Both are retained as separate padding/data regions and in
`src/data/text_0045.cpp`; the C++ `switch` replaces the dispatch at runtime.
The C++ output and exact code generation remain unverified.
