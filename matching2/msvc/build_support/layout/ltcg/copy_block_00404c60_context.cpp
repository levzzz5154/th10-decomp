// Compiler context only; its bytes are not recovered game code.
#include "../../../src/unreferenced/unassigned_404c60.cpp"

#pragma code_seg(".text$03context")
int __stdcall Ctx(Block** d, Block** s, int n) {
    while (n--) CopyBlock(*d++, *s++);
    return 0;
}
#pragma code_seg()
