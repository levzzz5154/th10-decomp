// Compiler context only; never selected as recovered game code.
#include "../../../src/game/front/front_delete.cpp"
#pragma code_seg(".text$03context")
void __stdcall DestroyOwnedCompilerContext_004148e0(Front** objects, int count) {
    for (int index = 0; index < count; ++index) Front_Delete(objects[index]);
}
#pragma code_seg()
