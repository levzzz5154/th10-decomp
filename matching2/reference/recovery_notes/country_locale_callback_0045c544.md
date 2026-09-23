# Country locale callback at `0x0045C544`

The callback parses the enumerated locale-name string into an LCID and queries
its country name through the `GetLocaleInfoA` function pointer at
`data_00477648`. The requested locale-info type is `7` when the current country
text at `data_0047763C` has exactly three characters, and `0x1002` otherwise.
If the returned country name matches and the LCID's low word is absent from the
ten-word table at `data_0046BD3C`, the callback sets bit `0x4` in
`data_00477628` and stores the LCID in `data_00477630` and `data_0047762C`.
An unsuccessful locale-info query clears the match state and returns `1`;
otherwise it returns `~(state >> 2) & 1`.

The callback accepts one locale-name pointer and returns a BOOL-like integer.
Its epilogue at `0x0045C5D9` is `RET 4`, so the C++ definition uses stdcall.
Ghidra infers an ECX input because that value is passed to the fastcall LCID
parser, whose ECX slot is unused. `_GetLcidFromCountry` passes this callback to
`EnumSystemLocalesA` at `0x0045C954`.

Ghidra's decompilation, callback epilogue, and wrapper call support the semantic
model. Byte-exact output has not been checked.
