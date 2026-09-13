#include "th10/render/quad_batch.hpp"
#pragma code_seg(".text$02gradient")
int __stdcall DrawGradientQuad(const ScreenRect* rect, unsigned int top_left, unsigned int top_right, unsigned int bottom_left, unsigned int bottom_right) {
    SolidVertex vertices[4];
    data_00491c10->Flush();
    vertices[0].position = SolidPosition(rect->left, rect->top, 0.0f);
    vertices[1].position = SolidPosition(rect->right, rect->top, 0.0f);
    vertices[2].position = SolidPosition(rect->left, rect->bottom, 0.0f);
    vertices[3].position = SolidPosition(rect->right, rect->bottom, 0.0f);
    vertices[0].rhw = vertices[1].rhw = vertices[2].rhw = vertices[3].rhw = 1.0f;
    vertices[0].color = top_left;
    vertices[1].color = top_right;
    vertices[2].color = bottom_left;
    vertices[3].color = bottom_right;
    data_00491c30->Stage(0, 4, 2);
    data_00491c30->Stage(0, 1, 2);
    data_00491c30->Stage(0, 5, 0);
    data_00491c30->Stage(0, 2, 0);
    data_00491c30->State(20, 6);
    data_00491c30->Format(0x44);
    data_00491c30->Draw(5, 2, vertices, sizeof(SolidVertex));
    unsigned char* cache = (unsigned char*)data_00491c10;
    cache[0x3ADA6A] = 0xFF;
    *(int*)(cache + 0x3ADA70) = 0;
    *(int*)(cache + 0x3ADA64) = 0;
    cache[0x3ADA69] = 0xFF;
    cache[0x3ADA68] = 3;
    cache[0x3ADA6B] = 0xFF;
    data_00491c30->Stage(0, 4, 4);
    data_00491c30->Stage(0, 1, 4);
    data_00491c30->Stage(0, 5, 2);
    return data_00491c30->Stage(0, 2, 2);
}
#pragma code_seg()
