# Text overlay renderer at `0x00401760`

## C++ source conversion

`src/game/fun_00401760_00401760.cpp` now expresses the renderer as ordinary
C++ with the observed one-pointer stdcall entry, return value `1`, and callee
stack cleanup (`RET 4`). The outer object still uses a local byte-offset view:
the text count is at `+0x896c`, line-width factor at `+0x898c`, font resource at
`+0x8994`, and records start at `+0x76c` with stride `0x68`. A record contains
text bytes at `+0`, position at `+0x40`, color at `+0x4c`, scale at `+0x50`,
camera mode at `+0x5c`, font index at `+0x60`, and the outline flag at `+0x64`.

The source uses the existing `RenderEntity`, `RenderCamera`, and
`AnimationManager_00442F50` views. It calls typed `Flush()` and `Apply()`
methods. The camera switch still publishes the selected camera through
`data_00491fac`, applies its view/projection, publishes the viewport at camera
offset `+0xcc`, and updates `data_00491fb0`.

The two raw calls to `0x00443080` are represented by one inline geometry body
inside the glyph pass loop, followed by `SubmitSpriteQuad(entity, 1)`. This
retains the outline pass at `+2,+2` with half alpha, restores the base position
for the normal pass, and preserves anchor modes 0/1/2. Anchor mode 3 leaves the
shared x or y corner coordinates untouched, as the retail helper does.

## Alias and layout dependencies

This source needs a native-LTCG render batch with the implementations behind
`Flush()` and `Apply()`; their recovered retail receivers are ESI and EDI. The
manifest now classifies the region as semantic and binds its decorated stdcall
symbol. The shared alias declaration and typed forwarding caller use the
observed one-pointer signature. The existing `format_record_text` layout places
a synthetic compiler context at `0x00401760`, which overlaps this region; the
two contexts are not integrated. The 738-byte extent and compiler placement
remain unverified because no build was run.

Other raw callers still need the existing `0x00443080` alias:
`0x00401a50`, `0x0040a940`, and `0x0042b780`. `0x004451c0` has its own C++
entry declaration at that address. The raw aliases for `0x00442f50` and
`0x004215a0` likewise remain needed by their other callers.

## Transitive assembly dependencies and verification

The centered anchors call `asm_FUN_00452ff0_00452ff0` through its ordinary
double-argument cdecl ABI. The existing `SubmitSpriteQuad` body also contains
an inline x87 `FRNDINT` block. These dependencies remain assembly; the new
`0x00401760` body itself has no inline assembly or private-register calls.

No build, probe, or test was run for this change. In particular, this note does
not claim byte identity or confirm the 738-byte region size.
