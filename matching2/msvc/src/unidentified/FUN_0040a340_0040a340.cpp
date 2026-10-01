#include "th10/game/startup_managers_0040a350.hpp"

// Complete original startup callback; loads the state for the private member ABI.
#pragma code_seg(".text$00ab")
extern "C" __declspec(noinline) int __cdecl StartupManagers_0040a340() {
    data_004776f8->InitializeManagers();
    return 0;
}
#pragma code_seg()
