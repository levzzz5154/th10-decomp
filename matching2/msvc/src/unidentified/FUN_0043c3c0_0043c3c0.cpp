// 0x0043C3C0: scheduler overlay callback, public ECX receiver.
#include "th10/render/quad_batch.hpp"
#include <stddef.h>
struct AsciiOverlay_0043C3C0 {
    unsigned char reserved_000[0x18];
    unsigned int alpha;
    unsigned int reserved_01c;
    unsigned int color;
    __declspec(noinline) int Draw();
};
typedef char AsciiOverlay_0043C3C0_AlphaOffset[(offsetof(AsciiOverlay_0043C3C0, alpha) == 0x18) ? 1 : -1];
typedef char AsciiOverlay_0043C3C0_ColorOffset[(offsetof(AsciiOverlay_0043C3C0, color) == 0x20) ? 1 : -1];
#pragma code_seg(".text$03w2overlay")
int AsciiOverlay_0043C3C0::Draw() {
    ScreenRect rect = {0.0f, 0.0f, 640.0f, 480.0f};
    DrawSolidQuad(&rect, color | (alpha << 24));
    return 1;
}
#pragma code_seg()
