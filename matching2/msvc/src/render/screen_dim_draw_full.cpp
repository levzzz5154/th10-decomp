// 0x0043C3C0: the full-screen dim draw task (ScreenEffectController mode 6).
#include "th10/render/quad_batch.hpp"
#include <stddef.h>
struct ScreenDimFullQuad {
    unsigned char reserved_000[0x18];
    unsigned int alpha;
    unsigned int reserved_01c;
    unsigned int color;
    __declspec(noinline) int Draw();
};
typedef char AsciiOverlay_0043C3C0_AlphaOffset[(offsetof(ScreenDimFullQuad, alpha) == 0x18) ? 1 : -1];
typedef char AsciiOverlay_0043C3C0_ColorOffset[(offsetof(ScreenDimFullQuad, color) == 0x20) ? 1 : -1];
#pragma code_seg(".text$03w2overlay")
int ScreenDimFullQuad::Draw() {
    ScreenRect rect = {0.0f, 0.0f, 640.0f, 480.0f};
    DrawSolidQuad(&rect, color | (alpha << 24));
    return 1;
}
#pragma code_seg()
