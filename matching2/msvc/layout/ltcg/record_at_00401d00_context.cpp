// Compiler context only; its bytes are not recovered game code.
#include "../../src/unreferenced/entry_at_00401d00.cpp"

#pragma code_seg(".text$03context")
int __stdcall Ctx(RecordTable_00401d00* table, int count) {
    int sum = 0;
    for (int i = 0; i < count; ++i) sum += table->At(i)->bytes[i];
    return sum;
}
#pragma code_seg()
