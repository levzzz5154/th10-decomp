// Compiler context only: real bodies of the callees, so the pass derives
// their register arguments.
#include "th10/game/life_stock_add_004188a0.hpp"

#pragma code_seg(".text$00413790_fn")
void AnimationManager_00413790::SetActiveCount(int count) {
    int index = 0;
    for (; index < count; ++index)
        records_4cdc[index].flags_0000 |= 2;
    if (index >= 9)
        return;
    for (; index < 9; ++index)
        records_4cdc[index].flags_0000 &= ~2u;
}
#pragma code_seg(".text$00448d00_fn")
struct AnimationObject_00448d00 {
    unsigned char reserved_000[0x20];
    int render_bucket_020;
    unsigned char reserved_024[0x35C - 0x24];
    unsigned int flags_035c;
};
struct AnimationResource_00449870 {
    void* __declspec(noinline) InitializeObject(void* object, int index);
};
extern "C" void* __cdecl asm_FUN_00449950_00449950(void* manager);
extern "C" void** __cdecl asm_AnimationManager_RegisterPrimaryBack_004489d0(
    void* manager, void** out, void* entity);
void** __stdcall AnimationManager_CreatePrimaryBack_00448d00(
        void* resource, void** out, int index, int render_bucket) {
    AnimationObject_00448d00* object =
        (AnimationObject_00448d00*)asm_FUN_00449950_00449950(g_sprt_ctrl);
    unsigned int flags = object->flags_035c;
    object->render_bucket_020 = render_bucket;
    object->flags_035c = flags | 0x40000000u;
    ((AnimationResource_00449870*)resource)->InitializeObject(object, index);
    asm_AnimationManager_RegisterPrimaryBack_004489d0(g_sprt_ctrl, out, object);
    return out;
}
#pragma code_seg(".text$004491c0_fn")
AnimationNode_004188a0* AnimationLists_004188a0::Find(AnimationHandle_004188a0 handle) {
    if (!handle.value)
        return 0;
    for (AnimationNode_004188a0* node = primary; node != 0; node = node->next)
        if (*reinterpret_cast<unsigned int*>(node->object) == handle.value)
            return node->object;
    for (AnimationNode_004188a0* node = secondary; node != 0; node = node->next)
        if (*reinterpret_cast<unsigned int*>(node->object) == handle.value)
            return node->object;
    return 0;
}
#pragma code_seg(".text$004492a0_fn")
AnimationNode_004188a0* AnimationLists_004188a0::MarkForRemoval(AnimationHandle_004188a0 handle) {
    AnimationNode_004188a0* node = Find(handle);
    if (node) {
        node->flags |= 0x04000000u;
        if (!node->children_flagged)
            for (node = node->children; node != 0; node = node->next)
                node->object->flags |= 0x04000000u;
    }
    return node;
}
#pragma code_seg()
