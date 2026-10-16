// Compiler context only; never selected as recovered game code.
#define code_seg(name) code_seg(".text$00g09")
#include "../../../src/core/main/game_main.cpp"
#undef code_seg

#pragma code_seg(".text$0actx")
// The link's entry: the one caller the whole-program link sees.
extern "C" int __stdcall RigEntry(void* instance, int show) {
    return GameMain2(instance, 0, 0, show);
}
#pragma code_seg()
