#pragma once
#include <stddef.h>
#include <string.h>
struct RenderDevice;
struct RenderSurface;
struct RenderTexture;
struct RenderRect { long left,top,right,bottom; };
struct RenderXYWH { int x,y,width,height; };
struct RenderLock { int pitch; unsigned char* bits; };
struct RenderDeviceMethods {
    void* before_reset[0x40/4];
    long (__stdcall* Reset)(RenderDevice*,void*);
    long (__stdcall* Present)(RenderDevice*,const RenderRect*,const RenderRect*,void*,const void*);
    long (__stdcall* GetBackBuffer)(RenderDevice*,unsigned int,unsigned int,unsigned int,RenderSurface**);
    void* before_create_target[(0x70-0x4c)/4];
    long (__stdcall* CreateRenderTarget)(RenderDevice*,unsigned int,unsigned int,unsigned int,unsigned int,unsigned int,int,RenderSurface**,void**);
    void* before_create_plain[(0x90-0x74)/4];
    long (__stdcall* CreatePlain)(RenderDevice*,unsigned int,unsigned int,unsigned int,unsigned int,RenderSurface**,void**);
    void* before_stage[(0x10c-0x94)/4];
    long (__stdcall* Stage)(RenderDevice*,unsigned int,unsigned int,unsigned int);
    void* before_draw[(0x14c-0x110)/4];
    long (__stdcall* Draw)(RenderDevice*,unsigned int,unsigned int,const void*,unsigned int);
    void* before_fvf[(0x164-0x150)/4];
    long (__stdcall* SetFVF)(RenderDevice*,unsigned int);
};
struct RenderDevice { RenderDeviceMethods* methods; };
struct RenderSurfaceMethods {
    void* query; void* addref;
    unsigned long (__stdcall* Release)(RenderSurface*);
    void* before_lock[(0x34-0xc)/4];
    long (__stdcall* Lock)(RenderSurface*,RenderLock*,const RenderRect*,unsigned int);
    long (__stdcall* Unlock)(RenderSurface*);
};
struct RenderSurface { RenderSurfaceMethods* methods; };
struct RenderTextureMethods {
    void* before_level[0x48/4];
    long (__stdcall* GetLevel)(RenderTexture*,unsigned int,RenderSurface**);
};
struct RenderTexture { RenderTextureMethods* methods; };
struct RenderTextureEntry { RenderTexture* texture; unsigned char reserved[12]; };
struct RenderBank { unsigned char reserved[0x120]; RenderTextureEntry* entries; };
struct RenderTargetMetadata { unsigned int width,height,reserved[5]; };
struct NativeRenderManager {
    int primary_index,capture_bank;
    RenderXYWH capture_source,capture_destination;
    int capture_index;
    RenderXYWH primary_source,primary_destination;
    unsigned char reserved_04c[0x54-0x4c];
    int state_changes,draw_calls;
    float origin_x,origin_y;
    unsigned char reserved_064[0x3ad06c-0x64];
    RenderBank* banks[0x21];
    unsigned char reserved_3ad0f0[0x3ad4e0-0x3ad0f0];
    RenderSurface* primary[32];
    RenderSurface* secondary[32];
    void* memory[32];
    unsigned char reserved_3ad660[0x80];
    RenderTargetMetadata metadata[32];
    unsigned int cached_color;
    void* cached_texture;
    unsigned char cached_flags[8];
    unsigned char reserved_3ada70[0x3adac8-0x3ada70];
    int quad_count;
    unsigned char reserved_3adacc[0x72dacc-0x3adacc];
    void* cursor;
    void* batch_start;
    __declspec(noinline) void FinishTargets();
    __declspec(noinline) void Capture(int bank,int index,int sx,int sy,int sw,int sh,int dx,int dy,int dw,int dh);
    __declspec(noinline) void Prepare(int index,int sx,int sy,int sw,int sh,int dx,int dy,int dw,int dh);
    __declspec(noinline) int Flush();
    __declspec(noinline) void Clear(int index);
    __declspec(noinline) void ReleaseTargets();
};
#pragma pack(push,2)
struct BitmapFileImage { unsigned short type; unsigned int size; unsigned short reserved1,reserved2; unsigned int offset; };
#pragma pack(pop)
struct BitmapInfoImage { unsigned int size; long width,height; unsigned short planes,bits; unsigned int compression,image_size; long xppm,yppm; unsigned int colors,important,extra; };
struct ScreenshotState {
    unsigned char reserved_000[8];
    RenderDevice* device;
    unsigned char reserved_00c[0xec-0xc];
    unsigned int format;
    unsigned char reserved_0f0[0x50c-0xf0];
    unsigned int thread;
    BitmapFileImage file_image;
    unsigned char reserved_51e[2];
    BitmapInfoImage* info;
    unsigned char* pixels;
    char filename[256];
    __declspec(noinline) int CaptureScreenshot(const char* filename);
};
typedef char ManagerBanks[offsetof(NativeRenderManager,banks)==0x3ad06c?1:-1];
typedef char ManagerPrimary[offsetof(NativeRenderManager,primary)==0x3ad4e0?1:-1];
typedef char ManagerMetadata[offsetof(NativeRenderManager,metadata)==0x3ad6e0?1:-1];
typedef char ManagerCount[offsetof(NativeRenderManager,quad_count)==0x3adac8?1:-1];
typedef char ManagerCursor[offsetof(NativeRenderManager,cursor)==0x72dacc?1:-1];
typedef char ScreenshotHeader[offsetof(ScreenshotState,file_image)==0x510?1:-1];
typedef char ScreenshotInfo[offsetof(ScreenshotState,info)==0x520?1:-1];
typedef char ScreenshotName[offsetof(ScreenshotState,filename)==0x528?1:-1];
typedef char DeviceBackBuffer[offsetof(RenderDeviceMethods,GetBackBuffer)==0x48?1:-1];
typedef char DeviceCreateTarget[offsetof(RenderDeviceMethods,CreateRenderTarget)==0x70?1:-1];
typedef char DeviceCreatePlain[offsetof(RenderDeviceMethods,CreatePlain)==0x90?1:-1];
extern "C" {
extern NativeRenderManager* data_00491c10;
extern RenderDevice* data_00491c30;
extern ScreenshotState data_00491c28;
extern unsigned int data_00491fd4,data_00474e36,data_00492134,data_00491d14;
extern char data_00491d0c[],data_0046f6e4[],data_0046f6d0[],data_0046deb0[],data_0046df38[],data_0046def0[];
void __cdecl Renderer_ApplyDeviceDefaults();
int __cdecl MakeDirectory_00452abc(const char*);
int __cdecl FormatString_00452ae8(char*,const char*,...);
int __stdcall FileProbe_0044b4d0(const char*);
long __stdcall CopySurface_004521d6(RenderSurface*,const void*,const RenderRect*,RenderSurface*,const void*,const RenderRect*,unsigned int,unsigned int);
void __cdecl entry_free_00452422(void*);
void* __cdecl retail_malloc_00452706(unsigned int);
unsigned int __cdecl retail_beginthread_00452eec(void (__cdecl*)(void*),unsigned int,void*);
void __cdecl ScreenshotWriter(void*);
extern void (__stdcall* data_004660ac)(unsigned int);
}
