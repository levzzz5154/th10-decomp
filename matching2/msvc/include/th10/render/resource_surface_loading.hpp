#ifndef TH10_RESOURCE_SURFACE_LOADING_HPP
#define TH10_RESOURCE_SURFACE_LOADING_HPP
struct ResourceView {
    virtual long __stdcall QueryInterface(const void*, void**) = 0;
    virtual unsigned long __stdcall AddRef() = 0;
    virtual unsigned long __stdcall Release() = 0;
};
struct ImageInfo {
    unsigned int width, height, depth, mipLevels, format, resourceType, fileFormat;
};
struct SurfaceRect {
    int left, top, right, bottom;
};
struct SurfacePoint {
    int x, y;
};
struct AnimationManagerIndexed {
    unsigned char pad[0x3ad4e0];
    ResourceView* primary[32];
    ResourceView* secondary[32];
    void* memory[32];
    int memorySize[32];
    ImageInfo info[32];
    __declspec(noinline) void Clear(int index);
    // 0x00447FD0
    __declspec(noinline) void CopyToBackBuffer(int index, int left, int top, int x, int y);
    __declspec(noinline) void CopyRectToBackBuffer(int index, int x, int y, int left, int top,
                                                   int width, int height);
    __declspec(noinline) void CaptureBackBufferImage(int index, int left, int top, int width, int height,
                                                     int target_left, int target_top,
                                                     int target_width, int target_height);
};
struct SurfaceDevice {
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
    virtual long __stdcall GetBackBuffer(unsigned int swap_chain, unsigned int index, int type, ResourceView** result) = 0;
    virtual void __stdcall Reserved19() = 0;
    virtual void __stdcall Reserved20() = 0;
    virtual void __stdcall Reserved21() = 0;
    virtual void __stdcall Reserved22() = 0;
    virtual void __stdcall Reserved23() = 0;
    virtual void __stdcall Reserved24() = 0;
    virtual void __stdcall Reserved25() = 0;
    virtual void __stdcall Reserved26() = 0;
    virtual void __stdcall Reserved27() = 0;
    virtual long __stdcall CreateRenderTarget(unsigned int width, unsigned int height, int format, int multisample, unsigned int quality, int lockable, ResourceView** result, void* shared) = 0;
    virtual void __stdcall Reserved29() = 0;
    virtual long __stdcall UpdateSurface(ResourceView* source, const SurfaceRect* source_rect, ResourceView* destination, const SurfacePoint* destination_point) = 0;
    virtual void __stdcall Reserved31() = 0;
    virtual void __stdcall Reserved32() = 0;
    virtual void __stdcall Reserved33() = 0;
    virtual void __stdcall Reserved34() = 0;
    virtual void __stdcall Reserved35() = 0;
    virtual long __stdcall CreateOffscreenPlainSurface(unsigned int width, unsigned int height, int format, int pool, ResourceView** result, void* shared) = 0;
};
extern "C" SurfaceDevice* g_d3d_device;
extern "C" int g_render_target_format;
extern "C" char str_string_format[], str_cannot_load_format[];
extern "C" int __cdecl sprintf(char*, const char*, ...);
extern "C" void __cdecl ReleaseHeapMemory(void*);
extern "C" long __stdcall LoadSurfaceFile(ResourceView*, const void*, const void*, const void*, unsigned int, const void*, unsigned int, unsigned int, ImageInfo*);
extern "C" long __stdcall LoadSurfaceCopy(ResourceView*, const void*, const void*, ResourceView*, const void*, const void*, unsigned int, unsigned int);
extern "C" __declspec(noinline) int __fastcall AnimationLoadSurface_00447c80(AnimationManagerIndexed*,const char*,int);
extern "C" __declspec(noinline) int __stdcall AnimationLoadMemory_00447ec0(int,AnimationManagerIndexed*,const char*);
#endif
