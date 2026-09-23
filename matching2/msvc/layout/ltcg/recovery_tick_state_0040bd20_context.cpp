// Compiler context only; never selected as recovered game code.
// The callback route gives LTCG visibility of the public ECX receiver and
// both private calls through the emitter decision and tick bodies.
#include "../../src/game/recovery_tick_state_0040bd20.cpp"

#pragma code_seg(".text$04context")
int __stdcall RecoveryEmitterStateCompilerContext_0040bd20(
        RecoveryUpdateEmitterState_0040b9f0** states, int count) {
    int result = 0;
    for (int index = 0; index < count; ++index)
        result = states[index]->RunDecisionCallback();
    return result;
}
#pragma code_seg()
