#include "th10/render/edge_strip_fillers.hpp"

// 0x00444B10..0x00444BD8. Fill alternating top and bottom vertices of a
// horizontal strip. Native LTCG supplies count in EAX, this in ECX, and
// vertices in EBX; the function returns with a plain RET.
#pragma code_seg(".text$01horizontal")
int EdgeStripSurface::FillHorizontal(int count, EdgeStripVertex* vertices) const {
    if (count < 3) return -1;

    const float u_start = base_x + rect->right;
    float v_edge = rect->top + base_y;
    const float step = (rect->right - rect->left) / ((count + 1) / 2 - 1);
    float u = u_start;

    // Each pass visits every other 0x1C-byte vertex, a 0x38-byte stride.
    for (int index = 0; index < count; index += 2) {
        EdgeStripVertex* vertex = vertices + index;
        vertex->u = u;
        u -= step;
        vertex->v = v_edge;
        vertex->color = color;
        vertex->rhw = 1.0f;
    }

    u = u_start;
    v_edge = rect->bottom + base_y;
    for (int index = 1; index < count; index += 2) {
        EdgeStripVertex* vertex = vertices + index;
        vertex->u = u;
        u -= step;
        vertex->v = v_edge;
        vertex->color = color;
        vertex->rhw = 1.0f;
    }
    return 0;
}
#pragma code_seg()
