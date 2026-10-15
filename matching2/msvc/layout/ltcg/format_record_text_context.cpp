// Compiler context only; never selected as recovered game code.
#include "../../src/unreferenced/FUN_00401700_00401700.cpp"

#pragma code_seg(".text$03context")
int __stdcall FormatRecordTextCompilerContext(char** texts, int count) {
    int total = 0;
    for (int index = 0; index < count; ++index)
        total += (int)GameThread_FormatRecordText(texts[index]);
    return total;
}
#pragma code_seg()
