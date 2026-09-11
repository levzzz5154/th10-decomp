#include "../../src/unidentified/FUN_00404ce0_00404ce0.cpp"

#pragma code_seg(".text$03context")
int __stdcall GetField84CompilerContext(Field84Holder** holders, int count) {
    int total = 0;
    while (count--)
        total += (*holders++)->GetField84();
    return total;
}
#pragma code_seg()
