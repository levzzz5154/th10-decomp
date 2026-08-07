// =============================================================================
// d3d_init.cpp - Direct3D 9 device creation and render state setup
// Function: 0x00439890
// =============================================================================
#include "th10/game/entity.hpp"

// D3D COM interface - vtable offsets used:
// +0x08: IUnknown::Release
// +0x20: IDirect3D9::GetAdapterDisplayMode (idx 8)
// +0x28: IDirect3D9::CheckDeviceFormatConversion (idx 10)
// +0x40: IDirect3D9::CreateDevice (idx 16)
// Device vtable:
// +0x1C: IDirect3DDevice9::SetRenderState (idx 7)
// +0xB0: IDirect3DDevice9::SetTransform (idx 44)
// +0xC0: IDirect3DDevice9::SetViewport (idx 48)

extern void*    g_pD3D9;
extern void*    g_pD3DDevice;
extern void*    g_pWnd;
extern uint8_t  DAT_00491d65;    // fullscreen flag
// Retail treats this as a dword: 0x00438AD0 tests bit 0x100 of it to decide
// whether to raise the startup dialog. Declaring it as a byte made that bit
// unreachable. The low two bits this file tests are unaffected.
extern uint32_t DAT_00491d78;    // device caps flags
extern int8_t   DAT_00491d62;    // display mode index
extern uint32_t DAT_00491ff4;    // status flags
extern uint32_t DAT_00491fdc;    // vsync flag
extern uint32_t _DAT_00491fe0;   // windowed flag
extern uint32_t DAT_00492518;    // replay flag
extern uint32_t DAT_004924f4;
extern uint32_t _DAT_00491fe4;
extern float    DAT_00491d0c[14];   // D3DPRESENT_PARAMETERS copy
extern float    DAT_00491c74[16];   // view matrix
extern float    DAT_00491cb4[16];   // projection matrix
extern float    DAT_00491cf4[4];    // viewport
extern float    DAT_00492000[36];   // render state block
extern float    DAT_00492090;       // caps bit
extern uint32_t DAT_00492058;       // caps value
extern float    _DAT_00470c00;      // FOV angle (radians)
extern float    _DAT_00470bfc;      // camera distance
extern char     DAT_00474f70[];     // log buffer
extern char     DAT_0046f640[];
extern char     DAT_0046f614[];
extern char     DAT_0046f5f0[];
extern char     DAT_0046f4a8[];
extern char     DAT_0046f5cc[];
extern char     DAT_0046f4c4[];
extern char     DAT_0046f5ac[];
extern char     DAT_0046f584[];
extern char     DAT_0046f514[];
extern char     DAT_0046f54c[];
extern char     DAT_0046f4d8[];
extern char     DAT_0046f458[];
extern char     DAT_0046f408[];
extern char     DAT_0046f3c0[];

void Logger_AppendFormatted(char* buf, const char* msg);
void Platform_LogMessage(const char* msg);
void D3D_ApplyDefaultRenderState(int initialization_mode);
void D3D_InitializeViewport(void);

extern "C" float tanf(float);
extern "C" void D3DXMatrixLookAtLH(float* out, float* eye, float* at, float* up);
extern "C" void D3DXMatrixPerspectiveFovLH(float* out, float fov, float aspect, float znear, float zfar);

