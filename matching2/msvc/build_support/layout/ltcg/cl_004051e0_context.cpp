// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_4051e0.cpp"

#pragma code_seg(".text$03context")
int __stdcall AllocateContext_004051e0(unsigned int* sizes, int count) {
    int total = 0;
    for (int i = 0; i < count; ++i) {
        total += (int)AllocateBlock(sizes[i]);
    }
    return total;
}
#pragma code_seg()
