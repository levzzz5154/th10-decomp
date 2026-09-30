// Compiler context only; its bytes are not recovered game code.
#include "../../src/game/game_thread_queue.cpp"

#pragma code_seg(".text$03context")
int __stdcall Ctx(GameThread_00401530** t, const char** s, const Vec3_00401530* p, int n) {
    for (int i = 0; i < n; ++i) AppendRecord_00401530(t[i], s[i], p + i);
    return 0;
}
#pragma code_seg()
