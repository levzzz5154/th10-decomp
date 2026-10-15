// 0x00437590: copy a Direct3D surface's pixels into a GDI surface of the same format.
#include <string.h>
struct SurfaceDesc_00437590 {
    int format;
    int type;
    unsigned long usage;
    int pool;
    int multisample_type;
    unsigned long multisample_quality;
    unsigned int width;
    unsigned int height;
};
struct LockedRect_00437590 {
    int pitch;
    unsigned char* bits;
};
struct Rect_00437590 {
    long left, top, right, bottom;
};
struct Surface_00437590 {
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
    virtual long __stdcall GetDesc(SurfaceDesc_00437590* desc) = 0;
    virtual long __stdcall LockRect(LockedRect_00437590* locked, const Rect_00437590* rect, unsigned long flags) = 0;
    virtual long __stdcall UnlockRect() = 0;
};
struct GdiSurface_00437590 {
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
__declspec(noinline) bool __stdcall ReadFrom_00437590(GdiSurface_00437590* gdi, Surface_00437590* surface) {
    if (!gdi->bitmap) return false;
    SurfaceDesc_00437590 desc;
    surface->GetDesc(&desc);
    Rect_00437590 rect;
    rect.left = 0;
    rect.top = 0;
    rect.right = gdi->width;
    rect.bottom = gdi->height;
    LockedRect_00437590 locked;
    surface->LockRect(&locked, &rect, 0x10);
    int row_bytes = gdi->row_bytes;
    unsigned char* source = locked.bits;
    int pitch = locked.pitch;
    unsigned char* target = gdi->pixels;
    if (desc.format == gdi->format) {
        for (int y = 0; y < gdi->height; ++y) {
            memcpy(target, source, row_bytes);
            source += pitch;
            target += row_bytes;
        }
    }
    surface->UnlockRect();
    return true;
}
#pragma code_seg()
