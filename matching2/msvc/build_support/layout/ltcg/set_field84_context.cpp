#include "../../../src/unreferenced/FUN.cpp_404c90.cpp"

#pragma code_seg(".text$03context")
int __stdcall SetField84CompilerContext(Field84Setter** holders, int* values, int count) {
    while (count--)
        (*holders++)->SetField84(*values++);
    return 0;
}
#pragma code_seg()
