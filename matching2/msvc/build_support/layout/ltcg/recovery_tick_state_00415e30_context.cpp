// Compiler context only; never selected as recovered game code.
// The array-walking caller is what makes the whole-program pass pick the
// observed retail convention: the state in ESI, plain RET.
#include "../../../src/unreferenced/unassigned_00415e30.cpp"

#pragma code_seg(".text$03context")
int __stdcall RecoveryTickStateCompilerContext_00415e30(RecoveryTickState** states,
                                                       int count) {
    int result = 0;
    for (int index = 0; index < count; ++index)
        result = TickRecoveryState(states[index]);
    return result;
}
#pragma code_seg()
