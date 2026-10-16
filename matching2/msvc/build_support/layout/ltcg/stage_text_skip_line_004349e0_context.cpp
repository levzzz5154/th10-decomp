// Compiler context only; never selected as recovered game code.
#include "../../../src/game/title/stage_text_skip_line.cpp"

#pragma code_seg(".text$03context")
int __stdcall StageTextSkipLineCompilerContext(char** cursors, int** remainings,
                                                int count) {
    int total = 0;
    while (count--) {
        total += StageText_SkipLine(*cursors++, *remainings++) != 0;
    }
    return total;
}
#pragma code_seg()
