#include "../../../src/core/zwave/archive_cursor_read_model.cpp"
#pragma code_seg(".text$03context")
extern "C" __declspec(noinline) int __stdcall ArchiveCursorReadContext(
    ArchiveReadCursor** cursors,unsigned int* sizes,unsigned int* destinations,
    unsigned int* counts,int length) {
    int result=0;
    while (length--) result |= ArchiveCursorRead(*cursors++, *sizes++, *destinations++, counts++);
    return result;
}
#pragma code_seg()
