// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/FUN_00418ac0_00418ac0.cpp"

#pragma code_seg(".text$03context")
int __stdcall ResetPairCompilerContext(GameAppStateReset** objects, int count) {
    GameAppStateReset** cursor = objects;
    while (count--) {
        GameAppStateReset* object = *cursor++;
        object->ResetPair();
        object->ResetPair();
    }
    return 0;
}
#pragma code_seg()
