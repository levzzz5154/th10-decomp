// Compiler context only: real bodies of the callees, so the pass derives
// their register arguments.
#include "th10/game/life_stock_add.hpp"

#pragma code_seg(".text$00413790_fn")
void AnimationManager4::SetActiveCount(int count) {
    int index = 0;
    for (; index < count; ++index)
        records_4cdc[index].flags_0000 |= 2;
    if (index >= 9)
        return;
    for (; index < 9; ++index)
        records_4cdc[index].flags_0000 &= ~2u;
}
#pragma code_seg(".text$00448d00_fn")
struct AnimationObject5 {
    unsigned char reserved_000[0x20];
    int render_bucket_020;
    unsigned char reserved_024[0x35C - 0x24];
    unsigned int flags_035c;
};
struct AnimationBank {
    void* __declspec(noinline) InitializeObject(void* object, int index);
};
extern "C" void* __cdecl asm_FUN_00449950_00449950(void* manager);
extern "C" void** __cdecl asm_AnimationManager_RegisterPrimaryBack_004489d0(
    void* manager, void** out, void* entity);
void** __stdcall AnimationManager_CreatePrimaryBack(
        void* resource, void** out, int index, int render_bucket) {
    AnimationObject5* object =
        (AnimationObject5*)asm_FUN_00449950_00449950(g_sprt_ctrl);
    unsigned int flags = object->flags_035c;
    object->render_bucket_020 = render_bucket;
    object->flags_035c = flags | 0x40000000u;
    ((AnimationBank*)resource)->InitializeObject(object, index);
    asm_AnimationManager_RegisterPrimaryBack_004489d0(g_sprt_ctrl, out, object);
    return out;
}
#pragma code_seg(".text$004491c0_fn")
AnimationNode6* AnimationLists4::Find(AnimationHandle6 handle) {
    if (!handle.value)
        return 0;
    for (AnimationNode6* node = primary; node != 0; node = node->next)
        if (*reinterpret_cast<unsigned int*>(node->object) == handle.value)
            return node->object;
    for (AnimationNode6* node = secondary; node != 0; node = node->next)
        if (*reinterpret_cast<unsigned int*>(node->object) == handle.value)
            return node->object;
    return 0;
}
#pragma code_seg(".text$004492a0_fn")
AnimationNode6* AnimationLists4::MarkForRemoval(AnimationHandle6 handle) {
    AnimationNode6* node = Find(handle);
    if (node) {
        node->flags |= 0x04000000u;
        if (!node->children_flagged)
            for (node = node->children; node != 0; node = node->next)
                node->object->flags |= 0x04000000u;
    }
    return node;
}
#pragma code_seg()
