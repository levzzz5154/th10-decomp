// 0x00437670: copy a GDI surface's pixels into a Direct3D surface of the same format.
#include <string.h>
struct SurfaceDesc_00437670 {
    int format;
    int type;
    unsigned long usage;
    int pool;
    int multisample_type;
    unsigned long multisample_quality;
    unsigned int width;
    unsigned int height;
};
struct LockedRect_00437670 {
    int pitch;
    unsigned char* bits;
};
struct Rect_00437670 {
    long left, top, right, bottom;
};
struct Surface_00437670 {
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
    virtual long __stdcall GetDesc(SurfaceDesc_00437670* desc) = 0;
    virtual long __stdcall LockRect(LockedRect_00437670* locked, const Rect_00437670* rect, unsigned long flags) = 0;
    virtual long __stdcall UnlockRect() = 0;
};
struct GdiSurface_00437670 {
    unsigned char unknown_000[0x100];
    int format;
    int width;
    int height;
    unsigned char unknown_10c[4];
    int row_bytes;
    void* dc;
    void* previous_bitmap;
    void* bitmap;
    unsigned char* pixels;
};

#pragma code_seg(".text$01accessor")
__declspec(noinline) bool __stdcall WriteTo(GdiSurface_00437670* gdi, Surface_00437670* surface) {
    if (!gdi->bitmap) return false;
    SurfaceDesc_00437670 desc;
    surface->GetDesc(&desc);
    Rect_00437670 rect;
    rect.left = 0;
    rect.top = 0;
    rect.right = gdi->width;
    rect.bottom = gdi->height;
    LockedRect_00437670 locked;
    if (surface->LockRect(&locked, &rect, 0)) return false;
    int pitch = locked.pitch;
    unsigned char* source = gdi->pixels;
    unsigned char* target = locked.bits;
    int row_bytes = gdi->row_bytes;
    if (desc.format == gdi->format) {
        for (int y = 0; y < gdi->height; ++y) {
            memcpy(target, source, row_bytes);
            source += row_bytes;
            target += pitch;
        }
    }
    surface->UnlockRect();
    return true;
}
#pragma code_seg()
