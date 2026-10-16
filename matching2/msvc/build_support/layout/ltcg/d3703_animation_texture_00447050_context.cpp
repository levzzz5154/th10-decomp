#include "../../../src/core/sprtlib/animation_texture_create.cpp"

#pragma code_seg(".text$03context")
extern "C" int __stdcall D3703AnimationContext_00447050(
        int* widths, int* heights, void** outputs, int* formats, int count) {
    for (int i = 0; i < count; ++i)
        AnimationTextureCreate2(widths[i], heights[i], outputs[i], formats[i]);
    return 0;
}
#pragma code_seg()
