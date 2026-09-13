// 0x0043C1A0: apply the full viewport and draw the configured color overlay.
#include "th10/render/quad_batch.hpp"
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
    data_00491c10->Flush();
    data_00491cf4.x = 0;
    data_00491cf4.y = 0;
    data_00491cf4.width = 640;
    data_00491cf4.height = 480;
    data_00491c30->Viewport(&data_00491cf4);
    DrawSolidQuad(&rect, color | (alpha << 24));
    return 1;
}
#pragma code_seg()
