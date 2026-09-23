# Language locale callback at `0x0045C86F`

The callback parses the enumerated locale name into an LCID, asks the
`GetLocaleInfoA` function pointer at `data_00477648` for that locale's language
name, and compares it with the current language text at `data_00477644`. Exact
matches for a non-three-character language and prefix matches for a longer
locale name are checked with `CheckLocaleLanguageAt0045C5DC`. A successful
match sets bit `0x4` in `data_00477628` and stores the LCID in both
`data_00477630` and `data_0047762C`. A failed locale-info query clears the match
state and returns `1` so enumeration continues; other paths return the
inverted state bit 2 as the enumeration continuation value.

The function takes one locale-name pointer and returns a BOOL-like integer.
Its epilogue at `0x0045C93B` is `RET 4`, establishing the stdcall callback
cleanup. Ghidra's inferred ECX `this` value is forwarded to the LCID parser,
whose ECX fastcall slot is ignored. The C++ wrapper therefore calls the parser
with an explicit zero ECX value and exposes the correct stdcall callback
signature to `_GetLcidFromLanguage` at `0x0045CA34`.

Ghidra's decompilation and disassembly support the recovered comparisons,
state update, and callback ABI. Byte-exact output has not been checked.
