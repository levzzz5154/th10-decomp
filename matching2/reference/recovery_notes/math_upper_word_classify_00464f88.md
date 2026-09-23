# Binary64 upper-word classifier at `0x00464F88`

Ghidra analysis of the current `th10.exe` image identifies a 22-byte ordinary
`__cdecl` function. Its decompilation takes two 32-bit words, ignores the first,
and applies this rule to the second:

```cpp
const unsigned int exponent = high_word & 0x7FF00000u;
return exponent == 0x7FF00000u ? high_word : exponent;
```

The listing confirms that the function reads `[esp+8]`, the second stack
argument, masks it with `0x7FF00000`, and returns either the mask or that
original word. In its caller at `0x00463BF0`, Ghidra shows `FST qword ptr [esp]`
before the call. That lays out the low and high halves as the first and second
arguments, so the value classified here is the high 32-bit word of the stored
binary64 value. When the exponent field is all ones, the helper preserves the
whole high word, including the sign and high significand bits; otherwise it
returns only the exponent field.

The source uses integer operations and avoids floating-point library helpers.
Its existing C symbol name remains `asm_FUN_00464f88_00464f88`. The active
manifest marks this region semantic and retains the former assembly row in
`previous_record`. Byte-for-byte code generation has not been probed or verified.
