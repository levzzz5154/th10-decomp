// Frame timer: the delta-time source the app and the renderer poll each frame.
//
// Recovered 2026-09: both routines of this translation unit are byte-exact
// against the retail image, so no inline assembly is left here.

// ---------------------------------------------------------------------------
// Kernel32 / winmm entry points.  The retail build reaches every one of them
// through its import slot (call dword ptr [__imp__...]), which is what the
// dllimport declaration produces.
// ---------------------------------------------------------------------------
extern "C" __declspec(dllimport) void __stdcall EnterCriticalSection(void* section);
extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(void* section);
extern "C" __declspec(dllimport) int __stdcall QueryPerformanceCounter(long long* count);
extern "C" __declspec(dllimport) unsigned int __stdcall timeGetTime(void);
extern "C" __declspec(dllimport) unsigned int __stdcall timeBeginPeriod(unsigned int period);
extern "C" __declspec(dllimport) unsigned int __stdcall timeEndPeriod(unsigned int period);

// ---------------------------------------------------------------------------
// Frame timer state (retail addresses in the comments).
// ---------------------------------------------------------------------------
struct CriticalSectionStorage {
    unsigned int opaque[6];                 // CRITICAL_SECTION, 24 bytes
};

extern "C" CriticalSectionStorage data_004922ec;    // 0x004922EC  timer lock
extern "C" unsigned char data_00492321;             // 0x00492321  nesting counter
extern "C" long long data_00492508;                 // 0x00492508  QPC ticks per second
extern "C" long long data_00492510;                 // 0x00492510  previous QPC sample
extern "C" double data_00492540;                    // 0x00492540  smallest delta seen

// QueryPerformanceCounter fills a 64-bit tick count.  The retail frame keeps a
// trailing DWORD next to it (the 20-byte frame of 0x00439540), so the sample is
// declared as the record the image reserves; the last field is never read.
#pragma pack(push, 4)
struct TickSample {
    long long ticks;                        // counter value
    unsigned int reserved;                  // unused; keeps the retail stack extent
};
#pragma pack(pop)

// 0x00439540..0x004395DE - FrameTimer_GetDelta
//
// Delta time in seconds since the previous call, taken from the performance
// counter when one is available and from timeGetTime otherwise.  Both paths
// update the smallest delta seen and run under the timer lock; the nesting
// counter lets the caller see that it is inside the timer.
extern "C" double __cdecl FrameTimer_GetDelta(void) {
    double Time;
    TickSample sample;
    EnterCriticalSection(&data_004922ec);
    ++data_00492321;
    if (data_00492508 != 0) {
        QueryPerformanceCounter(&sample.ticks);
        Time = (double)(sample.ticks - data_00492510) / (double)data_00492508;
        if (data_00492540 > Time)
            data_00492540 = Time;
        LeaveCriticalSection(&data_004922ec);
        --data_00492321;
        return Time - data_00492540;
    }
    // No performance counter: the millisecond clock is the only source, and the
    // delta is scaled to seconds only after the smallest one is remembered.
    timeBeginPeriod(1);
    Time = (double)timeGetTime();
    timeEndPeriod(1);
    if (data_00492540 > Time)
        data_00492540 = Time;
    Time = (Time - data_00492540 * 1000.0) * 0.001;
    LeaveCriticalSection(&data_004922ec);
    --data_00492321;
    return Time;
}

// ---------------------------------------------------------------------------
// Direct3D 9 device state used by the device reset below.
//
// g_pD3DDevice (0x00491C30) holds the retail IDirect3DDevice9 pointer; its
// vtable is the IDirect3DDevice9 one, so only the slots this file reaches are
// named and the remaining entries keep the layout by staying untyped.
// ---------------------------------------------------------------------------
struct D3D9Device;

struct D3D9DeviceVtbl {
    void* unused_000[57];                                                        // 0x000..0x0E0
    long (__stdcall* SetRenderState)(D3D9Device*, unsigned int, unsigned int);    // 0x0E4
    void* unused_0E8[9];                                                         // 0x0E8..0x108
    long (__stdcall* SetTextureStageState)(D3D9Device*, unsigned int,
                                           unsigned int, unsigned int);          // 0x10C
    void* unused_110[1];                                                         // 0x110
    long (__stdcall* SetSamplerState)(D3D9Device*, unsigned int,
                                      unsigned int, unsigned int);               // 0x114
};

struct D3D9Device {
    D3D9DeviceVtbl* lpVtbl;
};

extern "C" unsigned char g_sprt_ctrl;             // 0x00491C10  game state object
extern "C" unsigned char data_00491c30;             // 0x00491C30  IDirect3DDevice9*

