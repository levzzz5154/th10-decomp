# `___isctype_mt` semantic model at `0x00455752`

The 119-byte region now has an ordinary C++ model and is marked `semantic` in
the manifest. Its previous ASM record and external symbol are preserved.

## Ghidra evidence

Ghidra identifies the routine as `int __cdecl ___isctype_mt(void*, int, int)`.
The disassembly reads those three arguments from the stack, returns an integer
in EAX, and makes one cdecl helper call whose seven arguments are removed by
the caller. There are no private entry-register inputs.

The one-byte classification path reads a 16-bit ctype value from the locale
table at offset `+0x48`. For larger values, the listing checks the high byte
against the locale's DBCS lead-byte flags, builds a one- or two-byte sequence,
and calls `___crtGetStringTypeA` at `0x0045A25D`. Other direct callers include
`_atol`, `_tolower_mt`, `_isspace`, `_isdigit`, `_isxdigit`, and the CRT
classification accessors at `0x004567AB..0x00456A08`.

Ghidra's decompiler assigns shifted types to the helper's parameters. The C++
declaration follows the call-site stack order: info type, source, source
length, output word, code page, locale ID, and strict flag. The helper's
assembly definition and shared header now use that same cdecl interface.

## Recovered behavior

For values in the byte range (including the CRT's biased EOF table entry), the
routine returns `ctype[character] & mask`. For larger values, it checks
whether the high byte is a DBCS lead byte; if so, it classifies the high byte
followed by the low byte, otherwise it classifies only the low byte. A failed
Windows string-type conversion returns zero. Successful conversion returns
the resulting 16-bit classification flags masked by the caller's mask.

## Limits

The behavior follows the Ghidra body and its call-site dataflow. Emitted bytes
have not been compared with retail. No build, probe, or test was run.
