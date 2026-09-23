# `_strncmp` at `0x00452F80`

## Recovered interface

The existing C-linkage symbol is `asm_strncmp_00452f80`, with `__cdecl` ABI.
Ghidra identifies the function as:

```c
int __cdecl _strncmp(char *_Str1, char *_Str2, size_t _MaxCount)
```

The readable body keeps that linker symbol and ABI. It compares bytes as
unsigned values and returns exactly `-1`, `0`, or `1`.

## Behavior and evidence

Ghidra MCP analysis of `th10.exe` at `0x00452F80` reports the function body as
`0x00452F80..0x00452FB8`, three parameters, and no callees. The disassembly
shows `_MaxCount` loaded from `[EBP+0x10]`; zero skips directly to a zero return.
For a nonzero count, `REPNE SCASB` finds the first NUL in `_Str1` or exhausts
the count, then `REPE CMPSB` compares `_Str1` and `_Str2` through the first
mismatch or that bound.

At the comparison exit, Ghidra shows `CMP AL,[EDI-1]` followed by unsigned
`JA`. Here `AL` is the last byte read from `_Str2`, while `[EDI-1]` is the last
byte read from `_Str1`. The branch sequence returns `-1` when the second byte
is greater, `1` when the first byte is greater, and `0` when equal. This
establishes unsigned-byte ordering and sign-only results, including the NUL
terminator in the bounded comparison.

Ghidra reports these callers: `FUN_00420dd0` (`0x00420DD0`),
`FUN_0043d250` (`0x0043D250`), `FUN_0043d390` (`0x0043D390`),
`FUN_00455fe7` (`0x00455FE7`), and `FUN_00458b53` (`0x00458B53`). The source
also has a direct declaration and uses in `version_list.cpp`.

## Exactness status

The C++ expresses the recovered comparison and return behavior. Byte-exact
equivalence to the 57-byte retail region has not been verified; no build or
binary comparison was performed for this recovery.
