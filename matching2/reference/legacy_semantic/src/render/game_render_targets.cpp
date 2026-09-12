#include "th10/render/game_render_targets.hpp"

#if defined(_WIN32)
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#endif

extern void* g_pD3DDevice;

// 0x00443F80 - Prepare projected render state before invoking the normal draw
// path. Preparation failures use the retail -1 result.
int Render_PrepareAndDraw(void* object, int (*prepare)(),
                          int (*draw)(void*, int)) {
    if (prepare == 0 || prepare() != 0)
        return -1;
    return draw != 0 ? draw(object, 0) : -1;
}

// 0x00444580 - Restore the four render scale factors to identity.
void Render_ResetScaleFactors(float factors[4]) {
    factors[0] = 1.0f;
    factors[1] = 1.0f;
    factors[2] = 1.0f;
    factors[3] = 1.0f;
}

void GameRender_ReleaseCaptureTarget(
    GameRenderTargets* targets, int32_t handle, const uint32_t* arguments) {
#if defined(_WIN32)
    if (targets == nullptr || arguments == nullptr ||
        g_pD3DDevice == nullptr || handle < 0)
        return;
    auto* manager = reinterpret_cast<unsigned char*>(targets);
    void* resource = *reinterpret_cast<void**>(
        manager + 0x3ad06c + static_cast<unsigned int>(handle) * 4);
    if (resource == nullptr)
        return;
    auto* texture_words = *reinterpret_cast<unsigned int**>(
        static_cast<unsigned char*>(resource) + 0x120);
    if (texture_words == nullptr)
        return;
    auto* texture = reinterpret_cast<IDirect3DTexture9*>(
        static_cast<uintptr_t>(texture_words[arguments[8] * 4]));
    if (texture == nullptr)
        return;
    auto* device = static_cast<IDirect3DDevice9*>(g_pD3DDevice);
    IDirect3DSurface9* source = nullptr;
    IDirect3DSurface9* destination = nullptr;
    if (SUCCEEDED(device->GetBackBuffer(
            0, 0, D3DBACKBUFFER_TYPE_MONO, &source)) &&
        SUCCEEDED(texture->GetSurfaceLevel(0, &destination))) {
        D3DXLoadSurfaceFromSurface(destination, nullptr, nullptr, source,
                                   nullptr, nullptr, D3DX_FILTER_POINT, 0);
    }
    if (destination != nullptr)
        destination->Release();
    if (source != nullptr)
        source->Release();
#else
    (void)targets; (void)handle; (void)arguments;
#endif
}

void GameRender_ReleasePrimaryTarget(
    GameRenderTargets* targets, int32_t handle, const uint32_t*) {
#if defined(_WIN32)
    if (targets == nullptr || g_pD3DDevice == nullptr || handle < 0 ||
        handle >= 32)
        return;
    auto* manager = reinterpret_cast<unsigned char*>(targets);
    auto** first = reinterpret_cast<IDirect3DSurface9**>(
        manager + 0x3ad4e0 + static_cast<unsigned int>(handle) * 4);
    auto** second = reinterpret_cast<IDirect3DSurface9**>(
        manager + 0x3ad560 + static_cast<unsigned int>(handle) * 4);
    if (*first != nullptr) {
        (*first)->Release();
        *first = nullptr;
    }
    if (*second != nullptr) {
        (*second)->Release();
        *second = nullptr;
    }
    auto* device = static_cast<IDirect3DDevice9*>(g_pD3DDevice);
    IDirect3DSurface9* back_buffer = nullptr;
    if (FAILED(device->GetBackBuffer(
            0, 0, D3DBACKBUFFER_TYPE_MONO, &back_buffer)))
        return;
    D3DSURFACE_DESC description = {};
    back_buffer->GetDesc(&description);
    auto* dimensions = reinterpret_cast<unsigned int*>(
        manager + 0x3ad6e0 + static_cast<unsigned int>(handle) * 0x1c);
    dimensions[0] = description.Width;
    dimensions[1] = description.Height;
    const D3DFORMAT format = description.Format;
    if (SUCCEEDED(device->CreateOffscreenPlainSurface(
            description.Width, description.Height, format,
            D3DPOOL_DEFAULT, first, nullptr)) &&
        SUCCEEDED(device->CreateOffscreenPlainSurface(
            description.Width, description.Height, format,
            D3DPOOL_DEFAULT, second, nullptr))) {
        D3DXLoadSurfaceFromSurface(*first, nullptr, nullptr, back_buffer,
                                   nullptr, nullptr, D3DX_FILTER_NONE, 0);
        D3DXLoadSurfaceFromSurface(*second, nullptr, nullptr, *first,
                                   nullptr, nullptr, D3DX_FILTER_NONE, 0);
    }
    back_buffer->Release();
#else
    (void)targets; (void)handle;
#endif
}

// Initialization is inlined into GameStateInit at 0x00445900.
void GameRenderTargets_Initialize(GameRenderTargets* targets) {
    targets->primary_handle = -1;
    targets->capture_handle = -1;
    for (uint32_t index = 0; index < 9; ++index) {
        targets->capture_args[index] = 0;
    }
    for (uint32_t index = 0; index < 8; ++index) {
        targets->primary_args[index] = 0;
    }
}

// 0x00438A60 - Release reset-sensitive capture and primary render targets.
void GameRenderTargets_Release(GameRenderTargets* targets) {
    if (targets->capture_handle >= 0) {
        GameRender_ReleaseCaptureTarget(
            targets, targets->capture_handle, targets->capture_args);
        targets->capture_handle = -1;
    }
    if (targets->primary_handle >= 0) {
        GameRender_ReleasePrimaryTarget(
            targets, targets->primary_handle, targets->primary_args);
        targets->primary_handle = -1;
    }
}
