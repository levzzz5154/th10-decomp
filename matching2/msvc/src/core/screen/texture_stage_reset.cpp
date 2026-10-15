#include "th10/render/quad_batch.hpp"
#pragma code_seg(".text$02gradient")
int __stdcall DrawGradientQuad(const ScreenRect* rect, unsigned int top_left, unsigned int top_right, unsigned int bottom_left, unsigned int bottom_right) {
    SolidVertex vertices[4];
    g_sprt_ctrl->Flush();
    vertices[0].position = SolidPosition(rect->left, rect->top, 0.0f);
    vertices[1].position = SolidPosition(rect->right, rect->top, 0.0f);
    vertices[2].position = SolidPosition(rect->left, rect->bottom, 0.0f);
    vertices[3].position = SolidPosition(rect->right, rect->bottom, 0.0f);
    vertices[0].rhw = vertices[1].rhw = vertices[2].rhw = vertices[3].rhw = 1.0f;
    vertices[0].color = top_left;
    vertices[1].color = top_right;
    vertices[2].color = bottom_left;
    vertices[3].color = bottom_right;
    g_d3d_device->Stage(0, 4, 2);
    g_d3d_device->Stage(0, 1, 2);
    g_d3d_device->Stage(0, 5, 0);
    g_d3d_device->Stage(0, 2, 0);
    g_d3d_device->State(20, 6);
    g_d3d_device->Format(0x44);
    g_d3d_device->Draw(5, 2, vertices, sizeof(SolidVertex));
    unsigned char* cache = (unsigned char*)g_sprt_ctrl;
    cache[0x3ADA6A] = 0xFF;
    *(int*)(cache + 0x3ADA70) = 0;
    *(int*)(cache + 0x3ADA64) = 0;
    cache[0x3ADA69] = 0xFF;
    cache[0x3ADA68] = 3;
    cache[0x3ADA6B] = 0xFF;
    g_d3d_device->Stage(0, 4, 4);
    g_d3d_device->Stage(0, 1, 4);
    g_d3d_device->Stage(0, 5, 2);
    return g_d3d_device->Stage(0, 2, 2);
}
#pragma code_seg()
