// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_00413070.cpp"
#pragma code_seg(".text$03context")
extern "C" __declspec(noinline) void __stdcall AdvanceContext_00413070(
        FrameTimer** items, int* frames, int count) {
    for (int index = 0; index < count; ++index) items[index]->AdvanceFrames(frames[index]);
}
#pragma code_seg()
