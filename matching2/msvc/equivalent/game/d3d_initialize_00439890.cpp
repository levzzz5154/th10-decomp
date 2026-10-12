// 0x00439890..0x00439D16: the Direct3D device creation with its three
// attempt loop, the view/projection setup and the render-state defaults.
//
// The mode decision: the back-buffer format 0x16/0x17 comes from the bpp
// byte at 0x491D62 (0xFF = first boot, 32-bit); the windowed/VSync path
// reads 0x492518 and 0x491FDC; the refresh-rate fields of the present
// parameters carry the decision.
//
// Equivalent recovery: the COM slot calls compile as member wrappers, the
// two D3DX matrix builders stay out of line; the interleaved logger
// scheduling is recorded.
#include "th10/render/d3d_initialize_00439890.hpp"
#include "th10/platform/text_log.hpp"
#include <math.h>
#pragma intrinsic(tan)

extern "C" {
// The D3D object and device the body creates and configures.
extern void* data_00491c2c;              // IDirect3D9
extern void* data_00491c30;              // IDirect3DDevice9
extern char data_00491d0c[];             // the reset parameters
// The mode-decision flags.
extern unsigned char data_00491d62;      // the bpp log byte (0xFF: first boot)
extern unsigned char data_00491d65;      // the startup dialog ran
extern unsigned int data_00491d78;       // configuration flags
extern unsigned int data_00491fdc;       // the VSync decision
extern unsigned char data_00492518;      // the windowed flag
extern unsigned int data_00491fe0;       // the presentation interval home
extern unsigned int data_00491ff4;       // runtime flags (bit 1: windowed,
                                         //  bit 2: 16-bit fallback)
// The transform homes and the render-state probe targets.
extern void* data_00491c74;              // the view matrix
extern void* data_00491cb4;              // the projection matrix
extern void* data_00491cf4;              // the viewport
extern void* data_00492000;              // the render-state block
extern unsigned char data_00492090;      // the texture-op capability byte
extern unsigned int data_00492058;       // the max texture size
extern void* data_004924f0;              // the game window
extern unsigned int data_004924f4;       // quit requested
extern unsigned int data_00491fe4;       // the presentation state
extern TextLog_0044b810 data_00474f70;   // the 8 KiB diagnostic log
}

// 0x00452194, 0x0045219A: the D3DX builders (bound to their asm bodies).
extern "C" void* __stdcall D3DXMatrixLookAtLH_00452194(
    void* out, const void* eye, const void* at, const void* up);
extern "C" void* __stdcall D3DXMatrixPerspectiveFovLH_0045219a(
    void* out, float fov_y, float aspect, float near_z, float far_z);
// 0x00439D20: apply the device defaults; 0x0043BCD0: the default viewport.
extern "C" void __stdcall Renderer_ApplyDeviceDefaults_00439d20();
extern "C" int __stdcall ApplyDefaultViewport_0043bcd0(unsigned color);

