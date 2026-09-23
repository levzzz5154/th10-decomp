# ASCII case comparison helpers (`0x004603D0`, `0x004617E0`)

## Recovered behavior

`___ascii_stricmp` at `0x004603D0` (78 bytes) compares two NUL-terminated
byte strings after folding ASCII `A` through `Z` to lowercase. It returns
`-1` when the folded left byte is less, `1` when it is greater, and `0` when
the strings compare equal through their terminators.

`___ascii_strnicmp` at `0x004617E0` (97 bytes) applies the same comparison to
at most the requested number of bytes. A zero count returns `0`. Equal NUL
terminators also end the comparison early. Both implementations treat bytes
as unsigned and leave bytes outside ASCII uppercase unchanged.

The readable models are in
`matching2/msvc/src/unidentified/ascii_stricmp_004603d0.cpp` and
`matching2/msvc/src/unidentified/ascii_strnicmp_004617e0.cpp`. They retain
the existing C-linkage cdecl symbols and take their arguments from the
ordinary stack ABI.

## Evidence and callers

Live Ghidra decompilation identifies the functions as `___ascii_stricmp`
and `___ascii_strnicmp`, with cdecl signatures `(char*, char*)` and
`(char*, char*, size_t)`. The assembly reads the arguments from the stack,
preserves EBX/ESI/EDI, folds only the ASCII uppercase interval, and produces
the three-way ordering above. Ghidra xrefs show the first helper called by
`__stricmp` and `__store_winword` (including call sites at `0x0045AC5D` and
`0x0045ACC4`); the bounded helper is called by `__strnicmp`.

The current C++ `__stricmp` and `__strnicmp` wrappers route to these helpers
when the locale code page is zero. The legacy semantic reference provides
the higher-level `__stricmp` wrapper and representative case-insensitive
use sites in `platform/window.cpp` and `archive/dat.cpp`; it does not contain
these internal ASCII helper bodies.

## Status

The two source bodies no longer contain inline assembly. The active manifest
marks both regions semantic and retains their former assembly rows in
`previous_record`; the existing C-linkage symbols remain unchanged. Exact byte
matching remains unverified. No build, probe, or test was run for this recovery.
