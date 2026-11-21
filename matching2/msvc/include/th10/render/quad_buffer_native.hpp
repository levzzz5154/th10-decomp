#pragma once
#include <stddef.h>
struct ClipVec3 { float x,y,z; };
struct SpriteQuadVertex { ClipVec3 position; float u,v; };
struct SpriteQuadColorVertex { ClipVec3 position; unsigned int color; float u,v; };
struct ClipBuffer;
struct ClipBufferVtable {
    void *unused[11];
    long (__stdcall *Lock)(ClipBuffer*,unsigned int,unsigned int,void**,unsigned int);
    long (__stdcall *Unlock)(ClipBuffer*);
};
struct ClipBuffer { ClipBufferVtable *vtable; };
struct ClipDevice;
struct ClipDeviceVtable {
    void *unused[26];
    long (__stdcall *CreateVertexBuffer)(ClipDevice*,unsigned int,unsigned int,unsigned int,int,ClipBuffer**,void*);
    void *unused_27_to_99[73];
    long (__stdcall *SetStreamSource)(ClipDevice*,unsigned int,ClipBuffer*,unsigned int,unsigned int);
};
struct ClipDevice { ClipDeviceVtable *vtable; };
struct SprtCtrl {
    unsigned char reserved[0x3ada74];
    ClipBuffer *buffer;
    SpriteQuadVertex vertices[4];
    __declspec(noinline) void CreateQuadVertexBuffer();
};
typedef char ClipVertexSize[sizeof(SpriteQuadVertex)==20?1:-1];
typedef char ClipMirrorSize[sizeof(SpriteQuadColorVertex)==24?1:-1];
typedef char ClipBufferOffset[offsetof(SprtCtrl,buffer)==0x3ada74?1:-1];
typedef char ClipVerticesOffset[offsetof(SprtCtrl,vertices)==0x3ada78?1:-1];
typedef char ClipCreateOffset[offsetof(ClipDeviceVtable,CreateVertexBuffer)==0x68?1:-1];
typedef char ClipStreamOffset[offsetof(ClipDeviceVtable,SetStreamSource)==0x190?1:-1];
extern "C" ClipDevice *g_d3d_device;
extern "C" SprtCtrl *g_sprt_ctrl;
extern "C" SpriteQuadColorVertex g_sprite_quad_vertices[4];
