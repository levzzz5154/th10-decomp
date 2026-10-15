// Compiler context only; never selected as recovered game code.
#include "../../src/game/background/stage_objects_on_draw_background.cpp"

#pragma code_seg(".text$03context")
int __stdcall FUN00403060CompilerContext(int* values, int count) {
    void (__fastcall* forward)(int) = StageObjects_OnDrawBackground;
    while (count--)
        forward(*values++);
    return 0;
}
#pragma code_seg()
