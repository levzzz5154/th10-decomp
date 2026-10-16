// Compiler context only; its bytes are not recovered game code.
#include "../../../src/game/ascii/add_late_string.cpp"

#pragma code_seg(".text$03context")
int __stdcall Ctx(GameThread3** t, const char** s, const Vec33* p, int n) {
    for (int i = 0; i < n; ++i) AsciiManager_AddLateString(t[i], s[i], p + i);
    return 0;
}
#pragma code_seg()
