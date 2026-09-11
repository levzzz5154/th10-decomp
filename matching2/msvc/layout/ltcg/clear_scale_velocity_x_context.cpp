// Compiler context only; never selected as recovered game code.
#include "../../src/unidentified/FUN_00401f50_00401f50.cpp"

#pragma code_seg(".text$03context")
int __stdcall ClearScaleVelocityXCompilerContext(EntityMotion** objects, int count) {
    EntityMotion** cursor = objects;
    while (count--) {
        EntityMotion* object = *cursor++;
        object->ClearScaleVelocityX();
        object->ClearScaleVelocityX();
    }
    return 0;
}
#pragma code_seg()
