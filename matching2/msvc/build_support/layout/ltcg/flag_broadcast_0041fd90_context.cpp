#include "../../../src/unreferenced/flag_broadcast.cpp"
#pragma code_seg(".text$03context")
extern "C" int __stdcall FlagBroadcastCompilerContext(void** items, int count) {
    int total = 0;
    for (int index = 0; index < count; ++index)
        total += Update2(0, (Flagged4*)items[index]);
    return total;
}
#pragma code_seg()
