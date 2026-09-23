# `_memcpy` at `0x0045BFC0`

## Recovery

Replaced the assembly source in `msvc/src/unidentified/memcpy_0045bfc0.cpp` with a byte-wise C++ implementation of the observed copy behavior. It retains the current C-linkage alias `asm_memcpy_0045bfc0` with the typed signature `void* __cdecl(void* destination, const void* source, size_t size)`. It returns the original destination pointer and performs no reads or writes when `size` is zero. The manifest now records the full 829-byte retail extent as one semantic row and stores the former 47 code, data, and padding rows in `previous_records`; the current per-table overlays and internal assembly labels are removed because this C++ model does not use those implementation details. The shared header now exposes the typed entry signature.

## Ghidra evidence

- Ghidra identifies this as the Visual Studio 2003 CRT library function `_memcpy`, with signature `void* __cdecl _memcpy(void* _Dst, void* _Src, size_t _Size)`.
- Ghidra reports the body as `0x0045BFC0..0x0045C2FC` inclusive. The final `RET` is at `0x0045C2FC`.
- The prologue reads destination, source, and size from `[EBP+8]`, `[EBP+0xC]`, and `[EBP+0x10]`. Return paths restore EAX from `[EBP+8]`; plain `RET` leaves stack cleanup to the caller. For example, the caller at `0x0045FF12` adds `0xC` to ESP after the call.
- The retail implementation copies forward unless the destination starts inside the source range. Its overlap check is `source < destination < source + size`; that case branches to `0x0045C15C`, sets the direction flag, and copies backward to avoid overwriting unread source bytes. The C++ implementation expresses the same condition as `destination > source && destination - source < size`, and uses backward or forward byte loops accordingly. Thus it preserves the observed behavior for both overlapping and disjoint ranges.
- The forward path uses alignment adjustments, 32-bit word copies, and byte tails in the retail code; those optimizations are represented by the same byte-copy result. The zero-size paths return the destination without accessing either buffer.
- The retail span interleaves code with dispatch-table data and alignment padding. The six former data ranges were `0x0045C024..0x0045C02F`, `0x0045C0A0..0x0045C0BF`, `0x0045C10C..0x0045C11B`, `0x0045C1B0..0x0045C1BB`, `0x0045C23C..0x0045C25B`, and `0x0045C2A8..0x0045C2B7`; they remain recorded in row provenance, while the current C++ model covers the full semantic function span.
- Ghidra lists callers `FUN_00455bf3` (`0x00455BF3`, two call sites), `FUN_00455d53` (`0x00455D53`, two), `FUN_00457395` (`0x00457395`, two), `FUN_0045bb33` (`0x0045BB33`), `__Gettnames` (`0x0045A52B`), and `___crtGetEnvironmentStringsA` (`0x0045940A`). An additional cross-reference at `0x0045FF12` is in the unassigned fragment beginning at `0x0045FE87`.

## Limits

The C++ source represents the observed copy semantics, not the retail alignment/word-copy optimization or exact instruction layout. Exact compiler code generation and byte-for-byte equivalence are unverified; no build, probe, or test was run.
