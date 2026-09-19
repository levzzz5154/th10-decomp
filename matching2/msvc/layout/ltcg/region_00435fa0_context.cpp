// Compiler context only; never selected as recovered game code.
#include "../../src/unidentified/unassigned_00435fa0.cpp"

#pragma code_seg(".text$03context")
int __stdcall InitCompilerContext(unsigned int count) {
    while (count--) {
        Init_00435fa0(count);
    }
    return 0;
}
#pragma code_seg()
