# Image alpha transform at `0x00437160`

`src/render/image_alpha_transform.cpp` now expresses the 157-byte retail region
as `ImageSurface_00437160::InvertAlpha` in ordinary C++. Ghidra shows the
receiver in ECX, `row_count` at `[ESP+4]`, the byte count computed from the
surface pitch at `+0x110`, the pixel buffer at `+0x120`, and the format at
`+0x100`. The routine makes no calls. Its known callers are `0x00437DB0` and
`0x00437FE0`.

The candidate returns a `char` so success or unsupported-format status is
represented in AL. For format `0x15`, it complements byte offsets 3, 7, 11,
and so on. For `0x19`, it visits each 16-bit word when the byte count is
positive, toggles bit 15, and clears the word when the transformed alpha bit is
clear. For `0x1A`, it XORs `0xF0` into byte offsets 1, 3, 5, and so on. It
returns 1 for each supported format, including when a loop has no elements,
and 0 for other formats.

The `ImageSurface_00437160` layout only declares the three fields accessed by
this function. Its full type name, class relationship, and source-level
operation name are not established by the retail instructions.

The prior near-match analysis in `00408880_wave17.md` records a readable model
with the same transform and a measured 156-byte output against the 157-byte
retail extent. All 61 instruction shapes matched; the first byte differed at
`+0x01` because the compiler placed the byte-count value in a different
register. Retail also has one alignment byte before the `0x19` loop at
`0x004371AF`. That note found no source spelling among its tested variants
that changed the byte-count register allocation. The current candidate follows
that best model; its output has not been rebuilt or compared.

The source now binds region `0x00437160` as semantic member
`?InvertAlpha@ImageSurface_00437160@@QAEDH@Z`; the previous ASM row remains in
`previous_record`, and its raw address aliases remain mapped. The ordinary
`__thiscall` signature matches the observed ECX receiver and one stack integer.
The provisional class layout and method name are still based on accessed
offsets and behavior. The source has not been rebuilt or compared; byte
equivalence remains unverified. No build, probe, or test was run for this edit.
