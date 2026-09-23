# `_memcmp` at `0x0045CC10`

## Recovered interface and behavior

The body is a `__cdecl` comparison of two byte ranges and an unsigned 32-bit
count. Its C++ model accepts `const void*` arguments and reads them as
`unsigned char`, matching the byte-oriented accesses in the binary. A zero
count returns `0` before either input is read. Otherwise, comparison stops at
the first unequal byte: a smaller first byte returns `-1`, a greater first
byte returns `1`, and equal ranges return `0`.

## Ghidra evidence

Live Ghidra analysis of `th10.exe` at `0x0045CC10` identifies
`int __cdecl FUN_0045cc10(uint*, uint*, uint)` with a body spanning
`0x0045CC10..0x0045CCC7`. The initial count test jumps directly to the zero
return, confirming the zero-count behavior. If either input is not four-byte
aligned, the routine compares bytes in address order, including a one-byte
head when needed and then pairs of bytes. When both inputs are aligned, it
compares four-byte words for equality; after finding a different word, it
checks that word's bytes from lowest to highest address before returning.

The mismatch path uses `CMP` on byte registers and `SBB` to produce `-1` or
`1`, so ordering is unsigned and the returned value is normalized to its sign
rather than being the arithmetic difference of the bytes. Equal data, or a
zero count, returns `0`.

Ghidra reports one caller, `FUN_00455d53` at `0x00455D53`, with the call at
`0x00455F41`. That caller passes a count of `0xFE` and two buffers, then
normalizes the comparison result for its own condition.

The manifest now marks the 184-byte span semantic and retains its prior
assembly row in `previous_record`. The shared header declares the typed cdecl
signature under the existing address alias.

## Exactness status

The readable C++ captures the observed bounded comparison and its return
values. It does not reproduce the retail alignment optimizations, and exact
code generation, byte-for-byte equivalence, and the compiled function size
have not been verified. No build, probe, or test was run for this recovery.
