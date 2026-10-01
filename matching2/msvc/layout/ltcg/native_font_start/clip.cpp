#include <string.h>
#include "th10/render/clip_worker_native.hpp"
#pragma code_seg(".text$a08clip")
void ClipHost_004462f0::InitializeClip() {
    // Four XYZ/UV vertices; the color words belong only to the mirror.
    vertices[0].position.z=0.0f;vertices[3].position.z=0.0f;
    vertices[2].position.z=0.0f;vertices[1].position.z=0.0f;
    vertices[2].u=0.0f;vertices[0].u=0.0f;
    vertices[1].v=0.0f;vertices[0].v=0.0f;
    vertices[3].position.x=128.0f;vertices[1].position.x=128.0f;
    vertices[3].position.y=128.0f;vertices[2].position.y=128.0f;
    vertices[3].v=1.0f;vertices[2].v=1.0f;
    vertices[3].u=1.0f;vertices[1].u=1.0f;
    vertices[2].position.x=-128.0f;vertices[0].position.x=-128.0f;
    vertices[1].position.y=-128.0f;vertices[0].position.y=-128.0f;
    data_00497930[0].position=vertices[0].position;
    data_00497930[1].position=vertices[1].position;
    data_00497930[2].position=vertices[2].position;
    data_00497930[3].position=vertices[3].position;
    data_00497930[0].u=vertices[0].u;data_00497930[0].v=vertices[0].v;
    data_00497930[1].u=vertices[1].u;data_00497930[1].v=vertices[1].v;
    data_00497930[2].u=vertices[2].u;data_00497930[2].v=vertices[2].v;
    data_00497930[3].u=vertices[3].u;data_00497930[3].v=vertices[3].v;
    ClipDevice *device=data_00491c30;
    device->vtable->CreateVertexBuffer(device,80,0,0x102,1,&buffer,0);
    void *mapped;
    buffer->vtable->Lock(buffer,0,0,&mapped,0);
    memcpy(mapped,vertices,sizeof(vertices));
    buffer->vtable->Unlock(buffer);
    device=data_00491c30;
    device->vtable->SetStreamSource(device,0,buffer,0,sizeof(ClipVertex));
}
#pragma code_seg()
