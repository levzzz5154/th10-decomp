// Compiler context and ABI anchors only; none of these bytes enter the image.
#include "../../../src/game/item/item_manager_draw_0041b8e0.cpp"

#include "../../../src/core/sprtanim/animation_object_configure_from_resource_0043e5a0.cpp"

// 0x004451C0 enters on (EAX entity, ECX manager). The recovered dispatcher
// lives in the render-batch cluster; this stand-in only fixes the parameter
// homes.
struct AnimationManager_0041b8e0 {
    virtual int Submit(AnimationObject_0043e5a0* entity);
};

#pragma code_seg(".text$03dispatch")
extern "C" __declspec(noinline) int __cdecl asm_FUN_004451c0_004451c0(
        AnimationObject_0043e5a0* entity, AnimationManager_0041b8e0* manager) {
    if (!(entity->record_index & 1))
        return -1;
    return manager->Submit(entity);
}
#pragma code_seg()

#pragma code_seg(".text$05context")
int __stdcall ItemManagerDrawCompilerContext_0041b8e0(ItemManager_0041b8e0** managers, int count) {
    int total = 0;
    while (count--)
        total += ItemManager_OnDraw_0041ba30(*managers++);
    return total;
}
#pragma code_seg()