// Every call site reads the global again: the device is published around a
// Reset (0x00438AD0), so the pointer is not allowed to live in a register.
#define D3D9_DEVICE (*(D3D9Device**)&data_00491c30)

// D3DRENDERSTATETYPE values used by the default 2D state.
enum {
    D3DRS_ZENABLE = 7,
    D3DRS_SHADEMODE = 9,
    D3DRS_ALPHATESTENABLE = 15,
    D3DRS_SRCBLEND = 19,
    D3DRS_DESTBLEND = 20,
    D3DRS_CULLMODE = 22,
    D3DRS_ZFUNC = 23,
    D3DRS_ALPHAREF = 24,
    D3DRS_ALPHAFUNC = 25,
    D3DRS_ALPHABLENDENABLE = 27,
    D3DRS_FOGENABLE = 28,
    D3DRS_FOGCOLOR = 34,
    D3DRS_FOGTABLEMODE = 35,
    D3DRS_FOGSTART = 36,
    D3DRS_FOGEND = 37,
    D3DRS_FOGDENSITY = 38,
    D3DRS_LIGHTING = 137,
    D3DRS_FOGVERTEXMODE = 140,
    D3DRS_MULTISAMPLEANTIALIAS = 161
};

// D3DTEXTURESTAGESTATETYPE values used by the default 2D state.
enum {
    D3DTSS_COLOROP = 1,
    D3DTSS_COLORARG1 = 2,
    D3DTSS_COLORARG2 = 3,
    D3DTSS_ALPHAOP = 4,
    D3DTSS_ALPHAARG1 = 5,
    D3DTSS_ALPHAARG2 = 6,
    D3DTSS_TEXCOORDINDEX = 11,
    D3DTSS_TEXTURETRANSFORMFLAGS = 24
};

// D3DSAMPLERSTATETYPE values used by the default 2D state.
enum {
    D3DSAMP_ADDRESSU = 1,
    D3DSAMP_ADDRESSV = 2,
    D3DSAMP_ADDRESSW = 3,
    D3DSAMP_MAGFILTER = 5,
    D3DSAMP_MINFILTER = 6,
    D3DSAMP_MIPFILTER = 7
};

// Tail of the game state object (g_pGameStateManager, 0x00491C10) that caches
// the state the sprite batches push; the reset below restores its defaults.
// Only the widths and offsets of these fields are certain, so the dirty
// markers after the texture factor keep their retail addresses as names.
struct SprtCtrlStateCacheView {
    unsigned char unused_0000[0x3ADA64];
    unsigned int texture_factor;          // +0x3ADA64
    unsigned char flags_3ADA68;           // +0x3ADA68
    unsigned char flags_3ADA69;           // +0x3ADA69
    unsigned char flags_3ADA6A;           // +0x3ADA6A
    unsigned char flags_3ADA6B;           // +0x3ADA6B
    unsigned char flags_3ADA6C;           // +0x3ADA6C
};

