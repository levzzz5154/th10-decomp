// 0x004658F0: dynamic initializer of the render state at 0x00491C28; registers
// its destructor (0x004659F0) with atexit.

#include "th10/game/large_initialization_state_00421f00.hpp"
extern "C" void __cdecl Register_00452e0a(void* entry);
extern "C" LargeInitializationState_00421f00 g_application;
#pragma code_seg(".text$03start")
__declspec(noinline) void StaticInit_RenderState() {
    Init_00421f00(&g_application);
    Register_00452e0a((void*)0x4659F0);
}
#pragma code_seg()
