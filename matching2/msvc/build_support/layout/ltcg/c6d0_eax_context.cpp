// Synthetic compiler context for the private EAX receiver at 0x0040C6D0.
#include "../../../src/unreferenced/unassigned_0040c6d0.cpp"

#pragma code_seg(".text$03context")
extern "C" __declspec(noinline) int __stdcall C6D0EaxContext(
        ObjectAccessor_0040c6d0** items, int count) {
    while (count-- > 0)
        (*items++)->Subtract(1.0f);
    return count;
}
#pragma code_seg()
