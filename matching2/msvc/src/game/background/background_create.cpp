// 0x00402640: allocate a game state and initialise it from a stage script;
// a state that fails to load is destroyed again.
#include "th10/game/background.hpp"

void* __cdecl operator new(unsigned int size);
void __cdecl operator delete(void* block);

#pragma code_seg(".text$02factory")
__declspec(noinline) BackGround* __stdcall BackGround_Create(const char* name, int state_id) {
    BackGround* state = new BackGround;
    if (BackGround_Initialize(state, name, state_id) != 0) {
        delete state;
        return 0;
    }
    return state;
}
#pragma code_seg()
