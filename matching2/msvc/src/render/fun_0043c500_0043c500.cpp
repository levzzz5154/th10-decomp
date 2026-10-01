#include "th10/render/quad_batch.hpp"
#include <stddef.h>
struct AsciiOverlay_0043C500 {
    unsigned char reserved_00[0x18];
    unsigned int alpha;
    unsigned char reserved_1C[8];
    unsigned int color;
    __declspec(noinline) int Draw();
};
typedef char OverlayAlphaOffset[(offsetof(AsciiOverlay_0043C500,alpha)==0x18)?1:-1];
typedef char OverlayColorOffset[(offsetof(AsciiOverlay_0043C500,color)==0x24)?1:-1];
#pragma code_seg(".text$03callback")
int AsciiOverlay_0043C500::Draw() {
    unsigned int composed_color = (color & 0x00ffffffu) | (alpha << 24);
    ScreenRect rect = {32.0f,16.0f,416.0f,464.0f};
    DrawSolidQuad(&rect,composed_color);
    return 1;
}
#pragma code_seg()
