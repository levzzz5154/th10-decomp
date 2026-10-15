// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_00408620.cpp"

#pragma code_seg(".text$03context")
int __stdcall AccessorCompilerContext(ObjectAccessor_00408620** items, Vec3_00408620* other) {
    float t = 0.0f;
    int n = 4;
    while (n--) t += (*items++)->DistSq(other);
    return t != 0.0f;
}
#pragma code_seg()
