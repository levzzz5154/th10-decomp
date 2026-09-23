# Font cache initialization audit at 0x00437A00

## Disposition

The 781-byte production region remains its exact naked assembly body in
`matching2/msvc/src/platform/font_cache_init.cpp`. Live Ghidra establishes the
observable work, but the initial surface creation uses a private register ABI
that an ordinary C++ call cannot express. The region already has an exact
MSVC 13.10 assembly baseline (781/781 bytes); no build, probe, or test was run
for this audit.

## Live Ghidra evidence

The active program was `th10.exe`, x86 little-endian, image base
`0x00400000`. Ghidra reports `FUN_00437a00` at
`0x00437A00..0x00437D0C`, with no explicit parameters and a plain `RET`.
The caller xref is the unconditional direct call at `0x00420260`. The caller
does not pass an argument and discards the result; the next instruction is
`xor eax,eax`.

The first call is `FUN_00436af0(0x400, 0x40, 0x1a)`. If AL is zero, the
routine retries with format `0x15`. The retail listing at `0x00437A09` and
`0x00437A20` explicitly loads `EAX=0x00474CB0` before each call. Ghidra's
callee decompilation confirms `FUN_00436af0` takes three stack arguments and
uses the incoming EAX as the font-surface receiver; its function body returns
with `ret 0xc`. The current source declaration
`asm_FUN_00436af0_00436af0()` intentionally hides this private receiver and
argument setup behind a naked bridge. A direct ordinary C++ call would place
the receiver under a different x86 convention.

After surface setup, the region performs 256 iterations. For each iteration it
takes the low word of `0x004918B0`, computes
`v = (uint16_t)((seed ^ 0x9630) - 0x6553)`, then
`next = (uint16_t)((v << 2) + (v >> 14))`. It writes `next` back only to the
low word at `0x004918B0`, preserving that dword's high word, increments a
local copy of the dword at `0x004918B4`, and writes `next >> 9` to byte
`0x00474CB0 + index`. It stores the incremented dword counter after the loop,
so its final value is the old value plus 256 modulo 2^32.

The routine then calls the `CreateFontA` import through the IAT slot at
`0x00466034` fifteen times. Heights are `0x20, 0x22, ..., 0x3C`; the
remaining arguments are zero except weight 400, charset `0x80`, quality 4,
pitch/family `0x11`, and face pointer `0x0046F36C`. Returned handles are
stored from `0x004918A0` down through `0x00491868` in four-byte steps,
corresponding to ascending height. Ghidra's external prototype in
`decompiled/ghidra_augmented/externals.tsv` is
`HFONT __stdcall CreateFontA(int, int, int, int, int, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, LPCSTR)`.

## Integration names

The existing retail function symbol/prototype can stay as
`extern "C" void __cdecl asm_FUN_00437a00_00437a00()`; the no-argument plain
`RET` boundary is compatible with the call at `0x00420260`. Useful data
aliases for a future shared declaration pass are:

- `font_surface_receiver_00474cb0`: 0x00474CB0, also the 256-byte destination
  base and the receiver passed to `FUN_00436af0`.
- `font_rng_seed_word_004918b0`: low 16 bits only; upper 16 bits are preserved.
- `font_rng_counter_004918b4`: 32-bit counter incremented by 256.
- `font_handles_00491868_to_004918a0`: fifteen 32-bit GDI handles, stored in
  reverse address order as font height increases.
- `create_font_a_iat_00466034`: 32-bit import slot for `CreateFontA`.

The surface helper has no standard prototype that includes its EAX receiver.
Its observed stack arguments are width, height, and format, and it consumes
0x0C stack bytes. Keep the assembly bridge as the integration alias unless the
helper is separately exposed through a receiver-aware wrapper or its behavior
is moved into a verified semantic implementation.
