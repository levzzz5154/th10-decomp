// Compiler context only; never selected as recovered game code.
#include "../../src/unreferenced/unassigned_00438860.cpp"

#pragma code_seg(".text$03context")
int __stdcall AllocateCompilerContext(unsigned int count) {
    void* last = 0;
    while (count--) {
        last = Allocate_00438860(count);
    }
    return (int)last;
}
#pragma code_seg()
