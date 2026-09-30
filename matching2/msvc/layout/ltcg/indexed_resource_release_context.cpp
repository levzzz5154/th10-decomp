// Synthetic compiler context, not selected game code.
#include "../../src/render/animation_manager_clear_indexed_resources_00447f70.cpp"
#pragma code_seg(".text$03context")
extern "C" int __stdcall IndexedResourceContext(AnimationManagerIndexed_00447f70* manager, int count) {
    for (int i = 0; i < count; ++i) manager->Clear(i);
    return 0;
}
#pragma code_seg()
