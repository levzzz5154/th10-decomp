# `_GetLcidFromLangCountry` at `0x0045C975`

This routine prepares language and country match state before enumerating system
locales. It records whether the current language text at `data_00477644` and
country text at `data_0047763C` each have exactly three characters. It clears
the candidate locale ID at `data_0047762C`, then stores primary-language length
`2` for a three-character language or computes the length with
`_GetPrimaryLen`. It calls the `EnumSystemLocalesA` function pointer at
`data_00466058` with flags `1` and the callback at `0x0045C651`. After callback
processing, it reads one dword snapshot from `data_00477628`, checks bits
`0x100` and `0x200` in its high byte and the low three bits in its low byte,
then clears the full dword at `data_00477628` unless both high match bits and
at least one low state bit are present.

The entry point takes no arguments and returns with a plain `RET`; the two
callers at `0x0045CAD4` and `0x0045CB0D` issue direct calls without stack
arguments. The locale-enumeration callback uses the stdcall one-string callback
shape and its existing body ends with `RET 4`. Ghidra reports an ECX input on
that callback because it forwards ECX to the fastcall locale parser, whose ECX
slot is ignored; the C++ wrapper passes its existing symbol address through a
stdcall callback pointer type.

Ghidra's disassembly at `0x0045C975..0x0045C9FA`, the direct callers, and the
callback disassembly support the recovered control flow and ABI model. The C++
implementation is semantic; byte-exact output has not been checked.
