// Compiler context only; never selected as recovered game code.
#include "../../../src/core/zwave/archive_cursor_reset.cpp"

#pragma code_seg(".text$03context")
int __stdcall ArchiveCursorResetCompilerContext(
        ArchiveCursor** cursors, int count) {
    while (count--)
        (*cursors++)->Reset();
    return 0;
}
#pragma code_seg()
