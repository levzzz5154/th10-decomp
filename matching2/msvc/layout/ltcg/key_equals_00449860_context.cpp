// Compiler context only; its bytes are not recovered game code.
#include "../../src/unidentified/unassigned_00449860.cpp"

#pragma code_seg(".text$03context")
int __stdcall Ctx(Handle_00449860** a, Handle_00449860** b, int count) {
    int sum = 0;
    while (count--) sum += (*a++)->Equals(*b++);
    return sum;
}
#pragma code_seg()
