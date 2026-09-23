# `File_ReadShared` at `0x0044B790` — live Ghidra ABI audit

Date: 2026-09-23. Read-only review of the live `th10.exe` Ghidra program.

## Symbol and boundary

Ghidra names the function `ReadSharedFile` and reports its entry at
`0x0044B790`, with body `0x0044B790..0x0044B7D9` inclusive (74 bytes, 32
instructions, five basic blocks). The following function begins at
`0x0044B7E0`; six padding bytes occupy `0x0044B7DA..0x0044B7DF`.
Ghidra's inferred signature is `void* __stdcall ReadSharedFile(void)`, and
its name search finds only this entry for `ReadShared`. The assembly overlay
uses `asm_File_ReadShared_0044b790` (linker symbol
`_asm_File_ReadShared_0044b790`). The source comment calls the retail routine
`?File_ReadShared@@`; the separate semantic header declaration
`File_ReadShared(void* handle, DWORD size, ...)` is not the live entry ABI.

## Caller-supplied ABI

The only direct caller is `FUN_0042A200`, which calls the function at
`0x0042A277` and `0x0042A29E`. Immediately before those calls it puts the
requested byte count in `EDI`: first `0x24`, then the dword at `buffer+0x1C`.
Neither call pushes arguments. The live function reads `EDI` as the allocation
size and as the `ReadFile` byte count. Ghidra consequently decompiles it as a
no-argument function with `size_t unaff_EDI`.

`ECX` is not an input argument. The entry pushes it and later passes the saved
slot's address to `ReadFile` as `lpNumberOfBytesRead`, then restores `ECX` on
each return. This saved dword is not subsequently read. Thus the actual private
entry contract is: byte count in `EDI`, with the file handle obtained from the
shared global at `0x00474C38`; no stack arguments.

## Helpers and behavior

The handle global is set by `OpenSharedFileRead` at `0x0044B6B0`. The replay
loader calls `CloseProbeFile` at `0x0044B7E0` after a header-validation
failure or after the second read succeeds. The read helper itself:

1. Returns null immediately if the shared handle is `INVALID_HANDLE_VALUE`.
2. Calls `_malloc` at `0x00452706` with the `EDI` size. Ghidra identifies this
   as the Visual Studio 2003 CRT `_malloc(size_t)` wrapper around
   `__nh_malloc`.
3. If allocation fails, calls the `CloseHandle` import through slot
   `0x004660CC` and returns null.
4. Otherwise calls `ReadFile` through slot `0x004660D0`, passing the shared
   handle, allocated buffer, `EDI` size, the saved-`ECX` dword as the byte-count
   output, and null for `OVERLAPPED`. It ignores both the API result and byte
   count, then returns the allocated buffer.

The two imports are the expected stdcall helpers (`CloseHandle@4` and
`ReadFile@20`). The read helper does not clear the shared global or leave the
file critical section.

## Conversion decision

Keep the exact naked body in
`matching2/msvc/src/platform/file_read_shared_0044b790.cpp`. Ordinary MSVC C++
cannot declare a formal input in `EDI`; the direct caller's two call sites
depend on that register handoff, and a normal no-argument function is free to
reuse `EDI`. The semantic declaration with an explicit `size` argument would
change the live ABI. Preserving this entry as ordinary C++ would require an
assembly/native-LTCG adapter or a caller-and-callee cluster, outside this
function-only conversion.

No source, manifest, caller, or layout change was made. No build, probe, or test
was run for this audit.
