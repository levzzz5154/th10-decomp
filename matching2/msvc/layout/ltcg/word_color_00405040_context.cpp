// Compiler context only; never selected as recovered game code.
// The array-walking caller is what makes the whole-program pass keep the
// record in ESI while leaving all six float arguments on the stack.
#include "../../src/game/recovery_initialize_word_color_00405040.cpp"

#pragma code_seg(".text$03context")
int __stdcall WordColorCompilerContext(WordColor_00405040** items, int count, float a0,
                                       float a1, float a2, float a3, float a4, float a5) {
    while (count--) {
        WordColor_00405040* item = *items++;
        item->Initialize(a0, a1, a2, a3, a4, a5);
    }
    return 0;
}
#pragma code_seg()
