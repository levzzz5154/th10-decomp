# `0x0043C500` overlay draw callback

The former assembly source at
`matching2/msvc/src/render/fun_0043c500_0043c500.cpp` is represented by a
readable C++ member callback. The active manifest marks this region semantic,
binds it to `AsciiOverlay_0043C500::Draw`, and retains the previous assembly
row in `previous_record`.

## Ghidra evidence and dataflow

Live Ghidra analysis lists a 74-byte function at `0x0043C500`, with the
callback receiver in `ECX`, no stack parameters, and integer `1` returned in
`EAX` via a plain `RET`. The code reads `alpha` from receiver offset `0x18`
and `color` from offset `0x24`, computes
`(color & 0x00ffffff) | (alpha << 24)`, and prepares rectangle coordinates
`32.0f`, `16.0f`, `416.0f`, and `464.0f`.

The callback passes the rectangle address in `EDI` and the composed color in
`EBX` to `0x0043BDA0`; it does not push either value. Ghidra's disassembly of
`0x0043BDA0` confirms it reads the rectangle through `EDI` and the color from
`EBX`. It first loads `data_00491c10` into `ESI` and calls `0x00442F50`.
That callee reads the manager from `ESI`, so this nested edge also uses a
register-only convention.

When `manager->quad_count` is nonzero, `0x00442F50` sets texture stages
`(0, 6, 0)` and `(0, 3, 0)`, sets format `0x144`, and draws primitive type
`4` with `quad_count * 2` primitives from `batch_start` at stride `0x1c`.
It then assigns `cursor` to `batch_start`, clears `quad_count`, and increments
`draw_calls`. The callback source spells out this flush path so it does not
depend on a C++ member call using the wrong receiver register.

After the flush, `0x0043BDA0` builds four solid vertices in rectangle corner
order, sets each `rhw` to `1.0f` and each color to the composed ARGB value,
sets texture stages `(0, 4, 2)`, `(0, 1, 2)`, `(0, 5, 0)`, `(0, 2, 0)`, state
`(20, 6)`, and format `0x44`, then draws primitive type `5` with count `2`
and stride `0x14`. It resets manager cache values at offsets `0x3ADA60` through
`0x3ADA6B`, then restores texture stages `(0, 4, 4)`, `(0, 1, 4)`, `(0, 5, 2)`,
and `(0, 2, 2)`. The helper's final stage-call result is discarded; the
callback returns `1`.

The xref at `0x0043CA08` is in `FUN_0043C970`, which registers `0x0043C500` as
a scheduler callback. This supports the zero-explicit-argument `ECX` receiver.
Neighboring callbacks at `0x0043C2C0` and `0x0043C410` draw the same fixed
rectangle, though their helper call paths are not evidence for this callback's
register ABI.

## Semantic model and limits

The source now expresses the draw helper's observable state changes directly
inside `AsciiOverlay_0043C500::Draw`. This avoids the former call through the
typed `DrawSolidQuad(const ScreenRect*, unsigned int)` declaration, which
would pass stack arguments while the retail helper consumes `EDI` and `EBX`.
The queue flush is likewise spelled out instead of calling the `__thiscall`
`Flush` declaration, because retail `0x00442F50` consumes its manager in
`ESI`.
The remaining device calls use the typed vtable wrappers in
`th10/render/quad_batch.hpp`.

The receiver layout asserts the two observed field offsets and describes only
fields read by this callback. The C++ body is a semantic model of the observed
callback and helper behavior; it has not been built or compared with retail
bytes. Exact compiler output and runtime behavior remain unverified. No build,
probe, or test was run.
