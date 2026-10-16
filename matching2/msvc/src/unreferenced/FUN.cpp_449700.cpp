// 0x00449700: clear the top level of a Direct3D 9 texture to zero.
#include <string.h>
struct SurfaceDesc3 {
    int format;
    int type;
    unsigned long usage;
    int pool;
    int multisample_type;
    unsigned long multisample_quality;
    unsigned int width;
    unsigned int height;
};
struct LockedRect4 {
    int pitch;
    void* bits;
};
struct Surface4 {
    virtual long __stdcall QueryInterface(const void* iid, void** object) = 0;
    virtual unsigned long __stdcall AddRef() = 0;
    virtual unsigned long __stdcall Release() = 0;
    virtual long __stdcall GetDevice(void** device) = 0;
    virtual long __stdcall SetPrivateData(const void* guid, const void* data, unsigned long size, unsigned long flags) = 0;
    virtual long __stdcall GetPrivateData(const void* guid, void* data, unsigned long* size) = 0;
    virtual long __stdcall FreePrivateData(const void* guid) = 0;
    virtual unsigned long __stdcall SetPriority(unsigned long priority) = 0;
    virtual unsigned long __stdcall GetPriority() = 0;
    virtual void __stdcall PreLoad() = 0;
    virtual int __stdcall GetType() = 0;
    virtual long __stdcall GetContainer(const void* iid, void** container) = 0;
    virtual long __stdcall GetDesc(SurfaceDesc3* desc) = 0;
    virtual long __stdcall LockRect(LockedRect4* locked, const void* rect, unsigned long flags) = 0;
    virtual long __stdcall UnlockRect() = 0;
};
struct Texture3 {
    virtual long __stdcall QueryInterface(const void* iid, void** object) = 0;
    virtual unsigned long __stdcall AddRef() = 0;
    virtual unsigned long __stdcall Release() = 0;
    virtual long __stdcall GetDevice(void** device) = 0;
    virtual long __stdcall SetPrivateData(const void* guid, const void* data, unsigned long size, unsigned long flags) = 0;
    virtual long __stdcall GetPrivateData(const void* guid, void* data, unsigned long* size) = 0;
    virtual long __stdcall FreePrivateData(const void* guid) = 0;
    virtual unsigned long __stdcall SetPriority(unsigned long priority) = 0;
    virtual unsigned long __stdcall GetPriority() = 0;
    virtual void __stdcall PreLoad() = 0;
    virtual int __stdcall GetType() = 0;
    virtual unsigned long __stdcall SetLOD(unsigned long lod) = 0;
    virtual unsigned long __stdcall GetLOD() = 0;
    virtual unsigned long __stdcall GetLevelCount() = 0;
    virtual long __stdcall SetAutoGenFilterType(int filter) = 0;
    virtual int __stdcall GetAutoGenFilterType() = 0;
    virtual void __stdcall GenerateMipSubLevels() = 0;
    virtual long __stdcall GetLevelDesc(unsigned int level, SurfaceDesc3* desc) = 0;
    virtual long __stdcall GetSurfaceLevel(unsigned int level, Surface4** surface) = 0;
};
struct TextureHolder {
    Texture3* texture;
};

#pragma code_seg(".text$01accessor")
__declspec(noinline) void __stdcall ClearTexture(TextureHolder* holder) {
    Surface4* surface;
    LockedRect4 locked;
    SurfaceDesc3 desc;
    holder->texture->GetSurfaceLevel(0, &surface);
    surface->GetDesc(&desc);
    surface->LockRect(&locked, 0, 0);
    memset(locked.bits, 0, locked.pitch * desc.height);
    surface->UnlockRect();
    if (surface) surface->Release();
}
#pragma code_seg()
