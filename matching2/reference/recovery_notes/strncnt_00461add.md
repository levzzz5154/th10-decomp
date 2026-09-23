# `_strncnt` at `0x00461ADD`

## Ghidra identification

Live Ghidra MCP analysis of `th10.exe` identifies the region
`0x00461ADD..0x00461AF8` as the Visual Studio 2003 Release CRT helper
`_strncnt`, with the library prototype
`size_t __cdecl _strncnt(char *_String, size_t _Cnt)`. The analysis reports
one caller, `FUN_00461af9` at `0x00461AF9`, and no callees.

Ghidra's inferred parameter storage lists both prototype parameters on the
stack, but that does not match the instructions or call site. The disassembly
loads the only stack argument from `[ESP+4]` into `ECX`, scans bytes at the
address already in `EAX`, then computes the return value in `EAX`. The
decompiler also exposes this scan pointer as `in_EAX`.

The caller disassembly and existing source
`matching2/msvc/src/unidentified/FUN_00461af9_00461af9.cpp` confirm the
effective call form at both `0x00461B67` and `0x00461B7A`: push the count,
move the string pointer into `EAX`, call `_strncnt`, then pop the count in the
caller. The enclosing Ghidra function body is `0x00461AF9..0x00461E82`; its
source is one naked assembly function body. Thus the observed ABI is a string
pointer in `EAX`, one cdecl stack argument (`size_t count`), and a `size_t`
result in `EAX`. This register-plus-stack form is not representable by an
ordinary typed MSVC C++ function declaration.

## Recovered behavior

The instructions decrement the remaining count once per examined byte,
advance the input pointer only for non-NUL bytes, and stop at NUL or when the
bound is exhausted. The final arithmetic returns the number of non-NUL bytes
examined: `min(strlen(string), count)`. A zero count returns zero without
reading the string. Signedness is immaterial because each byte is only tested
for equality with zero.

## Recovery status

The source region remains assembly-backed because preserving its observed
EAX-plus-stack ABI requires a register-specific entry shim. No ordinary
MSVC C++ function type found in this recovery emits the string argument in
`EAX`. A standard typed helper is feasible if the caller is adapted: at both
call sites, push the count and string pointer as normal cdecl arguments, call
the helper, then discard both arguments. This changes the naked caller source
and its instruction layout, so it is outside this note-only recovery.

Byte-exactness for a C++ replacement and any caller adaptation remains
unverified; no build, probe, or test was run.
