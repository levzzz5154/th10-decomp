// Compiler context only; its bytes are not recovered game code.
#include "../../../src/unreferenced/unassigned_004187f0.cpp"

#pragma code_seg(".text$03context")
int __stdcall Ctx(Vec3_004187f0** a, Vec3_004187f0** b, int n) {
    while (n--) PlayfieldToScreen_004187f0(*a++, *b++);
    return 0;
}
#pragma code_seg()
