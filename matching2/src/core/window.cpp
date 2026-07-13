// =============================================================================
// window.cpp - Window creation, WndProc, system initialization
// Functions: 0x004390E0 (WndProc), 0x00439730 (CreateWindow),
//            0x004392E0 (SaveSystemSettings), 0x00439FF0 (InstanceCheck)
// =============================================================================
#include "th10/entity.hpp"

// Windows API - using __declspec(dllimport) for correct import call pattern
extern "C" {
    __declspec(dllimport) int     __stdcall SystemParametersInfoA(uint32_t, uint32_t, void*, uint32_t);
    __declspec(dllimport) int     __stdcall QueryPerformanceFrequency(int64_t*);
    __declspec(dllimport) int     __stdcall QueryPerformanceCounter(int64_t*);
    __declspec(dllimport) void*   __stdcall GetStockObject(int);
    __declspec(dllimport) void*   __stdcall LoadCursorA(void*, const char*);
    __declspec(dllimport) uint16_t __stdcall RegisterClassA(void*);
    __declspec(dllimport) void*   __stdcall CreateWindowExA(uint32_t, const char*, const char*,
                                                            uint32_t, int, int, int, int,
                                                            void*, void*, void*, void*);
    __declspec(dllimport) void*   __stdcall SendMessageA(void*, uint32_t, uint32_t, uint32_t);
    __declspec(dllimport) void    __stdcall Sleep(uint32_t);
    __declspec(dllimport) int     __stdcall GetSystemMetrics(int);
    __declspec(dllimport) void*   __stdcall CreateMutexA(void*, int, const char*);
    __declspec(dllimport) uint32_t __stdcall GetLastError(void);
    __declspec(dllimport) uint32_t __stdcall GetModuleFileNameA(void*, char*, uint32_t);
    __declspec(dllimport) uint32_t __stdcall GetConsoleTitleA(char*, uint32_t);
    __declspec(dllimport) void    __stdcall GetStartupInfoA(void*);
    __declspec(dllimport) void*   __stdcall SetForegroundWindow(void*);
    __declspec(dllimport) int     __stdcall ShowCursor(int);
    __declspec(dllimport) void*   __stdcall SetCursor(void*);
    __declspec(dllimport) int     __stdcall DefWindowProcA(void*, uint32_t, uint32_t, uint32_t);
}

// Globals
extern uint8_t  DAT_00491d65;    // fullscreen flag
extern uint32_t DAT_00492500;    // cursor visible flag
extern uint32_t DAT_004924fc;    // cursor state
extern void*    DAT_00491c70;    // HWND
extern void*    g_pWnd;
extern uint32_t DAT_00491ff4;    // status flags
extern uint32_t DAT_00491fe8;    // device change notify handle
extern uint32_t DAT_0049251c;    // saved work area
extern uint32_t DAT_00492520;    // saved SPI_53
extern uint32_t DAT_00492524;    // saved SPI_54
extern int64_t  DAT_00492508;    // perf frequency
extern int64_t  DAT_00492510;    // perf counter
extern char     DAT_0046f66c[];  // window title
extern void*    DAT_00497ba8;    // mutex handle
extern uint8_t  DAT_00492518;    // replay flag

void FUN_0043aeb0(void* this_, uint32_t param);
void FUN_0044b8e0(const char* msg);
int  FUN_0044b4d0(const char* str);
void FUN_0043a290(char* path);

// ============================================================================
// 0x004392E0 - Save System Settings + Init Performance Counters
// Saves current system settings (work area, screen save, power-off), then
// sets new values. Initializes high-resolution timer.
//
// Ghidra decompilation:
//   SystemParametersInfoA(0x10, 0, &DAT_0049251c, 0)  // SPI_GETWORKAREA
//   SystemParametersInfoA(0x53, 0, &DAT_00492520, 0)
//   SystemParametersInfoA(0x54, 0, &DAT_00492524, 0)
//   SystemParametersInfoA(0x11, 0, NULL, 2)           // SPI_SETWORKAREA
//   SystemParametersInfoA(0x55, 0, NULL, 2)
//   SystemParametersInfoA(0x56, 0, NULL, 2)
//   QueryPerformanceFrequency(&DAT_00492508)
//   QueryPerformanceCounter(&DAT_00492510)
// ============================================================================
void SaveSystemSettings(void) {
    SystemParametersInfoA(0x10, 0, &DAT_0049251c, 0);
    SystemParametersInfoA(0x53, 0, &DAT_00492520, 0);
    SystemParametersInfoA(0x54, 0, &DAT_00492524, 0);
    SystemParametersInfoA(0x11, 0, 0, 2);
    SystemParametersInfoA(0x55, 0, 0, 2);
    SystemParametersInfoA(0x56, 0, 0, 2);
    QueryPerformanceFrequency(&DAT_00492508);
    QueryPerformanceCounter(&DAT_00492510);
}

