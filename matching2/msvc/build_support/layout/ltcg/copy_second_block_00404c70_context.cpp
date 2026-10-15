// Compiler context only; its bytes are not recovered game code.
#include "../../../src/unreferenced/copy_second_block_00404c70.cpp"

#pragma code_seg(".text$03context")
int __stdcall Ctx(BlockPair** d, Block_00404c60** s, int n) {
    while (n--) CopySecond(*d++, *s++);
    return 0;
}
#pragma code_seg()
