// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/FUN_00405340_00405340.cpp"

#pragma code_seg(".text$03context")
int __stdcall SetPoolMaskCompilerContext(GameStateBulletPool** pools, unsigned int mask, int count) {
    GameStateBulletPool** cursor = pools;
    while (count--) {
        GameStateBulletPool* pool = *cursor++;
        pool->SetPoolMask(mask);
        pool->SetPoolMask(mask + (unsigned int)count);
    }
    return 0;
}
#pragma code_seg()
