// Compiler context only; its body is not recovered game code.
#include "../../src/game/update_player_00405750.cpp"
#include "../../src/unidentified/FUN_00405840_00405840.cpp"

#pragma code_seg(".text$05context")
int __stdcall PlayerUpdateCompilerContext(
        PlayerUpdate_00405750** players, int count) {
    while (count-- > 0) {
        PlayerUpdateCallback_00405840(*players++);
    }
    return 0;
}
#pragma code_seg()
