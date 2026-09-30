#pragma once

// Pretransformed XYZRHW, diffuse color, and one texture coordinate pair.
// The fillers only write RHW, color, and UV; XYZ is prepared separately.
struct EdgeStripVertex {
    float x;
    float y;
    float z;
    float rhw;
    unsigned int color;
    float u;
    float v;
};

struct EdgeStripRect {
    unsigned char unknown_000[0x20];
    float left;    // +0x20
    float top;     // +0x24
    float right;   // +0x28
    float bottom;  // +0x2C
};

struct EdgeStripSurface {
    unsigned char unknown_000[0x54];
    float base_x;  // +0x54
    float base_y;  // +0x58
    unsigned char unknown_05c[0x2FC - 0x5C];
    unsigned int color;  // +0x2FC
    unsigned char unknown_300[0x394 - 0x300];
    const EdgeStripRect* rect;  // +0x394

    __declspec(noinline) int FillHorizontal(int count, EdgeStripVertex* vertices) const;
    __declspec(noinline) int FillVertical(int count, EdgeStripVertex* vertices) const;
};