// ============================================================================
// 0x004390E0 - Window Procedure
// Handles WM_SETCURSOR (0x20), WM_CLOSE (0x10), WM_QUIT (0x14),
// WM_ENTERIDLE (0x1C), WM_LBUTTONDOWN (0x201), WM_DEVICECHANGE (0x3C9).
// __thiscall: ECX = this, but this is a window proc (HWND-based)
//
// Ghidra decompilation:
//   if (param_2 > 0x20): check 0x201 (SetForeground) and 0x3C9 (device change)
//   if (param_2 == 0x20): show/hide cursor based on fullscreen flag
//   if (param_2 == 0x10): set close flag (DAT_00491ff4 |= 0x80)
//   if (param_2 == 0x14): return 1 (swallow WM_QUIT)
//   if (param_2 == 0x1C): track cursor visibility
//   else: DefWindowProcA
// ============================================================================
void* __fastcall WndProc(void* this_, void* hwnd, uint32_t msg, uint32_t wParam, uint32_t lParam) {
    if (msg > 0x20) {
        if (msg == 0x201) {
            SetForegroundWindow(hwnd);
        } else if (msg == 0x3C9 && DAT_00491fe8 != 0) {
            FUN_0043aeb0(this_, DAT_00491fe8);
            return (void*)DefWindowProcA(hwnd, 0x3C9, wParam, lParam);
        }
        return (void*)DefWindowProcA(hwnd, msg, wParam, lParam);
    }

    if (msg == 0x20) {  // WM_SETCURSOR
        if (DAT_00491d65 == 0 && DAT_00492500 == 0) {
            ShowCursor(0);
            SetCursor(0);
            return (void*)1;
        }
        void* hCursor = LoadCursorA(0, (const char*)0x7F00);
        SetCursor(hCursor);
        ShowCursor(1);
        return (void*)1;
    }

    if (msg == 0x10) {  // WM_CLOSE
        DAT_00491ff4 |= 0x80;
    } else if (msg != 0x14) {  // not WM_QUIT
        if (msg == 0x1C) {  // WM_ENTERIDLE
            DAT_00492500 = (wParam == 0);
            DAT_004924fc = wParam;
            return (void*)DefWindowProcA(hwnd, 0x1C, wParam, lParam);
        }
        return (void*)DefWindowProcA(hwnd, msg, wParam, lParam);
    }
    return (void*)1;  // swallow WM_QUIT
}

