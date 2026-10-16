// 0x004658F0: dynamic initializer of the render state at 0x00491C28; registers
// its destructor (0x004659F0) with atexit.

#include "th10/game/large_initialization_state.hpp"
extern "C" void __cdecl Register2(void* entry);
extern "C" LargeInitializationState g_application;
#pragma code_seg(".text$03start")
__declspec(noinline) void StaticInit_RenderState() {
    Init11(&g_application);
    Register2((void*)0x4659F0);
}
#pragma code_seg()
