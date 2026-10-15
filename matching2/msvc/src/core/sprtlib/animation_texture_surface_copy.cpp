// 0x00448120, 0x00448270, 0x00448360 and 0x00448450: copies between the back
// buffer, loaded animation textures and indexed image surfaces.
//
// CopyRectToBackBuffer blits a rectangle of one indexed image to (x, y) on the
// back buffer, creating the image's device-side surface on first use. The
// manager arrives on the stack and the index in EBX. Nothing in the retail
// image calls it.
//
// CaptureBackBuffer copies a rectangle of the back buffer into the top level
// of one texture; CopyTexture copies between the top levels of two textures.
// Both flush the pending quad batch first, since they read or replace pixels
// the batch may still reference.
//
// Native LTCG passes the manager in ECX, the resource in EBX and the entry in
// EAX to CaptureBackBuffer, and the manager in EDX with the two entries in
// EAX and ECX to CopyTexture; the remaining arguments stay on the stack.
// Nothing in the retail image calls CopyTexture.
//
// CaptureBackBufferImage replaces one indexed image with a rectangle of the
// back buffer: it recreates the device-side surface (a render target, or an
// offscreen plain surface when that fails) and its system-memory twin, fills
// the first from the back buffer and the second from the first. The manager
// arrives in EAX; all nine arguments stay on the stack.
#include "th10/render/resource_surface_loading.hpp"

// The quad batch owner is the same object; only its flush is needed here.
struct SprtCtrlBatchView {
    __declspec(noinline) int Flush();
};

struct Texture_00448270 {
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
    virtual long __stdcall GetSurfaceLevel(unsigned int level, Resource_00447f70** surface) = 0;
};

struct AnimationTextureEntry_00448270 {
    Texture_00448270* texture;           // +0x00
    void* allocation;                    // +0x04
    unsigned char pad_08[8];
};

struct AnimationResource_00448270 {
    unsigned char pad_000[0x120];
    AnimationTextureEntry_00448270* entries;   // +0x120
};

struct AnimationTextureManager_00448270 {
    unsigned char pad_000000[0x3AD06C];
    AnimationResource_00448270* resources[0x21];   // +0x3AD06C

    __declspec(noinline) void CaptureBackBuffer(int resource, int entry,
                                                int left, int top, int width, int height,
                                                int target_left, int target_top,
                                                int target_width, int target_height);
    __declspec(noinline) void CopyTexture(int target_resource, int target_entry,
                                          int source_resource, int source_entry,
                                          const SurfaceRect_00447fd0* target_rect,
                                          const SurfaceRect_00447fd0* source_rect);
};

// The device is always reached through this accessor: it makes the compiler
// load the device and its vtable before the arguments, as retail does.
static inline SurfaceDevice_00447c80* Device() { return g_d3d_device; }

#pragma code_seg(".text$02rect")
void AnimationManagerIndexed_00447f70::CopyRectToBackBuffer(int index, int x, int y,
                                                            int left, int top,
                                                            int width, int height) {
    if (!secondary[index])
        return;
    Resource_00447f70* back_buffer;
    if (Device()->GetBackBuffer(0, 0, 0, &back_buffer) != 0)
        return;
    if (!primary[index]) {
        if (Device()->CreateRenderTarget(info[index].width, info[index].height, data_00491d14,
                                         0, 0, 1, &primary[index], 0) != 0 &&
            Device()->CreateOffscreenPlainSurface(info[index].width, info[index].height,
                                                  data_00491d14, 3, &primary[index], 0) != 0) {
            back_buffer->Release();
            return;
        }
        if (LoadSurfaceCopy_004521d6(primary[index], 0, 0, secondary[index], 0, 0, 1, 0) != 0) {
            back_buffer->Release();
            return;
        }
    }
    SurfaceRect_00447fd0 rect;
    rect.left = left;
    rect.top = top;
    rect.right = left + width;
    rect.bottom = top + height;
    SurfacePoint_00447fd0 point;
    point.x = x;
    point.y = y;
    Device()->UpdateSurface(primary[index], &rect, back_buffer, &point);
    back_buffer->Release();
}

