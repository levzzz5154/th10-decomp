// Compiler context only; none of these bytes enter the image.
#include "../../../../src/core/sprtlib/animation_texture_surface_copy.cpp"

#include "clear.cpp"

#pragma code_seg(".text$07context")
extern "C" int __stdcall AnimationTextureSurfaceCopyContext(
        AnimationTextureManager_00448270** managers,
        AnimationManagerIndexed_00447f70** images, const int* values,
        const SurfaceRect_00447fd0* rects, int count,
        RenderState_00448450** state) {
    // The render state object is reachable through pointers in the game, so
    // stores through other pointers may alias its members.
    *state = &g_application;
    for (int i = 0; i < count; ++i)
        managers[i]->CaptureBackBuffer(values[i], values[i + 1], i, count - i, count + i,
                                       count ^ i, values[i + 2], values[i + 3],
                                       values[i + 4], values[i + 5]);
    for (int i = 0; i < count; ++i)
        managers[i]->CopyTexture(values[i], values[i + 1], values[i + 2], values[i + 3],
                                 &rects[i], &rects[i + 1]);
    for (int i = 0; i < count; ++i)
        images[i]->CaptureBackBufferImage(values[i], i, count - i, count + i, count ^ i,
                                          values[i + 1], values[i + 2], values[i + 3],
                                          values[i + 4]);
    for (int i = 0; i < count; ++i)
        images[i]->CopyRectToBackBuffer(values[i], i, count - i, count + i, count ^ i,
                                        values[i + 1], values[i + 2]);
    return count;
}
#pragma code_seg()
