// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_408640.cpp"

#pragma code_seg(".text$03context")
int __stdcall AccessorCompilerContext(ObjectAccessor_00408640** items, Vec312* other) {
    int n = 4;
    float t = 0.0f;
    while (n--) t += (*items++)->LengthSq();
    return t != 0.0f;
    return 0;
}
#pragma code_seg()
