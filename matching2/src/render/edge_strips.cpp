#include "th10/render/edge_strips.hpp"

// Both fillers walk the strip two vertices at a time (0x38 bytes), first
// writing the even vertices and then the odd ones, so a strip of N
// vertices alternates between the two border edges. Retail carries the
// vertex count in EAX and the vertex base in EBX; the readable
// signatures reify both.

// 0x00444B10 - Horizontal border strip. The u coordinate starts at
// base_x + rect.right and steps toward the left edge in
// (count + 1) / 2 - 1 increments; even vertices take the top edge's v
// and odd vertices the bottom edge's v (both offset by base_y).
int32_t RenderTarget_FillHorizontalEdgeStrip(const EdgeStripSurface* surface,
                                             int32_t count,
                                             EdgeStripVertex* vertices) {
    if (count <= 2) {
        return -1;
    }
    const EdgeStripRect* rect = surface->rect;
    const float u_start = surface->base_x + rect->right;
    const float step =
        (rect->right - rect->left) / (float)((count + 1) / 2 - 1);

    float u = u_start;
    const float v_even = rect->top + surface->base_y;
    const int32_t even_count = (int32_t)(((uint32_t)(count - 1) >> 1) + 1);
    for (int32_t index = 0; index < even_count; ++index) {
        EdgeStripVertex* vertex = &vertices[index * 2];
        vertex->rhw = 1.0f;
        vertex->color = surface->color;
        vertex->u = u;
        vertex->v = v_even;
        u -= step;
    }

    u = u_start;
    const float v_odd = rect->bottom + surface->base_y;
    const int32_t odd_count = (int32_t)(((uint32_t)(count - 2) >> 1) + 1);
    for (int32_t index = 0; index < odd_count; ++index) {
        EdgeStripVertex* vertex = &vertices[index * 2 + 1];
        vertex->rhw = 1.0f;
        vertex->color = surface->color;
        vertex->u = u;
        vertex->v = v_odd;
        u -= step;
    }
    return 0;
}

// 0x00444BE0 - Vertical border strip. The v coordinate starts at
// base_y + rect.bottom and steps toward the top edge in
// (count + 1) / 2 - 1 increments; even vertices take the left edge's u
// and odd vertices the right edge's u (both offset by base_x).

int32_t RenderTarget_FillVerticalEdgeStrip(const EdgeStripSurface* surface,
                                           int32_t count,
                                           EdgeStripVertex* vertices) {
    if (count <= 2) {
        return -1;
    }
    const EdgeStripRect* rect = surface->rect;
    const float v_start = surface->base_y + rect->bottom;
    const float step =
        (rect->bottom - rect->top) / (float)((count + 1) / 2 - 1);

    float v = v_start;
    const float u_even = rect->left + surface->base_x;
    const int32_t even_count = (int32_t)(((uint32_t)(count - 1) >> 1) + 1);
    for (int32_t index = 0; index < even_count; ++index) {
        EdgeStripVertex* vertex = &vertices[index * 2];
        vertex->rhw = 1.0f;
        vertex->color = surface->color;
        vertex->u = u_even;
        vertex->v = v;
        v -= step;
    }

    v = v_start;
    const float u_odd = rect->right + surface->base_x;
    const int32_t odd_count = (int32_t)(((uint32_t)(count - 2) >> 1) + 1);
    for (int32_t index = 0; index < odd_count; ++index) {
        EdgeStripVertex* vertex = &vertices[index * 2 + 1];
        vertex->rhw = 1.0f;
        vertex->color = surface->color;
        vertex->u = u_odd;
        vertex->v = v;
        v -= step;
    }
    return 0;
}