// ============================================================================
// 0x00439890 - D3D Device Creation + Camera/Render State Setup
//
// 1. GetAdapterDisplayMode to fill D3DPRESENT_PARAMETERS
// 2. Determine refresh rate / vsync mode based on config
// 3. Try CreateDevice with hardware VP (0x40), then mixed VP (0x20),
//    then software VP with windowed fallback (0x20 + windowed=2)
// 4. Copy present params to global, set up view/projection matrices
// 5. Set viewport, render state block
// 6. Check device format conversion for fullscreen anti-aliasing
// 7. Call post-init functions
//
// Uses extraout_ECX (non-standard register output) — needs __asm for matching
// ============================================================================
int D3D_Init(void) {
    // D3DPRESENT_PARAMETERS (14 dwords = 56 bytes in presentation_parameters)
    // Layout: BackBufferWidth, BackBufferHeight, BackBufferFormat, BackBufferCount,
    //         MultiSampleType, MultiSampleQuality, SwapEffect, hDeviceWindow,
    //         Windowed, EnableAutoDepthStencil, AutoDepthStencilFormat,
    //         Flags, FullScreen_RefreshRateInHz, PresentationInterval
    // The zeroing loop below writes pp[4..17] (the 4-dword front alignment
    // area + the 14 present-parameter dwords), so the array carries 18.
    uint32_t pp[18];  // includes the extra dword block at the front
    uint32_t extra[6]; // additional params (uStack_24..iStack_10)

    // Zero the tail of present params
    uint32_t* p = pp + 4;
    for (int i = 0xE; i != 0; i--) {
        *p++ = 0;
    }

    // GetAdapterDisplayMode(0, &displayMode) -> fills pp[0..2]
    // vtable offset 0x20 = method index 8
    typedef void (__stdcall *GetAdapterDisplayMode_t)(void*, uint32_t, void*);
    GetAdapterDisplayMode_t getMode = *(GetAdapterDisplayMode_t*)((uintptr_t)*(uint32_t*)g_pD3D9 + 0x20);
    getMode(g_pD3D9, 0, pp);

    if (DAT_00491d65 == 0) {
        // Windowed mode
        if ((DAT_00491d78 & 1) == 0) {
            if (DAT_00491d62 == -1) {
                pp[3] = 0x16;  // D3DFMT_R5G6B5
                DAT_00491d62 = 0;
                Logger_AppendFormatted(DAT_00474f70, DAT_0046f640);
            } else {
                pp[3] = (DAT_00491d62 != 0) + 0x16;  // 0x16 or 0x17
            }
        } else {
            pp[3] = 0x17;  // D3DFMT_X8R8G8B8
            DAT_00491d62 = 1;
        }

        if (DAT_00492518 == 0) {
            if (DAT_00491fdc == 0) {
                extra[4] = 0x3C;   // 60Hz
                extra[5] = 1;      // PresentationInterval = D3DPRESENT_INTERVAL_ONE
                Logger_AppendFormatted(DAT_00474f70, DAT_0046f614);
                goto lab_windowed_vsync;
            }
        } else {
            DAT_00491fdc = 1;
        }
        extra[4] = 0;
        extra[3] = 1;    // Windowed = true
        extra[5] = (uint32_t)0x80000000;  // D3DPRESENT_INTERVAL_IMMEDIATE
                Logger_AppendFormatted(DAT_00474f70, DAT_0046f5f0);
    } else {
        // Fullscreen mode
        pp[3] = pp[0];   // use display mode format
        extra[0] = 1;     // uStack_24 = 1 (BackBufferCount?)
    lab_windowed_vsync:
        extra[3] = 1;     // windowed
    }

    DAT_00491ff4 |= 2;
    pp[1] = 0x280;  // BackBufferWidth = 640
    pp[2] = 0x1E0;  // BackBufferHeight = 480
    extra[1] = 1;    // uStack_20 (SwapEffect?)
    extra[2] = 0x50; // uStack_1c (???)
    extra[0] = 1;    // uStack_18 (EnableAutoDepthStencil?)
    _DAT_00491fe0 = 1;

    // CreateDevice attempts with fallback
    typedef int (__stdcall *CreateDevice_t)(void*, uint32_t, int, void*, uint32_t, void*, void**);
    CreateDevice_t createDev = *(CreateDevice_t*)((uintptr_t)*(uint32_t*)g_pD3D9 + 0x40);

    bool bVar1 = false;
    int result;

    while (true) {
        if ((DAT_00491d78 & 2) == 0) {
            // Try hardware vertex processing
            result = createDev(g_pD3D9, 0, 1, g_pWnd, 0x40, pp + 1, &g_pD3DDevice);
            if (result >= 0) {
                Logger_AppendFormatted(DAT_00474f70, DAT_0046f4a8);
                DAT_00491ff4 |= 1;
                goto d3d_setup;
            }
            if (bVar1) Logger_AppendFormatted(DAT_00474f70, DAT_0046f5cc);

            // Try mixed vertex processing
            result = createDev(g_pD3D9, 0, 1, g_pWnd, 0x20, pp + 1, &g_pD3DDevice);
            if (result >= 0) {
                Logger_AppendFormatted(DAT_00474f70, DAT_0046f4c4);
                DAT_00491ff4 &= 0xFFFFFFFE;
                goto d3d_setup;
            }
            if (bVar1) Logger_AppendFormatted(DAT_00474f70, DAT_0046f5ac);
        }

        // Try software vertex processing, windowed
        result = createDev(g_pD3D9, 0, 2, g_pWnd, 0x20, pp + 1, &g_pD3DDevice);
        if (result >= 0) break;

        if (DAT_00491fdc == 0) {
            Logger_AppendFormatted(DAT_00474f70, DAT_0046f584);
            extra[4] = 0;
            _DAT_00491fe0 = 0;
            bVar1 = true;
        } else {
            if (extra[5] != (uint32_t)0x80000000) {
                Platform_LogMessage(DAT_0046f514);
                if (g_pD3D9 != 0) {
                    typedef void (__stdcall *Release_t)(void*);
                    Release_t release = *(Release_t*)((uintptr_t)*(uint32_t*)g_pD3D9 + 8);
                    release(g_pD3D9);
                    g_pD3D9 = 0;
                }
                return 1;
            }
            Logger_AppendFormatted(DAT_00474f70, DAT_0046f54c);
            extra[5] = 1;
            extra[3] = 3;
        }
    }

    Logger_AppendFormatted(DAT_00474f70, DAT_0046f4d8);
    DAT_00491ff4 &= 0xFFFFFFFE;

d3d_setup:
    // Copy present params to global storage
    uint32_t* src = pp;
    uint32_t* dst = (uint32_t*)&DAT_00491d0c;
    for (int i = 0xE; i != 0; i--) {
        *dst++ = *src++;
    }

    // Camera setup
    // Eye:    (320.0, -560.0, 0.0)
    // LookAt: (320.0, -560.0, -dist/tan(fov/2))
    // Up:     (0.0, 1.0, 0.0)
    float eye[3]     = { 320.0f, -560.0f, 0.0f };        // 0x43A00000, 0xC3700000, 0
    float lookAt[3]  = { 320.0f, -560.0f, 0.0f };
    float up[3]      = { 0.0f, 1.0f, 0.0f };

    // fptan(FOV) -> camera Z offset
    float fov = _DAT_00470c00;
    float camZ = -(_DAT_00470bfc / tanf(fov));
    lookAt[2] = camZ;

    D3DXMatrixLookAtLH(DAT_00491c74, eye, lookAt, up);
    D3DXMatrixPerspectiveFovLH(DAT_00491cb4,
        0.3f,     // 0x3F060A92 ≈ 0.5236 rad (30 degrees)
        1.333f,   // 0x3FAAAAAB ≈ 4/3 aspect
        100.0f,   // 0x42C80000 near plane
        10000.0f  // 0x461C4000 far plane
    );

    // SetTransform(D3DTS_VIEW, &viewMatrix)
    typedef void (__stdcall *SetTransform_t)(void*, uint32_t, void*);
    SetTransform_t setTransform = *(SetTransform_t*)((uintptr_t)*(uint32_t*)g_pD3DDevice + 0xB0);
    setTransform(g_pD3DDevice, 2, DAT_00491c74);   // D3DTS_VIEW = 2
    setTransform(g_pD3DDevice, 3, DAT_00491cb4);   // D3DTS_PROJECTION = 3

    // SetViewport
    typedef void (__stdcall *SetViewport_t)(void*, void*);
    SetViewport_t setViewport = *(SetViewport_t*)((uintptr_t)*(uint32_t*)g_pD3DDevice + 0xC0);
    setViewport(g_pD3DDevice, DAT_00491cf4);

    // SetRenderState block
    typedef void (__stdcall *SetRenderState_t)(void*, void*);
    SetRenderState_t setRenderState =
        *(SetRenderState_t*)((uintptr_t)*(uint32_t*)g_pD3DDevice + 0x1C);
    setRenderState(g_pD3DDevice, DAT_00492000);

    // Check device caps
    if (((uint32_t)DAT_00492090 & 0x40) == 0) {
    Logger_AppendFormatted(DAT_00474f70, DAT_0046f458);
    }
    if ((int32_t)DAT_00492058 < 0x101) {
    Logger_AppendFormatted(DAT_00474f70, DAT_0046f408);
    }

    // Check format conversion for fullscreen AA
    if ((DAT_00491d78 & 1) == 0 &&
        ((char)((uint32_t)(uintptr_t)g_pD3DDevice >> 24) != 0)) {
        typedef int (__stdcall *CheckFormat_t)(void*, uint32_t, int, uint32_t, void*, uint32_t, uint32_t);
        CheckFormat_t checkFormat = *(CheckFormat_t*)((uintptr_t)*(uint32_t*)g_pD3D9 + 0x28);
        int fmtResult = checkFormat(g_pD3D9, 0, 1, 0, 0, 3, 0x15);
        if (fmtResult == 0) {
            DAT_00491ff4 |= 4;
        } else {
            DAT_00491d78 |= 1;
            DAT_00491ff4 &= 0xFFFFFFFB;
    Logger_AppendFormatted(DAT_00474f70, DAT_0046f3c0);
        }
    }

    D3D_ApplyDefaultRenderState(0);
    D3D_InitializeViewport();
    DAT_004924f4 = 0;
    _DAT_00491fe4 = 0;
    return 0;
}
