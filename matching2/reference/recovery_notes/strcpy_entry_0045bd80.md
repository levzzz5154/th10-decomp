# String copy entry at `0x0045BD80`

`FUN_0045bd80_0045bd80.cpp` now expresses the callable entry as ordinary C++:
copy the source through its NUL byte into the destination, then return the
original destination pointer. This is the `strcpy` contract for valid
NUL-terminated strings. The optimized copy loop itself is shared with the
adjacent string-append routine; the retail entry is only seven bytes.

## Ghidra evidence

In the open `th10.exe` program, Ghidra identifies `FUN_0045bd80` as a function
with entry `0x0045BD80` and body `0x0045BD80..0x0045BD86`. It reports the
signature `uint * __cdecl FUN_0045bd80(uint *, uint *)`, classifies it as not a
thunk, and lists 31 incoming call references from 18 caller functions.

The seven bytes are `push edi; mov edi,[esp+8]; jmp 0x0045BDF5`. The prologue
saves the callee-saved `EDI` and loads the first stack argument as the
destination. The target `0x0045BDF5` is inside the separate function
`FUN_0045bd90` (`0x0045BD90..0x0045BE77`), not its entry. At the shared target,
the second argument is loaded from `[esp+0xC]`, accounting for the saved
register, and bytes are copied from that source pointer into `EDI`. Exit paths
load the original first argument from `[esp+8]` into `EAX`, restore `EDI`, and
execute plain `RET`; caller cleanup and the Ghidra `__cdecl` prototype agree.

`FUN_0045bd90` scans the destination for its terminator before falling through
the same copy core, which makes it a `strcat` implementation. The
`0x0045BD80` entry skips that scan and starts directly at the copy core. This
distinguishes the entry from an import thunk: it is independently called and
sets up the destination and saved-register state expected by the shared
worker.

The callers confirm the byte-string and return-pointer interpretation.
Ghidra's `__strdup` allocates `strlen(source) + 1`, calls this entry with the
allocated buffer and source, and returns its result. `__Getdays` and
`__Getmonths` pass the returned pointer to `strlen` to advance their output
cursor. The other call sites likewise use it as a copy into a supplied
destination.

The source keeps the existing C-linkage symbol and `__cdecl` boundary. No
build, probe, or test was run; byte-exact code generation is unverified.
