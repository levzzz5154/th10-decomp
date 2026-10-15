// Compiler context only; never selected as recovered game code.
#include "../../src/unreferenced/FUN_00418ac0_00418ac0.cpp"

#pragma code_seg(".text$03context")
int __stdcall ResetPairCompilerContext(GameAppStateReset_00418ac0** objects, int count) {
    GameAppStateReset_00418ac0** cursor = objects;
    while (count--) {
        GameAppStateReset_00418ac0* object = *cursor++;
        object->ResetPair();
        object->ResetPair();
    }
    return 0;
}
#pragma code_seg()
