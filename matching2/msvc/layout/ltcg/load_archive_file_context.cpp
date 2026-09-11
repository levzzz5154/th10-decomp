// Compiler context only; never selected as recovered game code.
#include "../../src/platform/fun_0044b360_0044b360.cpp"

#pragma code_seg(".text$03context")
int __stdcall LoadArchiveFileCompilerContext(const char** names, int count, int* sizes) {
    int total = 0;
    for (int index = 0; index < count; ++index) {
        char* block = Archive_LoadFile(names[index], &sizes[index], 0);
        if (block)
            total += 1;
        block = Archive_LoadFile(names[index], 0, 0);
        if (block)
            total += 1;
    }
    return total;
}
#pragma code_seg()
