# `0x00403090`: semantic recovery is understood, integration remains blocked

Checked against the live Ghidra project `th10` / `th10.exe` on 2026-09-23.
The function body is `0x00403090..0x0040384f` (1,984 bytes). The checked-in
retail definition remains unchanged in
`matching2/msvc/src/render/fun_00403090_00403090.cpp`.

## Entry and call contract

Ghidra reports `undefined4 __fastcall FUN_00403090(int, float *, float)`.
The disassembly and its sole caller, `FUN_00403a30` at `0x00403a30`, refine
that signature:

| Value at entry | Evidence |
| --- | --- |
| `ECX`: object record | Caller loads `ESI` (the selected record) into `ECX` at `0x00403acc`; callee reads center fields at `+4..+0xc` and extents at `+0x10..+0x18`. |
| `EDX`: three-float translation | Caller forms a pointer to its stack `Vec3` at `0x00403ac8`; callee reads three floats at `[EDX]`, `[EDX+4]`, `[EDX+8]`. |
| `EAX`: camera/view state at `0x00491d7c` | Caller loads the literal `0x00491d7c` at `0x00403ac3`; the callee saves it in `ESI` and reads camera values and three D3D matrices/viewport at fixed offsets from it. This is a fixed singleton in the observed call path, not a variable fourth C argument. |
| stack `float`: maximum squared distance | Caller pushes `[caller+0x1ee0]` at `0x00403ac2`; callee compares the squared center delta against `[ESP+0x130]` after reserving its frame and saving `ESI`. |

The function returns a 32-bit culling result in `EAX` and ends in `ret 4` on
both result paths. A semantic declaration can express the three formal values
as a typed `__fastcall` function (`ECX`, `EDX`, then one stack float), with the
camera state read from the fixed address above. A default `__cdecl` declaration
cannot express this call contract.

## Behavior and call edges

The live decompilation and instruction stream show a distance precheck between
the translated object center and the camera position-plus-eye offset. A
rejected distance returns `1`. Otherwise, the function scales the record's
three extents by the global half-size constant, builds eight box corners and a
translation matrix, then calls the two local D3DX thunks:

- `D3DXMatrixTranslation` at `0x00452182`
- `D3DXVec3ProjectArray` at `0x00452188`

It accumulates screen-space x/y bounds from projected corners with normalized
depth in `[0, 1)`, then checks those bounds against the viewport limits. The
overlap path returns `0`; the non-overlap path returns `1`. Ghidra reports
`FUN_00403a30` as the only caller and the two thunks above as the callees.

## Concrete integration blocker

The shared checked-in declaration in `matching2/msvc/include/asm_symbols.hpp`
is still `extern "C" void __cdecl asm_FUN_00403090_00403090();`. The real
caller is inline assembly using that declaration's symbol name, while the
retail callee depends on the caller's ECX/EDX/EAX setup and pops its one stack
argument. Replacing only this translation unit with a normal C++ body under
the declared no-argument `__cdecl` type would lose the object and vector
register inputs, return the wrong type, and leave the pushed float on the
stack. A faithful C++ entry needs the shared declaration and symbol mapping to
move to a typed `__fastcall` contract; those shared files are outside this
recovery unit's ownership, so this pass does not add an uncompiled semantic
sidecar or alter the retail definition.

The prior exact-byte source-shape blocker also remains recorded in the retail
source comment: the closest candidate had the right behavior and calls but
could not reproduce the retail `0x128` stack frame and slot packing. No build,
probe, or test was run for this pass.
