// Compiler context only.
#include "../../src/render/animation_find_embedded_child_00449770.cpp"
#pragma code_seg(".text$03context")
extern "C" __declspec(noinline) int __stdcall EmbeddedChildContext(EmbeddedAnimationChildren** items, int index, int count) {
    int result = 0;
    while (count--) result += (*items++)->FindChildId(index).value;
    return result;
}
#pragma code_seg()
