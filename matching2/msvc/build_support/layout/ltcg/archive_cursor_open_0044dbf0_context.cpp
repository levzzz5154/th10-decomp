// Compiler context only; its bytes are not recovered game code.
#include "../../../src/core/zwave/archive_cursor_open.cpp"

#pragma code_seg(".text$03context")
int __stdcall Ctx(ArchiveCursor_0044dbf0** c, const char** p, ArchiveEntry_0044dbf0** e, int n) {
    int r = 0;
    for (int i = 0; i < n; ++i) r += OpenCursor_0044dbf0(c[i], i, p[i], e[i]);
    return r;
}
#pragma code_seg()
