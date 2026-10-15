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

extern Application g_application;
extern MainWindow data_004924f0;
extern TextLog_0044b810 g_log;

// Log lines (Shift-JIS).
extern char str_first_run_32bit[];    // "first run, the screen was initialised at 32 bits"
extern char str_trying_60hz[];    // "trying to change the refresh rate to 60Hz"
extern char str_trying_vsync_async[];    // "trying whether presenting without VSync is possible"
extern char str_no_tnl_hal[];    // "T&L HAL does not seem to be usable"
extern char str_no_hal[];    // "HAL does not seem to be usable either"
extern char str_refresh_rate_unchangeable[];    // "the refresh rate cannot be changed"
extern char str_no_async_present[];    // "asynchronous updates do not work either, changing to the ugliest mode"
extern char str_d3d_init_failed[];    // "Direct3D initialisation failed, the game cannot run like this"
extern char str_running_ref[];    // "running on REF, but it is too slow to be a game..."
extern char str_running_hal[];    // "running on HAL"
extern char str_running_tnl_hal[];    // "running on T&L HAL"
extern char str_no_texop_add[];    // "D3DTEXOPCAPS_ADD is not supported, emulating additive colour"
extern char str_no_512_textures[];    // "textures of 512 and above are not supported, most pictures will be blurred"
extern char str_no_a8r8g8b8[];    // "D3DFMT_A8R8G8B8 is not supported, running with reduced colours"
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
    g_application.direct3d->GetAdapterDisplayMode(0, &desktop);
    if (!g_application.config.field_1d) {
        if (g_application.config.flags & 1) {
            parameters.back_buffer_format = 23;         // D3DFMT_R5G6B5
            g_application.config.field_1a = 1;
        } else if (g_application.config.field_1a == 0xFF) {
            parameters.back_buffer_format = 22;         // D3DFMT_X8R8G8B8
            g_application.config.field_1a = 0;
            g_log.Append(str_first_run_32bit);
        } else {
            parameters.back_buffer_format = g_application.config.field_1a == 0 ? 22 : 23;
        }
        if (data_004924f0.force_no_vsync) {
            g_application.no_vsync = 1;
            goto immediate;
        }
        if (g_application.no_vsync == 0) {
            parameters.refresh_rate = 60;
            parameters.presentation_interval = 1;
            g_log.Append(str_trying_60hz);
            parameters.swap_effect = 1;
        } else {
immediate:
            parameters.refresh_rate = 0;
            parameters.swap_effect = 1;
            parameters.presentation_interval = 0x80000000;
            g_log.Append(str_trying_vsync_async);
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
    g_application.flags |= 2;
    g_application.fixed_refresh = 1;

    retried = 0;
    for (;;) {
        if (g_application.config.flags & 2)
            goto reference;
        if (g_application.direct3d->CreateDevice(0, 1, data_004924f0.window, 0x40,
                &parameters, &g_application.device) < 0) {
            if (retried)
                g_log.Append(str_no_tnl_hal);
            if (g_application.direct3d->CreateDevice(0, 1, data_004924f0.window, 0x20,
                    &parameters, &g_application.device) < 0) {
                if (retried)
                    g_log.Append(str_no_hal);
reference:
                if (g_application.direct3d->CreateDevice(0, 2, data_004924f0.window, 0x20,
                        &parameters, &g_application.device) < 0) {
                    if (g_application.no_vsync == 0) {
                        g_log.Append(str_refresh_rate_unchangeable);
                        parameters.refresh_rate = 0;
                        g_application.fixed_refresh = 0;
                        retried = 1;
                        continue;
                    }
                    if (parameters.presentation_interval == 0x80000000) {
                        g_log.Append(str_no_async_present);
                        parameters.presentation_interval = 1;
                        parameters.swap_effect = 3;
                        continue;
                    }
                    reinterpret_cast<TextLog_0044b8e0*>(&g_log)->AppendLine(str_d3d_init_failed);
                    if (g_application.direct3d != 0) {
                        g_application.direct3d->Release();
                        g_application.direct3d = 0;
                    }
                    return 1;
                } else {
                    g_log.Append(str_running_ref);
                    g_application.flags &= ~1u;
                    hardware = false;
                }
            } else {
                g_log.Append(str_running_hal);
                g_application.flags &= ~1u;
            }
        } else {
            g_log.Append(str_running_tnl_hal);
            g_application.flags |= 1;
        }
        break;
    }

    g_application.present_parameters = parameters;
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
    asm_D3DXMatrixLookAtLH_00452194(&g_application.view, &eye, &at, &up);
    asm_D3DXMatrixPerspectiveFovLH_0045219a(&g_application.projection, field_of_view,
                                            640.0f / 480.0f, 100.0f, 10000.0f);
    g_application.device->SetTransform(2, &g_application.view);
    g_application.device->SetTransform(3, &g_application.projection);
    g_application.device->GetViewport(&g_application.viewport);
    g_application.device->GetDeviceCaps(&g_application.caps);
    if (!(g_application.caps.texture_op_caps & 0x40))
        g_log.Append(str_no_texop_add);
    if (g_application.caps.max_texture_width <= 256)
        g_log.Append(str_no_512_textures);
    if (!(g_application.config.flags & 1) && hardware) {
        if (g_application.direct3d->CheckDeviceFormat(0, 1, parameters.back_buffer_format,
                0, 3, 21) == 0) {
            g_application.flags |= 4;
        } else {
            g_application.flags &= ~4u;
            g_application.config.flags |= 1;
            g_log.Append(str_no_a8r8g8b8);
        }
    }
    Renderer_ApplyDeviceDefaults();
    ApplyDefaultViewport(0xFF000000);
    data_004924f0.quit = 0;
    g_application.frames_presented = 0;
    return 0;
}
#pragma code_seg()

// The link's entry: a caller for the whole-program link to see.
extern "C" int __stdcall RigEntry(void* instance, int show) {
    return D3DInitialize_00439890();
}
