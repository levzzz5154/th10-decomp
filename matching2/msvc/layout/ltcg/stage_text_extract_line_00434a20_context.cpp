// Compiler context only; never selected as recovered game code.
#include "../../src/game/title/stage_text_extract_line_00434a20.cpp"

#pragma code_seg(".text$03context")
int __stdcall StageTextExtractLineCompilerContext(char** cursors,
                                                   char** destinations,
                                                   int** remainings, int count) {
    int total = 0;
    while (count--) {
        *cursors = StageText_ExtractLine(*cursors, *destinations++, *remainings++);
        ++cursors;
        ++total;
    }
    return total;
}
#pragma code_seg()
