// 0x00439890: create the Direct3D device and set up the fixed camera.
//
// Picks the back-buffer format and the presentation mode from the
// configuration, then tries the device kinds from best to worst (hardware
// vertex processing, software vertex processing, the reference rasteriser),
// relaxing the presentation mode between rounds. With a device in hand it
// stores the 2D camera, reads the capabilities and decides whether 32-bit
// textures can be used. Returns 1 when no device could be created.
//
// Written from the retail instructions block by block and linked against the
// recovered sources of the two log writers (the layout's context_sources).
#include "th10/app/application.hpp"
#include "th10/platform/text_log.hpp"
#include <math.h>
#include <string.h>

struct SprtCtrlStateCacheView;

extern "C" {
Direct3DMatrix* __stdcall asm_D3DXMatrixLookAtLH_00452194(Direct3DMatrix* out,
    const Direct3DVector* eye, const Direct3DVector* at, const Direct3DVector* up);
Direct3DMatrix* __stdcall asm_D3DXMatrixPerspectiveFovLH_0045219a(Direct3DMatrix* out,
    float fov_y, float aspect, float near_z, float far_z);
SprtCtrlStateCacheView* __cdecl Renderer_ApplyDeviceDefaults(void);

extern Application data_00491c28;
extern MainWindow data_004924f0;
extern TextLog_0044b810 data_00474f70;

// Log lines (Shift-JIS).
extern char data_0046f640[];    // "first run, the screen was initialised at 32 bits"
extern char data_0046f614[];    // "trying to change the refresh rate to 60Hz"
extern char data_0046f5f0[];    // "trying whether presenting without VSync is possible"
extern char data_0046f5cc[];    // "T&L HAL does not seem to be usable"
extern char data_0046f5ac[];    // "HAL does not seem to be usable either"
extern char data_0046f584[];    // "the refresh rate cannot be changed"
extern char data_0046f54c[];    // "asynchronous updates do not work either, changing to the ugliest mode"
extern char data_0046f514[];    // "Direct3D initialisation failed, the game cannot run like this"
extern char data_0046f4d8[];    // "running on REF, but it is too slow to be a game..."
extern char data_0046f4c4[];    // "running on HAL"
extern char data_0046f4a8[];    // "running on T&L HAL"
extern char data_0046f458[];    // "D3DTEXOPCAPS_ADD is not supported, emulating additive colour"
extern char data_0046f408[];    // "textures of 512 and above are not supported, most pictures will be blurred"
extern char data_0046f3c0[];    // "D3DFMT_A8R8G8B8 is not supported, running with reduced colours"
}

int __stdcall ApplyDefaultViewport(unsigned int color);

struct TextLog_0044b8e0 {
    char text[0x2000];
    char* cursor;
    unsigned char dirty;
    char* AppendLine(char* format, ...);
};

