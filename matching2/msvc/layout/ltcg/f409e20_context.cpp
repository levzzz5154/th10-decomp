// Compiler context only; never selected as recovered game code.
#include "../../src/game/score_retire_callbacks_00409e20.cpp"

#pragma code_seg(".text$03context")
int __stdcall f409e20CompilerContext(CallbackPair** pairs, int count) {
    for (int index = 0; index < count; ++index) {
        pairs[index]->RetireCallbacks();
        pairs[index]->RetireCallbacks();
    }
    return 0;
}
#pragma code_seg()
