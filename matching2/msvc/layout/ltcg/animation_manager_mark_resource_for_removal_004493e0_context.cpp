// Compiler context only; never selected as recovered game code.
#include "../../src/render/animation_manager_mark_resource_for_removal_004493e0.cpp"

#pragma code_seg(".text$30context")
int __stdcall AnimationManagerHelperCompilerContext(
    AnimationManager** managers, void** resources, int count) {
    int total = 0;
    while (count--) {
        (*managers++)->MarkResourceForRemoval(*resources++);
        total += count;
    }
    return total;
}
#pragma code_seg()
