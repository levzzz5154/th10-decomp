// Compiler context only; its bytes are not recovered game code.
#include "../../src/unidentified/unassigned_0040ce10.cpp"

#pragma code_seg(".text$03context")
int __stdcall Ctx(PairTable_0040ce10* table, int count, int tag, float v) {
    for (int i = 0; i < count; ++i) table->Set(i, tag, v);
    return 0;
}
#pragma code_seg()
