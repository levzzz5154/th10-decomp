# Multibyte character search at `0x0046227B`

The body at `0x0046227B..0x004622F5` is a cdecl multibyte character search.
Its source now expresses the loop and its locale-dependent single-byte and
double-byte cases as ordinary C++.

## Ghidra evidence

Live Ghidra identifies the entry as
`uint* __cdecl FUN_0046227b(uint* text, uint character)`. Its only caller is
`FUN_00461f31` at `0x00461F31`; that caller pushes the character and text
pointer, calls `0x0046227B`, then removes the eight argument bytes. The direct
callees are `__getptd` (`0x00456357`), `___updatetmbcinfo` (`0x0045CF49`), and
the byte-search helper at `0x00452730`.

The function reads the thread locale pointer at thread-data offset `0x60`.
When it differs from the global locale pointer at `0x00497F94`, the update
helper returns the current locale in EAX. The locale dword at offset `+8`
selects the ordinary byte-search path. Otherwise, a flag at `locale + 0x1D +
first_byte` marks lead bytes: unmarked bytes are compared directly, while a
marked byte is paired with the following byte and compared as a big-endian
16-bit character. A trailing NUL byte cannot complete a pair. A search for
zero returns the string terminator; other misses return null.

The readable entry is now named `FindMultibyteCharacter_0046227B`; the
manifest uses `_FindMultibyteCharacter_0046227B` as its canonical symbol.
Existing assembly callers still target `_asm_FUN_0046227b_0046227b`, which the
source maps to the semantic entry with a linker fallback. The same source file
also emits the separate `0x00452720` helper under
`_asm_FUN_0046227b_part_00452720`; that assembly body is unchanged because
`0x00452730` branches to it. The rewritten source calls the updater and byte
search through typed function-pointer views because their shared assembly
declarations do not describe their return values.

No build, probe, or test was run, so generated-code equivalence is unverified.
The manifest marks this region semantic and preserves the prior assembly row
as `previous_record`; its canonical and legacy symbols both resolve to the
retail entry. Generated-code equivalence remains unverified.
