// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/FUN.cpp_405160.cpp"

#pragma code_seg(".text$03context")
int __stdcall f405160CompilerContext(RuntimeRecord** records, int count, int value) {
    for (int index = 0; index < count; ++index)
        records[index]->SetValue44(value);
    return 0;
}
#pragma code_seg()
