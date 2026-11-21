// Compiler context only; its bytes are not recovered game code.
#include "../../../src/core/zwave/archive_cursor.cpp"

#pragma code_seg(".text$03context")
int __stdcall Ctx(MusicReadCursor** c, bool* s, int n) {
    int r = 0;
    for (int i = 0; i < n; ++i) r += Rewind2(c[i], s[i]);
    return r;
}
#pragma code_seg()
