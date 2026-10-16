#include "../../../src/unreferenced/publish_index.cpp"
#pragma code_seg(".text$09context")
extern "C" int __stdcall PublishIndexCompilerContext(void** items, int count) {
    for (int index = 0; index < count; ++index)
        Publish2((unsigned)index, (Indexed2*)items[index]);
    return 0;
}
#pragma code_seg()
