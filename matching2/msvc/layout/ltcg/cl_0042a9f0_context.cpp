// Compiler context only; never selected as recovered game code.
#include "../../src/unidentified/unassigned_0042a9f0.cpp"

// The real defaults routine (0x00418C40) is an ABI anchor: its unused first
// parameter lets the pass drop ECX at the call.
#pragma code_seg(".text$00h_config")
#include "../../src/game/game_config_defaults.cpp"
#pragma code_seg()

#pragma code_seg(".text$03context")
int __stdcall ConfigHolderContext_0042a9f0(GameConfigHolder_0042a9f0* holders, int count) {
    int result = 0;
    for (int i = 0; i < count; ++i)
        result += (int)holders[i].Construct();
    return result;
}
#pragma code_seg()
