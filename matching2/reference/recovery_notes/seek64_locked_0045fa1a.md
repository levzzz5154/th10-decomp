# Locked 64-bit CRT seek at 0x0045FA1A

Ghidra identifies the complete 131-byte Visual Studio 2003
`__lseeki64_lk` routine, with ordinary cdecl arguments: descriptor, 64-bit
distance, and origin. It first resolves the descriptor's OS handle. A
missing handle sets errno to 9 and returns `-1` as a 64-bit value.

The valid path passes the low distance word and a pointer to its high word
to the `SetFilePointer` import at `0x004660C8`. A low result of
`0xFFFFFFFF` is successful when `GetLastError` returns zero; a nonzero
error is passed to `__dosmaperr` and returns `-1`. On success, the function
clears bit 1 of the descriptor flags at entry offset `+0x04` and returns
the updated high word joined to the low result.

The [C++ source](../semantic_candidates/seek64_locked_0045fa1a.cpp)
keeps these distinctions explicit. The manifest retains the former assembly
body in `previous_record`. Byte matching is unverified, and no build or
byte comparison was run.

**Build status (2026-09-25):** the full byte-verified build showed that this model does not reproduce the retail bytes. The maintained source keeps the exact assembly, and the model is preserved in `reference/semantic_candidates/`.
