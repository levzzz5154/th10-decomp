#include "../../../src/unreferenced/FUN.cpp_404990.cpp"

#pragma code_seg(".text$03context")
int __stdcall ReadField44CompilerContext(Field44Holder** holders, int count) {
    int total = 0;
    while (count--)
        total += (*holders++)->GetField44();
    return total;
}
#pragma code_seg()
