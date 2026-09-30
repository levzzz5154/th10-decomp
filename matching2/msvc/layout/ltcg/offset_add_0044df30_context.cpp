// Compiler context only; its bytes are not recovered game code.
#include "../../src/unidentified/unassigned_0044df30.cpp"

#pragma code_seg(".text$03context")
int __stdcall Ctx(char** bases, int* offsets, int count) {
    int sum = 0;
    while (count--) sum += *AdvanceBytes_0044df30(*bases++, *offsets++);
    return sum;
}
#pragma code_seg()
