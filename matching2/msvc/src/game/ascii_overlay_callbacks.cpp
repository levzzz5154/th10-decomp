// 0x0043C2C0: scheduler overlay callback, public ECX receiver.
#include "th10/render/quad_batch.hpp"
#include <stddef.h>
struct AsciiOverlay_0043C2C0 {
    unsigned char reserved_000[0x18];
    unsigned int alpha;
    unsigned int reserved_01c;
    unsigned int color;
    __declspec(noinline) int Draw();
};
typedef char AsciiOverlay_0043C2C0_AlphaOffset[(offsetof(AsciiOverlay_0043C2C0, alpha) == 0x18) ? 1 : -1];
typedef char AsciiOverlay_0043C2C0_ColorOffset[(offsetof(AsciiOverlay_0043C2C0, color) == 0x20) ? 1 : -1];
#pragma code_seg(".text$03w0overlay")
int AsciiOverlay_0043C2C0::Draw() {
    ScreenRect rect = {32.0f, 16.0f, 416.0f, 464.0f};
    DrawSolidQuad(&rect, color | (alpha << 24));
    return 1;
}
#pragma code_seg()
