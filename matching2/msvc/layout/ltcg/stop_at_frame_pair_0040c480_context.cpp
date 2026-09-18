// Compiler context only; never selected as recovered game code.
#include "../../src/render/anm_propagate.cpp"

#pragma code_seg(".text$70context")
int __stdcall StopAtFrameCompilerContext(AnimationHandle* handles, int count) {
    while (count--) {
        handles->StopAtFrame1();
        handles->StopAtFrame2();
        handles->StopAtFrame3();
        handles++;
    }
    return 0;
}
#pragma code_seg()
