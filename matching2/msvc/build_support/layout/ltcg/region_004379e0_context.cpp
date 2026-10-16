// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_4379e0.cpp"

#pragma code_seg(".text$03context")
int __stdcall CreateTextureCompilerContext(unsigned int count) {
    void* last = 0;
    while (count--) {
        last = CreateTexture(count, count + 1);
    }
    return (int)last;
}
#pragma code_seg()
