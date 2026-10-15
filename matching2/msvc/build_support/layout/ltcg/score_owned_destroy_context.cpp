// Compiler context only; never selected as recovered game code.
#include "../../../src/game/ending/score_owned_destroy_0040b9d0.cpp"

#pragma code_seg(".text$03context")
void __stdcall ScoreOwnedObjectDestroyCompilerContext(ScoreOwnedObject** objects, int count) {
    for (int index = 0; index < count; ++index) {
        ScoreOwnedObject_Destroy(objects[index]);
    }
}
#pragma code_seg()
