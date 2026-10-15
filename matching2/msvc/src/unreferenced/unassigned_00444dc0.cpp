// 0x00444DC0: bind an entity texture and queue its quad vertices.
#include "th10/render/quad_batch.hpp"
#pragma code_seg(".text$06dquad")
int SprtCtrlBatchView::DrawQuad(const RenderEntity* entity, const TexturedVertex* vertices) {
    if (!(entity->flags & 1)) return -1;
    if (!(entity->flags & 2)) return -1;
    if (((const unsigned char*)&entity->color)[3] == 0) return -1;
    if (cached_texture != entity->texture->texture) {
        cached_texture = entity->texture->texture;
        Flush();
        data_00491c30->Texture(0, cached_texture);
    }
    if (cached_format != 1) {
        Flush();
        cached_format = 1;
    }
    SyncRenderState(entity);
    AppendQuad(vertices);
    return 0;
}
#pragma code_seg()
