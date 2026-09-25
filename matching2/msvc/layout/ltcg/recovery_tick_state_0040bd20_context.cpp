// Compiler context only; never selected as recovered game code.
// The array-walking caller is what makes the whole-program pass pick the
// observed retail convention: the state in ESI, plain RET.
#include "../../src/game/recovery_tick_state_0040bd20.cpp"

#pragma code_seg(".text$03context")
int __stdcall RecoveryTickStateCompilerContext_0040bd20(RecoveryTickState_0040bd20** states,
                                                       int count) {
    int result = 0;
    for (int index = 0; index < count; ++index)
        result = TickRecoveryState_0040bd20(states[index]);
    return result;
}
#pragma code_seg()
