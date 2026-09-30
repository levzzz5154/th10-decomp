// Compiler context only; its bytes are not recovered game code.
#include "../../src/unidentified/unassigned_0044bcd0.cpp"

#pragma code_seg(".text$03context")
int __stdcall Ctx(Vec2_0044bcd0** a, Vec2_0044bcd0** b, float f, int n) {
    while (n--) Rotate_0044bcd0(*a++, *b++, f);
    return 0;
}
#pragma code_seg()
