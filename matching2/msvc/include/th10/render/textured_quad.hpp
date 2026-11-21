#pragma once

struct TexturedVertex {
    float x, y, z, rhw;
    unsigned int color;
    float u, v;
};

// The shared sprite quad both submit pipelines finish and append.
extern "C" TexturedVertex g_quad_vertices[4];

// Anchor modes: 0 centers the sprite, 1 fixes its near edge, 2 fixes its far edge.
static __forceinline void WriteAnchoredSpriteCorners(unsigned int flags, float width, float height,
                                                     float cosine, float sine, float center_x, float center_y) {
    float xs[4], ys[4];
    switch ((flags >> 18) & 3) {
    case 0:
        xs[0] = xs[2] = width * -0.5f;
        xs[1] = xs[3] = width * 0.5f;
        break;
    case 1:
        xs[0] = xs[2] = 0.0f;
        xs[1] = xs[3] = width;
        break;
    case 2:
        xs[0] = xs[2] = -width;
        xs[1] = xs[3] = 0.0f;
        break;
    }
    switch ((flags >> 20) & 3) {
    case 0:
        ys[0] = ys[1] = height * -0.5f;
        ys[2] = ys[3] = height * 0.5f;
        break;
    case 1:
        ys[0] = ys[1] = 0.0f;
        ys[2] = ys[3] = height;
        break;
    case 2:
        ys[0] = ys[1] = -height;
        ys[2] = ys[3] = 0.0f;
        break;
    }

    g_quad_vertices[0].x = xs[0] * cosine - ys[0] * sine + center_x;
    g_quad_vertices[0].y = xs[0] * sine + ys[0] * cosine + center_y;
    g_quad_vertices[1].x = xs[1] * cosine - ys[1] * sine + center_x;
    g_quad_vertices[1].y = xs[1] * sine + ys[1] * cosine + center_y;
    g_quad_vertices[2].x = xs[2] * cosine - ys[2] * sine + center_x;
    g_quad_vertices[2].y = xs[2] * sine + ys[2] * cosine + center_y;
    g_quad_vertices[3].x = xs[3] * cosine - ys[3] * sine + center_x;
    g_quad_vertices[3].y = xs[3] * sine + ys[3] * cosine + center_y;
}
