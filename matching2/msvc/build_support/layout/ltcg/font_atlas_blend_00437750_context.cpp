// Compiler context only; never selected as recovered game code.
#pragma code_seg(".text$01blend")
#include "../../../src/core/main/font_atlas_blend.cpp"

#pragma code_seg(".text$03context")
// A direct caller, so the compiler picks the private register homes.
extern "C" __declspec(noinline) int __stdcall FontAtlasBlendEntry(FontAtlas2** atlases,
                                                                  FontSurface** surfaces, int count) {
    int result = 0;
    while (count--) {
        FontAtlas2* atlas = *atlases++;
        result = FontAtlas_BlendToSurface(atlas, count, count, *surfaces++, atlas->width, atlas->height);
    }
    return result;
}
#pragma code_seg()
