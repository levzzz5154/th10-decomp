// Compiler context only; never selected as recovered game code.
#include "../../src/unidentified/FUN_004052e0_004052e0.cpp"

#pragma code_seg(".text$03context")
int __stdcall ReleasePoolMaskCompilerContext(GameStateBulletPool** pools, int count) {
    GameStateBulletPool** cursor = pools;
    while (count--) {
        GameStateBulletPool* pool = *cursor++;
        pool->ReleasePoolMask();
        pool->ReleasePoolMask();
    }
    return 0;
}
#pragma code_seg()
