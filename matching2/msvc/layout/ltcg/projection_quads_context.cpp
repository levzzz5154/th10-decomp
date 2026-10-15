// Compiler context only; never selected as recovered game code.
#include "../../src/core/sprtfunc/projection_quads.cpp"

#pragma code_seg(".text$00context")
int __stdcall ProjectionQuadsCompilerContext(BillboardSource_00443B60** sources, int count) {
    BillboardSource_00443B60** cursor = sources;
    while (count--) {
        BillboardSource_00443B60* source = *cursor++;
        source->BuildProjectedQuad();
    }
    return 0;
}
#pragma code_seg()
