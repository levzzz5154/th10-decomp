#include <string.h>
#include "../../../src/unreferenced/record_links_0042.cpp"
#pragma code_seg(".text$07context")
extern "C" int __stdcall RecordLinksCompilerContext(void** items, int count) {
    for (int index = 0; index < count; ++index)
        Init_0042aae0(0, (RecordInit_0042aae0*)items[index]);
    for (int index = 0; index < count; ++index)
        Init_0043bc20(0, (RecordInit_0043bc20*)items[index]);
    for (int index = 0; index < count; ++index)
        ((ListHolder_0042abd0*)items[index])->Clear();
    return 0;
}
#pragma code_seg()
