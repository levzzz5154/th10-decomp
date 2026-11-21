// 0x004390E0: WindowProcedure
#include "th10/platform/window_midi_native.hpp"

enum WindowProcMessage {
    WIN_WM_CLOSE = 0x0010,
    WIN_WM_ERASEBKGND = 0x0014,
    WIN_WM_ACTIVATEAPP = 0x001C,
    WIN_WM_SETCURSOR = 0x0020,
    WIN_WM_LBUTTONDOWN = 0x0201,
    WIN_MM_MOM_DONE = 0x03C9,
    WIN_IDC_ARROW = 0x7F00,
    WIN_FLAG_CLOSING = 0x80
};

// Win32 WNDCLASS callback: four stack arguments, public stdcall ABI.
#pragma code_seg(".text$10window")
extern "C" __declspec(noinline) LRESULT __stdcall WindowProcedure(HWND window, UINT message, WPARAM wparam, LPARAM lparam) {
    switch (message) {
    case WIN_WM_CLOSE: window_flags |= WIN_FLAG_CLOSING; // fall through to the shared success return
    case WIN_WM_ERASEBKGND: return 1;
    case WIN_WM_SETCURSOR:
        if (window_cursor_enabled == 0 && window_inactive == 0) {
            IatShowCursor(0); IatSetCursor(0); return 1;
        }
        IatSetCursor(IatWindowLoadCursorA(0, reinterpret_cast<LPCSTR>(WIN_IDC_ARROW)));
        IatShowCursor(1); return 1;
    case WIN_WM_ACTIVATEAPP:
        window_active = wparam;
        window_inactive = wparam == 0;
        break;
    case WIN_WM_LBUTTONDOWN: IatSetForegroundWindow(window); break;
    case WIN_MM_MOM_DONE:
        if (window_midi_manager) {
            CompleteMidiHeader2(window_midi_manager,reinterpret_cast<midihdr_tag*>(lparam));
            break;
        }
        break;
    }
    return IatDefWindowProcA(window,message,wparam,lparam);
}
