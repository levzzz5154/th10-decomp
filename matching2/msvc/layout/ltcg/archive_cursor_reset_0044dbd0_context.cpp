// Compiler context only; never selected as recovered game code.
#include "../../src/game/archive_cursor_reset_0044dbd0.cpp"

#pragma code_seg(".text$03context")
int __stdcall ArchiveCursorResetCompilerContext(
        ArchiveCursor_0044dbd0** cursors, int count) {
    while (count--)
        (*cursors++)->Reset();
    return 0;
}
#pragma code_seg()
