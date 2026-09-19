// Compiler context only; never selected as recovered game code.
#include "../../src/render/animation_manager_validate_handle_00449450.cpp"

#pragma code_seg(".text$03context")
int __stdcall AnimationValidateHandleCompilerContext(
        AnimationManager_00449450* manager, AnimationHandle_00449450* handles, int count) {
    int validated = count;
    while (count--)
        manager->ValidateHandle(handles++);
    return validated;
}
#pragma code_seg()
