# Locale enumeration callback at `0x0045C651`

The callback parses each enumerated locale name into an LCID, then queries the
locale's country and language names through the `GetLocaleInfoA` function
pointer at `data_00477648`. It compares those names with the current country and
language strings, records exact and primary-language matches in
`data_00477628`, and stores selected LCIDs in `data_0047762C` and
`data_00477630`. A final language-name query and `CheckLocaleLanguageAt0045C5DC`
can set the final language-match bit. The callback returns the inverted state
bit 2, which controls whether `EnumSystemLocalesA` continues enumeration.

The callback receives one locale-name pointer on the stack and returns with
`RET 4` at `0x0045C86C`, so the C++ definition uses the stdcall callback ABI and
returns an integer. Ghidra's inferred `__thiscall` ECX parameter comes from the
call to the fastcall LCID parser; that parser ignores its ECX slot, so the
callback's actual API contract remains one stdcall string argument. Its only
entry reference is the callback address passed by `_GetLcidFromLangCountry` at
`0x0045C9D5`.

Ghidra's decompilation and disassembly support the state updates and control
flow. The C++ model retains the observed word-width OR for `0x304` and the
byte-width ORs for `0x200` and `0x100`; the candidate-LCID flag ORs remain
dword-width. Byte-exact output has not been checked.
