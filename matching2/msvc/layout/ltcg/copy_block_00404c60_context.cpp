// Compiler context only; its bytes are not recovered game code.
#include "../../src/unidentified/unassigned_00404c60.cpp"

#pragma code_seg(".text$03context")
int __stdcall Ctx(Block_00404c60** d, Block_00404c60** s, int n) {
    while (n--) CopyBlock_00404c60(*d++, *s++);
    return 0;
}
#pragma code_seg()
