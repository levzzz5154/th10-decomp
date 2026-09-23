# GDI font cache object teardown at 0x00437D10

## Behavior from Ghidra

The live `th10.exe` function at `0x00437D10` spans `0x00437D10..0x00437DA4`.
Its decompilation first calls `FUN_00436A30`, then calls the GDI
`DeleteObject` import on the globals from `0x004918A0` down through
`0x00491868` in four-byte steps. There are fifteen handle calls. The function
does not clear those global slots.

The instruction listing shows the call convention edge directly: at
`0x00437D11`, retail loads `0x00474CB0` into `ESI`, calls `0x00436A30`, then
reuses `ESI` for the `DeleteObject` import slot at `0x00466030`. The caller
cross-reference is `FUN_00420270` at `0x00420270`.

Ghidra's decompilation of `0x00436A30` identifies its implicit receiver as
`unaff_ESI`. It checks receiver offset `+0x114`; when nonzero it restores the
object at `+0x118` with `SelectObject`, deletes the device context, deletes
the font object at `+0x11C`, and clears fields at `+0x104`, `+0x108`,
`+0x114`, `+0x11C`, `+0x118`, and `+0x120`. It sets `+0x100` to `-1`. When
`+0x114` is null it does not change the receiver. This agrees with the
existing summary in
`matching2/reference/legacy_semantic/src/platform/gdi_font_cache.cpp` and
the declaration/comment in
`matching2/reference/legacy_semantic/include/th10/platform/gdi_font_cache.hpp`.

## C++ model

`matching2/msvc/src/platform/font_cache_delete_gdi_objects_retail_00437d10.cpp`
models the private receiver explicitly as the cache surface at `0x00474CB0`
and applies the observed `0x00436A30` effects before deleting the fifteen
global handles from highest slot to lowest. It reads the GDI function
pointers from their IAT slots (`0x00466028`, `0x0046602C`, and `0x00466030`).
During the cache flush each pointer is read immediately before its API call.
Afterward the retail body loads `DeleteObject` once into `ESI` and reuses it
for all fifteen global handles; the C++ loop does the same. The helper is
spelled out in C++ instead of called with the wrong ordinary calling
convention: the retail helper consumes `ESI`, and C++ does not express that
private register argument.

## Byte status

The manifest now classifies this readable ordinary-C++ body as a semantic
region. This is not an exact-byte claim: the previous stand-alone candidate
emitted 196 bytes and matched 5 of the 149 retail bytes, and the new semantic
spelling has not been byte-compared. No build, probe, or test was run for this
change.
