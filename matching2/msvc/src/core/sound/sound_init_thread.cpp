#include "../../../build_support/include/asm_symbols.hpp"

// 0x0043CD30 is the sound-device/window initialisation routine that follows
// this entry point. It takes its target object in ECX and the window handle on
// the stack. MSVC passes a floating-point argument of a __fastcall callee on the
// stack, so this pointer type is exactly the ordering the retail call site uses
// (object in ECX, handle pushed by the caller, callee pops it).
typedef int (__fastcall* SoundDeviceInitFn)(void* self, float hwnd);

extern "C" __declspec(dllimport) void __stdcall Sleep(unsigned long milliseconds);

// The global runtime object the startup path initialises and polls.
extern "C" unsigned char g_sound_manager;

// 0x0043CCF0: Sound_InitThread - bring the sound device up for the new main window,
// wait until the worker thread has finished, then publish that it happened.
void __stdcall Sound_InitThread() {
    // The handle is bit-cast to float only so that it selects the stack-passing
    // form of the call above; no conversion happens.
    ((SoundDeviceInitFn)asm_FUN_0043cd30_0043cd30)(&g_sound_manager,
                                                   *(float*)&data_004977b8);
    while (*(int*)&data_004977b4 == 0)
        Sleep(1);
    *(int*)&data_004977bc = 1;
}
