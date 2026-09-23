// Compiler context only; its bytes are not recovered game code.
#include "../../src/unidentified/FUN_00448600_00448600.cpp"
#include "../../src/render/animation_manager_render_bucket_00448980.cpp"

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
