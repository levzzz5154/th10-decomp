// Compiler context only; never selected as recovered game code.
#include "../../../src/game/enemy/ecl_file_destructor.cpp"

#pragma code_seg(".text$03context")
int __stdcall BulletEntityReleaseResourceCompilerContext(
        EclFileDestroyView** entities, int count) {
    int released = 0;
    for (int index = 0; index < count; ++index) {
        entities[index]->DestroyEntries();
        ++released;
    }
    return released;
}
#pragma code_seg()
