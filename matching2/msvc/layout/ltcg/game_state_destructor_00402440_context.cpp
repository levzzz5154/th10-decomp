#include "../../src/game/background/background_destroy.cpp"
#pragma code_seg(".text$03context")
extern "C" void __stdcall GameStateDestructorContext_00402440(BackGround* state) { state->~BackGround(); }
#pragma code_seg()
