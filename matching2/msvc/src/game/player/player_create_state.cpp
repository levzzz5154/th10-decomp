#include "th10/game/large_player_native.hpp"
void* __cdecl operator new(unsigned int);
void __cdecl operator delete(void*);
extern "C" void __stdcall LargePlayerCleanup(PlayerResetBlock*);
#pragma code_seg(".text$a09body")
__declspec(noinline) PlayerResetBlock* __cdecl Create6() {
    PlayerResetBlock* state=new PlayerResetBlock;
    if (state->Initialize()!=0) {
        if (state) { LargePlayerCleanup(state); ::operator delete(state); }
        return 0;
    }
    return state;
}
#pragma code_seg()
