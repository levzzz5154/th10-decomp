// Compiler context only; never selected as recovered game code.
#include "../../src/game/replay/platform_deleting_destructor_with_release_004297b0.cpp"

#pragma code_seg(".text$03context")
int __stdcall PlatformResourceDestroyCompilerContext(PlatformResource** resources, int count) {
    PlatformResource* first = *resources;
    for (int index = 0; index < count; ++index) {
        PlatformResource_Destroy(first);
        PlatformResource_Destroy(resources[index]);
    }
    return 0;
}
#pragma code_seg()
