#include "../../src/unreferenced/publish_index_0040ada0.cpp"
#pragma code_seg(".text$09context")
extern "C" int __stdcall PublishIndexCompilerContext(void** items, int count) {
    for (int index = 0; index < count; ++index)
        Publish_0040ada0((unsigned)index, (Indexed_0040ada0*)items[index]);
    return 0;
}
#pragma code_seg()
