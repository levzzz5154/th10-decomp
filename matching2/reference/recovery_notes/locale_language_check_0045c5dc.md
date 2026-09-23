# Locale language check at `0x0045C5DC`

Ghidra identifies a 117-byte `__cdecl` function with two stack arguments: an
LCID and a flag controlling an additional locale-string check. The function
calls the `GetLocaleInfoA` pointer at `0x00477648` with
`(locale_id & 0x3ff) | 0x400`, `LOCALE_IDEFAULTLANGUAGE` (`1`), a 120-byte local
buffer, and the buffer size. A failed API call returns zero.

On success, it parses the returned hexadecimal language identifier with
`_LcidFromHexString` at `0x0045C4F2`. A matching LCID returns one. A mismatching
LCID also returns one when the optional check flag is zero. Otherwise the
function compares the length of the current locale string at `0x00477644` with
the length of its leading ASCII-letter run. If those lengths match, it returns
zero; otherwise it returns one.

The ordinary C++ source calls the helpers with typed declarations: the parser
and primary-language counter use their fastcall register arguments, while
`strlen` is cdecl. The locale API pointer is read from its retail global slot.
The large stack buffer should retain the compiler security-cookie protection
under the project's normal compiler settings, but byte-for-byte output is
unverified because no build or probe was run.
