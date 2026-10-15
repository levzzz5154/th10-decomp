// Compiler context only; never selected as recovered game code.
#include "../../../src/game/title/title_delete.cpp"
#pragma code_seg(".text$03context")
void __stdcall DestroyOwnedCompilerContext_0042cdb0(Title** objects, int count) {
    for (int index = 0; index < count; ++index) Title_Delete(objects[index]);
}
#pragma code_seg()
