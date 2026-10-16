// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/FUN.cpp_401f70.cpp"

#pragma code_seg(".text$03context")
int __stdcall ClearScaleVelocityAlternateCompilerContext(EntityScaleAlternate** objects, int count) {
    EntityScaleAlternate** cursor = objects;
    while (count--) {
        EntityScaleAlternate* object = *cursor++;
        object->ClearScaleVelocityXAlternate();
        object->ClearScaleVelocityXAlternate();
    }
    return 0;
}
#pragma code_seg()
