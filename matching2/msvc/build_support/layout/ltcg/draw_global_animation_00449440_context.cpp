// Compiler context and ABI anchor only; none of these bytes enter the image.
#include "../../../src/unreferenced/FUN_00449440_00449440.cpp"

// 0x004451C0 enters on (EAX entity, ECX manager), which no declaration names.
// The recovered dispatcher lives in the render-batch cluster, so this link
// carries a stand-in body placed at the retail address; only its parameter
// homes matter. Dispatching through the manager's vtable is what earns the
// manager ECX: a stand-in that only reads both objects gets them reversed.
struct RenderEntity_00449440 {
    unsigned int flags;
};

struct AnimationManager_00449440 {
    virtual int Submit(RenderEntity_00449440* entity);
};

#pragma code_seg(".text$01dispatch")
extern "C" __declspec(noinline) int __cdecl asm_FUN_004451c0_004451c0(
        RenderEntity_00449440* entity, AnimationManager_00449440* manager) {
    if (!(entity->flags & 1))
        return -1;
    return manager->Submit(entity);
}
#pragma code_seg()

#pragma code_seg(".text$05context")
int __stdcall DrawGlobalAnimationCompilerContext(RenderEntity_00449440** entities, int count) {
    int total = 0;
    while (count--)
        total += DrawGlobalAnimation_00449440(*entities++);
    return total;
}
#pragma code_seg()
