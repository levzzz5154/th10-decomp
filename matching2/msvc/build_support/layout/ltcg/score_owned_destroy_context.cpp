// Compiler context only; never selected as recovered game code.
#include "../../../src/game/ending/ending_delete.cpp"

#pragma code_seg(".text$03context")
void __stdcall ScoreOwnedObjectDestroyCompilerContext(EndingObject** objects, int count) {
    for (int index = 0; index < count; ++index) {
        Ending_Delete(objects[index]);
    }
}
#pragma code_seg()
