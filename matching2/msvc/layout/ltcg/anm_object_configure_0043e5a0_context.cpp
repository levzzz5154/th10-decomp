// Compiler context only; never selected as recovered game code.
#include "../../src/game/animation_object_configure_from_resource_0043e5a0.cpp"

#pragma code_seg(".text$03context")
int __stdcall AnimationObjectConfigureCompilerContext(
    AnimationObject_0043e5a0** objects, int count,
    Resource_0043e5a0* resource) {
    int result = 0;
    for (int slot = 0; slot < count; ++slot)
        result += resource->ConfigureObject(objects[slot], slot);
    return result;
}
#pragma code_seg()
