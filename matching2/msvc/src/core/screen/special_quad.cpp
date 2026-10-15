#include "th10/render/quad_batch.hpp"
#pragma code_seg(".text$01quad")
int __stdcall DrawSolidQuad(const ScreenRect* rect, unsigned int color) {
    SolidVertex vertices[4];
    g_sprt_ctrl->Flush();
    vertices[0].position = SolidPosition(rect->left, rect->top, 0.0f);
    vertices[1].position = SolidPosition(rect->right, rect->top, 0.0f);
    vertices[2].position = SolidPosition(rect->left, rect->bottom, 0.0f);
    vertices[3].position = SolidPosition(rect->right, rect->bottom, 0.0f);
    vertices[0].rhw = vertices[1].rhw = vertices[2].rhw = vertices[3].rhw = 1.0f;
    vertices[0].color = vertices[1].color = vertices[2].color = vertices[3].color = color;
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
