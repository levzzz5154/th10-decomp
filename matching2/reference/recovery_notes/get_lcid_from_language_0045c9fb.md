# `_GetLcidFromLanguage` at `0x0045C9FB`

This routine prepares three global locale values before enumerating the system's
installed locales. It reads the current locale string through `data_00477644`,
stores whether its length is exactly three in `data_00477634`, and stores either
`2` or the primary-language length in `data_00477640`. It then calls the
`EnumSystemLocalesA` function pointer at `data_00466058` with flag `1` and the
callback at `0x0045C86F`. It tests bit `2` in the low byte of the match-state
value at `data_00477628`; if that bit is clear, the routine clears the full
dword state.

The entry point has no arguments and uses a plain cdecl return. The callback
uses the stdcall convention and consumes one string argument (`RET 4` in its
existing assembly body); the C++ wrapper converts its existing symbol address
to that callback type when passing it to the API pointer. `strlen` and
`_GetPrimaryLen` remain calls to their existing recovered helpers.

Ghidra's disassembly and both callers at `0x0045CADB` and `0x0045CB14` support
the entry ABI and control flow. The ordinary C++ implementation is a semantic
recovery; byte-exact output has not been checked.
