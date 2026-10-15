// Compiler context only; never selected as recovered game code.
#include "../../src/unreferenced/unassigned_004087e0.cpp"

#pragma code_seg(".text$03context")
int __stdcall AccessorCompilerContext(ObjectAccessor_004087e0** items, Vec3_004087e0* other) {
    int n = 4;
    while (n--) {
        (*items++)->Apply(other);
    }
    return 0;
}
#pragma code_seg()
