// Compiler context only; no context bytes count as recovered code.
#include "../../src/render/texture_stage_reset.cpp"
#pragma code_seg(".text$07context")
int __stdcall GradientQuadContext(const ScreenRect** rects, const unsigned int* colors, int count) {
    for (int i = 0; i < count; ++i)
        DrawGradientQuad(rects[i], colors[4*i], colors[4*i+1], colors[4*i+2], colors[4*i+3]);
    return count;
}
#pragma code_seg()
