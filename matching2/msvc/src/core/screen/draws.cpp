// The screen effect's overlay draw tasks (full screen and playfield quads),
// compiled in the anm_batch_flush native-LTCG cluster with the quad batch.
#include "th10/render/quad_batch.hpp"
#include <stddef.h>

// 0x0043C1A0: apply the full viewport and draw the configured color overlay.
struct ColorViewport {
    char reserved[0x18];
    unsigned int alpha;
    int reserved_01c;
    unsigned int color;
    __declspec(noinline) int Draw();
};
#pragma code_seg(".text$03viewport")
int ColorViewport::Draw() {
    ScreenRect rect = {0.0f, 0.0f, 640.0f, 480.0f};
    g_sprt_ctrl->Flush();
    data_00491cf4.x = 0;
    data_00491cf4.y = 0;
    data_00491cf4.width = 640;
    data_00491cf4.height = 480;
    data_00491c30->Viewport(&data_00491cf4);
    DrawSolidQuad(&rect, color | (alpha << 24));
    return 1;
}
#pragma code_seg()

// 0x0043C2C0: the fade-out draw task (Screen mode 2): a solid
// playfield quad at the current alpha.
struct ScreenFadeOutQuad {
    unsigned char reserved_000[0x18];
    unsigned int alpha;
    unsigned int reserved_01c;
    unsigned int color;
    __declspec(noinline) int Draw();
};
typedef char AsciiOverlay_0043C2C0_AlphaOffset[(offsetof(ScreenFadeOutQuad, alpha) == 0x18) ? 1 : -1];
typedef char AsciiOverlay_0043C2C0_ColorOffset[(offsetof(ScreenFadeOutQuad, color) == 0x20) ? 1 : -1];
#pragma code_seg(".text$03w0overlay")
int ScreenFadeOutQuad::Draw() {
    ScreenRect rect = {32.0f, 16.0f, 416.0f, 464.0f};
    DrawSolidQuad(&rect, color | (alpha << 24));
    return 1;
}
#pragma code_seg()

// 0x0043C3C0: the full-screen dim draw task (Screen mode 6).
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

// 0x0043C410: the playfield dim draw task (Screen mode 7).
struct ScreenDimPlayfieldQuad {
    unsigned char reserved_000[0x18];
    unsigned int alpha;
    unsigned int reserved_01c;
    unsigned int color;
    __declspec(noinline) int Draw();
};
typedef char AsciiOverlay_0043C410_AlphaOffset[(offsetof(ScreenDimPlayfieldQuad, alpha) == 0x18) ? 1 : -1];
typedef char AsciiOverlay_0043C410_ColorOffset[(offsetof(ScreenDimPlayfieldQuad, color) == 0x20) ? 1 : -1];
#pragma code_seg(".text$03w4overlay")
int ScreenDimPlayfieldQuad::Draw() {
    ScreenRect rect = {32.0f, 16.0f, 416.0f, 464.0f};
    DrawSolidQuad(&rect, color | (alpha << 24));
    return 1;
}
#pragma code_seg()
