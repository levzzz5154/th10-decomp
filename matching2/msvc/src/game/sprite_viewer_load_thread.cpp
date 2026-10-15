// 0x0040A340: the sprite viewer's loader-thread entry; recreates the game
// managers for the selected script file (0x0040A350).
#include "th10/game/startup_managers_0040a350.hpp"

// Complete original startup callback; loads the state for the private member ABI.
#pragma code_seg(".text$00ab")
extern "C" __declspec(noinline) int __cdecl SpriteViewer_LoadThread() {
    data_004776f8->InitializeManagers();
    return 0;
}
#pragma code_seg()
