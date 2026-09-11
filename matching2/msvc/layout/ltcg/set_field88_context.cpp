#include "../../src/unidentified/FUN_00404c50_00404c50.cpp"

#pragma code_seg(".text$03context")
int __stdcall SetField88CompilerContext(Field88Holder** holders, int* values, int count) {
    while (count--)
        (*holders++)->SetField88(*values++);
    return 0;
}
#pragma code_seg()
