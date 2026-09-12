#include "th10/render/final_quad_pipeline.hpp"
#include "th10/render/animation_manager.hpp"

#include <cmath>

// 0x00442670 - Finish the shared sprite quad and stage it for the batch.
//
// Retail ABI: the animation VM arrives in EAX, the animation manager in ECX
// and the mode byte on the stack (`retn 4`). The quad itself is the file
// static at 0x004978C0 that 0x00443080 and its siblings have just filled
// with corner positions.
int Quad_SubmitFinal(QuadSubmitVertex quad[4], const QuadSubmitVm* vm,
                     QuadSubmitManager* manager, const QuadSubmitEnv* env,
                     unsigned int mode) {
    // Eight `fadd dword ptr [esi+5Ch]` / `[esi+60h]` pairs: the manager's
    // screen origin is added to every corner.
    for (int corner = 0; corner < 4; ++corner) {
        quad[corner].x = quad[corner].x + manager->offset_x;
        quad[corner].y = quad[corner].y + manager->offset_y;
    }

    if ((mode & 1) != 0) {
        // loc_442764's predecessor: `frndint` then `fsub ds:flt_4700EC`,
        // where flt_4700EC is 0.5f. Only four coordinates are rounded -
        // vertex 0's x and y, vertex 1's x and vertex 2's y - and each
        // result is stored to both vertices that share that edge, so the
        // snap assumes an axis-aligned quad. frndint follows the x87
        // rounding mode, which the game leaves at round-to-nearest-even;
        // nearbyint is that same operation.
        const float left = std::nearbyint(quad[0].x) - 0.5f;
        const float right = std::nearbyint(quad[1].x) - 0.5f;
        const float top = std::nearbyint(quad[0].y) - 0.5f;
        const float bottom = std::nearbyint(quad[2].y) - 0.5f;
        quad[2].y = bottom;
        quad[3].y = bottom;
        quad[0].y = top;
        quad[1].y = top;
        quad[1].x = right;
        quad[3].x = right;
        quad[0].x = left;
        quad[2].x = left;
    }

    // loc_442764: the sprite's four texture coordinates plus the VM's uv
    // scroll at vm+0x54 (u) and vm+0x58 (v). Sprite +0x20/+0x28 are the u
    // pair and +0x24/+0x2C the v pair.
    const QuadSubmitSprite* sprite = vm->sprite;
    const float u_left = sprite->u0 + vm->uv_scroll_x;
    const float u_right = sprite->u1 + vm->uv_scroll_x;
    const float v_top = sprite->v0 + vm->uv_scroll_y;
    const float v_bottom = sprite->v1 + vm->uv_scroll_y;
    quad[2].u = u_left;
    quad[0].u = u_left;
    quad[3].u = u_right;
    quad[1].u = u_right;
    quad[1].v = v_top;
    quad[0].v = v_top;
    quad[3].v = v_bottom;
    quad[2].v = v_bottom;

    float maximum_x = quad[0].x <= quad[1].x ? quad[1].x : quad[0].x;
    if (quad[2].x > maximum_x) maximum_x = quad[2].x;
    if (quad[3].x > maximum_x) maximum_x = quad[3].x;
    float maximum_y = quad[0].y <= quad[1].y ? quad[1].y : quad[0].y;
    if (quad[2].y > maximum_y) maximum_y = quad[2].y;
    if (quad[3].y > maximum_y) maximum_y = quad[3].y;
    float minimum_x = quad[0].x >= quad[1].x ? quad[1].x : quad[0].x;
    if (quad[2].x < minimum_x) minimum_x = quad[2].x;
    if (quad[3].x < minimum_x) minimum_x = quad[3].x;
    float minimum_y = quad[0].y >= quad[1].y ? quad[1].y : quad[0].y;
    if (quad[2].y < minimum_y) minimum_y = quad[2].y;
    if (quad[3].y < minimum_y) minimum_y = quad[3].y;

    // loc_44292C: the quad's bounding box against the active viewport. The
    // four `fild` loads treat the viewport words as unsigned - each is
    // followed by a `jge` past `fadd ds:flt_470B98`, 4294967296.0f - so the
    // comparison operands are the unsigned sums retail forms.
    const unsigned int clip_right = manager->clip_x + manager->clip_width;
    const unsigned int clip_bottom = manager->clip_y + manager->clip_height;
    if (!(maximum_x >= (float)manager->clip_x &&
          (float)manager->clip_y <= maximum_y &&
          (float)clip_right >= minimum_x &&
          (float)clip_bottom >= minimum_y)) {
        return 0;
    }

    // loc_4429BF's tail: a sprite whose texture differs from the manager's
    // cached one closes the open batch before SetTexture(0, texture).
    if (manager->cached_texture != sprite->texture) {
        manager->cached_texture = sprite->texture;
        env->flush();
        env->set_texture(manager->cached_texture);
    }
    // loc_442A01: the manager's "textured pipeline" byte at +0x3ADA6A. Any
    // other value means the batch in flight was staged for a different
    // pipeline, so it is drawn before the byte is claimed.
    if (manager->textured != 1) {
        env->flush();
        manager->textured = 1;
    }

    if ((mode & 2) == 0) {
        // `test ah, ah / jns` on vm+0x35C: bit 15 selects the VM's second
        // colour register at +0x300 over the first at +0x2FC.
        unsigned int color = (vm->flags & 0x8000u) != 0 ? vm->color_secondary
                                                        : vm->color_primary;
        if (manager->fade_enabled != 0) {
            // Four 0x004423C0 calls against the fade bytes at
            // manager+0x732458 (blue), +0x732459 (green), +0x73245A (red)
            // and +0x73245B (alpha). Every call reads the original channel:
            // retail writes each result back into a scratch dword whose
            // other bytes it has not touched yet.
            const unsigned int red =
                AnimationColor_MultiplyChannel(color >> 16, manager->fade[2]);
            const unsigned int green =
                AnimationColor_MultiplyChannel(color >> 8, manager->fade[1]);
            const unsigned int blue =
                AnimationColor_MultiplyChannel(color, manager->fade[0]);
            const unsigned int alpha =
                AnimationColor_MultiplyChannel(color >> 24, manager->fade[3]);
            color = (alpha << 24) | (red << 16) | (green << 8) | blue;
        }
        // loc_442A94: the colour lands in all four vertices, which is what
        // 0x00442F50's D3DTA_DIFFUSE ARG2 selectors then modulate with.
        quad[0].color = color;
        quad[1].color = color;
        quad[2].color = color;
        quad[3].color = color;
    }

    env->sync_render_state(vm->flags);
    env->append(quad);
    return 0;
}
