// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/FUN.cpp_401f80.cpp"

#pragma code_seg(".text$03context")
int __stdcall ClearRotationXCompilerContext(EntityOrientation** objects, int count) {
    EntityOrientation** cursor = objects;
    while (count--) {
        EntityOrientation* object = *cursor++;
        object->ClearRotationX();
        object->ClearRotationX();
    }
    return 0;
}
#pragma code_seg()
