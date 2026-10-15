// Compiler context only; its bytes are not recovered game code.
#include "../../src/core/sprtlib/animation_manager_draw_bucket1.cpp"
#include "../../src/core/sprtlib/animation_manager_render_bucket_00448980.cpp"

#pragma code_seg(".text$05context")
int __stdcall AnimationManagerRenderBucket1Context(
        AnimationManagerBucket1_00448600** managers, int count) {
    int result = 0;
    for (int index = 0; index < count; ++index) {
        result = managers[index]->RenderBucket1();
    }
    return result;
}
#pragma code_seg()
