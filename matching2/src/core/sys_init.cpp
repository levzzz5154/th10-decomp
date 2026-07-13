// =============================================================================
// sys_init.cpp - System initialization (window, D3D, performance, mutex)
// Functions: 0x004392e0, 0x00439730, 0x00439890, 0x00439ff0
// =============================================================================
#include "th10/th10_types.hpp"
#include "th10/entity.hpp"

// ---- Globals ----
extern HWND    g_pWnd;
extern HANDLE  DAT_00497ba8;     // mutex handle
extern DWORD   DAT_00491ff4;     // flags
extern u8      DAT_00491d65;
extern u8      DAT_00491d78;
extern u8      DAT_00491d62;
extern u8      DAT_00492518;
extern i32     DAT_00491fdc;
extern i32     _DAT_00491fe0;
extern i32     DAT_004924f4;
extern i32     _DAT_00491fe4;
extern HWND    DAT_00491c70;
extern void*   g_pD3D9;
extern void*   g_pD3DDevice;
extern f32     DAT_00491c14;
extern f32     DAT_00491c18;
extern f32     DAT_00491c1c;
extern f32     DAT_00491c20;
extern f32     DAT_00491c24;
extern f32     DAT_00491d0c[14];  // D3DPRESENT_PARAMETERS copy
extern f32     DAT_00491c74[16];  // view matrix
extern f32     DAT_00491cb4[16];  // projection matrix
extern f32     DAT_00491cf4[4];   // viewport
extern f32     DAT_00492000[36];  // render state block
extern f32     DAT_00492090;      // caps bit
extern i32     DAT_00492058;      // caps value
extern i64     DAT_00492508;      // performance frequency
extern i64     DAT_00492510;      // performance counter
extern DWORD   DAT_0049251c;      // saved work area
extern DWORD   DAT_00492520;      // saved SPI_53
extern DWORD   DAT_00492524;      // saved SPI_54
extern DWORD   DAT_004924fc;      // wndclass style
extern DWORD   DAT_00492500;      // wndclass cbClsExtra
extern f32     _DAT_00470c00;
extern f32     _DAT_00470bfc;
extern char    DAT_00474f70[];     // log buffer
extern char    DAT_0046f394[];     // "already running" msg
extern char    DAT_0046f640[];
extern char    DAT_0046f614[];
extern char    DAT_0046f5f0[];
extern char    DAT_0046f4a8[];
extern char    DAT_0046f5cc[];
extern char    DAT_0046f4c4[];
extern char    DAT_0046f5ac[];
extern char    DAT_0046f584[];
extern char    DAT_0046f514[];
extern char    DAT_0046f54c[];
extern char    DAT_0046f4d8[];
extern char    DAT_0046f458[];
extern char    DAT_0046f408[];
extern char    DAT_0046f3c0[];
extern char    DAT_0046f66c[];     // window class name
extern void     FUN_0044b810(char* buf, const char* msg);
extern void     FUN_0044b8e0(const char* msg);
extern void     FUN_0043a290(char* path);
extern int      FUN_0044b4d0(const char* str);
extern void     FUN_00439d20(int);
extern void     FUN_0043bcd0(void);
extern void     FUN_004390e0(void);   // wndproc
extern void     D3DXMatrixLookAtLH(void*, void*, void*, void*);
extern void     D3DXMatrixPerspectiveFovLH(void*, f32, f32, f32, f32);

// =====================================================
// 0x004392E0 - Save system settings, init performance counters
// From Ghidra: calls SystemParametersInfoA (save), QueryPerformance*
// Pure C++ matchable (all __stdcall / cdecl API calls)
// =====================================================
void SystemInit_PerfAndSettings(void) {
    SystemParametersInfoA(0x10, 0, &DAT_0049251c, 0);  // SPI_GETWORKAREA (0x30? 0x10?)
    SystemParametersInfoA(0x53, 0, &DAT_00492520, 0);
    SystemParametersInfoA(0x54, 0, &DAT_00492524, 0);
    SystemParametersInfoA(0x11, 0, NULL, 2);             // SPI_SETWORKAREA
    SystemParametersInfoA(0x55, 0, NULL, 2);
    SystemParametersInfoA(0x56, 0, NULL, 2);
    QueryPerformanceFrequency((LONGLONG*)&DAT_00492508);
    QueryPerformanceCounter((LONGLONG*)&DAT_00492510);
}

// =====================================================
// 0x00439FF0 - Instance check (CreateMutex, .lnk resolution)
// From Ghidra: creates "Touhou 10 App" mutex, checks for duplicates,
// handles .lnk shortcut resolution for replay drag-drop
// Mixed - has custom control flow with register vars
// =====================================================
// (Naked asm - complex SEH + string handling)

// =====================================================
// 0x00439730 - Window creation (RegisterClass + CreateWindowEx)
// From Ghidra: registers "BASE" window class, creates window,
// handles fullscreen vs windowed mode via SystemMetrics
// =====================================================
// (Naked asm - uses EBX as unaff_EBX for HINSTANCE)

// =====================================================
// 0x00439890 - D3D device creation + camera setup
// From Ghidra: enumerates display modes, creates D3D device with
// HW VP or SW VP fallback, sets up view/projection matrices, viewport.
// Complex fallback logic: tries 0x40 (HW VP), then 0x20 (mixed),
// then 0x20 with windowed (0x2). Largest init function.
// =====================================================
// (Naked asm - complex D3D COM interface calls via vtable)
