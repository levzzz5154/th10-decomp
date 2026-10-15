#ifndef TH10_RESOURCE_SURFACE_LOADING_HPP
#define TH10_RESOURCE_SURFACE_LOADING_HPP
struct Resource_00447f70 {
    virtual long __stdcall QueryInterface(const void*, void**) = 0;
    virtual unsigned long __stdcall AddRef() = 0;
    virtual unsigned long __stdcall Release() = 0;
};
struct ImageInfo_00447c80 {
    unsigned int width, height, depth, mipLevels, format, resourceType, fileFormat;
};
struct SurfaceRect_00447fd0 {
    int left, top, right, bottom;
};
struct SurfacePoint_00447fd0 {
    int x, y;
};
struct AnimationManagerIndexed_00447f70 {
    unsigned char pad[0x3ad4e0];
    Resource_00447f70* primary[32];
    Resource_00447f70* secondary[32];
    void* memory[32];
    int memorySize[32];
    ImageInfo_00447c80 info[32];
    __declspec(noinline) void Clear(int index);
    // 0x00447FD0
    __declspec(noinline) void CopyToBackBuffer(int index, int left, int top, int x, int y);
    __declspec(noinline) void CopyRectToBackBuffer(int index, int x, int y, int left, int top,
                                                   int width, int height);
    __declspec(noinline) void CaptureBackBufferImage(int index, int left, int top, int width, int height,
                                                     int target_left, int target_top,
                                                     int target_width, int target_height);
};
struct SurfaceDevice_00447c80 {
    virtual long __stdcall QueryInterface(const void*, void**) = 0;
    virtual unsigned long __stdcall AddRef() = 0;
    virtual unsigned long __stdcall Release() = 0;
    virtual void __stdcall Reserved3() = 0;
    virtual void __stdcall Reserved4() = 0;
    virtual void __stdcall Reserved5() = 0;
    virtual void __stdcall Reserved6() = 0;
    virtual void __stdcall Reserved7() = 0;
    virtual void __stdcall Reserved8() = 0;
    virtual void __stdcall Reserved9() = 0;
    virtual void __stdcall Reserved10() = 0;
    virtual void __stdcall Reserved11() = 0;
    virtual void __stdcall Reserved12() = 0;
    virtual void __stdcall Reserved13() = 0;
    virtual void __stdcall Reserved14() = 0;
    virtual void __stdcall Reserved15() = 0;
    virtual void __stdcall Reserved16() = 0;
    virtual void __stdcall Reserved17() = 0;
    virtual long __stdcall GetBackBuffer(unsigned int swap_chain, unsigned int index, int type, Resource_00447f70** result) = 0;
    virtual void __stdcall Reserved19() = 0;
    virtual void __stdcall Reserved20() = 0;
    virtual void __stdcall Reserved21() = 0;
    virtual void __stdcall Reserved22() = 0;
    virtual void __stdcall Reserved23() = 0;
    virtual void __stdcall Reserved24() = 0;
    virtual void __stdcall Reserved25() = 0;
    virtual void __stdcall Reserved26() = 0;
    virtual void __stdcall Reserved27() = 0;
    virtual long __stdcall CreateRenderTarget(unsigned int width, unsigned int height, int format, int multisample, unsigned int quality, int lockable, Resource_00447f70** result, void* shared) = 0;
    virtual void __stdcall Reserved29() = 0;
    virtual long __stdcall UpdateSurface(Resource_00447f70* source, const SurfaceRect_00447fd0* source_rect, Resource_00447f70* destination, const SurfacePoint_00447fd0* destination_point) = 0;
    virtual void __stdcall Reserved31() = 0;
    virtual void __stdcall Reserved32() = 0;
    virtual void __stdcall Reserved33() = 0;
    virtual void __stdcall Reserved34() = 0;
    virtual void __stdcall Reserved35() = 0;
    virtual long __stdcall CreateOffscreenPlainSurface(unsigned int width, unsigned int height, int format, int pool, Resource_00447f70** result, void* shared) = 0;
};
extern "C" SurfaceDevice_00447c80* g_d3d_device;
extern "C" int data_00491d14;
extern "C" char data_0046e1c8[], data_00470150[];
extern "C" int __cdecl sprintf(char*, const char*, ...);
extern "C" void __cdecl ReleaseHeapMemory_00452422(void*);
extern "C" long __stdcall LoadSurfaceFile_004521d0(Resource_00447f70*, const void*, const void*, const void*, unsigned int, const void*, unsigned int, unsigned int, ImageInfo_00447c80*);
extern "C" long __stdcall LoadSurfaceCopy_004521d6(Resource_00447f70*, const void*, const void*, Resource_00447f70*, const void*, const void*, unsigned int, unsigned int);
extern "C" __declspec(noinline) int __fastcall AnimationLoadSurface_00447c80(AnimationManagerIndexed_00447f70*,const char*,int);
extern "C" __declspec(noinline) int __stdcall AnimationLoadMemory_00447ec0(int,AnimationManagerIndexed_00447f70*,const char*);
#endif
