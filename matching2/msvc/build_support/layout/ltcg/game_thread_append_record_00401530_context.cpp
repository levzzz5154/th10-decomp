// Compiler context only; its bytes are not recovered game code.
#include "../../../src/game/ascii/add_string.cpp"

#pragma code_seg(".text$03context")
int __stdcall Ctx(AsciiManagerQueueView** t, const char** s, const Vec32* p, int n) {
    for (int i = 0; i < n; ++i) AsciiManager_AddString(t[i], s[i], p + i);
    return 0;
}
#pragma code_seg()
