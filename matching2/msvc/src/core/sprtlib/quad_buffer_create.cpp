// 0x004462F0: build the unit quad every textured sprite is drawn with.
//
// The quad is 256 units square, centred on the origin, with its texture
// coordinates running 0..1. A second copy with room for a colour per vertex is
// kept in g_clip_mirror_vertices. The quad is uploaded to a new vertex buffer, which is
// left bound as stream 0.
//
// Native LTCG passes the host in EAX.
#include <string.h>
#include "th10/render/clip_worker_native.hpp"

#pragma code_seg(".text$a14clip")
void ClipHost::InitializeClip() {
    vertices[0].position.x = vertices[2].position.x = -128.0f;
    vertices[1].position.x = vertices[3].position.x = 128.0f;
    vertices[0].position.y = vertices[1].position.y = -128.0f;
    vertices[2].position.y = vertices[3].position.y = 128.0f;
    vertices[1].position.z = vertices[2].position.z = vertices[3].position.z =
        vertices[0].position.z = 0.0f;
    vertices[0].u = vertices[2].u = 0.0f;
    vertices[1].u = vertices[3].u = 1.0f;
    vertices[0].v = vertices[1].v = 0.0f;
    vertices[2].v = vertices[3].v = 1.0f;

    g_clip_mirror_vertices[0].position = vertices[0].position;
    g_clip_mirror_vertices[1].position = vertices[1].position;
    g_clip_mirror_vertices[2].position = vertices[2].position;
    g_clip_mirror_vertices[3].position = vertices[3].position;
    g_clip_mirror_vertices[0].u = vertices[0].u;
    g_clip_mirror_vertices[0].v = vertices[0].v;
    g_clip_mirror_vertices[1].u = vertices[1].u;
    g_clip_mirror_vertices[1].v = vertices[1].v;
    g_clip_mirror_vertices[2].u = vertices[2].u;
    g_clip_mirror_vertices[2].v = vertices[2].v;
    g_clip_mirror_vertices[3].u = vertices[3].u;
    g_clip_mirror_vertices[3].v = vertices[3].v;

    ClipDevice* device = g_d3d_device;
    device->vtable->CreateVertexBuffer(device, sizeof(vertices), 0, 0x102, 1, &buffer, 0);
    void* mapped;
    buffer->vtable->Lock(buffer, 0, 0, &mapped, 0);
    memcpy(mapped, vertices, sizeof(vertices));
    buffer->vtable->Unlock(buffer);
    device = g_d3d_device;
    device->vtable->SetStreamSource(device, 0, buffer, 0, sizeof(ClipVertex));
}
#pragma code_seg()
