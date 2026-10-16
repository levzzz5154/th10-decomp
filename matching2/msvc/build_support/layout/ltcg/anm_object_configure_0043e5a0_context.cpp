// Compiler context only; never selected as recovered game code.
#include "../../../src/core/sprtanim/animation_object_configure_from_resource.cpp"

#pragma code_seg(".text$03context")
int __stdcall AnimationObjectConfigureCompilerContext(
    AnimationObject3** objects, int count,
    Resource2* resource) {
    int result = 0;
    for (int slot = 0; slot < count; ++slot)
        result += resource->ConfigureObject(objects[slot], slot);
    return result;
}
#pragma code_seg()
