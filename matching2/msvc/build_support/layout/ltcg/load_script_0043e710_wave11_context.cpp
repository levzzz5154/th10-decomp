// Compiler context only; never selected as recovered game code.
#include "../../../src/core/sprtanim/animation_object_load_script_0043e710.cpp"
#pragma code_seg(".text$03context")
int __stdcall LoadScriptCompilerContext(AnimationObjectFile** objects,
                                        int count,
                                        AnimationResourceFile* resource) {
    for (int slot = 0; slot < count; ++slot)
        LoadScript_0043e710(resource, objects[slot], slot);
    return count;
}
#pragma code_seg()
