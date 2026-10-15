// Compiler context only; none of these bytes enter the image.
#include "../../../src/core/sprtlib/animation_manager_copy_to_back_buffer_00447fd0.cpp"

#pragma code_seg(".text$05context")
extern "C" int __stdcall CopyToBackBufferContext_00447fd0(
        AnimationManagerIndexed** managers, const int* values, int count) {
    for (int i = 0; i < count; ++i)
        managers[i]->CopyToBackBuffer(values[i], i, count - i, count + i, count ^ i);
    return count;
}
#pragma code_seg()