// 0x00439D20..0x00439FE5 - Renderer_ApplyDeviceDefaults
//
// Re-applies every render state the 2D sprite renderer assumes (opaque-safe
// blending, alpha test, fog and a single modulated texture stage with clamped
// filtering), then invalidates the cached sprite state.  Runs right after a
// successful device Reset.  Returns the game state object it touched; the
// caller ignores it.
extern "C" SprtCtrlStateCacheView* __cdecl Renderer_ApplyDeviceDefaults(void) {
    D3D9_DEVICE->lpVtbl->SetRenderState(D3D9_DEVICE, D3DRS_ZENABLE, 1);
    D3D9_DEVICE->lpVtbl->SetRenderState(D3D9_DEVICE, D3DRS_LIGHTING, 0);
    D3D9_DEVICE->lpVtbl->SetRenderState(D3D9_DEVICE, D3DRS_CULLMODE, 1);
    D3D9_DEVICE->lpVtbl->SetRenderState(D3D9_DEVICE, D3DRS_ALPHABLENDENABLE, 1);
    D3D9_DEVICE->lpVtbl->SetRenderState(D3D9_DEVICE, D3DRS_SHADEMODE, 2);
    D3D9_DEVICE->lpVtbl->SetRenderState(D3D9_DEVICE, D3DRS_SRCBLEND, 5);
    D3D9_DEVICE->lpVtbl->SetRenderState(D3D9_DEVICE, D3DRS_DESTBLEND, 6);
    D3D9_DEVICE->lpVtbl->SetRenderState(D3D9_DEVICE, D3DRS_ZFUNC, 8);
    D3D9_DEVICE->lpVtbl->SetRenderState(D3D9_DEVICE, D3DRS_ALPHATESTENABLE, 1);
    D3D9_DEVICE->lpVtbl->SetRenderState(D3D9_DEVICE, D3DRS_ALPHAREF, 1);
    D3D9_DEVICE->lpVtbl->SetRenderState(D3D9_DEVICE, D3DRS_ALPHAFUNC, 7);
    D3D9_DEVICE->lpVtbl->SetRenderState(D3D9_DEVICE, D3DRS_FOGENABLE, 1);
    // D3DRS_FOGDENSITY/FOGSTART/FOGEND take the FLOAT bit pattern, which the
    // retail build pushes out of a stack slot; the local keeps that shape.
    float bits = 1.0f;
    D3D9_DEVICE->lpVtbl->SetRenderState(D3D9_DEVICE, D3DRS_FOGDENSITY,
                                        *(unsigned int*)&bits);
    D3D9_DEVICE->lpVtbl->SetRenderState(D3D9_DEVICE, D3DRS_FOGTABLEMODE, 0);
    D3D9_DEVICE->lpVtbl->SetRenderState(D3D9_DEVICE, D3DRS_FOGVERTEXMODE, 3);
    D3D9_DEVICE->lpVtbl->SetRenderState(D3D9_DEVICE, D3DRS_FOGCOLOR, 0xFFA0A0A0u);
    bits = 1000.0f;
    D3D9_DEVICE->lpVtbl->SetRenderState(D3D9_DEVICE, D3DRS_FOGSTART,
                                        *(unsigned int*)&bits);
    bits = 5000.0f;
    D3D9_DEVICE->lpVtbl->SetRenderState(D3D9_DEVICE, D3DRS_FOGEND,
                                        *(unsigned int*)&bits);
    D3D9_DEVICE->lpVtbl->SetRenderState(D3D9_DEVICE, D3DRS_MULTISAMPLEANTIALIAS, 0);

    D3D9_DEVICE->lpVtbl->SetTextureStageState(D3D9_DEVICE, 0, D3DTSS_ALPHAOP, 4);
    D3D9_DEVICE->lpVtbl->SetTextureStageState(D3D9_DEVICE, 0, D3DTSS_ALPHAARG1, 2);
    D3D9_DEVICE->lpVtbl->SetTextureStageState(D3D9_DEVICE, 0, D3DTSS_ALPHAARG2, 3);
    D3D9_DEVICE->lpVtbl->SetTextureStageState(D3D9_DEVICE, 0, D3DTSS_COLOROP, 4);
    D3D9_DEVICE->lpVtbl->SetTextureStageState(D3D9_DEVICE, 0, D3DTSS_COLORARG1, 2);
    D3D9_DEVICE->lpVtbl->SetTextureStageState(D3D9_DEVICE, 0, D3DTSS_COLORARG2, 3);
    D3D9_DEVICE->lpVtbl->SetTextureStageState(D3D9_DEVICE, 0,
                                              D3DTSS_TEXTURETRANSFORMFLAGS, 2);
    D3D9_DEVICE->lpVtbl->SetTextureStageState(D3D9_DEVICE, 0, D3DTSS_TEXCOORDINDEX, 0);

    D3D9_DEVICE->lpVtbl->SetSamplerState(D3D9_DEVICE, 0, D3DSAMP_MIPFILTER, 0);
    D3D9_DEVICE->lpVtbl->SetSamplerState(D3D9_DEVICE, 0, D3DSAMP_MAGFILTER, 2);
    D3D9_DEVICE->lpVtbl->SetSamplerState(D3D9_DEVICE, 0, D3DSAMP_MINFILTER, 2);
    D3D9_DEVICE->lpVtbl->SetSamplerState(D3D9_DEVICE, 0, D3DSAMP_ADDRESSW, 3);
    D3D9_DEVICE->lpVtbl->SetSamplerState(D3D9_DEVICE, 0, D3DSAMP_ADDRESSU, 1);
    D3D9_DEVICE->lpVtbl->SetSamplerState(D3D9_DEVICE, 0, D3DSAMP_ADDRESSV, 1);

    SprtCtrlStateCacheView* state = *(SprtCtrlStateCacheView**)&g_sprt_ctrl;
    if (state != 0) {
        state->flags_3ADA68 = 3;
        state->flags_3ADA69 = 0xFF;
        state->flags_3ADA6A = 0xFF;
        state->texture_factor = 0;
        state->flags_3ADA6C = 0xFF;
    }
    return state;
}
