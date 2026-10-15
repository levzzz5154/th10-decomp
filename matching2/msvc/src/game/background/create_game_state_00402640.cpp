// 0x00402640: allocate a game state and initialise it from a stage script;
// a state that fails to load is destroyed again.
#include "th10/game/game_state.hpp"

void* __cdecl operator new(unsigned int size);
void __cdecl operator delete(void* block);

#pragma code_seg(".text$02factory")
__declspec(noinline) GameState_00402230* __stdcall CreateGameState_00402640(const char* name, int state_id) {
    GameState_00402230* state = new GameState_00402230;
    if (InitializeGameState_00402230(state, name, state_id) != 0) {
        delete state;
        return 0;
    }
    return state;
}
#pragma code_seg()
