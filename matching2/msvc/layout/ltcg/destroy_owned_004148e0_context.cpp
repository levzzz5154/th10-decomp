// Compiler context only; never selected as recovered game code.
#include "../../src/game/hud_delete.cpp"
#pragma code_seg(".text$03context")
void __stdcall DestroyOwnedCompilerContext_004148e0(Hud** objects, int count) {
    for (int index = 0; index < count; ++index) Hud_Delete(objects[index]);
}
#pragma code_seg()
