// Compiler context only; never selected as recovered game code.
#include "../../src/unreferenced/unassigned_0044c6e0.cpp"
#pragma code_seg(".text$03context")
void UnassignedSetContext_0044c6e0(UnassignedSet_0044c6e0* objects, int count,
                                   UnassignedValues_0044c6e0 values) {
    for (int index = 0; index < count; ++index) {
        objects[index].Set(values);
    }
}
#pragma code_seg()
