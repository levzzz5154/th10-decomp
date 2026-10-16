// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_4051d0.cpp"

#pragma code_seg(".text$03context")
int __stdcall RetireContext_004051d0(void** objects, int count) {
    int total = 0;
    for (int i = 0; i < count; ++i) {
        total += RetireBlock(objects[i]);
    }
    return total;
}
#pragma code_seg()
