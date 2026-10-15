// Compiler context only; never selected as recovered game code.
#include "../../src/unreferenced/unassigned_004177c0.cpp"

struct AnimationSlots_004177e0 {
    __declspec(noinline) void SetFlags();
};

struct AnimationObject_004497b0;
struct AnimationManager_004497b0 {
    __declspec(noinline) AnimationObject_004497b0* FindChildByScriptIndex(int);
};

#pragma code_seg(".text$07context")
int __stdcall SmallPrivateAbiBCompilerContext(
        AnimationSlots_004177c0** first_items,
        AnimationSlots_004177e0** second_items,
        AnimationManager_004497b0** managers,
        int count) {
    for (int i = 0; i < count; ++i)
        first_items[i]->SetFlags();
    for (int i = 0; i < count; ++i)
        second_items[i]->SetFlags();

    AnimationObject_004497b0* result = 0;
    for (int i = 0; i < count; ++i)
        result = managers[i]->FindChildByScriptIndex(i);
    return result != 0;
}
#pragma code_seg()
