// Compiler context only; never selected as recovered game code.
#include "../../src/render/projection_quads_cull.cpp"

#pragma code_seg(".text$03context")
extern "C" int __stdcall ProjectionQuadCullCompilerContext(ProjectionSource** sources, int count,
                                                const float* position, const ProjectionBox* box,
                                                float radius) {
    ProjectionSource** cursor = sources;
    while (count--) {
        ProjectionSource* source = *cursor++;
        ProjectionQuad_CullTest(source, position, box, radius);
        ProjectionQuad_CullTest(source, position, box, radius);
    }
    return 0;
}
#pragma code_seg()
