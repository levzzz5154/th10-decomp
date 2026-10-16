#include "../../../src/core/sprtanim/animation_object_load_script_preserving_state.cpp"
#pragma code_seg(".text$03context")
int __stdcall LoadScriptPreservingStateCompilerContext(AnimationObject4** objects, int count, AnimationResource4* resource) {
    for (int slot = 0; slot < count; ++slot)
        LoadScriptPreservingState(resource, objects[slot], slot);
    return count;
}
#pragma code_seg()
