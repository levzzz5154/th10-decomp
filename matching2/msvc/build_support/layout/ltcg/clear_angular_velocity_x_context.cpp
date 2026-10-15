// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/FUN_00401f60_00401f60.cpp"

#pragma code_seg(".text$03context")
int __stdcall ClearAngularVelocityXCompilerContext(EntitySpin** objects, int count) {
    EntitySpin** cursor = objects;
    while (count--) {
        EntitySpin* object = *cursor++;
        object->ClearAngularVelocityX();
        object->ClearAngularVelocityX();
    }
    return 0;
}
#pragma code_seg()
