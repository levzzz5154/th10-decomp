// Compiler context only; never selected as recovered game code.
// The conditional calls give both methods the same native entry convention.
#include "../../../src/core/sprtfunc/edge_strips.cpp"

#pragma code_seg(".text$05context")
int __stdcall EdgeStripCompilerContext(
    int count, EdgeStripSurface* surface, EdgeStripVertex* vertices, int vertical) {
    if (vertical) return surface->FillVertical(count, vertices);
    return surface->FillHorizontal(count, vertices);
}
#pragma code_seg()
