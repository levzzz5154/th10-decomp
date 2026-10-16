// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_4177c0.cpp"

struct AnimationSlots4 {
    __declspec(noinline) void SetFlags();
};

struct AnimationObject17;
struct AnimationManager16 {
    __declspec(noinline) AnimationObject17* FindChildByScriptIndex(int);
};

#pragma code_seg(".text$07context")
int __stdcall SmallPrivateAbiBCompilerContext(
        AnimationSlots3** first_items,
        AnimationSlots4** second_items,
        AnimationManager16** managers,
        int count) {
    for (int i = 0; i < count; ++i)
        first_items[i]->SetFlags();
    for (int i = 0; i < count; ++i)
        second_items[i]->SetFlags();

    AnimationObject17* result = 0;
    for (int i = 0; i < count; ++i)
        result = managers[i]->FindChildByScriptIndex(i);
    return result != 0;
}
#pragma code_seg()
