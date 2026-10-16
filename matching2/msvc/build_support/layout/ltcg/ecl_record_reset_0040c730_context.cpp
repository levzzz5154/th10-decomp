// Compiler context only; never selected as recovered game code.
#include "../../../src/game/enemy/ecl_record_reset.cpp"

#pragma code_seg(".text$03context")
int __stdcall EclRecordResetCompilerContext(EclRecord** records, int count) {
    while (count--)
        (*records++)->Reset();
    return 0;
}
#pragma code_seg()
