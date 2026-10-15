// 0x00442FE0: expand a four-vertex strip into two triangles in the batch.
#include "th10/render/quad_batch.hpp"
#pragma code_seg(".text$05happend")
int SprtCtrlBatchView::AppendQuad(const TexturedVertex* vertices) {
    cursor[0] = vertices[0];
    cursor[1] = vertices[1];
    cursor[2] = vertices[2];
    cursor[3] = vertices[1];
    cursor[4] = vertices[2];
    cursor[5] = vertices[3];
    cursor += 6;
    ++quad_count;
    return 0;
}
#pragma code_seg()
