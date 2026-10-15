// Compiler context only; never selected as recovered game code.
#include "../../../src/core/sprtfunc/projection_quads.cpp"

#pragma code_seg(".text$00context")
int __stdcall ProjectionQuadsCompilerContext(BillboardSource** sources, int count) {
    BillboardSource** cursor = sources;
    while (count--) {
        BillboardSource* source = *cursor++;
        source->BuildProjectedQuad();
    }
    return 0;
}
#pragma code_seg()
