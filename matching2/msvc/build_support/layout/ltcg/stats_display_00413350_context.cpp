#include "../../../src/game/fps/fps_create.cpp"
#pragma code_seg(".text$02context")
extern "C" FPS* __cdecl FPSCompilerContext() { return FPS_Create(); }
#pragma code_seg()
