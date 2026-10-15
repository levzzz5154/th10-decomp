#ifndef TH10_PLATFORM_WINDOW_CREATE_00439730_HPP
#define TH10_PLATFORM_WINDOW_CREATE_00439730_HPP
#include "th10/platform/windows_types.hpp"

// The window state at 0x004924F0.
struct GameWindow {
    HWND window;              // 0x004924F0
    int reserved_04[2];
    int input_enabled;        // 0x004924FC
    int reserved_10;          // 0x00492500
};

extern "C" {
extern GameWindow g_main_window;
extern HWND g_supervisor_window;              // the supervisor's copy of the window
extern unsigned char g_windowed;     // the configuration's windowed flag
extern const char str_window_title[];      // the window title (Shift-JIS), "... Mountain of Faith. ver 1.00a"
LRESULT __stdcall WindowProcedure(HWND, UINT, WPARAM, LPARAM);
}

// 0x00439730: register the window class and create the game window.
// Returns 1 when the window could not be created.
int __fastcall CreateGameWindow_00439730(HINSTANCE instance);

#endif
