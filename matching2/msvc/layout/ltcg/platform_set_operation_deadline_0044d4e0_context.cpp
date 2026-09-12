// Compiler context only; never selected as recovered game code.
#include "../../src/game/platform_set_operation_deadline_0044d4e0.cpp"

#pragma code_seg(".text$03context")
int __stdcall PlatformSetOperationDeadline0044D4E0CompilerContext(
        PlatformInterfaceState_0044D4E0* state, int deadline) {
    return state->SetOperationDeadline(deadline);
}
#pragma code_seg()
