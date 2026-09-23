# String append helper at `0x0045BD90`

`matching2/msvc/src/unidentified/FUN_0045bd90_0045bd90.cpp` now expresses the
function as ordinary C++: find the NUL at the end of `destination`, copy
`source` there through its NUL, and return the original `destination` pointer.
This is `strcat` behavior for valid NUL-terminated strings. Semantic confidence
is high.

## Ghidra evidence

In the open `th10.exe` program, Ghidra reports
`uint * __cdecl FUN_0045bd90(uint * param_1, uint * param_2)`, with entry
`0x0045BD90` and body `0x0045BD90..0x0045BE77` (232 bytes). Its pseudocode
scans `param_1` to its zero byte, copies bytes from `param_2` until and
including its zero byte, and returns `param_1`.

The disassembly reads the first argument at `[ESP+4]`, saves `EDI`, and then
reads the second argument at `[ESP+0xC]`. It locates the destination terminator
with aligned byte handling and a 32-bit zero-byte scan using `0x7EFEFEFF` and
mask `0x81010100`; the source copy likewise has byte-aligned and word-at-a-time
paths. All exits return the first argument in `EAX` and use plain `RET`, leaving
argument cleanup to the caller, consistent with `__cdecl`.

Ghidra lists four direct callers: `FUN_00455990` (`0x00455990`),
`FUN_00455b19` (`0x00455B19`), `FUN_00458efd` (`0x00458EFD`), and
`FUN_0045f259` (`0x0045F259`). Their call sites push the source and destination
arguments before calling this entry. The source definition retains the
C-linkage name `asm_FUN_0045bd90_0045bd90` and an explicit `__cdecl` boundary;
its `char*` types express the byte-string behavior more directly than Ghidra's
word-pointer types.

The live manifest now marks the 232-byte row semantic while preserving the
original assembly record in `previous_record`. The shared declaration and the
typed call from `strcats_00455990.cpp` both use the recovered two-pointer
`__cdecl` interface; assembly call sites keep the same C symbol.

The optimized instruction sequence has not been reproduced. Byte-exactness is
unverified, and no build, probe, or test was run.
