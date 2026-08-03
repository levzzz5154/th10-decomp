#pragma once

#ifdef _MSC_VER
#include "th10/msvc_stdint.hpp"
#else
#include <cstdint>
#endif

// Pre-transformed vertex used by the render-target border strips
// (retail FVF XYZRHW | DIFFUSE | TEX1, 0x1C bytes per vertex).
struct EdgeStripVertex {
    float x;         // +0x00 (untouched by the fillers)
    float y;         // +0x04 (untouched by the fillers)
    float z;         // +0x08 (untouched by the fillers)
    float rhw;       // +0x0C, set to 1.0
    uint32_t color;  // +0x10, copied from the surface state
    float u;         // +0x14
    float v;         // +0x18
};

// UV rectangle block inside the render-target descriptor (+0x20..+0x2C).
struct EdgeStripRect {
    uint8_t reserved_00[0x20];
    float left;    // +0x20
    float top;     // +0x24
    float right;   // +0x28
    float bottom;  // +0x2C
};

// Fragment of the render-surface state referenced by both fillers. Retail
// offsets: base x at +0x54, base y at +0x58, diffuse color at +0x2FC, and
// the render-target descriptor pointer at +0x394 (a 32-bit slot in retail;
// the host layout pads it to the next pointer boundary).
struct EdgeStripSurface {
    uint8_t reserved_000[0x54];
    float base_x;               // +0x54
    float base_y;               // +0x58
    uint8_t reserved_05c[0x2fc - 0x5c];
    uint32_t color;             // +0x2FC
    uint8_t reserved_300[0x394 - 0x300];
    const EdgeStripRect* rect;  // +0x394
};

// 0x00444B10 - Fill the even/odd triangle-strip vertices of a horizontal
// border: u interpolated from right toward left, even vertices on the top
// edge and odd vertices on the bottom edge. Returns -1 when fewer than
// three vertices are requested.
int32_t RenderTarget_FillHorizontalEdgeStrip(const EdgeStripSurface* surface,
                                             int32_t count,
                                             EdgeStripVertex* vertices);

// 0x00444BE0 - Fill the even/odd triangle-strip vertices of a vertical
// border: v interpolated from bottom toward top, even vertices on the left
// edge and odd vertices on the right edge. Returns -1 when fewer than
// three vertices are requested.
int32_t RenderTarget_FillVerticalEdgeStrip(const EdgeStripSurface* surface,
                                           int32_t count,
                                           EdgeStripVertex* vertices);
