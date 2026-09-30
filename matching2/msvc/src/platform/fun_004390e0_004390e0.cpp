#include "th10/platform/window_midi_native.hpp"
// Win32 WNDCLASS callback: four stack arguments, public stdcall ABI.
#pragma code_seg(".text$10window")
extern "C" __declspec(noinline) LRESULT __stdcall WindowProcedure_004390e0(HWND window, UINT message, WPARAM wparam, LPARAM lparam) {
    switch (message) {
    case 0x10: window_flags |= 0x80; // fall through to the shared success return
    case 0x14: return 1;
    case 0x20:
        if (window_cursor_enabled == 0 && window_inactive == 0) {
            IatShowCursor(0); IatSetCursor(0); return 1;
        }
        IatSetCursor(IatWindowLoadCursorA(0, reinterpret_cast<LPCSTR>(0x7f00)));
        IatShowCursor(1); return 1;
    case 0x1c:
        window_active = wparam;
        window_inactive = wparam == 0;
        break;
    case 0x201: IatSetForegroundWindow(window); break;
    case 0x3c9:
        if (window_midi_manager) {
            CompleteMidiHeader_0043aeb0(window_midi_manager,reinterpret_cast<midihdr_tag*>(lparam));
            break;
        }
        break;
    }
    return IatDefWindowProcA(window,message,wparam,lparam);
}