// ============================================================================
// 0x00439730 - Create Game Window
// Registers "BASE" window class and creates the game window.
// Windowed mode: 640x480 with WS_VISIBLE|WS_CAPTION|WS_SYSMENU|WS_MINIMIZEBOX
// Fullscreen: extended borderless window using GetSystemMetrics for sizing.
// Uses unaff_EBX = HINSTANCE (non-standard register passing)
//
// Ghidra decompilation:
//   GetStockObject(4)  // NULL_BRUSH
//   LoadCursorA(NULL, IDC_ARROW)
//   local_24 = FUN_004390e0  // wndproc
//   RegisterClassA(&local_28)
//   if (fullscreen):
//     CreateWindowExA(0, "BASE", title, 0x100A0000, ...)
//   else:
//     CreateWindowExA(0, "BASE", title, 0xCF0000, 0, 0, 640, 480, ...)
//   SendMessageA(hwnd, WM_SYSCOMMAND, SC_MINIMIZE, 0)
//   Sleep(16)
//   SendMessageA(hwnd, WM_SYSCOMMAND, SC_RESTORE, 0)
// ============================================================================
uint32_t CreateGameWindow(void* hInstance) {
    // WNDCLASSA structure (40 bytes = 10 dwords)
    uint32_t wndclass[10];
    wndclass[0] = 0;  // style
    wndclass[1] = 0;  // lpfnWndProc (set below)
    wndclass[2] = 0;  // cbClsExtra
    wndclass[3] = 0;  // cbWndExtra
    wndclass[4] = 0;  // hInstance
    wndclass[5] = 0;  // hIcon
    wndclass[6] = 0;  // hCursor (set below)
    wndclass[7] = 0;  // hbrBackground
    wndclass[8] = 0;  // lpszMenuName
    wndclass[9] = 0;  // lpszClassName

    GetStockObject(4);  // NULL_BRUSH
    void* hCursor = LoadCursorA(0, (const char*)0x7F00);  // IDC_ARROW
    wndclass[1] = (uint32_t)WndProc;  // lpfnWndProc
    DAT_004924fc = 1;
    DAT_00492500 = 0;
    RegisterClassA(wndclass);

    if (DAT_00491d65 == 0) {
        // Windowed mode
        DAT_00491c70 = CreateWindowExA(
            0, "BASE", (const char*)&DAT_0046f66c,
            0xCF0000,  // WS_VISIBLE|WS_CAPTION|WS_SYSMENU|WS_THICKFRAME|WS_MINIMIZEBOX|WS_MAXIMIZEBOX
            0, 0, 0x280, 0x1E0,  // 640x480
            0, 0, hInstance, 0);
    } else {
        // Fullscreen mode
        int cx = GetSystemMetrics(7);  // SM_CXFULLSCREEN
        int cy = GetSystemMetrics(8);  // SM_CYFULLSCREEN
        int cyMenu = GetSystemMetrics(4);  // SM_CYMENU
        DAT_00491c70 = CreateWindowExA(
            0, "BASE", (const char*)&DAT_0046f66c,
            0x100A0000,  // WS_POPUP|WS_VISIBLE|WS_CLIPSIBLINGS|WS_CLIPCHILDREN
            (int)0x80000000, (int)0x80000000,
            cx * 2 + 0x280, cyMenu + 0x1E0 + cy * 2,
            0, 0, hInstance, 0);
    }

    g_pWnd = DAT_00491c70;
    if (DAT_00491c70 == 0) {
        return 1;
    }

    // Minimize then restore to force taskbar update
    SendMessageA(DAT_00491c70, 0x112, 0xF020, 0);  // WM_SYSCOMMAND, SC_MINIMIZE
    Sleep(0x10);
    SendMessageA(g_pWnd, 0x112, 0xF120, 0);  // WM_SYSCOMMAND, SC_RESTORE

    return 0;
}

// ============================================================================
// 0x00439FF0 - Instance Check (Mutex + LNK Resolution)
// Creates a named mutex to prevent multiple instances. Checks if launched
// via a .lnk shortcut (for replay drag-drop support). Uses security cookie.
//
// Ghidra decompilation:
//   CreateMutexA(NULL, TRUE, "Touhou 10 App")
//   if (GetLastError() == ERROR_ALREADY_EXISTS):
//     FUN_0044b8e0("already running message")
//     return -1
//   GetModuleFileNameA(NULL, path, 0x105)
//   GetConsoleTitleA(title, 0x105)
//   GetStartupInfoA(&si)
//   if (si.lpTitle == NULL):
//     DAT_00491ff4 |= 0x40
//   else:
//     Check if .lnk extension, resolve shortcut, compare paths
//     Set DAT_00492518 = 1 if launched from different path (replay)
//     DAT_00491ff4 &= ~0x40
//   return (mutex != NULL) - 1  // 0 if success, -1 if no mutex
// ============================================================================
int InstanceCheck(void) {
    DAT_00497ba8 = CreateMutexA(0, 1, "Touhou 10 App");
    uint32_t err = GetLastError();
    if (err == 0xB7) {  // ERROR_ALREADY_EXISTS
        FUN_0044b8e0("already running");
        return -1;
    }

    // STARTUPINFOA (0x44 bytes)
    char startupInfo[0x44];
    char modulePath[0x105];
    char consoleTitle[0x105];

    // Zero out STARTUPINFOA
    uint32_t* p = (uint32_t*)startupInfo;
    for (int i = 0x11; i != 0; i--) {
        *p++ = 0;
    }
    *(uint32_t*)startupInfo = 0x44;  // cb = sizeof(STARTUPINFOA)

    GetModuleFileNameA(0, modulePath, 0x105);
    GetConsoleTitleA(consoleTitle, 0x105);
    GetStartupInfoA(startupInfo);

    char* lpTitle = *(char**)(startupInfo + 0x3C);  // STARTUPINFOA.lpTitle at offset 60

    if (lpTitle == 0) {
        DAT_00491ff4 |= 0x40;
    } else {
        char* dot = 0;
        // Check for .lnk extension
        // ... (complex shortcut resolution logic)
        // If .lnk: resolve recursively via FUN_0043a290
        // If not .lnk: copy title to consoleTitle
        // Compare modulePath vs consoleTitle
        // If different: DAT_00492518 = 1 (replay launched)
        DAT_00491ff4 &= 0xFFFFFFBF;
    }

    return (int)(DAT_00497ba8 != 0) - 1;
}
