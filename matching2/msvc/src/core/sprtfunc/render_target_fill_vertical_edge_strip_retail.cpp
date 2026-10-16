#include "th10/render/edge_strip_fillers.hpp"

// 0x00444BE0..0x00444CA8. Fill alternating left and right vertices of a
// vertical strip. Native LTCG supplies count in EAX, this in ECX, and
// vertices in EBX; the function returns with a plain RET.
#pragma code_seg(".text$03vertical")
int EdgeStripSurface::FillVertical(int count, EdgeStripVertex* vertices) const {
    if (count < 3) return -1;

    const float v_start = base_y + rect->bottom;
    float u_edge = rect->left + base_x;
    const float step = (rect->bottom - rect->top) / ((count + 1) / 2 - 1);
    float v = v_start;

    for (int index = 0; index < count; index += 2) {
        EdgeStripVertex* vertex = vertices + index;
        vertex->v = v;
        v -= step;
        vertex->u = u_edge;
        vertex->color = color;
        vertex->rhw = 1.0f;
    }

    v = v_start;
    u_edge = rect->right + base_x;
    for (int index = 1; index < count; index += 2) {
        EdgeStripVertex* vertex = vertices + index;
        vertex->v = v;
        v -= step;
        vertex->u = u_edge;
        vertex->color = color;
        vertex->rhw = 1.0f;
    }
    return 0;
}
#pragma code_seg()
