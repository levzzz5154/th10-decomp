#include "../../../src/core/sprtanim/animation_object_load_script_preserving_state_0043e7e0.cpp"
#pragma code_seg(".text$03context")
int __stdcall LoadScriptPreservingStateCompilerContext(AnimationObject_0043e7e0** objects, int count, AnimationResource_0043e7e0* resource) {
    for (int slot = 0; slot < count; ++slot)
        LoadScriptPreservingState(resource, objects[slot], slot);
    return count;
}
#pragma code_seg()
