// Compiler context only; its bytes are not recovered game code.
#include "../../../src/unreferenced/unassigned_418850.cpp"

#pragma code_seg(".text$03context")
int __stdcall Ctx(const char** a, int n) {
    int s = 0;
    while (n--) s += *CopyToScratch(*a++);
    return s;
}
#pragma code_seg()