namespace {

// The log lines (retail addresses).
extern "C" const char kFirstBoot32[];         // 0x0046F640
extern "C" const char kTryRefresh60[];        // 0x0046F614
extern "C" const char kTryVSyncAsync[];       // 0x0046F5F0
extern "C" const char kNoTnlHal[];            // 0x0046F5CC
extern "C" const char kRefreshFailed[];       // 0x0046F584
extern "C" const char kAsyncFailed[];         // 0x0046F54C
extern "C" const char kD3dInitFailed[];       // 0x0046F514
extern "C" const char kRunningRef[];          // 0x0046F4D8
extern "C" const char kRunningHal[];          // 0x0046F4C4
extern "C" const char kRunningTnlHal[];       // 0x0046F4A8
extern "C" const char kNoAddBlending[];       // 0x0046F458
extern "C" const char kNoLargeTextures[];     // 0x0046F408
extern "C" const char kNoA8R8G8B8[];          // 0x0046F3C0

// The Direct3D9 object: CreateDevice at slot 0x40, Release at slot 8.
struct Direct3DObject_00439890 {
    void* vtable;
    long CreateDevice(unsigned adapter, unsigned type, void* window,
                      unsigned flags, PresentParameters_00439890* parameters,
                      void** device) {
        typedef long (__stdcall *Call)(void*, unsigned, unsigned, void*,
                                       unsigned, PresentParameters_00439890*, void**);
        return ((Call)static_cast<void**>(vtable)[0x40 / 4])(
            this, adapter, type, window, flags, parameters, device);
    }
    unsigned long Release() {
        typedef unsigned long (__stdcall *Call)(void*);
        return ((Call)static_cast<void**>(vtable)[8 / 4])(this);
    }
};

// The device: SetTransform at 0xB0, the 0xC0 slot and the 0x1C slot the
// body configures.
struct RenderDeviceSlots_00439890 {
    void* vtable;
    long SetTransform(unsigned state, const void* matrix) {
        typedef long (__stdcall *Call)(void*, unsigned, const void*);
        return ((Call)static_cast<void**>(vtable)[0xB0 / 4])(this, state, matrix);
    }
    long Configure(void* block) {
        typedef long (__stdcall *Call)(void*, void*);
        return ((Call)static_cast<void**>(vtable)[0xC0 / 4])(this, block);
    }
    long Apply(void* block) {
        typedef long (__stdcall *Call)(void*, void*);
        return ((Call)static_cast<void**>(vtable)[0x1C / 4])(this, block);
    }
    long CheckFormat(unsigned adapter, unsigned type, unsigned format,
                     unsigned usage) {
        typedef long (__stdcall *Call)(void*, unsigned, unsigned, unsigned, unsigned);
        return ((Call)static_cast<void**>(vtable)[0x28 / 4])(
            this, adapter, type, format, usage);
    }
};

// The view matrix rows: the eye (320, -240, 0) with the default up.
struct ViewEye_00439890 {
    float x, y, z;
};

}

