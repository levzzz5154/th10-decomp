# `_strcmp` semantic model at `0x0045BF30`

`matching2/msvc/src/unidentified/strcmp_0045bf30.cpp` now expresses the retail
entry as an ordinary typed `__cdecl` function. It reads each pair of bytes as
unsigned values, returns `-1` when the left byte is smaller, `1` when it is
larger, and `0` when both strings end together. The C-linkage symbol
`asm_strcmp_0045bf30` is retained so existing assembly callers can keep calling
the same entry.

## Ghidra evidence

Ghidra identifies one Visual Studio 2003 Release `_strcmp` function at
`0x0045BF30`. Its body consists of `0x0045BF30..0x0045BF72` and
`0x0045BF74..0x0045BFB7`, totaling 135 instruction bytes. The retail code uses
alignment-specific byte, word, and dword reads, compares bytes unsigned, and
returns a normalized `-1`, `0`, or `1` result.

`0x0045BF74` is an internal mismatch-result block, not a second callable
function: it converts the comparison carry flag to `-1` or `1` and returns
through the caller's original return address. `0x0045BF7C` is another internal
path in the same function. Ghidra's external call references enter at
`0x0045BF30`; the split `asm_strcmp_part_0045bf74` name in the previous source
was a source-layout device for the disjoint body fragment.

## Manifest and symbol integration

The manifest now covers the retail address span `0x0045BF30..0x0045BFB7` as
one semantic row of 136 bytes under the retained C-linkage symbol
`_asm_strcmp_0045bf30`. Its `previous_record` keeps the former entry row, and
`previous_records` retains both disjoint assembly fragments and the intervening
one-byte NOP padding row. The trailing `CC` padding at
`0x0045BFB8..0x0045BFBF` remains a separate data row. The shared header exposes
the typed cdecl signature; the obsolete interior fragment and branch-target
aliases have been removed because no other source uses them.

The 136-byte figure describes the retail address span, not the emitted size of
this C++ implementation. Compiler output and byte equivalence are unverified.
The byte loop also does not reproduce the retail word/dword read footprint, so
memory access behavior near a string terminator may differ. No build, probe, or
test was run for this recovery.
