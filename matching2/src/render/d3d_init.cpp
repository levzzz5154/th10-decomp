// =============================================================================
// d3d_init.cpp - Direct3D 9 device creation, camera and caps probe
// Function: 0x00439890
// =============================================================================
#include "th10/game/entity.hpp"

#include <cmath>

// IDirect3D9 vtable offsets used here:
// +0x20: GetAdapterDisplayMode (idx 8)
// +0x28: CheckDeviceFormat     (idx 10)
// +0x40: CreateDevice          (idx 16)
// +0x08: IUnknown::Release     (idx 2)
// IDirect3DDevice9 vtable offsets used here:
// +0x1C: GetDeviceCaps         (idx 7)
// +0xB0: SetTransform          (idx 44)
// +0xC0: GetViewport           (idx 48)

extern void*    g_pD3D9;         // 0x00491C2C
extern void*    g_pD3DDevice;    // 0x00491C30
extern void*    g_pWnd;          // 0x00491C70 (retail hWnd)
// byte_491D65: set from the startup dialog. Non-zero selects retail's
// borderless window, whose present parameters are Windowed with the desktop
// back-buffer format; zero selects the exclusive 640x480 device.
extern uint8_t  DAT_00491d65;
// Retail treats this as a dword: 0x00438AD0 tests bit 0x100 of it to decide
// whether to raise the startup dialog. Declaring it as a byte made that bit
// unreachable. The low two bits this file tests are unaffected.
extern uint32_t DAT_00491d78;    // bit 0 = force 16-bit, bit 1 = skip HAL
extern int8_t   DAT_00491d62;    // back-buffer depth selector (-1 = unset)
extern uint32_t DAT_00491ff4;    // status flags
extern uint32_t DAT_00491fdc;    // "vsync disabled" marker
extern uint32_t _DAT_00491fe0;   // refresh-rate honoured marker
extern uint8_t  DAT_00492518;    // byte_492518 - replay launch
extern uint32_t DAT_004924f4;
extern uint32_t _DAT_00491fe4;
extern uint32_t DAT_00491d0c[14];   // unk_491D0C - D3DPRESENT_PARAMETERS copy
extern float    DAT_00491c74[16];   // view matrix
extern float    DAT_00491cb4[16];   // projection matrix
extern uint32_t DAT_00491cf4[6];    // D3DVIEWPORT9 read back after creation
extern uint8_t  DAT_00492000[];     // D3DCAPS9 filled by GetDeviceCaps
extern uint8_t  DAT_00492090;       // caps +0x90 - TextureOpCaps low byte
extern uint32_t DAT_00492058;       // caps +0x58 - MaxTextureWidth
extern double   DAT_00470c00;       // dbl_470C00 = 0.2617993950843811
extern float    DAT_00470bfc;       // flt_470BFC = 240.0
extern char     DAT_00474f70[];     // the retail text log object
extern char     DAT_0046f640[];     // depth-selector defaulted
extern char     DAT_0046f614[];     // refresh-rate line
extern char     DAT_0046f5f0[];     // "VSync..."
extern char     DAT_0046f4a8[];     // "T&L HAL " (created)
extern char     DAT_0046f5cc[];     // "T&L HAL " (retry failed)
extern char     DAT_0046f4c4[];     // "HAL " (created)
extern char     DAT_0046f5ac[];     // "HAL " (retry failed)
extern char     DAT_0046f584[];     // refresh-rate retry notice
extern char     DAT_0046f514[];     // "Direct3D ..." (fatal)
extern char     DAT_0046f54c[];     // vsync retry notice
extern char     DAT_0046f4d8[];     // "REF " (created)
extern char     DAT_0046f458[];     // "D3DTEXOPCAPS_ADD "
extern char     DAT_0046f408[];     // "512 "
extern char     DAT_0046f3c0[];     // "D3DFMT_A8R8G8B8 "

struct TextLog;
void TextLog_Append(TextLog* log, const char* format, ...);      // 0x0044B810
void TextLog_AppendLine(TextLog* log, const char* format, ...);  // 0x0044B8E0
void D3D_ApplyDefaultRenderState(int initialization_mode);       // 0x00439D20
void D3D_InitializeViewport(void);                               // 0x0043BCD0

extern "C" void D3DXMatrixLookAtLH(float* out, float* eye, float* at,
                                   float* up);
extern "C" void D3DXMatrixPerspectiveFovLH(float* out, float fov, float aspect,
                                           float znear, float zfar);

namespace {

TextLog* RetailLog() {
    return reinterpret_cast<TextLog*>(DAT_00474f70);
}

void* const* VTable(void* object) {
    return *reinterpret_cast<void* const* const*>(object);
}

} // namespace

