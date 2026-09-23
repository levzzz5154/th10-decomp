# `___wtomb_environ` (`0x004610F4`)

Ghidra identifies this as a standard `int __cdecl(void)` helper with a
144-byte body ending at `0x00461183`. Its callers are `__getenv_lk` at
`0x0045E063` and `FUN_00461F31` at `0x00461F31`; both test its EAX status.
The latter invokes it at `0x00461F9E` while initializing the environment.

The function walks the wide-environment pointer table stored at `0x00477498`.
For each non-null entry it calls the `WideCharToMultiByte` import through the
IAT slot at `0x00466154`, using the active code page (`CP_ACP`), to obtain the
required byte count and then convert the NUL-terminated string. It allocates
the reported size through `_malloc` at `0x00452706` and passes the converted
string by address to `FUN_00461F31` with mode zero. If that helper reports a
negative result and leaves the pointer non-null, this function frees the
buffer. A failed size query, allocation, or second conversion returns `-1`;
otherwise the walk ends with `0`. A null first table entry therefore produces
success without processing any strings.

The API call is stdcall with eight arguments. `_malloc`, `_free`, and
`FUN_00461F31` use cdecl; the setter takes `(char**, int)`. The entry itself
has no arguments and preserves the normal callee-saved registers, so the body
is represented as ordinary C++ with no private calling convention. Its former
assembly label `_asm_wtomb_environ_004610f4` remains mapped to the same address
alongside the canonical `_WtombEnviron_004610F4` symbol for the existing
assembly callers.