#pragma code_seg(".text$00439890_fn")
__declspec(noinline) int __stdcall D3DInitialize_00439890() {
    Direct3DPresentParameters parameters;
    Direct3DDisplayMode desktop;
    Direct3DVector eye, at, up;
    bool hardware;
    int retried;

    memset(&parameters, 0, sizeof(parameters));
    hardware = true;
    data_00491c28.direct3d->GetAdapterDisplayMode(0, &desktop);
    if (!data_00491c28.config.field_1d) {
        if (data_00491c28.config.flags & 1) {
            parameters.back_buffer_format = 23;         // D3DFMT_R5G6B5
            data_00491c28.config.field_1a = 1;
        } else if (data_00491c28.config.field_1a == 0xFF) {
            parameters.back_buffer_format = 22;         // D3DFMT_X8R8G8B8
            data_00491c28.config.field_1a = 0;
            data_00474f70.Append(data_0046f640);
        } else {
            parameters.back_buffer_format = data_00491c28.config.field_1a == 0 ? 22 : 23;
        }
        if (data_004924f0.force_no_vsync) {
            data_00491c28.no_vsync = 1;
            goto immediate;
        }
        if (data_00491c28.no_vsync == 0) {
            parameters.refresh_rate = 60;
            parameters.presentation_interval = 1;
            data_00474f70.Append(data_0046f614);
            parameters.swap_effect = 1;
        } else {
immediate:
            parameters.refresh_rate = 0;
            parameters.swap_effect = 1;
            parameters.presentation_interval = 0x80000000;
            data_00474f70.Append(data_0046f5f0);
        }
    } else {
        parameters.back_buffer_format = desktop.format;
        parameters.swap_effect = 1;
        parameters.windowed = 1;
    }
    parameters.back_buffer_width = 640;
    parameters.back_buffer_height = 480;
    parameters.enable_auto_depth_stencil = 1;
    parameters.auto_depth_stencil_format = 80;          // D3DFMT_D16
    parameters.flags = 1;
    data_00491c28.flags |= 2;
    data_00491c28.fixed_refresh = 1;

    retried = 0;
    for (;;) {
        if (data_00491c28.config.flags & 2)
            goto reference;
        if (data_00491c28.direct3d->CreateDevice(0, 1, data_004924f0.window, 0x40,
                &parameters, &data_00491c28.device) < 0) {
            if (retried)
                data_00474f70.Append(data_0046f5cc);
            if (data_00491c28.direct3d->CreateDevice(0, 1, data_004924f0.window, 0x20,
                    &parameters, &data_00491c28.device) < 0) {
                if (retried)
                    data_00474f70.Append(data_0046f5ac);
reference:
                if (data_00491c28.direct3d->CreateDevice(0, 2, data_004924f0.window, 0x20,
                        &parameters, &data_00491c28.device) < 0) {
                    if (data_00491c28.no_vsync == 0) {
                        data_00474f70.Append(data_0046f584);
                        parameters.refresh_rate = 0;
                        data_00491c28.fixed_refresh = 0;
                        retried = 1;
                        continue;
                    }
                    if (parameters.presentation_interval == 0x80000000) {
                        data_00474f70.Append(data_0046f54c);
                        parameters.presentation_interval = 1;
                        parameters.swap_effect = 3;
                        continue;
                    }
                    reinterpret_cast<TextLog_0044b8e0*>(&data_00474f70)->AppendLine(data_0046f514);
                    if (data_00491c28.direct3d != 0) {
                        data_00491c28.direct3d->Release();
                        data_00491c28.direct3d = 0;
                    }
                    return 1;
                } else {
                    data_00474f70.Append(data_0046f4d8);
                    data_00491c28.flags &= ~1u;
                    hardware = false;
                }
            } else {
                data_00474f70.Append(data_0046f4c4);
                data_00491c28.flags &= ~1u;
            }
        } else {
            data_00474f70.Append(data_0046f4a8);
            data_00491c28.flags |= 1;
        }
        break;
    }

    data_00491c28.present_parameters = parameters;
    // The camera looks straight at the middle of the 640x480 field from the
    // distance at which a 30 degree field of view spans its height.
    float field_of_view = 0.5235988f;
    eye.x = 320.0f;
    eye.y = -240.0f;
    at.x = 320.0f;
    at.y = -240.0f;
    at.z = 0.0f;
    up.x = 0.0f;
    up.y = 1.0f;
    up.z = 0.0f;
    eye.z = -(240.0f / (float)tan(field_of_view / 2));
    asm_D3DXMatrixLookAtLH_00452194(&data_00491c28.view, &eye, &at, &up);
    asm_D3DXMatrixPerspectiveFovLH_0045219a(&data_00491c28.projection, field_of_view,
                                            640.0f / 480.0f, 100.0f, 10000.0f);
    data_00491c28.device->SetTransform(2, &data_00491c28.view);
    data_00491c28.device->SetTransform(3, &data_00491c28.projection);
    data_00491c28.device->GetViewport(&data_00491c28.viewport);
    data_00491c28.device->GetDeviceCaps(&data_00491c28.caps);
    if (!(data_00491c28.caps.texture_op_caps & 0x40))
        data_00474f70.Append(data_0046f458);
    if (data_00491c28.caps.max_texture_width <= 256)
        data_00474f70.Append(data_0046f408);
    if (!(data_00491c28.config.flags & 1) && hardware) {
        if (data_00491c28.direct3d->CheckDeviceFormat(0, 1, parameters.back_buffer_format,
                0, 3, 21) == 0) {
            data_00491c28.flags |= 4;
        } else {
            data_00491c28.flags &= ~4u;
            data_00491c28.config.flags |= 1;
            data_00474f70.Append(data_0046f3c0);
        }
    }
    Renderer_ApplyDeviceDefaults();
    ApplyDefaultViewport(0xFF000000);
    data_004924f0.quit = 0;
    data_00491c28.frames_presented = 0;
    return 0;
}
#pragma code_seg()

// The link's entry: a caller for the whole-program link to see.
extern "C" int __stdcall RigEntry(void* instance, int show) {
    return D3DInitialize_00439890();
}
