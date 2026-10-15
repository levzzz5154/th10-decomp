#include "../../src/game/background/background_construct.cpp"
void* __cdecl operator new(unsigned int size);
void __cdecl operator delete(void* block);
#pragma code_seg(".text$02context")
extern "C" BackGround* __stdcall GameStateConstructorContext_00402160() { return new BackGround; }
#pragma code_seg()