#pragma code_seg(".text$00439890_fn")
__declspec(noinline) int __stdcall D3DInitialize_00439890() {
    PresentParameters_00439890 parameters;
    unsigned int mode_block[14];
    Direct3DObject_00439890* d3d =
        static_cast<Direct3DObject_00439890*>(data_00491c2c);
    int windowed = 0;
    int error = 0;
    unsigned no_tnl = 0;
    unsigned refresh = 0x80000000;
    int attempt_count = 0;
    // The bpp log byte: 0xFF marks the first boot (32-bit), otherwise the
    // saved bit decides 16/32.
    if (data_00491d65 == 0)
        error = 0;                     // ebx = 0
    else
        error = 1;                     // the dialog path keeps [esp+0x50]
    if (data_00491d62 == 0xFF) {
        data_00474f70.Append(const_cast<char*>(kFirstBoot32));
        parameters.back_buffer_format = 0x16;
        data_00491d62 = 0;
    } else {
        parameters.back_buffer_format = (data_00491d62 != 0) + 0x16;
    }
    if (data_00492518 != 0) {
        windowed = 1;
        data_00491fdc = 1;
    } else if (data_00491fdc != 0) {
        data_00474f70.Append(const_cast<char*>(kTryRefresh60));
        refresh = 0x3C;
        parameters.presentation_interval = 1;
    } else {
        windowed = 1;
        data_00474f70.Append(const_cast<char*>(kTryVSyncAsync));
        refresh = 0;
        parameters.presentation_interval = refresh;
    }
    data_00491ff4 |= 2u;
    parameters.back_buffer_width = 0x280;
    parameters.back_buffer_height = 0x1E0;
    parameters.windowed = windowed;
    parameters.swap_effect = 0x50;
    parameters.flags = windowed;
    data_00491fe0 = windowed;
    // The three CreateDevice attempts, straight-line as in retail: the
    // windowed/flag state mutates between them and each carries its own
    // logging.
    if (!(data_00491d78 & 2)) {
        no_tnl = 1;
        if (d3d->CreateDevice(0, windowed, data_004924f0, 0x40,
                              &parameters, &data_00491c30) >= 0) {
            data_00474f70.Append(const_cast<char*>(kRunningTnlHal));
            data_00491ff4 |= 1u;
            goto transforms;
        }
        if (attempt_count != 0)
            data_00474f70.Append(const_cast<char*>(kNoTnlHal));
        if (d3d->CreateDevice(0, windowed, data_004924f0, 0x20,
                              &parameters, &data_00491c30) >= 0) {
            data_00474f70.Append(const_cast<char*>(kRunningHal));
            data_00491ff4 &= ~1u;
            goto transforms;
        }
        if (data_00491fdc == 0) {
            data_00474f70.Append(const_cast<char*>(kRefreshFailed));
            parameters.flags = 0;
            data_00491fe0 = 0;
            windowed = 1;
            goto retry_mixed;
        }
        if (refresh == 0x80000000) {
            data_00474f70.Append(const_cast<char*>(kAsyncFailed));
            refresh = windowed;
            parameters.back_buffer_format = 3;
            goto retry_mixed;
        }
        data_00474f70.Append(const_cast<char*>(kD3dInitFailed));
        if (d3d != 0) {
            d3d->Release();
            data_00491c2c = 0;
        }
        return windowed;
    } else {
        no_tnl = 1;
        goto retry_mixed;
    }
retry_mixed:
    if (d3d->CreateDevice(0, 2, data_004924f0, 0x20,
                          &parameters, &data_00491c30) >= 0) {
        goto transforms;
    }
    if (data_00491fdc == 0) {
        data_00474f70.Append(const_cast<char*>(kRefreshFailed));
        parameters.flags = 0;
        data_00491fe0 = 0;
        windowed = 1;
    } else if (refresh == 0x80000000) {
        data_00474f70.Append(const_cast<char*>(kAsyncFailed));
        refresh = windowed;
        parameters.back_buffer_format = 3;
    } else {
        data_00474f70.Append(const_cast<char*>(kD3dInitFailed));
        if (d3d != 0) {
            d3d->Release();
            data_00491c2c = 0;
        }
        return windowed;
    }
    goto retry_mixed;
transforms:
    if (data_00491c30 == 0)
        return 0;
    // The projection: -240/tan(π/12) — the fptan sequence of retail, in
    // the fixed half-angle the image keeps in .rdata.
    const float view_height =
        -240.0f / tan(0.2617993950843811);
    {
        const ViewEye_00439890 eye = {320.0f, -240.0f, 0.0f};
        const ViewEye_00439890 up = {0.0f, 1.0f, 0.0f};
        D3DXMatrixLookAtLH_00452194(data_00491c74, &eye, &eye, &up);
        D3DXMatrixPerspectiveFovLH_0045219a(
            data_00491cb4, 0.5235987901687622f, 1.3333333730697632f,
            100.0f, 10000.0f);
    }
    {
        RenderDeviceSlots_00439890* device =
            static_cast<RenderDeviceSlots_00439890*>(data_00491c30);
        device->SetTransform(2, data_00491c74);
        device->SetTransform(3, data_00491cb4);
        device->Configure(data_00491cf4);
        device->Apply(data_00492000);
    }
    if (!(data_00492090 & 0x40))
        data_00474f70.Append(const_cast<char*>(kNoAddBlending));
    if (data_00492058 <= 0x100)
        data_00474f70.Append(const_cast<char*>(kNoLargeTextures));
    if ((data_00491d78 & 1) && error != 0) {
        RenderDeviceSlots_00439890* d3d_check =
            reinterpret_cast<RenderDeviceSlots_00439890*>(data_00491c2c);
        if (d3d_check->CheckFormat(0, windowed, parameters.back_buffer_format,
                                   0x15) == 0) {
            data_00491ff4 |= 4u;
        } else {
            data_00491ff4 &= ~4u;
            data_00491d78 |= 1u;
            data_00474f70.Append(const_cast<char*>(kNoA8R8G8B8));
        }
    }
    Renderer_ApplyDeviceDefaults_00439d20();
    ApplyDefaultViewport_0043bcd0(0xFF000000u);
    data_004924f4 = 0;
    data_00491fe4 = 0;
    return 0;
}
#pragma code_seg()
