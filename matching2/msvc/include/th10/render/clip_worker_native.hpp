#pragma once
#include <stddef.h>
struct ClipVec3 { float x,y,z; };
struct ClipVertex { ClipVec3 position; float u,v; };
struct ClipMirrorVertex { ClipVec3 position; unsigned int color; float u,v; };
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
struct ClipHost {
    unsigned char reserved[0x3ada74];
    ClipBuffer *buffer;
    ClipVertex vertices[4];
    __declspec(noinline) void InitializeClip();
};
typedef char ClipVertexSize[sizeof(ClipVertex)==20?1:-1];
typedef char ClipMirrorSize[sizeof(ClipMirrorVertex)==24?1:-1];
typedef char ClipBufferOffset[offsetof(ClipHost,buffer)==0x3ada74?1:-1];
typedef char ClipVerticesOffset[offsetof(ClipHost,vertices)==0x3ada78?1:-1];
typedef char ClipCreateOffset[offsetof(ClipDeviceVtable,CreateVertexBuffer)==0x68?1:-1];
typedef char ClipStreamOffset[offsetof(ClipDeviceVtable,SetStreamSource)==0x190?1:-1];
extern "C" ClipDevice *g_d3d_device;
extern "C" ClipHost *g_sprt_ctrl;
extern "C" ClipMirrorVertex g_clip_mirror_vertices[4];
