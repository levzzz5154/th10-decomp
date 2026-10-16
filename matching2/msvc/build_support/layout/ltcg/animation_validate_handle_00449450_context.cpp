// Compiler context only; never selected as recovered game code.
#include "../../../src/core/sprtlib/animation_manager_validate_handle.cpp"
#include "animation_validate_handle_00449450_find_anchor.cpp"

#pragma code_seg(".text$05context")
int __stdcall AnimationValidateHandleCompilerContext(
        AnimationManager15* manager, AnimationHandle10* handles, int count) {
    int validated = count;
    while (count--)
        manager->ValidateHandle(handles++);
    return validated;
}
#pragma code_seg()
