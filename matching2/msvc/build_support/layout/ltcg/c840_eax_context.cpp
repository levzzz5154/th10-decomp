// Synthetic compiler context for the private ECX/EAX byte lookup at 0x0042C840.
#include "../../../src/unreferenced/unassigned_0042c840.cpp"

#pragma code_seg(".text$03context")
extern "C" __declspec(noinline) int __stdcall C840EaxContext(
        ByteTable_0042c840** items, int count) {
    int total = 0;
    int index = 0;
    while (count-- > 0)
        total += (*items++)->Read(index++);
    return total;
}
#pragma code_seg()
