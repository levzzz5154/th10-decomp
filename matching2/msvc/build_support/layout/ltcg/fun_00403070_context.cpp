// Compiler context only; never selected as recovered game code.
#include "../../../src/game/background/background_on_draw.cpp"

#pragma code_seg(".text$03context")
int __stdcall FUN00403070CompilerContext(int* values, int count) {
    void (__fastcall* forward)(int) = BackGround_OnDraw;
    while (count--)
        forward(*values++);
    return 0;
}
#pragma code_seg()
