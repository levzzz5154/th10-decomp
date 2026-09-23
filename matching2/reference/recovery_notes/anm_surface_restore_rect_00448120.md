# `0x00448120` Ghidra ABI and behavior audit

## Boundary and call graph

Live Ghidra analysis of `th10.exe` places the function at `0x00448120..0x00448264`, a 325-byte region. The epilogue is `ret 0x1c`, so the caller removes seven 32-bit stack words. Ghidra labels the function `__stdcall`, but only reconstructs two parameters and leaves an incoming `EBX` value as `unaff_EBX`.

Ghidra reports no direct callers or function xrefs. A byte-pattern search for the entry pointer (`20 81 44 00`) also found no embedded reference. The sole named direct callee is `D3DXLoadSurfaceFromSurface` at `0x004521d6`; the other calls go through `data_00491c30`'s D3D9 vtable.

## Recovered behavior

- `EBP` receives the manager pointer from the first stack word. `EBX` is a live slot index: it selects the cached-surface pointer at `manager + 0x3ad560 + EBX*4` and the texture/surface slot at `manager + 0x3ad4e0 + EBX*4`.
- If the cached surface is null, the function returns. Otherwise, D3D9 `GetBackBuffer` (vtable offset `+0x48`, arguments `0, 0, 0, &temporary`) obtains a surface; a failed HRESULT returns immediately. The first stack word's home is reused for this temporary output, after its manager value has already been copied to `EBP`.
- If the indexed texture/surface slot is null, the function tries `CreateRenderTarget` (`+0x70`) using the indexed width/height fields at `manager + 0x3ad6e0 + EBX*0x1c` and `+4`, the format at `0x00491d14`, and the other creation flags from the disassembly. On failure it falls back to `CreateOffscreenPlainSurface` (`+0x90`). If both fail, it releases the acquired backbuffer and returns.
- A newly created surface is initialized from the cached surface with `D3DXLoadSurfaceFromSurface`. If that fails, the acquired backbuffer is released and the function returns.
- It builds rectangle/point temporaries from the remaining stack words and calls D3D9 `UpdateSurface` (`+0x78`) with the selected surface and the acquired backbuffer. It then releases the backbuffer.

The old `reference/legacy_semantic/src/render/anm_surface_restore.cpp` description treats the `+0x48` call as a cooperative-level check. The live call shape is instead `GetBackBuffer(0, 0, 0, outSurface)`, so that older behavioral description is not authoritative for this region.

## Conversion blocker

The slot index arrives in `EBX`, not in a supported x86 C++ parameter register or on the stack. The function also relies on seven stack words, while Ghidra has not recovered their complete source-level types or the indirect caller that establishes this ABI. An ordinary standalone C++ definition cannot read that incoming `EBX` value, and no known source-local caller exists to rewrite as part of a small cluster. Keep the body intact until the indirect dispatcher and its call contract are recovered; then the index can be made an explicit typed parameter in a caller-inclusive native C++ cluster.

No build, probe, or test was run during this audit.
