# Extended-float decimal conversion at 0x00461841

## Function and ABI

matching2/msvc/regions.json assigns this region to
src/unidentified/FUN_00461841_00461841.cpp, with a size of 668 bytes
(0x00461841..0x00461ADC). Live Ghidra reports the same body bounds. The entry
is a standard x86 cdecl function with six stack arguments:

```text
int __cdecl (uint32 significand_low, uint32 significand_high,
             uint16 sign_and_exponent, int requested_digits,
             uint8 flags, DecimalConversionRecord *output)
```

The result record has a 16-bit decimal exponent at offset 0, sign byte at 2,
digit count at 3, and digit text at 4. Its stack-cookie check is part of the
normal epilogue. Ghidra finds one direct caller, FUN_00460E41, at call site
0x00460E80; the adapter passes precision 17 and flags 0. The return value is
one for finite values (including zero) and zero for the infinity/NaN strings.

## Conversion behavior

The function first separates the sign and biased exponent. Zero significand
with exponent zero becomes a one-digit "0" record; retail also clears the
sign on negative zero. Exponent 0x7fff selects the special strings
1#INF, 1#IND, 1#QNAN, or 1#SNAN, with the sign kept in the separate
record field and the returned status set to zero.

For finite nonzero inputs, the ten significant bytes of the extended value
are placed at offset two in a three-dword, little-endian workspace. Integer
arithmetic estimates the base-ten exponent using 0x4d10, 0x4d, and
0xecbced0c; the value is then scaled by the corresponding power of ten. If
the scaled extended exponent is at least 0x3fff, the decimal exponent is
incremented and the 0x3ffbcccccccccccccccc extended value (0.8) is added as
the retail rounding bias.

The formatter clears the exponent field, shifts the 96-bit workspace eight
places left, adjusts its binary scale, and repeatedly multiplies by ten to
extract requested_digits + 1 decimal digits. The extra digit is the guard
digit. A guard digit below '5' drops trailing zeroes; a guard digit of '5'
or greater rounds upward, propagating through nines and incrementing the
decimal exponent when the carry passes the leading digit. If every kept digit
rounds to zero, the output is normalized to the one-digit zero record. Flag
bit 0 adds the decimal exponent to the requested digit count; nonpositive
adjusted counts also produce zero. The count is capped at 21 before digit
generation, matching the retail instruction sequence.

## Dependencies and integration status

The source expresses the formatter in ordinary C++ and contains no inline
assembly. Its calls to 0x00460817 (96-bit left shift), 0x00460845 (right
shift), and 0x004607B9 (96-bit addition) resolve to existing semantic C++
helpers. Scaling and extended addition still depend on the assembly functions
at 0x00460B90 and 0x0046095A; the former multiplies by powers from the
retail tables at 0x00473D60/0x00473EC0, while the latter performs extended
addition and normalization. Replacing those helpers is separate work.

The source defines the existing C-linkage symbol with the observed typed ABI
and declares its dependencies locally. `asm_symbols.hpp` now has the matching
typed entry declaration, and `regions.json` classifies the 668-byte region as
semantic while retaining the original linker symbol and recording the prior
assembly row.

No build, probe, or test was run, so source compilation and emitted code remain
unverified.
