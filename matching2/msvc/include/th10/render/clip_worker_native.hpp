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
struct ClipHost_004462f0 {
    unsigned char reserved[0x3ada74];
    ClipBuffer *buffer;
    ClipVertex vertices[4];
    __declspec(noinline) void InitializeClip();
};
typedef char ClipVertexSize[sizeof(ClipVertex)==20?1:-1];
typedef char ClipMirrorSize[sizeof(ClipMirrorVertex)==24?1:-1];
typedef char ClipBufferOffset[offsetof(ClipHost_004462f0,buffer)==0x3ada74?1:-1];
typedef char ClipVerticesOffset[offsetof(ClipHost_004462f0,vertices)==0x3ada78?1:-1];
typedef char ClipCreateOffset[offsetof(ClipDeviceVtable,CreateVertexBuffer)==0x68?1:-1];
typedef char ClipStreamOffset[offsetof(ClipDeviceVtable,SetStreamSource)==0x190?1:-1];
extern "C" ClipDevice *data_00491c30;
extern "C" ClipHost_004462f0 *g_sprt_ctrl;
extern "C" ClipMirrorVertex data_00497930[4];
