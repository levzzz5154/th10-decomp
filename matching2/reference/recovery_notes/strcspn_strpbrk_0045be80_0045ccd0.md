# `_strcspn` and `_strpbrk`, `0x0045BE80` and `0x0045CCD0`

Ghidra identifies the functions as the Visual Studio 2003 Release library
implementations of `_strcspn` and `_strpbrk`. Both use a 32-byte stack bitmap
to represent membership across all 256 possible byte values. They populate
the bitmap from the second argument until its NUL terminator, then scan the
first string until either a member byte or its NUL terminator is reached.

The ordinary C++ replacements in `src/unidentified/strcspn_0045be80.cpp` and
`src/unidentified/strpbrk_0045ccd0.cpp` use eight 32-bit words for that
bitmap. The byte is read as `unsigned char` before deriving both the word
index and bit index, preserving correct membership for bytes `0x80..0xFF`.
`strcspn` returns the count of initial nonmember bytes; `strpbrk` returns the
pointer to the first member byte, or null if the first string ends first.

Ghidra reports cdecl functions with the two string pointers on the stack and
plain `RET`. Its xrefs show `_strcspn` used by `FUN_00455FE7` and
`lc_strtolc_004559b4`; `_strpbrk` is used by `FUN_00455FE7`.

Both C-linkage definitions retain their existing `asm_...` names. The active
manifest marks both regions semantic and keeps their former assembly rows in
`previous_record`. No build, probe, or test was run, so byte-exact matching is
unverified.