// ============================================================================
// 0x00439890
//
// 1. GetAdapterDisplayMode, so the windowed back buffer takes the desktop
//    format instead of a fixed one.
// 2. Pick the back-buffer format, refresh rate and presentation interval.
// 3. CreateDevice ladder: HAL + hardware vertex processing (0x40), HAL +
//    mixed (0x20), then REF + mixed (0x20), retrying the whole ladder once
//    without the refresh rate and once without vsync.
// 4. Copy the accepted present parameters to unk_491D0C - every later
//    IDirect3DDevice9::Reset presents that block.
// 5. Build the view/projection matrices and hand them to SetTransform.
// 6. Read back the viewport and the device caps, logging the two caps the
//    game depends on.
// 7. CheckDeviceFormat drives bit 4 of dword_491FF4 (A8R8G8B8 textures).
// 8. Apply the default device state (0x00439D20) and the default viewport
//    with the opaque-black clear (0x0043BCD0).
// ============================================================================
int D3D_Init(void) {
    // D3DPRESENT_PARAMETERS, 14 dwords / 0x38 bytes (retail v10):
    //  0 BackBufferWidth        7 hDeviceWindow
    //  1 BackBufferHeight       8 Windowed
    //  2 BackBufferFormat       9 EnableAutoDepthStencil
    //  3 BackBufferCount       10 AutoDepthStencilFormat
    //  4 MultiSampleType       11 Flags
    //  5 MultiSampleQuality    12 FullScreen_RefreshRateInHz
    //  6 SwapEffect            13 PresentationInterval
    uint32_t present[14];
    uint32_t display_mode[4];   // D3DDISPLAYMODE (retail v9)
    // Retail v5: cleared only when the REF device is the one that came back,
    // and read again by the CheckDeviceFormat guard below.
    uint8_t hardware_device = 1;

    for (int index = 0; index < 14; ++index)
        present[index] = 0;

    typedef void (__stdcall *GetAdapterDisplayMode_t)(void*, uint32_t, void*);
    ((GetAdapterDisplayMode_t)VTable(g_pD3D9)[8])(g_pD3D9, 0, display_mode);

    if (DAT_00491d65 != 0) {
        present[2] = display_mode[3];   // D3DDISPLAYMODE::Format
        present[6] = 1;                 // D3DSWAPEFFECT_DISCARD
        present[8] = 1;                 // Windowed
    } else {
        if ((DAT_00491d78 & 1) != 0) {
            present[2] = 23;            // D3DFMT_R5G6B5
            DAT_00491d62 = 1;
        } else if (DAT_00491d62 == -1) {
            present[2] = 22;            // D3DFMT_X8R8G8B8
            DAT_00491d62 = 0;
            TextLog_Append(RetailLog(), DAT_0046f640);
        } else {
            present[2] = (DAT_00491d62 != 0) + 22;
        }

        if (DAT_00492518 != 0)
            DAT_00491fdc = 1;
        if (DAT_00491fdc != 0) {
            present[12] = 0;
            present[6] = 1;             // D3DSWAPEFFECT_DISCARD
            present[13] = 0x80000000u;  // D3DPRESENT_INTERVAL_IMMEDIATE
            TextLog_Append(RetailLog(), DAT_0046f5f0);
        } else {
            present[12] = 60;           // FullScreen_RefreshRateInHz
            present[13] = 1;            // D3DPRESENT_INTERVAL_ONE
            TextLog_Append(RetailLog(), DAT_0046f614);
            present[6] = 1;             // D3DSWAPEFFECT_DISCARD
        }
    }

    present[0] = 640;
    present[1] = 480;
    present[9] = 1;    // EnableAutoDepthStencil
    present[10] = 80;  // D3DFMT_D16
    present[11] = 1;   // D3DPRESENTFLAG_LOCKABLE_BACKBUFFER
    DAT_00491ff4 |= 2;
    _DAT_00491fe0 = 1;

    typedef int (__stdcall *CreateDevice_t)(void*, uint32_t, int, void*,
                                            uint32_t, void*, void**);
    CreateDevice_t create_device = (CreateDevice_t)VTable(g_pD3D9)[16];
    int retried = 0;   // retail v0: only the second lap logs the failures

    for (;;) {
        if ((DAT_00491d78 & 2) == 0) {
            if (create_device(g_pD3D9, 0, 1, g_pWnd, 0x40, present,
                              &g_pD3DDevice) >= 0) {
                TextLog_Append(RetailLog(), DAT_0046f4a8);
                DAT_00491ff4 |= 1;
                break;
            }
            if (retried)
                TextLog_Append(RetailLog(), DAT_0046f5cc);
            if (create_device(g_pD3D9, 0, 1, g_pWnd, 0x20, present,
                              &g_pD3DDevice) >= 0) {
                TextLog_Append(RetailLog(), DAT_0046f4c4);
                DAT_00491ff4 &= 0xFFFFFFFEu;
                break;
            }
            if (retried)
                TextLog_Append(RetailLog(), DAT_0046f5ac);
        }
        if (create_device(g_pD3D9, 0, 2, g_pWnd, 0x20, present,
                          &g_pD3DDevice) >= 0) {
            TextLog_Append(RetailLog(), DAT_0046f4d8);
            DAT_00491ff4 &= 0xFFFFFFFEu;
            hardware_device = 0;
            break;
        }
        if (DAT_00491fdc != 0) {
            if (present[13] != 0x80000000u) {
                TextLog_AppendLine(RetailLog(), DAT_0046f514);
                if (g_pD3D9 != 0) {
                    typedef void (__stdcall *Release_t)(void*);
                    ((Release_t)VTable(g_pD3D9)[2])(g_pD3D9);
                    g_pD3D9 = 0;
                }
                return 1;
            }
            TextLog_Append(RetailLog(), DAT_0046f54c);
            present[13] = 1;            // D3DPRESENT_INTERVAL_ONE
            present[6] = 3;             // D3DSWAPEFFECT_COPY
        } else {
            TextLog_Append(RetailLog(), DAT_0046f584);
            present[12] = 0;
            _DAT_00491fe0 = 0;
            retried = 1;
        }
    }

    // qmemcpy(&unk_491D0C, v10, 0x38): the block every later Reset presents.
    for (int index = 0; index < 14; ++index)
        DAT_00491d0c[index] = present[index];

    // 439B68..439BE7: eye (320.0, -240.0, -(flt_470BFC / tan(dbl_470C00))),
    // look-at (320.0, -240.0, 0.0), up (0.0, 1.0, 0.0).
    float eye[3];
    float at[3];
    float up[3];
    eye[0] = 320.0f;
    eye[1] = -240.0f;
    eye[2] = (float)-((double)DAT_00470bfc / std::tan(DAT_00470c00));
    at[0] = 320.0f;
    at[1] = -240.0f;
    at[2] = 0.0f;
    up[0] = 0.0f;
    up[1] = 1.0f;
    up[2] = 0.0f;

    D3DXMatrixLookAtLH(DAT_00491c74, eye, at, up);
    D3DXMatrixPerspectiveFovLH(DAT_00491cb4,
                               0.5235988f,   // 3F060A92h
                               1.3333334f,   // 3FAAAAABh
                               100.0f,       // 42C80000h
                               10000.0f);    // 461C4000h

    typedef void (__stdcall *SetTransform_t)(void*, uint32_t, void*);
    SetTransform_t set_transform = (SetTransform_t)VTable(g_pD3DDevice)[44];
    set_transform(g_pD3DDevice, 2, DAT_00491c74);   // D3DTS_VIEW
    set_transform(g_pD3DDevice, 3, DAT_00491cb4);   // D3DTS_PROJECTION

    typedef void (__stdcall *GetViewport_t)(void*, void*);
    ((GetViewport_t)VTable(g_pD3DDevice)[48])(g_pD3DDevice, DAT_00491cf4);

    typedef void (__stdcall *GetDeviceCaps_t)(void*, void*);
    ((GetDeviceCaps_t)VTable(g_pD3DDevice)[7])(g_pD3DDevice, DAT_00492000);

    if ((DAT_00492090 & 0x40) == 0)       // D3DTEXOPCAPS_ADD
        TextLog_Append(RetailLog(), DAT_0046f458);
    if (DAT_00492058 <= 0x100)            // MaxTextureWidth
        TextLog_Append(RetailLog(), DAT_0046f408);

    if ((DAT_00491d78 & 1) == 0 && hardware_device != 0) {
        // CheckDeviceFormat(0, D3DDEVTYPE_HAL, BackBufferFormat, 0,
        //                   D3DRTYPE_TEXTURE, D3DFMT_A8R8G8B8)
        typedef int (__stdcall *CheckDeviceFormat_t)(void*, uint32_t, int,
                                                     uint32_t, uint32_t,
                                                     uint32_t, uint32_t);
        CheckDeviceFormat_t check_format =
            (CheckDeviceFormat_t)VTable(g_pD3D9)[10];
        if (check_format(g_pD3D9, 0, 1, present[2], 0, 3, 21) != 0) {
            DAT_00491ff4 &= 0xFFFFFFFBu;
            DAT_00491d78 |= 1;
            TextLog_Append(RetailLog(), DAT_0046f3c0);
        } else {
            DAT_00491ff4 |= 4;
        }
    }

    D3D_ApplyDefaultRenderState(0);   // sub_439D20
    D3D_InitializeViewport();         // sub_43BCD0(0FF000000h)
    DAT_004924f4 = 0;
    _DAT_00491fe4 = 0;
    return 0;
}
