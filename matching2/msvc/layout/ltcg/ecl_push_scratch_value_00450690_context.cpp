// Compiler context only; never selected as recovered game code.
#include "../../src/script/ecl_push_scratch_value_00450690.cpp"

#pragma code_seg(".text$04context")
extern "C" __declspec(noinline) int __stdcall EclPushScratchValueContext(
        EclFrame_00450690** items, int size, int count) {
    int last = 0;
    while (count--) {
        EclFrame_00450690* frame = *items++;
        last = frame->Push(size);
        frame->PopScratchValue();
    }
    return last;
}
#pragma code_seg()
