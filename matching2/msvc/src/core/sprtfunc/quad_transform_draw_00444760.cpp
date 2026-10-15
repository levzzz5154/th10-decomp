// 0x00444760..0x00444B00 (929 bytes): draw one entity's quad through the
// hardware-transform pipeline, with the world matrix and the texture-stage
// matrix both derived from the entity's stored transforms.
//
// Retail enters with the entity in EAX and the manager on the stack (the callee
// pops it); the dispatcher 0x004451C0 marshals `push ecx; call 0x00444760`.
#include <math.h>
#include "th10/render/quad_batch.hpp"

struct RenderMatrix4x4 {
    float m[16];
};
struct RenderEntityMatrixView {
    unsigned char pad_000[0x23C];
    RenderMatrix4x4 local_transform;
    RenderMatrix4x4 world_transform;
    RenderMatrix4x4 texture_transform;
};

extern "C" double data_00470b70;
extern "C" __declspec(noinline) void SyncRenderState_004423e0(
        SprtCtrlBatchView* manager, RenderEntity* entity);
extern "C" void __stdcall asm_D3DXMatrixRotationX_004521ac(RenderMatrix4x4* out, float angle);
extern "C" void __stdcall asm_D3DXMatrixRotationY_004521b8(RenderMatrix4x4* out, float angle);
extern "C" void __stdcall asm_D3DXMatrixRotationZ_004521be(RenderMatrix4x4* out, float angle);
extern "C" void __stdcall asm_D3DXMatrixMultiply_004521b2(RenderMatrix4x4* out,
                                                          const RenderMatrix4x4* left,
                                                          const RenderMatrix4x4* right);

#pragma code_seg(".text$06b09z00transform")
extern "C" __declspec(noinline) int EntityDraw_00444760(RenderEntity* entity,
                                                        SprtCtrlBatchView* manager);
int EntityDraw_00444760(RenderEntity* entity, SprtCtrlBatchView* manager) {
    RenderMatrix4x4 world;
    RenderMatrix4x4 rotation;
    RenderMatrix4x4 tex_matrix;

    unsigned int flags = entity->flags;
    if (!(flags & 1)) return -1;
    if (!(flags & 2)) return -1;
    if (((const unsigned char*)&entity->color)[3] == 0) return -1;

    if (manager->quad_count) manager->Flush();

    flags = entity->flags;
    if ((flags & 0x4000u) == 0 && (flags & 0x0Cu) != 0) {
        RenderEntityMatrixView* const view = (RenderEntityMatrixView*)entity;
        view->world_transform = view->local_transform;
        view->world_transform.m[0] *= entity->scale_x;
        view->world_transform.m[5] *= entity->scale_y;
        flags &= 0xFFFFFFF7u;
        entity->flags = flags;
        if (entity->rotation.x != data_00470b70) {
            asm_D3DXMatrixRotationX_004521ac(&rotation, entity->rotation.x);
            asm_D3DXMatrixMultiply_004521b2(&view->world_transform, &view->world_transform, &rotation);
        }
        if (entity->rotation.y != data_00470b70) {
            asm_D3DXMatrixRotationY_004521b8(&rotation, entity->rotation.y);
            asm_D3DXMatrixMultiply_004521b2(&view->world_transform, &view->world_transform, &rotation);
        }
        if (entity->rotation.z != data_00470b70) {
            asm_D3DXMatrixRotationZ_004521be(&rotation, entity->rotation.z);
            asm_D3DXMatrixMultiply_004521b2(&view->world_transform, &view->world_transform, &rotation);
        }
        entity->flags &= 0xFFFFFFFBu;
    }

    RenderEntityMatrixView* const view = (RenderEntityMatrixView*)entity;
    world = view->world_transform;
    switch ((entity->flags >> 18) & 3u) {
    case 0:
        world.m[12] = entity->render_offset.x + entity->position.x + entity->base_position.x;
        break;
    case 1:
        world.m[12] = (entity->render_offset.x + entity->position.x + entity->base_position.x)
                    - fabsf(entity->sprite_width * entity->scale_x * 0.5f);
        break;
    case 2:
        world.m[12] = fabsf(entity->sprite_width * entity->scale_x * 0.5f)
                    + entity->render_offset.x + entity->position.x + entity->base_position.x;
        break;
    }
    switch ((entity->flags >> 20) & 3u) {
    case 0:
        world.m[13] = entity->render_offset.y + entity->position.y + entity->base_position.y;
        break;
    case 1:
        world.m[13] = (entity->render_offset.y + entity->position.y + entity->base_position.y)
                    - fabsf(entity->sprite_height * entity->scale_y * 0.5f);
        break;
    case 2:
        world.m[13] = fabsf(entity->sprite_height * entity->scale_y * 0.5f)
                    + entity->render_offset.y + entity->position.y + entity->base_position.y;
        break;
    }
    world.m[14] = entity->base_position.z + entity->position.z;
    SyncRenderState_004423e0(manager, entity);
    world.m[14] = entity->render_offset.z + entity->base_position.z + entity->position.z;

    RenderDevice* device = g_d3d_device;
    typedef long (__stdcall *SetTransform)(void*, unsigned int, const void*);
    ((SetTransform)device->vtable[0xB0 / 4])(device, 0x100, &world);

    if (manager->cached_texture != entity->texture->texture) {
        void* texture = entity->texture->texture;
        manager->cached_texture = texture;
        RenderDevice* const volatile& current_device = g_d3d_device;
        RenderDevice* texture_device = current_device;
        typedef long (__stdcall *SetTexture)(void*, unsigned int, void*);
        ((SetTexture)texture_device->vtable[0x104 / 4])(texture_device, 0, texture);
    }

    const unsigned char format = 2;
    if (*(void**)((unsigned char*)manager + 0x3ADA70) != entity->texture) goto update_stage;
    if (entity->uv_scroll_x != 0.0f) goto update_stage;
    if (entity->uv_scroll_x == 0.0f) goto skip_stage;
update_stage:
    {
        *(void**)((unsigned char*)manager + 0x3ADA70) = entity->texture;
        tex_matrix = view->texture_transform;
        tex_matrix.m[8] = entity->texture->u0 + entity->uv_scroll_x;
        tex_matrix.m[9] = entity->texture->v0 + entity->uv_scroll_y;
        RenderDevice* tex_device = g_d3d_device;
        ((SetTransform)tex_device->vtable[0xB0 / 4])(tex_device, 0x10, &tex_matrix);
    }
skip_stage:

    if (manager->cached_format != format) {
        RenderDevice* stream_device = g_d3d_device;
        typedef long (__stdcall *SetStreamSource)(void*, unsigned int, void*, unsigned int, unsigned int);
        ((SetStreamSource)stream_device->vtable[0x190 / 4])(
            stream_device, 0, *(void**)((unsigned char*)manager + 0x3ADA74), 0, 20);
        g_d3d_device->Format(0x102);
        g_d3d_device->Stage(0, 6, 3);
        g_d3d_device->Stage(0, 3, 3);
        manager->cached_format = format;
    }
    RenderDevice* draw_device = g_d3d_device;
    typedef long (__stdcall *DrawPrimitive)(void*, unsigned int, unsigned int, unsigned int);
    ((DrawPrimitive)draw_device->vtable[0x144 / 4])(draw_device, 5, 0, format);
    return 0;
}
#pragma code_seg()
