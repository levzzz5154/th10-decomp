#include "../../src/unidentified/flag_broadcast_0041fd90.cpp"
#pragma code_seg(".text$03context")
extern "C" int __stdcall FlagBroadcastCompilerContext(void** items, int count) {
    int total = 0;
    for (int index = 0; index < count; ++index)
        total += Update_0041fd90(0, (Flagged_0041fd90*)items[index]);
    return total;
}
#pragma code_seg()
