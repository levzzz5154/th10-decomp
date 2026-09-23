# `_GetLcidFromCountry` at `0x0045C93E`

This wrapper stores whether the current country string at `data_0047763C` has
exactly three characters, calls the `EnumSystemLocalesA` function pointer at
`data_00466058` with the stdcall callback at `0x0045C544` and flags `1`, then
checks the callback's match bit. If bit `0x4` is absent in the low byte of
`data_00477628`, it clears the full dword state value.

The wrapper has no arguments and ends with a plain `RET`, matching the direct
call from `_get_qualified_locale`. Its callback accepts one string argument and
ends with `RET 4` at `0x0045C5D9`. Ghidra disassembly at
`0x0045C93E..0x0045C974` supports the wrapper's dword flag store, byte-width
state test, and dword-width state clear.

The C++ is a semantic model; byte-exact output has not been checked.
