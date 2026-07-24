#include "th10/render/edge_strip_draw.hpp"

namespace {

const unsigned int kRequiredFlags = 3;
const unsigned int kTransformedTexturedFvf = 0x144;
const int kVertexMode = 3;
const int kTriangleStrip = 5;
const int kVertexStride = 28;

}  // namespace

// 0x00444CE0 - Draw a live textured edge strip, synchronizing the cached
// texture and vertex mode before issuing the triangle-strip draw.
int Renderer_DrawTexturedEdgeStrip(const EdgeStripRecord* strip,
                                   EdgeStripRenderer* renderer,
                                   const EdgeStripDrawEnv* env) {
    if ((strip->flags & kRequiredFlags) != kRequiredFlags ||
        !strip->drawable) {
        return -1;
    }

    if (renderer->pending) {
        env->flush();
        renderer->pending = 0;
    }

    if (renderer->texture != strip->texture) {
        env->bind_texture(strip->texture);
        renderer->texture = strip->texture;
    }

    if (renderer->mode != kVertexMode) {
        env->set_fvf(kTransformedTexturedFvf);
        renderer->mode = kVertexMode;
    }

    env->apply_state(strip);
    env->stage(0, 6, 0);
    env->stage(0, 3, 0);
    env->draw(kTriangleStrip, strip->vertex_count - 2,
              strip->primitive_count, kVertexStride);
    return 0;
}