#pragma code_seg(".text$03capture")
void AnimationTextureManager_00448270::CaptureBackBuffer(int resource, int entry,
                                                         int left, int top, int width, int height,
                                                         int target_left, int target_top,
                                                         int target_width, int target_height) {
    if (!resources[resource]->entries[entry].texture)
        return;
    reinterpret_cast<SprtCtrlBatchView*>(this)->Flush();
    Resource_00447f70* back_buffer;
    if (Device()->GetBackBuffer(0, 0, 0, &back_buffer) != 0)
        return;
    Resource_00447f70* surface;
    if (resources[resource]->entries[entry].texture->GetSurfaceLevel(0, &surface) != 0) {
        back_buffer->Release();
        return;
    }
    SurfaceRect_00447fd0 source;
    source.left = left;
    source.top = top;
    source.right = left + width;
    source.bottom = top + height;
    SurfaceRect_00447fd0 target;
    target.left = target_left;
    target.top = target_top;
    target.right = target_left + target_width;
    target.bottom = target_top + target_height;
    if (LoadSurfaceCopy_004521d6(surface, 0, &target, back_buffer, 0, &source, 2, 0) != 0) {
        surface->Release();
        back_buffer->Release();
        return;
    }
    surface->Release();
    back_buffer->Release();
}

#pragma code_seg(".text$05copy")
void AnimationTextureManager_00448270::CopyTexture(int target_resource, int target_entry,
                                                   int source_resource, int source_entry,
                                                   const SurfaceRect_00447fd0* target_rect,
                                                   const SurfaceRect_00447fd0* source_rect) {
    if (!resources[target_resource]->entries[target_entry].texture)
        return;
    if (!resources[source_resource]->entries[source_entry].texture)
        return;
    reinterpret_cast<SprtCtrlBatchView*>(this)->Flush();
    Resource_00447f70* target;
    if (resources[target_resource]->entries[target_entry].texture->GetSurfaceLevel(0, &target) != 0)
        return;
    Resource_00447f70* source;
    if (resources[source_resource]->entries[source_entry].texture->GetSurfaceLevel(0, &source) != 0) {
        target->Release();
        return;
    }
    if (LoadSurfaceCopy_004521d6(target, 0, target_rect, source, 0, source_rect, 0xFFFFFFFF, 0) != 0) {
        target->Release();
        source->Release();
        return;
    }
    target->Release();
    source->Release();
}

// The device and the surface format are members of one render state object.
struct RenderState_00448450 {
    unsigned char pad_00[0x08];
    SurfaceDevice_00447c80* device;      // +0x08
    unsigned char pad_0C[0xEC - 0x0C];
    int format;                          // +0xEC
};
extern "C" RenderState_00448450 g_application;

static inline SurfaceDevice_00447c80* StateDevice() { return g_application.device; }

#pragma code_seg(".text$06image")
void AnimationManagerIndexed_00447f70::CaptureBackBufferImage(int index, int left, int top,
                                                              int width, int height,
                                                              int target_left, int target_top,
                                                              int target_width, int target_height) {
    reinterpret_cast<SprtCtrlBatchView*>(this)->Flush();
    if (primary[index])
        Clear(index);
    SurfaceRect_00447fd0 source;
    source.left = left;
    source.top = top;
    source.right = left + width;
    source.bottom = top + height;
    SurfaceRect_00447fd0 target;
    target.left = target_left;
    target.top = target_top;
    target.right = target_left + target_width;
    target.bottom = target_top + target_height;
    Resource_00447f70* back_buffer;
    if (StateDevice()->GetBackBuffer(0, 0, 0, &back_buffer) != 0)
        return;
    info[index].width = target_width;
    info[index].height = target_height;
    if ((StateDevice()->CreateRenderTarget(info[index].width, info[index].height, g_application.format,
                                      0, 0, 1, &primary[index], 0) == 0 ||
         StateDevice()->CreateOffscreenPlainSurface(info[index].width, info[index].height,
                                               g_application.format, 3, &primary[index], 0) == 0) &&
        StateDevice()->CreateOffscreenPlainSurface(info[index].width, info[index].height,
                                              g_application.format, 3, &secondary[index], 0) == 0 &&
        LoadSurfaceCopy_004521d6(primary[index], 0, &target, back_buffer, 0, &source,
                                 0xFFFFFFFF, 0) == 0) {
        LoadSurfaceCopy_004521d6(secondary[index], 0, 0, primary[index], 0, 0, 0xFFFFFFFF, 0);
    }
    if (back_buffer)
        back_buffer->Release();
}
#pragma code_seg()
