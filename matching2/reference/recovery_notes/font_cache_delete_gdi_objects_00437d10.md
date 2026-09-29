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

## C++ model and exactness

`matching2/msvc/src/platform/font_cache_delete_gdi_objects_retail_00437d10.cpp`
calls the existing `ReleaseSurface_00436a30` C++ body for the global surface at
`0x00474CB0`, then calls the `DeleteObject` pointer loaded once from IAT slot
`0x00466030` for the fifteen handles at `0x00491868..0x004918A0` in descending
order. It does not clear those handle slots. The same native LTCG cluster also
contains the 13-byte static-exit surface-release callback at `0x00465A20`;
seeing the real releaser body lets both callers supply its private ESI argument
without inline assembly.

The focused probe matches all 149 teardown bytes, all 107 releaser bytes, all
13 callback bytes, and the 293-byte game shutdown caller after its symbol
cutover. A host runtime smoke checks reverse handle order and unmodified slots,
both null-DC and populated-DC paths, and the surface releaser's GDI calls.
The full build is byte-identical to the 487,936-byte retail executable.
