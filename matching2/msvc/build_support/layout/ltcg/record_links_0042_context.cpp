#include <string.h>
#include "../../../src/unreferenced/record_links_0042.cpp"
#pragma code_seg(".text$07context")
extern "C" int __stdcall RecordLinksCompilerContext(void** items, int count) {
    for (int index = 0; index < count; ++index)
        Init13(0, (RecordInit*)items[index]);
    for (int index = 0; index < count; ++index)
        Init14(0, (RecordInit2*)items[index]);
    for (int index = 0; index < count; ++index)
        ((ListHolder*)items[index])->Clear();
    return 0;
}
#pragma code_seg()
