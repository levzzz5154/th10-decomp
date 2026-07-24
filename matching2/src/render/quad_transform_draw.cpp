#include "th10/render/quad_transform_draw.hpp"

#include <cmath>

namespace {

const unsigned int kRequiredFlags = 3;
const unsigned int kScaleDirty = 4;
const unsigned int kTransformDirty = 8;
const unsigned int kFixedTransform = 0x4000;
const unsigned int kHorizontalAnchorShift = 18;
const unsigned int kVerticalAnchorShift = 20;
const unsigned int kAnchorMask = 3;
const int kWorldTransform = 0x100;
const int kTextureTransform = 0x10;
const int kVertexStride = 20;
const unsigned int kVertexFvf = 0x102;
const int kVertexMode = 2;

float AnchorOffset(unsigned int mode, float extent) {
    if (mode == 1) {
        return -std::fabs(extent * 0.5f);
    }
    if (mode == 2) {
        return std::fabs(extent * 0.5f);
    }
    return 0.0f;
}

}  // namespace

// 0x00444760 - Rebuild the quad's cached world transform when dirty, apply
// anchor placement and texture translation, synchronize render state, and draw
// the two-triangle quad. Invalid or hidden records return -1.
int Renderer_DrawTransformedQuad(TransformedQuad* quad,
                                 QuadRenderer* renderer,
                                 const QuadDrawEnv* env) {
    if ((quad->flags & kRequiredFlags) != kRequiredFlags ||
        !quad->drawable) {
        return -1;
    }

    if (renderer->pending) {
        env->flush();
        renderer->pending = 0;
    }

    if (!(quad->flags & kFixedTransform) &&
        (quad->flags & (kScaleDirty | kTransformDirty))) {
        quad->world = quad->base;
        quad->world.m[0] *= quad->scale[0];
        quad->world.m[5] *= quad->scale[1];
        quad->flags &= ~kTransformDirty;

        for (int axis = 0; axis < 3; ++axis) {
            if (quad->angle[axis] != 0.0f) {
                QuadMatrix rotation;
                QuadMatrix result;
                env->rotation(&rotation, axis, quad->angle[axis]);
                env->multiply(&result, &quad->world, &rotation);
                quad->world = result;
            }
        }
        quad->flags &= ~kScaleDirty;
    }

    QuadMatrix world = quad->world;
    const float x = quad->anchor[0] + quad->shared[0] + quad->local[0];
    const float y = quad->anchor[1] + quad->shared[1] + quad->local[1];
    const unsigned int horizontal_anchor =
        (quad->flags >> kHorizontalAnchorShift) & kAnchorMask;
    const unsigned int vertical_anchor =
        (quad->flags >> kVerticalAnchorShift) & kAnchorMask;

    if (horizontal_anchor != 3) {
        world.m[12] = x + AnchorOffset(
            horizontal_anchor, quad->size[0] * quad->scale[0]);
    }
    if (vertical_anchor != 3) {
        world.m[13] = y + AnchorOffset(
            vertical_anchor, quad->size[1] * quad->scale[1]);
    }
    world.m[14] =
        quad->anchor[2] + quad->local[2] + quad->shared[2];

    env->apply_state(quad);
    env->transform(kWorldTransform, &world);

    if (renderer->texture_handle != quad->texture->handle) {
        env->bind(quad->texture->handle);
        renderer->texture_handle = quad->texture->handle;
        renderer->texture_record = quad->texture;
    }

    QuadMatrix texture = quad->texture_matrix;
    texture.m[12] += quad->texture->u + quad->texoff[0];
    texture.m[13] += quad->texture->v + quad->texoff[1];
    env->transform(kTextureTransform, &texture);

    if (renderer->vertex_mode != kVertexMode) {
        env->stream(renderer->vertex_buffer, kVertexStride);
        env->fvf(kVertexFvf);
        env->stage(0, 6, 3);
        env->stage(0, 3, 3);
        renderer->vertex_mode = kVertexMode;
    }

    env->draw(5, 0, 2);
    return 0;
}
