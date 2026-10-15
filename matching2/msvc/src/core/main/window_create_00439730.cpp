// 0x00439730..0x00439885: register the "BASE" window class and create the
// game window.
//
// Without the windowed flag the window is a plain 640x480 overlapped window
// at the origin (the full-screen device takes it over). In windowed mode it
// is a fixed-size captioned window whose client area is 640x480. The handle
// is published to the window state and to the supervisor; the new window is
// then minimised and restored, which brings it to the foreground.
//
// The instance arrives in EBX (the compiler's own convention for the single
// call in the entry point).
#include "th10/platform/window_create_00439730.hpp"
#include <string.h>

#pragma code_seg(".text$00439730_fn")
__declspec(noinline) int __fastcall CreateGameWindow_00439730(HINSTANCE instance) {
    WNDCLASSA window_class;
    memset(&window_class, 0, sizeof(window_class));
    window_class.hbrBackground = (HBRUSH)GetStockObject(4);            // BLACK_BRUSH
    window_class.hCursor = LoadCursorA(0, (LPCSTR)0x7F00);             // IDC_ARROW
    window_class.hInstance = instance;
    window_class.lpfnWndProc = WindowProcedure;
    g_main_window.input_enabled = 1;
    g_main_window.reserved_10 = 0;
    window_class.lpszClassName = "BASE";
    RegisterClassA(&window_class);

    HWND window;
    if (g_windowed == 0) {
        // WS_OVERLAPPEDWINDOW
        window = CreateWindowExA(0, "BASE", str_window_title, 0x00CF0000, 0, 0, 640, 480, 0, 0, instance, 0);
    } else {
        int width = GetSystemMetrics(7) * 2 + 640;                           // SM_CXFIXEDFRAME
        int height = GetSystemMetrics(8) * 2 + GetSystemMetrics(4) + 480;    // SM_CYFIXEDFRAME, SM_CYCAPTION
        // WS_VISIBLE | WS_SYSMENU | WS_MINIMIZEBOX at CW_USEDEFAULT
        window = CreateWindowExA(0, "BASE", str_window_title, 0x100A0000, 0x80000000, 0x80000000, width,
                                 height, 0, 0, instance, 0);
    }
    g_main_window.window = window;
    g_supervisor_window = window;
    if (window == 0)
        return 1;
    SendMessageA(window, 0x112, 0xF020, 0);                    // WM_SYSCOMMAND, SC_MINIMIZE
    Sleep(16);
    SendMessageA(g_main_window.window, 0x112, 0xF120, 0);      // WM_SYSCOMMAND, SC_RESTORE
    return 0;
}
#pragma code_seg()
