// Compiler context only; never selected as recovered game code.
#include "../../src/unidentified/unassigned_004379e0.cpp"

#pragma code_seg(".text$03context")
int __stdcall CreateTextureCompilerContext(unsigned int count) {
    void* last = 0;
    while (count--) {
        last = CreateTexture_004379e0(count, count + 1);
    }
    return (int)last;
}
#pragma code_seg()
