// Compiler context only; its bytes are not recovered game code.
#include "../../../src/game/ascii/add_late_string.cpp"

#pragma code_seg(".text$03context")
int __stdcall Ctx(GameThread_004015c0** t, const char** s, const Vec3_004015c0* p, int n) {
    for (int i = 0; i < n; ++i) AsciiManager_AddLateString(t[i], s[i], p + i);
    return 0;
}
#pragma code_seg()
