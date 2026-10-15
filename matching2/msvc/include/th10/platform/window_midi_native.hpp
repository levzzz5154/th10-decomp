#pragma once
#include "th10/platform/windows_types.hpp"
#include "th10/platform/midi_sequencer.hpp"
struct midihdr_tag { char* lpData; unsigned char remainder[0x3c]; };
extern "C" __declspec(noinline) int CompleteMidiHeader_0043aeb0(MidiSequencer*, midihdr_tag*);
typedef LRESULT (__stdcall *DefWindowProcA_type)(HWND,UINT,WPARAM,LPARAM);
extern "C" DefWindowProcA_type IatDefWindowProcA;
typedef BOOL (__stdcall *SetForegroundWindow_type)(HWND);
extern "C" SetForegroundWindow_type IatSetForegroundWindow;
typedef int (__stdcall *ShowCursor_type)(BOOL);
extern "C" ShowCursor_type IatShowCursor;
typedef HCURSOR (__stdcall *SetCursor_type)(HCURSOR);
extern "C" SetCursor_type IatSetCursor;
typedef HCURSOR (__stdcall *WindowLoadCursorA_type)(HINSTANCE,LPCSTR);
extern "C" WindowLoadCursorA_type IatWindowLoadCursorA;
typedef unsigned int (__stdcall *midiOutUnprepareHeader_type)(void*,midihdr_tag*,UINT);
extern "C" midiOutUnprepareHeader_type IatmidiOutUnprepareHeader;
extern "C" void __cdecl crt_free(void*);
extern "C" { extern MidiSequencer* window_midi_manager; extern unsigned int window_flags; extern unsigned char window_cursor_enabled; extern unsigned int window_active; extern int window_inactive; }

extern "C" LRESULT __stdcall WindowProcedure_004390e0(HWND, UINT, WPARAM, LPARAM);
