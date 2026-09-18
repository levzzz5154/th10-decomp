// Compiler context only; never selected as recovered game code.
#include "../../src/render/animation_manager_stop_at_frame2_0040c480.cpp"

#pragma code_seg(".text$70context")
int __stdcall StopAtFrameCompilerContext(AnimationHandle* handles, int count) {
    while (count--) {
        handles->StopAtFrame2();
        handles->StopAtFrame3();
        handles++;
    }
    return 0;
}
#pragma code_seg()
