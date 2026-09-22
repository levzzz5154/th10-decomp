// 0x0043C410: scheduler overlay callback, public ECX receiver.
#include "th10/render/quad_batch.hpp"
#include <stddef.h>
struct AsciiOverlay_0043C410 {
    unsigned char reserved_000[0x18];
    unsigned int alpha;
    unsigned int reserved_01c;
    unsigned int color;
    __declspec(noinline) int Draw();
};
typedef char AsciiOverlay_0043C410_AlphaOffset[(offsetof(AsciiOverlay_0043C410, alpha) == 0x18) ? 1 : -1];
typedef char AsciiOverlay_0043C410_ColorOffset[(offsetof(AsciiOverlay_0043C410, color) == 0x20) ? 1 : -1];
#pragma code_seg(".text$03w4overlay")
int AsciiOverlay_0043C410::Draw() {
    ScreenRect rect = {32.0f, 16.0f, 416.0f, 464.0f};
    DrawSolidQuad(&rect, color | (alpha << 24));
    return 1;
}
#pragma code_seg()
