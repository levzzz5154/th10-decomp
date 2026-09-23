# `0x004559B4` `___lc_strtolc` semantic model

The ordinary C++ model is in
[`lc_strtolc_004559b4.cpp`](../../msvc/src/unidentified/lc_strtolc_004559b4.cpp).
It keeps the C-linkage `asm_lc_strtolc_004559b4` symbol with a recovered
`int __cdecl(char* fields, const char* text)` signature.

## Behavior

The function clears a `0x90`-byte destination, then splits the input at the
separators `_`, `.`, and `,`. It stores up to three components at offsets
`0x00`, `0x40`, and `0x80`. The first two components must be shorter than
`0x40` bytes; the final component must be shorter than `0x10`. The first
separator cannot be `.`, the second cannot be `_`, and the final component may
end only at NUL or comma. Empty components and other separator sequences
return `-1`; a comma or input terminator ends parsing successfully with return
`0`.

A leading period followed by a nonempty string is a special form: up to 15
bytes after the period are copied into the field at offset `0x80`, that
field's final byte is forced to NUL, and the function returns `0`. Empty input
also returns `0` after clearing the destination.

## ABI and call graph

Ghidra shows `fields` at `[ESP+4]`, `text` at `[ESP+8]`, EAX carrying the
status, and a plain `RET`; the caller removes the two stack arguments. No
private register inputs are used. The direct caller is `FUN_00455BF3`, at call
site `0x00455C99`. Direct callees are `_memset` at `0x0045BED0`, `_strncpy` at
`0x00452960`, and `_strcspn` at `0x0045BE80`.

## Model status

The active manifest now marks `0x004559B4` as semantic and retains the prior
assembly row in `previous_record`. Its C-linkage entry and helper calls match
the recovered cdecl ABI. This is a behavior-level model; retail byte identity
and exact compiler output remain unverified. No build, probe, or test was run.
