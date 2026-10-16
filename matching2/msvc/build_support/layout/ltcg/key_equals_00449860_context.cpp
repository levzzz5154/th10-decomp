// Compiler context only; its bytes are not recovered game code.
#include "../../../src/unreferenced/unassigned_449860.cpp"

#pragma code_seg(".text$03context")
int __stdcall Ctx(Handle2** a, Handle2** b, int count) {
    int sum = 0;
    while (count--) sum += (*a++)->Equals(*b++);
    return sum;
}
#pragma code_seg()
