// 0x0043C500: scheduler overlay callback with its record in ECX.
#include "th10/render/quad_batch.hpp"
#include <stddef.h>

struct AsciiOverlay_0043C500 {
    unsigned char reserved_000[0x18];
    unsigned int alpha;
    unsigned int reserved_01c;
    unsigned int reserved_020;
    unsigned int color;
    __declspec(noinline) int Draw();
};

typedef char AsciiOverlay_0043C500_AlphaOffset[
    (offsetof(AsciiOverlay_0043C500, alpha) == 0x18) ? 1 : -1];
typedef char AsciiOverlay_0043C500_ColorOffset[
    (offsetof(AsciiOverlay_0043C500, color) == 0x24) ? 1 : -1];

#pragma code_seg(".text$03w5overlay")
int AsciiOverlay_0043C500::Draw() {
    ScreenRect rect = {32.0f, 16.0f, 416.0f, 464.0f};
    unsigned int argb = (color & 0x00ffffffu) | (alpha << 24);

    // Retail passes this rectangle and color to 0x0043BDA0 in EDI and EBX.
    // That helper in turn calls the batch flush with its manager in ESI.
    // Keep both register-only edges inside this semantic body.
    AnimationManager_00442F50* manager = data_00491c10;
    if (manager->quad_count != 0) {
        data_00491c30->Stage(0, 6, 0);
        data_00491c30->Stage(0, 3, 0);
        data_00491c30->Format(0x144);
        data_00491c30->Draw(
            4,
            static_cast<unsigned int>(manager->quad_count) << 1,
            manager->batch_start,
            0x1c);
        manager->batch_start = manager->cursor;
        manager->quad_count = 0;
        ++manager->draw_calls;
    }

    SolidVertex vertices[4];
    vertices[0].position = SolidPosition(rect.left, rect.top, 0.0f);
    vertices[1].position = SolidPosition(rect.right, rect.top, 0.0f);
    vertices[2].position = SolidPosition(rect.left, rect.bottom, 0.0f);
    vertices[3].position = SolidPosition(rect.right, rect.bottom, 0.0f);
    vertices[0].rhw = vertices[1].rhw = vertices[2].rhw = vertices[3].rhw = 1.0f;
    vertices[0].color = argb;
    vertices[1].color = argb;
    vertices[2].color = argb;
    vertices[3].color = argb;

    data_00491c30->Stage(0, 4, 2);
    data_00491c30->Stage(0, 1, 2);
    data_00491c30->Stage(0, 5, 0);
    data_00491c30->Stage(0, 2, 0);
    data_00491c30->State(20, 6);
    data_00491c30->Format(0x44);
    data_00491c30->Draw(5, 2, vertices, sizeof(SolidVertex));

    manager->cached_format = 0xff;
    manager->cached_texture = 0;
    manager->cached_color = 0;
    manager->cached_unknown_69 = 0xff;
    manager->cached_blend = 3;
    manager->cached_unknown_6b = 0xff;

    data_00491c30->Stage(0, 4, 4);
    data_00491c30->Stage(0, 1, 4);
    data_00491c30->Stage(0, 5, 2);
    data_00491c30->Stage(0, 2, 2);
    return 1;
}
#pragma code_seg()
