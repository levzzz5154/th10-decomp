#include "th10/platform/windows_types.hpp"

typedef void* HMIDIOUT;
typedef unsigned int MMRESULT;
struct MIDIHDR { char* lpData; };
typedef MIDIHDR* LPMIDIHDR;

enum {
    WM_ACTIVATEAPP = 0x001C,
    WM_CLOSE = 0x0010,
    WM_ERASEBKGND = 0x0014,
    WM_SETCURSOR = 0x0020,
    WM_LBUTTONDOWN = 0x0201
};

#include "asm_symbols.hpp"

extern "C" void __cdecl entry_free_00452422(void* memory);

struct MidiManager_004390e0 {
    unsigned char reserved_000[0x14];
    MIDIHDR* pending_headers[0x20];
    unsigned char reserved_094[0xA8];
    HMIDIOUT midi_output;
};

typedef LRESULT (__stdcall *DefWindowProcA_004390e0)(HWND, UINT, WPARAM, LPARAM);
typedef BOOL (__stdcall *SetForegroundWindow_004390e0)(HWND);
typedef int (__stdcall *ShowCursor_004390e0)(BOOL);
typedef HCURSOR (__stdcall *SetCursor_004390e0)(HCURSOR);
typedef HCURSOR (__stdcall *LoadCursorA_004390e0)(HINSTANCE, LPCSTR);
typedef MMRESULT (__stdcall *MidiOutUnprepareHeader_004390e0)(
    HMIDIOUT, LPMIDIHDR, UINT);

template <typename Function>
static __forceinline Function WindowProc_Iat_004390e0(unsigned char& slot) {
    return reinterpret_cast<Function>(*reinterpret_cast<void**>(&slot));
}

// The callback body is a regular Win32 WNDPROC.  Ghidra's automatic
// __thiscall guess for this address comes from its interpretation of the
// adjacent private MIDI callback, not from the callback's entry arguments.
extern "C" LRESULT CALLBACK WindowProcedure_004390e0(
    HWND window, UINT message, WPARAM wparam, LPARAM lparam) {
    if (message > 0x20) {
        if (message == WM_LBUTTONDOWN) {
            WindowProc_Iat_004390e0<SetForegroundWindow_004390e0>(
                data_004661f0)(window);
        } else if (message == 0x3C9) { // MM_MOM_DONE
            MidiManager_004390e0* manager =
                *reinterpret_cast<MidiManager_004390e0**>(&data_00491fe8);
            if (manager != 0) {
                MIDIHDR* header = reinterpret_cast<MIDIHDR*>(lparam);
                for (unsigned int index = 0; index != 0x20; ++index) {
                    if (manager->pending_headers[index] == header) {
                        manager->pending_headers[index] = 0;
                        WindowProc_Iat_004390e0<MidiOutUnprepareHeader_004390e0>(
                            data_00466284)(manager->midi_output, header, 0x40);
                        if (header->lpData != 0) {
                            entry_free_00452422(header->lpData);
                            header->lpData = 0;
                        }
                        entry_free_00452422(header);
                        break;
                    }
                }
            }
        }
        return WindowProc_Iat_004390e0<DefWindowProcA_004390e0>(
            data_00466248)(window, message, wparam, lparam);
    }

    if (message == WM_SETCURSOR) {
        if (data_00491d65 == 0 &&
            *reinterpret_cast<unsigned int*>(&data_00492500) == 0) {
            WindowProc_Iat_004390e0<ShowCursor_004390e0>(data_00466230)(FALSE);
            WindowProc_Iat_004390e0<SetCursor_004390e0>(data_00466224)(0);
            return 1;
        }

        HCURSOR arrow = WindowProc_Iat_004390e0<LoadCursorA_004390e0>(
            data_00466260)(0, reinterpret_cast<LPCSTR>(0x7F00));
        WindowProc_Iat_004390e0<SetCursor_004390e0>(data_00466224)(arrow);
        WindowProc_Iat_004390e0<ShowCursor_004390e0>(data_00466230)(TRUE);
        return 1;
    }

    if (message == WM_CLOSE) {
        *reinterpret_cast<unsigned int*>(&data_00491ff4) |= 0x80;
        return 1;
    }
    if (message == WM_ERASEBKGND) {
        return 1;
    }
    if (message == WM_ACTIVATEAPP) {
        *reinterpret_cast<unsigned int*>(&data_004924fc) = wparam;
        *reinterpret_cast<unsigned int*>(&data_00492500) = (wparam == 0);
    }

    return WindowProc_Iat_004390e0<DefWindowProcA_004390e0>(
        data_00466248)(window, message, wparam, lparam);
}
