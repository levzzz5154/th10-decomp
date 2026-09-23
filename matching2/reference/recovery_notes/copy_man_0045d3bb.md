# `__CopyMan` at `0x0045D3BB`

The source now models this helper as an ordinary `__cdecl` function taking a destination word pointer followed by a source word pointer. It copies exactly three 32-bit words, from index 0 through index 2, reading each source word immediately before writing the corresponding destination word. The byte order is therefore preserved as a forward word copy, including its overlap behavior; do not substitute `memmove`.

Ghidra confirms a 27-byte body that loads its two arguments from `[ESP+4]` and `[ESP+8]`, loops three times, and returns with plain `RET` (caller cleanup). Its two direct call sites are `0x0045D4E3` and `0x0045D522`, both in `__ld12cvt` at `0x0045D476`; Ghidra decompiles the arguments as three-word temporary buffers.

The C++ body has no inline assembly. The active manifest marks this region
semantic and retains the prior assembly row in `previous_record`. Exact ABI
emission and byte output remain unverified; no build, probe, or test was run.
