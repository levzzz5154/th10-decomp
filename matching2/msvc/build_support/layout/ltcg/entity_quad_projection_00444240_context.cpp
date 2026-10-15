// Compiler context only; this caller is never selected as recovered game code.
// The shared native LTCG unit recovers EAX as the entity pointer and puts the
// manager on the stack, which is the region's retail entry convention.
#include "../../../src/core/sprtfunc/fun_00444240_00444240.cpp"

#pragma code_seg(".text$03context")
int __stdcall EntityQuadProjectionCompilerContext(ProjectedEntity** entities,
                                                  ProjectionManager** managers,
                                                  int count) {
    int result = 0;
    for (int index = 0; index < count; ++index) {
        result += entities[index]->ProjectQuad(managers[index]);
    }
    return result;
}
#pragma code_seg()
